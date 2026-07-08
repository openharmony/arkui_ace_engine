# 特性规格

> Func-05-03-08-Feat-06 C API 全量规格：固化 Swiper 所有 NODE_SWIPER_* 属性、NODE_SWIPER_EVENT_* 事件、OH_ArkUI_Swiper_* 控制器函数、OH_ArkUI_SwiperIndicator_*/OH_ArkUI_SwiperDigitIndicator_*/OH_ArkUI_SwiperArrowStyle_* 对象函数、ArkUI_SwiperArrow/ArkUI_SwiperNestedScrollMode/ArkUI_PageFlipMode/ArkUI_SwiperIndicatorType/ArkUI_SwiperAnimationMode 枚举的完整 C API 行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | C API 全量规格 (C API Full Specification) |
| 特性编号 | Func-05-03-08-Feat-06 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 12 起支持（C API） |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/08-swiper/design.md` | Baselined |
| Feat-01 Spec | `specs/05-ui-components/03-scroll-container-components/08-swiper/Feat-01-swiper-creation-layout-spec.md` | Baselined |
| Feat-02 Spec | `specs/05-ui-components/03-scroll-container-components/08-swiper/Feat-02-swiper-autoplay-indicator-spec.md` | Baselined |
| Feat-03 Spec | `specs/05-ui-components/03-scroll-container-components/08-swiper/Feat-03-swiper-animation-transition-spec.md` | Baselined |
| Feat-04 Spec | `specs/05-ui-components/03-scroll-container-components/08-swiper/Feat-04-swiper-interaction-controller-spec.md` | Baselined |
| Feat-05 Spec | `specs/05-ui-components/03-scroll-container-components/08-swiper/Feat-05-swiper-events-spec.md` | Baselined |

---

## 用户故事

### US-1: C API Swiper 属性全量

**作为** NDK 开发者,
**我想要** 通过 C API 设置 Swiper 所有属性（NODE_SWIPER_*）,
**以便** 在 NDK 应用中使用 Swiper 完整属性功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 使用 NODE_SWIPER_LOOP 属性 THEN 设置循环滑动（bool） | 正常 |
| AC-1.2 | WHEN 使用 NODE_SWIPER_AUTO_PLAY 属性 THEN 设置自动播放（bool） | 正常 |
| AC-1.3 | WHEN 使用 NODE_SWIPER_SHOW_INDICATOR 属性 THEN 设置显示指示器（bool） | 正常 |
| AC-1.4 | WHEN 使用 NODE_SWIPER_INTERVAL 属性 THEN 设置自动播放间隔（int32_t） | 正常 |
| AC-1.5 | WHEN 使用 NODE_SWIPER_VERTICAL 属性 THEN 设置纵向滑动（bool） | 正常 |
| AC-1.6 | WHEN 使用 NODE_SWIPER_DURATION 属性 THEN 设置动画时长（int32_t） | 正常 |
| AC-1.7 | WHEN 使用 NODE_SWIPER_CURVE 属性 THEN 设置动画曲线（int32_t ArkUI_AnimationCurve） | 正常 |
| AC-1.8 | WHEN 使用 NODE_SWIPER_ITEM_SPACE 属性 THEN 设置子项间距（Dimension） | 正常 |
| AC-1.9 | WHEN 使用 NODE_SWIPER_INDEX 属性 THEN 设置初始索引，含可选 animationMode 参数 | 正常 |
| AC-1.10 | WHEN 使用 NODE_SWIPER_DISPLAY_COUNT 属性 THEN 设置同屏显示数量 | 正常 |
| AC-1.11 | WHEN 使用 NODE_SWIPER_DISABLE_SWIPE 属性 THEN 设置禁用手势滑动（bool） | 正常 |
| AC-1.12 | WHEN 使用 NODE_SWIPER_SHOW_DISPLAY_ARROW 属性 THEN 设置导航箭头（ArkUI_SwiperArrow 或 ArkUI_SwiperArrowStyle） | 正常 |
| AC-1.13 | WHEN 使用 NODE_SWIPER_EDGE_EFFECT_MODE 属性 THEN 设置边缘效果（int32_t EdgeEffect） | 正常 |
| AC-1.14 | WHEN 使用 NODE_SWIPER_NODE_ADAPTER 属性 THEN 设置 NodeAdapter | 正常 |
| AC-1.15 | WHEN 使用 NODE_SWIPER_CACHED_COUNT 属性 THEN 设置预加载缓存数量 | 正常 |
| AC-1.16 | WHEN 使用 NODE_SWIPER_PREV_MARGIN 属性 THEN 设置前预览边距（Dimension + ignoreBlank） | 正常 |
| AC-1.17 | WHEN 使用 NODE_SWIPER_NEXT_MARGIN 属性 THEN 设置后预览边距（Dimension + ignoreBlank） | 正常 |
| AC-1.18 | WHEN 使用 NODE_SWIPER_INDICATOR 属性 THEN 设置指示器类型和样式（ArkUI_SwiperIndicatorType + ArkUI_SwiperIndicator/DigitIndicator） | 正常 |
| AC-1.19 | WHEN 使用 NODE_SWIPER_NESTED_SCROLL 属性 THEN 设置嵌套滚动模式（ArkUI_SwiperNestedScrollMode） | 正常 |
| AC-1.20 | WHEN 使用 NODE_SWIPER_SWIPE_TO_INDEX 属性 THEN 跳转到指定页（index + optional animationMode） | 正常 |
| AC-1.21 | WHEN 使用 NODE_SWIPER_INDICATOR_INTERACTIVE 属性 THEN 设置指示器可交互（bool） | 正常 |
| AC-1.22 | WHEN 使用 NODE_SWIPER_PAGE_FLIP_MODE 属性 THEN 设置翻页模式（ArkUI_PageFlipMode） | 正常 |
| AC-1.23 | WHEN 使用 NODE_SWIPER_AUTO_FILL 属性 THEN 设置自动填充（displayCount + overflow） | 正常 |
| AC-1.24 | WHEN 使用 NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION 属性 THEN 设置保持可见内容位置（bool） | 正常 |
| AC-1.25 | WHEN 使用 NODE_SWIPER_ITEMFILLPOLICY 属性 THEN 设置项目填充策略 | 正常 |

> NODE_SWIPER_* 属性枚举：`native_node.h:7924-8301`。实现层：`node_swiper_modifier.cpp`。参数传递通过 ArkUI_AttributeItem。

### US-2: C API Swiper 事件全量

**作为** NDK 开发者,
**我想要** 通过 C API 注册 Swiper 所有事件（NODE_SWIPER_EVENT_*）,
**以便** 在 NDK 应用中监听 Swiper 事件回调。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 注册 NODE_SWIPER_EVENT_ON_CHANGE 事件 THEN 页面切换完成时回调触发，参数含 index | 正常 |
| AC-2.2 | WHEN 注册 NODE_SWIPER_EVENT_ON_ANIMATION_START 事件 THEN 动画开始时回调触发，参数含 index/targetIndex/extraInfo | 正常 |
| AC-2.3 | WHEN 注册 NODE_SWIPER_EVENT_ON_ANIMATION_END 事件 THEN 动画结束时回调触发，参数含 index/extraInfo | 正常 |
| AC-2.4 | WHEN 注册 NODE_SWIPER_EVENT_ON_GESTURE_SWIPE 事件 THEN 手势滑动时回调触发，参数含 index/offset | 正常 |
| AC-2.5 | WHEN 注册 NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL 事件 THEN 内容滚动时回调触发 | 正常 |
| AC-2.6 | WHEN 注册 NODE_SWIPER_EVENT_ON_SELECTED 事件 THEN 页面选中时回调触发，参数含 index | 正常 |
| AC-2.7 | WHEN 注册 NODE_SWIPER_EVENT_ON_UNSELECTED 事件 THEN 页面取消选中时回调触发，参数含 index | 正常 |
| AC-2.8 | WHEN 注册 NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL 事件 THEN 内容即将滚动时回调触发 | 正常 |
| AC-2.9 | WHEN 注册 NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED 事件 THEN 滚动状态变化时回调触发 | 正常 |

> NODE_SWIPER_EVENT_* 事件枚举：`native_node.h:11283-11399`。

### US-3: C API Swiper 控制器函数全量

**作为** NDK 开发者,
**我想要** 通过 C API 调用 Swiper 控制器函数（OH_ArkUI_Swiper_*）,
**以便** 在 NDK 应用中控制 Swiper 翻页和交互。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `OH_ArkUI_Swiper_FinishAnimation(node)` THEN 结束当前动画，返回 ARKUI_ERROR_CODE_NO_ERROR 或错误码 | 正常 |
| AC-3.2 | WHEN 调用 `OH_ArkUI_Swiper_StartFakeDrag(node, &isSuccessful)` THEN 开始模拟拖拽 | 正常 |
| AC-3.3 | WHEN 调用 `OH_ArkUI_Swiper_FakeDragBy(node, offset, &isConsumedOffset)` THEN 模拟拖拽偏移 | 正常 |
| AC-3.4 | WHEN 调用 `OH_ArkUI_Swiper_StopFakeDrag(node, &isSuccessful)` THEN 结束模拟拖拽 | 正常 |
| AC-3.5 | WHEN 调用 `OH_ArkUI_Swiper_IsFakeDragging(node, &isFakeDragging)` THEN 查询模拟拖拽状态 | 正常 |
| AC-3.6 | WHEN 调用 `OH_ArkUI_Swiper_ShowPrevious(node)` THEN 翻到上一页 | 正常 |
| AC-3.7 | WHEN 调用 `OH_ArkUI_Swiper_ShowNext(node)` THEN 翻到下一页 | 正常 |
| AC-3.8 | WHEN node 为无效指针 THEN OH_ArkUI_Swiper_* 返回 ARKUI_ERROR_CODE_PARAM_INVALID | 异常 |

> C API 控制器函数：`native_node.h:14199-14292`。返回值类型：int32_t（ARKUI_ERROR_CODE_*）。

### US-4: C API 指示器对象函数全量

**作为** NDK 开发者,
**我想要** 通过 C API 使用 Swiper 指示器对象（OH_ArkUI_SwiperIndicator_*）,
**以便** 在 NDK 应用中配置指示器样式。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `OH_ArkUI_SwiperIndicator_Create(ARKUI_SWIPER_INDICATOR_TYPE_DOT)` THEN 创建 DOT 类型指示器对象 | 正常 |
| AC-4.2 | WHEN 调用 `OH_ArkUI_SwiperIndicator_Create(ARKUI_SWIPER_INDICATOR_TYPE_DIGIT)` THEN 创建 DIGIT 类型指示器对象 | 正常 |
| AC-4.3 | WHEN 调用 `OH_ArkUI_SwiperIndicator_Dispose(indicator)` THEN 释放指示器对象 | 正常 |
| AC-4.4 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetStartPosition(indicator, value) THEN 设置起始位置偏移 | 正常 |
| AC-4.5 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetTopPosition(indicator, value) THEN 设置顶部位置偏移 | 正常 |
| AC-4.6 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetEndPosition(indicator, value) THEN 设置结束位置偏移 | 正常 |
| AC-4.7 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetBottomPosition(indicator, value) THEN 设置底部位置偏移 | 正常 |
| AC-4.8 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetItemWidth(indicator, value) THEN 设置圆点未选中宽度 | 正常 |
| AC-4.9 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetItemHeight(indicator, value) THEN 设置圆点未选中高度 | 正常 |
| AC-4.10 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetSelectedItemWidth(indicator, value) THEN 设置圆点选中宽度 | 正常 |
| AC-4.11 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetSelectedItemHeight(indicator, value) THEN 设置圆点选中高度 | 正常 |
| AC-4.12 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetMask(indicator, mask) THEN 设置蒙版 | 正常 |
| AC-4.13 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetColor(indicator, color) THEN 设置未选中颜色 | 正常 |
| AC-4.14 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetSelectedColor(indicator, selectedColor) THEN 设置选中颜色 | 正常 |
| AC-4.15 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetMaxDisplayCount(indicator, maxDisplayCount) THEN 设置最大显示数量 | 正常 |
| AC-4.16 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom(indicator, ignoreSize) THEN 设置忽略底部尺寸 | 正常 |
| AC-4.17 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetSpace(indicator, space) THEN 设置指示器间距 | 正常 |
| AC-4.18 | WHEN 调用 OH_ArkUI_SwiperIndicator_Get* THEN 返回对应属性值 | 正常 |
| AC-4.19 | WHEN indicator 为 NULL THEN OH_ArkUI_SwiperIndicator_* 不崩溃，返回默认值 | 异常 |

> OH_ArkUI_SwiperIndicator_* 函数：`native_type.h:2368-2632`。

### US-5: C API 数字指示器对象函数全量

**作为** NDK 开发者,
**我想要** 通过 C API 使用 Swiper 数字指示器对象（OH_ArkUI_SwiperDigitIndicator_*）,
**以便** 在 NDK 应用中配置数字指示器样式。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `OH_ArkUI_SwiperDigitIndicator_Create()` THEN 创建数字指示器对象（@since 19） | 正常 |
| AC-5.2 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetStartPosition(indicator, value) THEN 设置起始位置偏移 | 正常 |
| AC-5.3 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetTopPosition(indicator, value) THEN 设置顶部位置偏移 | 正常 |
| AC-5.4 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetEndPosition(indicator, value) THEN 设置结束位置偏移 | 正常 |
| AC-5.5 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetBottomPosition(indicator, value) THEN 设置底部位置偏移 | 正常 |
| AC-5.6 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetFontColor(indicator, color) THEN 设置字体颜色 | 正常 |
| AC-5.7 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetSelectedFontColor(indicator, selectedColor) THEN 设置选中字体颜色 | 正常 |
| AC-5.8 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetFontSize(indicator, size) THEN 设置字体大小 | 正常 |
| AC-5.9 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetSelectedFontSize(indicator, size) THEN 设置选中字体大小 | 正常 |
| AC-5.10 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetFontWeight(indicator, fontWeight) THEN 设置字体粗细 | 正常 |
| AC-5.11 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetSelectedFontWeight(indicator, fontWeight) THEN 设置选中字体粗细 | 正常 |
| AC-5.12 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom(indicator, ignoreSize) THEN 设置忽略底部尺寸 | 正常 |
| AC-5.13 | WHEN 调用 `OH_ArkUI_SwiperDigitIndicator_Destroy(indicator)` THEN 释放数字指示器对象 | 正常 |
| AC-5.14 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_Get* THEN 返回对应属性值 | 正常 |

> OH_ArkUI_SwiperDigitIndicator_* 函数：`native_type.h:2640-2848`。

### US-6: C API 箭头样式对象函数全量

**作为** NDK 开发者,
**我想要** 通过 C API 使用 Swiper 箭头样式对象（OH_ArkUI_SwiperArrowStyle_*）,
**以便** 在 NDK 应用中配置导航箭头样式。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `OH_ArkUI_SwiperArrowStyle_Create()` THEN 创建箭头样式对象 | 正常 |
| AC-6.2 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetShowBackground(arrowStyle, showBackground) THEN 设置背景显示标志 | 正常 |
| AC-6.3 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetShowSidebarMiddle(arrowStyle, showSidebarMiddle) THEN 设置居中显示标志 | 正常 |
| AC-6.4 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetBackgroundSize(arrowStyle, backgroundSize) THEN 设置背景尺寸 | 正常 |
| AC-6.5 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetBackgroundColor(arrowStyle, backgroundColor) THEN 设置背景颜色 | 正常 |
| AC-6.6 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetArrowSize(arrowStyle, arrowSize) THEN 设置箭头尺寸 | 正常 |
| AC-6.7 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_SetArrowColor(arrowStyle, arrowColor) THEN 设置箭头颜色 | 正常 |
| AC-6.8 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_Get* THEN 返回对应属性值 | 正常 |
| AC-6.9 | WHEN 调用 `OH_ArkUI_SwiperArrowStyle_Destroy(arrowStyle)` THEN 释放箭头样式对象 | 正常 |

> OH_ArkUI_SwiperArrowStyle_* 函数：`native_type.h:2856-2986`。

### US-7: C API 枚举全量

**作为** NDK 开发者,
**我想要** 通过 C API 使用 Swiper 相关枚举,
**以便** 在 NDK 应用中使用正确的枚举值。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-7.1 | WHEN ArkUI_SwiperArrow 使用 THEN HIDE(0)/SHOW(1)/SHOW_ON_HOVER(2) | 正常 |
| AC-7.2 | WHEN ArkUI_SwiperNestedScrollMode 使用 THEN SELF_ONLY(0)/SELF_FIRST(1) | 正常 |
| AC-7.3 | WHEN ArkUI_PageFlipMode 使用 THEN CONTINUOUS(0)/SINGLE(1) | 正常 |
| AC-7.4 | WHEN ArkUI_SwiperIndicatorType 使用 THEN DOT(0)/DIGIT(1) | 正常 |
| AC-7.5 | WHEN ArkUI_SwiperAnimationMode 使用 THEN NO_ANIMATION(0)/DEFAULT_ANIMATION(1)/FAST_ANIMATION(2) | 正常 |

> C API 枚举定义：ArkUI_SwiperArrow: `native_type.h:663-670`；ArkUI_SwiperNestedScrollMode: `native_type.h:677-684`；ArkUI_PageFlipMode: `native_type.h:691-697`；ArkUI_SwiperIndicatorType: `native_type.h:1306-1311`；ArkUI_SwiperAnimationMode: `native_node.h:8035`。

### US-8: C API 实现文件映射

**作为** 代码审查者,
**我想要** 确认 C API 实现文件的完整映射,
**以便** 确保所有 C API 属性和事件在 node_swiper_modifier.cpp 中有对应实现。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-8.1 | WHEN 检查 node_swiper_modifier.cpp THEN 所有 25 个 NODE_SWIPER_* 属性有对应 SetAttr/ResetAttr 实现 | 正常 |
| AC-8.2 | WHEN 检查 node_swiper_modifier.cpp THEN 所有 9 个 NODE_SWIPER_EVENT_* 事件有对应 OnEvent 注册实现 | 正常 |
| AC-8.3 | WHEN 检查 swiper_option.cpp THEN OH_ArkUI_Swiper_* 控制器函数有对应实现 | 正常 |

> node_swiper_modifier.cpp：`frameworks/core/interfaces/native/node/node_swiper_modifier.cpp`。swiper_option.cpp（如果存在）：C API 控制器函数实现。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.25 | R-1 | — | C API 单元测试 | `native_node.h:7924-8301` |
| AC-2.1~2.9 | R-2 | — | C API 单元测试 | `native_node.h:11283-11399` |
| AC-3.1~3.8 | R-3 | — | C API 单元测试 | `native_node.h:14199-14292` |
| AC-4.1~4.19 | R-4 | — | C API 单元测试 | `native_type.h:2368-2632` |
| AC-5.1~5.14 | R-5 | — | C API 单元测试 | `native_type.h:2640-2848` |
| AC-6.1~6.9 | R-6 | — | C API 单元测试 | `native_type.h:2856-2986` |
| AC-7.1~7.5 | R-7 | — | C API 单元测试 | `native_type.h:663-697,1306-1311` |
| AC-8.1~8.3 | R-8 | — | 代码审查 | `node_swiper_modifier.cpp` |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | C API 属性通过 ArkUI_AttributeItem 传递参数；NODE_SWIPER_* 属性调用 node_swiper_modifier.cpp SetAttr/ResetAttr，最终调用 SwiperModelNG 静态方法 | — | AC-1.1~1.25 |
| R-2 | 行为 | — | C API 事件通过 ArkUI_NodeEventType 注册回调；NODE_SWIPER_EVENT_* 事件在 node_swiper_modifier.cpp OnEvent 中绑定，回调触发时通过 ArkUI_NodeEvent 获取参数 | — | AC-2.1~2.9 |
| R-3 | 行为 | — | C API 控制器函数 OH_ArkUI_Swiper_* 返回 int32_t 错误码；node 为无效指针时返回 ARKUI_ERROR_CODE_PARAM_INVALID | — | AC-3.1~3.8 |
| R-4 | 行为 | — | OH_ArkUI_SwiperIndicator 对象管理 DOT/DIGIT 类型指示器样式属性；需手动 Create/Dispose | — | AC-4.1~4.19 |
| R-5 | 行为 | — | OH_ArkUI_SwiperDigitIndicator 对象管理数字指示器样式属性（@since 19）；需手动 Create/Destroy | — | AC-5.1~5.14 |
| R-6 | 行为 | — | OH_ArkUI_SwiperArrowStyle 对象管理箭头样式属性；需手动 Create/Destroy | — | AC-6.1~6.9 |
| R-7 | 行为 | — | C API 枚举：ArkUI_SwiperArrow(HIDE/SHOW/SHOW_ON_HOVER)、ArkUI_SwiperNestedScrollMode(SELF_ONLY/SELF_FIRST)、ArkUI_PageFlipMode(CONTINUOUS/SINGLE)、ArkUI_SwiperIndicatorType(DOT/DIGIT)、ArkUI_SwiperAnimationMode(NO_ANIMATION/DEFAULT_ANIMATION/FAST_ANIMATION) | — | AC-7.1~7.5 |
| R-8 | 行为 | — | node_swiper_modifier.cpp 必须实现所有 NODE_SWIPER_* 属性和 NODE_SWIPER_EVENT_* 事件的 SetAttr/ResetAttr/OnEvent | — | AC-8.1~8.3 |
| R-9 | 边界 | — | C API 对象函数传入 NULL 指针时不崩溃，返回默认值或错误码 | — | AC-3.8, AC-4.19 |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.25 (属性全量) | C API 单元测试 | 25 个 NODE_SWIPER_* 属性设置和重置 |
| VM-2 | AC-2.1~2.9 (事件全量) | C API 单元测试 | 9 个 NODE_SWIPER_EVENT_* 事件注册和回调 |
| VM-3 | AC-3.1~3.8 (控制器函数全量) | C API 单元测试 | OH_ArkUI_Swiper_* 7 个控制器函数 |
| VM-4 | AC-4.1~4.19 (指示器对象全量) | C API 单元测试 | OH_ArkUI_SwiperIndicator_* 20+ 函数 |
| VM-5 | AC-5.1~5.14 (数字指示器对象全量) | C API 单元测试 | OH_ArkUI_SwiperDigitIndicator_* 15+ 函数 |
| VM-6 | AC-6.1~6.9 (箭头样式对象全量) | C API 单元测试 | OH_ArkUI_SwiperArrowStyle_* 9+ 函数 |
| VM-7 | AC-7.1~7.5 (枚举全量) | C API 单元测试 | 5 个 C API 枚举值 |
| VM-8 | AC-8.1~8.3 (实现文件映射) | 代码审查 | node_swiper_modifier.cpp 完整实现 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| NODE_SWIPER_LOOP | System | C API 设置循环滑动 | AC-1.1 |
| NODE_SWIPER_AUTO_PLAY | System | C API 设置自动播放 | AC-1.2 |
| NODE_SWIPER_SHOW_INDICATOR | System | C API 设置显示指示器 | AC-1.3 |
| NODE_SWIPER_INTERVAL | System | C API 设置自动播放间隔 | AC-1.4 |
| NODE_SWIPER_VERTICAL | System | C API 设置纵向滑动 | AC-1.5 |
| NODE_SWIPER_DURATION | System | C API 设置动画时长 | AC-1.6 |
| NODE_SWIPER_CURVE | System | C API 设置动画曲线 | AC-1.7 |
| NODE_SWIPER_ITEM_SPACE | System | C API 设置子项间距 | AC-1.8 |
| NODE_SWIPER_INDEX | System | C API 设置初始索引 | AC-1.9 |
| NODE_SWIPER_DISPLAY_COUNT | System | C API 设置同屏显示数量 | AC-1.10 |
| NODE_SWIPER_DISABLE_SWIPE | System | C API 设置禁用手势滑动 | AC-1.11 |
| NODE_SWIPER_SHOW_DISPLAY_ARROW | System | C API 设置导航箭头 | AC-1.12 |
| NODE_SWIPER_EDGE_EFFECT_MODE | System | C API 设置边缘效果 | AC-1.13 |
| NODE_SWIPER_NODE_ADAPTER | System | C API 设置 NodeAdapter | AC-1.14 |
| NODE_SWIPER_CACHED_COUNT | System | C API 设置预加载缓存数量 | AC-1.15 |
| NODE_SWIPER_PREV_MARGIN | System | C API 设置前预览边距 | AC-1.16 |
| NODE_SWIPER_NEXT_MARGIN | System | C API 设置后预览边距 | AC-1.17 |
| NODE_SWIPER_INDICATOR | System | C API 设置指示器类型和样式 | AC-1.18 |
| NODE_SWIPER_NESTED_SCROLL | System | C API 设置嵌套滚动模式 | AC-1.19 |
| NODE_SWIPER_SWIPE_TO_INDEX | System | C API 跳转到指定页 | AC-1.20 |
| NODE_SWIPER_INDICATOR_INTERACTIVE | System | C API 设置指示器可交互 | AC-1.21 |
| NODE_SWIPER_PAGE_FLIP_MODE | System | C API 设置翻页模式 | AC-1.22 |
| NODE_SWIPER_AUTO_FILL | System | C API 设置自动填充 | AC-1.23 |
| NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION | System | C API 设置保持可见内容位置 | AC-1.24 |
| NODE_SWIPER_ITEMFILLPOLICY | System | C API 设置项目填充策略 | AC-1.25 |
| NODE_SWIPER_EVENT_ON_CHANGE | System | C API 页面切换完成事件 | AC-2.1 |
| NODE_SWIPER_EVENT_ON_ANIMATION_START | System | C API 动画开始事件 | AC-2.2 |
| NODE_SWIPER_EVENT_ON_ANIMATION_END | System | C API 动画结束事件 | AC-2.3 |
| NODE_SWIPER_EVENT_ON_GESTURE_SWIPE | System | C API 手势滑动事件 | AC-2.4 |
| NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL | System | C API 内容滚动事件 | AC-2.5 |
| NODE_SWIPER_EVENT_ON_SELECTED | System | C API 页面选中事件 | AC-2.6 |
| NODE_SWIPER_EVENT_ON_UNSELECTED | System | C API 页面取消选中事件 | AC-2.7 |
| NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL | System | C API 内容即将滚动事件 | AC-2.8 |
| NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED | System | C API 滚动状态变化事件 | AC-2.9 |
| OH_ArkUI_Swiper_FinishAnimation | System | C API 结束动画 | AC-3.1 |
| OH_ArkUI_Swiper_StartFakeDrag | System | C API 开始模拟拖拽 | AC-3.2 |
| OH_ArkUI_Swiper_FakeDragBy | System | C API 模拟拖拽偏移 | AC-3.3 |
| OH_ArkUI_Swiper_StopFakeDrag | System | C API 结束模拟拖拽 | AC-3.4 |
| OH_ArkUI_Swiper_IsFakeDragging | System | C API 查询模拟拖拽状态 | AC-3.5 |
| OH_ArkUI_Swiper_ShowPrevious | System | C API 翻到上一页 | AC-3.6 |
| OH_ArkUI_Swiper_ShowNext | System | C API 翻到下一页 | AC-3.7 |
| OH_ArkUI_SwiperIndicator_Create/Dispose/Set*/Get* | System | C API 指示器对象函数 | AC-4.1~4.18 |
| OH_ArkUI_SwiperDigitIndicator_Create/Set*/Get*/Destroy | System | C API 数字指示器对象函数 | AC-5.1~5.14 |
| OH_ArkUI_SwiperArrowStyle_Create/Set*/Get*/Destroy | System | C API 箭头样式对象函数 | AC-6.1~6.9 |
| ArkUI_SwiperArrow | System | C API 箭头枚举 | AC-7.1 |
| ArkUI_SwiperNestedScrollMode | System | C API 嵌套滚动枚举 | AC-7.2 |
| ArkUI_PageFlipMode | System | C API 翻页模式枚举 | AC-7.3 |
| ArkUI_SwiperIndicatorType | System | C API 指示器类型枚举 | AC-7.4 |
| ArkUI_SwiperAnimationMode | System | C API 动画模式枚举 | AC-7.5 |

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
- **最低支持版本:** API 12（C API）
- **API 版本号策略:** C API 属性 @since 12；OH_ArkUI_SwiperDigitIndicator_* @since 19；NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION @since 20；OH_ArkUI_Swiper_StartFakeDrag/FakeDragBy/StopFakeDrag/IsFakeDragging @since 23

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| C API 双通道 | C API 走 node_modifier → SwiperModelNG 静态方法，与 ArkTS Bridge 并行（ADR-2） | AC-1.1~1.25 |
| C API 参数传递 | 所有 NODE_SWIPER_* 属性通过 ArkUI_AttributeItem 参数传递 | AC-1.1~1.25 |
| C API 对象生命周期 | OH_ArkUI_SwiperIndicator/DigitIndicator/ArrowStyle 对象需手动 Create/Dispose/Destroy | AC-4.3, AC-5.13, AC-6.9 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | C API 属性设置与 ArkTS Bridge 性能一致 | 代码审查 | `node_swiper_modifier.cpp` → `SwiperModelNG` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ARC_DOT 指示器不在 C API ArkUI_SwiperIndicatorType 中 | 仅 DOT/DIGIT | 构建验证 | `native_type.h:1306-1311` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | C API 属性和事件不直接影响无障碍 | — |
| 大字体 | 否 | C API 参数不涉及字体 | — |
| 深色模式 | 否 | C API 颜色参数由开发者传入 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | OH_ArkUI_SwiperDigitIndicator_* @since 19，NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION @since 20，FakeDrag C API @since 23 | AC-5.1, AC-1.24, AC-3.2 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper C API 全量规格

  Scenario: 通过 C API 设置 Swiper 属性
    Given 一个 ARKUI_NODE_SWIPER 节点
    When 设置 NODE_SWIPER_LOOP 为 true
    And 设置 NODE_SWIPER_AUTO_PLAY 为 true
    And 设置 NODE_SWIPER_INTERVAL 为 5000
    Then Swiper 启用循环自动播放，间隔 5000ms

  Scenario: 通过 C API 设置指示器
    Given 一个 ARKUI_NODE_SWIPER 节点
    And 创建 OH_ArkUI_SwiperIndicator(ARKUI_SWIPER_INDICATOR_TYPE_DOT)
    When 设置 indicator 的 ItemWidth/ItemHeight/SelectedColor
    And 设置 NODE_SWIPER_INDICATOR 属性传入 indicator
    Then Swiper 显示自定义样式圆点指示器

  Scenario: 通过 C API 注册事件回调
    Given 一个 ARKUI_NODE_SWIPER 节点
    When 注册 NODE_SWIPER_EVENT_ON_CHANGE 事件
    Then 页面切换完成时回调触发
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（C API 全量规格，涵盖所有 NODE_SWIPER_* 属性/事件/控制器/对象/枚举）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper NODE_SWIPER attributes all C API properties native_node.h node_swiper_modifier.cpp"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper NODE_SWIPER_EVENT events C API registration native_node.h"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper OH_ArkUI_Swiper controller functions OH_ArkUI_SwiperIndicator OH_ArkUI_SwiperDigitIndicator OH_ArkUI_SwiperArrowStyle"
```

**关键文档：** `design.md`（同目录）
