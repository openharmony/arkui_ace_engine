# AGENTS.md

This file defines working rules for agents in `ace_engine`.

## 1. Scope and Priority

- This file applies to `OpenHarmony/foundation/arkui/ace_engine`.
- Direct user instructions take priority over this file.
- Principle: **code first, evidence first, no fabrication**.

## 2. Quick Build and Test

### Build

```bash
# Build ace_engine (from OpenHarmony root)
./build.sh --product-name rk3568 --build-target ace_engine

# Build SDK variant
./build.sh --product-name ohos-sdk --build-target ace_engine

# Build a GN target
./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text:text_pattern
```

### Unit Test / Benchmark Build

```bash
./build.sh --product-name rk3568 --build-target unittest
./build.sh --product-name rk3568 --build-target benchmark_linux
```

### Run Tests

```bash
# Example unit test
./out/rk3568/tests/ace_engine/unittest/components_ng/text/text_pattern_test

# Run a single gtest case
./out/rk3568/tests/ace_engine/unittest/components_ng/text/text_pattern_test --gtest_filter=TextPatternTest.OnModifyDone

# Example benchmark
./out/rk3568/tests/ace_engine/benchmark/text/text_benchmark --benchmark_filter=TextRender
```

### C API Unit Tests

```bash
./build.sh --product-name rk3568 --build-target linux_unittest_capi --ccache
# Executables: out/rk3568/tests/unittest/ace_engine/C-API-Main/components/capi_*_test
```

### Build Outputs

- Main output dir: `out/rk3568/arkui/ace_engine/`
- Detailed library listing: `docs/kb/architecture/build-outputs.md`

### Frontend Support

| Frontend | Language | Use Case |
|----------|----------|----------|
| **Declarative Frontend** | ArkTS dynamic version | Recommended - modern declarative UI |
| **ArkTS Frontend** | ArkTS static version | Incremental engine-based frontend |
| **JavaScript Frontend** | JavaScript | Legacy web-style development |

- Frontend architecture details: `docs/kb/syntax/frontend-overview.md`

## 3. Knowledge Base

Use the KB as the first-stop context before any deep code analysis. Always treat the KB as context — **then verify against real source code**.

### 3.1 Lookup First

**MANDATORY: Before any code search or analysis on components, architecture, APIs, or patterns, you MUST run a KB query first. Do NOT skip this step and jump straight to source code.**

- Prefer `docs/kb_search.py` for KB lookup:
  - `python3 docs/kb_search.py <keyword>`
- Use KB query results to precisely locate files for follow-up code inspection.
- Use `rg` in `docs/` as a fallback when script results are insufficient.
- Entry points: `docs/knowledge_base_README.md`, `docs/knowledge_base_INDEX.json`, and KB directories under `docs/` (for example: `pattern/`, `common/`, `layout/`, `api/`, `sdk/`, `architecture/`).

Before editing any file, the agent MUST state:
1. Task category (from the routing table below)
2. KB documents read (or explicitly state "no KB hit")
3. Constraints found that apply to this change

### 3.2 KB Routing (Task / Term / Path → KB)

| Input | KB lookup |
|---|---|
| **Task: UI component / Pattern / Model** | `docs/kb/components/<category>/` |
| **Task: Layout / render pipeline / scheduling** | `docs/kb/architecture/layout-framework.md`, `docs/kb/architecture/basic-render-pipeline.md` |
| **Task: C API / NAPI / NDK Modifier** | `docs/kb/api/` |
| **Task: ArkTS syntax / compiler / frontend** | `docs/kb/syntax/` |
| **Task: Drag / gesture / event / accessibility** | `docs/kb/architecture/drag-framework.md`, `docs/kb/architecture/event-base-framework.md`, `docs/kb/architecture/accessibility.md` |
| **Task: Resource / theme / multi-instance** | `docs/kb/architecture/resource-access.md`, `docs/kb/architecture/theme-framework.md`, `docs/kb/architecture/multi-instance-management.md` |
| **Task: Bug / stability / regression** | `docs/kb/issues/` |
| **Task: Cross-cutting capability** | `docs/kb/capabilities/` |
| **Term: FrameNode, Pattern, LayoutProperty, PaintProperty** | `docs/kb/architecture/basic-render-pipeline.md` |
| **Term: PipelineContext, FlushTask, UITaskScheduler** | `docs/kb/architecture/layout-framework.md` |
| **Term: Modifier, node_modifier, ArkUIModifier** | `docs/kb/api/` or `docs/kb/components/<category>/` |
| **Term: CustomNode, CustomSpan, FrameNodeAdapter** | `docs/kb/components/custom-node/` |
| **Term: LazyForEach, Repeat, Swiper+LazyForEach** | `docs/kb/syntax/lazy_for_each.md`, `docs/kb/syntax/repeat.md` |
| **Term: DragFrameSuite, DragDropManager** | `docs/kb/architecture/drag-framework.md` |
| **Term: ComponentReuse, RecycleNode** | `docs/kb/architecture/component_reuse_framework.md` |
| **Term: Subwindow, Popup, Menu, bindSheet** | `docs/kb/architecture/subwindow-mechanism.md` |
| **Term: ResourceAdapter, instanceId, dark mode switching** | `docs/kb/architecture/resource-dynamic-switching.md` |
| **Path: `components_ng/pattern/<comp>/`** | `docs/kb/components/<category>/` |
| **Path: `pipeline_ng/`** | `docs/kb/architecture/layout-framework.md`, `docs/kb/architecture/basic-render-pipeline.md` |
| **Path: `interfaces/native/node/`** | `docs/kb/api/` |
| **Path: `bridge/declarative_frontend/` or `bridge/arkts_frontend/`** | `docs/kb/syntax/` |
| **Path: `core/accessibility/`** | `docs/kb/architecture/accessibility.md` |

### 3.3 KB Authoring

- Detailed templates/rules: `docs/knowledge_base_README.md`

## 4. Core Working Principles (Must Follow)

### 4.1 Actual Code Only

- Always read real code via search/read tools before concluding behavior.
- Always cite file path and line when giving code-level conclusions.
- If code is missing, explicitly state: **"此代码在 ace_engine 中未找到"**.
- Do not write hypothetical implementation as fact.

### 4.2 Speculation Management

- Any unverified statement must be labeled **"推测"**.
- Try to verify first; only keep speculation when verification is impossible.

### 4.3 Code-First Verification

- User suggestions may be wrong; verify with source before accepting.
- Resolve disagreements with evidence from implementation.

### 4.4 Error Learning

- If a user correction reveals a doc error, update relevant knowledge base docs.
- Record root cause and prevention in the knowledge base when appropriate.

## 5. Project Map

- `adapter/`: platform adaptation (`ohos/`, `preview/`)
- `advanced_ui_component/`, `advanced_ui_component_static/`: advanced/composite components for the dynamic and static paradigms (counterparts of `@ohos.arkui.advanced.*`).
- `frameworks/base/`: base utilities
- `frameworks/bridge/`: frontend bridge (`declarative_frontend`, `arkts_frontend`, `js_frontend`, `cj_frontend`)
- `frameworks/core/components_ng/`: new-generation component framework (preferred for new development), centered on `FrameNode` + `Pattern` + property/modifier pipelines.
- `frameworks/core/components/`: legacy component framework (DOM/Component/Element/Render style), mainly for historical compatibility and older implementation paths.
- `frameworks/core/pipeline_ng/` (+ legacy `pipeline/`): rendering pipeline, frame scheduling, and task dispatch for `components_ng`.
- `interfaces/native/node/`: C API for components — entry point of the Modifier bridge consumed by NDK scenario (covered by `linux_unittest_capi`).
- `interfaces/napi/kits/`: NAPI implementations for `@ohos.*` modules such as `router`, `promptAction`, `mediaquery`, `animator`, `font`, `measure`, `curves`, `matrix4` (31 subdirectories).
- `test/unittest`, `test/benchmark`: tests

### Frequently Changed Paths

- `frameworks/core/components_ng/pattern/` — most frequent change target (component behavior)
- `frameworks/core/pipeline_ng/` — rendering pipeline changes (high impact)
- `frameworks/bridge/declarative_frontend/` — dynamic API surface changes
- `interfaces/native/node/` — C API / Modifier bridge changes

### Task-to-Path Quick Reference

| Task | Start here |
|---|---|
| Add/modify a UI component | `frameworks/core/components_ng/pattern/<component>/` |
| Change layout algorithm | `frameworks/core/components_ng/pattern/<component>/` + `*_layout_algorithm.*` |
| Fix rendering pipeline | `frameworks/core/pipeline_ng/` |
| Add/modify C API / Modifier | `interfaces/native/node/` → `frameworks/core/components_ng/` modifier bridge |
| Add/modify NAPI | `interfaces/napi/kits/<module>/` |
| Fix dynamic frontend bridge | `frameworks/bridge/declarative_frontend/` |
| Fix static frontend bridge | `frameworks/bridge/arkts_frontend/` |
| Platform adaptation | `adapter/ohos/` |
| Add/modify advanced component | `advanced_ui_component/` or `advanced_ui_component_static/` |
| Add/modify event / gesture | `frameworks/core/components_ng/pattern/` + `*_event_hub.*` |
| Fix accessibility | `frameworks/core/accessibility/` |

### Nested Agent Guidance

| Path | Purpose |
|---|---|
| `.claude/agents/openharmony-build-fix.md` | Build error diagnosis and fix loop |
| `.claude/skills/arkui-api-design/` | ArkUI API design conventions and review rules |
| `.claude/skills/capi-test-fixer/` | C API test failure diagnosis and fix |
| `.claude/skills/capi-test-naming-verifier/` | C API test naming convention verification |

## 6. Component Development Guidance

- Prefer `components_ng` over legacy `components`.
- Typical component files:
  - `*_pattern.*`, `*_model.*`, `*_layout_property.*`, `*_paint_property.*`, `*_event_hub.*`
- Register new components in `frameworks/core/components_ng/components.gni` when needed.
- Keep platform-specific logic in `adapter/`, not in core business logic.

## 7. Testing Guidance

- Test path should mirror source layout.
- Run targeted unit tests for changed modules first, then broader regression tests if impact is large.
- For C API related changes: build `linux_unittest_capi`, run `capi_*` test executables, ensure correct architecture (`file <test_binary>`).

### Validation Fallback

If no build/test environment is available: state explicitly, provide exact commands to run, and describe expected pass criteria.

### Final Response Expectations

When reporting completion, include:
- Files modified (with line counts)
- Build command run and result
- Test command run, gtest filter, and actual passed/failed counts
- Any constraints identified and respected (especially API/ABI/compatibility)

### Done Definition

A task is done when:
1. All modified files compile without errors.
2. Targeted unit tests pass (with gtest filter if applicable).
3. No lint or static analysis regressions introduced.
4. All constraints from Section 8 are respected.
5. Final response includes: files modified, build result, test result, constraints respected.
6. If public API files (`interfaces/native/`, `interfaces/napi/`) were changed, verify no signature/ABI breakage (e.g., diff headers against base branch).

### Lint / Static Analysis

- This repository does not configure `clang-tidy` — agent may skip this step.
- Verify no new warnings in build output instead.

## 8. Hard Boundaries (Do not / Ask before)

Do not (without explicit user confirmation):

- Change public API signatures/semantics/error codes/struct layout under `interfaces/native/` or `interfaces/napi/` (including ABI-risk changes).
- Manually edit generated files under `**/generated/`.
- Add dependencies on other OpenHarmony system modules outside `adapter/` (including `BUILD.gn` `deps/public_deps/data_deps` dependency entries).
- Run destructive or hard-to-recover commands (for example `rm -rf`, `git reset --hard`).
- Change permission checks or trust boundaries without security review.
- Modify logging, DFX instrumentation, or fault attribution behavior without DFX owner review.
- Change persistent data formats, serialization, or cross-version protocol behavior without compatibility review.
- Introduce third-party dependencies without license review (including copying source code snippets from third-party projects).

Ask before:

- Any API/ABI compatibility-impacting change or default behavior change.
- Any new/updated/replaced dependency: `bundle.json` dependency changes; new `deps/public_deps/data_deps` in any `BUILD.gn`.
- Regenerating static ArkTS generated files (must edit `frameworks/bridge/arkts_frontend/arkoala_generator/` first).

### Common Agent Pitfalls

- Forgetting `MarkDirty` / `MarkMeasureDirty` after property changes — layout will not update without explicit dirty marking.
- Mixing `components/` (legacy) and `components_ng/` (new) APIs in the same feature — always use `components_ng/` for new code.
- Holding `RefPtr<Parent>` from child without `WeakPtr` — creates reference cycles that leak memory.
- Assuming `DynamicCast` always succeeds — always null-check the result before dereferencing.
- Editing generated files under `**/generated/` directly instead of modifying the source generator.
- Confusing `declarative_frontend` (dynamic) and `arkts_frontend` (static) — they have different pipelines and APIs.
- Ignoring `OnModifyDone` — property changes that require follow-up logic must be handled in this callback.
- Accessing UI objects from a non-UI thread — must post tasks to the UI thread via `PipelineContext::PostTask` or similar mechanism.
