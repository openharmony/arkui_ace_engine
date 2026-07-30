# Refresh Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Refresh`

## 定位

Refresh 是 ArkUI 的下拉刷新容器组件，纵向（`Axis::VERTICAL`）嵌套滚动容器，包裹一个可滚动子节点（List/Grid/WaterFlow），通过阻尼下拉手势触发 `RefreshStatus` 状态机（INACTIVE→DRAG→OVER_DRAG→REFRESH→DONE）并驱动默认 LoadingProgress 或自定义指示器。Refresh 已完成组件化改造，经 `bridge/` 子目录统一 Bridge，输出独立动态库 `libarkui_refresh.z.so`。

本文档用于快速定位 Refresh 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern（手势/状态机/动画/嵌套） | `frameworks/core/components_ng/pattern/refresh/refresh_pattern.cpp` | `RefreshPattern : NestableScrollContainer`，Axis 固定 VERTICAL |
| Pattern 类型声明 | `frameworks/core/components_ng/pattern/refresh/refresh_pattern.h` | `RefreshPattern` 成员：refreshStatus_/scrollOffset_/refreshOffset_(64vp)/pullToRefresh_/pullUpToCancelRefresh_/offsetProperty_(API11+)/lowVersionOffset_(API10-) |
| 布局属性 | `frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h` | IsRefreshing/IndicatorOffset/Friction/LoadingText(promptText)/PullToRefresh/RefreshOffset/PullDownRatio/MaxPullDownDistance/PullUpToCancelRefresh |
| 布局算法 | `frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.cpp` | `BoxLayoutAlgorithm` 子类，Measure/Layout/CalculateBuilderSize |
| 事件存储 | `frameworks/core/components_ng/pattern/refresh/refresh_event_hub.h` | StateChange/RefreshChange/Refreshing/OffsetChange/OffsetStepChange |
| 无障碍 | `frameworks/core/components_ng/pattern/refresh/refresh_accessibility_property.cpp` | a11y |
| 状态枚举 | `frameworks/core/components_ng/pattern/refresh/refresh_constant.h` | `RefreshStatus` |
| 动画状态枚举 | `frameworks/core/components_ng/pattern/refresh/refresh_animation_state.h` | FOLLOW_HAND/FOLLOW_TO_RECYCLE/RECYCLE |
| 主题 | `frameworks/core/components_ng/pattern/refresh/refresh_theme_ng.h` / `refresh_theme_wrapper.h` | 颜色/尺寸 |
| Model（抽象/NG/静态） | `frameworks/core/components_ng/pattern/refresh/refresh_model_ng.cpp` / `refresh_model_static.cpp` | Create/Set*/静态访问器 |
| 嵌套滚动基类 | `frameworks/core/components_ng/pattern/scrollable/nestable_scroll_container.h` | RefreshPattern 继承 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/refresh.d.ts` | 动态 ArkTS Refresh 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/refresh.static.d.ets` | 静态声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/RefreshModifier.d.ts` | 动态 Modifier |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/RefreshModifier.static.d.ets` | 静态 Modifier |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_REFRESH`、`NODE_REFRESH_*` 属性与事件枚举 |

API 检索建议：属性搜 `RefreshAttribute`、`RefreshOptions`；状态搜 `RefreshStatus`；C API 搜 `NODE_REFRESH_`、`ARKUI_NODE_REFRESH`。

### API 解析实现路径

Refresh 已完成组件化改造（存在 `bridge/` 子目录，无 `js_refresh.cpp` JSView 文件，使用动态 Ark 组件 + Modifier 系统）。动态库映射 `{ "Refresh", "refresh" }`（见 `adapter/ohos/osal/dynamic_module_helper.cpp`），输出 `libarkui_refresh.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkrefresh.ts` | `JSRefresh` + `ArkRefreshComponent` + 各属性 Modifier |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/refresh/bridge/arkts_native_refresh_bridge.cpp` | Create/Set*/Reset*/RegisterRefreshAttributes，经 `getUINativeModule().refresh.*` 转 ModelNG |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/refresh/bridge/refresh_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/refresh/bridge/refresh_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/refresh/bridge/refresh_dynamic_module.cpp` | `RefreshDynamicModule : DynamicModule`，`OHOS_ACE_DynamicModule_Create_Refresh` 入口，`libarkui_refresh.z.so` |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_refresh_modifier.cpp` | C++ Set/Reset/Get，经 DynamicModuleHelper 转发到动态模块 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/refresh_modifier.ts` | `RefreshModifier(LazyArkRefreshComponent)` 实现 `AttributeModifier<RefreshAttribute>` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Refresh 单元测试 | `test/unittest/core/pattern/refresh/` | RefreshPattern/Model/Layout/Accessibility 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-06 | Refresh | `specs/05-ui-components/03-scroll-container-components/06-refresh/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/06-refresh/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 创建、刷新状态生命周期与指示器内容 | Refresh(value)/refreshing($$)/RefreshStatus 状态机/onStateChange/onRefreshing, builder/refreshingContent/promptText, 默认 LoadingProgress 替换契约, 键盘 F5/Ctrl+R | Baselined |
| Feat-02 | 下拉物理、触发/取消手势与偏移观测 | offset/friction(弃用 11)/refreshOffset/pullDownRatio/maxPullDownDistance, 阻尼 exp(-ratio_*gamma), pullToRefresh/pullUpToCancelRefresh, onOffsetChange, 嵌套滚动协调, API10-/11+ 双路径 | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 刷新不触发 | `pullToRefresh`(默认 true)、子节点是否在顶部、`refreshOffset`(默认 64vp) 阈值、`HandleScroll` 嵌套模式 |
| 状态机/事件顺序异常 | `refresh_pattern.cpp` `UpdateRefreshStatus`（INACTIVE→DRAG→OVER_DRAG→REFRESH→DONE，事件顺序固定） |
| 阻尼手感异常 | `CalculatePullDownRatio`（`exp(-ratio_*gamma)`）、`InterpolatingSpring(velocity,1.0,228.0,30.0)` |
| 自定义指示器叠加/未替换 | `AddCustomBuilderNode`（先删默认 LoadingProgress 再加 builder） |
| offset/friction 弃用迁移 | `refresh.d.ts`（offset/friction 弃用 11 → refreshOffset/pullDownRatio，语义不同需重设） |
| API10- 设备异常 | `offsetProperty_`(API11+) vs `lowVersionOffset_`(API10-) 双路径 |
| 键盘快捷键不响应 | `OnKeyEvent`（F5/Ctrl+R，仅非刷新中） |
| C API 属性无效 | `node_refresh_modifier.cpp`、`arkts_native_refresh_bridge.cpp` |

## 调试入口

- 关键字：grep `RefreshPattern`、`RefreshLayoutProperty`、`RefreshEventHub`、`RefreshStatus`
- 状态机/动画：grep `UpdateRefreshStatus`、`RefreshAnimationState`、`CalculatePullDownRatio`
- 自定义指示器：grep `AddCustomBuilderNode`、`progressChild_`、`loadingTextNode_`、`customBuilder_`
- 嵌套：grep `HandleScroll`、`OnScrollStartRecursive`、`OnScrollEndRecursive`、`HandleScrollVelocity`
- 组件化：grep `RefreshDynamicModule`、`OHOS_ACE_DynamicModule_Create_Refresh`、`arkrefresh`
- C API：grep `NODE_REFRESH_`、`ARKUI_NODE_REFRESH`
- 弃用迁移：grep `offset`(弃用 11)、`friction`(弃用 11)

## 相关主题

- Scroll/List/Grid/WaterFlow：Refresh 包裹的可滚动子节点，复用 `NestableScrollContainer`，详见各自 KB
- LoadingProgress：Refresh 默认指示器委托 LoadingProgress 绘制
