/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "grid_test_ng.h"

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;

GestureJudgeFunc GetGestureJudgeCallback(const RefPtr<GridPattern>& pattern)
{
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    return gestureHub->gestureJudgeNativeFunc_;
}

RefPtr<GestureInfo> CreateGestureInfo(GestureTypeName type, InputEventType inputEventType)
{
    auto info = AceType::MakeRefPtr<GestureInfo>(type);
    info->SetInputEventType(inputEventType);
    return info;
}

std::shared_ptr<PanGestureEvent> CreatePanGestureEvent(int32_t fingerCount, InputEventType inputEventType)
{
    auto event = std::make_shared<PanGestureEvent>();
    event->SetRawInputEventType(inputEventType);
    std::list<FingerInfo> fingers;
    for (int32_t i = 0; i < fingerCount; i++) {
        FingerInfo finger;
        finger.fingerId_ = i;
        fingers.push_back(finger);
    }
    event->SetFingerList(fingers);
    return event;
}
} // namespace

class GridTwoFingerSelectTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }
};

// ============================================================
// ShouldEnableTwoFingerSelect
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, ShouldEnableTwoFingerSelectAllConditionsMet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;

    EXPECT_TRUE(pattern_->ShouldEnableTwoFingerSelect());
}

HWTEST_F(GridTwoFingerSelectTestNg, ShouldEnableTwoFingerSelectNoCallback001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;

    EXPECT_FALSE(pattern_->ShouldEnableTwoFingerSelect());
}

HWTEST_F(GridTwoFingerSelectTestNg, ShouldEnableTwoFingerSelectFingerDisabled001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;

    EXPECT_FALSE(pattern_->ShouldEnableTwoFingerSelect());
}

HWTEST_F(GridTwoFingerSelectTestNg, ShouldEnableTwoFingerSelectEditModeOn001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = true;

    EXPECT_FALSE(pattern_->ShouldEnableTwoFingerSelect());
}

HWTEST_F(GridTwoFingerSelectTestNg, ShouldEnableTwoFingerSelectBindingEventCounts001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;

    EXPECT_TRUE(pattern_->ShouldEnableTwoFingerSelect());
}

// ============================================================
// HasEnableEditModeBinding
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, HasEnableEditModeBindingNeitherSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->HasEnableEditModeBinding());
}

HWTEST_F(GridTwoFingerSelectTestNg, HasEnableEditModeBindingChangeEventSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EXPECT_TRUE(pattern_->HasEnableEditModeBinding());
}

HWTEST_F(GridTwoFingerSelectTestNg, HasEnableEditModeBindingBindingEventSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EXPECT_TRUE(pattern_->HasEnableEditModeBinding());
}

HWTEST_F(GridTwoFingerSelectTestNg, HasEnableEditModeBindingBothSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EXPECT_TRUE(pattern_->HasEnableEditModeBinding());
}

// ============================================================
// FireEnableEditModeChangeEvent fires both callbacks
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, FireEnableEditModeChangeEventBothFire001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool changeEventFired = false;
    bool bindingEventFired = false;
    pattern_->SetEnableEditModeChangeEvent([&](bool) { changeEventFired = true; });
    pattern_->SetEnableEditModeBindingEvent([&](bool) { bindingEventFired = true; });

    pattern_->FireEnableEditModeChangeEvent(true);
    EXPECT_TRUE(changeEventFired);
    EXPECT_TRUE(bindingEventFired);
}

HWTEST_F(GridTwoFingerSelectTestNg, FireEnableEditModeChangeEventValuePassed001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool changeEventValue = false;
    bool bindingEventValue = false;
    pattern_->SetEnableEditModeChangeEvent([&](bool val) { changeEventValue = val; });
    pattern_->SetEnableEditModeBindingEvent([&](bool val) { bindingEventValue = val; });

    pattern_->FireEnableEditModeChangeEvent(true);
    EXPECT_TRUE(changeEventValue);
    EXPECT_TRUE(bindingEventValue);

    pattern_->FireEnableEditModeChangeEvent(false);
    EXPECT_FALSE(changeEventValue);
    EXPECT_FALSE(bindingEventValue);
}

HWTEST_F(GridTwoFingerSelectTestNg, FireEnableEditModeChangeEventOnlyChangeEvent001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool changeEventFired = false;
    pattern_->SetEnableEditModeChangeEvent([&](bool) { changeEventFired = true; });

    EXPECT_NO_FATAL_FAILURE(pattern_->FireEnableEditModeChangeEvent(true));
    EXPECT_TRUE(changeEventFired);
}

HWTEST_F(GridTwoFingerSelectTestNg, FireEnableEditModeChangeEventOnlyBindingEvent001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool bindingEventFired = false;
    pattern_->SetEnableEditModeBindingEvent([&](bool) { bindingEventFired = true; });

    EXPECT_NO_FATAL_FAILURE(pattern_->FireEnableEditModeChangeEvent(true));
    EXPECT_TRUE(bindingEventFired);
}

HWTEST_F(GridTwoFingerSelectTestNg, FireEnableEditModeChangeEventNoCallback001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_NO_FATAL_FAILURE(pattern_->FireEnableEditModeChangeEvent(true));
    EXPECT_NO_FATAL_FAILURE(pattern_->FireEnableEditModeChangeEvent(false));
}

// ============================================================
// SetEnableEditMode fires both callbacks on change
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, SetEnableEditModeFiresBothCallbacks001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    int32_t changeCount = 0;
    int32_t bindingCount = 0;
    pattern_->SetEnableEditModeChangeEvent([&](bool) { changeCount++; });
    pattern_->SetEnableEditModeBindingEvent([&](bool) { bindingCount++; });

    pattern_->SetEnableEditMode(true);
    EXPECT_EQ(changeCount, 1);
    EXPECT_EQ(bindingCount, 1);

    pattern_->SetEnableEditMode(false);
    EXPECT_EQ(changeCount, 2);
    EXPECT_EQ(bindingCount, 2);
}

HWTEST_F(GridTwoFingerSelectTestNg, SetEnableEditModeNoFireOnSameValue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    int32_t changeCount = 0;
    int32_t bindingCount = 0;
    pattern_->SetEnableEditModeChangeEvent([&](bool) { changeCount++; });
    pattern_->SetEnableEditModeBindingEvent([&](bool) { bindingCount++; });

    pattern_->SetEnableEditMode(false);
    EXPECT_EQ(changeCount, 0);
    EXPECT_EQ(bindingCount, 0);
}

// ============================================================
// OnModifyDone needSwipeSelect with ShouldEnableTwoFingerSelect
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, OnModifyDoneInitsSwipeSelectWhenTwoFingerEnabled001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;

    ASSERT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
    pattern_->OnModifyDone();
    EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridTwoFingerSelectTestNg, OnModifyDoneUninitsWhenBothDisabled001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->OnModifyDone();
    ASSERT_NE(pattern_->swipeSelectPanEvent_, nullptr);

    pattern_->SetEnableEditModeBindingEvent(nullptr);
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridTwoFingerSelectTestNg, OnModifyDoneKeepsSwipeSelectWhenEditModeOnAndTwoFingerDisabled001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->OnModifyDone();
    ASSERT_NE(pattern_->swipeSelectPanEvent_, nullptr);

    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = true;
    pattern_->OnModifyDone();
    EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);
}

// ============================================================
// Gesture judge — single PanRecognizer + finger count check
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOffSingleFingerReject001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreatePanGestureEvent(1, InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOffTwoFingerContinue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreatePanGestureEvent(2, InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOnSingleFingerContinue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = true;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreatePanGestureEvent(1, InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOnTwoFingerContinue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = true;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreatePanGestureEvent(2, InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeMouseAlwaysContinue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->isMouseEventInit_ = true;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::MOUSE_BUTTON);
    auto baseEvent = CreatePanGestureEvent(1, InputEventType::MOUSE_BUTTON);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOffThreeFingerReject001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreatePanGestureEvent(3, InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOffFingerTooFarReject001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto event = std::make_shared<PanGestureEvent>();
    event->SetRawInputEventType(InputEventType::TOUCH_SCREEN);
    std::list<FingerInfo> fingers;
    FingerInfo finger0;
    finger0.fingerId_ = 0;
    finger0.globalLocation_ = Offset(0.0, 0.0);
    fingers.push_back(finger0);
    FingerInfo finger1;
    finger1.fingerId_ = 1;
    finger1.globalLocation_ = Offset(500.0, 500.0);
    fingers.push_back(finger1);
    event->SetFingerList(fingers);

    auto result = callback(gestureInfo, event);
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

HWTEST_F(GridTwoFingerSelectTestNg, GestureJudgeEditModeOffFingerNearContinue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeChangeEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    pattern_->enableEditMode_ = false;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto event = std::make_shared<PanGestureEvent>();
    event->SetRawInputEventType(InputEventType::TOUCH_SCREEN);
    std::list<FingerInfo> fingers;
    FingerInfo finger0;
    finger0.fingerId_ = 0;
    finger0.globalLocation_ = Offset(100.0, 100.0);
    fingers.push_back(finger0);
    FingerInfo finger1;
    finger1.fingerId_ = 1;
    finger1.globalLocation_ = Offset(120.0, 120.0);
    fingers.push_back(finger1);
    event->SetFingerList(fingers);

    auto result = callback(gestureInfo, event);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

// ============================================================
// OnModifyDone init/uninit cycle with two-finger select
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, OnModifyDoneCycleWithTwoFingerToggle001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditModeBindingEvent([](bool) {});
    EditModeOptions options;
    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);

    for (int32_t i = 0; i < 3; i++) {
        pattern_->OnModifyDone();
        EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);

        options.enableFingerMultiSelect = false;
        pattern_->SetEditModeOptions(options);
        pattern_->enableEditMode_ = false;
        pattern_->OnModifyDone();
        EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);

        options.enableFingerMultiSelect = true;
        pattern_->SetEditModeOptions(options);
    }
}

// ============================================================
// SetEnableEditMode via GridModelNG static with binding event
// ============================================================

HWTEST_F(GridTwoFingerSelectTestNg, SetEnableEditModeBindingEventViaModelNG001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool bindingFired = false;
    GridModelNG::SetEnableEditModeBindingEvent(AceType::RawPtr(frameNode_), [&](bool) { bindingFired = true; });

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(bindingFired);
}

HWTEST_F(GridTwoFingerSelectTestNg, SetEnableEditModeBindingEventViaModelNGNoFireOnSameValue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    int32_t bindingCount = 0;
    GridModelNG::SetEnableEditModeBindingEvent(AceType::RawPtr(frameNode_), [&](bool) { bindingCount++; });

    pattern_->SetEnableEditMode(false);
    EXPECT_EQ(bindingCount, 0);
}

HWTEST_F(GridTwoFingerSelectTestNg, SetEnableEditModeBindingEventReset001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    int32_t bindingCount = 0;
    GridModelNG::SetEnableEditModeBindingEvent(AceType::RawPtr(frameNode_), [&](bool) { bindingCount++; });
    GridModelNG::SetEnableEditModeBindingEvent(AceType::RawPtr(frameNode_), nullptr);

    pattern_->SetEnableEditMode(true);
    EXPECT_EQ(bindingCount, 0);
}

} // namespace OHOS::Ace::NG
