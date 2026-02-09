# ImageAnimator Component - Technical Overview

**Core**: Frame-based animation player with pre-loading cache for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → ImageAnimatorModifier (bridge/)
    → ImageAnimatorPattern (pattern/) - Business logic
    → ControlledAnimator (base/image/) - Animation scheduling
    → ImagePattern (image/) - Single frame loading and rendering
```

## Core Classes

### ImageAnimatorPattern (pattern/image_animator/image_animator_pattern.h)

**Key Members**:
```cpp
RefPtr<ControlledAnimator> controlledAnimator_;  // Animation controller
std::vector<ImageProperties> images_;             // Image sequence
std::list<CacheImageStruct> cacheImages_;         // Pre-load cache
ControlStatus status_;                           // Animation state
int32_t iteration_ = 1;                          // Iteration count
int32_t durationTotal_;                          // Total duration
int32_t nowImageIndex_;                          // Current frame index
bool isReverse_;                                 // Reverse playback
bool fixedSize_;                                 // Fixed size mode
```

**Lifecycle Flow**:
```
OnModifyDone() → GenerateCachedImages()
    → CreatePictureAnimation() → AddInterpolator()
    → AddListener(frame callback)
    → RunAnimatorByStatus()
    ↓
[Animation Running] → Forward() / Backward()
    → OnFrameCallback(index)
    → SetShowingIndex(index)
    ↓
Check current src vs target src
    → [Same] → Update info only
    → [Different + No cache] → Load directly
    → [Different + Has cache] → Swap cache node
    ↓
Update cache queue → MarkDirty(PROPERTY_UPDATE_MEASURE_SELF)
```

**Critical Methods**:
- `OnModifyDone()`: Entry point - initializes animation and cache
- `SetShowingIndex()`: Switch display frame with cache optimization
- `GenerateCachedImages()`: Create pre-load cache nodes based on frame duration
- `UpdateCacheImageInfo()`: Update cache queue for next frame
- `OnVisibleAreaChange()`: Pause/resume based on visibility

### ControlledAnimator (base/image/controlled_animator.h)

**State Machine**:
```
IDLE → RUNNING → PAUSED
              ↓
           STOPPED
```

**Core Interface**:
```cpp
void SetDuration(int32_t duration);                  // Set animation duration
void SetIteration(int32_t iteration);               // Set iteration count
void Forward();                                      // Play forward
void Backward();                                     // Play backward
void Pause();                                        // Pause animation
void Finish();                                       // Finish animation
void Cancel();                                       // Cancel animation

void AddInterpolator(const std::vector<PictureInfo>&);  // Add frame interpolator
void AddListener(const OnFrameCallback&);            // Add frame callback
```

**PictureInfo Structure**:
```cpp
struct PictureInfo {
    float weight;    // Display duration ratio (duration / totalDuration)
    int32_t index;   // Image index
};
```

## Animation Pipeline (5 Stages)

### Stage 1: Property Configuration
```cpp
ImageAnimator()
  .images([{ src: 'frame1.png', duration: 100 }, ...])
  .duration(1000)
  .iterations(3)
  .reverse(false)
  .fixedSize(true)
```

### Stage 2: Initialize Animation
```cpp
ImageAnimatorPattern::OnModifyDone()
    → GenerateCachedImages()  // Create cache nodes
    → CreatePictureAnimation(size)
    → AddInterpolator(pictureAnimation)
    → AddListener([this](int32_t index) { SetShowingIndex(index); })
    → RunAnimatorByStatus(index)
```

**Picture Animation Creation**:
```cpp
std::vector<PictureInfo> CreatePictureAnimation(int32_t size) {
    auto pictureAnimation = std::vector<PictureInfo>();

    if (durationTotal_ > 0) {
        for (int32_t index = 0; index < size; ++index) {
            if (images_[index].duration) {
                float weight = images_[index].duration / static_cast<float>(durationTotal_);
                pictureAnimation.emplace_back(weight, index);
            }
        }
    } else {
        // Equal duration for all frames
        for (int32_t index = 0; index < size; ++index) {
            float weight = NORMALIZED_DURATION_MAX / static_cast<float>(size);
            pictureAnimation.emplace_back(weight, index);
        }
    }

    return pictureAnimation;
}
```

### Stage 3: Frame Switching
```cpp
ControlledAnimator triggers frame callback
    ↓
SetShowingIndex(index)
    ↓
Check current display source vs target source
    ↓
[same src] → UpdateShowingImageInfo(imageFrameNode, index)
[different + no cache] → UpdateShowingImageInfo(imageFrameNode, index)
[different + has cache + loaded] → Swap cache node
    ↓
Update cache queue:
    for (auto& cacheImage : cacheImages_) {
        nextIndex = GetNextIndex(nextIndex);
        UpdateCacheImageInfo(cacheImage, nextIndex);
    }
    ↓
host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF)
```

**Cache Node Swap**:
```cpp
if (cacheImageIter->isLoaded) {
    auto cacheImageNode = cacheImageIter->imageNode;
    host->RemoveChild(imageFrameNode);           // Remove old node
    host->AddChild(cacheImageNode, ...);         // Add cache node
    cacheImages_.erase(cacheImageIter);          // Remove from cache

    // Add old node to cache pool for reuse
    CacheImageStruct newCacheImageStruct(imageFrameNode);
    newCacheImageStruct.isLoaded = true;
    cacheImages_.emplace_back(newCacheImageStruct);
}
```

### Stage 4: Update Cache
```cpp
void ImageAnimatorPattern::UpdateCacheImageInfo(
    CacheImageStruct& cacheImage, int32_t index)
{
    auto imageLayoutProperty = cacheImage.imageNode->GetLayoutProperty<ImageLayoutProperty>();
    const auto& image = images_[index];

    // Update image source if changed
    if (image.pixelMap == nullptr) {
        auto preSrc = imageLayoutProperty->GetImageSourceInfoValue().GetSrc();
        if (preSrc != image.src) {
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(image.src));
            cacheImage.index = index;
            cacheImage.isLoaded = false;  // Will trigger load
        }
    } else {
        // PixelMap source
        if (imageLayoutProperty->GetImageSourceInfoValue().GetPixmap() != image.pixelMap) {
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(image.pixelMap));
            cacheImage.index = index;
            cacheImage.isLoaded = false;
        }
    }

    cacheImage.imageNode->MarkModifyDone();
}
```

### Stage 5: Rendering
```cpp
ImagePattern::OnModifyDone()
    → LoadImageDataIfNeed()
    → OnImageDataReady()
    → OnDirtyLayoutWrapperSwap()
    → OnImageLoadSuccess()
    → Paint()
```

## Critical Technical Points

### 1. Pre-load Cache Strategy

**Cache Count Calculation**:
```cpp
// CRITICAL_TIME = 50ms
auto averageShowTime = totalDuration / frameCount;

size_t cacheImageNum;
if (averageShowTime >= CRITICAL_TIME) {
    cacheImageNum = 1;  // Slow animation, cache 1 frame
} else {
    cacheImageNum = 2;  // Fast animation, cache 2 frames
}

cacheImageNum = std::min(frameCount - 1, cacheImageNum);
```

**Cache Node Management**:
```cpp
struct CacheImageStruct {
    RefPtr<FrameNode> imageNode;  // Cached image node
    int32_t index;                 // Current cached frame index
    bool isLoaded;                 // Load completed
};
```

### 2. Adaptive Container Size

```cpp
void ImageAnimatorPattern::AdaptSelfSize() {
    // Iterate all frames to find max size
    Dimension maxWidth;
    Dimension maxHeight;

    for (const auto& image : images_) {
        auto widthPx = image.width.ConvertToPx();
        if (widthPx > maxWidthPx) {
            maxWidthPx = widthPx;
            maxWidth = image.width;
        }

        auto heightPx = image.height.ConvertToPx();
        if (heightPx > maxHeightPx) {
            maxHeightPx = heightPx;
            maxHeight = image.height;
        }
    }

    // Set container size to max frame size
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(maxWidth), CalcLength(maxHeight))
    );
}
```

### 3. Fixed Size vs Adaptive Size

**fixedSize = true (default)**:
```cpp
// All frames fill container
imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
margin.SetEdges(CalcLength(0.0));
```

**fixedSize = false**:
```cpp
// Each frame has independent size and position
imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
margin.left = CalcLength(images_[index].left);
margin.top = CalcLength(images_[index].top);
CalcSize realSize = {
    CalcLength(images_[index].width),
    CalcLength(images_[index].height)
};
imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
```

### 4. Reverse Playback

```cpp
int32_t ImageAnimatorPattern::GetNextIndex(int32_t preIndex) {
    if (isReverse_) {
        // Reverse: previous frame (wrap to end)
        return preIndex == 0 ? (static_cast<int32_t>(images_.size()) - 1)
                             : (preIndex - 1);
    }
    // Forward: next frame (wrap to start)
    return (preIndex + 1) % static_cast<int32_t>(images_.size());
}
```

### 5. Visibility Optimization

```cpp
void ImageAnimatorPattern::OnVisibleAreaChange(bool visible, double ratio) {
    if (!visible) {
        OnInActiveImageAnimator();  // → controlledAnimator_->Pause()
    } else {
        OnActiveImageAnimator();    // → Forward() / Backward()
    }
}
```

## Property System

### ImageAnimatorLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **images** | vector\<ImageProperties\> | - | Image sequence (src, duration, width, height) |
| **duration** | int32_t | 1000 | Total animation duration (ms) |
| **iterations** | int32_t | 1 | Iteration count (-1 = infinite loop) |
| **reverse** | bool | false | Reverse playback |
| **fixedSize** | bool | true | Fixed size mode |

### ImageProperties Structure

```cpp
struct ImageProperties {
    std::string src;              // Image source (network/local/resource)
    RefPtr<PixelMap> pixelMap;    // Pixel map
    int32_t duration = 0;         // Display duration (ms)
    Dimension left = 0.0_vp;      // Left margin (fixedSize=false)
    Dimension top = 0.0_vp;       // Top margin (fixedSize=false)
    Dimension width = 0.0_vp;     // Width (fixedSize=false)
    Dimension height = 0.0_vp;    // Height (fixedSize=false)
    std::string bundleName;       // Bundle name
    std::string moduleName;       // Module name
};
```

### FillMode

| Mode | Description |
|------|-------------|
| **None** | Return to initial state after animation ends |
| **Forwards** (default) | Keep last frame state after animation ends |
| **Backwards** | Apply first frame state before animation starts |
| **Both** | Combine Forwards and Backwards |

## Event System

### Event Types

**onStart** - Animation start:
```cpp
controlledAnimator_->AddStartListener([startEvent] {
    startEvent();
});
```

**onStop** - Animation stop:
```cpp
controlledAnimator_->AddStopListener([stopEvent] {
    stopEvent();
});
```

**onPause** - Animation pause:
```cpp
controlledAnimator_->AddPauseListener([pauseEvent] {
    pauseEvent();
});
```

**onRepeat** - Animation repeat:
```cpp
controlledAnimator_->AddRepeatListener([repeatEvent] {
    repeatEvent();
});
```

**onCancel** - Animation cancel:
```cpp
controlledAnimator_->AddCancelListener([cancelEvent] {
    cancelEvent();
});
```

## Performance Optimization

### 1. Cache Optimization

**Strategy**: Pre-load next frame (or two frames)

**Benefits**:
- Reduce frame switch latency
- Avoid playback stuttering
- Improve smoothness

**Memory Trade-off**:
- Slow animation (>= 50ms/frame): Cache 1 frame
- Fast animation (< 50ms/frame): Cache 2 frames

### 2. Node Reuse

```cpp
// Reuse cache nodes instead of destroy/recreate
if (cacheImageIter->isLoaded) {
    auto cacheImageNode = cacheImageIter->imageNode;
    host->RemoveChild(imageFrameNode);
    host->AddChild(cacheImageNode, ...);
    cacheImages_.erase(cacheImageIter);

    // Add old node to cache pool for reuse
    CacheImageStruct newCacheImageStruct(imageFrameNode);
    newCacheImageStruct.isLoaded = true;
    cacheImages_.emplace_back(newCacheImageStruct);
}
```

### 3. Visibility Pause

```cpp
// Automatically pause when invisible to save CPU/GPU
void ImageAnimatorPattern::OnVisibleAreaChange(bool visible, double ratio) {
    if (!visible) {
        OnInActiveImageAnimator();  // Pause
    } else {
        OnActiveImageAnimator();    // Resume
    }
}
```

## Error Handling

### Image Load Failure

```cpp
void ImageAnimatorPattern::AddImageLoadSuccessEvent(...) {
    auto eventHub = imageFrameNode->GetEventHub<ImageEventHub>();
    eventHub->SetOnComplete([](const LoadImageSuccessEvent& info) {
        if (info.GetLoadingStatus() != 1) {  // Non 1 = failed
            LOGE("Image load failed");
            return;
        }

        // Mark cache as loaded
        iter->isLoaded = true;
    });
}
```

### Index Out of Bounds Protection

```cpp
void ImageAnimatorPattern::SetShowingIndex(int32_t index) {
    if (index >= static_cast<int32_t>(images_.size()) || index < 0) {
        LOGW("ImageAnimator update index error, index: %{public}d, size: %{public}zu",
             index, images_.size());
        return;
    }
    // ...
}
```

## Advanced Features

### 1. Card Render Optimization

```cpp
void ImageAnimatorPattern::UpdateFormDurationByRemainder() {
    if (IsFormRender()) {
        // Calculate remaining display time
        formAnimationRemainder_ = DEFAULT_DURATION -
            (GetMicroTickCount() - formAnimationStartTime_) / MICROSEC_TO_MILLISEC;

        // Use remaining time as animation duration
        if ((formAnimationRemainder_ > 0) &&
            (controlledAnimator_->GetDuration() > formAnimationRemainder_)) {
            controlledAnimator_->SetDuration(formAnimationRemainder_);
        }

        // Time exhausted, end animation
        if (formAnimationRemainder_ <= 0) {
            isFormAnimationEnd_ = true;
        }
    }
}
```

### 2. Animated Image Control

```cpp
void ImageAnimatorPattern::ControlAnimatedImageAnimation(
    const RefPtr<FrameNode>& imageFrameNode, bool play)
{
    auto imagePattern = DynamicCast<ImagePattern>(imageFrameNode->GetPattern());
    auto image = imagePattern->GetCanvasImage();

    if (!image->IsStatic()) {  // GIF/WebP
        image->ControlAnimation(play);  // Control internal animation
    }
}
```

## Related Directories

```
frameworks/core/components_ng/pattern/image_animator/
├── image_animator_pattern.h/cpp           # Main logic
├── image_animator_event_hub.h             # Event handling
└── image_animator_model.h                 # Data model

base/image/
└── controlled_animator.h/cpp              # Animation controller
```

## Key Takeaways

1. **Pre-load Cache**: Dynamically adjust cache count based on frame duration
2. **Adaptive Size**: Automatically calculate max frame size as container size
3. **State Driven**: Clear state machine for animation lifecycle management
4. **Node Reuse**: Cache node pool reuse reduces create/destroy overhead
5. **Visibility Optimization**: Automatically pause when invisible
6. **Reverse Support**: Support forward/backward playback with cache update order adjustment
7. **Card Optimization**: Special handling for animation duration in card scenarios
8. **Animated Images**: Support GIF/WebP internal animation control
