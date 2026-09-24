---
id: issue-76660-withenv-direction
type: feature
title: "WithEnv Direction & Framework Refactoring"
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles:
  - component
  - sdk-api
target_release:
  id: unplanned
  status: proposed
complexity: standard
lineage: new-on-legacy
status: implementing
owner: "未指定（需求记录未提供）"
source_issue: "https://gitcode.com/openharmony/arkui_ace_engine/issues/76660"
created_at: 2025-05-25
updated_at: 2026-08-05
related: []
related_tasks:
  - TASK-001
  - TASK-002
  - TASK-003
related_decisions: []
code_refs:
  - "foundation/arkui/ace_engine"
commits:
  - 3df5112f727
  - 705e5d27151
  - 46849cd852ab
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
| 长期 spec | `specs/04-03-01-env-container/Feat-01-direction-spec.md`（尚未回灌） |
| 长期 design | `specs/04-03-01-env-container/design.md`（尚未回灌） |
| SpecTest feature | 不适用：本轮以组件 unittest 与 ArkTS/HAP 手工验证覆盖，尚未建立 Inspector 稳定断言 |

## 阶段状态

| 阶段 | 状态 | 产物 |
|------|------|------|
| 定义 (Stage 1) | Approved | proposal.md, evidence/gates/gate-define.md |
| 规格说明 (Stage 2) | Approved | design.md, spec.md, evidence/gates/gate-specify.md |
| 设计 (Stage 3) | Reviewing | design.md, evidence/gates/gate-design.md |
| 计划 (Stage 4) | Reviewing（代码已实现，native 定向测试与 ArkTS/HAP 验证待执行） | execution-plan.md, tasks/TASK-001-environment-manager-direction-sdk-api.md, evidence/gates/gate-plan.md |

### Stage 3+4 实现偏差

Owner 在 `3df5112f727..705e5d27151` 中合并实现了 Tasks 1-4，但做出了以下架构简化：

- 原设计中的 O(1) 缓存、全部精准通知和 dirty/revision 协议未实现；当前 `design.md` 已按真实实现重写为“父链解析 + explicit reader 双向索引”，缓存优化后置
- direction 三级优先级已实现，实际入口名为 `GetLayoutDirection()`
- SystemEnvKey/WritableEnvKey 类型体系已实现（TS 层）
- `46849cd852ab` 追加已初始化 Env/CustomEnv 的 detach 默认值、attach 重查、按需 callback 和 C++ 生命周期测试代码；运行验证仍未闭合

### 46849cd852ab 文档归并

该提交中的 tree-state/reparent 分析与 ETS 用例草稿已按 SDD 职责归并：可观察行为进入 `spec.md`，实现决策、对象关系、精确时序和剩余风险进入 `design.md`，验证矩阵进入 `execution-plan.md`，审查结论与证据分别进入 `review.md` 和 `evidence/reviews/spec-compliance.md`。临时分析文档不再作为独立事实源。

## baseline_approval

| 字段 | 内容 |
|------|------|
| approved | true |
| approver | 需求 Owner |
| evidence | Owner 在对话中明确"批准 stage1"，2025-05-25 |
| date | 2025-05-25 |
