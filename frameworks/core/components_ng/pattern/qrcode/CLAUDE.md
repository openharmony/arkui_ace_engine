# QRCode Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the QRCode component.

---

## Overview

**QRCode** is a component that generates and displays QR codes from string content.

**Architecture**: NG Pattern → QRCodePattern → QRCodeLayoutAlgorithm → QRCodeModifier

**Key Features**:
- String to QR code encoding (using qrcodegen library)
- Custom foreground/background colors
- Content opacity support
- Theme configuration and system color change response
- Always square layout (width = height)
- Clip to frame boundary

**Technical Dependencies**:
- **qrcodegen**: QR code encoding library
- **RSBitmap/RSImage**: Rendering subsystem
- **QrcodeTheme**: Theme defaults

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `qrcode_pattern.h/cpp` | ~200 | Pattern layer - OnModifyDone, color updates, qrCodeSize_ tracking |
| `qrcode_layout_algorithm.h/cpp` | ~135 | Square layout measurement, API 11+ padding support |
| `qrcode_modifier.h/cpp` | ~120 | QR code bitmap generation and drawing (qrcodegen integration) |
| `qrcode_paint_property.h` | ~80 | Paint properties (Value, Color, BackgroundColor, Opacity) |
| `qrcode_model_ng.h/cpp` | ~180 | Frontend bridge - Create(), SetQRCodeColor(), static FrameNode methods |
| `qrcode_paint_method.h/cpp` | ~50 | Paint method wrapper for QRCodeModifier |
| `qrcode_napi.h/cpp` | ~100 | NAPI/JS bindings |

**Path**: `frameworks/core/components_ng/pattern/qrcode/`

---

## Core Class Hierarchy

```
                    Pattern
                       ↑
                QRCodePattern
                (qrcode_pattern.h)
                       |
        +--------------+--------------+
        |              |              |
  PaintProperty  LayoutAlgorithm  NodePaintMethod
        ↑              ↑              ↑
QRCodePaintProperty  QRCodeLayoutAlgorithm  QRCodePaintMethod
                                              |
                                        QRCodeModifier
```

---

## Key Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `Value` | string | "" | QR code content string |
| `Color` | Color | Black (theme) | Foreground color (QR modules) |
| `BackgroundColor` | Color | White (theme) | Background color |
| `Opacity` | double | 1.0 | Content opacity (0.0-1.0) |
| `QRCodeColorSetByUser` | bool | false | User explicitly set foreground color |
| `QRBackgroundColorSetByUser` | bool | false | User explicitly set background color |

**User Set Flags**: Prevent theme updates from overriding user values

---

## Common Operations

### Creating QRCode

```cpp
// In Model layer
auto frameNode = FrameNode::GetOrCreateFrameNode(
    V2::QRCODE_ETS_TAG, nodeId,
    []() { return AceType::MakeRefPtr<QRCodePattern>(); });

auto paintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
paintProperty->UpdateValue("https://example.com");
```

### Setting Colors

```cpp
// Foreground color
paintProperty->UpdateColor(Color::BLACK);
auto renderContext = frameNode->GetRenderContext();
renderContext->UpdateForegroundColor(Color::BLACK);
renderContext->UpdateForegroundColorFlag(true);

// Background color
paintProperty->UpdateBackgroundColor(Color::WHITE);
renderContext->UpdateBackgroundColor(Color::WHITE);
```

### Setting Opacity

```cpp
paintProperty->UpdateOpacity(0.8f);
```

### Creating with Static Methods

```cpp
// Direct FrameNode manipulation
auto frameNode = QRCodeModelNG::CreateFrameNode(nodeId);
QRCodeModelNG::SetQRCodeValue(frameNode, "content");
QRCodeModelNG::SetQRCodeColor(frameNode, Color::BLACK);
QRCodeModelNG::SetQRBackgroundColor(frameNode, Color::WHITE);
QRCodeModelNG::SetContentOpacity(frameNode, 1.0);
```

---

## Important Implementation Details

### 1. QR Code Uses qrcodegen Library

**Source**: `qrcode_modifier.cpp:47`

```cpp
auto qrCode = qrcodegen::QrCode::encodeText(value.c_str(), qrcodegen::QrCode::Ecc::LOW);
```

**Validation**: Size must be >= qrCode.getSize() to render:

```cpp
if (qrCodeSize <= 0 || qrCodeSize < static_cast<float>(qrCode.getSize())) {
    TAG_LOGE(AceLogTag::ACE_QRCODE, "QRCodeSize is too small. QRCodeSize: %{public}f", qrCodeSize);
    return;
}
```

### 2. Always Square Layout

**Source**: `qrcode_layout_algorithm.cpp:98-99`

```cpp
auto qrCodeSize = std::min(width, height);
qrCodeSize_ = qrCodeSize;
return SizeF(qrCodeSize, qrCodeSize);
```

### 3. Size Tracked in Pattern

**Source**: `qrcode_pattern.cpp:38-42`

```cpp
bool QRCodePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                                              bool skipMeasure, bool skipLayout)
{
    // ...
    qrCodeSize_ = layoutAlgorithm->GetQRCodeSize();  // Capture for modifier
    return true;
}
```

### 4. Default Alignment to CENTER

**Source**: `qrcode_pattern.cpp:51-56`

```cpp
void QRCodePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto layoutProperty = host->GetLayoutProperty();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
}
```

### 5. Clip to Frame Enabled

**Source**: `qrcode_pattern.cpp:27`

```cpp
host->GetRenderContext()->SetClipToFrame(true);
```

Ensures QR code does not overflow container boundary.

### 6. API 11+ Handles Padding

**Source**: `qrcode_layout_algorithm.cpp:51-63`

API 11+ considers padding when calculating content size, while older versions use simplified calculation.

### 7. Background Fill Before API 12

**Source**: `qrcode_modifier.cpp:95-98`

```cpp
// Before API 12, need to manually fill background color
if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
    return bitMap;  // Skip background fill
}
// ... manual background fill loop
```

### 8. Color Format Conversion

**Source**: `qrcode_modifier.cpp:112-120`

Converts ACE Color to BGRA format for RSBitmap:

```cpp
uint32_t ConvertColorFromHighToLow(const Color& color) const
{
    BGRA convertedColor;
    convertedColor.argb.blue = color.GetBlue();
    convertedColor.argb.green = color.GetGreen();
    convertedColor.argb.red = color.GetRed();
    convertedColor.argb.alpha = color.GetAlpha();
    return convertedColor.value;
}
```

---

## Layout Policies

| Policy | Behavior |
|--------|----------|
| `Match` | Use parent container constraint size |
| `Wrap` | Use min(default size, parent constraint) |
| `Fix` | Use default size from theme |

**Default Size**: From `QrcodeTheme::GetQrcodeDefaultSize()` (typically 300x300)

---

## ArkTS API Reference

```typescript
// Constructor
QRCode(value: string)

// Property methods
.qrCodeColor(value: ResourceColor)
.qrBackgroundColor(value: ResourceColor)
.opacity(value: number | Resource)

// Example
QRCode('https://example.com')
    .width(200)
    .height(200)
    .qrCodeColor(Color.Black)
    .qrBackgroundColor(Color.White)
    .opacity(1.0)
```

---

## Debugging

### Log Tag

```cpp
TAG_LOGE(AceLogTag::ACE_QRCODE, "QRCodeSize is too small. QRCodeSize: %{public}f", qrCodeSize);
```

### Common Issues

| Issue | Check |
|-------|-------|
| QR code not displaying | `value` non-empty, `qrCodeSize >= qrCode.getSize()` |
| Wrong size | Square constraint: `size = min(width, height)` |
| Colors not applied | Check `*SetByUser` flags - user values override theme |
| Background not filled | API version < 12 requires manual fill |

---

## Execution Flow

```
Frontend: QRCode('content')
    ↓
QRCodeModelNG::Create()
    ├── FrameNode::GetOrCreateFrameNode(QRCODE_ETS_TAG)
    ├── Create QRCodePattern
    ├── Reset color user-set flags
    └── Update Value property
    ↓
QRCodePattern::OnAttachToFrameNode()
    ├── SetClipToFrame(true)
    └── UpdateBackgroundColor(WHITE)
    ↓
QRCodePattern::OnModifyDone()
    └── UpdateAlignment(CENTER)
    ↓
QRCodeLayoutAlgorithm::MeasureContent()
    ├── Get theme defaults
    ├── Apply layout policy (Match/Wrap/Fix)
    └── Return square SizeF(qrCodeSize, qrCodeSize)
    ↓
QRCodePattern::OnDirtyLayoutWrapperSwap()
    └── qrCodeSize_ = layoutAlgorithm->GetQRCodeSize()
    ↓
QRCodePaintMethod::UpdateContentModifier()
    └── Set properties on QRCodeModifier
    ↓
QRCodeModifier::onDraw()
    ├── qrcodegen::QrCode::encodeText()
    ├── Validate size
    ├── CreateBitMap() (pixel-by-pixel rendering)
    ├── Build RSImage
    └── Canvas::DrawImage()
```

---

## References

- **qrcodegen library**: External QR code encoding library
- **Theme**: `frameworks/core/components/qrcode/theme/qrcode_theme.h`
