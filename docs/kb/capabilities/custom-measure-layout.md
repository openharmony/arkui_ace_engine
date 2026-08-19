# Custom Measure/Layout Context

> 文档版本：v1.0
> 更新时间：2026-08-03
> 来源：`docs/context_registry.json` 主题 `CustomMeasureLayout`

## 定位

Custom Measure/Layout 是 ArkUI 自定义组件的布局扩展能力。应用侧通过 `onMeasureSize` 返回自定义组件尺寸，并通过 `onPlaceChildren` 对已测量子组件执行放置；回调使用 `GeometryInfo`、`Measurable`、`Layoutable`、`ConstraintSizeOptions` 与 `SizeResult` 等布局数据对象。

该主题覆盖自定义组件回调及其 Dynamic/Static 前端实现，不覆盖 `DynamicLayout` 的 `CustomLayoutAlgorithm`（该能力以 `FrameNode` 为 API 载体）。具体参数语义、约束和兼容性以当前 SDK、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 自定义布局节点 | `frameworks/core/components_ng/pattern/custom/custom_measure_layout_node.h`、`frameworks/core/components_ng/pattern/custom/custom_measure_layout_node.cpp` | `CustomMeasureLayoutNode` 保存测量、放置及参数更新回调。 |
| 节点布局算法 | `frameworks/core/components_ng/pattern/custom/custom_node_layout_algorithm.h`、`frameworks/core/components_ng/pattern/custom/custom_node_layout_algorithm.cpp` | 自定义节点的 Measure/Layout 分发及默认布局路径。 |
| 子项参数抽象 | `frameworks/core/components_ng/pattern/custom/custom_measure_layout_param.h`、`frameworks/core/components_ng/pattern/custom/custom_measure_layout_param.cpp` | 子项 wrapper、约束创建和测量结果更新的通用承载。 |
| Dynamic 组件创建 | `frameworks/core/components_ng/base/view_partial_update_model_ng.cpp` | 根据自定义组件回调信息创建并配置 `CustomMeasureLayoutNode`。 |
| Dynamic 回调执行 | `frameworks/bridge/declarative_frontend/jsview/js_view_functions.cpp` | Dynamic 前端调用 `onMeasureSize`、`onPlaceChildren` 的执行入口。 |
| Dynamic 参数桥接 | `frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h`、`frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.cpp` | 生成 Dynamic 回调的 self、children、constraint 及子项 measure/layout 操作对象。 |
| Static ANI 组件接入 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/custom/custom_node_module.cpp` | 读取 Static 自定义组件的两个回调并连接到 `CustomMeasureLayoutNode`。 |
| Static ANI 参数桥接 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/custom/ani_measure_layout.h`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/custom/ani_measure_layout.cpp` | Static 回调的参数和子项操作对象入口。 |
| Static native modifier | `frameworks/core/interfaces/native/implementation/custom_layout_root_modifier.cpp` | Static `CustomLayoutRoot` 回调订阅的 native 实现。 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 自定义组件 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `CustomComponent` / `CustomComponentV2` 及 `onMeasureSize`、`onPlaceChildren`、布局数据对象声明。 |
| Static 自定义组件 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/customComponent.static.d.ets` | `LayoutCallbacks`、`@Layoutable` 自定义组件和对应的测量/放置回调声明。 |
| Dynamic FrameNode | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.d.ts` | 相邻 `DynamicLayout` 自定义算法使用的 `FrameNode` 测量、放置 API；不替代本主题的自定义组件回调。 |
| Static FrameNode | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.static.d.ets` | Static `FrameNode` 布局操作声明，供相邻 `CustomLayoutAlgorithm` 场景核验。 |

没有独立的应用侧 Native Node C API；`CustomLayoutRoot` modifier 是 Static 前端内部接入，不应视为公开 C API。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 自定义测量/布局节点测试 | `test/unittest/core/pattern/custom/custom_measure_layout_node_test.cpp`、`test/unittest/core/pattern/custom/custom_measure_layout_node_test2.cpp` | 节点创建、回调和 Measure/Layout 路径回归。 |
| 参数对象测试 | `test/unittest/core/pattern/custom/custom_measure_layout_param_test_ng.cpp` | 子项参数、约束与测量结果承载的回归。 |
| 自定义组件测试 | `test/unittest/core/pattern/custom/custom_test_ng_first_part.cpp`、`test/unittest/core/pattern/custom/custom_test_ng_second_part.cpp` | 自定义组件的布局、复用和生命周期交叉回归。 |
| Static modifier 测试 | `test/unittest/capi/modifiers/custom_layout_root_modifier_test.cpp` | Static `CustomLayoutRoot` modifier 的回调接入回归。 |

### 相关 Spec

自定义测量/布局功能域：`specs/07-frontend/03-custom-components/05-custom-measure-layout/`（功能 ID `07-03-05`）。该功能域已在 functions registry 登记，目录中包含 Feature 规格与 design 文档，因此 registry 标记为 `spec_status: active`。

## 历史演变与保留代码

下表只区分 SDK 已废弃的公开 API、仍在使用的现行路径与兼容实现；“保留”不等同于无用或可直接删除。

| 范围 | 当前判定 | 证据路由 | 后续维护含义 |
|------|----------|----------|--------------|
| Dynamic `CustomComponent.onMeasure` / `onLayout` | 已废弃的公开 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` 标记 `@deprecated since 10` 并指向新回调 | 不应为新代码选择；保留兼容性需单独核验。 |
| `JSMeasureLayoutParam`、`ViewFunctions::ExecuteMeasure/ExecuteLayout` | 旧 API 的兼容实现，不是死代码 | `js_view_measure_layout.h` 标注其用于已废弃接口；`js_view_functions.cpp` 仍有执行入口 | 不要删除或把它当作现行 `onMeasureSize`/`onPlaceChildren` 路径。 |
| Dynamic `onMeasureSize` / `onPlaceChildren` | 现行 Dynamic 自定义组件路径 | `common.d.ts`、`JSMeasureLayoutParamNG` 与 `ViewFunctions::ExecuteMeasureSize/ExecutePlaceChildren` | 新增或排查 Dynamic 自定义组件时优先使用。 |
| Static `LayoutCallbacks` / `@Layoutable` | 现行 Static 路径 | `customComponent.static.d.ets`、`custom_node_module.cpp`、`ani_measure_layout.*` | 使用 ANI 与 Static native modifier 接入，不经 Dynamic JSView。 |
| `CustomLayoutRoot` modifier | Static 前端内部接入 | `custom_layout_root_modifier.cpp` | 不是应用侧 Native Node C API。 |
| `DynamicLayout.CustomLayoutAlgorithm` | 相邻但不同的公共能力 | `docs/kb/components/container/dynamic-layout.md`、`<OH_ROOT>/interface/sdk-js/api/arkui/LayoutAlgorithm.d.ts` | 以 `onMeasure` / `onLayout` 和 `FrameNode` 为载体，不能与本主题的两个自定义组件回调混用。 |

源码历史显示自定义测量节点及早期 `onMeasure` / `onLayout` 路径先存在，随后增加 `onMeasureSize` / `onPlaceChildren`，并继续补充复用、懒加载与 Static ANI 支持。历史提交仅用于解释保留边界；实际删除决策仍需以当前 SDK 兼容承诺、引用关系和测试为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `onMeasureSize` 未触发或尺寸异常 | 自定义组件 SDK 声明、`ViewFunctions::ExecuteMeasureSize` 或 Static `custom_node_module.cpp`、`CustomNodeLayoutAlgorithm::Measure`。 |
| 子项无法测量或测量结果未刷新 | `Measurable` API、`MeasureLayoutParam`、Dynamic/Static 参数桥接和参数对象测试。 |
| `onPlaceChildren` 未触发或子项位置异常 | `Layoutable` API、`ViewFunctions::ExecutePlaceChildren` 或 Static `custom_node_module.cpp`、`CustomNodeLayoutAlgorithm::Layout`。 |
| 旧 `onMeasure` / `onLayout` 仍被调用 | SDK 废弃标记、`JSMeasureLayoutParam` 与 `ViewFunctions::ExecuteMeasure/ExecuteLayout`；按兼容路径排查。 |
| Dynamic 与 Static 行为不一致 | 对照 JSView 参数桥接与 ANI 参数桥接，不要跨范式套用实现细节。 |
| 将 DynamicLayout 回调混入自定义组件 | 转到 `LayoutAlgorithm` SDK 和 DynamicLayout KB，确认 API 载体后再继续。 |

## 调试入口

- 先确认调用的是自定义组件 `onMeasureSize` / `onPlaceChildren`，还是 DynamicLayout 的 `CustomLayoutAlgorithm`。
- Dynamic 路径从 `ViewFunctions::ExecuteMeasureSize` 或 `ExecutePlaceChildren` 进入，检查 `JSMeasureLayoutParamNG` 的 self、children 和 constraint 组装。
- Static 路径从 `NativeCustomComponent::ConstructCustomNode` 与 `AniMeasureLayoutParamNG` 进入，检查 ANI 回调和参数包装。
- 原生布局阶段回到 `CustomMeasureLayoutNode` 与 `CustomNodeLayoutAlgorithm`，检查回调分发、子项 wrapper 和默认 Measure/Layout 路径。
- 兼容问题先确认是否仍使用 SDK 已废弃的 `onMeasure` / `onLayout`，再检查对应 JSView 兼容实现与定向测试。

## 相关主题

- [DynamicLayout：`docs/kb/components/container/dynamic-layout.md`](../components/container/dynamic-layout.md)
- [布局框架：`docs/kb/architecture/layout-framework.md`](../architecture/layout-framework.md)
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`