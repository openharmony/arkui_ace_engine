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
Patch management script for applying and creating patches between directory trees.
Uses git for cross-platform compatibility (Windows, macOS, Linux).

Patches are stored as individual .patch files, one per changed source file,
organized in a directory structure that mirrors the source tree.

Usage:
    python patch.py apply --input <path> --output <path> --patch <patch_dir>
    python patch.py create-patch --input <path> --output <path> --patch <patch_dir>

Example patch directory layout:
    patch_dir/
    ├── foo.txt.patch
    └── folder/
        └── boo.txt.patch

Commands:
    apply          Copy input directory to output and apply per-file patches.
    create-patch   Find differences between input and output directories and
                   save as per-file patches.
"""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile


def run_git(git_args, cwd=None, check=True):
    """Run a git command and return the CompletedProcess."""
    return subprocess.run(
        ['git'] + git_args,
        cwd=cwd,
        check=check,
        capture_output=True,
        text=True,
    )


def check_git_available():
    """Verify that git is installed and accessible."""
    try:
        subprocess.run(
            ['git', '--version'],
            capture_output=True,
            check=True,
        )
        return True
    except (subprocess.CalledProcessError, FileNotFoundError):
        return False


def find_rej_files(directory):
    """Find all .rej files under a directory, returning relative paths."""
    rej_files = []
    for root, dirs, files in os.walk(directory):
        for f in files:
            if f.endswith('.rej'):
                rel = os.path.relpath(os.path.join(root, f), directory)
                rej_files.append(str(rel).replace('\\', '/'))
    return sorted(rej_files)


def collect_patch_files(patch_dir):
    """Collect all .patch files in a directory, returning (rel_path, abs_path) pairs."""
    patch_abs = os.path.abspath(patch_dir)
    patch_files = []
    for root, dirs, files in os.walk(patch_abs):
        for f in files:
            if f.endswith('.patch'):
                abs_path = os.path.join(root, f)
                rel = os.path.relpath(abs_path, patch_abs)
                patch_files.append((rel, abs_path))
    return sorted(patch_files)


def is_deletion_patch(patch_path):
    """Check if a patch file represents a file deletion (targets /dev/null)."""
    try:
        with open(patch_path, 'r', encoding='utf-8') as f:
            for line in f:
                if line.startswith('+++ /dev/null'):
                    return True
    except (IOError, UnicodeDecodeError):
        pass
    return False


def format_create_patch_cmd(input_abs, output_abs, patch_abs):
    """Format the create-patch command for display to the user."""
    script = os.path.abspath(__file__)
    parts = [
        sys.executable, script, 'create-patch',
        '--input', input_abs,
        '--output', output_abs,
        '--patch', patch_abs,
    ]
    return ' '.join(parts)


def apply_patch(input_path, output_path, patch_dir):
    """Copy input directory to output and apply per-file patches from a directory.

    Each .patch file in the patch directory corresponds to a source file.
    The directory structure mirrors the source tree with '.patch' appended
    to filenames.

    If a patch does not apply cleanly, falls back to ``git apply --reject``
    which applies as many hunks as possible and writes rejected hunks to
    ``.rej`` files alongside the affected files.

    Args:
        input_path: Source directory to copy from.
        output_path: Destination directory to copy to and apply patches in.
        patch_dir: Directory containing per-file patches.

    Returns:
        True on success, False on failure.
    """
    input_abs = os.path.abspath(input_path)
    output_abs = os.path.abspath(output_path)
    patch_abs = os.path.abspath(patch_dir)

    if not os.path.isdir(input_abs):
        print(f"Error: Input directory does not exist: {input_abs}")
        return False

    if not os.path.isdir(patch_abs):
        print(f"Error: Patch directory does not exist: {patch_abs}")
        return False

    # Collect all .patch files in the patch directory
    patch_files = collect_patch_files(patch_abs)

    # Remove output directory if it exists
    if os.path.exists(output_abs):
        print(f"Removing existing output directory: {output_abs}")
        shutil.rmtree(output_abs)

    # Copy input to output
    print(f"Copying {input_abs} -> {output_abs}")
    shutil.copytree(input_abs, output_abs)

    if not patch_files:
        print("No patch files found. Output is a copy of input without changes.")
        return True

    # Apply each patch file individually
    failed = []
    for rel_path, abs_path in sorted(patch_files):
        if os.path.getsize(abs_path) == 0:
            print(f"Skipping empty patch: {rel_path}")
            continue

        print(f"Applying patch: {rel_path}")
        try:
            run_git(['apply', '-p1', abs_path], cwd=output_abs)
        except subprocess.CalledProcessError:
            # Clean apply failed — attempt partial apply with .rej files
            print("  Clean apply failed. Attempting partial apply with conflict markers...")
            run_git(['apply', '-p1', '--reject', abs_path], cwd=output_abs, check=False)
            failed.append(rel_path)

    if not failed:
        print("All patches applied successfully.")
        print()
        print("To edit the output and update patches:")
        print(f"  1. Make changes in the output directory {output_abs}.")
        print("  2. Regenerate patches:")
        print()
        print(f"    {format_create_patch_cmd(input_abs, output_abs, patch_abs)}")
        print()
        return True

    # Detect structural conflicts that don't produce .rej files
    missing_in_source = []    # patch modifies file deleted in source
    delete_conflicts = []     # patch deletes file changed in source
    for rel_path in failed:
        patch_file_abs = os.path.join(patch_abs, rel_path)
        source_rel = rel_path[:-6]  # strip '.patch' suffix
        source_abs = os.path.join(output_abs, source_rel)
        if is_deletion_patch(patch_file_abs):
            if os.path.isfile(source_abs):
                delete_conflicts.append(source_rel)
        else:
            if not os.path.isfile(source_abs):
                missing_in_source.append(source_rel)

    rej_files = find_rej_files(output_abs)

    print()
    print(f"Failed to apply {len(failed)} patch(es):")
    for f in failed:
        print(f"  {f}")

    if missing_in_source:
        print()
        print(f"Conflicts: patch modifies file deleted in source ({len(missing_in_source)}):")
        for f in missing_in_source:
            print(f"  {f}")

    if delete_conflicts:
        print()
        print(f"Conflicts: patch deletes file changed in source ({len(delete_conflicts)}):")
        for f in delete_conflicts:
            print(f"  {f}")

    if rej_files:
        print()
        print(f"Rejected hunks saved in {len(rej_files)} .rej file(s):")
        for f in rej_files:
            print(f"  {f}")

    print()
    print("Partial changes (if any) have been written to the output directory.")
    print("Rejected hunks are saved in corresponding .rej files.")
    print()
    print("To resolve conflicts:")
    print("  1. Review the .rej files in the output directory and manually")
    print("     apply the rejected changes to the corresponding source files.")
    print("  2. Delete all .rej files after resolving.")
    print("  3. Regenerate patches with the resolved output:")
    print()
    print(f"    {format_create_patch_cmd(input_abs, output_abs, patch_abs)}")
    print()

    return False


def create_patch(input_path, output_path, patch_dir):
    """Find differences between input and output and save as per-file patches.

    Uses a temporary git repository to produce reliable unified diffs that
    capture file additions, modifications, and deletions.

    Each changed file gets its own ``.patch`` file in the patch directory,
    mirroring the source directory structure with ``.patch`` appended to the
    filename.

    Args:
        input_path: Original (unmodified) directory.
        output_path: Modified directory.
        patch_dir: Directory to save per-file patches into.

    Returns:
        True on success, False on failure.
    """
    input_abs = os.path.abspath(input_path)
    output_abs = os.path.abspath(output_path)
    patch_abs = os.path.abspath(patch_dir)

    if not os.path.isdir(input_abs):
        print(f"Error: Input directory does not exist: {input_abs}")
        return False

    if not os.path.isdir(output_abs):
        print(f"Error: Output directory does not exist: {output_abs}")
        return False

    # Clean and recreate patch directory
    if os.path.exists(patch_abs):
        shutil.rmtree(patch_abs)
    os.makedirs(patch_abs, exist_ok=True)

    with tempfile.TemporaryDirectory() as tmpdir:
        # Initialize a bare git repo for diffing purposes
        print("Creating temporary git repository for diff...")
        run_git(['init'], cwd=tmpdir)
        run_git(['config', 'user.email', 'patch@tool.local'], cwd=tmpdir)
        run_git(['config', 'user.name', 'Patch Tool'], cwd=tmpdir)

        # Copy input files as the base commit
        print(f"Staging input files from {input_abs}")
        shutil.copytree(input_abs, tmpdir, dirs_exist_ok=True)
        run_git(['add', '-A'], cwd=tmpdir)
        run_git(['commit', '-m', 'base'], cwd=tmpdir)

        # Remove all tracked content (keep .git directory)
        for item in os.listdir(tmpdir):
            if item == '.git':
                continue
            item_path = os.path.join(tmpdir, item)
            if os.path.isdir(item_path):
                shutil.rmtree(item_path)
            else:
                os.remove(item_path)

        # Copy output files as the modified state
        print(f"Staging output files from {output_abs}")
        shutil.copytree(output_abs, tmpdir, dirs_exist_ok=True)
        run_git(['add', '-A'], cwd=tmpdir)

        # Get list of changed files
        name_result = run_git(['diff', '--cached', '--name-only', 'HEAD'], cwd=tmpdir)
        changed_files = [f for f in name_result.stdout.strip().split('\n') if f]

        if not changed_files:
            print(f"No differences found. Empty patch directory at {patch_abs}")
            return True

        # Generate per-file patches
        print(f"Generating patches for {len(changed_files)} file(s)...")
        for file_path in changed_files:
            result = run_git(['diff', '--cached', 'HEAD', '--', file_path], cwd=tmpdir)
            patch_file = os.path.join(patch_abs, file_path + '.patch')
            patch_subdir = os.path.dirname(patch_file)
            if patch_subdir:
                os.makedirs(patch_subdir, exist_ok=True)
            with open(patch_file, 'w', encoding='utf-8') as f:
                f.write(result.stdout)

        print(f"Patches saved to {patch_abs}")
        for file_path in sorted(changed_files):
            print(f"  {file_path}.patch")

    return True


def main():
    if not check_git_available():
        print("Error: git is required but not found in PATH.")
        print("Please install git and ensure it is accessible from the command line.")
        return 1

    parser = argparse.ArgumentParser(
        description='Apply or create per-file patches between directory trees',
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )

    subparsers = parser.add_subparsers(dest='command', required=True)

    # apply subcommand
    apply_parser = subparsers.add_parser(
        'apply',
        help='Copy input directory to output and apply per-file patches',
    )
    apply_parser.add_argument(
        '--input', required=True,
        help='Source directory to copy from',
    )
    apply_parser.add_argument(
        '--output', required=True,
        help='Destination directory to copy to and apply patches in',
    )
    apply_parser.add_argument(
        '--patch', required=True,
        help='Directory containing per-file patches',
    )
    apply_parser.add_argument(
        '--stamp',
        help='Create an empty stamp file at this path on success',
    )

    # create-patch subcommand
    create_parser = subparsers.add_parser(
        'create-patch',
        help='Create per-file patches from differences between two directories',
    )
    create_parser.add_argument(
        '--input', required=True,
        help='Original (unmodified) directory',
    )
    create_parser.add_argument(
        '--output', required=True,
        help='Modified directory',
    )
    create_parser.add_argument(
        '--patch', required=True,
        help='Directory to save per-file patches into',
    )

    args = parser.parse_args()

    if args.command == 'apply':
        success = apply_patch(args.input, args.output, args.patch)
        if success and args.stamp:
            stamp_abs = os.path.abspath(args.stamp)
            stamp_dir = os.path.dirname(stamp_abs)
            if stamp_dir:
                os.makedirs(stamp_dir, exist_ok=True)
            with open(stamp_abs, 'w') as f:
                pass
    elif args.command == 'create-patch':
        success = create_patch(args.input, args.output, args.patch)
    else:
        parser.print_help()
        return 1

    return 0 if success else 1


if __name__ == '__main__':
    sys.exit(main())
