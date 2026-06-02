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
import difflib
import json
import shutil
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

    return ignore_list, native_list


def copy_generated_files(src_dir, dst_dir, ignore_list):
    """
    Copy all generated files from source to destination recursively,
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

    print(f"Source: {src_path}")
    print(f"Destination: {dst_path}")
    print()

    copied_count = 0
    skipped_count = 0

    # Walk all files recursively
    for src_file in sorted(src_path.rglob('*')):
        if not src_file.is_file():
            continue

        rel_path = src_file.relative_to(src_path)
        rel_path_str = str(rel_path).replace('\\', '/')

        # Skip ignored files
        if rel_path_str in ignore_list:
            print(f"  Skipped (ignored): {rel_path_str}")
            skipped_count += 1
            continue

        dst_file = dst_path / rel_path

        try:
            dst_file.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src_file, dst_file)
            print(f"  Copied: {rel_path_str}")
            copied_count += 1
        except Exception as e:
            print(f"  Error copying {rel_path_str}: {e}")

    print()
    print(f"Summary: {copied_count} copied, {skipped_count} skipped (ignored)")

    return True

def log_file_diff(src, dst):
    """Print unified diff between src (from) and dst (to) files."""
    try:
        src_lines = src.read_text(encoding='utf-8').splitlines(keepends=True)
    except OSError as e:
        print(f"  Diff: failed to read source {src}: {e}")
        return

    if not dst.exists():
        print(f"  Diff for {src.name}: destination does not exist, {len(src_lines)} new lines")
        return

    try:
        dst_lines = dst.read_text(encoding='utf-8').splitlines(keepends=True)
    except OSError as e:
        print(f"  Diff: failed to read destination {dst}: {e}")
        return

    diff = list(difflib.unified_diff(
        dst_lines, src_lines,
        fromfile=f"to/{dst}", tofile=f"from/{src}",
    ))
    if not diff:
        print(f"  Diff for {src.name}: no changes")
        return

    print(f"  Diff for {src.name} (from -> to):")
    for line in diff:
        print(line.rstrip('\n'))


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

        if src.name == 'arkoala_api_generated.h':
            log_file_diff(src, dst)

        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        print(f"  Copied native: {entry['from']} -> {entry['to']}")
        copied += 1

    print(f"\nNative files: {copied} copied, {len(native_list) - copied} skipped")
    return True


def generate_gitignore(dst_dir, ignore_list):
    """
    Generate a .gitignore file in the destination directory.

    The .gitignore ignores everything in the generated directory but negates
    (keeps tracked) the files listed in the ignore list (instructive/handwritten files).

    Args:
        dst_dir: Destination directory where .gitignore will be created.
        ignore_list: Set of relative paths from instructive-config.json that
                     should be negated (kept tracked in git).
    """
    dst_path = Path(dst_dir)
    gitignore_path = dst_path / ".gitignore"

    lines = [
        "# Auto-generated by idlizer - ignore all generated files",
        "*",
        "",
        "# Keep instructive (handwritten) files from generation_config/instructive-config.json",
    ]

    # Re-include parent directories of ignored files so git can traverse into them
    ignore_dirs = set()
    for filename in sorted(ignore_list):
        parts = Path(filename).parts
        for i in range(1, len(parts)):
            ignore_dirs.add(str(Path(*parts[:i])))
    for dirname in sorted(ignore_dirs):
        lines.append(f"!/{dirname}/")

    for filename in sorted(ignore_list):
        lines.append(f"!/{filename}")

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

    ignore_list, native_list = load_config(args.config)
    if ignore_list:
        print(f"Ignore list: {sorted(ignore_list)}")
        print()

    success = copy_generated_files(
        str(Path(args.source) / "sig/arkoala-arkts/arkui/generated"),
        args.destination,
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
