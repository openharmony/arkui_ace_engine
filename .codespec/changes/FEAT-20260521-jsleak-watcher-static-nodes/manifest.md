---
id: FEAT-20260521-jsleak-watcher-static-nodes
type: feature
title: "静态语言命令式节点 JsLeakWatcher 内存上报"
spec_schema: ohos-sdd/v1
profile: arkui
target_release:
  id: TBD
  status: proposed
complexity: standard
lineage: new-on-legacy
status: archived
owner: sunbees
source_issue: ""
created_at: 2026-05-21
updated_at: 2026-06-05
related: []
related_tasks: []
related_decisions: []
code_refs:
  - "frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/"
commits:
  - sha: c74921c397b
    message: "Base SHA — 实现代码已存在于 base 提交中"
func_id: "04-06-02 (primary), also 04-06-03, 04-06-04, 04-06-05"
feat_id: Feat-01
subprofiles: []
long_term_spec_path: "specs/04-common-capability/06-custom-node-capability/"
long_term_design_path: "specs/04-common-capability/06-custom-node-capability/design.md"
spectest_feature_path: "N/A — 回调注册仅 InnerApi，外部无法注册带 UI 逻辑的回调"
---

## Baseline Approval

| 字段 | 值 |
|------|-----|
| approved | true |
| approver | sunbees |
| evidence | 参考规格 FEAT-20260521 已通过完整 SDD 流程（Stage 4 Released），用户确认内容完全有效 |
| date | 2026-05-21 |

## Artifacts

| Stage | Artifact | Status |
|-------|----------|--------|
| 1-Define | proposal.md | Baselined |
| 1-Define | evidence/gates/gate-define.md | Approved |
| 2-Specify | design.md | Approved |
| 2-Specify | spec.md | Approved |
| 2-Specify | evidence/gates/gate-specify.md | Approved |
| 3-Implement | execution-plan.md | Approved |
| 3-Implement | review.md | Approved |
| 3-Implement | evidence/gates/gate-implement.md | Approved |
| 4-Release | evidence/gates/gate-archive.md | Approved |

## Scope

- **In scope**: 静态语言路径 4 个命令式节点 dispose() 添加 fireArkUIObjectLifecycleCallback 调用（ETS + C++ ANI Bridge）
- **Out of scope**: PipelineContext 修改、动态语言修改、UIContext 接口修改、JsLeakWatcher 组件实现

## FuncID Cross-Reference

| FuncID | 域名 | FeatID | 特性名 | 注册状态 |
|--------|------|--------|--------|----------|
| 04-06-02 | FrameNode | Feat-01 | JS 内存上报 | 已注册 |
| 04-06-03 | RenderNode | Feat-01 | JS 内存上报 | 已注册 |
| 04-06-04 | BuilderNode | Feat-01 | JS 内存上报 | 已注册 |
| 04-06-05 | ComponentContent | Feat-01 | JS 内存上报 | 已注册 |
