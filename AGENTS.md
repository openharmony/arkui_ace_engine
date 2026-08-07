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
# Build C API tests
./build.sh --product-name rk3568 --build-target linux_unittest_capi --ccache
```

- Test locations:
  - ARM: `out/rk3568/tests/unittest/ace_engine/C-API-Main/components/`
  - X86: `out/rk3568/<x64 target>/tests/unittest/ace_engine/C-API-Main/components/`
- Typical executables: `capi_all_modifiers_test`, `capi_all_accessors_test`, `capi_all_utils_test`, `capi_generated_modifiers_test`.

### Build Outputs Summary

Main output dir: `out/rk3568/arkui/ace_engine/`

- Core engine libraries (`libace*.z.so`):
  - `libace_compatible.z.so`: core library for current ArkUI framework and components, still containing compatibility code paths for legacy/web-style chains
  - `libace_compatible_components.z.so`: split-out compatible components for on-demand loading
  - other examples: `libace_engine_pa_ark.z.so`, `libace_ndk.z.so`, `libace_form_render.z.so`, `libace_xcomponent_controller.z.so`
- Frontend bridge libraries:
  - `libarkts_frontend.z.so`, `libcj_frontend_ohos.z.so`
- Component libraries (`libarkui_*.z.so`):
  - per-component shared libs such as `libarkui_slider.z.so`, `libarkui_checkbox.z.so`
- ArkTS native bridge libraries (`*_ani.so`):
  - ArkTS<->Native bridge libs such as `libanimator_ani.so`, `libarkuicustomnode_ani.so`
- Functional module libraries (`lib*.z.so`):
  - module-oriented libs such as `libanimator.z.so`, `libdialog.z.so`, `libdragcontroller.z.so`
- ArkTS bytecode files (`.abc`):
  - component/runtime bytecode such as `ark*.abc`, `modifier.abc`, `node.abc`, `statemanagement.abc`, `uicontext.abc`

### Frontend Support (Quick)

| Frontend | Language | Use Case |
|----------|----------|----------|
| **Declarative Frontend** | ArkTS dynamic version | Recommended - modern declarative UI |
| **ArkTS Frontend** | ArkTS static version | Incremental engine-based frontend |
| **JavaScript Frontend** | JavaScript | Legacy web-style development |

- ArkTS dynamic version (Declarative Frontend):
  - Path: `frameworks/bridge/declarative_frontend/`
  - Main mode for most apps; uses ArkTS/TS declarative syntax with state management (`@Watch`, `@Link`, `@Prop`) and modifier-based property updates.
  - Corresponds to the dynamic version pipeline (Dynamic API): runtime bridge dispatch in `declarative_frontend`, mainly through `jsview/`, `ark_modifier/`, and `engine/jsi/nativeModule/`.
  - Dynamic API artifacts are typically `*.d.ts` (component APIs) and `*Modifier.d.ts` (modifier APIs), in parallel with static APIs.
- ArkTS static version (ArkTS Frontend):
  - "Static" means ArkTS syntax hardened with static-compilation-friendly constraints (strong typing, fully statically analyzable), executed on the new static ArkTS Runtime.
  - For the static version, ArkUI rebuilds the frontend and state management on top of the koala_projects incremental engine, replacing the dynamic version's `declarative_frontend` runtime-dispatch model.
  - Path: `frameworks/bridge/arkts_frontend/`
  - Static frontend pipeline is based on `koala_projects/` + `arkoala_generator/`, bridged by `libarkts_frontend.z.so`.
  - `frameworks/bridge/arkts_frontend/arkoala_generator/BUILD.gn` provides `idlize_gen`, which installs generated ArkUI static bridge files into `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/`.
  - `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/BUILD.gn` depends on `../../arkoala_generator:idlize_gen` and uses `generate_static_abc("components_compile_abc")` to produce static `.abc` artifacts (e.g. `components.abc`).

## 3. Knowledge Base

Use the KB as the first-stop context before any deep code analysis, and follow the authoring rules below when adding or updating entries. Always treat the KB as context — **then verify against real source code**.

### 3.1 Lookup First

**MANDATORY: Before any code search or analysis on components, architecture, APIs, or patterns, you MUST run a KB query first. Do NOT skip this step and jump straight to source code.**

- Prefer `docs/kb_search.py` for KB lookup:
  - `python3 docs/kb_search.py <keyword>`
- Use KB query results to precisely locate files for follow-up code inspection.
- Use `rg` in `docs/` as a fallback when script results are insufficient.
- Entry points: `docs/knowledge_base_README.md`, `docs/knowledge_base_INDEX.json`, and KB directories under `docs/` (for example: `pattern/`, `common/`, `layout/`, `api/`, `sdk/`, `architecture/`).

#### 3.1.1 Task Routing Rules (KB-first)

- Keep this section rule-based, not an exhaustive scenario catalog.
- Run `python3 docs/kb_search.py <keyword>` with 1-2 core keywords and read the top matching 1-3 KB docs first.
- If KB hits are weak or ambiguous, refine query (`--field`, second keyword) and fallback to `rg -n "<keyword>" docs`.
- After KB routing, verify only in real source code and tests (typically `frameworks/`, `interfaces/`, `test/`) before concluding.

Before editing any file, the agent MUST state:
1. Task category (from the routing table above)
2. KB documents read (or explicitly state "no KB hit")
3. Constraints found that apply to this change

### 3.2 Task Routing Table

| Task | Read this KB category / doc first |
|---|---|
| UI component behavior / Pattern / Model | `docs/kb/components/<category>/` |
| Layout algorithm / render pipeline / scheduling | `docs/kb/architecture/layout-framework.md`, `docs/kb/architecture/basic-render-pipeline.md` |
| C API / NAPI / NDK Modifier | `docs/kb/api/` |
| ArkTS declarative syntax / compiler / frontend | `docs/kb/syntax/` |
| Drag / gesture / event / accessibility | `docs/kb/architecture/drag-framework.md`, `docs/kb/architecture/event-base-framework.md`, `docs/kb/architecture/accessibility.md` |
| Resource / theme / multi-instance | `docs/kb/architecture/resource-access.md`, `docs/kb/architecture/theme-framework.md`, `docs/kb/architecture/multi-instance-management.md` |
| Bug / stability / regression issue | `docs/kb/issues/` |
| Cross-cutting capability | `docs/kb/capabilities/` |

### 3.3 Vocabulary Routing

| Term | KB lookup |
|---|---|
| FrameNode, Pattern, LayoutProperty, PaintProperty | `docs/kb/architecture/basic-render-pipeline.md` |
| PipelineContext, FlushTask, UITaskScheduler | `docs/kb/architecture/layout-framework.md` |
| Modifier, node_modifier, ArkUIModifier | `docs/kb/api/` or `docs/kb/components/<category>/` |
| CustomNode, CustomSpan, FrameNodeAdapter | `docs/kb/components/custom-node/` |
| LazyForEach, Repeat, Swiper+LazyForEach | `docs/kb/syntax/lazy_for_each.md`, `docs/kb/syntax/repeat.md` |
| DragFrameSuite, DragDropManager | `docs/kb/architecture/drag-framework.md` |
| ComponentReuse, RecycleNode | `docs/kb/architecture/component_reuse_framework.md` |
| Subwindow, Popup, Menu, bindSheet | `docs/kb/architecture/subwindow-mechanism.md` |
| ResourceAdapter, instanceId, dark mode switching | `docs/kb/architecture/resource-dynamic-switching.md` |

### 3.4 Path-based KB Routing

When editing files under a specific path, read the corresponding KB first:

| Path pattern | Read KB |
|---|---|
| `frameworks/core/components_ng/pattern/<comp>/` | `docs/kb/components/<category>/` |
| `frameworks/core/pipeline_ng/` | `docs/kb/architecture/layout-framework.md`, `docs/kb/architecture/basic-render-pipeline.md` |
| `interfaces/native/node/` | `docs/kb/api/` |
| `frameworks/bridge/declarative_frontend/` | `docs/kb/syntax/` |
| `frameworks/bridge/arkts_frontend/` | `docs/kb/syntax/` |
| `frameworks/core/accessibility/` | `docs/kb/architecture/accessibility.md` |
| `frameworks/core/components_ng/pattern/<comp>/*drag*` | `docs/kb/architecture/drag-framework.md` |

### 3.5 Authoring Standard (Minimal)

- Naming/location: use `XXX_Knowledge_Base.md` or `XXX_Knowledge_Base_CN.md`; place under `docs/pattern/<component>/`, `docs/sdk/`, `docs/architecture/`, `docs/common/`, `docs/layout/`, `docs/api/`, `docs/accessibility/` (choose by topic).
- Index metadata (`docs/knowledge_base_INDEX.json`) must include: `name`, `name_cn`, `category`, `type`, `file_path`, `last_updated`, `keywords` (5-15), `aliases` (2-5); recommend `source_paths` and `api_paths`.
- Allowed categories: `basic`, `container`, `selector`, `shape`, `media`, `data_display`, `rich_text`, `advanced`, `sdk`, `system`.
- Required sections in each KB doc: 概述, 目录结构, 核心类继承关系, Pattern层详解, Model层详解, 完整API清单, 关键实现细节, 使用示例, 调试指南, 常见问题.

Quick checks:

```bash
find docs -name "*_Knowledge_Base*.md" -type f | wc -l
python3 -m json.tool docs/knowledge_base_INDEX.json > /dev/null && echo "Valid JSON"
python3 docs/kb_search.py --list-categories
```

Detailed templates/rules: `docs/knowledge_base_README.md`.

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
- For C API related changes:
  - Build `linux_unittest_capi`
  - Run relevant `capi_*` test executables
  - Ensure host binaries are correct architecture (`file <test_binary>`)

### Validation Fallback

If no build/test environment is available:
1. State explicitly that build/test validation was not performed.
2. Provide the exact build and test commands that should be run.
3. Describe expected pass criteria based on code analysis.

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
