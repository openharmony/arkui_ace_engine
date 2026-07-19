# Lineage

| 字段 | 值 |
|------|----|
| Lineage | new-on-legacy |
| Target Release | `manifest.target_release.id` |
| Source | New UISession page scene awareness requirement |
| Original Docs | None |
| Source Code Evidence | `interfaces/inner_api/ui_session`, `adapter/ohos/entrance/ui_session`, `adapter/ohos/entrance/ui_content_impl.cpp`, `frameworks/core/components_ng/manager/content_change_manager`, `frameworks/core/pipeline_ng/pipeline_context.cpp`, `frameworks/core/components_ng/pattern/text_field`, `frameworks/core/components_ng/pattern/search`, `frameworks/core/components_ng/pattern/rich_editor`, `frameworks/core/components_ng/pattern/web` |
| Compatibility Boundary | New scene awareness must remain independent from existing `ContentChange` and `ComponentChange` event semantics; no ArkTS/Public API is introduced in Stage 1. |
| Migration Status | Native CodeSpec entry created on 2026-06-18 |
| Supersedes | - |
| Superseded By | - |

## Notes

- The Stage 1 baseline was created from user-confirmed SDD discussion on 2026-06-18.
- The first supported scene is `TEXT_EDITOR`.
- Web and UIExtension are treated as child content sources that only receive rule lifecycle pass-through requests in the current scope; internal matching, reporting back to the host, and validation are deferred.
- Stage 3 confirmed the stable-check policy: input control attach/detach only updates count and pending detection rules; PageScene matching is flushed from `ContentChangeManager` page-stable points or VSync end when no scroll, Swiper scroll, or transition is active.
- `PipelineContext` must not directly depend on PageScene rule state or `UiSessionManager::FlushPageSceneNodeChanged`; it only invokes `ContentChangeManager::OnVsyncEnd`.
- Text/Image concrete ContentChange events are not PageScene-only detection points.
