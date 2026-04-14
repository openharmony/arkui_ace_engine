#!/usr/bin/env python3

# Copyright (c) 2026 Huawei Device Co., Ltd.
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
import argparse
from pathlib import Path

def write_depfile(depfile_path, output_file, inputs):
    """Write Ninja depfile in format: output: input1 input2 ..."""
    with open(depfile_path, 'w') as f:
        f.write(f"{output_file}:")
        for input_file in inputs:
            f.write(f" {input_file}")
        f.write("\n")

def scan_directory(directory):
    """Recursively find all files in directory."""
    discovered = []
    root_path = Path(directory)
    
    if not root_path.exists():
        print(f"Warning: Directory does not exist: {directory}")
        return discovered
    
    for entry in root_path.rglob('*'):
        if entry.is_file():
            # Convert to string with forward slashes for GN/Ninja compatibility
            discovered.append(str(entry).replace('\\', '/'))
    
    return sorted(discovered)

def main():
    parser = argparse.ArgumentParser(description='Scan directory and generate file list with depfile')
    parser.add_argument('--depfile', required=True,
                       help='Path prefix for output files (without extension)')
    parser.add_argument('--input', required=True,
                       help='Directory path to scan recursively')
    args = parser.parse_args()
    
    # Construct output paths
    txt_output = f"{args.depfile}.txt"
    dep_output = f"{args.depfile}.d"
    
    # Scan directory for all files
    print(f"Scanning directory: {args.input}")
    discovered_files = scan_directory(args.input)
    
    # Write the file list
    with open(txt_output, 'w') as f:
        for file_path in discovered_files:
            f.write(f"{file_path}\n")
    
    # Write the depfile - tracks ALL discovered files as dependencies
    if discovered_files:
        write_depfile(dep_output, txt_output, discovered_files)
    else:
        # Write empty depfile to avoid Ninja errors
        with open(dep_output, 'w') as f:
            f.write(f"{txt_output}:\n")
    
    # Print summary
    print(f"\nScanner: Found {len(discovered_files)} files in {args.input}")
    print(f"  List file: {txt_output}")
    print(f"  Depfile: {dep_output}")

if __name__ == '__main__':
    sys.exit(main())