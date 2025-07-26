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

# Description
#
# This script is invoked by the build system and does not need to be executed directly by the developer.
# First, it checks if --release is provided as an argument. This is the only allowed type for stateMgmt
# that is included in the build image. It then verifies if the node_modules folder exists. If not, npm
# install is executed. Afterward, npm run build_release is performed, which also generates generateGni.js
# The files_to_watch.gni file contains a list of input files from tsconfig.base.json. When any of these
# files are modified, the build system triggers this script to regenerate stateMgmt.js.

import os
import sys
import json
import time
import shutil
import subprocess
from typing import Dict, List

from preprocess import merge_component


TARGET_CMD = "arkoala:abc"
ABC_FILE = "arkoala.abc"
NPM_REPO = "https://repo.huaweicloud.com/repository/npm/"


class Paths:
    def __init__(self):
        self.project_path = None
        self.build_path = None
        self.node_path = None
        self.output_target_path = None
        self.es2panda_path = None
        self.ohos_ets_api_path = None
        self.ohos_ets_arkts_path = None
        self.arklink_path = None
        self.ets_stdlib_path = None
        self.innerkits_path = None
        self.check_install_path = None
        self.check_bin_path = None
        self.dist_path = None
        self.logfile = None
        self.built_path = None
        self.check_fast_arktsc = None
        self.arkui_ohos_path = None


def parse_argv(argv) -> Paths:
    """
    parse command line arguments
    """
    if len(argv) < 4:
        print("Usage: python build.py <path_to_project> <build_path> <node_path> <output_target_path>")
        sys.exit(1)

    path = Paths()
    path.project_path = os.path.abspath(argv[1])
    path.build_path = os.path.abspath(argv[2])
    path.node_path = os.path.abspath(argv[3])
    path.output_target_path = os.path.abspath(argv[4])
    path.es2panda_path = os.path.abspath(argv[5])
    path.ohos_ets_api_path = os.path.abspath(argv[6])
    path.ohos_ets_arkts_path = os.path.abspath(argv[7])
    path.arklink_path = os.path.abspath(argv[8])
    path.ets_stdlib_path = os.path.abspath(argv[9])
    path.innerkits_path = os.path.abspath(argv[10])
    path.check_install_path = os.path.join(path.project_path, "arkoala-arkts", "node_modules")
    path.check_bin_path = os.path.join(path.check_install_path, ".bin")
    path.check_fast_arktsc = os.path.join(path.check_bin_path, "fast-arktsc")
    path.dist_path = os.path.join(path.build_path, "dist")
    path.logfile = os.path.join(path.dist_path, "koala_build.log")
    path.arkui_ohos_path = os.path.join(path.project_path, "arkoala-arkts" ,"arkui-ohos-preprocess")
    return path


def prebuilt_dist(path: Paths):
    """
    create log file and prebuilt dist path
    """
    if os.path.exists(path.logfile):
        try:
            os.remove(path.logfile)
        except OSError as e:
            print("remove log file filed!")
    if not os.path.exists(path.dist_path):
        os.makedirs(path.dist_path)
    with open(path.logfile, "a+") as f:
        f.write("koala build:\n")
        f.write(path.logfile + "\n")
        f.write("es2panda_path: " + path.es2panda_path + "\n")
        f.write("arklink_path:" + path.arklink_path + "\n")
        f.write("ets_stdlib_path:" + path.ets_stdlib_path + "\n")
        f.close()


def change_env_path(env, path: Paths):
    """
    change env path for es2pand and arklink process
    """
    env["PATH"] = f"{path.node_path}:{env['PATH']}"
    if (path.es2panda_path != ""):
        env["ES2PANDA_PATH"] = path.es2panda_path
    if (path.arklink_path != ""):
        env["ARKLINK_PATH"] = path.arklink_path
    if (path.ets_stdlib_path != ""):
        env["ETS_STDLIB_PATH"] = path.ets_stdlib_path
    try:
        ret = subprocess.run(["npm", "-v"], capture_output=True, env = env, text=True, check=True)
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("path env:" + env["PATH"] + "\n")
            f.write("npm version:" + ret.stdout)
            print(f"npm version: {ret.stdout}")
            f.close()
    except subprocess.CalledProcessError as e:
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("error message: "+ e.stderr + "\n")
            print(f"error message: {e.stderr}")
            f.close()
    os.chdir(path.project_path)


def check_node_modules(env, path: Paths):
    """
    Check if `node_modules` exists. If yes skip npm install
    """
    if not os.path.exists(path.check_install_path):
        try:
            ret = subprocess.run(
                ["npm", "install", "--registry", NPM_REPO, "--verbose"],
                capture_output=True,
                env = env,
                text=True,
                check=True
            )
            with open(path.logfile, "a+") as f:
                f.write("\n")
                f.write("install log:\n" + ret.stdout)
                print(f"install log:\n {ret.stdout}")
                f.close()
        except subprocess.CalledProcessError as e:
            with open(path.logfile, "a+") as f:
                f.write("\n")
                f.write("error message: "+ e.stderr + "\n")
                print(f"error message: {e.stderr}")
                f.close()
    else:
        print(f"arkola node_modules directory exists, skip install")
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("arkola node_modules directory exists, skip install\n")
            f.close()


def check_fast_arktsc(path: Paths):
    """
    check fast arktsc
    """
    if not os.path.exists(path.check_fast_arktsc):
        print(f"fast-arktsc not found!")
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("fast-arktsc not found!\n")
            f.close()


def is_target_file(file_name: str) -> bool:
    """
    Check if the given file name is a target file.
    """
    target_extensions = [".d.ets", ".ets"]
    return any(file_name.endswith(ext) for ext in target_extensions)


def get_key_from_file_name(file_name: str) -> str:
    """
    Extract the key from the given file name.
    """
    if ".d." in file_name:
        file_name = file_name.replace(".d.", ".")
    return os.path.splitext(file_name)[0]


def scan_directory_for_paths(directory: str) -> Dict[str, List[str]]:
    """
    Scan the specified directory to find all target files and organize their paths by key.
    """
    paths = {}
    for root, _, files in os.walk(directory):
        for file in files:
            if not is_target_file(file):
                continue
            file_path = os.path.abspath(os.path.join(root, file))
            file_name = get_key_from_file_name(file)
            file_abs_path = os.path.abspath(os.path.join(root, file_name))
            file_rel_path = os.path.relpath(file_abs_path, start=directory)
            # Split the relative path into components
            path_components = file_rel_path.split(os.sep)
            first_level_dir = path_components[0] if len(path_components) > 0 else ""
            second_level_dir = path_components[1] if len(path_components) > 1 else ""
            # Determine the key based on directory structure
            if first_level_dir == "arkui" and second_level_dir == "runtime-api":
                key = file_name
            else:
                key = file_rel_path.replace(os.sep, ".")
            if key in paths:
                paths[key].append(file_path)
            else:
                paths[key] = [file_path]
    return paths


def generate_new_arkts_config(path: Paths):
    """
    generate new arkts config json
    """
    paths = {}
    new_paths = {}
    if path.ohos_ets_api_path == "" or path.ohos_ets_arkts_path == "":
        print(f"ohos ets api or arkts path not exists")
        sys.exit(1)
    else:
        scan_paths = [path.ohos_ets_api_path, path.ohos_ets_arkts_path]
        for scan_path in scan_paths:
            scanned_paths = scan_directory_for_paths(scan_path)
            for key, value in scanned_paths.items():
                if key in paths:
                    paths[key].extend(value)
                else:
                    paths[key] = value
    old_arkts_config_path = os.path.join(path.arkui_ohos_path, "arktsconfig-unmemoized.json")
    new_arkts_config_path = os.path.join(path.arkui_ohos_path, "arktsconfig-unmemoized-merged.json")
    # need take old arkts config json paths splicing to new arkts config paths
    with open(old_arkts_config_path, 'r', encoding='utf-8') as f:
        old_data = json.load(f)
        old_paths = old_data['compilerOptions']['paths']
        for key, value in paths.items():
            if key not in old_paths:
                old_paths[key] = value
        with open(new_arkts_config_path, 'w', encoding="utf-8") as f:
            json.dump(old_data, f, indent=2, ensure_ascii=False)


def run_build_arkoala(env, path: Paths):
    """
    run build arkoala
    """
    try:
        ret = subprocess.run(
            ["npm", "run", TARGET_CMD, "--verbose"],
            capture_output=True,
            env = env,
            text=True,
            check=True
        )
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("build log:\n" + ret.stdout)
            print(f"build log:\n {ret.stdout}")
            f.close()
    except subprocess.CalledProcessError as e:
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("build log: "+ e.stdout + "\n")
            f.write("error message: "+ e.stderr + "\n")
            print(f"build log:\n {e.stdout}")
            print(f"error message: {e.stderr}")
            f.close()


def copy_akoala_abc(path: Paths):
    """
    copy arkoala abc file and move to dist path
    """
    built_path = os.path.join(path.project_path, "arkoala-arkts", "build", ABC_FILE)
    if not os.path.exists(built_path):
        print(f"Error: Built file not found at {built_path}")
        sys.exit(1)
    dist_file = os.path.join(path.dist_path, ABC_FILE)
    output_file = os.path.join(path.output_target_path, ABC_FILE)
    try:
        shutil.copy(built_path, dist_file)
        shutil.copy(built_path, output_file)
        print(f"Arkoala: File successfully copied to {dist_file}")
        with open(path.logfile, "a+") as f:
            f.write("\n")
            f.write("Arkoala: File successfully copied to " + dist_file + " \n")
            f.write("Arkoala: File successfully copied to " + output_file + " \n")
            f.close()
    except Exception as e:
        print(f"Error: Failed to copy file: {e}")
        sys.exit(1)


def resolve_innerkis_config(path: Paths, config_file, output_file):
    config_file_path = os.path.join(path.arkui_ohos_path, config_file)
    with open(path.logfile, "a+") as f:
        f.write("\n")
        f.write("resolve config path: " + config_file_path + " \n")
        f.close()

    try:
        with open(config_file_path, 'r', encoding='utf-8') as file:
            with open(path.logfile, "a+") as f:
                f.write("resolved path file opend \n")
                f.close()
            json_data = json.load(file)

            # 获取 baseUrl
            base_url = json_data['compilerOptions']['baseUrl']

            # 获取配置文件的目录路径
            config_dir = os.path.dirname(config_file_path)

            # 将 baseUrl 解析为绝对路径（相对于配置文件）
            absolute_base_url = os.path.abspath(os.path.join(config_dir, base_url))

            # 获取 paths
            paths = json_data['compilerOptions']['paths']

            # 处理 paths 中的相对路径
            resolved_paths = {}
            for key, value in paths.items():
                resolved_value = [os.path.abspath(os.path.join(absolute_base_url, path)) for path in value]
                resolved_paths[key] = resolved_value
            if not os.path.exists(path.innerkits_path):
                os.makedirs(path.innerkits_path)
            with open(output_file, 'w', encoding='utf-8') as f:
                json.dump({"paths": resolved_paths}, f, indent=2, ensure_ascii=False)
            with open(path.logfile, "a+") as f:
                f.write("output_file generated:" + output_file + " \n")
                f.close()
    except Exception as e:
        with open(path.logfile, "a+") as f:
            f.write("Error: Failed to generate innerkit path file: " + e + " \n")
            f.close()
        sys.exit(1)


def pre_processing(path: Paths):
    start_time = time.time()
    original_path = os.path.join(
        path.project_path, "arkoala-arkts", "arkui-ohos")
    target_path = os.path.join(
        path.project_path, "arkoala-arkts", "arkui-ohos-preprocess")

    if os.path.exists(target_path):
        shutil.rmtree(target_path)

    def ignore_build_path(src, names):
        return ["build"] if "build" in names else []

    shutil.copytree(original_path, target_path, ignore=ignore_build_path, dirs_exist_ok=True)

    handwritten_path = os.path.join(target_path, "src", "handwritten", "component")
    generated_path = os.path.join(target_path, "src", "component")

    merge_component(handwritten_path, generated_path)

    shutil.rmtree(handwritten_path)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: preprocess time: {elapsed_time:.2f} seconds")
    return

def main(argv):
    path = parse_argv(argv)
    pre_processing(path)
    prebuilt_dist(path)
    env = os.environ.copy()
    env_old_path = env["PATH"]
    change_env_path(env, path)
    check_node_modules(env, path)
    check_fast_arktsc(path)
    generate_new_arkts_config(path)
    run_build_arkoala(env, path)
    env["PATH"] = env_old_path
    copy_akoala_abc(path)
    resolve_innerkis_config(path, "arktsconfig-unmemoized-merged.json", os.path.join(path.innerkits_path, "arkts_paths.json"))


if __name__ == '__main__':
    start_time = time.time()
    main(sys.argv)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Arkoala: build time: {elapsed_time:.2f} seconds")
