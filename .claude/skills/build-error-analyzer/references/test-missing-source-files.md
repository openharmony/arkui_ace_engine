# 问题：测试链接错误 - 缺失源文件

## 错误特征

```
ld.lld: error: undefined symbol: OHOS::Ace::ClassName::MethodName(...)
>>> referenced by test_file.cpp:123

ld.lld: error: undefined symbol: OHOS::Ace::SomeSymbol
>>> referenced by another_test.cpp:456
```

**关键特征**：
- 错误发生在测试可执行文件链接阶段（如 `xxx_unittest`）
- 未定义的符号来自新增或重构的源文件
- 符号的实现存在于某个 .cpp 文件中，但未被编译进测试

## 常见场景

### 场景 1：头文件优化后提取实现到 .cpp

**示例**：StringUtils、LogWrapper 等工具类的内联函数被移到 .cpp 文件

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::StringUtils::StringSplitter<Color>
>>> referenced by color_property.cpp:50
```

**原因**：`string_utils.cpp` 新增了模板显式实例化，但测试 BUILD.gn 中未包含该文件

### 场景 2：新增辅助类实现文件

**示例**：新增了 layout_constraint.cpp、measure_property.cpp 等

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::NG::LayoutConstraintT<float>::UpdateMaxSizeWithCheck
>>> referenced by slider_layout_algorithm.cpp:212
```

**原因**：新增的 .cpp 实现文件未添加到测试的 BUILD.gn

### 场景 3：日志系统条件编译

**示例**：LogWrapper 方法在非 USE_HILOG 配置下需要完整实现

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::LogWrapper::JudgeLevel(OHOS::Ace::LogLevel)
>>> referenced by system_properties.cpp:362
```

**原因**：`log_wrapper.cpp` 未包含在测试的 sources 中

## 根本原因

测试用例的 BUILD.gn 配置中缺少必要的源文件。常见情况：

1. **头文件优化**：将内联函数从 .h 移到 .cpp，但测试未包含新的 .cpp
2. **新增文件**：创建了新的实现文件，但未添加到构建系统
3. **条件编译**：某些功能在特定配置下需要额外源文件

## 诊断步骤

### 1. 确认错误发生在测试链接阶段

```bash
# 检查错误日志中的链接任务
# 例如：
# [144/183] LINK tests/unittest/ace_engine/ace_engine/adapter/system_properties_unittest
```

### 2. 识别缺失的符号及其源文件

**方法 1：通过符号名推断源文件**

```bash
# LogWrapper 相关 → log_wrapper.cpp
# StringUtils 相关 → string_utils.cpp
# LayoutConstraintT 相关 → layout_constraint.cpp
# MeasureProperty 相关 → measure_property.cpp
```

**方法 2：搜索符号定义**

```bash
# 在 frameworks/ 目录下搜索符号定义
grep -r "ClassName::MethodName" --include="*.cpp" frameworks/

# 示例：搜索 LogWrapper::JudgeLevel
grep -r "LogWrapper::JudgeLevel" --include="*.cpp" frameworks/
```

**方法 3：根据头文件推断**

```bash
# 如果符号来自某个头文件，对应的 .cpp 通常在同目录
# 例如：
# frameworks/base/log/log_wrapper.h → frameworks/base/log/log_wrapper.cpp
# frameworks/base/utils/string_utils.h → frameworks/base/utils/string_utils.cpp
```

### 3. 确认源文件存在

```bash
# 检查推断的源文件是否存在
ls -la frameworks/base/log/log_wrapper.cpp
ls -la frameworks/base/utils/string_utils.cpp
```

### 4. 检查测试的 BUILD.gn 配置

```bash
# 查看失败的测试对应的 BUILD.gn
cat test/unittest/adapter/ohos/osal/system_properties/BUILD.gn
```

检查要点：
- sources 列表是否包含目标源文件？
- 是否依赖了 `ace_base` source_set？
- 使用的测试模板类型（`ohos_unittest` 或 `ace_unittest`）

## 解决方案

### 核心原则

**根据测试模板类型和依赖关系，在适当的位置添加缺失的源文件到 sources 列表。**

### ⚠️ 重要说明

- ❌ **不要**修改 cflags
- ❌ **不要**修改 configs
- ❌ **不要**添加 defines 宏定义
- ✅ **只需要**添加缺失的 `.cpp` 文件到 sources 列表

### 三种场景的解决方案

#### 场景 1：ohos_unittest 且不依赖 ace_base

**特征**：
- 使用 `ohos_unittest` 模板
- `deps` 中没有 `ace_base` 或类似的基础库依赖

**解决方案**：直接在测试的 sources 中添加

**示例 1**：`test/unittest/adapter/ohos/osal/system_properties/BUILD.gn`

```gn
ohos_unittest("system_properties_unittest") {
  module_out_path = adapter_test_output_path
  sources = [
    "$ace_root/adapter/ohos/osal/system_properties.cpp",
    "$ace_root/frameworks/base/log/log_wrapper.cpp",       # ← 添加缺失的源文件
    "$ace_root/frameworks/base/utils/string_utils.cpp",    # ← 添加缺失的源文件
    "system_properties_test.cpp",
    "mock_window_utils.cpp",
  ]

  configs = [
    "$ace_root/test/unittest:ace_unittest_config",
    ":system_properties_test_config",
  ]

  deps = [
    # 没有 ace_base 依赖
  ]
}
```

**示例 2**：`test/unittest/adapter/ohos/capability/feature_config/BUILD.gn`

```gn
ohos_unittest("arkui_feature_param_manager_test") {
  sources = [
    # ... 其他源文件
    "$ace_root/adapter/ohos/osal/log_wrapper.cpp",
    "$ace_root/frameworks/base/utils/string_utils.cpp",
    "$ace_root/frameworks/base/log/log_wrapper.cpp",       # ← 添加缺失的源文件
    "$ace_root/test/mock/adapter/mock_log_wrapper.cpp",
    # ... 其他源文件
  ]
}
```

#### 场景 2：ohos_unittest 但依赖了 ace_base source_set

**特征**：
- 使用 `ohos_unittest` 模板
- `deps` 中包含 `ace_base` 或类似的基础库

**解决方案**：在 ace_base 的 sources 中添加

**步骤**：

1. 查找 ace_base source_set 定义：

```bash
# 搜索 ace_base source_set
grep -r "source_set.*ace_base" test/unittest/*.gni
```

2. 在 ace_base source_set 中添加源文件：

```gn
source_set("ace_base") {
  sources = [
    "log/log_wrapper.cpp",           # ← 添加缺失的源文件
    "utils/string_utils.cpp",        # ← 添加缺失的源文件
    "property/measure_property.cpp", # ← 添加缺失的源文件
    # ... 其他基础源文件
  ]
}
```

#### 场景 3：ace_unittest（默认依赖 ace_base）

**特征**：
- 使用 `ace_unittest` 模板
- 默认会依赖 `ace_base`

**解决方案**：与场景 2 相同，在 ace_base 的 sources 中添加

### 常见需要添加的源文件

基于历史经验，以下源文件常需要在测试中添加：

| 源文件 | 路径 | 何时需要 |
|--------|------|----------|
| **log_wrapper.cpp** | `frameworks/base/log/log_wrapper.cpp` | 使用 LogWrapper 方法（JudgeLevel、GetBriefFileName、PrintLog 等） |
| **string_utils.cpp** | `frameworks/base/utils/string_utils.cpp` | 使用 StringUtils 方法（StringSplitter、TransformStrCase、StrToInt 等） |
| **layout_constraint.cpp** | `frameworks/core/components_ng/property/layout_constraint.cpp` | 使用 LayoutConstraintT 模板类方法 |
| **measure_property.cpp** | `frameworks/core/components_ng/property/measure_property.cpp` | 使用 PaddingPropertyF、MeasureProperty 等属性类方法 |
| **transition_property.cpp** | `frameworks/core/components_ng/property/transition_property.cpp` | 使用 TransitionProperty 相关方法 |

## 验证步骤

### 1. 修改 BUILD.gn 后重新编译

```bash
# 从 OpenHarmony 根目录
cd <openharmony_root>

# 重新编译测试
./build.sh --product-name rk3568 --build-target unittest --ccache

# 或只编译特定测试（如果支持）
./build.sh --product-name rk3568 --build-target ace_engine_test --ccache
```

### 2. 检查链接是否成功

```bash
# 提取最新的错误
foundation/arkui/ace_engine/.claude/skills/build-error-analyzer/script/extract_last_error.sh out/rk3568/build.log

# 检查结果
cat out/rk3568/last_error.log

# 应该看到：build success, no error
# 或者不再出现之前的 undefined symbol 错误
```

### 3. 验证可执行文件生成

```bash
# 检查测试可执行文件是否存在
ls -la out/rk3568/tests/unittest/ace_engine/ace_engine/adapter/system_properties_unittest
```

## 历史案例

### 案例 1：system_properties_unittest 缺少 log_wrapper.cpp

**文件**：`test/unittest/adapter/ohos/osal/system_properties/BUILD.gn`

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::LogWrapper::JudgeLevel(OHOS::Ace::LogLevel)
ld.lld: error: undefined symbol: OHOS::Ace::LogWrapper::GetBriefFileName(char const*)
ld.lld: error: undefined symbol: OHOS::Ace::LogWrapper::PrintLog(...)
```

**修改**：
```diff
 sources = [
   "$ace_root/adapter/ohos/osal/system_properties.cpp",
+  "$ace_root/frameworks/base/log/log_wrapper.cpp",
   "$ace_root/frameworks/base/utils/string_utils.cpp",
```

**结果**：链接成功

### 案例 2：arkui_feature_param_manager_test 缺少 log_wrapper.cpp

**文件**：`test/unittest/adapter/ohos/capability/feature_config/BUILD.gn`

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::LogWrapper::JudgeLevel
```

**修改**：
```diff
 sources = [
   "$ace_root/adapter/ohos/osal/log_wrapper.cpp",
   "$ace_root/frameworks/base/utils/string_utils.cpp",
+  "$ace_root/frameworks/base/log/log_wrapper.cpp",
   "$ace_root/test/mock/adapter/mock_log_wrapper.cpp",
```

**结果**：链接成功

### 案例 3：时间选择器模块缺少多个源文件

**背景**：头文件优化后，StringUtils 和 LayoutConstraint 方法被提取到 .cpp

**错误**：
```
ld.lld: error: undefined symbol: OHOS::Ace::StringUtils::StringSplitter<Color>
ld.lld: error: undefined symbol: OHOS::Ace::NG::LayoutConstraintT<float>::UpdateMaxSizeWithCheck
```

**解决方案**：在测试的 BUILD.gn 中添加：
- `$ace_root/frameworks/base/utils/string_utils.cpp`
- `$ace_root/frameworks/core/components_ng/property/layout_constraint.cpp`

**结果**：链接成功

## 技术背景

### 为什么会出现这个问题？

1. **头文件优化**：
   - 为了减少编译依赖，将内联函数从 .h 移到 .cpp
   - 参考 commit e0fd3724d21（StringUtils 重构）

2. **模板显式实例化**：
   - 模板函数的显式实例化必须在 .cpp 中
   - 使用模板的测试代码需要链接包含这些实例化的 .cpp

3. **条件编译**：
   - 某些功能根据宏定义有不同的实现路径
   - 测试环境可能需要完整实现（非内联版本）

### 测试与组件库的差异

- **组件库**：`libace.z.so` 包含所有必要的源文件（在 ace_core_ng_source_set 中）
- **测试用例**：独立编译，需要显式包含所有依赖的源文件

## 相关案例

- `undefined-symbol-missing-cpp.md` - 通用未定义符号诊断流程（主库场景）
- `build-system-ace-core-ng-source_set.md` - ace_core_ng source_set 配置
- `symbol-export-ace-force-export.md` - 跨模块符号导出

## 最佳实践

### 编写新测试用例时

1. **检查依赖**：确认使用了哪些工具类和辅助类
2. **参考现有测试**：查看同目录下其他测试的 BUILD.gn 配置
3. **优先使用 ace_unittest**：如果可能，使用 `ace_unittest` 模板（自动包含 ace_base）

### 修复测试链接错误时

1. **识别缺失的符号**：从错误信息中提取未定义的符号名
2. **定位源文件**：通过符号名或头文件推断对应的 .cpp 文件
3. **判断场景类型**：确认测试模板和 ace_base 依赖关系
4. **添加到正确位置**：根据场景 1-3 选择添加位置
5. **不要修改编译标志**：仅添加源文件，不修改 cflags/configs/defines

### 判断是否需要添加源文件

**需要添加的情况**：
- ✅ 错误发生在测试链接阶段
- ✅ 未定义符号来自新增或重构的源文件
- ✅ 源文件存在于 frameworks/ 目录

**不需要添加的情况**：
- ❌ 符号来自其他动态库（需要添加 deps）
- ❌ 符号需要导出但未添加 ACE_FORCE_EXPORT（参考符号导出案例）
- ❌ 源文件不存在（需要创建源文件）

## 常见错误

### ❌ 错误做法 1：修改 cflags

```gn
# 错误：不要这样做
cflags = [ "-UUSE_HILOG" ]
```

**原因**：这是治标不治本的方法，可能导致其他问题。

### ❌ 错误做法 2：添加 defines

```gn
# 错误：不要这样做
defines = [ "USE_HILOG=false" ]
```

**原因**：定义不能正确控制条件编译，且违反了"只添加源文件"的原则。

### ❌ 错误做法 3：添加到错误的 location

```gn
# 错误：如果测试依赖了 ace_base，应该添加到 ace_base source_set
# 而不是每个测试都重复添加
ohos_unittest("test1") {
  sources = [
    "$ace_root/frameworks/base/log/log_wrapper.cpp",  # 冗余
  ]
  deps = [ ":ace_base" ]  # ace_base 应该包含 log_wrapper.cpp
}
```

**原因**：应该在 ace_base source_set 中统一添加，避免重复。

### ✅ 正确做法：添加到正确的位置

```gn
# 场景 1：无 ace_base 依赖，添加到测试的 sources
ohos_unittest("test1") {
  sources = [
    "$ace_root/frameworks/base/log/log_wrapper.cpp",  # ✅ 正确
  ]
}

# 场景 2/3：有 ace_base 依赖，添加到 ace_base source_set
source_set("ace_base") {
  sources = [
    "log/log_wrapper.cpp",  # ✅ 正确：统一管理
  ]
}
```

## 决策树

```
测试链接错误（undefined symbol）
    │
    ├─→ 符号来自其他动态库？
    │   └─→ YES: 添加 deps 依赖（参考其他案例）
    │
    ├─→ 符号需要导出但未标记？
    │   └─→ YES: 添加 ACE_FORCE_EXPORT（参考 symbol-export 案例）
    │
    └─→ NO: 符号实现存在于 .cpp 文件
        │
        ├─→ 定位源文件（通过符号名或头文件）
        │
        ├─→ 检查测试模板类型
        │   │
        │   ├─→ ohos_unittest 无 ace_base
        │   │   └─→ 添加到测试的 sources
        │   │
        │   └─→ ohos_unittest/ace_unittest 有 ace_base
        │       └─→ 添加到 ace_base source_set
        │
        └─→ 重新编译验证
```

## 总结

当遇到测试链接时出现未定义符号错误：

1. **确认场景**：测试链接错误，符号来自新增或重构的源文件
2. **定位源文件**：通过符号名、头文件或搜索推断对应的 .cpp
3. **判断类型**：检查测试模板和 ace_base 依赖关系
4. **添加文件**：在正确的位置添加源文件到 sources
5. **验证修复**：重新编译并确认链接成功

**关键原则**：
- ✅ 只添加源文件到 sources
- ❌ 不修改 cflags/configs/defines
- ✅ 根据依赖关系选择添加位置
- ✅ 优先使用公共 source_set（如 ace_base）
