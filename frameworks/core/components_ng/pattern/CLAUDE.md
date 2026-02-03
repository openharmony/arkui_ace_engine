# CLAUDE.md

This file provides guidance to Codex when working in `frameworks/core/components_ng/pattern`.

## Scope and Inheritance
- This document applies to the Pattern layer under `frameworks/core/components_ng/pattern`.
- All rules from the repository root `CLAUDE.md` apply here.
- If a component folder contains its own `CLAUDE.md`, follow it in addition to this file.

## Quick Start
- Identify the component folder that matches the user request.
- Locate the Pattern class (`*_pattern.h/.cpp`) and read the real code.
- Always cite exact file paths when describing behavior.
- Do not guess; if code is not found, say so and ask for clarification.

## Directory Layout
- Root files:
- `BUILD.gn` defines build rules for Pattern targets.
- `pattern.h` declares core Pattern base types and interfaces.
- `pattern.cpp` provides base Pattern implementations.
- Each component folder typically includes:
- `*_pattern.h/.cpp` for component logic and lifecycle.
- `*_model.h/.cpp` for ArkTS/TS API and node creation.
- `*_layout_property.h/.cpp` for layout-facing properties.
- `*_paint_property.h/.cpp` for render-facing properties.
- `*_layout_algorithm.h/.cpp` for Measure/Layout.
- `*_paint_method.h/.cpp` for drawing.
- `*_event_hub.h/.cpp` for event registration and dispatch.
- `*_accessibility_property.h/.cpp` for a11y metadata.
- `*_theme.h/.cpp` for default styles.
- Optional: `*_modifier.h/.cpp` for dynamic and static modifiers.
- Optional: `*_focus.h/.cpp` for focus navigation rules.

## Component Index (Top Level)
- `ability_component`
- `action_sheet`
- `animator`
- `app_bar`
- `arc_list`
- `arc_scroll`
- `arc_scroll_bar`
- `badge`
- `blank`
- `bubble`
- `button`
- `calendar`
- `calendar_picker`
- `canvas`
- `checkbox`
- `checkboxgroup`
- `common_view`
- `container_modal`
- `container_picker`
- `corner_mark`
- `counter`
- `custom`
- `custom_frame_node`
- `custom_node_ext`
- `data_panel`
- `dialog`
- `divider`
- `effect_component`
- `flex`
- `folder_stack`
- `form`
- `form_button`
- `form_link`
- `gauge`
- `gesture`
- `grid`
- `grid_col`
- `grid_container`
- `grid_row`
- `hyperlink`
- `image`
- `image_animator`
- `indexer`
- `lazy_layout`
- `linear_indicator`
- `linear_layout`
- `linear_split`
- `list`
- `loading_progress`
- `marquee`
- `menu`
- `model`
- `navigation`
- `navigator`
- `navrouter`
- `node_container`
- `overlay`
- `panel`
- `particle`
- `patternlock`
- `picker`
- `picker_utils`
- `plugin`
- `preview_mock`
- `progress`
- `qrcode`
- `radio`
- `rating`
- `recycle_view`
- `refresh`
- `relative_container`
- `remote_window`
- `render_node`
- `rich_editor`
- `rich_editor_drag`
- `root`
- `scroll`
- `scroll_bar`
- `scrollable`
- `search`
- `security_component`
- `select`
- `select_content_overlay`
- `select_overlay`
- `shape`
- `sheet`
- `side_bar`
- `slider`
- `stack`
- `stage`
- `stepper`
- `swiper`
- `swiper_indicator`
- `symbol`
- `tabs`
- `text`
- `text_area`
- `text_clock`
- `text_drag`
- `text_field`
- `text_input`
- `text_picker`
- `texttimer`
- `time_picker`
- `toast`
- `toggle`
- `toolbaritem`
- `ui_extension`
- `union_effect_container`
- `video`
- `view_context`
- `waterflow`
- `web`
- `window_scene`
- `xcomponent`

## Pattern Architecture Overview
- NG architecture flows: Model -> FrameNode -> Pattern -> LayoutAlgorithm -> PaintMethod.
- Pattern owns component state and orchestrates layout, paint, and events.
- LayoutAlgorithm is responsible for Measure and Layout only.
- PaintMethod is responsible for drawing only.

## Responsibility Boundaries
- Pattern handles:
- State storage and synchronization.
- Lifecycle hooks (OnAttach, OnModifyDone, OnDirtyLayoutWrapperSwap).
- Event dispatch and callbacks.
- LayoutAlgorithm selection and configuration.
- Pattern must not:
- Perform final layout positioning.
- Draw directly or access rendering APIs.
- Create child nodes directly (Model is responsible for creation).

## Lifecycle and Invariants
- CreateLayoutProperty -> CreateEventHub -> CreateLayoutAlgorithm is the normal creation order.
- OnModifyDone updates derived state after properties change.
- OnDirtyLayoutWrapperSwap is the sync point after layout.
- Do not read geometry before Measure or before layout completes.
- Keep Pattern state consistent with LayoutAlgorithm state.

## Property System
- Layout properties drive Measure/Layout.
- Paint properties drive rendering.
- Use ACE_UPDATE/ACE_RESET macros to update properties.
- Pick correct update flags (measure, layout, render) to avoid over-invalidation.
- Avoid direct mutation of property objects outside Pattern or Model.

## Model Layer Guidance
- Model parses ArkTS/TS input and creates FrameNode + Pattern.
- When adding new APIs:
- Update the Model, property types, and Pattern usage.
- Update bridge mappings and d.ts declarations if applicable.
- Add or update tests.

## Layout Algorithm Guidance
- Measure must be deterministic and side-effect free.
- Layout should only place children using measured sizes.
- Avoid firing events or touching global state during Measure/Layout.
- Use LayoutWrapper and GeometryNode for size/position.

## Paint Method Guidance
- Paint methods should only read PaintProperty and Geometry data.
- Cache expensive resources when possible.
- Avoid allocations in hot draw paths.
- Do not change Pattern state while painting.

## Event, Gesture, and Focus
- EventHub owns callback registration and dispatch.
- Do not fire events during Measure/Layout.
- Use base classes (e.g., ScrollablePattern) when available.
- Focus and accessibility live in their own property classes.

## Testing and Debugging
- Unit tests live under `test/unittest/core/pattern/<component>`.
- Use `DumpInfo` and `DumpAdvanceInfo` for state inspection.
- Use component log tags for consistent logging.

## Performance Guidance
- Avoid triggering layout from scroll or animation callbacks.
- Batch property updates before invalidation.
- Prefer cached computations where possible.
- Guard against repeated tree traversal in hot paths.

## Change Checklist
- New property:
- Add to layout/paint property class.
- Update Model setters and parsing.
- Apply in Pattern or LayoutAlgorithm/PaintMethod.
- Add tests and update docs if needed.
- New event:
- Add to EventHub and Model.
- Wire dispatch at correct lifecycle point.
- Add tests for ordering and parameters.
- New layout algorithm:
- Implement class and update selection logic.
- Add tests for layout correctness.
- New component:
- Add to build files and registration lists.
- Provide default theme values.
- Add tests and any required docs.

## Common Pitfalls
- Creating child nodes inside Pattern.
- Modifying layout properties during layout.
- Reading geometry before it is valid.
- Firing events in Measure or Layout.
- Breaking public API semantics without compatibility controls.

## References
- Root `CLAUDE.md` for global rules and knowledge base usage.
- Component specific `CLAUDE.md` files for deeper invariants.
