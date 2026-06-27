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

#include "test/unittest/core/event/drag_event_test_ng.h"

#include "test/mock/frameworks/base/thread/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class DragEventIncrementalCoverageNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }
};
} // namespace

/**
 * @tc.name: DragEventActuatorHandleOnPanActionCancelTest001
 * @tc.desc: Test HandleOnPanActionCancel with allowed and not-allowed drag states.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventIncrementalCoverageNg, DragEventActuatorHandleOnPanActionCancelTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    int32_t cancelCount = 0;
    GestureEventFunc actionStart = [](GestureEvent& info) {};
    GestureEventNoParameter actionCancel = [&cancelCount]() {
        ++cancelCount;
    };
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(actionStart), GestureEventFunc(), GestureEventFunc(), std::move(actionCancel));
    dragEventActuator->userCallback_ = dragEvent;
    dragEventActuator->isDragPrepareFinish_ = true;
    dragEventActuator->HandleOnPanActionCancel();
    EXPECT_EQ(cancelCount, 1);
    EXPECT_FALSE(dragEventActuator->isDragPrepareFinish_);

    auto dragEventWithoutCancel = AceType::MakeRefPtr<DragEvent>(
        GestureEventFunc(), GestureEventFunc(), GestureEventFunc(), GestureEventNoParameter());
    dragEventActuator->userCallback_ = dragEventWithoutCancel;
    dragEventActuator->HandleOnPanActionCancel();
    EXPECT_EQ(cancelCount, 1);

    dragEventActuator->userCallback_ = nullptr;
    dragEventActuator->HandleOnPanActionCancel();
    EXPECT_EQ(cancelCount, 1);

    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        return DragDropInfo();
    };
    frameNode->SetDraggable(true);
    eventHub->SetOnDragStart(std::move(onDragStart));
    dragEventActuator->userCallback_ = dragEvent;
    dragEventActuator->HandleOnPanActionCancel();
    EXPECT_EQ(cancelCount, 1);
}

/**
 * @tc.name: DragEventActuatorDragStatusHelperTest001
 * @tc.desc: Test drag status helper methods.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventIncrementalCoverageNg, DragEventActuatorDragStatusHelperTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    dragEventActuator->SetExecTimerCallback(true);
    EXPECT_TRUE(dragEventActuator->isExecCallback_);

    dragEventActuator->isDragUserReject_ = true;
    dragEventActuator->isThumbnailCallbackTriggered_ = true;
    dragEventActuator->InitDragDropStatusToIdle();
    EXPECT_FALSE(dragEventActuator->isExecCallback_);
    EXPECT_FALSE(dragEventActuator->isDragUserReject_);
    EXPECT_FALSE(dragEventActuator->isThumbnailCallbackTriggered_);
}

/**
 * @tc.name: DragEventActuatorCallTimerCallbackTest001
 * @tc.desc: Test CallTimerCallback with and without pipeline context or task executor.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventIncrementalCoverageNg, DragEventActuatorCallTimerCallbackTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    MockPipelineContext::TearDown();
    dragEventActuator->CallTimerCallback(frameNode);
    EXPECT_FALSE(dragEventActuator->isExecCallback_);

    MockPipelineContext::SetUp();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(nullptr);
    dragEventActuator->CallTimerCallback(frameNode);
    EXPECT_FALSE(dragEventActuator->isExecCallback_);

    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    dragEventActuator->CallTimerCallback(frameNode);
    EXPECT_TRUE(dragEventActuator->isExecCallback_);

    dragEventActuator->CallTimerCallback(frameNode);
    EXPECT_TRUE(dragEventActuator->isExecCallback_);
}
} // namespace OHOS::Ace::NG
