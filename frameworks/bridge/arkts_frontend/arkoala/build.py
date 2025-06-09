#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2024 Huawei Device Co., Ltd.
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

# Description
#
# This script is invoked by the build system and does not need to be executed directly by the developer.
# First, it checks if --release is provided as an argument. This is the only allowed type for stateMgmt that is included in the build image.
# It then verifies if the node_modules folder exists. If not, npm install is executed.
# Afterward, npm run build_release is performed, which also generates generateGni.js
# The files_to_watch.gni file contains a list of input files from tsconfig.base.json.
# When any of these files are modified, the build system triggers this script to regenerate stateMgmt.js.

import os
import sys
import time
import shutil
import subprocess


def main(argv):
    if len(argv) < 4:
        print("Usage: python build.py <path_to_project> <build_path> <node_path> <output_target_path>")
        sys.exit(1)

    project_path = os.path.abspath(argv[1])
    build_path = os.path.abspath(argv[2])
    node_path = os.path.abspath(argv[3])
    output_target_path = os.path.abspath(argv[4])
    es2panda_path = os.path.abspath(argv[5])
    arklink_path = os.path.abspath(argv[6])
    ets_stdlib_path = os.path.abspath(argv[7])
    check_install_path = os.path.join(project_path, "arkoala-arkts", "node_modules")
    check_bin_path = os.path.join(check_install_path, ".bin")
    check_fast_arktsc = os.path.join(check_bin_path, "fast-arktsc")
    dist_path = os.path.join(build_path, "dist")
    logfile = os.path.join(dist_path, "koala_build.log")
    target_cmd = "arkoala:abc"
    if os.path.exists(logfile):
        try:
            os.remove(logfile)
        except OSError as e:
            print("remove log file filed!")
    npm_repo = "https://repo.huaweicloud.com/repository/npm/"
    if not os.path.exists(dist_path):
        os.makedirs(dist_path)
    with open(logfile, "a+") as f:
        f.write("koala build:\n")
        f.write(logfile + "\n")
        f.write("es2panda_path: " + es2panda_path + "\n")
        f.write("arklink_path:" + arklink_path + "\n")
        f.write("ets_stdlib_path:" + ets_stdlib_path + "\n")
        f.close()

    env = os.environ.copy()
    env_old_path = env["PATH"]
    env["PATH"] = f"{node_path}:{env['PATH']}"

    if (es2panda_path != ""):
        env["ES2PANDA_PATH"] = es2panda_path
    if (arklink_path != ""):
        env["ARKLINK_PATH"] = arklink_path
    if (ets_stdlib_path != ""):
        env["ETS_STDLIB_PATH"] = ets_stdlib_path

    try:
        ret = subprocess.run(["npm", "-v"], capture_output=True, env = env, text=True, check=True)
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("path env:" + env["PATH"] + "\n")
            f.write("npm version:" + ret.stdout)
            print(f"npm version: {ret.stdout}")
            f.close()
    except subprocess.CalledProcessError as e:
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.stderr + "\n")
            print(f"error message: {e.stderr}")
            f.close()
    os.chdir(project_path)
    # Check if `node_modules` exists. If yes skip npm install
    if not os.path.exists(check_install_path):
        try:
            ret = subprocess.run(["npm", "install", "--registry", npm_repo, "--verbose"], capture_output=True, env = env, text=True, check=True)
            with open(logfile, "a+") as f:
                f.write("\n")
                f.write("install log:\n" + ret.stdout)
                print(f"install log:\n {ret.stdout}")
                f.close()
        except subprocess.CalledProcessError as e:
            with open(logfile, "a+") as f:
                f.write("\n")
                f.write("error message: "+ e.stderr + "\n")
                print(f"error message: {e.stderr}")
                f.close()
    else:
        print(f"arkola node_modules directory exists, skip install")
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("arkola node_modules directory exists, skip install\n")
            f.close()

    if not os.path.exists(check_fast_arktsc):
        print(f"fast-arktsc not found!")
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("fast-arktsc not found!\n")
            f.close()

    # Run build arkoala
    try:
        ret = subprocess.run(["npm", "run", target_cmd, "--verbose"], capture_output=True, env = env, text=True, check=True)
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("build log:\n" + ret.stdout)
            print(f"build log:\n {ret.stdout}")
            f.close()
    except subprocess.CalledProcessError as e:
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("build log: "+ e.stdout + "\n")
            f.write("error message: "+ e.stderr + "\n")
            print(f"build log:\n {ret.stdout}")
            print(f"error message: {e.stderr}")
            f.close()
    # restore old env
    env["PATH"] = env_old_path

    abc_file = "arkoala.abc"
    built_file = os.path.join(project_path, "arkoala-arkts", "build", abc_file)

    if not os.path.exists(built_file):
        print(f"Error: Built file not found at {built_file}")
        sys.exit(1)

    dist_file = os.path.join(dist_path, abc_file)
    output_file = os.path.join(output_target_path, abc_file)
    try:
        shutil.copy(built_file, dist_file)
        shutil.copy(built_file, output_file)
        print(f"Arkoala: File successfully copied to {dist_file}")
        with open(logfile, "a+") as f:
            f.write("\n")
            f.write("Arkoala: File successfully copied to " + dist_file + " \n")
            f.write("Arkoala: File successfully copied to " + output_file + " \n")
            f.close()
    except Exception as e:
        print(f"Error: Failed to copy file: {e}")
        sys.exit(1)

if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: build time: {elapsed_time:.2f} seconds")
