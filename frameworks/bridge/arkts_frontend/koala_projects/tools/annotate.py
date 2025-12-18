#!/usr/bin/env python
# -*- coding: utf-8 -*-
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

import os
import glob
import shutil
import re
from pathlib import Path

COMMON_SRC_FILE_NAME = "generated/component/common.ets"

class Config:
    def __init__(self):
        self.inputDir = "./src"
        self.outputDir = "./ets"
        self.include = ["./src/**/*"]
        self.exclude = []
        self.baseUrl = "."
        self.fileExtension = None
        self.memoTypeImport = None
        self.commonMethodSrc = ""

memoImport = "@koalaui/runtime/annotations"

def convert_memo(text: str, memo_import: str, memo_type_import: str) -> str:
    replacements = {
        "/** @memo */": "@memo",
        "/** @memo:intrinsic */": "@memo_intrinsic",
        "/** @memo:stable */": "@memo_stable",
        "/** @memo:entry */": "@memo_entry",
        "/** @skip:memo */": "@memo_skip"
    }
    result = text
    for k, v in replacements.items():
        result = result.replace(k, v)
    # if result == text:
    #     return result
    if memo_type_import:
        result = f'import {{ __memo_id_type, __memo_context_type }} from "{memo_type_import}"\n' + result
    return f'import {{ memo, memo_intrinsic, memo_entry, memo_stable, memo_skip }} from "{memo_import}"\n' + result


# return argument names from argument statement, and additionaly adds type to import to types_to_import map.
def extract_args_from_parameter(args, types_to_import):
    arg_names = []
    types = ""
    while args.find(':') > 0:
        colon_position = args.find(':')
        name = args[:colon_position]
        arg_names.append(name.replace('?', '').strip())
        # find ',' position that is not within () or <>
        comma_pos = -1
        closure_depth = 0
        for arg_idx in range(len(args)):
            if args[arg_idx] == ',' and closure_depth == 0:
                comma_pos = arg_idx
                break
            elif args[arg_idx] == '(' or args[arg_idx] == '<':
                closure_depth += 1
            elif args[arg_idx] == ')' or args[arg_idx] == '>':
                closure_depth -= 1
        if comma_pos == -1:
            types += args[colon_position:]
            break
        types += args[colon_position:comma_pos]
        args = args[comma_pos+1:]
    types = list(
        filter(lambda t: len(t) > 0 and t not in [ 
            'undefined', 'boolean', 'string', 'number', 'int', 'double', 'long', 'Array', 'void' ], 
        re.sub(r"[<>:|()=,?]", ' ', types).split(' ')))
    for arg_type in types:
        if arg_type.find('.') > 0:
            types_to_import.add(arg_type[:arg_type.find('.')])
        else:
            types_to_import.add(arg_type)
    return arg_names


# Reads CommonMethod and adds its implementation to customComponent.ets
def convert_common_methods(text: str, common_text: str) -> str:
    # Find CommonMethod from common_text
    lines = common_text.splitlines()
    common_methods_start = False
    types_to_import = set({})
    new_text = ''
    for line in lines:
        new_text += line + '\n'
        if line.startswith("export interface CommonMethod"):
            common_methods_start = True
        elif line.startswith("} // end CommonMethod"):
            common_methods_start = False
        elif common_methods_start:
            if line.strip().endswith(": this {"):
                method_name = line[:line.find('(')].strip()
                if (method_name.startswith('public ')):
                    method_name = method_name[len('public '):].strip()
                args = line[line.find('(') + 1:line.rfind(')')]
                # find argument names and count
                arg_names = extract_args_from_parameter(args, types_to_import)
                new_text += f"""        const commonStyle: Array<(instance: CommonMethod) => void> | undefined = this.__get__commonStyles__Internal();
        if (commonStyle) {{
          (commonStyle as Array<(instance: CommonMethod) => void>).push((instance: CommonMethod): void => instance.{method_name}({', '.join(arg_names)}));
          return this;
        }}
""" 
    return new_text

def get_matching_files(patterns, root_dir):
    matched = set()
    for pattern in patterns:
        # 把pattern相对路径转成绝对路径glob匹配
        full_pattern = os.path.join(root_dir, os.path.relpath(pattern, start=root_dir))
        files = glob.glob(full_pattern, recursive=True)
        for f in files:
            if os.path.isfile(f):
                matched.add(os.path.abspath(f))
    return matched

def main(options: Config):
    os.chdir(options.baseUrl)
    input_dir = os.path.abspath(options.inputDir)
    output_dir = os.path.abspath(options.outputDir)
    if os.path.exists(output_dir):
        shutil.rmtree(output_dir)

    # 递归获取所有文件，保持相对路径
    all_files = []
    for root, _, files in os.walk(input_dir):
        for file in files:
            full_path = os.path.join(root, file)
            rel_path = os.path.relpath(full_path, input_dir)
            all_files.append((full_path, rel_path))

    include_files = get_matching_files(options.include, ".")
    exclude_files = get_matching_files(options.exclude, ".")

    os.makedirs(output_dir, exist_ok=True)

    finds_common_method = False
    for full_path, rel_path in all_files:
        abs_path = os.path.abspath(full_path)

        # 判断是否include且不在exclude里
        if abs_path in include_files and abs_path not in exclude_files:
            with open(full_path, "r", encoding="utf-8") as f:
                text = f.read()
            new_text = convert_memo(text, memoImport, options.memoTypeImport)

            if COMMON_SRC_FILE_NAME in full_path:
                # Reads CommonMethod from src/component/common.ets
                finds_common_method = True
                common_path = config.commonMethodSrc
                with open(common_path, "r", encoding="utf-8") as f:
                    common_text = f.read()
                new_text = convert_common_methods(new_text, common_text)

            output_file = os.path.join(output_dir, rel_path)
            if options.fileExtension:
                base, _ = os.path.splitext(output_file)
                output_file = base + options.fileExtension

            if os.path.exists(output_file):
                with open(output_file, "r", encoding="utf-8") as f:
                    old_text = f.read()
                if old_text == new_text:
                    # 内容没变不写文件
                    continue

            print(f"Writing to: {output_file}")
            os.makedirs(os.path.dirname(output_file), exist_ok=True)
            with open(output_file, "w", encoding="utf-8") as f:
                f.write(new_text)
        else:
            print(f"Skipped (not in include or excluded): {rel_path}")
    if not finds_common_method and len(options.commonMethodSrc) > 0:
        print(f"[ERROR] failed to transform common method.")
        raise Exception("failed to transform common method.")

if __name__ == "__main__":
    import sys
    import json

    if len(sys.argv) == 3:
        base_url_path = os.path.abspath(sys.argv[1])
        config_path = os.path.abspath(sys.argv[2])
        with open(config_path, "r", encoding="utf-8") as f:
            config_data = json.load(f)
        config = Config()
        config.baseUrl = base_url_path
        for k, v in config_data.items():
            setattr(config, k, v)
        main(config)
    elif len(sys.argv) == 2:
        base_url_path = os.path.abspath(sys.argv[1])
        config = Config()
        config.baseUrl = base_url_path
        main(config)
    else:
        main(Config())
