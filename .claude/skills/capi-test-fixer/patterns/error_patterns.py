"""Error patterns for C API test failures."""

import os
import json

# Load patterns from JSON file
_patterns_json_path = os.path.join(os.path.dirname(__file__), "error_patterns.json")

if os.path.exists(_patterns_json_path):
    with open(_patterns_json_path, 'r') as f:
        PATTERNS = json.load(f)
else:
    # Fallback patterns
    PATTERNS = {
        "static_modifier_missing": {
            "regex": r"undefined symbol.*Get(\w+)StaticModifier",
            "category": "static_modifier",
            "fix_template": "static_modifier",
            "severity": "high"
        },
        "converter_api_misuse": {
            "regex": r"GetOptPtr\(\&",
            "category": "converter_api",
            "fix_template": "converter_api",
            "severity": "medium"
        },
        "nullptr_modifier_in_tests": {
            "regex": r"modifier_test_base\.h.*modifier_.*!=.*nullptr",
            "category": "static_modifier",
            "fix_template": "static_modifier",
            "severity": "high"
        },
        "test_build_config_missing_files": {
            "regex": r"undefined reference.*static_modifier",
            "category": "build_config",
            "fix_template": "build_config",
            "severity": "high"
        }
    }