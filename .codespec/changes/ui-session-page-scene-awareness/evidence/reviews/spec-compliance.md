# Spec Compliance Review

## 2026-07-13

- `PageSceneRuleManagerTestNg.*` host gtest passed: 8 tests.
- `git diff --check` passed with no whitespace errors.
- `ohos-sdd validate --level all` was run after this evidence file was added; see latest validation result in the working log.

## 2026-08-22

- Formal archive synchronized: `onlyVisible` now describes component-visibility filtering, while
  `rectCulling` independently controls page viewport intersection and defaults to `false`.
- Added acceptance/design/test coverage for transform size, opacity (including ancestors), parent-subtree
  dirty coalescing, stable-point recomputation, and rect calculation gating.
- Node-ID list deduplication remains unchanged; coordinate-only changes do not create a new report.
- `ohos-sdd validate .codespec/changes/ui-session-page-scene-awareness --level all`: 32 checks, 0 broken, 0 warn.
