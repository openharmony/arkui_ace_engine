# CodeSpec

This directory stores OpenHarmony SDD deliverables for this repository.

## Layout

- `registry.md`: global index for active features, bugfixes and ADRs.
- `changes/`: feature and bugfix specifications.
- `decisions/`: cross-feature ADRs.
- `migrations/`: migration notes from old SDD layouts.
- `release-views/`: release-oriented derived views.
- `shared/`: shared terms, context packs and verification baselines.
- `archive/`: deprecated or superseded specifications.

The current SDD plugin uses `.codespec/changes/<id>/` as the canonical deliverable location. Older `.ai-specs/` content is retained only as historical compatibility material.

## Gate Files

The latest OHOS SDD stage terms are Define, Specify, Implement and Release. Gate evidence is stored with the ODK-compatible file names:

- `evidence/gates/gate-define.md`: Define
- `evidence/gates/gate-design.md`: Specify
- `evidence/gates/gate-implement.md`: Implement
- `evidence/gates/gate-archive.md`: Release
