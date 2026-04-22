# RichEditor组件新增接口编码指导

> **文档版本**: v1.0
> **更新时间**: 2026-04-18
> **适用范围**: RichEditor组件接口扩展开发

---

## ⚠️ 关键规范速查（必读）

**在开始实现前，请务必遵守以下规范，违反这些规范会导致接口注册失败或破坏现有接口稳定性：**

| 规范 | 说明 | 影响范围 |
|------|------|----------|
| **数组末尾添加** | Bridge层 `functionNames` 和 `functionValues` 数组，新增接口必须添加到**数组末尾**，禁止插入中间位置 | Bridge层 |
| **数组一一对应** | `functionNames` 和 `functionValues` 数组必须保持一一对应关系，数量和顺序完全匹配 | Bridge层 |
| **Modifier末尾注册** | `GetRichEditorDynamicModifier()` 中新增字段添加到结构体末尾，在最后一个现有字段之后 | Modifier层 |
| **API末尾添加** | `arkoala_api.h` 中 `ArkUIRichEditorModifier` 结构体，新增函数指针添加到结构体末尾 | API定义层 |

**为什么必须添加到末尾？**
- 数组/结构体顺序决定了接口的注册索引
- 插入中间位置会导致已有接口索引变化，破坏现有接口稳定性
- 添加到末尾可以保证向后兼容

---

## 目录

1. [概述](#概述)
2. [接口调用链架构](#接口调用链架构)
3. [需要适配的文件清单](#需要适配的文件清单)
4. [各层适配详解](#各层适配详解)
5. [参数解析规范](#参数解析规范)
6. [事件回调处理](#事件回调处理)
7. [完整示例：新增一个属性接口](#完整示例新增一个属性接口)
8. [完整示例：新增一个事件接口](#完整示例新增一个事件接口)
9. [常见问题与注意事项](#常见问题与注意事项)

---

## 概述

本文档旨在指导开发者为RichEditor组件新增接口时的编码流程。RichEditor组件采用多层架构设计，新增接口需要在多个层级进行适配，从JS/ArkTS层到Native C++层，最终调用至Model层的业务逻辑实现。

### 核心设计原则

1. **分层解耦**: 每层只处理本层职责，参数解析在Bridge层完成
2. **统一接口**: 通过Modifier结构体统一暴露Native接口
3. **双向支持**: 同时支持ArkTS声明式调用和C API调用

---

## 接口调用链架构

RichEditor接口调用链采用以下架构：

```
┌─────────────────────────────────────────────────────────────────┐
│  应用层 (ArkTS/JS)                                              │
│  RichEditor().newProperty(value)                                │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│  JS组件层                                                        │
│  frameworks/bridge/declarative_frontend/ark_component/          │
│  ├── components/arkricheditor.js                                │
│  └── src/ArkRichEditor.ts                                       │
│  职责: 接口入口定义、参数收集                                     │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│  Bridge层 (C++)                                                  │
│  frameworks/core/components_ng/pattern/rich_editor/bridge/      │
│  ├── arkts_native_rich_editor_bridge.cpp                        │
│  ├── arkts_native_rich_editor_bridge.h                          │
│  └── rich_editor_dynamic_modifier.cpp                           │
│  职责: 参数解析、类型转换、调用Native Modifier                    │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│  API定义层                                                        │
│  frameworks/core/interfaces/                                     │
│  ├── arkoala/arkoala_api.h (ArkUIRichEditorModifier)            │
│  └── cjui/cjui_api.h (CJUIRichEditorModifier)                   │
│  职责: 定义Modifier结构体，声明函数指针接口                        │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│  Model层 (C++)                                                   │
│  frameworks/core/components_ng/pattern/rich_editor/             │
│  ├── rich_editor_model.h                                        │
│  ├── rich_editor_model_ng.h                                     │
│  └── rich_editor_model_ng.cpp                                   │
│  职责: 业务逻辑实现，操作Pattern/EventHub                        │
└─────────────────────────────────────────────────────────────────┘
```

---

## 需要适配的文件清单

新增接口需要按顺序适配以下文件：

| 序号 | 文件路径 | 作用 | 必须修改 |
|------|----------|------|----------|
| 1 | `frameworks/bridge/declarative_frontend/ark_component/components/arkricheditor.js` | JS层接口入口 | ✓ |
| 2 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkRichEditor.ts` | ArkTS类型定义 | ✓ |
| 3 | `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.h` | Bridge层头文件 | ✓ |
| 4 | `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp` | Bridge层实现 | ✓ |
| 5 | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp` | Modifier注册 | ✓ |
| 6 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h` | Model接口定义 | ✓ |
| 7 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h` | ModelNG接口定义 | ✓ |
| 8 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` | ModelNG实现 | ✓ |
| 9 | `frameworks/core/interfaces/arkoala/arkoala_api.h` | ArkUI Modifier结构体 | ✓ |
| 10 | `frameworks/core/interfaces/cjui/cjui_api.h` | CJUI Modifier结构体 | 可选(如需Cangjie支持) |
| 11 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h` | Pattern层头文件 | 可选(如需Pattern存储) |
| 12 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` | Pattern层实现 | 可选(如需Pattern存储) |

---

## 各层适配详解

### 1. JS层 (arkricheditor.js)

**文件位置**: `frameworks/bridge/declarative_frontend/ark_component/components/arkricheditor.js`

**职责**: 定义接口入口，收集参数并调用Native Bridge

**适配模式**:

```javascript
// 属性接口示例
newProperty: function (value) {
    return this.newPropertyAttr(value);
},

newPropertyAttr: function (value) {
    var attrValue = value;
    if (attrValue === undefined || attrValue === null) {
        attrValue = null;  // 重置时传null
    }
    this.__newProperty = attrValue;
    return this;
},
```

**关键点**:
- 属性接口通常返回`this`以支持链式调用
- 需要在组件初始化时处理属性值传递
- 重置接口需要传递null或undefined

### 2. ArkTS层 (ArkRichEditor.ts)

**文件位置**: `frameworks/bridge/declarative_frontend/ark_component/src/ArkRichEditor.ts`

**职责**: 定义ArkTS类型接口，调用Bridge层函数

**适配模式**:

```typescript
// 属性接口
newProperty(value: Type): RichEditor {
    // 调用Bridge层函数
    ArkUIRichEditorBridge.SetNewProperty(this.nativeNode, value);
    return this;
}

// 重置接口
resetNewProperty(): RichEditor {
    ArkUIRichEditorBridge.ResetNewProperty(this.nativeNode);
    return this;
}
```

**关键点**:
- 需要定义正确的TypeScript类型
- 通过`nativeNode`传递节点句柄
- Bridge函数命名遵循`Set/Reset/Get`前缀规范

### 3. Bridge头文件 (arkts_native_rich_editor_bridge.h)

**文件位置**: `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.h`

**职责**: 声明Bridge层函数，供ArkTS层调用

**适配模式**:

```cpp
// 在RichEditorBridge类中添加静态方法声明
class RichEditorBridge {
public:
    static ArkUINativeModuleValue SetNewProperty(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetNewProperty(ArkUIRuntimeCallInfo* runtimeCallInfo);
    // 如果是Getter接口
    static ArkUINativeModuleValue GetNewProperty(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
```

**关键点**:
- 函数签名统一使用`ArkUINativeModuleValue`返回类型
- 参数统一为`ArkUIRuntimeCallInfo* runtimeCallInfo`
- 命名遵循`Set/Reset/Get`前缀

### 4. Bridge实现文件 (arkts_native_rich_editor_bridge.cpp)

**文件位置**: `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp`

**职责**: 解析参数，调用Native Modifier函数

**适配模式**:

```cpp
ArkUINativeModuleValue RichEditorBridge::SetNewProperty(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    // 1. 获取第一个参数（节点句柄）
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, 
                    panda::JSValueRef::Undefined(vm));
    
    // 2. 获取实际参数值
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    
    // 3. 参数解析（根据参数类型选择合适的解析方法）
    // 示例：解析整数
    if (!valueArg->IsNumber(vm)) {
        // 参数无效时的处理
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUI_Int32 value = valueArg->Int32Value(vm);
    
    // 4. 获取Modifier并调用Native函数
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->setNewProperty(nativeNode, value);
    
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetNewProperty(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    
    nodeModifiers->getRichEditorModifier()->resetNewProperty(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
```

**注册函数到RegisterRichEditorAttributes**:

在 `RegisterRichEditorAttributes` 方法中，需要将新增接口注册到 `functionNames` 和 `functionValues` 数组：

```cpp
void RichEditorBridge::RegisterRichEditorAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    const char* functionNames[] = {
        // ... 现有接口
        "setOrphanCharOptimization", "resetOrphanCharOptimization",
        // 新增接口添加到末尾
        "setHorizontalScrolling", "resetHorizontalScrolling"
    };

    Local<JSValueRef> functionValues[] = {
        // ... 现有接口对应的函数
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOrphanCharOptimization),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOrphanCharOptimization),
        // 新增接口对应的函数添加到末尾
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetHorizontalScrolling),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetHorizontalScrolling),
    };
}
```

**重要规范**:
- **新增接口必须添加到数组末尾**，不要插入到中间位置
- `functionNames` 和 `functionValues` 数组必须保持一一对应关系
- 数组顺序决定了接口的注册顺序，插入中间可能导致已有接口索引变化
- 添加到末尾可以避免破坏现有接口的稳定性

**参数解析常用方法**:

| 参数类型 | 解析方法 | 示例 |
|----------|----------|------|
| 整数 | `valueArg->Int32Value(vm)` | `ArkUI_Int32 value = valueArg->Int32Value(vm);` |
| 浮点数 | `valueArg->NumberValue(vm)` | `ArkUI_Float64 value = valueArg->NumberValue(vm);` |
| 字符串 | `valueArg->ToString(vm)` | `auto str = valueArg->ToString(vm);` |
| 颜色 | `ArkTSUtils::ParseJsColorAlpha()` | `ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color);` |
| 数组 | `panda::ArrayRef::GetValueAt()` | `auto value = panda::ArrayRef::GetValueAt(vm, array, i);` |
| 对象 | `valueArg->ToObject(vm)` | `auto obj = valueArg->ToObject(vm);` |
| 函数 | `valueArg->IsFunction(vm)` | `panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);` |

### 5. Dynamic Modifier (rich_editor_dynamic_modifier.cpp)

**文件位置**: `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp`

**职责**: 实现Native函数，注册到Modifier结构体

**适配模式**:

```cpp
// 1. 实现Set函数
void SetNewProperty(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetNewProperty(frameNode, value);
}

// 2. 实现Reset函数
void ResetNewProperty(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetNewProperty(frameNode);
}

// 3. 实现Get函数（如果需要）
ArkUI_Int32 GetNewProperty(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return RichEditorModelNG::GetNewProperty(frameNode);
}

// 4. 在GetRichEditorDynamicModifier()中注册
const ArkUIRichEditorModifier* GetRichEditorDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIRichEditorModifier modifier = {
        // ... 其他接口
        .setNewProperty = SetNewProperty,
        .resetNewProperty = ResetNewProperty,
        .getNewProperty = GetNewProperty,
        // ... 
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
```

**关键点**:
- 函数命名遵循`Set/Reset/Get`前缀
- 使用`CHECK_NULL_VOID`/`CHECK_NULL_RETURN`进行空指针检查
- 通过`reinterpret_cast<FrameNode*>(node)`获取FrameNode
- 最终调用`RichEditorModelNG`的静态方法

### 6. API定义层 (arkoala_api.h)

**文件位置**: `frameworks/core/interfaces/arkoala/arkoala_api.h`

**职责**: 定义`ArkUIRichEditorModifier`结构体中的函数指针

**适配模式**:

```cpp
struct ArkUIRichEditorModifier {
    // ... 其他接口
    
    // 新增接口声明
    void (*setNewProperty)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetNewProperty)(ArkUINodeHandle node);
    ArkUI_Int32 (*getNewProperty)(ArkUINodeHandle node);
    
    // ...
};
```

**关键点**:
- 函数指针命名与实现函数一致
- 参数类型使用ArkUI基础类型（`ArkUI_Int32`, `ArkUI_Uint32`, `ArkUI_Bool`等）
- 需要在结构体末尾的`CHECK_INITIALIZED_FIELDS_END`之前添加

### 7. CJUI API定义 (cjui_api.h)

**文件位置**: `frameworks/core/interfaces/cjui/cjui_api.h`

**职责**: 为Cangjie语言定义Modifier结构体（可选）

**适配模式**:

```cpp
struct CJUIRichEditorModifier {
    // ... 其他接口
    
    // 新增接口声明（仅包含Cangjie需要的接口）
    void (*setNewProperty)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetNewProperty)(ArkUINodeHandle node);
    ArkUI_Int32 (*getNewProperty)(ArkUINodeHandle node);
    
    // ...
};
```

**关键点**:
- CJUI通常只包含部分常用接口
- 根据实际需求决定是否添加

### 8. Model层 (rich_editor_model.h / rich_editor_model_ng.h/cpp)

**文件位置**: 
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h`
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h`
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp`

**职责**: 实现业务逻辑，操作Pattern/EventHub/LayoutProperty

**适配模式**:

```cpp
// rich_editor_model.h - 定义接口
class RichEditorModel : public Model {
public:
    virtual void SetNewProperty(const RefPtr<FrameNode>& frameNode, int32_t value) = 0;
    virtual void ResetNewProperty(const RefPtr<FrameNode>& frameNode) = 0;
    virtual int32_t GetNewProperty(const RefPtr<FrameNode>& frameNode) = 0;
};

// rich_editor_model_ng.h - ModelNG声明
class RichEditorModelNG : public RichEditorModel {
public:
    static void SetNewProperty(FrameNode* frameNode, int32_t value);
    static void ResetNewProperty(FrameNode* frameNode);
    static int32_t GetNewProperty(FrameNode* frameNode);
};

// rich_editor_model_ng.cpp - ModelNG实现
void RichEditorModelNG::SetNewProperty(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNewProperty(value);
}

void RichEditorModelNG::ResetNewProperty(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetNewProperty();  // 重置为默认值
}

int32_t RichEditorModelNG::GetNewProperty(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_VALUE);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, DEFAULT_VALUE);
    return pattern->GetNewProperty();
}
```

**关键点**:
- Model层方法通常为静态方法
- 通过`frameNode->GetPattern<RichEditorPattern>()`获取Pattern
- 根据接口类型选择操作对象：
  - 属性类: 操作Pattern或LayoutProperty/PaintProperty
  - 事件类: 操作EventHub
  - 样式类: 操作RenderContext

### 9. Pattern层 (rich_editor_pattern.h/cpp)

**文件位置**: 
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h`
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp`

**职责**: 实现核心业务逻辑，存储属性状态

**适配模式（不需要LayoutProperty的接口）**:

对于不需要添加到LayoutProperty的接口，直接在Pattern层实现：

```cpp
// rich_editor_pattern.h - 添加成员变量和方法声明
class RichEditorPattern : public TextPattern, public ScrollablePattern {
private:
    bool isHorizontalScrollingEnabled_ = false;
    
public:
    void SetHorizontalScrolling(bool isEnabled);
    bool GetHorizontalScrolling();
};

// rich_editor_pattern.cpp - 实现方法
void RichEditorPattern::SetHorizontalScrolling(bool isEnabled)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setHorizontalScrolling=%{public}d", isEnabled);
    if (isHorizontalScrollingEnabled_ == isEnabled) {
        return;
    }
    isHorizontalScrollingEnabled_ = isEnabled;
    // 触发相关逻辑更新
    InitScrollablePattern();
}

bool RichEditorPattern::GetHorizontalScrolling()
{
    return isHorizontalScrollingEnabled_;
}
```

**关键点**:
- 成员变量命名遵循`isXxxEnabled_`或`xxxEnabled_`格式
- Set方法中检查值是否变化，避免重复触发
- 值变化后调用相关更新函数（如`InitScrollablePattern()`）
- 使用TAG_LOGI记录日志便于调试

**与LayoutProperty接口的区别**:

| 特性 | LayoutProperty接口 | Pattern直接存储 |
|------|-------------------|----------------|
| 属性持久化 | 支持属性继承和序列化 | 仅运行时状态 |
| 布局影响 | 触发重新测量/布局 | 可按需触发更新 |
| 适用场景 | 需要影响布局的属性 | 运行时行为控制 |
| 示例 | SingleLine, MaxLength | HorizontalScrolling, EnableHapticFeedback |

---

## 参数解析规范

### 基础类型参数

```cpp
// 整数
Local<JSValueRef> intArg = runtimeCallInfo->GetCallArgRef(NUM_1);
if (intArg->IsInt(vm)) {
    int32_t value = intArg->Int32Value(vm);
}

// 浮点数
Local<JSValueRef> floatArg = runtimeCallInfo->GetCallArgRef(NUM_1);
if (floatArg->IsNumber(vm)) {
    double value = floatArg->NumberValue(vm);
}

// 字符串
Local<JSValueRef> strArg = runtimeCallInfo->GetCallArgRef(NUM_1);
if (strArg->IsString(vm)) {
    auto str = strArg->ToString(vm);
    std::string value = str->ToString(vm);
}

// 颜色
Color color;
Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color);
```

### 数组参数

```cpp
Local<JSValueRef> arrayArg = runtimeCallInfo->GetCallArgRef(NUM_1);
if (!arrayArg->IsArray(vm)) {
    return panda::JSValueRef::Undefined(vm);
}

auto array = panda::Local<panda::ArrayRef>(arrayArg);
auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));

std::vector<int32_t> values;
for (uint32_t i = 0; i < length; i++) {
    auto value = panda::ArrayRef::GetValueAt(vm, array, i);
    if (value->IsInt(vm)) {
        values.push_back(value->Int32Value(vm));
    }
}
```

### 对象参数

```cpp
Local<JSValueRef> objArg = runtimeCallInfo->GetCallArgRef(NUM_1);
if (!objArg->IsObject(vm)) {
    return panda::JSValueRef::Undefined(vm);
}

auto obj = objArg->ToObject(vm);

// 获取对象属性
auto propValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "propertyName"));
if (propValue->IsInt(vm)) {
    int32_t value = propValue->Int32Value(vm);
}
```

### Dimension参数

```cpp
Local<JSValueRef> dimArg = runtimeCallInfo->GetCallArgRef(NUM_1);
CalcDimension dimension;
if (ArkTSUtils::ParseJsDimension(vm, dimArg, dimension)) {
    // dimension已解析成功
}
```

---

## 事件回调处理

### 事件接口特点

事件接口需要处理回调函数，将Native事件传递回ArkTS层。

### 事件接口适配模式

```cpp
// Bridge层实现
ArkUINativeModuleValue RichEditorBridge::SetOnNewEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, 
                    panda::JSValueRef::Undefined(vm));
    
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    
    // 检查回调是否有效
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            auto nodeModifiers = GetArkUINodeModifiers();
            nodeModifiers->getRichEditorModifier()->resetOnNewEvent(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : 
        reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    
    // 创建回调函数
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const EventInfo&)> callback = 
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const EventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        
        // 构造回调参数对象
        Local<panda::JSValueRef> params[NUM_1] = {
            CreateEventInfoObject(vm, info)
        };
        
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    
    auto nodeModifiers = GetArkUINodeModifiers();
    nodeModifiers->getRichEditorModifier()->setOnNewEvent(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    
    return panda::JSValueRef::Undefined(vm);
}
```

### NAPI事件处理（用于C API）

```cpp
// Dynamic Modifier中的NAPI版本
void SetRichEditorNapiOnNewEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    auto onNewEvent = [extraParam](const EventInfo& info) {
        ArkUINodeEvent event = CreateArkUINodeEvent(COMPONENT_ASYNC_EVENT, extraParam);
        event.componentAsyncEvent.subKind = ON_RICH_EDITOR_ON_NEW_EVENT;
        event.componentAsyncEvent.data[0].i32 = info.value1;
        event.componentAsyncEvent.data[1].i32 = info.value2;
        SendArkUISyncEvent(&event);
    };
    
    RichEditorModelNG::SetOnNewEvent(frameNode, std::move(onNewEvent));
}
```

---

## 完整示例：新增一个属性接口

假设需要新增一个`newFeature(value: number)`属性接口：

### Step 1: JS层 (arkricheditor.js)

```javascript
newFeature: function (value) {
    return this.newFeatureAttr(value);
},

newFeatureAttr: function (value) {
    var attrValue = value;
    this.__newFeature = attrValue;
    return this;
},
```

### Step 2: ArkTS层 (ArkRichEditor.ts)

```typescript
newFeature(value: number): RichEditor {
    ArkUIRichEditorBridge.SetNewFeature(this.nativeNode, value);
    return this;
}

resetNewFeature(): RichEditor {
    ArkUIRichEditorBridge.ResetNewFeature(this.nativeNode);
    return this;
}
```

### Step 3: Bridge头文件 (arkts_native_rich_editor_bridge.h)

```cpp
static ArkUINativeModuleValue SetNewFeature(ArkUIRuntimeCallInfo* runtimeCallInfo);
static ArkUINativeModuleValue ResetNewFeature(ArkUIRuntimeCallInfo* runtimeCallInfo);
```

### Step 4: Bridge实现 (arkts_native_rich_editor_bridge.cpp)

```cpp
ArkUINativeModuleValue RichEditorBridge::SetNewFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, 
                    panda::JSValueRef::Undefined(vm));
    
    if (!valueArg->IsNumber(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUI_Int32 value = valueArg->Int32Value(vm);
    
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->setNewFeature(nativeNode, value);
    
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetNewFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    
    nodeModifiers->getRichEditorModifier()->resetNewFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
```

### Step 5: Dynamic Modifier (rich_editor_dynamic_modifier.cpp)

```cpp
void SetNewFeature(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetNewFeature(frameNode, value);
}

void ResetNewFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::ResetNewFeature(frameNode);
}

// 在GetRichEditorDynamicModifier()中注册
const ArkUIRichEditorModifier* GetRichEditorDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIRichEditorModifier modifier = {
        // ... 其他接口
        .setNewFeature = SetNewFeature,
        .resetNewFeature = ResetNewFeature,
        // ...
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
```

### Step 6: API定义 (arkoala_api.h)

```cpp
struct ArkUIRichEditorModifier {
    // ... 其他接口
    void (*setNewFeature)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetNewFeature)(ArkUINodeHandle node);
    // ...
};
```

### Step 7: Model层

```cpp
// rich_editor_model.h
virtual void SetNewFeature(const RefPtr<FrameNode>& frameNode, int32_t value) = 0;
virtual void ResetNewFeature(const RefPtr<FrameNode>& frameNode) = 0;

// rich_editor_model_ng.h
static void SetNewFeature(FrameNode* frameNode, int32_t value);
static void ResetNewFeature(FrameNode* frameNode);

// rich_editor_model_ng.cpp
void RichEditorModelNG::SetNewFeature(FrameNode* frameNode, int32_t value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNewFeature(value);
}

void RichEditorModelNG::ResetNewFeature(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetNewFeature();
}
```

---

## 完整示例：新增一个事件接口

假设需要新增一个`onNewEvent(callback: (info: EventInfo) => void)`事件接口：

### Step 1: JS层 (arkricheditor.js)

```javascript
onNewEvent: function (callback) {
    return this.onNewEventEvent(callback);
},

onNewEventEvent: function (callback) {
    if (callback === undefined || callback === null) {
        this.__onNewEvent = null;
    } else {
        this.__onNewEvent = callback;
    }
    return this;
},
```

### Step 2: ArkTS层 (ArkRichEditor.ts)

```typescript
onNewEvent(callback: (info: EventInfo) => void): RichEditor {
    ArkUIRichEditorBridge.SetOnNewEvent(this.nativeNode, callback);
    return this;
}
```

### Step 3: Bridge头文件

```cpp
static ArkUINativeModuleValue SetOnNewEvent(ArkUIRuntimeCallInfo* runtimeCallInfo);
static ArkUINativeModuleValue ResetOnNewEvent(ArkUIRuntimeCallInfo* runtimeCallInfo);
```

### Step 4: Bridge实现

```cpp
ArkUINativeModuleValue RichEditorBridge::SetOnNewEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, 
                    panda::JSValueRef::Undefined(vm));
    
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            auto nodeModifiers = GetArkUINodeModifiers();
            nodeModifiers->getRichEditorModifier()->resetOnNewEvent(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    
    auto frameNode = isJsView ?
        ViewStackProcessor::GetInstance()->GetMainFrameNode() : 
        reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const NewEventInfo&)> callback = 
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const NewEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        
        Local<panda::JSValueRef> params[NUM_1] = {
            CreateNewEventInfoObject(vm, info)
        };
        
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    
    auto nodeModifiers = GetArkUINodeModifiers();
    nodeModifiers->getRichEditorModifier()->setOnNewEvent(
        nativeNode, reinterpret_cast<void*>(&callback), isJsView);
    
    return panda::JSValueRef::Undefined(vm);
}
```

### Step 5: Dynamic Modifier

```cpp
void SetOnNewEvent(ArkUINodeHandle node, void* callback, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onNewEvent = reinterpret_cast<std::function<void(const NewEventInfo&)>*>(callback);
        RichEditorModelNG::SetOnNewEvent(frameNode, std::move(*onNewEvent), isJsView);
    } else {
        RichEditorModelNG::SetOnNewEvent(frameNode, nullptr, isJsView);
    }
}

void ResetOnNewEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnNewEvent(frameNode, nullptr);
}
```

### Step 6: API定义

```cpp
struct ArkUIRichEditorModifier {
    // ...
    void (*setOnNewEvent)(ArkUINodeHandle node, void* callback, bool isJsView);
    void (*resetOnNewEvent)(ArkUINodeHandle node);
    // ...
};
```

### Step 7: Model层

```cpp
// rich_editor_model_ng.h
static void SetOnNewEvent(FrameNode* frameNode, 
    std::function<void(const NewEventInfo&)>&& callback, bool isJsView = false);

// rich_editor_model_ng.cpp
void RichEditorModelNG::SetOnNewEvent(
    FrameNode* frameNode, std::function<void(const NewEventInfo&)>&& callback, bool isJsView)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNewEvent(std::move(callback));
}
```

---

## 常见问题与注意事项

### 1. 空指针检查

所有层级都需要进行空指针检查：

```cpp
CHECK_NULL_VOID(frameNode);       // void返回
CHECK_NULL_RETURN(frameNode, defaultValue);  // 有返回值
```

### 2. isJsView判断

区分声明式调用和命令式调用：

```cpp
bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
auto frameNode = isJsView ?
    ViewStackProcessor::GetInstance()->GetMainFrameNode() : 
    reinterpret_cast<FrameNode*>(nativeNode);
```

### 3. 资源对象处理

如果接口支持资源引用（如颜色、尺寸），需要处理资源对象：

```cpp
void SetNewProperty(ArkUINodeHandle node, ArkUI_Int32 value, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    // 注册资源对象以支持配置变更
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        resObj ? pattern->RegisterResource<int32_t>("newProperty", resObj, value) 
               : pattern->UnRegisterResource("newProperty");
    }
    
    RichEditorModelNG::SetNewProperty(frameNode, value);
}
```

### 4. 默认值处理

Reset接口需要设置合理的默认值：

```cpp
void ResetNewProperty(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    
    // 从主题获取默认值
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    
    auto defaultValue = theme->GetNewPropertyDefaultValue();
    RichEditorModelNG::SetNewProperty(frameNode, defaultValue);
}
```

### 5. Modifier结构体顺序

在`CHECK_INITIALIZED_FIELDS_BEGIN()`和`CHECK_INITIALIZED_FIELDS_END()`之间添加新接口，顺序需要与结构体定义一致。

### 6. 编译验证

新增接口后需要验证编译：

```bash
# 编译ace_engine
./build.sh --product-name rk3568 --build-target ace_engine

# 编译单元测试
./build.sh --product-name rk3568 --build-target unittest
```

---

## 附录：相关文件路径汇总

| 文件 | 完整路径 |
|------|----------|
| arkricheditor.js | `frameworks/bridge/declarative_frontend/ark_component/components/arkricheditor.js` |
| ArkRichEditor.ts | `frameworks/bridge/declarative_frontend/ark_component/src/ArkRichEditor.ts` |
| Bridge头文件 | `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.h` |
| Bridge实现 | `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp` |
| Model接口 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h` |
| ModelNG头文件 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h` |
| ModelNG实现 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` |
| ArkUI API | `frameworks/core/interfaces/arkoala/arkoala_api.h` |
| CJUI API | `frameworks/core/interfaces/cjui/cjui_api.h` |
| Pattern头文件 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h` |
| Pattern实现 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` |