# Image Component - Technical Overview

**Core**: Image loading, decoding, and rendering pipeline for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → ImageModifier (bridge/)
    → ImageLayoutProperty + ImageRenderProperty (properties)
    → ImagePattern (pattern/) - Business logic
    → ImageProvider + ImageLoadingContext (image_provider/) - Load coordination
    → ImageLoader + ImageObject + ImageDecoder (core/image/) - Data processing
    → CanvasImage (render/) - GPU rendering
```

## Core Classes

### ImagePattern (pattern/image_pattern.h)

**Key Members**:
```cpp
RefPtr<ImageLoadingContext> loadingCtx_;    // Main image loading state
RefPtr<ImageLoadingContext> altLoadingCtx_; // Fallback image
RefPtr<CanvasImage> image_;                 // Final rendered image
RectF dstRect_, srcRect_;                  // Rendering rectangles
```

**Lifecycle Flow**:
```
OnModifyDone() → LoadImageDataIfNeed() → Create ImageLoadingContext
    ↓
OnImageDataReady() [async callback] → UpdateOrientation + CheckIfNeedLayout
    ↓
OnDirtyLayoutWrapperSwap() → StartDecoding(finalDstSize)
    ↓
OnImageLoadSuccess() → SetImagePaintConfig() + PrepareAnimation()
    ↓
Paint() → ImageContentModifier::Draw()
```

**Critical Methods**:
- `OnModifyDone()`: Entry point - triggers image loading
- `OnImageDataReady()`: Image size known, determines if layout needed
- `OnDirtyLayoutWrapperSwap()`: Layout complete, final size known, start decoding
- `OnVisibleChange()`: Pause/resume animation, recycle memory

### ImageLoadingContext (image_provider/image_loading_context.h)

**State Machine**:
```
UNLOADED → DATA_LOADING → DATA_READY → MAKE_CANVAS_IMAGE → SUCCESS
                                      ↓
                                   LOAD_FAIL
```

**Core Interface**:
```cpp
void LoadImageData();                                    // Stage 1: Load
void MakeCanvasImage(const SizeF& dstSize, ...);         // Stage 2: Decode
bool MakeCanvasImageIfNeed(...);                         // Optimization check

// Callbacks registered from ImagePattern
void DataReadyCallback(const RefPtr<ImageObject>&);     // Data loaded
void SuccessCallback(const RefPtr<CanvasImage>&);       // Decoding complete
void FailCallback(const std::string&);                 // Error
```

**Key Responsibilities**:
- Manages loading state transitions via ImageStateManager
- Coordinates between main thread (UI) and background thread (loading/decoding)
- Provides dstSize calculation for auto-resize optimization

### ImageProvider (image_provider/image_provider.h)

**Static Factory Methods**:
```cpp
static void CreateImageObject(src, ctx, sync, isSceneBoardWindow);
    ↓
// Selects loader by srcType: Network/File/Asset/Base64/PixelMap
// Returns ImageObject via DataReadyCallback

static void MakeCanvasImage(imageObj, ctx, targetSize, options);
    ↓
// Background: ImageObject::MakeCanvasImage() → Decode → Upload GPU
// Main thread: SuccessCallback(CanvasImage)
```

**Cache Strategy** (3 levels):
1. **ImageObject Cache**: `ImageCache::GetImageObject(key)` - decoded objects
2. **PixelMap Cache**: `weakPixelMapCache_` - size-specific, weak refs
3. **CanvasImage Cache**: `CanvasImage::GetCache(key)` - GPU texture

## Image Loading Pipeline (7 Stages)

### Stage 1: Property Configuration
```cpp
Image(src).width(100).fit(ImageFit.Cover)
    → ImageModifier::ApplySrc()
    → ImageLayoutProperty::UpdateImageSourceInfo()
```

### Stage 2: Trigger Loading
```cpp
ImagePattern::OnModifyDone()
    → LoadImageDataIfNeed()
    → ImageLoadingContext(src, callbacks={DataReady, Success, Fail})
    → loadingCtx_->LoadImageData()
```

### Stage 3: Data Loading (Background Thread)
```
ImageProvider::CreateImageObject()
    → [srcType]Loader::Load()  // Network/File/Asset/Base64
    → ImageObject::Create()    // Static/Animated/Svg/PixelMap
    → Post to main: DataReadyCallback(imageObj)
```

### Stage 4: Data Ready (Main Thread)
```cpp
ImagePattern::OnImageDataReady(imageObj)
    → UpdateOrientation()        // EXIF rotation
    → PreprocessYUVDecodeFormat() // Performance optimization
    → if (sizeChanged) MarkDirty(PROPERTY_UPDATE_LAYOUT) // Need re-layout
    → else StartDecoding(dstSize) // Size already known
```

**Critical Decision Point**: Size determination
- If image size unknown → Trigger layout → Wait for `OnDirtyLayoutWrapperSwap()`
- If size known → Skip layout → Direct decode

### Stage 5: Decoding (Background Thread)
```cpp
ImageLoadingContext::MakeCanvasImage(dstSize, autoResize, imageFit)
    → ImageProvider::MakeCanvasImage()
    → imageObj->MakeCanvasImage()
        → ImageDecoder::Decode(options) → PixelMap
        → CanvasImage::Build() → GPU texture upload
    → Post to main: SuccessCallback(canvasImage)
```

**Decoding Options**:
```cpp
ImageDecoderOptions {
    preMultiply: true,              // Alpha pre-multiplication
    desiredPixelFormat: RGBA_8888,  // Target format
    desiredSize: dstSize,           // Auto-resize target
    editable: false
};
```

### Stage 6: Success (Main Thread)
```cpp
ImagePattern::OnImageLoadSuccess(canvasImage)
    → image_ = loadingCtx_->MoveCanvasImage()
    → srcRect_ = loadingCtx_->GetSrcRect()  // Source crop
    → dstRect_ = loadingCtx_->GetDstRect()  // Target position
    → SetImagePaintConfig(srcRect, dstRect, ...)
        → Apply: quality, interpolation, HDR, colorFilter, antiAlias
    → PrepareAnimation() if animated
    → MarkDirty(PROPERTY_UPDATE_RENDER)
```

### Stage 7: Rendering
```cpp
Paint()
    → ImageContentModifier::Draw(image_, srcRect_, dstRect_)
    → canvasImage_->DrawToRSCanvas()
    → GPU rendering
```

## Critical Technical Points

### 1. Auto-Resize Optimization

**Purpose**: Decode at display size, not full resolution

**Implementation**:
```cpp
// Round up to nearest power of 2
int32_t sizeLevel = std::ceil(std::log2(dstSize.Width()));
float targetWidth = std::pow(2, sizeLevel);

ImageDecoderOptions.desiredSize = SizeF(targetWidth, dstSize.Height());
```

**Benefit**: 4x memory reduction for 2x downscale

### 2. Layout Synchronization

**Problem**: Image size unknown until loaded

**Solution**:
```
Initial Layout (use placeholder size)
    ↓
[Data Ready] - size now known
    ↓
MarkDirty(PROPERTY_UPDATE_LAYOUT)
    ↓
Re-layout with actual image size
    ↓
OnDirtyLayoutWrapperSwap() - final dstSize confirmed
    ↓
StartDecoding(finalDstSize) - decode once at correct size
```

**Key**: Decoding deferred until layout complete to avoid re-decoding

### 3. ImageFit Calculation

**Core Algorithm**:
```cpp
SizeF CalculateCoverSize(imageSize, containerSize) {
    float ratio = max(containerW/imageW, containerH/imageH);
    return SizeF(imageW * ratio, imageH * ratio); // May crop
}

SizeF CalculateContainSize(imageSize, containerSize) {
    float ratio = min(containerW/imageW, containerH/imageH);
    return SizeF(imageW * ratio, imageH * ratio); // Complete display
}

// Rect calculation for Cover (center crop)
srcRect.x = (imageW - fittedW) / 2 * scaleX;
srcRect.y = (imageH - fittedH) / 2 * scaleY;
dstRect = containerSize; // Fill entire container
```

### 4. Three-Level Fallback Strategy

```cpp
Try: Main Image
    ↓ Fail
Try: Alt Image (alt property)
    ↓ Fail
Try: AltError Image (altError property)
    ↓ Fail
Show: AltPlaceholder (altPlaceholder property) or blank
```

**Member Variables**:
```cpp
RefPtr<ImageLoadingContext> altLoadingCtx_;    // Alt loading
RefPtr<ImageLoadingContext> altErrorCtx_;     // Error loading
RefPtr<CanvasImage> altImage_;
RefPtr<CanvasImage> altErrorImage_;
```

### 5. Animation Management

**Supported**: GIF, WebP, animated SVG

**Lifecycle**:
```cpp
PrepareAnimation(canvasImage)
    → SetRedrawCallback([this]() { MarkDirty(PROPERTY_UPDATE_RENDER); })
    → SetOnFinishCallback([this]() { FireFinishEvent(); })
    → RegisterVisibleAreaChange()
    → canvasImage->StartAnimation()

OnVisibleChange(visible)
    → visible ? canvasImage->ResumeAnimation() : PauseAnimation()

OnDetachFromMainTree()
    → canvasImage->StopAnimation()
```

**Optimization**: Pause when invisible, reduce frame rate for battery

### 6. Memory Management

**Callbacks**:
```cpp
OnNotifyMemoryLevel(level)
    → level >= CRITICAL ? RecycleAllImageData() : RecycleAltData()

OnVisibleChange(visible)
    → !visible && ShouldRecycle() ? RecycleImageData()

OnWindowHide()
    → RecycleImageData()
```

**Recycle Strategy**:
- Clear `image_` (CanvasImage)
- Cancel `loadingCtx_` callbacks
- Keep `ImageObject` in cache for potential reload

## Property System

### Layout Properties (image_layout_property.h)

```cpp
ImageSourceInfo src;           // URI + type (network/file/asset/base64/pixelmap)
ImageFit fit;                  // Cover/Contain/Fill/None/ScaleDown
bool autoResize;               // Decode at display size
SizeF sourceSize;              // Explicit source size
ImageSourceInfo alt;           // Fallback
ImageSourceInfo altError;      // Error fallback
ImageSourceInfo altPlaceholder; // Loading placeholder
bool isYUVDecode;              // YUV format optimization
```

### Render Properties (image_render_property.h)

```cpp
RefPtr<PixelMap> colorFilter;  // Color transformation
ImageRepeat repeat;            // NoRepeat/X/Y/XY
Color fillColor;               // SVG fill
DynamicRangeMode dynamicRange; // Standard/HDR/SDR
bool matchTextDirection;       // RTL/LTR mirroring
ImageInterpolation interpolation; // High/Low/Medium/None
float hdrBrightness;           // HDR boost
bool antiAlias;                // Edge smoothing
```

## Event System

### Callback Registration

```cpp
// From ArkTS
Image(src)
    .onComplete((info: LoadImageSuccessInfo) => {...})
    .onError((info: LoadImageFailInfo) => {...})
    .onFinish(() => {...})  // SVG animation complete
    ↓
// Internally
eventHub->onLoadSuccess_ = callback;
eventHub->onLoadFail_ = callback;
eventHub->onFinish_ = callback;
```

### Progress Callback (Network Only)

```cpp
loadingCtx_->SetOnProgressCallback([](uint32_t dlNow, uint32_t dlTotal) {
    double progress = dlNow / dlTotal;
    UpdateProgressBar(progress);
});
// Triggered during DownloadManager::Download()
```

## Error Handling

### Error Codes

```cpp
enum ImageErrorCode {
    LOAD_FAIL,                      // Generic failure
    DATA_SIZE_INVALID,              // Corrupted data
    CREATE_IMAGE_UNKNOWN_SOURCE_TYPE,  // Unsupported URI scheme
    BUILD_IMAGE_DATA_SIZE_INVALID,  // Parse error
    NETWORK_ERROR,                  // Download failed
    DECODE_ERROR,                   // Format not supported
    OUT_OF_MEMORY                   // Allocation failed
};
```

### Error Propagation

```
Loader::Load() FAIL
    ↓ ImageLoadingContext::FailCallback(errorMsg, errorInfo)
    ↓ ImagePattern::OnImageLoadFail()
    ↓ Try alt image OR
    ↓ FireErrorEvent(info)
    ↓ eventHub->onLoadFail_(info)
    ↓ ArkTS onError callback
```

## Performance Optimization

### 1. Caching Strategy

```
Level 1: DownloadManager (network cache)
    Key: URL
    Value: Downloaded file
    Auto-cleanup: LRU

Level 2: ImageCache (object cache)
    Key: ImageSourceInfo.GetKey()
    Value: ImageObject (pre-decode)
    Capacity: 2000 objects
    Hit benefit: Skip loading, go directly to decode

Level 3: weakPixelMapCache_ (decode cache)
    Key: ImageObject + Size
    Value: PixelMap (decoded)
    Weak refs: Allow GC under memory pressure
    Hit benefit: Skip decoding, direct GPU upload

Level 4: CanvasImage::Cache() (GPU cache)
    Key: ImageObject + Size + Options
    Value: CanvasImage (GPU texture)
    Hit benefit: Zero CPU/GPU work
```

### 2. Thread Model

```
Main Thread:
    - UI operations
    - Layout calculation
    - CanvasImage drawing
    - Callback execution

Background Thread (TaskExecutor):
    - Network download (DownloadManager)
    - File I/O (FileLoader)
    - Decoding (ImageDecoder)
    - GPU texture upload (if supported)

Thread Switching:
    Main → Background: ImageUtils::PostToBg(task, "taskName", containerId)
    Background → Main: ImageUtils::PostToUI(callback, "taskName", containerId)
```

**Key**: `containerId` ensures thread affinity - callbacks execute on original thread

### 3. DFX (Debugging/Performance)

```cpp
struct ImageDfxConfig {
    int64_t loadStartTimestamp;     // Entry point
    int64_t dataReadyTimestamp;     // Data loaded
    int64_t loadSuccessTimestamp;   // Decoding complete
    int64_t imageWidth, imageHeight;
    std::string srcType;            // network/file/asset/base64
};

// Automatic reporting at state transitions
ReportPerfData(host, STATE_DATA_READY);
ReportPerfData(host, STATE_SUCCESS);
```

## Debugging

### Dump Interfaces

```cpp
DumpInfo()         → Source URL, loading state, image size
DumpLayoutInfo()   → DstRect, srcRect, imageFit, autoResize
DumpRenderInfo()   → CanvasImage exists, isAnimated, frameCount
DumpAdvanceInfo()  → ImageQuality, copyOption, orientation
DumpSvgInfo()      → IsSvg, supportSvg2, svgDom exists
```

### Common Issues

**Symptom**: Image loads slowly
**Cause**: No caching, full-resolution decode
**Fix**:
```cpp
layoutProp->autoResize = true;
src.SetNeedCache(true);
```

**Symptom**: High memory usage
**Cause**: Too many cached images, no auto-resize
**Fix**:
```cpp
OnNotifyMemoryLevel(level) {
    if (level >= CRITICAL) RecycleImageData();
}
```

**Symptom**: Blurry image
**Cause**: Low interpolation setting
**Fix**:
```cpp
renderProp->interpolation = ImageInterpolation::HIGH;
```

**Symptom**: Wrong aspect ratio
**Cause**: Incorrect ImageFit
**Fix**:
```cpp
layoutProp->imageFit = ImageFit::CONTAIN; // or COVER
```

## Related Directories

```
frameworks/core/
├── components_ng/pattern/image/
│   ├── image_pattern.h/cpp           # Main logic
│   ├── image_layout_property.h       # Layout props
│   └── image_render_property.h       # Render props
├── components_ng/image_provider/
│   ├── image_provider.h/cpp          # Load coordination
│   ├── image_loading_context.h/cpp   # State management
│   └── image_state_manager.h/cpp     # State machine
├── image/
│   ├── image_loader.h/cpp            # Loader base
│   ├── network_image_loader.h/cpp    # HTTP/HTTPS
│   ├── file_image_loader.h/cpp       // file://
│   └── image_decoder.h/cpp           # Decoding interface
└── components_ng/render/
    └── canvas_image.h/cpp            # GPU rendering
```

## Key Takeaways

1. **Async Pipeline**: Load/decode on background, callbacks on main thread
2. **Layout-Aware**: Defer decoding until final size known
3. **Auto-Resize**: Decode at display size for memory efficiency
4. **3-Level Fallback**: Main → Alt → AltError → Placeholder
5. **Cache Strategy**: Download → Object → PixelMap → GPU (4 levels)
6. **State Machine**: ImageLoadingContext + ImageStateManager
7. **Animation Support**: GIF/WebP/SVG with frame callbacks
8. **Memory Management**: Visibility-based + memory level callbacks
