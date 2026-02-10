# C Native API 开发指南

本文档详细说明了如何为 ACE Engine 组件新增 C Native API（属性设置接口），包括完整的开发流程、技术约束和参考实现。

## 目录

- [技术约束与开发规则](#技术约束与开发规则)
- [开发流程](#开发流程)
- [调用链说明](#调用链说明)
- [完整示例](#完整示例)

---

## 技术约束与开发规则

在开发 C Native API 时，必须遵守以下分层架构和技术约束。

### 1. 枚举定义层 (Enumeration Layer)

#### 代码位置

`interfaces/native/native_node.h`

#### 枚举命名规则

在 `ArkUI_NodeAttributeType` 枚举类中新增枚举值时，必须遵守以下范围约束：

| 组件 | 属性枚举范围 | 事件枚举范围 |
|-----|------------|------------|
| **TextInput** | `> NODE_TEXT_INPUT_PLACEHOLDER`<br`< NODE_TEXT_AREA_PLACEHOLDER` | `> NODE_TEXT_INPUT_ON_CHANGE`<br`< NODE_TEXT_AREA_ON_CHANGE` |
| **TextArea** | `> NODE_TEXT_AREA_PLACEHOLDER`<br`< NODE_BUTTON_LABEL` | `> NODE_TEXT_AREA_ON_CHANGE`<br`< NODE_CHECKBOX_EVENT_ON_CHANGE` |
| **Text** | `> NODE_TEXT_BASE`<br`< NODE_TEXT_INPUT_PLACEHOLDER` | - |

#### 实现要点

1. **枚举命名**：遵循 `NODE_<组件>_<属性>` 格式（如 `NODE_TEXT_AREA_HORIZONTAL_SCROLLING`）
2. **追加规则**：新增枚举必须追加到对应范围的**末尾**
3. **避免冲突**：确保不与现有枚举值冲突
4. **事件枚举**：如果是事件类型，需要在事件枚举范围内添加

### 2. 入口方法层 (Entry Point Layer)

#### 代码位置

`interfaces/native/node/style_modifier.cpp`

#### 入口方法对应关系

| 操作类型 | 通用入口方法 | 组件专用入口方法 |
|---------|------------|----------------|
| **设置属性** | `SetNodeAttribute` | `SetTextAttribute` / `SetTextInputAttribute` / `SetTextAreaAttribute` |
| **重置属性** | `ResetNodeAttribute` | `ResetTextAttribute` / `ResetTextInputAttribute` / `ResetTextAreaAttribute` |
| **获取属性** | `GetNodeAttribute` | - |

#### 组件与入口方法映射

| 组件 | 设置入口 | 重置入口 |
|-----|---------|---------|
| Text | `SetTextAttribute` | `ResetTextAttribute` |
| TextInput | `SetTextInputAttribute` | `ResetTextInputAttribute` |
| TextArea | `SetTextAreaAttribute` | `ResetTextAreaAttribute` |
| Search | `SetSearchAttribute` | `ResetSearchAttribute` |

#### 实现机制

入口方法层使用**函数指针数组**来实现属性设置的路由，而不是传统的 switch-case 分支。

**核心机制**:
```cpp
// 定义函数指针类型
using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);
using Getter = const ArkUI_AttributeItem*(ArkUI_NodeHandle node);
using Resetter = void(ArkUI_NodeHandle node);

// 在入口方法中定义静态函数指针数组
static Setter* setters[] = {
    SetTextAreaPlaceholder,
    SetTextAreaText,
    // ... 其他 setter
    SetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
};

// 通过枚举值作为索引调用对应的函数
return setters[subTypeId](node, value);
```

#### 实现要点

1. **函数指针数组**：使用静态数组存储所有 setter 函数指针
2. **索引映射**：枚举值作为数组索引，直接调用对应函数
3. **数组追加**：新增属性时，将函数指针追加到数组末尾
4. **边界检查**：检查 `subTypeId` 是否超出数组范围
5. **空指针检查**：检查数组元素是否为 `nullptr`（某些属性可能未实现）

### 3. Modifier 层 (Modifier Layer)

#### 代码位置

`frameworks/core/interfaces/native/node/`

#### 组件与文件对应关系

| 组件名称 | Modifier 文件 |
|---------|--------------|
| Text | `node_text_modifier.cpp` |
| TextInput | `node_text_input_modifier.cpp` |
| TextArea | `node_text_area_modifier.cpp` |
| Search | `search_modifier.cpp` |

#### 实现要点

1. **类型转换**：将 ArkUI 类型转换为 C++ 类型
2. **调用 Model**：调用 Model 层的静态方法设置属性
3. **节点转换**：将 `ArkUINodeHandle` 转换为 `FrameNode*`
4. **空指针检查**：使用 `CHECK_NULL_VOID` 等宏进行检查

### 4. Model 层 (Model Layer)

#### 代码位置

| 组件 | Model 文件 |
|-----|-----------|
| TextInput | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp` |
| TextArea | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp` |
| Text | `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` |

#### 实现要点

1. 提供 `SetXXX(FrameNode* frameNode, T value)` 静态方法
2. 提供 `GetXXX(FrameNode* frameNode)` 静态方法（可选）
3. 提供 `ResetXXX(FrameNode* frameNode)` 静态方法
4. 通过 Pattern 层操作实际属性

---

## 开发流程

### 步骤 1: 在 native_node.h 中新增枚举

**位置**: `interfaces/native/native_node.h`

**任务**:
在 `ArkUI_NodeAttributeType` 枚举类中添加新的枚举值, 需要参考gicode的PR提交，请询问我PR地址。
枚举代码插入顺序按枚举值升序

**代码模板**:

```cpp
// 在对应的枚举范围内追加
enum class ArkUI_NodeAttributeType {
    // ... 现有枚举

    // TextInput 属性范围 (NODE_TEXT_INPUT_PLACEHOLDER ~ NODE_TEXT_AREA_PLACEHOLDER)
    NODE_TEXT_INPUT_XXX,  // 新增 TextInput 属性

    // TextArea 属性范围 (NODE_TEXT_AREA_PLACEHOLDER ~ NODE_BUTTON_LABEL)
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING,  // 新增 TextArea 属性

    // ... 其他枚举
};
```

**命名规则**:
- 格式：`NODE_<组件>_<属性>`
- 示例：`NODE_TEXT_AREA_HORIZONTAL_SCROLLING`

### 步骤 2: 在入口方法层添加函数指针到数组

**位置**: `interfaces/native/node/style_modifier.cpp`

**任务**:
1. 实现 setter 函数（如果步骤 3 还未实现）
2. 将函数指针添加到组件入口方法的 `setters[]` 数组中，插入顺序需要参考ArkUI_NodeAttributeType中枚举值的顺序
3. 将 resetter 函数指针追加到 `resetters[]` 数组中（如需要）， 插入顺序需要参考ArkUI_NodeAttributeType中枚举值的顺序
4. 将 getter 函数指针追加到 `getters[]` 数组中（如需要），插入顺序需要参考ArkUI_NodeAttributeType中枚举值的顺序

**代码模板**:

```cpp
// 1. 实现 setter 函数（通常在文件前面定义）
int32_t SetTextAreaHorizontalScrolling(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value)
{
    // 类型转换和参数校验
    if (!value || value->size <= 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    // 调用 Modifier 层方法
    auto* fullImpl = GetFullImpl();
    bool horizontalScrolling = static_cast<bool>(value->value[0].i32);
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setHorizontalScrolling(
        node->uiNodeHandle, static_cast<uint32_t>(horizontalScrolling));

    return ERROR_CODE_NATIVE_IMPL_OK;
}

// 2. 实现 resetter 函数（可选）
void ResetTextAreaHorizontalScrolling(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(node->uiNodeHandle);
}

// 3. 实现 getter 函数（可选）
const ArkUI_AttributeItem* GetTextAreaHorizontalScrolling(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    static ArkUI_AttributeItem attrItem = { .size = 1 };
    attrItem.value[0].i32 = fullImpl->getNodeModifiers()->getTextAreaModifier()->getHorizontalScrolling(node->uiNodeHandle);
    return &attrItem;
}

// 4. 在 SetTextAreaAttribute 函数的 setters 数组末尾追加
int32_t SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = {
        SetTextAreaPlaceholder,
        SetTextAreaText,
        // ... 现有 setter
        SetTextAreaTextOverflow,
        SetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

// 5. 在 ResetTextAreaAttribute 函数的 resetters 数组末尾追加
void ResetTextAreaAttribute(ArkUINodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = {
        ResetTextAreaPlaceholder,
        ResetTextAreaText,
        // ... 现有 resetter
        ResetTextAreaTextOverflow,
        ResetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        resetters[subTypeId](node);
    }
}

// 6. 在 GetTextAreaAttribute 函数的 getters 数组末尾追加（如实现了 getter）
const ArkUI_AttributeItem* GetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = {
        GetTextAreaPlaceholder,
        GetTextAreaText,
        // ... 现有 getter
        GetTextAreaTextOverflow,
        GetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}
```

**重要说明**:

1. **数组顺序**：函数指针在数组中的位置**必须**与枚举值一一对应
2. **枚举值**：从枚举定义的第一个值开始，数组索引 = 枚举值 - 基础枚举值
3. **空指针处理**：如果某些属性未实现，对应位置可以是 `nullptr`
4. **保持同步**：setters、resetters、getters 三个数组必须保持相同的索引对应关系

### 步骤 3: 在 Modifier 层添加方法实现

**位置**: `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp`

**任务**:
1. 实现设置属性的方法
2. 实现重置属性的方法
3. 实现获取属性的方法（可选）

**代码模板**:

```cpp
// 设置属性
void SetTextAreaHorizontalScrolling(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    // 类型转换：ArkUI_Uint32 -> bool
    bool horizontalScrolling = static_cast<bool>(value);

    // 调用 Model 层方法
    TextFieldModelNG::SetHorizontalScrolling(frameNode, horizontalScrolling);
}

// 重置属性
void ResetTextAreaHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    // 调用 Model 层方法
    TextFieldModelNG::ResetHorizontalScrolling(frameNode);
}

// 获取属性（可选）
ArkUI_Int32 GetTextAreaHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);

    // 调用 Model 层方法并转换类型
    bool value = TextFieldModelNG::GetHorizontalScrolling(frameNode);
    return static_cast<ArkUI_Int32>(value);
}
```

### 步骤 4: 在 Model 层添加属性设置方法（如不存在）

**位置**:
- 头文件: `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.h`
- 实现文件: `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp`

**任务**:
1. 检查是否已存在同名方法
2. 如不存在，添加 Set、Get、Reset 方法的声明和实现

**代码模板**:

```cpp
// .h 文件 - 方法声明
class TextFieldModelNG {
    // ... 其他方法
    static void SetHorizontalScrolling(FrameNode* frameNode, bool value);
    static bool GetHorizontalScrolling(FrameNode* frameNode);
    static void ResetHorizontalScrolling(FrameNode* frameNode);
};

// .cpp 文件 - 方法实现
void TextFieldModelNG::SetHorizontalScrolling(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);

    // 调用 Pattern 层方法设置属性
    pattern->SetHorizontalScrolling(value);
}

bool TextFieldModelNG::GetHorizontalScrolling(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);

    // 调用 Pattern 层方法获取属性
    return pattern->GetHorizontalScrolling();
}

void TextFieldModelNG::ResetHorizontalScrolling(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);

    // 调用 Pattern 层方法重置属性
    pattern->ResetHorizontalScrolling();
}
```

---

## 调用链说明

### 完整调用链示例

以 `halfLeading` 属性为例，完整的调用链如下：

```
NODE_TEXT_INPUT_HALF_LEADING (枚举)
    ↓
SetNodeAttribute (通用入口)
    ↓
SetTextAreaAttribute (组件专用入口)
    ↓ (通过函数指针数组索引)
setters[subTypeId] (函数指针数组调用)
    ↓
SetTextInputHalfLeading (入口层实现)
    ↓
TextFieldModelNG::SetHalfLeading (Model 层)
    ↓
TextFieldPattern::SetHalfLeading (Pattern 层)
    ↓
更新 LayoutProperty (最终操作)
```

### 函数指针数组路由机制

入口层使用**函数指针数组**实现高效的路由机制：

```cpp
// 1. 定义函数指针类型
using Setter = int32_t(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value);

// 2. 定义函数指针数组（索引 = 枚举值 - 基础值）
static Setter* setters[] = {
    SetTextAreaPlaceholder,          // 索引 0
    SetTextAreaText,                 // 索引 1
    // ...
    SetTextAreaHorizontalScrolling,  // 索引 N
};

// 3. 通过枚举值作为索引直接调用
int32_t SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    // 边界检查
    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    // 直接通过索引调用，无需 switch-case
    return setters[subTypeId](node, value);
}
```

**优势**:
- **性能优化**：O(1) 时间复杂度，比 switch-case 更高效
- **可维护性**：新增属性只需追加到数组末尾
- **编译时检查**：函数指针类型安全

### 调用链层次说明

| 层级 | 文件位置 | 作用 | 示例方法 | 实现方式 |
|-----|---------|-----|---------|---------|
| **枚举层** | `interfaces/native/native_node.h` | 定义属性枚举 | `NODE_TEXT_AREA_HORIZONTAL_SCROLLING` | 枚举值 |
| **入口层** | `interfaces/native/node/style_modifier.cpp` | 函数指针数组路由 | `SetTextAreaAttribute` | 静态函数指针数组 |
| **入口实现** | `interfaces/native/node/style_modifier.cpp` | 类型转换和参数校验 | `SetTextAreaHorizontalScrolling` | 函数实现 |
| **Modifier 层** | `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp` | 类型转换和桥接 | `SetTextAreaHorizontalScrolling` | 调用 Model 层 |
| **Model 层** | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp` | 业务逻辑处理 | `SetHorizontalScrolling` | 调用 Pattern 层 |
| **Pattern 层** | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.cpp` | 实际属性操作 | `SetHorizontalScrolling` | 更新 Property |

### 数据流转过程

```
Native API 调用
    ↓ (ArkUINodeHandle, int32_t subTypeId, ArkUI_AttributeItem)
SetTextAreaAttribute
    ↓ (subTypeId 作为索引)
setters[subTypeId] 函数指针数组
    ↓ (直接调用对应的函数)
入口层实现 (SetTextAreaHorizontalScrolling)
    ↓ (类型转换: ArkUI 类型 -> C++ 类型)
Modifier 层 (node_text_area_modifier.cpp)
    ↓ (FrameNode*, C++ 类型值)
Model 层 (text_field_model_ng.cpp)
    ↓ (FrameNode*, C++ 类型值)
Pattern 层 (text_field_pattern.cpp)
    ↓ (更新 Property)
Property 更新
    ↓ (触发重绘/重排)
UI 更新
```

### 数组索引映射示例

```cpp
// 假设 TextArea 的属性枚举从 200 开始
enum class ArkUI_NodeAttributeType {
    NODE_TEXT_AREA_PLACEHOLDER = 200,
    NODE_TEXT_AREA_TEXT = 201,
    NODE_TEXT_AREA_MAX_LENGTH = 202,
    // ...
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 235,  // 新增属性
};

// 函数指针数组（索引 = 枚举值 - 200）
static Setter* setters[] = {
    /* [0] */ SetTextAreaPlaceholder,      // 200 - 200 = 0
    /* [1] */ SetTextAreaText,             // 201 - 200 = 1
    /* [2] */ SetMaxLength,                // 202 - 200 = 2
    // ...
    /* [35] */ SetTextAreaHorizontalScrolling,  // 235 - 200 = 35
};

// 调用时：subTypeId = 235
// 实际数组索引：235 - 200 = 35
setters[35](node, value);  // 调用 SetTextAreaHorizontalScrolling
```

---

## 完整示例

### 示例: 为 TextArea 添加 `horizontalScrolling` C Native API

#### 需求描述

为 TextArea 组件添加 C Native API，支持设置横向滚动属性。

#### 类型定义

- **枚举名称**: `NODE_TEXT_AREA_HORIZONTAL_SCROLLING`
- **参数类型**: `ArkUI_Uint32` (映射到 C++ 的 `bool`)
- **默认值**: `false`

#### 实现清单

| 步骤 | 文件 | 添加内容 |
|-----|------|---------|
| 1 | native_node.h | 枚举 `NODE_TEXT_AREA_HORIZONTAL_SCROLLING` |
| 2 | style_modifier.cpp | 入口函数实现并追加到函数指针数组 |
| 3 | node_text_area_modifier.cpp | `SetTextAreaHorizontalScrolling` 等方法 |
| 4 | text_field_model_ng.cpp/h | Model 层方法（如不存在） |

#### 步骤 1: 添加枚举

**文件**: `interfaces/native/native_node.h`

```cpp
enum class ArkUI_NodeAttributeType {
    // ... 在 NODE_TEXT_AREA_PLACEHOLDER 之后添加

    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = XXX,  // 具体值需根据现有枚举确定

    // ... 其他枚举
};
```

#### 步骤 2: 添加入口层函数实现并追加到函数指针数组

**文件**: `interfaces/native/node/style_modifier.cpp`

```cpp
// 1. 实现 setter 函数（通常在文件前面定义）
int32_t SetTextAreaHorizontalScrolling(ArkUI_NodeHandle node, const ArkUI_AttributeItem* value)
{
    // 参数校验
    if (!value || value->size <= 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    // 调用 Modifier 层方法
    auto* fullImpl = GetFullImpl();
    bool horizontalScrolling = static_cast<bool>(value->value[0].i32);
    fullImpl->getNodeModifiers()->getTextAreaModifier()->setHorizontalScrolling(
        node->uiNodeHandle, static_cast<uint32_t>(horizontalScrolling));

    return ERROR_CODE_NATIVE_IMPL_OK;
}

// 2. 实现 resetter 函数
void ResetTextAreaHorizontalScrolling(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    fullImpl->getNodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(node->uiNodeHandle);
}

// 3. 实现 getter 函数（可选）
const ArkUI_AttributeItem* GetTextAreaHorizontalScrolling(ArkUI_NodeHandle node)
{
    auto* fullImpl = GetFullImpl();
    static ArkUI_AttributeItem attrItem = { .size = 1 };
    attrItem.value[0].i32 = fullImpl->getNodeModifiers()->getTextAreaModifier()->getHorizontalScrolling(node->uiNodeHandle);
    return &attrItem;
}

// 4. 在 SetTextAreaAttribute 函数的 setters 数组末尾追加
int32_t SetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId, const ArkUI_AttributeItem* value)
{
    static Setter* setters[] = {
        SetTextAreaPlaceholder,
        SetTextAreaText,
        SetMaxLength,
        SetPlaceholderColor,
        // ... 其他 setter
        SetTextAreaTextOverflow,
        SetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(setters) / sizeof(Setter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    return setters[subTypeId](node, value);
}

// 5. 在 ResetTextAreaAttribute 函数的 resetters 数组末尾追加
void ResetTextAreaAttribute(ArkUINodeHandle node, int32_t subTypeId)
{
    static Resetter* resetters[] = {
        ResetTextAreaPlaceholder,
        ResetTextAreaText,
        ResetMaxLength,
        // ... 其他 resetter
        ResetTextAreaTextOverflow,
        ResetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(resetters) / sizeof(Resetter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return;
    }
    if (resetters[subTypeId]) {
        resetters[subTypeId](node);
    }
}

// 6. 在 GetTextAreaAttribute 函数的 getters 数组末尾追加（如实现了 getter）
const ArkUI_AttributeItem* GetTextAreaAttribute(ArkUI_NodeHandle node, int32_t subTypeId)
{
    static Getter* getters[] = {
        GetTextAreaPlaceholder,
        GetTextAreaText,
        GetMaxLength,
        // ... 其他 getter
        GetTextAreaTextOverflow,
        GetTextAreaHorizontalScrolling,  // 新增：追加到数组末尾
    };

    if (static_cast<uint32_t>(subTypeId) >= sizeof(getters) / sizeof(Getter*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "textarea node attribute: %{public}d NOT IMPLEMENT", subTypeId);
        return nullptr;
    }
    return getters[subTypeId](node);
}
```

**关键点**:
1. 函数指针在数组中的位置必须与枚举值对应
2. 三个数组（setters、resetters、getters）必须保持同步
3. 使用 `GetFullImpl()` 获取 Modifier 实例

#### 步骤 3: 添加 Modifier 层实现

**文件**: `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp`

```cpp
void SetTextAreaHorizontalScrolling(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    // 类型转换：uint32 -> bool
    bool horizontalScrolling = (value != 0);

    // 调用 Model 层方法
    TextFieldModelNG::SetHorizontalScrolling(frameNode, horizontalScrolling);
}

void ResetTextAreaHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    // 调用 Model 层方法重置为默认值
    TextFieldModelNG::ResetHorizontalScrolling(frameNode);
}

ArkUI_Int32 GetTextAreaHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);

    // 获取值并转换类型：bool -> int32
    bool value = TextFieldModelNG::GetHorizontalScrolling(frameNode);
    return static_cast<ArkUI_Int32>(value);
}
```

#### 步骤 4: 添加 Model 层方法

**文件**: `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp/h`

```cpp
// .h 文件
class TextFieldModelNG {
    static void SetHorizontalScrolling(FrameNode* frameNode, bool value);
    static bool GetHorizontalScrolling(FrameNode* frameNode);
    static void ResetHorizontalScrolling(FrameNode* frameNode);
};

// .cpp 文件
void TextFieldModelNG::SetHorizontalScrolling(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHorizontalScrolling(value);
}

bool TextFieldModelNG::GetHorizontalScrolling(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetHorizontalScrolling();
}

void TextFieldModelNG::ResetHorizontalScrolling(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHorizontalScrolling(false);  // 重置为默认值 false
}
```

#### 使用示例

```c
// C Native API 调用
ArkUI_NativeNodeHandle* textArea = ...;

// 设置横向滚动为 true
ArkUI_Uint32 value = 1;
SetTextAreaAttribute(textArea, NODE_TEXT_AREA_HORIZONTAL_SCROLLING, &value);

// 重置横向滚动
ResetTextAreaAttribute(textArea, NODE_TEXT_AREA_HORIZONTAL_SCROLLING);

// 获取横向滚动值
ArkUI_Int32 scrolling = GetTextAreaAttribute(textArea, NODE_TEXT_AREA_HORIZONTAL_SCROLLING);
```

---

## 开发注意事项

### 1. 顺序要求

**必须严格按照步骤 1-4 的顺序实现**，确保各层之间的调用链正确。

### 2. 枚举范围约束

新增枚举时必须在指定的范围内，避免与现有枚举冲突：

```cpp
// ✅ 正确：在 TextArea 属性范围内
NODE_TEXT_AREA_HORIZONTAL_SCROLLING  // > NODE_TEXT_AREA_PLACEHOLDER && < NODE_BUTTON_LABEL

// ❌ 错误：超出范围
NODE_TEXT_AREA_HORIZONTAL_SCROLLING  // > NODE_BUTTON_LABEL
```

### 3. 类型转换

常见类型转换示例：

| ArkUI 类型 | C++ 类型 | 转换方法 |
|-----------|---------|---------|
| `ArkUI_Uint32` | `bool` | `static_cast<bool>(value)` 或 `value != 0` |
| `ArkUI_Int32` | `int32_t` | `static_cast<int32_t>(value)` |
| `ArkUI_Float32` | `float` | `static_cast<float>(value)` |
| `ArkUI_CharPtr` | `std::string` | `std::string(value)` |
| `ArkUINodeHandle` | `FrameNode*` | `reinterpret_cast<FrameNode*>(node)` |

### 4. 空指针检查

使用提供的宏进行空指针检查：

```cpp
// 检查并返回（适用于有返回值的函数）
CHECK_NULL_RETURN(pointer, defaultValue);

// 检查并返回（适用于 void 函数）
CHECK_NULL_VOID(pointer);
```

### 5. 边界情况处理

- 处理 `nullptr` 节点
- 处理无效的属性值
- 在重置时恢复到合理的默认值

### 6. 代码风格

- 添加详细的注释说明功能
- 遵循项目现有的代码风格
- 保持与现有代码的一致性
- 新增方法追加到同类的末尾处

---

## 常见问题

### Q1: 如何确定枚举的值？

A: 查看对应范围内最后一个枚举的值，在此基础上递增。例如：

```cpp
NODE_TEXT_AREA_PLACEHOLDER = 250,
NODE_TEXT_AREA_CUSTOM_KEY_BOARD = 251,
// 新增枚举应该是 252
NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 252,
```

### Q2: 如何确保函数指针数组与枚举值正确对应？

A: 函数指针数组的索引与枚举值必须一一对应：

```cpp
// 假设枚举定义
enum class ArkUI_NodeAttributeType {
    NODE_TEXT_AREA_PLACEHOLDER = 200,     // 基础枚举值
    NODE_TEXT_AREA_TEXT = 201,
    NODE_TEXT_AREA_MAX_LENGTH = 202,
    // ...
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 235,  // 新增枚举
};

// 函数指针数组
static Setter* setters[] = {
    SetTextAreaPlaceholder,      // 索引 0 -> 对应枚举 200 (200-200=0)
    SetTextAreaText,             // 索引 1 -> 对应枚举 201 (201-200=1)
    SetMaxLength,                // 索引 2 -> 对应枚举 202 (202-200=2)
    // ...
    SetTextAreaHorizontalScrolling,  // 索引 35 -> 对应枚举 235 (235-200=35)
};

// 调用时
SetTextAreaAttribute(node, 235, value);  // subTypeId=235，实际调用 setters[35]
```

**关键点**:
- 数组索引 = 枚举值 - 基础枚举值
- 中间未实现的属性位置填 `nullptr`
- 三个数组（setters、resetters、getters）的索引必须一致

### Q3: 为什么要同时实现 Set、Reset、Get 三个方法？

A:
- **Set**: 设置属性值
- **Reset**: 重置属性到默认值（用于动画结束后恢复）
- **Get**: 获取当前属性值（用于读取状态）

Get 方法是可选的，如果不需要读取属性可以不实现。

### Q4: 如何处理复杂的属性类型（如结构体）？

A: 参考 `SetTextAreaPlaceholderFont` 等复杂属性的实现，需要解析 `ArkUI_AttributeItem` 中的结构体指针。

### Q5: 为什么使用函数指针数组而不是 switch-case？

A: 函数指针数组方案具有以下优势：

| 特性 | 函数指针数组 | switch-case |
|-----|------------|-----------|
| **性能** | O(1) 直接索引 | O(1) 但有分支预测开销 |
| **可维护性** | 新增只需追加到数组末尾 | 需要添加 case 分支 |
| **类型安全** | 编译时检查函数签名 | 编译时检查函数签名 |
| **代码量** | 较少 | 较多（重复的 case/break） |
| **错误处理** | 统一的边界检查 | 每个 case 都需要处理 |

对于有数十甚至上百个属性的组件，函数指针数组方案更优。

### Q6: 如何测试新增的 C Native API？

A:
1. 编写 C 测试用例
2. 编译并通过 NDK 调用 API
3. 验证属性是否正确生效
4. 测试边界情况（空指针、无效值等）

---

## 附录

### 相关目录结构

```
ace_engine/
├── interfaces/native/
│   ├── native_node.h                    # 枚举定义
│   └── node/
│       ├── style_modifier.cpp            # 入口方法层
│       ├── node_text_area_modifier.cpp   # Modifier 层
│       ├── node_text_input_modifier.cpp
│       ├── node_text_modifier.cpp
│       └── search_modifier.cpp
└── frameworks/core/components_ng/pattern/
    ├── text_field/
    │   ├── text_field_model_ng.cpp       # Model 层
    │   ├── text_field_model_ng.h
    │   ├── text_field_pattern.cpp        # Pattern 层
    │   └── text_field_pattern.h
    └── text/
        ├── text_model_ng.cpp
        └── text_model_ng.h
```

### 常用宏定义

```cpp
// 空指针检查
CHECK_NULL_VOID(pointer)      // 检查空指针，为空时返回
CHECK_NULL_RETURN(pointer, value)  // 检查空指针，为空时返回默认值

// 属性更新宏
ACE_UPDATE_NODE_LAYOUT_PROPERTY(PropertyType, PropertyName, value, node)
ACE_UPDATE_NODE_PAINT_PROPERTY(PropertyType, PropertyName, value, node)
ACE_RESET_NODE_LAYOUT_PROPERTY(PropertyType, PropertyName, node)
```

### 类型映射表

| 用途 | ArkUI 类型 | C++ 类型 | 说明 |
|-----|-----------|---------|-----|
| 节点句柄 | `ArkUINodeHandle` | `void*` | 指向 FrameNode 的指针 |
| 布尔值 | `ArkUI_Uint32` | `bool` | 0=false, 非0=true |
| 整数 | `ArkUI_Int32` | `int32_t` | 32位有符号整数 |
| 无符号整数 | `ArkUI_Uint32` | `uint32_t` | 32位无符号整数 |
| 浮点数 | `ArkUI_Float32` | `float` | 32位浮点数 |
| 字符串 | `ArkUI_CharPtr` | `char*` | C 风格字符串 |

---

## 参考资源

### 相关文档

- [Modifier API 开发指南](./modifier_api_guide.md)
- [ACE Engine 架构文档](../CLAUDE.md)

### Git 命令

```bash
# 查看文件历史
git log --oneline -- <文件路径>

# 查看特定提交
git show <commit-id> -- <文件路径>

# 搜索相关代码
git grep -i "horizontalScrolling"
```

---

**文档版本**: v1.0
**最后更新**: 2026-02-05
**维护者**: ACE Engine Team
