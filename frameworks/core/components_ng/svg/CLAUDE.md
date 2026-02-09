# SVG Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the SVG component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [SVG_Knowledge_Base_CN.md](../../../../docs/svg/SVG_Knowledge_Base_CN.md)

---

## Overview

**SVG** (Scalable Vector Graphics) component provides comprehensive SVG parsing and rendering capabilities in ArkUI. It transforms SVG markup into a renderable node tree using SkDOM parser and renders via Rosen/Skia canvas.

**Architecture**: SVG Stream → SkDOM → SvgDom → SvgNode Tree → Canvas Rendering

**Key Features**:
- Full SVG 1.1 parsing support (shapes, paths, gradients, patterns, masks, filters)
- SVG 2.0 feature support (configurable via usrConfigVersion)
- Animation support (animate, animateMotion, animateTransform)
- Effects (filters, masks, clip-paths)
- Dynamic color filling and image color filters
- Smooth edge (blur) effect support
- ViewBox and preserveAspectRatio handling
- Multi-instance sharing (same SvgDom across multiple CanvasImage)

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `svg_dom.h/cpp` | ~100 (h) / ~500+ (cpp) | SVG parsing, DOM tree building, rendering entry point |
| `svg_context.h/cpp` | ~180 (h) / ~190 (cpp) | Parsing context, ID mapping, animator management, style management |
| `parse/svg_node.h/cpp` | ~270 (h) / ~800+ (cpp) | Base class for all SVG elements, drawing pipeline, attribute handling |
| `parse/svg_graphic.h/cpp` | ~240 (h) | Base class for drawable shapes (fill, stroke, gradients) |
| `parse/svg_group.h` | ~45 | Container element (g, use) |
| `parse/svg_svg.h/cpp` | ~50 (h) | Root SVG element, viewBox handling |
| `parse/svg_rect/circle/ellipse/line/polygon/path.h` | ~40 each | Shape element implementations |
| `parse/svg_gradient.h/cpp` | ~45 (h) | Linear and radial gradient support |
| `parse/svg_clip_path/mask/filter.h` | ~40-60 each | Effects implementation |
| `parse/svg_animation.h/cpp` | ~55 (h) | SVG animation support |
| `parse/svg_attributes_parser.h` | ~460 | Attribute parsing utilities and data structures |
| `svg_utils.h/cpp` | ~30 | Utility functions |
| `base/svg_length_scale_rule.h` | Length scale rule for different coordinate systems |
| `base/svg_bounding_box_context.h` | Bounding box calculation |
| `base/svg_filter_context.h` | Filter rendering context |
| `effect/svg_colorfilter_effect.h` | Color filter effects |

**Path**: `frameworks/core/components_ng/svg/`

---

## Core Class Hierarchy

```
                    AceType
                       |
                    SvgNode (parse/svg_node.h:47)
                       |
       +---------------+---------------+---------------+---------------+
       |               |               |               |               |
   SvgGroup       SvgGraphic       SvgQuote      SvgGradient     SvgAnimation
       |               |               |               |               |
   +---+---+       +---+---+       +---+---+           |           animate
   |   |   |       |   |   |       |   |   |           +        animateMotion
SvgSvg SvgG SvgUse Rect Circle Path...  ClipPath     RadialGradient    animateTransform
               Mask           LinearGradient   (parse/svg_gradient.h)
               Filter
               Pattern
```

**Three-Level Inheritance Examples**:
- `SvgMask::SvgQuote::SvgNode`
- `SvgPath::SvgGraphic::SvgNode`
- `SvgSvg::SvgGroup::SvgNode`

---

## SVG Element Support Matrix

| Category | Elements | Status |
|----------|----------|--------|
| **Container** | `<svg>`, `<g>`, `<defs>`, `<use>` | Full Support |
| **Shapes** | `<rect>`, `<circle>`, `<ellipse>`, `<line>`, `<polygon>`, `<polyline>`, `<path>` | Full Support |
| **Gradients** | `<linearGradient>`, `<radialGradient>`, `<stop>` | Full Support |
| **Patterns** | `<pattern>` | Full Support |
| **Clipping** | `<clipPath>` | Full Support |
| **Masking** | `<mask>` | Full Support |
| **Filters** | `<filter>`, `<feBlend>`, `<feColorMatrix>`, `<feComposite>`, `<feFlood>`, `<feGaussianBlur>`, `<feOffset>` | Partial Support |
| **Animation** | `<animate>`, `<animateMotion>`, `<animateTransform>` | Full Support |
| **Images** | `<image>` | Full Support |
| **Text** | `<text>`, `<tspan>` | Limited Support |

---

## Key Properties

### SvgAttributes (Root SVG)

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `viewBox` | Rect | - | Viewport bounds for scaling |
| `x`, `y` | Dimension | 0 | Position |
| `width`, `height` | Dimension | - | SVG size |
| `preserveAspectRatio` | SvgPreserveAspectRatio | ALIGN_XMID_YMID, MEET | Scaling behavior |

### SvgBaseAttribute (All Elements)

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `opacity` | double | 1.0 | Element opacity |
| `fill` | FillState | - | Fill color/pattern |
| `stroke` | StrokeState | - | Stroke color/width |
| `transform` | string | - | CSS transform |
| `transformOrigin` | pair<Dimension, Dimension> | center | Transform origin |
| `clip-path` | string | - | Reference to clipPath |
| `mask` | string | - | Reference to mask |
| `filter` | string | - | Reference to filter |
| `id` | string | - | Element identifier |

### FillState & StrokeState

| Property | Type | Description |
|----------|------|-------------|
| `color` | Color | Fill/stroke color |
| `opacity` | double | Fill/stroke opacity |
| `fillRule` | SvgRuleType | NONZERO or EVENODD |
| `lineWidth` | Dimension | Stroke width |
| `lineCap` | LineCapStyle | BUTT, ROUND, SQUARE |
| `lineJoin` | LineJoinStyle | MITER, ROUND, BEVEL |
| `miterLimit` | double | Miter join limit |
| `lineDash` | LineDash | Dash array and offset |

---

## Common Operations

### Creating an SVG DOM

```cpp
// Verify stream is valid before parsing
if (!svgStream.hasLength() || svgStream.getLength() == 0) {
    LOGE("Invalid or empty SVG stream");
    return;
}

// Parse SVG from stream
RefPtr<SvgDom> svgDom = SvgDom::CreateSvgDom(svgStream, imageSourceInfo);
if (!svgDom) {
    LOGE("Failed to parse SVG");
    return;
}
```

### Drawing SVG

```cpp
// Validate before drawing
if (!svgDom) {
    LOGE("SvgDom is null");
    return;
}

// Check layout size validity
if (layoutSize.Width() <= 0 || layoutSize.Height() <= 0) {
    LOGW("Invalid layout size: %{public}f x %{public}f", layoutSize.Width(), layoutSize.Height());
    return;
}

// Draw to canvas with fit mode
svgDom->DrawImage(canvas, ImageFit::CONTAIN, layoutSize);

// Direct drawing with viewport (always check GetRoot() result)
auto root = svgDom->GetRoot();
if (root) {
    root->Draw(canvas, viewPortSize, fillColor);
}
```

### Setting Properties

```cpp
// Set fill color for entire SVG
svgDom->SetFillColor(Color::RED);

// Set smooth edge (blur effect)
svgDom->SetSmoothEdge(1.0f);

// Set color filter
ImageColorFilter filter;
// ... configure filter ...
svgDom->SetColorFilter(filter);
```

### Animation Control

```cpp
// Play all animations
svgDom->ControlAnimation(true);

// Pause all animations
svgDom->ControlAnimation(false);

// Set animation finish callback
svgDom->SetAnimationOnFinishCallback([]() {
    LOGI("Animation finished");
});
```

---

## SVG Element Factories

**Source**: `svg_dom.cpp:58-94`

```cpp
static const LinearMapNode<RefPtr<SvgNode> (*)()> TAG_FACTORIES[] = {
    { "animate", []() -> RefPtr<SvgNode> { return SvgAnimation::Create(); } },
    { "animateMotion", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateMotion(); } },
    { "animateTransform", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateTransform(); } },
    { "circle", []() -> RefPtr<SvgNode> { return SvgCircle::Create(); } },
    { "clipPath", []() -> RefPtr<SvgNode> { return SvgClipPath::Create(); } },
    { "defs", []() -> RefPtr<SvgNode> { return SvgDefs::Create(); } },
    { "ellipse", []() -> RefPtr<SvgNode> { return SvgEllipse::Create(); } },
    { "feBlend", []() -> RefPtr<SvgNode> { return SvgFeBlend::Create(); } },
    { "feColorMatrix", []() -> RefPtr<SvgNode> { return SvgFeColorMatrix::Create(); } },
    { "feComposite", []() -> RefPtr<SvgNode> { return SvgFeComposite::Create(); } },
    { "feFlood", []() -> RefPtr<SvgNode> { return SvgFeFlood::Create(); } },
    { "feGaussianBlur", []() -> RefPtr<SvgNode> { return SvgFeGaussianBlur::Create(); } },
    { "feOffset", []() -> RefPtr<SvgNode> { return SvgFeOffset::Create(); } },
    { "filter", []() -> RefPtr<SvgNode> { return SvgFilter::Create(); } },
    { "g", []() -> RefPtr<SvgNode> { return SvgG::Create(); } },
    { "image", []() -> RefPtr<SvgNode> { return SvgImage::Create(); } },
    { "line", []() -> RefPtr<SvgNode> { return SvgLine::Create(); } },
    { "linearGradient", []() -> RefPtr<SvgNode> { return SvgGradient::CreateLinearGradient(); } },
    { "mask", []() -> RefPtr<SvgNode> { return SvgMask::Create(); } },
    { "path", []() -> RefPtr<SvgNode> { return SvgPath::Create(); } },
    { "pattern", []() -> RefPtr<SvgNode> { return SvgPattern::Create(); } },
    { "polygon", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolygon(); } },
    { "polyline", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolyline(); } },
    { "radialGradient", []() -> RefPtr<SvgNode> { return SvgGradient::CreateRadialGradient(); } },
    { "rect", []() -> RefPtr<SvgNode> { return SvgRect::Create(); } },
    { "stop", []() -> RefPtr<SvgNode> { return SvgStop::Create(); } },
    { "style", []() -> RefPtr<SvgNode> { return SvgStyle::Create(); } },
    { "svg", []() -> RefPtr<SvgNode> { return SvgSvg::Create(); } },
    { "use", []() -> RefPtr<SvgNode> { return SvgUse::Create(); } },
};
```

> **Note**: Current factory functions lack null pointer checks. Consider adding error handling for production use or when adding new elements:

```cpp
// Recommended improvement (with null pointer check)
{ "animate", []() -> RefPtr<SvgNode> {
    auto node = SvgAnimation::Create();
    CHECK_NULL_RETURN(node, nullptr);  // Add null pointer check
    return node;
} },
```

---

## Important Implementation Details

### 1. SVG Parsing Flow

**Source**: `svg_dom.cpp:128-144`

```cpp
bool SvgDom::ParseSvg(SkStream& svgStream)
{
    // 1. Build XML DOM using Skia
    SkDOM xmlDom;
    if (!xmlDom.build(svgStream)) {
        LOGE("Failed to parse xml file.");
        return false;
    }

    // 2. Translate to SvgNode tree
    root_ = TranslateSvgNode(xmlDom, xmlDom.getRootNode(), nullptr);
    CHECK_NULL_RETURN(root_, false);

    // 3. Extract SVG metadata
    auto svg = AceType::DynamicCast<SvgSvg>(root_);
    svgSize_ = svg->GetSize();
    viewBox_ = svg->GetViewBox();
    svgContext_->SetRootViewBox(viewBox_);

    return true;
}
```

### 2. Drawing Pipeline

**Source**: `svg_node.cpp`

```
Draw() entry point
    ↓
OnCanvas() - Check canvas validity
    ↓
OnClipPath() - Apply clipping if specified
    ↓
OnMask() - Apply masking if specified
    ↓
OnFilter() - Apply filters if specified
    ↓
OnTransform() - Apply transformations
    ↓
OnDraw() - Element-specific drawing
    ├─ Graphic shapes: Fill and/or Stroke
    ├─ Groups: Recursively draw children
    └─ Quotes: Draw as reference (defs, mask, etc.)
    ↓
Restore canvas state
```

### 3. Attribute Inheritance

**Flags controlling inheritance behavior** (`svg_node.h:261-265`):

| Flag | Description | Typical Values |
|------|-------------|----------------|
| `hrefFill_` | Inherit fill attributes from href reference | Graphic: true, Quote: true |
| `hrefRender_` | Inherit render attributes (mask, filter, transform) | Graphic: true, Quote: false |
| `passStyle_` | Pass style attributes to children | Group: true, Graphic: false |
| `inheritStyle_` | Inherit style from parent | Most: true, Defs/Mask/Filter: false |
| `drawTraversed_` | Enable OnDraw traversal | Most: true, Defs: false |

### 4. Coordinate System & Length Scaling

**SvgLengthScaleRule** handles different coordinate systems:

| Unit Type | Description |
|-----------|-------------|
| `USER_SPACE_ON_USE` | Use current user coordinate system |
| `OBJECT_BOUNDING_BOX` | Use bounding box of referenced element |
| `STROKE_WIDTH` | Relative to stroke width |

### 5. SVG Context Management

**Source**: `svg_context.h`

```cpp
class SvgContext {
    // ID to node mapping for href references
    std::unordered_map<std::string, WeakPtr<SvgNode>> idMapper_;

    // Animator management for animations
    std::unordered_map<int32_t, WeakPtr<Animator>> animators_;

    // CSS class style mapping
    ClassStyleMap styleMap_;

    // ViewBox and ViewPort
    Rect rootViewBox_;
    Size viewPort_;

    // Dimension normalization function
    FuncNormalizeToPx funcNormalizeToPx_;

    // Multi-instance callbacks
    std::map<WeakPtr<CanvasImage>, FuncAnimateFlush> animateCallbacks_;
};
```

### 6. ViewBox & preserveAspectRatio

**Source**: `svg_attributes_parser.h:31-52`

```cpp
enum class SvgAlign {
    ALIGN_XMIN_YMIN, ALIGN_XMIN_YMID, ALIGN_XMIN_YMAX,
    ALIGN_XMID_YMIN, ALIGN_XMID_YMID, ALIGN_XMID_YMAX,
    ALIGN_XMAX_YMIN, ALIGN_XMAX_YMID, ALIGN_XMAX_YMAX,
    ALIGN_NONE
};

enum class SvgMeetOrSlice {
    MEET,   // Scale to fit within viewport
    SLICE   // Scale to cover viewport
};
```

---

## SVG 2.0 Feature Support

**Version Control**: `svg_context.h:154-162`

```cpp
enum SVG_FEATURE_SUPPORT {
    SVG_FEATURE_SUPPORT_UNDEFINE = 0,
    SVG_FEATURE_SUPPORT_TWO = 2,  // SVG 2.0 features
};

// Enable SVG 2.0 features
svgContext_->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
```

**SVG 2.0 Elements**: New gradient implementations in `TAG_FACTORIES_SVG2`:
- `SvgLinearGradient` (SVG 2.0 version)
- `SvgRadialGradient` (SVG 2.0 version)

---

## Debugging

### Dump Commands

```bash
# View SVG component info
hidumper -s WindowManagerService -a '-a Svg'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'

# Get SVG dump info
svgDom->GetDumpInfo();
```

### Log Tag

SVG component uses `AceLogTag::ACE_IMAGE` for logging.

### Common Issues

| Issue | Check |
|-------|-------|
| SVG not rendering | Check ParseSvg() return value, verify SVG syntax |
| Gradients not showing | Verify gradient ID references, check stop colors |
| Animations not playing | Verify isStatic flag, check animator registration |
| ClipPath/Mask not working | Check href references, verify coordinate system |
| ViewBox scaling incorrect | Check preserveAspectRatio settings |

---

## Execution Flow

```
Image Component / CanvasImage
    ↓
SvgDom::CreateSvgDom(svgStream, imageSourceInfo)
    ↓
SvgDom::ParseSvg()
    ├── SkDOM::build() - Parse XML
    └── TranslateSvgNode() - Build SvgNode tree
    └── Extract viewBox, size
    ↓
CanvasImage::OnDraw()
    ↓
SvgDom::DrawImage(canvas, imageFit, layout)
    ↓
FitImage() - Apply viewBox scaling
    ↓
SvgNode::Draw(canvas, viewPort, fillColor)
    ↓
[Drawing Pipeline]
    ├── OnClipPath()
    ├── OnMask()
    ├── OnFilter()
    ├── OnTransform()
    ├── OnDraw() - Per-element drawing
    └── Children traversal for containers
    ↓
Canvas rendering via Rosen/Skia
```

---

## ArkTS API Reference

```typescript
// SVG Image component
Image($r('app.media.example_svg'))
  .width(200)
  .height(200)
  .fillColor(Color.Red)        // Set fill color
  .matchTextDirection(true)    // Auto-mirror for RTL

// SVG in custom drawing
@Component
struct SvgCanvas {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  build() {
    Canvas(this.context)
      .width('100%')
      .height('100%')
      .onReady(() => {
        // Draw SVG programmatically
      })
  }
}
```

---

## References

- **Knowledge Base**: [SVG_Knowledge_Base_CN.md](../../../../docs/svg/SVG_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **SVG Specification**: [W3C SVG 1.1](https://www.w3.org/TR/SVG11/), [SVG 2.0](https://www.w3.org/TR/SVG2/)
- **Skia Documentation**: [Skia XML DOM](https://api.skia.org/classSkDOM.html)
- **Related**: CanvasImage component, Image component, Rosen rendering engine
