#!/usr/bin/env python3
# Copyright (c) 2026 Huawei Device Co., Ltd.
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

"""Extract the original public error getter for the isolated page-text tests."""

import argparse
from pathlib import Path
import re


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    source = args.source.read_text(encoding="utf-8")
    match = re.search(
        r"^const char\* OH_ArkUI_NativeModule_GetErrorMessage\(\)\n\{.*?^\}",
        source, re.M | re.S)
    if not match:
        raise SystemExit("Original public error getter not found")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(
        '// Generated from node_utils.cpp; do not edit.\n'
        '#include "interfaces/native/node/node_model.h"\n'
        '#include "interfaces/native/native_interface.h"\n'
        f'{match.group(0)}\n', encoding="utf-8")


if __name__ == "__main__":
    main()
