# UIExtension 窗口状态回调注册时机不正确 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-07
> 来源：`docs/context_registry.json` 主题 `UIExtensionWindowStateRegistration`
> 关联功能域：05-12-03（UIExtensionComponent）、05-12-04（EmbeddedComponent）、04-17-01（UIExtension 机制）、03-05-01（窗口机制）

## 问题概述

UIExtensionComponent 的窗口状态回调若在 Model 创建节点时注册，而不是在节点实际挂载到 PipelineContext 时注册，回调可能绑定到创建阶段的当前 Pipeline，或者因创建入口差异而没有注册。宿主窗口显示、隐藏时，UIExtension 子 Ability 因此可能无法同步进入前台或后台状态。

典型表现：
- 宿主窗口进入后台后，UIExtension 子 Ability 仍保持前台状态。
- 宿主窗口重新显示后，UIExtension 子 Ability 没有收到对应的前台通知。
- UIExtension 节点跨 Context 挂载、移动或重新挂载后，窗口状态通知仍落在旧 Pipeline 或不再触发。
- 不同 UIExtensionComponent、Modal UIExtension 或 EmbeddedComponent 创建入口表现不一致。

> 覆盖范围说明：Issue #79623 的公开描述较简略，当前内容基于 PR #87472 的源码差异和现有窗口状态回调链路推断。当前仅覆盖 `UIExtensionPattern` 的窗口显示/隐藏回调注册，不扩展到焦点、可见区域、窗口尺寸或 SecurityUIExtension/DynamicComponent 的独立注册实现。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | UIExtensionComponent 与 EmbeddedComponent | PR #87472 修改其公共 `UIExtensionPattern` 和多个 Model 创建入口 | verified |
| architecture | trigger | FrameNode 挂载、移动和 Context 切换 | `FrameNode::AttachContext` 调用 `Pattern::OnAttachContext` | verified |
| architecture | root_cause_owner | UIExtension 窗口状态回调注册生命周期 | 注册从 `UIExtensionModelNG::Create` 迁移到 `UIExtensionPattern::OnAttachContext` | verified |
| architecture | fix_location | `UIExtensionPattern::OnAttachContext` | PR #87472 和当前源码 | verified |
| architecture | dependency | PipelineContext 窗口状态回调集合 | `AddWindowStateChangedCallback`、`FlushWindowStateChangedCallback` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. 创建阶段注册早于实际 Context 挂载 | 创建节点时的 `PipelineContext::GetCurrentContext()` 与节点最终挂载 Context 不一致，或节点随后发生 Context 切换 | 节点移动、重新挂载或通过非当前 Pipeline 构造后，窗口显示/隐藏回调绑定错误 |
| B. 回调注册散落在部分 Model 创建入口 | 不同重载分别维护 `AddWindowStateChangedCallback`，部分入口缺少注册或后续新增入口没有同步处理 | Modal UIExtension、普通 UIExtensionComponent、EmbeddedComponent 或原生创建入口的状态行为不一致 |

## 排查路径

### 快速判断

1. 确认异常是宿主窗口 `OnShow/OnHide` 后 UIExtension 子 Ability 的前后台状态未同步，而不是组件自身可见性变化。
2. 获取 UIExtension host node ID，检查它是否存在于实际挂载 Pipeline 的窗口状态回调集合。
3. 对比节点创建时的 current Pipeline 与 `OnAttachContext` 收到的 PipelineContext/instance ID。
4. 检查窗口状态分发是否通过 `FlushWindowStateChangedCallback` 找到该节点并调用 `OnWindowShow` 或 `OnWindowHide`。
5. 检查 `UIExtensionPattern` 是否进一步调用 `NotifyForeground` 或 `NotifyBackground`，以及 session 是否有效。

### 详细排查

#### A. 创建阶段注册早于实际 Context 挂载排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 记录 Model 创建节点时的 current Pipeline instance ID | 仅作为创建上下文，不直接决定最终回调归属 | 若直接在此注册，继续核对实际挂载 Context |
| 2 | 检查 `FrameNode::AttachContext` | 对实际挂载 Context 调用 `UIExtensionPattern::OnAttachContext` | 若未调用，排查节点挂载链路 |
| 3 | 检查 `UIExtensionPattern::OnAttachContext` 更新后的 `instanceId_` | 与实际挂载 Pipeline 的 instance ID 一致 | 若不一致，检查 Context 切换和 `RegisterEvent` 顺序 |
| 4 | 检查 `AddWindowStateChangedCallback` 的调用对象 | 使用实际 instance ID 获取的 Pipeline，并登记 host node ID | 若仍使用创建阶段 Pipeline，窗口事件可能发往错误上下文 |
| 5 | 节点分离或切换 Context 后检查旧 Pipeline | 旧 Pipeline 中对应 node ID 已由注销链路移除 | 若残留，检查 `OnDetachContext`、`UnRegisterEvent` 和 `UnRegisterPipelineEvent` |

关键代码定位：
- `frameworks/core/components_ng/base/frame_node.cpp`，`FrameNode::AttachContext`、`FrameNode::DetachContext`：Pattern Context 生命周期入口。
- `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.cpp`，`OnAttachContext`、`OnDetachContext`：按实际 instance ID 注册或注销 UIExtension 事件。
- `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.cpp`，`UnRegisterPipelineEvent`：从原 Pipeline 移除窗口状态回调。

#### B. 回调注册散落在部分 Model 创建入口排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 枚举 `UIExtensionModelNG::Create` 重载 | 创建逻辑只负责构造和配置节点，不分别登记窗口状态回调 | 若某重载仍单独注册，可能再次产生入口差异 |
| 2 | 检查各入口创建的 Pattern 类型 | UIExtensionComponent 和 EmbeddedComponent 均使用 `UIExtensionPattern` | 若使用其他 Pattern，应检查其独立生命周期策略 |
| 3 | 对不同创建入口触发节点挂载 | 均进入同一个 `UIExtensionPattern::OnAttachContext` 注册点 | 若某入口不进入，排查节点是否真正上树和绑定 Context |
| 4 | 触发 Pipeline `OnHide/OnShow` | `FlushWindowStateChangedCallback` 能通过 node ID 找到对应节点 | 若找不到，检查回调集合和 ElementRegister |
| 5 | 检查 Pattern 状态转换 | 可见且 session 有效时分别调用 `NotifyBackground`、`NotifyForeground` | 若回调已到达但状态未变，继续排查可见性和 session 状态 |

关键代码定位：
- `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model_ng.cpp`，各 `Create` 重载：节点创建和配置入口。
- `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.cpp`，`OnWindowShow`、`OnWindowHide`：窗口状态到子 Ability 状态的转换。
- `frameworks/core/pipeline_ng/pipeline_context.cpp`，`AddWindowStateChangedCallback`、`RemoveWindowStateChangedCallback`、`FlushWindowStateChangedCallback`：回调集合维护和分发。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A. 创建阶段注册早于实际 Context 挂载 | 将窗口状态回调注册迁移到 `UIExtensionPattern::OnAttachContext`，使用 Pattern 当前 instance ID 对应的实际 Pipeline 和 host node ID | `ui_extension_pattern.cpp` | [PR #87472](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87472) (`fixed`) | PR diff 新增挂载阶段注册，并由提交说明明确修复 `onWindowHide` 回调 |
| B. 回调注册散落在部分 Model 创建入口 | 删除 Modal UIExtension、普通 UIExtensionComponent 和 EmbeddedComponent 创建分支中的重复注册，统一由 Pattern 生命周期处理 | `ui_extension_model_ng.cpp` | [PR #87472](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87472) (`fixed`) | PR diff 删除三个 `Create` 路径中的 `GetCurrentContext` 和 `AddWindowStateChangedCallback` |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | [Issue #79623](https://gitcode.com/openharmony/arkui_ace_engine/issues/79623) 提出 UEC 状态变化应在节点上树/挂载时注册 | A、B | related | 公开 Issue 标题与需求描述 | verified |
| CHG-02 | 将窗口状态回调从 Model 创建阶段统一迁移到 Pattern 的 Context 挂载阶段 | A、B | fixed | [PR #87472](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87472)、提交 `6d7e6a5b912` 及当前源码 | verified |
| CHG-03 | 历史创建入口分别添加窗口状态回调 | B | related | `git blame` 显示相关注册来自多个独立创建入口；没有充分回归区间证据将其标记为 `introduced` | inferred |

## 预防措施

- 与 Pipeline、Container 或 Context 归属相关的监听注册，应优先放在 `OnAttachContext` 或等价的实际挂载生命周期中，而不是 Model 创建阶段。
- 注册和注销必须以同一个实际 Pipeline、同一个 node ID 成对执行；节点跨 Context 时先清理旧归属，再登记新归属。
- 多个创建重载共享同一 Pattern 时，将生命周期监听集中到 Pattern，避免每个入口重复维护。
- 增加直接回归测试：断言 `OnAttachContext` 后 node ID 位于目标 Pipeline 的窗口状态回调集合，`OnDetachContext` 后从旧集合移除。
- 增加跨两个 Pipeline 移动节点的测试，验证 `OnHide/OnShow` 只由新 Pipeline 驱动。
- 当前 UIExtension 单元测试会调用 `OnAttachContext`、`OnWindowShow` 和 `OnWindowHide`，但未直接覆盖 PR #87472 的注册归属和跨 Context 场景，后续应补齐。

## 相关主题

- [docs/kb/components/container/ui-extension-component.md](../../components/container/ui-extension-component.md) — UIExtensionComponent，FuncID `05-12-03`
- [docs/kb/components/container/embedded-component.md](../../components/container/embedded-component.md) — EmbeddedComponent，FuncID `05-12-04`
- [docs/kb/components/container/ui-extension-component.md](../../components/container/ui-extension-component.md) — UIExtension 机制，FuncID `04-17-01`
- [docs/kb/architecture/window-mechanism.md](../../architecture/window-mechanism.md) — Pipeline 窗口显示/隐藏与状态分发，FuncID `03-05-01`