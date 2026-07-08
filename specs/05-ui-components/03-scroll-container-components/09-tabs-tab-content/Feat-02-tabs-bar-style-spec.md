# 特性规格

> Func-05-03-09-Feat-02 Tabs/TabContent 标签栏样式：固化 SubTabBarStyle（构造器/.of()/indicator/selectedMode/board/labelStyle/padding/id）、BottomTabBarStyle（构造器/.of()/labelStyle/padding/layoutMode/verticalAlign/symmetricExtensible/id/iconStyle）、TabBarSymbol（normal/selected）、TabBarOptions（icon/text）、IndicatorStyle、DrawableTabBarIndicator（since 22）、BoardStyle、LabelStyle（overflow/maxLines/font/selectedColor since 12/unselectedColor since 12）、TabBarIconStyle（selectedColor/unselectedColor）、SelectedMode、BarGridColumnOptions、ScrollableBarModeOptions 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Tabs/TabContent 标签栏样式 (Tabs/TabContent Bar Style) |
| 特性编号 | Func-05-03-09-Feat-02 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 8 起支持，API 10+ 有多项扩展 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 高 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。覆盖 SubTabBarStyle/BottomTabBarStyle/TabBarSymbol 三种标签栏样式类及其全部属性（indicator/board/labelStyle/iconStyle/selectedMode/padding/layoutMode 等）、关联类型定义（IndicatorStyle/BoardStyle/LabelStyle/TabBarIconStyle/DrawableTabBarIndicator/BarGridColumnOptions/ScrollableBarModeOptions/SelectedMode/TabBarOptions）。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md` | Baselined |
| SDK API | `docs/sdk/ArkUI_SDK_API_Knowledge_Base.md` | — |
| SDK 组件 | `docs/sdk/Component_API_Knowledge_Base_CN.md` | — |

---

## 用户故事

### US-1: 配置子标签栏样式（SubTabBarStyle）

**作为** 应用开发者,
**我想要** 使用 SubTabBarStyle 构造器和属性方法配置顶部子标签栏样式（指示器/底板/标签样式/选中模式）,
**以便** 在顶部标签栏场景下精细控制标签的外观和交互反馈。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 使用 `SubTabBarStyle()` 构造器 THEN 创建默认子标签栏样式（SelectedMode=INDICATOR，无 Indicator/Board/LabelStyle 自定义） | 正常 |
| AC-2.2 | WHEN 使用 `SubTabBarStyle.of(contentModifier)` THEN 创建带 contentModifier 的子标签栏样式 | 正常 |
| AC-2.3 | WHEN 调用 `.indicator(IndicatorStyle)` THEN TabBarPaintProperty::propIndicator_ 被设置（strokeWidth/startMargin/endMargin/color/borderRadius） | 正常 |
| AC-2.4 | WHEN 调用 `.selectedMode(SelectedMode)` THEN TabBarPaintProperty::propSelectedMode_ 被设置（INDICATOR 或 BOARD） | 正常 |
| AC-2.5 | WHEN 调用 `.board(BoardStyle)` THEN TabBarPaintProperty::propBoard_ 被设置（borderRadius/backgroundColor） | 正常 |
| AC-2.6 | WHEN 调用 `.labelStyle(LabelStyle)` THEN TabBarPaintProperty::propLabelStyle_ 被设置（overflow/maxLines/font/fontSize/fontWeight/fontColor/height/selectedColor/unselectedColor） | 正常 |
| AC-2.7 | WHEN 调用 `.padding(Padding)` THEN 标签栏内间距被设置 | 正常 |
| AC-2.8 | WHEN 调用 `.id(string)` THEN 标签栏样式 id 被设置用于标识 | 正常 |

### US-2: 配置底部标签栏样式（BottomTabBarStyle）

**作为** 应用开发者,
**我想要** 使用 BottomTabBarStyle 构造器和属性方法配置底部图标标签栏样式（图标样式/标签样式/布局模式/对齐/可扩展）,
**以便** 在底部标签栏场景下精细控制图标+文字标签的外观和布局。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.9 | WHEN 使用 `BottomTabBarStyle()` 构造器 THEN 创建默认底部标签栏样式 | 正常 |
| AC-2.10 | WHEN 使用 `BottomTabBarStyle.of(contentModifier)` THEN 创建带 contentModifier 的底部标签栏样式 | 正常 |
| AC-2.11 | WHEN 调用 `.labelStyle(LabelStyle)` THEN 标签样式被设置（overflow/maxLines/font/selectedColor/unselectedColor） | 正常 |
| AC-2.12 | WHEN 调用 `.padding(Padding)` THEN 底部标签栏内间距被设置 | 正常 |
| AC-2.13 | WHEN 调用 `.layoutMode(BarLayoutMode)` THEN 底部标签栏布局模式被设置 | 正常 |
| AC-2.14 | WHEN 调用 `.verticalAlign(Alignment)` THEN 底部标签栏垂直对齐被设置 | 正常 |
| AC-2.15 | WHEN 调用 `.symmetricExtensible(boolean)` THEN 底部标签栏对称可扩展属性被设置 | 正常 |
| AC-2.16 | WHEN 调用 `.id(string)` THEN 底部标签栏样式 id 被设置 | 正常 |
| AC-2.17 | WHEN 调用 `.iconStyle(TabBarIconStyle)` THEN 底部标签栏图标样式被设置（selectedColor/unselectedColor） | 正常 |

### US-3: 配置标签栏符号图标（TabBarSymbol）

**作为** 应用开发者,
**我想要** 使用 TabBarSymbol 为标签栏配置 SymbolGlyph 图标（normal 和 selected 状态）,
**以便** 在标签栏中使用系统 Symbol 图标替代资源图片。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.18 | WHEN 创建 `TabBarSymbol(normal, selected)` THEN 标签栏图标使用 SymbolGlyph 分别表示未选中态和选中态 | 正常 |
| AC-2.19 | WHEN normal 为空 THEN 标签栏不显示未选中态图标 | 边界 |
| AC-2.20 | WHEN selected 为空 THEN 标签栏选中态不显示 Symbol 图标 | 边界 |

### US-4: 配置标签栏项图标和文字（TabBarOptions）

**作为** 应用开发者,
**我想要** 通过 TabBarOptions（icon/text）为 TabContent 配置标签栏项的图标和文字,
**以便** 在 TabContent 中声明标签栏项的基本内容。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.21 | WHEN TabContent 传入 `tabBarItem: { icon: Resource, text: string }` THEN 标签栏项显示图标和文字 | 正常 |
| AC-2.22 | WHEN icon 为空 THEN 标签栏项仅显示文字 | 边界 |
| AC-2.23 | WHEN text 为空 THEN 标签栏项仅显示图标 | 边界 |

### US-5: 配置可滚动标签栏模式选项

**作为** 应用开发者,
**我想要** 通过 ScrollableBarModeOptions 配置可滚动标签栏的额外属性（gridColumnOptions/非统一宽度）,
**以便** 在 BarMode.Scrollable 模式下精细控制标签栏列数和宽度分布。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.24 | WHEN 设置 ScrollableBarModeOptions.gridColumnOptions(BarGridColumnOptions) THEN 标签栏列数配置被设置（sm/md/lg 列数） | 正常 |
| AC-2.25 | WHEN 设置 ScrollableBarModeOptions.nonUniformHeight(boolean) THEN 标签栏非统一高度配置被设置 | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-2.1 | US-1 | R-1 | 代码审查 js_tabs.cpp |
| AC-2.2 | US-1 | R-2 | 代码审查 js_tabs.cpp |
| AC-2.3 | US-1 | R-3 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.4 | US-1 | R-4 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.5 | US-1 | R-5 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.6 | US-1 | R-6 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.7 | US-1 | R-7 | 代码审查 tabs_model_ng.cpp |
| AC-2.8 | US-1 | R-8 | 代码审查 js_tabs.cpp |
| AC-2.9 | US-2 | R-9 | 代码审查 js_tabs.cpp |
| AC-2.10 | US-2 | R-10 | 代码审查 js_tabs.cpp |
| AC-2.11 | US-2 | R-6 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.12 | US-2 | R-7 | 代码审查 tabs_model_ng.cpp |
| AC-2.13 | US-2 | R-11 | 代码审查 tabs_model_ng.cpp |
| AC-2.14 | US-2 | R-12 | 代码审查 tabs_model_ng.cpp |
| AC-2.15 | US-2 | R-13 | 代码审查 tabs_model_ng.cpp |
| AC-2.16 | US-2 | R-8 | 代码审查 js_tabs.cpp |
| AC-2.17 | US-2 | R-14 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-2.18 | US-3 | R-15 | 代码审查 js_tabs.cpp |
| AC-2.19 | US-3 | R-16 | 代码审查 tab_bar_pattern.cpp |
| AC-2.20 | US-3 | R-17 | 代码审查 tab_bar_pattern.cpp |
| AC-2.21 | US-4 | R-18 | 单元测试 tabs_test_ng.cpp |
| AC-2.22 | US-4 | R-19 | 代码审查 js_tabs.cpp |
| AC-2.23 | US-4 | R-20 | 代码审查 js_tabs.cpp |
| AC-2.24 | US-5 | R-21 | 代码审查 tabs_model_ng.cpp |
| AC-2.25 | US-5 | R-22 | 代码审查 tabs_model_ng.cpp |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `js_tabs.cpp` | SubTabBarStyle() 构造器创建默认子标签栏样式 | SelectedMode 默认 INDICATOR | AC-2.1 |
| R-2 | 行为 | `js_tabs.cpp` | SubTabBarStyle.of(contentModifier) 创建带自定义修饰器的子标签栏样式 | contentModifier 类型为 ContentModifier | AC-2.2 |
| R-3 | 行为 | `tab_bar_paint_property.h` | indicator 属性写入 TabBarPaintProperty::propIndicator_ | IndicatorStyle 含 strokeWidth/startMargin/endMargin/color/borderRadius | AC-2.3 |
| R-4 | 行为 | `tab_bar_paint_property.h` | selectedMode 属性写入 TabBarPaintProperty::propSelectedMode_ | SelectedMode 枚举: INDICATOR/BOARD | AC-2.4 |
| R-5 | 行为 | `tab_bar_paint_property.h` | board 属性写入 TabBarPaintProperty::propBoard_ | BoardStyle 含 borderRadius/backgroundColor | AC-2.5 |
| R-6 | 行为 | `tab_bar_paint_property.h` | labelStyle 属性写入 TabBarPaintProperty::propLabelStyle_ | LabelStyle 含 overflow/maxLines/font/fontSize/fontWeight/fontColor/height/selectedColor/unselectedColor | AC-2.6, AC-2.11 |
| R-7 | 行为 | `tabs_model_ng.cpp` | padding 属性设置标签栏内间距 | 支持 Padding/Length 类型 | AC-2.7, AC-2.12 |
| R-8 | 行为 | `js_tabs.cpp` | id 属性设置标签栏样式标识字符串 | 用于样式标识和查找 | AC-2.8, AC-2.16 |
| R-9 | 行为 | `js_tabs.cpp` | BottomTabBarStyle() 构造器创建默认底部标签栏样式 | 默认 layoutMode 和 verticalAlign | AC-2.9 |
| R-10 | 行为 | `js_tabs.cpp` | BottomTabBarStyle.of(contentModifier) 创建带自定义修饰器的底部标签栏样式 | contentModifier 类型为 ContentModifier | AC-2.10 |
| R-11 | 行为 | `tabs_model_ng.cpp` | layoutMode 属性设置底部标签栏布局模式 | BarLayoutMode 枚举 | AC-2.13 |
| R-12 | 行为 | `tabs_model_ng.cpp` | verticalAlign 属性设置底部标签栏垂直对齐 | Alignment 类型 | AC-2.14 |
| R-13 | 行为 | `tabs_model_ng.cpp` | symmetricExtensible 属性设置底部标签栏对称可扩展 | boolean 类型 | AC-2.15 |
| R-14 | 行为 | `tab_bar_paint_property.h` | iconStyle 属性写入 TabBarIconStyle | TabBarIconStyle 含 selectedColor/unselectedColor | AC-2.17 |
| R-15 | 行为 | `js_tabs.cpp` | TabBarSymbol(normal, selected) 为标签栏配置 SymbolGlyph 图标 | normal 和 selected 为 SymbolGlyphModifier | AC-2.18 |
| R-16 | 边界 | `tab_bar_pattern.cpp` | normal 为空时标签栏不显示未选中态 Symbol 图标 | 不影响选中态图标显示 | AC-2.19 |
| R-17 | 边界 | `tab_bar_pattern.cpp` | selected 为空时标签栏选中态不显示 Symbol 图标 | 选中态文字仍然显示 | AC-2.20 |
| R-18 | 行为 | `js_tabs.cpp` | TabBarOptions { icon, text } 配置标签栏项图标和文字 | icon 支持 Resource/ResourceStr | AC-2.21 |
| R-19 | 边界 | `js_tabs.cpp` | icon 为空时标签栏项仅显示文字 | 不显示图标占位 | AC-2.22 |
| R-20 | 边界 | `js_tabs.cpp` | text 为空时标签栏项仅显示图标 | 不显示文字区域 | AC-2.23 |
| R-21 | 行为 | `tabs_model_ng.cpp` | ScrollableBarModeOptions.gridColumnOptions 配置标签栏列数 | BarGridColumnOptions 含 sm/md/lg 列数 | AC-2.24 |
| R-22 | 行为 | `tabs_model_ng.cpp` | ScrollableBarModeOptions.nonUniformHeight 配置标签栏非统一高度 | boolean 类型 | AC-2.25 |
| R-23 | 行为 | `tab_bar_paint_property.h` | IndicatorStyle 渲染属性路径: strokeWidth/startMargin/endMargin/color/borderRadius | 默认值由 TabBarPaintProperty 提供 | — |
| R-24 | 行为 | `tab_bar_paint_property.h` | BoardStyle 渲染属性路径: borderRadius/backgroundColor | 默认值由 TabBarPaintProperty 提供 | — |
| R-25 | 行为 | `tab_bar_paint_property.h` | DrawableTabBarIndicator (since 22) 支持自定义绘制指示器 | 替代 IndicatorStyle 的绘制方式 | — |
| R-26 | 行为 | `js_tabs.cpp` | SubTabBarStyle 属性变更触发 TabBarPaintProperty 脏标记 PROPERTY_UPDATE_NORMAL 或 PROPERTY_UPDATE_MEASURE | indicator/board 变更触发绘制更新 | — |
| R-27 | 行为 | `js_tabs.cpp` | BottomTabBarStyle 属性变更触发对应脏标记 | layoutMode/verticalAlign 变更触发 PROPERTY_UPDATE_MEASURE | — |
| R-28 | 异常 | — | SubTabBarStyle.of 传入非法 contentModifier 类型时，样式创建失败并回退到默认样式 | 不崩溃 | — |
| R-29 | 恢复 | — | TabBarPaintProperty 属性写入失败时，保留前值不覆盖 | 部分属性设置失败不影响其他属性 | — |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-2.1 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-2 | AC-2.2 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-3 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-4 | AC-2.4 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-5 | AC-2.5 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-6 | AC-2.6 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-7 | AC-2.7 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-8 | AC-2.8 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-9 | AC-2.9 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-10 | AC-2.10 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-11 | AC-2.11 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-12 | AC-2.12 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-13 | AC-2.13 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-14 | AC-2.14 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-15 | AC-2.15 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-16 | AC-2.16 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-17 | AC-2.17 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-18 | AC-2.18 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-19 | AC-2.19 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tab_bar_pattern.cpp` |
| VM-20 | AC-2.20 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tab_bar_pattern.cpp` |
| VM-21 | AC-2.21 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` |
| VM-22 | AC-2.22 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-23 | AC-2.23 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |
| VM-24 | AC-2.24 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-25 | AC-2.25 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 签名基于现有 SDK 定义。

#### SubTabBarStyle

```typescript
declare class SubTabBarStyle {
  constructor();
  static of(contentModifier?: ContentModifier<TabContent>): SubTabBarStyle;
  indicator(value: IndicatorStyle): SubTabBarStyle;
  selectedMode(value: SelectedMode): SubTabBarStyle;
  board(value: BoardStyle): SubTabBarStyle;
  labelStyle(value: LabelStyle): SubTabBarStyle;
  padding(value: Padding | Length): SubTabBarStyle;
  id(value: string): SubTabBarStyle;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 存储位置 |
|----------|----------|------|--------|----------|
| `constructor()` | SubTabBarStyle | 默认子标签栏样式 | API 8 | — |
| `of(contentModifier?)` | SubTabBarStyle | 带自定义修饰器的子标签栏样式 | API 11 | — |
| `indicator(value)` | SubTabBarStyle | 指示器样式 | API 10 | TabBarPaintProperty::propIndicator_ |
| `selectedMode(value)` | SubTabBarStyle | 选中模式 | API 10 | TabBarPaintProperty::propSelectedMode_ |
| `board(value)` | SubTabBarStyle | 底板样式 | API 10 | TabBarPaintProperty::propBoard_ |
| `labelStyle(value)` | SubTabBarStyle | 标签样式 | API 10 | TabBarPaintProperty::propLabelStyle_ |
| `padding(value)` | SubTabBarStyle | 内间距 | API 10 | TabBarPaintProperty |
| `id(value)` | SubTabBarStyle | 样式标识 | API 10 | TabBarPaintProperty |

#### BottomTabBarStyle

```typescript
declare class BottomTabBarStyle {
  constructor();
  static of(contentModifier?: ContentModifier<TabContent>): BottomTabBarStyle;
  labelStyle(value: LabelStyle): BottomTabBarStyle;
  padding(value: Padding | Length): BottomTabBarStyle;
  layoutMode(value: BarLayoutMode): BottomTabBarStyle;
  verticalAlign(value: Alignment): BottomTabBarStyle;
  symmetricExtensible(value: boolean): BottomTabBarStyle;
  id(value: string): BottomTabBarStyle;
  iconStyle(value: TabBarIconStyle): BottomTabBarStyle;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 存储位置 |
|----------|----------|------|--------|----------|
| `constructor()` | BottomTabBarStyle | 默认底部标签栏样式 | API 8 | — |
| `of(contentModifier?)` | BottomTabBarStyle | 带自定义修饰器的底部标签栏样式 | API 11 | — |
| `labelStyle(value)` | BottomTabBarStyle | 标签样式 | API 10 | TabBarPaintProperty::propLabelStyle_ |
| `padding(value)` | BottomTabBarStyle | 内间距 | API 10 | TabBarPaintProperty |
| `layoutMode(value)` | BottomTabBarStyle | 布局模式 | API 10 | TabBarLayoutProperty |
| `verticalAlign(value)` | BottomTabBarStyle | 垂直对齐 | API 10 | TabBarLayoutProperty |
| `symmetricExtensible(value)` | BottomTabBarStyle | 对称可扩展 | API 10 | TabBarLayoutProperty |
| `id(value)` | BottomTabBarStyle | 样式标识 | API 10 | TabBarPaintProperty |
| `iconStyle(value)` | BottomTabBarStyle | 图标样式 | API 10 | TabBarPaintProperty::propIconStyle_ |

#### 关联类型定义

| 类型 | 定义 | 用途 | @since |
|------|------|------|--------|
| IndicatorStyle | `{ strokeWidth?: Length, startMargin?: Length, endMargin?: Length, color?: ResourceColor, borderRadius?: Length }` | 子标签栏指示器样式 | API 10 |
| BoardStyle | `{ borderRadius?: Length, backgroundColor?: ResourceColor }` | 子标签栏底板样式 | API 10 |
| LabelStyle | `{ overflow?: TextOverflow, maxLines?: number, font?: Font, selectedColor?: ResourceColor, unselectedColor?: ResourceColor }` | 标签文字样式 | API 10 (selectedColor/unselectedColor since 12) |
| TabBarIconStyle | `{ selectedColor?: ResourceColor, unselectedColor?: ResourceColor }` | 底部标签栏图标颜色 | API 10 |
| DrawableTabBarIndicator | 自定义绘制指示器 | 替代 IndicatorStyle 的绘制方式 | API 22 |
| SelectedMode | INDICATOR / BOARD | 选中模式枚举 | API 10 |
| TabBarSymbol | `{ normal: SymbolGlyphModifier, selected: SymbolGlyphModifier }` | 标签栏 Symbol 图标 | API 12 |
| TabBarOptions | `{ icon?: ResourceStr, text?: ResourceStr }` | 标签栏项图标和文字 | API 8 |
| BarGridColumnOptions | `{ sm?: number, md?: number, lg?: number }` | 标签栏列数配置 | API 11 |
| ScrollableBarModeOptions | `{ gridColumnOptions?: BarGridColumnOptions, nonUniformHeight?: boolean }` | 可滚动标签栏模式选项 | API 11 |

#### 枚举映射

| ArkTS 枚举 | C++ 枚举 | 文件 |
|------------|----------|------|
| SelectedMode.INDICATOR | SelectedMode::INDICATOR | `tabs_constants.h` |
| SelectedMode.BOARD | SelectedMode::BOARD | `tabs_constants.h` |
| TabBarStyle.NoStyle | TabBarStyle::NOSTYLE | `tabs_constants.h` |
| TabBarStyle.SubTabBarStyle | TabBarStyle::SUBTABBATSTYLE | `tabs_constants.h` |
| TabBarStyle.BottomTabBarStyle | TabBarStyle::BOTTOMTABBATSTYLE | `tabs_constants.h` |
| TabBarStyle.SidebarAdaptable | TabBarStyle::SIDEBARADAPTABLE | `tabs_constants.h` |

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
| API 8 | SubTabBarStyle/BottomTabBarStyle 仅支持构造器和 tabBarItem 基本设置 | 基础版本，无 indicator/board/labelStyle/selectedMode 属性方法 | 无需迁移 |
| API 10 | SubTabBarStyle 新增 indicator/selectedMode/board/labelStyle/padding/id 属性方法 | API < 10 不支持样式属性方法 | 无需迁移（新属性默认不设置） |
| API 10 | BottomTabBarStyle 新增 labelStyle/padding/layoutMode/verticalAlign/iconStyle/id 属性方法 | API < 10 不支持样式属性方法 | 无需迁移 |
| API 11 | SubTabBarStyle.of/BottomTabBarStyle.of 支持 ContentModifier | API < 11 不支持 .of() | 无需迁移 |
| API 12 | LabelStyle 新增 selectedColor/unselectedColor | API < 12 标签颜色由 font.fontColor 统一控制 | 无需迁移 |
| API 12 | TabBarSymbol 支持 SymbolGlyph 图标 | API < 12 仅支持 Resource 图标 | 无需迁移 |
| API 22 | DrawableTabBarIndicator 支持自定义绘制指示器 | API < 22 仅支持 IndicatorStyle 配置 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 三种样式类 | SubTabBarStyle/BottomTabBarStyle/SidebarAdaptable 三种样式类对应 TabBarStyle 枚举，存储在 TabBarPaintProperty |
| 属性分离存储 | Indicator/Board/SelectedMode/LabelStyle 存储在 TabBarPaintProperty，layoutMode/verticalAlign/symmetricExtensible 存储在 TabBarLayoutProperty |
| 枚举名差异 | ArkTS 枚举名 SubTabBarStyle/BottomTabBarStyle 与 C++ 枚举名 SUBTABBATSTYLE/BOTTOMTABBATSTYLE 不统一，需在规格中明确映射 |
| JSView 桥接 | 样式类属性通过 JSView 桥接层解析并分发到对应 PaintProperty/LayoutProperty |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | SubTabBarStyle/BottomTabBarStyle 属性设置应在单次属性更新中完成，避免多次绘制 |
| 可调试性 | TabBarPaintProperty 提供 DumpInfo（indicator/board/selectedMode/labelStyle/iconStyle）用于 Inspector 诊断 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | BarGridColumnOptions 可差异化配置列数 | sm/md/lg 列数断点 | — | — |
| 折叠屏 | 同平板 | sm/md/lg 列数断点 | — | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| TabBar Pattern | SubTabBarStyle/BottomTabBarStyle 属性变更触发 TabBarPattern 重绘 |
| SymbolGlyph | TabBarSymbol 依赖 SymbolGlyph 组件渲染能力 |
| ContentModifier | SubTabBarStyle.of/BottomTabBarStyle.of 依赖 ContentModifier 框架 |

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
| `frameworks/core/components_ng/pattern/tabs/tab_bar_paint_property.h` | TabBar 渲染属性 |
| `frameworks/core/components_ng/pattern/tabs/tab_bar_layout_property.h/.cpp` | TabBar 布局属性 |
| `frameworks/core/components_ng/pattern/tabs/tab_bar_pattern.cpp/.h` | TabBar Pattern |
| `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp/.h` | Tabs NG Model 层 |
| `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp/.h` | JS 桥接层 |
| `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs_constants.h` | 枚举定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` | Tabs 属性测试 |
| `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` | Tabs NG 单元测试 |
