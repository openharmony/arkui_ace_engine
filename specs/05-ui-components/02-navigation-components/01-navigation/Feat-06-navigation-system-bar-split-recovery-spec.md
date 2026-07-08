# 特性规格

> Func-05-02-01-Feat-06 Navigation 系统栏/安全区/分栏/恢复：固化 systemBarStyle（SystemBarStyle from @ohos.window）、BarStyle（STANDARD/STACK/SAFE_AREA_PADDING）、divider（NavigationDividerStyle since 23）、enableDragBar（since 14）、splitPlaceholder（since 20）、recoverable（since 14）、enableVisibilityLifecycleWithContentCover（since 21）、NavigationDividerStyle、NavigationSplitPolicy（since 26）的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 系统栏/安全区/分栏/恢复 |
| 特性编号 | Func-05-02-01-Feat-06 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P1 |
| 目标版本 | API 8 起支持系统栏配置，BarStyle API 9，enableDragBar/recoverable API 14，splitPlaceholder API 20，divider API 23，NavigationSplitPolicy API 26 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 中 |

## 本次变更范围（Delta）

无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |
| Navigation Layout Property | `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h` | — |

---

## 用户故事

### US-1: 配置系统栏样式

**作为** 应用开发者,
**我想要** 通过 `systemBarStyle()` 配置 Navigation 状态栏和导航栏的样式,
**以便** 控制系统栏的颜色、内容和可见性。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.systemBarStyle(style: SystemBarStyle)` THEN Navigation 状态栏和导航栏按 SystemBarStyle 配置样式 | 正常 |
| AC-1.2 | WHEN SystemBarStyle 来自 @ohos.window THEN SystemBarStyle 属性（statusBarColor/statusBarContentColor/navigationBarColor/navigationBarContentColor）被正确解析 | 正常 |
| AC-1.3 | WHEN 未设置 systemBarStyle THEN 使用系统默认系统栏样式 | 边界 |

### US-2: 配置 BarStyle 模式

**作为** 应用开发者,
**我想要** 通过 `barStyle()` 配置 NavBar 的 BarStyle 模式（STANDARD/STACK/SAFE_AREA_PADDING）,
**以便** 控制 NavBar 与系统栏的避让关系。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.barStyle(BarStyle.STANDARD)` THEN NavBar 不避让安全区，与内容区域正常叠加 | 正常 |
| AC-2.2 | WHEN 调用 `.barStyle(BarStyle.STACK)` THEN NavBar 避让安全区，标题栏内容嵌入安全区区域 | 正常 |
| AC-2.3 | WHEN 调用 `.barStyle(BarStyle.SAFE_AREA_PADDING)` THEN NavBar 避让安全区，标题栏内容使用安全区 padding | 正常 |
| AC-2.4 | WHEN 未设置 barStyle THEN 默认为 STANDARD 模式 | 边界 |

### US-3: 配置分栏特性

**作为** 应用开发者,
**我想要** 通过 `divider()`、`enableDragBar()`、`splitPlaceholder()` 和 `recoverable()` 配置分栏模式的分隔线、拖拽条、占位内容和恢复能力,
**以便** 增强 Split 模式的交互体验和数据恢复能力。

| AC编号 | 醉收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.divider(style: NavigationDividerStyle)`（API 23 新增）THEN Split 模式下 NavBar 和 Content 之间显示分隔线样式 | 正常 |
| AC-3.2 | WHEN 调用 `.enableDragBar(true)`（API 14 新增）THEN Split 模式下 NavBar 和 Content 之间显示拖拽条，可拖拽调整宽度 | 正常 |
| AC-3.3 | WHEN 调用 `.enableDragBar(false)` THEN Split 模式下不显示拖拽条 | 边界 |
| AC-3.4 | WHEN 调用 `.splitPlaceholder(value: CustomBuilder)`（API 20 新增）THEN Split 模式下 Content 区域无 NavDestination 时显示占位内容 | 正常 |
| AC-3.5 | WHEN 调用 `.recoverable(true)`（API 14 新增）THEN Navigation 模式切换时可恢复 NavDestination 状态 | 正常 |
| AC-3.6 | WHEN 调用 `.recoverable(false)` THEN Navigation 模式切换时不恢复 NavDestination 状态 | 边界 |

### US-4: 配置可见性生命周期

**作为** 应用开发者,
**我想要** 通过 `enableVisibilityLifecycleWithContentCover()` 控制 NavDestination 在 ContentCover 遮盖时的生命周期行为,
**以便** 管理 NavDestination 在半模态遮盖场景下的可见性状态。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.enableVisibilityLifecycleWithContentCover(true)`（API 21 新增）THEN NavDestination 被 ContentCover 遮盖时触发不可见生命周期回调 | 正常 |
| AC-4.2 | WHEN 调用 `.enableVisibilityLifecycleWithContentCover(false)` THEN NavDestination 被 ContentCover 遮盖时不触发生命周期回调 | 边界 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 systemBarStyle |
| AC-1.2 | US-1 | R-1 | 单元测试 SystemBarStyle 属性解析 |
| AC-1.3 | US-1 | R-1 | 代码审查 NavigationPattern 默认 systemBarStyle |
| AC-2.1 | US-2 | R-2 | 单元测试 barStyle STANDARD |
| AC-2.2 | US-2 | R-2 | 单元测试 barStyle STACK |
| AC-2.3 | US-2 | R-2 | 单元测试 barStyle SAFE_AREA_PADDING |
| AC-2.4 | US-2 | R-2 | 代码审查 NavigationPattern 默认 barStyle |
| AC-3.1 | US-3 | R-3 | 单元测试 divider NavigationDividerStyle |
| AC-3.2 | US-3 | R-4 | 单元测试 enableDragBar true |
| AC-3.3 | US-3 | R-4 | 单元测试 enableDragBar false |
| AC-3.4 | US-3 | R-5 | 单元测试 splitPlaceholder |
| AC-3.5 | US-3 | R-6 | 单元测试 recoverable true |
| AC-3.6 | US-3 | R-6 | 单元测试 recoverable false |
| AC-4.1 | US-4 | R-7 | 单元测试 enableVisibilityLifecycleWithContentCover true |
| AC-4.2 | US-4 | R-7 | 单元测试 enableVisibilityLifecycleWithContentCover false |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | systemBarStyle 配置系统栏样式：SystemBarStyle 来自 @ohos.window，包含 statusBarColor/statusBarContentColor/navigationBarColor/navigationBarContentColor 等属性；未设置时使用系统默认样式 | — | AC-1.1~AC-1.3 |
| R-2 | 行为 | — | barStyle 配置 NavBar 避让模式：STANDARD=0（不避让安全区，与内容正常叠加）、STACK=1（避让安全区，标题栏嵌入安全区）、SAFE_AREA_PADDING=2（避让安全区，标题栏使用安全区 padding）；默认 STANDARD | — | AC-2.1~AC-2.4 |
| R-3 | 行为 | — | divider 配置分栏分隔线样式（API 23 新增）：NavigationDividerStyle 定义分隔线颜色和宽度属性 | API 23 新增 | AC-3.1 |
| R-4 | 行为 | — | enableDragBar 启用分栏拖拽条（API 14 新增）：true 时 Split 模式下显示拖拽条，可拖拽调整 NavBar 和 Content 宽度；false 时不显示拖拽条 | API 14 新增 | AC-3.2, AC-3.3 |
| R-5 | 行为 | — | splitPlaceholder 配置分栏占位内容（API 20 新增）：CustomBuilder 构建的占位内容在 Split 模式下 Content 区域无 NavDestination 时显示 | API 20 新增 | AC-3.4 |
| R-6 | 行为 | — | recoverable 配置模式切换恢复（API 14 新增）：true 时 Navigation 模式切换（Stack↔Split）可恢复 NavDestination 状态；false 时不恢复 | API 14 新增 | AC-3.5, AC-3.6 |
| R-7 | 行为 | — | enableVisibilityLifecycleWithContentCover 配置 ContentCover 遮盖可见性生命周期（API 21 新增）：true 时 NavDestination 被 ContentCover 遮盖触发不可见生命周期回调；false 时不触发 | API 21 新增 | AC-4.1, AC-4.2 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` systemBarStyle |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` SystemBarStyle 属性 |
| VM-3 | AC-1.3 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 systemBarStyle |
| VM-4 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` barStyle STANDARD |
| VM-5 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` barStyle STACK |
| VM-6 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` barStyle SAFE_AREA_PADDING |
| VM-7 | AC-2.4 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 barStyle |
| VM-8 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` divider |
| VM-9 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableDragBar true |
| VM-10 | AC-3.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableDragBar false |
| VM-11 | AC-3.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` splitPlaceholder |
| VM-12 | AC-3.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` recoverable true |
| VM-13 | AC-3.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` recoverable false |
| VM-14 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableVisibilityLifecycleWithContentCover true |
| VM-15 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableVisibilityLifecycleWithContentCover false |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `systemBarStyle(style: SystemBarStyle): NavigationAttribute` | Public | navigation.d.ts | API 8 | Public | 配置系统栏样式 |
| `barStyle(style: BarStyle): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 配置 NavBar 避让模式 |
| `enableDragBar(enable: boolean): NavigationAttribute` | Public | navigation.d.ts | API 14 | Public | 启用分栏拖拽条 |
| `splitPlaceholder(value: CustomBuilder): NavigationAttribute` | Public | navigation.d.ts | API 20 | Public | 配置分栏占位内容 |
| `recoverable(enable: boolean): NavigationAttribute` | Public | navigation.d.ts | API 14 | Public | 配置模式切换恢复 |
| `divider(style: NavigationDividerStyle): NavigationAttribute` | Public | navigation.d.ts | API 23 | Public | 配置分栏分隔线样式 |
| `enableVisibilityLifecycleWithContentCover(enable: boolean): NavigationAttribute` | Public | navigation.d.ts | API 21 | Public | 配置 ContentCover 遮盖可见性生命周期 |

**关联类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `SystemBarStyle` | 来自 @ohos.window，包含 statusBarColor/statusBarContentColor/navigationBarColor/navigationBarContentColor | API 8 |
| `BarStyle` | `{ STANDARD=0, STACK=1, SAFE_AREA_PADDING=2 }` | API 9 |
| `NavigationDividerStyle` | 分隔线样式（颜色、宽度等） | API 23 |
| `NavigationSplitPolicy` | 分栏策略配置（API 26 新增） | API 26 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 8 | systemBarStyle 基础接口 | 系统栏样式配置 | 无需迁移 |
| API 9 | BarStyle 三种避让模式新增 | NavBar 避让行为可配置 | 默认 STANDARD，旧代码无影响 |
| API 14 | enableDragBar/recoverable 新增 | 分栏拖拽和模式恢复 | 未设置时默认不显示拖拽条、不恢复 |
| API 20 | splitPlaceholder 新增 | 分栏占位内容 | 未设置时 Content 区域无 NavDestination 时空白 |
| API 21 | enableVisibilityLifecycleWithContentCover 新增 | ContentCover 生命周期 | 未设置时默认不触发生命周期回调 |
| API 23 | divider 新增 | 分栏分隔线样式 | 未设置时默认无分隔线 |
| API 26 | NavigationSplitPolicy 新增 | 分栏策略配置 | 旧分栏行为不变 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 系统栏样式来源 | SystemBarStyle 来自 @ohos.window 模块，Navigation 仅使用其属性 |
| BarStyle 与安全区联动 | BarStyle.STACK/SAFE_AREA_PADDING 与 IAvoidInfoListener 安全区避让机制联动 |
| 分栏特性仅 Split 模式 | divider/enableDragBar/splitPlaceholder 仅在 Split 模式下生效 |
| recoverable 模式切换 | recoverable 在 Stack↔Split 模式切换时恢复 NavDestination 状态 |
| ContentCover 生命周期 | enableVisibilityLifecycleWithContentCover 与 NavDestination 的 onPageShow/onPageHide 生命周期联动 |

---

## 非性需求

| 维度 | 要求 |
|------|------|
| 性能 | systemBarStyle/barStyle 属性直接写入 Property，无额外开销；enableDragBar 拖拽操作在 UI 线程执行 |
| 可调试性 | NavigationPattern 支持 DumpInfo 输出 systemBarStyle/barStyle/enableDragBar 等属性 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | BarStyle.STANDARD 为默认，Stack 模式为主 | — | 单元测试 | — |
| 平板 | Split 模式下 enableDragBar 拖拽条有效 | 拖拽调整 NavBar/Content 宽度 | 单元测试 | — |
| 折叠屏 | recoverable 在折叠/展开模式切换时恢复 NavDestination 状态 | — | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| 安全区避让 | BarStyle.STACK/SAFE_AREA_PADDING 参与全局安全区避让机制 |
| 系统栏样式 | systemBarStyle 影响全局系统栏颜色和内容 |
| ContentCover 生命周期 | enableVisibilityLifecycleWithContentCover 影响全局 NavDestination 生命周期管理 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异（enableDragBar/recoverable API 14、splitPlaceholder API 20、divider API 23、NavigationSplitPolicy API 26）
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，系统栏/安全区/分栏配置管理 |
| `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h` | 布局属性，barStyle 等属性定义 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
