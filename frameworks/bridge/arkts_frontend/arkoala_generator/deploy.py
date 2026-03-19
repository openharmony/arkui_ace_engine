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
    python deploy.py --source <src_dir> --destination <dst_dir> --config <config_file>

Arguments:
    --source       Source directory containing *Modifier.ets files
    --destination  Destination directory to copy files to
    --config       JSON configuration file containing blacklist of files to skip

Blacklist format (relative paths from source directory):
    {
        "blacklist": ["CommonMethodModifier.ets", "subdir/SomeModifier.ets"]
    }
"""

import argparse
import json
import shutil
import glob
from pathlib import Path


def load_blacklist(config_path):
    """
    Load blacklist from configuration file.

    The config file should be a JSON file with relative paths from source dir:
    {
        "blacklist": ["File1Modifier.ets", "subdir/File2Modifier.ets"]
    }

    Returns an empty set if file doesn't exist or is invalid.
    """
    blacklist = set()

    if not config_path:
        return blacklist

    config_file = Path(config_path)
    if not config_file.exists():
        print(f"Warning: Config file not found: {config_path}")
        return blacklist

    try:
        with open(config_file, 'r', encoding='utf-8') as f:
            config = json.load(f)

        if isinstance(config.get('blacklist'), list):
            # Normalize paths to use forward slashes
            for item in config['blacklist']:
                normalized = str(item).replace('\\', '/')
                blacklist.add(normalized)
            print(f"Loaded {len(blacklist)} files from blacklist")
    except json.JSONDecodeError as e:
        print(f"Warning: Failed to parse config file: {e}")
    except Exception as e:
        print(f"Warning: Error reading config file: {e}")

    return blacklist


def copy_modifier_files(src_dir, dst_dir, blacklist):
    """
    Copy all *Modifier.ets files from source to destination,
    excluding files in the blacklist.

    Blacklist uses relative paths from src_dir.

    Returns True if all non-blacklisted files were copied successfully.
    """
    src_path = Path(src_dir)
    dst_path = Path(dst_dir)

    if not src_path.exists():
        print(f"Error: Source directory does not exist: {src_path}")
        return False

    if not dst_path.exists():
        print(f"Creating destination directory: {dst_path}")
        dst_path.mkdir(parents=True, exist_ok=True)

    # Find all Modifier.ets files in source directory (including subdirectories)
    modifier_pattern = str(src_path / "**" / "*Modifier.ets")
    modifier_files = glob.glob(modifier_pattern, recursive=True)

    if not modifier_files:
        print(f"No *Modifier.ets files found in {src_path}")
        return True  # Not an error, just no files to copy

    print(f"Source: {src_path}")
    print(f"Destination: {dst_path}")
    print()

    copied_count = 0
    skipped_count = 0

    for src_file in sorted(modifier_files):
        src_file_path = Path(src_file)

        # Get relative path from source directory
        rel_path = src_file_path.relative_to(src_path)
        rel_path_str = str(rel_path).replace('\\', '/')

        # Skip blacklisted files (using relative path)
        if rel_path_str in blacklist:
            print(f"  Skipped (blacklisted): {rel_path_str}")
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
    print(f"Summary: {copied_count} copied, {skipped_count} skipped (blacklisted)")

    return True


def main():
    parser = argparse.ArgumentParser(
        description='Deploy Modifier.ets files from generator output to koala_projects',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument(
        '--source', '-s',
        required=True,
        help='Source directory containing *Modifier.ets files'
    )
    parser.add_argument(
        '--destination', '-d',
        required=True,
        help='Destination directory to copy files to'
    )
    parser.add_argument(
        '--config', '-c',
        required=False,
        help='JSON configuration file containing blacklist of files to skip'
    )

    args = parser.parse_args()

    print("=" * 60)
    print("Arkoala Modifier.ets Deployment Script")
    print("=" * 60)
    print()

    # Load blacklist from config
    blacklist = load_blacklist(args.config)
    if blacklist:
        print(f"Blacklist: {sorted(blacklist)}")
        print()

    # Copy files
    success = copy_modifier_files(args.source, args.destination, blacklist)

    if success:
        print("\nDeployment completed successfully!")
        return 0
    else:
        print("\nDeployment failed!")
        return 1


if __name__ == "__main__":
    exit(main())
