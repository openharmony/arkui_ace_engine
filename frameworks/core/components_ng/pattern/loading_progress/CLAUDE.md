# LoadingProgress Component - Claude Code Development Guide

> **Component**: LoadingProgress (Loading Progress Component)
> **Location**: `components_ng/pattern/loading_progress/`
> **Knowledge Base**: [LoadingProgress_Knowledge_Base.md](../../../../../../docs/pattern/loading_progress/LoadingProgress_Knowledge_Base.md)

---

## Quick Reference

### Core Files

| File | Purpose | Key Classes/Functions |
|------|---------|----------------------|
| `loading_progress_pattern.h/cpp` | Pattern Layer Core | `LoadingProgressPattern`, `StartAnimation`, `StopAnimation`, `OnVisibleChange` |
| `loading_progress_model_ng.h/cpp` | Model Layer | `LoadingProgressModelNG::Create`, `SetXxx` methods |
| `loading_progress_layout_algorithm.h/cpp` | Layout Algorithm | `LoadingProgressLayoutAlgorithm::MeasureContent` |
| `loading_progress_paint_method.h` | Paint Method | `LoadingProgressPaintMethod::UpdateModifier` |
| `loading_progress_modifier.h/cpp` | Paint Modifier | `LoadingProgressModifier`, animation drawing, custom content |
| `loading_progress_paint_property.h` | Paint Property | `LoadingProgressPaintProperty`, `color`, `enableLoading` |
| `loading_progress_pattern_multi_thread.cpp` | Multi-threading Support | Multi-threaded animation updates |

---

## Component Overview

**LoadingProgress** is a loading progress animation component that supports:
- Circular loading animation
- Customizable colors
- Enable/disable loading control
- Custom content modifier (Builder)
- Visibility management (auto start/stop animation)
- Multi-threaded animation support
- Window state management

---

## Architecture

### Layer Structure

```
Frontend (ArkTS)
    ↓
LoadingProgressModelNG (Model Layer)
    ↓
LoadingProgressPattern (Pattern Layer)
    ↓
LoadingProgressLayoutAlgorithm (Layout Layer)
    ↓
LoadingProgressPaintMethod + LoadingProgressModifier (Paint Layer)
    ↓
Rosen/Skia Rendering
```

### Key Data Flow

**Animation Lifecycle**:
```
OnAttachToMainTree()
    → RegisterVisibleAreaChange() (register visibility listener)
    → StartAnimation()
    → LoadingProgressModifier::SetEnableLoading(true)
    → Animation Playing...

OnVisibleChange(isVisible=false) / OnWindowHide() / enableLoading=false
    → StopAnimation()
    → LoadingProgressModifier::SetEnableLoading(false)
```

**Custom Content Flow**:
```
SetBuilderFunc(makeFunc)
    → FireBuilder()
    → BuildContentModifierNode()
    → contentModifierNode_ = makeFunc(config)
    → LoadingProgressModifier::UseContentModifier(true)
    → Render custom content instead of default animation
```

---

## Common Development Tasks

### Task 1: Add New Animation Type

**Scenario**: Need to add a new animation style, e.g., "pulse" animation

**Steps**:

1. **Add Animation Type Enum** (`loading_progress_paint_property.h`):
   ```cpp
   enum class LoadingProgressAnimationType {
       DEFAULT,      // Default circular
       PULSE,        // Pulse style (new)
       // ...
   };
   ```

2. **Update PaintProperty**:
   ```cpp
   // In loading_progress_paint_property.h
   void SetAnimationType(LoadingProgressAnimationType type);
   const std::optional<LoadingProgressAnimationType>& GetAnimationTypeValue() const;
   private:
       std::optional<LoadingProgressAnimationType> animationType_;
   ```

3. **Update ModelNG** (`loading_progress_model_ng.h/cpp`):
   ```cpp
   // In header
   void SetAnimationType(LoadingProgressAnimationType type);
   static void SetAnimationType(FrameNode* frameNode, LoadingProgressAnimationType type);

   // In cpp
   void LoadingProgressModelNG::SetAnimationType(LoadingProgressAnimationType type)
   {
       auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
       CHECK_NULL_VOID(frameNode);

       auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
       paintProperty->SetAnimationType(type);

       frameNode->MarkModifyDone();
   }
   ```

4. **Update Modifier** (`loading_progress_modifier.h/cpp`):
   ```cpp
   // In header
   void SetAnimationType(LoadingProgressAnimationType type);
   private:
       LoadingProgressAnimationType animationType_ = LoadingProgressAnimationType::DEFAULT;

   // In cpp - Draw method
   void LoadingProgressModifier::Draw(DrawingContext& context)
   {
       if (animationType_ == LoadingProgressAnimationType::PULSE) {
           DrawPulseAnimation(context);
       } else {
           DrawDefaultAnimation(context);
       }
   }

   void LoadingProgressModifier::DrawPulseAnimation(DrawingContext& context)
   {
       auto canvas = context.GetCanvas();
       // Implement pulse animation drawing logic
       // ...
   }
   ```

5. **Update Pattern** (`loading_progress_pattern.cpp:OnModifyDone`):
   ```cpp
   void LoadingProgressPattern::OnModifyDone()
   {
       // ... existing code ...

       auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
       if (paintProperty->GetAnimationTypeValue()) {
           auto type = paintProperty->GetAnimationTypeValue().value();
           loadingProgressModifier_->SetAnimationType(type);
       }
   }
   ```

**Verification**:
```cpp
// Unit Test
TEST_F(LoadingProgressPatternTest, SetPulseAnimation_ShouldUpdateModifier)
{
    auto pattern = CreateLoadingProgressPattern();
    auto paintProperty = pattern->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetAnimationType(LoadingProgressAnimationType::PULSE);

    pattern->OnModifyDone();

    EXPECT_EQ(pattern->GetModifier()->GetAnimationType(),
              LoadingProgressAnimationType::PULSE);
}
```

---

### Task 2: Modify Animation Speed

**Scenario**: Need to adjust animation speed, add an `animationDuration` property

**Steps**:

1. **Add Property** (`loading_progress_paint_property.h`):
   ```cpp
   void SetAnimationDuration(int32_t duration);  // Unit: milliseconds
   const std::optional<int32_t>& GetAnimationDurationValue() const;
   private:
       std::optional<int32_t> animationDuration_ = 2000;  // Default 2000ms
   ```

2. **Update ModelNG**:
   ```cpp
   void LoadingProgressModelNG::SetAnimationDuration(int32_t duration)
   {
       auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
       CHECK_NULL_VOID(frameNode);

       auto paintProperty = frameNode->GetPaintProperty<LoadingProgressPaintProperty>();
       paintProperty->SetAnimationDuration(duration);

       frameNode->MarkModifyDone();
   }
   ```

3. **Update Modifier**:
   ```cpp
   void LoadingProgressModifier::SetAnimationDuration(int32_t duration)
   {
       animationDuration_ = duration;

       // Update animation speed
       UpdateAnimationSpeed();
   }

   void LoadingProgressModifier::UpdateAnimationSpeed()
   {
       // Calculate new animation speed
       float speed = 1000.0f / static_cast<float>(animationDuration_);

       if (animatableProperty_) {
           animatableProperty_->SetAnimationSpeed(speed);
       }
   }
   ```

**Testing**:
```cpp
TEST_F(LoadingProgressModifierTest, SetAnimationDuration_ShouldUpdateSpeed)
{
    auto modifier = CreateLoadingProgressModifier();
    modifier->SetAnimationDuration(1000);  // 1 second

    // Speed should be faster
    EXPECT_GT(modifier->GetAnimationSpeed(), 1.0f);
}
```

---

### Task 3: Add Animation Pause/Resume Feature

**Scenario**: Need to be able to pause and resume animation

**Steps**:

1. **Add Methods to Pattern** (`loading_progress_pattern.h`):
   ```cpp
   public:
       void PauseAnimation();
       void ResumeAnimation();
       bool IsAnimationPaused() const;

   private:
       bool isAnimationPaused_ = false;
   ```

2. **Implement in Pattern** (`loading_progress_pattern.cpp`):
   ```cpp
   void LoadingProgressPattern::PauseAnimation()
   {
       if (!loadingProgressModifier_) {
           return;
       }

       isAnimationPaused_ = true;
       loadingProgressModifier_->SetAnimationPaused(true);

       auto host = GetHost();
       CHECK_NULL_VOID(host);
       host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
   }

   void LoadingProgressPattern::ResumeAnimation()
   {
       if (!loadingProgressModifier_) {
           return;
       }

       isAnimationPaused_ = false;

       // Only resume when enable loading is true and visible
       if (enableLoading_ && isVisibleArea_) {
           loadingProgressModifier_->SetAnimationPaused(false);
       }

       auto host = GetHost();
       CHECK_NULL_VOID(host);
       host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
   }
   ```

3. **Update Modifier**:
   ```cpp
   // In loading_progress_modifier.h
   void SetAnimationPaused(bool paused);
   private:
       bool isAnimationPaused_ = false;

   // In loading_progress_modifier.cpp - Draw method
   void LoadingProgressModifier::Draw(DrawingContext& context)
   {
       if (!enableLoading_ || isAnimationPaused_) {
           // Don't update animation, keep current state
           return;
       }

       // Draw animation normally
       DrawDefaultAnimation(context);
   }
   ```

4. **Add to ModelNG**:
   ```cpp
   // Static methods
   static void PauseAnimation(FrameNode* frameNode);
   static void ResumeAnimation(FrameNode* frameNode);

   // Implementation
   void LoadingProgressModelNG::PauseAnimation(FrameNode* frameNode)
   {
       CHECK_NULL_VOID(frameNode);
       auto pattern = frameNode->GetPattern<LoadingProgressPattern>();
       pattern->PauseAnimation();
   }
   ```

**Testing**:
```cpp
TEST_F(LoadingProgressPatternTest, PauseAnimation_ShouldStopAnimationUpdates)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->StartAnimation();

    pattern->PauseAnimation();

    EXPECT_TRUE(pattern->IsAnimationPaused());
    EXPECT_FALSE(pattern->GetModifier()->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, ResumeAnimation_ShouldRestoreAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->StartAnimation();
    pattern->PauseAnimation();

    pattern->ResumeAnimation();

    EXPECT_FALSE(pattern->IsAnimationPaused());
}
```

---

### Task 4: Debug Animation Not Playing

**Scenario**: LoadingProgress created but animation doesn't play

**Debug Steps**:

1. **Check enableLoading State** (`loading_progress_pattern.cpp:OnModifyDone`):
   ```cpp
   void LoadingProgressPattern::OnModifyDone()
   {
       auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
       enableLoading_ = paintProperty->GetEnableLoadingValue(true);

       TAG_LOGI(AceLogTag::ACE_LOADING_PROGRESS,
           "OnModifyDone: enableLoading_=%{public}d, isVisibleArea_=%{public}d",
           enableLoading_, isVisibleArea_);

       // Start/stop animation based on state
       if (enableLoading_ && isVisibleArea_) {
           StartAnimation();
       } else {
           StopAnimation();
       }
   }
   ```

2. **Check Visibility** (`loading_progress_pattern.cpp:OnVisibleChange`):
   ```cpp
   void LoadingProgressPattern::OnVisibleChange(bool isVisible)
   {
       TAG_LOGI(AceLogTag::ACE_LOADING_PROGRESS,
           "OnVisibleChange: isVisible=%{public}d, enableLoading_=%{public}d",
           isVisible, enableLoading_);

       isVisibleArea_ = isVisible;

       if (enableLoading_) {
           if (isVisible) {
               StartAnimation();
           } else {
               StopAnimation();
           }
       }
   }
   ```

3. **Check Modifier State**:
   ```cpp
   void LoadingProgressPattern::StartAnimation()
   {
       if (!loadingProgressModifier_) {
           TAG_LOGE(AceLogTag::ACE_LOADING_PROGRESS,
               "StartAnimation: Modifier is null!");
           return;
       }

       TAG_LOGI(AceLogTag::ACE_LOADING_PROGRESS,
           "StartAnimation: Setting enableLoading=true");

       loadingProgressModifier_->SetEnableLoading(true);

       auto host = GetHost();
       CHECK_NULL_VOID(host);
       host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
   }
   ```

4. **Check Attachment to Main Tree**:
   ```cpp
   void LoadingProgressPattern::OnAttachToMainTree()
   {
       TAG_LOGI(AceLogTag::ACE_LOADING_PROGRESS,
           "OnAttachToMainTree: Registering and starting animation");

       RegisterVisibleAreaChange();
       StartAnimation();
       FireBuilder();
   }
   ```

**Common Issues**:
- Component not attached to main tree
- `enableLoading` set to `false`
- Component in invisible area
- Window is hidden

---

## Testing Guidelines

### Unit Test Structure

**Test File**: `test/unittest/components_ng/pattern/loading_progress/loading_progress_pattern_test.cpp`

**Essential Test Cases**:

```cpp
class LoadingProgressPatternTest : public testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    RefPtr<LoadingProgressPattern> CreateLoadingProgressPattern();
    RefPtr<FrameNode> frameNode_;
};

// 1. Lifecycle Tests
TEST_F(LoadingProgressPatternTest, OnAttachToMainTree_ShouldStartAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    auto paintProperty = pattern->GetPaintProperty<LoadingProgressPaintProperty>();
    paintProperty->SetEnableLoading(true);

    pattern->OnAttachToMainTree();

    EXPECT_TRUE(pattern->hasVisibleChangeRegistered_);
    EXPECT_TRUE(pattern->GetModifier()->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, OnDetachFromMainTree_ShouldStopAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->OnAttachToMainTree();

    pattern->OnDetachFromMainTree();

    EXPECT_FALSE(pattern->hasVisibleChangeRegistered_);
}

// 2. Animation Control Tests
TEST_F(LoadingProgressPatternTest, StartAnimation_ShouldSetEnableLoadingTrue)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->StartAnimation();

    EXPECT_TRUE(pattern->GetModifier()->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, StopAnimation_ShouldSetEnableLoadingFalse)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->StartAnimation();
    pattern->StopAnimation();

    EXPECT_FALSE(pattern->GetModifier()->GetEnableLoading());
}

// 3. Visibility Tests
TEST_F(LoadingProgressPatternTest, OnVisibleChange_WithEnableLoadingTrue_ShouldStartAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;

    pattern->OnVisibleChange(true);

    EXPECT_TRUE(pattern->GetModifier()->GetEnableLoading());
}

TEST_F(LoadingProgressPatternTest, OnVisibleChange_WithEnableLoadingFalse_ShouldStopAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = false;
    pattern->isVisibleArea_ = true;

    pattern->OnVisibleChange(true);

    EXPECT_FALSE(pattern->GetModifier()->GetEnableLoading());
}

// 4. Color Management Tests
TEST_F(LoadingProgressPatternTest, UpdateColor_WithColorLockTrue_ShouldNotUpdate)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->SetColorLock(true);
    Color newColor(Color::RED);

    pattern->UpdateColor(newColor, false);

    EXPECT_NE(pattern->GetModifier()->GetColor(), newColor);
}

TEST_F(LoadingProgressPatternTest, UpdateColor_WithColorLockFalse_ShouldUpdate)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->SetColorLock(false);
    Color newColor(Color::RED);

    pattern->UpdateColor(newColor, false);

    EXPECT_EQ(pattern->GetModifier()->GetColor(), newColor);
}

// 5. Builder Tests
TEST_F(LoadingProgressPatternTest, SetBuilderFunc_ShouldCreateContentNode)
{
    auto pattern = CreateLoadingProgressPattern();

    auto makeFunc = [](const LoadingProgressConfiguration& config) {
        return FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, -1,
            []() { return MakeRefPtr<TextPattern>(); }
        );
    };

    pattern->SetBuilderFunc(std::move(makeFunc));
    pattern->FireBuilder();

    EXPECT_NE(pattern->GetContentModifierNode(), nullptr);
}

// 6. Window State Tests
TEST_F(LoadingProgressPatternTest, OnWindowHide_ShouldStopAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;
    pattern->StartAnimation();

    pattern->OnWindowHide();

    EXPECT_FALSE(pattern->GetModifier()->GetEnableLoading());
    EXPECT_FALSE(pattern->isShow_);
}

TEST_F(LoadingProgressPatternTest, OnWindowShow_ShouldStartAnimation)
{
    auto pattern = CreateLoadingProgressPattern();
    pattern->enableLoading_ = true;
    pattern->isVisibleArea_ = true;
    pattern->OnWindowHide();

    pattern->OnWindowShow();

    EXPECT_TRUE(pattern->GetModifier()->GetEnableLoading());
    EXPECT_TRUE(pattern->isShow_);
}
```

### Branch Coverage Checklist

**LoadingProgressPattern::OnModifyDone**:
- [ ] Color exists (GetColorValue has value)
- [ ] Color not exists (GetColorValue no value)
- [ ] Enable loading true
- [ ] Enable loading false
- [ ] Visible area true
- [ ] Visible area false
- [ ] Builder exists (makeFunc_ has value)
- [ ] Builder not exists (makeFunc_ no value)

**LoadingProgressPattern::UpdateColor**:
- [ ] Normal update (colorLock_=false)
- [ ] Color locked (colorLock_=true, isFirstLoad=false)
- [ ] First load (isFirstLoad=true)
- [ ] Modifier is null
- [ ] Modifier is not null

**LoadingProgressPattern::FireBuilder**:
- [ ] Builder exists (makeFunc_ has value)
- [ ] Builder not exists (makeFunc_ no value)
- [ ] Content node already exists (contentModifierNode_ != nullptr)
- [ ] Content node is null (contentModifierNode_ == nullptr)

**LoadingProgressPattern::OnVisibleChange**:
- [ ] Visible + enableLoading true
- [ ] Visible + enableLoading false
- [ ] Not visible + enableLoading true
- [ ] Not visible + enableLoading false

---

## Key Implementation Details

### 1. Animation State Management

**States**:
```cpp
bool enableLoading_      // Property control
bool isVisibleArea_      // Visibility control
bool isShow_             // Window state control
```

**Start Condition**: `enableLoading_ && isVisibleArea_`
**Stop Condition**: `!enableLoading_ || !isVisibleArea_`

**Source**: `loading_progress_pattern.cpp:StartAnimation()`, `StopAnimation()`

### 2. Visibility Optimization

**Mechanism**: `VisibleAreaChangeNode` callback

**Source**: `loading_progress_pattern.cpp:RegisterVisibleAreaChange()`

**Benefit**: Automatically stops animation when component is not visible, saves CPU/GPU

### 3. Color Lock Mechanism

**Purpose**: Prevent external color modification after initial set

**Source**: `loading_progress_pattern.cpp:UpdateColor()`

### 4. Custom Content Modifier

**Configuration**:
```cpp
struct LoadingProgressConfiguration : public CommonConfiguration {
    bool enableloading_;
};
```

**Callback Type**:
```cpp
using LoadingProgressMakeCallback =
    std::function<RefPtr<FrameNode>(const LoadingProgressConfiguration&)>;
```

**Source**: `loading_progress_model_ng.h`, `loading_progress_pattern.cpp:FireBuilder()`

### 5. Theme Integration

**Theme**: `LoadingProgressTheme`

**Properties**:
- `loadingColor`: Default loading color
- `focusColor`: Focus color

**Source**: `loading_progress_pattern.cpp:InitThemeValues()`

### 6. Multi-threading Support

**Files**: `loading_progress_pattern_multi_thread.cpp`

**Methods**:
- `OnAttachToFrameNodeMultiThread()`
- `OnAttachToMainTreeMultiThread()`
- `OnDetachFromMainTreeMultiThread()`

**Benefit**: Animation updates in separate thread, better performance

---

## Common Issues & Solutions

### Issue 1: Animation Not Playing

**Symptoms**: Component created but animation doesn't play

**Debug Checklist**:
- [ ] Is `enableLoading` true?
- [ ] Is component attached to main tree?
- [ ] Is component in visible area?
- [ ] Is window visible?

**Debug Code**:
```cpp
// In OnModifyDone
TAG_LOGI("enableLoading_=%d, isVisibleArea_=%d",
    enableLoading_, isVisibleArea_);

// In OnAttachToMainTree
TAG_LOGI("Attached to main tree, starting animation");

// In StartAnimation
if (!loadingProgressModifier_) {
    TAG_LOGE("Modifier is null!");
}
```

**Solution**: Ensure all conditions are met

---

### Issue 2: Color Not Updating

**Symptoms**: `SetColor` called but color doesn't change

**Possible Cause**: Color lock is enabled

**Check**:
```cpp
bool colorLock = pattern->GetColorLock();
TAG_LOGI("Color lock: %d", colorLock);
```

**Solution**:
```cpp
pattern->SetColorLock(false);  // Disable color lock
pattern->UpdateColor(newColor);
```

---

### Issue 3: Visibility Listener Not Working

**Symptoms**: Animation doesn't stop when component scrolls out of view

**Possible Cause**: `RegisterVisibleAreaChange()` not called

**Check**:
```cpp
bool registered = pattern->hasVisibleChangeRegistered_;
TAG_LOGI("Visible change registered: %d", registered);
```

**Solution**: Ensure `OnAttachToMainTree()` is called

---

### Issue 4: Custom Content Not Displaying

**Symptoms**: Builder set but custom content not rendered

**Possible Cause**: `UseContentModifier()` returns false

**Debug**:
```cpp
// In FireBuilder
if (contentModifierNode_) {
    TAG_LOGI("Content node already exists, skipping creation");
    return;
}

TAG_LOGI("Creating content modifier node");
contentModifierNode_ = makeFunc(config);

TAG_LOGI("Content node created: %p", contentModifierNode_.Get());

// In Modifier
if (useContentModifier_) {
    TAG_LOGI("Using content modifier");
    DrawCustomContent(context);
} else {
    TAG_LOGI("Using default animation");
    DrawDefaultAnimation(context);
}
```

**Solution**:
```cpp
loadingProgressModifier_->SetUseContentModifier(true);
loadingProgressModifier_->SetContentModifierNode(contentModifierNode_);
```

---

## Related Documentation

- **Complete Knowledge Base**: [docs/pattern/loading_progress/LoadingProgress_Knowledge_Base.md](../../../../../../docs/pattern/loading_progress/LoadingProgress_Knowledge_Base.md)
- **Component Creation Guide**: [如何新增一个组件.md](../../../../../../如何新增一个组件.md)
- **Project CLAUDE.md**: [CLAUDE.md](../../../../../../CLAUDE.md)

---

## Quick Commands

### Build
```bash
# From OpenHarmony root
./build.sh --product-name rk3568 --build-target ace_engine
```

### Run Tests
```bash
# Build unit tests
./build.sh --product-name rk3568 --build-target unittest

# Run specific test
./out/rk3568/tests/ace_engine/test/unittest/components_ng/pattern/loading_progress \
    --gtest_filter=LoadingProgressPatternTest.StartAnimation
```

### Grep Patterns
```bash
# Find LoadingProgress pattern usages
grep -r "LoadingProgressPattern" frameworks/core/components_ng/pattern/loading_progress/

# Find animation control code
grep -r "StartAnimation\|StopAnimation" frameworks/core/components_ng/pattern/loading_progress/*.cpp

# Find visibility management code
grep -r "OnVisibleChange\|RegisterVisibleAreaChange" frameworks/core/components_ng/pattern/loading_progress/*.cpp

# Find modifier drawing code
grep -r "Draw" frameworks/core/components_ng/pattern/loading_progress/loading_progress_modifier.cpp
```

---

## Performance Optimization Tips

### 1. Visibility Management
Always use `RegisterVisibleAreaChange()` to automatically stop animation when not visible:
```cpp
void LoadingProgressPattern::OnAttachToMainTree()
{
    RegisterVisibleAreaChange();  // ← Don't forget!
    StartAnimation();
}
```

### 2. Avoid Frequent Updates
Only call `MarkDirtyNode()` when necessary:
```cpp
if (valueChanged) {  // Only if value actually changed
    modifier_->SetValue(newValue);
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}
```

### 3. Use Multi-threading for Complex Animations
Enable multi-threading support for better performance:
```cpp
// The framework automatically uses multi-threading methods
// when available
```

### 4. Reuse Components
Avoid frequently creating/destroying LoadingProgress components:
```cpp
// ❌ Bad: Creating new component each time
@State show: boolean = false;
build() {
    if (this.show) {
        LoadingProgress()  // New instance each time
    }
}

// ✅ Good: Reuse component
build() {
    LoadingProgress()
        .enableLoading(this.show)  // Just control state
}
```

---

**Last Updated**: 2026-02-02
**Maintained By**: Component Development Team
