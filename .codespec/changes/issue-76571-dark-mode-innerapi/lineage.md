# Lineage

| 字段 | 值 |
|------|----|
| Lineage | new-on-legacy |
| Target Release | `manifest.target_release.id` (OpenHarmony-7.0-Release) |
| Source | existing code + new requirement |
| Original Docs | `.ai-specs/features/FEAT-20260509-dark-mode-innerapi` |
| Source Code Evidence | `frameworks/core/common/resource/resource_parse_utils.h` — 已有全量资源解析实现 |
| Source Code Evidence | `frameworks/core/common/color_inverter.h` — 已有 ColorInverter 单例 |
| Source Code Evidence | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` — 已有 UIContext 部分 API |
| Source Code Evidence | `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` — 已有 Tabs 类 |
| Source Code Evidence | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp:1416` — 已有 CreateWithResourceObj/Handle* 资源对象注册能力 |
| Compatibility Boundary | 现有 ace_kit API 不变，纯新增接口和重载；ResourceParseUtils 采用继承式迁移（ResourceParseUtilsBase 基类在 ace_kit，ResourceParseUtils 派生类在 frameworks），174 个消费者零改动 |
| Migration Status | migrated to `.codespec/changes/feat-20260509-dark-mode-innerapi` on 2026-06-25 |
| Supersedes | `.ai-specs/features/FEAT-20260509-dark-mode-innerapi` |
| Superseded By | - |

## Migration Notes

- `requirement.md` was migrated to `proposal.md` according to the current `.codespec` layout.
- `gates/define.md`, `gates/specify-design.md`, and `gates/implement.md` were migrated to `evidence/gates/gate-define.md`, `gate-design.md`, and `gate-implement.md`.
- A new `evidence/gates/gate-archive.md` placeholder was added so the Release-stage evidence path matches the current CodeSpec convention.
- The old `.ai-specs/` path is retained for historical compatibility and should not be used as the canonical location for new edits.
