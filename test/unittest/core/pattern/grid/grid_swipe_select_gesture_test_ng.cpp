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

#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::NG {

class GridSwipeSelectGestureTestNg : public GridTestNg {
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

static GestureJudgeFunc GetGestureJudgeCallback(const RefPtr<GridPattern>& pattern)
{
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    return gestureHub->gestureJudgeNativeFunc_;
}

static RefPtr<GestureInfo> CreateGestureInfo(GestureTypeName type, InputEventType inputEventType)
{
    auto info = AceType::MakeRefPtr<GestureInfo>(type);
    info->SetInputEventType(inputEventType);
    return info;
}

static std::shared_ptr<BaseGestureEvent> CreateBaseGestureEvent(InputEventType inputEventType)
{
    auto event = std::make_shared<BaseGestureEvent>();
    event->SetRawInputEventType(inputEventType);
    return event;
}

HWTEST_F(GridSwipeSelectGestureTestNg, InitSwipeSelectEvent001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);

    ASSERT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
    pattern_->InitSwipeSelectEvent();
    EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, UninitSwipeSelectEvent001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->InitSwipeSelectEvent();
    ASSERT_NE(pattern_->swipeSelectPanEvent_, nullptr);

    pattern_->UninitSwipeSelectEvent();
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, InitSwipeSelectEventTwice001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->InitSwipeSelectEvent();
    auto first = pattern_->swipeSelectPanEvent_;
    ASSERT_NE(first, nullptr);

    pattern_->InitSwipeSelectEvent();
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, first);
}

HWTEST_F(GridSwipeSelectGestureTestNg, UninitSwipeSelectEventWhenNull001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    ASSERT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
    EXPECT_NO_FATAL_FAILURE(pattern_->UninitSwipeSelectEvent());
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgeBoxSelectMouseOnlyMultiSelectable001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = true;
    pattern_->InitMouseEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::MOUSE_BUTTON);
    auto baseEvent = CreateBaseGestureEvent(InputEventType::MOUSE_BUTTON);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgeBoxSelectTouchOnlyMultiSelectable001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = true;
    pattern_->InitMouseEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreateBaseGestureEvent(InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgeNoCallbackWithoutInit001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = false;

    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    EXPECT_NE(callback, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgeClearedWhenBothEnabled001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = true;
    pattern_->InitMouseEvent();
    ASSERT_NE(GetGestureJudgeCallback(pattern_), nullptr);

    pattern_->enableEditMode_ = true;
    pattern_->InitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    EXPECT_NE(callback, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgeRestoredOnUninitSwipe001, TestSize.Level0)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = true;
    pattern_->InitMouseEvent();
    pattern_->enableEditMode_ = true;
    pattern_->InitSwipeSelectEvent();
    ASSERT_NE(GetGestureJudgeCallback(pattern_), nullptr);

    pattern_->UninitSwipeSelectEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::BOXSELECT, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreateBaseGestureEvent(InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

HWTEST_F(GridSwipeSelectGestureTestNg, GestureJudgePanGesture001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);
    pattern_->multiSelectable_ = true;
    pattern_->InitMouseEvent();

    auto callback = GetGestureJudgeCallback(pattern_);
    ASSERT_NE(callback, nullptr);

    auto gestureInfo = CreateGestureInfo(GestureTypeName::PAN_GESTURE, InputEventType::TOUCH_SCREEN);
    auto baseEvent = CreateBaseGestureEvent(InputEventType::TOUCH_SCREEN);
    auto result = callback(gestureInfo, baseEvent);
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

HWTEST_F(GridSwipeSelectGestureTestNg, OnModifyDoneInit001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    ASSERT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
    ASSERT_FALSE(pattern_->enableEditMode_);

    pattern_->enableEditMode_ = true;
    pattern_->OnModifyDone();
    EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, OnModifyDoneUninit001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->enableEditMode_ = true;
    pattern_->OnModifyDone();
    ASSERT_NE(pattern_->swipeSelectPanEvent_, nullptr);

    pattern_->enableEditMode_ = false;
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

HWTEST_F(GridSwipeSelectGestureTestNg, OnModifyDoneInitUninitCycle001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    for (int i = 0; i < 3; i++) {
        pattern_->enableEditMode_ = true;
        pattern_->OnModifyDone();
        EXPECT_NE(pattern_->swipeSelectPanEvent_, nullptr);

        pattern_->enableEditMode_ = false;
        pattern_->OnModifyDone();
        EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
    }
}

HWTEST_F(GridSwipeSelectGestureTestNg, HandleSwipeSelectEndRequiresEditMode001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->enableEditMode_ = true;
    pattern_->multiSelectable_ = false;
    pattern_->swipeSelectState_ = SelectableContainerPattern::SwipeSelectState::SELECTING;
    pattern_->HandleSwipeSelectEnd();
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
}

HWTEST_F(GridSwipeSelectGestureTestNg, HandleSwipeSelectEndBlockedByMultiSelectable001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->enableEditMode_ = true;
    pattern_->multiSelectable_ = true;
    pattern_->swipeSelectState_ = SelectableContainerPattern::SwipeSelectState::SELECTING;
    pattern_->HandleSwipeSelectEnd();
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
}

HWTEST_F(GridSwipeSelectGestureTestNg, HandleSwipeSelectEndBlockedByNoEditMode001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->enableEditMode_ = false;
    pattern_->swipeSelectState_ = SelectableContainerPattern::SwipeSelectState::SELECTING;
    pattern_->HandleSwipeSelectEnd();
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
}

HWTEST_F(GridSwipeSelectGestureTestNg, HandleSwipeSelectCancel001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->swipeSelectState_ = SelectableContainerPattern::SwipeSelectState::DESELECTING;
    pattern_->HandleSwipeSelectCancel();
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
}

} // namespace OHOS::Ace::NG
