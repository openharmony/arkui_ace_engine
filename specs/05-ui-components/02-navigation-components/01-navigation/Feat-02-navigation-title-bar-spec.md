# 特性规格

> Func-05-02-01-Feat-02 Navigation 标题栏配置：固化 title（ResourceStr/CustomBuilder/NavigationCommonTitle/NavigationCustomTitle）、subTitle（deprecated since 9）、titleMode（Free/Full/Mini）、hideTitleBar（boolean + animated since 13）、hideBackButton、backButtonIcon（string/PixelMap/Resource/SymbolGlyphModifier + accessibilityText since 19）、menus（Array<NavigationMenuItem>/CustomBuilder + NavigationMenuOptions since 19）、NavigationTitleOptions、NavigationCommonTitle、NavigationCustomTitle、NavigationMenuItem、NavigationMenuOptions、MoreButtonOptions 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 标题栏配置 |
| 特性编号 | Func-05-02-01-Feat-02 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 8 起支持，titleMode/hideTitleBar 集中于 API 9-13，backButtonIcon accessibilityText API 19，NavigationMenuOptions API 19 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |
| Navigation Model NG | `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp` | — |

---

## 用户故事

### US-1: 设置标题和标题模式

**作为** 应用开发者,
**我想要** 通过 `title()` 设置 Navigation 标题栏的主标题、副标题和标题模式（Free/Full/Mini）,
**以便** 在导航栏顶部展示应用页面标题信息并控制标题显示样式。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.title(value: ResourceStr)` THEN 标题栏主标题设置为字符串资源值 | 正常 |
| AC-1.2 | WHEN 调用 `.title(value: CustomBuilder)` THEN 标题栏主标题区域显示自定义构建内容 | 正常 |
| AC-1.3 | WHEN 调用 `.title(value: NavigationCommonTitle)` THEN 标题栏主标题和副标题按 NavigationCommonTitle 结构设置 | 正常 |
| AC-1.4 | WHEN 调用 `.title(value: NavigationCustomTitle)` THEN 标题栏按 NavigationCustomTitle 结构设置，包括自定义构建内容和高度模式 | 正常 |
| AC-1.5 | WHEN 调用 `.title(value: NavigationCommonTitle, options: NavigationTitleOptions)` THEN 标题栏按 NavigationCommonTitle 设置，并通过 NavigationTitleOptions 配置标题栏背景色等选项 | 正常 |
| AC-1.6 | WHEN 调用 `.title(value: NavigationCustomTitle, options: NavigationTitleOptions)` THEN 标题栏按 NavigationCustomTitle 设置，并通过 NavigationTitleOptions 配置标题栏背景色等选项 | 正常 |
| AC-1.7 | WHEN 调用 `.titleMode(NavigationTitleMode.Free)` THEN 标题栏使用自由模式，标题可动态滚动 | 正常 |
| AC-1.8 | WHEN 调用 `.titleMode(NavigationTitleMode.Full)` THEN 标题栏使用完整模式，标题居中固定显示 | 正常 |
| AC-1.9 | WHEN 调用 `.titleMode(NavigationTitleMode.Mini)` THEN 标题栏使用迷你模式，标题缩小显示 | 正常 |
| AC-1.10 | WHEN 未设置 titleMode THEN 默认标题模式为 Free | 边界 |
| AC-1.11 | WHEN 调用 `.subTitle(value: ResourceStr)` THEN 标题栏副标题设置为字符串资源值（deprecated since API 9，推荐使用 NavigationCommonTitle.subTitle） | 异常 |

### US-2: 隐藏/显示标题栏

**作为** 应用开发者,
**我想要** 通过 `hideTitleBar()` 隐藏或显示标题栏，支持动画过渡,
**以便** 在需要时完全隐藏标题栏，仅显示 NavDestination 内容。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.hideTitleBar(true)` THEN 标题栏区域完全隐藏，Content 区域向上扩展占满 | 正常 |
| AC-2.2 | WHEN 调用 `.hideTitleBar(false)` 或重置 THEN 标题栏区域恢复显示 | 正常 |
| AC-2.3 | WHEN 调用 `.hideTitleBar(true, { animated: true })`（API 13 新增 animated 参数）THEN 标题栏隐藏时播放过渡动画 | 正常 |
| AC-2.4 | WHEN 调用 `.hideTitleBar(true, { animated: false })` THEN 标题栏隐藏时无动画，直接消失 | 边界 |
| AC-2.5 | WHEN 未设置 animated 参数 THEN 默认有动画过渡 | 边界 |

### US-3: 配置返回按钮

**作为** 应用开发者,
**我想要** 通过 `hideBackButton()` 和 `backButtonIcon()` 配置返回按钮的显示和图标,
**以便** 控制标题栏返回按钮的可见性和自定义图标样式。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.hideBackButton(true)` THEN 标题栏返回按钮被隐藏 | 正常 |
| AC-3.2 | WHEN 调用 `.hideBackButton(false)` 或重置 THEN 标题栏返回按钮恢复显示 | 正常 |
| AC-3.3 | WHEN 调用 `.backButtonIcon(value: string)` THEN 返回按钮图标设置为指定路径字符串 | 正常 |
| AC-3.4 | WHEN 调用 `.backButtonIcon(value: PixelMap)` THEN 返回按钮图标设置为 PixelMap 图片 | 正常 |
| AC-3.5 | WHEN 调用 `.backButtonIcon(value: Resource)` THEN 返回按钮图标设置为 Resource 资源引用 | 正常 |
| AC-3.6 | WHEN 调用 `.backButtonIcon(value: SymbolGlyphModifier)` THEN 返回按钮图标设置为 SymbolGlyph 系统图标 | 正常 |
| AC-3.7 | WHEN 调用 `.backButtonIcon(value, { accessibilityText: '返回' })`（API 19 新增 accessibilityText）THEN 返回按钮无障碍文本被设置为指定值 | 正常 |
| AC-3.8 | WHEN backButtonIcon 设置为空值 THEN 返回按钮图标使用系统默认图标 | 边界 |

### US-4: 配置菜单项

**作为** 应用开发者,
**我想要** 通过 `menus()` 配置标题栏右侧菜单项，支持 NavigationMenuItem 数组和 CustomBuilder,
**以便** 在标题栏右侧添加操作菜单按钮。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.menus(value: Array<NavigationMenuItem>)` THEN 标题栏右侧显示 NavigationMenuItem 列表中的菜单项 | 正常 |
| AC-4.2 | WHEN 调用 `.menus(value: CustomBuilder)` THEN 标题栏右侧显示自定义构建的菜单内容 | 正常 |
| AC-4.3 | WHEN 调用 `.menus(value: Array<NavigationMenuItem>, options: NavigationMenuOptions)`（API 19 新增 NavigationMenuOptions）THEN 标题栏菜单按 NavigationMenuItem 列表设置，并通过 NavigationMenuOptions 配置更多按钮选项 | 正常 |
| AC-4.4 | WHEN 调用 `.menus(value: CustomBuilder, options: NavigationMenuOptions)` THEN 标题栏菜单按自定义构建设置，并通过 NavigationMenuOptions 配置更多按钮选项 | 正常 |
| AC-4.5 | WHEN NavigationMenuOptions 包含 MoreButtonOptions THEN 更多按钮的图标、颜色等属性可通过 MoreButtonOptions 配置 | 正常 |
| AC-4.6 | WHEN 未设置 menus THEN 标题栏右侧不显示菜单项 | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 title ResourceStr |
| AC-1.2 | US-1 | R-1 | 单元测试 title CustomBuilder |
| AC-1.3 | US-1 | R-2 | 单元测试 title NavigationCommonTitle |
| AC-1.4 | US-1 | R-2 | 单元测试 title NavigationCustomTitle |
| AC-1.5 | US-1 | R-2, R-3 | 单元测试 title NavigationCommonTitle + NavigationTitleOptions |
| AC-1.6 | US-1 | R-2, R-3 | 单元测试 title NavigationCustomTitle + NavigationTitleOptions |
| AC-1.7 | US-1 | R-4 | 单元测试 titleMode Free |
| AC-1.8 | US-1 | R-4 | 单元测试 titleMode Full |
| AC-1.9 | US-1 | R-4 | 单元测试 titleMode Mini |
| AC-1.10 | US-1 | R-4 | 代码审查 NavigationPattern 默认 titleMode |
| AC-1.11 | US-1 | R-5 | 代码审查 subTitle deprecated 标注 |
| AC-2.1 | US-2 | R-6 | 单元测试 hideTitleBar true |
| AC-2.2 | US-2 | R-6 | 单元测试 hideTitleBar false/reset |
| AC-2.3 | US-2 | R-7 | 单元测试 hideTitleBar animated true |
| AC-2.4 | US-2 | R-7 | 单元测试 hideTitleBar animated false |
| AC-2.5 | US-2 | R-7 | 代码审查 NavigationPattern hideTitleBar 默认动画 |
| AC-3.1 | US-3 | R-8 | 单元测试 hideBackButton true |
| AC-3.2 | US-3 | R-8 | 单元测试 hideBackButton false/reset |
| AC-3.3 | US-3 | R-9 | 单元测试 backButtonIcon string |
| AC-3.4 | US-3 | R-9 | 单元测试 backButtonIcon PixelMap |
| AC-3.5 | US-3 | R-9 | 单元测试 backButtonIcon Resource |
| AC-3.6 | US-3 | R-9 | 单元测试 backButtonIcon SymbolGlyphModifier |
| AC-3.7 | US-3 | R-10 | 单元测试 backButtonIcon accessibilityText |
| AC-3.8 | US-3 | R-9 | 代码审查 NavigationPattern 默认 backButtonIcon |
| AC-4.1 | US-4 | R-11 | 单元测试 menus NavigationMenuItem |
| AC-4.2 | US-4 | R-11 | 单元测试 menus CustomBuilder |
| AC-4.3 | US-4 | R-11, R-12 | 单元测试 menus NavigationMenuOptions |
| AC-4.4 | US-4 | R-11, R-12 | 单元测试 menus CustomBuilder + NavigationMenuOptions |
| AC-4.5 | US-4 | R-12 | 单元测试 MoreButtonOptions |
| AC-4.6 | US-4 | R-11 | 代码审查 NavigationPattern 默认 menus |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | title 设置标题栏主标题：ResourceStr 直接设置字符串标题，CustomBuilder 设置自定义构建标题内容 | ResourceStr 支持字符串和 $r() 资源引用 | AC-1.1, AC-1.2 |
| R-2 | 行为 | — | title 设置标题栏结构化标题：NavigationCommonTitle 包含 main 和 subTitle 字段；NavigationCustomTitle 包含 titleContent（CustomBuilder）和 height 字段 | NavigationCommonTitle.subTitle 替代已废弃的 subTitle 属性 | AC-1.3, AC-1.4 |
| R-3 | 行为 | — | NavigationTitleOptions 配置标题栏选项：包含 backgroundColor（ResourceColor）等属性，与 title 配合使用 | — | AC-1.5, AC-1.6 |
| R-4 | 行为 | — | titleMode 设置标题显示模式：Free=0（自由模式，标题可动态滚动）、Full=1（完整模式，标题居中固定）、Mini=2（迷你模式，标题缩小显示），默认 Free | — | AC-1.7~AC-1.10 |
| R-5 | 废弃 | — | subTitle 设置标题栏副标题，API 9 起废弃，推荐使用 NavigationCommonTitle.subTitle | 旧代码仍可使用但不推荐 | AC-1.11 |
| R-6 | 行为 | — | hideTitleBar 隐藏/显示标题栏：true 时标题栏完全隐藏，Content 区域向上扩展；false 或重置时恢复标题栏显示 | — | AC-2.1, AC-2.2 |
| R-7 | 行为 | — | hideTitleBar 支持 animated 参数（API 13 新增）：animated=true 时隐藏/显示播放过渡动画，animated=false 时直接切换，默认有动画 | API 13 新增 | AC-2.3~AC-2.5 |
| R-8 | 行为 | — | hideBackButton 隐藏/显示标题栏返回按钮：true 时返回按钮不显示，false 或重置时恢复显示 | Stack 模式下返回按钮用于 pop 操作 | AC-3.1, AC-3.2 |
| R-9 | 行为 | — | backButtonIcon 设置返回按钮图标：支持 string（路径）、PixelMap（图片）、Resource（资源引用）、SymbolGlyphModifier（系统图标）四种类型，未设置时使用系统默认图标 | — | AC-3.3~AC-3.6, AC-3.8 |
| R-10 | 行为 | — | backButtonIcon 支持 accessibilityText 参数（API 19 新增）：设置返回按钮的无障碍文本描述 | API 19 新增 | AC-3.7 |
| R-11 | 行为 | — | menus 设置标题栏右侧菜单项：Array<NavigationMenuItem> 按列表显示菜单图标/文字项；CustomBuilder 显示自定义构建菜单内容，未设置时不显示菜单 | NavigationMenuItem 包含 icon、title、id 等字段 | AC-4.1, AC-4.2, AC-4.6 |
| R-12 | 行为 | — | NavigationMenuOptions 配置菜单选项（API 19 新增）：包含 MoreButtonOptions 用于配置更多按钮的图标、颜色等属性 | API 19 新增 | AC-4.3~AC-4.5 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title ResourceStr |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title CustomBuilder |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title NavigationCommonTitle |
| VM-4 | AC-1.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title NavigationCustomTitle |
| VM-5 | AC-1.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title + NavigationTitleOptions |
| VM-6 | AC-1.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` title + NavigationTitleOptions Custom |
| VM-7 | AC-1.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` titleMode Free |
| VM-8 | AC-1.8 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` titleMode Full |
| VM-9 | AC-1.9 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` titleMode Mini |
| VM-10 | AC-1.10 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 titleMode |
| VM-11 | AC-1.11 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp` subTitle deprecated 标注 |
| VM-12 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideTitleBar true |
| VM-13 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideTitleBar reset |
| VM-14 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideTitleBar animated |
| VM-15 | AC-2.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideTitleBar animated false |
| VM-16 | AC-2.5 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` hideTitleBar 默认动画 |
| VM-17 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideBackButton true |
| VM-18 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideBackButton reset |
| VM-19 | AC-3.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` backButtonIcon string |
| VM-20 | AC-3.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` backButtonIcon PixelMap |
| VM-21 | AC-3.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` backButtonIcon Resource |
| VM-22 | AC-3.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` backButtonIcon SymbolGlyphModifier |
| VM-23 | AC-3.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` backButtonIcon accessibilityText |
| VM-24 | AC-3.8 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 backButtonIcon |
| VM-25 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` menus NavigationMenuItem |
| VM-26 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` menus CustomBuilder |
| VM-27 | AC-4.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` menus + NavigationMenuOptions |
| VM-28 | AC-4.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` menus CustomBuilder + NavigationMenuOptions |
| VM-29 | AC-4.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` MoreButtonOptions |
| VM-30 | AC-4.6 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 menus |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `title(value: ResourceStr): NavigationAttribute` | Public | navigation.d.ts | API 8 | Public | 设置标题栏主标题（字符串资源） |
| `title(value: CustomBuilder): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置标题栏自定义标题 |
| `title(value: NavigationCommonTitle): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置标题栏通用标题结构 |
| `title(value: NavigationCustomTitle): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置标题栏自定义标题结构 |
| `title(value: NavigationCommonTitle, options: NavigationTitleOptions): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置通用标题结构并配置标题栏选项 |
| `title(value: NavigationCustomTitle, options: NavigationTitleOptions): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置自定义标题结构并配置标题栏选项 |
| `subTitle(value: ResourceStr): NavigationAttribute` | Public | navigation.d.ts | API 8 | Public | 设置标题栏副标题（deprecated since 9） |
| `titleMode(mode: NavigationTitleMode): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置标题显示模式 |
| `hideTitleBar(value: boolean): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 隐藏/显示标题栏 |
| `hideTitleBar(value: boolean, options: NavigationTitleBarOptions): NavigationAttribute` | Public | navigation.d.ts | API 13 | Public | 隐藏/显示标题栏并配置动画选项 |
| `hideBackButton(value: boolean): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 隐藏/显示返回按钮 |
| `backButtonIcon(value: string \| PixelMap \| Resource \| SymbolGlyphModifier): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置返回按钮图标 |
| `backButtonIcon(value: string \| PixelMap \| Resource \| SymbolGlyphModifier, options: NavigationBackButtonOptions): NavigationAttribute` | Public | navigation.d.ts | API 19 | Public | 设置返回按钮图标并配置无障碍选项 |
| `menus(value: Array<NavigationMenuItem> \| CustomBuilder): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置标题栏菜单项 |
| `menus(value: Array<NavigationMenuItem>, options: NavigationMenuOptions): NavigationAttribute` | Public | navigation.d.ts | API 19 | Public | 设置菜单项并配置菜单选项 |
| `menus(value: CustomBuilder, options: NavigationMenuOptions): NavigationAttribute` | Public | navigation.d.ts | API 19 | Public | 设置自定义菜单并配置菜单选项 |

**关联类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `NavigationTitleMode` | `{ Free=0, Full=1, Mini=2 }` | API 9 |
| `NavigationCommonTitle` | `{ main: ResourceStr, subTitle: ResourceStr }` | API 9 |
| `NavigationCustomTitle` | `{ titleContent: CustomBuilder, height?: TitleHeightMode \| Length }` | API 9 |
| `NavigationTitleOptions` | `{ backgroundColor?: ResourceColor }` | API 9 |
| `NavigationTitleBarOptions` | `{ animated?: boolean }` | API 13 |
| `NavigationBackButtonOptions` | `{ accessibilityText?: ResourceStr }` | API 19 |
| `NavigationMenuItem` | `{ icon?: ResourceStr, title?: ResourceStr, id?: number, action?: () => void }` | API 9 |
| `NavigationMenuOptions` | `{ moreButtonOptions?: MoreButtonOptions }` | API 19 |
| `MoreButtonOptions` | `{ icon?: ResourceStr \| SymbolGlyphModifier, ... }` | API 19 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 8 | title(ResourceStr) 和 subTitle 为原始接口 | 仅支持字符串标题 | API 9+ 推荐使用 NavigationCommonTitle/NavigationCustomTitle |
| API 9 | subTitle 废弃，推荐 NavigationCommonTitle.subTitle | 旧代码仍可使用但不推荐 | 使用 NavigationCommonTitle 代替 subTitle |
| API 9 | title 支持 CustomBuilder/NavigationCommonTitle/NavigationCustomTitle | 新增结构化标题类型 | 无需迁移，旧 ResourceStr 仍支持 |
| API 9 | titleMode/hideTitleBar/hideBackButton/menus/backButtonIcon 新增 | 标题栏配置完善 | 无需迁移 |
| API 13 | hideTitleBar 支持 animated 参数 | 标题栏隐藏时可配置动画 | 未传 animated 时默认有动画 |
| API 19 | backButtonIcon 支持 accessibilityText | 返回按钮无障碍文本 | 未传 accessibilityText 时无额外描述 |
| API 19 | menus 支持 NavigationMenuOptions | 菜单更多按钮可配置 | 未传 options 时默认菜单行为不变 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 标题栏属性管理 | 标题栏属性通过 NavigationPattern 管理，NavBar 节点内部持有 NavBarPattern |
| title 类型分流 | title 根据 ResourceStr/CustomBuilder/NavigationCommonTitle/NavigationCustomTitle 四种类型分别处理 |
| subTitle 废弃兼容 | subTitle 在 JSView 层仍可调用但标注 deprecated，内部转发至 NavigationCommonTitle.subTitle |
| hideTitleBar 动画参数 | animated 参数通过 NavigationTitleBarOptions 传入，NavigationPattern 控制 NavBar 节点显隐动画 |
| backButtonIcon 类型分流 | backButtonIcon 根据 string/PixelMap/Resource/SymbolGlyphModifier 四种类型分别解析 |
| menus 类型分流 | menus 根据 Array<NavigationMenuItem>/CustomBuilder 两种类型分别处理 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 标题栏属性设置无额外开销，title/titleMode/menus 属性直接写入 Property |
| 可调试性 | NavigationPattern 支持 DumpInfo 输出 title/titleMode/hideTitleBar 等标题栏属性 |
| 无障碍 | backButtonIcon accessibilityText 为返回按钮提供无障碍文本描述 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | titleMode Free 为默认，标题可滚动 | 窄屏下 Free 模式标题可能被截断 | 单元测试 | — |
| 平板 | titleMode Full 居中固定显示更合适 | 宽屏下建议使用 Full 或 Mini | 单元测试 | — |
| 折叠屏 | titleMode 在折叠/展开时可能需动态切换 | onTitleModeChange 回调可监听模式变化 | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| 标题栏样式 | title/titleMode/hideTitleBar 影响 NavBar 节点的样式和布局计算 |
| 菜单项交互 | menus 菜单项的 action 回调在 UI 线程执行 |
| 无障碍 | backButtonIcon accessibilityText 参与全局无障碍体系 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异（subTitle deprecated、animated API 13、accessibilityText API 19）
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，标题栏配置管理 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层，title/titleMode/hideTitleBar 等属性设置 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层，标题栏属性解析 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
