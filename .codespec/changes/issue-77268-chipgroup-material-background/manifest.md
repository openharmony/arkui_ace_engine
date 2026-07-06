---
id: draft-20260610-chipgroup-material-background
type: feature
title: "ChipGroup 新增支持新材质的背景配置能力"
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles:
  - arkui/component
target_release:
  id: OpenHarmony-7.0-Release
  name: OpenHarmony 7.0
  label: OpenHarmony 7.0 Release
  status: proposed
  source: PRD
  decided_by: TBD (pending Owner)
  decided_at: 2026-06-10
complexity: standard
lineage: new-on-legacy
status: approved
owner: "youzhi92"
source_issue: PRD
created_at: 2026-06-10
updated_at: 2026-06-10
related: []
related_tasks: []
related_decisions: []
code_refs:
  - "advanced_ui_component/chipgroup/source/chipgroup.ets"
  - "advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.ChipGroup.ets"
  - "advanced_ui_component/chip/source/chip.ets"
  - "advanced_ui_component/chip/source/chip_v16.ets"
  - "advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.Chip.ets"
  - "advanced_ui_component/chipgroup/source/chipgroup.ets (IconGroupSuffix struct)"
commits: []
func_id: 07-01-02
feat_id: Feat-01
long_term_spec_path: specs/07-01-chipgroup/Feat-01-chipgroup-material-background-spec.md
long_term_design_path: specs/07-01-chipgroup/design.md
spectest_feature_path: TBD
---

# 变更元数据

> 本文件是变更 `draft-20260610-chipgroup-material-background` 的机器可读元数据。
> 事实源为 `manifest.md`，其它文档引用本文件中的字段而非硬编码版本号。

## 变更类型

| 字段 | 值 |
|------|----|
| ID | draft-20260610-chipgroup-material-background |
| 类型 | feature |
| 标题 | ChipGroup 新增支持新材质的背景配置能力 |
| Profile | arkui (子 profile: arkui/component) |
| Lineage | new-on-legacy（在存量 ChipGroup 组件上新增材质背景能力） |
| 复杂度 | standard |

## 状态历史

| 日期 | 阶段 | 状态 | 说明 |
|------|------|------|------|
| 2026-06-10 | 定义 | Draft | 初始创建，原始需求记录 |
| 2026-06-10 | 定义 | Clarifying | 澄清完成，待基线审批 |
| 2026-06-10 | 定义 | Blocked | FuncID/FeatID 和 Owner 未确认，按 arkui profile 必检规则阻塞 |
| 2026-06-10 | 定义 | Clarifying | FuncID=07-01-02, FeatID=Feat-01, Owner=youzhi92, 优先级=P0, 提出人=UX 已确认，阻塞解除 |
| 2026-06-10 | 定义 | Baselined | 需求方确认基线总结，Define 阶段通过 |
| 2026-06-11 | 规格化 | Approved | design.md + spec.md 审阅通过，gate-design 全项通过，用户批准进入 Stage 3 |