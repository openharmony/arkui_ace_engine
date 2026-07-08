# 特性规格

> Func-05-02-01-Feat-01 Navigation 创建与布局模式：固化 Navigation 容器创建、NavigationMode（Stack/Split/Auto/AUTO_WITH_ASPECT_RATIO）、navBarWidth/navBarPosition/navBarWidthRange/minContentWidth/hideNavBar/ignoreLayoutSafeArea/enableModeChangeAnimation/configuration 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 创建与布局模式 |
| 特性编号 | Func-05-02-01-Feat-01 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 8 起支持，核心增强集中于 API 9-12，AUTO_WITH_ASPECT_RATIO 在 API 26 新增 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

> 历史规格补齐，补录已有实现的完整行为规格。范围包括 Navigation 创建接口（三种构造方式）、NavigationMode 四种模式、NavBar 宽度/位置/范围约束、最小内容宽度、隐藏导航栏、安全区避让配置、模式切换动画、运行参数配置。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |
| Navigation Layout Algorithm | `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp` | — |

---

## 用户故事

### US-1: 创建 Navigation 容器并选择导航模式

**作为** 应用开发者,
**我想要** 使用 `Navigation()` 或 `Navigation(NavPathStack)` 创建导航容器并通过 `mode()` 选择 Stack/Split/Auto 导航模式,
**以便** 在应用中实现单页导航、分栏导航或自适应导航。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `Navigation()` 无参创建 THEN 创建默认 Stack 模式的 Navigation 容器，内部创建空 NavPathStack | 正常 |
| AC-1.2 | WHEN 调用 `Navigation(navPathStack)` 传入 NavPathStack THEN 创建 Navigation 容器，使用传入的 NavPathStack 作为路由栈 | 正常 |
| AC-1.3 | WHEN 调用 `Navigation(navPathStack, homePathInfo)` THEN 创建 Navigation 容器，使用传入的 NavPathStack 并设置 HomePathInfo 作为首页信息 | 正常 |
| AC-1.4 | WHEN 调用 `.mode(NavigationMode.Stack)` THEN Navigation 进入 Stack 模式，NavBar 和 NavDestination 以栈形式叠加显示 | 正常 |
| AC-1.5 | WHEN 调用 `.mode(NavigationMode.Split)` THEN Navigation 进入 Split 模式，NavBar 和 Content 并列显示 | 正常 |
| AC-1.6 | WHEN 调用 `.mode(NavigationMode.Auto)` THEN Navigation 根据容器宽度自动选择 Stack 或 Split 模式 | 正常 |
| AC-1.7 | WHEN 调用 `.mode(NavigationMode.AUTO_WITH_ASPECT_RATIO)` THEN Navigation 根据 NavBar 与 Content 宽度比例自动选择模式（API 26 新增） | 边界 |
| AC-1.8 | WHEN 未调用 mode() THEN 默认导航模式为 Stack | 正常 |

### US-2: 配置 NavBar 宽度和位置

**作为** 应用开发者,
**我想要** 通过 `navBarWidth()` 和 `navBarPosition()` 配置分栏模式下导航栏的宽度和位置,
**以便** 控制 NavBar 在 Split 模式下的布局参数。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.navBarWidth(value)` THEN Split 模式下 NavBar 宽度被设置为 value，默认 240vp | 正常 |
| AC-2.2 | WHEN 调用 `.navBarPosition(NavBarPosition.START)` THEN NavBar 显示在左侧（默认位置） | 正常 |
| AC-2.3 | WHEN 调用 `.navBarPosition(NavBarPosition.END)` THEN NavBar 显示在右侧 | 正常 |
| AC-2.4 | WHEN 未设置 navBarPosition THEN 默认位置为 START | 正常 |

### US-3: 隐藏 NavBar

**作为** 应用开发者,
**我想要** 通过 `hideNavBar()` 隐藏导航栏,
**以便** 在需要时将 NavBar 完全隐藏，仅显示 NavDestination 内容区域。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.hideNavBar(true)` THEN NavBar 区域被隐藏，Content 区域占满全宽 | 正常 |
| AC-3.2 | WHEN 调用 `.hideNavBar(false)` 或重置 THEN NavBar 区域恢复显示 | 正常 |
| AC-3.3 | WHEN Stack 模式下 hideNavBar(true) THEN 仅显示 NavDestination 内容，不显示 NavBar | 边界 |

### US-4: 配置分栏宽度范围和最小内容宽度

**作为** 应用开发者,
**我想要** 通过 `navBarWidthRange()` 和 `minContentWidth()` 配置分栏模式下 NavBar 宽度范围约束和 Content 最小宽度,
**以便** 确保 Split/Auto 模式下 NavBar 和 Content 区域的宽度不会过窄或过宽。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.navBarWidthRange({ min, max })` THEN NavBar 宽度被约束在 [min, max] 范围内 | 正常 |
| AC-4.2 | WHEN NavBar 宽度小于 navBarWidthRange.min THEN NavBar 宽度被钳位到 min 值 | 边界 |
| AC-4.3 | WHEN NavBar 宽度大于 navBarWidthRange.max THEN NavBar 宽度被钳位到 max 值 | 边界 |
| AC-4.4 | WHEN 调用 `.minContentWidth(value)` THEN Split/Auto 模式下 Content 区域最小宽度为 value，默认 360vp | 正常 |
| AC-4.5 | WHEN Content 区域剩余宽度小于 minContentWidth THEN Auto 模式切换为 Stack 模式 | 边界 |
| AC-4.6 | WHEN 未设置 navBarWidthRange THEN NavBar 宽度无范围约束，仅受 navBarWidth 限制 | 正常 |

### US-5: 配置导航模式切换动画

**作为** 应用开发者,
**我想要** 通过 `enableModeChangeAnimation()` 控制 Stack/Split 模式切换时的动画效果,
**以便** 在模式切换时提供平滑过渡或禁用动画。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `.enableModeChangeAnimation(true)` THEN Navigation 在 Stack/Split 模式切换时播放过渡动画 | 正常 |
| AC-5.2 | WHEN 调用 `.enableModeChangeAnimation(false)` THEN Navigation 在模式切换时无动画，直接切换布局 | 正常 |
| AC-5.3 | WHEN 未设置 enableModeChangeAnimation THEN 默认开启模式切换动画 | 边界 |

### US-6: 配置 Navigation 运行参数

**作为** 应用开发者,
**我想要** 通过 `configuration()` 设置 Navigation 运行参数（如栈大小限制）,
**以便** 控制 Navigation 的运行行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `.configuration({ maxNavStackCount: N })` THEN NavPathStack 最大栈深度被限制为 N | 正常 |
| AC-6.2 | WHEN NavPathStack 深度超过 maxNavStackCount THEN 超出的 NavDestination 不被推入栈 | 边界 |
| AC-6.3 | WHEN 未设置 configuration THEN 不限制栈深度 | 正常 |
| AC-6.4 | WHEN configuration 为 NavigationConfiguration 对象 THEN 支持按字段设置运行参数 | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 NavigationModelNG Create |
| AC-1.2 | US-1 | R-2 | 单元测试 NavigationModelNG Create with NavPathStack |
| AC-1.3 | US-1 | R-2 | 单元测试 NavigationModelNG Create with NavPathStack + HomePathInfo |
| AC-1.4 | US-1 | R-3 | 单元测试 NavigationMode Stack |
| AC-1.5 | US-1 | R-3 | 单元测试 NavigationMode Split |
| AC-1.6 | US-1 | R-3 | 单元测试 NavigationMode Auto |
| AC-1.7 | US-1 | R-3, R-8 | 代码审查 NavigationLayoutAlgorithm AUTO_WITH_ASPECT_RATIO 分支 |
| AC-1.8 | US-1 | R-1 | 代码审查 NavigationPattern 默认模式 |
| AC-2.1 | US-2 | R-4 | 单元测试 navBarWidth |
| AC-2.2 | US-2 | R-4 | 单元测试 navBarPosition START |
| AC-2.3 | US-2 | R-4 | 单元测试 navBarPosition END |
| AC-2.4 | US-2 | R-4 | 代码审查 NavigationLayoutProperty 默认 navBarPosition |
| AC-3.1 | US-3 | R-7 | 单元测试 hideNavBar true |
| AC-3.2 | US-3 | R-7 | 单元测试 hideNavBar false/reset |
| AC-3.3 | US-3 | R-7 | 代码审查 NavigationLayoutAlgorithm hideNavBar 分支 |
| AC-4.1 | US-4 | R-5 | 单元测试 navBarWidthRange |
| AC-4.2 | US-4 | R-5 | 单元测试 navBarWidthRange clamp min |
| AC-4.3 | US-4 | R-5 | 单元测试 navBarWidthRange clamp max |
| AC-4.4 | US-4 | R-6 | 单元测试 minContentWidth |
| AC-4.5 | US-4 | R-6, R-8 | 代码审查 NavigationLayoutAlgorithm Auto 模式阈值判断 |
| AC-4.6 | US-4 | R-5 | 代码审查 NavigationLayoutProperty 默认 navBarWidthRange |
| AC-5.1 | US-5 | R-9 | 单元测试 enableModeChangeAnimation true |
| AC-5.2 | US-5 | R-9 | 单元测试 enableModeChangeAnimation false |
| AC-5.3 | US-5 | R-9 | 代码审查 NavigationPattern 默认 enableModeChangeAnimation |
| AC-6.1 | US-6 | R-10 | 单元测试 configuration maxNavStackCount |
| AC-6.2 | US-6 | R-10 | 单元测试 maxNavStackCount exceeded |
| AC-6.3 | US-6 | R-10 | 代码审查 NavigationPattern 默认 configuration |
| AC-6.4 | US-6 | R-10 | 代码审查 NavigationConfiguration 结构 |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | Navigation() 无参创建默认 Stack 模式，内部创建空 NavPathStack | — | AC-1.1, AC-1.8 |
| R-2 | 行为 | — | Navigation(NavPathStack) 以传入栈创建，栈与 NavigationPattern 生命周期绑定；Navigation(NavPathStack, HomePathInfo) 同时设置首页信息 | — | AC-1.2, AC-1.3 |
| R-3 | 行为 | — | mode 设置导航模式：Stack=0（栈叠加显示）、Split=1（分栏并列显示）、Auto=2（根据宽度自动切换）、AUTO_WITH_ASPECT_RATIO=3（根据宽度比例自动选择） | — | AC-1.4~AC-1.7 |
| R-4 | 行为 | — | navBarWidth 设置导航栏宽度，默认 240vp，仅在 Split/Auto 模式下生效；navBarPosition 设置导航栏位置（START=0 左侧/END=1 右侧），默认 START | — | AC-2.1~AC-2.4 |
| R-5 | 边界 | — | navBarWidthRange 设置宽度范围约束（{min, max}），NavBar 实际宽度被钳位在 [min, max] 范围内；未设置时无范围约束 | min 和 max 需为正数，min <= max | AC-4.1~AC-4.3, AC-4.6 |
| R-6 | 行为 | — | minContentWidth 设置最小内容宽度，默认 360vp，仅在 Split/Auto 模式下生效；当 Content 剩余宽度小于 minContentWidth 时，Auto 模式切换为 Stack | — | AC-4.4, AC-4.5 |
| R-7 | 行为 | — | hideNavBar 隐藏导航栏：true 时 NavBar 区域不显示，Content 区域占满全宽；false 或重置时恢复 NavBar 显示 | — | AC-3.1~AC-3.3 |
| R-8 | 行为 | — | AUTO_WITH_ASPECT_RATIO 根据 NavBar 宽度与 Content 宽度比例自动选择 Stack 或 Split 模式，比例计算基于 navBarWidth 和容器剩余宽度 | API 26 新增 | AC-1.7, AC-4.5 |
| R-9 | 行为 | — | enableModeChangeAnimation 控制 Stack/Split 模式切换动画：true 时播放过渡动画，false 时直接切换，默认开启 | — | AC-5.1~AC-5.3 |
| R-10 | 行为 | — | configuration 设置运行参数：NavigationConfiguration 包含 maxNavStackCount（最大栈深度限制），未设置时不限制栈深度，超出限制时新 NavDestination 不被推入栈 | API 26 新增 | AC-6.1~AC-6.4 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModelNG Create |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModelNG Create with NavPathStack |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModelNG Create with HomePathInfo |
| VM-4 | AC-1.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationMode Stack |
| VM-5 | AC-1.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationMode Split |
| VM-6 | AC-1.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationMode Auto |
| VM-7 | AC-1.7 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp` AUTO_WITH_ASPECT_RATIO 分支 |
| VM-8 | AC-1.8 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 NavigationMode |
| VM-9 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarWidth |
| VM-10 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarPosition START |
| VM-11 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarPosition END |
| VM-12 | AC-2.4 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h` 默认 navBarPosition |
| VM-13 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideNavBar true |
| VM-14 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideNavBar reset |
| VM-15 | AC-3.3 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp` hideNavBar Stack 分支 |
| VM-16 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarWidthRange |
| VM-17 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarWidthRange clamp |
| VM-18 | AC-4.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` navBarWidthRange clamp max |
| VM-19 | AC-4.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` minContentWidth |
| VM-20 | AC-4.5 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp` Auto 模式阈值 |
| VM-21 | AC-4.6 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h` navBarWidthRange 默认 |
| VM-22 | AC-5.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableModeChangeAnimation true |
| VM-23 | AC-5.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableModeChangeAnimation false |
| VM-24 | AC-5.3 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认动画 |
| VM-25 | AC-6.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` configuration |
| VM-26 | AC-6.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` maxNavStackCount exceeded |
| VM-27 | AC-6.3 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` configuration 默认 |
| VM-28 | AC-6.4 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` NavigationConfiguration |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `Navigation()` | Public | navigation.d.ts | API 8 | Public | 无参创建 Navigation 容器，默认 Stack 模式 |
| `Navigation(navPathStack: NavPathStack)` | Public | navigation.d.ts | API 9 | Public | 以传入 NavPathStack 创建 Navigation |
| `Navigation(navPathStack: NavPathStack, homePathInfo: HomePathInfo)` | Public | navigation.d.ts | API 26 | Public | 以传入 NavPathStack 和 HomePathInfo 创建 Navigation |
| `mode(mode: NavigationMode): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置导航模式 |
| `navBarWidth(value: Length): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置导航栏宽度 |
| `navBarPosition(position: NavBarPosition): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置导航栏位置 |
| `navBarWidthRange(range: NavBarWidthRange): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置导航栏宽度范围 |
| `minContentWidth(value: Length): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置最小内容宽度 |
| `hideNavBar(value: boolean): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 隐藏导航栏 |
| `ignoreLayoutSafeArea(types: SafeAreaType, edges?: SafeAreaEdge): NavigationAttribute` | Public | navigation.d.ts | API 11 | Public | 忽略安全区避让 |
| `enableModeChangeAnimation(enable: boolean): NavigationAttribute` | Public | navigation.d.ts | API 12 | Public | 模式切换动画开关 |
| `configuration(config: NavigationConfiguration): NavigationAttribute` | Public | navigation.d.ts | API 26 | Public | 设置运行参数 |

**关联枚举/类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `NavigationMode` | `{ Stack=0, Split=1, Auto=2, AUTO_WITH_ASPECT_RATIO=3 }` | API 9（Stack/Split/Auto），API 26（AUTO_WITH_ASPECT_RATIO） |
| `NavBarPosition` | `{ START=0, END=1 }` | API 9 |
| `NavBarWidthRange` | `{ min?: Length, max?: Length }` | API 9 |
| `NavigationConfiguration` | `{ maxNavStackCount?: number }` | API 26 |
| `HomePathInfo` | 首页路径信息 | API 26 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 8 | Navigation() 无参创建 | 仅支持无参创建，内部自动创建空 NavPathStack | API 9+ 推荐传入 NavPathStack 以在 ArkTS 层直接操作栈 |
| API 9 | 引入 NavPathStack 构造方式和 mode/navBarWidth 等属性 | Navigation(NavPathStack) 成为推荐创建方式 | 旧的无参创建仍可使用，但无法在 ArkTS 层直接操作栈 |
| API 9 | Auto 模式根据容器宽度自动切换 | 切换阈值逻辑与后续版本可能有差异 | 建议显式设置 navBarWidthRange 和 minContentWidth 控制阈值 |
| API 10 | NavigationMode AUTO 行为增强 | Auto 模式切换判断更精确 | 无需迁移 |
| API 11 | ignoreLayoutSafeArea 新增 | 支持选择性关闭安全区避让 | 未使用时默认避让行为不变 |
| API 12 | enableModeChangeAnimation 新增 | 默认开启模式切换动画 | 关闭动画需显式设置 false |
| API 26 | AUTO_WITH_ASPECT_RATIO 新增 | 基于宽度比例自动选择模式 | 旧的 Auto 模式行为不变 |
| API 26 | Navigation(NavPathStack, HomePathInfo) 新增 | 支持设置首页信息 | 旧构造方式不变 |
| API 26 | configuration 新增 | 支持栈大小限制等运行参数 | 未设置时不限制栈深度 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 属性分层 | NavigationLayoutProperty 存储 mode/navBarWidth/navBarPosition/navBarWidthRange/minContentWidth/hideNavBar 等布局属性 |
| 未组件化 | Navigation 未组件化，JSView（js_navigation.cpp）和 Bridge（arkts_native_navigation_bridge.cpp）双路径共存 |
| NavPathStack 生命周期 | Navigation(NavPathStack) 构造时传入的栈与 NavigationPattern 生命周期绑定，栈变更需通知 Pattern |
| NavigationMode 门控 | Stack/Split/Auto/AUTO_WITH_ASPECT_RATIO 四种模式在 NavigationLayoutAlgorithm 中分别处理 |
| Split 模式宽度约束 | navBarWidth 受 navBarWidthRange 约束钳位，Content 受 minContentWidth 约束 |
| Auto 模式阈值 | Auto 模式根据容器宽度与 navBarWidthRange + minContentWidth 计算阈值决定 Stack/Split |

---

## 非性需求

| 维度 | 要求 |
|------|------|
| 性能 | NavigationLayoutAlgorithm 布局计算开销 O(1)，不依赖栈深度；Auto/AUTO_WITH_ASPECT_RATIO 模式切换判断在布局前完成 |
| 可调试性 | NavigationLayoutProperty 支持 DumpInfo/ToJsonValue 输出 mode/navBarWidth 等属性供 Inspector 检查 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | Auto 模式倾向于 Stack 模式（窄屏） | minContentWidth=360vp 时，宽度 < 600vp 切换为 Stack | 单元测试 | — |
| 平板 | Auto 模式倾向于 Split 模式（宽屏） | navBarWidth=240vp，宽度 >= 600vp 切换为 Split | 单元测试 | — |
| 折叠屏 | Auto 模式在折叠/展开时动态切换 | enableModeChangeAnimation 控制切换动画 | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| 安全区避让 | Navigation 的 ignoreLayoutSafeArea 参与全局安全区避让机制（IAvoidInfoListener + CustomSafeAreaExpander） |
| NavPathStack | NavPathStack 作为全局路由管理核心，可能被多个 Navigation 或其他组件引用 |
| 模式切换动画 | enableModeChangeAnimation 影响渲染管线的动画调度 |

---

## 行为场景

### 场景 1: Navigation 无参创建默认 Stack 模式

```
Given 调用 Navigation() 无参创建
When 创建完成
THEN Navigation 进入默认 Stack 模式
  And 内部创建空 NavPathStack
  And NavBar 显示在当前页面
```

### 场景 2: Navigation 传入 NavPathStack 创建

```
Given 调用 Navigation(navPathStack) 传入 NavPathStack
When 创建完成
THEN Navigation 使用传入的 NavPathStack
  And 栈变更通知 NavigationPattern
  And 模式默认为 Stack
```

### 场景 3: Navigation 设置 Split 模式

```
Given 一个 Navigation 容器
When 调用 .mode(NavigationMode.Split)
THEN Navigation 进入 Split 模式
  And NavBar 显示在左侧（默认 START 位置）
  And NavBar 宽度为 240vp（默认）
  And Content 区域显示 NavDestination
```

### 场景 4: Navigation 设置 Auto 模式

```
Given 一个 Navigation 容器
  And 设置 .mode(NavigationMode.Auto)
  And 设置 .navBarWidth(240)
  And 设置 .minContentWidth(360)
When 容器宽度 >= 600vp（navBarWidth + minContentWidth）
THEN Navigation 进入 Split 模式
When 容器宽度 < 600vp
THEN Navigation 进入 Stack 模式
```

### 场景 5: Navigation 隐藏 NavBar

```
Given 一个 Navigation 容器
When 调用 .hideNavBar(true)
THEN NavBar 区域被隐藏
  And Content 区域占满全宽
```

### 场景 6: Navigation 配置 navBarWidthRange 钳位

```
Given 一个 Navigation 容器
  And 设置 .navBarWidth(200)
  And 设置 .navBarWidthRange({ min: 180, max: 280 })
When 执行 Split 模式布局
THEN NavBar 实际宽度为 200vp（在 [180, 280] 范围内）
When navBarWidth 设置为 150vp
THEN NavBar 实际宽度被钳位为 180vp
When navBarWidth 设置为 300vp
THEN NavBar 实际宽度被钳位为 280vp
```

### 场景 7: Navigation 模式切换动画

```
Given 一个 Navigation 容器
  And 设置 .enableModeChangeAnimation(true)
  And 当前为 Stack 模式
When Auto 模式判定切换为 Split 模式
THEN 模式切换播放过渡动画
When 设置 .enableModeChangeAnimation(false)
THEN 模式切换无动画，直接切换布局
```

### 场景 8: Navigation 设置 configuration 限制栈深度

```
Given 一个 Navigation 容器
  And 设置 .configuration({ maxNavStackCount: 5 })
When NavPathStack push 第 6 个 NavDestination
THEN NavDestination 不被推入栈
  And 栈深度保持为 5
```

### 场景 9: AUTO_WITH_ASPECT_RATIO 模式

```
Given 一个 Navigation 容器
  And 设置 .mode(NavigationMode.AUTO_WITH_ASPECT_RATIO)
  And 设置 .navBarWidth(240)
When NavBar 与 Content 宽度比例适合分栏
THEN Navigation 进入 Split 模式
When NavBar 与 Content 宽度比例不适合分栏
THEN Navigation 进入 Stack 模式
```

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 业务规则/功能规则/边界规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异
- [x] 行为场景使用 Gherkin Given/When/Then 格式，覆盖关键路径
- [x] 所有源码引用包含 file 信息
- [x] 构建系统影响章节已确认无变更
- [x] AUTO_WITH_ASPECT_RATIO 和 configuration 的 API 26 版本标注已完成

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，导航模式管理、栈协调 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层，创建和属性设置 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_static.cpp/.h` | 静态版 Model 层 |
| `frameworks/core/components_ng/pattern/navigation/navigation_layout_property.h/.cpp` | 布局属性定义 |
| `frameworks/core/components_ng/pattern/navigation/navigation_layout_algorithm.cpp/.h` | 布局算法 |
| `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` | 事件回调定义 |
| `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp/.h` | NavPathStack 路由栈 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层 |
| `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.cpp/.h` | ArkTS 桥接层 |
| `frameworks/bridge/declarative_frontend/ark_modifier/src/navigation_modifier.ts` | ArkTS Modifier |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录 |
