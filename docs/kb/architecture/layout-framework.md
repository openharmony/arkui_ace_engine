# Layout Framework Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `LayoutFramework`

## 定位

Layout Framework 是 ArkUI NG（`components_ng` + `pipeline_ng`）中负责布局任务收集与调度、节点测量和放置、布局约束传递、几何结果保存及渲染上下文同步的内部框架。它不是独立的应用侧组件，也不直接定义一套公共 API；组件公共布局属性和各组件布局算法在此框架上运行。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体阶段顺序、更新标记语义、兼容性和边界条件应回到当前源码、测试与相关 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 一帧管线编排 | `frameworks/core/pipeline_ng/pipeline_context.cpp`、`frameworks/core/pipeline_ng/pipeline_context.h` | 从 `PipelineContext::FlushVsync`、`FlushUITasks`、`AddDirtyLayoutNode` 定位布局任务进入整帧管线的位置 |
| 布局任务调度 | `frameworks/core/pipeline_ng/ui_task_scheduler.cpp`、`frameworks/core/pipeline_ng/ui_task_scheduler.h` | `UITaskScheduler` 收集 dirty layout node，驱动布局、附加布局、几何同步和后布局任务 |
| 节点布局执行 | `frameworks/core/components_ng/base/frame_node.cpp`、`frameworks/core/components_ng/base/frame_node.h` | `FrameNode` 的 dirty 标记、`CreateLayoutTask`、`Measure`、`Layout`、布局完成和几何同步入口 |
| 布局包装抽象 | `frameworks/core/components_ng/layout/layout_wrapper.h`、`frameworks/core/components_ng/layout/layout_wrapper.cpp` | `LayoutWrapper` 抽象、约束应用及布局过程共享数据入口 |
| NG 布局包装实现 | `frameworks/core/components_ng/layout/layout_wrapper_node.cpp`、`frameworks/core/components_ng/layout/layout_wrapper_node.h` | `LayoutWrapperNode` 对布局算法的 Measure/Layout 分发以及跳过、强制布局判断 |
| 布局算法抽象 | `frameworks/core/components_ng/layout/layout_algorithm.cpp`、`frameworks/core/components_ng/layout/layout_algorithm.h` | `LayoutAlgorithm` 与 `LayoutAlgorithmWrapper` 基础接口和包装逻辑 |
| 通用盒布局 | `frameworks/core/components_ng/layout/box_layout_algorithm.cpp`、`frameworks/core/components_ng/layout/box_layout_algorithm.h` | 通用子节点测量和放置算法入口；组件专属算法仍应进入对应 pattern 目录查看 |
| 布局属性与约束 | `frameworks/core/components_ng/layout/layout_property.cpp`、`frameworks/core/components_ng/layout/layout_property.h` | `LayoutProperty` 的约束更新、子约束生成、通用布局属性存储和更新标记入口 |
| 更新标记定义 | `frameworks/core/components_ng/property/property.h` | 检索 `PROPERTY_UPDATE_MEASURE`、`PROPERTY_UPDATE_LAYOUT` 及相关组合标记 |
| 几何结果 | `frameworks/core/components_ng/base/geometry_node.cpp`、`frameworks/core/components_ng/base/geometry_node.h` | `GeometryNode` 保存 frame/content 的尺寸、偏移及布局结果 |
| 渲染同步抽象 | `frameworks/core/components_ng/render/render_context.h` | `RenderContext::SyncGeometryProperties`、`SavePaintRect` 等几何同步接口 |
| Rosen 渲染适配 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`、`frameworks/core/components_ng/render/adapter/rosen_render_context.h` | 布局几何结果到 Rosen/RenderService 节点属性的适配入口 |

建议按问题使用类型名或方法名检索，不依赖行号：

| 问题阶段 | 优先检索 |
|----------|----------|
| dirty 节点没有进入布局 | `MarkDirtyNode`、`AddDirtyLayoutNode`、`dirtyLayoutNodes_` |
| 布局任务没有执行 | `FlushUITasks`、`FlushTaskWithCheck`、`FlushLayoutTask`、`CreateLayoutTask` |
| 测量结果异常 | `FrameNode::Measure`、`LayoutWrapperNode::Measure`、`CreateChildConstraint` |
| 放置结果异常 | `FrameNode::Layout`、`LayoutWrapperNode::Layout`、组件 `*LayoutAlgorithm::Layout` |
| 几何结果未反映到渲染 | `OnLayoutFinish`、`AddSyncGeometryNodeTask`、`SyncGeometryNode`、`SyncGeometryProperties` |
| 布局发生附加轮次 | `NeedAdditionalLayout`、`FlushTaskWithCheck`、`RequestFrameOnLayoutCountExceeds` |

### API 入口

Layout Framework 本身是引擎内部机制，没有独立 SDK API。应用侧公共布局属性从下列 SDK 声明进入，再由前端桥接和组件 Model 写入布局属性；属性语义和 API 版本以 SDK 声明为准。

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 公共属性 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 公共组件属性声明；可按 `width`、`height`、`layoutWeight`、`alignSelf` 等具体属性名检索 |
| Static 公共属性 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS 公共组件属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | 动态 Modifier 公共属性声明 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 静态 Modifier 公共属性声明 |

公共属性从前端到 `LayoutProperty` 的解析路径属于“基础布局属性”主题；排查某个具体组件时，还应进入该组件的 Model、bridge/node modifier 和 `*LayoutProperty`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| Rosen / RenderService | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`、`frameworks/core/components_ng/render/adapter/rosen_render_context.h` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/`、`rosen/modules/render_service_base/include/` | `FrameNode` 完成布局后经 `RenderContext` 抽象同步几何属性，Rosen 适配层持有并更新 RS 节点 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 布局框架单元测试 | `test/unittest/core/layout/` | `LayoutProperty`、`LayoutWrapper`、`LayoutAlgorithm`、BoxLayout、像素取整、溢出和安全区等回归 |
| FrameNode 单元测试 | `test/unittest/core/base/frame_node_test_ng*.cpp` | 节点 dirty、Measure/Layout、几何和生命周期相关回归 |
| 几何节点单元测试 | `test/unittest/core/base/geometry_node_test_ng.cpp` | `GeometryNode` 尺寸、偏移和几何数据回归 |
| 布局约束单元测试 | `test/unittest/core/property/layout_constraint_test_ng.cpp` | `LayoutConstraint` 基础数据和约束行为回归 |
| 调度器 Mock | `test/mock/frameworks/core/pipeline_ng/mock_ui_task_scheduler.cpp` | 依赖 `UITaskScheduler` 的测试替身入口 |
| Context registry | `docs/context_registry.json` | `LayoutFramework` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

基础渲染管线功能域：`specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/`（功能 ID `03-01-01`）。

| 文档 | 稳定路径 | 与布局框架的关系 |
|------|----------|------------------|
| 主流程规格 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-01-render-main-flow-spec.md` | 覆盖 VSync、Build、Layout/Render 主编排以及 `UITaskScheduler`、`FrameNode` 的阶段边界 |
| 设计文档 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/design.md` | 记录基础渲染管线的模块边界和架构决策 |

布局框架内部算法、基础布局属性及具体组件算法不由该 Spec 全量定义，应继续路由到对应能力或组件功能域。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 属性变化后没有重新测量 | SDK 公共属性声明、属性解析写入点、`LayoutProperty` 更新标记、`FrameNode::MarkDirtyNode` |
| 子节点约束或尺寸异常 | `LayoutProperty::UpdateLayoutConstraint`、`CreateChildConstraint`、父组件布局算法的 Measure 入口 |
| 节点尺寸正确但位置异常 | 组件布局算法的 Layout 入口、`GeometryNode` frame offset、父节点的子节点放置逻辑 |
| Measure/Layout 被跳过 | `LayoutAlgorithmWrapper` 和 `LayoutWrapperNode` 的 skip/force 判断、节点 property change flag |
| 布局后界面仍未更新 | `FrameNode::OnLayoutFinish`、同步几何任务、`RenderContext::SyncGeometryProperties` |
| 同一帧出现额外布局 | `UITaskScheduler::NeedAdditionalLayout`、布局期间新增 dirty node、geometry transition 相关入口 |
| 安全区导致约束或位置变化 | `docs/layout/Safe_Area_Mechanism_Knowledge_Base.md` 与 `docs/layout/Ignore_Layout_Safe_Area_Knowledge_Base.md`；再回到 `test/unittest/core/layout/safe_area/` |
| 某个组件的布局结果异常 | 先看该组件的 `*LayoutProperty`、`*LayoutAlgorithm` 和 pattern 测试，不要只停留在通用框架 |

## 调试入口

- 在 trace 中检索 `UITaskScheduler::FlushTask`、`FlushSyncGeometryNodeTasks`、Measure/Layout 相关节点标签，确认问题发生在任务收集、测量、放置还是几何同步阶段。
- 节点现场优先查看 `FrameNode` dump 中的 `FrameRect`、`ParentLayoutConstraint`、布局约束、padding、safe area、align rules 和 LayoutInfo。
- dirty 链路从具体属性写入点开始，依次核对 property change flag、`MarkDirtyNode`、`AddDirtyLayoutNode` 和调度器 dirty 集合。
- 约束问题同时记录父约束、当前节点 layout constraint、content constraint 和组件算法生成的 child constraint。
- 通用框架回归优先运行 `test/unittest/core/layout/` 或 `test/unittest/core/base/` 下的定向用例；组件问题运行对应 pattern 目录测试。

## 相关主题

- 基础渲染管线 Spec：`specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/`
- 安全区域机制：`docs/layout/Safe_Area_Mechanism_Knowledge_Base.md`
- 忽略布局安全区机制：`docs/layout/Ignore_Layout_Safe_Area_Knowledge_Base.md`
- 基础布局属性 Spec：`specs/04-common-capability/03-common-attributes/01-layout-attributes/`
- 组件布局算法：`frameworks/core/components_ng/pattern/<component>/`
