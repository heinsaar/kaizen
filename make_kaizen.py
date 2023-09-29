import datetime
import re
import os

# Collects header files from specified dirs
def collect_main_header_files(dirs):
    header_files = []
    alpha_header = None # separate out the alpha.h file
    for dir in dirs:
        for filename in os.listdir(dir):
            if filename.endswith('.h'):
                file_path = os.path.join(dir, filename)
                if filename == 'alpha.h' and dir.endswith('zen/datas'):
                    alpha_header = file_path
                else:
                    header_files.append(file_path)
    return header_files, alpha_header

def collect_composite_headers(composites_dir):
    header_files = []
    composite_includes = set()
    for filename in os.listdir(composites_dir):
        if filename.endswith('.h'):
            header_file = os.path.join(composites_dir, filename)
            include_directives, _ = parse_header_file(header_file)
            composite_includes.update(include_directives)
            header_files.append(header_file)
    return header_files, composite_includes

# Separates license, include directives and code
def parse_header_file(header_file):
    include_directives = set()
    code_content = []
    with open(header_file, 'r') as input_file:
        lines = input_file.readlines()
        skipping_license = True # to skip license comments at the top of files
        for line in lines:
            if skipping_license:
                if line.strip().startswith('//'):
                    continue # license part, so skip
                else:
                    skipping_license = False # end of license comment section, prepare for reading code

            if '#pragma once' in line:
                continue
            
            # If line #includes any non-standard C++ headers (like Kaizen-internal), skip it
            if re.match(r'#include\s+"(.*)"', line):
                continue # skip non-standard headers

            match_include = re.match(r'#include\s+[<](.*)[>]', line)
            if match_include:
                include_directives.add(line.strip())
            else:
                code_content.append(line)
    return include_directives, code_content

# Reads license and turns it into a ready comment
def read_license(filename):
    with open(filename, 'r') as license_file:
        lines = license_file.readlines()
        # Return with comment characters added if they're not present
        return ['// ' + line if not line.startswith('// ') else line for line in lines]

def compact_namespace_zen(code_content):
    first_namespace_found      = False
    last_closing_namespace_idx = None
    compacted_code_content     = []
    
    # Find the index of the last "} // namespace zen"
    for idx, line in reversed(list(enumerate(code_content))):
        if "} // namespace zen" in line:
            last_closing_namespace_idx = idx
            break
            
    # Create a new list for compacted code content
    for idx, line in enumerate(code_content):
        if "namespace zen {" in line:
            if not first_namespace_found:
                first_namespace_found = True
                compacted_code_content.append(line)
            continue
        elif "} // namespace zen" in line:
            if idx == last_closing_namespace_idx:
                compacted_code_content.append(line)
            continue
        else:
            compacted_code_content.append(line)
    
    return compacted_code_content

def deflate(code_content):
    deflated_code_content = []
    prev_was_empty = False # keep track of whether the previous line was empty
    
    for line in code_content:
        if line.strip() == '':
            if not prev_was_empty:
                deflated_code_content.append(line)
            prev_was_empty = True
        else:
            deflated_code_content.append(line)
            prev_was_empty = False
            
    return deflated_code_content

# Produces the final resulting kaizen library single header file
def write_output_file(filename, license_text, include_directives, code_content):
    code_content = compact_namespace_zen(code_content)
    code_content = deflate(code_content)
    
    with open(filename, 'w') as output_file:
        now = datetime.datetime.now()
        output_file.write('// FILE GENERATED ON: ' + now.strftime("%d.%m.%Y %H:%M:%S") + '\n//\n')
        output_file.writelines(license_text)
        output_file.write('\n#pragma once\n\n')
        output_file.write('// Since the order of these #includes doesn\'t matter,\n// they\'re sorted in descending length for aesthetics\n')
        for include_directive in sorted(include_directives, key=len, reverse=True):
            output_file.write(include_directive + '\n')
        # Remove all leading empty lines but one that come right after the #include directives:
        while code_content and code_content[0].strip() == '':
            code_content.pop(0)
        code_content.insert(0, '\n')
        output_file.writelines(code_content)
        os.chmod(filename, 0o444) # make readonly

if __name__ == '__main__':
    project_dir = os.path.dirname(os.path.abspath(__file__))
    
    datas_dir     = os.path.join(project_dir, 'zen/datas')
    function_dir  = os.path.join(project_dir, 'zen/functions')
    composites_dir = os.path.join(project_dir, 'zen/composites')

    license_file = os.path.join(project_dir, 'LICENSE.txt')

    header_files, alpha_header = collect_main_header_files([datas_dir, function_dir])
    composite_headers, composite_includes = collect_composite_headers(composites_dir)
    
    license_text = read_license(license_file)

    all_include_directives = set()
    all_code_content = []

    # Process 'alpha.h' separately and ensure its content is added first
    if alpha_header:
        _, alpha_content = parse_header_file(alpha_header)
        all_code_content.extend(alpha_content) # ensure alpha.h content is first
    
    # Process regular headers
    for header_file in header_files:
        include_directives, code_content = parse_header_file(header_file)
        all_include_directives.update(include_directives)
        all_code_content.extend(code_content)
        
    # Process composite headers
    for composite_header in composite_headers:
        _, code_content = parse_header_file(composite_header)
        all_code_content.extend(code_content)
        
    # Remove headers included in composite headers
    all_include_directives -= composite_includes

    # Generate the final result of the Kaizen library header file
    write_output_file('kaizen.h', license_text, all_include_directives, all_code_content)

# end of make_kayzen.py