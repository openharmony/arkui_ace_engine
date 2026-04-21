#!/usr/bin/env python3
"""
Fix Converter API misuse in C API tests.
Replaces Converter::GetOptPtr(&var) with Converter::GetOpt(var).
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Tuple

class ConverterAPIFixer:
    """Fix Converter API misuse issues."""

    def __init__(self, ace_engine_root: str):
        self.root = ace_engine_root
        self.pattern = re.compile(r'Converter::GetOptPtr\s*\(\s*&([a-zA-Z_][a-zA-Z0-9_]*)\s*\)')

    def find_test_files(self) -> List[str]:
        """Find C API test files that might have Converter API issues."""
        test_files = []
        test_dir = os.path.join(self.root, "test/unittest/capi")

        for dirpath, _, filenames in os.walk(test_dir):
            for filename in filenames:
                if filename.endswith("_test.cpp") or filename.endswith("_accessor_test.cpp"):
                    test_files.append(os.path.join(dirpath, filename))

        return test_files

    def find_converter_api_issues(self, file_path: str) -> List[Tuple[int, str, str]]:
        """Find Converter::GetOptPtr(&var) issues in file."""
        issues = []

        with open(file_path, 'r') as f:
            lines = f.readlines()

        for i, line in enumerate(lines, 1):
            matches = self.pattern.findall(line)
            for var_name in matches:
                issues.append((i, line.strip(), var_name))

        return issues

    def fix_file(self, file_path: str) -> bool:
        """Fix Converter API issues in a file."""
        with open(file_path, 'r') as f:
            content = f.read()

        # Find all matches
        matches = list(self.pattern.finditer(content))
        if not matches:
            return False

        # Backup original
        backup_path = file_path + ".bak"
        with open(backup_path, 'w') as f:
            f.write(content)

        # Replace in reverse order to preserve positions
        for match in reversed(matches):
            var_name = match.group(1)
            old_expr = match.group(0)
            new_expr = f'Converter::GetOpt({var_name})'

            start, end = match.span()
            content = content[:start] + new_expr + content[end:]

        # Write fixed content
        with open(file_path, 'w') as f:
            f.write(content)

        print(f"Fixed {len(matches)} Converter API issue(s) in {file_path}")
        print(f"Backup saved to {backup_path}")

        return True

    def update_test_expectations(self, file_path: str) -> bool:
        """Update test expectations from nullptr to nullopt."""
        with open(file_path, 'r') as f:
            content = f.read()

        # Common patterns that need updating
        patterns = [
            (r'EXPECT_EQ\s*\(\s*optValue\s*,\s*nullptr\s*\)', 'EXPECT_FALSE(optValue.has_value())'),
            (r'ASSERT_EQ\s*\(\s*optValue\s*,\s*nullptr\s*\)', 'ASSERT_FALSE(optValue.has_value())'),
            (r'EXPECT_EQ\s*\(\s*optValue\s*,\s*std::nullopt\s*\)', 'EXPECT_FALSE(optValue.has_value())'),
            (r'ASSERT_EQ\s*\(\s*optValue\s*,\s*std::nullopt\s*\)', 'ASSERT_FALSE(optValue.has_value())'),
        ]

        changed = False
        for pattern, replacement in patterns:
            if re.search(pattern, content):
                content = re.sub(pattern, replacement, content)
                changed = True

        if changed:
            with open(file_path, 'w') as f:
                f.write(content)
            print(f"Updated test expectations in {file_path}")

        return changed

    def fix_all(self) -> int:
        """Fix all Converter API issues in test files."""
        test_files = self.find_test_files()
        total_fixes = 0

        for test_file in test_files:
            issues = self.find_converter_api_issues(test_file)
            if issues:
                print(f"\nFound {len(issues)} Converter API issue(s) in {test_file}:")
                for line_num, line, var_name in issues:
                    print(f"  Line {line_num}: {line}")

                if self.fix_file(test_file):
                    total_fixes += len(issues)

                # Also update test expectations
                self.update_test_expectations(test_file)

        return total_fixes

    def fix_specific_test(self, test_name: str) -> bool:
        """Fix Converter API issues in specific test file."""
        test_file = os.path.join(self.root, "test/unittest/capi", test_name)
        if not os.path.exists(test_file):
            # Try to find with extensions
            test_file = os.path.join(self.root, "test/unittest/capi", f"{test_name}.cpp")
            if not os.path.exists(test_file):
                test_file = os.path.join(self.root, "test/unittest/capi", f"{test_name}_test.cpp")
                if not os.path.exists(test_file):
                    test_file = os.path.join(self.root, "test/unittest/capi", f"{test_name}_accessor_test.cpp")

        if not os.path.exists(test_file):
            print(f"Test file not found: {test_name}")
            return False

        issues = self.find_converter_api_issues(test_file)
        if not issues:
            print(f"No Converter API issues found in {test_file}")
            return False

        print(f"Found {len(issues)} Converter API issue(s) in {test_file}:")
        for line_num, line, var_name in issues:
            print(f"  Line {line_num}: {line}")

        success = self.fix_file(test_file)
        if success:
            self.update_test_expectations(test_file)

        return success


def main():
    """Main entry point."""
    import argparse

    parser = argparse.ArgumentParser(description="Fix Converter API misuse in C API tests")
    parser.add_argument("--test", help="Specific test file to fix")
    parser.add_argument("--all", action="store_true", help="Fix all test files")
    parser.add_argument("--root", help="ACE Engine root directory (default: current directory)")

    args = parser.parse_args()

    root = args.root if args.root else os.getcwd()

    fixer = ConverterAPIFixer(root)

    if args.test:
        success = fixer.fix_specific_test(args.test)
        return 0 if success else 1
    elif args.all:
        total_fixes = fixer.fix_all()
        print(f"\nTotal fixes applied: {total_fixes}")
        return 0
    else:
        print("Please specify --test <test_file> or --all")
        return 1


if __name__ == "__main__":
    sys.exit(main())