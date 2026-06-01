---
id: issue-76660-withenv-direction
type: feature
title: "WithEnv Direction & Framework Refactoring"
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles: [arkui/component, arkui/sdk-api]
target_release:
  id: TBD
  status: proposed
complexity: standard
lineage: new-on-legacy
status: implementing
owner: "TBD (pending requirement Owner)"
source_issue: "https://gitcode.com/openharmony/arkui_ace_engine/issues/76660"
created_at: 2025-05-25
updated_at: 2026-06-12
related: []
related_tasks:
  - TASK-001
related_decisions: []
code_refs:
  - "foundation/arkui/ace_engine"
commits:
  - 3df5112f727
  - 705e5d27151
---

# Manifest — WithEnv Direction & Framework Refactoring

## 需求标识

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-04-03-01-01 |
| 需求名称 | WithEnv 环境变量框架新增 direction 支持 & 内部重构 |
| func_id | 04-03-01 |
| feat_id | Feat-01 |

## 功能域路径

```
通用能力 (L1) > 容器组件 (L2) > 环境变量 (L3, 04-03-01)
```

## 长期规格路径

| 资产 | 路径 |
|------|------|
| 长期 spec | `specs/04-03-01-env-container/Feat-01-direction-spec.md` |
| 长期 design | `specs/04-03-01-env-container/design.md` |
| SpecTest feature | TBD (待 Stage 2 评估 SpecTest 适用性) |

## 阶段状态

| 阶段 | 状态 | 产物 |
|------|------|------|
| 定义 (Stage 1) | Approved | proposal.md, evidence/gates/gate-define.md |
| 规格说明 (Stage 2) | Approved | design.md, spec.md, evidence/gates/gate-specify.md |
| 设计 (Stage 3) | Conditional Pass | evidence/gates/gate-design.md |
| 计划 (Stage 4) | Conditional Pass (Tasks 1-4 merged, cache deferred; tests follow-up) | execution-plan.md, tasks/TASK-001-environment-manager-direction-sdk-api.md, evidence/gates/gate-plan.md |

### Stage 3+4 实现偏差

Owner 在 `3df5112f727..705e5d27151` 中合并实现了 Tasks 1-4，但做出了以下架构简化：

- **ADR-1/2/3 缓存+精准通知 未实现**：保持原始 O(n) 爬树 + DFS 通知方案，首期聚焦功能正确性
- **ADR-4 三级方向优先级 已实现**：方法名从 `GetEffectiveLayoutDirection()` 改为 `GetLayoutDirection()`
- **ADR-5 SystemEnvKey 注册表 已实现**（TS 层）
- 缓存优化标记为后续迭代目标

## baseline_approval

| 字段 | 内容 |
|------|------|
| approved | true |
| approver | 需求 Owner |
| evidence | Owner 在对话中明确"批准 stage1"，2025-05-25 |
| date | 2025-05-25 |
