# 特性规格

> Func-05-03-08-Feat-05 事件回调：固化 Swiper onChange/onSelected/onUnselected/onAnimationStart/onAnimationEnd/onGestureSwipe/onContentDidScroll/onContentWillScroll/onScrollStateChanged 等事件回调行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 事件回调 (Event Callbacks) |
| 特性编号 | Func-05-03-08-Feat-05 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 7 起支持（部分事件 @since 12/15/18/20） |
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

### US-1: 页面切换事件

**作为** 应用开发者,
**我想要** 监听 Swiper 页面切换完成事件（onChange）,
**以便** 在页面切换后执行相关逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.onChange(callback: (index: number) => void)` THEN 注册页面切换完成回调 | 正常 |
| AC-1.2 | WHEN 页面切换动画完成 THEN onChange 回调触发，参数为当前页 index | 正常 |
| AC-1.3 | WHEN 连续快速滑动 THEN 每次切换完成触发一次 onChange | 正常 |
| AC-1.4 | WHEN onChange 设置多个回调 THEN 所有回调依次触发 | 正常 |

> onChange 事件存储在 SwiperEventHub：`swiper_event_hub.h:44-52`。触发时机：`swiper_pattern.cpp` 动画完成时。

### US-2: 页面选中与取消选中事件

**作为** 应用开发者,
**我想要** 监听 Swiper 页面选中与取消选中事件（onSelected/onUnselected）,
**以便** 在页面选中/取消选中时执行相关逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.onSelected(callback: (index: number) => void)` THEN 注册页面选中回调（@since 18） | 正常 |
| AC-2.2 | WHEN 页面被选中 THEN onSelected 回调触发，参数为选中页 index | 正常 |
| AC-2.3 | WHEN 调用 `.onUnselected(callback: (index: number) => void)` THEN 注册页面取消选中回调（@since 18） | 正常 |
| AC-2.4 | WHEN 页面被取消选中 THEN onUnselected 回调触发，参数为取消选中的页 index | 正常 |
| AC-2.5 | WHEN 页面从 index=0 切换到 index=1 THEN onSelected(1) 和 onUnselected(0) 同时触发 | 正常 |

> onSelected/onUnselected 事件存储在 SwiperEventHub：`swiper_event_hub.h:84-92`。

### US-3: 动画开始与结束事件

**作为** 应用开发者,
**我想要** 监听 Swiper 动画开始与结束事件（onAnimationStart/onAnimationEnd）,
**以便** 在动画开始/结束时执行相关逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.onAnimationStart(callback: OnSwiperAnimationStartCallback)` THEN 注册动画开始回调 | 正常 |
| AC-3.2 | WHEN 翻页动画开始 THEN onAnimationStart 回调触发，参数为 (index, targetIndex, extraInfo) | 正常 |
| AC-3.3 | WHEN SwiperAnimationEventInfo.currentOffset 获取 THEN 返回当前偏移量 | 正常 |
| AC-3.4 | WHEN SwiperAnimationEventInfo.targetOffset 获取 THEN 返回目标偏移量 | 正常 |
| AC-3.5 | WHEN SwiperAnimationEventInfo.velocity 获取 THEN 返回动画速度 | 正常 |
| AC-3.6 | WHEN 调用 `.onAnimationEnd(callback: OnSwiperAnimationEndCallback)` THEN 注册动画结束回调 | 正常 |
| AC-3.7 | WHEN 翻页动画结束 THEN onAnimationEnd 回调触发，参数为 (index, extraInfo) | 正常 |
| AC-3.8 | WHEN disableTransitionAnimation 为 true THEN onAnimationStart/onAnimationEnd 不触发 | 边界 |

> onAnimationStart/onAnimationEnd 事件存储在 SwiperEventHub：`swiper_event_hub.h:69-77`。SwiperAnimationEventInfo 类型定义。

### US-4: 手势滑动事件

**作为** 应用开发者,
**我想要** 监听 Swiper 手势滑动事件（onGestureSwipe）,
**以便** 在手势滑动过程中获取实时偏移量。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.onGestureSwipe(callback: OnSwiperGestureSwipeCallback)` THEN 注册手势滑动回调 | 正常 |
| AC-4.2 | WHEN 用户手势滑动过程中 THEN onGestureSwipe 回调触发，参数为 (index, offset) | 正常 |
| AC-4.3 | WHEN disableSwipe 为 true THEN onGestureSwipe 不触发 | 边界 |

> onGestureSwipe 事件存储在 SwiperEventHub：`swiper_event_hub.h:79-82`。

### US-5: 内容滚动事件

**作为** 应用开发者,
**我想要** 监听 Swiper 内容滚动事件（onContentDidScroll/onContentWillScroll）,
**以便** 在内容滚动过程中获取实时位置信息。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `.onContentDidScroll(callback: ContentDidScrollCallback)` THEN 注册内容滚动完成回调（@since 12） | 正常 |
| AC-5.2 | WHEN 内容滚动过程中 THEN onContentDidScroll 回调触发，参数为 (index, targetIndex, extraInfo) | 正常 |
| AC-5.3 | WHEN 调用 `.onContentWillScroll(callback: ContentWillScrollCallback)` THEN 注册内容即将滚动回调（@since 15） | 正常 |
| AC-5.4 | WHEN 内容即将滚动 THEN onContentWillScroll 回调触发，参数为 (index, targetIndex, extraInfo) | 正常 |
| AC-5.5 | WHEN onContentWillScroll 回调返回 SwiperContentWillScrollResult THEN 可控制滚动是否允许 | 边界 |

> onContentDidScroll 映射：`swiper_model.h`。onContentWillScroll @since 15。

### US-6: 滚动状态变化事件

**作为** 应用开发者,
**我想要** 监听 Swiper 滚动状态变化事件（onScrollStateChanged）,
**以便** 在滚动状态变化时执行相关逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `.onScrollStateChanged(callback)` THEN 注册滚动状态变化回调（@since 20） | 正常 |
| AC-6.2 | WHEN 滚动状态从 IDLE 变为 SCROLLING THEN onScrollStateChanged 回调触发 | 正常 |
| AC-6.3 | WHEN 滚动状态从 SCROLLING 变为 IDLE THEN onScrollStateChanged 回调触发 | 正常 |

> onScrollStateChanged 事件存储在 SwiperEventHub：`swiper_event_hub.h:94-97`。

### US-7: C API 事件回调

**作为** NDK 开发者,
**我想要** 通过 C API 监听 Swiper 事件回调,
**以便** 在 NDK 应用中使用 Swiper 事件功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-7.1 | WHEN 注册 NODE_SWIPER_EVENT_ON_CHANGE 事件 THEN 页面切换完成时回调触发 | 正常 |
| AC-7.2 | WHEN 注册 NODE_SWIPER_EVENT_ON_ANIMATION_START 事件 THEN 动画开始时回调触发 | 正常 |
| AC-7.3 | WHEN 注册 NODE_SWIPER_EVENT_ON_ANIMATION_END 事件 THEN 动画结束时回调触发 | 正常 |
| AC-7.4 | WHEN 注册 NODE_SWIPER_EVENT_ON_GESTURE_SWIPE 事件 THEN 手势滑动时回调触发 | 正常 |
| AC-7.5 | WHEN 注册 NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL 事件 THEN 内容滚动时回调触发 | 正常 |
| AC-7.6 | WHEN 注册 NODE_SWIPER_EVENT_ON_SELECTED 事件 THEN 页面选中时回调触发 | 正常 |
| AC-7.7 | WHEN 注册 NODE_SWIPER_EVENT_ON_UNSELECTED 事件 THEN 页面取消选中时回调触发 | 正常 |
| AC-7.8 | WHEN 注册 NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL 事件 THEN 内容即将滚动时回调触发 | 正常 |
| AC-7.9 | WHEN 注册 NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED 事件 THEN 滚动状态变化时回调触发 | 正常 |

> C API 事件枚举：`native_node.h:11283-11399`。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.4 | R-1 | — | 代码审查 + XTS | `swiper_event_hub.h:44-52` |
| AC-2.1~2.5 | R-2 | — | 代码审查 + XTS | `swiper_event_hub.h:84-92` |
| AC-3.1~3.8 | R-3 | — | 代码审查 + XTS | `swiper_event_hub.h:69-77` |
| AC-4.1~4.3 | R-4 | — | 代码审查 + XTS | `swiper_event_hub.h:79-82` |
| AC-5.1~5.5 | R-5 | — | 代码审查 + XTS | `swiper_model.h` |
| AC-6.1~6.3 | R-6 | — | 代码审查 + XTS | `swiper_event_hub.h:94-97` |
| AC-7.1~7.9 | R-7 | — | C API 单元测试 | `native_node.h:11283-11399` |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | onChange 在页面切换动画完成后触发，参数为当前页 index；支持注册多个回调，依次触发 | — | AC-1.1~1.4 |
| R-2 | 行为 | — | onSelected/onUnselected @since 18，页面选中/取消选中时触发，参数为 index；切换时 onSelected(新页) 和 onUnselected(旧页) 同时触发 | — | AC-2.1~2.5 |
| R-3 | 行为 | — | onAnimationStart 参数 (index, targetIndex, extraInfo)；onAnimationEnd 参数 (index, extraInfo)；extraInfo 含 currentOffset/targetOffset/velocity；disableTransitionAnimation 为 true 时不触发 | — | AC-3.1~3.8 |
| R-4 | 行为 | — | onGestureSwipe 参数 (index, offset)，手势滑动过程中触发；disableSwipe 为 true 时不触发 | — | AC-4.1~4.3 |
| R-5 | 行为 | — | onContentDidScroll @since 12 参数 (index, targetIndex, extraInfo)；onContentWillScroll @since 15 参数 (index, targetIndex, extraInfo)，返回 SwiperContentWillScrollResult 可控制滚动 | — | AC-5.1~5.5 |
| R-6 | 行为 | — | onScrollStateChanged @since 20，滚动状态变化时触发（IDLE ↔ SCROLLING） | — | AC-6.1~6.3 |
| R-7 | 行为 | — | C API 事件枚举：NODE_SWIPER_EVENT_ON_CHANGE/ON_ANIMATION_START/ON_ANIMATION_END/ON_GESTURE_SWIPE/ON_CONTENT_DID_SCROLL/ON_SELECTED/ON_UNSELECTED/ON_CONTENT_WILL_SCROLL/ON_SCROLL_STATE_CHANGED | — | AC-7.1~7.9 |
| R-8 | 边界 | — | 事件回调均在 UI 线程触发，与属性设置和动画驱动在同一线程 | — | — |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.4 (onChange) | XTS + 代码审查 | onChange 触发时机和多回调机制 |
| VM-2 | AC-2.1~2.5 (onSelected/onUnselected) | XTS + 代码审查 | 选中/取消选中触发时序 |
| VM-3 | AC-3.1~3.8 (onAnimationStart/onAnimationEnd) | XTS + 代码审查 | 动画事件参数和 SwiperAnimationEventInfo |
| VM-4 | AC-4.1~4.3 (onGestureSwipe) | XTS + 代码审查 | 手势滑动事件和 disableSwipe 互斥 |
| VM-5 | AC-5.1~5.5 (onContentDidScroll/onContentWillScroll) | XTS + 代码审查 | 内容滚动事件和 SwiperContentWillScrollResult |
| VM-6 | AC-6.1~6.3 (onScrollStateChanged) | XTS + 代码审查 | 滚动状态变化事件 |
| VM-7 | AC-7.1~7.9 (C API 事件) | C API 单元测试 | NODE_SWIPER_EVENT_* 事件注册和回调 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `onChange(callback: (index: number) => void)` | Public | 页面切换完成回调 | AC-1.1 |
| `onSelected(callback: (index: number) => void)` | Public | 页面选中回调 | AC-2.1 |
| `onUnselected(callback: (index: number) => void)` | Public | 页面取消选中回调 | AC-2.3 |
| `onAnimationStart(callback: OnSwiperAnimationStartCallback)` | Public | 动画开始回调 | AC-3.1 |
| `onAnimationEnd(callback: OnSwiperAnimationEndCallback)` | Public | 动画结束回调 | AC-3.6 |
| `onGestureSwipe(callback: OnSwiperGestureSwipeCallback)` | Public | 手势滑动回调 | AC-4.1 |
| `onContentDidScroll(callback: ContentDidScrollCallback)` | Public | 内容滚动完成回调 | AC-5.1 |
| `onContentWillScroll(callback: ContentWillScrollCallback)` | Public | 内容即将滚动回调 | AC-5.3 |
| `onScrollStateChanged(callback)` | Public | 滚动状态变化回调 | AC-6.1 |
| `SwiperAnimationEventInfo` | Public | 动画事件信息类型 | AC-3.3~3.5 |
| `SwiperContentWillScrollResult` | Public | 内容滚动控制结果类型 | AC-5.5 |

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
- **API 版本号策略:** onChange @since 7；onAnimationStart/onAnimationEnd/onGestureSwipe @since 7；onContentDidScroll @since 12；onContentWillScroll @since 15；onSelected/onUnselected @since 18；onScrollStateChanged @since 20

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| 事件存储在 EventHub | 所有事件回调存储在 SwiperEventHub，由 Pattern 在动画/手势回调中触发 | AC-1~6 |
| 事件触发线程 | 所有事件回调在 UI 线程触发 | R-8 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | 事件回调不影响 Swiper 主轴布局和动画性能 | 代码审查 | `swiper_pattern.cpp` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ArcSwiper 增加 ArcDotIndicator 选中事件 | SUPPORT_DIGITAL_CROWN 宏守卫 | 构建验证 | `arc_swiper_pattern.cpp` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 是 | 事件回调可触发无障碍通知 | onChange 触发时通知无障碍 |
| 大字体 | 否 | 事件回调不涉及字体 | — |
| 深色模式 | 否 | 无特殊处理 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | onContentDidScroll @since 12，onContentWillScroll @since 15，onSelected/onUnselected @since 18，onScrollStateChanged @since 20 | AC-5.1, AC-5.3, AC-2.1, AC-2.3, AC-6.1 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper 事件回调

  Scenario: onChange 页面切换完成
    Given 一个 Swiper 组件，包含 5 个子项
    When 用户滑动到第 3 页
    Then onChange 回调触发，参数 index=2

  Scenario: onAnimationStart/onAnimationEnd
    Given 一个 Swiper 组件，注册了 onAnimationStart 和 onAnimationEnd
    When 翻页动画开始
    Then onAnimationStart 回调触发，参数含 index、targetIndex、extraInfo
    When 翻页动画结束
    Then onAnimationEnd 回调触发，参数含 index、extraInfo

  Scenario: onSelected/onUnselected
    Given 一个 Swiper 组件，注册了 onSelected 和 onUnselected
    When 页面从 index=0 切换到 index=1
    Then onSelected(1) 和 onUnselected(0) 同时触发

  Scenario: onContentWillScroll 控制滚动
    Given 一个 Swiper 组件，注册了 onContentWillScroll
    When 内容即将滚动
    Then onContentWillScroll 回调触发
    And 回调返回 SwiperContentWillScrollResult 控制滚动是否允许
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 茄围边界明确（事件回调，不含自动播放/指示器/动画属性/控制器/C API 全量）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper onChange onAnimationStart onAnimationEnd onGestureSwipe event hub callbacks"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper onContentDidScroll onContentWillScroll onSelected onUnselected onScrollStateChanged events"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper NODE_SWIPER_EVENT C API event registration callbacks"
```

**关键文档：** `design.md`（同目录）
