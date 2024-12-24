/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/drag_event/drag_event_test_ng_base_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragStartTestCase {
    bool isMouseDrag = false;
    bool hasOnDragStartFunc = false;
    bool draggable = false;
    bool isTextSelected = false;
    bool expectResult = false;
    DragStartTestCase(
        bool isMouseDrag, bool hasOnDragStartFunc, bool draggable, bool isTextSelected, bool expectResult)
        : isMouseDrag(isMouseDrag), hasOnDragStartFunc(hasOnDragStartFunc),
          draggable(draggable), isTextSelected(isTextSelected), expectResult(expectResult) {}
};

struct DragStartInfo {
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
    DragRet dragResult;
    bool hasPixelMap = true;
};

const std::vector<DragStartTestCase> DRAG_START_TEST_CASES = {
    DragStartTestCase(true, true, true, false, true),     // case 0
    DragStartTestCase(true, true, false, false, false),   // case 1
    DragStartTestCase(true, false, true, false, false),   // case 2
    DragStartTestCase(true, false, false, false, false),  // case 3
    DragStartTestCase(false, true, true, false, true),    // case 4
    DragStartTestCase(false, true, false, false, false),  // case 5
    DragStartTestCase(false, false, true, false, false),  // case 6
    DragStartTestCase(false, false, false, false, false), // case 7
};

const std::vector<DragStartTestCase> DRAG_START_TEST_CASES_FOR_TEXT = {
    DragStartTestCase(true, true, true, true, true),       // case 0
    DragStartTestCase(true, true, true, false, false),     // case 1
    DragStartTestCase(true, true, false, true, false),     // case 2
    DragStartTestCase(true, true, false, false, false),    // case 3
    DragStartTestCase(true, false, true, true, false),     // case 4
    DragStartTestCase(true, false, true, false, false),    // case 5
    DragStartTestCase(true, false, false, true, false),    // case 6
    DragStartTestCase(true, false, false, false, false),   // case 7
    
    DragStartTestCase(false, true, true, true, true),      // case 8
    DragStartTestCase(false, true, true, false, false),    // case 9
    DragStartTestCase(false, true, false, true, false),    // case 10
    DragStartTestCase(false, true, false, false, false),   // case 11
    DragStartTestCase(false, false, true, true, false),    // case 12
    DragStartTestCase(false, false, true, false, false),   // case 13
    DragStartTestCase(false, false, false, true, false),   // case 14
    DragStartTestCase(false, false, false, false, false),  // case 15
};

class DragEventTestNgBase : public DragEventCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    void InitTestFrameNodeStatus(
        const RefPtr<FrameNode>& frameNode, DragStartTestCase inputInfo, DragStartInfo& dragStartInfo);
    GestureEvent CreateGestureEventInfo(DragStartTestCase inputInfo);
    void ResetDragging();
    void MockTouchDown(const RefPtr<DragEventActuator>& actuator);
    void MockDragPanSuccess(const RefPtr<DragEventActuator>& actuator, GestureEvent info);
    void Mock150MSTimerCallback(const RefPtr<DragEventActuator>& actuator, GestureEvent info);
    void MockLongPress500MS(const RefPtr<DragEventActuator>& actuator, GestureEvent info);
    void MockLongPress800MS(const RefPtr<DragEventActuator>& actuator, GestureEvent info);
};

void DragEventTestNgBase::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragEventTestNgBase::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DragEventTestNgBase::InitTestFrameNodeStatus(
    const RefPtr<FrameNode>& frameNode, DragStartTestCase inputInfo, DragStartInfo& dragStartInfo)
{
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(200.0f), NG::CalcLength(200.0f)));
    if (inputInfo.hasOnDragStartFunc) {
        auto onDragStart = [&dragStartInfo](
            const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) -> NG::DragDropInfo {
            info->SetResult(dragStartInfo.dragResult);
            NG::DragDropInfo dragDropInfo;
            if (dragStartInfo.hasPixelMap) {
                dragStartInfo.pixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
            }
            dragDropInfo.pixelMap = dragStartInfo.pixelMap;
            dragDropInfo.extraInfo = dragStartInfo.extraInfo;
            return dragDropInfo;
        };
        auto eventHub = frameNode->GetEventHub<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        eventHub->SetOnDragStart(std::move(onDragStart));
    }
    frameNode->SetDraggable(inputInfo.draggable);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->InitDragDropEvent();
    if (gestureHub->IsTextCategoryComponent(frameNode->GetTag())) {
        gestureHub->SetTextDraggable(true);
        gestureHub->SetIsTextDraggable(true);
        if (inputInfo.isTextSelected) {
            auto textPattern = frameNode->GetPattern<TextBase>();
            textPattern->textSelector_.baseOffset = 0;
            textPattern->textSelector_.destinationOffset = 1;
        }
    }
}

GestureEvent DragEventTestNgBase::CreateGestureEventInfo(DragStartTestCase inputInfo)
{
    GestureEvent info;
    Point globalPoint{ 100.0, 100.0 };
    info.SetGlobalPoint(globalPoint).SetLocalLocation(Offset(globalPoint.GetX(), globalPoint.GetY()));
    info.SetScreenLocation(Offset(110.0f, 110.0f));
    if (inputInfo.isMouseDrag) {
        info.SetSourceDevice(SourceType::MOUSE);
        info.SetInputEventType(InputEventType::MOUSE_BUTTON);
        info.SetSourceTool(SourceTool::MOUSE);
    } else {
        info.SetSourceDevice(SourceType::TOUCH);
        info.SetInputEventType(InputEventType::TOUCH_SCREEN);
        info.SetSourceTool(SourceTool::FINGER);
    }
    return info;
}

void DragEventTestNgBase::ResetDragging()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->ResetDragging();
}

void DragEventTestNgBase::MockTouchDown(const RefPtr<DragEventActuator>& actuator)
{
    ASSERT_NE(actuator, nullptr);
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    ASSERT_NE(gestureHub, nullptr);
    auto frameNode = gestureHub->GetFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    ASSERT_NE(getEventTargetImpl, nullptr);
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    frameNode->GetOrCreateFocusHub();
    actuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, DRAG_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
}

void DragEventTestNgBase::MockDragPanSuccess(const RefPtr<DragEventActuator>& actuator, GestureEvent info)
{
    ASSERT_NE(actuator, nullptr);
    if (actuator->actionStart_) {
        actuator->actionStart_(info);
    }
}

void DragEventTestNgBase::Mock150MSTimerCallback(const RefPtr<DragEventActuator>& actuator, GestureEvent info)
{
    ASSERT_NE(actuator, nullptr);
    if (actuator->longPressRecognizer_ && actuator->longPressRecognizer_->callback_) {
        actuator->longPressRecognizer_->callback_(
            Offset(info.GetScreenLocation().GetX(), info.GetScreenLocation().GetY()));
    }
}

void DragEventTestNgBase::MockLongPress500MS(const RefPtr<DragEventActuator>& actuator, GestureEvent info)
{
    ASSERT_NE(actuator, nullptr);
    if (actuator->longPressRecognizer_->onAction_) {
        (*(actuator->longPressRecognizer_->onAction_))(info);
    }
}

void DragEventTestNgBase::MockLongPress800MS(const RefPtr<DragEventActuator>& actuator, GestureEvent info)
{
    ASSERT_NE(actuator, nullptr);
    if (actuator->longPressUpdate_) {
        actuator->longPressUpdate_(info);
    }
}

/**
 * @tc.name: DragEventTestNGBase001
 * @tc.desc: Test drag start function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgBase, DragEventTestNGBase001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_START_TEST_CASES) {
        /**
        * @tc.steps: step1. create image frameNode.
        */
        auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
        ASSERT_NE(frameNode, nullptr);

        /**
        * @tc.steps: step2. init frameNode drag status.
        */
        DragStartInfo dragStartInfo;
        dragStartInfo.extraInfo = "onDragStart" + std::to_string(caseNum);
        InitTestFrameNodeStatus(frameNode, testCase, dragStartInfo);

        /**
        * @tc.steps: step3. get frameNode dragEventActuator.
        */
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        auto dragEventActuator = gestureHub->GetDragEventActuator();
        ASSERT_NE(dragEventActuator, nullptr);

        /**
        * @tc.steps: step4. call MockTouchDown function to simulate the generation of a down event.
        */
        ResetDragging();
        MockTouchDown(dragEventActuator);

        /**
        * @tc.steps: step5. if non-mouse dragging, simulate the generation of 150ms timer callback and
        *                   500ms, 800ms long press event.
        */
        auto info = CreateGestureEventInfo(testCase);
        if (!testCase.isMouseDrag) {
            Mock150MSTimerCallback(dragEventActuator, info);
            MockLongPress500MS(dragEventActuator, info);
            MockLongPress800MS(dragEventActuator, info);
        }

        /**
        * @tc.steps: step6. call drag start function when pan gesture success.
        * @tc.expected: step6. call MSDP StartDrag function and expect result equals.
        */
        MockDragPanSuccess(dragEventActuator, info);
        auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
        bool actualState = mock->gDragData_.extraInfo == dragStartInfo.extraInfo;
        EXPECT_TRUE(IsDragStartStateEqual(caseNum, actualState, testCase.expectResult));
        ++caseNum;
    }
}

/**
 * @tc.name: DragEventTestNGBase002
 * @tc.desc: Test drag start function when frameNode is text.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgBase, DragEventTestNGBase002, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_START_TEST_CASES_FOR_TEXT) {
        /**
        * @tc.steps: step1. create image frameNode.
        */
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(frameNode, nullptr);

        /**
        * @tc.steps: step2. init frameNode drag status.
        */
        DragStartInfo dragStartInfo;
        dragStartInfo.extraInfo = "onDragStart" + std::to_string(caseNum);
        InitTestFrameNodeStatus(frameNode, testCase, dragStartInfo);

        /**
        * @tc.steps: step3. get frameNode dragEventActuator.
        */
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        auto dragEventActuator = gestureHub->GetDragEventActuator();
        ASSERT_NE(dragEventActuator, nullptr);

        /**
        * @tc.steps: step4. call MockTouchDown function to simulate the generation of a down event.
        */
        ResetDragging();
        MockTouchDown(dragEventActuator);

        /**
        * @tc.steps: step5. if non-mouse dragging, simulate the generation of 150ms timer callback and
        *                   500ms, 800ms long press event.
        */
        auto info = CreateGestureEventInfo(testCase);
        if (!testCase.isMouseDrag) {
            Mock150MSTimerCallback(dragEventActuator, info);
            MockLongPress500MS(dragEventActuator, info);
            MockLongPress800MS(dragEventActuator, info);
            // ensure that pixelMap is not empty when using text components.
            gestureHub->pixelMap_ = PixelMap::CreatePixelMap(static_cast<void*>(new char[1]));
        }

        /**
        * @tc.steps: step6. call drag start function when pan gesture success.
        * @tc.expected: step6. call MSDP StartDrag function and expect result equals.
        */
        MockDragPanSuccess(dragEventActuator, info);
        auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
        bool actualState = mock->gDragData_.extraInfo == dragStartInfo.extraInfo;
        EXPECT_TRUE(IsDragStartStateEqual(caseNum, actualState, testCase.expectResult));
        ++caseNum;
    }
}

/**
 * @tc.name: DragEventTestNGBase003
 * @tc.desc: Abnormal condition testing, test drag start function when drag result is DRAG_FAIL and DRAG_CANCEL.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgBase, DragEventTestNGBase003, TestSize.Level1)
{
    const std::vector<DragRet> DRAG_RESULT_ABNORMAL_TEST_CASE = { DragRet::DRAG_FAIL, DragRet::DRAG_CANCEL };
    for (int caseNum = 0; caseNum < DRAG_RESULT_ABNORMAL_TEST_CASE.size(); ++caseNum) {
        /**
        * @tc.steps: step1. create image frameNode.
        */
        auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
        ASSERT_NE(frameNode, nullptr);

        /**
        * @tc.steps: step2. init frameNode drag status.
        */
        DragStartInfo dragStartInfo;
        dragStartInfo.extraInfo = "onDragStart" + std::to_string(caseNum);
        dragStartInfo.dragResult = DRAG_RESULT_ABNORMAL_TEST_CASE[caseNum];
        DragStartTestCase testCase(false, true, true, false, false);
        InitTestFrameNodeStatus(frameNode, testCase, dragStartInfo);

        /**
        * @tc.steps: step3. get frameNode dragEventActuator.
        */
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureHub, nullptr);
        auto dragEventActuator = gestureHub->GetDragEventActuator();
        ASSERT_NE(dragEventActuator, nullptr);

        /**
        * @tc.steps: step4. call MockTouchDown function to simulate the generation of a down event.
        */
        ResetDragging();
        MockTouchDown(dragEventActuator);

        /**
        * @tc.steps: step5. if non-mouse dragging, simulate the generation of 150ms timer callback and
        *                   500ms, 800ms long press event.
        */
        auto info = CreateGestureEventInfo(testCase);
        if (!testCase.isMouseDrag) {
            Mock150MSTimerCallback(dragEventActuator, info);
            MockLongPress500MS(dragEventActuator, info);
            MockLongPress800MS(dragEventActuator, info);
        }

        /**
        * @tc.steps: step6. call drag start function when pan gesture success.
        * @tc.expected: step6. call MSDP StartDrag function and expect result equals.
        */
        MockDragPanSuccess(dragEventActuator, info);
        auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
        ASSERT_NE(mock, nullptr);
        bool actualState = mock->gDragData_.extraInfo == dragStartInfo.extraInfo;
        EXPECT_TRUE(IsDragStartStateEqual(caseNum, actualState, testCase.expectResult));
    }
}

/**
 * @tc.name: DragEventTestNGBase004
 * @tc.desc: Abnormal condition testing, test drag start function when drag pixelMap is null.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgBase, DragEventTestNGBase004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create image frameNode.
    */
    auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    /**
    * @tc.steps: step2. init frameNode drag status.
    */
    DragStartInfo dragStartInfo;
    dragStartInfo.extraInfo = "pixelMap is null.";
    dragStartInfo.hasPixelMap = false;
    DragStartTestCase testCase(false, true, true, false, false);
    InitTestFrameNodeStatus(frameNode, testCase, dragStartInfo);

    /**
    * @tc.steps: step3. create onDragEnd function.
    */
    auto onDragEnd = [&dragStartInfo](const RefPtr<OHOS::Ace::DragEvent>& info) {
        dragStartInfo.dragResult = info->GetResult();
    };
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnDragEnd(std::move(onDragEnd));

    /**
    * @tc.steps: step4. get frameNode dragEventActuator.
    */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto dragEventActuator = gestureHub->GetDragEventActuator();
    ASSERT_NE(dragEventActuator, nullptr);


    /**
    * @tc.steps: step5. call MockTouchDown function to simulate the generation of a down event.
    */
    ResetDragging();
    MockTouchDown(dragEventActuator);

    /**
    * @tc.steps: step6. if non-mouse dragging, simulate the generation of 150ms timer callback and
    *                   500ms, 800ms long press event.
    */
    auto info = CreateGestureEventInfo(testCase);
    if (!testCase.isMouseDrag) {
        Mock150MSTimerCallback(dragEventActuator, info);
        MockLongPress500MS(dragEventActuator, info);
        MockLongPress800MS(dragEventActuator, info);
    }

    /**
    * @tc.steps: step7. call drag start function when pan gesture success.
    * @tc.expected: step7. call MSDP StartDrag function and expect result equals.
    */
    MockDragPanSuccess(dragEventActuator, info);
    EXPECT_EQ(dragStartInfo.dragResult, DragRet::DRAG_FAIL);
    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    ASSERT_NE(mock, nullptr);
    bool actualState = mock->gDragData_.extraInfo == dragStartInfo.extraInfo;
    EXPECT_EQ(actualState, testCase.expectResult);
}
} // namespace OHOS::Ace::NG