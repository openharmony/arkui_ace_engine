#!/usr/bin/env python3
"""
Fix test build configuration issues.
Adds missing static modifier files to test BUILD.gn.
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Optional

class BuildConfigFixer:
    """Fix test build configuration issues."""

    def __init__(self, ace_engine_root: str):
        self.root = ace_engine_root
        self.build_gn_path = os.path.join(self.root, "test/unittest/capi/BUILD.gn")

    def find_missing_static_modifiers(self) -> List[str]:
        """Find static modifier files that are not in BUILD.gn."""
        if not os.path.exists(self.build_gn_path):
            print(f"BUILD.gn not found: {self.build_gn_path}")
            return []

        # Read BUILD.gn to see what's already included
        with open(self.build_gn_path, 'r') as f:
            build_content = f.read()

        # Find all static modifier files in the codebase
        static_modifier_files = []
        bridge_dir = os.path.join(self.root, "frameworks/core/components_ng/pattern")

        for dirpath, _, filenames in os.walk(bridge_dir):
            for filename in filenames:
                if filename.endswith("_static_modifier.cpp"):
                    rel_path = os.path.relpath(os.path.join(dirpath, filename), self.root)
                    static_modifier_files.append(rel_path)

        # Check which ones are missing from BUILD.gn
        missing_files = []
        for file_path in static_modifier_files:
            # Convert to BUILD.gn format
            gn_path = f"\"$ace_root/{file_path}\","
            if gn_path not in build_content:
                missing_files.append(file_path)

        return missing_files

    def find_static_modifier_for_component(self, component: str) -> Optional[str]:
        """Find static modifier file for a specific component."""
        component_lower = component.lower()
        possible_paths = [
            f"frameworks/core/components_ng/pattern/{component_lower}/bridge/{component_lower}_static_modifier.cpp",
            f"frameworks/core/components_ng/pattern/{component}/bridge/{component}_static_modifier.cpp",
        ]

        for rel_path in possible_paths:
            full_path = os.path.join(self.root, rel_path)
            if os.path.exists(full_path):
                return rel_path

        # Search for the file
        search_pattern = f"*{component_lower}*static_modifier.cpp"
        for dirpath, _, filenames in os.walk(os.path.join(self.root, "frameworks/core/components_ng/pattern")):
            for filename in filenames:
                if component_lower in filename.lower() and "static_modifier.cpp" in filename:
                    rel_path = os.path.relpath(os.path.join(dirpath, filename), self.root)
                    return rel_path

        return None

    def add_file_to_build_gn(self, file_path: str) -> bool:
        """Add a file to BUILD.gn sources."""
        if not os.path.exists(self.build_gn_path):
            print(f"BUILD.gn not found: {self.build_gn_path}")
            return False

        # Convert to BUILD.gn format
        gn_path = f"\"$ace_root/{file_path}\","

        with open(self.build_gn_path, 'r') as f:
            lines = f.readlines()

        # Check if already present
        for line in lines:
            if gn_path in line:
                print(f"File already in BUILD.gn: {gn_path}")
                return True

        # Find insertion point (look for similar static modifier files)
        insertion_point = -1
        for i, line in enumerate(lines):
            if "static_modifier.cpp" in line and "bridge" in line:
                # Insert after this line
                insertion_point = i + 1
                break

        if insertion_point == -1:
            # Look for sources list
            for i, line in enumerate(lines):
                if "sources = [" in line:
                    insertion_point = i + 1
                    # Find the closing bracket
                    for j in range(i, len(lines)):
                        if "]" in lines[j]:
                            insertion_point = j
                            break
                    break

        if insertion_point == -1:
            print("Could not find insertion point in BUILD.gn")
            return False

        # Backup original
        backup_path = self.build_gn_path + ".bak"
        with open(backup_path, 'w') as f:
            f.writelines(lines)

        # Insert the line with proper indentation
        # Determine indentation of previous line
        prev_line = lines[insertion_point - 1] if insertion_point > 0 else ""
        indent = len(prev_line) - len(prev_line.lstrip())

        new_line = " " * indent + gn_path + "\n"
        lines.insert(insertion_point, new_line)

        # Write updated content
        with open(self.build_gn_path, 'w') as f:
            f.writelines(lines)

        print(f"Added {gn_path} to BUILD.gn")
        print(f"Backup saved to {backup_path}")

        return True

    def remove_duplicate_entries(self) -> int:
        """Remove duplicate entries from BUILD.gn sources."""
        if not os.path.exists(self.build_gn_path):
            return 0

        with open(self.build_gn_path, 'r') as f:
            lines = f.readlines()

        # Find sources section
        in_sources = False
        sources_start = -1
        sources_end = -1
        sources_lines = []

        for i, line in enumerate(lines):
            if "sources = [" in line:
                in_sources = True
                sources_start = i
            elif in_sources and line.strip() == "]":
                sources_end = i
                break

        if sources_start == -1 or sources_end == -1:
            print("Could not find sources section in BUILD.gn")
            return 0

        # Extract sources lines
        sources_lines = lines[sources_start:sources_end + 1]

        # Remove duplicates while preserving order
        seen = set()
        unique_lines = []
        duplicates = 0

        for line in sources_lines:
            stripped = line.strip()
            if stripped in seen:
                duplicates += 1
                continue
            if stripped:  # Skip empty lines
                seen.add(stripped)
            unique_lines.append(line)

        if duplicates == 0:
            print("No duplicate entries found")
            return 0

        # Replace sources section
        new_lines = lines[:sources_start] + unique_lines + lines[sources_end + 1:]

        # Backup
        backup_path = self.build_gn_path + ".bak.duplicates"
        with open(backup_path, 'w') as f:
            f.writelines(lines)

        # Write updated content
        with open(self.build_gn_path, 'w') as f:
            f.writelines(new_lines)

        print(f"Removed {duplicates} duplicate entries from BUILD.gn")
        print(f"Backup saved to {backup_path}")

        return duplicates

    def fix_missing_files(self) -> int:
        """Fix all missing static modifier files."""
        missing_files = self.find_missing_static_modifiers()
        if not missing_files:
            print("No missing static modifier files found")
            return 0

        print(f"Found {len(missing_files)} missing static modifier file(s):")
        for file_path in missing_files:
            print(f"  {file_path}")

        added_count = 0
        for file_path in missing_files:
            if self.add_file_to_build_gn(file_path):
                added_count += 1

        return added_count

    def fix_component(self, component: str) -> bool:
        """Fix build config for specific component."""
        file_path = self.find_static_modifier_for_component(component)
        if not file_path:
            print(f"Could not find static modifier file for component {component}")
            return False

        print(f"Found static modifier file: {file_path}")
        return self.add_file_to_build_gn(file_path)


def main():
    """Main entry point."""
    import argparse

    parser = argparse.ArgumentParser(description="Fix test build configuration issues")
    parser.add_argument("--component", help="Specific component to fix")
    parser.add_argument("--missing", action="store_true", help="Fix all missing static modifier files")
    parser.add_argument("--deduplicate", action="store_true", help="Remove duplicate entries from BUILD.gn")
    parser.add_argument("--root", help="ACE Engine root directory (default: current directory)")

    args = parser.parse_args()

    root = args.root if args.root else os.getcwd()

    fixer = BuildConfigFixer(root)

    if args.component:
        success = fixer.fix_component(args.component)
        return 0 if success else 1
    elif args.missing:
        added_count = fixer.fix_missing_files()
        print(f"\nAdded {added_count} missing file(s) to BUILD.gn")
        return 0
    elif args.deduplicate:
        removed_count = fixer.remove_duplicate_entries()
        print(f"\nRemoved {removed_count} duplicate entry(s)")
        return 0
    else:
        print("Please specify an option: --component, --missing, or --deduplicate")
        return 1


if __name__ == "__main__":
    sys.exit(main())