# Modifier API 开发指南

本文档详细说明了如何为 ACE Engine 组件新增 Modifier API，包括完整的开发流程、技术约束和参考实现。

## 目录

- [技术约束与开发规则](#技术约束与开发规则)
- [开发流程](#开发流程)
- [参考实现](#参考实现)
- [完整示例](#完整示例)

---

## 技术约束与开发规则

在开发 Modifier API 时，必须遵守以下分层架构和技术约束。

### 1. JS 适配层 (JavaScript Adapter Layer)

#### 代码位置

- **arkComponent.js**: `frameworks/bridge/declarative_frontend/engine/arkComponent.js`
- **TypeScript 文件**: `frameworks/bridge/declarative_frontend/ark_component/src/`

#### 组件与类型对应关系

| 组件名称 | arkComponent.js 类名 | TypeScript 文件 | TypeScript 类名 |
|---------|---------------------|----------------|----------------|
| TextArea | `ArkTextAreaComponent` | `ArkTextArea.ts` | `ArkTextAreaComponent` |
| Text | `ArkTextComponent` | `ArkText.ts` | `ArkTextComponent` |
| TextInput | `ArkTextInputComponent` | `ArkTextInput.ts` | `ArkTextInputComponent` |
| Search | `ArkSearchComponent` | `ArkSearch.ts` | `ArkSearchComponent` |

#### 实现要点

1. **Modifier 类定义**：创建继承自 `ModifierWithKey` 的 Modifier 类
2. **方法实现**：在组件类中添加 modifier 方法
3. **applyPeer 方法**：调用 C++ 适配层暴露的方法
4. **参数校验**：处理空值、undefined 等边界情况

### 2. C++ 适配层 (C++ Adapter Layer)

#### 代码位置

`frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/`

#### 组件与文件对应关系

| 组件名称 | Bridge 文件 |
|---------|------------|
| TextInput | `arkts_native_text_input_bridge.cpp` |
| TextArea | `arkts_native_text_area_bridge.cpp` |
| Search | `arkts_native_text_search_bridge.cpp` |

#### 实现要点

1. **Set 方法**：设置属性值，需要处理参数校验
2. **Reset 方法**：重置属性到默认值
3. **错误处理**：使用 `CHECK_NULL_RETURN` 等宏进行空指针检查
4. **类型转换**：正确处理 JavaScript 到 C++ 的类型转换

### 3. API 注册层 (API Registration Layer)

#### 代码位置

`frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp`

#### 实现要点

1. 在组件的 ObjectRef 中注册 Set 和 Reset 方法
2. 使用 `panda::FunctionRef::New` 绑定方法
3. 方法命名遵循驼峰命名规范（如 `setHorizontalScrolling`）

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

### 5. Native Modifier 层 (Native Modifier Layer)

#### 代码位置

`frameworks/core/interfaces/native/node/node_XXX_modifier.cpp`

#### 实现要点

1. 实现桥接函数，转换 ArkUI 类型和 C++ 类型
2. 在 Modifier 结构体中添加函数指针
3. 同时更新 ArkUI 和 CJUI 两个 API

### 6. API 头文件层 (API Header Layer)

#### 代码位置

- ArkUI API: `frameworks/core/interfaces/arkoala/arkoala_api.h`
- CJUI API: `frameworks/core/interfaces/cjui/cjui_api.h`

#### 实现要点

1. 在对应的 Modifier 结构体中添加函数指针声明
2. 函数签名必须与实现完全匹配
3. 同时更新 ArkUI 和 CJUI 两个 API

---

## 开发流程

### 步骤 1: 在 arkComponent.js 中添加方法和 Modifier 类

**位置**: `frameworks/bridge/declarative_frontend/engine/arkComponent.js`

**任务**:
1. 创建 `XXXModifier` 类（继承自 `ModifierWithKey`）
2. 在组件类中添加 `xxx(value)` 方法

**代码模板**:

```javascript
// 1. 定义 Modifier 类
class TextAreaHorizontalScrollingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetHorizontalScrolling(node);
    } else {
      getUINativeModule().textArea.setHorizontalScrolling(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaHorizontalScrollingModifier.identity = Symbol('textAreaHorizontalScrolling');

// 2. 在组件类中添加方法
class ArkTextAreaComponent extends ArkComponent {
  // ... 其他方法
  horizontalScrolling(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaHorizontalScrollingModifier.identity, TextAreaHorizontalScrollingModifier, value);
    return this;
  }
}
```

### 步骤 2: 在 TypeScript 文件中添加方法和 Modifier 类

**位置**: `frameworks/bridge/declarative_frontend/ark_component/src/ArkTextArea.ts`

**任务**:
1. 创建 `XXXModifier` 类（使用 TypeScript 语法）
2. 在组件类中添加 `xxx(value)` 方法（带类型注解）

**代码模板**:

```typescript
// 1. 定义 Modifier 类
class TextAreaHorizontalScrollingModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaHorizontalScrolling');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textArea.resetHorizontalScrolling(node);
    } else {
      getUINativeModule().textArea.setHorizontalScrolling(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// 2. 在组件类中添加方法
class ArkTextAreaComponent extends ArkComponent {
  // ... 其他方法
  horizontalScrolling(value: boolean): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaHorizontalScrollingModifier.identity, TextAreaHorizontalScrollingModifier, value);
    return this;
  }
}
```

### 步骤 3: 在 C++ 适配层添加方法实现

**位置**:
- 头文件: `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_area_bridge.h`
- 实现文件: `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_area_bridge.cpp`

**任务**:
1. 在头文件中声明静态方法
2. 在实现文件中实现 Set 和 Reset 方法

**代码模板**:

```cpp
// .h 文件 - 方法声明
class TextAreaBridge {
    // ... 其他方法
    static ArkUINativeModuleValue SetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo);
};

// .cpp 文件 - 方法实现
ArkUINativeModuleValue TextAreaBridge::SetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> horizontalScrollingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    // 参数校验：处理 null、undefined 或类型不匹配
    if (horizontalScrollingArg->IsNull() || horizontalScrollingArg->IsUndefined() ||
        !horizontalScrollingArg->IsBoolean()) {
        GetArkUINodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    uint32_t horizontalScrolling = horizontalScrollingArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextAreaModifier()->setHorizontalScrolling(nativeNode, horizontalScrolling);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextAreaBridge::ResetHorizontalScrolling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextAreaModifier()->resetHorizontalScrolling(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
```

### 步骤 4: 在 API 注册文件中注册方法

**位置**: `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp`

**任务**:
在 textArea 对象中注册 Set 和 Reset 方法

**代码模板**:

```cpp
// 在 GetArkUINativeModule 或类似函数中
auto textArea = panda::ObjectRef::New(vm);

// 在相关方法附近添加注册
textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHorizontalScrolling"),
    panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHorizontalScrolling));
textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHorizontalScrolling"),
    panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHorizontalScrolling));
```

### 步骤 5: 在 Model 层添加属性设置方法

**位置**:
- 头文件: `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.h`
- 实现文件: `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp`

**任务**:
1. 在头文件中声明静态方法（带 FrameNode 参数）
2. 在实现文件中实现这些方法

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
    pattern->ResetHorizontalScrolling();
}
```

### 步骤 6: 在 Native Modifier 层添加桥接实现

**位置**: `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp`

**任务**:
1. 实现桥接函数（转换类型）
2. 在 Modifier 结构体中添加函数指针

**代码模板**:

```cpp
// 1. 实现桥接函数
void SetHorizontalScrolling(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetHorizontalScrolling(frameNode, static_cast<bool>(value));
}

ArkUI_Int32 GetHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetHorizontalScrolling(frameNode));
}

void ResetHorizontalScrolling(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ResetHorizontalScrolling(frameNode);
}

// 2. 在结构体中添加函数指针
namespace NodeModifier {
const ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const ArkUITextAreaModifier modifier = {
        // ... 其他函数指针
        .setHorizontalScrolling = SetHorizontalScrolling,
        .getHorizontalScrolling = GetHorizontalScrolling,
        .resetHorizontalScrolling = ResetHorizontalScrolling,
        // ... 其他函数指针
    };
    return &modifier;
}

const CJUITextAreaModifier* GetCJUITextAreaModifier()
{
    static const CJUITextAreaModifier modifier = {
        // ... 其他函数指针
        .setHorizontalScrolling = SetHorizontalScrolling,
        .getHorizontalScrolling = GetHorizontalScrolling,
        .resetHorizontalScrolling = ResetHorizontalScrolling,
        // ... 其他函数指针
    };
    return &modifier;
}
}
```

### 步骤 7: 在 API 头文件中添加函数指针声明

**位置**:
- ArkUI API: `frameworks/core/interfaces/arkoala/arkoala_api.h`
- CJUI API: `frameworks/core/interfaces/cjui/cjui_api.h`

**任务**:
在对应的 Modifier 结构体中添加函数指针声明

**代码模板**:

```cpp
// arkoala_api.h
struct ArkUITextAreaModifier {
    // ... 其他函数指针
    void (*setHorizontalScrolling)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetHorizontalScrolling)(ArkUINodeHandle node);
    ArkUI_Int32 (*getHorizontalScrolling)(ArkUINodeHandle node);
    // ... 其他函数指针
};

// cjui_api.h
struct CJUITextAreaModifier {
    // ... 其他函数指针
    void (*setHorizontalScrolling)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetHorizontalScrolling)(ArkUINodeHandle node);
    ArkUI_Int32 (*getHorizontalScrolling)(ArkUINodeHandle node);
    // ... 其他函数指针
};
```

---

## 参考实现

### Git 提交参考

查看提交 `e44d10a171cccba6af61fee8917b72770a02e3c0`，了解 `enableSelectedDataDetector` 接口的完整实现。

### 参考命令

```bash
git show e44d10a171cccba6af61fee8917b72770a02e3c0 --stat
git show e44d10a171cccba6af61fee8917b72770a02e3c0 -- <文件路径>
```

### 关键实现文件

该提交涉及的主要文件：

1. **arkComponent.js** - Modifier 类和组件方法
2. **arkts_native_text_area_bridge.cpp** - C++ 适配层实现
3. **text_field_model_ng.cpp** - Model 层实现
4. **node_text_area_modifier.cpp** - Native Modifier 层实现
5. **arkoala_api.h / cjui_api.h** - API 头文件声明

---

## 完整示例

### 示例: 为 TextArea 添加 `horizontalScrolling` 属性

#### 需求描述

为 TextArea 组件添加 `horizontalScrolling` modifier API，用于控制是否启用横向滚动能力。

#### 类型定义

- **方法名**: `horizontalScrolling`
- **参数类型**: `boolean`
- **默认值**: `false`

#### 实现清单

| 层级 | 文件 | 添加内容 |
|-----|------|---------|
| JS 适配层 | arkComponent.js | `TextAreaHorizontalScrollingModifier` 类, `horizontalScrolling()` 方法 |
| TypeScript | ArkTextArea.ts | `TextAreaHorizontalScrollingModifier` 类, `horizontalScrolling()` 方法 |
| C++ 适配层 | arkts_native_text_area_bridge.h | 方法声明 |
| C++ 适配层 | arkts_native_text_area_bridge.cpp | `SetHorizontalScrolling()`, `ResetHorizontalScrolling()` 实现 |
| API 注册 | arkts_native_api_impl_bridge.cpp | 注册 `setHorizontalScrolling`, `resetHorizontalScrolling` |
| Model 层 | text_field_model_ng.h | 方法声明 |
| Model 层 | text_field_model_ng.cpp | `SetHorizontalScrolling()`, `GetHorizontalScrolling()`, `ResetHorizontalScrolling()` 实现 |
| Native Modifier | node_text_area_modifier.cpp | 桥接函数和结构体初始化 |
| API 头文件 | arkoala_api.h | 函数指针声明 |
| API 头文件 | cjui_api.h | 函数指针声明 |

#### 使用示例

```typescript
// 启用横向滚动
TextArea()
  .horizontalScrolling(true)

// 禁用横向滚动
TextArea()
  .horizontalScrolling(false)
```

---

## 开发注意事项

### 1. 顺序要求

**必须严格按照步骤 1-7 的顺序实现**，否则会导致编译错误或运行时崩溃。

### 2. 类型安全

- JavaScript 到 C++ 的类型转换必须进行参数校验
- 使用 `CHECK_NULL_RETURN`、`CHECK_NULL_VOID` 等宏进行空指针检查
- 布尔值在 JavaScript 和 C++ 之间的转换需要注意（使用 `Uint32Value`）

### 3. 命名规范

| 层级 | Set 方法命名 | Reset 方法命名 | Get 方法命名（可选） |
|-----|------------|--------------|-------------------|
| JavaScript | `setXxx` | `resetXxx` | - |
| C++ Bridge | `SetXxx` | `ResetXxx` | - |
| Model | `SetXxx` | `ResetXxx` | `GetXxx` |
| Native Modifier | `SetXxx` | `ResetXxx` | `GetXxx` |

### 4. 边界情况处理

- 处理 `null`、`undefined` 参数
- 处理类型不匹配的情况（如期望 boolean 但传了 number）
- 在无效参数时调用 Reset 方法

### 5. 代码风格

- 添加详细的注释说明功能
- 遵循项目现有的代码风格
- 保持与现有代码的一致性
- 新增方法追加到同类的末尾处

---

## 常见问题

### Q1: 为什么要同时修改 ArkUI 和 CJUI 两个 API？

A: ArkUI 用于 ArkTS/TypeScript 开发，CJUI 用于 Cangjie 开发。两个 API 需要保持同步。

### Q2: 如果参数类型是复杂对象（如数组、对象）怎么办？

A: 参考 `enableSelectedDataDetector` 的实现，需要解析 JavaScript 对象并转换为 C++ 类型。

### Q3: 是否需要实现 Get 方法？

A: Get 方法是可选的，主要用于 Native API 中获取当前属性值。如果不需要从 C++ 侧获取值，可以不实现。

### Q4: 如何测试新增的 Modifier API？

A:
1. 编写 ArkTS 测试用例
2. 编译并运行测试
3. 验证属性是否正确生效
4. 测试边界情况（null、undefined、类型错误等）

---

## 附录

### 相关目录结构

```
ace_engine/
├── frameworks/
│   ├── bridge/
│   │   └── declarative_frontend/
│   │       ├── engine/
│   │       │   ├── arkComponent.js                    # JS 适配层
│   │       │   └── jsi/nativeModule/
│   │       │       ├── arkts_native_api_impl_bridge.cpp  # API 注册
│   │       │       ├── arkts_native_text_area_bridge.cpp # C++ 适配层
│   │       │       └── ...
│   │       └── ark_component/src/
│   │           ├── ArkTextArea.ts                      # TypeScript 定义
│   │           ├── ArkTextInput.ts
│   │           └── ...
│   └── core/
│       ├── components_ng/pattern/
│       │   ├── text_field/
│       │   │   ├── text_field_model_ng.cpp              # Model 层
│       │   │   └── text_field_model_ng.h
│       │   └── text/
│       │       ├── text_model_ng.cpp
│       │       └── text_model_ng.h
│       └── interfaces/native/node/
│           ├── node_text_area_modifier.cpp               # Native Modifier 层
│           └── ...
├── interfaces/native/
│   ├── native_node.h
│   └── native_type.h
└── frameworks/core/interfaces/
    ├── arkoala/arkoala_api.h                            # ArkUI API 头文件
    └── cjui/cjui_api.h                                  # CJUI API 头文件
```

### 有用的 Git 命令

```bash
# 查看参考提交的文件变更
git show e44d10a171cccba6af61fee8917b72770a02e3c0 --stat

# 查看特定文件的变更
git show e44d10a171cccba6af61fee8917b72770a02e3c0 -- <文件路径>

# 查看当前分支的修改
git diff
git diff <文件路径>
```

---

**文档版本**: v1.0
**最后更新**: 2026-02-05
**维护者**: ACE Engine Team
