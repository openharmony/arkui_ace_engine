# 特性规格

> Func-05-03-08-Feat-04 交互与控制器：固化 Swiper disableSwipe/nestedScroll、SwiperController（showNext/showPrevious/changeIndex/finishAnimation/preloadItems/fakeDrag）、maintainVisibleContentPosition 等交互与控制器行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 交互与控制器 (Interaction & Controller) |
| 特性编号 | Func-05-03-08-Feat-04 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 7 起支持（部分属性 @since 12/15/18/20/23） |
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

### US-1: 禁用手势滑动

**作为** 应用开发者,
**我想要** 禁用 Swiper 手势滑动（disableSwipe）,
**以便** 在特定场景下阻止用户手势翻页。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.disableSwipe(value: boolean)` THEN 设置是否禁用手势滑动，默认 false | 正常 |
| AC-1.2 | WHEN disableSwipe 为 true THEN PanGesture 手势滑动被禁用，用户无法通过触摸/鼠标手势翻页 | 正常 |
| AC-1.3 | WHEN disableSwipe 为 false THEN PanGesture 手势滑动正常响应 | 正常 |
| AC-1.4 | WHEN disableSwipe 变更 THEN 触发 PROPERTY_UPDATE_MEASURE | 正常 |

> disableSwipe 存储在 SwiperLayoutProperty：`swiper_layout_property.h`。手势处理：`swiper_pattern.cpp` PanGesture。

### US-2: 配置嵌套滚动

**作为** 应用开发者,
**我想要** 配置 Swiper 嵌套滚动模式（nestedScroll）,
**以便** 控制 Swiper 与父容器的滚动联动。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.nestedScroll(value: SwiperNestedScrollMode)` THEN 设置嵌套滚动模式（@since 12） | 正常 |
| AC-2.2 | WHEN SwiperNestedScrollMode.SELF_ONLY THEN Swiper 仅自身滚动，不与父组件联动 | 正常 |
| AC-2.3 | WHEN SwiperNestedScrollMode.SELF_FIRST THEN Swiper 自身先滚动，到边界后父组件滚动；父到边界后，父有边缘效果则父触发，否则 Swiper 触发 | 正常 |

> SwiperNestedScrollMode 映射：`swiper_model.h`。C API：ArkUI_SwiperNestedScrollMode（SELF_ONLY=0, SELF_FIRST=1）。

### US-3: 使用 SwiperController 翻页

**作为** 应用开发者,
**我想要** 使用 SwiperController 控制翻页（showNext/showPrevious/changeIndex）,
**以便** 通过代码控制 Swiper 翻页行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `SwiperController.showNext()` THEN Swiper 翻到下一页 | 正常 |
| AC-3.2 | WHEN 调用 `SwiperController.showPrevious()` THEN Swiper 翻到上一页 | 正常 |
| AC-3.3 | WHEN 调用 `SwiperController.changeIndex(index: number, useAnimation: boolean)` THEN 切换到指定页，useAnimation 控制是否有动画 | 正常 |
| AC-3.4 | WHEN 调用 `SwiperController.changeIndex(index: number, animationMode: SwiperAnimationMode)` THEN 切换到指定页，指定动画模式（@since 15） | 正常 |
| AC-3.5 | WHEN changeIndex index 超出范围 THEN 不执行翻页 | 异常 |
| AC-3.6 | WHEN SwiperController 绑定到 Swiper THEN controller 通过 Set*Impl 注册回调，Pattern 层执行翻页逻辑 | 正常 |

> SwiperController 实现：`swiper_controller.h:80-104`。showNext/showPrevious/changeIndex 通过 Impl 回调：`swiper_controller.h:68-114`。

### US-4: 使用 SwiperController 结束动画和预加载

**作为** 应用开发者,
**我想要** 使用 SwiperController 结束动画和预加载子项,
**以便** 控制翻页动画和预加载缓存。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `SwiperController.finishAnimation()` THEN 结束当前翻页动画，立即跳到目标页 | 正常 |
| AC-4.2 | WHEN 调用 `SwiperController.preloadItems(indexSet: Set<number>)` THEN 预加载指定索引的子项（@since 18） | 正常 |
| AC-4.3 | WHEN 调用 `SwiperController.swipeTo(index: number, useAnimation: boolean)` THEN 跳转到指定页 | 正常 |

> finishAnimation：`swiper_controller.h:116-126`。preloadItems：`swiper_controller.h:238-243`。swipeTo：`swiper_controller.h:44-49`。

### US-5: 使用 SwiperController 模拟拖拽

**作为** 应用开发者,
**我想要** 使用 SwiperController 模拟拖拽（FakeDrag）,
**以便** 实现自动化测试或动画驱动的翻页效果。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `SwiperController.startFakeDrag()` THEN 开始模拟拖拽（@since 23） | 正常 |
| AC-5.2 | WHEN startFakeDrag 成功 THEN 返回 true，isFakeDragging 为 true | 正常 |
| AC-5.3 | WHEN startFakeDrag 失败（已有手势拖拽进行中）THEN 返回 false | 异常 |
| AC-5.4 | WHEN 调用 `SwiperController.fakeDragBy(offset: number)` THEN 模拟拖拽偏移量（@since 23） | 正常 |
| AC-5.5 | WHEN fakeDragBy 成功 THEN 返回 true，Swiper 按偏移量移动 | 正常 |
| AC-5.6 | WHEN 调用 `SwiperController.stopFakeDrag()` THEN 结束模拟拖拽（@since 23） | 正常 |
| AC-5.7 | WHEN stopFakeDrag 成功 THEN 返回 true，模拟拖拽结束 | 正常 |
| AC-5.8 | WHEN 调用 `SwiperController.isFakeDragging()` THEN 查询是否在模拟拖拽中 | 正常 |

> startFakeDrag/fakeDragBy/stopFakeDrag/isFakeDragging：`swiper_controller.h:257-306`。

### US-6: 配置 maintainVisibleContentPosition

**作为** 应用开发者,
**我想要** 配置 Swiper maintainVisibleContentPosition,
**以便** 在 Swiper 内容变化时保持当前可见内容位置稳定。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `.maintainVisibleContentPosition(value: boolean)` THEN 设置是否保持可见内容位置（@since 20） | 正常 |
| AC-6.2 | WHEN maintainVisibleContentPosition 为 true THEN Swiper 内容变化时保持当前可见内容位置不变 | 正常 |
| AC-6.3 | WHEN maintainVisibleContentPosition 为 false THEN Swiper 内容变化时不保持可见内容位置 | 正常 |

> maintainVisibleContentPosition 映射：`swiper_model.h:242`。C API：NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION。

### US-7: C API 交互与控制器

**作为** NDK 开发者,
**我想要** 通过 C API 控制 Swiper 翻页和交互,
**以便** 在 NDK 应用中使用控制器和交互功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-7.1 | WHEN 使用 NODE_SWIPER_DISABLE_SWIPE 属性 THEN 设置禁用手势滑动 | 正常 |
| AC-7.2 | WHEN 使用 NODE_SWIPER_NESTED_SCROLL 属性 THEN 设置嵌套滚动模式 | 正常 |
| AC-7.3 | WHEN 使用 NODE_SWIPER_SWIPE_TO_INDEX 属性 THEN 跳转到指定页 | 正常 |
| AC-7.4 | WHEN 调用 `OH_ArkUI_Swiper_ShowPrevious(node)` THEN 翻到上一页 | 正常 |
| AC-7.5 | WHEN 调用 `OH_ArkUI_Swiper_ShowNext(node)` THEN 翻到下一页 | 正常 |
| AC-7.6 | WHEN 调用 `OH_ArkUI_Swiper_FinishAnimation(node)` THEN 结束当前动画 | 正常 |
| AC-7.7 | WHEN 调用 `OH_ArkUI_Swiper_StartFakeDrag(node, &isSuccessful)` THEN 开始模拟拖拽 | 正常 |
| AC-7.8 | WHEN 调用 `OH_ArkUI_Swiper_FakeDragBy(node, offset, &isConsumedOffset)` THEN 模拟拖拽偏移 | 正常 |
| AC-7.9 | WHEN 调用 `OH_ArkUI_Swiper_StopFakeDrag(node, &isSuccessful)` THEN 结束模拟拖拽 | 正常 |
| AC-7.10 | WHEN 调用 `OH_ArkUI_Swiper_IsFakeDragging(node, &isFakeDragging)` THEN 查询模拟拖拽状态 | 正常 |
| AC-7.11 | WHEN ArkUI_SwiperNestedScrollMode 枚举使用 THEN 对应 SELF_ONLY(0)/SELF_FIRST(1) | 正常 |

> C API 控制器函数：`native_node.h:14199-14292`。C API 属性枚举：`native_node.h:8080-8213`。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.4 | R-1 | — | 代码审查 + XTS | `swiper_layout_property.h`, `swiper_pattern.cpp` |
| AC-2.1~2.3 | R-2 | — | 代码审查 + XTS | `swiper_model.h` |
| AC-3.1~3.6 | R-3 | — | 代码审查 + XTS | `swiper_controller.h:68-114` |
| AC-4.1~4.3 | R-3 | — | 代码审查 + XTS | `swiper_controller.h:116-243` |
| AC-5.1~5.8 | R-4 | — | 代码审查 + XTS | `swiper_controller.h:257-306` |
| AC-6.1~6.3 | R-5 | — | 代码审查 + XTS | `swiper_model.h:242` |
| AC-7.1~7.11 | R-6 | — | C API 单元测试 | `native_node.h:8080-8213,14199-14292` |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | disableSwipe 默认 false，存储在 SwiperLayoutProperty，为 true 时 PanGesture 手势滑动被禁用 | — | AC-1.1~1.4 |
| R-2 | 行为 | — | SwiperNestedScrollMode 两种：SELF_ONLY(0)=仅自身滚动，SELF_FIRST(1)=自身先滚动后联动父组件 | — | AC-2.1~2.3 |
| R-3 | 行为 | — | SwiperController 通过 Impl 回调机制绑定到 Pattern 层；showNext/showPrevious/changeIndex/finishAnimation/swipeTo/preloadItems 均由 Pattern 执行 | — | AC-3.1~3.6, AC-4.1~4.3 |
| R-4 | 行为 | — | FakeDrag 操作序列：startFakeDrag → fakeDragBy → stopFakeDrag；startFakeDrag 失败时返回 false；isFakeDragging 查询状态 | — | AC-5.1~5.8 |
| R-5 | 行为 | — | maintainVisibleContentPosition 默认 false，为 true 时内容变化保持可见位置 | — | AC-6.1~6.3 |
| R-6 | 行为 | — | C API 交互属性：NODE_SWIPER_DISABLE_SWIPE/NESTED_SCROLL/SWIPE_TO_INDEX；C API 控制器函数：OH_ArkUI_Swiper_ShowPrevious/ShowNext/FinishAnimation/StartFakeDrag/FakeDragBy/StopFakeDrag/IsFakeDragging | — | AC-7.1~7.11 |
| R-7 | 异常 | — | FakeDrag 与手势拖拽互斥：手势拖拽进行中时 startFakeDrag 返回 false；FakeDrag 进行中时手势拖拽被禁止 | — | AC-5.3 |
| R-8 | 边界 | — | changeIndex index 超出范围时不执行翻页 | — | AC-3.5 |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.4 (禁用手势滑动) | XTS + 代码审查 | disableSwipe 手势禁用逻辑 |
| VM-2 | AC-2.1~2.3 (嵌套滚动) | XTS + 代码审查 | SwiperNestedScrollMode 两种模式 |
| VM-3 | AC-3.1~3.6 (控制器翻页) | XTS + 代码审查 | showNext/showPrevious/changeIndex Impl 回调 |
| VM-4 | AC-4.1~4.3 (结束动画和预加载) | XTS + 代码审查 | finishAnimation/preloadItems/swipeTo |
| VM-5 | AC-5.1~5.8 (模拟拖拽) | XTS + 代码审查 | FakeDrag 操作序列和互斥逻辑 |
| VM-6 | AC-6.1~6.3 (保持可见位置) | XTS + 代码审查 | maintainVisibleContentPosition |
| VM-7 | AC-7.1~7.11 (C API 交互与控制器) | C API 单元测试 | NODE_SWIPER_* 交互属性和 OH_ArkUI_Swiper_* 控制器函数 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `disableSwipe(value: boolean)` | Public | 设置禁用手势滑动 | AC-1.1 |
| `nestedScroll(value: SwiperNestedScrollMode)` | Public | 设置嵌套滚动模式 | AC-2.1 |
| `SwiperController.showNext()` | Public | 翻到下一页 | AC-3.1 |
| `SwiperController.showPrevious()` | Public | 翻到上一页 | AC-3.2 |
| `SwiperController.changeIndex(index, useAnimation)` | Public | 切换到指定页 | AC-3.3 |
| `SwiperController.changeIndex(index, animationMode)` | Public | 切换到指定页（动画模式） | AC-3.4 |
| `SwiperController.finishAnimation()` | Public | 结束当前动画 | AC-4.1 |
| `SwiperController.preloadItems(indexSet)` | Public | 预加载子项 | AC-4.2 |
| `SwiperController.startFakeDrag()` | Public | 开始模拟拖拽 | AC-5.1 |
| `SwiperController.fakeDragBy(offset)` | Public | 模拟拖拽偏移 | AC-5.4 |
| `SwiperController.stopFakeDrag()` | Public | 结束模拟拖拽 | AC-5.6 |
| `SwiperController.isFakeDragging()` | Public | 查询模拟拖拽状态 | AC-5.8 |
| `maintainVisibleContentPosition(value: boolean)` | Public | 设置保持可见内容位置 | AC-6.1 |
| `OH_ArkUI_Swiper_ShowPrevious(node)` | System | C API 翻到上一页 | AC-7.4 |
| `OH_ArkUI_Swiper_ShowNext(node)` | System | C API 翻到下一页 | AC-7.5 |
| `OH_ArkUI_Swiper_FinishAnimation(node)` | System | C API 结束动画 | AC-7.6 |
| `OH_ArkUI_Swiper_StartFakeDrag(node, &isSuccessful)` | System | C API 开始模拟拖拽 | AC-7.7 |
| `OH_ArkUI_Swiper_FakeDragBy(node, offset, &isConsumedOffset)` | System | C API 模拟拖拽偏移 | AC-7.8 |
| `OH_ArkUI_Swiper_StopFakeDrag(node, &isSuccessful)` | System | C API 结束模拟拖拽 | AC-7.9 |
| `OH_ArkUI_Swiper_IsFakeDragging(node, &isFakeDragging)` | System | C API 查询模拟拖拽 | AC-7.10 |
| `ArkUI_SwiperNestedScrollMode` | System | C API 嵌套滚动枚举 | AC-7.11 |

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
- **API 版本号策略:** disableSwipe @since 7；nestedScroll @since 12；changeIndex(animationMode) @since 15；preloadItems @since 18；maintainVisibleContentPosition @since 20；FakeDrag @since 23

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| SwiperController Impl 回调 | SwiperController 通过 Set*Impl 注册回调，Pattern 层执行实际翻页逻辑 | AC-3.1~3.6, AC-4.1~4.3 |
| FakeDrag 与手势互斥 | FakeDrag 进行中时手势拖拽被禁止；手势拖拽进行中时 startFakeDrag 返回 false | AC-5.3, R-7 |
| NestableScrollContainer | SwiperPattern 继承 NestableScrollContainer，支持嵌套滚动机制 | AC-2.1~2.3 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | preloadItems 预加载减少懒加载延迟 | 代码审查 | `swiper_controller.h:238-243` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ArcSwiper 支持表冠 FakeDrag | SUPPORT_DIGITAL_CROWN 宏守卫 | 构建验证 | `arc_swiper_pattern.cpp` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 控制器交互不影响无障碍 | — |
| 大字体 | 否 | 控制器不涉及字体 | — |
| 深色模式 | 否 | 无特殊处理 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | nestedScroll @since 12，changeIndex(animationMode) @since 15，preloadItems @since 18，maintainVisibleContentPosition @since 20，FakeDrag @since 23 | AC-2.1, AC-3.4, AC-4.2, AC-6.1, AC-5.1 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper 交互与控制器

  Scenario: 使用 SwiperController 翻页
    Given 一个 Swiper 组件，包含 5 个子项，初始 index=0
    When 调用 controller.showNext()
    Then Swiper 翻到 index=1

  Scenario: 使用 SwiperController changeIndex
    Given 一个 Swiper 组件，包含 5 个子项
    When 调用 controller.changeIndex(3, true)
    Then Swiper 带动画翻到 index=3

  Scenario: 使用 FakeDrag 模拟拖拽
    Given 一个 Swiper 组件
    When 调用 controller.startFakeDrag()
    Then isFakeDragging() 返回 true
    When 调用 controller.fakeDragBy(100)
    Then Swiper 按偏移量 100 移动
    When 调用 controller.stopFakeDrag()
    Then 模拟拖拽结束

  Scenario: 设置嵌套滚动模式
    Given 一个嵌套在滚动容器内的 Swiper
    When 调用 .nestedScroll(SwiperNestedScrollMode.SELF_FIRST)
    Then Swiper 自身先滚动，到边界后父容器滚动
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（交互与控制器，不含自动播放/指示器/动画/事件/C API 全量）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper SwiperController showNext showPrevious changeIndex finishAnimation preloadItems swipeTo"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper FakeDrag startFakeDrag fakeDragBy stopFakeDrag isFakeDragging"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper disableSwipe nestedScroll SwiperNestedScrollMode and C API controller functions"
```

**关键文档：** `design.md`（同目录）
