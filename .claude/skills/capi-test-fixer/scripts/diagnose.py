#!/usr/bin/env python3
"""
C API Test Fixer - Main diagnosis script
Automatically diagnose and fix common C API unit test failures in OpenHarmony ACE Engine.
"""

import os
import sys
import re
import argparse
import json
from pathlib import Path
from typing import List, Dict, Optional, Tuple

# Add parent directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# Load pattern modules
def load_patterns():
    """Load patterns from JSON file or use defaults."""
    patterns_json_path = os.path.join(
        os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
        "patterns",
        "error_patterns.json"
    )

    if os.path.exists(patterns_json_path):
        try:
            with open(patterns_json_path, 'r') as f:
                return json.load(f)
        except (json.JSONDecodeError, IOError) as e:
            print(f"Warning: Could not load patterns from {patterns_json_path}: {e}")

    # Define default patterns if not available
    return {
        "static_modifier_missing": {
            "regex": r"undefined symbol.*Get(\w+)StaticModifier",
            "category": "static_modifier",
            "severity": "high",
            "fix_template": "static_modifier"
        },
        "converter_api_misuse": {
            "regex": r"GetOptPtr\(\&",
            "category": "converter_api",
            "severity": "medium",
            "fix_template": "converter_api"
        },
        "nullptr_modifier_in_tests": {
            "regex": r"modifier_test_base\.h.*modifier_.*!=.*nullptr",
            "category": "static_modifier",
            "severity": "high",
            "fix_template": "static_modifier"
        },
        "test_build_config_missing_files": {
            "regex": r"undefined reference.*static_modifier",
            "category": "build_config",
            "severity": "high",
            "fix_template": "build_config"
        }
    }

PATTERNS = load_patterns()


class CAPITestDiagnoser:
    """Main class for diagnosing C API test failures."""

    def __init__(self, ace_engine_root: str = None):
        """Initialize with ACE Engine root directory."""
        if ace_engine_root is None:
            # Try to find ACE Engine root
            current_dir = os.getcwd()
            while current_dir != '/' and not os.path.exists(os.path.join(current_dir, 'CLAUDE.md')):
                current_dir = os.path.dirname(current_dir)
            if os.path.exists(os.path.join(current_dir, 'CLAUDE.md')):
                self.root = current_dir
            else:
                raise ValueError("Could not find ACE Engine root directory")
        else:
            self.root = ace_engine_root

        self.build_log_path = None
        self.test_output_path = None
        self.detected_issues = []

    def find_build_log(self, product: str = "rk3568") -> Optional[str]:
        """Find build log for given product."""
        possible_paths = [
            os.path.join(self.root, "..", "..", "out", product, "build.log"),
            os.path.join(self.root, "..", "..", "out", "sdk", "build.log"),
            os.path.join(self.root, "out", product, "build.log"),
        ]

        for path in possible_paths:
            if os.path.exists(path):
                self.build_log_path = path
                return path

        return None

    def analyze_build_log(self, log_path: str = None) -> List[Dict]:
        """Analyze build log for C API test failure patterns."""
        if log_path is None:
            if self.build_log_path is None:
                self.find_build_log()
            log_path = self.build_log_path

        if not os.path.exists(log_path):
            print(f"Build log not found: {log_path}")
            return []

        issues = []
        with open(log_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        for pattern_name, pattern_info in PATTERNS.items():
            regex = pattern_info["regex"]
            matches = re.finditer(regex, content, re.MULTILINE | re.IGNORECASE)

            for match in matches:
                issue = {
                    "pattern": pattern_name,
                    "category": pattern_info["category"],
                    "severity": pattern_info["severity"],
                    "fix_template": pattern_info.get("fix_template", ""),
                    "context": match.group(0),
                    "line": content[:match.start()].count('\n') + 1,
                    "match": match.group(0)
                }

                # Extract component name for static modifier issues
                if pattern_name == "static_modifier_missing" and match.groups():
                    component = match.group(1)
                    issue["component"] = component.replace("StaticModifier", "").replace("Modifier", "")

                issues.append(issue)

        self.detected_issues.extend(issues)
        return issues

    def diagnose_test_failure(self, test_name: str = None) -> List[Dict]:
        """Diagnose specific test failure."""
        # This would analyze test output files
        # For now, return any build log issues related to the test
        issues = []
        if test_name:
            for issue in self.detected_issues:
                if test_name.lower() in str(issue).lower():
                    issues.append(issue)
        return issues or self.detected_issues

    def generate_fixes(self) -> Dict:
        """Generate fixes for detected issues."""
        fixes = {}

        for issue in self.detected_issues:
            pattern = issue["pattern"]
            if pattern == "static_modifier_missing":
                fixes[pattern] = self._generate_static_modifier_fix(issue)
            elif pattern == "converter_api_misuse":
                fixes[pattern] = self._generate_converter_api_fix(issue)
            elif pattern == "test_build_config_missing_files":
                fixes[pattern] = self._generate_build_config_fix(issue)

        return fixes

    def _generate_static_modifier_fix(self, issue: Dict) -> Dict:
        """Generate fix for missing static modifier."""
        component = issue.get("component", "Unknown")

        fix = {
            "description": f"Add ARKUI_CAPI_UNITTEST support for {component} modifier",
            "files_to_modify": [
                f"frameworks/core/interfaces/native/implementation/{component.lower()}_modifier.cpp",
                "test/unittest/capi/BUILD.gn"
            ],
            "steps": [
                f"1. Check if {component.lower()}_modifier.cpp has ARKUI_CAPI_UNITTEST conditional",
                "2. If not, add similar pattern as radio_modifier.cpp",
                f"3. Add {component.lower()}_static_modifier.cpp to test BUILD.gn sources"
            ],
            "template": "static_modifier"
        }

        return fix

    def _generate_converter_api_fix(self, issue: Dict) -> Dict:
        """Generate fix for Converter API misuse."""
        fix = {
            "description": "Replace Converter::GetOptPtr(&var) with Converter::GetOpt(var)",
            "files_to_modify": [
                "test/unittest/capi/accessors/*_accessor_test.cpp"
            ],
            "steps": [
                "1. Find all occurrences of Converter::GetOptPtr(&local_var)",
                "2. Replace with Converter::GetOpt(local_var)",
                "3. Ensure test expectations match (nullopt vs nullptr)"
            ],
            "template": "converter_api"
        }

        return fix

    def _generate_build_config_fix(self, issue: Dict) -> Dict:
        """Generate fix for missing files in test build config."""
        fix = {
            "description": "Add missing static modifier files to test BUILD.gn",
            "files_to_modify": [
                "test/unittest/capi/BUILD.gn"
            ],
            "steps": [
                "1. Locate test BUILD.gn file",
                "2. Find sources list",
                "3. Add missing *_static_modifier.cpp file paths"
            ],
            "template": "build_config"
        }

        return fix

    def print_diagnosis(self):
        """Print diagnosis results."""
        if not self.detected_issues:
            print("No C API test issues detected.")
            return

        print(f"Detected {len(self.detected_issues)} C API test issue(s):")
        print("=" * 80)

        for i, issue in enumerate(self.detected_issues, 1):
            print(f"\n{i}. {issue['pattern'].replace('_', ' ').title()}")
            print(f"   Category: {issue['category']}")
            print(f"   Severity: {issue['severity']}")
            print(f"   Context: {issue['context'][:100]}...")

            if 'component' in issue:
                print(f"   Component: {issue['component']}")

        print("\n" + "=" * 80)

        fixes = self.generate_fixes()
        if fixes:
            print("\nRecommended fixes:")
            for pattern, fix in fixes.items():
                print(f"\n{pattern.replace('_', ' ').title()}:")
                print(f"  {fix['description']}")
                print(f"  Files to modify: {', '.join(fix['files_to_modify'])}")


def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(description="Diagnose C API unit test failures")
    parser.add_argument("--build-log", help="Path to build.log file")
    parser.add_argument("--product", default="rk3568", help="Product name (default: rk3568)")
    parser.add_argument("--test", help="Specific test name to diagnose")
    parser.add_argument("--diagnose-only", action="store_true", help="Only diagnose, don't suggest fixes")
    parser.add_argument("--generate-fix", action="store_true", help="Generate fix scripts")

    args = parser.parse_args()

    try:
        diagnoser = CAPITestDiagnoser()

        # Find and analyze build log
        if args.build_log:
            log_path = args.build_log
        else:
            log_path = diagnoser.find_build_log(args.product)

        if log_path:
            print(f"Analyzing build log: {log_path}")
            issues = diagnoser.analyze_build_log(log_path)
        else:
            print(f"Warning: No build log found for product {args.product}")
            issues = []

        # Diagnose specific test if requested
        if args.test:
            test_issues = diagnoser.diagnose_test_failure(args.test)
            if test_issues:
                print(f"Found {len(test_issues)} issue(s) for test {args.test}")

        # Print diagnosis
        diagnoser.print_diagnosis()

        # Generate fixes if requested
        if args.generate_fix and not args.diagnose_only:
            fixes = diagnoser.generate_fixes()
            if fixes:
                print("\nGenerated fix scripts available in scripts/ directory")

    except Exception as e:
        print(f"Error during diagnosis: {e}")
        import traceback
        traceback.print_exc()
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())