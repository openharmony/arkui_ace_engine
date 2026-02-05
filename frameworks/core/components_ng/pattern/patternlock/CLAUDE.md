# PatternLock Component - Claude Code Development Guide

> **Component**: PatternLock (Pattern Lock Component)
> **Location**: `components_ng/pattern/patternlock/`
> **Knowledge Base**: [PatternLock_Knowledge_Base.md](../../../../../../docs/pattern/patternlock/PatternLock_Knowledge_Base.md)

---

## Quick Reference

### Core Files

| File | Purpose | Key Classes/Functions |
|------|---------|----------------------|
| `patternlock_pattern.h/cpp` | Pattern Layer Core | `PatternLockPattern`, `OnTouchDown/Move/Up`, `CheckChoosePoint` |
| `patternlock_model_ng.h/cpp` | Model Layer | `PatternLockModelNG::Create`, `SetXxx` methods |
| `patternlock_layout_algorithm.h/cpp` | Layout Algorithm | `PatternLockLayoutAlgorithm::MeasureContent` |
| `patternlock_paint_method.h/cpp` | Paint Method | `PatternLockPaintMethod::UpdateModifier` |
| `patternlock_modifier.h/cpp` | Paint Modifier | `PatternLockModifier`, draws 9 dots and connection lines |
| `patternlock_event_hub.h` | Event Handling | `PatternLockEventHub`, `patternComplete`, `dotConnect` |
| `pattern_lock_controller.h/cpp` | Controller | `PatternLockController::Reset` |

---

## Component Overview

**PatternLock** is a 3x3 grid pattern lock component that supports:
- 3x3 grid layout
- Gesture swipe to connect dots
- Customizable colors, circle radius, line width
- Auto reset functionality
- Skip unselected points
- Accessibility support

---

## Architecture

### Layer Structure

```
Frontend (ArkTS)
    ↓
PatternLockModelNG (Model Layer)
    ↓
PatternLockPattern (Pattern Layer)
    ↓
PatternLockLayoutAlgorithm (Layout Layer)
    ↓
PatternLockPaintMethod + PatternLockModifier (Paint Layer)
    ↓
Rosen/Skia Rendering
```

### Key Data Flow

**Touch Event Flow**:
```
User Touch → PatternLockPattern::HandleTouchEvent()
    → OnTouchDown() / OnTouchMove() / OnTouchUp()
    → CheckChoosePoint() (check if point is hit)
    → AddChoosePoint() (add selected point)
    → UpdateDotConnectEvent() (trigger dot connect event)
    → SetChallengeResult() (set result)
    → patternComplete() (trigger complete callback)
```

**Cell Coordinate System**:
```
  0   1   2
0 [0] [1] [2]
1 [3] [4] [5]
2 [6] [7] [8]

Index calculation: index = y * 3 + x
```

---

## Common Development Tasks

### Task 1: Add New Color Property

**Scenario**: Need to add a new color property, e.g., `shadowColor`

**Steps**:
1. **Model Layer** (`patternlock_model.h`):
   ```cpp
   virtual void SetShadowColor(const Color& shadowColor) = 0;
   ```

2. **ModelNG** (`patternlock_model_ng.h/cpp`):
   ```cpp
   void SetShadowColor(const Color& shadowColor) override;
   static void SetShadowColor(FrameNode* frameNode, const Color& shadowColor);
   ```

3. **PaintProperty** (`patternlock_paint_property.h`):
   ```cpp
   void SetShadowColor(const Color& shadowColor);
   const std::optional<Color>& GetShadowColorValue() const;
   private:
       std::optional<Color> shadowColor_;
   ```

4. **Pattern** (`patternlock_pattern.h/cpp`):
   ```cpp
   // In header
   void UpdateShadowColor(const Color& color, bool isFristLoad = false);

   // In cpp
   void PatternLockPattern::UpdateShadowColor(const Color& color, bool isFristLoad)
   {
       if (!patternLockModifier_) {
           return;
       }
       patternLockModifier_->SetShadowColor(color);
       host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
   }
   ```

5. **Modifier** (`patternlock_modifier.h/cpp`):
   ```cpp
   void SetShadowColor(const Color& color);
   private:
       Color shadowColor_;
   ```

6. **Register in BUILD.gn**: Ensure all new files are included

**Verification**:
```cpp
// Unit Test
TEST_F(PatternLockPatternTest, UpdateShadowColor_ShouldUpdateModifier)
{
    auto pattern = CreatePatternLockPattern();
    Color testColor(0xFF0000FF);

    pattern->UpdateShadowColor(testColor);

    EXPECT_EQ(pattern->GetModifier()->GetShadowColor(), testColor);
}
```

---

### Task 2: Modify Point Detection Algorithm

**Scenario**: Need to adjust hotspot size (from 1.5x radius to 2.0x)

**Location**: `patternlock_pattern.cpp:CheckInHotSpot()`

**Current Implementation**:
```cpp
bool PatternLockPattern::CheckInHotSpot(const OffsetF& offset, int32_t x, int32_t y)
{
    auto cellCenter = GetCellCenter(x, y);
    float distance = (offset - cellCenter).GetDistance();
    float circleRadius = GetHandleCircleRadius();
    return distance <= circleRadius * 1.5f;  // ← Modify here
}
```

**Modified**:
```cpp
return distance <= circleRadius * 2.0f;  // Change to 2.0x
```

**Testing**:
```cpp
TEST_F(PatternLockPatternTest, CheckInHotSpot_With2xRadius_ShouldReturnTrue)
{
    auto pattern = CreatePatternLockPattern();
    pattern->CalculateCellCenter();
    auto cellCenter = pattern->GetCellCenter(0, 0);
    float radius = pattern->GetHandleCircleRadius();

    // Test 2.0x radius boundary
    OffsetF testPoint(
        cellCenter.GetX() + radius * 1.9f,
        cellCenter.GetY()
    );

    bool result = pattern->CheckInHotSpot(testPoint, 0, 0);
    EXPECT_TRUE(result);
}
```

---

### Task 3: Add New Pattern Validation Rule

**Scenario**: Add rule requiring pattern to have at least 5 points (instead of current 4)

**Location**: `patternlock_pattern.cpp:SetChallengeResult()`

**Current**:
```cpp
void PatternLockPattern::SetChallengeResult(V2::PatternLockChallengeResult challengeResult)
{
    challengeResult.success_ = static_cast<int32_t>(choosePoint_.size()) >= 4;
    // ...
}
```

**Modified**:
```cpp
challengeResult.success_ = static_cast<int32_t>(choosePoint_.size()) >= 5;
```

**Better Approach** (using constant):
```cpp
// In patternlock_pattern.h
private:
    static constexpr int32_t MIN_SUCCESS_POINTS = 5;  // Change to 5

// In patternlock_pattern.cpp
challengeResult.success_ = static_cast<int32_t>(choosePoint_.size()) >= MIN_SUCCESS_POINTS;
```

---

### Task 4: Debug Pattern Selection Issues

**Scenario**: User reports certain points cannot be selected

**Debug Steps**:

1. **Add Logging** (`patternlock_pattern.cpp:CheckChoosePoint`):
   ```cpp
   bool PatternLockPattern::CheckChoosePoint(int32_t x, int32_t y) const
   {
       TAG_LOGI(AceLogTag::ACE_PATTERNLOCK,
           "CheckChoosePoint: x=%{public}d, y=%{public}d", x, y);

       for (int32_t i = 0; i < 3; i++) {
           for (int32_t j = 0; j < 3; j++) {
               if (CheckInHotSpot(offset, i, j)) {
                   TAG_LOGI(AceLogTag::ACE_PATTERNLOCK,
                       "Hit detected at [%{public}d, %{public}d]", i, j);
                   return true;
               }
           }
       }
       return false;
   }
   ```

2. **Check Cell Center Calculation** (`patternlock_pattern.cpp:CalculateCellCenter`):
   ```cpp
   void PatternLockPattern::CalculateCellCenter()
   {
       // ... calculation logic ...

       TAG_LOGI(AceLogTag::ACE_PATTERNLOCK,
           "CellCenter: x=%{public}f, y=%{public}f, "
           "contentSize=%{public}fx%{public}f",
           cellCenter_.GetX(), cellCenter_.GetY(),
           contentWidth, contentHeight);
   }
   ```

3. **Verify Hotspot Radius**:
   ```cpp
   float PatternLockPattern::GetHandleCircleRadius(float& handleCircleRadius)
   {
       auto paintProperty = GetPaintProperty<PatternLockPaintProperty>();
       if (paintProperty && paintProperty->GetCircleRadiusValue()) {
           handleCircleRadius = paintProperty->GetCircleRadiusValue()->ConvertToPx();
       }

       TAG_LOGI(AceLogTag::ACE_PATTERNLOCK,
           "CircleRadius: %{public}f", handleCircleRadius);

       return handleCircleRadius;
   }
   ```

---

## Testing Guidelines

### Unit Test Structure

**Test File**: `test/unittest/components_ng/pattern/patternlock/patternlock_pattern_test.cpp`

**Essential Test Cases**:

```cpp
class PatternLockPatternTest : public testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    RefPtr<PatternLockPattern> CreatePatternLockPattern();
    RefPtr<FrameNode> frameNode_;
};

// 1. Lifecycle Tests
TEST_F(PatternLockPatternTest, OnAttachToFrameNode_ShouldInitializeController)
{
    auto pattern = CreatePatternLockPattern();
    pattern->OnAttachToFrameNode();

    EXPECT_NE(pattern->GetPatternLockController(), nullptr);
}

// 2. Touch Event Tests
TEST_F(PatternLockPatternTest, OnTouchDown_ShouldSetFingerId)
{
    auto pattern = CreatePatternLockPattern();
    TouchLocationInfo info(1);
    info.SetLocalLocation(OffsetF(100, 100));

    pattern->OnTouchDown(info);

    EXPECT_EQ(pattern->GetFingerId(), 1);
}

// 3. Point Detection Tests
TEST_F(PatternLockPatternTest, CheckChoosePoint_WithValidPoint_ShouldReturnTrue)
{
    auto pattern = CreatePatternLockPattern();
    pattern->CalculateCellCenter();
    auto center = pattern->GetCellCenter(0, 0);

    bool result = pattern->CheckChoosePoint(center.GetX(), center.GetY());

    EXPECT_TRUE(result);
}

// 4. Skip Logic Tests
TEST_F(PatternLockPatternTest, AddPassPointToChoosePoint_ShouldAddMiddlePoint)
{
    auto pattern = CreatePatternLockPattern();
    pattern->choosePoint_.push_back(PatternLockCell(0, 0));

    std::vector<PatternLockCell> passPointVec;
    pattern->AddPassPointToChoosePoint(0, 2, passPointVec);

    EXPECT_EQ(pattern->choosePoint_.size(), 2);
    EXPECT_EQ(pattern->choosePoint_[1].x, 0);
    EXPECT_EQ(pattern->choosePoint_[1].y, 1);
}

// 5. Controller Tests
TEST_F(PatternLockPatternTest, HandleReset_ShouldClearChoosePoint)
{
    auto pattern = CreatePatternLockPattern();
    pattern->choosePoint_.push_back(PatternLockCell(0, 0));
    pattern->isMoveEventValid_ = true;

    pattern->HandleReset();

    EXPECT_TRUE(pattern->choosePoint_.empty());
    EXPECT_FALSE(pattern->isMoveEventValid_);
}
```

### Branch Coverage Checklist

**PatternLockPattern::OnTouchDown**:
- [ ] Normal flow (fingerId set)
- [ ] First touch (fingerId == -1)
- [ ] Subsequent touch (fingerId != -1)

**PatternLockPattern::AddChoosePoint**:
- [ ] Not in hotspot
- [ ] Already chosen
- [ ] New point
- [ ] Skip middle point (skipUnselectedPoint=true)
- [ ] Don't skip middle point (skipUnselectedPoint=false)

**PatternLockPattern::OnTouchUp**:
- [ ] Auto reset enabled
- [ ] Auto reset disabled
- [ ] Success pattern (>=4 points)
- [ ] Failure pattern (<4 points)

---

## Key Implementation Details

### 1. Cell Center Calculation

**Formula**:
```cpp
cellIntervalX = (contentWidth - paddingLeft - paddingRight) / 4.0f
cellIntervalY = (contentHeight - paddingTop - paddingBottom) / 4.0f

Center coordinates of point [x,y]:
centerX = paddingLeft + cellIntervalX * (x + 1)
centerY = paddingTop + cellIntervalY * (y + 1)
```

**Source**: `patternlock_pattern.cpp:CalculateCellCenter()`

### 2. Hotspot Detection

**Radius Multiplier**: 1.5x circle radius

**Source**: `patternlock_pattern.cpp:CheckInHotSpot()`

### 3. Skip Point Logic

**Condition**: `lastCode + nowCode == 2 * middleCode`

**Valid Skip Patterns**:
- (0,0) → (0,2): skips (0,1)
- (0,0) → (2,0): skips (1,0)
- (0,0) → (2,2): skips (1,1)
- etc.

**Source**: `patternlock_pattern.cpp:AddPassPointToChoosePoint()`

### 4. Multi-Touch Handling

**Logic**: Only track first finger, ignore others

**Source**: `patternlock_pattern.cpp:HandleTouchEvent()`

### 5. Auto Reset Mechanism

**Default**: `autoReset_ = true`

**Trigger**: After `OnTouchUp()` completes

**Source**: `patternlock_pattern.cpp:OnTouchUp()`

---

## Common Issues & Solutions

### Issue 1: Points Cannot Be Selected

**Symptoms**: No response when touching points

**Possible Causes**:
1. Hotspot too small
2. Cell center calculation error
3. Padding affects coordinate transformation

**Debug Steps**:
```cpp
// 1. Check hotspot radius
float radius = pattern->GetHandleCircleRadius();
TAG_LOGI("Radius: %f", radius);

// 2. Check cell center
pattern->CalculateCellCenter();
auto center = pattern->GetCellCenter(0, 0);
TAG_LOGI("Center[0,0]: x=%f, y=%f", center.GetX(), center.GetY());

// 3. Check touch coordinates
auto touchPoint = info.GetLocalLocation();
TAG_LOGI("Touch: x=%f, y=%f", touchPoint.GetX(), touchPoint.GetY());
```

**Solution**: Adjust `HOTSPOT_RADIUS_MULTIPLIER` or check padding values

---

### Issue 2: Skip Logic Not Working

**Symptoms**: Middle points are not automatically added

**Possible Cause**: `skipUnselectedPoint_` flag not set

**Check**:
```cpp
// In PatternLockPattern::InitSkipUnselectedPoint()
void PatternLockPattern::InitSkipUnselectedPoint()
{
    auto paintProperty = GetPaintProperty<PatternLockPaintProperty>();
    if (paintProperty && paintProperty->GetSkipUnselectedPointValue()) {
        skipUnselectedPoint_ = paintProperty->GetSkipUnselectedPointValue().value();
    }
}
```

**Solution**: Ensure `SetSkipUnselectedPoint(true)` is called in Model layer

---

### Issue 3: Animation Not Smooth

**Symptoms**: Connection animation is choppy

**Possible Causes**:
1. Frequent MarkDirtyNode calls
2. Modifier updates too frequent

**Optimization**:
```cpp
// Only mark dirty node when necessary
void PatternLockPattern::AddChoosePoint(...)
{
    if (newPointAdded) {  // Only update when actually adding new point
        StartModifierConnectedAnimate(x, y);
        host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
    }
}
```

---

## Related Documentation

- **Complete Knowledge Base**: [docs/pattern/patternlock/PatternLock_Knowledge_Base.md](../../../../../../docs/pattern/patternlock/PatternLock_Knowledge_Base.md)
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
./out/rk3568/tests/ace_engine/test/unittest/components_ng/pattern/patternlock \
    --gtest_filter=PatternLockPatternTest.CheckChoosePoint
```

### Grep Patterns
```bash
# Find PatternLock pattern usages
grep -r "PatternLockPattern" frameworks/core/components_ng/pattern/patternlock/

# Find touch event handling
grep -r "OnTouch" frameworks/core/components_ng/pattern/patternlock/*.cpp

# Find modifier drawing code
grep -r "Draw" frameworks/core/components_ng/pattern/patternlock/patternlock_modifier.cpp
```

---

**Last Updated**: 2026-02-02
**Maintained By**: Component Development Team
