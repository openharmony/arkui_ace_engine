# 同帧下树重新上树 isPendingState_ 状态错乱 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `IsPendingStateRenderTreeDiff`
> 关联功能域：03-01-01

## 问题概述

FrameNode::ProcessRenderTreeDiff 中将父节点的 isPendingState_ 作为 isOnMainTree 参数传递给子节点的 AttachToRenderTree/DetachFromRenderTree，当节点在同一帧中从旧父节点下树后重新上树到新父节点时，isPendingState_ 状态值与实际渲染树状态不一致，导致生命周期回调错调或漏调，以及 ImagePattern::OnWindowHide 中 RecycleImageData 误触。

典型表现：
- Image 节点在同一帧下树重新上树后，OnWindowHide 中 IsPendingOnMainRenderTree() 返回 false，导致 RecycleImageData 误触、图片数据被回收
- OnAttachToMainRenderTree/OnDetachFromMainRenderTree 生命周期回调在同一帧下树重新上树时漏调或错调
- 节点实际仍在渲染树上，但 isPendingState_ 为 false，后续状态判断失准


## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | frame_node | frameworks/core/components_ng/base/frame_node.cpp | verified |
| capability | root_cause_owner | image_pattern | frameworks/core/components_ng/pattern/image/image_pattern.cpp | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 父节点 isPendingState_ 作为 isOnMainTree 传递导致同帧移动时状态错乱 | 节点在同一帧中从旧父节点移到新父节点，且新父节点 ProcessRenderTreeDiff 先于旧父节点执行 | 节点 A 在同一帧中从 ParentA 移到 ParentB，ParentB 的 RebuildRenderContextTree 先执行 |
| AttachToRenderTree 因 isPendingState_=true 而 early return | 节点已上树（isPendingState_=true），新父节点 ProcessRenderTreeDiff 尝试 AttachToRenderTree 时因子节点 isPendingState_ 已为 true 而 early return | 节点移动到新父节点时，OnAttachToMainRenderTree 未被调用 |
| 旧父节点 DetachFromRenderTree 错误清除 isPendingState_ | 旧父节点 ProcessRenderTreeDiff 后执行，调用 DetachFromRenderTree 时将已在新父节点上的子节点的 isPendingState_ 设为 false | 节点已在新父节点渲染树上，但旧父节点 DetachFromRenderTree 将 isPendingState_ 设为 false |

## 排查路径

### 快速判断

1. 检查 Image 节点在同一帧中是否发生了父节点变更（如条件渲染、列表项移动等）
2. 检查 ImagePattern::OnWindowHide 中 RecycleImageData 是否被意外调用
3. 检查 FrameNode::IsPendingOnMainRenderTree() 返回值是否与节点实际渲染树状态一致
4. 检查 OnAttachToMainRenderTree/OnDetachFromMainRenderTree 是否被漏调或错调

### 详细排查

#### 父节点 isPendingState_ 传递导致同帧移动时状态错乱 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 ProcessRenderTreeDiff 中打断点或加日志，观察 AttachToRenderTree 和 DetachFromRenderTree 的调用时序 | 新父节点先 Attach，旧父节点后 Detach | 确认时序颠倒导致 isPendingState_ 错乱 |
| 2 | 检查子节点在 AttachToRenderTree 被调用时 isPendingState_ 的值 | 如果子节点 isPendingState_ 已为 true，则 AttachToRenderTree 会 early return | 确认 early return 导致 OnAttachToMainRenderTree 漏调 |
| 3 | 检查旧父节点 DetachFromRenderTree 被调用时子节点 isPendingState_ 的值 | 子节点 isPendingState_ 为 true，DetachFromRenderTree 会执行并设为 false | 确认 isPendingState_ 被错误清除 |
| 4 | 检查子节点最终 isPendingState_ 值与实际渲染树状态 | 节点实际在渲染树上，但 isPendingState_ 为 false | 确认根因 |

关键代码定位：
- `frameworks/core/components_ng/base/frame_node.cpp:3358`（ProcessRenderTreeDiff → AttachToRenderTree 调用点）
- `frameworks/core/components_ng/base/frame_node.cpp:3365`（ProcessRenderTreeDiff → DetachFromRenderTree 调用点）
- `frameworks/core/components_ng/base/frame_node.cpp:3396`（AttachToRenderTree 中 isPendingState_ 早退守卫）
- `frameworks/core/components_ng/base/frame_node.cpp:3379`（DetachFromRenderTree 中 isPendingState_ 清除点）
- `frameworks/core/components_ng/pattern/image/image_pattern.cpp:1759`（ImagePattern::OnWindowHide 中依赖 IsPendingOnMainRenderTree() 的回收判断）

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 父节点 isPendingState_ 作为 isOnMainTree 传递 | ProcessRenderTreeDiff 中恢复使用 renderContext_->IsOnRenderTree() 或使用子节点自身的渲染树状态判断 | frame_node.cpp:3358,3365 | 待修复 | 7e9278af335 将 renderContext_->IsOnRenderTree() 改为 isPendingState_，引入了此问题 |
| AttachToRenderTree early return 逻辑 | 当节点从旧父节点移到新父节点时，应先 Detach 再 Attach，或允许 Attach 在 isPendingState_=true 时仍执行 | frame_node.cpp:3394-3409 | 待修复 | 03889ac01dc 引入 isPendingState_ 替代 renderContext_->IsOnRenderTree() 检查 |
| DetachFromRenderTree 错误清除 | DetachFromRenderTree 应检查节点是否仍在渲染树上（如仍在新父节点的 frameChildren_ 中），避免错误清除 | frame_node.cpp:3377-3392 | 待修复 | 03889ac01dc 引入 isPendingState_ 作为唯一状态标记 |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 03889ac01dc refineImageRecycle：引入 isPendingState_、CleanRenderTreeLifeCycle、AttachToRenderTree/DetachFromRenderTree 的 isPendingState_ 替代逻辑 | 父节点 isPendingState_ 传递 | introduced | git show 03889ac01dc：将 AttachToRenderTree/DetachFromRenderTree 从 renderContext_->IsOnRenderTree() 改为 isPendingState_ 内部状态标记 | verified |
| CHG-02 | 7e9278af335 refineFrameNodeInRenderTree：ProcessRenderTreeDiff 中将 renderContext_->IsOnRenderTree() 改为 isPendingState_ | 父节点 isPendingState_ 传递 | introduced | git show 7e9278af335：-bool isOnMainTree = renderContext_->IsOnRenderTree(); +item->AttachToRenderTree(isPendingState_); | verified |
| CHG-03 | 86677e32d33 refineImageRecycleProcess：引入 ProcessRenderTreeDiff、AttachToRenderTree、DetachFromRenderTree 等方法声明 | 父节点 isPendingState_ 传递 | introduced | git show 86677e32d33：初始方法声明 | verified |

## 预防措施

- ProcessRenderTreeDiff 中传递给子节点的 isOnMainTree 参数应反映子节点实际所属渲染树的状态，而非父节点的逻辑标记
- AttachToRenderTree/DetachFromRenderTree 的 early return 逻辑应考虑节点在同帧中的状态变化（如先 Detach 再 Attach），避免使用单一布尔标记追踪多父节点场景
- 新增 isPendingState_ 相关逻辑时，需补充同帧下树重新上树的测试用例覆盖

## 相关主题

- [渲染树同步](../../architecture/render-tree-sync.md) — 渲染树同步机制代码型 KB，覆盖 ProcessRenderTreeDiff 全链路
- [基础渲染管线](../../architecture/basic-render-pipeline.md) — FlushVsync 编排，RebuildRenderContextTree 在 FlushTask 阶段执行
- [布局框架](../../architecture/layout-framework.md) — FrameNode Measure/Layout，与渲染树同步在帧编排中的位置
- [FrameNode](../../capabilities/frame-node.md) — ArkTS FrameNode API，C++ 底层能力提供者
- [RenderNode](../../capabilities/render-node.md) — RenderNode 绘制节点，与 FrameNode 共享 RS 节点树重建机制
- [Image](../../components/media/image.md) — ImagePattern::OnAttachToMainRenderTree 和 OnWindowHide 依赖 isPendingState_，受已知缺陷影响
- [转场动画](../../capabilities/transition-animation.md) — TransitionEffect 的转出动画通过 HasTransitionOutAnimation 影响可见子节点收集
- [共享元素动画](../../capabilities/geometry-transition.md) — GeometryTransition 触发二次布局和 isDeleteRsNode_ 传播