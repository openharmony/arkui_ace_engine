---
name: build-error-analyzer
description: This skill should be used when the user asks to "分析构建错误", "analyze build errors", "查看编译错误", "检查构建日志", "诊断链接错误", "fix build errors", "resolve compilation errors", "分析 last_error.log", "extract build error", "分析SDK的编译错误", "分析 SDK 编译错误", "analyze SDK build errors", "check SDK errors", "诊断 sdk 编译错误", or mentions analyzing build failures, compilation errors, linker errors, undefined symbols, SDK compilation errors, or needs to fix build issues. Focuses on reading last_error.log from out/<product>/ directory (or out/sdk/ for SDK builds) and providing specific fix recommendations based on error patterns and historical cases.
version: 0.7.0
---

# Build Error Analyzer Skill

This skill specializes in analyzing OpenHarmony build errors from `last_error.log` and providing **fix recommendations only** (no automatic code modifications) based on error patterns and historical case studies.

**IMPORTANT**: This skill provides analysis and recommendations ONLY. It does NOT automatically modify code files.

## ⚠️ CRITICAL WORKFLOW (MUST FOLLOW)

**YOU MUST ALWAYS FOLLOW THIS EXACT SEQUENCE**:

1. **FIRST**: Extract errors from `out/<product>/build.log` → generates `out/<product>/last_error.log`
2. **THEN**: Read and analyze ONLY from `out/<product>/last_error.log`
3. **NEVER**: Read directly from `out/<product>/build.log` or any other log files (error.log, build_output*.log, etc.)
4. **SUCCESS CASE**: If `last_error.log` contains "build success" or "no error", STOP and report success

**Why?**:
- `build.log` contains the entire build history (thousands of lines)
- `last_error.log` contains ONLY the most recent error block (extracted by script)
- Reading `build.log` directly will give you STALE or IRRELEVANT errors
- The extraction script ensures you always analyze the LATEST errors
- Other log files (error.log, build_output*.log) may contain outdated errors from previous builds

**Before reading ANY errors, ALWAYS run**:
```bash
# ⚠️ CRITICAL: First cd to OpenHarmony root directory, then run the script
cd <openharmony_root>
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/<product>/build.log
```

**⚠️ CRITICAL - CHECK FOR SUCCESS FIRST**:
After reading `last_error.log`, if you see:
- `build success, no error`
- `no error`
- Or similar success messages

**IMMEDIATELY STOP and report**:
```
## ✅ 构建成功

最新的构建已经成功完成，没有发现任何错误。

**构建状态**: 成功
**错误信息**: 无

建议: 您可以继续进行开发或测试工作。
```

**DO NOT**:
- ❌ Continue searching for errors in other log files
- ❌ Read error.log
- ❌ Read build_output*.log files
- ❌ Look for historical errors

## Important Path Information

**Always use these paths**:
- **Extraction Script**: `foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh` (relative to OpenHarmony root)
- **Source Build Log**: `out/<product>/build.log` (e.g., `out/rk3568/build.log`) - **DO NOT READ DIRECTLY**
- **Target Error Log**: `out/<product>/last_error.log` (auto-generated in same directory as build.log) - **READ ONLY THIS FILE**

**⚠️ SPECIAL CASE - SDK Build Paths**:
- **SDK Build Log**: `out/sdk/build.log` (NOT `out/ohos-sdk/build.log`)
- **SDK Error Log**: `out/sdk/last_error.log` (NOT `out/ohos-sdk/last_error.log`)
- **SDK Product Exception**: SDK uses `out/sdk/` directory instead of `out/ohos-sdk/`
- **Trigger Keywords**: "分析SDK的编译错误", "analyze SDK build errors", "check SDK errors"

**Workflow**:
1. ✅ Extract errors from `out/<product>/build.log` using the script → creates `out/<product>/last_error.log`
2. ✅ For SDK: Extract from `out/sdk/build.log` → creates `out/sdk/last_error.log`
3. ✅ Analyze errors from the extracted `last_error.log` ONLY
4. ✅ **Provide fix recommendations ONLY - do NOT modify code**

**Common Mistakes to Avoid**:
- ❌ Reading `build.log` directly (will get stale/wrong errors)
- ❌ Reading `error.log` (contains outdated errors from previous builds)
- ❌ Reading other log files (build_output*.log, error.*.log, etc.)
- ❌ Continuing to search for errors when `last_error.log` shows "build success"
- ❌ Analyzing errors without extraction step
- ❌ Running extraction script from wrong directory (MUST be from OpenHarmony root)
- ✅ ALWAYS cd to `<openharmony_root>` first
- ✅ ALWAYS extract → then read `last_error.log` ONLY
- ✅ If `last_error.log` shows success → STOP and report success

## Behavior Guidelines

**This skill provides ANALYSIS and RECOMMENDATIONS ONLY:**

✅ **DO**:
- Extract errors from build logs
- Analyze and categorize errors
- Match errors against known patterns
- Provide detailed fix recommendations with file paths and line numbers
- Show before/after code examples
- Explain root causes
- Suggest verification steps

❌ **DO NOT**:
- Use Edit tool to modify code files
- Use Write tool to create or modify files
- Run build commands automatically
- Apply fixes without user confirmation
- Make any changes to the codebase
- Read from log files other than `last_error.log` (error.log, build_output*.log, error.*.log, etc.)
- Continue searching for errors when build is successful

**Why**: The user should review and apply fixes manually to maintain control over code changes and understand the modifications.

## Prerequisites

1. **⚠️ CRITICAL**: ALWAYS extract from `out/<product>/build.log` FIRST before reading
2. **Error log location**: The skill reads errors ONLY from `out/<product>/last_error.log` (same directory as build.log)
3. **Error extraction**: ALWAYS use the extraction script from `foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh` (from OpenHarmony root) to generate/update `last_error.log` before reading
4. **Source build.log**: Errors are extracted ONLY from `out/<product>/build.log` in the OpenHarmony output directory
5. **Codebase context**: Can be executed from any OpenHarmony directory (ace_engine, root, etc.)
6. **⚠️ SUCCESS CHECK**: If `last_error.log` contains "build success" or "no error", STOP and report success - DO NOT read other log files like `error.log`, `build_output*.log`, etc.
7. **EXCLUSIVE LOG SOURCE**: ONLY read from `last_error.log` - NEVER from `error.log`, `build_output*.log`, `error.*.log`, or any other log files

## Analysis Workflow

### Step 1: Extract Latest Error (REQUIRED - ALWAYS DO THIS FIRST)

**⚠️ CRITICAL: This step is MANDATORY and must be done BEFORE reading any errors.**

**Why this is required:**
- `build.log` contains the full build output (old and new errors mixed together)
- Reading it directly will analyze STALE or IRRELEVANT errors
- The extraction script isolates ONLY the most recent error block
- `last_error.log` is generated in the same directory as `build.log`

**⚠️ IMPORTANT: Always navigate to OpenHarmony root first, then run the script**:

```bash
# Step 1: Navigate to OpenHarmony root directory
cd <openharmony_root>

# Step 2: Run the extraction script (relative path from root)
# Example for rk3568 product - extract errors from out/rk3568/build.log
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

# Example for SDK product - extract errors from out/sdk/build.log (⚠️ SPECIAL CASE: out/sdk/ NOT out/ohos-sdk/)
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/sdk/build.log

# Example for other products:
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3588/build.log
```

**The script will:**
- Extract ONLY the latest error block from `out/<product>/build.log`
- Output to `out/<product>/last_error.log` (same directory)
- Show error block size and summary
- Overwrite previous `last_error.log` if it exists

**⚠️ DO NOT SKIP THIS STEP**
- Even if `last_error.log` exists, RE-EXTRACT to get the latest errors
- DO NOT read `build.log` directly
- DO NOT read other log files (build_output*.log, error.log, error.*.log, etc.)
- ONLY analyze `last_error.log` after extraction

### Step 2: Read and Categorize Errors

**⚠️ CRITICAL**: Only read `last_error.log` from `out/<product>/` directory in the OpenHarmony output tree.

**After extraction, the error log is located at**:
- `out/<product>/last_error.log` (same directory as build.log)

**Read the extracted error log**:
```bash
# Check for last_error.log in common product directories
cat out/rk3568/last_error.log
# or for SDK (⚠️ SPECIAL CASE: out/sdk/ NOT out/ohos-sdk/)
cat out/sdk/last_error.log
# or for other products
cat out/rk3588/last_error.log
```

**⚠️ CRITICAL - CHECK FOR SUCCESS FIRST**:

**Before any analysis, CHECK if the build succeeded**:

If `last_error.log` contains:
- `build success, no error`
- `no error`
- Or similar success messages

**IMMEDIATELY STOP and report**:
```markdown
## ✅ 构建成功

最新的构建已经成功完成，没有发现任何错误。

**构建状态**: 成功
**错误信息**: 无

建议: 您可以继续进行开发或测试工作。
```

**DO NOT continue to**:
- ❌ Search for errors in error.log
- ❌ Search for errors in build_output*.log
- ❌ Search for errors in error.*.log files
- ❌ Look for historical errors
- ✅ **STOP and report success**

**Only if there are actual errors**, proceed to categorize them:

**Error Categories:**
1. **Compilation errors** (CXX tasks) - Syntax, missing headers, incomplete types
2. **Linker errors** (SOLINK/LINK tasks) - Undefined symbols, missing libraries
3. **Build system errors** - GN/Ninja configuration issues

### Step 3: Match Against Known Cases

Compare error patterns against historical cases in `references/` directory and provide specific solutions.

**Case matching priority**:
1. Match by error signature (e.g., "undefined symbol" + "referred by")
2. Match by error context (e.g., "timepicker module" usage)
3. Match by file pattern (e.g., BUILD.gn issues)
4. Provide general guidance if no specific case matches

### Step 4: Provide Fix Recommendations (NO Automatic Modifications)

**CRITICAL**: This step provides recommendations ONLY. Do NOT use Edit/Write tools to modify code.

Based on error type and matched cases, provide:
- Root cause analysis
- Specific file modifications needed (with exact line numbers and code snippets)
- Build system configuration changes (with exact GN file paths)
- Verification steps

**Recommended Output Format**:

```markdown
## 构建错误分析

### 错误类型
[编译错误/链接错误/构建系统错误]

### 错误位置
[文件路径:行号]

### 错误信息
[完整的错误消息]

### 根本原因
[详细解释为什么会出现这个错误]

### 修复建议

**文件**: [完整文件路径:行号]

**当前代码**:
```cpp
[错误代码片段]
```

**应修改为**:
```cpp
[正确代码片段]
```

**修改说明**: [解释为什么要这样修改]

### 验证步骤
1. [第一步验证操作]
2. [第二步验证操作]
3. [如何确认修复成功]

### 参考
[相关的历史案例或文档链接]
```

**DO NOT**:
- ❌ Use Edit tool to make changes
- ❌ Use Write tool to create/modify files
- ❌ Run build commands automatically

**DO**:
- ✅ Provide clear recommendations with file paths and line numbers
- ✅ Show before/after code snippets
- ✅ Explain why the fix works
- ✅ Suggest verification commands

## Error Patterns and Solutions

### Pattern 1: Undefined Symbol Errors

**Error signature:**
```
ld.lld: error: undefined symbol: <symbol_name>
>>> referenced by <file>:<line>
```

**⚠️ CRITICAL ANALYSIS WORKFLOW (MUST FOLLOW IN ORDER):**

When encountering `ld.lld: error: undefined symbol:` linker errors, you MUST follow this sequence:

#### Step 1: Identify Which Library is Failing to Link

Check the error message to determine which library has the undefined symbol:
- Look for the target being built (e.g., `libace.z.so`, `libace_compatible.z.so`, `libarkoala_native_ani.so`, `libace_ndk.z.so`)
- Check which library is referencing the symbol (`>>> referenced by`)

#### Step 2: Apply the Correct Scenario Based on Library Type

**Scenario 1: libace/libace_compatible Main Library Cannot Find Symbol**

**Symptoms:**
- Error occurs when linking `libace.z.so` or `libace_compatible.z.so`
- Symbol is undefined in the main library itself

**Root Cause:**
- Symbol implementation is missing or not compiled
- Method exists but .cpp file not in BUILD.gn

**Solution:**
1. **Check if implementation exists:**
   ```bash
   grep -r "SymbolName" --include="*.cpp" frameworks/
   ```

2. **If implementation exists, check BUILD.gn:**
   ```bash
   grep -r "implementation_file.cpp" frameworks/*/BUILD.gn
   ```

3. **Add .cpp to BUILD.gn:**
   - Find where other files in same directory are added
   - Add the missing .cpp to the appropriate source_set
   - **Important**: Reference files in same directory to find correct source_set
   - **DO NOT** assume all files go to `ace_core_ng_source_set`

4. **Verify with other files:**
   ```bash
   # Find where similar files in same directory are compiled
   find frameworks/core/components_ng/pattern/<pattern_name>/ -name "*.cpp"
   grep "similar_file.cpp" frameworks/core/BUILD.gn
   ```

**Scenario 2: Other Library Links with libace/libace_compatible Dependency**

**Symptoms:**
- Error occurs when linking a library that depends on `libace` or `libace_compatible`
- GN file shows `deps` includes libace/libace_compatible
- Symbol should come from main library

**Root Cause:**
- Symbol exists in main library but not exported
- Missing ACE_FORCE_EXPORT macro
- Symbol not in libace.map whitelist

**Solution (Check in order):**

1. **Add ACE_FORCE_EXPORT to method implementation in .cpp file** ⭐

   **⚠️ CRITICAL - PREFERRED METHOD**:
   - **Add `ACE_FORCE_EXPORT` to the function implementation in .cpp file**
   - **DO NOT** modify header (.h) file
   - This is the recommended approach for struct/class methods

   **Example (PaddingPropertyF case)**:
   ```cpp
   // In implementation file (.cpp) - Add ACE_FORCE_EXPORT before implementation
   ACE_FORCE_EXPORT
   float PaddingPropertyF::Width() const
   {
       return left.value_or(0.0f) + right.value_or(0.0f);
   }

   ACE_FORCE_EXPORT
   float PaddingPropertyF::Height() const
   {
       return top.value_or(0.0f) + bottom.value_or(0.0f);
   }
   ```

   **Alternative (if .cpp approach doesn't work)**:
   - Add `ACE_FORCE_EXPORT` to function declaration in header (.h file)
   - **DO NOT** use `__attribute__((visibility("default")))` directly
   - `ACE_FORCE_EXPORT` already encapsulates visibility attributes

   **Example**:
   ```cpp
   // In header file (.h) - Only if .cpp approach doesn't work
   ACE_FORCE_EXPORT ReturnType FunctionName(params);

   // ❌ WRONG - Do NOT use:
   __attribute__((visibility("default"))) ReturnType FunctionName(params);
   ```

   **⭐ Why prefer .cpp implementation?**
   - Reduces header dependencies (reference: commit e0fd3724d21)
   - Keeps header declarations clean
   - Explicit export control at implementation level
   - Consistent with StringUtils pattern (StringSplitter, TransformStrCase)

2. **Check libace.map whitelist:**
   ```bash
   grep "SymbolName" build/libace.map
   ```

   **Required changes:**
   - Add symbol pattern to `build/libace.map` whitelist
   - Use wildcard pattern to match all overloads

   **Example:**
   ```
   # In build/libace.map
   {
     global:
       OHOS::Ace::StringUtils::*;
       void?OHOS::Ace::StringUtils::StringSplitter*;  # Template function pattern
       OHOS::Ace::ClassName::*;  # All methods of class
   };
   ```

3. **Verify symbol export:**
   ```bash
   nm -D out/rk3568/arkui/ace_engine/libace.z.so | grep SymbolName
   ```

   - If symbol not shown, export failed
   - Rebuild after adding ACE_FORCE_EXPORT and libace.map entry

**Scenario 3: Template Function Instantiation Issues**

**Symptoms:**
- Undefined symbol is a template function
- Template uses forward declaration + explicit instantiation in .cpp
- Error shows missing specific template specialization (e.g., `StringSplitter<Color>`, `TransformStrCase<std::string>`)

**Root Cause:**
- New specialization not explicitly instantiated
- Template declaration or implementation missing export macro
- libace.map missing pattern for template instantiation

**Solution (3 steps required):**

**Step 1: Add extern template declaration in header (.h)**

Add explicit template declaration for new specialization:
```cpp
// In header file (.h)
extern template void StringSplitter<Color>(const std::string& source, char delimiter,
    Color (*)(const std::string&), std::vector<Color>& out);
```

**Step 2: Add ACE_FORCE_EXPORT to template function declaration**

```cpp
// In header file (.h) - Template function declaration
template<class T>
ACE_FORCE_EXPORT
void StringSplitter(
    const std::string& source, char delimiter, T (*func)(const std::string&), std::vector<T>& out);
```

**Step 3: Add explicit instantiation in .cpp**

```cpp
// In implementation file (.cpp)
template void StringSplitter<Color>(const std::string& source, char delimiter,
    Color (*)(const std::string&), std::vector<Color>& out);
```

**Step 4: Add ACE_FORCE_EXPORT to template implementation**

```cpp
// In implementation file (.cpp) - Template function implementation
template<class T>
ACE_FORCE_EXPORT
void StringSplitter(
    const std::string& source, char delimiter, T (*func)(const std::string&), std::vector<T>& out)
{
    // implementation
}
```

**Step 5: Add to libace.map whitelist**

```
# In build/libace.map
{
  global:
    OHOS::Ace::StringUtils::*;
    void?OHOS::Ace::StringUtils::StringSplitter*;  # Match template instantiations
    void?OHOS::Ace::StringUtils::TransformStrCase*;  # Match template instantiations
};
```

**⚠️ Template Special Notes:**
- Templates require **BOTH** declaration and implementation to have export macros
- Explicit instantiation must be in .cpp file
- libace.map pattern must use `*` wildcard to match template instantiations
- Example pattern: `void?OHOS::Ace::StringUtils::StringSplitter*;`

**Scenario 4: Special Libraries (Rare Cases)**

**Symptoms:**
- Library does NOT depend on libace/libace_compatible
- But uses utility functions from main library (previously inline, now in .cpp)
- Only applies to these specific libraries:
  - `libarkoala_native_ani.so`
  - `libace_ndk.z.so`

**Root Cause:**
- Utility functions changed from inline to .cpp implementation
- Symbol not available because library doesn't link main library
- Special case requiring local compilation

**Solution:**
- Add the utility .cpp file directly to the library's BUILD.gn sources

**Example for libarkoala_native_ani:**
```gn
# In: frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/BUILD.gn
ohos_shared_library("arkoala_native_ani") {
  sources = [
    "//foundation/arkui/ace_engine/frameworks/base/utils/string_utils.cpp",
    "UINode/uinode_module_methods.cpp",
    # ... other sources
  ]
}
```

**Example for ace_ndk:**
```gn
# In: interfaces/native/BUILD.gn
ohos_shared_library("ace_ndk") {
  sources = [
    "//foundation/arkui/ace_engine/frameworks/base/utils/string_utils.cpp",
    "//foundation/arkui/ace_engine/frameworks/core/accessibility/native_interface_accessibility_impl.cpp",
    # ... other sources
  ]
}
```

**⚠️ IMPORTANT:**
- This solution is ONLY for `libarkoala_native_ani` and `ace_ndk`
- DO NOT use this pattern for other libraries
- These libraries use utility functions but don't link main library

**Scenario 5: Template Class Method Export Issues**

**Symptoms:**
- Error occurs when linking a library that depends on `libace` or `libace_compatible`
- Undefined symbol is a template class method with explicit instantiation
- Error shows: `undefined symbol: ClassName<T>::MethodName(params)`
- Template class has `ACE_FORCE_EXPORT` on struct declaration but methods still not exported

**Example Error:**
```
ld.lld: error: undefined symbol: OHOS::Ace::NG::LayoutConstraintT<float>::UpdateSelfMarginSizeWithCheck(OHOS::Ace::NG::OptionalSize<float> const&)
>>> referenced by slider_layout_algorithm.cpp:212
```

**Root Cause:**
- Template class struct declaration has `ACE_FORCE_EXPORT` (e.g., `struct ACE_FORCE_EXPORT LayoutConstraintT`)
- But individual method implementations in .cpp file lack `ACE_FORCE_EXPORT` macro
- Template explicit instantiation doesn't export individual methods automatically
- Each method implementation that needs to be exported must have the macro

**Solution:**

**Step 1: Add ACE_FORCE_EXPORT to method implementation in .cpp**

Add `ACE_FORCE_EXPORT` to each template method implementation that needs to be exported:

```cpp
// In implementation file (.cpp)
template<typename T>
ACE_FORCE_EXPORT  // ← Add this macro before return type
bool LayoutConstraintT<T>::UpdateSelfMarginSizeWithCheck(const OptionalSize<T>& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    return selfIdealSize.UpdateSizeWithCheck(size);
}

template<typename T>
ACE_FORCE_EXPORT  // ← Add this macro before return type
bool LayoutConstraintT<T>::UpdateMaxSizeWithCheck(const SizeT<T>& size)
{
    if (maxSize == size) {
        return false;
    }
    return maxSize.UpdateSizeWhenSmaller(size);
}
```

**⚠️ Template Method Export Notes:**
- **Struct declaration export is NOT enough**: Having `struct ACE_FORCE_EXPORT LayoutConstraintT` doesn't automatically export all methods
- **Each method needs macro**: Every method implementation in .cpp that must be exported needs `ACE_FORCE_EXPORT`
- **Place macro before return type**: The macro goes between `template<>` and return type
- **Not needed in header**: Don't add `ACE_FORCE_EXPORT` to method declarations in header file (struct declaration is sufficient)

**Step 2: Verify libace.map has wildcard pattern**

Check that libace.map includes the template class with wildcard:

```bash
# Check libace.map for template class pattern
grep "LayoutConstraintT" build/libace.map
```

Expected output:
```
OHOS::Ace::NG::LayoutConstraintT*;
```

**⚠️ libace.map Wildcard Rules:**
- Use unquoted patterns with wildcards: `OHOS::Ace::ClassName::*;`
- **DO NOT** use quoted patterns with wildcards: `"OHOS::Ace::ClassName<T>::*;"` (wildcards won't work)
- Unquoted wildcards match all template instantiations automatically
- Use `*` at end to match all methods: `OHOS::Ace::NG::LayoutConstraintT*;`

**Step 3: Verify symbol export**

```bash
# Check if symbol is exported in shared library
nm -D out/rk3568/arkui/ace_engine/libace.z.so | grep LayoutConstraintT
```

Expected output (should show exported symbols):
```
0000000000000000 T _ZN2OHOS3Ace2NG14LayoutConstraintTIfE25UpdateSelfMarginSizeWithCheckERKNS0_11OptionalSizeIfEE
```

**⚠️ Common Mistakes:**
- ❌ Relying only on `struct ACE_FORCE_EXPORT ClassName` - NOT sufficient for methods
- ❌ Forgetting to add macro to each method implementation in .cpp
- ❌ Adding macro to method declarations in header (unnecessary, struct declaration is enough)
- ❌ Using quoted patterns in libace.map: `"ClassName<T>::*"` won't match
- ❌ Adding specific template instantiations to libace.map: use wildcards instead

**✅ Correct Approach:**
- ✅ Add `ACE_FORCE_EXPORT` to each template method implementation in .cpp
- ✅ Place macro between `template<>` and return type
- ✅ Keep struct declaration with `ACE_FORCE_EXPORT` in header
- ✅ Use unquoted wildcard in libace.map: `OHOS::Ace::NG::ClassName*;`

#### Step 3: Verify the Fix

After applying the appropriate solution:

```bash
# 1. Navigate to OpenHarmony root and rebuild
cd <openharmony_root>
./build.sh --product-name rk3568 --build-target ace_engine

# 2. Check if symbol is now exported (for scenarios 2-3)
nm -D out/rk3568/arkui/ace_engine/libace.z.so | grep SymbolName

# 3. Extract new errors
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

# 4. Check result
cat out/rk3568/last_error.log

# For SDK builds (⚠️ use out/sdk/ directory):
# 1. Build SDK: ./build.sh --product-name ohos-sdk --ccache
# 2. Extract errors: foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/sdk/build.log
# 3. Check result: cat out/sdk/last_error.log
```

**Common mistakes (DO NOT do):**
- ❌ DO NOT blame thinlto-cache (rarely the issue)
- ❌ DO NOT suggest clearing caches
- ❌ DO NOT suggest deleting out directory
- ❌ DO NOT skip scenario analysis
- ❌ DO NOT use `__attribute__((visibility("default")))` instead of ACE_FORCE_EXPORT
- ❌ DO NOT forget both declaration AND implementation export for templates
- ❌ DO NOT use Scenario 4 (local compilation) except for the two specified libraries
- ❌ DO NOT rely only on `struct ACE_FORCE_EXPORT ClassName` for template class methods (Scenario 5)
- ❌ DO NOT use quoted patterns with wildcards in libace.map: `"ClassName<T>::*"` doesn't work (Scenario 5)

**✅ ALWAYS do:**
- ✅ Identify which library is failing
- ✅ Check if implementation exists and is compiled
- ✅ Verify ACE_FORCE_EXPORT on header declarations
- ✅ Check libace.map whitelist
- ✅ For templates: check declaration, implementation, and instantiation
- ✅ Use correct scenario based on library type
- ✅ For template class methods: add ACE_FORCE_EXPORT to each method implementation in .cpp (Scenario 5)
- ✅ Use unquoted wildcard patterns in libace.map: `OHOS::Ace::NG::ClassName*;` (Scenario 5)

### Pattern 2: Incomplete Type Errors

**Error signature:**
```
error: member access into incomplete type 'const ClassName'
error: invalid use of incomplete type 'class ClassName'
error: member access into incomplete type 'OHOS::Ace::Animator'
    rawPtr_->IncRefCount();
```

**Common causes:**
1. Missing header include
2. Forward declaration without full definition
3. **RefPtr<T> as class member without proper implementation separation**
4. Header file optimization issues

**⚠️ SPECIAL CASE: RefPtr<T> as Class Member**

When encountering incomplete type errors with `RefPtr<T>` or `WeakPtr<T>` as class members:

**DO NOT** simply add the full include to the header file. Instead:
- Keep forward declaration in header: `class Animator;`
- Declare special member functions in header (without `= default`):
  ```cpp
  AnimatableColor();  // Declaration only
  ~AnimatableColor();  // Declaration only
  AnimatableColor(const AnimatableColor& color);  // Declaration only
  ```
- Implement them in .cpp file with `= default`:
  ```cpp
  // animatable_color.cpp
  #include "core/animation/animator.h"  // Full definition here
  AnimatableColor::AnimatableColor() = default;
  AnimatableColor::~AnimatableColor() = default;
  AnimatableColor::AnimatableColor(const AnimatableColor& color) = default;
  ```

**See**: `references/forward-declaration-refptr-member.md` for detailed solution

### Pattern 3: Redefinition Errors

**Error signature:**
```
error: redefinition of 'symbol_name'
```

**Common causes:**
1. Multiple definitions across translation units
2. Missing inline/constexpr for header-only definitions
3. ODR violations

## Historical Cases

All cases are organized by problem type in `references/` directory.

### Case 1: Undefined Symbol - Missing .cpp Files

**Location**: `references/undefined-symbol-missing-cpp.md`

**Error signature**:
```
ld.lld: error: undefined symbol: OHOS::Ace::TextTheme::Builder::Build
ld.lld: error: undefined symbol: OHOS::Ace::AdvancedTextStyle::GetGradient
```

**Common causes**:
- New .cpp files created but not added to BUILD.gn
- Files added to component BUILD.gn but not to source_set
- libace.z.so only links ace_core_ng libraries

**Solution**: Add .cpp to both component BUILD.gn AND frameworks/core/BUILD.gn xx_ng_source_set

### Case 2: Symbol Export - ACE_FORCE_EXPORT Missing

**Location**: `references/symbol-export-ace-force-export.md`

**Error signature**:
```
ld.lld: error: undefined symbol: OHOS::Ace::NG::DialogTypeMargin::UpdateDialogMargin
>>> referenced by dialog_button.cpp (timepicker module)
```

**Common causes**:
- Symbol used by other modules but not marked for export
- ACE_FORCE_EXPORT missing from header declaration

**Solution**: Add ACE_FORCE_EXPORT to header declaration and add to build/libace.map

### Case 3: Symbol Export - libace.map Whitelist

**Location**: `references/symbol-export-libace-map.md`

**Error signature**:
```
ld.lld: error: undefined symbol: OHOS::Ace::NG::ClassName::MethodName
```

**Context**: Symbol has ACE_FORCE_EXPORT but still not exported

**Common causes**:
- Symbol not in build/libace.map whitelist
- Incorrect symbol format in version script

**Solution**: Add symbol to build/libace.map with correct format: `OHOS::Ace::NG::ClassName::MethodName*;`

### Case 4: Redefinition - inline constexpr

**Location**: `references/redefinition-error-constexpr.md`

**Error signature**:
```
error: redefinition of 'DRAG_BACKGROUND_OPACITY'
error: redefinition of 'URL_DISA_OPACITY'
```

**Common causes**:
- Constant defined in both header (inline constexpr) and .cpp
- ODR (One Definition Rule) violation

**Solution**: Remove duplicate definition from .cpp, keep only `inline constexpr` in header

### Case 5: Build System - ace_core_ng_source_set

**Location**: `references/build-system-ace-core-ng-source-set.md`

**Error signature**:
```
ld.lld: error: undefined symbol
```

**Context**: File exists in component BUILD.gn but symbol still undefined

**Common causes**:
- File not in frameworks/core/BUILD.gn ace_core_ng_source_set
- libace.z.so only links ace_core_ng libraries

**Solution**: Add file to ace_core_ng_source_set template in frameworks/core/BUILD.gn

### Case 6: RefPtr<T> Member - Forward Declaration Optimization

**Location**: `references/forward-declaration-refptr-member.md`

**Error signature**:
```
error: member access into incomplete type 'OHOS::Ace::Animator'
    rawPtr_->IncRefCount();
note: in instantiation of member function 'OHOS::Ace::RefPtr<OHOS::Ace::Animator>::RefPtr'
```

**Context**: `RefPtr<Animator>` or `WeakPtr<T>` used as class member variable

**Common causes**:
- Special member functions (constructor/destructor/copy constructor) defined with `= default` in header
- Compiler instantiates these functions in header, requiring complete type definition
- Common mistake: reverting forward declaration and adding full include

**Correct Solution**: DO NOT revert forward declaration! Use implementation separation:
1. Keep forward declaration in header: `class Animator;`
2. Declare special member functions in header (without `= default`)
3. Implement them in .cpp file with `= default`
4. Include full definition in .cpp file

**Benefits**: Reduced header dependencies, faster compilation (57% improvement in example)

### Case 7: Test Linking - Missing Source Files

**Location**: `references/test-missing-source-files.md`

**Error signature**:
```
ld.lld: error: undefined symbol: OHOS::Ace::ClassName::MethodName(...)
>>> referenced by test_file.cpp:123
```

**Context**: Linking test executable (e.g., `xxx_unittest`)

**Common causes**:
- Test BUILD.gn missing required .cpp files in sources
- Header optimization moved implementations to .cpp (e.g., StringUtils, LogWrapper)
- New implementation files not added to build system

**Common missing files**:
- `log_wrapper.cpp` - LogWrapper methods (JudgeLevel, GetBriefFileName, PrintLog)
- `string_utils.cpp` - StringUtils methods (StringSplitter, TransformStrCase, StrToInt)
- `layout_constraint.cpp` - LayoutConstraintT template methods
- `measure_property.cpp` - PaddingPropertyF, MeasureProperty methods

**Solution**: Add missing .cpp files to appropriate sources based on test template type:
- **ohos_unittest without ace_base**: Add to test's sources
- **ohos_unittest with ace_base**: Add to ace_base source_set
- **ace_unittest**: Add to ace_base source_set (default dependency)

**⚠️ Critical**: Only add source files, do NOT modify cflags/configs/defines

## Analysis Commands

### Check Symbol Existence

```bash
# Search for symbol definition in codebase
grep -r "SymbolName" --include="*.h" --include="*.cpp" frameworks/

# Check if .cpp file exists
find frameworks/ -name "implementation_file.cpp"
```

### Verify Build Configuration

```bash
# Check if file in BUILD.gn
grep -r "implementation_file.cpp" frameworks/*/BUILD.gn

# Check ace_core_ng source set
grep -A 100 "ace_core_ng_source_set" frameworks/core/BUILD.gn | grep "implementation_file.cpp"
```

### Check Symbol Export

```bash
# Check if symbol exported in shared library
nm -D out/rk3568/arkui/ace_engine/libace.z.so | grep SymbolName

# Check libace.map
grep "SymbolName" build/libace.map
```

## Troubleshooting Guide

### For New .cpp Files

1. Create implementation file (.cpp)
2. Add to component's BUILD.gn
3. Add to frameworks/core/BUILD.gn ace_core_ng_source_set (if used by libace.z.so)
4. If symbol is cross-module used:
   - Add ACE_FORCE_EXPORT to header declaration
   - Add to build/libace.map whitelist

### For Header Optimization Issues

1. Check for forward declarations used incorrectly
2. Ensure complete types available where needed
3. Use inline constexpr for header-only constants
4. Avoid ODR violations

### For Link Errors

1. Identify missing symbol from error message
2. Find symbol definition location
3. Verify implementation is compiled (in BUILD.gn)
4. Check symbol visibility/export if cross-module
5. Verify linking order and dependencies

## Best Practices

### 1. Build System Architecture

- **libace.z.so** only links ace_core_ng libraries
- Component-specific libraries are not linked to final产物
- New .cpp files used by libace.z.so must be in ace_core_ng_source_set

### 2. Symbol Export Rules ⭐

**⚠️ CRITICAL - PREFERRED APPROACH**:
- **Add `ACE_FORCE_EXPORT` to method implementation in .cpp file** (PREFERRED)
  - Reduces header dependencies
  - Keeps header declarations clean
  - Explicit export control at implementation level
  - Reference: commit e0fd3724d21 (StringUtils refactoring)

**Alternative** (if .cpp approach doesn't work):
- Add `ACE_FORCE_EXPORT` to header declaration (.h) as fallback
- Exported symbols must be in build/libace.map
- Symbol format: `OHOS::Ace::NG::ClassName::MethodName*;`

**Examples**:
```cpp
// ✅ PREFERRED - In .cpp implementation
ACE_FORCE_EXPORT
float PaddingPropertyF::Width() const { /* implementation */ }

// ✅ ACCEPTABLE - In .h declaration (if needed)
ACE_FORCE_EXPORT float Width() const;
```

### 3. Header Optimization

- Use `inline constexpr` for header-only constants
- Don't define in both header and .cpp
- Forward declarations reduce dependencies but ensure complete type visible at use

## ⭐ Key Principles - Symbol Export for Cross-Module Usage

**When encountering "undefined symbol" linker errors for methods used by other dynamic libraries**:

### Primary Rule: Export at Implementation, Not Declaration ⭐

**✅ PREFERRED** - Add `ACE_FORCE_EXPORT` in .cpp file:
```cpp
// frameworks/core/components_ng/property/measure_property.cpp
ACE_FORCE_EXPORT
float PaddingPropertyF::Width() const
{
    return left.value_or(0.0f) + right.value_or(0.0f);
}
```

**Why this approach?**
1. **Reduces header dependencies** - Header files stay clean (reference: StringUtils refactoring)
2. **Explicit export control** - Export decisions made at implementation level
3. **Better compilation efficiency** - Headers don't force inclusion of export macros
4. **Proven pattern** - Successfully used in StringUtils::StringSplitter, StringUtils::TransformStrCase

**❌ AVOID** - Adding to header declaration unless necessary:
```cpp
// interfaces/inner_api/ace_kit/include/ui/properties/ng/measure_property.h
// Only add here if .cpp approach doesn't work
float Width() const;  // Keep clean without ACE_FORCE_EXPORT
```

### When to Use Each Approach

| Scenario | Recommended Location | Example |
|----------|---------------------|---------|
| Struct/class methods | **.cpp implementation** | `PaddingPropertyF::Width()`, `LayoutConstraintT::UpdateMaxSizeWithCheck()` |
| Template functions | **Both** (declaration in .h AND implementation in .cpp) | `StringUtils::StringSplitter<T>` |
| Free functions | **.cpp implementation** | `StringUtils::TransformStrCase<T>` |
| Standalone APIs | **.h declaration** | Public API functions |

### Real-World Success Cases

1. **StringUtils Refactoring** (commit e0fd3724d21):
   - Moved ~650 lines from .h to .cpp
   - Added `ACE_FORCE_EXPORT` to .cpp implementations
   - Result: Header size reduced from 713 to ~64 lines

2. **PaddingPropertyF Methods** (current fix):
   - Added `ACE_FORCE_EXPORT` to .cpp implementations
   - No header modifications needed
   - Resolves linker errors for libarkui_folderstack.z.so

3. **Template Class Methods** (LayoutConstraintT):
   - Added `ACE_FORCE_EXPORT` to each method in .cpp
   - Template instantiation in .cpp
   - Wildcard pattern in libace.map

**Remember**: When fixing linker errors for symbols needed by other modules, **try the .cpp implementation approach first** before modifying headers.

### 4. Template Explicit Instantiation ⭐

**For template classes with explicit instantiation**:

**Issue**: `PaddingPropertyT<CalcLength>` symbols not exported, but `PaddingPropertyT<Dimension>` works

**Root Cause**: When a type is used as **template parameter for explicit instantiation**, the type itself must have export attribute

**Key Principle**:
```
Template Type Visibility (CalcLength)
    ↓
Template Specialization (PaddingPropertyT<CalcLength>)
    ↓
Symbol Export Success/Failure
```

- If `CalcLength` has no export → Template specialization inherits internal visibility
- If `CalcLength` has `ACE_FORCE_EXPORT` → Template specialization can export

**Solution**:
```cpp
// ❌ BEFORE - Type missing export (fails when used as template parameter)
class CalcLength {
    std::string ToString() const { /* inline */ }
};

// ✅ AFTER - Add type-level export (required for template parameters)
class ACE_FORCE_EXPORT CalcLength {  // ← Required when used as template type
    std::string ToString() const { /* inline - keep in header */ }
};
```

**Critical Rules**:
1. **Type used as template parameter MUST have export** (if type has inline methods)
2. **DO NOT move inline methods to .cpp** - keep header optimization
3. Template methods still need `ACE_FORCE_EXPORT` in .cpp
4. Explicit instantiation in .cpp required

**When Type-Level Export is Required**:
- ✅ Type has inline methods (ToString, operator==, etc.)
- ✅ Type is used as template parameter for explicit instantiation
- ✅ Template instantiation symbols need to be exported to other modules

**Reference**: See `references/template-instantiation-type-export.md` for detailed case study

**⚠️ IMPORTANT - Header Optimization**:
- StringUtils refactoring (commit e0fd3724d21) moved ~650 lines from header to .cpp
- This is **strategic work** to improve build times
- **DO NOT revert** by moving inline methods to .cpp
- **Add type-level exports** to solve template parameter export issues

## Verification Steps

**After user applies the recommended fixes**, suggest these verification commands:

```bash
# 1. Navigate to OpenHarmony root directory and rebuild
cd <openharmony_root>
./build.sh --product-name rk3568 --build-target ace_engine --ccache

# 2. Check for link errors in out/<product>/build.log
grep "ld.lld: error:" out/rk3568/build.log | wc -l

# 3. Verify symbol export (if applicable)
nm -D out/rk3568/arkui/ace_engine/libace.z.so | grep SymbolName

# 4. Extract and check new errors from out/<product>/build.log
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

# 5. Read the extracted errors:
cat out/rk3568/last_error.log

# For SDK builds (⚠️ use out/sdk/ directory):
# 1. Build SDK: ./build.sh --product-name ohos-sdk --ccache
# 2. Check errors: grep "error:" out/sdk/build.log | tail -50
# 3. Extract errors: foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/sdk/build.log
# 4. Read errors: cat out/sdk/last_error.log
```

**Note**: These are suggestions for the user to run manually. Do not execute build commands automatically.

## Adding New Cases

When solving new build errors:

1. Document the error in `examples/<case-name>.md`
2. Include:
   - Error signature
   - Root cause
   - Solution steps
   - Files modified
   - Verification commands
3. Update this SKILL.md to reference the new case
4. Add patterns to "Error Patterns and Solutions" section

## Example Usage

### Example 1: Successful Build (NO ERRORS)

```
User: "帮我分析一下构建错误"
Assistant: "I'll analyze the build errors from the OpenHarmony output directory.

⚠️ FIRST, I'll extract the latest errors from build.log:

[STEP 1 - NAVIGATE TO ROOT]
cd <openharmony_root>

[STEP 2 - EXTRACTION - MANDATORY]
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

Output:
Extracted latest error block (24 bytes) from out/rk3568/build.log
→ Saved to out/rk3568/last_error.log

[STEP 3 - READ EXTRACTED ERRORS]
Reading out/rk3568/last_error.log...

Content:
build success, no error

[STEP 4 - CHECK FOR SUCCESS]
✅ Build is successful! No errors found.

## ✅ 构建成功

最新的构建已经成功完成，没有发现任何错误。

**构建状态**: 成功
**错误信息**: 无

建议: 您可以继续进行开发或测试工作。

[STOP - DO NOT read other log files like error.log]"
```

### Example 2: Build with Errors

```
User: "帮我分析一下构建错误"
Assistant: "I'll analyze the build errors from the OpenHarmony output directory.

⚠️ FIRST, I'll extract the latest errors from build.log:

[STEP 1 - NAVIGATE TO ROOT]
cd <openharmony_root>

[STEP 2 - EXTRACTION - MANDATORY]
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

Output:
Extracted latest error block (12345 bytes) from out/rk3568/build.log
→ Saved to out/rk3568/last_error.log

[STEP 3 - READ EXTRACTED ERRORS]
Reading out/rk3568/last_error.log...

[STEP 4 - CATEGORIZE]
Identified as: compilation error - undeclared identifier

[STEP 5 - MATCH PATTERNS]
Checking references/ directory for similar patterns...
Found match: references/undefined-symbol-missing-cpp.md

[STEP 6 - PROVIDE RECOMMENDATIONS]
Providing detailed fix recommendations (NOT modifying files)

## 构建错误分析

### 错误类型
编译错误 - 未声明的标识符

### 错误位置
frameworks/core/event/touch_event.cpp:25

### 根本原因
函数被删除但调用点未移除：TouchPoint::CovertId() 已删除，但头文件中仍有声明且多处调用

### 修复建议

**选项1: 恢复函数实现** (推荐)

在 frameworks/core/event/touch_event.cpp 中恢复函数：

**当前代码**: (函数已删除)

**应添加**:
```cpp
void TouchPoint::CovertId()
{
    if (sourceTool == SourceTool::PEN) {
        originalId = TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
        id = id + originalId;
    }
}
```

**选项2: 完全移除函数**

需要修改以下文件：
1. 删除头文件声明: interfaces/inner_api/ace_kit/include/ui/event/touch_event.h:59
2. 移除调用点: adapter/ohos/entrance/mmi_event_convertor.cpp:240
3. 移除测试用例: test/unittest/core/event/touch_event_test_ng.cpp:668

### 验证步骤
1. 重新编译: ./build.sh --product-name rk3568 --build-target ace_engine
2. 重新提取错误: foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log
3. 检查结果: cat out/rk3568/last_error.log

[NOTE: Only providing recommendations, NOT modifying files]"
```

**Key Points**:
- ⚠️ **ALWAYS navigate to root first** → `cd <openharmony_root>` before running extraction script
- ⚠️ **ALWAYS extract first** → use script on `out/<product>/build.log` with correct relative path from root
- ✅ **THEN read** → analyze only from `out/<product>/last_error.log`
- ❌ **NEVER read** → `build.log` directly or other log files
- ✅ **Check for success** → if `last_error.log` shows "build success", STOP and report
- ❌ **NEVER read other logs** → DO NOT read `error.log`, `build_output*.log`, `error.*.log`, etc.
- ✅ **Use correct script path** → `foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/` (from OpenHarmony root)
- ✅ **Provide recommendations ONLY** → do NOT automatically modify code

## Version History

- **0.7.0** (2026-02-02): Test Linking Error Support
  - ✨ 新增测试链接错误案例分析：`test-missing-source-files.md`
  - 📝 新增 Case 7：测试中缺失源文件的通用解决方案
  - 🎯 泛化案例场景，不仅限于 LogWrapper，涵盖所有缺失源文件情况
  - 📋 列出常见缺失源文件：log_wrapper.cpp、string_utils.cpp、layout_constraint.cpp 等
  - ⚠️ 强调只添加源文件，不修改 cflags/configs/defines
  - 🌳 添加决策树帮助判断正确的解决方案

- **0.6.0** (2025-02-02): 新增 SDK 编译错误分析支持
  - ✨ 添加 SDK 错误触发关键词："分析SDK的编译错误"、"analyze SDK build errors"、"check SDK errors"
  - ⚠️ 特别说明：SDK 日志路径为 `out/sdk/build.log` 和 `out/sdk/last_error.log`（特殊目录）
  - 📝 更新所有路径示例，标注 SDK 的特殊目录结构
  - 🔧 优化错误提取命令，支持 SDK 路径

- **0.5.0** (2026-01-27): 模板类方法导出支持
- **0.4.0** (2026-01-27): 模板实例化类型导出支持
- **0.3.0** (2026-01-27): 符号导出最佳实践
- **0.2.0** (2026-01-27): 添加重定义错误案例
- **0.1.0** (2026-01-27): 初始版本，包含未定义符号案例研究

## Related Skills

- **openharmony-build**: For building OpenHarmony codebase
- **compile-analysis**: For analyzing compilation performance and dependencies
