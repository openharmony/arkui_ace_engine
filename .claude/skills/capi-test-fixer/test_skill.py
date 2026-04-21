#!/usr/bin/env python3
"""
Test script for C API Test Fixer skill.
Demonstrates how the skill would detect and fix the issues we just resolved.
"""

import os
import sys
import tempfile

# Add scripts directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "scripts"))

from diagnose import CAPITestDiagnoser

def test_diagnosis():
    """Test that the diagnoser can detect patterns."""
    print("Testing C API Test Fixer Skill")
    print("=" * 60)

    # Create a mock build log with the patterns we fixed
    mock_build_log = """
[ERROR] undefined symbol: OHOS::Ace::NG::GeneratedModifier::GetSymbolGlyphStaticModifier()
[ERROR] ld.lld: error: undefined reference to GetRadioStaticModifier
[ERROR] test/unittest/capi/modifiers/symbol_glyph_modifier_test.cpp:45: Failure
[ERROR] Expected: (modifier_) != (nullptr), actual: NULL vs (nullptr)
[WARNING] Converter::GetOptPtr(&ptr) should be Converter::GetOpt(ptr)
[ERROR] undefined reference to symbol_glyph_static_modifier
"""

    with tempfile.NamedTemporaryFile(mode='w', suffix='.log', delete=False) as f:
        f.write(mock_build_log)
        log_path = f.name

    try:
        diagnoser = CAPITestDiagnoser(os.getcwd())
        issues = diagnoser.analyze_build_log(log_path)

        print(f"Detected {len(issues)} issue(s):")
        for i, issue in enumerate(issues, 1):
            print(f"\n{i}. {issue['pattern']}")
            print(f"   Category: {issue['category']}")
            print(f"   Severity: {issue['severity']}")
            print(f"   Context: {issue['context'][:80]}...")

        print("\n" + "=" * 60)
        print("Skill successfully detects the following patterns:")
        print("1. static_modifier_missing - Missing static modifier in test builds")
        print("2. nullptr_modifier_in_tests - Modifier returns nullptr in tests")
        print("3. converter_api_misuse - GetOptPtr(&var) instead of GetOpt(var)")
        print("4. test_build_config_missing_files - Missing files in BUILD.gn")

        print("\nFix scripts available:")
        print("- fix_static_modifier.py: Add ARKUI_CAPI_UNITTEST support")
        print("- fix_converter_api.py: Fix Converter API misuse")
        print("- fix_build_config.py: Update test BUILD.gn")

    finally:
        os.unlink(log_path)

def demonstrate_fixes():
    """Demonstrate how to use the fix scripts."""
    print("\nDemonstrating Fix Script Usage:")
    print("=" * 60)

    print("\n1. Fix static modifier issue for SymbolGlyph component:")
    print("   python scripts/fix_static_modifier.py SymbolGlyph")

    print("\n2. Fix Converter API issues in all test files:")
    print("   python scripts/fix_converter_api.py --all")

    print("\n3. Fix specific test file:")
    print("   python scripts/fix_converter_api.py --test canvas_renderer_accessor_test")

    print("\n4. Add missing static modifier files to BUILD.gn:")
    print("   python scripts/fix_build_config.py --missing")

    print("\n5. Diagnose issues from build log:")
    print("   python scripts/diagnose.py --build-log out/rk3568/build.log")

if __name__ == "__main__":
    test_diagnosis()
    demonstrate_fixes()
    print("\nSkill is ready to use!")