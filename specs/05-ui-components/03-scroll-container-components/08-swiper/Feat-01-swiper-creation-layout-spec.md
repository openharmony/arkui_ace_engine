# 特性规格

> Func-05-03-08-Feat-01 创建与布局属性：固化 Swiper 创建、index、loop、vertical、displayMode、displayCount、itemSpace、prevMargin、nextMargin、cachedCount、SwiperAutoFill、SwiperDisplayMode 等基础布局属性行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 创建与布局属性 (Creation & Layout Properties) |
| 特性编号 | Func-05-03-08-Feat-01 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 7 起支持 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

> 历史规格补齐，补录已有实现的完整行为规格。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/08-swiper/design.md` | Baselined |

---

## 用户故事

### US-1: 创建 Swiper 轮播容器并设置初始索引

**作为** 应用开发者,
**我想要** 创建 Swiper 轮播容器并指定初始显示的子项索引,
**以便** 在页面加载时显示指定页面而非默认第一页。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `Swiper(controller?: SwiperController)` 构造函数 THEN 创建 Swiper 轮播容器 FrameNode，初始索引为 0 | 正常 |
| AC-1.2 | WHEN 调用 `.index(value: number)` THEN 设置初始显示索引，默认值为 0 | 正常 |
| AC-1.3 | WHEN index 超出子项范围（index >= totalChildren） THEN Pattern 层将 index 修正为 totalChildren - 1 | 异常 |
| AC-1.4 | WHEN index 为负数 THEN Pattern 层将 index 修正为 0 | 异常 |
| AC-1.5 | WHEN index 变更时 THEN 触发 PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT，重新布局 | 正常 |
| AC-1.6 | WHEN 使用 SwiperController.swipeTo(index, useAnimation) THEN 不改变 LayoutProperty 中 index 的值，仅驱动动画跳转 | 正常 |

> index 属性存储在 `swiper_layout_property.h`，变更标志为 PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT。Pattern 层修正逻辑：`swiper_pattern.cpp` OnModifyDone。

### US-2: 配置轮播布局方向和显示模式

**作为** 应用开发者,
**我想要** 配置 Swiper 的滑动方向（水平/垂直）和显示模式（拉伸/自适应）,
**以便** 适配不同布局场景。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.vertical(value: boolean)` THEN 设置滑动方向，false 为水平（Axis::HORIZONTAL，默认），true 为垂直（Axis::VERTICAL） | 正常 |
| AC-2.2 | WHEN 调用 `.displayMode(value: SwiperDisplayMode)` THEN 设置显示模式，默认 STRETCH(0) | 正常 |
| AC-2.3 | WHEN displayMode 为 STRETCH(0) THEN 子项等分容器主轴尺寸减去 prevMargin/nextMargin/itemSpace | 正常 |
| AC-2.4 | WHEN displayMode 为 AUTO_LINEAR(1) THEN 子项按 minSize 自适应排列，不强制填满容器 | 正常 |
| AC-2.5 | WHEN 设置了 displayCount 且未设置 minSize THEN 强制使用 STRETCH 模式（IsStretch() 返回 true） | 边界 |
| AC-2.6 | WHEN 设置了 displayCount 且设置了 minSize THEN 使用 minSize 控制的自适应布局 | 边界 |
| AC-2.7 | WHEN vertical/direction 变更时 THEN 触发 PROPERTY_UPDATE_MEASURE | 正常 |

> SwiperDisplayMode 枚举 2 个值（0=STRETCH, 1=AUTO_LINEAR），`swiper_constants.h:20-23`。IsStretch() 逻辑：`swiper_layout_property.h:230-238`。

### US-3: 配置多页显示和间距

**作为** 应用开发者,
**我想要** 配置 Swiper 同屏显示多个子项及其间距,
**以便** 实现预览多页的轮播效果。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.displayCount(value: number \| SwiperAutoFill, swipeByGroup?: boolean)` THEN 设置同屏显示数量，默认值为 1 | 正常 |
| AC-3.2 | WHEN displayCount 为数字 THEN 容器主轴方向等分显示指定数量的子项 | 正常 |
| AC-3.3 | WHEN displayCount 为 SwiperAutoFill 对象 `{ overflow: number }` THEN 根据容器尺寸自动计算显示数量，overflow 指定超出部分占比 | 正常 |
| AC-3.4 | WHEN displayCount 设置后 THEN itemSpace 可能被忽略（ignoreItemSpace_ = true），displayCount 和 margin 的优先级高于 itemSpace | 边界 |
| AC-3.5 | WHEN 调用 `.itemSpace(value: number \| Dimension)` THEN 设置子项间距，默认值为 0vp | 正常 |
| AC-3.6 | WHEN displayCount > 1 且 itemSpace 设置 THEN 布局算法在子项之间插入指定间距 | 正常 |
| AC-3.7 | WHEN displayCount 设置但 ignoreItemSpace_ 为 true THEN itemSpace 在布局计算中被忽略 | 边界 |
| AC-3.8 | WHEN displayCount 变更时 THEN 触发 PROPERTY_UPDATE_MEASURE | 正常 |
| AC-3.9 | WHEN itemSpace 变更时 THEN 触发 PROPERTY_UPDATE_MEASURE | 正常 |
| AC-3.10 | WHEN swipeByGroup 为 true THEN 每次滑动以 displayCount 个子项为单位 | 正常 |

> displayCount 与 itemSpace 优先级规则：`swiper_layout_algorithm.cpp`。ignoreItemSpace_ 标志：`swiper_layout_property.h:290-293`。SwiperAutoFill 类型：`arkoala_api_generated.h:17902-17905`（overflow: number）。

### US-4: 配置前后预览边距

**作为** 应用开发者,
**我想要** 配置 Swiper 前后预览边距（prevMargin/nextMargin）,
**以便** 在当前页前后显示相邻页的缩略预览。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.prevMargin(value: number \| Dimension, ignoreBlank?: boolean)` THEN 设置前预览边距，默认值为 0vp | 正常 |
| AC-4.2 | WHEN 调用 `.nextMargin(value: number \| Dimension, ignoreBlank?: boolean)` THEN 设置后预览边距，默认值为 0vp | 正常 |
| AC-4.3 | WHEN prevMargin/nextMargin 设置且 displayMode 为 STRETCH THEN 布局算法在前后预留指定尺寸区域，显示相邻子项缩略图 | 正常 |
| AC-4.4 | WHEN prevMargin/nextMargin 设置且 displayMode 非 STRETCH THEN GetCalculatedPrevMargin/GetCalculatedNextMargin 返回 0，margin 不生效 | 边界 |
| AC-4.5 | WHEN ignorePrevMarginAndNextMargin_ 为 true THEN GetCalculatedPrevMargin/GetCalculatedNextMargin 返回 0，即使 displayMode 为 STRETCH | 边界 |
| AC-4.6 | WHEN prevMarginIgnoreBlank 为 true THEN 前预览区域不渲染空白背景 | 正常 |
| AC-4.7 | WHEN nextMarginIgnoreBlank 为 true THEN 后预览区域不渲染空白背景 | 正常 |
| AC-4.8 | WHEN prevMargin/nextMargin 变更时 THEN 触发 PROPERTY_UPDATE_MEASURE | 正常 |

> GetCalculatedPrevMargin/GetCalculatedNextMargin 逻辑：`swiper_layout_property.h:214-228`。ignorePrevMarginAndNextMargin_ 标志用于 displayCount 与 margin 优先级冲突。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.6 | R-1, R-5 | — | 代码审查 | `swiper_layout_property.h:256`, `swiper_pattern.cpp` |
| AC-2.1~2.7 | R-2, R-3 | — | 单元测试 | `swiper_layout_algorithm.cpp`, `swiper_layout_property.h:230-238` |
| AC-3.1~3.10 | R-4, R-6, R-7 | — | 单元测试 | `swiper_layout_algorithm.cpp` |
| AC-4.1~4.8 | R-8, R-9 | — | 单元测试 | `swiper_layout_property.h:214-228` |

## 规则定义

> **统一规则表，取消 FR/BR/EX/RC 四分类。** 类型标签：**行为**（正常路径下的系统行为）、**边界**（输入/状态的临界点）、**异常**（非法输入或异常状态的处理）、**恢复**（系统异常后的恢复策略）。

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | Swiper 组件属性分布在两层存储：LayoutProperty（触发 MEASURE/LAYOUT 的属性）、PaintProperty（触发 RENDER 的动画属性），属性变更的影响范围由存储层决定 | — | — |
| R-2 | 行为 | — | displayMode STRETCH(0) 为默认值，子项等分容器主轴尺寸减去 margin 和 itemSpace；AUTO_LINEAR(1) 按 minSize 自适应排列 | — | AC-2.3, AC-2.4 |
| R-3 | 行为 | — | 设置 displayCount 且未设置 minSize 时，IsStretch() 返回 true，强制使用 STRETCH 模式 | — | AC-2.5, AC-2.6 |
| R-4 | 行为 | — | displayCount 为数字时等分显示指定数量子项；为 SwiperAutoFill 时根据 overflow 自动计算显示数量 | — | AC-3.2, AC-3.3 |
| R-5 | 行为 | — | index 超出子项范围时 Pattern 层修正为 totalChildren - 1；为负数时修正为 0；SwiperController.swipeTo 不改变 LayoutProperty index 值 | — | AC-1.3~1.6 |
| R-6 | 边界 | — | displayCount 设置后 itemSpace 可能被忽略（ignoreItemSpace_ = true），displayCount 和 margin 优先级高于 itemSpace | — | AC-3.4, AC-3.7 |
| R-7 | 行为 | — | swipeByGroup 为 true 时每次滑动以 displayCount 个子项为单位 | — | AC-3.10 |
| R-8 | 行为 | — | prevMargin/nextMargin 仅在 STRETCH 模式下生效；非 STRETCH 模式或 ignorePrevMarginAndNextMargin_ 为 true 时返回 0 | — | AC-4.3~4.5 |
| R-9 | 行为 | — | prevMarginIgnoreBlank/nextMarginIgnoreBlank 为 true 时预览区域不渲染空白背景 | — | AC-4.6, AC-4.7 |
| R-10 | 异常 | — | loop 在子项数量 <= 1 时被 Pattern 层强制设为 false，无论用户设置值 | — | — |
| R-11 | 行为 | — | loop 默认值为 true，存储在 SwiperLayoutProperty，变更触发 PROPERTY_UPDATE_MEASURE_SELF | — | — |
| R-12 | 行为 | — | vertical 对应 Axis 枚举：false = HORIZONTAL（默认），true = VERTICAL | — | AC-2.1 |
| R-13 | 异常 | — | cachedCount 默认值为 1，必须 >= 0；设置负数时桥接层静默拒绝 | — | — |
| R-14 | 恢复 | — | — | — | — |
| R-15 | 恢复 | — | — | — | — |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.6 (创建与初始索引) | XTS + 代码审查 | index 修正逻辑和变更触发标志 |
| VM-2 | AC-2.1~2.7 (布局方向与显示模式) | 单元测试 | STRETCH/AUTO_LINEAR 布局计算和 IsStretch() 判断 |
| VM-3 | AC-3.1~3.10 (多页显示与间距) | 单元测试 | displayCount 布局计算、SwiperAutoFill、ignoreItemSpace_ 优先级 |
| VM-4 | AC-4.1~4.8 (前后预览边距) | 单元测试 | prevMargin/nextMargin 计算逻辑和 ignoreBlank |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `Swiper(controller?: SwiperController)` | Public | 创建 Swiper 轮播容器 | AC-1.1 |
| `index(value: number)` | Public | 设置初始索引（默认 0） | AC-1.2~1.5 |
| `loop(value: boolean)` | Public | 设置循环滑动（默认 true） | R-10, R-11 |
| `vertical(value: boolean)` | Public | 设置纵向滑动 | AC-2.1 |
| `displayMode(value: SwiperDisplayMode)` | Public | 设置显示模式（默认 STRETCH） | AC-2.2~2.6 |
| `displayCount(value: number \| SwiperAutoFill, swipeByGroup?: boolean)` | Public | 设置同屏显示数量 | AC-3.1~3.10 |
| `itemSpace(value: number \| Dimension)` | Public | 设置子项间距（默认 0vp） | AC-3.5~3.7 |
| `prevMargin(value: number \| Dimension, ignoreBlank?: boolean)` | Public | 设置前预览边距 | AC-4.1~4.8 |
| `nextMargin(value: number \| Dimension, ignoreBlank?: boolean)` | Public | 设置后预览边距 | AC-4.1~4.8 |
| `cachedCount(value: number \| CachedCountOptions)` | Public | 设置预加载缓存数量 | R-13 |
| `fillType(value: int32_t)` | Public | 设置 SwiperAutoFill 填充策略 | AC-3.3 |

### 变更/废弃 API

无。

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

- **已有 API 行为变更:** 否
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** API 7
- **API 版本号策略:** @since 7 标注基础属性

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| 属性两层存储 | index/direction/displayMode/displayCount/itemSpace/prevMargin/nextMargin/loop/cachedCount 存 LayoutProperty；autoPlay/duration/curve 存 PaintProperty | AC-1~4 |
| displayCount 优先级 | displayCount 设置后 itemSpace 可能被忽略（ignoreItemSpace_），margin 和 displayCount 优先级高于 itemSpace | AC-3.4, AC-3.7 |
| prevMargin/nextMargin 模式约束 | 仅 STRETCH 模式下 prevMargin/nextMargin 生效；非 STRETCH 或 ignorePrevMarginAndNextMargin_ 时返回 0 | AC-4.3~4.5 |
| loop 子项约束 | loop 在子项 <=1 时强制 false | R-10 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | cachedCount 预加载减少首次渲染延迟 | 代码审查 | `swiper_pattern.cpp` |
| 内存 | displayCount 控制同屏子项数量，影响布局内存占用 | 代码审查 | `swiper_layout_algorithm.cpp` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ArcSwiper 使用弧形布局 | SUPPORT_DIGITAL_CROWN 宏守卫 | 构建验证 | `arc_swiper_pattern.h` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 是 | Swiper 支持 aria-role/aria-label | 桥接层处理 |
| 大字体 | 否 | Swiper 子项尺寸由 displayMode/displayCount 控制 | — |
| 深色模式 | 否 | 深色模式由子项自行处理 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | displayCount SwiperAutoFill 类型在 API 版本中逐步增强 | AC-3.3 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper 创建与布局属性

  Scenario: 创建 Swiper 并设置初始索引
    Given 一个 Swiper 组件，包含 5 个子项
    When 调用 .index(2) 设置初始索引
    Then Swiper 初始显示第 3 个子项（index=2）
    When 调用 .index(10) 设置超出范围的索引
    Then Pattern 层将 index 修正为 4（totalChildren - 1）

  Scenario: 设置 displayMode 为 STRETCH（默认值）
    Given 一个 Swiper 组件，未显式设置 displayMode
    And 容器主轴尺寸为 360vp，displayCount 为 1
    When 触发布局计算
    Then 子项占据全部主轴尺寸 360vp

  Scenario: 设置 displayCount 为 3
    Given 一个 Swiper 组件，displayCount 设置为 3
    And 容器主轴尺寸为 360vp，itemSpace 为 10vp
    When 触发布局计算
    Then 每个子项宽度为 (360 - 2*10) / 3 = 113.33vp
    And ignoreItemSpace_ 可能被设为 true 或 false，取决于 margin 设置

  Scenario: 设置 prevMargin 和 nextMargin
    Given 一个 Swiper 组件，displayMode 为 STRETCH
    And prevMargin 为 40vp，nextMargin 为 40vp
    And 容器主轴尺寸为 360vp
    When 触发布局计算
    Then 前预览区域 40vp，后预览区域 40vp
    And 当前子项占据 360 - 40 - 40 = 280vp

  Scenario: prevMargin/nextMargin 非 STRETCH 模式不生效
    Given 一个 Swiper 组件，displayMode 为 AUTO_LINEAR
    And prevMargin 为 40vp，nextMargin 为 40vp
    When 触发布局计算
    Then GetCalculatedPrevMargin() 返回 0
    And GetCalculatedNextMargin() 返回 0

  Scenario: loop 在子项 <=1 时强制 false
    Given 一个 Swiper 组件，loop 设置为 true
    And 包含 1 个子项
    When Pattern 层 OnModifyDone 执行
    Then loop_ 被强制设为 false

  Scenario: displayCount 为 SwiperAutoFill 自动计算
    Given 一个 Swiper 组件，displayCount 设置为 { overflow: 1 }
    And 容器主轴尺寸为 360vp
    When 触发布局计算
    Then 根据 overflow 值和容器尺寸自动计算 displayCount
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（创建与布局属性，不含自动播放/指示器/动画/事件）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper LayoutProperty/PaintProperty two-layer property storage and displayMode displayCount layout algorithm"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper prevMargin nextMargin calculated margin and ignoreBlank behavior"
```

**关键文档：** `design.md`（同目录）
