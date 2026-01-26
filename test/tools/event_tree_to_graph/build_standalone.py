#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
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
#

"""
Build standalone event tree visualizer script.

This script combines all Python modules into a single standalone file
for easy distribution.
"""

import os
import sys
from pathlib import Path


def safe_print(text):
    """Print text with encoding safety for Windows console."""
    try:
        print(text)
    except UnicodeEncodeError:
        # Fallback for Windows console with GBK encoding
        print(text.encode('ascii', 'ignore').decode('ascii'))


# Module dependency order (topological sort)
MODULES = [
    # Base utilities
    'src/utils/log_wrapper.py',
    'src/utils/value_parser.py',
    'src/keywords.py',

    # Bean classes
    'src/beans/base_bean.py',
    'src/beans/touch_point.py',
    'src/beans/procedure_step.py',
    'src/beans/state_history.py',
    'src/beans/event_node.py',
    'src/beans/frame_node.py',
    'src/beans/event_scope.py',
    'src/beans/event_procedures.py',
    'src/beans/event_tree.py',
    'src/beans/dump_result.py',

    # Core processing
    'src/pre_process.py',
    'src/content_parser.py',

    # Graph generation
    'src/graph/graph_converter.py',

    # Main entry
    'main.py',
]


def read_module_file(filepath):
    """Read a Python module file and return its content."""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    return content


def process_module_content(content, filepath):
    """Process module content to make it standalone-compatible.

    Args:
        content: The Python file content
        filepath: Path to the module file

    Returns:
        Processed content ready for inclusion in standalone script
    """
    lines = content.split('\n')
    processed_lines = []

    # Skip shebang and encoding for non-main modules
    if filepath != 'main.py':
        # Skip first two lines if they are shebang/encoding
        if lines and lines[0].startswith('#!'):
            lines = lines[1:]
        if lines and (lines[0].startswith('# -*-') or lines[0].startswith('# coding')):
            lines = lines[1:]

    # Track if we've seen any actual code
    seen_code = False
    skip_import_continuation = False

    for i, line in enumerate(lines):
        # Skip copyright header for non-main modules (keep only for main.py)
        if filepath != 'main.py' and not seen_code:
            if line.startswith('#') or line.strip() == '':
                continue
            seen_code = True

        # Handle multi-line import continuation
        if skip_import_continuation:
            # Comment out continuation lines
            processed_lines.append(f'# {line}')
            # Check if continuation ends (no backslash)
            if not line.rstrip().endswith('\\'):
                skip_import_continuation = False
            continue

        # Modify imports to use local namespace
        # Remove "from src." imports
        if line.strip().startswith('from src.') or line.strip().startswith('from .'):
            # Convert "from src.xyz import abc" to "# import abc (inlined)"
            processed_lines.append(f'# {line}')
            # Check if line ends with backslash (continuation)
            if line.rstrip().endswith('\\'):
                skip_import_continuation = True
            continue

        # Modify "import src.xxx" imports
        if 'import src.' in line:
            processed_lines.append(f'# {line}')
            # Check if line ends with backslash (continuation)
            if line.rstrip().endswith('\\'):
                skip_import_continuation = True
            continue

        # Keep everything else
        processed_lines.append(line)

    return '\n'.join(processed_lines)


def build_standalone():
    """Build standalone script by combining all modules."""
    print('='*100)
    print('Building standalone event tree visualizer...')
    print('='*100)

    output_file = 'event_tree_visualizer.py'

    # Start with header
    output_parts = []
    output_parts.append('#!/usr/bin/env python3')
    output_parts.append('# -*- coding: utf-8 -*-')
    output_parts.append('')
    output_parts.append('from __future__ import annotations  # Enable postponed evaluation of annotations')
    output_parts.append('')
    output_parts.append('#')
    output_parts.append('# Standalone Event Tree Visualizer')
    output_parts.append('#')
    output_parts.append('# This is a standalone version combining all modules.')
    output_parts.append('# Generated automatically by build_standalone.py')
    output_parts.append('#')
    output_parts.append('')
    output_parts.append('')

    # Add module separator comment
    def add_module_separator(name):
        output_parts.append('')
        output_parts.append('# ' + '='*96)
        output_parts.append(f'# Module: {name}')
        output_parts.append('# ' + '='*96)
        output_parts.append('')

    # Process each module
    for module_path in MODULES:
        if not os.path.exists(module_path):
            print(f'[WARNING]  Warning: {module_path} not found, skipping...')
            continue

        print(f'[PROCESSING] Processing: {module_path}')

        add_module_separator(module_path)

        content = read_module_file(module_path)
        processed = process_module_content(content, module_path)

        output_parts.append(processed)
        output_parts.append('')

    # Combine all parts
    standalone_script = '\n'.join(output_parts)

    # Write to output file
    print(f'\n[WRITE] Writing to: {output_file}')
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(standalone_script)

    # Make executable
    os.chmod(output_file, 0o755)

    file_size = os.path.getsize(output_file)
    print(f'[OK] Successfully created: {output_file} ({file_size:,} bytes)')
    print('='*100)
    print('\n[INFO] Usage:')
    print(f'  python3 {output_file}')
    print(f'  python3 {output_file} -r  # Dump from device')
    print(f'  python3 {output_file} -d  # Enable debug mode')
    print('\n')

    return output_file


if __name__ == '__main__':
    try:
        output_file = build_standalone()
        print(f'[OK] Build completed successfully!')
        print(f'[FILE] Output: {output_file}')
    except Exception as e:
        print(f'[ERROR] Build failed: {e}')
        import traceback
        traceback.print_exc()
        sys.exit(1)
