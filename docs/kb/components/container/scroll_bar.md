# ScrollBar Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `ScrollBar`

## 定位

ScrollBar 是 ArkUI 的独立滚动条组件，通过 `Scroller`/`ScrollBarProxy` 与可滚动宿主（Scroll/List/Grid/WaterFlow）配对，不渲染滚动内容本身。需与可滚动容器的内建滚动条属性（`scrollBar`/`scrollBarColor`/`scrollBarWidth`，属 `ScrollableCommonMethod`）区分——后者属各可滚动组件规格，本主题仅覆盖独立 `ScrollBar` 组件。穿戴设备另有 ArcScrollBar 形态。

本文档用于快速定位 ScrollBar 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern（偏移/距离/手势/消失动画/代理） | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_pattern.cpp` | `ScrollBarPattern : Pattern`，displayMode 默认 AUTO、axis 默认 VERTICAL |
| Pattern 类型声明 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h` | `ScrollBarPattern`，`enableNestedSorll_` 嵌套开关 |
| 布局属性 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_layout_property.h` | Axis/DisplayMode/Visibility |
| 绘制属性 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_paint_property.h` | ScrollBarColor |
| 布局算法 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_layout_algorithm.cpp` | currentOffset/scrollableDistance/controlDistance |
| 绘制 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_paint_method.cpp` | 仅 API≥12 启用 |
| 无障碍 | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_accessibility_property.cpp` | a11y |
| 代理（与宿主配对） | `frameworks/core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h` | 登记多 ScrollBar 与一宿主 |
| Model（抽象/NG/静态） | `frameworks/core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.cpp` / `scroll_bar_model_static.cpp` | Create/SetEnableNestedScroll/SetScrollBarColor/资源对象 |
| 复用事件 | `frameworks/core/components_ng/pattern/scroll/scroll_event_hub.h` | ScrollBarPattern 复用为 EventHub |
| 内建 ScrollBar 对象 | `frameworks/core/components_ng/pattern/scroll/inner/scroll_bar.h` | 被 ScrollBarPattern 复用绘制 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/scroll_bar.d.ts` | 动态 ArkTS ScrollBar 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/scrollBar.static.d.ets` | 静态声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_SCROLL`、`NODE_SCROLL_BAR_*` 属性枚举 |

API 检索建议：属性搜 `ScrollBarAttribute`、`ScrollBarOptions`；方向搜 `ScrollBarDirection`；C API 搜 `NODE_SCROLL_BAR_`、`ARKUI_NODE_SCROLL`。

### API 解析实现路径

ScrollBar 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.cpp` | `JSScrollBar::Create` 解析 scroller/direction/state → Model |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_scroll_bar_modifier.cpp` | `ArkUIScrollBarModifier` 函数表（`setScrollBarDirection` 为 nullptr，方向经 options 设置） |
| 生成 Modifier | `frameworks/core/interfaces/native/implementation/scroll_bar_modifier.cpp` | `GeneratedModifier::ScrollBarModifier`：ConstructImpl/SetScrollBarOptionsImpl/SetEnableNestedScrollImpl/SetScrollBarColorImpl |
| C API（NDK） | `interfaces/native/native_node.h` | `NODE_SCROLL_BAR_*`（display mode/width/color/state/scroller 等） |

> 注：ScrollBar 无专属 `ark_modifier` Modifier.ts；属性经 JSView 与 node_modifier 两路径，无静态 Modifier 类。

组件化改造参考：`./组件化重构通用方案.md`。改造后 JSView 和 Bridge 双路径将统一到 `pattern/scroll_bar/bridge/`，并输出独立 so。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| ScrollBar 单元测试 | `test/unittest/core/pattern/scroll_bar/` | ScrollBarPattern/Model/Layout + ArcScrollBar 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-03 | ScrollBar | `specs/05-ui-components/03-scroll-container-components/03-scroll-bar/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/03-scroll-bar/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 核心构造与绑定 | ScrollBar(value)/scroller/direction/state/ScrollBarDirection + Scroller↔ScrollBarProxy 绑定机制（API8/10/11），方向/状态越界钳位 VERTICAL/AUTO | Baselined |
| Feat-02 | 行为与视觉扩展 | enableNestedScroll(@14, 委派宿主 SearchAndSetParentNestedScroll), scrollBarColor(@20, ColorMetrics+资源对象+主题回退) | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 滚动条不显示 | `scroll_bar_model_ng.cpp` Create 的 direction/state 校验与默认（越界→VERTICAL/AUTO，Off→INVISIBLE） |
| 未与宿主联动 | `scroll_bar_proxy.h` 配对登记、`scroller` 是否绑定、`ScrollBarProxy` 是否非空 |
| enableNestedScroll 无效 | `scroll_bar_model_ng.cpp` `SetEnableNestedScroll`（无 Proxy 时提前返回 no-op，委派宿主） |
| 颜色/reset 异常 | `SetScrollBarColor`/`ResetScrollBarColor`（主题 `ScrollBarTheme::GetForegroundColor` 回退）、`HandleSetScrollBarColor` 资源热重载 |
| API<12 不绘制 | `scroll_bar_pattern.h` `CreateNodePaintMethod` 版本分支（仅 ≥12 走 ScrollBarPaintMethod） |
| ArcScrollBar 异常 | `node_arc_scroll_bar_modifier.cpp`、`CreateArcScrollBar`（WATCH/WEARABLE） |
| C API 方向设置无效 | `node_scroll_bar_modifier.cpp`（`setScrollBarDirection` 为 nullptr，方向只能经 options 设置） |
| 签名差异 | ScrollBar `scrollBarColor(ColorMetrics@20)` vs 可滚动容器 `scrollBarColor(Color|string|number|Resource)` |

## 调试入口

- 关键字：grep `ScrollBarPattern`、`ScrollBarModelNG`、`ScrollBarProxy`
- 创建/校验：grep `JSScrollBar`、`SCROLL_BAR_ETS_TAG`、`RegisterScrollBar`
- 嵌套：grep `enableNestedSorll_`、`SearchAndSetParentNestedScroll`
- 颜色：grep `ScrollBarPaintProperty`、`ScrollBarTheme`、`HandleSetScrollBarColor`
- 弧形：grep `ArcScrollBar`、`ARC_SCROLL_BAR_ETS_TAG`、`CreateArcScrollBar`
- C API：grep `NODE_SCROLL_BAR_`、`ARKUI_NODE_SCROLL`、`GetScrollBarModifier`

## 相关主题

- Scroll/List/Grid/WaterFlow：可滚动宿主，内建滚动条经 `ScrollableCommonMethod`，独立 ScrollBar 经 `ScrollBarProxy` 与之配对，详见各自 KB
- Scroll：Scroller 类型共享，详见 Scroll KB
