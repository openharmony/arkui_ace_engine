---
id: ui-session-page-scene-awareness
type: feature
title: UISession page scene rule awareness
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles:
  - component
target_release:
  id: TBD
  name: TBD
  label: TBD
  release_note: TBD
  status: proposed
  source: requirement
  decided_by: User
  decided_at: 2026-06-18
  change_policy: "Only update manifest.md and append release_change_log."
release_change_log:
  - date: 2026-07-21
    summary: "Scope PageScene matching to full-tree scans, viewport-only filtering, node-ID deduplication, and attach/detach-triggered re-evaluation; defer candidate-index performance work."
  - date: 2026-07-13
    summary: "Align PageScene ruleJson version, stable-point text input detection, unregister story, report JSON examples, and test error-code coverage."
complexity: "standard + security/performance"
lineage: new-on-legacy
status: designed
owner: "ACE/UISession owner"
source_issue: "TBD"
created_at: 2026-06-18
updated_at: 2026-07-21
related: []
related_tasks:
  - TASK-001: UISession IPC / ReportService 接口扩展
  - TASK-002: ruleJson 解析、校验和 Manager 状态
  - TASK-003: ArkUI 宿主 TEXT_EDITOR 匹配
  - TASK-004: Web 规则透传通路
  - TASK-005: UIExtension 规则透传通路
  - TASK-006: sample/hidumper 验证命令
  - TASK-007: 单测和回归验证
related_decisions:
  - DEC-001: 页面场景感知独立于 ContentChange / ComponentChange
  - DEC-002: 首批 sceneType 为 TEXT_EDITOR，首版 operator 为 COUNT_GTE
  - DEC-003: Web / UIExtension 提供规则生命周期透传通路
  - DEC-004: 输入类控件上下树只挂起待检测规则，PageScene 在稳定点全量扫描当前页面树；Pipeline 不直接依赖 PageScene flush
  - DEC-005: onlyVisible 仅按当前页面窗口范围过滤；去重只比较命中节点 ID 列表，坐标变化不构成新状态
code_refs:
  - interfaces/inner_api/ui_session
  - adapter/ohos/entrance/ui_session
  - adapter/ohos/entrance/ui_content_impl.cpp
  - frameworks/core/components_ng/manager/content_change_manager
  - frameworks/core/pipeline_ng/pipeline_context.cpp
  - frameworks/core/components_ng/pattern/text_field
  - frameworks/core/components_ng/pattern/search
  - frameworks/core/components_ng/pattern/rich_editor
  - frameworks/core/components_ng/pattern/web
commits: []
legacy_paths: []
---

# Manifest

This manifest is the single source of truth for the CodeSpec identity and release/profile metadata.
