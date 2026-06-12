---
id: issue-85818-ui-session-arkui-text-translate
type: feature
title: Uisession ArkUI text translate
spec_schema: ohos-sdd/v1
profile: arkui/component
subprofiles:
  - arkui/component
target_release:
  id: TBD
  name: TBD
  label: TBD
  release_note: TBD
  status: proposed
  source: requirement
  decided_by: User
  decided_at: 2026-05-13
  change_policy: "Only update manifest.md and append release_change_log."
release_change_log:
  - from: TBD
    to: TBD
    reason: Initial baseline did not specify product release.
    decided_by: User
    decided_at: 2026-05-13
complexity: "standard + security/performance"
lineage: new-on-legacy
status: implementing
owner: "ACE/Uisession/Text module owner"
source_issue: "https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/85818"
created_at: 2026-05-13
updated_at: 2026-06-11
related: []
related_tasks:
  - TASK-001
  - TASK-002
  - TASK-003
  - TASK-004
  - TASK-005
  - TASK-006
  - TASK-007
related_decisions: []
code_refs:
  - interfaces/inner_api/ui_session
  - adapter/ohos/entrance/ui_session
  - adapter/ohos/entrance/ace_translate_manager.cpp
  - frameworks/core/components_ng/manager/content_change_manager
  - frameworks/core/components_ng/pattern/page_translate
  - frameworks/core/components_ng/pattern/text
  - frameworks/core/components_ng/pattern/text_field
  - frameworks/core/components_ng/pattern/rich_editor
  - frameworks/core/components_ng/pattern/web
commits:
  - 9ab9e42cc81f9da3d8ea4ce3f5ae8f20036d7bf6
legacy_paths:
  - .ai-specs/features/ui-session-arkui-text-translate
---

# Manifest

This manifest is the single source of truth for the CodeSpec identity and release/profile metadata.
