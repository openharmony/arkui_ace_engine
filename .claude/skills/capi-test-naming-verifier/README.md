# C API Test Naming Verifier Skill

This skill verifies that all C API unit test names follow the standardized naming convention `methodNameTestScenario`. It scans all C API test files (excluding generated tests) and validates compliance with the established naming pattern.

## Naming Convention

### Primary Pattern: `methodNameTestScenario`

- **methodName**: Method name being tested, preserving original casing and underscores
  - camelCase methods: `setEnableHapticFeedback`
  - Underscored methods: `set_onChangeEvent_selected` (preserve underscores!)
- **Test**: Literal "Test" with capital T
- **Scenario**: Descriptive scenario in PascalCase (e.g., `InvalidValues`, `DefaultValues`)

### Special Cases

1. **DISABLED tests**: `DISABLED_methodNameTestScenario`
2. **Utility tests**: Simple names with "Test" suffix (e.g., `SimpleTypesTest`, `ArrayTypesTest`)
3. **Conditional compilation**: Tests in `#ifdef` blocks should have differentiated names (e.g., `WithSupport`, `WithoutSupport`)
4. **Methods containing "Test"**: When method name contains "Test" (e.g., `setHitTestBehavior`, `setOnChildTouchTest`), the separator "Test" is still added, resulting in double/triple "Test" - **this is acceptable**:
   - `setHitTestBehaviorTestValidInput` ✅ (double "Test")
   - `setOnChildTouchTestTestValidCallback` ✅ (triple "Test")
5. **Underscored method names**: Methods with underscores must preserve them:
   - `set_onChangeEvent_selectedTestValidCallback` ✅
   - `setOnChangeEventSelectedTestValidCallback` ❌ (don't convert underscores)

### Examples

**Standard camelCase:**
- `setEnableHapticFeedbackTestInvalidValues`
- `setShowTipsTestDefaultValues`
- `getResponseDataTestSuccess`
- `ctorTestDefault`
- `DISABLED_setResponseRegionTestBasic`

**Methods with "Test" in name (double/triple "Test" OK):**
- `setHitTestBehaviorTestValidInput` ✅
- `setOnChildTouchTestTestValidCallback` ✅

**Underscored methods (preserve underscores):**
- `set_onChangeEvent_selectedTestValidCallback` ✅
- `set_onChangeEvent_textTestValidInput` ✅

**Methods with variant types (variant in scenario, not method name):**
- `setStyleTestCapsuleValidBorderRadiusValues` ✅ (method: `setStyle`, scenario: `CapsuleValidBorderRadiusValues`)
- `setStyleTestLinearValidValues` ✅ (method: `setStyle`, scenario: `LinearValidValues`)
- `setStyleCapsuleTestValidBorderRadiusValues` ❌ (incorrectly treats "Capsule" as part of method name)

**Utility tests:**
- `SimpleTypesTest`
- `ArrayConversionTest`

## Usage

### Basic Verification

```bash
claude-code skill capi-test-naming-verifier --verify
```

### Scan Specific Directory

```bash
claude-code skill capi-test-naming-verifier --directory test/unittest/capi/modifiers
```

### Generate Detailed Report

```bash
claude-code skill capi-test-naming-verifier --report
```

### Check Specific File

```bash
claude-code skill capi-test-naming-verifier --file test/unittest/capi/modifiers/common_method_modifier_test2.cpp
```

## Validation Rules

### Rule 1: Method Name Format
- **camelCase methods**: Must start with lowercase (e.g., `setEnableHapticFeedback`, not `SetEnableHapticFeedback`)
- **Underscored methods**: Must preserve underscores exactly as in C API (e.g., `set_onChangeEvent_selected`)
- **CRITICAL**: Never convert underscored method names to camelCase
- Must match actual C API method name (including underscores)

### Rule 2: "Test" Separator
- Must appear between method name and scenario
- Must be capitalized "Test" (not `test` or `TEST`)
- **Multiple "Test" allowed**: When method name contains "Test" (e.g., `setHitTestBehavior`), multiple occurrences are acceptable
  - `setHitTestBehaviorTestValidInput` ✅ (double "Test" OK)
  - `setOnChildTouchTestTestValidCallback` ✅ (triple "Test" OK)

### Rule 3: Scenario Format
- Must be PascalCase (first letter uppercase, e.g., `InvalidValues`, `DefaultValues`)
- Should be descriptive but concise
- Should not repeat method name

### Rule 4: Length Constraints
- Target length: 30-70 characters
- Warning if > 100 characters
- Consider shorter scenario names for very long method names

### Rule 5: Special Prefixes
- DISABLED tests: Must start with `DISABLED_` (uppercase)
- No other prefixes allowed

### Rule 6: Method Call Verification
- Method name in test should match methods called in test body
- Preserving underscores is required for match: `set_onChangeEvent_selected` matches `accessor_->set_onChangeEvent_selected()`
- **Exception**: Tests ending in `DefaultValues` don't require method calls (they verify default state)

## Excluded Directories

- `test/unittest/capi/modifiers/generated/` - Auto-generated tests
- Any other generated test directories

## Implementation

The skill scans C API test directories using the following process:

1. **File Discovery**: Recursively find all `.cpp` test files
2. **Pattern Extraction**: Extract test names from `HWTEST_F` macros
3. **Validation**: Check each test name against naming rules
4. **Reporting**: Generate compliance report with violations

## Integration with Existing Skills

- **capi-test-fixer**: Can be used to fix naming violations
- **tdd**: Provides test writing guidelines
- **openharmony-build**: Build verification after naming fixes

## Common Violations

### Violation 1: Missing "Test" suffix
- `setEnableHapticFeedbackInvalidValues` → `setEnableHapticFeedbackTestInvalidValues`

### Violation 2: Incorrect case
- `SetEnableHapticFeedbackTestInvalidValues` → `setEnableHapticFeedbackTestInvalidValues`
- `setEnableHapticFeedbackTestinvalidvalues` → `setEnableHapticFeedbackTestInvalidValues`

### Violation 3: Duplicate "Test" (When Method Name Doesn't Contain "Test")
- `setEnableHapticFeedbackTestTestInvalidValues` → `setEnableHapticFeedbackTestInvalidValues`
- **Note**: Multiple "Test" is acceptable when method name contains "Test" (e.g., `setHitTestBehaviorTestValidInput`)

### Violation 4: Missing scenario
- `setEnableHapticFeedbackTest` → `setEnableHapticFeedbackTestDefaultValues` (add appropriate scenario)

### Violation 5: Incorrect DISABLED prefix
- `Disabled_setResponseRegionTest` → `DISABLED_setResponseRegionTest`
- `DISABLED_setResponseRegionTest` (correct)

### Violation 6: Variant Type in Method Name
- `setStyleCapsuleTestValidBorderRadiusValues` → `setStyleTestCapsuleValidBorderRadiusValues`
- **Explanation**: The actual method is `setStyle()`. "Capsule" describes the variant/option type being tested (part of scenario), not the method name.
- **Pattern**: When a method accepts union types or multiple option types, the variant descriptor should be in the scenario, not method name.

## Output Examples

### Compliance Report
```
C API Test Naming Verification Report
=====================================
Scanned files: 317
Total tests: 934
Compliant tests: 934 (100%)
Violations: 0
```

### Violation Report
```
Violations found in test/unittest/capi/modifiers/common_method_modifier_test2.cpp:
  Line 123: setResponseRegionTest → Should be setResponseRegionTestDefaultValues
  Line 145: SetEnableHapticFeedbackTestInvalidValues → Should be setEnableHapticFeedbackTestInvalidValues
```

## Best Practices

1. **Run verification after adding new tests**: Ensure new tests follow naming convention
2. **Use during code reviews**: Check naming compliance before merging
3. **Integrate with CI**: Add naming verification to continuous integration pipeline
4. **Regular audits**: Periodically verify existing test names

## Limitations

- Cannot automatically fix naming violations (use capi-test-fixer for fixes)
- Requires manual review for scenario appropriateness
- Does not verify test logic or implementation