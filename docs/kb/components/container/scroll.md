# Scroll Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Scroll`

## 定位

Scroll 是 ArkUI 的通用可滚动容器组件，继承 `ScrollablePattern`（进而继承 `NestableScrollContainer`），支持纵向/横向/二维自由滚动（`ScrollDirection.FREE`）、滚动条与边缘效果、程序化控制器（`Scroller`）、嵌套滚动、事件可观测性、分页吸附与捏合缩放。

本文档用于快速定位 Scroll 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、偏移、snap、zoom、free-scroll | `frameworks/core/components_ng/pattern/scroll/scroll_pattern.cpp` | ScrollPattern 核心行为 |
| Pattern 类型声明 | `frameworks/core/components_ng/pattern/scroll/scroll_pattern.h` | `ScrollPattern : ScrollablePattern` |
| 基类（滚动条/边缘效果/摩擦/嵌套/pan） | `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp` | 继承复用的滚动基础设施 |
| 嵌套滚动基类 | `frameworks/core/components_ng/pattern/scrollable/nestable_scroll_container.h` | 嵌套分发 |
| 布局属性 | `frameworks/core/components_ng/pattern/scroll/scroll_layout_property.h` | Axis/ScrollEnabled/ScrollSnapAlign/ScrollWidth |
| 布局算法 | `frameworks/core/components_ng/pattern/scroll/scroll_layout_algorithm.cpp` | currentOffset/scrollableDistance/UseInitialOffset |
| 事件存储 | `frameworks/core/components_ng/pattern/scroll/scroll_event_hub.h` | onScroll/onWillScroll/onDidScroll + zoom 事件 |
| 绘制 | `frameworks/core/components_ng/pattern/scroll/scroll_paint_method.cpp` | Scroll 绘制 |
| 内容 modifier | `frameworks/core/components_ng/pattern/scroll/scroll_content_modifier.cpp` | 脏矩形/内容 modifier |
| 边缘效果 | `frameworks/core/components_ng/pattern/scroll/scroll_edge_effect.h` + `effect/` | Spring/Fade 子系统 |
| 内建滚动条 1D/2D | `frameworks/core/components_ng/pattern/scroll/inner/scroll_bar.h` / `scroll_bar_2d.h` | FREE 模式用 2D |
| 自由滚动控制器 | `frameworks/core/components_ng/pattern/scroll/free_scroll_controller.cpp` | 2D 偏移 |
| 缩放控制器 | `frameworks/core/components_ng/pattern/scroll/zoom_controller.cpp` | 捏合缩放 |
| Model（抽象/NG/静态） | `frameworks/core/components_ng/pattern/scroll/scroll_model_ng.cpp` / `scroll_model_static.cpp` | 属性 Set/Get + 静态 FrameNode 访问器 |
| 控制器基类 | `frameworks/core/components/scroll/scroll_controller_base.h` / `scroll_position_controller.cpp` | Scroller 实现 |
| 无障碍 | `frameworks/core/components_ng/pattern/scroll/scroll_accessibility_property.cpp` | a11y 动作 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/scroll.d.ts` | 动态 ArkTS Scroll 接口声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/scroll.static.d.ets` | 静态 ArkTS Scroll 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ScrollModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ScrollModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_SCROLL`、`NODE_SCROLL_*` 属性与事件枚举 |

API 检索建议：属性声明搜 `ScrollAttribute`；构造搜 `ScrollInterface`/`Scroll(`；控制器搜 `Scroller`；C API 搜 `NODE_SCROLL_`、`ARKUI_NODE_SCROLL`。

### API 解析实现路径

Scroll 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_scroll.cpp` | `JSScroll::SetXxx()` → `ScrollModel::GetInstance()->SetXxx()` |
| 控制器桥接 | `frameworks/bridge/declarative_frontend/jsview/js_scroller.cpp` | `JSScroller` 绑定 `scrollTo`/`scrollEdge`/`fling` 等控制器方法 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_scroll_modifier.cpp` | C++ Set/Reset/Get，Bridge 和 C API 共用 |
| C API（NDK） | `interfaces/native/native_node.h` | 30+ `NODE_SCROLL_*` 属性、17 `NODE_SCROLL_EVENT_*` 事件枚举 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/scroll_modifier.ts` | ArkTS Scroll Modifier 类 |


### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Scroll 单元测试 | `test/unittest/core/pattern/scroll/` | ScrollModelNG/ScrollPattern/Layout/FreeScroll/Zoom 测试 |
| C-API accessor 测试 | `test/unittest/capi/accessors/` | scrollable_target_info_accessor 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-07 | Scroll | `specs/05-ui-components/03-scroll-container-components/07-scroll/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/07-scroll/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 核心几何/方向与布局 | Scroll/Scroller 创建, scrollable, initialOffset, contentStartOffset/EndOffset, ScrollLayoutAlgorithm | Baselined |
| Feat-02 | 滚动条与视觉边缘效果 | scrollBar/Color/Width/Margin, autoAdjustScrollBarMargin, edgeEffect, fadingEdge, clipContent | Baselined |
| Feat-03 | 滚动运动控制器 API | scrollTo/scrollEdge/fling/scrollPage/scrollBy/scrollToIndex/currentOffset/offset/isAtEnd/getItemRect/getItemIndex/contentSize/getFrameNode/flingSpeedLimit | Baselined |
| Feat-04 | 交互/手势与嵌套滚动 | enableScrollInteraction/friction/enableScrollWithMouse/digitalCrownSensitivity/backToTop/nestedScroll | Baselined |
| Feat-05 | 滚动事件与可观测性 | onScroll(弃用)/onWillScroll/onDidScroll/onScrollEdge/onScrollStart/onScrollStop/onScrollFrameBegin/onReachStart/End/onWillStartDragging/onDidStopDragging/onWillStartFling/onDidStopFling | Baselined |
| Feat-06 | 分页与吸附对齐 | scrollSnap/enablePaging/ScrollSnapOptions/ScrollSnapAlign | Baselined |
| Feat-07 | 缩放与二维自由滚动 | maxZoomScale/minZoomScale/zoomScale/enableBouncesZoom/onDidZoom/onZoomStart/onZoomStop + ScrollDirection.FREE | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 滚动不响应 | `scrollable_pattern.cpp` pan 识别与 `enableScrollInteraction`/`scrollable` |
| 边缘回弹/渐隐异常 | `scroll_edge_effect.h`、`effect/scroll_fade_effect.cpp`、`scroll_spring_effect.cpp` |
| 滚动条显示/颜色/宽度异常 | `inner/scroll_bar.h`、`scrollable_pattern.cpp` 滚动条 plumbing |
| 嵌套滚动分发异常 | `nestable_scroll_container.h`、`nestedScroll` 配置 |
| scrollTo/scrollEdge 行为异常 | `scroll_position_controller.cpp`、`scrollable_controller.h` |
| 事件不触发/时序异常 | `scroll_event_hub.h`（onScroll 弃用 12→onWillScroll/onDidScroll） |
| 分页/吸附异常 | `scroll_pattern.cpp` snap 块（CaleSnapOffsets/StartScrollSnapAnimation） |
| 缩放/2D 自由滚动异常 | `zoom_controller.cpp`、`free_scroll_controller.cpp`、`inner/scroll_bar_2d.h` |
| C API 属性无效 | `node_scroll_modifier.cpp` Set/Reset |

## 调试入口

- 滚动关键字：grep `ScrollPattern`、`ScrollModel`、`ScrollLayoutProperty`、`ScrollEventHub`
- 自由滚动/缩放：grep `FreeScrollController`、`ZoomController`、`ScrollBar2D`
- 控制器：grep `ScrollPositionController`、`JSScroller`
- C API：grep `NODE_SCROLL_`、`ARKUI_NODE_SCROLL`
- 弃用迁移：grep `onScroll`(弃用 12)、`ScrollDirection.Free`(弃用 9)

## 相关主题

- [ScrollBar：独立滚动条经 `Scroller`/`ScrollBarProxy` 与 Scroll 配对，详见 ScrollBar KB](scroll-bar.md)
- [List](list.md)
- [Grid](grid.md)
- [WaterFlow](waterflow.md)
- [Tabs](tabs.md)
- [Swiper](swiper.md)