# OpenHarmony ArkUI interface/ets 目录知识库

本文档为 Claude Code (claude.ai/code) 提供指导，用于处理 OpenHarmony ArkUI 的 interface/ets 目录代码。

## 概述

**interface/ets** 目录包含 OpenHarmony ArkUI 框架的 ArkTS 接口定义文件，这些文件构成了 ArkTS-Sta（ArkTS 静态模式）与 C++ 实现之间的桥接层。

**核心定位**：
- **ANI (ArkTS Native Interface)**: 类似于 JNI 的桥接机制
- **ArkTS-Sta**: ArkTS 静态模式，是 ArkTS 语言的静态变体，语法类似 TypeScript
- **主要功能**: 桥接 ArkTS-Sta API 到 C++ 实现

**重要说明**：
- `.static.d.ets` 文件是 **ArkTS 接口文件**，不是 TypeScript 接口文件
- ArkTS 是 OpenHarmony 的声明式开发语言，基于 TypeScript 扩展而来
- ArkTS-Sta 是 ArkTS 的静态模式，提供更强的类型安全和性能优化

### 双模式支持

```
┌─────────────────────────────────────────────────────────────────┐
│                    ArkUI 双模式架构                              │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Dynamic Mode (动态模式)        Static Mode (静态模式 - ArkTS-Sta) │
│  ├─ .d.ts 文件                 ├─ .static.d.ets 文件             │
│  ├─ ArkTS 动态模式             ├─ ArkTS 静态模式                │
│  ├─ 运行时类型检查              ├─ 编译时类型检查                 │
│  └─ 灵活性高                   └─ 性能优化                       │
│                                                                 │
│            共享 C++ 实现层 (arkui_ace_engine)                    │
│            ├─ Pattern 层: 业务逻辑                               │
│            ├─ Model 层: 数据模型                                  │
│            └─ ANI Bridge: ArkTS → C++ 桥接                       │
└─────────────────────────────────────────────────────────────────┘
```

## 代码组织

### 仓库结构

```
interface/sdk-js/
├── api/                           # API 声明文件目录
│   ├── @ohos.×.d.ts              # 动态模式 API 声明
│   ├── @ohos.×.static.d.ets      # 静态模式 API 声明 (ArkTS-Sta)
│   ├── arkui/                    # ArkUI 组件 API
│   │   ├── component/            # 组件定义
│   │   │   ├── button.static.d.ets
│   │   │   ├── common.static.d.ets
│   │   │   └── ...
│   │   ├── ButtonModifier.d.ts   # Modifier 定义 (动态)
│   │   ├── ButtonModifier.static.d.ets  # Modifier 定义 (静态)
│   │   └── ...
│   └── ability/                  # 能力 API
│       ├── app/
│       └── ...
└── build-tools/                  # 构建工具
    ├── api_check_plugin/         # API 规范检查
    ├── collect_api/              # API 收集工具
    └── arkui_transformer/        # ArkUI 转换工具
```

### ace_engine 中的 ANI Bridge 实现

```
arkui_ace_engine/
└── frameworks/
    └── bridge/
        └── declarative_frontend/
            └── engine/
                └── jsi/
                    └── nativeModule/
                        ├── arkts_native_api_bridge.h       # ANI 基础设施
                        ├── arkts_native_button_bridge.cpp  # Button 桥接实现
                        ├── arkts_native_stack_bridge.cpp   # Stack 桥接实现
                        └── ...                             # 其他组件桥接
```

## 文件类型说明

### 1. .d.ts 文件 (动态模式)

**用途**: Dynamic ArkTS 的类型声明文件

**示例**:
```typescript
// AttributeUpdater.d.ts
declare type Initializer<T> = () => T;

export declare class AttributeUpdater<T, C = Initializer<T>>
  implements AttributeModifier<T> {

  applyNormalAttribute?(instance: T): void;

  initializeModifier(instance: T): void;

  get attribute(): T | undefined;

  updateConstructorParams: C;

  onComponentChanged(component: T): void;
}
```

**特点**:
- 使用标准 TypeScript 语法
- 运行时进行类型检查
- 灵活性高，兼容性好

### 2. .static.d.ets 文件 (静态模式)

**用途**: ArkTS-Sta 静态模式的 ArkTS 接口定义

**注意**: 这些是 **ArkTS 接口文件**，不是 TypeScript 接口文件

**文件头部**:
```typescript
'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * ...
 */

/**
 * @file
 * @kit ArkUI
 */
```

**示例 - 组件定义**:
```typescript
import { ComponentBuilder } from './builder';
import { ResourceStr, ResourceColor, Length } from './units';

/**
 * Provides a button component.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 */
export declare enum ButtonType {
    /** Capsule button */
    Capsule,
    /** Normal button */
    Normal,
}

/**
 * Defines Button Component.
 *
 * @struct { ButtonAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 */
@Component
declare struct ButtonComponent {
    /**
     * Button type.
     * @type { ButtonType }
     */
    @PropRef
    type: ButtonType;

    /**
     * Button label.
     * @type { ResourceStr }
     */
    label: ResourceStr;

    @Builder
    build(): void;
}
```

**示例 - Modifier 定义**:
```typescript
// ButtonModifier.static.d.ets
'use static'
import { AttributeModifier } from './component/common';
import { ButtonAttribute } from './component/button';

/**
 * Defines Button Modifier
 *
 * @implements { ButtonAttribute, AttributeModifier<ButtonAttribute> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
*/
export declare class ButtonModifier
  implements ButtonAttribute, AttributeModifier<ButtonAttribute> {}
```

**关键语法元素**:

| 语法 | 用途 | 说明 |
|------|------|------|
| `'use static'` | 声明静态模式 | 文件级别指令，标识为静态 ArkTS |
| `@Component` | 组件装饰器 | 标记结构体为 UI 组件 |
| `@PropRef` | 属性引用 | 标记组件属性为响应式引用 |
| `@Builder` | 构建方法 | 标记组件构建函数 |
| `declare struct` | 结构体声明 | ArkTS-Sta 的值类型 |
| `declare enum` | 枚举声明 | 类型安全的枚举 |
| `declare class` | 类声明 | 接口定义 (无实现) |

## ANI 桥接机制

### 架构设计

```
┌─────────────────────────────────────────────────────────────────┐
│                    ANI 桥接调用流程                              │
└─────────────────────────────────────────────────────────────────┘

ArkTS-Sta 代码层
    ↓
Button().type(ButtonType.Capsule)
    ↓
┌─────────────────────────────────────────────────────────────────┐
│  ArkTS 接口层 (interface/ets)                                   │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │  ButtonModifier.static.d.ets                            │    │
│  │  export declare class ButtonModifier                    │    │
│  │    implements ButtonAttribute, AttributeModifier<...> {} │    │
│  └─────────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────────┘
    ↓ (绑定机制)
┌─────────────────────────────────────────────────────────────────┐
│  ANI Bridge 层 (arkui_ace_engine)                               │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │  arkts_native_button_bridge.cpp                         │    │
│  │  ArkUINativeModuleValue SetType(                        │    │
│  │      ArkUIRuntimeCallInfo* runtimeCallInfo)             │    │
│  │  {                                                      │    │
│  │    EcmaVM* vm = runtimeCallInfo->GetVM();               │    │
│  │    Local<JSValueRef> firstArg =                         │    │
│  │      runtimeCallInfo->GetCallArgRef(0);                 │    │
│  │    auto nativeNode =                                    │    │
│  │      nodePtr(firstArg->ToNativePointer(vm)->Value());   │    │
│  │    int32_t type = secondArg->Int32Value(vm);            │    │
│  │    GetArkUINodeModifiers()                              │    │
│  │      ->getButtonModifier()                              │    │
│  │      ->setType(nativeNode, type);                       │    │
│  │    return panda::JSValueRef::Undefined(vm);             │    │
│  │  }                                                      │    │
│  └─────────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────────┘
    ↓
┌─────────────────────────────────────────────────────────────────┐
│  C++ Pattern 层 (components_ng/pattern)                         │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │  button_pattern.cpp                                     │    │
│  │  void ButtonPattern::SetButtonType(ButtonType type)      │    │
│  │  {                                                      │    │
│  │    buttonEventHub_->SetButtonType(type);                 │    │
│  │    MarkDirtyNode();                                      │    │
│  │  }                                                      │    │
│  └─────────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────────┘
    ↓
UI 更新和渲染
```

### Bridge 类命名规范

**模式**: `arkts_native_<Component>_bridge.h/cpp`

**示例**:
- `arkts_native_button_bridge.h` - Button 组件桥接
- `arkts_native_stack_bridge.cpp` - Stack 组件桥接
- `arkts_native_text_bridge.h` - Text 组件桥接

### Bridge 方法命名规范

| 前缀 | 用途 | 示例 |
|------|------|------|
| `Set` | 设置属性 | `SetType`, `SetWidth` |
| `Reset` | 重置属性 | `ResetType`, `ResetWidth` |
| `Create` | 创建组件 | `CreateButton` |
| `Get` | 获取属性 | `GetFrameNodeById` |
| `Register` | 注册模块 | `RegisterButtonAttributes` |

**示例 - Bridge 头文件**:
```cpp
// arkts_native_button_bridge.h
#ifndef FRAMEWORKS_..._ARKTS_NATIVE_BUTTON_BRIDGE_H
#define FRAMEWORKS_..._ARKTS_NATIVE_BUTTON_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class ButtonBridge {
public:
    // 注册接口
    static void RegisterButtonAttributes(
        Local<panda::ObjectRef> object, EcmaVM* vm);

    // 属性设置方法
    static ArkUINativeModuleValue SetType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // 创建方法
    static ArkUINativeModuleValue CreateButton(ArkUIRuntimeCallInfo* runtimeCallInfo);
};

} // namespace OHOS::Ace::NG
#endif
```

### Bridge 实现模式

```cpp
// arkts_native_button_bridge.cpp
ArkUINativeModuleValue ButtonBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // 1. 获取虚拟机实例
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    // 2. 获取参数
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);  // Native Node
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1); // Type value

    // 3. 提取 Native Node 指针
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    // 4. 提取参数值
    int32_t type = 0; // Default
    if (secondArg->IsNumber()) {
        type = secondArg->Int32Value(vm);
    }

    // 5. 调用 C++ Pattern 层
    GetArkUINodeModifiers()->getButtonModifier()->setType(nativeNode, type);

    // 6. 返回 undefined
    return panda::JSValueRef::Undefined(vm);
}
```

## 关键类型定义

### ANI 核心类型

```cpp
// arkts_native_api_bridge.h
namespace OHOS::Ace::NG {
// ANI 返回值类型
using ArkUINativeModuleValue = panda::Local<panda::JSValueRef>;

// ANI 运行时调用信息
using ArkUIRuntimeCallInfo = panda::JsiRuntimeCallInfo;

// Panda VM 类型
using panda::ecmascript::EcmaVM;

// 基础 Bridge 类
class ArkUINativeModule {
public:
    // 核心方法
    static ArkUINativeModuleValue GetFrameNodeById(ArkUIRuntimeCallInfo*);
    static ArkUINativeModuleValue GetArkUINativeModule(ArkUIRuntimeCallInfo*);
    static ArkUINativeModuleValue LoadNativeModule(ArkUIRuntimeCallInfo*);

private:
    // 组件注册方法
    static void RegisterButtonAttributes(Local<panda::ObjectRef>, EcmaVM*);
    static void RegisterTextAttributes(Local<panda::ObjectRef>, EcmaVM*);
    // ... 其他组件注册
};
}
```

### ArkTS 接口类型

```typescript
// units.static.d.ets - ArkTS 基础类型定义
export declare type Length = number | string | Resource;
export declare type Dimension = number | string | Resource;
export declare type ResourceColor = Color | string | Resource;
export declare type ResourceStr = string | Resource;

// AttributeModifier 基础接口
export declare interface AttributeModifier<T> {
    applyNormalAttribute?: (instance: T) => void;
    initializeModifier?: (instance: T) => void;
}

// ComponentBuilder 基础接口
export declare interface ComponentBuilder<T> {
    build(): void;
}

// 组件 Attribute 接口
export declare interface ButtonAttribute {
    type(value: ButtonType): ButtonAttribute;
    stateEffect(value: boolean): ButtonAttribute;
    // ... 其他属性方法
}
```

## 文档注释规范

### JSDoc 标签

**常用标签**:

| 标签 | 用途 | 示例 |
|------|------|------|
| `@file` | 文件描述 | `@file Button component definition` |
| `@kit` | 所属套件 | `@kit ArkUI` |
| `@syscap` | 系统能力 | `@syscap SystemCapability.ArkUI.ArkUI.Full` |
| `@since` | 起始版本 | `@since 23 static` |
| `@crossplatform` | 跨平台 | `@crossplatform` |
| `@atomicservice` | 原子化服务 | `@atomicservice` |
| `@stagemodelonly` | 仅 Stage 模型 | `@stagemodelonly` |
| `@noninterop` | 不可互操作 | `@noninterop` |
| `@deprecated` | 已废弃 | `@deprecated Use alternative instead` |
| `@param` | 参数说明 | `@param { number } value - Value` |
| `@returns` | 返回值 | `@returns { string } Result` |
| `@default` | 默认值 | `@default 0` |

**完整示例**:
```typescript
/**
 * Sets the type of the button.
 *
 * <p><strong>NOTE</strong>:
 * <br>Capsule: Capsule-shaped button
 * <br>Normal: Normal button without rounded corners
 * </p>
 *
 * @param { ButtonType } type - Type of the button to set.
 * @returns { ButtonAttribute } The interface for chained calls.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 * @crossplatform
 * @atomicservice
 */
type(value: ButtonType): ButtonAttribute;
```

## 开发指南

### 新增组件接口

**1. 创建 ArkTS 接口文件**

```typescript
// api/arkui/component/mycomponent.static.d.ets
'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * ...
 */

/**
 * @file
 * @kit ArkUI */
import { ResourceStr } from './units';
import { CommonConfiguration } from './common';

/**
 * Defines MyComponent Attribute.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24 static
 */
export declare interface MyComponentAttribute extends CommonConfiguration {
    /**
     * Sets the value.
     *
     * @param { ResourceStr } value - Value to set.
     * @returns { MyComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24 static
     */
    value(value: ResourceStr): MyComponentAttribute;
}

/**
 * Defines MyComponent Component.
 *
 * @struct { MyComponentAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24 static
 */
@Component
declare struct MyComponentComponent {
    /**
     * Component value.
     * @type { ResourceStr }
     */
    value: ResourceStr;

    @Builder
    build(): void;
}
```

**2. 创建 Modifier 定义文件**

```typescript
// api/arkui/MyComponentModifier.static.d.ets
'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * ...
 */

/**
 * @file
 * @kit ArkUI
 */

import { AttributeModifier } from './component/common';
import { MyComponentAttribute } from './component/mycomponent';

/**
 * Defines MyComponent Modifier
 *
 * @implements { MyComponentAttribute, AttributeModifier<MyComponentAttribute> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24 static
*/
export declare class MyComponentModifier
  implements MyComponentAttribute, AttributeModifier<MyComponentAttribute> {}
```

**3. 创建 C++ Bridge 头文件**

```cpp
// arkts_native_mycomponent_bridge.h
#ifndef FRAMEWORKS_..._ARKTS_NATIVE_MYCOMPONENT_BRIDGE_H
#define FRAMEWORKS_..._ARKTS_NATIVE_MYCOMPONENT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class MyComponentBridge {
public:
    static void RegisterMyComponentAttributes(
        Local<panda::ObjectRef> object, EcmaVM* vm);

    static ArkUINativeModuleValue SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetValue(ArkUIRuntimeCallInfo* runtimeCallInfo);
};

} // namespace OHOS::Ace::NG
#endif
```

**4. 创建 C++ Bridge 实现文件**

```cpp
// arkts_native_mycomponent_bridge.cpp
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_mycomponent_bridge.h"

namespace OHOS::Ace::NG {

ArkUINativeModuleValue MyComponentBridge::SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::string value;
    if (secondArg->IsString()) {
        value = secondArg->ToString(vm)->ToString();
    }

    GetArkUINodeModifiers()->getMyComponentModifier()->setValue(nativeNode, value);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MyComponentBridge::ResetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getMyComponentModifier()->resetValue(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

void MyComponentBridge::RegisterMyComponentAttributes(
    Local<panda::ObjectRef> object, EcmaVM* vm)
{
    // 绑定方法到 JS 对象
}
}
```

**5. 注册 Bridge 模块**

```cpp
// arkts_native_api_bridge.h 或相应的注册文件
class ArkUINativeModule {
private:
    static void RegisterMyComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    // ...
};
```

## 构建工具

### API 检查工具

**位置**: `build-tools/api_check_plugin/`

**功能**:
- 检查 API 声明是否符合规范
- 验证 JSDoc 注释完整性
- 检查 syscap、since 等标签正确性

### API 收集工具

**位置**: `build-tools/collect_api/`

**功能**:
- 解析应用中使用的 API
- 生成 API 使用报告
- 支持 API 兼容性分析

### Transformer 工具

**位置**: `build-tools/arkui_transformer/`

**功能**:
- .d.ts 到 .static.d.ets 的转换
- 代码生成和转换

## 调试技巧

### 1. 检查类型声明

```bash
# 检查 API 声明规范
python3 build-tools/api_check_plugin/check_api.py \
  --api-dir interface/sdk-js/api \
  --output report.txt
```

### 2. 验证 Bridge 绑定

```cpp
// 在 Bridge 方法中添加日志
ArkUINativeModuleValue MyComponentBridge::SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGI("MyComponentBridge::SetValue called");

    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    // ... 实现代码
}
```

### 3. 追踪调用链

```
ArkTS-Sta API 调用
    ↓ (ArkTS 接口层)
.interface/ets/api/arkui/component/mycomponent.static.d.ets
    ↓ (ANI Bridge 绑定)
.arkui_ace_engine/.../arkts_native_mycomponent_bridge.cpp
    ↓ (Pattern 层)
.components_ng/pattern/mycomponent/mycomponent_pattern.cpp
    ↓ (Render 层)
.components_ng/render/mycomponent_render_property.cpp
```

## 常见问题

### 1. 找不到组件定义

**问题**: ArkTS 编译错误 "Cannot find name 'Button'"

**排查**:
- 检查 import 路径是否正确
- 确认组件定义文件存在 (`button.static.d.ets`)
- 验证 export 声明

### 2. Bridge 方法未调用

**问题**: 修改 Bridge 实现后无效果

**排查**:
- 确认 Bridge 方法已注册
- 检查方法命名是否符合规范 (SetXxx, ResetXxx)
- 验证模块编译和链接

### 3. 类型不匹配

**问题**: ArkTS 类型检查失败

**排查**:
- 确认使用的类型定义 (.static.d.ets)
- 检查 `use static` 指令
- 验证 `@Component` 装饰器使用

## 最佳实践

### 1. 接口设计

- **一致性**: 保持命名和结构与其他组件一致
- **文档化**: 为所有公开 API 添加 JSDoc 注释
- **类型安全**: 使用明确的类型定义，避免 `any`

### 2. Bridge 实现

- **错误处理**: 使用 `CHECK_NULL_RETURN` 宏处理空指针
- **类型检查**: 在转换前验证参数类型
- **资源管理**: 遵循 RAII 原则管理资源

### 3. 版本管理

- **@since 标签**: 明确 API 起始版本
- **@deprecated 标签**: 标记废弃 API 并提供替代方案
- **兼容性**: 保持 API 向后兼容

## 搜索模式

```bash
# 查找组件接口定义
find interface/sdk-js/api/arkui/component -name "*.static.d.ets"

# 查找 Modifier 定义
find interface/sdk-js/api/arkui -name "*Modifier.static.d.ets"

# 查找 Bridge 实现
find ace_engine -name "arkts_native_*_bridge.cpp"

# 搜索特定组件的 API
grep -r "ButtonType" interface/sdk-js/api/arkui/
```

## 参考资源

### 文档

- **OpenHarmony 文档**: https://docs.openharmony.cn/
- **ArkUI 开发指南**: https://docs.openharmony.cn/ui/
- **API 参考**: https://docs.openharmony.cn/application-dev/reference/

### 相关仓库

- **interface/sdk-js**: https://gitee.com/openharmony/interface_sdk_js
- **arkui_ace_engine**: https://gitee.com/openharmony/arkui_ace_engine
- **arkui_napi**: https://gitee.com/openharmony/arkui_napi

### 关键源文件

| 文件 | 说明 |
|------|------|
| `arkts_native_api_bridge.h` | ANI 基础设施定义 |
| `common.static.d.ets` | 公共类型和接口 |
| `button.static.d.ets` | Button 组件示例 |
| `arkts_native_button_bridge.cpp` | Button Bridge 实现示例 |

## 常用命令

```bash
# API 规范检查
./build-tools/api_check_plugin/check.sh

# 构建接口模块
./build.sh --product-name rk3568 --build-target interface_sdk_js

# 收集 API 使用
./build-tools/collect_api/collect.sh --app-path /path/to/app

# 生成 API 文档
./build-tools/dts_parser/generate_docs.sh
```

## 总结

**interface/ets 目录核心职责**:

1. **API 声明**: 定义 ArkTS-Sta 静态模式下的 ArkTS 接口
2. **类型安全**: 提供编译时类型检查
3. **桥接定义**: 连接 ArkTS 和 C++ 实现层
4. **文档规范**: 通过 JSDoc 提供 API 文档

**关键概念**:

- **ANI**: ArkTS Native Interface，类似 JNI 的桥接机制
- **双模式**: Dynamic (.d.ts) 和 Static (.static.d.ets)
- **Bridge 层**: arkts_native_*_bridge 实现桥接逻辑
- **Pattern 层**: components_ng/pattern 实现 C++ 业务逻辑

**开发流程**:

```
ArkTS 接口定义 (.static.d.ets)
    ↓
C++ Bridge 实现 (*_bridge.cpp/h)
    ↓
Pattern 层实现 (*_pattern.cpp)
    ↓
Render 层实现 (*_render_property.cpp)
    ↓
UI 渲染
```

---

**最后更新**: 2025-02-04
**适用版本**: OpenHarmony API 24+
**状态维护**: 请根据最新代码持续更新本文档
