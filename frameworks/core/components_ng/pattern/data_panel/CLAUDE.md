# DataPanel Component - CLAUDE.md

This file provides guidance for Claude Code when working with the DataPanel component in ArkUI ACE Engine.

## Component Overview

The DataPanel component (`DataPanelPattern`) is responsible for rendering data visualization with percentage/ratio display, including:
- Circle type data panel (ring/circular progress)
- Line type data panel (linear progress bar)
- Gradient color support for data segments
- Shadow/glow effects
- Animation effects for data changes
- Custom content modifier support
- Accessibility support

## Architecture

### Class Hierarchy

```
DataPanelPattern
├── Pattern (base class)
├── DataPanelModifier (rendering modifier)
└── DataPanelPaintMethod (paint method)
```

### Core Components

| Component | File | Purpose |
|-----------|------|---------|
| **DataPanelPattern** | `data_panel_pattern.h/cpp` | Main pattern class for DataPanel component |
| **DataPanelLayoutAlgorithm** | `data_panel_layout_algorithm.h/cpp` | Layout algorithm for DataPanel |
| **DataPanelPaintProperty** | `data_panel_paint_property.h/cpp` | Paint properties for DataPanel |
| **DataPanelPaintMethod** | `data_panel_paint_method.h/cpp` | Paint method for rendering |
| **DataPanelModifier** | `data_panel_modifier.h/cpp` | Content modifier for rendering |
| **DataPanelModelNG** | `data_panel_model_ng.h/cpp` | Model interface for DataPanel |
| **DataPanelModelStatic** | `data_panel_model_static.h/cpp` | Static model interface |

## Directory Structure

```
data_panel/
├── data_panel_pattern.h/cpp              # Main pattern implementation
├── data_panel_layout_algorithm.h/cpp     # Layout algorithm
├── data_panel_paint_property.h/cpp       # Paint properties
├── data_panel_paint_method.h/cpp         # Paint method
├── data_panel_modifier.h/cpp             # Content modifier
├── data_panel_model.h/cpp                # Base model interface
├── data_panel_model_ng.h/cpp             # NG model implementation
├── data_panel_model_static.h/cpp         # Static model implementation
├── data_panel_pattern_multi_thread.cpp   # Multi-threading support
└── bridge/                               # Bridge layer files
    ├── data_panel_model_impl.h/cpp       # Model implementation
    ├── data_panel_dynamic_module.h/cpp   # Dynamic module
    ├── data_panel_dynamic_modifier.cpp   # Dynamic modifier
    ├── data_panel_static_modifier.cpp    # Static modifier
    ├── data_panel_content_modifier_helper.h  # Content modifier helper
    └── arkts_native_data_panel_bridge.h/cpp  # ArkTS bridge
```

## Key Data Structures

### DataPanelType
Controls the type of data panel display:
- `CIRCLE` (0): Circular/ring type data panel
- `LINE` (1): Linear progress bar type data panel

### DataPanelShadow
Controls shadow/glow effects:
- `isShadowVisible`: Whether shadow is visible (bool)
- `radius`: Shadow blur radius (double)
- `offsetX`: Horizontal offset (double)
- `offsetY`: Vertical offset (double)
- `colors`: Shadow colors for each data segment (vector<Gradient>)
- `resMap_`: Resource object map for dynamic color updates

### ArcData
Internal structure for circle type rendering:
```cpp
struct ArcData {
    Offset center;                  // Center position
    float progressValue;            // Current progress value
    float radius;                   // Circle radius
    float thickness;                // Stroke width
    double maxValue;                // Maximum value
    double totalValue;              // Total of all values
    Gradient progressColors;        // Progress gradient colors
    Gradient shadowColor;           // Shadow gradient colors
    float drawAngle;                // Angle to draw
    float gradientPointBase;        // Gradient base point
    float lastAngle;                // Last drawn angle
    float totalAllValue;            // Total of all values
    float totalDrawAngle;           // Total draw angle
    float circleAngle;              // Circle angle
};
```

### LinearData
Internal structure for line type rendering:
```cpp
struct LinearData {
    OffsetF offset;                 // Position offset
    Gradient segmentColor;          // Segment color gradient
    Gradient segmentShadowColor;    // Segment shadow gradient
    float segmentWidth;             // Segment width
    float xSegment;                 // X position
    float height;                   // Height
    float totalWidth;               // Total width
    bool isFirstData;               // Is first segment
    bool isEndData;                 // Is last segment
};
```

### DataPanelConfiguration
Configuration object for content modifier:
```cpp
class DataPanelConfiguration : public CommonConfiguration {
    std::vector<double>& values_;   // Data values array
    double maxValue_;               // Maximum value
    bool enabled_;                  // Is enabled (inherited)
};
```

## Paint Properties

### Core Properties
| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `Values` | vector<double> | - | Data values array (max 9 values) |
| `Max` | double | 100.0 | Maximum value for ratio calculation |
| `DataPanelType` | size_t | 0 (CIRCLE) | Type of data panel |
| `Effect` | bool | true | Enable animation and shadow effects |
| `ValueColors` | vector<Gradient> | theme | Color for each data segment |
| `TrackBackground` | Color | '#08182431' | Background track color |
| `StrokeWidth` | Dimension | 24vp | Width of circle stroke |
| `ShadowOption` | DataPanelShadow | theme | Shadow effect options |

### User Set Flags
| Property | Type | Description |
|----------|------|-------------|
| `StrokeWidthSetByUser` | bool | Whether stroke width was set by user |
| `TrackBackgroundSetByUser` | bool | Whether track background was set by user |
| `ValueColorsSetByUser` | bool | Whether value colors were set by user |

## ArkTS API Mapping

| ArkTS API | C++ Property/Method | Description |
|-----------|-------------------|-------------|
| `DataPanel({ values, max, type })` | `DataPanelModelNG::Create()` | Create DataPanel component |
| `.closeEffect(boolean)` | `SetEffect()` / `propEffect_` | Enable/disable animation and shadow |
| `.valueColors(Array<ResourceColor \| LinearGradient>)` | `SetValueColors()` / `propValueColors_` | Set data segment colors |
| `.trackBackgroundColor(ResourceColor)` | `SetTrackBackground()` / `propTrackBackground_` | Set track background color |
| `.strokeWidth(Length)` | `SetStrokeWidth()` / `propStrokeWidth_` | Set circle stroke width |
| `.trackShadow(DataPanelShadowOptions)` | `SetShadowOption()` / `propShadowOption_` | Set shadow effect |
| `.contentModifier(ContentModifier)` | `SetBuilderFunc()` / `makeFunc_` | Set custom content modifier |

### DataPanelOptions Constructor
```cpp
// ArkTS: DataPanel({ values: number[], max: number, type: DataPanelType })
void Create(const std::vector<double>& values, double max, int32_t dataPanelType)
```

## Rendering

### Circle Type (DataPanelType::CIRCLE)

The circle type renders a circular progress ring with:
- Background track (full circle)
- Data segments (arcs proportional to values)
- Optional shadow/glow effect
- Smooth animation on value changes

**Key Drawing Methods**:
- `PaintCircle()`: Main circle drawing entry
- `PaintTrackBackground()`: Draw background track
- `PaintCircleShadow()`: Draw shadow effect
- `PaintCircleProgress()`: Draw progress arcs
- `GetPaintPath()`: Calculate arc paths

**Animation Constants**:
```cpp
constexpr int32_t ANIMATION_DURATION = 1200;  // 1200ms duration
constexpr int32_t ANIMATION_DELAY = 0;        // No delay
constexpr int32_t ANIMATION_TIMES = 1;        // Play once
```

**Spring Curve Parameters**:
```cpp
constexpr float ANIMATION_CURVE_VELOCITY = 0.0f;
constexpr float ANIMATION_CURVE_MASS = 1.0f;
constexpr float ANIMATION_CURVE_STIFFNESS = 110.0f;
constexpr float ANIMATION_CURVE_DAMPING = 17.0f;
```

### Line Type (DataPanelType::LINE)

The line type renders a linear progress bar with:
- Background track
- Data segments (rectangles proportional to values)
- Rounded corners for segments
- Optional shadow effect

**Key Drawing Methods**:
- `PaintLinearProgress()`: Main linear drawing entry
- `PaintBackground()`: Draw background track
- `PaintColorSegment()`: Draw color segments
- `PaintSpace()`: Draw spacing between segments
- `SetCornerRadius()`: Apply rounded corners

## Gradient Support

DataPanel supports linear gradients for both solid colors and complex gradients:

### Creating Solid Gradient
```cpp
static Gradient CreateSolidGradient(Color value) {
    Gradient gradient;
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(value));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(value));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    return gradient;
}
```

### Gradient from Color Pair
```cpp
void CreateGradient(const std::pair<Color, Color>& itemParam, Gradient& gradient) const {
    GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(itemParam.first));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(itemParam.second));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
}
```

## Common Operations

### Creating a DataPanel

```cpp
// Circle type DataPanel
std::vector<double> values = {10, 20, 30, 40};
double max = 100.0;
int32_t type = static_cast<int32_t>(DataPanelType::CIRCLE);
DataPanelModelNG::CreateDataPanelModelNG(values, max, type);
```

### Setting Value Colors

```cpp
// Using model interface
FrameNode* frameNode = ...;
std::vector<Gradient> colors;
// Create gradients...
DataPanelModelNG::SetValueColors(frameNode, colors);

// Using property directly
auto paintProperty = host->GetPaintProperty<DataPanelPaintProperty>();
paintProperty->UpdateValueColors(colors);
```

### Setting Shadow Effect

```cpp
DataPanelShadow shadowOption;
shadowOption.radius = 5.0;
shadowOption.offsetX = 15.0;
shadowOption.offsetY = 15.0;
shadowOption.isShadowVisible = true;
shadowOption.colors = shadowColors;  // vector<Gradient>

DataPanelModelNG::SetShadowOption(frameNode, shadowOption);
```

### Setting Custom Content Modifier

```cpp
// Create a custom content modifier builder
DataPanelMakeCallback makeFunc = [](const DataPanelConfiguration& config) {
    // Build custom content based on config.values_ and config.maxValue_
    return customFrameNode;
};

DataPanelModelNG::SetBuilderFunc(frameNode, std::move(makeFunc));
```

## Resource Management

DataPanel supports dynamic resource updates for theme changes:

### Resource Types
```cpp
enum class DataPanelResourceType {
    TRACK_BACKGROUND_COLOR,
    VALUE_COLORS,
    STROKE_WIDTH
};
```

### Resource Update Pattern
```cpp
// Register resource for shadow colors
shadowOption.AddResource(key, resObj,
    [](const RefPtr<ResourceObject>& resObj, DataPanelShadow& shadow) {
        // Update shadow colors from resource
    });

// Reload all resources
shadowOption.ReloadResources();
```

## Theme Integration

DataPanel integrates with `DataPanelTheme` for default values:

| Theme Property | Type | Description |
|----------------|------|-------------|
| `GetColorsArray()` | vector<pair<Color,Color>> | Default color gradients for segments |
| `GetBackgroundColor()` | Color | Default track background color |
| `GetThickness()` | Dimension | Default stroke width |
| `GetTrackShadowRadius()` | Dimension | Default shadow radius |
| `GetTrackShadowOffsetX()` | Dimension | Default shadow X offset |
| `GetTrackShadowOffsetY()` | Dimension | Default shadow Y offset |

### Color Configuration Update
```cpp
void OnColorConfigurationUpdate() {
    auto dataPanelTheme = pipeline->GetTheme<DataPanelTheme>();
    // Update track background if not set by user
    if (!paintProperty->GetTrackBackgroundSetByUser().value_or(false)) {
        UpdateTrackBackground(dataPanelTheme->GetBackgroundColor(), false);
    }
    // Update stroke width if not set by user
    if (!paintProperty->GetStrokeWidthSetByUser().value_or(false)) {
        UpdateStrokeWidth(dataPanelTheme->GetThickness(), false);
    }
    // Update value colors if not set by user
    if (!paintProperty->GetValueColorsSetByUser().value_or(false)) {
        auto themeColors = dataPanelTheme->GetColorsArray();
        // Convert to gradients and update
    }
}
```

## Layout Algorithm

The `DataPanelLayoutAlgorithm` extends `BoxLayoutAlgorithm`:

```cpp
class DataPanelLayoutAlgorithm : public BoxLayoutAlgorithm {
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper) override;
};
```

Key features:
- Supports match parent and fixed size
- Default alignment is CENTER
- OnDirtyLayoutWrapperSwap triggers repaint on measure changes

## Constants

```cpp
constexpr size_t MAX_COUNT = 9;                // Maximum number of data values
constexpr size_t DEFAULT_VALUE_COUNT = 0;      // Default value count
constexpr float DEFAULT_MAX_VALUE = 100.0f;    // Default max value
constexpr float START_ANGLE = 0.0f;            // Starting angle for circle
```

## Content Modifier

The content modifier system allows custom rendering of DataPanel content:

### Implementation Pattern
```cpp
// 1. Define custom ContentModifier class
class CustomDataPanelModifier : public ContentModifier<DataPanelConfiguration> {
    applyContent(): WrappedBuilder<[DataPanelConfiguration]> {
        return wrapBuilder(buildCustomDataPanel);
    }
};

// 2. Define builder function
@Builder function buildCustomDataPanel(config: DataPanelConfiguration) {
    // Access config.values and config.maxValue
    // Build custom UI
}

// 3. Apply to DataPanel
DataPanel({ values: [...], max: 100, type: DataPanelType.Circle })
    .contentModifier(new CustomDataPanelModifier())
```

### DataPanelConfiguration Access
- `values`: number[] - Current data values (0-9 items, negative values clamped to 0)
- `maxValue`: number - Maximum value for ratio (<= 0 uses sum of values)
- `enabled`: boolean - Whether component is enabled

## Accessibility

DataPanelPattern provides accessibility support through:
- `GetFocusPattern()`: Returns focus pattern with OUTER_BORDER style
- Focus type: NODE
- Focus support: true

## Important Notes

1. **Data Value Limits**: Maximum 9 data values. Values less than 0 are clamped to 0.

2. **Type Immutability**: DataPanelType cannot be changed after creation (not dynamic).

3. **Shadow Color Fallback**: If shadow colors are not specified, they default to valueColors.

4. **Animation**: The circle animation uses a spring curve with specific mass/stiffness/damping values for smooth effect.

5. **RTL Support**: The component respects RTL layout direction via `SetIsRtl()`.

6. **Resource Priority**: User-set properties take precedence over theme values during color configuration updates.

7. **Bounds Calculation**: The bounds rect is calculated to include shadow offsets for proper rendering.

## Related Components

- `ProgressPattern`: Progress indicator component
- `GaugePattern`: Gauge/dial component
- `ArcPattern`: Arc component

## References

- DataPanel theme: `frameworks/core/components/data_panel/data_panel_theme.h`
- Gradient property: `frameworks/core/components_ng/property/gradient_property.h`
- Common configuration: `frameworks/core/components_ng/base/common_configuration.h`
- ArkTS API docs: [ts-basic-components-datapanel.md](../../../../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-basic-components-datapanel.md)
