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
import time
import shutil
import subprocess

def main(argv):
    if len(argv) < 6:
        print("[NPM_OP INFO] Usage: python npm_run.py <cmd> <project_path> <js_out_path> <js_out_file> <target_gen_dir>")
        sys.exit(1)

    cmd = argv[1]
    project_path = os.path.abspath(argv[2])
    js_out_path = argv[3]
    js_out_file = argv[4]
    target_gen_dir = os.path.abspath(argv[5])

    built_file = os.path.join(project_path, js_out_path, js_out_file)
    output_file = os.path.join(target_gen_dir, js_out_file)

    # Determine the npm script to run. Currently only build_release supported.
    print(f"[NPM_OP INFO] Running npm script '{cmd}', changing directory to {project_path}.")
    os.chdir(project_path)
    try:
        subprocess.check_call(["npm", "run", cmd])
    except subprocess.CalledProcessError as e:
        print(f"[NPM_OP Error] npm run {cmd} failed with exit code {e.returncode}.")
        sys.exit(e.returncode)

    if not os.path.exists(built_file):
        print(f"[NPM_OP Error] Built file not found at {built_file}")
        sys.exit(1)

    if not os.path.exists(target_gen_dir):
        os.makedirs(target_gen_dir)

    try:
        shutil.copy(built_file, output_file)
        print(f"[NPM_OP INFO] File successfully copied to {output_file}")
    except Exception as e:
        print(f"[NPM_OP Error] Failed to copy file: {e}")
        sys.exit(1)

if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"[NPM_OP INFO] build time: {elapsed_time:.2f} seconds")
