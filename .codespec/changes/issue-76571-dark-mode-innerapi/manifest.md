---
id: feat-20260509-dark-mode-innerapi
type: feature
title: 深浅色模式 Inner API 扩展
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles:
  - arkui
target_release:
  id: OpenHarmony-7.0-Release
  name: OpenHarmony 7.0
  label: OpenHarmony-7.0-Release
  release_note: Inner API dark mode support for ace_kit consumers.
  status: proposed
  source: requirement
  decided_by: User
  decided_at: 2026-05-09
  change_policy: Only update manifest.md and append release_change_log.
release_change_log:
  - from: none
    to: OpenHarmony-7.0-Release
    reason: Initial migration from legacy .ai-specs retained the approved target release.
    decided_by: User
    decided_at: 2026-05-09
complexity: standard
lineage: new-on-legacy
status: implementing
owner: ""
source_issue: ""
created_at: 2026-05-09
updated_at: 2026-06-25
related: []
related_tasks:
  - TASK-001
  - TASK-002
  - TASK-003
related_decisions: []
code_refs:
  - interfaces/inner_api/ace_kit/include/ui/resource/resource_parse_utils.h
  - interfaces/inner_api/ace_kit/include/ui/view/ui_context.h
  - interfaces/inner_api/ace_kit/include/ui/view/frame_node.h
  - interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h
  - interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h
  - interfaces/inner_api/ace_kit/include/ui/resource/node_info.h
  - interfaces/inner_api/ace_kit/src/view/ui_context_impl.h
  - interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp
  - interfaces/inner_api/ace_kit/src/view/components/tabs.cpp
  - frameworks/core/common/resource/resource_parse_utils.h
  - frameworks/core/common/resource/resource_parse_utils.cpp
  - test/mock/frameworks/core/common/resource/mock_resource_parse_utils.cpp
  - test/mock/interfaces/inner_api/ace_kit/view/mock_ui_context_impl.cpp
  - test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp
  - test/unittest/interfaces/ace_kit/tabs_test.cpp
  - test/unittest/interfaces/ace_kit/BUILD.gn
  - frameworks/core/common/color_inverter.h
  - frameworks/base/utils/system_properties.h
  - frameworks/core/components_ng/pattern/tabs/tabs_model.h
  - frameworks/core/components_ng/pattern/tabs/tabs_model_ng.h
  - frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp
commits: []
legacy_paths:
  - .ai-specs/features/FEAT-20260509-dark-mode-innerapi
---

# Manifest

This manifest is the single source of truth for the CodeSpec identity and release/profile metadata.
