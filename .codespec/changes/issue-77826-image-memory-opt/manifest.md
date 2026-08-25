---
id: issue-77826-image-memory-opt
type: feature
title: Image 组件基础内存优化
spec_schema: ohos-sdd/v1
profile: arkui/component
target_release:
  id: TBD
  name: TBD
  label: TBD
  release_note: TBD
  status: proposed
  source: requirement
  decided_by: liyujie43
  decided_at: 2026-06-11
complexity: standard
lineage: legacy
status: done
owner: liyujie43
source_issue: "https://gitcode.com/openharmony/arkui_ace_engine/issues/77826"
created_at: 2026-06-11
updated_at: 2026-07-16
related: []
related_tasks:
  - TASK-01-dfx-config-sharing
  - TASK-02-imagesourceinfo-sharing
  - TASK-03-imagesourceinfo-field-cleanup
  - TASK-05-bool-bitfield
related_decisions: []
code_refs:
  - frameworks/core/components_ng/pattern/image/
  - frameworks/core/components_ng/image_provider/
  - frameworks/core/image/image_source_info.h
commits: []
func_id: 05-08-01
feat_id: Feat-05
subprofiles:
  - arkui/component
long_term_spec_path: specs/05-ui-components/08-image-components/01-image/Feat-05-image-base-memory-opt-spec.md
long_term_design_path: specs/05-ui-components/08-image-components/01-image/design.md
spectest_feature_path: N/A (内存优化不产生可 Inspector 断言的行为变化)
baseline_approval:
  approved: true
  approver: liyujie43
  evidence: "2026-06-11 对话中明确回复'批准'"
---
