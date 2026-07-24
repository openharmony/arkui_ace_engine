---
id: drawable-descriptor-release-state
type: feature
title: "DrawableDescriptor release/isReleased binding-state API"
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles:
  - sdk-api
complexity: standard
lineage: new-on-legacy
status: approved
owner: "liyujie"
source_issue: "user request"
created_at: 2026-07-21
updated_at: 2026-07-23
related: []
related_tasks: []
related_decisions: []
profile_source: inferred
code_refs:
  - "foundation/arkui/ace_engine/interfaces/inner_api/drawable_descriptor"
  - "foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets"
  - "foundation/arkui/ace_engine/interfaces/native/node/native_node_napi.cpp"
  - "foundation/arkui/ace_engine/interfaces/native/node/native_node_ani.cpp"
  - "interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts"
  - "interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets"
commits: []
func_id: 04-01-03
feat_id: "Feat-01-delta"
long_term_spec_path: "specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md"
long_term_design_path: "specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md"
---

# 变更元数据

> 本文件是变更 `drawable-descriptor-release-state` 的机器可读元数据。

## 变更类型

| 字段 | 值 |
|------|----|
| ID | drawable-descriptor-release-state |
| 类型 | feature |
| 标题 | DrawableDescriptor release/isReleased binding-state API |
| Profile | arkui |
| 子 Profile | sdk-api |
| Lineage | new-on-legacy |
| 复杂度 | standard |
| 状态 | approved |

## 状态历史

| 日期 | 阶段 | 状态 | 说明 |
|------|------|------|------|
| 2026-07-21 | Define | Draft | 初始 SDD 需求分析；源码和既有规格已核验，待 Owner/需求方确认基线。 |
| 2026-07-21 | Define | Clarifying | 已形成推荐确认口径，等待需求方/Owner 逐项确认后基线。 |
| 2026-07-21 | Define | Clarifying | liyujie 确认 Q-1 到 Q-6；Static 行为、文档/示例范围待确认。 |
| 2026-07-21 | Define | Baselined | liyujie 确认 Q-7 Static 不动；Q-8 不补 NAPI 单测、不强制 XTS、允许新增 previewer 可执行用例；proposal 基线通过。 |
| 2026-07-21 | Specify | ReadyForReview | 已创建 spec.md，Level B 结构校验通过；等待规格确认后进入 design。 |
| 2026-07-21 | Specify | Approved | liyujie 批准 spec.md；进入 design。 |
| 2026-07-21 | Design | Approved | liyujie 批准 design.md；进入 execution-plan。 |
| 2026-07-21 | Plan | ReadyForReview | 已创建 execution-plan.md，覆盖 AC-1.1 到 AC-3.5；等待计划审批后进入代码实现。 |
| 2026-07-22 | Plan | Approved | liyujie 批准 execution-plan.md；进入代码实现。 |
| 2026-07-23 | Review/Validate | Approved | 按最新实现更新 SDD 各环节文档；实现口径为 JS object `_isReleased` 属性、`napi_remove_wrap` 解绑，未标 SDK 错误码的控制/刷新类 API 不额外检查 `_isReleased`，native 为空即无操作返回。 |
