# 特性规格

> Func-05-03-09-Feat-03 Tabs/TabContent 侧边栏模式：固化 barStyle（NoStyle/BottomTabBar/SidebarAdaptable）、TabBarDisplayMode、SidebarDisplayStyle、SidebarPosition、sidebarWidth、sidebarBackgroundColor、sidebarDivider（TabsSidebarDivider）、showSideBar、showSideBarWithGesture、sidebarAutoHide、minSidebarWidth、maxSidebarWidth、minContentWidth、sidebarPosition、sidebarHeader、sidebarFooter、sidebarSearchable、barDisplayModeBreakpoint（TabBarDisplayModeBreakpoint）、onBarDisplayModeChange、onSideBarChange、TabContent sidebarSection、defaultVisibility（TabVisibility）、preferredPlacement（TabBarPlacement）、customizationBehavior（CustomizationBehavior）的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Tabs/TabContent 侧边栏模式 (Tabs/TabContent Sidebar Mode) |
| 特性编号 | Func-05-03-09-Feat-03 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 12+ 支持 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 高 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。覆盖 BarStyle.SidebarAdaptable 侧边栏模式全量属性（sidebarWidth/sidebarBackgroundColor/sidebarDivider/showSideBar/showSideBarWithGesture/sidebarAutoHide/minSidebarWidth/maxSidebarWidth/minContentWidth/sidebarPosition/sidebarHeader/sidebarFooter/sidebarSearchable/barDisplayModeBreakpoint/onBarDisplayModeChange/onSideBarChange）、TabContent 侧边栏扩展（sidebarSection/defaultVisibility/preferredPlacement/customizationBehavior）、关联枚举类型（TabBarDisplayMode/SidebarDisplayStyle/SidebarPosition/TabVisibility/TabBarPlacement/CustomizationBehavior）。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md` | Baselined |
| SDK API | `docs/sdk/ArkUI_SDK_API_Knowledge_Base.md` | — |
| SDK 组件 | `docs/sdk/Component_API_Knowledge_Base_CN.md` | — |

---

## 用户故事

### US-1: 配置侧边栏样式和基本属性

**作为** 应用开发者,
**我想要** 使用 BarStyle.SidebarAdaptable 和 sidebarWidth/sidebarBackgroundColor/sidebarDivider 配置侧边栏样式,
**以便** 在大屏设备上将标签栏切换为侧边栏模式，提供更大内容区空间。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.barStyle(BarStyle.SidebarAdaptable)` THEN TabsLayoutProperty::propBarStyle_ 被设置为 SIDEBARADAPTABLE，标签栏变为侧边栏 | 正常 |
| AC-3.2 | WHEN 调用 `.barStyle(BarStyle.NoStyle)` THEN TabsLayoutProperty::propBarStyle_ 被设置为 NOSTYLE | 正常 |
| AC-3.3 | WHEN 调用 `.barStyle(BarStyle.BottomTabBar)` THEN TabsLayoutProperty::propBarStyle_ 被设置为 BOTTOMTABBATSTYLE | 正常 |
| AC-3.4 | WHEN 调用 `.sidebarWidth(value: Length)` THEN TabsLayoutProperty::propSidebarWidth_ 被设置 | 正常 |
| AC-3.5 | WHEN 调用 `.sidebarBackgroundColor(value: ResourceColor)` THEN TabsLayoutProperty::propSidebarBackgroundColor_ 被设置 | 正常 |
| AC-3.6 | WHEN 调用 `.sidebarDivider(value: TabsSidebarDivider)` THEN TabsLayoutProperty::propSidebarDivider_ 被设置（strokeWidth/color/startMargin/endMargin） | 正常 |

### US-2: 配置侧边栏显示和交互

**作为** 应用开发者,
**我想要** 通过 showSideBar/showSideBarWithGesture/sidebarAutoHide 控制侧边栏的显示和交互行为,
**以便** 在不同场景下灵活控制侧边栏的可见性和手势响应。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.7 | WHEN 调用 `.showSideBar(value: boolean)` THEN 侧边栏显示/隐藏状态被设置 | 正常 |
| AC-3.8 | WHEN 调用 `.showSideBarWithGesture(value: boolean)` THEN 侧边栏手势显示/隐藏能力被启用或禁用 | 正常 |
| AC-3.9 | WHEN 调用 `.sidebarAutoHide(value: boolean)` THEN 侧边栏自动隐藏能力被启用或禁用 | 正常 |
| AC-3.10 | WHEN showSideBar=false 且 sidebarAutoHide=true THEN 侧边栏在内容区聚焦时自动隐藏 | 正常 |

### US-3: 配置侧边栏尺寸约束和位置

**作为** 应用开发者,
**我想要** 通过 minSidebarWidth/maxSidebarWidth/minContentWidth/sidebarPosition 精细控制侧边栏尺寸和位置,
**以便** 在不同屏幕尺寸下确保内容区和侧边栏的最小可见空间。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.11 | WHEN 调用 `.minSidebarWidth(value: Length)` THEN TabsLayoutProperty::propMinSidebarWidth_ 被设置 | 正常 |
| AC-3.12 | WHEN 调用 `.maxSidebarWidth(value: Length)` THEN TabsLayoutProperty::propMaxSidebarWidth_ 被设置 | 正常 |
| AC-3.13 | WHEN 调用 `.minContentWidth(value: Length)` THEN TabsLayoutProperty::propMinContentWidth_ 被设置 | 正常 |
| AC-3.14 | WHEN 调用 `.sidebarPosition(SidebarPosition.Start)` THEN 侧边栏位于左侧（水平）或顶部（垂直） | 正常 |
| AC-3.15 | WHEN 调用 `.sidebarPosition(SidebarPosition.End)` THEN 侧边栏位于右侧（水平）或底部（垂直） | 正常 |

### US-4: 配置侧边栏断点自适应和装饰

**作为** 应用开发者,
**我想要** 通过 barDisplayModeBreakpoint/sidebarHeader/sidebarFooter/sidebarSearchable 配置侧边栏断点自适应和装饰内容,
**以便** 在不同屏幕宽度下自动切换 Bottom/Sidebar 显示模式，并为侧边栏添加头部/尾部/搜索功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.16 | WHEN 调用 `.barDisplayModeBreakpoint(value: TabBarDisplayModeBreakpoint)` THEN 断点自适应配置被设置（sm/md/lg 断点值） | 正常 |
| AC-3.17 | WHEN 窗口宽度 <= sm 断点 THEN 显示模式自动切换为 BottomTabBar | 正常 |
| AC-3.18 | WHEN 窗口宽度 > md 断点 THEN 显示模式自动切换为 Sidebar | 正常 |
| AC-3.19 | WHEN 调用 `.sidebarHeader(value: CustomBuilder)` THEN 侧边栏头部区域被设置 | 正常 |
| AC-3.20 | WHEN 调用 `.sidebarFooter(value: CustomBuilder)` THEN 侧边栏尾部区域被设置 | 正常 |
| AC-3.21 | WHEN 调用 `.sidebarSearchable(value: SidebarSearchableOptions)` THEN 侧边栏搜索功能被设置 | 正常 |

### US-5: 配置侧边栏事件回调

**作为** 应用开发者,
**我想要** 通过 onBarDisplayModeChange/onSideBarChange 监听侧边栏显示模式切换和可见性变化,
**以便** 在侧边栏状态变化时执行响应逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.22 | WHEN 断点触发 Bottom→Sidebar 切换 THEN onBarDisplayModeChange 回调被触发，参数为当前 TabBarDisplayMode | 正常 |
| AC-3.23 | WHEN 侧边栏显示/隐藏状态变化 THEN onSideBarChange 回调被触发，参数为 isVisible boolean | 正常 |
| AC-3.24 | WHEN 断点切换为 BottomTabBar THEN onBarDisplayModeChange 回调参数为 TabBarDisplayMode.BOTTOM_TAB_BAR | 正常 |

### US-6: 配置 TabContent 侧边栏扩展属性

**作为** 应用开发者,
**我想要** 通过 TabContent 的 sidebarSection/defaultVisibility/preferredPlacement/customizationBehavior 配置侧边栏下各标签项的分组、默认可见性、排列偏好和自定义行为,
**以便** 在侧边栏模式下精细控制各标签项的展示和行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.25 | WHEN TabContent 设置 `.sidebarSection(string)` THEN 标签项属于指定分组 | 正常 |
| AC-3.26 | WHEN TabContent 设置 `.defaultVisibility(TabVisibility.Visible)` THEN 标签项默认可见 | 正常 |
| AC-3.27 | WHEN TabContent 设置 `.defaultVisibility(TabVisibility.Hidden)` THEN 标签项默认隐藏，需用户手动展开 | 正常 |
| AC-3.28 | WHEN TabContent 设置 `.preferredPlacement(TabBarPlacement.Top)` THEN 标签项偏好排列在顶部 | 正常 |
| AC-3.29 | WHEN TabContent 设置 `.customizationBehavior(CustomizationBehavior)` THEN 标签项自定义行为被设置 | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-3.1 | US-1 | R-1 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-3.2 | US-1 | R-2 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-3.3 | US-1 | R-3 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-3.4 | US-1 | R-4 | 代码审查 tabs_model_ng.cpp |
| AC-3.5 | US-1 | R-5 | 代码审查 tabs_model_ng.cpp |
| AC-3.6 | US-1 | R-6 | 代码审查 tabs_model_ng.cpp |
| AC-3.7 | US-2 | R-7 | 代码审查 tabs_model_ng.cpp |
| AC-3.8 | US-2 | R-8 | 代码审查 tabs_model_ng.cpp |
| AC-3.9 | US-2 | R-9 | 代码审查 tabs_model_ng.cpp |
| AC-3.10 | US-2 | R-10 | 代码审查 tabs_pattern.cpp |
| AC-3.11 | US-3 | R-11 | 代码审查 tabs_model_ng.cpp |
| AC-3.12 | US-3 | R-12 | 代码审查 tabs_model_ng.cpp |
| AC-3.13 | US-3 | R-13 | 代码审查 tabs_model_ng.cpp |
| AC-3.14 | US-3 | R-14 | 代码审查 tabs_model_ng.cpp |
| AC-3.15 | US-3 | R-15 | 代码审查 tabs_model_ng.cpp |
| AC-3.16 | US-4 | R-16 | 代码审查 tabs_model_ng.cpp |
| AC-3.17 | US-4 | R-17 | 代码审查 tabs_pattern.cpp |
| AC-3.18 | US-4 | R-18 | 代码审查 tabs_pattern.cpp |
| AC-3.19 | US-4 | R-19 | 代码审查 tabs_model_ng.cpp |
| AC-3.20 | US-4 | R-20 | 代码审查 tabs_model_ng.cpp |
| AC-3.21 | US-4 | R-21 | 代码审查 tabs_model_ng.cpp |
| AC-3.22 | US-5 | R-22 | 单元测试 tabs_event_test_ng.cpp |
| AC-3.23 | US-5 | R-23 | 单元测试 tabs_event_test_ng.cpp |
| AC-3.24 | US-5 | R-24 | 单元测试 tabs_event_test_ng.cpp |
| AC-3.25 | US-6 | R-25 | 代码审查 js_tabs.cpp |
| AC-3.26 | US-6 | R-26 | 代码审查 js_tabs.cpp |
| AC-3.27 | US-6 | R-27 | 代码审查 js_tabs.cpp |
| AC-3.28 | US-6 | R-28 | 代码审查 js_tabs.cpp |
| AC-3.29 | US-6 | R-29 | 代码审查 js_tabs.cpp |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `tabs_model_ng.cpp` | barStyle(SidebarAdaptable) → TabsLayoutProperty::propBarStyle_ = SIDEBARADAPTABLE | API >= 12 | AC-3.1 |
| R-2 | 行为 | `tabs_model_ng.cpp` | barStyle(NoStyle) → TabsLayoutProperty::propBarStyle_ = NOSTYLE | — | AC-3.2 |
| R-3 | 行为 | `tabs_model_ng.cpp` | barStyle(BottomTabBar) → TabsLayoutProperty::propBarStyle_ = BOTTOMTABBATSTYLE | — | AC-3.3 |
| R-4 | 行为 | `tabs_model_ng.cpp` | sidebarWidth 设置写入 TabsLayoutProperty::propSidebarWidth_ | 默认值 200vp | AC-3.4 |
| R-5 | 行为 | `tabs_model_ng.cpp` | sidebarBackgroundColor 设置写入 TabsLayoutProperty::propSidebarBackgroundColor_ | 默认值 #ffffff | AC-3.5 |
| R-6 | 行为 | `tabs_model_ng.cpp` | sidebarDivider 设置写入 TabsLayoutProperty::propSidebarDivider_（strokeWidth/color/startMargin/endMargin） | TabsSidebarDivider 类型 | AC-3.6 |
| R-7 | 行为 | `tabs_model_ng.cpp` | showSideBar 设置侧边栏显示/隐藏 | 默认 true | AC-3.7 |
| R-8 | 行为 | `tabs_model_ng.cpp` | showSideBarWithGesture 设置手势显示/隐藏能力 | 默认 true | AC-3.8 |
| R-9 | 行为 | `tabs_model_ng.cpp` | sidebarAutoHide 设置侧边栏自动隐藏 | 默认 false | AC-3.9 |
| R-10 | 行为 | `tabs_pattern.cpp` | showSideBar=false + sidebarAutoHide=true → 内容区聚焦时侧边栏自动隐藏 | sidebarAutoHide 依赖 showSideBar | AC-3.10 |
| R-11 | 行为 | `tabs_model_ng.cpp` | minSidebarWidth 设置写入 TabsLayoutProperty::propMinSidebarWidth_ | 限制侧边栏最小宽度 | AC-3.11 |
| R-12 | 行为 | `tabs_model_ng.cpp` | maxSidebarWidth 设置写入 TabsLayoutProperty::propMaxSidebarWidth_ | 限制侧边栏最大宽度 | AC-3.12 |
| R-13 | 行为 | `tabs_model_ng.cpp` | minContentWidth 设置写入 TabsLayoutProperty::propMinContentWidth_ | 限制内容区最小宽度 | AC-3.13 |
| R-14 | 行为 | `tabs_model_ng.cpp` | sidebarPosition(Start) → 侧边栏位于左侧/顶部 | SidebarPosition 枚举 | AC-3.14 |
| R-15 | 行为 | `tabs_model_ng.cpp` | sidebarPosition(End) → 侧边栏位于右侧/底部 | SidebarPosition 枚举 | AC-3.15 |
| R-16 | 行为 | `tabs_model_ng.cpp` | barDisplayModeBreakpoint 设置断点自适应配置 | TabBarDisplayModeBreakpoint 含 sm/md/lg 断点值 | AC-3.16 |
| R-17 | 行为 | `tabs_pattern.cpp` | 窗口宽度 <= sm 断点 → 显示模式自动切换为 BottomTabBar | 断点自适应逻辑 | AC-3.17 |
| R-18 | 行为 | `tabs_pattern.cpp` | 窗口宽度 > md 断点 → 显示模式自动切换为 Sidebar | 断点自适应逻辑 | AC-3.18 |
| R-19 | 行为 | `tabs_model_ng.cpp` | sidebarHeader 设置侧边栏头部区域 | CustomBuilder 类型 | AC-3.19 |
| R-20 | 行为 | `tabs_model_ng.cpp` | sidebarFooter 设置侧边栏尾部区域 | CustomBuilder 类型 | AC-3.20 |
| R-21 | 行为 | `tabs_model_ng.cpp` | sidebarSearchable 设置侧边栏搜索功能 | SidebarSearchableOptions 含 autoSearchOnFocus/searchAreaHeight | AC-3.21 |
| R-22 | 行为 | `tabs_model_ng.cpp` | 断点触发 Bottom→Sidebar 切换 → onBarDisplayModeChange 回调 | 参数为 TabBarDisplayMode | AC-3.22 |
| R-23 | 行为 | `tabs_model_ng.cpp` | 侧边栏显示/隐藏变化 → onSideBarChange 回调 | 参数为 isVisible boolean | AC-3.23 |
| R-24 | 行为 | `tabs_model_ng.cpp` | 断点切换为 BottomTabBar → onBarDisplayModeChange 回调参数为 BOTTOM_TAB_BAR | — | AC-3.24 |
| R-25 | 行为 | `js_tabs.cpp` | TabContent sidebarSection 设置标签项分组 | string 类型 | AC-3.25 |
| R-26 | 行为 | `js_tabs.cpp` | TabContent defaultVisibility(Visible) → 标签项默认可见 | TabVisibility 枚举 | AC-3.26 |
| R-27 | 行为 | `js_tabs.cpp` | TabContent defaultVisibility(Hidden) → 标签项默认隐藏 | 需用户手动展开 | AC-3.27 |
| R-28 | 行为 | `js_tabs.cpp` | TabContent preferredPlacement 设置标签项排列偏好 | TabBarPlacement 枚举 | AC-3.28 |
| R-29 | 行为 | `js_tabs.cpp` | TabContent customizationBehavior 设置标签项自定义行为 | CustomizationBehavior 类型 | AC-3.29 |
| R-30 | 边界 | `tabs_layout_property.h` | 侧边栏模式仅 API >= 12 支持，API < 12 设置 SidebarAdaptable 不生效 | Container::LessThanAPIVersion 门控 | — |
| R-31 | 异常 | — | sidebarWidth 为 0 或负值时被钳位到 minSidebarWidth | 不崩溃 | — |
| R-32 | 恢复 | — | 断点切换失败时保持当前显示模式不变 | 不自动回退 | — |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-2 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-3 | AC-3.3 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-4 | AC-3.4 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-5 | AC-3.5 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-6 | AC-3.6 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-7 | AC-3.7 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-8 | AC-3.8 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-9 | AC-3.9 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-10 | AC-3.10 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-11 | AC-3.11 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-12 | AC-3.12 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-13 | AC-3.13 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-14 | AC-3.14 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-15 | AC-3.15 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-16 | AC-3.16 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-17 | AC-3.17 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-18 | AC-3.18 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-19 | AC-3.19 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-20 | AC-3.20 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-21 | AC-3.21 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-22 | AC-3.22 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-23 | AC-3.23 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-24 | AC-3.24 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-25 | AC-3.25 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-26 | AC-3.26 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-27 | AC-3.27 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-28 | AC-3.28 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-29 | AC-3.29 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 签名基于现有 SDK 定义。

#### TabsAttribute 侧边栏属性

```typescript
declare class TabsAttribute extends CommonMethod<TabsAttribute> {
  barStyle(value: BarStyle): TabsAttribute;
  sidebarWidth(value: Length): TabsAttribute;
  sidebarBackgroundColor(value: ResourceColor): TabsAttribute;
  sidebarDivider(value: TabsSidebarDivider): TabsAttribute;
  showSideBar(value: boolean): TabsAttribute;
  showSideBarWithGesture(value: boolean): TabsAttribute;
  sidebarAutoHide(value: boolean): TabsAttribute;
  minSidebarWidth(value: Length): TabsAttribute;
  maxSidebarWidth(value: Length): TabsAttribute;
  minContentWidth(value: Length): TabsAttribute;
  sidebarPosition(value: SidebarPosition): TabsAttribute;
  sidebarHeader(value: CustomBuilder): TabsAttribute;
  sidebarFooter(value: CustomBuilder): TabsAttribute;
  sidebarSearchable(value: SidebarSearchableOptions): TabsAttribute;
  barDisplayModeBreakpoint(value: TabBarDisplayModeBreakpoint): TabsAttribute;
  onBarDisplayModeChange(callback: (displayMode: TabBarDisplayMode) => void): TabsAttribute;
  onSideBarChange(callback: (isVisible: boolean) => void): TabsAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 存储位置 |
|----------|----------|------|--------|----------|
| `barStyle(value: BarStyle)` | TabsAttribute | 标签栏样式类型 | API 12 | TabsLayoutProperty::propBarStyle_ |
| `sidebarWidth(value: Length)` | TabsAttribute | 侧边栏宽度 | API 12 | TabsLayoutProperty::propSidebarWidth_ |
| `sidebarBackgroundColor(value: ResourceColor)` | TabsAttribute | 侧边栏背景颜色 | API 12 | TabsLayoutProperty::propSidebarBackgroundColor_ |
| `sidebarDivider(value: TabsSidebarDivider)` | TabsAttribute | 侧边栏分割线 | API 12 | TabsLayoutProperty::propSidebarDivider_ |
| `showSideBar(value: boolean)` | TabsAttribute | 侧边栏显示/隐藏 | API 12 | TabsLayoutProperty::propShowSideBar_ |
| `showSideBarWithGesture(value: boolean)` | TabsAttribute | 手势显示/隐藏 | API 12 | TabsLayoutProperty::propShowSideBarWithGesture_ |
| `sidebarAutoHide(value: boolean)` | TabsAttribute | 侧边栏自动隐藏 | API 12 | TabsLayoutProperty::propSidebarAutoHide_ |
| `minSidebarWidth(value: Length)` | TabsAttribute | 侧边栏最小宽度 | API 12 | TabsLayoutProperty::propMinSidebarWidth_ |
| `maxSidebarWidth(value: Length)` | TabsAttribute | 侧边栏最大宽度 | API 12 | TabsLayoutProperty::propMaxSidebarWidth_ |
| `minContentWidth(value: Length)` | TabsAttribute | 内容区最小宽度 | API 12 | TabsLayoutProperty::propMinContentWidth_ |
| `sidebarPosition(value: SidebarPosition)` | TabsAttribute | 侧边栏位置 | API 12 | TabsLayoutProperty::propSidebarPosition_ |
| `sidebarHeader(value: CustomBuilder)` | TabsAttribute | 侧边栏头部 | API 12 | TabsLayoutProperty |
| `sidebarFooter(value: CustomBuilder)` | TabsAttribute | 侧边栏尾部 | API 12 | TabsLayoutProperty |
| `sidebarSearchable(value: SidebarSearchableOptions)` | TabsAttribute | 侧边栏搜索 | API 12 | TabsLayoutProperty |
| `barDisplayModeBreakpoint(value: TabBarDisplayModeBreakpoint)` | TabsAttribute | 断点自适应配置 | API 12 | TabsLayoutProperty::propBarDisplayModeBreakpoint_ |
| `onBarDisplayModeChange(callback)` | TabsAttribute | 断点切换回调 | API 12 | TabsPattern 事件 |
| `onSideBarChange(callback)` | TabsAttribute | 侧边栏可见性回调 | API 12 | TabsPattern 事件 |

#### TabContent 侧边栏扩展属性

```typescript
declare class TabContentAttribute extends CommonMethod<TabContentAttribute> {
  sidebarSection(value: string): TabContentAttribute;
  defaultVisibility(value: TabVisibility): TabContentAttribute;
  preferredPlacement(value: TabBarPlacement): TabContentAttribute;
  customizationBehavior(value: CustomizationBehavior): TabContentAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since |
|----------|----------|------|--------|
| `sidebarSection(value: string)` | TabContentAttribute | 标签项分组 | API 12 |
| `defaultVisibility(value: TabVisibility)` | TabContentAttribute | 标签项默认可见性 | API 12 |
| `preferredPlacement(value: TabBarPlacement)` | TabContentAttribute | 标签项排列偏好 | API 12 |
| `customizationBehavior(value: CustomizationBehavior)` | TabContentAttribute | 标签项自定义行为 | API 12 |

#### 关联类型定义

| 类型 | 定义 | 用途 | @since |
|------|------|------|--------|
| TabsSidebarDivider | `{ strokeWidth?: Length, color?: ResourceColor, startMargin?: Length, endMargin?: Length }` | 侧边栏分割线 | API 12 |
| TabBarDisplayModeBreakpoint | `{ sm?: string, md?: string, lg?: string }` | 断点自适应配置 | API 12 |
| SidebarSearchableOptions | `{ autoSearchOnFocus?: boolean, searchAreaHeight?: Length }` | 侧边栏搜索配置 | API 12 |
| TabBarDisplayMode | BOTTOM_TAB_BAR / SIDEBAR | 显示模式枚举 | API 12 |
| SidebarDisplayStyle | EMBED / OVERLAY / DISPLACE | 侧边栏展示样式枚举 | API 12 |
| SidebarPosition | Start / End | 侧边栏位置枚举 | API 12 |
| TabVisibility | Visible / Hidden | 标签项可见性枚举 | API 12 |
| TabBarPlacement | Top / Bottom | 标签项排列偏好枚举 | API 12 |
| CustomizationBehavior | 自定义行为类型 | 标签项自定义行为 | API 12 |

#### 枚举映射

| ArkTS 枚举 | C++ 枚举 | 文件 |
|------------|----------|------|
| BarStyle.NoStyle | TabBarStyle::NOSTYLE | `tabs_constants.h` |
| BarStyle.BottomTabBar | TabBarStyle::BOTTOMTABBATSTYLE | `tabs_constants.h` |
| BarStyle.SidebarAdaptable | TabBarStyle::SIDEBARADAPTABLE | `tabs_constants.h` |
| SidebarPosition.Start | SidebarPosition::START | `tabs_constants.h` |
| SidebarPosition.End | SidebarPosition::END | `tabs_constants.h` |
| TabBarDisplayMode.BOTTOM_TAB_BAR | TabBarDisplayMode::BOTTOM_TAB_BAR | `tabs_constants.h` |
| TabBarDisplayMode.SIDEBAR | TabBarDisplayMode::SIDEBAR | `tabs_constants.h` |

---

### 变更/废弃 API

| API 名称 | 变更类型 | 关联 AC |
|----------|----------|---------|
| — | — | 无变更/废弃 API |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API < 12 | 侧边栏模式不支持（BarStyle.SidebarAdaptable 设置不生效） | API < 12 无法使用侧边栏模式 | 无需迁移（新属性默认不设置） |
| API 12 | 侧边栏模式全量支持（sidebarWidth/sidebarBackgroundColor/sidebarDivider/showSideBar/showSideBarWithGesture/sidebarAutoHide/minSidebarWidth/maxSidebarWidth/minContentWidth/sidebarPosition/sidebarHeader/sidebarFooter/sidebarSearchable/barDisplayModeBreakpoint） | 侧边栏模式完整能力 | 无需迁移 |
| API 12 | TabContent 侧边栏扩展（sidebarSection/defaultVisibility/preferredPlacement/customizationBehavior） | 侧边栏下标签项精细化控制 | 无需迁移 |
| API 12 | 断点自适应（barDisplayModeBreakpoint/onBarDisplayModeChange） | 不同屏幕尺寸自动切换 Bottom/Sidebar | 无需迁移 |
| API 12 | 侧边栏事件（onSideBarChange） | 侧边栏可见性变化回调 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| API 版本门控 | 侧边栏模式仅 API >= 12 支持，通过 Container::LessThanAPIVersion 门控 |
| Sidebar 属性存储 | 侧边栏属性全部存储在 TabsLayoutProperty（propSidebarWidth_/propSidebarBackgroundColor_/propSidebarDivider_/propShowSideBar_/propShowSideBarWithGesture_/propSidebarAutoHide_/propMinSidebarWidth_/propMaxSidebarWidth_/propMinContentWidth_/propSidebarPosition_/propBarDisplayModeBreakpoint_ 等） |
| 断点自适应逻辑 | TabsPattern::OnModifyDone 中根据 BarStyle == SIDEBARADAPTABLE 和 BarDisplayModeBreakpoint 断点值，在窗口宽度变化时自动切换 Bottom/Sidebar |
| Swiper 联动 | 侧边栏模式下 Swiper 内容区布局受 minContentWidth 约束 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 断点自适应切换应在单帧内完成，避免多次 layout |
| 可调试性 | TabsLayoutProperty 提供 DumpInfo（sidebarWidth/sidebarBackgroundColor/sidebarDivider/showSideBar/sidebarAutoHide/minSidebarWidth/maxSidebarWidth/minContentWidth/sidebarPosition/barDisplayModeBreakpoint）用于 Inspector 诊断 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 断点自适应 → 小屏自动切换为 BottomTabBar | sm 断点值配置 | — | — |
| 平板 | 断点自适应 → 大屏自动切换为 Sidebar | md/lg 断点值配置 | — | — |
| 折叠屏 | 折叠/展开时断点自适应触发 Bottom/Sidebar 切换 | onBarDisplayModeChange 回调 | — | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| Swiper | 侧边栏模式下 Swiper 内容区宽度受 minContentWidth 约束 |
| 焦点框架 | 侧边栏显示/隐藏时焦点需重新分配到内容区或侧边栏 |
| 断点机制 | BarDisplayModeBreakpoint 依赖窗口宽度变化监听（VpSizeChangeEvent） |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 业务规则/功能规则/异常规则/恢复契约编号连续且可追溯到源码
- [x] API 变更分析基于真实源码枚举定义
- [x] 兼容性声明标注 API 版本差异
- [x] 行为场景覆盖关键路径
- [x] 所有源码引用包含 file:line 信息
- [x] 构建系统影响章节已确认无变更

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp/.h` | Tabs 主 Pattern（侧边栏逻辑） |
| `frameworks/core/components_ng/pattern/tabs/tabs_layout_property.h` | Tabs 布局属性（Sidebar 系属性） |
| `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp/.h` | Tabs NG Model 层 |
| `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp/.h` | JS 桥接层 |
| `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs_constants.h` | 枚举定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` | Tabs 属性测试 |
| `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` | Tabs 事件测试 |
