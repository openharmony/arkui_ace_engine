# aboutToDisappear下树屏蔽与组件复用冲突 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `AboutToDisappearUnmountBlockedOnReuse`
> 关联功能域：07-03-01, 04-19-01, 03-02-05

## 问题概述

自定义组件在 `aboutToDisappear` 生命周期中修改状态变量触发子组件下树，但由于动画期间屏蔽下树行为，子组件实际未从树中移除。该组件被复用时新子组件上树，导致旧组件与新组件同时存在，引起内容重叠。

典型表现：
- 页面 A 跳转页面 B 后，页面 B 中复用的组件出现文字/图片重叠
- 仅在涉及转场动画的页面切换场景下复现
- 应用升级 API19 后出现（引入了"自定义组件前端对象删除前移"的性能优化需求）
- 组件在 `aboutToDisappear` 中通过修改状态变量（如 `flg = false`）控制子节点下树时触发


## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| capability | symptom_surface | jsi_view_register_impl_ng | frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register_impl_ng.cpp | verified |
| architecture | root_cause_owner | frame_node | frameworks/core/components_ng/base/frame_node.cpp | verified |
| architecture | root_cause_owner | ui_node | frameworks/core/components_ng/base/ui_node.cpp | verified |
| capability | root_cause_owner | custom_node_base | frameworks/core/components_ng/pattern/custom/custom_node_base.cpp | verified |
| capability | root_cause_owner | pipeline_context | frameworks/core/pipeline_ng/pipeline_context.cpp | verified |
| capability | root_cause_owner | builder_node_ops_accessor | frameworks/core/interfaces/native/implementation/builder_node_ops_accessor.cpp | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 生命周期时序变更导致下树被屏蔽 | `aboutToDisappear` 在 `Clean()` 之前执行，动画期间 `RemoveImmediately()` 返回 false 走 `AddDisappearingChild` | 页面转场动画期间，`aboutToDisappear` 中修改状态变量触发子组件下树 |
| 动画屏蔽下树与复用缓存池冲突 | 组件的子节点滞留在 `disappearingChildren_` 时被回收至缓存池，复用时新子节点上树导致重叠 | `@Reusable` 自定义组件在 `aboutToDisappear` 中修改条件渲染状态后立即被 `FireRecycleSelf` 回收 |
| BuilderNode 内节点结构异常 | BuilderNode 内的组件下树被屏蔽后保留陈旧节点结构，复用时陈旧节点与新节点共存 | BuilderNode 包裹的条件渲染子组件（`if (flg)`）在页面转场时触发下树 |

## 排查路径

### 快速判断

1. 确认问题是否仅在页面转场动画期间复现（非转场场景正常）
2. 确认应用是否在 `aboutToDisappear` 中修改状态变量触发子组件条件渲染变化
3. 确认涉及的组件是否使用了 `@Reusable` / `reuseOrCreateNewComponent` / BuilderNode 复用机制
4. 确认是否升级了 API19 或使用了"自定义组件前端对象删除前移"特性（PR #54006）
5. 检查 `HasTransitionOutAnimation()` 是否为 true（转场动画进行中）

### 详细排查

#### 生命周期时序变更导致下树被屏蔽排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `CleanPageNode` 中确认 `Reset()` 与 `Clean()` 的调用顺序 | `Reset()`（清空 `destroyFunc_`，非插件路径不调用 `FireOnDisappear`）在 `Clean()` 之前 | 若 `Clean()` 先执行，说明未引入 PR #54006 变更 |
| 2 | 在 `aboutToDisappear` 执行后检查子组件是否已从 `children_` 移除 | 子组件仍在 `children_` 中（被屏蔽） | 若已移除，说明动画未进行或不受屏蔽影响 |
| 3 | 检查 `FrameNode::RemoveImmediately` 返回值 | 返回 false（`HasTransitionOutAnimation()` 为 true） | 若返回 true，说明无转场动画，不受屏蔽影响 |
| 4 | 检查 `OnRemoveFromParent` 返回值及后续路径 | 返回 false，走 `AddDisappearingChild` | 若返回 true，说明组件已正常下树 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register_impl_ng.cpp`：`CleanPageNode`，`Reset()`（清空 `destroyFunc_`）在 `Clean()` 之前调用；`FireOnDisappear` 仅在 `PLUGIN_COMPONENT_SUPPORTED` 分支（line 193-197）对 plugin 子容器生效
- `frameworks/core/components_ng/base/frame_node.cpp`：`RemoveImmediately`，`HasTransitionOutAnimation()` 为 true 时返回 false
- `frameworks/core/components_ng/base/ui_node.cpp`：`OnRemoveFromParent`，`RemoveImmediately` 返回 false 时返回 false
- `frameworks/core/components_ng/base/ui_node.cpp`：`Clean`，`OnRemoveFromParent` 返回 false 时走 `AddDisappearingChild` 屏蔽下树
- `frameworks/core/components_ng/pattern/custom/custom_node_base.cpp`：`FireOnDisappear`，调用 `destroyFunc_()` 触发 JS `aboutToDisappear`（仅在插件子容器路径生效）

#### 动画屏蔽下树与复用缓存池冲突排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 确认 `aboutToDisappear` 中的状态变量修改是否触发子组件条件渲染变化 | 触发 `FlushBuild` → `Clean`/`RemoveChild` → `AddDisappearingChild` | 若未触发，说明状态变更未影响渲染树 |
| 2 | 确认组件在 `aboutToDisappear` 后是否被 `FireRecycleSelf` 回收至缓存池 | 组件被 `RecycleManager::Push` 回收，但子节点仍在 `disappearingChildren_` | 若未被回收，说明未使用复用机制 |
| 3 | 确认复用时 `FireRecycleRenderFunc` 是否从缓存池取出组件并重建 | `RecycleManager::Pop` 取出组件，执行 `recycleRenderFunc_()` 重建 | 若未重建，说明复用流程异常 |
| 4 | 确认复用后状态变量（如 `flg = true`）是否触发新子组件上树 | 新子组件 mount 到 `children_`，旧子组件仍在 `disappearingChildren_` | 若两者都在 `children_`，说明屏蔽未生效 |

关键代码定位：
- `frameworks/core/components_ng/pattern/custom/custom_node_base.cpp`：`MarkNeedUpdate`，触发 `AddDirtyCustomNode` 进入脏节点队列
- `frameworks/core/pipeline_ng/pipeline_context.cpp`：`FlushBuild`，重建脏自定义节点，处理 `flg = false`
- `frameworks/core/components_ng/pattern/custom/custom_node_base.cpp`：`FireRecycleSelf`，回收至缓存池（`RecycleManager::Push`）
- `frameworks/core/components_ng/pattern/custom/custom_node_base.cpp`：`FireRecycleRenderFunc`，从缓存池复用（`RecycleManager::Pop`）
- `frameworks/core/components_ng/base/ui_node.cpp`：`AddDisappearingChild`，将子节点设为 `isDisappearing_ = true` 并保留

#### BuilderNode 内节点结构异常排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 确认下树失败的组件是否在 BuilderNode 内 | 在 BuilderNode 内 | 若不在，参考前两个根因排查 |
| 2 | 检查 BuilderNode 的 `IsRootBuilderNode` 标记 | 为 true | 若为 false，说明 BuilderNode 初始化异常 |
| 3 | 确认 BuilderNode 内条件渲染子组件在动画期间是否被屏蔽下树 | 子组件滞留在 `disappearingChildren_`，节点结构未被清理 | 若已清理，说明不受影响 |
| 4 | 确认复用后 BuilderNode 内是否同时存在新旧子组件 | `children_` 有新组件，`disappearingChildren_` 有旧组件 | 若仅有一个，说明问题已缓解 |

关键代码定位：
- `frameworks/core/interfaces/native/implementation/builder_node_ops_accessor.cpp`：BuilderNode 创建，设置 `SetIsBuilderNode(true)` 和 `SetIsRootBuilderNode(true)`
- `frameworks/core/interfaces/native/node/frame_node_modifier.cpp`：`AddBuilderNodeInFrameNode` / `RemoveBuilderNodeInFrameNode` / `ClearBuilderNodeInFrameNode`
- `frameworks/core/common/builder_util.cpp,56-118`：`GetBuilderNodes` / `BuilderNodeFunc` 遍历和增删

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 典型 PR / Commit 参考 |
|----------|----------|---------------|----------------------|
| 生命周期时序变更导致下树被屏蔽 | 将"自定义组件前端对象删除前移"特性改为默认不使能，开放接口让应用选择是否使能 | 系统侧功能开关默认关闭 | 特性引入 PR [54006](https://gitcode.com/openharmony/arkui_ace_engine/pull/54006) |
| 动画屏蔽下树与复用缓存池冲突 | 应用侧规避：不在 `aboutToDisappear` 中执行依赖组件下树时序的操作 | 应用代码调整为不在此生命周期中修改条件渲染状态 | — |
| BuilderNode 内节点结构异常 | 应用侧规避：BuilderNode 内条件渲染子组件的下树不依赖 `aboutToDisappear` 时序 | 应用代码调整为在 `onRecycle` 或其他时机处理状态变更 | — |

## 关联案例

| 案例编号 | 问题简述 | 根因类别 | 修复方式 | 关联 PR / Issue |
|----------|----------|----------|----------|----------------|
| CASE-01 | 页面 A 跳转 B 后，复用的 buildText 组件内 Image 重叠 | 生命周期时序变更 + 动画屏蔽与复用冲突 | 应用规避 + 系统侧特性默认不使能 | 特性引入 [PR #54006](https://gitcode.com/openharmony/arkui_ace_engine/pull/54006) |
| CASE-02 | BuilderNode 内 `if (flg)` 子组件在页面转场时下树被屏蔽，复用后新旧组件共存 | 动画屏蔽下树与复用冲突 + BuilderNode 节点结构异常 | 应用侧调整状态变更时机，不在 `aboutToDisappear` 中修改 BuilderNode 内条件渲染状态 | 特性引入 [PR #54006](https://gitcode.com/openharmony/arkui_ace_engine/pull/54006) |

## 预防措施

- 不在 `aboutToDisappear` 中执行依赖组件下树时序的状态变量修改（如 `flg = false` 触发条件渲染子组件下树）
- 若需要在组件回收前清理状态，使用 `aboutToRecycle` / `onRecycle` 生命周期而非 `aboutToDisappear`
- BuilderNode 内条件渲染子组件的下树不应依赖 `aboutToDisappear` 与动画时序的配合
- 系统侧新增影响生命周期时序的特性时，应默认不使能并开放接口让应用按需开启，避免不兼容变更
- 单元测试应覆盖 `aboutToDisappear` 在动画期间触发状态变更的场景，验证 `AddDisappearingChild` 与复用流程的交互（参考 `geometry_transition_test_ng.cpp` 中 `hasOutAnim_` / `isRemoving_` 断言）

## 相关主题

- `docs/kb/frontend/state_management/custom-component.md` — 自定义组件机制（FuncID 07-03-01）
- `docs/kb/frontend/state_management/static-custom-component.md` — 静态自定义组件状态相关（FuncID 07-03-07）
- `docs/kb/architecture/component-reuse-framework.md` — 组件复用框架（FuncID 04-19-01）
- `docs/kb/capabilities/transition-animation.md` — 转场动画（FuncID 03-02-05）
- `docs/kb/capabilities/geometry-transition.md` — 组件共享元素动画（FuncID 03-02-07）