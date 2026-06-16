# Lineage

| 字段 | 值 |
|------|----|
| Lineage | new-on-legacy |
| Target Release | `manifest.target_release.id` |
| Source | Existing Web translate implementation + new ArkUI text translate requirement |
| Original Docs | `.ai-specs/features/ui-session-arkui-text-translate` |
| Source Code Evidence | `interfaces/inner_api/ui_session`, `adapter/ohos/entrance/ui_session`, `adapter/ohos/entrance/ace_translate_manager.cpp`, `frameworks/core/components_ng/manager/content_change_manager`, `frameworks/core/components_ng/pattern/text`, `frameworks/core/components_ng/pattern/web` |
| Compatibility Boundary | Existing Web-only Uisession translation APIs and Web JS injection behavior must remain compatible; ArkUI translation must not replace original text attributes. |
| Migration Status | migrated to `.codespec/changes/issue-85818-ui-session-arkui-text-translate` on 2026-06-04 |
| Supersedes | `.ai-specs/features/ui-session-arkui-text-translate` |
| Superseded By | - |

## Migration Notes

- `requirement.md` was migrated to `proposal.md` according to the 2026-06-04 SDD plugin update.
- `gates/define.md`, `gates/specify.md`, and `gates/implement.md` were migrated to `evidence/gates/gate-define.md`, `gate-design.md`, and `gate-implement.md`.
- `review.md` moved under `evidence/reviews/` and manual verification evidence moved under `evidence/verification/`.
- The old `.ai-specs/` path is retained for historical compatibility and should not be used as the canonical location for new edits.
