import datetime
import re
import os

# Directories to look for header files
dirs = [
    '../functions',
    '../types'
]

header_files = []

# Populate header_files dynamically from specified dirs
for directory in dirs:
    for filename in os.listdir(directory):
        if filename.endswith('.h'):
            header_files.append(os.path.join(directory, filename))

include_directives = set()
license_text       = []
code_content       = []
has_pragma_once    = False

for header_file in header_files:
    with open(header_file, 'r') as input_file:
        lines = input_file.readlines()
        skipping_license = True  # to skip license comments at the top of files
        
        for line in lines:
            if skipping_license:
                if line.strip().startswith('//'):
                    continue  # license part, so skip
                else:
                    skipping_license = False  # end of license comment section, prepare for reading code

            if '#pragma once' in line:
                has_pragma_once = True
                continue

            match_include = re.match(r'#include\s+["<](.*)[">]', line)
            if match_include:
                include_directives.add(line.strip())
            else:
                code_content.append(line)

# Read license text from LICENSE.txt
with open('../LICENSE.txt', 'r') as license_file:
    license_text = license_file.readlines()
    # Add comment characters if they're not present
    license_text = ['// ' + line if not line.startswith('// ') else line for line in license_text]

with open('kaizen.h', 'w') as kaizenh:
    now = datetime.datetime.now()
    kaizenh.write('// FILE AUTO-GENERATED ON: ' + now.strftime("%d.%m.%Y %H:%M:%S") + '\n//\n')
    kaizenh.writelines(license_text)
    kaizenh.write('\n#pragma once\n\n')
    
    for include_directive in sorted(include_directives):
        kaizenh.write(include_directive + '\n')

    # Remove all leading empty lines but one
    # that come right after the #include directives
    while code_content and code_content[0].strip() == '':
        code_content.pop(0)
    code_content.insert(0, '\n')
        
    kaizenh.writelines(code_content)