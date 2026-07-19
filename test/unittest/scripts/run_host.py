#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2025 Huawei Device Co., Ltd.
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
Host unit-test runner for ace_engine.

Discovers test binaries under out/host/host_product/tests/unittest/ace_engine,
supports listing all test cases and running them with parallel execution.

Usage examples:
    # List all discovered tests
    python3 run_host.py --list

    # List tests matching a keyword
    python3 run_host.py --list --filter text

    # Run all tests (64 parallel processes by default)
    python3 run_host.py

    # Run a specific test by binary name
    python3 run_host.py -t text_test_ng

    # Run multiple specific tests
    python3 run_host.py -t text_test_ng image_test_ng

    # Run tests under a category directory
    python3 run_host.py -p TextSet-Text

    # Run with gtest filter
    python3 run_host.py -t text_test_ng --gtest_filter "TextPattern*"

    # Export results to a specific file
    python3 run_host.py -o /tmp/result.json
"""

import os
import sys
import time
import json
import stat
import types
import fnmatch
import argparse
import subprocess
import multiprocessing
import xml.etree.ElementTree as ET
from datetime import datetime

# Default host UT output path relative to OpenHarmony root
HOST_UT_REL_PATH = "out/host/host_product/tests/unittest/ace_engine"


def get_ohos_root():
    """Resolve the OpenHarmony source root (6 levels up from this script)."""
    base_path = os.path.dirname(os.path.realpath(__file__))
    for _ in range(6):
        base_path = os.path.dirname(base_path)
    return base_path


def get_host_tests_path():
    """Return the absolute path to the host UT output directory."""
    return os.path.join(get_ohos_root(), HOST_UT_REL_PATH)


class TestCase:
    """Represents a single host test binary (or an expected-but-missing one)."""

    def __init__(self, category, name, binary_path=None, source_path=None):
        self.category = category      # e.g. "TextSet-Text"
        self.name = name              # e.g. "text_test_ng"
        self.binary_path = binary_path  # absolute path or None if not compiled
        self.source_path = source_path  # GN source path from *_path.txt

    @property
    def compiled(self):
        return self.binary_path is not None and os.path.isfile(self.binary_path)

    def __repr__(self):
        status = "compiled" if self.compiled else "NOT compiled"
        return f"<TestCase {self.category}/{self.name} [{status}]>"


def collect_tests(tests_path):
    """
    Walk the host UT directory and collect all test cases.

    Each subdirectory (category) may contain:
      - executable test binaries
      - *_path.txt files indicating expected tests and their GN source paths

    Returns a list of TestCase objects.
    """
    if not os.path.isdir(tests_path):
        print(f"Error: test directory not found: {tests_path}")
        print("Please build host UT first:")
        print("  ./build.sh --product-name host --build-target unittest")
        sys.exit(1)

    tests = []
    seen = set()

    for category in sorted(os.listdir(tests_path)):
        category_dir = os.path.join(tests_path, category)
        if not os.path.isdir(category_dir):
            continue

        # Collect executables in this category
        executables = {}
        path_txt_files = {}

        for fname in os.listdir(category_dir):
            fpath = os.path.join(category_dir, fname)

            if fname.endswith("_path.txt"):
                # e.g. "text_test_ng_path.txt" -> test name "text_test_ng"
                test_name = fname[:-len("_path.txt")]
                source_path = None
                try:
                    with open(fpath, 'r', encoding='utf-8') as f:
                        source_path = f.read().strip()
                except (OSError, UnicodeDecodeError):
                    pass
                path_txt_files[test_name] = source_path
            elif fname.endswith(".xml"):
                # Skip result xml files
                continue
            else:
                # Check if it's an executable
                if os.path.isfile(fpath) and os.access(fpath, os.X_OK):
                    executables[fname] = fpath

        # Merge: executables always win; path.txt may add missing entries
        all_names = set(executables.keys()) | set(path_txt_files.keys())

        for name in sorted(all_names):
            key = (category, name)
            if key in seen:
                continue
            seen.add(key)
            tests.append(TestCase(
                category=category,
                name=name,
                binary_path=executables.get(name),
                source_path=path_txt_files.get(name),
            ))

    return tests


def filter_tests(tests, pattern):
    """Filter tests by a case-insensitive keyword or glob pattern on category/name."""
    if not pattern:
        return tests
    pat = pattern.lower()
    result = []
    for t in tests:
        full = f"{t.category}/{t.name}".lower()
        if pat in full or fnmatch.fnmatch(full, f"*{pat}*"):
            result.append(t)
    return result


def print_test_list(tests):
    """Pretty-print the test list in a table format."""
    if not tests:
        print("No tests found.")
        return

    compiled = [t for t in tests if t.compiled]
    missing = [t for t in tests if not t.compiled]

    # Column widths
    cat_width = max(len(t.category) for t in tests)
    name_width = max(len(t.name) for t in tests)

    header = f"  {'CATEGORY':<{cat_width}}  {'TEST NAME':<{name_width}}  STATUS    SOURCE"
    print(header)
    print("  " + "-" * (len(header) - 2))

    for t in compiled:
        src = t.source_path or ""
        print(f"  {t.category:<{cat_width}}  {t.name:<{name_width}}  \033[32mOK\033[0m        {src}")

    for t in missing:
        src = t.source_path or ""
        print(f"  {t.category:<{cat_width}}  {t.name:<{name_width}}  \033[31mMISSING\033[0m   {src}")

    print()
    print(f"  Total: {len(tests)}  |  Compiled: {len(compiled)}  |  Missing: {len(missing)}")


def build_target_name(xml_file_path):
    """Extract the test binary name from an xml result path."""
    last_slash = xml_file_path.rfind('/')
    last_dot = xml_file_path.rfind('.')
    if last_slash != -1 and last_dot != -1 and last_slash < last_dot:
        return xml_file_path[last_slash + 1:last_dot]
    return "unknown"


def parse_xml(xml_file_path):
    """Parse a gtest XML result file and return (common_info, failed_info, passed_info)."""
    test_module_name = build_target_name(xml_file_path)
    tree = ET.parse(xml_file_path)
    root = tree.getroot()
    tests = root.attrib.get("tests", "0")
    failures = root.attrib.get("failures", "0")
    disabled = root.attrib.get("disabled", "0")

    common_info = types.SimpleNamespace()
    common_info.total = int(tests)
    common_info.disabled = int(disabled)

    failed_info = {
        "test_module_name": test_module_name,
        "total_count": tests,
        "failed_count": failures,
        "failed_testcase_name": []
    }
    passed_info = {
        "test_module_name": test_module_name,
        "total_count": tests,
        "passed_count": 0,
        "passed_testcase_name": []
    }

    passed_count = 0
    for testsuite in root.findall(".//testsuite"):
        testsuite_name = testsuite.attrib.get("name")
        for testcase in testsuite.findall(".//testcase"):
            testcase_status = testcase.attrib.get("status")
            testcase_result = testcase.attrib.get("result")
            if testcase_status != "run" or testcase_result != "completed":
                continue
            testcase_name = testcase.attrib.get("name")
            failure = testcase.find("failure")
            if failure is not None:
                failed_info["failed_testcase_name"].append(
                    f"{testsuite_name}#{testcase_name}")
            else:
                passed_info["passed_testcase_name"].append(
                    f"{testsuite_name}#{testcase_name}")
                passed_count += 1

    passed_info["passed_count"] = str(passed_count)
    return common_info, failed_info, passed_info


def run_command(args_tuple):
    """
    Run a single gtest binary.

    args_tuple: (binary_path, extra_args_list)
    """
    binary_path, extra_args = args_tuple
    cmds = [
        binary_path,
        f"--gtest_output=xml:{binary_path}.xml",
        "--gtest_print_time=0",
        "--gtest_brief=1",
    ]
    if extra_args:
        cmds.extend(extra_args)
    try:
        subprocess.run(cmds, timeout=120, stderr=subprocess.DEVNULL)
    except subprocess.TimeoutExpired:
        print(f"  TIMEOUT: {os.path.basename(binary_path)}")
    except Exception:
        pass


def run_tests(tests, process_count, output_path, gtest_filter=None):
    """
    Run the given compiled tests in parallel and produce a JSON result report.

    Returns the number of failures + crashes.
    """
    compiled = [t for t in tests if t.compiled]
    if not compiled:
        print("No compiled test binaries to run.")
        return 0

    print(f"Running {len(compiled)} test binaries with {process_count} parallel processes...")
    print()

    # Build run args
    extra_args = []
    if gtest_filter:
        extra_args.append(f"--gtest_filter={gtest_filter}")

    run_args = [(t.binary_path, extra_args) for t in compiled]

    # Clean old xml results
    for t in compiled:
        xml_path = f"{t.binary_path}.xml"
        if os.path.exists(xml_path):
            os.remove(xml_path)

    start = time.time()
    with multiprocessing.Pool(processes=process_count) as pool:
        pool.map(run_command, run_args)
    end = time.time()

    # Collect results
    test_result = {
        "time_stamp": str(datetime.now()),
        "execute_time": 0,
        "total_execute_tests": 0,
        "failed_tests_count": 0,
        "disabled_tests_count": 0,
        "passed_tests_count": 0,
        "crashed_tests_count": 0,
        "unavailable": [],
        "failed": [],
        "passed": []
    }

    total_count = 0
    failed_count = 0
    passed_count = 0
    disabled_count = 0

    for t in compiled:
        xml_path = f"{t.binary_path}.xml"
        if os.path.exists(xml_path):
            try:
                common_info, failed_info, passed_info = parse_xml(xml_path)
                total_count += common_info.total
                disabled_count += common_info.disabled
                this_failed = int(failed_info.get('failed_count', '0'))
                this_passed = int(passed_info.get('passed_count', '0'))
                failed_count += this_failed
                passed_count += this_passed
                if this_failed:
                    test_result['failed'].append(failed_info)
                test_result['passed'].append(passed_info)
            except ET.ParseError:
                test_result["unavailable"].append(t.name)
        else:
            test_result["unavailable"].append(t.name)

    test_result["execute_time"] = f"{round(end - start, 2)} seconds"
    test_result["total_execute_tests"] = total_count
    test_result["failed_tests_count"] = failed_count
    test_result["passed_tests_count"] = passed_count
    test_result["disabled_tests_count"] = disabled_count
    test_result["crashed_tests_count"] = len(test_result["unavailable"])

    # Write JSON report
    tests_path = get_host_tests_path()
    json_path = output_path if output_path else os.path.join(tests_path, "test_result.json")
    flags = os.O_CREAT | os.O_WRONLY | os.O_TRUNC
    mode = stat.S_IRUSR | stat.S_IWUSR
    with os.fdopen(os.open(json_path, flags, mode), 'w') as f:
        json.dump(test_result, f, indent=2)

    # Print summary
    crashed = len(test_result["unavailable"])
    print("=" * 60)
    print(f"  Execution time : {test_result['execute_time']}")
    print(f"  Total tests    : {total_count}")
    print(f"  Passed         : \033[32m{passed_count}\033[0m")
    if failed_count:
        print(f"  Failed         : \033[31m{failed_count}\033[0m")
    else:
        print(f"  Failed         : {failed_count}")
    print(f"  Disabled       : {disabled_count}")
    if crashed:
        print(f"  Crashed/NoXml  : \033[31m{crashed}\033[0m")
    else:
        print(f"  Crashed/NoXml  : {crashed}")
    print(f"  Report         : {os.path.abspath(json_path)}")
    print("=" * 60)

    if test_result["failed"]:
        print()
        print("Failed tests:")
        for fi in test_result["failed"]:
            module = fi["test_module_name"]
            for tc in fi["failed_testcase_name"]:
                print(f"  \033[31mFAIL\033[0m  {module} :: {tc}")

    if test_result["unavailable"]:
        print()
        print("Crashed / no XML output:")
        for name in test_result["unavailable"]:
            print(f"  \033[31mCRASH\033[0m {name}")

    return failed_count + crashed


def main():
    parser = argparse.ArgumentParser(
        description="Host unit-test runner for ace_engine",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""Examples:
  %(prog)s --list                         List all discovered tests
  %(prog)s --list --filter text           List tests matching 'text'
  %(prog)s                                Run all compiled tests
  %(prog)s -t text_test_ng                Run a specific test
  %(prog)s -t text_test_ng image_test_ng  Run multiple tests
  %(prog)s -p TextSet-Text                Run tests under a category
  %(prog)s --gtest_filter "TextPattern*"  Run with gtest filter
""")

    parser.add_argument(
        "--list", action="store_true",
        help="List all discovered test cases instead of running them")
    parser.add_argument(
        "--filter", type=str, default=None,
        help="Filter tests by keyword or glob pattern (used with --list or to select which tests to run)")
    parser.add_argument(
        "-t", "--target", nargs='+', type=str, default=None,
        help="Specific test binary name(s) to run")
    parser.add_argument(
        "-p", "--path", type=str, default=None,
        help="Only run tests under this category subdirectory")
    parser.add_argument(
        "-j", "--process", type=int, default=64,
        help="Number of parallel processes (default: 64)")
    parser.add_argument(
        "-o", "--output", type=str, default=None,
        help="Custom output path for the JSON result report")
    parser.add_argument(
        "--gtest_filter", type=str, default=None,
        help="Pass gtest_filter to all test binaries")
    parser.add_argument(
        "--tests-dir", type=str, default=None,
        help="Override the host UT output directory path")

    args = parser.parse_args()

    tests_path = args.tests_dir if args.tests_dir else get_host_tests_path()

    # Collect all tests
    all_tests = collect_tests(tests_path)

    # Apply filters
    tests = all_tests
    if args.path:
        tests = [t for t in tests if t.category == args.path]
        if not tests:
            print(f"No tests found under category: {args.path}")
            return 1
    if args.target:
        target_set = set(args.target)
        tests = [t for t in tests if t.name in target_set]
        if not tests:
            print(f"No tests matching targets: {args.target}")
            return 1
    if args.filter:
        tests = filter_tests(tests, args.filter)
        if not tests:
            print(f"No tests matching filter: {args.filter}")
            return 1

    # List mode
    if args.list:
        print_test_list(tests)
        return 0

    # Run mode
    return run_tests(tests, args.process, args.output, args.gtest_filter)


if __name__ == "__main__":
    sys.exit(main())
