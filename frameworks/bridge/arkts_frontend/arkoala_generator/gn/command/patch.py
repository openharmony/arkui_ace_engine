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
Uses Python's standard difflib module — no external tools required.

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

Notes:
    Files without a trailing newline are normalized to end with a newline
    when patches are generated and applied. Binary files are skipped.
"""

import argparse
import difflib
import os
import re
import shutil
import sys


HUNK_HEADER_RE = re.compile(r'^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@')


def list_relative_files(directory):
    """Return a set of forward-slash relative paths of all files under directory."""
    result = set()
    for root, _dirs, fnames in os.walk(directory):
        for fname in fnames:
            abs_path = os.path.join(root, fname)
            rel = os.path.relpath(abs_path, directory).replace(os.sep, '/')
            result.add(rel)
    return result


def read_text_lines(path):
    """Read file as text lines, preserving newlines. Returns None for binary files.

    Ensures the last line ends with '\\n' so that generated diffs are well-formed
    even for files that were missing a trailing newline.
    """
    try:
        with open(path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except UnicodeDecodeError:
        return None
    if lines and not lines[-1].endswith('\n'):
        lines[-1] = lines[-1] + '\n'
    return lines


def files_equal(path_a, path_b):
    """Byte-compare two files."""
    try:
        with open(path_a, 'rb') as fa, open(path_b, 'rb') as fb:
            while True:
                ba = fa.read(65536)
                bb = fb.read(65536)
                if ba != bb:
                    return False
                if not ba:
                    return True
    except IOError:
        return False


def collect_patch_files(patch_dir):
    """Collect all .patch files in a directory, returning (rel_path, abs_path) pairs."""
    patch_abs = os.path.abspath(patch_dir)
    patch_files = []
    for root, _dirs, files in os.walk(patch_abs):
        for f in files:
            if f.endswith('.patch'):
                abs_path = os.path.join(root, f)
                rel = os.path.relpath(abs_path, patch_abs).replace(os.sep, '/')
                patch_files.append((rel, abs_path))
    return sorted(patch_files)


def parse_patch(patch_text):
    """Parse a unified diff. Returns dict with from_file, to_file, hunks."""
    lines = patch_text.splitlines(keepends=True)
    from_file = None
    to_file = None
    hunks = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith('--- '):
            from_file = line[4:].rstrip('\r\n').split('\t', 1)[0]
            i += 1
            continue
        if line.startswith('+++ '):
            to_file = line[4:].rstrip('\r\n').split('\t', 1)[0]
            i += 1
            continue
        m = HUNK_HEADER_RE.match(line)
        if m:
            hunk = {
                'old_start': int(m.group(1)),
                'old_count': int(m.group(2)) if m.group(2) is not None else 1,
                'new_start': int(m.group(3)),
                'new_count': int(m.group(4)) if m.group(4) is not None else 1,
                'lines': [],
            }
            i += 1
            while i < len(lines):
                hl = lines[i]
                if hl.startswith('@@') or hl.startswith('--- ') or hl.startswith('+++ '):
                    break
                if hl and hl[0] in ' +-\\':
                    hunk['lines'].append(hl)
                    i += 1
                    continue
                break
            hunks.append(hunk)
            continue
        i += 1
    return {'from_file': from_file, 'to_file': to_file, 'hunks': hunks}


def lines_match(source_line, patch_line):
    """Return True if a source line matches a patch context/removed line."""
    if source_line == patch_line:
        return True
    return source_line.rstrip('\r\n') == patch_line.rstrip('\r\n')


def apply_hunks_to_lines(source_lines, hunks):
    """Apply hunks to source lines. Returns new lines list, or None on failure."""
    result = []
    src_idx = 0  # 0-based index into source_lines

    for hunk in hunks:
        if hunk['old_count'] == 0:
            # Pure insertion. With "@@ -X,0 +..." insert before source index X
            # (i.e., after 1-based line X). For new files, X is 0.
            target_idx = hunk['old_start']
        else:
            target_idx = hunk['old_start'] - 1

        if target_idx < src_idx or target_idx > len(source_lines):
            return None

        result.extend(source_lines[src_idx:target_idx])
        src_idx = target_idx

        for hl in hunk['lines']:
            if not hl:
                continue
            tag = hl[0]
            if tag == '\\':
                # "\ No newline at end of file" — strip trailing newline
                # from the most recently emitted line if present.
                if result and result[-1].endswith('\n'):
                    result[-1] = result[-1].rstrip('\r\n')
                continue
            content = hl[1:]
            if tag == ' ':
                if src_idx >= len(source_lines):
                    return None
                if not lines_match(source_lines[src_idx], content):
                    return None
                result.append(source_lines[src_idx])
                src_idx += 1
            elif tag == '-':
                if src_idx >= len(source_lines):
                    return None
                if not lines_match(source_lines[src_idx], content):
                    return None
                src_idx += 1
            elif tag == '+':
                result.append(content)

    result.extend(source_lines[src_idx:])
    return result


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

    patch_files = collect_patch_files(patch_abs)

    input_basename = os.path.basename(os.path.normpath(input_abs))
    copy_dest = os.path.join(output_abs, input_basename)

    if os.path.exists(output_abs):
        print(f"Removing existing output directory: {output_abs}")
        shutil.rmtree(output_abs)

    os.makedirs(output_abs, exist_ok=True)
    print(f"Copying {input_abs} -> {copy_dest}")
    shutil.copytree(input_abs, copy_dest)

    if not patch_files:
        print("No patch files found. Output is a copy of input without changes.")
        return True

    failed = []
    missing_in_source = []
    delete_conflicts = []

    for rel_patch, abs_patch in patch_files:
        if os.path.getsize(abs_patch) == 0:
            print(f"Skipping empty patch: {rel_patch}")
            continue

        print(f"Applying patch: {rel_patch}")

        try:
            with open(abs_patch, 'r', encoding='utf-8') as f:
                patch_text = f.read()
        except (IOError, UnicodeDecodeError) as exc:
            print(f"  Failed to read patch: {exc}")
            failed.append(rel_patch)
            continue

        parsed = parse_patch(patch_text)
        from_file = parsed['from_file']
        to_file = parsed['to_file']
        hunks = parsed['hunks']

        if not rel_patch.endswith('.patch'):
            print(f"  Skipping non-patch file: {rel_patch}")
            continue

        source_rel = rel_patch[:-len('.patch')]
        source_abs = os.path.join(output_abs, source_rel)

        is_new = (from_file == '/dev/null')
        is_delete = (to_file == '/dev/null')

        if is_delete:
            if not os.path.isfile(source_abs):
                print("  Conflict: target file to delete does not exist")
                delete_conflicts.append(source_rel)
                failed.append(rel_patch)
                continue
            if not files_equal_to_patch_source(source_abs, hunks):
                print("  Conflict: file changed in source, cannot cleanly delete")
                delete_conflicts.append(source_rel)
                failed.append(rel_patch)
                continue
            os.remove(source_abs)
            continue

        if is_new:
            if os.path.isfile(source_abs):
                print("  Conflict: file already exists for new-file patch")
                failed.append(rel_patch)
                continue
            new_lines = []
            for hunk in hunks:
                for hl in hunk['lines']:
                    if not hl:
                        continue
                    if hl[0] == '+':
                        new_lines.append(hl[1:])
                    elif hl[0] == '\\':
                        if new_lines and new_lines[-1].endswith('\n'):
                            new_lines[-1] = new_lines[-1].rstrip('\r\n')
            parent = os.path.dirname(source_abs)
            if parent:
                os.makedirs(parent, exist_ok=True)
            with open(source_abs, 'w', encoding='utf-8') as f:
                f.writelines(new_lines)
            continue

        if not os.path.isfile(source_abs):
            print("  Conflict: source file missing for modification patch")
            missing_in_source.append(source_rel)
            failed.append(rel_patch)
            continue

        source_lines = read_text_lines(source_abs)
        if source_lines is None:
            print("  Failed to read source: not a text file")
            failed.append(rel_patch)
            continue

        new_lines = apply_hunks_to_lines(source_lines, hunks)
        if new_lines is None:
            print("  Failed to apply patch (context mismatch)")
            failed.append(rel_patch)
            continue

        with open(source_abs, 'w', encoding='utf-8') as f:
            f.writelines(new_lines)

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

    print()
    print("Partial changes (if any) have been written to the output directory.")
    print()
    print("To resolve conflicts:")
    print("  1. Manually edit the affected files in the output directory.")
    print("  2. Regenerate patches with the resolved output:")
    print()
    print(f"    {format_create_patch_cmd(input_abs, output_abs, patch_abs)}")
    print()

    return False


def files_equal_to_patch_source(source_abs, hunks):
    """Verify the source file matches the '-' / context lines of a deletion patch."""
    source_lines = read_text_lines(source_abs)
    if source_lines is None:
        return False
    expected = []
    for hunk in hunks:
        for hl in hunk['lines']:
            if not hl:
                continue
            tag = hl[0]
            if tag in (' ', '-'):
                expected.append(hl[1:])
    if len(expected) != len(source_lines):
        return False
    for src, exp in zip(source_lines, expected):
        if not lines_match(src, exp):
            return False
    return True


def create_patch(input_path, output_path, patch_dir):
    """Find differences between input and output and save as per-file patches.

    Uses ``difflib.unified_diff`` to produce standard unified diffs. Each changed
    file gets its own ``.patch`` file in the patch directory, mirroring the
    source directory structure with ``.patch`` appended to the filename.

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

    # When apply_patch copies input into output/basename(input), we must
    # compare against that subdirectory so paths stay aligned with patches.
    input_basename = os.path.basename(os.path.normpath(input_abs))
    actual_output = os.path.join(output_abs, input_basename)
    if not os.path.isdir(actual_output):
        actual_output = output_abs

    if not os.path.isdir(actual_output):
        print(f"Error: Output directory does not exist: {actual_output}")
        return False

    if os.path.exists(patch_abs):
        shutil.rmtree(patch_abs)
    os.makedirs(patch_abs, exist_ok=True)

    # When actual_output is a subdirectory of output_abs, patch paths must
    # include the basename prefix so they align with apply_patch expectations.
    path_prefix = ''
    if actual_output != output_abs:
        path_prefix = input_basename + '/'

    input_files = list_relative_files(input_abs)
    output_files = list_relative_files(actual_output)
    all_files = sorted(input_files | output_files)

    skipped_binary = []
    changed = []

    for rel in all_files:
        in_input = rel in input_files
        in_output = rel in output_files
        in_path = os.path.join(input_abs, rel) if in_input else None
        out_path = os.path.join(actual_output, rel) if in_output else None

        if in_input and in_output and files_equal(in_path, out_path):
            continue

        from_lines = read_text_lines(in_path) if in_input else []
        to_lines = read_text_lines(out_path) if in_output else []

        if from_lines is None or to_lines is None:
            skipped_binary.append(rel)
            continue

        patch_rel = path_prefix + rel
        from_label = 'a/' + patch_rel if in_input else '/dev/null'
        to_label = 'b/' + patch_rel if in_output else '/dev/null'

        diff = list(difflib.unified_diff(
            from_lines, to_lines,
            fromfile=from_label, tofile=to_label,
        ))
        if not diff:
            continue

        patch_text = ''.join(diff)
        if not patch_text.endswith('\n'):
            patch_text += '\n'

        patch_file = os.path.join(patch_abs, patch_rel + '.patch')
        parent = os.path.dirname(patch_file)
        if parent:
            os.makedirs(parent, exist_ok=True)
        with open(patch_file, 'w', encoding='utf-8') as f:
            f.write(patch_text)
        changed.append(rel)

    if skipped_binary:
        print(f"Skipped {len(skipped_binary)} binary file(s):")
        for f in skipped_binary:
            print(f"  {f}")

    if not changed:
        print(f"No textual differences found. Empty patch directory at {patch_abs}")
        return True

    print(f"Generated patches for {len(changed)} file(s):")
    for rel in changed:
        print(f"  {rel}.patch")
    print(f"Patches saved to {patch_abs}")
    return True


def main():
    parser = argparse.ArgumentParser(
        description='Apply or create per-file patches between directory trees',
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )

    subparsers = parser.add_subparsers(dest='command', required=True)

    apply_parser = subparsers.add_parser(
        'apply',
        help='Copy input directory to output and apply per-file patches',
    )
    apply_parser.add_argument('--input', required=True,
                              help='Source directory to copy from')
    apply_parser.add_argument('--output', required=True,
                              help='Destination directory to copy to and apply patches in')
    apply_parser.add_argument('--patch', required=True,
                              help='Directory containing per-file patches')
    apply_parser.add_argument('--stamp',
                              help='Create an empty stamp file at this path on success')

    create_parser = subparsers.add_parser(
        'create-patch',
        help='Create per-file patches from differences between two directories',
    )
    create_parser.add_argument('--input', required=True,
                               help='Original (unmodified) directory')
    create_parser.add_argument('--output', required=True,
                               help='Modified directory')
    create_parser.add_argument('--patch', required=True,
                               help='Directory to save per-file patches into')

    args = parser.parse_args()

    if args.command == 'apply':
        success = apply_patch(args.input, args.output, args.patch)
        if success and args.stamp:
            stamp_abs = os.path.abspath(args.stamp)
            stamp_dir = os.path.dirname(stamp_abs)
            if stamp_dir:
                os.makedirs(stamp_dir, exist_ok=True)
            with open(stamp_abs, 'w'):
                pass
    elif args.command == 'create-patch':
        success = create_patch(args.input, args.output, args.patch)
    else:
        parser.print_help()
        return 1

    return 0 if success else 1


if __name__ == '__main__':
    sys.exit(main())
