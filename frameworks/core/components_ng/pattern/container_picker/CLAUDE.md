# ContainerPicker Component - Technical Overview

**Core**: Scrollable picker container with physics-based inertia for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → ContainerModifier (bridge/)
    → ContainerPickerPattern (pattern/) - Business logic and state
    → NestableScrollContainer (scrollable/) - Nested scroll support
    → AxisAnimator (scrollable/axis/) - Scroll animation and inertia
```

## Core Classes

### ContainerPickerPattern (pattern/container_picker/container_picker_pattern.h)

**Key Members**:
```cpp
// Scroll parameters
double yLast_;                    // Last Y position
double yOffset_;                  // Y offset
double dragStartTime_;            // Drag start time
double dragEndTime_;              // Drag end time
double dragVelocity_;             // Drag velocity
double currentPos_;               // Current position

float currentOffset_;             // Current scroll offset
float height_;                    // Container height
float contentMainSize_;           // Content main axis size
float pickerItemHeight_;          // Single item height

// Animation
RefPtr<AxisAnimator> axisAnimator_;
RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
std::shared_ptr<AnimationUtils::Animation> scrollAnimation_;

// State
bool isDragging_;                 // Whether dragging
bool isAnimationRunning_;         // Animation running
int32_t selectedIndex_;           // Selected index
int32_t totalItemCount_;          // Total item count
int32_t displayCount_;            // Display count (default 7)

// Haptic feedback
std::shared_ptr<IPickerAudioHaptic> hapticController_;
bool isEnableHaptic_;             // Whether haptic enabled
```

**Lifecycle Flow**:
```
OnModifyDone() → InitDefaultParams()
    → InitAxisAnimator()
    → InitMouseAndPressEvent()
    → UpdatePanEvent()
    → InitOrRefreshHapticController()
```

**Critical Methods**:
- `OnModifyDone()`: Initialize component and events
- `HandleDragStart()`: Drag start - record position and stop animation
- `HandleDragUpdate()`: Drag update - calculate offset and update position
- `HandleDragEnd()`: Drag end - calculate velocity and trigger animation
- `PlayInertialAnimation()`: Inertia scroll animation
- `SnapToNearestItem()`: Snap to nearest item
- `CalcCurrentMiddleItem()`: Calculate current middle item

### AxisAnimator

**Core Interface**:
```cpp
class AxisAnimator {
public:
    void MoveTo(float position, float duration);  // Move to position
    void Stop();                                  // Stop animation
    bool IsRunning() const;                       // Whether running
};
```

## Complete Scroll Flow

### Drag Scroll

```
User presses and drags
    ↓
HandleDragStart()
    - Record start position
    - Stop current animation
    ↓
User dragging
    ↓
HandleDragUpdate()
    - Calculate offset
    - UpdateCurrentOffset(deltaY)
    - Update child positions
    ↓
User releases
    ↓
HandleDragEnd(dragVelocity)
    - Calculate drag velocity
    - Check if out of boundary
    ↓
[Out of boundary] → PlaySpringAnimation() → Rebound
[In boundary] → PlayInertialAnimation() → Inertia scroll
    ↓
Snap to nearest item
    ↓
FireChangeEvent() → Trigger onChange event
```

### Item Click

```
User clicks an item
    ↓
ItemClickEventListener
    ↓
Calculate clicked item index
    ↓
SwipeTo(index)
    - Calculate target offset
    - PlayTargetAnimation()
    ↓
Animation complete
    ↓
HandleTargetIndex()
    - Update selectedIndex_
    - FireChangeEvent()
```

## Critical Technical Points

### 1. Item Position Calculation

```cpp
std::pair<int32_t, PickerItemInfo> ContainerPickerPattern::CalcCurrentMiddleItem() const {
    // Calculate middle item index based on current offset
    float middleOffset = currentOffset_ + height_ / 2.0f;

    int32_t index = static_cast<int32_t>(middleOffset / pickerItemHeight_);

    // Adjust index in loop mode
    if (isLoop_) {
        index = (index % totalItemCount_ + totalItemCount_) % totalItemCount_;
    }

    return { index, GetItemInfo(index) };
}
```

### 2. Loop Scroll

```cpp
bool ContainerPickerPattern::IsLoop() const {
    // Enable condition: item count > display count
    return totalItemCount_ > displayCount_ && isLoop_;
}

void ContainerPickerPattern::UpdateColumnChildPosition(double offsetY) {
    for (auto& [index, pos] : itemPosition_) {
        // Calculate new position
        float newPos = pos + offsetY;

        // Handle boundary in loop mode
        if (IsLoop()) {
            if (newPos < -pickerItemHeight_) {
                newPos += totalItemCount_ * pickerItemHeight_;
            } else if (newPos > contentMainSize_) {
                newPos -= totalItemCount_ * pickerItemHeight_;
            }
        }

        itemPosition_[index] = newPos;
    }
}
```

### 3. Inertia Scroll Calculation

```cpp
void ContainerPickerPattern::PlayInertialAnimation() {
    // Calculate inertia distance
    float dragDistance = dragVelocity_ * FLING_DURATION;
    float targetOffset = currentOffset_ + dragDistance;

    // Create target animation
    CreateTargetAnimation(targetOffset);

    // Use friction curve
    animationOption_.SetCurve(Curves::FRICTION);
    animationOption_.SetDuration(FLING_DURATION);

    AnimationUtils::StartAnimation(&context_, animationOption_, [weak = WeakClaim(this)]() {
        // Animation complete callback
    });
}
```

### 4. Spring Rebound

```cpp
void ContainerPickerPattern::PlaySpringAnimation() {
    float endOffset;

    if (IsOutOfStart()) {
        // Exceed upper boundary
        CalcEndOffset(endOffset, 0.0);
    } else if (IsOutOfEnd()) {
        // Exceed lower boundary
        CalcEndOffset(endOffset, 0.0);
    }

    // Use spring curve
    CreateSpringProperty();
    animationOption_.SetCurve(Curves::SPRING_OVERSHOOT);
    animationOption_.SetDuration(SPRING_DURATION);

    AnimationUtils::StartAnimation(&context_, animationOption_, [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SnapToNearestItem();
    });
}

bool ContainerPickerPattern::IsOutOfBoundary(float mainOffset) const {
    // Check if out of boundary
    float minOffset = 0.0f;
    float maxOffset = contentMainSize_ - height_;

    return mainOffset < minOffset || mainOffset > maxOffset;
}
```

### 5. FRC Performance Optimization

```cpp
void ContainerPickerPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus) {
    // Dynamically adjust refresh rate based on scroll speed
    if (speed > FAST_SCROLL_THRESHOLD) {
        // Fast scroll: lower refresh rate
        SetRefreshRate(60 Hz);
    } else if (speed > MEDIUM_SCROLL_THRESHOLD) {
        // Medium scroll: normal refresh rate
        SetRefreshRate(90 Hz);
    } else {
        // Slow or static: high refresh rate
        SetRefreshRate(120 Hz);
    }
}
```

## Property System

### ContainerPickerLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **selectedIndex** | int32_t | 0 | Selected index |
| **options** | vector\<string\> | - | Options list |
| **loop** | bool | true | Whether loop |
| **enableHaptic** | bool | true | Whether haptic enabled |
| **indicatorStyle** | PickerIndicatorStyle | - | Indicator style |

### PickerIndicatorStyle

```cpp
struct PickerIndicatorStyle {
    bool enabled = true;              // Whether enabled
    float width = 1.0f;              // Width
    Color color = Color::GRAY;       // Color
    Dimension startMargin;           // Start margin
    Dimension endMargin;             // End margin
};
```

## Event System

### Event Types

**onChange** - Selection change:
```cpp
void ContainerPickerPattern::FireChangeEvent() {
    auto eventHub = GetEventHub<ContainerPickerEventHub>();
    auto onChange = eventHub->GetChangeEvent();

    if (onChange) {
        onChange(selectedIndex_);  // Trigger ArkTS onChange callback
    }
}
```

**onScrollStop** - Scroll stop:
```cpp
void ContainerPickerPattern::FireScrollStopEvent() {
    auto eventHub = GetEventHub<ContainerPickerEventHub>();
    auto onScrollStop = eventHub->GetScrollStopEvent();

    if (onScrollStop) {
        onScrollStop(selectedIndex_);
    }
}
```

## Animation System

### Animation Types

| Type | Curve | Purpose |
|------|-------|---------|
| **Inertia Scroll** | FRICTION | Inertia movement after drag |
| **Spring Animation** | SPRING_OVERSHOOT | Boundary rebound |
| **Target Animation** | EASE_OUT | Snap to target item |
| **Reset Animation** | EASE_IN_OUT | Fast reset |

### Animation Creation

```cpp
void ContainerPickerPattern::CreateTargetAnimation(float delta) {
    // Create scroll property
    CreateScrollProperty();

    // Set target value
    float targetOffset = currentOffset_ + delta;
    scrollProperty_->Set(targetOffset);

    // Create animation
    auto animation = AnimationUtils::CreateAnimation(
        scrollProperty_,
        AnimationOption()
            .SetDuration(INERTIAL_DURATION)
            .SetCurve(Curves::FRICTION)
    );

    scrollAnimation_ = animation;
    isAnimationRunning_ = true;
}
```

## Haptic Feedback

### Haptic Controller

```cpp
class IPickerAudioHaptic {
public:
    virtual void Play() = 0;              // Play vibration
    virtual void Stop() = 0;              // Stop vibration
    virtual void SetIntensity(float) = 0; // Set intensity
};
```

### Haptic Trigger Timing

```cpp
void ContainerPickerPattern::PlayHaptic(float offset) {
    if (!IsEnableHaptic()) {
        return;
    }

    // Check if crossing item boundary
    int32_t newIndex = static_cast<int32_t>(offset / pickerItemHeight_);
    if (newIndex != selectedIndex_) {
        // Crossing boundary, trigger vibration
        if (hapticController_) {
            hapticController_->Play();
        }
        selectedIndex_ = newIndex;
    }
}
```

## Best Practices

### Basic Usage

```typescript
// 1. Set options
ContainerPicker({ options: ['A', 'B', 'C'] })
  .selected(0)
  .onChange((index: number) => {
    console.log('Selected:', index);
  })

// 2. Enable loop
ContainerPicker()
  .loop(true)

// 3. Disable haptic feedback
ContainerPicker()
  .enableHaptic(false)
```

### Performance Optimization

```typescript
// 1. Limit option count
ContainerPicker()
  .options(items.slice(0, 100))  // Avoid too many options

// 2. Use virtual scrolling
// Automatically implemented internally
```

## Common Issues

| Symptom | Possible Cause | Solution |
|---------|----------------|----------|
| Scroll stutter | Too many items | Reduce item count |
| Rebound unnatural | Spring parameter error | Adjust spring curve |
| Haptic no response | Permission issue | Check haptic permission |
| Position offset | Height calculation error | Check layout config |

## Related Directories

```
frameworks/core/components_ng/pattern/container_picker/
├── container_picker_pattern.h/cpp            # Main logic
├── container_picker_layout_property.h        # Layout properties
├── container_picker_layout_algorithm.h/cpp   # Layout algorithm
├── container_picker_event_hub.h              # Event handling
├── container_picker_paint_method.h/cpp       # Paint method
├── container_picker_utils.h                  # Utils class
└── container_picker_theme.h                  # Theme config
```

## Key Takeaways

1. **Smooth Scroll**: Physics model-based inertia scroll
2. **Snap Alignment**: Automatically snap to nearest item
3. **Loop Scroll**: Support infinite loop option list
4. **Haptic Feedback**: Vibration feedback during scrolling
5. **Boundary Rebound**: Spring animation for boundary rebound
6. **FRC Optimization**: Dynamically adjust refresh rate based on speed
7. **Gesture Support**: Complete drag and click gesture support
8. **Nested Scroll**: Inherits NestableScrollContainer for nested scrolling support
