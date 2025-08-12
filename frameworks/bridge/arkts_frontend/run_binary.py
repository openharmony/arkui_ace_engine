#!/usr/bin/env python3
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


"""
A script to run binary commands in GN build actions.
This script takes the binary name as the first argument,
followed by any arguments to pass to the binary.
If the first argument is in the format 'path-env=xxxx',
it will add xxxx to the beginning of the PATH environment variable.
"""

import os
import sys
import subprocess
import platform

def main():
    if len(sys.argv) < 2:
        print("Error: No binary specified")
        print("Usage: run_binary.py <binary_name> [args...]")
        print("       run_binary.py path-env=<path> <binary_name> [args...]")
        return 1

    # Check if the first argument is a path-env parameter
    args_start_index = 1
    if sys.argv[1].startswith("path-env="):
        # Extract the path from the parameter
        path_to_add = sys.argv[1].split("=", 1)[1]
        # Add the path to the beginning of the PATH environment variable
        current_path = os.environ.get("PATH", "")
        os.environ["PATH"] = path_to_add + os.pathsep + current_path
        print(f"Added '{path_to_add}' to the beginning of PATH")

        args_start_index = 2
        
        if len(sys.argv) < 3:
            print("Error: No binary specified after path-env parameter")
            print("Usage: run_binary.py path-env=<path> <binary_name> [args...]")
            return 1

    # The binary name is now at args_start_index
    binary = sys.argv[args_start_index]

    # All remaining arguments are passed to the binary
    args = sys.argv[args_start_index + 1:]

    # Construct the full command
    cmd = [binary] + args
    print("start run cmd:")
    print(" ".join(cmd))

    try:
        ret = subprocess.run(cmd, capture_output=True, text=True, check=True)
        print(f"run cmd: {ret.stdout}")
        return 0
    except subprocess.CalledProcessError as e:
        print(f"Error executing command: {e}", file=sys.stderr)
        print(f"error message: {e.stderr}")
        print(f"output message: {e.output}")
        return 1

if __name__ == "__main__":
    sys.exit(main())