#!/usr/bin/env python3
"""
C API Test Naming Verifier

This script verifies that all C API unit test names follow the standardized
naming convention: methodNameTestScenario

Usage:
    python verify_naming.py [options]

Options:
    --verify               Verify all test names (default)
    --report               Generate detailed compliance report
    --directory DIR        Scan specific directory
    --file FILE            Check specific file
    --exclude-generated    Exclude generated test directories
    --help                 Show this help message
"""

import os
import re
import sys
import argparse
from collections import Counter
from pathlib import Path
from typing import List, Tuple, Dict, Optional

def find_ace_engine_root(start_path: Path) -> Path:
    """Find the ace_engine root directory by looking for marker files."""
    current = start_path.absolute()
    markers = [".gn", "CLAUDE.md", "test/unittest/capi"]

    while current != current.parent:  # Stop at root
        # Check if any marker exists
        for marker in markers:
            marker_path = current / marker
            if marker_path.exists():
                return current
        current = current.parent

    # Fallback to start_path parent's parent (should be ace_engine)
    return start_path.parent.parent.parent.parent

# Directories to scan (relative to ace_engine root)
BASE_DIR = find_ace_engine_root(Path(__file__))
DEFAULT_DIRS = [
    "test/unittest/capi/modifiers",
    "test/unittest/capi/accessors",
    "test/unittest/capi/utils",
]

# Exclude generated directories
EXCLUDE_DIRS = ["generated"]

# Regex to match HWTEST_F macros and extract test class and name
HWTEST_F_REGEX = re.compile(r'HWTEST_F\s*\(\s*(\w+)\s*,\s*(\w+)\s*,', re.MULTILINE)

# Regex to match @tc.name tags (should match test name)
TC_NAME_REGEX = re.compile(r'@tc\.name:\s*(\w+)', re.MULTILINE)

# Regex to find line numbers for error reporting
LINE_SPLIT_REGEX = re.compile(r'\n')

# Regex to find method calls in test bodies
ACCESSOR_METHOD_REGEX = re.compile(r'accessor_->([A-Za-z0-9_]+)')
MODIFIER_METHOD_REGEX = re.compile(r'modifier_->([A-Za-z0-9_]+)')
COMMON_MODIFIER_METHOD_REGEX = re.compile(r'commonModifier_->([A-Za-z0-9_]+)')

def extract_test_body(content: str, start_pos: int) -> str:
    """Extract the test body starting from the given position."""
    # Find the opening brace after the HWTEST_F macro
    brace_pos = content.find('{', start_pos)
    if brace_pos == -1:
        return ""

    # Count braces to find matching closing brace
    brace_count = 1
    pos = brace_pos + 1

    while pos < len(content) and brace_count > 0:
        if content[pos] == '{':
            brace_count += 1
        elif content[pos] == '}':
            brace_count -= 1
        pos += 1

    if brace_count == 0:
        return content[brace_pos + 1:pos - 1]
    return ""

def find_tc_name_for_test(content: str, hwtest_start_pos: int) -> Optional[str]:
    """
    Find the @tc.name tag for a test given the HWTEST_F start position.

    Searches backwards from the HWTEST_F macro for the nearest @tc.name tag,
    stopping at the previous HWTEST_F macro.
    """
    # Find all HWTEST_F positions before the current one
    all_hwtest_matches = list(HWTEST_F_REGEX.finditer(content))

    # Find the HWTEST_F match that ends just before our start position
    prev_hwtest_end = 0  # Start of file by default
    for match in all_hwtest_matches:
        if match.end() < hwtest_start_pos:
            prev_hwtest_end = match.end()
        else:
            break  # We've reached or passed current position

    # Search between previous HWTEST_F end and current HWTEST_F start
    search_start = max(prev_hwtest_end, hwtest_start_pos - 2000)  # Limit search to 2000 chars
    window = content[search_start:hwtest_start_pos]

    # Find all @tc.name matches in the window
    matches = list(TC_NAME_REGEX.finditer(window))
    if matches:
        # Return the last match (closest to HWTEST_F)
        return matches[-1].group(1)

    return None

class TestNameValidator:
    """Validate test names against naming convention."""

    @staticmethod
    def extract_method_name(test_name: str) -> str:
        """Extract method name from test name following methodNameTestScenario pattern."""
        # Handle DISABLED prefix
        if test_name.startswith('DISABLED_'):
            test_name = test_name[len('DISABLED_'):]

        # Split by "Test"
        parts = test_name.split('Test')
        if len(parts) >= 2:
            return parts[0]
        return ""

    @staticmethod
    def validate_name(name: str, test_body: str = "", file_path: Optional[str] = None) -> Tuple[bool, List[str]]:
        """
        Validate a test name against naming convention.

        Args:
            name: Test name to validate
            test_body: Optional test body content to verify method calls
            file_path: Optional file path to identify utils tests

        Returns:
            Tuple of (is_valid, list_of_violations)
        """
        violations = []
        original_name = name

        # Check for DISABLED prefix
        disabled = name.startswith('DISABLED_')
        if disabled:
            name = name[len('DISABLED_'):]

        # Rule 1: Check for "Test" in name
        parts = name.split('Test')

        if len(parts) == 1:
            # No 'Test' in name
            violations.append(f"No 'Test' in name: '{original_name}'")
            return False, violations

        # Multiple 'Test' occurrences are ALLOWED when method name contains "Test"
        # e.g., setHitTestBehaviorTestValidInput → ['setHitTestBehavior', 'ValidInput']
        # e.g., setOnChildTouchTestTestValidCallback → ['setOnChildTouch', '', 'ValidCallback']
        # Last part is scenario, everything before last "Test" is method name
        scenario_part = parts[-1]  # Last part after final "Test"
        method_part = 'Test'.join(parts[:-1])  # Join all parts before final "Test"

        # Rule 2: Method name format
        # - camelCase methods: first character lowercase (e.g., setWidth)
        # - Underscored methods: preserve underscores (e.g., set_onChangeEvent_selected)
        if not method_part:
            violations.append(f"Empty method name in: '{original_name}'")
        elif '_' not in method_part and method_part[0].isupper():
            # Only flag camelCase methods starting with uppercase
            violations.append(f"Method name should start with lowercase: '{original_name}' → '{method_part[0].lower()}{method_part[1:]}'")

        # Check for empty scenario (test name ends with "Test")
        # Disable for the moment
        #if not scenario_part:
        #    violations.append(f"Empty scenario (name ends with 'Test'): '{original_name}' → add scenario like 'DefaultValues' or 'ValidInput'")

        # Rule 3: Scenario should be PascalCase (first letter uppercase)
        if scenario_part and scenario_part[0].islower():
            violations.append(f"Scenario should start with uppercase: '{original_name}' → '{scenario_part[0].upper()}{scenario_part[1:]}'")

        # Rule 4: Length check (warning only)
        if len(original_name) > 100:
            violations.append(f"Name too long ({len(original_name)} > 100 chars): '{original_name}'")

        # Rule 5: Check for DISABLED prefix format
        if disabled and not original_name.startswith('DISABLED_'):
            violations.append(f"DISABLED prefix should be uppercase: '{original_name}' → 'DISABLED_{name}'")

        # Rule 6: For utility tests (simple names with Test suffix)
        # Allow simple names like SimpleTypesTest, ArrayTypesTest
        # These have empty method_part (or very short)
        if not method_part and scenario_part:
            # This is a simple test name like "SimpleTypesTest"
            # Check that scenario_part is CamelCase
            if scenario_part and scenario_part[0].islower():
                violations.append(f"Simple test name should be CamelCase: '{original_name}' → '{scenario_part[0].upper()}{scenario_part[1:]}'")
            # Simple names are valid
            return len(violations) == 0, violations

        # Additional checks for method-scenario names
        # NOTE: Method names CAN contain "Test" (e.g., setHitTestBehavior, setOnChildTouchTest)
        # This is acceptable and will result in multiple "Test" in the full test name

        # Determine if we should skip method call verification
        skip_method_check = False
        if file_path and "/utils/" in file_path:
            skip_method_check = True
        elif scenario_part and "DefaultValues" in scenario_part:
            skip_method_check = True
        elif scenario_part and scenario_part.lower().startswith('default'):
            skip_method_check = True

        # NEW RULE: Verify method name matches actual method calls in test body
        if test_body and method_part and not skip_method_check:
            # Look for method calls in the test body
            accessor_methods = set(ACCESSOR_METHOD_REGEX.findall(test_body))
            modifier_methods = set(MODIFIER_METHOD_REGEX.findall(test_body))
            common_modifier_methods = set(COMMON_MODIFIER_METHOD_REGEX.findall(test_body))
            all_methods = accessor_methods.union(modifier_methods).union(common_modifier_methods)

            if all_methods:
                # Check if the method name from test name appears in the test body
                # For underscored names: exact match required (preserves underscores)
                # For camelCase names: case-insensitive match
                found_method = False

                for actual_method in all_methods:
                    # Exact match (handles underscored methods)
                    if actual_method == method_part:
                        found_method = True
                        break

                    # Case-insensitive match for camelCase methods
                    if '_' not in actual_method and '_' not in method_part:
                        if actual_method.lower() == method_part.lower():
                            found_method = True
                            break

                    # For both camelCase and underscored methods
                    if actual_method == method_part:
                        found_method = True
                        break

                if not found_method:
                    # Try to find the most likely method that should be in the test name
                    possible_methods = []
                    for actual_method in all_methods:
                            possible_methods.append(actual_method)

                    if possible_methods:
                        # Find the most common method (likely the one being tested)
                        method_counts = Counter(possible_methods)
                        most_common_method = method_counts.most_common(1)[0][0]

                        # Check if method_part contains extra words that should be in scenario
                        # e.g., "setButtonOptions1ButtonType" -> method should be "setButtonOptions1"
                        # Try to find the longest matching prefix
                        method_part_lower = method_part.lower()
                        best_match = None
                        for actual_method in all_methods:
                            actual_lower = actual_method.lower()
                            if method_part_lower.startswith(actual_lower):
                                # method_part starts with actual method name
                                if not best_match or len(actual_method) > len(best_match):
                                    best_match = actual_method

                        if best_match:
                            # Found a matching prefix
                            # Extract extra part from method_part and prepend to scenario
                            extra_part = method_part[len(best_match):]
                            if extra_part:
                                # Prepend extra part to scenario
                                combined_scenario = extra_part + scenario_part
                                suggested_name = f"{best_match}Test{combined_scenario}"
                            else:
                                suggested_name = f"{best_match}Test{scenario_part}"
                            violations.append(f"Method name mismatch: Test name has '{method_part}' but test body calls '{best_match}'")
                            violations.append(f"  Suggested test name: '{suggested_name}'")
                        else:
                            violations.append(f"Method name mismatch: Test name has '{method_part}' but test body calls methods: {sorted(all_methods)}")
                            violations.append(f"  Suggested method name: '{most_common_method}'")
            else:
                # Test body has no method calls
                # This could be a valid test (e.g., checking default values)
                # Only warn if the test name suggests it should test a method
                if method_part and not scenario_part.lower().startswith('default'):
                    # Test has a method name but no method calls, and it's not a default values test
                    violations.append(f"Test name suggests testing method '{method_part}' but test body contains no method calls: '{original_name}'")

        return len(violations) == 0, violations

    @staticmethod
    def suggest_fix(name: str) -> str:
        """Suggest a fixed name based on naming convention."""
        original = name

        # Handle DISABLED prefix
        disabled = name.startswith('DISABLED_')
        if disabled:
            name = name[len('DISABLED_'):]

        parts = name.split('Test')
        if len(parts) != 2:
            # Cannot auto-fix complex cases
            return original

        method, scenario = parts

        # Fix method name case
        if method and method[0].isupper():
            method = method[0].lower() + method[1:]

        # Fix scenario case
        if scenario and scenario[0].islower():
            scenario = scenario[0].upper() + scenario[1:]

        # Reconstruct
        fixed = f"{method}Test{scenario}"
        if disabled:
            fixed = f"DISABLED_{fixed}"

        return fixed

class TestFileScanner:
    """Scan test files for naming violations."""

    def __init__(self, base_dir: Path, exclude_generated: bool = True):
        self.base_dir = base_dir
        self.exclude_generated = exclude_generated

    def find_test_files(self, specific_dirs: Optional[List[str]] = None) -> List[Path]:
        """Find all C API test files."""
        test_files = []

        if specific_dirs:
            dirs_to_scan = [self.base_dir / d for d in specific_dirs]
        else:
            dirs_to_scan = [self.base_dir / d for d in DEFAULT_DIRS]

        for test_dir in dirs_to_scan:
            if not test_dir.exists():
                print(f"Warning: Directory not found: {test_dir}")
                continue

            for root, dirs, files in os.walk(test_dir):
                # Skip excluded directories
                if self.exclude_generated:
                    dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]

                for file in files:
                    if file.endswith('.cpp'):
                        filepath = Path(root) / file
                        test_files.append(filepath)

        return test_files

    def scan_file(self, filepath: Path) -> List[Dict]:
        """Scan a single file for test names and validate them."""
        violations = []

        try:
            content = filepath.read_text(encoding='utf-8', errors='ignore')

            # Find line numbers for error reporting
            lines = LINE_SPLIT_REGEX.split(content)

            # Find all HWTEST_F macros
            for match in HWTEST_F_REGEX.finditer(content):
                test_class = match.group(1)
                test_name = match.group(2)
                start_pos = match.start()

                # Calculate line number
                line_num = 1
                chars_seen = 0
                for i, line in enumerate(lines):
                    chars_seen += len(line) + 1  # +1 for newline
                    if chars_seen > start_pos:
                        line_num = i + 1
                        break

                # Extract test body
                test_body = extract_test_body(content, start_pos)

                # Validate the test name
                is_valid, name_violations = TestNameValidator.validate_name(test_name, test_body, str(filepath))

                # Check @tc.name tag (if present)
                tc_name = find_tc_name_for_test(content, start_pos)
                # Debug: print capture
                # if tc_name:
                #     print(f"DEBUG: tc_name captured: '{tc_name}'")

                # Store original test name for reporting
                original_test_name = test_name

                # For comparison with @tc.name, remove DISABLED_ prefix
                test_name_for_comparison = test_name
                if test_name_for_comparison.startswith('DISABLED_'):
                    test_name_for_comparison = test_name_for_comparison[len('DISABLED_'):]
                if tc_name and tc_name != test_name_for_comparison:
                    name_violations.append(f"@tc.name mismatch: '{tc_name}' != test name '{test_name_for_comparison}'")

                if not is_valid or name_violations:
                    violation = {
                        'file': str(filepath),
                        'line': line_num,
                        'test_class': test_class,
                        'test_name': original_test_name,
                        'tc_name': tc_name,
                        'violations': name_violations,
                        'suggestion': TestNameValidator.suggest_fix(original_test_name)
                    }
                    violations.append(violation)

        except Exception as e:
            print(f"Error reading {filepath}: {e}")

        return violations

    def scan_files(self, filepaths: List[Path]) -> Tuple[int, List[Dict]]:
        """Scan multiple files and collect violations."""
        all_violations = []
        total_tests = 0

        for filepath in filepaths:
            violations = self.scan_file(filepath)
            all_violations.extend(violations)

            # Count total tests in file
            try:
                content = filepath.read_text(encoding='utf-8', errors='ignore')
                test_count = len(HWTEST_F_REGEX.findall(content))
                total_tests += test_count
            except:
                pass

        return total_tests, all_violations

def print_violation_report(violations: List[Dict], total_tests: int, show_suggestions: bool = True):
    """Print a formatted violation report."""
    if not violations:
        print("✅ All test names comply with naming convention!")
        print(f"Total tests scanned: {total_tests}")
        return

    print(f"❌ Found {len(violations)} naming violations in {total_tests} total tests")
    print("=" * 80)

    # Group violations by file
    violations_by_file = {}
    for v in violations:
        violations_by_file.setdefault(v['file'], []).append(v)

    for filepath, file_violations in violations_by_file.items():
        print(f"\nFile: {filepath}")
        print("-" * 40)

        for v in file_violations:
            print(f"  Line {v['line']}: {v['test_class']}::{v['test_name']}")
            for violation in v['violations']:
                print(f"    ❌ {violation}")

            if show_suggestions and v['suggestion'] != v['test_name']:
                print(f"    💡 Suggestion: {v['suggestion']}")

            if v['tc_name'] and v['tc_name'] != v['test_name']:
                print(f"    📝 @tc.name tag: {v['tc_name']}")

def print_compliance_report(violations: List[Dict], total_tests: int, total_files: int):
    """Print a comprehensive compliance report."""
    compliant_tests = total_tests - len(violations)
    compliance_percent = (compliant_tests / total_tests * 100) if total_tests > 0 else 100

    print("=" * 80)
    print("C API Test Naming Compliance Report")
    print("=" * 80)
    print(f"Scanned files: {total_files}")
    print(f"Total tests: {total_tests}")
    print(f"Compliant tests: {compliant_tests} ({compliance_percent:.1f}%)")
    print(f"Violations: {len(violations)}")

    if violations:
        print("\nViolation Summary:")
        print("-" * 40)

        # Count violation types
        violation_types = {}
        for v in violations:
            for violation in v['violations']:
                # Extract violation type
                if "No 'Test' in name" in violation:
                    violation_types["Missing 'Test'"] = violation_types.get("Missing 'Test'", 0) + 1
                elif "Multiple 'Test' occurrences" in violation:
                    violation_types["Multiple 'Test'"] = violation_types.get("Multiple 'Test'", 0) + 1
                elif "should start with lowercase" in violation:
                    violation_types["Method name case"] = violation_types.get("Method name case", 0) + 1
                elif "Scenario should start with uppercase" in violation:
                    violation_types["Scenario case"] = violation_types.get("Scenario case", 0) + 1
                elif "@tc.name mismatch" in violation:
                    violation_types["@tc.name mismatch"] = violation_types.get("@tc.name mismatch", 0) + 1
                elif "Name too long" in violation:
                    violation_types["Name too long"] = violation_types.get("Name too long", 0) + 1
                elif "Method name mismatch" in violation:
                    violation_types["Method name mismatch"] = violation_types.get("Method name mismatch", 0) + 1
                elif "  Suggested" in violation:
                    pass
                elif "Test name suggests testing method" in violation:
                    violation_types["No method calls"] = violation_types.get("No method calls", 0) + 1
                elif "Method name appears to include scenario element" in violation:
                    violation_types["Method includes scenario"] = violation_types.get("Method includes scenario", 0) + 1
                else:
                    violation_types["Other"] = violation_types.get("Other", 0) + 1

        for vtype, count in sorted(violation_types.items(), key=lambda x: x[1], reverse=True):
            print(f"  {vtype}: {count}")

    print("\n" + "=" * 80)

def main():
    parser = argparse.ArgumentParser(
        description="Verify C API test naming convention compliance",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument('--verify', action='store_true', default=True,
                       help='Verify all test names (default)')
    parser.add_argument('--report', action='store_true',
                       help='Generate detailed compliance report')
    parser.add_argument('--directory', type=str, nargs='+',
                       help='Scan specific directory(ies)')
    parser.add_argument('--file', type=str, nargs='+',
                       help='Check specific file(s)')
    parser.add_argument('--exclude-generated', action='store_true', default=True,
                       help='Exclude generated test directories')
    parser.add_argument('--include-generated', action='store_false', dest='exclude_generated',
                       help='Include generated test directories')

    args = parser.parse_args()

    # Determine files to scan
    scanner = TestFileScanner(BASE_DIR, args.exclude_generated)

    if args.file:
        filepaths = [Path(f) for f in args.file]
    elif args.directory:
        filepaths = scanner.find_test_files(args.directory)
    else:
        filepaths = scanner.find_test_files()

    if not filepaths:
        print("No test files found to scan!")
        return 1

    print(f"Scanning {len(filepaths)} test files...")

    # Scan files for violations
    total_tests, violations = scanner.scan_files(filepaths)

    # Generate report
    if args.report:
        print_compliance_report(violations, total_tests, len(filepaths))

    # Always print violations
    if violations:
        print_violation_report(violations, total_tests)
        print(f"\n❌ Naming convention violations found!")
        return 1
    else:
        print_violation_report(violations, total_tests)
        print(f"\n✅ All test names comply with naming convention!")
        return 0

if __name__ == "__main__":
    sys.exit(main())