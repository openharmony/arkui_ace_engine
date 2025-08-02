#!/usr/bin/env python3
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

import json
import os
import glob
import argparse
from datetime import datetime
import sys
import subprocess

def find_files(include_patterns, exclude_patterns=None, base_url=None):
    """
    根据 include 和 exclude 规则生成文件列表，路径为相对当前路径
    """
    file_list = []
    current_dir = os.getcwd()

    # 处理 include 规则
    for pattern in include_patterns:
        matched_files = glob.glob(pattern, recursive=True)
        for file in matched_files:
            absolute_file_path = os.path.abspath(file)
            relative_path = os.path.relpath(absolute_file_path, current_dir)
            file_list.append(relative_path)

    # 处理 exclude 规则（如果存在）
    if exclude_patterns:
        filtered_file_list = []
        for file_path in file_list:
            # 将 exclude 规则中的路径转换为绝对路径
            exclude_match = False
            for pattern in exclude_patterns:
                absolute_exclude_pattern = os.path.abspath(pattern)
                relative_exclude_pattern = os.path.relpath(absolute_exclude_pattern, current_dir)
                # 检查是否匹配 exclude 规则
                if glob.fnmatch.fnmatch(file_path, relative_exclude_pattern):
                    exclude_match = True
                    break
            if not exclude_match:
                filtered_file_list.append(file_path)
        file_list = filtered_file_list

    file_list.sort()
    return file_list

def generate_files_var_name(package_name, part_index=None):
    """
    根据 package 字段生成变量名，如果指定了 part_index，则生成带编号的变量名
    """
    var_name = package_name.replace("@", "").replace("/", "_")
    if part_index is not None:
        return f"{var_name}_files_{part_index}"
    return f"{var_name}_files"

def generate_paths_arrays(package_name, paths, base_url):
    """
    解析 paths 字段，生成 keys 和 values 两个数组
    """
    var_prefix = package_name.replace("@", "").replace("/", "_")

    # 提取 keys 和 values
    keys = list(paths.keys())
    values = list(paths.values())

    # 将 values 中的路径转换为相对于当前路径的路径
    current_dir = os.getcwd()
    base_url_path = os.path.abspath(base_url)
    relative_values = []
    for value in values:
        value_path = value[0]
        absolute_value_path = os.path.abspath(os.path.join(base_url_path, value_path))
        try:
            relative_path = os.path.relpath(absolute_value_path, current_dir)
            relative_values.append(relative_path)
        except ValueError:
            continue

    keys_var_name = f"{var_prefix}_path_keys"
    values_var_name = f"{var_prefix}_path_values"

    return keys_var_name, values_var_name, keys, relative_values

def generate_gni_file(include, exclude, output_file, package_name, paths, base_url, part_size=None):
    """
    生成 .gni 文件，包含文件列表和 paths 的 keys 和 values 数组
    """
    # 根据 include 和 exclude 规则生成文件列表
    file_list = find_files(include, exclude, base_url)

    # 解析 paths 字段
    keys_var_name, values_var_name, keys, values = generate_paths_arrays(package_name, paths, base_url)

    # 获取当前年份
    current_year = datetime.now().year

    # 获取当前执行的命令
    current_command = " ".join(sys.argv)

    # 写入 .gni 文件
    with open(output_file, "w") as f:
        # 写入版权头
        f.write(f"# Copyright (c) {current_year} Huawei Device Co., Ltd.\n")
        f.write("# Licensed under the Apache License, Version 2.0 (the \"License\");\n")
        f.write("# you may not use this file except in compliance with the License.\n")
        f.write("# You may obtain a copy of the License at\n")
        f.write("#\n")
        f.write("#     http://www.apache.org/licenses/LICENSE-2.0\n")
        f.write("#\n")
        f.write("# Unless required by applicable law or agreed to in writing, software\n")
        f.write("# distributed under the License is distributed on an \"AS IS\" BASIS,\n")
        f.write("# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n")
        f.write("# See the License for the specific language governing permissions and\n")
        f.write("# limitations under the License.\n\n")

        # 写入新增的两句话
        f.write("# DO NOT MODIFY THIS FILE MANUALLY.\n")
        f.write(f"# USE FOLLOWING COMMAND:\n# {current_command}\n\n")

        # 处理文件列表的分割
        if part_size and len(file_list) > part_size:
            part_count = (len(file_list) + part_size - 1) // part_size  # 确保不会多生成一个空列表
            # 写入分块数量变量
            parts_var_name = package_name.replace("@", "").replace("/", "_") + "_parts"
            files_array_var_name = package_name.replace("@", "").replace("/", "_") + "_files_array"

            # 写入分块的文件列表
            for i in range(part_count):
                start_index = i * part_size
                end_index = start_index + part_size
                part_file_list = file_list[start_index:end_index]
                if part_file_list:  # 确保列表不为空
                    files_var_name = generate_files_var_name(package_name, i + 1)
                    f.write(f"{files_var_name} = [\n")
                    for file in part_file_list:
                        f.write(f'  "{file}",\n')
                    f.write("]\n\n")

            # 生成 xxx_parts 数组
            f.write(f"{parts_var_name} = [\n")
            for i in range(1, part_count + 1):
                f.write(f'  {i},\n')
            f.write("]\n\n")
            
            # 生成 xxx_files_array 数组
            f.write(f"{files_array_var_name} = [\n")
            for i in range(1, part_count + 1):
                files_var_name = generate_files_var_name(package_name, i)
                f.write(f'  {files_var_name},\n')
            f.write("]\n\n")
        else:
            files_var_name = generate_files_var_name(package_name)
            f.write(f"{files_var_name} = [\n")
            for file in file_list:
                f.write(f'  "{file}",\n')
            f.write("]\n\n")

        # 写入 paths 的 keys 数组
        f.write(f"{keys_var_name} = [\n")
        for key in keys:
            f.write(f'  "{key}",\n')
        f.write("]\n\n")

        # 写入 paths 的 values 数组
        f.write(f"{values_var_name} = [\n")
        for value in values:
            f.write(f'  "{value}",\n')
        f.write("]\n")

def format_gni_file(gn_tool, file):
    """
    对生成的 .gni 文件，进行格式化
    """
    cmd = [gn_tool, "format", file]
    print("format cmd:")
    print(" ".join(cmd))
    try:
        ret = subprocess.run(cmd, capture_output=True, text=True, check=True)
        return 0
    except subprocess.CalledProcessError as e:
        print(f"Error executing command: {e}", file=sys.stderr)
        print(f"error message: {e.stderr}")
        print(f"output message: {e.output}")
        return 1

if __name__ == "__main__":
    # 解析命令行参数
    parser = argparse.ArgumentParser(description="Generate .gni file from JSON configuration.")
    parser.add_argument("--json", required=True, help="Path to the input JSON file.")
    parser.add_argument("--output", default="output.gni", help="Path to the output .gni file.")
    parser.add_argument("--gn-tool", default="gn", help="Path to the gn tool.")
    parser.add_argument("--part-size", type=int, help="Maximum size of each file list part.")
    args = parser.parse_args()

    # 读取 JSON 文件
    with open(args.json, "r") as f:
        json_data = json.load(f)

    # 提取所需字段
    include = json_data["include"]
    exclude = json_data.get("exclude")  # 使用 get 方法，避免 KeyError 异常
    package_name = json_data["compilerOptions"]["package"]
    paths = json_data["compilerOptions"]["paths"]
    base_url = json_data["compilerOptions"]["baseUrl"]

    # 生成 .gni 文件
    generate_gni_file(include, exclude, args.output, package_name, paths, base_url, args.part_size)
    format_gni_file(args.gn_tool, args.output)