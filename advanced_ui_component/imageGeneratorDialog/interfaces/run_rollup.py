#!/usr/bin/env python3
# Copyright (c) 2025 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import re
import os
import subprocess

IMAGE_GENERATOR_CREATOR = '''\n
let __CreateErrorCode;
(function (__CreateErrorCode) {
    __CreateErrorCode.NO_ERROR = 0;
    __CreateErrorCode.IMAGES_OVERSIZE = 1;
    __CreateErrorCode.CONTENT_OVERSIZE = 2;
})(__CreateErrorCode || (__CreateErrorCode = {}));

export function __localImageGeneratorDialogCreator(options) {
    if (options) {
        if (options.images && options.images.length > 4) {
            return __CreateErrorCode.IMAGES_OVERSIZE;
        }
        if (options.content && (typeof options.content === 'string') && options.content.length > 600) {
            return __CreateErrorCode.CONTENT_OVERSIZE;
        }
    }
    console.info('[imageGenerator]', `will call loadImageGeneratorDialog`);
    ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
    loadImageGeneratorDialog(new ImageGeneratorDialog(undefined, {options: options}));
    ViewStackProcessor.StopGetAccessRecording();
    return __CreateErrorCode.NO_ERROR;
}
globalThis.__imageGeneratorDialogCreator = __localImageGeneratorDialogCreator;
'''

def convert_imports_to_requirenapi(line):
    new_line = ''
    if line.find('@ohos.') == -1:
        return new_line
    # import [\s+|\S+]+ from [\s+|\S+]+
    imported = line[line.find('import') + len('import') : line.find('from')]
    bundle_name = line[line.find('@ohos.') + len('@ohos.') : max(line.rfind('\''), line.rfind('\"'))]
    if imported.find('{') != -1 and imported.find('}') != -1:
        imported = imported[imported.find('{') + 1 : imported.find('}')].strip()
    else:
        imported = imported.strip()
    imported_modules = imported.split(',')
    for module in imported_modules:
        if module.find('as') == -1:
            new_line += 'const %s = requireNapi(\'%s\');\n' % (module.strip(), bundle_name)
        else:
            # import { moduleA as NameB } from "@ohos.xx.yy";
            real_name = module[0 : module.find('as')].strip()
            new_name = module[module.find('as') + len('as') : len(module)].strip()
            new_line += 'const %s = requireNapi(\'%s\').%s;\n' % (new_name, bundle_name, real_name)
    return new_line

def modify_js(file_to_modify):
    pattern = r'import[\s+|\S+]+from[\s+|\S+]+'
    lines = []
    with open(file_to_modify, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    with open(file_to_modify, 'w', encoding='utf-8') as file:
        # replace import to requireNapi begin
        line_number = 0
        for line in lines:
            if not re.match(pattern, line):
                break
            lines[line_number] = convert_imports_to_requirenapi(line)
            line_number = line_number + 1
        # replace import to requireNapi end
        # append imageGenerator creator func begin
        lines.append(IMAGE_GENERATOR_CREATOR)
        # append imageGenerator creator func end
        file.writelines(lines)

def main():
    if len(sys.argv) < 4:
        sys.exit(1)

    rollup_path = sys.argv[1]
    input_file = sys.argv[2]
    output_file = sys.argv[3]

    rollup_executable = os.path.join(rollup_path, 'rollup')

    if not os.path.isfile(rollup_executable):
        sys.exit(1)

    command = [rollup_executable, input_file, '--file', output_file]

    try:
        subprocess.run(command, check=True)
    except subprocess.CalledProcessError as e:
        sys.exit(1)
    else:
        modify_js(output_file)

if __name__ == "__main__":
    main()