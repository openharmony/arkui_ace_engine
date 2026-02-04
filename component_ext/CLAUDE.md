# CLAUDE.md

This file provides guidance to Claude Code when working in `component_ext/`.

## Overview

`component_ext/` hosts **ArkUI extension components** that are built as separate shared libraries. Most components here follow a common pattern:

- **JS/ETS front-end definitions** (`arkui_*.js` or `.ets`) that expose the ArkUI API.
- **NAPI or ANI bridge** in C++ that parses JS/ETS inputs and forwards to NG models.
- **NG component integration** (notably for MovingPhoto) that owns lifecycle, layout, and rendering.

## Directory Layout

```
component_ext/
├── arc_alphabet_indexer/          # ArcAlphabetIndexer: JS + NAPI bridge to IndexerModelNG
├── arc_list/                      # ArcList: JS modifiers + NAPI bridge to ListModelNG
├── arc_scroll_bar/                # ArcScrollBar: JS + NAPI bridge to ScrollBarModelNG
├── arc_swiper/                    # ArcSwiper: JS + NAPI bridge to SwiperModelNG
├── movingphoto/                   # MovingPhotoView NG component + NAPI bridge
├── movingphoto_ani/               # MovingPhotoView ArkTS/ANI bridge (ETS + ANI C++)
├── ext_common/                    # Shared NAPI utilities (ExtNapiUtils, NapiAsyncEvent)
└── BUILD.gn                       # Group target wiring all component_ext libs
```

## Build & Packaging Patterns

### Arc Components (`arc_*`)
- Each `arc_*` directory compiles its JS file to an `.abc` via `es2abc_gen_abc` and embeds it into the shared library via `gen_obj`.
- The C++ NAPI module exports `NAPI_arkui_*_GetABCCode` and registers `nm_modname` (e.g., `"arkui.ArcList"`).
- Output libraries install to `module/arkui` (`relative_install_dir = "module/arkui"`).

### MovingPhoto
- `multimedia_movingphotoview.js` compiles to `.abc` and is embedded into `movingphotoview`.
- `movingphotoview` installs to `module/multimedia`.
- `movingphoto_ani` builds a **static ArkTS ABC** from `ets/movingphotoview.ets` using `generate_static_abc` and packages it via `ohos_prebuilt_etc`.

## Component Notes

### ArcAlphabetIndexer
- **JS entry**: `component_ext/arc_alphabet_indexer/arkui_arcalphabetindexer.js`
- **Bridge**: `component_ext/arc_alphabet_indexer/arc_alphabet_indexer_napi.cpp`
- **Model**: `core/components_ng/pattern/indexer/indexer_model_ng.h`
- `JsCreate` expects an object containing `arrayValue` and optional `selected`.

### ArcList
- **JS entry**: `component_ext/arc_list/arkui_arclist.js` (ModifierMap-based modifiers)
- **Bridge**: `component_ext/arc_list/arc_list_napi.cpp`
- **Model**: `core/components_ng/pattern/list/*`
- NAPI exposes a `modifier` object with `reset*/set*` APIs used by JS modifiers.

### ArcScrollBar
- **JS entry**: `component_ext/arc_scroll_bar/arkui_arcscrollbar.js`
- **Bridge**: `component_ext/arc_scroll_bar/arc_scroll_bar_napi.cpp`
- **Model**: `core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h`
- `JsCreate` can wire a `JSScroller` to a `ScrollBarProxy`.

### ArcSwiper
- **JS entry**: `component_ext/arc_swiper/arkui_arcswiper.js`
- **Bridge**: `component_ext/arc_swiper/arc_swiper_napi.cpp`
- **Model**: `core/components_ng/pattern/swiper/swiper_model_ng.h`
- `arc_swiper_indicator.h` defines `JsArcSwiperIndicator` for arc-dot styling.
- `arc_swiper_controller.h` exposes `ShowNext`, `ShowPrevious`, `FinishAnimation`.

### MovingPhotoView (JS + NAPI)
- **JS entry**: `component_ext/movingphoto/multimedia_movingphotoview.js`
- **Bridge**: `component_ext/movingphoto/movingphoto_napi.cpp`
- **Model & NG**: `component_ext/movingphoto/movingphoto_model_ng.*`, `movingphoto_pattern.*`
- **Layout**: `movingphoto_layout_algorithm.*`, `movingphoto_layout_property.h`, `movingphoto_styles.h`
- **Events**: `movingphoto_event_hub.h` (onComplete/onStart/onStop/onPause/onFinish/onError/onPrepared)
- **Controller**: `movingphoto_controller.h` (playback/control callbacks)
- **Node**: `movingphoto_node.*` (custom FrameNode, manages image/video/column child nodes)

Typical flow:
```
multimedia_movingphotoview.js
  -> movingphoto_napi.cpp (NAPI)
    -> MovingPhotoModelNG
      -> MovingPhotoNode + MovingPhotoPattern
        -> Layout/Render/MediaPlayer/EventHub
```

### MovingPhotoView (ArkTS / ANI)
- **ETS API**: `component_ext/movingphoto_ani/ets/movingphotoview.ets`
- **ANI bridge**: `component_ext/movingphoto_ani/src/movingphotoview_ani.*`
- ArkTS calls `MovingPhotoNative.*` which maps to ANI functions that forward to `MovingPhotoModelNG` and `MovingPhotoController`.

## Change Checklist

- Keep **JS/ETS API**, **NAPI/ANI bindings**, and **NG model/pattern** updates in sync.
- Match JS `requireInternal/requireNapi` module names with `nm_modname` in NAPI registration.
- When adding a JS module, update `BUILD.gn` to generate `.abc` and embed it (`es2abc_gen_abc` + `gen_obj`).
- For new MovingPhoto properties, update:
  - `movingphoto_styles.h` + `movingphoto_layout_property.h`
  - `movingphoto_model_ng.*` setters
  - `movingphoto_pattern.*` to apply behavior
- When adding NAPI exports, update the `napi_property_descriptor` lists in the relevant `*_napi.cpp`.
