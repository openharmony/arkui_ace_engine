# Basic Render Pipeline Context

> 文档版本：v1.2
> 更新时间：2026-08-04
> 来源：`docs/context_registry.json` 主题 `BasicRenderPipeline`
> 旧 KB 迁移来源：`docs/pattern/pipeline/Pipeline_Knowledge_Base.md`（旧 KB 位置，已迁移）

## 定位

基础渲染管线是 ArkUI 引擎从 VSync 信号到 RS 提交的帧编排基础设施，涵盖 NG 管线一帧主编排（FlushVsync 14+ 子阶段硬序列、dirty 四条队列、UITaskScheduler Layout+Render 驱动、RS SendMessages 单点提交、VSync 合并与后台门控）以及旧管线三层架构（Component→Element→RenderNode）的兼容性边界。NG 管线为推荐路径，旧管线仅用于 FA 模型兼容。它不是对外公共 API，而是引擎内部渲染架构。

本文档只提供稳定的源码、测试和 Spec 路由。具体帧编排子阶段顺序、dirty 标记语义、兼容性边界条件应回到当前源码、测试与相关 Spec 核实。

## 快速路由

### 源码入口

#### NG 管线

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 主管线编排 | `frameworks/core/pipeline_ng/pipeline_context.h` | NG::PipelineContext::FlushVsync 一帧主编排；14+ 子阶段硬序列（ADR-1） |
| 任务调度器 | `frameworks/core/pipeline_ng/ui_task_scheduler.h` | UITaskScheduler；dirtyLayoutNodes_/dirtyRenderNodes_；FlushTask do-while ≤2（ADR-2） |
| 帧节点 | `frameworks/core/components_ng/base/frame_node.h` | FrameNode 生命周期/MarkDirtyNode/Measure/Layout/Paint 入口 |
| Paint 分发 | `frameworks/core/components_ng/render/paint_wrapper.h` | PaintWrapper::FlushRender；Modifier vs Draw fallback 分发（ADR-5） |
| Rosen 渲染适配 | `frameworks/core/components_ng/render/adapter/rosen_window.h` | NG::RosenWindow；VSync 接收/RequestFrame 合并/帧超时/SendMessages（ADR-3/6） |
| Rosen 渲染上下文 | `frameworks/core/components_ng/render/adapter/rosen_render_context.h` | NG RenderContext 与 RSNode 桥接；StartRecording/FinishRecording |
| Window 抽象 | `frameworks/core/common/window.h` | Window 接口抽象；callbacks_ 多容器 VSync 扇出 |
| PipelineBase 基类 | `frameworks/core/pipeline/pipeline_base.h` | 主管线/子管线公共基类；isSubPipeline_/parentPipeline_ 标记；Vsync/事件/资源管理 |
| CustomNode Build | `frameworks/core/components_ng/pattern/custom/custom_node_base.h` | CustomNode rebuild/MarkNeedUpdate；FlushDirtyNodeUpdate 入队边界 |

#### 旧管线（兼容性参考）

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 旧 PipelineContext | `frameworks/core/pipeline/pipeline_context.h` | 旧管线帧编排：PushPage/PopPage/FlushVsync/FlushLayout/FlushRender/FlushAnimation |
| Component 基类 | `frameworks/core/pipeline/base/component.h` | 声明层基类；不可变配置；CreateElement 接口 |
| Element 基类 | `frameworks/core/pipeline/base/element.h` | 逻辑层基类；Mount→Activate→Deactivate→Detach 生命周期 |
| RenderNode 基类 | `frameworks/core/pipeline/base/render_node.h` | 渲染层基类；布局/绘制/触摸测试/RSNode 同步 |
| RenderElement | `frameworks/core/pipeline/base/render_element.h` | 渲染元素；持有 RenderNode |
| ComposedElement | `frameworks/core/pipeline/base/composed_element.h` | 组合元素；管理子 Element 树；RenderFunction |
| RosenRenderContext（旧） | `frameworks/core/pipeline/base/rosen_render_context.h` | 旧管线 Rosen 后端渲染上下文实现 |
| WindowManager | `frameworks/core/pipeline/container_window_manager.h` | 旧管线窗口管理器；窗口操作/系统栏/视口配置 |
| Layer 系统 | `frameworks/core/pipeline/layers/layer.h` | Flutter 渲染后端 Layer 抽象 |
| RenderSubContainer | `frameworks/core/pipeline/base/render_sub_container.h` | 旧管线子容器桥接；GetSubPipelineContext |
| ElementRegister | `frameworks/core/pipeline/base/element_register.h` | 元素注册表；增量更新 ID 管理 |

### API 入口

基础渲染管线是引擎内部能力，没有独立 SDK API。NG 管线由 FrameNode+Pattern+Modifier 驱动，旧管线由 JSView→Component→Element→RenderNode 桥接驱动，均不在公共 API 列表中。

### NG 管线帧编排概览

```
FlushVsync(nano, frameCount):
  FlushAnimation → FlushModifierAnimation
  FlushTouchEvents / FlushDragEvents
  FlushBuild → FlushDirtyNodeUpdate (dirtyPropertyNodes_ + dirtyNodes_ ×≤3)
  taskScheduler_->FlushTask (Layout+Render do-while ≤2)
  FlushModifier / FlushFrameRate
  FlushMessages → SendMessages (RS 唯一提交点)
  FlushAfterRenderTask / FlushVsync / A11y
```

关键架构规则（锁定于 design.md ADR）：
- ADR-1: FlushVsync 子阶段固定硬序列，不可动态调整
- ADR-2: Layout+Render 由 UITaskScheduler::FlushTask 统一驱动，ENDORSE_LAYOUT_COUNT=2
- ADR-3: RequestFrame 用 isRequestVsync_ 自合并，后台 !onShow_ 整体跳过
- ADR-4: dirty 四条队列（dirtyPropertyNodes_/dirtyNodes_/dirtyLayoutNodes_/dirtyRenderNodes_）分级收集
- ADR-5: Paint 优先 Modifier 路径，缺失时回退 Draw 录制
- ADR-6: RS 状态变更仅在 FlushMessages→SendMessages 单点提交

### 旧管线三层架构对照（兼容性参考）

| 层 | 基类 | 不可变性 | 职责 | NG 对应 |
|----|------|---------|------|---------|
| 声明层 | Component | 不可变配置 | 描述外观和行为 | 无直接对应（NG 由 Pattern+Property 替代） |
| 逻辑层 | Element | 可变状态 | 生命周期/子元素/状态管理 | FrameNode（合并逻辑+渲染） |
| 渲染层 | RenderNode | 渲染单元 | 布局/绘制/RSNode 同步 | FrameNode + RenderContext |

旧管线帧流水线：`VSync → FlushVsync → FlushAnimation → FlushLayout → FlushRender → FlushRenderFinish → SendMessages`。脏节点按深度排序（NodeCompare），旧管线使用 dirtyElements_/dirtyRenderNodes_/dirtyLayoutNodes_ 三个 set 管理。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| Rosen 渲染服务 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`, `rosen_window.cpp` | `foundation/graphic/graphic_2d` | RSUIDirector IPC；RSNode 创建/SyncGeometryProperties/SendMessages |
| Rosen 窗口 | `frameworks/core/components_ng/render/adapter/rosen_window.cpp` | `foundation/graphic/graphic_2d`, `foundation/window_manager` | VSync 回调注册/RequestFrame/帧超时 DFX |
| Rosen 渲染服务（旧管线） | `frameworks/core/pipeline/base/rosen_render_context.cpp` | `foundation/graphic/graphic_2d` | 旧管线 RSNode 创建/SyncGeometryProperties |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| NG PipelineContext 测试 | `test/unittest/core/pipeline/pipeline_context_test_ng.cpp` | NG 管线帧编排回归（FlushVsync/FlushBuild/FlushMessages） |
| 旧管线 PipelineContext 测试 | `test/unittest/core/pipeline/pipeline_context_test_ng.cpp` | 含旧管线兼容回归 |
| MockRenderContext | `test/unittest/core/pipeline/mock_rosen_render_context.cpp` | RenderContext 测试替身 |
| FrameNode 测试 | `test/unittest/core/base/frame_node_test_ng.cpp` | FrameNode dirty/Measure/Layout/几何回归 |
| UITaskScheduler Mock | `test/mock/frameworks/core/pipeline_ng/mock_ui_task_scheduler.cpp` | UITaskScheduler 测试替身 |
| Rosen Window 测试 | `test/unittest/adapter/ohos/entrance/rs_adapter_test.cpp` | Rosen 渲染窗口适配 |

### 相关 Spec

基础渲染管线功能域：`specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/`（功能 ID `03-01-01`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 渲染主流程规格 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-01-render-main-flow-spec.md` | FlushVsync 14+ 子阶段顺序、dirty 四条队列、RS 提交边界、VSync 合并、后台门控 |
| 设计文档 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/design.md` | NG 管线一帧主编排、ADR-1~6、VSync 接收与帧合并、Build/Layout/Render/RS 提交详细设计 |

兼容性边界在以下 Spec 中记录：

| 文档 | 稳定路径 | 涉及旧管线的范围 |
|------|----------|------------------|
| 平台抽象规格 | `specs/02-cross-platform/01-platform-adapter/01-oh-platform-adapter/Feat-01-platform-abstraction-build-spec.md` | PlatformWindow::Create → 旧管线 RSWindow 路径 |
| 路由栈恢复规格 | `specs/04-common-capability/07-migration-recovery/02-router-stack-recovery/Feat-01-router-stack-save-restore-spec.md` | FA 旧管线路由栈简化序列化 |
| 多级渲染管线规格 | `specs/03-engine-framework/01-render-pipeline/02-multi-level-render-pipeline/Feat-01-sub-pipeline-multi-container-vsync-coordination-spec.md` | 旧管线 SubContainer 进程内子管线 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| NG 帧编排顺序错误 | PipelineContext::FlushVsync 硬序列（ADR-1）；Spec Feat-01 AC-2.1 |
| dirty 节点未进入 Layout/Render | 四条 dirty 队列分级；MarkDirtyNode→AddDirtyLayoutNode/AddDirtyRenderNode |
| Build 后节点未进入当帧 Layout | FlushBuild 必先于 FlushTask（ADR-1）；否则新节点延入下一帧 |
| Layout 二次触发延入下一帧 | ENDORSE_LAYOUT_COUNT=2（ADR-2）；超出后 RequestFrameOnLayoutCountExceeds |
| RS 状态未提交 | FlushMessages→SendMessages 单点（ADR-6）；之后修改进入下一帧 |
| 后台窗口浪费 VSync | RequestFrame !onShow_ 门控（ADR-3）；ForceFlushVsync 500ms 兜底 |
| FA 模型页面渲染异常 | 旧管线 PipelineContext FlushVsync→FlushLayout→FlushRender |
| 旧管线组件更新不生效 | Element::UpdateChild→RenderNode::Update→MarkNeedLayout/MarkNeedRender |
| 旧管线触摸事件不命中 | RenderNode::TouchTest→InTouchRectList→递归子节点→OnTouchTestHit |

## 调试入口

- NG 帧编排断点：PipelineContext::FlushVsync → 14+ 子阶段依次执行
- NG dirty 链路断点：FrameNode::MarkDirtyNode → AddDirtyPropertyNode/AddDirtyLayoutNode/AddDirtyRenderNode
- NG RS 提交断点：FlushMessages → RosenWindow::FlushTasks → rsUIDirector_->SendMessages
- NG VSync 合并断点：RosenWindow::RequestFrame → isRequestVsync_ 自合并 → rsWindow_->RequestVsync
- 旧管线帧编排断点：PipelineContext::OnVsyncEvent → FlushVsync → FlushAnimation → FlushLayout → FlushRender
- 旧管线脏链路断点：Element→AddDirtyElement / RenderNode→AddDirtyRenderNode/AddDirtyLayoutNode
- 旧管线 RSNode 同步断点：RenderNode::SyncGeometryProperties → RosenRenderContext → RSNode

## 相关主题

- NG 布局框架：`docs/kb/architecture/layout-framework.md`（FrameNode/LayoutWrapper/LayoutAlgorithm/GeometryNode 细节）
- [多级渲染管线：`docs/kb/architecture/multi-level-render-pipeline.md`（子管线与多容器 VSync 协调）](multi-level-render-pipeline.md)
- OH 平台适配层：`docs/kb/architecture/oh-platform-adapter.md`（Container/AceContainer/RosenWindow）
- [编译构建：`docs/kb/architecture/build-system.md`（旧管线 vs NG 管线构建选择）](build-system.md)
- [窗口机制：`docs/kb/architecture/window-mechanism.md`（Rosen Window 窗口管理）](window-mechanism.md)
- [渲染树同步](render-tree-sync.md) — RebuildRenderContextTree 的同步触发与 FlushVsync 内延迟合并执行路径
- [同帧下树重新上树 isPendingState_ 状态错乱](../issues/lifecycle/ispending-state-render-tree-diff.md) — isPendingState_ 同帧下树重新上树问题型 KB