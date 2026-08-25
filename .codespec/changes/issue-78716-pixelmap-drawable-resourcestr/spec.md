# 特性规格

## 概述

| 字段 | 内容 |
|------|------|
| 特性名称 | PixelMapDrawableDescriptor ResourceStr 支持 |
| 特性编号 | Feat-02 |
| 所属 FuncID | 04-01-03 |
| 优先级 | P0 |
| 目标版本 | API 26 |
| SIG 归属 | ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 |

为 `PixelMapDrawableDescriptor` 补全 `ResourceStr` 构造函数实现。SDK 声明文件（`.d.ts` / `.static.d.ets`）已在 @since 26.0.0 声明 `constructor(src?: image.PixelMap | ResourceStr)` 重载，动态和静态实现均缺失。

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | 动态 NAPI: `PixelMapConstructor` 新增 string 和 Resource 分支 | 复用 `AnimatedConstructor` 已有的 ParseResourceObject 模式 |
| ADDED | 核心层: `PixelMapDrawableDescriptor` 新增 Info/Loader 加载路径 | 通过 `DrawableDescriptorInfo` + `DrawableDescriptorLoader` 加载 |
| ADDED | drawable_api: 新增 `setPixelMapPath` / `setPixelMapResource` 接口 | modifier 函数表扩展 |
| ADDED | 静态前端: `PixelMapDrawableDescriptor` 新增 `constructor(src: ResourceStr)` | 参考 `AnimatedDrawableDescriptor` 已有 ResourceStr 模式 |
| ADDED | 静态 ANI: 新增 `_Drawable_CreatePixelMapDrawableByString/Resource` | ANI_CALL 注册 + C++ 实现 |
| ADDED | 单元测试: ResourceStr 构造路径测试用例 | string 路径 + Resource 引用 |

## 输入文档

- 需求基线: [proposal.md](../proposal.md)
- 设计文档: [design.md](../design.md)
- 参考实现: `AnimatedDrawableDescriptor` ResourceStr 模式
  - NAPI: `js_drawable_descriptor.cpp:1208-1275` (AnimatedConstructor)
  - ANI: `drawable_module.cpp:367-405` (CreateAnimatedDrawableByResource/ByString)
  - ArkTS: `drawableDescriptor.ets:302-325`
- SDK 声明: `@ohos.arkui.drawableDescriptor.d.ts:362`, `.static.d.ets:235`

## 用户故事

### US-1: 通过 string 路径构造 PixelMapDrawableDescriptor

作为应用开发者，我想要通过文件路径（string）直接创建 PixelMapDrawableDescriptor，不必先手动解码为 PixelMap。

- **AC-1.1**: WHEN 通过 `new PixelMapDrawableDescriptor("/data/storage/image.png")` 构造 THEN `getPixelMap()` 返回从文件路径加载的有效 PixelMap
- **AC-1.2**: WHEN 通过 `new PixelMapDrawableDescriptor("data:image/png;base64,...")` 构造 THEN `getPixelMap()` 返回从 base64 数据解码的有效 PixelMap
- **AC-1.3**: WHEN 传入无效文件路径或损坏的 base64 数据 THEN 构造成功但 `getPixelMap()` 返回 `nullptr`/`undefined`
- **AC-1.4**: WHEN 通过 ResoureStr 构造且 `getPixelMap()` 返回非空 THEN 后续 `loadSync()` 返回正确的宽高

### US-2: 通过 Resource 引用构造 PixelMapDrawableDescriptor

作为应用开发者，我想要通过资源引用（`$r('app.media.icon')`）创建 PixelMapDrawableDescriptor。

- **AC-2.1**: WHEN 通过 `new PixelMapDrawableDescriptor($r('app.media.icon'))` 构造 THEN `getPixelMap()` 返回从资源管理系统加载的有效 PixelMap
- **AC-2.2**: WHEN 资源不存在或资源 ID 无效 THEN 构造成功但 `getPixelMap()` 返回 `nullptr`/`undefined`

### US-3: 静态前端 ResourceStr 支持

作为应用开发者，我在静态 ArkTS 工程中使用 PixelMapDrawableDescriptor 时，同样支持 ResourceStr 输入。

- **AC-3.1**: WHEN 静态前端调用 `new PixelMapDrawableDescriptor(src: string)` THEN 行为与动态一致
- **AC-3.2**: WHEN 静态前端调用 `new PixelMapDrawableDescriptor(src: Resource)` THEN 行为与动态一致

### US-4: 向后兼容

已有 `constructor(src?: image.PixelMap)` 路径必须保持不变。

- **AC-4.1**: WHEN 通过 `new PixelMapDrawableDescriptor(pixelMap)`（PixelMap 对象）构造 THEN 行为与变更前完全一致
- **AC-4.2**: WHEN 不传参数 `new PixelMapDrawableDescriptor()` THEN 创建一个空的描述符，`getPixelMap()` 返回 `undefined`

## 验收追溯

| AC ID | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1 ~ AC-1.4 | FR-1, FR-2, EX-2 | TASK-1 | C API unittest + XTS | 待实现 |
| AC-2.1 ~ AC-2.2 | FR-1, FR-3, EX-2 | TASK-1 | C API unittest + XTS | 待实现 |
| AC-3.1 ~ AC-3.2 | FR-4, FR-5 | TASK-2 | 静态前端集成测试 | 待实现 |
| AC-4.1 ~ AC-4.2 | — | TASK-1, TASK-2 | C API unittest | 已有覆盖 |

## 业务规则

### BR-1: ResourceStr 类型判定

`ResourceStr = string | Resource`。构造时按以下顺序判定：
1. `napi_string` / ArkTS string → 文件路径或 base64 数据
2. `napi_object` + PixelMap → 已有 `setPixelMapByPixelMap` 路径
3. `napi_object` + 非 PixelMap → `ParseResourceObject` → Resource 引用
4. 其他/undefined → 空描述符

### BR-2: 资源加载方式

string 路径和 Resource 引用均通过 `DrawableDescriptorInfo` 解析 + `DrawableDescriptorLoader::LoadData` 加载为 `MediaData`，然后解码为 PixelMap。加载失败不抛异常，`getPixelMap()` 返回 nullptr/undefined。

## 功能规则

### FR-1: 动态 NAPI — PixelMapConstructor 扩展

在 `PixelMapConstructor`（`js_drawable_descriptor.cpp:1513`）中重写为走新架构，新增类型分支：
- 对 `napi_string` 类型参数：通过 `modifier->setPixelMapPath(descriptor, src)` 设置路径/数据
- 对 `napi_object` 类型参数（非 PixelMap）：通过 `ParseResourceObject(argv[0])` 提取 ResourceObject → `modifier->setPixelMapResource(descriptor, resourceObject)` 设置资源

参考实现: `AnimatedConstructor` `js_drawable_descriptor.cpp:1233-1253`

### FR-2: 核心层 — setPixelMapPath

`PixelMapDrawableDescriptor::setPixelMapPath(const std::string& path)` 或等效接口：
1. 构造 `DrawableDescriptorInfo(path)` 解析 src 类型（FILE/BASE64）
2. 调用 `DrawableDescriptorLoader::LoadData(info)` 获取 `MediaData`
3. 将 raw data 存入 `rawData_` 供后续 `CreatePixelMap()` 解码

### FR-3: 核心层 — setPixelMapResource

`PixelMapDrawableDescriptor::setPixelMapResource(ResourceObject* resource)` 或等效接口：
1. 构造 `DrawableDescriptorInfo(resource)` 解析 RESOURCE 类型
2. 调用 `DrawableDescriptorLoader::LoadData(info)` 获取 `MediaData`
3. 将 raw data 存入 `rawData_` 供后续 `CreatePixelMap()` 解码

### FR-4: 静态前端 ArkTS — constructor 重载

在 `@ohos.arkui.drawableDescriptor.ets` 的 `PixelMapDrawableDescriptor` 中新增：
```typescript
constructor(src: ResourceStr) {
  super()
  if (src instanceof string) {
    ArkUIAniModule._Drawable_CreatePixelMapDrawableByString(this, src as string)
  } else if (src instanceof Resource) {
    let resourceObjectKPointer = SystemOps.createResourceObject(src as Resource)
    ArkUIAniModule._Drawable_CreatePixelMapDrawableByResource(this, resourceObjectKPointer)
  }
  // 已有 PixelMap 构造保持不变
  ...
}
```

参考实现: `AnimatedDrawableDescriptor` constructor `drawableDescriptor.ets:302-325`

### FR-5: 静态 ANI — 新 native 方法

在 `ArkUIAniModule` 中注册两个新的 native static 方法：
- `_Drawable_CreatePixelMapDrawableByString(value: PixelMapDrawableDescriptor, src: string): void`
- `_Drawable_CreatePixelMapDrawableByResource(value: PixelMapDrawableDescriptor, resourceObjectKPointer: long): void`

C++ 实现：
- `DrawableCreatePixelMapDrawableByString`: 同 `DrawableCreateAnimatedDrawableByString` 模式但调用 `modifier->setPixelMapPath`
- `DrawableCreatePixelMapDrawableByResource`: 同 `DrawableCreateAnimatedDrawableByResource` 模式但调用 `modifier->setPixelMapResource`

### FR-6: drawable_api 接口扩展

在 `ArkUIDrawableModifier` 结构体中新增两个函数指针：
- `void (*setPixelMapPath)(void* object, const char* path)`
- `void (*setPixelMapResource)(void* object, void* resourceObject)`

## 异常/豁免规则

### EX-1: 已有 PixelMap 路径不变

已有 `constructor(src?: image.PixelMap)` 路径的所有逻辑和行为不变。

### EX-2: 无效资源不抛异常

无效路径 / 资源不存在 / base64 解码失败 → 不抛异常，`getPixelMap()` 返回 `nullptr`/`undefined`。与 `AnimatedDrawableDescriptor` 已有错误处理一致。

### EX-3: 参数为空

`new PixelMapDrawableDescriptor()` 无参数 → 空描述符，`getPixelMap()` 返回 undefined。行为与变更前一致。

## 恢复契约

无新增恢复契约。资源加载失败时返回 nullptr，调用方需检查返回值。

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | US-1 全 AC | C API unittest | string 路径/base64 加载正确性，失败处理 |
| VM-2 | US-2 全 AC | C API unittest | Resource 引用加载正确性 |
| VM-3 | US-3 全 AC | 静态前端集成测试 | static 前端 string/Resource 行为一致性 |
| VM-4 | US-4 全 AC | C API unittest (已有) | 回归：已有 PixelMap 路径不受影响 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `PixelMapDrawableDescriptor.constructor(src: string)` (dynamic + static) | System | 通过文件路径或 base64 字符串构造 | AC-1.1 ~ AC-1.4 |
| `PixelMapDrawableDescriptor.constructor(src: Resource)` (dynamic + static) | System | 通过资源引用构造 | AC-2.1 ~ AC-2.2 |

> 注：以上两重载已在 SDK `.d.ts` / `.static.d.ets` 中声明为 `constructor(src?: image.PixelMap \| ResourceStr)` @since 26.0.0，本次仅为实现补全。

### 变更/废弃 API

无。

## 兼容性声明

- **已有 API 行为变更:** 否 — 新增构造函数重载，已有 PixelMap 路径不变
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** API 26
- **API 版本号策略:** 跟随 SDK 声明 @since 26.0.0
- **向后兼容:** 已有 `constructor(src?: image.PixelMap)` 保持不变；`constructor(src: ResourceStr)` 为新增重载
- **动态/静态一致性:** 动静态行为完全一致

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| 复用 DrawableDescriptorInfo + Loader | ResourceStr 解析和加载走已有 RESOURCE/BASE64/FILE 三路径基础设施，不重复造轮子 | AC-1.1 ~ AC-2.2 |
| 走新架构 | 核心实现在 `frameworks/core/drawable/pixel_map_drawable_descriptor.*`，不涉及旧 `interfaces/inner_api/` 的 Napi::DrawableDescriptor 层 | AC-1.* ~ AC-2.* |
| 参考 AnimatedDrawableDescriptor 模式 | NAPI 分支判定、ANI 方法注册、ArkTS 构造重载均参考已有 AnimatedDrawableDescriptor ResourceStr 实现 | AC-3.* |
| drawable_api 接口扩展 | 新增 `setPixelMapPath` / `setPixelMapResource` 两个函数指针，需同步更新所有实现该接口的模块 | FR-2, FR-3, FR-6 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | 构造不触发同步解码（lazy: getPixelMap 时才解码） | 代码审查 | 参考已有 lazy 解码模式 |
| 内存 | 构造时仅存储 rawData_（文件/base64 数据），不影响峰值 | 代码审查 | rawData_ 与 PixelMap 互斥 |
| 可靠性 | 无效输入不崩溃 | C API unittest | EX-2 覆盖 |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 数据对象 | N/A |
| 大字体 | 否 | 无文本 | N/A |
| 深色模式 | 否 | 不感知主题 | N/A |
| 多窗口/分屏 | 否 | 不感知窗口 | N/A |
| 多用户 | 否 | 不涉及用户数据 | N/A |
| 版本升级 | 是 | API 26 新功能，向前兼容 | 已有 PixelMap 构造不变 |
| 生态兼容 | 是 | 新增构造重载不破坏已有 API | 动态/静态双通道一致 |

## 行为场景（Gherkin）

```gherkin
Feature: PixelMapDrawableDescriptor ResourceStr 构造
  作为 应用开发者
  我想要 通过文件路径或资源引用创建 PixelMapDrawableDescriptor
  以便 简化资源加载流程

  Scenario: 通过文件路径创建
    Given 存在有效的图片文件 "/data/storage/icon.png"
    When 调用 new PixelMapDrawableDescriptor("/data/storage/icon.png")
    Then getPixelMap() 返回非空的 image.PixelMap
    And loadSync() 返回 { imageWidth > 0, imageHeight > 0 }

  Scenario: 通过 base64 创建
    Given 存在有效的 base64 编码图片数据
    When 调用 new PixelMapDrawableDescriptor("data:image/png;base64,...")
    Then getPixelMap() 返回非空的 image.PixelMap

  Scenario: 通过 Resource 引用创建
    Given 资源系统中存在 "app.media.icon"
    When 调用 new PixelMapDrawableDescriptor($r("app.media.icon"))
    Then getPixelMap() 返回非空的 image.PixelMap

  Scenario: 无效路径静默失败
    Given 不存在文件 "/data/storage/nonexistent.png"
    When 调用 new PixelMapDrawableDescriptor("/data/storage/nonexistent.png")
    Then 构造成功不抛异常
    And getPixelMap() 返回 undefined

  Scenario: 已有 PixelMap 路径不受影响
    Given 持有一个有效的 image.PixelMap 对象
    When 调用 new PixelMapDrawableDescriptor(pixelMap)
    Then 行为与变更前完全一致
    And getPixelMap() 返回传入的同一 PixelMap

  Scenario: 静态前端 string 路径
    Given 静态 ArkTS 工程
    When 调用 new PixelMapDrawableDescriptor("path/to/image.png")
    Then 行为与动态前端一致
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（NAPI + Core + drawable_api + Koala + ANI + 测试）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则交叉一致
- [x] 参考 AnimatedDrawableDescriptor 已有实现，每条 FR 有对应源码路径
