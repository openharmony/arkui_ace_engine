/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"

#include "test/mock/base/mock_drag_window.h"
#include "test/mock/base/mock_subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void GestureEventHubTestFiveNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
    GTEST_LOG_(INFO) << "GestureEventHubTestNg SetUpTestCase";
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

void GestureEventHubTestFiveNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
    GTEST_LOG_(INFO) << "GestureEventHubTestNg TearDownTestCase";
}

/**
 * @tc.name: GestureEventHubTest022
 * @tc.desc: Test HandleOnDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. construct a dragDropProxy and update gestureEventHub attributes.
     */
    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;

    /**
     * @tc.steps: step3. call HandleOnDragUpdate with GestureEvent.
     * @tc.expected: gestureEventHub->dragDropProxy_ is true.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragUpdate(info);
    EXPECT_TRUE(gestureEventHub->dragDropProxy_);

    /**
     * @tc.steps: step4. call HandleOnDragUpdate with GestureEvent.
     * @tc.expected: gestureEventHub->IsDragged() the return value is false.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto dragDropManager = pipeline->GetDragDropManager();
    dragDropManager->SetIsDragged(false);
    gestureEventHub->HandleOnDragUpdate(info);
    EXPECT_FALSE(dragDropManager->IsDragged());
}

/**
 * @tc.name: GestureEventHubTest024
 * @tc.desc: Test HandleOnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps: step2. construct a func and update eventHub attributes.
     */
    auto func = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) { return DragDropInfo(); };
    eventHub->SetOnDrop(func);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, std::move(func));

    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(12);

    /**
     * @tc.steps: step3. call HandleOnDragEnd with GestureEvent.
     * @tc.expected: The return value of gestureEventHub->GetFrameNode() is true.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_TRUE(gestureEventHub->GetFrameNode());

    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;
    pipeline->SetMinPlatformVersion(9);

    /**
     * @tc.steps: step4. call HandleOnDragEnd with GestureEvent.
     * @tc.expected: The return value of gestureEventHub->dragDropProxy_ is false.
     */
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);
}

/**
 * @tc.name: GestureEventHubTest025
 * @tc.desc: Test HandleOnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps: step2. construct a func and update eventHub attributes.
     */
    auto func = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) { return DragDropInfo(); };
    eventHub->SetOnDrop(func);
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, std::move(func));

    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(9);

    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;

    /**
     * @tc.steps: step3. call HandleOnDragEnd with GestureEvent.
     * @tc.expected: gestureEventHub->dragDropProxy_ is null.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);

    eventHub->SetOnDrop(nullptr);
    eventHub->ClearCustomerOnDrop();
    gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);

    /**
     * @tc.steps: step4. call HandleOnDragEnd with GestureEvent.
     * @tc.expected: The return value of eventHub->HasOnDrop() is false.
     */
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_FALSE(eventHub->HasOnDrop());
}

/**
 * @tc.name: GestureEventHubTest026
 * @tc.desc: Test HandleOnDragCancel
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. construct a dragDropProxy and update gestureEventHub attribute.
     */
    constexpr int64_t PROXY_ID_NOT_FIT = 101;
    auto dragDropProxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    gestureEventHub->dragDropProxy_ = dragDropProxy;

    /**
     * @tc.steps: step3. call HandleOnDragCancel.
     * @tc.expected: gestureEventHub->dragDropProxy_ is null.
     */
    gestureEventHub->HandleOnDragCancel();
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);
}

/**
 * @tc.name: GestureEventHubTest027
 * @tc.desc: Test SetOnGestureJudgeBegin and SetOnGestureJudgeNativeBegin
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. construct a gestureJudgeFunc.
     */
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo,
                                const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
        return GestureJudgeResult(1);
    };

    /**
     * @tc.steps: step3. call SetOnGestureJudgeBegin with gestureJudgeFunc.
     * @tc.expected: gestureEventHub->gestureJudgeFunc_ is not null.
     */
    gestureEventHub->SetOnGestureJudgeBegin(gestureJudgeFunc);
    EXPECT_TRUE(gestureEventHub->gestureJudgeFunc_);

    /**
     * @tc.steps: step4. call SetOnGestureJudgeNativeBegin with gestureJudgeFunc.
     * @tc.expected: gestureEventHub->gestureJudgeNativeFunc_ is not null.
     */
    gestureEventHub->SetOnGestureJudgeNativeBegin(gestureJudgeFunc);
    EXPECT_TRUE(gestureEventHub->gestureJudgeNativeFunc_);
}

/**
 * @tc.name: GestureEventHubTest028
 * @tc.desc: Test IsAccessibilityClickable and IsAccessibilityLongClickable
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. Updated properties for gestureEventHub.
     */
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, FINGERS);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);

    /**
     * @tc.steps: step3. call IsAccessibilityClickable.
     * @tc.expected: retFlag is false.
     */
    bool retFlag = gestureEventHub->IsAccessibilityClickable();
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step3. call IsAccessibilityLongClickable.
     * @tc.expected: retFlag is false.
     */
    retFlag = gestureEventHub->IsAccessibilityLongClickable();
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: GestureEventHubTest029
 * @tc.desc: Test GetHitTestModeStr
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call GetHitTestModeStr with hitTestMode_ == -1.
     * @tc.expected: retStr is equal to "HitTestMode.Default".
     */
    gestureEventHub->SetHitTestMode(HitTestMode(-1));
    std::string retStr = GestureEventHub::GetHitTestModeStr(gestureEventHub);
    EXPECT_EQ(retStr, "HitTestMode.Default");

    /**
     * @tc.steps: step3. call GetHitTestModeStr with hitTestMode_ == 4.
     * @tc.expected: retStr is equal to "HitTestMode.Default".
     */
    gestureEventHub->SetHitTestMode(HitTestMode(4));
    retStr = GestureEventHub::GetHitTestModeStr(gestureEventHub);
    EXPECT_EQ(retStr, "HitTestMode.Default");
}

/**
 * @tc.name: GestureEventHubTest030
 * @tc.desc: Test ActClick
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. Updated properties for gestureEventHub.
     */
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, CLICK_COUNTS);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);

    /**
     * @tc.steps: step3. call ActClick.
     * @tc.expected: retFlag is false.
     */
    bool retFlag = gestureEventHub->ActClick();
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: GestureEventHubTest031
 * @tc.desc: Test UpdateGestureHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Updated properties for gestureEventHub.
     */
    gestureEventHub->recreateGesture_ = true;
    auto tapGesture = AceType::MakeRefPtr<TapGesture>(FINGERS, 1);
    gestureEventHub->gestures_.emplace_back(tapGesture);
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, 1, false);
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    gestureEventHub->UpdateGestureHierarchy();

    /**
     * @tc.steps: step3. call UpdateGestureHierarchy.
     * @tc.expected: gestureHierarchy_ has one elements.
     */
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeGestureHierarchy, 1);
}

/**
 * @tc.name: ResetDragActionForWeb001
 * @tc.desc: Test ResetDragActionForWeb
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, ResetDragActionForWeb001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->ResetDragActionForWeb();
    EXPECT_EQ(guestureEventHub->isReceivedDragGestureInfo_, false);
}

/**
 * @tc.name: ResetDragActionForWeb001
 * @tc.desc: Test ResetDragActionForWeb
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, OnDragStart001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    GestureEvent info;
    auto pipline = PipelineContext::GetCurrentContext();
    auto EventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(EventHub);
    auto frameNodeOfEvent = EventHub->GetFrameNode();
    EXPECT_TRUE(frameNodeOfEvent);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    event->SetData(unifiedData);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    event->SetResult(DragRet::DRAG_FAIL);
    guestureEventHub->OnDragStart(info, pipline, frameNode, dragDropInfo, event);
    event->SetResult(DragRet::DRAG_CANCEL);
    guestureEventHub->OnDragStart(info, pipline, frameNode, dragDropInfo, event);
    EXPECT_TRUE(EventHub->dragDropProxy_ == false);
}

/**
 * @tc.name: SetMouseDragGatherPixelMaps001
 * @tc.desc: Test SetMouseDragGatherPixelMaps
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, SetMouseDragGatherPixelMaps001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    guestureEventHub->SetMouseDragGatherPixelMaps();
    guestureEventHub->SetNotMouseDragGatherPixelMaps();
    EXPECT_NE(PipelineContext::GetCurrentContext(), nullptr);
}

/**
 * @tc.name: IsTextCategoryComponent001
 * @tc.desc: Test IsTextCategoryComponent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, IsTextCategoryComponent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    string frameTag = V2::TEXTAREA_ETS_TAG;
    bool result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_TRUE(result);
    frameTag = V2::TEXT_ETS_TAG;
    result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_TRUE(result);
    frameTag = V2::TEXTINPUT_ETS_TAG;
    result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_TRUE(result);
    frameTag = V2::SEARCH_Field_ETS_TAG;
    result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_TRUE(result);
    frameTag = V2::RICH_EDITOR_ETS_TAG;
    result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_TRUE(result);
    frameTag = "";
    result = guestureEventHub->IsTextCategoryComponent(frameTag);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetResponseRegion001
 * @tc.desc: Test SetResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, SetResponseRegion001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> responseRegion;
    guestureEventHub->SetResponseRegion(responseRegion);
    responseRegion.push_back(DimensionRect());
    int32_t callbackInfo = 0;
    guestureEventHub->SetResponseRegionFunc([&callbackInfo](const std::vector<DimensionRect>& /*reponseRegion*/) {
        callbackInfo = 1;
    });
    guestureEventHub->SetResponseRegion(responseRegion);
    EXPECT_TRUE(guestureEventHub->isResponseRegion_);
}

/**
 * @tc.name: RemoveLastResponseRect001
 * @tc.desc: Test RemoveLastResponseRect
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, RemoveLastResponseRect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> responseRegion;
    guestureEventHub->RemoveLastResponseRect();
    responseRegion.push_back(DimensionRect());
    responseRegion.push_back(DimensionRect());
    guestureEventHub->SetResponseRegion(responseRegion);
    guestureEventHub->RemoveLastResponseRect();
    int32_t callbackInfo = 0;
    guestureEventHub->SetResponseRegionFunc([&callbackInfo](const std::vector<DimensionRect>& /*reponseRegion*/) {
        callbackInfo = 1;
    });
    guestureEventHub->RemoveLastResponseRect();
    EXPECT_FALSE(guestureEventHub->isResponseRegion_);
}

/**
 * @tc.name: SetFrameNodeCommonOnTouchEvent001
 * @tc.desc: Test SetFrameNodeCommonOnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, SetFrameNodeCommonOnTouchEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    guestureEventHub->touchEventActuator_ = nullptr;
    TouchEventFunc touchEventFunc = [](TouchEventInfo& info) {};
    guestureEventHub->SetFrameNodeCommonOnTouchEvent(std::move(touchEventFunc));
    EXPECT_NE(guestureEventHub->touchEventActuator_, nullptr);
}

/**
 * @tc.name: SetDropAnimationTest
 * @tc.desc: Test SetDropAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, SetDropAnimation, TestSize.Level1)
{
    auto dropAnimationFun = []() {};
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_FALSE(dragEvent->HasDropAnimation());
    dragEvent->SetDropAnimation(std::move(dropAnimationFun));
    EXPECT_TRUE(dragEvent->HasDropAnimation());
}

/**
 * @tc.name: ExecuteDropAnimation
 * @tc.desc: Test ExecuteDropAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, ExecuteDropAnimation, TestSize.Level1)
{
    bool isExecuted = false;
    auto dropAnimationFun = [&isExecuted]() { isExecuted = true; };
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_FALSE(isExecuted);
    dragEvent->SetDropAnimation(std::move(dropAnimationFun));
    dragEvent->ExecuteDropAnimation();
    EXPECT_TRUE(isExecuted);
}

/**
 * @tc.name: StartVibratorByDrag001
 * @tc.desc: Test StartVibratorByDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, StartVibratorByDrag001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::WEB_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    NG::DragPreviewOption previewOption;
    previewOption.enableHapticFeedback = true;
    frameNode->SetDragPreviewOptions(previewOption, false);
    DragDropGlobalController::GetInstance().UpdateDragFilterShowingStatus(true);
    guestureEventHub->StartVibratorByDrag(frameNode);
    bool dragFilter = DragDropGlobalController::GetInstance().IsDragFilterShowing();
    EXPECT_FALSE(dragFilter);
}

/**
 * @tc.name: StartVibratorByDrag002
 * @tc.desc: Test StartVibratorByDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, StartVibratorByDrag002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    NG::DragPreviewOption previewOption;
    previewOption.enableHapticFeedback = true;
    frameNode->SetDragPreviewOptions(previewOption, false);
    DragDropGlobalController::GetInstance().UpdateDragFilterShowingStatus(true);
    guestureEventHub->StartVibratorByDrag(frameNode);
    bool dragFilter = DragDropGlobalController::GetInstance().IsDragFilterShowing();
    EXPECT_FALSE(dragFilter);
}

/**
 * @tc.name: GetGestureEventInfo
 * @tc.desc: Test GetGestureEventInfo and GetClickInfo
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetGestureEventInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. construct a clickEventActuator
     */
    auto clickCallback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);
    auto eventInfo = gestureEventHub->GetGestureEventInfo();
    auto clickInfo = gestureEventHub->GetClickInfo();
    EXPECT_EQ(eventInfo.GetPointerEventId(), 0);
    EXPECT_EQ(clickInfo.GetFingerId(), 0);
    /**
     * @tc.steps: step3. construct a clickEventActuator null
     */
    gestureEventHub->clickEventActuator_ = nullptr;
    eventInfo = gestureEventHub->GetGestureEventInfo();
    clickInfo = gestureEventHub->GetClickInfo();
    EXPECT_EQ(eventInfo.GetPointerEventId(), 0);
    EXPECT_EQ(clickInfo.GetFingerId(), -1);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected001
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(subRecognizers);
    gestureEventHub->externalParallelRecognizer_.clear();
    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::Parallel, PARALLEL_INDEX_1);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected002
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(subRecognizers);
    gestureEventHub->externalParallelRecognizer_.clear();
    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::Parallel, PARALLEL_INDEX_2);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected003
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(subRecognizers);
    gestureEventHub->externalExclusiveRecognizer_.clear();
    gestureEventHub->externalExclusiveRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::High, PARALLEL_INDEX_1);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected004
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(subRecognizers);
    gestureEventHub->externalExclusiveRecognizer_.clear();
    gestureEventHub->externalExclusiveRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::High, PARALLEL_INDEX_2);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected005
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(subRecognizers);
    gestureEventHub->externalExclusiveRecognizer_.clear();
    gestureEventHub->externalExclusiveRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::High, PARALLEL_INDEX_2);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected006
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected006, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetIsSystemGesture(true);
    auto groupClickRecognizerOne = AceType::MakeRefPtr<ClickRecognizer>();
    auto groupClickRecognizerTwo = AceType::MakeRefPtr<ClickRecognizer>();
    std::vector<RefPtr<NGGestureRecognizer>> groupSubRecognizers = { groupClickRecognizerOne, groupClickRecognizerTwo };
    auto childExclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(groupSubRecognizers);
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { nullptr, childExclusiveRecognizer, clickRecognizer };
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(subRecognizers);
    exclusiveRecognizer->recognizers_.emplace_front(nullptr);
    gestureEventHub->externalExclusiveRecognizer_.clear();
    gestureEventHub->externalExclusiveRecognizer_.push_back(exclusiveRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::High, PARALLEL_INDEX_2);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected007
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected007, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetIsSystemGesture(true);
    auto groupClickRecognizerOne = AceType::MakeRefPtr<ClickRecognizer>();
    groupClickRecognizerOne->SetIsSystemGesture(true);
    auto groupClickRecognizerTwo = AceType::MakeRefPtr<ClickRecognizer>();
    std::vector<RefPtr<NGGestureRecognizer>> groupSubRecognizers = { groupClickRecognizerOne, groupClickRecognizerTwo };
    auto childExclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(groupSubRecognizers);
    auto clickRecognizerTwo = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizerTwo->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { childExclusiveRecognizer, clickRecognizer,
        clickRecognizerTwo };
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(subRecognizers);
    gestureEventHub->externalExclusiveRecognizer_.clear();
    gestureEventHub->externalExclusiveRecognizer_.push_back(exclusiveRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::High, PARALLEL_INDEX_2);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected008
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected008, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetIsSystemGesture(true);
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(subRecognizers);
    gestureEventHub->externalParallelRecognizer_.clear();
    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::Parallel, PARALLEL_INDEX_2);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CheckLastInnerRecognizerCollected009
 * @tc.desc: Test CheckLastInnerRecognizerCollected
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, CheckLastInnerRecognizerCollected009, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetIsSystemGesture(true);
    auto clickRecognizerTwo = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizerTwo->node_ = frameNode;
    std::vector<RefPtr<NGGestureRecognizer>> subRecognizers = { clickRecognizer, clickRecognizerTwo };
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(subRecognizers);
    gestureEventHub->externalParallelRecognizer_.clear();
    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    auto res = gestureEventHub->CheckLastInnerRecognizerCollected(GesturePriority::Parallel, PARALLEL_INDEX_2);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: GestureEventHubSetPanEvent001
 * @tc.desc: Verify SetPanEvent (Dimension version) with new actuator creation
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubSetPanEvent001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    RefPtr<PanEvent> panEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});

    PanDirection direction;
    direction.type = PanDirection::ALL;

    gestureEventHub->SetPanEvent(panEvent, direction, 1, 10.0_px); // 10.0_px is initial distance threshold
    auto panEventActuator = gestureEventHub->panEventActuator_;
    ASSERT_NE(panEventActuator, nullptr);
    EXPECT_EQ(panEventActuator->userCallback_, panEvent);
}

/**
 * @tc.name: GestureEventHubSetPanEvent002
 * @tc.desc: Verify SetPanEvent when actuator already exists (Dimension version)
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubSetPanEvent002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    auto initialEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});
    PanDirection direction { PanDirection::VERTICAL };
    gestureEventHub->SetPanEvent(initialEvent, direction, 1, 10.0_px); // 10.0_px is initial distance threshold

    auto newPanEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});

    gestureEventHub->SetPanEvent(newPanEvent, direction, 1, 10.0_px); // 10.0_px is initial distance threshold
    auto panEventActuator = gestureEventHub->panEventActuator_;
    ASSERT_NE(panEventActuator, nullptr);
    EXPECT_EQ(panEventActuator->userCallback_, newPanEvent);
}

/**
 * @tc.name: GestureEventHubSetPanEvent003
 * @tc.desc: Verify SetPanEvent (PanDistanceMap version) with new actuator creation
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubSetPanEvent003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    auto panEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});

    PanDirection direction { PanDirection::HORIZONTAL };
    PanDistanceMap distanceMap;
    distanceMap[SourceTool::FINGER] = 10.0; // 10.0 is initial distance threshold for FINGER source

    gestureEventHub->SetPanEvent(panEvent, direction, 1, distanceMap);

    auto panEventActuator = gestureEventHub->panEventActuator_;
    ASSERT_NE(panEventActuator, nullptr);
    EXPECT_EQ(panEventActuator->userCallback_, panEvent);
}

/**
 * @tc.name: GestureEventHubSetPanEvent004
 * @tc.desc: Verify SetPanEvent when actuator already exists (PanDistanceMap version)
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventHubSetPanEvent004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    auto initialEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});
    PanDistanceMap initMap;
    initMap[SourceTool::FINGER] = 10.0; // 10.0 is initial distance threshold for FINGER source

    PanDirection direction { PanDirection::ALL };
    gestureEventHub->SetPanEvent(initialEvent, direction, 1, initMap);

    auto newPanEvent = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, [](GestureEvent& /*info*/) {}, []() {});
    gestureEventHub->SetPanEvent(newPanEvent, direction, 1, initMap);

    auto panEventActuator = gestureEventHub->panEventActuator_;
    ASSERT_NE(panEventActuator, nullptr);
    EXPECT_EQ(panEventActuator->userCallback_, newPanEvent);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest001
 * @tc.desc: Test GetDefaultPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and test data
     * @tc.expected: Return default scale when pixelMap is null
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    float result = gestureHub.GetDefaultPixelMapScale(nullptr, info, false, nullptr);
    EXPECT_FLOAT_EQ(result, DEFALUT_DRAG_PPIXELMAP_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest002
 * @tc.desc: Test GetDefaultPixelMapScale with mouse event
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and test data
     * @tc.expected: Return 1.0 for mouse event regardless of other conditions
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));
    EXPECT_NE(pixelMap, nullptr);
    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, false, pixelMap);
    EXPECT_FLOAT_EQ(result, EXPECT_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest003
 * @tc.desc: Test GetDefaultPixelMapScale with menu show and valid preview scale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto dragPreview = frameNode->GetDragPreview();
    dragPreview.onlyForLifting = false;
    frameNode->SetDragPreview(dragPreview);

    gestureHub.menuPreviewScale_ = PREVIEW_DOWN_SCALE;

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));

    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, true, pixelMap);
    EXPECT_FLOAT_EQ(result, PREVIEW_DOWN_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest004
 * @tc.desc: Test GetDefaultPixelMapScale with menu show and adjusted scale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest004, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto dragPreview = frameNode->GetDragPreview();
    dragPreview.onlyForLifting = false;
    frameNode->SetDragPreview(dragPreview);

    gestureHub.frameNodeSize_ = SizeF(SIZE_X, SIZE_Y);
    gestureHub.menuPreviewScale_ = PREVIEW_UP_SCALE;

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(Return(PIXELMAP_HEIGHT));

    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, true, pixelMap);
    EXPECT_FLOAT_EQ(result, PIXELMAP_DEFALUT_LIMIT_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest005
 * @tc.desc: Test GetDefaultPixelMapScale with menu not show
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and test data
     * @tc.expected: Return default scale when menu not show
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto dragPreview = frameNode->GetDragPreview();
    dragPreview.onlyForLifting = false;
    frameNode->SetDragPreview(dragPreview);
    gestureHub.frameNodeSize_ = SizeF(SIZE_X, SIZE_Y);
    gestureHub.menuPreviewScale_ = PREVIEW_DOWN_SCALE;

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));

    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, false, pixelMap);
    EXPECT_FLOAT_EQ(result, DEFALUT_DRAG_PPIXELMAP_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest006
 * @tc.desc: Test GetDefaultPixelMapScale with onlyForLifting true
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and test data
     * @tc.expected: Return default scale when onlyForLifting is true
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto dragPreview = frameNode->GetDragPreview();
    dragPreview.onlyForLifting = true;
    frameNode->SetDragPreview(dragPreview);
    gestureHub.frameNodeSize_ = SizeF(SIZE_X, SIZE_Y);
    gestureHub.menuPreviewScale_ = PREVIEW_DOWN_SCALE;

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));

    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, true, pixelMap);
    EXPECT_FLOAT_EQ(result, DEFALUT_DRAG_PPIXELMAP_SCALE);
}

/**
 * @tc.name: GetDefaultPixelMapScaleTest007
 * @tc.desc: Test GetDefaultPixelMapScale with invalid menuPreviewScale_
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDefaultPixelMapScaleTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub and test data
     * @tc.expected: Return default scale when menuPreviewScale_ is invalid
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    GestureEventHub gestureHub(eventHub);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto dragPreview = frameNode->GetDragPreview();
    dragPreview.onlyForLifting = false;
    frameNode->SetDragPreview(dragPreview);
    gestureHub.frameNodeSize_ = SizeF(SIZE_X, SIZE_Y);
    gestureHub.menuPreviewScale_ = PREVIEW_NEGA_SCALE;
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH_LARGE));

    /**
     * @tc.steps: step2. Call the function under test
     */
    float result = gestureHub.GetDefaultPixelMapScale(frameNode, info, true, pixelMap);

    /**
     * @tc.steps: step3. Verify the return value
     * @tc.expected: Return the default DEFALUT_DRAG_PPIXELMAP_SCALE value
     */
    EXPECT_FLOAT_EQ(result, DEFALUT_DRAG_PPIXELMAP_SCALE);

    /**
     * @tc.steps: step4. Verify menuPreviewScale_ is not modified
     * @tc.expected: menuPreviewScale_ remains the original invalid value
     */
    EXPECT_FLOAT_EQ(gestureHub.menuPreviewScale_, PREVIEW_NEGA_SCALE);
}

/**
 * @tc.name: GestureEventOnDragStartTest001
 * @tc.desc: Test OnDragStart resets drag position-related values.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GestureEventOnDragStartTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode, EventHub, GestureEventHub and DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Prepare pipeline and set non-zero drag position values in dragDropManager.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->dragMovePosition_ = OffsetF(INIT_MOVE_X, INIT_MOVE_Y);
    dragDropManager->lastDragMovePosition_ = OffsetF(LAST_MOVE_X, LAST_MOVE_Y);
    dragDropManager->dragTotalMovePosition_ = OffsetF(TOTAL_MOVE_X, TOTAL_MOVE_Y);

    /**
     * @tc.steps: step3. Call OnDragStart with a valid GestureEvent and DragDropInfo containing a pixelMap.
     * @tc.expected: All position values in dragDropManager are reset to OffsetF().
     */
    auto pixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
    ASSERT_NE(pixelMap, nullptr);
    DragDropInfo dragDropInfo;
    dragDropInfo.pixelMap = pixelMap;
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(dragEvent, nullptr);

    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gestureEventHub->OnDragStart(gestureEvent, pipeline, frameNode, dragDropInfo, dragEvent);

    EXPECT_EQ(dragDropManager->dragMovePosition_, OffsetF());
    EXPECT_EQ(dragDropManager->lastDragMovePosition_, OffsetF());
    EXPECT_EQ(dragDropManager->dragTotalMovePosition_, OffsetF());
}

/**
 * @tc.name: GetDragPreviewInitPositionToScreen001
 * @tc.desc: Test GetDragPreviewInitPositionToScreen when frameNode is null, expect default OffsetF() to be returned
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDragPreviewInitPositionToScreen001, TestSize.Level1)
{
    PreparedInfoForDrag data;
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(nullptr);
    ASSERT_NE(gestureEventHub, nullptr);
    OffsetF result = gestureEventHub->GetDragPreviewInitPositionToScreen(nullptr, data);
    EXPECT_EQ(result, OffsetF());
}

/**
 * @tc.name: GetDragPreviewInitPositionToScreen002
 * @tc.desc: Test when pixelMap is null, expect subtraction with pixelMapHalfSize(0, 0) to proceed normally
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDragPreviewInitPositionToScreen002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->frameNodeOffset_ = OffsetF(FRAME_OFFSET_X, FRAME_OFFSET_Y);
    gestureEventHub->frameNodeSize_ = SizeF(FRAME_WIDTH, FRAME_HEIGHT);
    PreparedInfoForDrag data;
    data.pixelMap = nullptr;
    data.isMenuShow = true;
    data.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    data.badgeNumber = 1;
    data.dragMovePosition = OffsetF(MOVE_OFFSET_X / 2, MOVE_OFFSET_Y);
    OffsetF result = gestureEventHub->GetDragPreviewInitPositionToScreen(PipelineContext::GetCurrentContext(), data);

    EXPECT_NE(result, OffsetF());
}

/**
 * @tc.name: GetDragPreviewInitPositionToScreen003
 * @tc.desc: Test WEB component pixelMap scaling path with matching frameTag branch
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDragPreviewInitPositionToScreen003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::WEB_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    PreparedInfoForDrag data;
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_CALL(*mockPixelMap, GetWidth()).WillRepeatedly(Return(PIXELMAP_WIDTH));
    EXPECT_CALL(*mockPixelMap, GetHeight()).WillRepeatedly(Return(PIXELMAP_HEIGHT));
    data.pixelMap = mockPixelMap;
    DragPreviewOption option;
    option.isScaleEnabled = true;
    frameNode->SetDragPreviewOptions(option);
    gestureEventHub->frameNodeOffset_ = OffsetF(MOVE_OFFSET_X, MOVE_OFFSET_Y);

    OffsetF result = gestureEventHub->GetDragPreviewInitPositionToScreen(PipelineContext::GetCurrentContext(), data);
    EXPECT_NE(result, OffsetF());
}

/**
 * @tc.name: GetDragPreviewInitPositionToScreen004
 * @tc.desc: Test menu case when isMenuShow is true, badgeNumber = 1, and sizeChangeEffect = DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetDragPreviewInitPositionToScreen004, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->frameNodeOffset_ = OffsetF(FRAME_OFFSET_X, FRAME_OFFSET_Y);
    gestureEventHub->frameNodeSize_ = SizeF(FRAME_WIDTH, FRAME_HEIGHT);

    PreparedInfoForDrag data;
    data.pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    data.isMenuShow = true;
    data.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    data.badgeNumber = 1;
    data.dragMovePosition = OffsetF(MOVE_OFFSET_X / 2, MOVE_OFFSET_Y / 2);

    OffsetF result = gestureEventHub->GetDragPreviewInitPositionToScreen(PipelineContext::GetCurrentContext(), data);
    EXPECT_NE(result, OffsetF());
}

/**
 * @tc.name: GetBadgeNumber001
 * @tc.desc: Test GetBadgeNumber when GetFrameNode returns null, expect default value 1
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetBadgeNumber001, TestSize.Level1)
{
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(nullptr);
    ASSERT_NE(gestureEventHub, nullptr);
    auto result = gestureEventHub->GetBadgeNumber(nullptr);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: GetBadgeNumber002
 * @tc.desc: Test GetBadgeNumber when pattern->GetDragRecordSize() >= 0, expect that value to be returned
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetBadgeNumber002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 101, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetPattern<TextPattern>()->ResetDragRecordSize(2);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto result = gestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetBadgeNumber003
 * @tc.desc: Test GetBadgeNumber when pattern->GetDragRecordSize() < 0 and unifiedData size > 1, expect unifiedData size
 * to be returned
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetBadgeNumber003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 101, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetPattern<TextPattern>()->ResetDragRecordSize(-1);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    EXPECT_CALL(*unifiedData, GetSize()).WillOnce(testing::Return(2));
    dragEvent->SetData(unifiedData);
    auto result = gestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetBadgeNumber004
 * @tc.desc: Test GetBadgeNumber when DragPreviewOption sets a custom badgeNumber, expect the set value to be returned
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, GetBadgeNumber004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 101, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetPattern<TextPattern>()->ResetDragRecordSize(-1);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();
    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    DragPreviewOption option;
    option.badgeNumber = 2;
    option.isNumber = true;
    frameNode->SetDragPreviewOptions(option, true);
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto result = gestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: TryDoDragStartAnimation001
 * @tc.desc: Test TryDoDragStartAnimation when subWindow is null
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, TryDoDragStartAnimation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("testNode", 101, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();

    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    RefPtr<Subwindow> subWindow = nullptr;
    GestureEvent info;
    PreparedInfoForDrag data;
    auto ret = gestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TryDoDragStartAnimation002
 * @tc.desc: Test TryDoDragStartAnimation when imageNode is null
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestFiveNg, TryDoDragStartAnimation002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("testNode", 101, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();

    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    RefPtr<Subwindow> subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline != mainPipeline));
    GestureEvent info;
    PreparedInfoForDrag data;

    auto ret = gestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG
