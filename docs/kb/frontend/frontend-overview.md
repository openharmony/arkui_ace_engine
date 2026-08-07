# Frontend Architecture Overview

## Three Frontend Pipelines

| Frontend | Language | Use Case |
|----------|----------|----------|
| **Declarative Frontend** | ArkTS dynamic version | Recommended - modern declarative UI |
| **ArkTS Frontend** | ArkTS static version | Incremental engine-based frontend |
| **JavaScript Frontend** | JavaScript | Legacy web-style development |

## ArkTS Dynamic Version (Declarative Frontend)

- Path: `frameworks/bridge/declarative_frontend/`
- Main mode for most apps; uses ArkTS/TS declarative syntax with state management (`@Watch`, `@Link`, `@Prop`) and modifier-based property updates.
- Corresponds to the dynamic version pipeline (Dynamic API): runtime bridge dispatch in `declarative_frontend`, mainly through `jsview/`, `ark_modifier/`, and `engine/jsi/nativeModule/`.
- Dynamic API artifacts are typically `*.d.ts` (component APIs) and `*Modifier.d.ts` (modifier APIs), in parallel with static APIs.

## ArkTS Static Version (ArkTS Frontend)

- "Static" means ArkTS syntax hardened with static-compilation-friendly constraints (strong typing, fully statically analyzable), executed on the new static ArkTS Runtime.
- For the static version, ArkUI rebuilds the frontend and state management on top of the koala_projects incremental engine, replacing the dynamic version's `declarative_frontend` runtime-dispatch model.
- Path: `frameworks/bridge/arkts_frontend/`
- Static frontend pipeline is based on `koala_projects/` + `arkoala_generator/`, bridged by `libarkts_frontend.z.so`.
- `frameworks/bridge/arkts_frontend/arkoala_generator/BUILD.gn` provides `idlize_gen`, which installs generated ArkUI static bridge files into `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/`.
- `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/BUILD.gn` depends on `../../arkoala_generator:idlize_gen` and uses `generate_static_abc("components_compile_abc")` to produce static `.abc` artifacts (e.g. `components.abc`).
