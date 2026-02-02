# Gauge Component Knowledge Base

> **Document Version**: v1.0
> **Update Time**: 2026-01-31
> **Source Code Version**: OpenHarmony ace_engine (master branch)
> **Component Tag**: `GAUGE_ETS_TAG`

---

## Table of Contents

1. [Overview](#overview)
2. [Directory Structure](#directory-structure)
3. [Core Class Hierarchy](#core-class-hierarchy)
4. [Pattern Layer](#pattern-layer)
5. [Model Layer](#model-layer)
6. [Layout Algorithm](#layout-algorithm)
7. [Paint Method](#paint-method)
8. [Property System](#property-system)
9. [Theme System](#theme-system)
10. [Bridge Layer](#bridge-layer)
11. [Execution Flow](#execution-flow)
12. [Complete API List](#complete-api-list)
13. [Key Implementation Details](#key-implementation-details)
14. [Usage Examples](#usage-examples)

---

## Overview

### Component Positioning

**Gauge Component** is a circular data gauge chart component in OpenHarmony ArkUI framework, used to display data as a ring chart. It provides:
- Circular gauge display with value visualization
- Three types: Multi-segment gradient, Single-segment gradient, Monochrome
- Custom indicator support (default or custom icon)
- Ring shadow effects
- Min/max value text display (minimum and maximum values)
- Custom description content
- Child component support (single child)

### Child Components

Gauge component can contain **one child component**.

**Notes**:
- Supported child component types: system components and custom components
- Supports conditional rendering with `if/else`, does NOT support loop rendering with `ForEach` and `LazyForEach`
- Recommended to use Text component to build current value text and auxiliary text
- If child component width/height are in percentage, the baseline range is the rectangle with the outer ring as inscribed circle

### API Version Support

- **Initial Version**: API version 8
- **Widget Capability**: Supported since API version 9
- **Atomic Service API**: Supported since API version 11

### Technical Stack

- **Frontend**: ArkTS/JavaScript
- **Bridge Layer**: GaugeModelNG + GaugeModifier
- **Core Layer**: NG Pattern Architecture
- **Render Layer**: Rosen + Skia

### Code Scale

- Total files: ~26 files
- Core code: ~4,000+ lines C++ code
- 4 architectural layers

### Design Patterns

Gauge component adopts **NG Pattern Architecture** + **Bridge Pattern**:

```
Frontend (ArkTS)
    ↓ (Bridge Layer)
GaugeModelNG (gauge_model_ng.cpp)
    ↓ (NG Pattern Layer)
GaugePattern (gauge_pattern.cpp)
    ↓ (NG LayoutAlgorithm Layer)
GaugeLayoutAlgorithm (gauge_layout_algorithm.cpp)
    ↓
GaugeModifier (gauge_modifier.cpp) → Render Display
```

---

## Directory Structure

## GaugeOptions Object Specification

GaugeOptions is the parameter object when creating a Gauge component (API 18+).

| Name | Type | Required | Description |
|------|------|----------|-------------|
| value | number | No | Current data value of the gauge, indicating the position where the gauge indicator points. Used for presetting the initial value of the gauge when creating the component. **Note**: If value is not within min and max range, min is used as the default value. |
| min | number | No | Minimum value of the current data segment. Default: 0. If max < min, default values 0 and 100 are used. min and max support negative numbers. |
| max | number | No | Maximum value of the current data segment. Default: 100. |

## Directory Structure

```
frameworks/core/components_ng/pattern/gauge/
├── gauge_pattern.h/cpp              # Main pattern logic
├── gauge_model.h                     # Model interface definition
├── gauge_model_ng.h/cpp              # NG model implementation
├── gauge_model_static.h/cpp          # Static model for ArkTS
├── gauge_layout_property.h           # Layout properties
├── gauge_paint_property.h            # Paint properties
├── gauge_layout_algorithm.h/cpp      # Layout calculation
├── gauge_paint_method.h/cpp          # Paint method
├── gauge_modifier.h/cpp              # Drawing modifier
├── gauge_theme.h                     # Theme definitions
├── gauge_accessibility_property.h/cpp# Accessibility support
├── gauge_pattern_multi_thread.cpp    # Multi-thread support
├── BUILD.gn                          # Build configuration
└── bridge/                           # Bridge layer
    ├── gauge_dynamic_modifier.cpp    # Dynamic modifier for ArkTS
    ├── gauge_static_modifier.cpp     # Static modifier for C API
    ├── gauge_dynamic_module.h/cpp    # Dynamic module
    ├── gauge_model_impl.h/cpp        # Model implementation
    ├── arkts_native_gauge_bridge.h/cpp# ArkTS native bridge
    └── content_modifier_helper.h     # Content modifier helper
```

---

## Core Class Hierarchy

```
Pattern (base class)
    ↓
GaugePattern
    ├── Creates: GaugePaintProperty
    ├── Creates: GaugeLayoutProperty
    ├── Creates: GaugeLayoutAlgorithm
    ├── Creates: GaugeAccessibilityProperty
    └── Creates: GaugeModifier → GaugePaintMethod

GaugeModel (abstract interface)
    ↓
GaugeModelNG (implementation)
    └── Static methods for FrameNode manipulation

GaugeLayoutAlgorithm
    ↓
BoxLayoutAlgorithm (base)

GaugeModifier
    ↓
ForegroundModifier (base)

GaugePaintMethod
    ↓
NodePaintMethod (base)
```

---

## Pattern Layer

### GaugePattern Class

**Location**: [gauge_pattern.h](frameworks/core/components_ng/pattern/gauge/gauge_pattern.h)

**Class Definition**:
```cpp
class GaugePattern : public Pattern {
public:
    // Factory methods
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

    // Lifecycle methods
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnSensitiveStyleChange(bool isSensitive) override;
    void OnColorModeChange(uint32_t colorMode) override;
    void OnColorConfigurationUpdate() override;

    // Node management
    bool HasDescriptionNode() const;
    bool HasMinValueTextNode() const;
    bool HasMaxValueTextNode() const;
    bool HasTitleChildNode() const;

    // Content modifier
    void SetBuilderFunc(GaugeMakeCallback&& makeFunc);
    const RefPtr<FrameNode>& GetContentModifierNode() const;
    bool UseContentModifier() const;

private:
    // Child node initialization
    void InitDescriptionNode();
    void InitLimitValueText(int32_t valueTextId, bool isMin);
    void InitIndicatorImage();
    void InitTitleContent();

    // Property updates
    void UpdateStrokeWidth(const CalcDimension& strokeWidth, bool isFirstLoad = false);
    void UpdateIndicatorIconPath(const std::string& iconPath, ...);
    void UpdateIndicatorSpace(const CalcDimension& space, bool isFirstLoad = false);

    // Image loading callbacks
    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    DataReadyNotifyTask CreateDataReadyCallback();
    LoadFailNotifyTask CreateLoadFailCallback();

    // Member variables
    std::optional<int32_t> descriptionNodeId_;
    std::optional<int32_t> minValueTextId_;
    std::optional<int32_t> maxValueTextId_;
    std::optional<int32_t> titleChildId_;
    RefPtr<UINode> descriptionNode_;
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx_;
    RefPtr<CanvasImage> indicatorIconCanvasImage_;
    RefPtr<GaugeModifier> gaugeModifier_;
    RefPtr<FrameNode> contentModifierNode_;
};
```

### Key Responsibilities

1. **Node Management**:
   - Description node (custom content)
   - Limit value text nodes (min/max display)
   - Title child node
   - Content modifier node (for custom UI)

2. **Property Updates**:
   - Stroke width, indicator icon, indicator space
   - Color mode changes
   - Privacy/sensitive style changes

3. **Image Loading**:
   - Indicator icon image loading with callbacks
   - Image data ready, load success, and load failure handling

---

## Model Layer

### GaugeModel (Abstract Interface)

**Location**: [gauge_model.h](frameworks/core/components_ng/pattern/gauge/gauge_model.h)

```cpp
class ACE_FORCE_EXPORT GaugeModel {
public:
    static GaugeModel* GetInstance();

    // Core configuration
    virtual void Create(float values, float min, float max) = 0;
    virtual void SetValue(float value) = 0;

    // Angles and appearance
    virtual void SetStartAngle(float startAngle) = 0;
    virtual void SetEndAngle(float endAngle) = 0;
    virtual void SetStrokeWidth(const Dimension& strokeWidth) = 0;

    // Colors
    virtual void SetColors(const std::vector<Color>& colors, const std::vector<float>& values) = 0;
    virtual void SetGradientColors(
        const std::vector<NG::ColorStopArray>& colors,
        const std::vector<float>& values,
        const NG::GaugeType& type) = 0;
    virtual void ResetGradientColors() = 0;

    // Description and labels
    virtual void SetDescription(const RefPtr<AceType>& customNode) = 0;
    virtual void SetLabelMarkedText(const std::string labelTextString) = 0;
    virtual void SetMarkedTextColor(const Color& color) = 0;
    virtual void SetIsShowLimitValue(bool isShowLimitValue) = 0;
    virtual void SetIsShowDescription(bool isShowDescription) = 0;

    // Shadow
    virtual void SetShadowOptions(const NG::GaugeShadowOptions& shadowOptions) = 0;
    virtual void ResetShadowOptions() = 0;

    // Indicator
    virtual void SetIsShowIndicator(bool isShowIndicator) = 0;
    virtual void SetIndicatorIconPath(const std::string& iconPath,
        const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetIndicatorSpace(const Dimension& space) = 0;
    virtual void ResetIndicatorIconPath() = 0;
    virtual void ResetIndicatorSpace() = 0;

    // Resource support
    virtual void CreateWithResourceObj(GaugeResourceType jsResourceType,
        const RefPtr<ResourceObject>& resObj) = 0;

    // Gradient settings
    virtual void SetUseGradient(bool useGradient) = 0;
    virtual void SetUseSpecialDefaultIndicator(bool useSpecialDefaultIndicator) = 0;
    virtual void SetGradientColorModeInit() = 0;
    virtual void SetGradientInit(const std::vector<NG::ColorStopArray>& colors) = 0;
};
```

### GaugeModelNG (Implementation)

**Location**: [gauge_model_ng.h](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.h)

**Key Static Methods**:
- `CreateFrameNode(float value, float min, float max)`
- `SetValue(FrameNode* frameNode, float value)`
- `SetStartAngle/EndAngle(FrameNode* frameNode, float value)`
- `SetGradientColors(...)`
- `SetBuilderFunc(FrameNode* frameNode, NG::GaugeMakeCallback&& jsMake)`

---

## Layout Algorithm

### GaugeLayoutAlgorithm

**Location**: [gauge_layout_algorithm.h](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.h)

**Key Methods**:

```cpp
class GaugeLayoutAlgorithm : public BoxLayoutAlgorithm {
public:
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;

private:
    void MeasureLimitValueText(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize, bool isMin);
    void MeasureDescription(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize);
    void MeasureTitleChild(LayoutWrapper* layoutWrapper,
        const SizeF& parentSize);
    void MeasureLimitValueTextWidth(LayoutWrapper* layoutWrapper);
    void MeasureFontSize(LayoutWrapper* layoutWrapper);

    bool CheckDescriptionIsImageNode(const RefPtr<LayoutWrapper>& layoutWrapper) const;
    bool GetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, Dimension& fontSize);
    void SetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, const Dimension& fontSize);

    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx_;
    double limitValueTextWidth_ = 0.0;
    double startAngleOffsetX_ = 0.0;
    double endAngleOffsetX_ = 0.0;
};
```

**Layout Calculations** (from gauge_theme.h):

```cpp
constexpr float DESCRIPTION_NODE_WIDTH_RATIO = 0.4444f;
constexpr float DESCRIPTION_NODE_HEIGHT_RATIO = 0.254f;
constexpr float DESCRIPTION_IMAGE_NODE_WIDTH_RATIO = 0.286f;
constexpr float DESCRIPTION_IMAGE_NODE_HEIGHT_RATIO = 0.286f;
constexpr float DESCRIPTION_X = 0.2778f;
constexpr float DESCRIPTION_Y = 0.746f;
constexpr float LIMIT_VALUE_MIN_OR_MAX_HEIGHT_RATIO = 0.2222f;
constexpr float LIMIT_VALUE_Y = 0.722f;
constexpr float INDICATOR_WIDTH_RADIO = 0.135f;
constexpr float INDICATOR_HEIGHT_RADIO = 0.095f;
```

---

## Paint Method

### GaugePaintMethod

**Location**: [gauge_paint_method.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_method.h)

```cpp
class GaugePaintMethod : public NodePaintMethod {
public:
    GaugePaintMethod(const WeakPtr<Pattern>& pattern,
        const RefPtr<GaugeModifier>& gaugeModifier);

    void UpdateForegroundModifier(PaintWrapper* paintWrapper) override;
    RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper) override;
    void SetBoundsRect();

private:
    WeakPtr<Pattern> pattern_;
    RefPtr<GaugeModifier> gaugeModifier_;
    RectF boundsRect_;
};
```

---

## Property System

### colors Property Details

From API version 11, the colors property uses the following rules:

| Parameter Type | Ring Type | Description |
|---------------|-----------|-------------|
| `ResourceColor` | Monochrome ring | Single solid color |
| `LinearGradient` | Gradient ring | Gradient across the entire arc |
| `Array<[ResourceColor\|LinearGradient, number]>` | Multi-segment gradient ring | Multiple color segments with weights, max 9 segments |

**Multi-segment Gradient Ring Rules**:
- Maximum display segments is 9, segments beyond 9 will not be displayed
- First parameter is the color value, if set to non-color type, it becomes `0xFFE84026` (red)
- Second parameter is the color weight, if set to negative or non-numeric type, the weight is reset to 0
- If the corresponding color weight is 0, that color is not displayed in the ring
- If all color weights are 0, the ring is not displayed

**Default Color Rules**:
- If no color is passed, or the array is empty, making it impossible to determine the ring type and color, the ring color is a gradient of `0xFF64BB5C` (green), `0xFFF7CE00` (yellow), `0xFFE84026` (red)
- If a color is passed but the color value is incorrect, that color becomes `0xFFE84026` (red)

### strokeWidth Property Details

| Item | Value |
|------|-------|
| Default | 4 |
| Unit | vp |
| Notes | Sets the ring thickness. Values less than or equal to 0 use the default value; Maximum ring thickness is the radius of the ring, values exceeding the maximum are treated as the maximum; Percentage is NOT supported |

### description Property Details (API 11+)

| Item | Description |
|------|-------------|
| Type | CustomBuilder |
| Notes | Content in @Builder is customized by the developer, Text or Image components are recommended |
| Baseline Range | 44.4% × 25.4% of ring diameter rectangle (28.6% × 28.6% for images) |
| Position | 0vp from the bottom of the ring, centered horizontally |
| Behavior | Setting null does not display content; Not set depends on whether data max/min values are set |

**description Default Behavior**:
- If max/min values are set or only one of them is set, the max/min values are displayed
- If max/min values are not set, content is not displayed
- Max/min values are displayed at the bottom of the ring, position cannot be moved, if the ring opening angle is set improperly, the ring may obscure the text

### trackShadow Property Details (API 11+)

**GaugeShadowOptions** inherits from **MultiShadowOptions**, having all properties of MultiShadowOptions.

| Item | Description |
|------|-------------|
| Shadow Color | Same as ring color |
| Setting null | Shadow effect is disabled |
| radius | Blur radius of the shadow |
| offsetX | X-axis offset of the shadow |
| offsetY | Y-axis offset of the shadow |

### indicator Property Details (API 11+)

**GaugeIndicatorOptions** Object Specification:

| Name | Type | Description |
|------|------|-------------|
| icon | ResourceStr | Icon resource path. If not configured, the system default style (triangle indicator) is used. **Only supports SVG format icons**, other formats will use the default triangle style indicator. |
| space | Dimension | Distance from the indicator to the outer edge of the ring. Default: 8vp; **Percentage is NOT supported**. If set to less than 0, the default value is used; If set to greater than the ring radius, the default value is used. |

### privacySensitive Property Details (API 12+)

Sets privacy sensitive mode for the gauge component.

| Item | Description |
|------|-------------|
| Parameter | `Optional<boolean>` |
| Behavior | When enabled, the gauge indicator points to the min value (0), max/min value text is masked, and the gauge range displays gray or background color |
| Setting null | Privacy mode is disabled |

### contentModifier Property Details (API 12+)

Method to customize the Gauge content area.

**GaugeConfiguration** Object Specification (inherits from CommonConfiguration):

| Name | Type | Description |
|------|------|-------------|
| value | number | Current data value |
| min | number | Current data segment minimum value |
| max | number | Current data segment maximum value |
| enabled | boolean | Whether enabled |

### GaugePaintProperty

**Location**: [gauge_paint_property.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_property.h)

**Properties**:

```cpp
// Value properties
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Min, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Max, float, PROPERTY_UPDATE_RENDER);

// Angle properties
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_RENDER);

// Color properties
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Colors, std::vector<Color>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColors, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<float>, PROPERTY_UPDATE_RENDER);

// Type
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GaugeType, GaugeType, PROPERTY_UPDATE_RENDER);

// Appearance
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShadowOptions, GaugeShadowOptions, PROPERTY_UPDATE_RENDER);

// Indicator
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowIndicator, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorIconSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorSpace, Dimension, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorChange, bool, PROPERTY_UPDATE_RENDER);

// Privacy
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSensitive, bool, PROPERTY_UPDATE_RENDER);

// Gradient settings
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseJsLinearGradient, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseSpecialDefaultIndicator, bool, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColorsInit, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColorModeInit, int, PROPERTY_UPDATE_RENDER);
```

### GaugeType Enum

```cpp
enum class GaugeType : int32_t {
    TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT = 0,  // Multi-segment with weights
    TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT = 1, // Single segment gradient
    TYPE_CIRCULAR_MONOCHROME = 2,              // Single color
};
```

### GaugeShadowOptions Struct

```cpp
struct GaugeShadowOptions {
    bool isShadowVisible = true;
    float radius = DEFAULT_GAUGE_SHADOW_RADIUS;      // Default: 20.0f
    float offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;    // Default: 5.0f
    float offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;    // Default: 5.0f

    // Resource management
    void AddResource(const std::string& key,
        const RefPtr<ResourceObject>& resObj, UpdateFunc&& updateFunc);
    void ReloadResources();
};
```

### GaugeLayoutProperty

**Location**: [gauge_layout_property.h](frameworks/core/components_ng/pattern/gauge/gauge_layout_property.h)

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowLimitValue, bool, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowDescription, bool, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_MEASURE_SELF);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_MEASURE_SELF);
```

---

## Theme System

### GaugeTheme

**Location**: [gauge_theme.h](frameworks/core/components_ng/pattern/gauge/gauge_theme.h)

**Default Values**:

```cpp
// Angle defaults
constexpr float DEFAULT_START_DEGREE = 0.0f;
constexpr float DEFAULT_END_DEGREE = 360.0f;

// Value defaults
constexpr float DEFAULT_MIN_VALUE = 0.0f;
constexpr float DEFAULT_MAX_VALUE = 100.0f;

// Shadow defaults
constexpr float DEFAULT_GAUGE_SHADOW_RADIUS = 20.0f;
constexpr float DEFAULT_GAUGE_SHADOW_OFFSETX = 5.0f;
constexpr float DEFAULT_GAUGE_SHADOW_OFFSETY = 5.0f;

// Stroke defaults
constexpr Dimension TRACK_THICKNESS = 4.0_vp;

// Indicator defaults
constexpr float INDICATOR_WIDTH_RATIO = 0.135f;
constexpr float INDICATOR_HEIGHT_RATIO = 0.087f;
constexpr Dimension INDICATOR_DISTANCE_TO_TOP = 8.0_vp;

// Limit value text
constexpr Dimension LIMIT_VALUE_MAX_FONTSIZE = 40.0_vp;
constexpr int32_t COLORS_MAX_COUNT = 9;

// Default colors
// Note: Default color order is green, yellow, red
constexpr std::vector<Color> GAUGE_DEFAULT_COLOR {
    Color(0xFF64BB5C),  // Green - 0xFF64BB5C
    Color(0xFFF7CE00),  // Yellow - 0xFFF7CE00
    Color(0xFFE84026)   // Red - 0xFFE84026
};

// Color error default value
constexpr Color COLOR_ERROR_DEFAULT = Color(0xFFE84026);  // Red
```

---

## Bridge Layer

### GaugeModifier (Drawing)

**Location**: [gauge_modifier.h](frameworks/core/components_ng/pattern/gauge/gauge_modifier.h)

**Key Drawing Methods**:

```cpp
class GaugeModifier : public ForegroundModifier {
public:
    void onDraw(DrawingContext& context) override;
    void UpdateValue();

private:
    void PaintCircularAndIndicator(RSCanvas& canvas);
    void NewPaintCircularAndIndicator(RSCanvas& canvas);
    void NewDrawIndicator(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);
    void NewDrawImageIndicator(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);

    // Three gauge types
    void PaintMonochromeCircular(RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);
    void PaintSingleSegmentGradientCircular(RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);
    void PaintMultiSegmentGradientCircular(RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);

    // Shadow drawing
    void PaintMonochromeCircularShadow(...);
    void PaintSingleSegmentGradientCircularShadow(...);
    void PaintMultiSegmentGradientCircularShadow(...);

    // Helper methods
    void CalculateStartAndSweepDegree(RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);
    float GetOffsetDegree(RenderRingInfo& data, float oppositeSide);
    bool ShouldHighLight(float start, float interval, float percent);
};
```

### Bridge Layer Files

| File | Purpose |
|------|---------|
| `gauge_dynamic_modifier.cpp` | ArkTS dynamic modifier implementations |
| `gauge_static_modifier.cpp` | Static C API modifier implementations |
| `gauge_model_impl.h/cpp` | Legacy model implementation |
| `arkts_native_gauge_bridge.h/cpp` | ArkTS native bridge |

---

## Execution Flow

### Creation Flow

```
ArkTS: Gauge({ value: 50, min: 0, max: 100 })
    ↓
GaugeModelNG::Create(50, 0, 100)
    ↓
FrameNode::GetOrCreateFrameNode(GAUGE_ETS_TAG, nodeId, GaugePattern)
    ↓
Create PaintProperty (Value=50, Min=0, Max=100)
Create LayoutProperty
Create GaugePattern
    ↓
OnModifyDone() → InitDescriptionNode(), InitLimitValueText(), InitIndicatorImage()
    ↓
Measure (GaugeLayoutAlgorithm)
    ↓
Layout (position child nodes)
    ↓
Paint (GaugeModifier::onDraw)
```

### Value Update Flow

```
ArkTS: gauge.value(75)
    ↓
GaugeModelNG::SetValue(75)
    ↓
ACE_UPDATE_PAINT_PROPERTY(GaugePaintProperty, Value, 75)
    ↓
Mark PROPERTY_UPDATE_RENDER
    ↓
GaugeModifier::UpdateValue() (via GaugePaintMethod)
    ↓
Re-render with new value
```

### Image Loading Flow

```
SetIndicatorIconPath(iconPath, bundleName, moduleName)
    ↓
GaugePaintProperty::UpdateIndicatorIconSourceInfo(ImageSourceInfo)
    ↓
InitIndicatorImage()
    ↓
ImageLoadingContext created with callbacks:
    - OnImageDataReady() → MarkNeedFrameFlushDirty(MEASURE_SELF)
    - OnImageLoadSuccess() → MarkNeedRenderOnly()
    - OnImageLoadFail() → ResetIndicatorIconSourceInfo()
```

---

## Complete API List

### Creation APIs

| API | Description | Location |
|-----|-------------|----------|
| `Create(float value, float min, float max)` | Create gauge with initial values | gauge_model_ng.cpp:25 |
| `CreateFrameNode(float value, float min, float max)` | Static creation method | gauge_model_ng.cpp:181 |

### Value APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetValue(float value)` | Set current value | gauge_model_ng.cpp:43 |
| `SetValue(FrameNode*, float value)` | Static setter | gauge_model_ng.cpp:199 |

### Angle APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetStartAngle(float startAngle)` | Set start angle (degrees) | gauge_model_ng.cpp:48 |
| `SetEndAngle(float endAngle)` | Set end angle (degrees) | gauge_model_ng.cpp:54 |

### Color APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetColors(vector<Color>, vector<float>)` | Set colors with weights (legacy) | gauge_model_ng.cpp:60 |
| `SetGradientColors(vector<ColorStopArray>, vector<float>, GaugeType)` | Set gradient colors | gauge_model_ng.cpp:66 |
| `ResetGradientColors()` | Reset to default colors | gauge_model_ng.cpp:155 |

### Appearance APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetStrokeWidth(Dimension)` | Set ring thickness | gauge_model_ng.cpp:76 |
| `SetShadowOptions(GaugeShadowOptions)` | Set ring shadow | gauge_model_ng.cpp:116 |
| `ResetShadowOptions()` | Reset shadow | gauge_model_ng.cpp:166 |

### Description APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetDescription(RefPtr<AceType>)` | Set custom description node | gauge_model_ng.cpp:82 |
| `SetIsShowDescription(bool)` | Show/hide description | gauge_model_ng.cpp:107 |
| `SetIsShowLimitValue(bool)` | Show/hide min/max values | gauge_model_ng.cpp:102 |

### Indicator APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetIsShowIndicator(bool)` | Show/hide indicator | gauge_model_ng.cpp:138 |
| `SetIndicatorIconPath(string, string, string)` | Set custom indicator icon | gauge_model_ng.cpp:143 |
| `SetIndicatorSpace(Dimension)` | Set distance from indicator to ring edge | gauge_model_ng.cpp:150 |
| `ResetIndicatorIconPath()` | Reset to default indicator | gauge_model_ng.cpp:171 |
| `ResetIndicatorSpace()` | Reset indicator space | gauge_model_ng.cpp:176 |

### Content Modifier APIs

| API | Description | Location |
|-----|-------------|----------|
| `SetBuilderFunc(FrameNode*, GaugeMakeCallback)` | Set custom UI builder | gauge_model_ng.cpp:314 |

---

## Key Implementation Details

### 1. Gauge Type Handling

The component supports three types via `GaugeType` enum:

1. **TYPE_CIRCULAR_MONOCHROME**: Single solid color
2. **TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT**: Gradient across the entire arc
3. **TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT**: Multiple color segments with weights

**Implementation**: `GaugeModifier::onDraw()` in [gauge_modifier.cpp](frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp)

### 2. Limit Value Text Layout

Limit value text positions are calculated using trigonometry based on start/end angles:

```cpp
// From gauge_layout_algorithm.cpp:173-178
auto startDegree = startAngle * ACE_PI / HALF_CIRCLE;
auto endDegree = endAngle * ACE_PI / HALF_CIRCLE;
startAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(startDegree);
endAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(endDegree);
```

### 3. Content Modifier Support

Custom UI can be provided via `GaugeMakeCallback`:

```cpp
using GaugeMakeCallback =
    std::function<RefPtr<FrameNode>(const GaugeConfiguration& gaugeConfiguration)>;

struct GaugeConfiguration : public CommonConfiguration {
    float value_;
    float min_;
    float max_;
};
```

### 4. Shadow Implementation

Ring shadows are rendered before the main gauge ring:

- **Monochrome**: `PaintMonochromeCircularShadow()`
- **Single Segment Gradient**: `PaintSingleSegmentGradientCircularShadow()`
- **Multi Segment Gradient**: `PaintMultiSegmentGradientCircularShadow()`

### 5. Indicator Rendering

Two indicator types:
1. **Default indicator**: Triangle shape drawn with RSPath
2. **Image indicator**: SVG loaded via `ImageLoadingContext`

### 6. Color Mode Change Support

Dark mode support with resource checking:

```cpp
bool CheckDarkResource(uint32_t resId) {
    auto colorMode = Container::CurrentColorMode();
    if (colorMode != ColorMode::DARK) {
        return true;
    }
    // Check if dark resource exists
    return resourceAdapter->ExistDarkResById(std::to_string(resId));
}
```

### 7. Privacy/Sensitive Style

When privacy mode is enabled:
- Limit value text is obscured via `ObscureText()`
- `isSensitive` flag is set on paint property

---

## Usage Examples

### Basic Gauge

```typescript
Gauge({ value: 50, min: 0, max: 100 })
```

### Monochrome Gauge

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(210)
  .endAngle(150)
  .colors('#cca5d61d')  // Single color
  .strokeWidth(18)
```

### Multi-segment Gradient Gauge

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(210)
  .endAngle(150)
  .colors([
    [new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
    [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
    [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
    [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
    [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
    [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
    [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
    [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
    [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]), 1]
  ])
  .strokeWidth(18)
```

### Single-segment Gradient Gauge

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .startAngle(225)
  .endAngle(135)
  .colors(new LinearGradient([
    { color: '#e84026', offset: 0 },
    { color: '#f7ce00', offset: 0.6 },
    { color: '#64bb5c', offset: 1 }
  ]))
  .strokeWidth(18)
```

### Gauge with Custom Indicator

```typescript
Gauge({ value: 50, min: 1, max: 100 })
  .indicator({
    space: 10,
    icon: $r('app.media.indicator')  // SVG format icon
  })
  .startAngle(210)
  .endAngle(150)
  .strokeWidth(18)
```

### Hide Indicator

```typescript
Gauge({ value: 50 })
  .indicator(null)
```

### Gauge with Description

```typescript
@Builder
descriptionBuilder() {
  Text('Description Text')
    .maxFontSize('30sp')
    .minFontSize('10.0vp')
    .fontColor('#fffa2a2d')
    .fontWeight(FontWeight.Medium)
}

Gauge({ value: 50, min: 1, max: 100 })
  .description(this.descriptionBuilder)
```

### Gauge with Child Component

```typescript
Gauge({ value: 50, min: 1, max: 100 }) {
  Column() {
    Text('50')
      .fontWeight(FontWeight.Medium)
      .maxFontSize('60.0vp')
      .minFontSize('30.0vp')
      .textAlign(TextAlign.Center)
    Text('Auxiliary Text')
      .maxFontSize('16.0fp')
      .minFontSize('10.0vp')
  }
}
```

### Privacy Sensitive Mode

```typescript
Gauge({ value: 60, min: 20, max: 100 })
  .startAngle(225)
  .endAngle(135)
  .colors(Color.Red)
  .strokeWidth(18)
  .privacySensitive(true)
```

### Custom Content Modifier (API 12+)

```typescript
@Builder
function buildGauge(config: GaugeConfiguration) {
  Column({ space: 30 }) {
    Text('value: ' + config.value)
    Text('min: ' + config.min)
    Text('max: ' + config.max)
    Gauge({
      value: config.value,
      min: config.min,
      max: config.max
    }).width('50%')
  }
}

class MyGaugeStyle implements ContentModifier<GaugeConfiguration> {
  value: number = 0
  min: number = 0
  max: number = 0

  constructor(value: number, min: number, max: number) {
    this.value = value
    this.min = min
    this.max = max
  }

  applyContent(): WrappedBuilder<[GaugeConfiguration]> {
    return wrapBuilder(buildGauge)
  }
}

Gauge({ value: 20, min: 0, max: 100 })
  .contentModifier(new MyGaugeStyle(30, 10, 100))
```

---

## File References

| File | Lines | Description |
|------|-------|-------------|
| [gauge_pattern.h](frameworks/core/components_ng/pattern/gauge/gauge_pattern.h) | 234 | Main pattern class definition |
| [gauge_pattern.cpp](frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp) | 507 | Pattern implementation |
| [gauge_model_ng.h](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.h) | 94 | NG model interface |
| [gauge_model_ng.cpp](frameworks/core/components_ng/pattern/gauge/gauge_model_ng.cpp) | 471 | NG model implementation |
| [gauge_layout_algorithm.cpp](frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp) | 399 | Layout calculations |
| [gauge_modifier.cpp](frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp) | ~1500+ | Drawing logic |
| [gauge_paint_property.h](frameworks/core/components_ng/pattern/gauge/gauge_paint_property.h) | 312 | Paint properties |
| [gauge_theme.h](frameworks/core/components_ng/pattern/gauge/gauge_theme.h) | 175 | Theme definitions |

---

*For Chinese version, see [docs/pattern/gauge/CLAUDE-CN.md](docs/pattern/gauge/CLAUDE-CN.md)*
