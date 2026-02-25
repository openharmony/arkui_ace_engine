# C API Test Fixer Skill

This skill automatically diagnoses and fixes common C API unit test failures in OpenHarmony ACE Engine. It handles patterns like missing static modifiers in test builds, incorrect Converter API usage, and test build configuration issues.

## Trigger Keywords

Use this skill when:
- "C API test failures", "C API unit test issues"
- "modifier tests failing", "undefined symbol in C API tests"
- "ARKUI_CAPI_UNITTEST compilation errors"
- "Converter API issues in tests"
- "test build configuration problems"
- "fix C API interface test failures"

## Common Failure Patterns

### Pattern 1: Missing Static Modifier in Test Builds
**Symptoms**:
- Linker error: `undefined symbol: OHOS::Ace::NG::GeneratedModifier::Get*StaticModifier()`
- Test failure: `modifier_test_base.h:210: Expected: (modifier_) != (nullptr)`

**Root Cause**: Modifier function uses `DynamicModuleHelper` which returns `nullptr` in tests.

**Fix Pattern**:
1. Add ARKUI_CAPI_UNITTEST conditional compilation to modifier.cpp
2. Include static modifier implementation in test BUILD.gn

### Pattern 2: Incorrect Converter API Usage
**Symptoms**:
- Test failure comparing `nullopt` vs `nullptr`
- Compilation warnings about pointer/reference mismatches

**Root Cause**: Using `Converter::GetOptPtr(&local_var)` instead of `Converter::GetOpt(local_var)`

**Fix Pattern**: Replace `GetOptPtr(&var)` with `GetOpt(var)` for local variables.

### Pattern 3: Test Build Configuration Missing Files
**Symptoms**:
- Build fails with "undefined reference" for static modifier functions
- File not included in test build sources

**Root Cause**: Static modifier .cpp file not listed in test BUILD.gn sources

**Fix Pattern**: Add missing .cpp file to test BUILD.gn sources list.

## Skill Implementation

The skill performs automated diagnosis through:

### 1. Error Analysis
- Parse build logs (`out/rk3568/build.log`)
- Extract linker errors and undefined symbols
- Analyze test failure messages

### 2. Pattern Matching
```python
# Example patterns
PATTERNS = {
    "static_modifier_missing": r"undefined symbol.*Get(\w+)StaticModifier",
    "converter_api_misuse": r"GetOptPtr\(&",
    "nullptr_modifier": r"modifier_test_base\.h.*modifier_.*!=.*nullptr",
}
```

### 3. Fix Generation
Based on detected patterns:
- **Static modifier missing**:
  - Check if modifier.cpp has ARKUI_CAPI_UNITTEST conditional
  - Verify test BUILD.gn includes static_modifier.cpp
  - Generate appropriate patches

- **Converter API misuse**:
  - Locate offending test file
  - Suggest GetOptPtr → GetOpt replacement

- **Build configuration**:
  - Check test BUILD.gn source lists
  - Add missing static modifier files

## Usage Examples

### Diagnose and Fix All Issues
```bash
claude-code skill capi-test-fixer --diagnose
```

### Fix Specific Test Failure
```bash
claude-code skill capi-test-fixer --test SymbolGlyphModifierTest
```

### Analyze Build Log
```bash
claude-code skill capi-test-fixer --build-log out/rk3568/build.log
```

## Integration with Existing Skills

This skill complements:
- **openharmony-build**: Uses build logs for diagnosis
- **build-error-analyzer**: Focuses specifically on C API test patterns
- **tdd**: Provides test-specific fixes

## File Structure

```
.cclaude/skills/capi-test-fixer/
├── README.md                 # This file
├── skill.json               # Skill configuration
├── scripts/
│   ├── diagnose.py          # Main diagnosis script
│   ├── fix_static_modifier.py
│   ├── fix_converter_api.py
│   └── fix_build_config.py
├── templates/
│   ├── static_modifier.patch
│   └── converter_fix.patch
└── patterns/
    └── error_patterns.json
```

## Error Resolution Workflow

1. **Collect Data**: Build logs, test outputs, source files
2. **Pattern Match**: Identify failure category
3. **Root Cause Analysis**: Determine exact issue
4. **Fix Generation**: Create appropriate patches
5. **Validation**: Verify fixes work

## Common Fix Templates

### Static Modifier Fix
```cpp
// Before
const GENERATED_ArkUI*Modifier* Get*Modifier()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("*");
    return reinterpret_cast<const GENERATED_ArkUI*Modifier*>(module->GetStaticModifier());
}

// After
#ifdef ARKUI_CAPI_UNITTEST
const GENERATED_ArkUI*Modifier* Get*StaticModifier();
#endif

const GENERATED_ArkUI*Modifier* Get*Modifier()
{
    static const GENERATED_ArkUI*Modifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GeneratedModifier::Get*StaticModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("*");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const GENERATED_ArkUI*Modifier*>(module->GetStaticModifier());
#endif
    }
    return cachedModifier;
}
```

### Converter API Fix
```cpp
// Before
auto optValue = Converter::GetOptPtr(&ptr);

// After
auto optValue = Converter::GetOpt(ptr);
```

### BUILD.gn Fix
```gn
# Add to test/unittest/capi/BUILD.gn sources
sources += [
    "$ace_root/frameworks/core/components_ng/pattern/*/bridge/*_static_modifier.cpp",
]
```

## Best Practices

1. **Always check existing patterns**: Radio modifier already implements ARKUI_CAPI_UNITTEST pattern
2. **Verify test builds**: Ensure `ARKUI_CAPI_UNITTEST` is defined in test config
3. **Use proper Converter API**: `GetOpt` for values, `GetOptPtr` for pointers
4. **Maintain consistency**: Follow established patterns in codebase

## Limitations

- Cannot fix complex test logic errors
- Requires clear error patterns
- May need manual review for edge cases

## Contributing

Add new patterns to `patterns/error_patterns.json`:
```json
{
  "pattern_name": {
    "regex": "error pattern",
    "category": "static_modifier|converter_api|build_config",
    "fix_template": "template_name",
    "severity": "high|medium|low"
  }
}
```