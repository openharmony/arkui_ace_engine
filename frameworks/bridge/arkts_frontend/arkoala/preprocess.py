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

import re
import os
import shutil
from collections import defaultdict


def get_ts_files(directory):
    return set(
        f for f in os.listdir(directory)
        if os.path.isfile(os.path.join(directory, f)) and f.endswith('.ts')
    )


def merge_component(handwritten_path: str, generated_path: str) -> None:
    if not os.path.exists(handwritten_path) or not os.path.exists(generated_path):
        return

    handwritten_files = get_ts_files(handwritten_path)
    generated_files = get_ts_files(generated_path)

    for file in handwritten_files:
        handwritten_file_path = os.path.join(handwritten_path, file)
        generated_file_path = os.path.join(generated_path, file)

        if file in generated_files:
            merge_file(generated_file_path, handwritten_file_path)
        else:
            shutil.copy(handwritten_file_path, generated_file_path)
    return


def merge_file(f1: str, f2: str) -> None:
    with open(f1, 'r') as file1:
        lines1 = file1.readlines()
    with open(f2, 'r') as file2:
        lines2 = file2.readlines()

    def process_lines(lines):
        import_dict = defaultdict(set)
        non_import = []
        pattern = re.compile(
            r'^import\s*{([^}]+)}\s*from\s*(["\'])(.*?)\2\s*;?\s*$')
        for line in lines:
            stripped = line.strip()
            match = pattern.match(stripped)
            if match:
                symbols_str, quote, module = match.groups()
                symbols = [s.strip() for s in symbols_str.split(',')]
                import_dict[module].update(symbols)
            else:
                non_import.append(line)
        return import_dict, non_import

    imports1, non_import1 = process_lines(lines1)
    imports2, non_import2 = process_lines(lines2)

    merged_imports = defaultdict(set)
    for module in {**imports1, **imports2}:
        merged_imports[module].update(imports1.get(module, set()))
        merged_imports[module].update(imports2.get(module, set()))

    import_lines = [
        f'import {{ {", ".join(sorted(symbols))} }} from "{module}";\n'
        for module, symbols in sorted(merged_imports.items())
    ]

    with open(f1, 'w') as f:
        f.writelines(import_lines + non_import1 + non_import2)

    return
