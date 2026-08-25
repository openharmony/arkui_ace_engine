---
id: FEAT-20260126978228-arc-navigation-capi
type: feature
title: "ArcSwiper 与 ArcAlphabetIndexer C API（NDK）开放"
spec_schema: ohos-sdd/v1
profile: arkui
complexity: critical
lineage: new-on-legacy
status: draft
owner: "ArkUI Owner（待确认）"
source_issue: "20260126978228; interface_sdk_c#5447"
created_at: 2026-07-14
updated_at: 2026-07-14
related:
  - https://gitcode.com/openharmony/interface_sdk_c/pull/5447
related_tasks:
  - TASK-001-arc-swiper-capi
  - TASK-002-arc-alphabet-indexer-capi
  - TASK-003-event-lifecycle-and-validation
related_decisions:
  - ADR-001-reuse-ng-model
  - ADR-002-paired-event-reset
subprofiles:
  - capi
  - component
profile_source: inferred
code_refs:
  - foundation/arkui/ace_engine
  - interface/sdk_c
commits: []
---

## ArkUI 资产登记

| 字段 | 值 |
|---|---|
| requirement_id | `20260126978228` |
| func_id / feat_id | Owner 尚未分配，Define gate 阻塞（Q-1） |
| long_term_spec_path | Owner 分配 FuncID/FeatID 后确定 |
| long_term_design_path | Owner 分配功能域后确定 |
| spectest_feature_path | C API 无直接 Inspector 入口；实施时评估 SpecTest 桥接或转入组件 unittest/SDK 验证 |
| target_release | OpenHarmony-6.1-Release（推断，待 Owner 终确认 Q-2） |
| interface_truth_source | interface_sdk_c PR #5447（当次会话经 gitcode API 完整读取） |

## Profile 命中声明

- **主 profile**：`arkui`（命中仓 `arkui_ace_engine`；path `interfaces/native/**`、`frameworks/core/components_ng/**`）
- **子 profile**：
  - `capi`（命中 `**/interfaces/native/**`、NDK C ABI 开发）—— 本变更主驱动
  - `component`（命中 `**/components_ng/**/*.cpp/.h`，ArcSwiperPattern/ArcIndexerPattern 复用）
- `sdk-api`（ArkTS `.d.ets`）：本变更不改 ArkTS 声明，N/A
- `render`：不改渲染/布局算法，N/A
