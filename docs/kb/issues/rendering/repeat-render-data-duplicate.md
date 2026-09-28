# Repeat 渲染数据重复 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `RepeatRenderDataDuplicate`
> 关联功能域：`07-05-03`

## 问题概述

某些 Repeat 子项把数据刷新或状态同步逻辑写在 `aboutToReuse` 生命周期里，但 `Repeat` 的复用链路不会触发该回调，导致复用后的节点仍沿用旧数据，表现为内容重复、错位或状态串位。
当前仅覆盖“生命周期错配”这一类已验证根因。

典型表现：
- 同一项被渲染出多份
- 数据刷新后内容顺序异常
- 子节点状态被意外复用或重置

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | Repeat / RepeatModelNG | `frameworks/core/components_ng/syntax/repeat_model_ng` | verified |
| architecture | root_cause_owner | ViewPU aboutToReuse 生命周期 / RepeatNode 复用边界 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view`，`frameworks/core/components_ng/syntax/repeat_node` | verified |
| capability | fix_location | aboutToReuse 数据同步逻辑与 Repeat 复用路径边界 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view`，`frameworks/core/components_ng/syntax/repeat_node` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| aboutToReuse 中更新数据 | 数据刷新或状态同步只写在 `aboutToReuse`，Repeat 复用时不会执行 | 复用后仍显示旧数据，出现重复或错位 |

## 排查路径

### 快速判断

1. 先确认数据刷新逻辑是否写在 `aboutToReuse`。
2. 再确认当前子项是否通过 `Repeat` 复用。
3. 最后核对 Repeat 的数据同步是否发生在实际构建/刷新链路里。

### 详细排查

#### aboutToReuse 依赖排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `aboutToReuse` 打日志 | Repeat 场景命中回调 | 说明刷新逻辑挂错生命周期 |
| 2 | 对比 Repeat 与非 Repeat 复用场景 | 两者回调链路不同 | 继续查复用边界 |
| 3 | 观察重复渲染时的数据来源 | 数据应来自最新同步结果 | 检查状态刷新位置 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view`：`aboutToReuse` 生命周期
- `frameworks/core/components_ng/syntax/repeat_node`：Repeat 复用与清理流程

#### Repeat 复用边界排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查数据更新是否依赖 `aboutToReuse` | 业务刷新逻辑可在当前渲染链路执行 | 改到构建/刷新路径 |
| 2 | 触发 Repeat 复用 | 数据仍保持最新 | 说明生命周期选错 |
| 3 | 对照重复渲染前后的状态值 | 状态应随数据同步更新 | 检查同步时机 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view`：复用回调入口
- `frameworks/core/components_ng/syntax/repeat_node`：Repeat 复用路径

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| aboutToReuse 中更新数据 | 将数据刷新从 `aboutToReuse` 迁移到 Repeat 实际执行的构建/刷新链路 | 数据更新逻辑 / itemGenerator | 当前实现 | `pu_view` |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | aboutToReuse 中的刷新逻辑在 Repeat 复用场景未生效 | aboutToReuse 中更新数据 | related | `pu_view` | verified |
| CHG-02 | Repeat 复用路径不会自动触发 aboutToReuse | aboutToReuse 中更新数据 | related | `repeat_node` | verified |

## 预防措施

- 使用稳定且唯一的业务 `key`。
- 不要把 Repeat 子项的关键数据刷新只放在 `aboutToReuse`。
- 将状态同步放到 Repeat 实际执行的构建/刷新链路。
- 对 Repeat 复用场景补充日志或测试，确认 `aboutToReuse` 不是唯一依赖。

## 相关主题

- `docs/syntax/Repeat_Knowledge_Base.md`
- `docs/syntax/ForEach_Knowledge_Base.md`
- `docs/syntax/RepeatVirtualScroll_Knowledge_Base.md`
