# WaterFlow Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `WaterFlow`

## 定位

WaterFlow 是 ArkUI 的瀑布流容器，FlowItem 是其子项节点。当前实现包含 WaterFlow/FlowItem 创建与 Sections、布局配置和 Item 约束、TOP_DOWN 普通/分段算法、SLIDING_WINDOW 算法、滚动控制与事件，以及缓存和懒加载等入口。

本文档用于定位当前源码、SDK、测试和 `05-03-10` Spec。具体默认值、算法规则、版本差异和异常恢复语义以当前实现与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期和算法派发 | `frameworks/core/components_ng/pattern/waterflow/water_flow_pattern.cpp` | Sections、Footer、LayoutInfo、控制器、事件和布局模式入口 |
| Dynamic Model | `frameworks/core/components_ng/pattern/waterflow/water_flow_model_ng.cpp` | WaterFlow 创建和动态属性写入 |
| Static Model | `frameworks/core/components_ng/pattern/waterflow/water_flow_model_static.cpp` | 静态 ArkTS 属性写入 |
| FlowItem Model/Node | `frameworks/core/components_ng/pattern/waterflow/water_flow_item_model_ng.cpp` | FlowItem 创建、约束和节点入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/waterflow/water_flow_layout_property.cpp` | 模板、gap、方向、Item 约束和缓存属性 |
| Sections | `frameworks/core/components_ng/pattern/waterflow/water_flow_sections.cpp` | Section 配置和变更管理 |
| 公共布局工具 | `frameworks/core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.cpp` | 轨道模板、Item 约束和测量辅助 |
| TOP_DOWN 普通算法 | `frameworks/core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_algorithm.cpp` | 普通 TOP_DOWN 测量、布局、跳转和 Footer |
| TOP_DOWN 分段算法 | `frameworks/core/components_ng/pattern/waterflow/layout/top_down/water_flow_segmented_layout.cpp` | Sections 分段轨道、margin 和尺寸回调 |
| SLIDING_WINDOW 算法 | `frameworks/core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.cpp` | 窗口 lanes、跳转、估算和缓存 |
| SLIDING_WINDOW 状态 | `frameworks/core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.cpp` | SW 布局状态和滚动信息 |
| 公共算法/缓存基类 | `frameworks/core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.cpp` | active/cache/predict/idle 预载入口 |
| Paint 与内容 Modifier | `frameworks/core/components_ng/pattern/waterflow/water_flow_paint_method.cpp` | 滚动条、边缘效果和内容绘制 |
| 事件存储 | `frameworks/core/components_ng/pattern/waterflow/water_flow_event_hub.h` | WaterFlow 事件回调入口 |
| WaterFlow node_modifier | `frameworks/core/interfaces/native/node/water_flow_modifier.cpp` | 通过动态模块取得 WaterFlow Modifier |
| FlowItem node_modifier | `frameworks/core/interfaces/native/node/flow_item_modifier.cpp` | FlowItem Native Modifier 委托入口 |
| Sections C API 对象 | `interfaces/native/node/waterflow_section_option.cpp` | WaterFlow SectionOptions Native 接口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| WaterFlow Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/water_flow.d.ts` | WaterFlow、Sections、布局、缓存和事件声明 |
| FlowItem Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/flow_item.d.ts` | FlowItem 声明 |
| WaterFlow Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/waterFlow.static.d.ets` | 静态 WaterFlow 与 Sections 声明 |
| FlowItem Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/flowItem.static.d.ets` | 静态 FlowItem 声明 |
| Dynamic Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/WaterFlowModifier.d.ts` | WaterFlow Dynamic Modifier 声明 |
| Static Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/WaterFlowModifier.static.d.ets` | WaterFlow Static Modifier 声明 |
| Public C API | `interfaces/native/native_node.h` | `ARKUI_NODE_WATER_FLOW`、`NODE_WATER_FLOW_*` 属性和事件 |

API 检索建议：

- 构造与 Sections：搜索 `WaterFlowInterface`、`WaterFlowOptions`、`WaterFlowSections`、`SectionOptions`。
- 属性和事件：搜索 `WaterFlowAttribute`、`cachedCount`、`layoutMode`、`onScrollIndex`。
- FlowItem：搜索 `FlowItemAttribute` 和 `ARKUI_NODE_FLOW_ITEM`。
- Public C API：搜索 `NODE_WATER_FLOW_`、`NODE_ON_WILL_SCROLL`、`NODE_WATER_FLOW_ON_DID_SCROLL`。

### API 解析实现路径

WaterFlow/FlowItem 已完成组件化改造：动态模块映射包含 `WaterFlow` 和 `FlowItem`，组件目录存在统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module；运行产物为共享的 `libarkui_waterflow.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkWaterFlow.ts`、`ArkFlowItem.ts` | WaterFlow/FlowItem 前端组件类 |
| WaterFlow 统一 Bridge | `frameworks/core/components_ng/pattern/waterflow/bridge/waterflow/arkts_native_water_flow_bridge.cpp` | 声明式与动态属性参数解析 |
| FlowItem 统一 Bridge | `frameworks/core/components_ng/pattern/waterflow/bridge/flowitem/arkts_native_water_flow_item_bridge.cpp` | FlowItem 参数解析 |
| WaterFlow Dynamic Modifier | `frameworks/core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_dynamic_modifier.cpp` | WaterFlow Dynamic ArkTS 属性路径 |
| FlowItem Dynamic Modifier | `frameworks/core/components_ng/pattern/waterflow/bridge/flowitem/water_flow_item_dynamic_modifier.cpp` | FlowItem Dynamic ArkTS 属性路径 |
| WaterFlow Static Modifier | `frameworks/core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_static_modifier.cpp` | WaterFlow 静态编译属性路径 |
| FlowItem Static Modifier | `frameworks/core/components_ng/pattern/waterflow/bridge/flowitem/water_flow_item_static_modifier.cpp` | FlowItem 静态编译属性路径 |
| WaterFlow Dynamic Module | `frameworks/core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_dynamic_module.cpp` | WaterFlow 动态模块入口 |
| FlowItem Dynamic Module | `frameworks/core/components_ng/pattern/waterflow/bridge/flowitem/water_flow_item_dynamic_module.cpp` | FlowItem 动态模块入口；与 WaterFlow 共享 `libarkui_waterflow.z.so` |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/water_flow_modifier.cpp`、`flow_item_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |
| Public C API | `interfaces/native/node/style_modifier.cpp`、`waterflow_section_option.cpp` | 通用 style 分派和 Sections 对象接口 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 外部目标 | 说明 |
|----------|----------|-----------|----------|------|
| API 指标统计（条件依赖） | `frameworks/core/components_ng/pattern/waterflow/BUILD.gn` | `<OH_ROOT>/base/hiviewdfx/api_metrics/` | `api_metrics:histogrammanager` | 构建环境提供 api_metrics 部件时启用 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| WaterFlow Host 单元测试 | `test/unittest/core/pattern/waterflow/` | Pattern、Model、三类布局路径、Sections、事件、缓存和可访问性 |
| WaterFlow Modifier C API | `test/unittest/capi/modifiers/water_flow_modifier_test.cpp` | Public C 属性设置、读取和重置 |
| Generated Modifier | `test/unittest/capi/modifiers/generated/water_flow_modifier_test.cpp` | generated Modifier 路径 |
| Sections Accessor C API | `test/unittest/capi/accessors/water_flow_section_accessor_test.cpp` | SectionOptions Native 访问器 |
| LazyWaterFlowLayout | `test/unittest/core/pattern/lazy_waterflow_layout/` | 相关懒布局组件集成测试 |

### 相关 Spec

功能域：`specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/`（功能 ID `05-03-10`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 设计文档 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/design.md` | WaterFlow/FlowItem 架构、算法派发与状态边界 |
| Feat-01 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-01-creation-footer-flowitem-spec.md` | 创建、Footer、Sections 与 FlowItem |
| Feat-02 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-02-layout-config-item-constraint-spec.md` | 布局配置与 Item 约束 |
| Feat-03 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-03-always-top-down-layout-spec.md` | TOP_DOWN 普通与分段算法 |
| Feat-04 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-04-sliding-window-layout-spec.md` | SLIDING_WINDOW 算法 |
| Feat-05 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-05-scroll-control-events-spec.md` | 滚动控制与事件 |
| Feat-06 | `specs/05-ui-components/03-scroll-container-components/10-water-flow-flow-item/Feat-06-cache-lazy-loading-spec.md` | 缓存与懒加载 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 布局模式选择或切换异常 | `water_flow_pattern.cpp`、对应 LayoutInfo 和 Feat-03/04 |
| Sections 轨道、间距或数量异常 | `water_flow_sections.cpp`、`water_flow_layout_utils.cpp` 和 Feat-02 |
| TOP_DOWN Item 位置或 Footer 异常 | `layout/top_down/` 和 Feat-01/03 |
| SLIDING_WINDOW 跳转或偏移估算异常 | `layout/sliding_window/` 和 Feat-04 |
| scrollToIndex、Reach 或 index 事件异常 | `water_flow_pattern.cpp`、`water_flow_event_hub.h` 和 Feat-05 |
| cachedCount、预载或回收异常 | `water_flow_layout_algorithm_base.cpp` 和 Feat-06 |
| ArkTS 与 NativeNode 属性结果不一致 | WaterFlow Bridge、Dynamic/Static Modifier、`style_modifier.cpp` |

## 调试入口

- 核心类型：`WaterFlowPattern`、`WaterFlowModelNG`、`WaterFlowLayoutInfoBase`、`WaterFlowSections`。
- 算法派发：搜索 `CreateLayoutAlgorithm`、`WaterFlowLayoutMode`、`WaterFlowSegmentedLayout`、`WaterFlowLayoutSW`。
- 布局状态：搜索 `startIndex_`、`endIndex_`、`currentOffset_`、`lanes_`、`segments_`。
- 缓存：搜索 `cachedCount`、`PredictBuildItem`、`PreloadItem`、`deadline`。
- NativeNode：搜索 `NODE_WATER_FLOW_`、`GetWaterFlowModifier`、`OHOS_ACE_DynamicModule_Create_WaterFlow`。

## 相关主题

- [滚动公共能力。](../../capabilities/scroll-common-capability.md)