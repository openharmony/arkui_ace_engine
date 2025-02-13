/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/drag_event/drag_event_common_test_ng.h"

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/gestures/drag_event.h"

#define private public
#define protected public

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragDropStartTestCase {
    GlobalDraggingInfo globalDraggingInfo;
    DragInfo dragInfo;
    MultiDragInfo multiDragInfo;
    InputEventType inputEventType;

    // calculate drag status
    DragDropInitiatingStatus expectStatus = DragDropInitiatingStatus::IDLE;
    DragDropStartTestCase(GlobalDraggingInfo globalDraggingInfo, DragInfo dragInfo, MultiDragInfo multiDragInfo,
        InputEventType inputEventType, DragDropInitiatingStatus expectStatus)
        : globalDraggingInfo(globalDraggingInfo), dragInfo(dragInfo), multiDragInfo(multiDragInfo),
          inputEventType(inputEventType), expectStatus(expectStatus)
    {}
};

class DragDropEventTestNgIssue : public DragEventCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    bool CheckDragDropInitiatingStatus(
        int32_t caseNum, DragDropInitiatingStatus dragStatus, DragDropInitiatingStatus status);
};

void DragDropEventTestNgIssue::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    SystemProperties::dragDropFrameworkStatus_ = 1;
}

void DragDropEventTestNgIssue::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    SystemProperties::dragDropFrameworkStatus_ = 0;
}

bool DragDropEventTestNgIssue::CheckDragDropInitiatingStatus(
    int32_t caseNum, DragDropInitiatingStatus dragStatus, DragDropInitiatingStatus expectStatus)
{
    if (dragStatus == expectStatus) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum
                                       << ", actual state: " << static_cast<int32_t>(dragStatus)
                                       << ", expect state: " << static_cast<int32_t>(expectStatus);
}

const std::vector<DragDropStartTestCase> DRAG_DROP_STATUS_DRAG_INFO_IMAGE_TEST_CASES = {
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(false, false, false, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 0
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(false, false, true, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::IDLE), // case 1
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(false, true, false, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 2
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(false, true, true, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 3
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(true, false, false, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 4
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(true, false, true, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::IDLE), // case 5
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(true, true, false, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 6
    DragDropStartTestCase(GlobalDraggingInfo(false, false), DragInfo(true, true, true, false),
        MultiDragInfo(false, false, false), InputEventType::TOUCH_SCREEN, DragDropInitiatingStatus::READY), // case 7
};

/**
 * @tc.name: DragDropEventTestNGIssue001
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropEventTestNgIssue, DragDropEventTestNGIssue001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_STATUS_DRAG_INFO_IMAGE_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragDropEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        gestureEventHub->SetDragForbiddenForcely(testCase.dragInfo.isDragForbidden);
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        ASSERT_NE(frameNode, nullptr);
        eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
        auto dragDropEventActuator =
            AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
        ASSERT_NE(dragDropEventActuator, nullptr);
        /**
         * @tc.steps: step2. call OnCollectTouchTarget function.
         * @tc.expected: step2. DragDropInitiatingStatus equals.
         */
        frameNode->draggable_ = testCase.dragInfo.isDraggable;
        frameNode->customerSet_ = testCase.dragInfo.isCustomerSet;
        TouchRestrict dragTouchRestrict = { TouchRestrict::NONE };
        dragTouchRestrict.inputEventType = testCase.inputEventType;
        auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
        EXPECT_NE(getEventTargetImpl, nullptr);
        TouchTestResult finalResult;
        ResponseLinkResult responseLinkResult;
        dragDropEventActuator->OnCollectTouchTarget(
            COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
        auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
        ASSERT_NE(handler, nullptr);
        EXPECT_TRUE(
            CheckDragDropInitiatingStatus(caseNum, handler->GetDragDropInitiatingStatus(), testCase.expectStatus));
        caseNum++;
    }
}

} // namespace OHOS::Ace::NG