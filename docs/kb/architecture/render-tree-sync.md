# Render Tree Sync Context

> 文档版本：v1.1
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `RenderTreeSync`

## 定位

渲染树同步（Render Tree Sync）是 ArkUI NG 引擎中负责将逻辑节点树（UINode/FrameNode）的可见性、Z 序和挂载状态变更同步到 RS 渲染节点树的内部机制。核心链路为 `MarkNeedSyncRenderTree` → `RebuildRenderContextTree` → `ProcessRenderTreeDiff` → `RenderContext::RebuildFrame`，并维护 `isPendingState_` 标记跟踪节点的渲染树上下树生命周期配对。

本文档只提供稳定的源码、测试和 Spec 路由。具体状态标记语义、时序约束和边界条件应回到当前源码、测试与相关 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **同步主流程** | `frameworks/core/components_ng/base/frame_node.cpp` | `RebuildRenderContextTree`、`ProcessRenderTreeDiff`、`AttachToRenderTree`、`DetachFromRenderTree` |
| **脏标记传播** | `frameworks/core/components_ng/base/frame_node.cpp`、`ui_node.cpp` | `MarkNeedSyncRenderTree`、`needSyncRenderTree_` |
| **可见子节点收集** | `frameworks/core/components_ng/base/ui_node.cpp`、`frame_node.cpp` | `GenerateOneDepthVisibleFrameWithTransition`、`OnGenerateOneDepthVisibleFrameWithTransition` |
| **Z 序排序** | `frameworks/core/components_ng/base/frame_node.h` | `ZIndexComparator`、`frameChildren_` multiset |
| **RS 节点树重建** | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `RebuildFrame`、`ReCreateRsNodeTree`、`ReCreateMixedRsNodeTree`、`ReCreateRsNodeTreeByTargetList` |
| **isPendingState_ 生命周期** | `frameworks/core/components_ng/base/frame_node.h`、`frame_node.cpp` | `isPendingState_`、`IsPendingOnMainRenderTree()`、`CleanRenderTreeLifeCycle` |
| **Pattern 生命周期回调** | `frameworks/core/components_ng/pattern/pattern.h` | `OnAttachToMainRenderTree`/`OnDetachFromMainRenderTree` 虚函数；ImagePattern 唯一 override（`image_pattern.cpp`） |
| **渲染状态监控** | `frameworks/core/components_ng/base/node_render_status_monitor.cpp` | `NodeRenderStatusMonitor`：注册回调、祖先遍历状态判断、节点释放通知 |
| **多线程变体** | `frameworks/core/components_ng/base/frame_node_multi_thread.cpp` | `RebuildRenderContextTreeMultiThread`：投递到 UI 线程 |

### 同步链路检索提示

按问题阶段使用方法名或标记名检索，不依赖行号：

| 问题阶段 | 优先检索 |
|----------|----------|
| 子节点增删后 RS 节点未同步 | `MarkNeedSyncRenderTree`、`needSyncRenderTree_`、`RebuildRenderContextTree` |
| 同帧下树重新上树后 isPendingState_ 错误 | `ProcessRenderTreeDiff`、`AttachToRenderTree`、`DetachFromRenderTree`、`isPendingState_` |
| 生命周期回调未触发 | `AttachToRenderTree`、`DetachFromRenderTree`、`OnAttachToMainRenderTree`、`OnDetachFromMainRenderTree` |
| RS 节点树重建不生效 | `isNeedRebuildRSTree_`、`ReCreateRsNodeTreeByTargetList` |
| 转场动画中节点不在可见列表 | `GenerateOneDepthVisibleFrameWithTransition`、`HasTransitionOutAnimation`、`disappearingChildren_` |
| Z 序不正确 | `ZIndexComparator`、`frameChildren_`、`GetZIndexValue` |
| 节点销毁时 isPendingState_ 未清理 | `CleanRenderTreeLifeCycle`、`~FrameNode` |

### 关键状态标记

| 标记 | 所属类 | 用途 |
|------|--------|------|
| `needSyncRenderTree_` | `FrameNode` | 脏标记：`MarkNeedSyncRenderTree` 设置，`RebuildRenderContextTree` 清除 |
| `isPendingState_` | `FrameNode` | 节点是否已上树等待配对下树。`AttachToRenderTree` 设 true，`DetachFromRenderTree` 设 false。根节点构造时初始化为 true |
| `isDeleteRsNode_` | `FrameNode` | RS 节点是否被删除优化。若 true，触发父节点重新同步 |
| `isNeedRebuildRSTree_` | `RenderContext` | 控制 `ReCreateRsNodeTree` 是否实际重建 RS 树 |

### API 入口

渲染树同步是引擎内部机制，没有独立 SDK API。应用侧通过组件树操作（添加/移除子节点、条件渲染、列表增删等）间接触发。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| Rosen / RenderService | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/`、`rosen/modules/render_service_base/include/` | `RebuildFrame` → `ReCreateRsNodeTree` → RS 节点树 diff-and-rebuild；`ReCreateRsNodeTreeByTargetList` 调用 `rsNode_->AddChild`/`RemoveChildByNodeSelf`/`MoveChild` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| RebuildRenderContextTree 测试 | `test/unittest/core/base/frame_node_test_ng_coverage.cpp` | needSyncRenderTree_ 守卫、overlayNode_ 可见性 |
| 基础 Rebuild 测试 | `test/unittest/core/base/frame_node_test_ng.cpp` | needSyncRenderTree_ 重置、overlayNode_ 分支 |
| 多线程变体测试 | `test/unittest/core/base/thread_safe_node_test_ng.cpp` | PostAfterAttachMainTreeTask |
| 渲染状态监控测试 | `test/unittest/core/base/node_render_status_monitor_test_ng.cpp` | 注册/遍历/释放/状态判断 |
| ImagePattern 生命周期测试 | `test/unittest/core/pattern/image/image_pattern_test_ng.cpp` | OnAttachToMainRenderTree |

**测试缺口**：`ProcessRenderTreeDiff`、`AttachToRenderTree`、`DetachFromRenderTree`、`CleanRenderTreeLifeCycle` 无直接单元测试覆盖。同帧下树重新上树场景无测试。

### 相关 Spec

渲染管线功能域：`specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/`（功能 ID `03-01-01`）。

| 文档 | 稳定路径 | 与渲染树同步的关系 |
|------|----------|------------------|
| 渲染主流程规格 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-01-render-main-flow-spec.md` | 覆盖 FlushVsync 编排，RebuildRenderContextTree 在 FlushTask 阶段执行 |
| 渲染树同步规格 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-02-render-tree-sync-spec.md` | 覆盖 MarkNeedSyncRenderTree→RebuildRenderContextTree→ProcessRenderTreeDiff 全链路，isPendingState_ 生命周期约束 |
| 设计文档 | `specs/03-engine-framework/01-render-pipeline/01-basic-render-pipeline/design.md` | 记录基础渲染管线的模块边界和架构决策 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 子节点增删后 RS 节点未同步 | `MarkNeedSyncRenderTree` 是否被调用、`needSyncRenderTree_` 是否被设置、`RebuildRenderContextTree` 是否在帧 flush 中执行 |
| 子节点 Z 序不正确 | `ZIndexComparator` 排序逻辑、`frameChildren_` multiset 重建时机 |
| 同帧下树重新上树后 isPendingState_ 错误 | `ProcessRenderTreeDiff` 中 `isPendingState_` 作为 `isOnMainTree` 传递的时序问题；参见问题型 KB `docs/kb/issues/lifecycle/ispending-state-render-tree-diff.md` |
| OnAttachToMainRenderTree/OnDetachFromMainRenderTree 未触发 | `AttachToRenderTree`/`DetachFromRenderTree` 的 early return 守卫（isOnMainTree + isPendingState_） |
| 节点销毁时 isPendingState_ 未清理 | `CleanRenderTreeLifeCycle` 在 FrameNode 析构中调用 |
| RS 节点树重建不生效 | `isNeedRebuildRSTree_` 标记、`ReCreateRsNodeTreeByTargetList` 的 diff 逻辑 |
| 转场动画中节点不在可见列表 | `GenerateOneDepthVisibleFrameWithTransition`：不可见节点需有 `HasTransitionOutAnimation` 才会被保留 |

## 调试入口

- `RebuildRenderContextTree` 断点：`frame_node.cpp` 中搜索 `RebuildRenderContextTree`，观察 `needSyncRenderTree_` 和 `frameChildren_` 变化
- `ProcessRenderTreeDiff` 断点：`frame_node.cpp` 中搜索 `ProcessRenderTreeDiff`，观察 Attach/Detach 调用时序
- `isPendingState_` 状态追踪：`AttachToRenderTree` 和 `DetachFromRenderTree` 中的 early return 守卫
- RS 节点树重建断点：`rosen_render_context.cpp` 中搜索 `ReCreateRsNodeTreeByTargetList`
- `NodeRenderStatusMonitor` 断点：`node_render_status_monitor.cpp` 中搜索 `WalkThroughAncestorForStateListener`

## 相关主题

- [基础渲染管线](basic-render-pipeline.md) — FlushVsync 编排，RebuildRenderContextTree 在 FlushTask 阶段执行
- [布局框架](layout-framework.md) — FrameNode Measure/Layout，与渲染树同步在帧编排中的位置
- [FrameNode](../capabilities/frame_node.md) — ArkTS FrameNode API，C++ 底层能力提供者
- [RenderNode](../capabilities/render_node.md) — RenderNode 绘制节点，与 FrameNode 共享 RS 节点树重建机制（MountPolicy::MIXED 路径）
- [Image](../components/media/image.md) — ImagePattern::OnAttachToMainRenderTree 和 OnWindowHide 依赖 isPendingState_，受已知缺陷影响
- [转场动画](../capabilities/transition_animation.md) — TransitionEffect 的转出动画通过 HasTransitionOutAnimation 影响可见子节点收集
- [共享元素动画](../capabilities/geometry_transition.md) — GeometryTransition 触发二次布局和 isDeleteRsNode_ 传播
- [Overlay Capability](../capabilities/overlay-capability.md) — OverlayManager 通过 RebuildRenderContextTree 同步浮层节点
- [同帧下树重新上树 isPendingState_ 状态错乱](../issues/lifecycle/ispending-state-render-tree-diff.md) — isPendingState_ 同帧下树重新上树问题型 KB
