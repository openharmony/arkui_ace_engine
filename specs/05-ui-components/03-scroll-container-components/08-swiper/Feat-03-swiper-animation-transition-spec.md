# 特性规格

> Func-05-03-08-Feat-03 动画与过渡：固化 Swiper duration/curve/effectMode、customContentTransition/SwiperContentTransitionProxy、SwiperAnimationMode/pageFlipMode 等动画与过渡行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 动画与过渡 (Animation & Transition) |
| 特性编号 | Func-05-03-08-Feat-03 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 7 起支持（部分属性 @since 12/15） |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/08-swiper/design.md` | Baselined |

---

## 用户故事

### US-1: 配置动画时长和曲线

**作为** 应用开发者,
**我想要** 配置 Swiper 翻页动画时长和曲线,
**以便** 控制翻页动画的速度和效果。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.duration(value: number)` THEN 设置翻页动画时长，默认 400ms，存储在 SwiperPaintProperty SwiperAnimationStyle 组 | 正常 |
| AC-1.2 | WHEN 调用 `.curve(value: Curve \| string \| ICurve)` THEN 设置动画曲线，默认 Curve.EASE_OUT | 正常 |
| AC-1.3 | WHEN duration 变更 THEN 触发 PROPERTY_UPDATE_RENDER | 正常 |
| AC-1.4 | WHEN curve 变更 THEN 触发 PROPERTY_UPDATE_RENDER | 正常 |

> duration/curve 存储在 SwiperPaintProperty SwiperAnimationStyle 组：`swiper_paint_property.h:71-72`。DEFAULT_DURATION = 400ms。

### US-2: 配置边缘效果

**作为** 应用开发者,
**我想要** 配置 Swiper 边缘滑动效果,
**以便** 控制到达边界时的视觉反馈。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.effectMode(value: EdgeEffect)` THEN 设置边缘效果模式，默认 EdgeEffect.Spring | 正常 |
| AC-2.2 | WHEN effectMode 为 EdgeEffect.Spring THEN 到达边界时弹性回弹效果 | 正常 |
| AC-2.3 | WHEN effectMode 为 EdgeEffect.Fade THEN 到达边界时渐隐效果，fadeColor 可自定义 | 正常 |
| AC-2.4 | WHEN effectMode 为 EdgeEffect.None THEN 到达边界时无任何效果 | 正常 |
| AC-2.5 | WHEN effectMode 变更 THEN 触发 PROPERTY_UPDATE_RENDER | 正常 |

> edgeEffect 存储在 SwiperPaintProperty：`swiper_paint_property.h:75`。fadeColor：`swiper_paint_property.h:76`。

### US-3: 配置自定义内容过渡

**作为** 应用开发者,
**我想要** 配置 Swiper 自定义内容过渡动画（customContentTransition）,
**以便** 实现自定义的翻页过渡效果。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.customContentTransition(value: SwiperContentAnimatedTransition)` THEN 设置自定义过渡动画（@since 12） | 正常 |
| AC-3.2 | WHEN SwiperContentAnimatedTransition.transition 回调触发 THEN 接收 SwiperContentTransitionProxy 参数 | 正常 |
| AC-3.3 | WHEN SwiperContentTransitionProxy.selectedIndex 获取 THEN 返回当前选中页索引 | 正常 |
| AC-3.4 | WHEN SwiperContentTransitionProxy.index 获取 THEN 返回过渡目标页索引 | 正常 |
| AC-3.5 | WHEN SwiperContentTransitionProxy.position 获取 THEN 返回过渡位置偏移（0.0~1.0） | 正常 |
| AC-3.6 | WHEN SwiperContentTransitionProxy.mainAxisLength 获取 THEN 返回主轴长度 | 正常 |
| AC-3.7 | WHEN SwiperContentTransitionProxy.finishTransition() 调用 THEN 结束当前自定义过渡 | 正常 |
| AC-3.8 | WHEN SwiperContentAnimatedTransition.timeout 设置 THEN 自定义过渡超时时间生效，超时后自动结束过渡 | 正常 |
| AC-3.9 | WHEN 调用 `.disableTransitionAnimation(value: boolean)` THEN 禁用所有过渡动画，默认 false | 正常 |

> customContentTransition 映射：`swiper_model_ng.cpp`。SwiperContentTransitionProxy：`swiper_content_transition_proxy.h/.cpp`。timeout 逻辑：`swiper_pattern.cpp`。

### US-4: 配置动画模式

**作为** 应用开发者,
**我想要** 配置 Swiper 动画模式（SwiperAnimationMode）,
**以便** 控制翻页动画行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN SwiperAnimationMode.NO_ANIMATION(0) THEN 无动画翻页 | 正常 |
| AC-4.2 | WHEN SwiperAnimationMode.DEFAULT_ANIMATION(1) THEN 默认动画翻页 | 正常 |
| AC-4.3 | WHEN SwiperAnimationMode.FAST_ANIMATION(2) THEN 快速动画翻页（@since 15） | 正常 |
| AC-4.4 | WHEN SwiperController.changeIndex(index, animationMode) THEN 指定动画模式翻页 | 正常 |

> SwiperAnimationMode 枚举：`constants.h:960-965`（NO_ANIMATION=0, DEFAULT_ANIMATION=1, FAST_ANIMATION=2）。SwiperController.changeIndex：`swiper_controller.h:99-104`。

### US-5: 配置翻页模式

**作为** 应用开发者,
**我想要** 配置 Swiper 鼠标滚轮翻页模式（pageFlipMode）,
**以便** 控制连续滚轮翻页行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `.pageFlipMode(value: PageFlipMode)` THEN 设置鼠标滚轮翻页模式（@since 15） | 正常 |
| AC-5.2 | WHEN PageFlipMode.CONTINUOUS(0) THEN 滚轮连续翻页，根据滚轮事件次数翻多页 | 正常 |
| AC-5.3 | WHEN PageFlipMode.SINGLE(1) THEN 滚轮单页翻页，翻页动画结束前不响应新滚轮事件 | 正常 |

> PageFlipMode 枚举：`swiper_pattern.h:46-49`（CONTINUOUS=0, SINGLE=1）。C API：ArkUI_PageFlipMode（CONTINUOUS=0, SINGLE=1）。

### US-6: C API 动画与过渡枚举

**作为** NDK 开发者,
**我想要** 通过 C API 配置 Swiper 动画与过渡属性,
**以便** 在 NDK 应用中使用动画与过渡功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 使用 NODE_SWIPER_DURATION 属性 THEN 设置翻页动画时长 | 正常 |
| AC-6.2 | WHEN 使用 NODE_SWIPER_CURVE 属性 THEN 设置动画曲线 | 正常 |
| AC-6.3 | WHEN 使用 NODE_SWIPER_EDGE_EFFECT_MODE 属性 THEN 设置边缘效果模式 | 正常 |
| AC-6.4 | WHEN 使用 NODE_SWIPER_PAGE_FLIP_MODE 属性 THEN 设置翻页模式 | 正常 |
| AC-6.5 | WHEN ArkUI_SwiperAnimationMode 枚举使用 THEN 对应 NO_ANIMATION/DEFAULT_ANIMATION/FAST_ANIMATION | 正常 |
| AC-6.6 | WHEN ArkUI_PageFlipMode 枚举使用 THEN 对应 CONTINUOUS/SINGLE | 正常 |

> C API 属性枚举：`native_node.h:7999-8301`。C API 枚举：`native_type.h:697`（ArkUI_PageFlipMode）。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.4 | R-1 | — | 代码审查 + XTS | `swiper_paint_property.h:71-72` |
| AC-2.1~2.5 | R-2 | — | 代码审查 + XTS | `swiper_paint_property.h:75-76` |
| AC-3.1~3.9 | R-3 | — | 代码审查 + XTS | `swiper_content_transition_proxy.h/.cpp` |
| AC-4.1~4.4 | R-4 | — | 代码审查 + XTS | `constants.h:960-965` |
| AC-5.1~5.3 | R-5 | — | 代码审查 + XTS | `swiper_pattern.h:46-49` |
| AC-6.1~6.6 | R-6 | — | C API 单元测试 | `native_node.h:7999-8301` |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | duration/curve 存储在 SwiperPaintProperty SwiperAnimationStyle 组，变更触发 PROPERTY_UPDATE_RENDER；duration 默认 400ms，curve 默认 Curve.EASE_OUT | — | AC-1.1~1.4 |
| R-2 | 行为 | — | effectMode 默认 EdgeEffect.Spring；Spring=弹性回弹，Fade=渐隐效果（fadeColor 可自定义），None=无效果 | — | AC-2.1~2.5 |
| R-3 | 行为 | — | customContentTransition 提供 transition 回调和 timeout；SwiperContentTransitionProxy 提供 selectedIndex/index/position/mainAxisLength/finishTransition | — | AC-3.1~3.9 |
| R-4 | 行为 | — | SwiperAnimationMode 三种：NO_ANIMATION(0)、DEFAULT_ANIMATION(1)、FAST_ANIMATION(2)；changeIndex 可指定动画模式 | — | AC-4.1~4.4 |
| R-5 | 行为 | — | PageFlipMode 两种：CONTINUOUS(0)=连续翻页，SINGLE(1)=单页翻页 | — | AC-5.1~5.3 |
| R-6 | 行为 | — | C API 动画属性：NODE_SWIPER_DURATION/CURVE/EDGE_EFFECT_MODE/PAGE_FLIP_MODE；C API 枚举：ArkUI_SwiperAnimationMode/ArkUI_PageFlipMode | — | AC-6.1~6.6 |
| R-7 | 边界 | — | disableTransitionAnimation 为 true 时所有过渡动画被禁用，包括 autoPlay 翻页动画 | — | AC-3.9 |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.4 (动画时长和曲线) | XTS + 代码审查 | duration/curve 存储和变更触发 |
| VM-2 | AC-2.1~2.5 (边缘效果) | XTS + 代码审查 | effectMode 三种模式行为 |
| VM-3 | AC-3.1~3.9 (自定义内容过渡) | XTS + 代码审查 | SwiperContentTransitionProxy 和 timeout |
| VM-4 | AC-4.1~4.4 (动画模式) | XTS + 代码审查 | SwiperAnimationMode 三种模式 |
| VM-5 | AC-5.1~5.3 (翻页模式) | XTS + 代码审查 | PageFlipMode 连续/单页 |
| VM-6 | AC-6.1~6.6 (C API 动画枚举) | C API 单元测试 | NODE_SWIPER_* 动画属性和枚举 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `duration(value: number)` | Public | 设置动画时长（ms） | AC-1.1 |
| `curve(value: Curve \| ICurve)` | Public | 设置动画曲线 | AC-1.2 |
| `effectMode(value: EdgeEffect)` | Public | 设置边缘效果模式 | AC-2.1 |
| `customContentTransition(value: SwiperContentAnimatedTransition)` | Public | 设置自定义内容过渡动画 | AC-3.1 |
| `disableTransitionAnimation(value: boolean)` | Public | 禁用过渡动画 | AC-3.9 |
| `pageFlipMode(value: PageFlipMode)` | Public | 设置翻页模式 | AC-5.1 |
| `SwiperAnimationMode` | Public | 动画模式枚举（NO_ANIMATION/DEFAULT_ANIMATION/FAST_ANIMATION） | AC-4.1~4.3 |
| `ArkUI_SwiperAnimationMode` | System | C API 动画模式枚举 | AC-6.5 |
| `ArkUI_PageFlipMode` | System | C API 翻页模式枚举 | AC-6.6 |

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
- **API 版本号策略:** duration/curve @since 7；effectMode @since 7；customContentTransition @since 12；SwiperAnimationMode.FAST_ANIMATION @since 15；pageFlipMode @since 15

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| 动画属性存储 | duration/curve 存 PaintProperty SwiperAnimationStyle 组，edgeEffect 存 PaintProperty | AC-1.1~1.4, AC-2.1~2.5 |
| 自定义过渡代理 | SwiperContentTransitionProxy 由 Pattern 创建并在过渡过程中传递给 transition 回调 | AC-3.2~3.7 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | duration 默认 400ms，FAST_ANIMATION 使用更短时长 | 代码审查 | `swiper_pattern.cpp` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ArcSwiper 使用弧形过渡效果 | ArcSwiperContentTransitionProxy | 构建验证 | `arc_swiper_pattern.cpp` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 动画与过渡不影响无障碍 | — |
| 大字体 | 否 | 动画参数不涉及字体 | — |
| 深色模式 | 否 | fadeColor 由属性控制 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | customContentTransition @since 12，SwiperAnimationMode.FAST_ANIMATION @since 15，pageFlipMode @since 15 | AC-3.1, AC-4.3, AC-5.1 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper 动画与过渡

  Scenario: 设置动画时长和曲线
    Given 一个 Swiper 组件
    When 调用 .duration(800) 和 .curve(Curve.EASE_IN_OUT)
    Then 翻页动画时长为 800ms，曲线为 EASE_IN_OUT

  Scenario: 设置自定义内容过渡
    Given 一个 Swiper 组件
    When 调用 .customContentTransition({ timeout: 1000, transition: (proxy) => { ... } })
    Then 翻页时 transition 回调接收 SwiperContentTransitionProxy
    And proxy.selectedIndex 返回当前页索引
    And proxy.position 返回过渡位置偏移

  Scenario: 设置边缘效果为 Spring
    Given 一个 Swiper 组件
    When 调用 .effectMode(EdgeEffect.Spring)
    Then 到达边界时弹性回弹效果

  Scenario: 设置翻页模式为 SINGLE
    Given 一个 Swiper 组件
    When 调用 .pageFlipMode(PageFlipMode.SINGLE)
    Then 鼠标滚轮翻页动画结束前不响应新滚轮事件
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（动画与过渡，不含自动播放/指示器/事件/C API 全量）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper duration curve effectMode EdgeEffect animation property storage"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper customContentTransition SwiperContentTransitionProxy SwiperContentAnimatedTransition"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper SwiperAnimationMode PageFlipMode and C API enums"
```

**关键文档：** `design.md`（同目录）
