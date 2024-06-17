#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# Copyright (c) 2023 Huawei Device Co., Ltd.
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
#

import argparse
import os
import subprocess
import sys

OUTPUT_TARGET = {
    "x86": "elf32-i386",
    "x64": "elf64-x86-64",
    "x86_64": "pe-x86-64",
    "arm": "elf32-littlearm",
    "arm64": "elf64-littleaarch64",
}

BUILD_ID_LINK_OUTPUT = {
    "x86": "i386",
    "x64": "i386:x86-64",
    "x86_64": "i386:x86-64",
    "arm": "arm",
    "arm64": "aarch64",
}


def main():
    parser = argparse.ArgumentParser(
        description="Translate and copy data file to object file"
    )
    parser.add_argument(
        "-e", "--objcopy", type=str, required=True, help="The path of objcopy"
    )
    parser.add_argument(
        "-a", "--arch", type=str, required=True, help="The architecture of target"
    )
    parser.add_argument(
        "-i", "--input", type=str, required=True, help="The path of input file"
    )
    parser.add_argument(
        "-o", "--output", type=str, required=True, help="The path of output target"
    )

    args = parser.parse_args()
    input_dir, input_file = os.path.split(args.input)

    cmd = [
        args.objcopy,
        "-I",
        "binary",
        "-B",
        BUILD_ID_LINK_OUTPUT[args.arch],
        "-O",
        OUTPUT_TARGET[args.arch],
        input_file,
        args.output,
    ]

    process = subprocess.Popen(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True,
        cwd=input_dir,
    )
    for line in iter(process.stdout.readline, ""):
        sys.stdout.write(line)
        sys.stdout.flush()

    process.wait()
    ret_code = process.returncode

    return ret_code


if __name__ == "__main__":
    sys.exit(main())
