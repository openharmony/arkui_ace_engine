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
import sys
import subprocess

def create_stamp_file(stamp_path):
    try:
        parent_dir = os.path.dirname(stamp_path)
        if parent_dir:
            os.makedirs(parent_dir, exist_ok=True)

        with open(stamp_path, "w") as f:
            f.write("npm install completed\n")
        return True
    except Exception as e:
        print(f"ERROR: Failed to create stamp file: {e}")
        return False

def main():
    if len(sys.argv) != 3:
        print("Usage: npm_install_guard.py <project_path> <stamp_path>")
        sys.exit(1)

    project_path = os.path.abspath(sys.argv[1])
    stamp_path = os.path.abspath(sys.argv[2])
    node_modules_path = os.path.join(project_path, "node_modules")

    if os.path.exists(stamp_path):
        if os.path.isdir(stamp_path):
            print(f"ERROR: {stamp_path} is a directory, should be a file!")
            return 1
        print("Stamp file exists, skipping npm install.")
        return 0

    if os.path.exists(node_modules_path):
        print("Node modules already exist, creating stamp file.")
        return 0 if create_stamp_file(stamp_path) else 1

    print("Node modules not found, running npm install...")
    try:
        subprocess.check_call(["npm", "install"], cwd=project_path)
    except subprocess.CalledProcessError as e:
        print(f"npm install failed with exit code {e.returncode}. Retry with registry...")
        print(e.stderr)
        return e.returncode

    if create_stamp_file(stamp_path):
        print("npm install completed.")
        return 0
    else:
        return 1

if __name__ == "__main__":
    sys.exit(main())