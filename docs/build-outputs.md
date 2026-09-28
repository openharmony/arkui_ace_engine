# Build Outputs Reference

## Output Directory

Main output dir: `out/rk3568/arkui/ace_engine/`

## Core Engine Libraries (`libace*.z.so`)

- `libace_compatible.z.so`: core library for current ArkUI framework and components, still containing compatibility code paths for legacy/web-style chains
- `libace_compatible_components.z.so`: split-out compatible components for on-demand loading
- Other examples: `libace_engine_pa_ark.z.so`, `libace_ndk.z.so`, `libace_form_render.z.so`, `libace_xcomponent_controller.z.so`

## Frontend Bridge Libraries

- `libarkts_frontend.z.so`, `libcj_frontend_ohos.z.so`

## Component Libraries (`libarkui_*.z.so`)

- Per-component shared libs such as `libarkui_slider.z.so`, `libarkui_checkbox.z.so`

## ArkTS Native Bridge Libraries (`*_ani.so`)

- ArkTS<->Native bridge libs such as `libanimator_ani.so`, `libarkuicustomnode_ani.so`

## Functional Module Libraries (`lib*.z.so`)

- Module-oriented libs such as `libanimator.z.so`, `libdialog.z.so`, `libdragcontroller.z.so`

## ArkTS Bytecode Files (`.abc`)

- Component/runtime bytecode such as `ark*.abc`, `modifier.abc`, `node.abc`, `statemanagement.abc`, `uicontext.abc`
