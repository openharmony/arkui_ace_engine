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

import argparse
import shutil
import subprocess
import os
import sys

NPM_REPO = "https://repo.huaweicloud.com/repository/npm/"

parser = argparse.ArgumentParser(description="npm command parser")
parser.add_argument("--project-path", help="project directory in koala repo")
parser.add_argument("--node-path", help="nodejs path")
parser.add_argument("--arklink-path", help="ark-link path")
parser.add_argument("--es2panda-path", help="es2panda path")
parser.add_argument("--stdlib-path", help="stdlib path")
parser.add_argument("--target-out-path", help="out directory of built target")
parser.add_argument("--built-file-path", help="result of building")
parser.add_argument("--install", action="store_true", help="request npm install")
parser.add_argument("--install-path", help="path to install in")
parser.add_argument("--run-tasks", nargs='+', help="npm run tasks")

args = parser.parse_args()

project_path = args.project_path
koala_log = os.path.join(project_path, "koala_build.log")

if args.node_path is None:
    print("Error: --node-path is expected")
    sys.exit(1)

os.environ["PATH"] = f"{args.node_path}:{os.environ['PATH']}"

if args.es2panda_path:
    os.environ["ES2PANDA_PATH"] = args.es2panda_path
if args.arklink_path:
    os.environ["ARKLINK_PATH"] = args.arklink_path
if args.stdlib_path:
    os.environ["ETS_STDLIB_PATH"] = args.stdlib_path

os.environ["PANDA_SDK_PATH"] = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../../ui2abc/build/sdk")

def run(args, dir = None):
    os.chdir(dir or project_path)

    if os.environ.get("KOALA_LOG_STDOUT"):
        subprocess.run(["npm"] + args, env=os.environ, text=True, check=True, stderr=subprocess.STDOUT)
        return
    try:
        ret = subprocess.run(["npm"] + args, capture_output=True, env=os.environ, text=True, check=True)
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("install log:\n" + ret.stdout)
            f.close()
    except subprocess.CalledProcessError as e:
        with open(koala_log, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.stderr + "\n")
            f.close()
        print(f"Error: npm failed, errors logged to {koala_log}")
        raise

def install(dir = None):
    run(["install", "--registry", NPM_REPO, "--verbose"], dir or project_path)

def copy_target():
    if not os.path.exists(args.built_file_path):
        print(f"Error: Built file not found at {args.built_file_path}")
        sys.exit(1)
    shutil.copy(args.built_file_path, args.target_out_path)

def main():
    if args.install:
        install(args.install_path)
    if args.run_tasks:
        for task in args.run_tasks:
            run(["run", task])
    if args.target_out_path and args.built_file_path:
        copy_target()

if __name__ == '__main__':
    main()    
