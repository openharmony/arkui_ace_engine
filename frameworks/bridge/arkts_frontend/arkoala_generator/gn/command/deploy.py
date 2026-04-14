#!/usr/bin/env python3
# -*- coding: utf-8 -*-
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
"""
Deploy script for copying generated Modifier.ets files from arkoala generator
to the koala_projects directory.

Usage:
    python deploy.py --source <src_dir> --destination <dst_dir> --config <config_file> --stamp <stamp_file>

Arguments:
    --source       Source directory containing *Modifier.ets files
    --destination  Destination directory to copy files to
    --config       JSON configuration file containing ignore list of files to skip
    --stamp        Path to stamp file created on successful completion

Ignore format (relative paths from source directory):
    {
        "ignore": ["CommonMethodModifier.ets", "subdir/SomeModifier.ets"]
    }
"""

import argparse
import json
import shutil
import glob
from pathlib import Path


def load_config(config_path):
    """
    Load configuration from JSON file.

    Config format:
    {
        "managed": {
            "ignore": ["File1Modifier.ets", ...]
        },
        "native": [
            {"from": "relative/from/outDir", "to": "relative/from/aceRoot"},
            ...
        ]
    }

    Returns (ignore_set, native_list). Both empty if file missing or invalid.
    """
    include_list = set()
    ignore_list = set()
    native_list = []

    if not config_path:
        return ignore_list, native_list

    config_file = Path(config_path)
    if not config_file.exists():
        print(f"Warning: Config file not found: {config_path}")
        return ignore_list, native_list

    try:
        with open(config_file, 'r', encoding='utf-8') as f:
            config = json.load(f)

        managed = config.get('managed', {})
        if isinstance(managed.get('include'), list):
            for item in managed['include']:
                normalized = str(item).replace('\\', '/')
                include_list.add(normalized)
            print(f"Loaded {len(include_list)} files from managed include list")
        if isinstance(managed.get('ignore'), list):
            for item in managed['ignore']:
                normalized = str(item).replace('\\', '/')
                ignore_list.add(normalized)
            print(f"Loaded {len(ignore_list)} files from managed ignore list")

        if isinstance(config.get('native'), list):
            for entry in config['native']:
                if isinstance(entry, dict) and 'from' in entry and 'to' in entry:
                    native_list.append({
                        'from': str(entry['from']).replace('\\', '/'),
                        'to': str(entry['to']).replace('\\', '/'),
                    })
            print(f"Loaded {len(native_list)} native file mappings")
    except json.JSONDecodeError as e:
        print(f"Warning: Failed to parse config file: {e}")
    except Exception as e:
        print(f"Warning: Error reading config file: {e}")

    return include_list, ignore_list, native_list


def copy_modifier_files(src_dir, dst_dir, include_list, ignore_list):
    """
    Copy all *Modifier.ets files from source to destination,
    excluding files in the ignore list.

    Ignore list uses relative paths from src_dir.

    Returns True if all non-ignored files were copied successfully.
    """
    src_path = Path(src_dir)
    dst_path = Path(dst_dir)

    if not src_path.exists():
        print(f"Error: Source directory does not exist: {src_path}")
        return False

    if not dst_path.exists():
        print(f"Creating destination directory: {dst_path}")
        dst_path.mkdir(parents=True, exist_ok=True)

    # Find Modifier.ets files in source directory (first layer only, no subdirectories)
    modifier_pattern = str(src_path / "*Modifier.ets")
    modifier_files = glob.glob(modifier_pattern)

    if not modifier_files:
        print(f"No *Modifier.ets files found in {src_path}")
        return True  # Not an error, just no files to copy

    print(f"Source: {src_path}")
    print(f"Destination: {dst_path}")
    print()

    copied_count = 0
    skipped_count = 0

    for file in include_list:
        included_file = src_path / file
        if included_file.exists():
            dst_file = dst_path / file
            dst_file.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(included_file, dst_file)
            print(f"Included (forced copy): {file}")
            copied_count += 1
        else:
            raise Exception(f"Included file not found: {file}")

    for src_file in sorted(modifier_files):
        src_file_path = Path(src_file)

        # Get relative path from source directory
        rel_path = src_file_path.relative_to(src_path)
        rel_path_str = str(rel_path).replace('\\', '/')

        # Skip ignored files (using relative path)
        if rel_path_str in ignore_list:
            print(f"  Skipped (ignored): {rel_path_str}")
            skipped_count += 1
            continue

        # Destination file preserves relative path structure
        dst_file = dst_path / rel_path

        try:
            # Create parent directories if needed
            dst_file.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src_file, dst_file)
            print(f"  Copied: {rel_path_str}")
            copied_count += 1
        except Exception as e:
            print(f"  Error copying {rel_path_str}: {e}")

    print()
    print(f"Summary: {copied_count} copied, {skipped_count} skipped (ignored)")

    return True

def copy_native_files(out_dir, config_dir, native_list):
    """
    Copy native (C/C++) files from generator output to ace_engine tree.

    Each entry has 'from' (relative to out_dir) and 'to' (relative to config_dir).
    """
    out_path = Path(out_dir)
    cfg_path = Path(config_dir)

    copied = 0
    for entry in native_list:
        src = out_path / entry['from']
        dst = cfg_path / entry['to']

        if not src.exists():
            print(f"  Skipped (not found): {entry['from']}")
            continue

        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        print(f"  Copied native: {entry['from']} -> {entry['to']}")
        copied += 1

    print(f"\nNative files: {copied} copied, {len(native_list) - copied} skipped")
    return True


def generate_gitignore(dst_dir, ignore_list):
    """
    Generate a .gitignore file in the destination directory.

    The .gitignore ignores all *Modifier.ets files but negates (keeps tracked)
    the files listed in the ignore list (instructive/handwritten files).

    Args:
        dst_dir: Destination directory where .gitignore will be created.
        ignore_list: Set of filenames from instructive-config.json that
                     should be negated (kept tracked in git).
    """
    dst_path = Path(dst_dir)
    gitignore_path = dst_path / ".gitignore"

    lines = [
        "# Auto-generated by idlizer - ignore all Modifier files",
        "*Modifier.ets",
        "",
        "# Keep instructive (handwritten) files from generation_config/instructive-config.json",
    ]

    for filename in sorted(ignore_list):
        lines.append(f"!{filename}")

    content = "\n".join(lines) + "\n"

    try:
        dst_path.mkdir(parents=True, exist_ok=True)
        gitignore_path.write_text(content, encoding="utf-8")
        print(f"Generated .gitignore: {gitignore_path}")
    except OSError as e:
        print(f"Error: Failed to generate .gitignore: {e}")
        raise


def main():
    parser = argparse.ArgumentParser(
        description='Deploy Modifier.ets files from generator output to koala_projects',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument(
        '--source', '-s',
        required=True,
        help='Source directory containing generator output (out/)'
    )
    parser.add_argument(
        '--destination', '-d',
        required=True,
        help='Destination directory to copy Modifier.ets files to'
    )
    parser.add_argument(
        '--config', '-c',
        required=False,
        help='JSON configuration file with managed ignore list and native file mappings'
    )
    parser.add_argument(
        '--stamp',
        required=True,
        help='Path to stamp file to create on successful completion'
    )

    args = parser.parse_args()

    print("=" * 60)
    print("Arkoala Modifier.ets Deployment Script")
    print("=" * 60)
    print()

    include_list, ignore_list, native_list = load_config(args.config)
    if include_list:
        print(f"Include list: {sorted(include_list)}")
        print()
    if ignore_list:
        print(f"Ignore list: {sorted(ignore_list)}")
        print()

    success = copy_modifier_files(
        str(Path(args.source) / "sig/arkoala-arkts/arkui/generated"),
        args.destination,
        include_list,
        ignore_list,
    )

    if native_list and args.config:
        config_dir = str(Path(args.config).parent)
        print()
        success = copy_native_files(args.source, config_dir, native_list) and success
    elif native_list:
        print("\nWarning: native entries found but --config not provided, skipping native copy")

    # Generate .gitignore for the destination directory
    generate_gitignore(args.destination, ignore_list)

    if success:
        Path(args.stamp).parent.mkdir(parents=True, exist_ok=True)
        Path(args.stamp).touch()
        print("\nDeployment completed successfully!")
        return 0
    else:
        print("\nDeployment failed!")
        return 1


if __name__ == "__main__":
    exit(main())
