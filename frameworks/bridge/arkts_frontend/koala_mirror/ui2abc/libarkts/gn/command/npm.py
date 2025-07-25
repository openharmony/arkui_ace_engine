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

import subprocess
import sys
import os
import shutil
import argparse

NPM_REPO = "https://repo.huaweicloud.com/repository/npm/"
 
parser = argparse.ArgumentParser(description="npm command parser")
parser.add_argument("--root-path", help="root directory of koala repo")
parser.add_argument("--project-path", help="project directory in koala repo")
parser.add_argument("--node-path", help="nodejs path")
parser.add_argument("--arklink-path", help="ark-link path")
parser.add_argument("--es2panda-path", help="es2panda path")
parser.add_argument("--stdlib-path", help="stdlib path")
parser.add_argument("--target-out-path", help="out directory of built target", default=None)
parser.add_argument("--built-file-path", help="result of building", default=None)
parser.add_argument("--npm-args", nargs='+', help="npm command args")

 
args = parser.parse_args()

root_path = args.root_path
project_path = args.project_path
node_path = args.node_path

target_out_path = args.target_out_path
built_file_path = args.built_file_path
npm_args = args.npm_args

env = os.environ.copy()
env_orig = env["PATH"]
env["PATH"] = f"{node_path}:{env['PATH']}"

koala_log = os.path.join(project_path, "koala_build.log")

def install(dir):
    os.chdir(dir)
    try:
        ret = subprocess.run(["npm", "install", "--registry", NPM_REPO, "--verbose"], capture_output=True, env=env, text=True, check=True)
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("install log:\n" + ret.stdout)
            f.close()
    except subprocess.CalledProcessError as e:
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.stderr + "\n")
            # In order to see errors in CI log
            print(f.read())
            f.close()

def npm_command(dir, command):
    os.chdir(dir)
    try:
        ret = subprocess.run(["npm"] + command, capture_output=True, env=env, text=True, check=True)
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("install log:\n" + ret.stdout)
            f.close()
    except subprocess.CalledProcessError as e:
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.output + "\n")
            f.close()

def main():
    install(root_path)
    npm_command(project_path, npm_args)

    if target_out_path and built_file_path:
        if not os.path.exists(built_file_path):
            print(f"Error: Built file not found at {built_file_path}")
            sys.exit(1)

        out_dir = os.path.join(target_out_path, os.path.basename(built_file_path))
        shutil.copy(built_file_path, out_dir)
    

if __name__ == '__main__':
    main()