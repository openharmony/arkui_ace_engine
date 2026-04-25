# RichEditor CAPI 属性添加指南

> **文档版本**: v1.0
> **更新时间**: 2026-04-18
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [新增属性：NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING](#新增属性node_text_editor_horizontal_scrolling)
3. [实现步骤详解](#实现步骤详解)
4. [代码修改清单](#代码修改清单)
5. [测试验证](#测试验证)
6. [常见问题](#常见问题)

---

## 概述

本文档详细说明如何为 RichEditor 组件新增 CAPI 属性枚举 `NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING`，该属性用于控制 RichEditor 是否启用横向滚动功能。

### 技术架构

RichEditor CAPI 属性的实现遵循以下架构层次：

```
┌─────────────────────────────────────────────────────────┐
│  CAPI 层 (interfaces/native/)                           │
│  - native_node.h: 枚举定义                              │
│  - rich_editor_properties.def: 属性定义宏               │
│  - style_modifier.cpp: Set/Get/Reset 函数实现           │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Bridge 层 (frameworks/core/components_ng/pattern/      │
│              rich_editor/bridge/)                       │
│  - arkts_native_rich_editor_bridge.cpp: ArkTS 桥接      │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Model 层 (frameworks/core/components_ng/pattern/       │
│             rich_editor/)                               │
│  - rich_editor_model_ng.cpp: 业务逻辑实现               │
│  - rich_editor_pattern.h/cpp: Pattern 层实现            │
└─────────────────────────────────────────────────────────┘
```

### 关键发现

通过代码分析发现：

1. **底层实现已存在**: `rich_editor_model_ng.cpp` 中已有 `SetHorizontalScrolling`、`GetHorizontalScrolling` 方法实现（1154-1175行）
2. **桥接函数已存在**: `arkts_native_rich_editor_bridge.cpp` 中已有 `SetHorizontalScrolling`、`ResetHorizontalScrolling` 桥接函数（182-183行，2810行开始）
3. **只需添加 CAPI 层**: 需要在 CAPI 层添加枚举定义和属性处理函数

---

## 新增属性：NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING

### 属性说明

- **属性名称**: `NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING`
- **功能**: 控制 RichEditor 是否启用横向滚动
- **数据类型**: `ArkUI_AttributeItem`
  - `.value[0].i32`: 布尔值，true 表示启用横向滚动，false 表示禁用
- **默认值**: false（禁用横向滚动）
- **支持操作**: set（设置）、get（获取）、reset（重置）

### 参考实现

类似属性实现参考：

1. **TextArea 的横向滚动**: `NODE_TEXT_AREA_HORIZONTAL_SCROLLING`（已实现）
   - 源码位置: `interfaces/native/node/style_modifier.cpp:13702-13712`
   - 枚举位置: `interfaces/native/native_node.h`

2. **RichEditor 的其他布尔属性**: `NODE_TEXT_EDITOR_ENABLE_HAPTIC_FEEDBACK`
   - 源码位置: `interfaces/native/node/style_modifier.cpp:5417-5438`

---

## 实现步骤详解

### 步骤 1: 添加枚举定义 (native_node.h)

**文件位置**: `interfaces/native/native_node.h`

**插入位置**: 在 `NODE_TEXT_EDITOR_ORPHAN_CHAR_OPTIMIZATION` 之后（约6571行）

**代码示例**:

```cpp
/**
 * @brief Defines whether horizontal scrolling is enabled for the TextEditor.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: Whether horizontal scrolling is enabled, true means enable, false means disable.
 * The default value is false.\n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: The current state of horizontal scrolling.\n
 *
 * @since 26
 */
NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING,
```

**关键点**:
- 枚举值会自动递增，无需手动指定数值
- 注释格式遵循现有规范
- `@since 26` 表示 API 版本号

### 步骤 2: 添加属性定义 (rich_editor_properties.def)

**文件位置**: `interfaces/native/node/rich_editor_properties.def`

**插入位置**: 在最后一行 `X(1, 1, 1, OrphanCharOptimization)` 之后

**代码示例**:

```cpp
X(1, 1, 1, RichEditorHorizontalScrolling)
```

**宏定义说明**:
- `X(needSetter, needGetter, needResetter, porpName)`
- 第一个参数 `1`: 需要 setter 函数
- 第二个参数 `1`: 需要 getter 函数
- 第三个参数 `1`: 需要 resetter 函数
- 第四个参数: 属性名称（会自动生成函数名）

**生成的函数名**:
- Setter: `SetRichEditorHorizontalScrolling`
- Getter: `GetRichEditorHorizontalScrolling`
- Resetter: `ResetRichEditorHorizontalScrolling`

### 步骤 3: 实现属性处理函数 (style_modifier.cpp)

**文件位置**: `interfaces/native/node/style_modifier.cpp`

**插入位置**: 在 `ResetRichEditorEnableAutoSpacing` 函数之后（约5520行）

**代码实现**:

```cpp
int32_t SetRichEditorHorizontalScrolling(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getRichEditorModifier()->setRichEditorHorizontalScrolling(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}

const ArkUI_AttributeItem* GetRichEditorHorizontalScrolling(ArkUI_NodeHandle node)
{
    g_numberValues[0].i32 = GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->
        getRichEditorHorizontalScrolling(node->uiNodeHandle);
    return &g_attributeItem;
}

void ResetRichEditorHorizontalScrolling(ArkUI_NodeHandle node)
{
    GetFullImpl()->getNodeModifiers()->getRichEditorModifier()->resetRichEditorHorizontalScrolling(
        node->uiNodeHandle);
}
```

**关键点**:
1. **参数验证**: 使用 `item->size == 0` 检查参数数量，使用 `CheckAttributeIsBool` 验证参数值
2. **布尔值验证**: `CheckAttributeIsBool` 确保参数值为 0 或 1，防止非法值
3. **返回值**: Getter 使用全局变量 `g_numberValues` 和 `g_attributeItem` 返回结果
4. **底层调用**: 通过 `getRichEditorModifier()` 获取 modifier 接口

### 步骤 4: 验证桥接层 (arkts_native_rich_editor_bridge.cpp)

**文件位置**: `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp`

**验证内容**: 桥接函数已存在，无需修改

**已有实现**（182-183行，2810-2843行）:

```cpp
// 函数注册（182-183行）
panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetHorizontalScrolling),
panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetHorizontalScrolling),

// SetHorizontalScrolling 实现（2810-2828行）
ArkUINativeModuleValue RichEditorBridge::SetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->setRichEditorHorizontalScrolling(
            nativeNode, secondArg->ToBoolean(vm)->Value());
    } else if (secondArg->IsNumber()) {
        nodeModifiers->getRichEditorModifier()->setRichEditorHorizontalScrolling(
            nativeNode, static_cast<uint32_t>(secondArg->ToNumber(vm)->Value()));
    }
    return panda::JSValueRef::Undefined(vm);
}

// ResetHorizontalScrolling 实现（2830-2843行）
ArkUINativeModuleValue RichEditorBridge::ResetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // ... 实现代码
}
```

### 步骤 5: 验证 Model 层 (rich_editor_model_ng.cpp)

**文件位置**: `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp`

**验证内容**: Model 层实现已存在，无需修改

**已有实现**（1154-1175行）:

```cpp
void RichEditorModelNG::SetHorizontalScrolling(bool isEnabled)
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetHorizontalScrolling(isEnabled);
}

void RichEditorModelNG::SetHorizontalScrolling(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetHorizontalScrolling(isEnabled);
}

bool RichEditorModelNG::GetHorizontalScrolling(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, false);
    return richEditorPattern->GetHorizontalScrolling();
}
```

---

## 代码修改清单

### 必须修改的文件

| 文件路径 | 修改内容 | 行数位置 |
|---------|---------|---------|
| `interfaces/native/native_node.h` | 添加枚举 `NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING` | 约6571行后 |
| `interfaces/native/node/rich_editor_properties.def` | 添加属性定义 `X(1, 1, 1, RichEditorHorizontalScrolling)` | 第33行后 |
| `interfaces/native/node/style_modifier.cpp` | 实现 Set/Get/Reset 函数 | 约5520行后 |

### 无需修改的文件（已存在实现）

| 文件路径 | 已有功能 | 代码位置 |
|---------|---------|---------|
| `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp` | SetHorizontalScrolling/ResetHorizontalScrolling | 182-183行，2810-2843行 |
| `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` | SetHorizontalScrolling/GetHorizontalScrolling | 1154-1175行 |

---

## 测试验证

### 编译验证

```bash
# 编译 ace_engine
./build.sh --product-name rk3568 --build-target ace_engine

# 编译 C API 单元测试
./build.sh --product-name rk3568 --build-target linux_unittest_capi --ccache
```

### 单元测试

**测试文件位置**: `out/rk3568/tests/unittest/ace_engine/C-API-Main/components/`

**测试用例示例**:

```cpp
// 测试设置横向滚动
ArkUI_NodeHandle node = createNode(ARKUI_NODE_TEXT_EDITOR);
ArkUI_AttributeItem item = { .value[0].i32 = 1 }; // 启用横向滚动
int32_t result = setAttribute(node, NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING, &item);
ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

// 测试获取横向滚动状态
const ArkUI_AttributeItem* resultItem = getAttribute(node, NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING);
ASSERT_NE(resultItem, nullptr);
ASSERT_EQ(resultItem->value[0].i32, 1);

// 测试重置横向滚动
resetAttribute(node, NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING);
const ArkUI_AttributeItem* resetItem = getAttribute(node, NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING);
ASSERT_NE(resetItem, nullptr);
ASSERT_EQ(resetItem->value[0].i32, 0); // 重置后应为 false
```

### 功能验证

1. **设置属性**: 调用 `setAttribute` 设置 `NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING` 为 true
2. **获取属性**: 调用 `getAttribute` 验证返回值是否正确
3. **重置属性**: 调用 `resetAttribute` 重置属性，验证是否恢复默认值
4. **边界测试**: 测试非法参数（如空指针、错误类型）的错误处理

---

## 常见问题

### Q1: 为什么 rich_editor_properties.def 使用宏定义？

**A**: 使用宏定义可以自动生成函数数组，避免手动维护数组索引。宏展开后会自动生成：
- Setter 数组：用于 `SetRichEditorAttribute` 函数
- Getter 数组：用于 `GetRichEditorAttribute` 函数
- Resetter 数组：用于 `ResetRichEditorAttribute` 函数

这种设计确保了属性定义的一致性和可维护性。

### Q2: 枚举值的数值是如何确定的？

**A**: 枚举值基于节点类型和属性索引计算：
- 基础值 = `MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR`
- 每个新属性自动递增
- 无需手动指定数值，编译器自动处理

### Q3: 为什么需要将 bool 转换为 uint32_t？

**A**: 底层 C API 使用 `uint32_t` 作为布尔值传递，这是跨语言接口的常见做法，确保类型安全和兼容性。

### Q4: 如何验证新属性是否正确添加？

**A**: 验证步骤：
1. 编译成功，无错误
2. C API 单元测试通过
3. 使用 `getAttribute` 获取属性，验证返回值
4. 检查 `native_node.h` 中枚举值是否正确递增

### Q5: 如果添加失败，如何排查问题？

**A**: 排查步骤：
1. 检查枚举定义是否在正确位置（在最后一个 TextEditor 属性之后）
2. 检查 `rich_editor_properties.def` 中的宏定义格式是否正确
3. 检查 `style_modifier.cpp` 中的函数实现是否正确调用底层接口
4. 检查编译日志，确认是否有链接错误

---

## 附录：相关代码位置索引

### CAPI 层

- **枚举定义**: `interfaces/native/native_node.h:6571` (NODE_TEXT_EDITOR_ORPHAN_CHAR_OPTIMIZATION)
- **属性定义**: `interfaces/native/node/rich_editor_properties.def:33`
- **属性处理**: `interfaces/native/node/style_modifier.cpp:5520` (ResetRichEditorEnableAutoSpacing)

### Bridge 层

- **桥接注册**: `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp:182-183`
- **SetHorizontalScrolling**: `arkts_native_rich_editor_bridge.cpp:2810-2828`
- **ResetHorizontalScrolling**: `arkts_native_rich_editor_bridge.cpp:2830-2843`

### Model 层

- **SetHorizontalScrolling**: `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp:1154-1167`
- **GetHorizontalScrolling**: `rich_editor_model_ng.cpp:1169-1175`

---

## 总结

本文档详细说明了为 RichEditor 组件新增 CAPI 属性 `NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING` 的完整实现流程。关键发现是底层实现已经存在，只需在 CAPI 层添加枚举定义和属性处理函数即可。遵循本文档的步骤和代码示例，可以确保新属性的正确实现和测试验证。

---

## 经验教训：布尔属性实现的参数检查规范

### 问题发现

在代码审查过程中，发现了三个关于布尔属性参数检查的问题：

1. **入参 item 是否需要判空？**
2. **actualSize==0 时，是否属于参数错误？**
3. **读取参数前是否需要 CheckAttributeIsBool？**

### 标准实现模式

通过分析现有代码（`SetRichEditorEnableHapticFeedback`、`SetRichEditorStopBackPress`、`SetRichEditorEnableAutoSpacing`），发现布尔属性的标准实现模式：

```cpp
int32_t SetRichEditorEnableHapticFeedback(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item) {
    auto fullImpl = GetFullImpl();
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getRichEditorModifier()->setRichEditorEnableHapticFeedback(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}
```

### 关键规范

#### 1. 不判空 item 参数

**原因**：
- CAPI 层的入口函数 `SetNodeAttribute` 已经在调用前进行了判空检查
- 现有代码遵循"信任上层调用"的原则，不重复判空
- 直接访问 `item->size` 和 `item->value[0]` 是安全的

**错误示例**：
```cpp
// ❌ 错误：使用 CheckAttributeItemArray 内部判空
auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
if (actualSize < 0) {
    return ERROR_CODE_PARAM_INVALID;
}
```

**正确示例**：
```cpp
// ✅ 正确：直接访问 item->size
if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
    return ERROR_CODE_PARAM_INVALID;
}
```

#### 2. 使用 item->size == 0 检查参数数量

**原因**：
- 简洁明了，符合现有代码风格
- `item->size == 0` 明确表示"没有参数"
- 避免使用复杂的辅助函数

**错误示例**：
```cpp
// ❌ 错误：使用 CheckAttributeItemArray
auto actualSize = CheckAttributeItemArray(item, REQUIRED_ONE_PARAM);
if (actualSize < 0) {
    return ERROR_CODE_PARAM_INVALID;
}
```

**正确示例**：
```cpp
// ✅ 正确：直接检查 size
if (item->size == 0) {
    return ERROR_CODE_PARAM_INVALID;
}
```

#### 3. 必须使用 CheckAttributeIsBool 验证布尔值

**原因**：
- `CheckAttributeIsBool` 确保参数值只能是 0 或 1
- 防止非法值（如 2、-1、100 等）被接受
- CAPI 层需要严格的参数验证，确保类型安全

**CheckAttributeIsBool 定义**（style_modifier.cpp:607-613）：
```cpp
bool CheckAttributeIsBool(int32_t value)
{
    if (value == DEFAULT_FALSE || value == DEFAULT_TRUE) {
        return true;
    }
    return false;
}
```

其中：
- `DEFAULT_FALSE = 0`
- `DEFAULT_TRUE = 1`

**错误示例**：
```cpp
// ❌ 错误：直接转换类型，可能接受非法值
bool horizontalScrolling = static_cast<bool>(item->value[0].i32);
fullImpl->getNodeModifiers()->getRichEditorModifier()->setRichEditorHorizontalScrolling(
    node->uiNodeHandle, static_cast<uint32_t>(horizontalScrolling));
```

**正确示例**：
```cpp
// ✅ 正确：使用 CheckAttributeIsBool 验证
if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
    return ERROR_CODE_PARAM_INVALID;
}
fullImpl->getNodeModifiers()->getRichEditorModifier()->setRichEditorHorizontalScrolling(
    node->uiNodeHandle, item->value[0].i32);
```

### 修正后的完整实现

```cpp
int32_t SetRichEditorHorizontalScrolling(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
{
    auto* fullImpl = GetFullImpl();
    if (item->size == 0 || !CheckAttributeIsBool(item->value[0].i32)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    fullImpl->getNodeModifiers()->getRichEditorModifier()->setRichEditorHorizontalScrolling(
        node->uiNodeHandle, item->value[0].i32);
    return ERROR_CODE_NO_ERROR;
}
```

### 经验总结

**核心原则**：
1. **遵循现有模式**：参考同类属性的现有实现，保持代码风格一致
2. **严格参数验证**：布尔属性必须使用 `CheckAttributeIsBool` 验证
3. **信任上层调用**：CAPI 层不重复判空，由入口函数统一处理
4. **简洁明了**：使用 `item->size == 0` 而非复杂的辅助函数

**适用范围**：
- 所有布尔类型的 CAPI 属性（如 `EnableHapticFeedback`、`StopBackPress`、`EnableAutoSpacing` 等）
- 所有需要验证参数值为特定枚举或范围的属性

**参考代码位置**：
- `SetRichEditorEnableHapticFeedback`: style_modifier.cpp:5417-5425
- `SetRichEditorStopBackPress`: style_modifier.cpp:5440-5448
- `SetRichEditorEnableAutoSpacing`: style_modifier.cpp:5500-5508
- `CheckAttributeIsBool`: style_modifier.cpp:607-613