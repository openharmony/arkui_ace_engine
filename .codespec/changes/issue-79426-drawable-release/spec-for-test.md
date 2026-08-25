---
artifact: spec-for-test
format_version: arkui-detailed-v1
status: ReadyForReview
source_spec: spec.md
source_spec_hash: b9d8964d8f55d5145740ea59ea371185745198498851fdea9b1813a403f18c60
source_design: design.md
source_design_hash: bee10616eb1e6a2323958e2e05273866aec86230101c49d4de0c0f4d41d2f87d
source_consistency: current
profile: arkui
subprofiles:
  - sdk-api
generated_at: 2026-07-23T15:07:58+00:00
---

# DrawableDescriptor release/isReleased 绑定状态能力 — 测试设计规格

> ArkUI 测试设计规格 | 格式版本: v1.0
>
> 本文档是测试用例设计的自包含输入件。需求目标、用户故事、规则、API、兼容性和非功能性要求来自 Approved `spec.md`；2D、2C、NFR 验证细项和 AC 验证点由测试输入分析补充。
> `GENERATED:*` 区域只能由 CLI 刷新；人工只填写 `TEST-ANALYSIS` 区域，不得摘要或改写来源规格。

---

## 元信息

| 字段 | 内容 |
|---|---|
| 需求编号 | drawable-descriptor-release-state |
| 需求名称 | DrawableDescriptor release/isReleased 绑定状态能力 |
| 特性编号 | Func-04-01-03-Feat-01-delta |
| 需求来源 | 未声明 |
| 提出人 | 未声明 |
| 优先级 | P1 |
| 目标版本 | API 26.0.0 |
| SIG归属 | ArkUI |
| 来源规格状态 | Approved |
| 产物状态 | ReadyForReview |
| 复杂度 | 标准 |
| 创建日期 | 2026-07-23 |
| 最后更新 | 2026-07-23 |

---

<!-- GENERATED:EXTERNAL-SPEC:BEGIN -->
## 一、需求目标与规格 `[源: spec.md]`

### 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | DrawableDescriptor release/isReleased 绑定状态能力 |
| 特性编号 | Func-04-01-03-Feat-01-delta |
| 所属 Epic | 无，存量能力增量 |
| 优先级 | P1 |
| 目标版本 | API 26.0.0 |
| SIG 归属 | ArkUI |
| 状态 | Approved |
| 复杂度 | 标准 |

### 用户故事

#### US-1: Dynamic DrawableDescriptor 显式释放

**作为** ArkTS Dynamic DrawableDescriptor 调用者，  
**我想要** 主动调用 `release()` 解除前端对象与后端对象的绑定，  
**以便** 提前释放 native 资源并避免继续访问已解绑对象。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-1.1 | WHEN Dynamic `DrawableDescriptor` 或任一子类对象首次调用 `release()` THEN 对象进入 released 状态，后续 `isReleased()` 返回 `true`。 | 正常 |
| AC-1.2 | WHEN Dynamic 同一对象重复调用 `release()` THEN 调用直接返回且不崩溃，`isReleased()` 保持 `true`。 | 边界 |
| AC-1.3 | WHEN Dynamic 对象未调用 `release()` THEN `isReleased()` 返回 `false`。 | 正常 |
| AC-1.4 | WHEN Dynamic 已释放对象调用 `getPixelMap()`、`getForeground()`、`getBackground()`、`getMask()`、`loadSync()` 或新发起 `load()` THEN 抛出或 reject `BusinessError 111002`。 | 异常 |
| AC-1.5 | WHEN Dynamic 已释放对象调用 `invalidate()`、`setHdrComposition()`、`getAnimationController()` 或 `setBlendMode()` THEN 调用无操作返回且不崩溃。 | 边界 |
| AC-1.6 | WHEN Dynamic 对象在未释放状态下使用既有加载、分层、动画、Picture/HDR 能力 THEN 既有行为不变。 | 兼容 |

#### US-2: 异步 load 与释放状态

**作为** ArkTS Dynamic DrawableDescriptor 调用者，  
**我想要** 在 `load()` 已发起后调用 `release()` 仍不会破坏异步结果，  
**以便** 避免异步加载与显式释放之间产生崩溃或未定义行为。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-2.1 | WHEN Dynamic 对象在未释放状态下发起 `load()`，随后调用 `release()` THEN 已发起的 Promise 继续安全完成，完成过程不访问已释放内存，也不重新绑定已 release 的前端对象。 | 边界 |
| AC-2.2 | WHEN Dynamic 对象已经处于 released 状态后再调用 `load()` THEN Promise reject `BusinessError 111002`。 | 异常 |

#### US-3: Static 与 C API 兼容边界

**作为** Static ArkTS 或 NDK 调用者，  
**我想要** 本次变更不改变 Static 既有 release 行为，也不改变 C API 生命周期接口，  
**以便** 保持现有调用方兼容。

**验收标准（AC, Acceptance Criteria）：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-3.1 | WHEN Static 已释放对象调用 `getPixelMap()` THEN 返回 `undefined`，不改为 `BusinessError 111002`。 | 兼容 |
| AC-3.2 | WHEN Static 已释放对象调用 `loadSync()` 或 `load()` THEN 返回或 resolve `imageWidth=-1,imageHeight=-1`，不改为 `BusinessError 111002`。 | 兼容 |
| AC-3.3 | WHEN 通过 NAPI/ANI bridge 从已释放 Dynamic 或 Static DrawableDescriptor 提取 native descriptor THEN 返回参数错误，不产生新的有效 native descriptor。 | 异常 |
| AC-3.4 | WHEN 已经提取出的 C 侧 `ArkUI_DrawableDescriptor*` 句柄存在 THEN 后续前端对象 `release()` 不主动使该 C 侧句柄失效；C 侧句柄仍按 `OH_ArkUI_DrawableDescriptor_Dispose` 管理生命周期。 | 兼容 |
| AC-3.5 | WHEN 调用现有 `OH_ArkUI_DrawableDescriptor_Dispose` THEN 函数签名、结构布局、错误码和生命周期语义保持不变。 | 兼容 |

## 二、规则定义 `[源: spec.md]`

### 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | Dynamic DrawableDescriptor 或子类首次调用 `release()`。 | 对象进入 released 状态；释放后不再允许访问其后端绑定对象。 | 覆盖 DrawableDescriptor、PixelMapDrawableDescriptor、LayeredDrawableDescriptor、AnimatedDrawableDescriptor、PictureDrawableDescriptor。 | AC-1.1 |
| R-2 | 行为 | Dynamic 对象调用 `isReleased()`。 | release 前返回 `false`；release 后返回 `true`。 | `isReleased()` 本身可在 released 状态下调用。 | AC-1.1, AC-1.3 |
| R-3 | 边界 | Dynamic 已 released 对象重复调用 `release()`。 | 直接返回，不崩溃，不改变已释放状态。 | 重复次数不产生额外副作用。 | AC-1.2 |
| R-4 | 异常 | Dynamic 已 released 对象调用 `getPixelMap/getForeground/getBackground/getMask/loadSync/load`。 | 同步 API 抛 `BusinessError 111002`；Promise API reject `BusinessError 111002`。 | 已发起的 `load()` 按 R-6 处理；released 后新发起的 `load()` 按本规则处理。 | AC-1.4, AC-2.2 |
| R-5 | 边界 | Dynamic 已 released 对象调用 `invalidate/setHdrComposition/getAnimationController/setBlendMode`。 | 无操作返回且不崩溃。 | 不重新创建或重新绑定后端对象。 | AC-1.5 |
| R-6 | 边界 | Dynamic 对象未 release 时已发起 `load()`，随后调用 `release()`。 | 已发起 Promise 继续安全完成；完成结果不重新绑定 released 前端对象。 | 不允许访问已释放内存。 | AC-2.1 |
| R-7 | 兼容 | Static 已 released 对象调用 `getPixelMap/loadSync/load`。 | 保持现有行为：`getPixelMap()` 返回 `undefined`；`loadSync/load` 返回或 resolve `imageWidth=-1,imageHeight=-1`。 | 本次不改变 Static 错误码语义。 | AC-3.1, AC-3.2 |
| R-8 | 异常 | 从已 released 前端对象提取 native descriptor。 | 返回参数错误，不产生新的有效 native descriptor。 | 适用于 NAPI/ANI bridge。 | AC-3.3 |
| R-9 | 兼容 | Dynamic 对象未调用 `release()` 并使用既有功能。 | 加载、分层、动画、Picture/HDR 等既有行为保持不变。 | 本次不扩展非 release 行为。 | AC-1.6 |
| R-10 | 兼容 | 前端对象 release 前已提取 C 侧 descriptor 句柄。 | 后续前端 release 不主动使既有 C 侧句柄失效。 | C 侧句柄继续由 C API 生命周期管理。 | AC-3.4 |
| R-11 | 兼容 | 使用现有 C API Dispose。 | `OH_ArkUI_DrawableDescriptor_Dispose` 签名、结构布局、错误码和生命周期语义不变。 | 不新增 C API release/isReleased。 | AC-3.5 |

## 三、API 变更分析 `[源: spec.md]`

#### 新增 API

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `DrawableDescriptor.release()` | System | 无 | `void` | N/A | 解除 Dynamic 前端对象与后端对象的绑定；重复调用无崩溃。SDK 声明已存在，本次补齐运行时行为。 | AC-1.1, AC-1.2 |
| `DrawableDescriptor.isReleased()` | System | 无 | `boolean` | N/A | 查询 Dynamic 前端对象是否已解除后端绑定。SDK 声明已存在，本次补齐运行时行为。 | AC-1.1, AC-1.3 |

#### 变更/废弃 API

| API 名称 | 变更类型 | 影响场景 | 迁移指引 | 关联 AC |
|----------|----------|----------|----------|---------|
| `DrawableDescriptor.getPixelMap()` | 行为补齐 | Dynamic release 后调用。 | 调用方可先用 `isReleased()` 判断；release 后调用将抛 `111002`。 | AC-1.4 |
| `LayeredDrawableDescriptor.getForeground/getBackground/getMask()` | 行为补齐 | Dynamic release 后调用。 | 调用方可先用 `isReleased()` 判断；release 后调用将抛 `111002`。 | AC-1.4 |
| `DrawableDescriptor.loadSync/load()` | 行为补齐 | Dynamic release 后新调用；已发起 load 后 release。 | release 后新调用失败；已发起 load 继续安全完成。 | AC-1.4, AC-2.1, AC-2.2 |
| `invalidate/setHdrComposition/getAnimationController/setBlendMode` | 行为补齐 | Dynamic release 后调用。 | release 后调用无操作返回。 | AC-1.5 |
| Static `DrawableDescriptor.release/isReleased` 相关行为 | 不变 | Static release 后访问。 | 无迁移；保持既有 `undefined/-1` 行为。 | AC-3.1, AC-3.2 |
| C API `OH_ArkUI_DrawableDescriptor_Dispose` | 不变 | C 侧 descriptor 生命周期。 | 无迁移；继续由调用方显式 Dispose。 | AC-3.5 |

## 四、兼容性声明 `[源: spec.md]`

### 兼容性声明

- **已有 API 行为变更:** 是。仅补齐 Dynamic release 后访问语义；未调用 `release()` 的既有路径保持不变。
- **配置文件格式变更:** 否。
- **数据存储格式变更:** 否。
- **最低支持版本:** API 26.0.0。
- **API 版本号策略:** 沿用 SDK 现有 `@since 26.0.0` 标注；本次不新增 C API。
<!-- GENERATED:EXTERNAL-SPEC:END -->

<!-- TEST-ANALYSIS:BEGIN -->
## 五、2D 能力特征分析

> 本章为测试独有内容。每个小节必须填写“是否涉及”；选择“是”时完成该小节全部细项，选择“否/N/A”时填写不涉及理由。

### 5.1 是否涉及新增开放 API

**是否涉及：** 是

**覆盖确认：** Dynamic System API 的 `release()` / `isReleased()` 运行时行为及释放后访问契约均已在第三章体现；SDK 声明已存在，本次是运行时能力补齐。

- API 变更内容是否已在第三章完整体现：是，包含签名、返回值、释放状态、错误语义和兼容边界。
- 关联 AC：AC-1.1、AC-1.2、AC-1.3、AC-1.4、AC-1.5、AC-2.1、AC-2.2。
- 测试侧验证方式：在真实 ArkTS Dynamic 调用环境中观察布尔返回值、同步异常、Promise reject/完成和重复调用结果；对各 descriptor 子类核对公共生命周期契约。

**不涉及理由：** N/A，本项涉及。

---

### 5.2 是否涉及应用兼容性

**是否涉及：** 是

| 兼容性维度 | 修改前规格 | 修改后规格 | 影响范围 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|
| API/行为兼容 | Dynamic 缺少完整的 release 后访问语义；Static 和 C API 有既有降级/生命周期行为。 | Dynamic 指定访问型 API 返回 `111002`，控制/刷新类 API 无操作；未 release 路径、Static 和 C API 保持不变。 | API 26.0.0 Dynamic 调用方、Static 调用方和 NDK 调用方。 | AC-1.4、AC-1.5、AC-1.6、AC-2.2、AC-3.1 至 AC-3.5 | Dynamic/Static 对照行为验证、版本升级兼容性验证、NDK 接口契约与 ABI 兼容性核对。 |
| 配置/数据兼容 | 无 DrawableDescriptor 配置或持久化数据格式变更。 | 配置和数据格式仍保持不变。 | 无配置迁移或数据迁移影响。 | AC-1.6、AC-3.5 | 确认旧应用无需新增配置或数据迁移即可继续使用未 release 路径和既有 C API。 |

**不涉及理由：** N/A，本项涉及。

---

### 5.3 是否涉及跨平台

**是否涉及：** N/A

| 平台 | 对外预期/差异 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|
| Android | N/A，本规格不定义 Android 平台契约。 | N/A | N/A |
| iOS | N/A，本规格不定义 iOS 平台契约。 | N/A | N/A |
| 其他 | N/A，本次仅定义 OpenHarmony ArkUI DrawableDescriptor 行为。 | N/A | N/A |

**不涉及理由：** `spec.md` 未定义 Android、iOS 或其他操作系统的跨平台契约，不得为此新增行为。

---

### 5.4 是否涉及 IDE 预览

**是否涉及：** 是

| 应用场景 | 能力用法 | UX 效果/可观察结果 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|
| IDE Previewer 中的 Dynamic DrawableDescriptor 生命周期验证 | 创建 Dynamic descriptor，调用 `isReleased()`、`release()`、释放后访问型 API 及控制/刷新类 API。 | 可观察 `false → true` 状态切换、`111002` 异常/Promise reject、无操作返回和无崩溃。 | AC-1.1 至 AC-1.5、AC-2.1、AC-2.2 | 在 IDE Previewer 可执行 ArkTS 页面中观察 API 返回值、错误码、Promise 完成和页面进程稳定性。 |

**不涉及理由：** N/A，现有规格已将 IDE Previewer 作为 Dynamic API 行为的可观察验证入口。

---

### 5.5 是否涉及编译工具链

**是否涉及：** 否

| 触发场景 | 错误类型 | 错误信息 | 报错位置 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|
| ArkTS 编译 | 不涉及 | N/A，本次不新增语法、编译诊断或工具链错误契约。 | N/A | N/A | N/A |

**不涉及理由：** SDK 声明已存在，`spec.md` 仅补齐运行时行为，未定义新的编译期告警或错误。

---

### 5.6 是否涉及全球化语言

**是否涉及：** N/A

| 语言/区域 | 输入或配置 | 对外预期 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|
| 所有语言/区域 | N/A | DrawableDescriptor 生命周期和错误码契约不依赖语言、区域或排序规则。 | N/A | N/A |

**不涉及理由：** 不涉及文案、资源本地化、区域格式或语言切换。

---

### 5.7 是否涉及深浅色模式

**是否涉及：** N/A

| 模式/切换场景 | 对外预期 | UX 效果 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|
| 深色模式 | 生命周期行为不变 | 无额外 UX 效果 | N/A | N/A |
| 浅色模式 | 生命周期行为不变 | 无额外 UX 效果 | N/A | N/A |
| 深浅色切换 | 不影响 released 状态和 API 契约 | 无可观察主题差异 | N/A | N/A |

**不涉及理由：** `spec.md` 明确不改变资源选择或主题适配。

---

### 5.8 是否涉及新材质

**是否涉及：** N/A

| 材质档位/场景 | 对外预期 | UX 效果图/链接 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|
| 档位1 | N/A | N/A | N/A | N/A |
| 档位2 | N/A | N/A | N/A | N/A |
| 档位3 | N/A | N/A | N/A | N/A |

**不涉及理由：** 本次不新增视觉材质、材质档位或效果图要求。

---

### 5.9 是否涉及无障碍

**是否涉及：** N/A

| AC编号 | 验收标准（WHEN/THEN 格式） | 类型 | 测试侧验证方式 |
|---|---|---|---|
| N/A | DrawableDescriptor 对象生命周期不参与无障碍树或辅助功能语义。 | N/A | N/A |

**不涉及理由：** 无 UI 节点、文本、焦点、语义属性或无障碍事件变更。

---

### 5.10 是否涉及多设备差异

**是否涉及：** 否

| 设备类型 | 差异化描述 | 关联 AC | 是否需要验证 | 测试侧验证方式 |
|---|---|---|---|---|
| 手机 | 无差异 | AC-1.6、AC-3.1 至 AC-3.5 | 否，不需要差异化验证 | 主支持设备上的 API 行为验证可覆盖。 |
| Pad | 无差异 | AC-1.6、AC-3.1 至 AC-3.5 | 否，不需要差异化验证 | 主支持设备上的 API 行为验证可覆盖。 |
| PC | 规格未定义差异 | N/A | 否 | N/A |
| 穿戴 | 规格未定义差异 | N/A | 否 | N/A |
| 智慧屏 | 规格未定义差异 | N/A | 否 | N/A |
| 座舱 | 规格未定义差异 | N/A | 否 | N/A |
| 其他 | 折叠屏无差异 | AC-1.6、AC-3.1 至 AC-3.5 | 否，不需要差异化验证 | 主支持设备上的 API 行为验证可覆盖。 |

**不涉及理由：** `spec.md` 明确手机、平板和折叠屏无形态差异，本次不定义多设备差异化行为。

---

### 5.11 是否涉及适老化

**是否涉及：** N/A

| AC编号 | 验收标准（WHEN/THEN 格式） | 类型 | 测试侧验证方式 |
|---|---|---|---|
| N/A | DrawableDescriptor 对象生命周期不依赖年龄、字体、尺寸或辅助交互配置。 | N/A | N/A |

**不涉及理由：** 不涉及字体缩放、简易模式、触控目标、读屏或其他适老化要求。

---

### 5.12 是否涉及资料新增或变更

**是否涉及：** 否

| 资料类型 | 新增/变更内容 | 链接或路径 | 关联 AC | 验证方式 |
|---|---|---|---|---|
| 开发者资料/API 文档/示例 | 本次不新增或变更资料交付要求；SDK 声明已存在。 | N/A | N/A | 确认对外 API 契约与现有声明一致。 |

**不涉及理由：** `spec.md` 未要求新增开发者资料、API 文档或示例，不得在测试交付件中扩展范围。

---

## 六、非功能性需求 `[源: spec.md]`

> 先读取以下来源规格，再把适用项展开为可直接转化为测试用例的条件、指标和测试侧验证方式。

<!-- GENERATED:NFR-SPEC:BEGIN -->
### 非功能性需求

| 类型 | 指标/阈值 |
|---|---|
| 性能 | 未调用 `release()` 的既有调用路径无用户可感知行为变化。 |
| 安全 | 不新增权限，不处理隐私数据。 |
| 可靠性 | 重复 release、release 后访问、异步 load 与 release 交错不崩溃。 |
| 可测试性 | P0/P1 AC 可通过 previewer 可执行用例或明确替代审查验证。 |

### 多设备适配声明

| 设备类型 | 行为差异 |
|---|---|
| 手机 | 无差异 |
| 平板 | 无差异 |
| 折叠屏 | 无差异 |

### 全局特性影响

| 特性 | 适用？ |
|---|---|
| 无障碍 | N/A |
| 大字体 | N/A |
| 深色模式 | N/A |
| 多窗口/分屏 | N/A |
| 多用户 | N/A |
| 版本升级 | 是 |
| 生态兼容 | 是 |
<!-- GENERATED:NFR-SPEC:END -->

### 6.1 是否涉及性能指标

**是否涉及：** N/A

| 规格描述（WHEN/THEN 格式） | 验证指标 | 目标值/阈值 | 场景与数据规模 | 测试侧验证方式 | 关联 AC |
|---|---|---|---|---|---|
| WHEN 未调用 `release()` 并使用既有调用路径 THEN 用户可观察行为保持不变。 | 用户可观察行为兼容性 | 与变更前一致；规格未定义独立时延、吞吐或内存阈值。 | 既有加载、分层、动画、Picture/HDR 代表性使用场景。 | 变更前后对外行为对照。 | AC-1.6 |

**不涉及理由：** `spec.md` 只规定“无用户可感知行为变化”，未给出可量化性能指标；因此不新增独立性能阈值，该要求按 AC-1.6 兼容性验证。

---

### 6.2 是否涉及功耗指标

**是否涉及：** N/A

| 规格描述（WHEN/THEN 格式） | 验证指标 | 目标值/阈值 | 测试场景 | 测试侧验证方式 | 关联 AC |
|---|---|---|---|---|---|
| N/A | N/A | N/A | N/A | N/A | N/A |

**不涉及理由：** `spec.md` 未定义功耗、能效、待机或温升指标，本次不涉及可观察功耗变化。

---

### 6.3 是否涉及稳定性 & 可靠性

**是否涉及：** 是

| 指标项 | 目标值 | 测试场景 | 故障/恢复条件 | 验证方法 | 关联 AC |
|---|---|---|---|---|---|
| 重复 release 稳定性 | 无崩溃，`isReleased()` 始终返回 `true` | 同一 Dynamic 对象首次 release 后多次重复 release | 无需恢复；对象保持 released | 观察调用返回、进程稳定性和释放状态 | AC-1.2 |
| release 后访问稳定性 | 访问型 API 稳定返回 `111002`，控制/刷新类 API 无操作且无崩溃 | 各类 Dynamic descriptor 释放后的指定 API 调用 | 无需恢复；不得重新绑定 | 观察异常码、Promise reject、无操作返回和 `isReleased()` 状态 | AC-1.4、AC-1.5、AC-2.2 |
| 异步 load 与 release 交错可靠性 | 已发起 Promise 安全完成，无崩溃，不重新绑定 released 对象 | `load()` 发起后、Promise 完成前调用 `release()` | 原 Promise 按已发起语义完成，对象保持 released | 观察 Promise 完成、进程稳定性和完成后 `isReleased()` 结果 | AC-2.1 |

**不涉及理由：** N/A，本项涉及。

---

### 6.4 是否涉及安全隐私合规

**是否涉及：** 否

| 类型 | 规格描述（WHEN/THEN 格式） | 数据/权限边界 | 预期结果 | 测试侧验证方式 | 关联 AC |
|---|---|---|---|---|---|
| 隐私合规 | N/A | 不处理用户数据或隐私数据 | 无隐私合规行为变更 | N/A | N/A |
| 信息安全 | N/A | 不新增权限、跨进程数据传输或安全边界 | 无新的安全威胁表面 | N/A | N/A |
| 安全编码约束 | N/A | 对外规格不定义新的安全编码契约 | 不新增对外行为 | N/A | N/A |

**不涉及理由：** `spec.md` 明确不新增权限且不处理隐私数据，本次没有用户可观察的安全隐私合规变更。

---

### 6.5 是否涉及 DFX

**是否涉及：** 是

| 维度 | 规格描述（WHEN/THEN 格式） | 可观察信息 | 隐私/脱敏要求 | 测试侧验证方式 | 关联 AC |
|---|---|---|---|---|---|
| 可测试性 | WHEN 调用生命周期和释放后访问 API THEN 通过布尔值、同步异常、Promise 结果和无操作返回观察行为。 | `isReleased()` 结果、`BusinessError 111002`、Promise 完成状态、进程稳定性 | 不涉及隐私数据 | ArkTS API 行为验证、NAPI/ANI 集成验证、NDK 兼容性验证 | AC-1.1 至 AC-3.5 |
| 自动化维测 | 本次不新增运行时统计、健康指标或维测接口。 | N/A | N/A | N/A | N/A |
| 定界定位 | WHEN 释放后调用指定访问型 API THEN 对外错误码为 `111002`。 | 异常码或 Promise reject 错误码 | 错误信息不包含用户隐私数据 | 错误码和 API 分组契约验证 | AC-1.4、AC-2.2 |

**不涉及理由：** N/A，可测试性和错误定界信息涉及本项。

---

## 七、2C 功能体验分析

> 本章为测试独有内容，覆盖 UX、交互和用户数据相关测试维度。

### 7.1 是否涉及 UX — 静态 UI 效果

**是否涉及：** N/A

| 效果编号 | 触发条件（WHEN） | 预期结果（THEN） | 共存属性/边界 | UX 效果图 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|---|
| N/A | N/A | N/A | 不改变布局、绘制、颜色、尺寸或图像呈现契约 | N/A | N/A | N/A |

**不涉及理由：** 本次变更是 DrawableDescriptor 对象生命周期 API 行为，不定义新的静态 UI 效果。

---

### 7.2 是否涉及 UX — 动态 UI 效果（动效）

**是否涉及：** N/A

| 效果编号 | 触发条件（WHEN） | 预期结果（THEN） | 动效过程/时序 | UX 效果图 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|---|
| N/A | N/A | N/A | 不新增动画、转场、帧时序或动效中断/恢复契约 | N/A | N/A | N/A |

**不涉及理由：** 异步 `load()` 的 Promise 生命周期不等同于 UI 动效，本次不定义动态 UI 效果。

---

### 7.3 是否涉及 UX — 手势/事件/交互/焦点

**是否涉及：** N/A

| 交互类型 | 触发条件（WHEN） | 预期结果（THEN） | 焦点/状态变化 | UX 效果图 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|---|
| 交互 | N/A | N/A | 无交互状态变化 | N/A | N/A | N/A |
| 拖拽 | N/A | N/A | 无拖拽状态变化 | N/A | N/A | N/A |
| 手势/事件 | N/A | N/A | 无手势或 UI 事件状态变化 | N/A | N/A | N/A |
| 焦点 | N/A | N/A | 无焦点变化 | N/A | N/A | N/A |

**不涉及理由：** `release()` / `isReleased()` 是编程接口，本次不改变手势、事件分发、拖拽、焦点或用户交互流程。

---

### 7.4 是否涉及用户数据

**是否涉及：** N/A

| 测试场景 | 触发条件（WHEN） | 预期结果（THEN） | 数据边界/兼容性 | 关联 AC | 测试侧验证方式 |
|---|---|---|---|---|---|
| 数据生产 | N/A | 不产生用户持久化数据 | N/A | N/A | N/A |
| 数据使用 | N/A | 不读取或处理用户持久化数据 | N/A | N/A | N/A |
| 重启恢复 | N/A | released 是对象实例生命周期状态，无跨进程重启恢复契约 | N/A | N/A | N/A |
| 版本升级 | API 26.0.0 起补齐 Dynamic 运行时行为 | 未 release 旧路径保持不变，但不涉及用户数据迁移 | AC-1.6、AC-3.1 至 AC-3.5 | 版本升级后 API 兼容性验证 |
| 数据克隆 | N/A | 无用户数据克隆或迁移契约 | N/A | N/A | N/A |

**不涉及理由：** 本次不涉及用户持久化数据、重启恢复或克隆迁移；版本升级影响属于 API 行为兼容，已在 5.2 分析。

---

## 八、AC 到验证点追溯

<!-- GENERATED:AC-VERIFICATION:BEGIN -->
| AC | 对外预期 | 验证点 | 测试侧验证方式 |
|---|---|---|---|
| AC-1.1 | 见对外行为规格 | Dynamic DrawableDescriptor 及各子类首次 `release()` 后状态切换为 released，`isReleased()` 返回 `true`。 | 对各类 Dynamic descriptor 调用生命周期 API，观察返回值和进程稳定性。 |
| AC-1.2 | 见对外行为规格 | 同一 Dynamic 对象重复 `release()` 直接返回、无崩溃，状态仍为 released。 | 首次 release 后多次重复调用，观察返回和 `isReleased()` 结果。 |
| AC-1.3 | 见对外行为规格 | 新建且未 release 的 Dynamic 对象 `isReleased()` 返回 `false`。 | 对新建 Dynamic descriptor 在任何 release 调用前读取状态。 |
| AC-1.4 | 见对外行为规格 | 释放后 `getPixelMap/getForeground/getBackground/getMask/loadSync` 同步抛 `111002`，新发起 `load()` reject `111002`。 | 按 API 所属 descriptor 类型调用全部指定访问型 API，核对同步异常和 Promise reject 的 BusinessError 代码。 |
| AC-1.5 | 见对外行为规格 | 释放后 `invalidate/setHdrComposition/getAnimationController/setBlendMode` 无操作返回、无崩溃，且不恢复绑定。 | 调用全部指定控制/刷新类 API，观察返回、进程稳定性和后续 `isReleased()` 仍为 `true`。 |
| AC-1.6 | 见对外行为规格 | 未 release 时既有加载、分层、动画、Picture/HDR 功能的用户可观察结果不变。 | 使用代表性输入对照变更前后的 API 返回、Promise 结果和可观察图像行为。 |
| AC-2.1 | 见对外行为规格 | 未 release 时已发起的 `load()` 在随后 release 后仍安全完成，不崩溃且不重新绑定。 | 在可控异步加载场景中于 Promise 完成前调用 `release()`，观察原 Promise 完成和完成后 released 状态。 |
| AC-2.2 | 见对外行为规格 | 已 released 对象新调用 `load()` 时 Promise reject `BusinessError 111002`。 | 先 release，再新发起 `load()`，核对 Promise reject 错误类型和错误码。 |
| AC-3.1 | 见对外行为规格 | Static 已释放对象 `getPixelMap()` 返回 `undefined`，不抛 `111002`。 | 在 Static ArkTS 调用环境中释放对象后观察 `getPixelMap()` 返回和异常情况。 |
| AC-3.2 | 见对外行为规格 | Static 已释放对象 `loadSync()` 返回、`load()` resolve `imageWidth=-1,imageHeight=-1`。 | 在 Static ArkTS 调用环境中分别观察同步返回和 Promise resolve 结果。 |
| AC-3.3 | 见对外行为规格 | 从已释放 Dynamic 或 Static 对象提取 native descriptor 返回参数错误，不产生新的有效 descriptor。 | 通过 NAPI/ANI 集成调用观察提取结果、错误类型和输出句柄有效性。 |
| AC-3.4 | 见对外行为规格 | 前端 release 不使已提取的 C 侧 `ArkUI_DrawableDescriptor*` 句柄失效，句柄仍由 Dispose 管理。 | 先提取 C 侧句柄，再 release 前端对象，通过 NDK 集成兼容性验证观察句柄生命周期。 |
| AC-3.5 | 见对外行为规格 | `OH_ArkUI_DrawableDescriptor_Dispose` 签名、结构布局、错误码和生命周期语义保持不变。 | 执行对外头文件/ABI 契约比对和 NDK 调用兼容性验证。 |
<!-- GENERATED:AC-VERIFICATION:END -->

### 测试可观察性与验证约束 `[源: design.md]`

<!-- GENERATED:DESIGN-CONSTRAINTS:BEGIN -->
未提供独立的测试输入约束。生成 Agent 必须结合 `spec.md` 的对外行为和实际可观察表面完成验证点分析；如缺少可观察能力，回修 `design.md`。
<!-- GENERATED:DESIGN-CONSTRAINTS:END -->

## 九、测试输入完备性

- 2D 分析已逐项给出涉及性、范围、关联 AC、验证方式或 N/A 理由。
- NFR 已保留规格中的对外要求，展开可靠性和可测试性，未为性能、功耗或安全隐私发明新指标。
- 2C 已确认不涉及静态 UI、动效、交互/焦点或用户持久化数据，并记录具体理由。
- AC-1.1 至 AC-3.5 共 13 条验收标准均已建立测试可观察验证点。
- 具体测试用例、数据组合、环境矩阵和执行结果不属于本交付件，应写入后续测试设计或测试管理系统。
<!-- TEST-ANALYSIS:END -->

## 十、参考资料

| 文档 | 路径 | 状态/Hash |
|---|---|---|
| spec.md | `spec.md` | Approved / `b9d8964d8f55d5145740ea59ea371185745198498851fdea9b1813a403f18c60` |
| design.md | `design.md` | Approved / `bee10616eb1e6a2323958e2e05273866aec86230101c49d4de0c0f4d41d2f87d` |
| Profile playbook | `analysis/arkui/spec-for-test.md` | Active |

## 十一、来源与审批

| 项 | 内容 |
|---|---|
| Spec 来源 | `spec.md` / `b9d8964d8f55d5145740ea59ea371185745198498851fdea9b1813a403f18c60` |
| Design 来源 | `design.md` / `bee10616eb1e6a2323958e2e05273866aec86230101c49d4de0c0f4d41d2f87d` |
| 开发/Spec Owner 结论 | 待审批 |
| 测试 Owner 结论 | 待审批 |

## 附录：术语表

| 术语 | 定义 |
|---|---|
| 2D | 能力特征维度分析 |
| 2C | 功能体验维度分析 |

---

**格式说明：**

1. 第一至四章来自 `spec.md`，不得摘要、删减或手工改写。
2. 第五章 2D、第六章 NFR 验证细项、第七章 2C 为测试输入分析区。
3. 每个“是否涉及”小节选择“是”时必须完成后续字段；选择“否/N/A”时必须填写不涉及理由。
4. `spec-for-test.md` 只描述对外行为和测试侧验证输入，不记录开发自验证类型、用例、命令或执行结果。
