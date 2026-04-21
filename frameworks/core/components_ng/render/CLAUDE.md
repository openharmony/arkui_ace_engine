# Render Module

This file provides guidance for Claude Code (claude.ai/code) when working with code in the `render` module.

## Module Overview

**Render** (`frameworks/core/components_ng/render/`) is the core rendering module of ACE Engine, responsible for converting component trees into images on screen. This module adopts a layered architecture design, supporting multiple graphics engines (Rosen, Skia) through an adapter layer, providing complete 2D rendering capabilities.

## Core Architecture

### Rendering Pipeline Architecture

```
┌─────────────────────────────────────────────────────────┐
│  Component Layer (Components NG)                        │
│  - Pattern: Business logic                             │
│  - LayoutProperty: Layout properties                   │
│  - PaintProperty: Render properties                    │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Render Context Layer (RenderContext)                   │
│  - Node management                                      │
│  - Property synchronization                            │
│  - Transform processing                                │
│  - Effect processing                                   │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Painter Layer                                          │
│  - ImagePainter: Image drawing                         │
│  - ShapePainter: Shape drawing                         │
│  - PathPainter: Path drawing                           │
│  - TextPainter: Text drawing                           │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Adapter Layer                                          │
│  - RosenRenderSurface: Rosen render surface            │
│  - DrawingPainter: Rosen drawing adapter               │
│  - SkiaPainter: Skia drawing adapter                   │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Graphics Engine Layer                                  │
│  - Rosen (OHOS)                                         │
│  - Skia (Cross-platform)                                │
└─────────────────────────────────────────────────────────┘
```

## Directory Structure

### Core Rendering Components (Root Directory)

```
render/
├── render_context.h/cpp              # Render context core class (898 lines)
├── render_property.h                 # Render property definitions
├── paint_property.h                  # Paint property base class
├── paint_wrapper.h                   # Paint wrapper
├── render_surface.h                  # Render surface abstract interface
├── drawing.h                         # Drawing core interface (Rosen API wrapper)
└── canvas_image.h                    # Canvas image abstraction
```

**RenderContext Core Functions**:
- **Node Management**: Add, remove, move child nodes
- **Property Synchronization**: Geometry properties, borders, backgrounds, etc.
- **Transform Processing**: Translation, scaling, rotation, matrix transforms
- **Effect Processing**: Blur, shadows, blend modes, filters
- **Animation Support**: Transition animations, property animations
- **Focus Management**: Focus state drawing, accessibility support

### Painter Series

```
render/
├── image_painter.h/cpp               # Image painter
├── border_image_painter.h/cpp        # Border image painter
├── rect_painter.h/cpp                # Rectangle painter
├── circle_painter.h/cpp              # Circle painter
├── ellipse_painter.h/cpp             # Ellipse painter
├── line_painter.h/cpp                # Line painter
├── polygon_painter.h/cpp             # Polygon painter
├── path_painter.h/cpp                # Path painter
├── shape_painter.h/cpp               # Shape painter (base class)
├── divider_painter.h/cpp             # Divider painter
└── debug_boundary_painter.h/cpp      # Debug boundary painter
```

**Painter Functionality Hierarchy**:
1. **Basic Shapes**: Rectangles, circles, ellipses, lines, polygons
2. **Image Drawing**: Static images, SVGs, animated images
3. **Complex Effects**: Border images, decoration drawing, path drawing
4. **Debug Tools**: Boundary drawing, focus states

### Adapter Layer (adapter/)

```
render/adapter/
├── Surface Management
│   ├── rosen_render_surface.h/cpp    # Rosen render surface (286 lines)
│   └── render_surface.h              # Render surface interface
├── Drawing Adapters
│   ├── drawing_painter.h/cpp         # Rosen drawing adapter
│   ├── sk_painter.h/cpp              # Skia drawing adapter
│   └── drawing_decoration_painter.h  # Decoration painter
├── Image Processing
│   ├── drawing_image.h/cpp           # Rosen image adapter
│   ├── animated_image.h/cpp          # Animated image
│   ├── pixelmap_image.h/cpp          # Pixel map image
│   └── svg_canvas_image.h/cpp        # SVG image
├── Modifiers
│   ├── background_modifier.h/cpp     # Background modifier
│   ├── border_image_modifier.h/cpp   # Border image modifier
│   ├── focus_state_modifier.h/cpp    # Focus state modifier
│   ├── focus_animation_modifier.h/cpp # Focus animation modifier
│   ├── graphic_modifier.h/cpp        # Graphic modifier
│   ├── overlay_modifier.h/cpp        # Overlay modifier
│   └── gradient_style_modifier.h/cpp # Gradient style modifier
├── Text Rendering
│   ├── txt_paragraph.h/cpp           # Text paragraph
│   ├── txt_font_collection.h/cpp     # Font collection
│   └── txt_text_effect.h/cpp         # Text effects
├── Media Playback
│   ├── media_player.h/cpp            # Media player
│   └── rosen_modifier_adapter.h      # Rosen modifier adapter
├── Transition Effects
│   └── rosen_transition_effect.h/cpp # Rosen transition effect
└── Utilities
    ├── image_painter_utils.h/cpp     # Image painter utilities
    ├── matrix_util.h/cpp             # Matrix utilities
    └── component_snapshot.h/cpp      # Component snapshot
```

## Core Features

### 1. Render Context

**Key Interfaces** (`render_context.h:99`):

```cpp
class RenderContext {
public:
    // Node management
    void AddChild(int32_t id, const std::string& tag);
    void RemoveChild(int32_t id);
    void MoveChild(int32_t id, int32_t targetId);

    // Property synchronization
    void SyncGeometryProperties(const GeometryProperty& property);
    void SetBackgroundColor(const Color& color);
    void SetBorderRadius(const Dimension& radius);

    // Transform processing
    void Translate(float x, float y);
    void Scale(float x, float y);
    void Rotate(float angle);
    void SetMatrix(const Matrix4& matrix);

    // Effect processing
    void SetBlurRadius(float radius);
    void SetShadow(const Shadow& shadow);
    void SetBlendMode(BlendMode mode);
};
```

**Usage Example**:
1. Create render context: `RenderContext::Create()`
2. Initialize render surface: `RenderSurface::InitSurface()`
3. Sync component properties: `SyncGeometryProperties()`
4. Apply effects: `SetBlurRadius()`, `SetShadow()`
5. Execute drawing: `FlushContentDrawFunction()`

### 2. Graphics Drawing System

**ImagePainter** (`image_painter.h:28`)
- Supports multiple image fit modes: `ImageFit` (Fill, Contain, Stretch, etc.)
- Supports image repeat: `ImageRepeat`
- Supports image alignment: `Alignment`
- Supports image clipping: Rounded corners, circular, path clipping

**ShapePainter** (`shape_painter.h`)
- Draw rectangles: `DrawRect()`
- Draw circles: `DrawCircle()`
- Draw ellipses: `DrawEllipse()`
- Draw lines: `DrawLine()`
- Draw polygons: `DrawPolygon()`

**PathPainter** (`path_painter.h`)
- Path construction: `MoveTo()`, `LineTo()`, `ArcTo()`
- Bezier curves: `QuadraticBezierTo()`, `CubicBezierTo()`
- Path filling: `FillPath()`
- Path stroking: `StrokePath()`

### 3. Modifier System

**Modifier Types**:

| Modifier | Function | File Location |
|----------|----------|---------------|
| `BackgroundModifier` | Background colors, images, gradients | `adapter/background_modifier.h` |
| `BorderImageModifier` | Border styles, colors, widths | `adapter/border_image_modifier.h` |
| `FocusStateModifier` | Focus state highlighting | `adapter/focus_state_modifier.h` |
| `FocusAnimationModifier` | Focus animation effects | `adapter/focus_animation_modifier.h` |
| `GraphicModifier` | Graphic transforms | `adapter/graphic_modifier.h` |
| `OverlayModifier` | Overlay text, overlays | `adapter/overlay_modifier.h` |
| `GradientStyleModifier` | Gradient styles | `adapter/gradient_style_modifier.h` |

**Usage Flow**:
1. Create modifier instance
2. Configure modifier properties
3. Apply to render node: `RenderContext::FlushContentModifier()`

### 4. Render Surface

**RosenRenderSurface** (`adapter/rosen_render_surface.h:42`)
- Surface configuration and size adjustment
- Buffer management (queue size: 5)
- XComponent/Web component integration
- Keyboard avoidance area
- Surface state change monitoring

**Initialization Flow**:
```cpp
// 1. Create render surface
auto surface = RosenRenderSurface::Create();

// 2. Initialize surface
surface->InitSurface(config);

// 3. Set callbacks
surface->SetSurfaceChangedCallback([](SurfaceConfig config) {
    // Handle surface changes
});

// 4. Connect to window
surface->ConnectToWindow(windowId);
```

### 5. Text Rendering

**TxtParagraph** (`adapter/txt_paragraph.h`)
- Text paragraph layout
- Multi-line text support
- Text alignment options
- Line height and letter spacing control

**TxtFontCollection** (`adapter/txt_font_collection.h`)
- Font collection management
- System font loading
- Custom font registration

**TxtTextEffect** (`adapter/txt_text_effect.h`)
- Text shadow effects
- Text decorations (underline, strikethrough, etc.)
- Text gradients

## Rendering Pipeline

### Complete Rendering Flow

```
1. Render context creation
   └─ RenderContext::Create()
      └─ RosenRenderContext::Create()

2. Render surface initialization
   └─ RenderSurface::InitSurface()
      └─ RosenRenderSurface::CreateNativeWindow()

3. Component property synchronization
   └─ RenderContext::SyncGeometryProperties()
   └─ RenderContext::SetBackgroundColor()
   └─ RenderContext::SetBorderRadius()

4. Draw function registration
   └─ RenderContext::FlushContentDrawFunction()
   └─ RenderContext::FlushForegroundDrawFunction()

5. Modifier application
   └─ RenderContext::FlushContentModifier()
   └─ RenderContext::FlushForegroundModifier()

6. Rendering execution
   └─ DrawingPainter drawing
   └─ ImagePainter image rendering
   └─ Modifier decoration effects
```

### Key Rendering Features

- **Multi-threading support**: `RenderContextMultiThread`
- **Hardware acceleration**: Supports OpenGL, Vulkan
- **Cross-platform adaptation**: Support for different platforms via adapter layer
- **Performance optimization**: Clipping, caching, batching
- **Accessibility support**: Focus states, text reading

## Development Guide

### Adding a New Painter

1. **Define Painter Class**:
   ```cpp
   // render/xxx_painter.h
   class XxxPainter : public ShapePainter {
   public:
       void Draw(Canvas* canvas, const PaintProperty& property) override;
   };
   ```

2. **Implement Drawing Logic**:
   ```cpp
   // render/xxx_painter.cpp
   void XxxPainter::Draw(Canvas* canvas, const PaintProperty& property) {
       // 1. Get Drawing instance
       auto drawing = property.GetDrawing();

       // 2. Draw shape
       drawing->DrawXxx(...);

       // 3. Apply effects
       drawing->Flush();
   }
   ```

3. **Adapter Layer Implementation** (if needed):
   ```cpp
   // render/adapter/drawing_xxx_painter.cpp
   void DrawingXxxPainter::Draw(...) {
       // Rosen drawing implementation
   }
   ```

4. **Register to Render Context**:
   Register new painter in `render_context.cpp`

### Adding a New Modifier

1. **Define Modifier Class**:
   ```cpp
   // render/adapter/xxx_modifier.h
   class XxxModifier : public Modifier {
   public:
       void Apply(Drawing* drawing) override;
       void SetProperty(const XxxProperty& property);
   };
   ```

2. **Implement Modifier Logic**:
   ```cpp
   // render/adapter/xxx_modifier.cpp
   void XxxModifier::Apply(Drawing* drawing) {
       // Apply modifier effect
       drawing->SetXxx(...);
   }
   ```

3. **Apply Modifier**:
   ```cpp
   renderContext->FlushContentModifier(modifier);
   ```

### Debugging Rendering Issues

**Enable Debug Drawing**:
```cpp
// Draw component boundaries
DebugBoundaryPainter::DrawBoundary(renderContext, Color::RED);

// Draw layout information
DebugBoundaryPainter::DrawLayoutInfo(renderContext);
```

**Rendering Logs**:
```cpp
// Set log level
ACE_LOG_LEVEL = DEBUG;

// View rendering calls
ACE_DEBUG(RenderContext, "Draw node: %{public}d", nodeId);
```

## Performance Optimization

### Rendering Optimization Tips

1. **Reduce Drawing Calls**:
   - Batch draw elements of the same type
   - Use offscreen canvas for caching
   - Avoid unnecessary redraws

2. **Use Hardware Acceleration**:
   ```cpp
   // Enable hardware acceleration
   renderContext->SetHardwareAccelerationEnabled(true);
   ```

3. **Clipping Optimization**:
   ```cpp
   // Set clipping region
   renderContext->SetClipRect(Rect(0, 0, width, height));
   ```

4. **Caching Strategies**:
   - Use offscreen buffers for static content
   - Use interpolation optimization for animations
   - Use multi-level caching for images

## Common Issues

### Q: Rendered content not displaying?
A: Check the following items:
1. Render surface correctly initialized: `RosenRenderSurface::InitSurface()`
2. Draw functions correctly registered: `FlushContentDrawFunction()`
3. Called `Flush()` to refresh drawing
4. Check if clipping region is correct

### Q: Blurry image rendering?
A: Check the following items:
1. Image DPI settings: `ImagePainter::SetDpi()`
2. Image fit mode: `ImageFit` parameter
3. Enable anti-aliasing: `drawing->SetAntiAlias(true)`

### Q: Choppy animations?
A: Optimization suggestions:
1. Use offscreen canvas to cache static content
2. Reduce drawing calls per frame
3. Use `RequestFrame` instead of `RequestAllFrames`
4. Enable hardware acceleration

### Q: High memory usage?
A: Optimization suggestions:
1. Release unused resources promptly
2. Use object pooling to reuse drawing objects
3. Limit image cache size
4. Check for memory leaks

## Dependencies

### Upstream Dependencies
- **Components NG**: Component framework
- **Pattern**: Business logic layer
- **Layout**: Layout algorithms

### Downstream Dependencies
- **Rosen**: OHOS graphics engine
- **Skia**: Cross-platform graphics library

### Lateral Dependencies
- **Gestures**: Gesture events
- **Animation**: Animation system
- **Window**: Window management

## Testing

**Unit Tests**:
```bash
# Run render module tests
./build.sh --product-name rk3568 --build-target render_test

# Run painter tests
./build.sh --product-name rk3568 --build-target painter_test
```

**Test Locations**:
- `test/unittest/components_ng/render/`
- `test/unittest/components_ng/render/painter/`

## References

- **Rosen Rendering Documentation**: `adapter/ohos/rosen/README.md`
- **Drawing API Documentation**: `render/drawing.h`
- **Rendering Performance Guide**: `docs/performance/render_optimization.md`

## Key File Index

| File Path | Description | Lines of Code |
|-----------|-------------|---------------|
| `render_context.h:99` | Render context core class | 898 |
| `adapter/rosen_render_surface.h:42` | Rosen render surface | 286 |
| `image_painter.h:28` | Image painter | 156 |
| `drawing_painter.h` | Rosen drawing adapter | 234 |
| `adapter/background_modifier.h` | Background modifier | 189 |
| `adapter/txt_paragraph.h` | Text paragraph | 312 |

## Architecture Design Principles

1. **Layered Decoupling**: Clear separation of core layer, adapter layer, and utility layer
2. **Platform Abstraction**: Support for multiple platforms through adapter layer
3. **Performance First**: Hardware acceleration, batching, caching optimization
4. **Extensibility**: Easy to add new painters and modifiers
5. **Accessibility Support**: Complete focus management and auxiliary functions

This architecture design makes the rendering module maintainable and extensible, capable of supporting complex UI rendering requirements.
