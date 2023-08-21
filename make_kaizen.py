import re

header_files = [
    'containers/list.h',
    'containers/vector.h',
]

include_directives = set()
license_text       = []
code_content       = []
has_pragma_once    = False

for header_file in header_files:
    with open(header_file, 'r') as input_file:
        lines = input_file.readlines()
        is_license = True
        for line in lines:
            if is_license and line.strip().startswith('//'):
                if header_file == header_files[0]:
                    license_text.append(line)
                continue
            elif is_license:
                is_license = False

            if '#pragma once' in line:
                has_pragma_once = True
                continue

            match_include = re.match(r'#include\s+["<](.*)[">]', line)
            if match_include:
                include_directives.add(line.strip())
            else:
                code_content.append(line)

with open('kaizen.h', 'w') as kaizenh:
    kaizenh.write('#pragma once\n\n')
    kaizenh.writelines(license_text)
    kaizenh.write('\n')
    
    for include_directive in sorted(include_directives):
        kaizenh.write(include_directive + '\n')

    # Remove all leading empty lines but one
    # that come right after the #include directives
    while code_content and code_content[0].strip() == '':
        code_content.pop(0)
    code_content.insert(0, '\n')
        
    kaizenh.writelines(code_content)