# QRCode Component Knowledge Base

## Table of Contents

- [1. Component Overview](#1-component-overview)
- [2. Directory Structure](#2-directory-structure)
- [3. Architecture Design](#3-architecture-design)
- [4. Pattern Layer](#4-pattern-layer)
- [5. Model Layer](#5-model-layer)
- [6. Property Layer](#6-property-layer)
- [7. Modifier Layer](#7-modifier-layer)
- [8. Layout Algorithm](#8-layout-algorithm)
- [9. Rendering Pipeline](#9-rendering-pipeline)
- [10. Lifecycle](#10-lifecycle)
- [11. Bridge Layer](#11-bridge-layer)
- [12. Test Coverage](#12-test-coverage)

---

## 1. Component Overview

**QRCode** is a component in OpenHarmony ACE Engine for generating and displaying QR codes.

### Core Features

- Encode string content into QR code images
- Support custom QR code color and background color
- Support content opacity settings
- Support theme configuration and system color change response
- Always maintain square layout

### Technical Dependencies

- **qrcodegen library**: For QR code encoding generation (`qrcodegen.hpp`)
- **RSBitmap/RSImage**: Rendering subsystem bitmap and image
- **QrcodeTheme**: Theme configuration management

### Source Location

```
frameworks/core/components_ng/pattern/qrcode/
```

---

## 2. Directory Structure

```
components_ng/pattern/qrcode/
├── qrcode_pattern.h/cpp                    # Main Pattern class
├── qrcode_paint_property.h                 # Paint property definitions
├── qrcode_layout_algorithm.h/cpp           # Layout algorithm
├── qrcode_paint_method.h/cpp               # Paint method
├── qrcode_modifier.h/cpp                   # Core rendering Modifier
├── qrcode_model.h                          # Abstract Model interface
├── qrcode_model_ng.h/cpp                   # NG Model implementation
├── qrcode_model_static.h/cpp               # Static Model implementation
├── qrcode_napi.h/cpp                       # NAPI interface
├── qrcode_modifier.h/cpp                   # Common Modifier
├── arkui_qrcode.js                         # JavaScript interface
└── bridge/                                 # Bridge layer
    ├── arkts_native_qrcode_bridge.h/cpp    # ArkTS Native Bridge
    ├── qrcode_dynamic_module.h/cpp         # Dynamic module
    ├── qrcode_dynamic_modifier.cpp         # Dynamic Modifier
    └── qrcode_static_modifier.cpp          # Static Modifier
```

---

## 3. Architecture Design

### 3.1 Four-Layer Architecture

QRCode component follows the standard NG component four-layer architecture:

```
┌─────────────────────────────────────────────┐
│  Model Layer (qrcode_model_*.h/cpp)         │
│  - Data model and creation interface        │
│  - Property setting API                     │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Pattern Layer (qrcode_pattern.h/cpp)       │
│  - Business logic and lifecycle management  │
│  - Coordinate Model, Property, Modifier     │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Property Layer (qrcode_paint_property.h)   │
│  - Paint property definitions and storage   │
│  - JSON serialization                       │
└─────────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────────┐
│  Modifier Layer (qrcode_modifier.h/cpp)     │
│  - QR code bitmap generation                │
│  - Actual drawing logic                     │
└─────────────────────────────────────────────┘
```

### 3.2 Key Class Relationships

```
QRCodePattern
    ├── QRCodePaintProperty (paint properties)
    ├── QRCodeLayoutAlgorithm (layout algorithm)
    ├── QRCodePaintMethod (paint method)
    │       └── QRCodeModifier (paint execution)
    └── QRCodeTheme (theme)
```

---

## 4. Pattern Layer

### 4.1 QRCodePattern Class

**Location**: `qrcode_pattern.h:31-77`

```cpp
class QRCodePattern : public Pattern
{
public:
    // Create paint property
    RefPtr<PaintProperty> CreatePaintProperty() override;

    // Create layout algorithm
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    // Create paint method
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    // Support parent container size matching
    bool IsEnableMatchParent() override;

    // Property update methods
    void UpdateQRCodeCreate(const std::string& value);
    void UpdateColor(const Color& color, bool isFristLoad = false);
    void UpdateBackgroundColor(const Color& color, bool isFristLoad = false);
    void UpdateContentOpacity(double opacity, bool isFristLoad = false);

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void OnColorConfigurationUpdate() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                                   bool skipMeasure, bool skipLayout) override;

    float qrCodeSize_ = 0.0f;
    RefPtr<QRCodeModifier> qrCodeModifier_;
};
```

### 4.2 Lifecycle Methods

#### OnAttachToFrameNode()

**Location**: `qrcode_pattern.cpp:24-30`

```cpp
void QRCodePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);      // Clip to boundary
    host->GetRenderContext()->UpdateBackgroundColor(Color::WHITE);  // Default white background
}
```

**Functionality**:
- Set clip to frame (`SetClipToFrame`)
- Set default white background

#### OnModifyDone()

**Location**: `qrcode_pattern.cpp:45-58`

```cpp
void QRCodePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // Set default alignment to CENTER
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
}
```

**Functionality**:
- Call parent implementation
- Set default alignment to `Alignment::CENTER`

#### OnDirtyLayoutWrapperSwap()

**Location**: `qrcode_pattern.cpp:32-43`

```cpp
bool QRCodePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                                              bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<QRCodeLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    qrCodeSize_ = layoutAlgorithm->GetQRCodeSize();  // Update QR code size
    return true;
}
```

**Functionality**:
- Update `qrCodeSize_` after layout calculation completes
- Return `true` indicating redraw is needed

#### OnColorConfigurationUpdate()

**Location**: `qrcode_pattern.cpp:179-200`

```cpp
void QRCodePattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(theme);
    auto pops = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(pops);

    // Only use theme colors when user hasn't set colors
    if (!pops->HasQRCodeColorSetByUser() ||
        (pops->HasQRCodeColorSetByUser() && !pops->GetQRCodeColorSetByUserValue())) {
        UpdateColor(theme->GetQrcodeColor(), false);
    }
    if (!pops->HasQRBackgroundColorSetByUser() ||
        (pops->HasQRBackgroundColorSetByUser() && !pops->GetQRBackgroundColorSetByUserValue())) {
        UpdateBackgroundColor(theme->GetBackgroundColor(), false);
    }
}
```

**Functionality**:
- Respond to system color theme changes
- Only update color properties not explicitly set by user

### 4.3 Property Update Methods

#### UpdateColor()

**Location**: `qrcode_pattern.cpp:123-142`

```cpp
void QRCodePattern::UpdateColor(const Color& color, bool isFristLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = host->GetPaintProperty<QRCodePaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange() || isFristLoad) {
        paintProperty->UpdateColor(color);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateForegroundColor(color);
        renderContext->ResetForegroundColorStrategy();
        renderContext->UpdateForegroundColorFlag(true);
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}
```

**Update Flow**:
1. Check if it's system color change or first load
2. Update color in PaintProperty
3. Update foreground color in RenderContext
4. Mark node as dirty to trigger redraw

#### UpdateBackgroundColor()

**Location**: `qrcode_pattern.cpp:144-161`

```cpp
void QRCodePattern::UpdateBackgroundColor(const Color& color, bool isFristLoad)
{
    // ... similar to UpdateColor
    paintProperty->UpdateBackgroundColor(color);
    renderContext->UpdateBackgroundColor(color);
}
```

#### UpdateContentOpacity()

**Location**: `qrcode_pattern.cpp:163-177`

```cpp
void QRCodePattern::UpdateContentOpacity(double opacity, bool isFristLoad)
{
    // ... check logic
    paintProperty->UpdateOpacity(opacity);
    // ... mark dirty node
}
```

---

## 5. Model Layer

### 5.1 QRCodeModel (Abstract Interface)

**Location**: `qrcode_model.h`

Defines the standard interface for QRCode component.

### 5.2 QRCodeModelNG

**Location**: `qrcode_model_ng.h:23-39`

```cpp
class QRCodeModelNG : public OHOS::Ace::QRCodeModel
{
public:
    void Create(const std::string& value) override;
    void SetQRCodeColor(const Color& color) override;
    void SetQRBackgroundColor(const Color& color) override;
    void SetContentOpacity(const double opacity) override;
    void CreateWithResourceObj(QRCodeResourceType jsResourceType,
                               const RefPtr<ResourceObject>& resObj) override;

    // Static methods for direct FrameNode manipulation
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetQRCodeValue(FrameNode* frameNode, const std::string& value);
    static void SetQRCodeColor(FrameNode* frameNode, const Color& color);
    static void SetQRBackgroundColor(FrameNode* frameNode, const Color& color);
    static void SetContentOpacity(FrameNode* frameNode, const double opacity);
};
```

### 5.3 Create() Method

**Location**: `qrcode_model_ng.cpp:29-44`

```cpp
void QRCodeModelNG::Create(const std::string& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", QRCODE_ETS_TAG, nodeId);

    // Create or get FrameNode
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        QRCODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<QRCodePattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    // Reset user set flags
    auto pros = frameNode->GetPaintProperty<QRCodePaintProperty>();
    if (pros) {
        pros->ResetQRCodeColorSetByUser();
        pros->ResetQRBackgroundColorSetByUser();
    }
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Value, value);
}
```

**Creation Flow**:
1. Get or create nodeId from ViewStackProcessor
2. Create FrameNode and associate with QRCodePattern
3. Push FrameNode onto ViewStack
4. Reset color user-set flags
5. Update QR code content value

### 5.4 SetQRCodeColor() Method

**Location**: `qrcode_model_ng.cpp:46-53`

```cpp
void QRCodeModelNG::SetQRCodeColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Color, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, QRCodeColorSetByUser, true);
}
```

**Key Point**: Sets `QRCodeColorSetByUser` flag to `true` to prevent theme override

### 5.5 Resource Object Support

QRCodeModelNG supports dynamic property updates via resource objects:

- `CreateWithResourceObj()`: Update corresponding properties based on resource type
- `HandleCreateResource()`: Handle content resources
- `HandleColorResource()`: Handle color resources
- `HandleBackgroundColorResource()`: Handle background color resources
- `HandleContentOpacityResource()`: Handle opacity resources

**Location**: `qrcode_model_ng.cpp:100-179`

---

## 6. Property Layer

### 6.1 QRCodePaintProperty Class

**Location**: `qrcode_paint_property.h:28-80`

```cpp
class QRCodePaintProperty : public PaintProperty
{
public:
    // Property cloning
    RefPtr<PaintProperty> Clone() const override;

    // Property reset
    void Reset() override;

    // JSON serialization (for Devtools)
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    // Property definitions
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Opacity, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRCodeColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(QRBackgroundColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
};
```

### 6.2 Property Description

| Property | Type | Description |
|----------|------|-------------|
| `Value` | `std::string` | QR code content string |
| `Color` | `Color` | QR code foreground color |
| `BackgroundColor` | `Color` | QR code background color |
| `Opacity` | `double` | Content opacity (0.0-1.0) |
| `QRCodeColorSetByUser` | `bool` | Whether user explicitly set foreground color |
| `QRBackgroundColorSetByUser` | `bool` | Whether user explicitly set background color |

### 6.3 ToJsonValue() Implementation

**Location**: `qrcode_paint_property.h:55-72`

```cpp
void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
{
    PaintProperty::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrCodeTheme);

    json->PutExtAttr("value", propValue_.value_or("").c_str(), filter);
    json->PutExtAttr("color",
        propColor_.value_or(qrCodeTheme->GetQrcodeColor()).ColorToString().c_str(), filter);
    json->PutExtAttr("backgroundColor",
        propBackgroundColor_.value_or(qrCodeTheme->GetBackgroundColor()).ColorToString().c_str(), filter);
    json->PutExtAttr("opacity", propOpacity_.value_or(1.0f), filter);
}
```

---

## 7. Modifier Layer

### 7.1 QRCodeModifier Class

**Location**: `qrcode_modifier.h:33-72`

```cpp
class QRCodeModifier : public ContentModifier
{
public:
    QRCodeModifier();
    void onDraw(DrawingContext& context) override;

    // Property setter methods
    void SetQRCodeOpacity(float opacity);
    void SetQRCodeSize(float qrCodeSize);
    void SetQRCodeValue(const std::string& value);
    void SetPaintOffset(const OffsetF& paintOffset);
    void SetQRCodeColor(const Color& color);
    void SetQRCodeBackgroundColor(const Color& bgColor);

private:
    // Bitmap generation
    RSBitmap CreateBitMap(int32_t width, const qrcodegen::QrCode& qrCode,
                          const Color& color, const Color& backgroundColor) const;

    // Color conversion
    uint32_t ConvertColorFromHighToLow(const Color& color) const;

    // Property members
    RefPtr<AnimatablePropertyFloat> opacity_;           // Animation-supported opacity
    RefPtr<PropertyFloat> qrCodeSize_;
    RefPtr<PropertyString> value_;
    RefPtr<PropertyOffsetF> paintOffset_;
    RefPtr<PropertyColor> color_;
    RefPtr<PropertyColor> backgroundColor_;
};
```

### 7.2 onDraw() Method

**Location**: `qrcode_modifier.cpp:34-73`

```cpp
void QRCodeModifier::onDraw(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto opacity = opacity_->Get();
    auto qrCodeSize = qrCodeSize_->Get();
    auto value = value_->Get();
    auto paintOffset = paintOffset_->Get();
    auto color = color_->Get();
    auto backgroundColor = backgroundColor_->Get();

    // Encode QR code using qrcodegen library
    auto qrCode = qrcodegen::QrCode::encodeText(value.c_str(), qrcodegen::QrCode::Ecc::LOW);

    // Validate effectiveness
    if (!qrCode.getFlag() || qrCode.getSize() == 0 || qrCodeSize <= 0 ||
        qrCodeSize < static_cast<float>(qrCode.getSize())) {
        TAG_LOGE(AceLogTag::ACE_QRCODE, "QRCodeSize is too small. QRCodeSize: %{public}f", qrCodeSize);
        return;
    }

    // Apply opacity
    color = color.BlendOpacity(opacity);

    // Create bitmap
    auto bitMap = CreateBitMap(static_cast<int32_t>(qrCodeSize), qrCode, color, backgroundColor);

    // Build image
    RSImage image;
    image.BuildFromBitmap(bitMap);

    // Calculate scaling
    int32_t blockCounts = static_cast<int32_t>(qrCodeSize) / qrCode.getSize();
    int32_t sizeInPixel = blockCounts * qrCode.getSize();
    if (sizeInPixel == 0) {
        return;
    }

    auto scale = qrCodeSize / sizeInPixel;

    // Draw
    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.Save();
    canvas.Scale(scale, scale);
    canvas.DrawImage(image, paintOffset.GetX() / scale, paintOffset.GetY() / scale, RSSamplingOptions());
    canvas.DetachBrush();
    canvas.Restore();
}
```

**Drawing Flow**:
1. Get all property values
2. Use qrcodegen library to encode string into QrCode object
3. Validate QR code effectiveness
4. Apply opacity to color
5. Create bitmap
6. Calculate scaling ratio
7. Draw to canvas

### 7.3 CreateBitMap() Method

**Location**: `qrcode_modifier.cpp:75-110`

```cpp
RSBitmap QRCodeModifier::CreateBitMap(
    int32_t width, const qrcodegen::QrCode& qrCode, const Color& color, const Color& backgroundColor) const
{
    RSBitmap bitMap;
    RSBitmapFormat colorType = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    if (!bitMap.Build(width, width, colorType)) {
        TAG_LOGW(AceLogTag::ACE_QRCODE, "rsBitmap build fail.");
        return bitMap;
    }

    void* rawData = bitMap.GetPixels();
    auto* data = reinterpret_cast<uint32_t*>(rawData);
    int32_t blockWidth = width / qrCode.getSize();
    int32_t maxWidth = 0;
    int32_t maxHeight = 0;

    // Draw foreground color modules
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < width; j++) {
            if (qrCode.getModule(i / blockWidth, j / blockWidth)) {
                data[i * width + j] = ConvertColorFromHighToLow(color);
                maxWidth = i > maxWidth ? i : maxWidth;
                maxHeight = j > maxHeight ? j : maxHeight;
            }
        }
    }

    // Before API 12, need to fill background color
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return bitMap;
    }

    // Draw background color modules
    for (int32_t i = 0; i <= maxWidth; i++) {
        for (int32_t j = 0; j <= maxHeight; j++) {
            if (!qrCode.getModule(i / blockWidth, j / blockWidth)) {
                data[i * width + j] = ConvertColorFromHighToLow(backgroundColor);
            }
        }
    }
    return bitMap;
}
```

**Key Logic**:
1. Create RGBA_8888 format bitmap
2. Iterate pixels and set foreground color based on qrcode modules
3. Before API 12, need to manually fill background color
4. Record max width/height to limit background fill range

### 7.4 ConvertColorFromHighToLow()

**Location**: `qrcode_modifier.cpp:112-120`

```cpp
uint32_t QRCodeModifier::ConvertColorFromHighToLow(const Color& color) const
{
    BGRA convertedColor;
    convertedColor.argb.blue = color.GetBlue();
    convertedColor.argb.green = color.GetGreen();
    convertedColor.argb.red = color.GetRed();
    convertedColor.argb.alpha = color.GetAlpha();
    return convertedColor.value;
}
```

**Function**: Convert ACE Color type to BGRA format 32-bit integer value

---

## 8. Layout Algorithm

### 8.1 QRCodeLayoutAlgorithm Class

**Location**: `qrcode_layout_algorithm.h:30-51`

```cpp
class ACE_FORCE_EXPORT QRCodeLayoutAlgorithm : public BoxLayoutAlgorithm
{
public:
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Measure(LayoutWrapper* layoutWrapper) override;

    float GetQRCodeSize() const { return qrCodeSize_; }

private:
    Color color_ = Color::BLACK;
    Color backgroundColor_ = Color::WHITE;
    float qrCodeSize_ = 0.0f;
};
```

### 8.2 MeasureContent() Implementation

**Location**: `qrcode_layout_algorithm.cpp:27-102`

```cpp
std::optional<SizeF> QRCodeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // ... get theme and layout properties

    auto pipeline = PipelineContext::GetCurrentContext();
    auto qrcodeTheme = pipeline->GetTheme<QrcodeTheme>();
    Dimension defaultSize = qrcodeTheme->GetQrcodeDefaultSize();
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_11) {
        // API 11+ size calculation logic
        // 1. Get padding
        // 2. Calculate default size considering padding
        // 3. Apply layout policy (match/wrap/fix)
        // 4. Ensure square (width = height = min(width, height))

        auto qrCodeSize = std::min(width, height);
        qrCodeSize_ = qrCodeSize;
        return SizeF(qrCodeSize, qrCodeSize);
    } else {
        // Before API 11 size calculation logic
        auto idealSize = CreateIdealSize(contentConstraint, Axis::HORIZONTAL, ...);
        if (LessNotEqual(idealSize.Width(), idealSize.Height())) {
            idealSize.SetHeight(idealSize.Width());
        } else if (LessNotEqual(idealSize.Height(), idealSize.Width())) {
            idealSize.SetWidth(idealSize.Height());
        }
        qrCodeSize_ = idealSize.Width();
        return idealSize;
    }
}
```

**Layout Policies**:

| Policy | Behavior |
|--------|----------|
| `Match` | Use parent container constraint size |
| `Wrap` | Use min(default size, parent container constraint) |
| `Fix` | Use default size (theme.GetQrcodeDefaultSize()) |

**Key Points**:
1. **API >= 11**: Consider padding for more precise size calculation
2. **API < 11**: Simplified constraint calculation
3. **Always Square**: `qrCodeSize = min(width, height)`

### 8.3 Measure() Implementation

**Location**: `qrcode_layout_algorithm.cpp:104-135`

```cpp
void QRCodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    if (layoutPolicy.has_value() && layoutPolicy->IsFix()) {
        // Special handling for Fix policy
        auto contentConstraint = layoutProperty->GetLayoutConstraint();
        auto pipeline = PipelineContext::GetCurrentContext();
        auto qrcodeTheme = pipeline->GetTheme<QrcodeTheme>();
        Dimension defaultSize = qrcodeTheme->GetQrcodeDefaultSize();
        auto defaultHeight = defaultSize.ConvertToPx();
        OptionalSizeF qrcodeFrameSize = { defaultHeight, defaultHeight };

        // Apply user specified size
        if (contentConstraint->selfIdealSize.Width().has_value()) {
            qrcodeFrameSize.SetWidth(contentConstraint->selfIdealSize.Width().value());
        }
        if (contentConstraint->selfIdealSize.Height().has_value()) {
            qrcodeFrameSize.SetHeight(contentConstraint->selfIdealSize.Height().value());
        }

        // Wrap policy uses default size
        if (layoutPolicy->IsWidthWrap()) {
            qrcodeFrameSize.SetWidth(defaultHeight);
        }
        if (layoutPolicy->IsHeightWrap()) {
            qrcodeFrameSize.SetHeight(defaultHeight);
        }

        layoutWrapper->GetGeometryNode()->SetFrameSize(qrcodeFrameSize.ConvertToSizeT());
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}
```

---

## 9. Rendering Pipeline

### 9.1 QRCodePaintMethod Class

**Location**: `qrcode_paint_method.h:28-47`

```cpp
class QRCodePaintMethod : public NodePaintMethod
{
public:
    QRCodePaintMethod(const WeakPtr<Pattern>& pattern, float qrCodeSize,
                      const RefPtr<QRCodeModifier>& qrCodeModifier)
        : pattern_(pattern), qrCodeSize_(qrCodeSize), qrCodeModifier_(qrCodeModifier)
    {}

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(qrCodeModifier_, nullptr);
        return qrCodeModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    WeakPtr<Pattern> pattern_;
    float qrCodeSize_ = 0.0f;
    RefPtr<QRCodeModifier> qrCodeModifier_;
};
```

### 9.2 Rendering Call Chain

```
Pattern::CreateNodePaintMethod()
    ↓
QRCodePaintMethod construction
    ↓
PaintWrapper::GetContentModifier()
    ↓
QRCodeModifier::onDraw()
    ↓
qrcodegen::QrCode::encodeText() + CreateBitMap()
    ↓
Canvas::DrawImage()
```

---

## 10. Lifecycle

### 10.1 Complete Lifecycle

```
┌─────────────────────────────────────────────────────────┐
│ 1. Creation Phase                                       │
│    QRCodeModelNG::Create()                              │
│    → FrameNode::GetOrCreateFrameNode()                  │
│    → QRCodePattern construction                         │
│    → ViewStackProcessor::Push()                         │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 2. Attachment Phase                                     │
│    QRCodePattern::OnAttachToFrameNode()                 │
│    → SetClipToFrame(true)                               │
│    → UpdateBackgroundColor(WHITE)                       │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 3. Property Setting Phase                               │
│    SetQRCodeColor() / SetQRBackgroundColor() / ...      │
│    → ACE_UPDATE_PAINT_PROPERTY                          │
│    → MarkDirtyNode(PROPERTY_UPDATE_RENDER)              │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 4. Modify Done Phase                                    │
│    QRCodePattern::OnModifyDone()                        │
│    → UpdateAlignment(CENTER)                            │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 5. Layout Phase                                         │
│    QRCodeLayoutAlgorithm::MeasureContent()              │
│    QRCodeLayoutAlgorithm::Measure()                     │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 6. Layout Swap Phase                                    │
│    QRCodePattern::OnDirtyLayoutWrapperSwap()            │
│    → qrCodeSize_ = layoutAlgorithm->GetQRCodeSize()     │
└─────────────────────────────────────────────────────────┘
                         ↓
┌─────────────────────────────────────────────────────────┐
│ 7. Paint Phase                                          │
│    QRCodePaintMethod::UpdateContentModifier()           │
│    QRCodeModifier::onDraw()                             │
│    → qrcodegen::QrCode::encodeText()                    │
│    → CreateBitMap()                                     │
│    → Canvas::DrawImage()                                │
└─────────────────────────────────────────────────────────┘
```

### 10.2 Property Update Triggers Redraw

```
SetQRCodeColor(value)
    ↓
ACE_UPDATE_PAINT_PROPERTY
    ↓
PaintProperty::UpdateProperty
    ↓
FrameNode::MarkDirtyNode(PROPERTY_UPDATE_RENDER)
    ↓
RenderContext needs update
    ↓
QRCodeModifier::onDraw() called during next frame paint
```

---

## 11. Bridge Layer

### 11.1 Bridge Layer Structure

```
bridge/
├── arkts_native_qrcode_bridge.h/cpp      # ArkTS Native interface
├── qrcode_dynamic_module.h/cpp           # Dynamic loading module
├── qrcode_dynamic_modifier.cpp           # Dynamic Modifier
└── qrcode_static_modifier.cpp            # Static Modifier
```

### 11.2 Dynamic Loading Support

QRCode component supports dynamic module loading for on-demand loading.

**QRCodeDynamicModule** implements `DynamicModule` interface:
- Provides module initialization and cleanup
- Supports runtime dynamic component loading

### 11.3 NAPI Interface

**Location**: `qrcode_napi.h/cpp`

Provides Node.js API bindings:
- `JsCreate()`: JavaScript creation function
- `JsColor()`: JavaScript color setting function
- `JsBackgroundColor()`: JavaScript background color setting function

### 11.4 JavaScript Interface

**Location**: `arkui_qrcode.js`

```javascript
// Using QRCode component in ArkTS
QRCode.create("https://example.com")
    .color(Color.Black)
    .backgroundColor(Color.White)
    .opacity(1.0)
    .width(200)
    .height(200)
```

---

## 12. Test Coverage

### 12.1 Unit Tests

**Location**: `test/unittest/core/pattern/qrcode/qrcode_test_ng.cpp`

Test coverage includes:
- Pattern lifecycle methods
- Property update methods
- Layout algorithm calculations
- Paint method invocations

### 12.2 Key Test Scenarios

| Test Scenario | Verification Content |
|---------------|---------------------|
| Creation test | FrameNode and Pattern correctly created |
| Color update | Foreground and background colors correctly updated |
| Opacity update | Opacity property correctly applied |
| Layout test | Square layout constraints |
| Theme change | System color change response |
| Validation | QR code size too small handling |

### 12.3 Testing Notes

1. **Mock Preparation**: Need to mock `PipelineContext` and `QrcodeTheme`
2. **Boundary Conditions**: Test QR code size being 0 or negative
3. **Platform Differences**: Test different layout behaviors before and after API 11

---

## Appendix

### A. Theme Configuration

Default configuration provided by QrcodeTheme:

| Property | Default Value |
|----------|---------------|
| Default Size | Typically 300x300 |
| Foreground Color | Black |
| Background Color | White |
| FocusStyleType | INNER_BORDER |
| FocusedColor | Theme specified |

### B. Common Questions

**Q1: Why is the QR code always square?**

A: In `QRCodeLayoutAlgorithm::MeasureContent()`, the final return is `SizeF(qrCodeSize, qrCodeSize)`, where `qrCodeSize = min(width, height)`.

**Q2: How to handle very long strings?**

A: The qrcodegen library handles this automatically, but very long strings may cause the QR code to be too dense. It's recommended to limit string length or use higher error correction levels (`Ecc::MEDIUM`, `Ecc::HIGH`).

**Q3: What's the difference between before and after API 11?**

A: API 11+ handles padding's impact on size more precisely, while before API 11 uses a simplified calculation method.

### C. Related File Index

| File | Key Content |
|------|-------------|
| `qrcode_pattern.h:24-30` | OnAttachToFrameNode |
| `qrcode_pattern.cpp:45-58` | OnModifyDone |
| `qrcode_pattern.cpp:32-43` | OnDirtyLayoutWrapperSwap |
| `qrcode_pattern.cpp:179-200` | OnColorConfigurationUpdate |
| `qrcode_layout_algorithm.cpp:27-102` | MeasureContent |
| `qrcode_modifier.cpp:34-73` | onDraw |
| `qrcode_modifier.cpp:75-110` | CreateBitMap |
| `qrcode_model_ng.cpp:29-44` | Create method |
| `qrcode_model_ng.cpp:46-53` | SetQRCodeColor |

### D. Version History

| Version | Date | Changes |
|---------|------|---------|
| v1.0 | 2026-02-02 | Initial version |

---

**End of Document**

> This document is generated based on OpenHarmony ace_engine source code analysis. Please report any errors or omissions.
