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
import shutil
import json
import argparse

def load_config(config_file):
    """Load the configuration file."""
    with open(config_file, 'r') as f:
        config = json.load(f)
    return config

def replace_out_root(value, out_root):
    """Replace $out_root in the string with the actual value."""
    return value.replace("$out_root", out_root)

def copy_files(config, src_base, dist_base, out_root):
    """Copy files or directories based on the configuration."""
    for mapping in config['file_mappings']:
        # Replace $out_root
        source = replace_out_root(mapping['source'], out_root)
        destination = replace_out_root(mapping['destination'], out_root)

        # Build full paths
        source = os.path.join(src_base, source)
        destination = os.path.join(dist_base, destination)

        # Check if the source path exists, otherwise try fallback
        if not os.path.exists(source):
            print(f"Source path does not exist (will try to fallback): {source}")
            if mapping['source_fallback']:
                source_fallback = replace_out_root(mapping['source_fallback'], out_root)
                source = os.path.join(src_base, source_fallback)
                if not os.path.exists(source):
                    print(f"Fallback source path does not exist: {source}")
                    continue
            else:
                continue

        # Create the destination directory if it doesn't exist
        dest_dir = os.path.dirname(destination) if os.path.isfile(source) else destination
        os.makedirs(dest_dir, exist_ok=True)

        # If it's a file, copy the file
        if os.path.isfile(source):
            try:
                shutil.copy2(source, destination)
                print(f"File copied: {source} -> {destination}")
            except Exception as e:
                print(f"Failed to copy file: {source} -> {destination}, error: {e}")
        # If it's a directory, recursively copy the directory
        elif os.path.isdir(source):
            try:
                shutil.copytree(source, destination, dirs_exist_ok=True)
                print(f"Directory copied: {source} -> {destination}")
            except Exception as e:
                print(f"Failed to copy directory: {source} -> {destination}, error: {e}")

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Copy files or directories.")
    parser.add_argument("--config", required=True, help="Path to the configuration file.")
    parser.add_argument("--src", required=True, help="Base source path.")
    parser.add_argument("--dist", required=True, help="Base destination path.")
    parser.add_argument("--out-root", required=True, help="Relative out directory to src, used to replace $out_root.")
    args = parser.parse_args()

    # Load the configuration
    config = load_config(args.config)

    # Copy files or directories
    copy_files(config, args.src, args.dist, args.out_root)

    # Create package.json to pass SDK validation
    content = """{
  "name": "@panda/sdk",
  "version": "1.0.0"
}"""
    with open(os.path.join(args.dist, "package.json"), "w") as file:
        file.write(content)

if __name__ == '__main__':
    main()