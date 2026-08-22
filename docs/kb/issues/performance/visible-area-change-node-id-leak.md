# 可见区域变化事件注册组件 ID 泄漏 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `VisibleAreaChangeNodeIdLeak`
> 关联功能域：04-04-10

## 问题概述

`FrameNode::GetNodesById` 以 `const` 引用接收事件注册 ID 集合，对已在 `ElementRegister` 中销毁的节点 ID 仅 `continue` 跳过而不清理。当组件注册了 `onVisibleAreaChange`/`onAreaChange`/`onFormVisibleChange` 后被销毁，其 ID 仍残留在 PipelineContext/FormVisibleManager 的集合中且永不收缩，导致集合随组件创建-销毁不断累积（ID 泄漏），每帧遍历无效 ID 造成性能劣化。

典型表现：
- 长时间运行、频繁创建/销毁组件的页面，`onVisibleAreaChangeNodeIds_`/`onAreaChangeNodeIds_`/`onFormVisibleChangeNodeIds_` 集合持续增长不收缩
- 每帧 `HandleVisibleAreaChangeEvent`/`HandleOnAreaChangeEvent` 对大量已销毁节点 ID 做无效 `GetUINodeById` 查找，CPU 占用升高
- 内存上表现为 `unordered_set<int32_t>` 元素数量与历史组件总数正相关

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | PipelineContext 事件分发（HandleVisibleAreaChangeEvent / HandleOnAreaChangeEvent） | commit diff：调用方集合持续膨胀 | verified |
| architecture | root_cause_owner | FrameNode::GetNodesById（const 引用，仅跳过不清理） | commit diff：原实现 `if (!uiNode) { continue; }` | verified |
| capability | fix_location | FrameNode::GetNodesByIdWithCleanup + PipelineContext/FormVisibleManager 三处调用替换 | commit 454d1c2e6a584e823cb0b2e3be48c17f9db2160e diff | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 事件注册集合未随节点销毁自动清理 | `GetNodesById` 入参为 `const std::unordered_set<int32_t>&`，对 `GetUINodeById` 返回 null 的 ID 仅 `continue`，不 erase | 组件注册 onVisibleAreaChange 后销毁，节点从 ElementRegister 移除但 ID 仍在 `onVisibleAreaChangeNodeIds_` 中，集合只增不减 |

## 排查路径

### 快速判断

1. 在长稳/压测场景下观察 `onVisibleAreaChangeNodeIds_`/`onAreaChangeNodeIds_`/`onFormVisibleChangeNodeIds_` 的 size 是否持续增长不收缩
2. 检查 `FrameNode::GetNodesById` 入参是否为 `const` 引用（无法就地清理）
3. 检查上述集合的遍历入口是否已替换为 `GetNodesByIdWithCleanup`
4. 用 ACE_SCOPED_TRACE 的 `nodeCount` 打点确认实际有效节点数是否远小于集合 size

### 详细排查

#### 事件注册集合未随节点销毁自动清理 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 查看 `FrameNode::GetNodesById` 签名 | 入参应为非 const 引用以支持就地 erase | 若为 const 引用，则无法清理 |
| 2 | 查看函数体对 `!uiNode` 分支 | 应执行 `set.erase(nodeId)` | 仅 `continue` 即泄漏 |
| 3 | 检查 PipelineContext/FormVisibleManager 三处调用是否使用 cleanup 版本 | 全部应替换为 `GetNodesByIdWithCleanup` | 残留 `GetNodesById` 调用即未修复 |
| 4 | 压测后 dump 集合 size 与实际存活节点数 | size 应趋于稳定 | size 持续增长即命中此根因 |

关键代码定位：
- `frameworks/core/components_ng/base/frame_node.cpp`：`FrameNode::GetNodesById`（const 引用，仅 `continue`，问题实现）
- `frameworks/core/components_ng/base/frame_node.cpp`：`FrameNode::GetNodesByIdWithCleanup`（非 const 引用，`set.erase(nodeId)` 清理，修复实现）
- `frameworks/core/components_ng/base/frame_node.h`：`GetNodesByIdWithCleanup` 静态方法声明
- `frameworks/core/pipeline_ng/pipeline_context.cpp`：`HandleVisibleAreaChangeEvent` 调用 `GetNodesByIdWithCleanup(onVisibleAreaChangeNodeIds_)`
- `frameworks/core/pipeline_ng/pipeline_context.cpp`：`HandleOnAreaChangeEvent` 调用 `GetNodesByIdWithCleanup(onAreaChangeNodeIds_)`
- `frameworks/core/components_ng/manager/form_visible/form_visible_manager.cpp`：`HandleFormVisibleChangeEvent` 调用 `GetNodesByIdWithCleanup(onFormVisibleChangeNodeIds_)`

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 事件注册集合未随节点销毁自动清理 | 新增 `GetNodesByIdWithCleanup`（入参改为非 const 引用），对 `GetUINodeById` 返回 null 的 ID 执行 `set.erase`；三处事件分发调用替换为 cleanup 版本 | `frame_node.cpp/.h` 新增方法；`pipeline_context.cpp`、`form_visible_manager.cpp` 替换调用 | 454d1c2e6a584e823cb0b2e3be48c17f9db2160e (fixed) | commit diff：新增 GetNodesByIdWithCleanup；三处 `GetNodesById(...)` 替换为 `GetNodesByIdWithCleanup(...)` |

核心修复代码（`frame_node.cpp`）：
```cpp
std::vector<RefPtr<FrameNode>> FrameNode::GetNodesByIdWithCleanup(std::unordered_set<int32_t>& set)
{
    std::vector<int32_t> ids(set.begin(), set.end());
    std::vector<RefPtr<FrameNode>> nodes;
    for (auto nodeId : ids) {
        auto uiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!uiNode) {
            set.erase(nodeId);   // 关键：清理已销毁节点 ID
            continue;
        }
        auto frameNode = DynamicCast<FrameNode>(uiNode);
        if (frameNode) {
            nodes.emplace_back(frameNode);
        }
    }
    return nodes;
}
```

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 新增 GetNodesByIdWithCleanup 并替换 PipelineContext/FormVisibleManager 三处调用 | 事件注册集合未随节点销毁自动清理 | fixed | commit 454d1c2e6a584e823cb0b2e3be48c17f9db2160e diff | verified |
| CHG-02 | 为 GetNodesByIdWithCleanup 补齐 5 个单元测试（空集/有效/无效清理/非 FrameNode 跳过/混合场景） | 事件注册集合未随节点销毁自动清理 | follow_up | commit 454d1c2e6a584e823cb0b2e3be48c17f9db2160e diff（frame_node_test_ng_coverage.cpp GetNodesByIdWithCleanup001-005） | verified |
| CHG-03 | mock_frame_node.cpp 补齐 GetNodesByIdWithCleanup 桩实现 | 事件注册集合未随节点销毁自动清理 | follow_up | commit 454d1c2e6a584e823cb0b2e3be48c17f9db2160e diff（mock_frame_node.cpp） | verified |

## 预防措施

- 任何按 ID 集合做事件分发的遍历入口，都应在遍历时清理已失效 ID，避免"只增不减"
- 新增事件注册类集合时，配套提供基于 `ElementRegister` 查 null 的就地清理路径，而不是依赖节点销毁时显式反注册
- 代码审查重点：`const std::unordered_set<int32_t>&` 入参的事件分发函数是否会累积失效 ID；长稳压测关注事件集合 size 是否收敛
- DFX 打点（如 `HandleVisibleAreaChangeEvent_nodeCount`）应对比集合 size 与实际有效 node 数，发现离散即存在泄漏

## 相关主题

- [docs/kb/capabilities/visible-area-mechanism.md](../../capabilities/visible-area-mechanism.md)：可见区域机制代码型 KB（FuncID 04-04-10，含 onVisibleAreaChange/onVisibleAreaApproximateChange）
- [docs/kb/capabilities/component-related-events.md](../../capabilities/component-related-events.md)：组件相关事件代码型 KB（FuncID 04-04-09，含 onAreaChange）
- [docs/kb/capabilities/frame-node.md](../../capabilities/frame-node.md)：FrameNode 节点代码型 KB（含 GetNodesById/ElementRegister 交互）