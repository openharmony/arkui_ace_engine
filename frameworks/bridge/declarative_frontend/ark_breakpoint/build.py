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
    if len(argv) < 4:
        print("Usage: python script.py <path_to_project> <path_to_node_modules> <js_output_path> [--release]")
        sys.exit(1)

    # Determine if it's a release build
    is_release = len(argv) > 4 and argv[4] == "--release"
    print(f": is_release set to {is_release}")

    # If not a release build, print an error and exit
    if not is_release:
        print("ERROR: ark_breakpoint/build.py requires a release build. Exiting...")
        sys.exit(1)

    project_path = os.path.abspath(argv[1])
    node_modules_path = os.path.abspath(argv[2])
    js_output_path = os.path.abspath(argv[3])

    output_file = os.path.join(js_output_path, "WindowSizeLayoutBreakpoint.js")

    print(f"ark_breakpoint: Changing directory to {project_path}. Out dir = {js_output_path}")
    os.chdir(project_path)

    if not os.path.exists(node_modules_path):
        print(f"ERROR: node_modules directory not found at {node_modules_path}")
        print("This should have been created by ark_breakpoint_npm_install action.")
        print("Check that :ark_breakpoint_npm_install is in the deps of :run_ark_breakpoint_build")
        sys.exit(1)
    else:
        print(f"ark_breakpoint: node_modules directory exists at {node_modules_path}")

    # Determine the npm script to run. Currently only build_release supported.
    script = "build"
    print(f"ark_breakpoint: Running npm script '{script}'")

    try:
        subprocess.check_call(["npm", "run", script])
    except subprocess.CalledProcessError as e:
        print(f"Error: npm run {script} failed with exit code {e.returncode}.")
        print("Error: Ark breakpoint build failed.")
        sys.exit(e.returncode)

    source_folder = "../engine"
    built_file = os.path.join(project_path, source_folder, "WindowSizeLayoutBreakpoint.js")

    if not os.path.exists(built_file):
        print(f"Error: Built file not found at {built_file}")
        sys.exit(1)

    if not os.path.exists(js_output_path):
        os.makedirs(js_output_path)

    try:
        shutil.copy(built_file, output_file)
        print(f"ark_breakpoint: File successfully copyed to {output_file}")
    except Exception as e:
        print(f"Error: Failed to copy file: {e}")
        sys.exit(1)

if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"ark_breakpoint: build time: {elapsed_time:.2f} seconds")
