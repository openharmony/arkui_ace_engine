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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"
#include "core/common/event_manager.h"

#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_interaction_interface.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
struct GestureEventHubAddPanEventTestCase {
    bool needCreatPanEventActuatorFirst = false;
    PanDirection panDirectionType;
    PanDirection comparePanDirectionType;
    bool expectRecreatePanEvent = false;
    Dimension expectDistance;
    GestureEventHubAddPanEventTestCase(bool needCreatPanEventActuatorFirst,
        PanDirection panDirectionType, PanDirection comparePanDirectionType, bool expectRecreatePanEvent,
        Dimension expectDistance)
        : needCreatPanEventActuatorFirst(needCreatPanEventActuatorFirst), panDirectionType(panDirectionType),
        comparePanDirectionType(comparePanDirectionType), expectRecreatePanEvent(expectRecreatePanEvent),
        expectDistance(expectDistance)
    {}
};
const std::vector<GestureEventHubAddPanEventTestCase> ADD_PAN_EVENT_TEST_CASE = {
    GestureEventHubAddPanEventTestCase(false, PAN_DIRECTION_ALL, PAN_DIRECTION_ALL, true, DEFAULT_PAN_DISTANCE),
    GestureEventHubAddPanEventTestCase(false, DRAG_DIRECTION, PAN_DIRECTION_ALL, true, DEFAULT_PAN_DISTANCE),
    GestureEventHubAddPanEventTestCase(true, DRAG_DIRECTION, PAN_DIRECTION_ALL, true, DEFAULT_PAN_DISTANCE),
    GestureEventHubAddPanEventTestCase(true, PAN_DIRECTION_ALL, PAN_DIRECTION_ALL, false, DISTANCE),
};
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize_001
 * @tc.desc: Test CalcFrameNodeOffsetAndSize
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CalcFrameNodeOffsetAndSize_001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto parentNode = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(parentNode);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
    renderContext->UpdateTransformRotate({ 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });

    /**
     * @tc.steps: step3. call CalcFrameNodeOffsetAndSize.
     */
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, true);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    EXPECT_EQ(guestureEventHub->frameNodeOffset_.GetX(), 0.0);
    EXPECT_EQ(guestureEventHub->frameNodeOffset_.GetY(), 0.0);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize_002
 * @tc.desc: Test CalcFrameNodeOffsetAndSize
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CalcFrameNodeOffsetAndSize_002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    dragDropManager->SetMenuWrapperNode(menuWrapperNode);

    /**
     * @tc.steps: step3. call CalcFrameNodeOffsetAndSize.
     */
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, true);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize_003
 * @tc.desc: Test CalcFrameNodeOffsetAndSize
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CalcFrameNodeOffsetAndSize_003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto parentNode = FrameNode::CreateFrameNode(
        "stack", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(parentNode);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
    renderContext->UpdateTransformRotate({ 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });

    /**
     * @tc.steps: step3. set onlyForLifting true.
     */
    DragDropInfo info;
    info.onlyForLifting = true;
    frameNode->SetDragPreview(info);

    /**
     * @tc.steps: step4. call CalcFrameNodeOffsetAndSize.
     */
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, true);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    EXPECT_EQ(guestureEventHub->frameNodeOffset_.GetX(), 0.0);
    EXPECT_EQ(guestureEventHub->frameNodeOffset_.GetY(), 0.0);
}

/**
 * @tc.name: GetDefaultPixelMapScale_001
 * @tc.desc: Test GetDefaultPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetDefaultPixelMapScale_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetDefaultPixelMapScale.
     */
    GestureEvent info;
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    guestureEventHub->GetDefaultPixelMapScale(frameNode, info, true, pixelMap);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);

    guestureEventHub->GetDefaultPixelMapScale(frameNode, info, false, pixelMap);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
}

/**
 * @tc.name: GetPixelMapOffset_001
 * @tc.desc: Test GetPixelMapOffset
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetPixelMapOffset_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetPixelMapOffset.
     */
    GestureEvent info;
    SizeF size(0.0f, 0.0f);
    PreparedInfoForDrag dragInfoData;
    float scale = 0.0f;
    RectF innerRect(0.0f, 0.0f, 0.0f, 0.0f);
    dragInfoData.displayPoint.SetX(0.0f);
    dragInfoData.displayPoint.SetY(0.0f);
    guestureEventHub->GetPixelMapOffset(info, size, dragInfoData, scale, innerRect);
    EXPECT_EQ(innerRect.Width(), 0.0);

    size.SetWidth(2.0f);
    size.SetHeight(2.0f);
    scale = -1.0f;
    guestureEventHub->frameNodeOffset_.SetX(1.0f);
    guestureEventHub->frameNodeOffset_.SetY(1.0f);
    guestureEventHub->GetPixelMapOffset(info, size, dragInfoData, scale, innerRect);
    EXPECT_EQ(innerRect.Width(), 0.0);

    size.SetWidth(7.0f);
    size.SetHeight(8.0f);
    innerRect.SetRect(1.0f, 1.0f, 5.0f, 6.0f);
    guestureEventHub->GetPixelMapOffset(info, size, dragInfoData, scale, innerRect);
    EXPECT_EQ(innerRect.Width(), 5.0);

    guestureEventHub->frameNodeSize_.SetWidth(4.0f);
    guestureEventHub->frameNodeSize_.SetHeight(5.0f);
    innerRect.SetRect(0.0f, 0.0f, 0.0f, 0.0f);
    guestureEventHub->GetPixelMapOffset(info, size, dragInfoData, scale, innerRect);
    EXPECT_EQ(innerRect.Width(), 0);

    dragInfoData.isNeedCreateTiled = true;
    guestureEventHub->GetPixelMapOffset(info, size, dragInfoData, scale, innerRect);
    EXPECT_EQ(innerRect.Width(), 0);
}
 
/**
 * @tc.name: ProcessMenuPreviewScale_001
 * @tc.desc: Test ProcessMenuPreviewScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, ProcessMenuPreviewScale_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call ProcessMenuPreviewScale.
     */
    float scale = 0.0f;
    float previewScale = 0.0f;
    float windowScale = 0.0f;
    float defaultMenuPreviewScale = 0.0f;
    guestureEventHub->ProcessMenuPreviewScale(frameNode, scale, previewScale, windowScale, defaultMenuPreviewScale);
    EXPECT_EQ(frameNode->GetOrCreateGestureEventHub()->GetMenuPreviewScale(), scale);
}

 /**
 * @tc.name: GetPreScaledPixelMapIfExist_001
 * @tc.desc: Test GetPreScaledPixelMapIfExist
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetPreScaledPixelMapIfExist_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. mock pixelmap and subwindow
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(testing::Return(4.0f));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(testing::Return(5.0f));
    guestureEventHub->SetPixelMap(pixelMap);
    guestureEventHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;

    /**
     * @tc.steps: step3. call GetPreScaledPixelMapIfExist.
     */
    EXPECT_NE(guestureEventHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);

    auto frameNode1 = guestureEventHub->GetFrameNode();
    DragDropInfo info;
    info.onlyForLifting = true;
    frameNode1->SetDragPreview(info);
    EXPECT_NE(guestureEventHub->GetPreScaledPixelMapIfExist(2.0f, pixelMap), nullptr);
}

/**
 * @tc.name: GetPixelMapScale_001
 * @tc.desc: Test GetPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetPixelMapScale_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetPixelMapScale.
     */
    auto ret = guestureEventHub->GetPixelMapScale(0.0f, 0.0f);
    EXPECT_EQ(ret, 1);

    ret = guestureEventHub->GetPixelMapScale(1.0f, 1.0f);
    EXPECT_EQ(ret, 1);
}

/**
 * @tc.name: GetPixelMapScale_002
 * @tc.desc: Test GetPixelMapScale
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetPixelMapScale_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetPixelMapScale.
     */
    auto frameNode1 = guestureEventHub->GetFrameNode();
    DragPreviewOption dpo = frameNode1->GetDragPreviewOption();
    dpo.isScaleEnabled = true;
    frameNode1->SetDragPreviewOptions(dpo);
    auto ret = guestureEventHub->GetPixelMapScale(1.0f, 1.0f);
    EXPECT_EQ(ret, 1);

    SystemProperties::SetDevicePhysicalHeight(1300);
    ret = guestureEventHub->GetPixelMapScale(1.0f, 1.0f);
    EXPECT_EQ(ret, 1);

    SystemProperties::SetDevicePhysicalHeight(1300);
    ret = guestureEventHub->GetPixelMapScale(400.0f, 1.0f);
    EXPECT_NE(ret, 1);

    SystemProperties::SetDevicePhysicalHeight(600);
    guestureEventHub->SetTextDraggable(true);
    ret = guestureEventHub->GetPixelMapScale(250.0f, 450.0f);
    EXPECT_NE(ret, 1);

    guestureEventHub->SetTextDraggable(false);
    ret = guestureEventHub->GetPixelMapScale(250.0f, 250.0f);
    EXPECT_NE(ret, 1);
}

/**
 * @tc.name: GenerateMousePixelMap_001
 * @tc.desc: Test GenerateMousePixelMap
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GenerateMousePixelMap_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GenerateMousePixelMap.
     */
    GestureEvent info;
    guestureEventHub->SetTextDraggable(true);
    guestureEventHub->GenerateMousePixelMap(info);
    EXPECT_TRUE(guestureEventHub->GetTextDraggable());
    guestureEventHub->SetTextDraggable(false);
    guestureEventHub->GenerateMousePixelMap(info);
    EXPECT_FALSE(guestureEventHub->GetTextDraggable());
}

 /**
 * @tc.name: HandleNotAllowDrag_001
 * @tc.desc: Test HandleNotAllowDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleNotAllowDrag_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call HandleNotAllowDrag.
     */
    GestureEvent info;
    guestureEventHub->HandleNotAllowDrag(info);
    EXPECT_TRUE(guestureEventHub->isReceivedDragGestureInfo_);
}

/**
 * @tc.name: HandleNotAllowDrag_002
 * @tc.desc: Test HandleNotAllowDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleNotAllowDrag_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call HandleNotAllowDrag.
     */
    GestureEvent info;
    guestureEventHub->isReceivedDragGestureInfo_ = false;
    guestureEventHub->HandleNotAllowDrag(info);
    EXPECT_FALSE(guestureEventHub->isReceivedDragGestureInfo_);
}

/**
 * @tc.name: HandleDragThroughTouch_001
 * @tc.desc: Test HandleDragThroughTouch
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleDragThroughTouch_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call HandleDragThroughTouch.
     */
    auto pipeline1 = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline1);
    auto dragDropManager = pipeline1->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetGrayedState(true);
    guestureEventHub->HandleDragThroughTouch(frameNode);
    EXPECT_TRUE(dragDropManager->GetGrayedState());

    dragDropManager->SetGrayedState(false);
    guestureEventHub->HandleDragThroughTouch(frameNode);
    EXPECT_FALSE(dragDropManager->GetGrayedState());

    auto overlayManager = pipeline1->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    overlayManager->MountGatherNodeToRootNode(frameNode, gatherNodeChildrenInfo);
    guestureEventHub->HandleDragThroughTouch(frameNode);
    EXPECT_TRUE(dragDropManager->GetGrayedState());
}

/**
 * @tc.name: HandleDragThroughMouse_001
 * @tc.desc: Test HandleDragThroughMouse
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, HandleDragThroughMouse_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call HandleDragThroughMouse.
     */
    auto pipeline1 = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline1);
    auto dragDropManager = pipeline1->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetGrayedState(true);
    guestureEventHub->HandleDragThroughMouse(frameNode);
    EXPECT_TRUE(dragDropManager->GetGrayedState());

    dragDropManager->SetGrayedState(false);
    guestureEventHub->HandleDragThroughMouse(frameNode);
    EXPECT_TRUE(dragDropManager->GetGrayedState());

    dragDropManager->SetGrayedState(false);
    guestureEventHub->dragEventActuator_->isSelectedItemNode_ = true;
    guestureEventHub->HandleDragThroughMouse(frameNode);
    EXPECT_TRUE(dragDropManager->GetGrayedState());
}

 /**
 * @tc.name: IsNeedSwitchToSubWindow_001
 * @tc.desc: Test IsNeedSwitchToSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, IsNeedSwitchToSubWindow_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call IsNeedSwitchToSubWindow.
     */
    PreparedInfoForDrag dragInfoData;
    dragInfoData.isMenuShow = true;
    guestureEventHub->IsNeedSwitchToSubWindow(dragInfoData);
    EXPECT_TRUE(dragInfoData.isMenuShow);

    dragInfoData.isMenuShow = false;
    dragInfoData.isNeedCreateTiled = true;
    guestureEventHub->IsNeedSwitchToSubWindow(dragInfoData);
    EXPECT_TRUE(dragInfoData.isNeedCreateTiled);

    dragInfoData.isMenuShow = false;
    dragInfoData.isNeedCreateTiled = false;
    guestureEventHub->IsNeedSwitchToSubWindow(dragInfoData);
    EXPECT_FALSE(guestureEventHub->IsPixelMapNeedScale());
}

 /**
 * @tc.name: ParsePixelMapAsync_001
 * @tc.desc: Test ParsePixelMapAsync
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, ParsePixelMapAsync_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call ParsePixelMapAsync.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    DragDropInfo dragDropInfo;
    DragDropInfo dragPreviewInfo;
    GestureEvent info;
    auto ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_FALSE(ret);

    dragPreviewInfo.pixelMap = pixelMap;
    ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_TRUE(ret);

    guestureEventHub->dragPreviewPixelMap_ = nullptr;
    dragPreviewInfo.pixelMap = nullptr;
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragPreviewInfo.customNode = customNode1;
    ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_TRUE(ret);

    guestureEventHub->SetDragPreviewPixelMap(pixelMap);
    ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_TRUE(ret);

    guestureEventHub->dragPreviewPixelMap_ = nullptr;
    dragPreviewInfo.inspectorId = "";
    dragPreviewInfo.inspectorId = "test";
    ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_TRUE(ret);

    guestureEventHub->dragPreviewPixelMap_ = pixelMap;
    ret = guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DoOnDragStartHandling_001
 * @tc.desc: Test DoOnDragStartHandling
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DoOnDragStartHandling_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call DoOnDragStartHandling.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);

    dragPreviewInfo.pixelMap = pixelMap;
    ctx.dragDropInfo = dragDropInfo;
    ctx.dragPreviewInfo = dragPreviewInfo;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_TRUE(guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info));
    EXPECT_TRUE(guestureEventHub->HandleResolvedDragPreview(ctx));
}

/**
 * @tc.name: DoOnDragStartHandling_002
 * @tc.desc: Test DoOnDragStartHandling
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DoOnDragStartHandling_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call DoOnDragStartHandling.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    DragDropInfo dragDropInfo;
    InputEventType inputEventType_ = InputEventType::TOUCH_SCREEN;
    info.SetInputEventType(inputEventType_);
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    guestureEventHub->textDraggable_ = true;
    guestureEventHub->pixelMap_ = pixelMap;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_NE(ctx.dragDropInfo.pixelMap, nullptr);

    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    dragDropInfo.pixelMap = nullptr;
    guestureEventHub->pixelMap_ = nullptr;
    ctx.info = info;
    ctx.dragDropInfo = dragDropInfo;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);
}

/**
 * @tc.name: StartVibratorByDrag_001
 * @tc.desc: Test StartVibratorByDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, StartVibratorByDrag_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call StartVibratorByDrag.
     */
    guestureEventHub->StartVibratorByDrag(frameNode);
    EXPECT_FALSE(OHOS::Ace::NG::DragDropGlobalController::GetInstance().isDragFilterShowing_);

    DragPreviewOption previewOption;
    previewOption.enableHapticFeedback = true;
    frameNode->SetDragPreviewOptions(previewOption);
    guestureEventHub->StartVibratorByDrag(frameNode);

    previewOption.enableHapticFeedback = false;
    frameNode->SetDragPreviewOptions(previewOption);
    OHOS::Ace::NG::DragDropGlobalController::GetInstance().isDragFilterShowing_ = true;
    guestureEventHub->StartVibratorByDrag(frameNode);

    previewOption.enableHapticFeedback = true;
    frameNode->SetDragPreviewOptions(previewOption);
    OHOS::Ace::NG::DragDropGlobalController::GetInstance().isDragFilterShowing_ = true;
    guestureEventHub->StartVibratorByDrag(frameNode);
    EXPECT_FALSE(OHOS::Ace::NG::DragDropGlobalController::GetInstance().isDragFilterShowing_);
}

/**
 * @tc.name: GetDragPreviewInitPositionToScreen_001
 * @tc.desc: Test GetDragPreviewInitPositionToScreen
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetDragPreviewInitPositionToScreen_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetDragPreviewInitPositionToScreen.
     */
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    PreparedInfoForDrag data;
    auto offsetF = guestureEventHub->GetDragPreviewInitPositionToScreen(context, data);
    EXPECT_EQ(offsetF.GetX(), 0.0f);

    guestureEventHub->textDraggable_ = true;
    offsetF = guestureEventHub->GetDragPreviewInitPositionToScreen(context, data);

    guestureEventHub->textDraggable_ = false;
    offsetF = guestureEventHub->GetDragPreviewInitPositionToScreen(context, data);
    EXPECT_EQ(offsetF.GetX(), 0.0f);

    data.imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 0, AceType::MakeRefPtr<ImagePattern>());
    auto frameNode1 =guestureEventHub->GetFrameNode();
    frameNode1->tag_ = V2::WEB_ETS_TAG;
    data.isMenuShow = true;
    offsetF = guestureEventHub->GetDragPreviewInitPositionToScreen(context, data);
    EXPECT_EQ(offsetF.GetX(), 0.0f);

    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect= DraggingSizeChangeEffect::SIZE_TRANSITION;
    data.imageNode->SetDragPreviewOptions(previewOption);
    OffsetF dragMovePosition = { 2.0f, 3.0f };
    data.dragMovePosition = dragMovePosition;
    offsetF = guestureEventHub->GetDragPreviewInitPositionToScreen(context, data);
    EXPECT_EQ(offsetF.GetX(), 2.0f);
}

/**
 * @tc.name: GetBadgeNumber_001
 * @tc.desc: Test GetBadgeNumber
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetBadgeNumber_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call GetBadgeNumber.
     */
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(dragEvent, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    dragEvent->SetData(unifiedData);
    EXPECT_CALL(*unifiedData, GetSize()).WillRepeatedly(testing::Return(5));
    dragEvent->SetUseDataLoadParams(false);
    auto ret1 = guestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(ret1, 5);

    dragEvent->SetUseDataLoadParams(true);
    RefPtr<MockDataLoadParams> mockDataLoadParams = AceType::MakeRefPtr<MockDataLoadParams>();
    ASSERT_NE(mockDataLoadParams, nullptr);
    dragEvent->SetDataLoadParams(mockDataLoadParams);
    EXPECT_CALL(*mockDataLoadParams, GetRecordCount()).WillRepeatedly(testing::Return(-1));
    auto ret2 = guestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(ret2, 1);

    EXPECT_CALL(*mockDataLoadParams, GetRecordCount()).WillRepeatedly(testing::Return(0));
    auto ret3 = guestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(ret3, 1);

    EXPECT_CALL(*mockDataLoadParams, GetRecordCount()).WillRepeatedly(testing::Return(INT32_MAX + 1));
    auto ret4 = guestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(ret4, 1);

    EXPECT_CALL(*mockDataLoadParams, GetRecordCount()).WillRepeatedly(testing::Return(10));
    auto ret5 = guestureEventHub->GetBadgeNumber(dragEvent);
    EXPECT_EQ(ret5, 10);
}

/**
 * @tc.name: TryDoDragStartAnimation_001
 * @tc.desc: Test TryDoDragStartAnimation
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, TryDoDragStartAnimation_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call TryDoDragStartAnimation.
     */
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    RefPtr<Subwindow> subWindow = nullptr;
    GestureEvent info;
    PreparedInfoForDrag data;
    auto ret = guestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_FALSE(ret);

    auto pipeline1 = AceType::DynamicCast<PipelineContext>(context);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline1 != mainPipeline));
    ret = guestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_FALSE(ret);

    data.imageNode =  FrameNode::CreateCommonNode("node", 1, false, AceType::MakeRefPtr<Pattern>());
    ret = guestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNodePositionBeforeStartAnimation_001
 * @tc.desc: Test UpdateNodePositionBeforeStartAnimation
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateNodePositionBeforeStartAnimation_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call UpdateNodePositionBeforeStartAnimation.
     */
    PreparedInfoForDrag data;
    guestureEventHub->UpdateNodePositionBeforeStartAnimation(frameNode, data);
    EXPECT_EQ(data.dragPreviewOffsetToScreen.GetX(), 0.0f);

    data.isMenuShow = true;
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);
    guestureEventHub->UpdateNodePositionBeforeStartAnimation(frameNode, data);
    EXPECT_EQ(data.dragPreviewOffsetToScreen.GetX(), 0.0f);
}

/**
 * @tc.name: CheckAllowDrag_001
 * @tc.desc: Test CheckAllowDrag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CheckAllowDrag_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call CheckAllowDrag.
     */
    GestureEvent info;
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_FALSE(ret);

    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) -> DragDropInfo {
        NG::DragDropInfo itemInfo;
        itemInfo.customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        return itemInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
    ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_TRUE(ret);

    auto frameNode1 = guestureEventHub->GetFrameNode();
    frameNode1->SetDraggable(false);
    ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_FALSE(ret);

    frameNode1->SetDraggable(true);
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    auto pipeline1 = AceType::DynamicCast<PipelineContext>(context);
    auto eventManager = pipeline1->GetEventManager();
    eventManager->SetLastMoveBeforeUp(true);
    ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CreateDragEvent_001
 * @tc.desc: Test CreateDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CreateDragEvent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call CreateDragEvent.
     */
    GestureEvent info;
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto dragEvent = guestureEventHub->CreateDragEvent(info, context, frameNode);
    EXPECT_EQ(dragEvent->GetX(), 0);
}

/**
 * @tc.name: CreateDragEvent_002
 * @tc.desc: Test CreateDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CreateDragEvent_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call CreateDragEvent.
     */
    GestureEvent info;
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto dragEvent = guestureEventHub->CreateDragEvent(info, context, frameNode);
    EXPECT_EQ(dragEvent->GetX(), 0);
}

/**
 * @tc.name: AddPreviewMenuHandleDragEnd_001
 * @tc.desc: Test AddPreviewMenuHandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, AddPreviewMenuHandleDragEnd_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call AddPreviewMenuHandleDragEnd.
     */
    auto actionEnd = [](const GestureEvent& info) {
        return;
    };
    guestureEventHub->AddPreviewMenuHandleDragEnd(actionEnd);
    EXPECT_NE(guestureEventHub->scrollableActuator_, nullptr);

    guestureEventHub->AddPreviewMenuHandleDragEnd(actionEnd);
    EXPECT_NE(guestureEventHub->scrollableActuator_, nullptr);
}

/**
 * @tc.name: SetDragEventd_001
 * @tc.desc: Test SetDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragEvent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call SetDragEvent.
     */
    RefPtr<DragEvent> dragEvent = nullptr;
    PanDirection direction;
    int32_t fingers = 0;
    Dimension distance;
    guestureEventHub->SetDragEvent(dragEvent, direction, fingers, distance);
    EXPECT_NE(guestureEventHub->dragEventActuator_, nullptr);

    guestureEventHub->dragEventActuator_->SetIsNewFwk(true);
    guestureEventHub->SetDragEvent(dragEvent, direction, fingers, distance);
    EXPECT_NE(guestureEventHub->dragEventActuator_, nullptr);

    guestureEventHub->dragEventActuator_ = nullptr;
    guestureEventHub->SetDragEvent(dragEvent, direction, fingers, distance);
    EXPECT_NE(guestureEventHub->dragEventActuator_, nullptr);
}

/**
 * @tc.name: SetDragDropEvent_001
 * @tc.desc: Test SetDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragDropEvent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call SetDragDropEvent.
     */
    guestureEventHub->SetDragDropEvent();
    EXPECT_TRUE(guestureEventHub->isDragNewFwk_);

    guestureEventHub->dragEventActuator_->SetIsNewFwk(true);
    guestureEventHub->SetDragDropEvent();
    EXPECT_TRUE(guestureEventHub->isDragNewFwk_);

    guestureEventHub->dragEventActuator_ = nullptr;
    guestureEventHub->SetDragDropEvent();
    EXPECT_TRUE(guestureEventHub->isDragNewFwk_);
}

/**
 * @tc.name: RemoveDragEvent_001
 * @tc.desc: Test RemoveDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, RemoveDragEvent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call RemoveDragEvent.
     */
    guestureEventHub->RemoveDragEvent();
    EXPECT_NE(guestureEventHub->dragEventActuator_, nullptr);

    guestureEventHub->dragEventActuator_->SetIsNewFwk(true);
    guestureEventHub->RemoveDragEvent();
    EXPECT_EQ(guestureEventHub->dragEventActuator_, 0);

    guestureEventHub->dragEventActuator_ = nullptr;
    guestureEventHub->RemoveDragEvent();
    EXPECT_EQ(guestureEventHub->dragEventActuator_, 0);
}

/**
 * @tc.name: SetThumbnailCallback_001
 * @tc.desc: Test SetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetThumbnailCallback_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call SetThumbnailCallback.
     */
    auto func = [](Offset offset) {
        return;
    };
    guestureEventHub->SetThumbnailCallback(func);
    EXPECT_NE(guestureEventHub->dragEventActuator_, nullptr);

    guestureEventHub->dragEventActuator_ = nullptr;
    guestureEventHub->SetThumbnailCallback(func);
    EXPECT_EQ(guestureEventHub->dragEventActuator_, 0);
}

/**
 * @tc.name: CheckNeedDragDropFrameworkStatus_001
 * @tc.desc: Test CheckNeedDragDropFrameworkStatus
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, CheckNeedDragDropFrameworkStatus_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("Web", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call CheckNeedDragDropFrameworkStatus.
     */
    SystemProperties::dragDropFrameworkStatus_ = 0;
    guestureEventHub->InitDragDropEvent();
    
    SystemProperties::dragDropFrameworkStatus_ = 1;
    guestureEventHub->InitDragDropEvent();
    auto frameNode1 = guestureEventHub->GetFrameNode();
    EXPECT_EQ(frameNode1->GetTag(), "Web");
}

/**
 * @tc.name: UpdateMenuNode001
 * @tc.desc: Test UpdateMenuNode
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateMenuNode001, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    targetNode->MountToParent(rootNode);
    textNode->MountToParent(targetNode);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    ASSERT_NE(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    PreparedInfoForDrag data;
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    frameNode->SetDragPreviewOptions(previewOption);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    RectF RECT(0.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(data.frameNodeRect, RECT);
    EXPECT_EQ(data.menuRect, RECT);
    EXPECT_EQ(data.menuPositionLeft, 0.0f);
    EXPECT_EQ(data.menuPositionTop, 0.0f);
    EXPECT_EQ(data.menuPositionRight, 0.0f);
    EXPECT_EQ(data.menuPositionBottom, 0.0f);
}

/**
 * @tc.name: UpdateMenuNode002
 * @tc.desc: Test UpdateMenuNode
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateMenuNode002, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    targetNode->MountToParent(rootNode);
    textNode->MountToParent(targetNode);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    ASSERT_NE(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(0.0f, 0.0f));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    auto previewNode = menuWrapperPattern->GetPreview();
    ASSERT_NE(previewNode, nullptr);
    auto previewRenderContext = previewNode->GetRenderContext();
    ASSERT_NE(previewRenderContext, nullptr);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(previewRenderContext);
    RectF frameSize(1.0f, 1.0f, 1.0f, 1.0f);
    mockRenderContext->SetPaintRectWithTransform(frameSize);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    PreparedInfoForDrag data;
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    RectF RECT(0.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(data.frameNodeRect, frameSize);
    EXPECT_EQ(data.menuRect, RECT);
    EXPECT_EQ(data.menuPositionLeft, -1.0f);
    EXPECT_EQ(data.menuPositionTop, -1.0f);
    EXPECT_EQ(data.menuPositionRight, 2.0f);
    EXPECT_EQ(data.menuPositionBottom, 2.0f);
}

/**
 * @tc.name: UpdateMenuNode003
 * @tc.desc: Test UpdateMenuNode
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateMenuNode003, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    targetNode->MountToParent(rootNode);
    textNode->MountToParent(targetNode);
    MenuParam menuParam;
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    PreparedInfoForDrag data;
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    frameNode->SetDragPreviewOptions(previewOption);
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    EXPECT_EQ(data.menuNode, nullptr);
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);
    menuWrapperPattern->SetHasTransitionEffect(true);
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    EXPECT_EQ(data.menuNode, nullptr);
    menuWrapperPattern->SetHasTransitionEffect(false);
    menuWrapperPattern->SetMenuStatus(MenuStatus::ON_HIDE_ANIMATION);
    guestureEventHub->UpdateMenuNode(menuWrapperNode, data, frameNode);
    EXPECT_EQ(data.menuNode, nullptr);
}

/**
 * @tc.name: MinRecognizerGroupLoopSizeTest001
 * @tc.desc: Test ProcessTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, MinRecognizerGroupLoopSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    OffsetF coordinateOffset;
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    PointF localPoint;

    /**
     * @tc.steps: step2. create userRecognizer and set to gestureHierarchy_.
     */
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, 1, false);
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0.0);
    panRecognizer->SetPriority(GesturePriority::Parallel);
    gestureEventHub->gestureHierarchy_.emplace_back(panRecognizer);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);

    auto otherFrameNode = FrameNode::CreateFrameNode("otherButton",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto otherClickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    otherClickRecognizer->AttachFrameNode(otherFrameNode);
    std::vector<RefPtr<NGGestureRecognizer>> exclusiveRecognizerGroup;
    exclusiveRecognizerGroup.push_back(otherClickRecognizer);
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(exclusiveRecognizerGroup);
    gestureEventHub->externalExclusiveRecognizer_.push_back(exclusiveRecognizer);

    /**
     * @tc.steps: step3. call ProcessTouchTestHit , recognizer is not instance of recognizer group
     * @tc.expected: result is false
     */
    auto result = gestureEventHub->ProcessTouchTestHit(
        coordinateOffset, touchRestrict, innerTargets, finalResult, 2, localPoint, nullptr, responseLinkResult);
    auto sizeOfResponseLinkResult = static_cast<int32_t>(responseLinkResult.size());
    EXPECT_FALSE(result);
    EXPECT_EQ(sizeOfResponseLinkResult, 3);
}

/**
 * @tc.name: GestureEventHubProcessTouchHitTest001
 * @tc.desc: Test ProcessTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubProcessTouchHitTest001, TestSize.Level1)
{
    auto panActionStart = [](GestureEvent& info) {};
    auto panActionUpdate = [](GestureEvent& info) {};
    auto panActionEnd = [](GestureEvent& info) {};
    auto panActionCancel = []() {};
    auto panEvent = AceType::MakeRefPtr<PanEvent>(
        std::move(panActionStart), std::move(panActionUpdate), std::move(panActionEnd), std::move(panActionCancel));

    for (const auto &testCase : ADD_PAN_EVENT_TEST_CASE) {
        /**
        * @tc.steps: step1. Create GestureEventHub.
        * @tc.expected: gestureEventHub is not null.
        */
        auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
        auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
        ASSERT_NE(gestureEventHub, nullptr);
        PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN, DISTANCE } };
        PanDistanceMapDimension expectDistanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE } };
        auto panEventActuator = AceType::MakeRefPtr<PanEventActuator>(
            AceType::WeakClaim(AceType::RawPtr(gestureEventHub)),
            testCase.panDirectionType, FINGERS_NUMBER, distanceMap);
        ASSERT_NE(panEventActuator, nullptr);
        if (testCase.needCreatPanEventActuatorFirst) {
            gestureEventHub->panEventActuator_ = panEventActuator;
        } else {
            gestureEventHub->panEventActuator_ = nullptr;
        }
        gestureEventHub->AddPanEvent(panEvent, testCase.comparePanDirectionType, FINGERS, expectDistanceMap);
        if (testCase.expectRecreatePanEvent) {
            EXPECT_NE(gestureEventHub->panEventActuator_, panEventActuator);
        } else {
            EXPECT_EQ(gestureEventHub->panEventActuator_, panEventActuator);
        }
        ASSERT_NE(gestureEventHub->panEventActuator_, nullptr);
        auto panRecognizer = gestureEventHub->panEventActuator_->panRecognizer_;
        ASSERT_NE(panRecognizer, nullptr);
        EXPECT_EQ(panRecognizer->GetDistance(), testCase.expectDistance.ConvertToPx());
    }
}

/**
 * @tc.name: ProcessTouchTestHitSequence001
 * @tc.desc: Test ProcessTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, ProcessTouchTestHitSequence001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create recognizer and add to innerTargets.
     */
    OffsetF coordinateOffset;
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    PointF localPoint;
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0.0);
    panRecognizer->SetPriority(GesturePriority::Low);
    innerTargets.emplace_back(panRecognizer);

    auto otherFrameNode = FrameNode::CreateFrameNode(
        "scroll", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollGestureEventHub = otherFrameNode->GetOrCreateGestureEventHub();
    auto scrollableActuator =
        AceType::MakeRefPtr<ScrollableActuator>(AceType::WeakClaim(AceType::RawPtr(scrollGestureEventHub)));

    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto panRecognizerNG = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0.0);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    scrollableEvent->SetScrollable(scrollable);
    scrollableActuator->AddScrollableEvent(scrollableEvent);
    EXPECT_EQ(scrollableActuator->scrollableEvents_.size(), 1);
    scrollGestureEventHub->scrollableActuator_ = scrollableActuator;

    /**
     * @tc.steps: step2. call ProcessTouchTestHit , recognizer is not instance of recognizer group
     * @tc.expected: result is false
     */
    auto result = scrollGestureEventHub->ProcessTouchTestHit(
        coordinateOffset, touchRestrict, innerTargets, finalResult, 2, localPoint, nullptr, responseLinkResult);
    EXPECT_FALSE(result);
    EXPECT_FALSE(panRecognizer->IsSystemGesture());
}

/**
 * @tc.name: PrepareDragStartInfo_001
 * @tc.desc: Test PrepareDragStartInfo
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, PrepareDragStartInfo_001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNodeGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(frameNodeGeometryNode, nullptr);
    frameNodeGeometryNode->SetFrameSize(SizeF(100, 50));
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(event, nullptr);
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapperNode, nullptr);
    dragDropManager->SetMenuWrapperNode(menuWrapperNode);

    /**
     * @tc.steps: step3. call PrepareDragStartInfo.
     */
    PreparedInfoForDrag data;
    data.dragPreviewRect = RectF(OffsetF(100, 200), SizeF(100, 200));
    guestureEventHub->PrepareDragStartInfo(pipeline, data, frameNode);
    EXPECT_EQ(data.originPreviewRect.Width(), 100);
}

/**
 * @tc.name: PrepareDragStartInfo_002
 * @tc.desc: Test PrepareDragStartInfo
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, PrepareDragStartInfo_002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(event, nullptr);
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);

    auto pipeline = frameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    auto imageNodeGeometryNode = imageNode->GetGeometryNode();
    ASSERT_NE(imageNodeGeometryNode, nullptr);
    imageNodeGeometryNode->SetFrameSize(SizeF(100, 50));
    columnNode->AddChild(imageNode);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));;
    overlayManager->hasPixelMap_ = true;

    /**
     * @tc.steps: step3. call PrepareDragStartInfo.
     */
    PreparedInfoForDrag data;
    data.dragPreviewRect = RectF(OffsetF(100, 200), SizeF(100, 200));
    guestureEventHub->PrepareDragStartInfo(pipeline, data, frameNode);
    EXPECT_EQ(data.originPreviewRect.Width(), 100);
}

/**
 * @tc.name: PrepareDragStartInfo_003
 * @tc.desc: Test PrepareDragStartInfo
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, PrepareDragStartInfo_003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create GestureEventHub.
    * @tc.expected: gestureEventHub is not null.
    */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

   /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(event, nullptr);
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    DragPreviewOption previewOption;
    previewOption.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION;
    frameNode->SetDragPreviewOptions(previewOption);

    auto pipeline = frameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step3. call PrepareDragStartInfo.
     */
    PreparedInfoForDrag data;
    data.dragPreviewRect = RectF(OffsetF(100, 200), SizeF(100, 200));
    guestureEventHub->PrepareDragStartInfo(pipeline, data, frameNode);
    EXPECT_EQ(data.originPreviewRect.Width(), 100);
}

/**
 * @tc.name: InitDragStartTargets_001
 * @tc.desc: Test InitDragStartTargets - success path where all checks pass
 * @tc.type: FUNC
 * @tc.require: Issue the function initialization
 */
HWTEST_F(GestureEventHubTestNg, InitDragStartTargets_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("nnnnn", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call CheckAllowDrag.
     */
    GestureEvent info;
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_FALSE(ret);

    auto eventHub = guestureEventHub->eventHub_.Upgrade();
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) -> DragDropInfo {
        NG::DragDropInfo itemInfo;
        itemInfo.customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        return itemInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
    ret = guestureEventHub->CheckAllowDrag(info, context, frameNode);
    EXPECT_TRUE(ret);


    /**
     * @tc.steps: step4. Call InitDragStartTargets
     * @tc.expected: Returns true, context is initialized
     */
    DragStartContext ctx;
    ctx.frameNode = frameNode;
    ctx.pipeline = pipeline;
    bool result = guestureEventHub->InitDragStartTargets(info, ctx);

    /**
     * @tc.expected: result is true, context fields are populated
     */
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitDragStartTargets_002
 * @tc.desc: Test InitDragStartTargets - failure path where GetFrameNode returns null
 * @tc.type: FUNC
 * @tc.require: Issue the function null frameNode handling
 */
HWTEST_F(GestureEventHubTestNg, InitDragStartTargets_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub without proper host
     * @tc.expected: gestureEventHub exists but has no valid frameNode
     */
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Create GestureEvent
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_PAD;

    /**
     * @tc.steps: step3. Call InitDragStartTargets
     * @tc.expected: Returns false because frameNode is null
     */
    DragStartContext ctx;
    bool result = gestureEventHub->InitDragStartTargets(info, ctx);

    /**
     * @tc.expected: result is false, HandleNotAllowDrag is called
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InitDragStartRequestState_001
 * @tc.desc: Test InitDragStartRequestState - MOUSE_BUTTON event path
 * @tc.type: FUNC
 * @tc.require: Issue the function mouse event handling
 */
HWTEST_F(GestureEventHubTestNg, InitDragStartRequestState_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with MOUSE_BUTTON event
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.frameNode = frameNode;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call InitDragStartRequestState
     * @tc.expected: SetMouseDragMonitorState(true) is called
     */
    gestureEventHub->InitDragStartRequestState(ctx);

    /**
     * @tc.expected: Mouse drag monitor state is set
     */
    EXPECT_EQ(ctx.info.GetInputEventType(), InputEventType::MOUSE_BUTTON);
}

/**
 * @tc.name: InitDragStartRequestState_002
 * @tc.desc: Test InitDragStartRequestState - TOUCH event path
 * @tc.type: FUNC
 * @tc.require: Issue the function touch event handling
 */
HWTEST_F(GestureEventHubTestNg, InitDragStartRequestState_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with TOUCH event
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.frameNode = frameNode;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call InitDragStartRequestState
     * @tc.expected: SetMouseDragMonitorState is NOT called
     */
    gestureEventHub->InitDragStartRequestState(ctx);

    /**
     * @tc.expected: Mouse drag monitor state remains unchanged
     */
    EXPECT_EQ(ctx.info.GetInputEventType(), InputEventType::TOUCH_PAD);
}

/**
 * @tc.name: BuildDragStartRequest_001
 * @tc.desc: Test BuildDragStartRequest - success path
 * @tc.type: FUNC
 * @tc.require: Issue the function dragDropManager exists
 */
HWTEST_F(GestureEventHubTestNg, BuildDragStartRequest_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.frameNode = frameNode;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call BuildDragStartRequest
     * @tc.expected: Returns true, event and dragDropInfo are initialized
     */
    bool result = gestureEventHub->BuildDragStartRequest(ctx);

    /**
     * @tc.expected: result is true, dragDropManager exists and ResetBundleInfo called
     */
    EXPECT_TRUE(result);
    EXPECT_NE(ctx.event, nullptr);
}

/**
 * @tc.name: DispatchDragStartByRequestState_001
 * @tc.desc: Test DispatchDragStartByRequestState - PENDING status path
 * @tc.type: FUNC
 * @tc.require: Issue the function drag start pended handling
 */
HWTEST_F(GestureEventHubTestNg, DispatchDragStartByRequestState_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.frameNode = frameNode;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Set DragStartRequestStatus to WAITING
     * @tc.expected: Delay callback will be set
     */
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::WAITING);

    /**
     * @tc.steps: step4. Call DispatchDragStartByRequestState
     * @tc.expected: drag start is pended, callbacks are set
     */
    gestureEventHub->DispatchDragStartByRequestState(ctx);
}

/**
 * @tc.name: HandleResolvedDragPreview_002
 * @tc.desc: Test HandleResolvedDragPreview - CustomBuilder path fallback
 * @tc.type: FUNC
 * @tc.require: Issue the function custom builder handling
 */
HWTEST_F(GestureEventHubTestNg, HandleResolvedDragPreview_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context without pixelMap or customNode
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.frameNode = frameNode;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step3. Call HandleResolvedDragPreview
     * @tc.expected: Returns false, falls through to PrepareFallbackDragPreview
     */
    bool result = gestureEventHub->HandleResolvedDragPreview(ctx);

    /**
     * @tc.expected: Returns false when no pixelMap or customNode available
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PrepareFallbackDragPreview_001
 * @tc.desc: Test PrepareFallbackDragPreview - TextDraggable path
 * @tc.type: FUNC
 * @tc.require: Issue the function text draggable handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareFallbackDragPreview_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with TOUCH event and textDraggable
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.dragDropInfo.pixelMap = nullptr;
    gestureEventHub->textDraggable_ = true;
    gestureEventHub->pixelMap_ = AceType::MakeRefPtr<MockPixelMap>();

    /**
     * @tc.steps: step3. Call PrepareFallbackDragPreview
     * @tc.expected: Uses existing pixelMap_ when textDraggable is true
     */
    gestureEventHub->PrepareFallbackDragPreview(ctx);

    /**
     * @tc.expected: pixelMap is set from pixelMap_
     */
    EXPECT_NE(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: PrepareFallbackDragPreview_002
 * @tc.desc: Test PrepareFallbackDragPreview - GenerateMousePixelMap path
 * @tc.type: FUNC
 * @tc.require: Issue the function mouse pixelMap generation
 */
HWTEST_F(GestureEventHubTestNg, PrepareFallbackDragPreview_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with TOUCH event but no pixelMap_
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.dragDropInfo.pixelMap = nullptr;
    gestureEventHub->textDraggable_ = false;
    gestureEventHub->pixelMap_ = nullptr;

    /**
     * @tc.steps: step3. Call PrepareFallbackDragPreview
     * @tc.expected: Calls GenerateMousePixelMap
     */
    gestureEventHub->PrepareFallbackDragPreview(ctx);

    /**
     * @tc.expected: pixelMap is set from pixelMap_
     */
    EXPECT_EQ(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: PrepareFallbackDragPreview_003
 * @tc.desc: Test PrepareFallbackDragPreview - MOUSE_BUTTON final fallback path
 * @tc.type: FUNC
 * @tc.require: Issue the function default mouse drag image handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareFallbackDragPreview_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with MOUSE_BUTTON event
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.dragDropInfo.pixelMap = nullptr;

    /**
     * @tc.steps: step3. Call PrepareFallbackDragPreview
     * @tc.expected: Uses CreatePixelMapFromString with DEFAULT_MOUSE_DRAG_IMAGE
     */
    gestureEventHub->PrepareFallbackDragPreview(ctx);
    EXPECT_EQ(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: PrepareFallbackDragPreview_004
 * @tc.desc: Test PrepareFallbackDragPreview - MOUSE_BUTTON final fallback path
 * @tc.type: FUNC
 * @tc.require: Issue the function default mouse drag image handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareFallbackDragPreview_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with MOUSE_BUTTON event
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.dragDropInfo.pixelMap = nullptr;
    gestureEventHub->textDraggable_ = true;
    gestureEventHub->pixelMap_ = AceType::MakeRefPtr<MockPixelMap>();
    gestureEventHub->SetTextDraggable(true);

    /**
     * @tc.steps: step3. Call PrepareFallbackDragPreview
     * @tc.expected: Uses CreatePixelMapFromString with DEFAULT_MOUSE_DRAG_IMAGE
     */
    gestureEventHub->PrepareFallbackDragPreview(ctx);
    EXPECT_NE(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: CheckDragStartResult_001
 * @tc.desc: Test CheckDragStartResult - Success path (not FAIL/CANCEL)
 * @tc.type: FUNC
 * @tc.require: Issue the function drag result success handling
 */
HWTEST_F(GestureEventHubTestNg, CheckDragStartResult_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with successful drag event
     */
    DragStartContext ctx;
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ctx.event->SetResult(DragRet::DRAG_SUCCESS);

    /**
     * @tc.steps: step3. Call CheckDragStartResult
     * @tc.expected: Returns true, drag can proceed
     */
    bool result = gestureEventHub->CheckDragStartResult(ctx);

    /**
     * @tc.expected: result is true
     */
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckDragStartResult_002
 * @tc.desc: Test CheckDragStartResult - Failure path (DRAG_FAIL)
 * @tc.type: FUNC
 * @tc.require: Issue the function drag result failure handling
 */
HWTEST_F(GestureEventHubTestNg, CheckDragStartResult_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with failed drag event
     */
    DragStartContext ctx;
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ctx.event->SetResult(DragRet::DRAG_FAIL);
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call CheckDragStartResult
     * @tc.expected: Returns false, FireCustomerOnDragEnd is called
     */
    bool result = gestureEventHub->CheckDragStartResult(ctx);

    /**
     * @tc.expected: result is false, failure handlers are called
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckDragStartResult_003
 * @tc.desc: Test CheckDragStartResult - Cancel path (DRAG_CANCEL) with MOUSE_BUTTON
 * @tc.type: FUNC
 * @tc.require: Issue the function drag result cancel mouse handling
 */
HWTEST_F(GestureEventHubTestNg, CheckDragStartResult_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with cancelled drag event and mouse input
     */
    DragStartContext ctx;
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ctx.event->SetResult(DragRet::DRAG_CANCEL);
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call CheckDragStartResult
     * @tc.expected: Returns false, SetMouseDragMonitorState(false) is called
     */
    bool result = gestureEventHub->CheckDragStartResult(ctx);

    /**
     * @tc.expected: result is false, mouse drag monitor is disabled
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PrepareDragStartPixelMap_001
 * @tc.desc: Test PrepareDragStartPixelMap - Success path where pixelMap exists
 * @tc.type: FUNC
 * @tc.require: Issue the function pixelMap exists handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareDragStartPixelMap_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with valid pixelMap
     */
    DragStartContext ctx;
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ctx.dragDropInfo.pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call PrepareDragStartPixelMap
     * @tc.expected: Returns true, SetPixelMap is called
     */
    bool result = gestureEventHub->PrepareDragStartPixelMap(ctx);

    /**
     * @tc.expected: result is true
     */
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PrepareDragStartPixelMap_002
 * @tc.desc: Test PrepareDragStartPixelMap - Failure path where pixelMap is null
 * @tc.type: FUNC
 * @tc.require: Issue the function null pixelMap handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareDragStartPixelMap_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with null pixelMap
     */
    DragStartContext ctx;
    ctx.event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ctx.dragDropInfo.pixelMap = nullptr;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. Call PrepareDragStartPixelMap
     * @tc.expected: Returns false, FireCustomerOnDragEnd is called
     */
    bool result = gestureEventHub->PrepareDragStartPixelMap(ctx);

    /**
     * @tc.expected: result is false
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleStartDragFailure_001
 * @tc.desc: Test HandleStartDragFailure - with subWindow path
 * @tc.type: FUNC
 * @tc.require: Issue the function drag failure with subwindow
 */
HWTEST_F(GestureEventHubTestNg, HandleStartDragFailure_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto pipeline1 = AceType::DynamicCast<PipelineContext>(context);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();

    /**
     * @tc.steps: step2. Setup context with subWindow
     */
    DragStartContext ctx;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ctx.subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline1 != mainPipeline));
    ctx.overlayManager = ctx.pipeline->GetOverlayManager();
    ctx.ret = -1;

    /**
     * @tc.steps: step3. Call HandleStartDragFailure
     * @tc.expected: HidePreviewNG and RemovePixelMap are called
     */
    gestureEventHub->HandleStartDragFailure(ctx);
}

/**
 * @tc.name: HandleStartDragFailure_002
 * @tc.desc: Test HandleStartDragFailure - without subWindow path
 * @tc.type: FUNC
 * @tc.require: Issue the function drag failure without subwindow
 */
HWTEST_F(GestureEventHubTestNg, HandleStartDragFailure_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context without subWindow
     */
    DragStartContext ctx;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ctx.subWindow = nullptr;
    ctx.overlayManager = ctx.pipeline->GetOverlayManager();
    ctx.ret = -1;

    /**
     * @tc.steps: step3. Call HandleStartDragFailure
     * @tc.expected: Only FireCustomerOnDragEnd is called, no HidePreviewNG
     */
    gestureEventHub->HandleStartDragFailure(ctx);
}

/**
 * @tc.name: UpdateDragStartAnimation_001
 * @tc.desc: Test UpdateDragStartAnimation - Animation success path with subWindow
 * @tc.type: FUNC
 * @tc.require: Issue the function drag start animation success
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragStartAnimation_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. call DoOnDragStartHandling.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);

    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto pipeline1 = AceType::DynamicCast<PipelineContext>(context);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    dragPreviewInfo.pixelMap = pixelMap;
    ctx.dragDropInfo = dragDropInfo;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.needChangeFwkForLeaveWindow = false;
    ctx.subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline1 != mainPipeline));;
    ctx.info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    ctx.isSwitchedToSubWindow = true;
    ctx.ret = 1;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_TRUE(guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info));
    EXPECT_TRUE(guestureEventHub->HandleResolvedDragPreview(ctx));
}

/**
 * @tc.name: UpdateDragWindowVisibility_001
 * @tc.desc: Test UpdateDragWindowVisibility - SceneBoard touch drag path
 * @tc.type: FUNC
 * @tc.require: Issue the function sceneboard touch drag handling
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);

    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    auto pipeline1 = AceType::DynamicCast<PipelineContext>(context);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    dragPreviewInfo.pixelMap = pixelMap;
    ctx.dragDropInfo = dragDropInfo;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.needChangeFwkForLeaveWindow = true;
    ctx.subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline1 != mainPipeline));;
    ctx.info.SetInputEventType(InputEventType::TOUCH_PAD);
    ctx.isSwitchedToSubWindow = true;
    ctx.ret = 1;
    guestureEventHub->DoOnDragStartHandling(ctx);
    EXPECT_TRUE(guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info));
    EXPECT_TRUE(guestureEventHub->HandleResolvedDragPreview(ctx));
}


/**
 * @tc.name: HandleOnDragStart_001
 * @tc.desc: Test HandleOnDragStart - Complete success flow
 * @tc.type: FUNC
 * @tc.require: Issue the function complete drag start flow
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragStart_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup eventHub host
     */
    auto event = gestureEventHub->eventHub_.Upgrade();
    ASSERT_NE(event, nullptr);
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    /**
     * @tc.steps: step3. Create valid GestureEvent
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_PAD;

    /**
     * @tc.steps: step4. Call HandleOnDragStart
     * @tc.expected: Full drag start flow is executed
     */
    gestureEventHub->HandleOnDragStart(info);
}

/**
 * @tc.name: HandleOnDragStart_002
 * @tc.desc: Test HandleOnDragStart - Early failure path
 * @tc.type: FUNC
 * @tc.require: Issue the function drag start validation failure
 */
HWTEST_F(GestureEventHubTestNg, HandleOnDragStart_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub without valid host
     */
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(WeakPtr<EventHub>());
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Create GestureEvent
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_PAD;

    /**
     * @tc.steps: step3. Call HandleOnDragStart
     * @tc.expected: Returns early due to InitDragStartTargets failure
     */
    gestureEventHub->HandleOnDragStart(info);
}

/**
 * @tc.name: CreateAsyncDragEndCallback_001
 * @tc.desc: Test CreateAsyncDragEndCallback - WAITING status path
 * @tc.type: FUNC
 * @tc.require: Issue the function async drag end waiting handling
 */
HWTEST_F(GestureEventHubTestNg, CreateAsyncDragEndCallback_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Create callback with WAITING status
     */
    auto callback = gestureEventHub->CreateAsyncDragEndCallback(frameNode);

    /**
     * @tc.steps: step3. Invoke callback with WAITING status
     * @tc.expected: FireCustomerOnDragEnd is called
     */
    callback(DragStartRequestStatus::WAITING);
}

/**
 * @tc.name: CreateAsyncDragEndCallback_002
 * @tc.desc: Test CreateAsyncDragEndCallback - Non-WAITING status path
 * @tc.type: FUNC
 * @tc.require: Issue the function async drag end non-waiting handling
 */
HWTEST_F(GestureEventHubTestNg, CreateAsyncDragEndCallback_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = gestureEventHub->CreateAsyncDragEndCallback(frameNode);

    /**
     * @tc.steps: step3. Invoke callback with READY status
     * @tc.expected: Callback returns early, nothing happens
     */
    callback(DragStartRequestStatus::READY);
}

/**
 * @tc.name: CreateDelayedDragStartCallback_001
 * @tc.desc: Test CreateDelayedDragStartCallback - MOUSE_BUTTON path
 * @tc.type: FUNC
 * @tc.require: Issue the function delayed drag start mouse handling
 */
HWTEST_F(GestureEventHubTestNg, CreateDelayedDragStartCallback_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with MOUSE_BUTTON
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;

    /**
     * @tc.steps: step3. Create and invoke delayed callback
     * @tc.expected: SetMouseDragMonitorState(true) is called before DoOnDragStartHandling
     */
    auto callback = gestureEventHub->CreateDelayedDragStartCallback(ctx);
    callback();
}

/**
 * @tc.name: CreateDelayedDragStartCallback_002
 * @tc.desc: Test CreateDelayedDragStartCallback - TOUCH path
 * @tc.type: FUNC
 * @tc.require: Issue the function delayed drag start touch handling
 */
HWTEST_F(GestureEventHubTestNg, CreateDelayedDragStartCallback_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with TOUCH
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_PAD;

    /**
     * @tc.steps: step3. Create and invoke delayed callback
     * @tc.expected: SetMouseDragMonitorState is NOT called
     */
    auto callback = gestureEventHub->CreateDelayedDragStartCallback(ctx);
    callback();
}

/**
 * @tc.name: ShowMouseDragWindow_001
 * @tc.desc: Test ShowMouseDragWindow - isSwitchedToSubWindow is true path, skip inner block
 * @tc.type: FUNC
 * @tc.require: Issue the function mouse drag window showing with subwindow switched
 */
HWTEST_F(GestureEventHubTestNg, ShowMouseDragWindow_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with isSwitchedToSubWindow = true
     * @tc.expected: The inner block of !ctx.isSwitchedToSubWindow will be skipped
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.isSwitchedToSubWindow = true;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(ctx.pipeline, nullptr);
    ctx.dragDropManager = ctx.pipeline->GetDragDropManager();
    ASSERT_NE(ctx.dragDropManager, nullptr);

    /**
     * @tc.steps: step3. Call ShowMouseDragWindow
     * @tc.expected: The inner block is skipped, only SetIsDragWindowShow(true) is called
     */
    gestureEventHub->ShowMouseDragWindow(ctx);

    /**
     * @tc.expected: dragDropManager's IsDragWindowShow is set to true
     */
    // Verified through the call that SetIsDragWindowShow(true) is executed
    EXPECT_TRUE(ctx.dragDropManager->IsDragWindowShow());
}

/**
 * @tc.name: UpdateDragWindowVisibility_004
 * @tc.desc: Test UpdateDragWindowVisibility - enter needChangeFwkForLeaveWindow branch
 * @tc.type: FUNC
 * @tc.require: Issue the function leave window transfer handling
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with TOUCH event and needChangeFwkForLeaveWindow = true
     * @tc.expected: Enter the branch: ctx.info.GetInputEventType() != MOUSE_BUTTON && ctx.needChangeFwkForLeaveWindow
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::TOUCH_SCREEN;  // Not MOUSE_BUTTON
    ctx.needChangeFwkForLeaveWindow = true;  // Trigger leave window branch
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(ctx.pipeline, nullptr);
    ctx.dragDropManager = ctx.pipeline->GetDragDropManager();
    gestureEventHub->DoOnDragStartHandling(ctx);
    ASSERT_NE(ctx.dragDropManager, nullptr);
}

/**
 * @tc.name: ShowSceneBoardTouchDragWindow_001
 * @tc.desc: Test ShowSceneBoardTouchDragWindow - isSceneBoardTouchDrag is false path, early return
 * @tc.type: FUNC
 * @tc.require: Issue the function sceneboard touch drag window early return handling
 */
HWTEST_F(GestureEventHubTestNg, ShowSceneBoardTouchDragWindow_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with isSceneBoardTouchDrag = false
     * @tc.expected: Enter the !ctx.preparedInfo.isSceneBoardTouchDrag branch and return early
     */
    DragStartContext ctx;
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(ctx.pipeline, nullptr);
    ctx.dragDropManager = ctx.pipeline->GetDragDropManager();
    gestureEventHub->ShowSceneBoardTouchDragWindow(ctx);
    ASSERT_NE(ctx.dragDropManager, nullptr);
}

/**
 * @tc.name: ShowSceneBoardTouchDragWindow_002
 * @tc.desc: Test ShowSceneBoardTouchDragWindow - isSceneBoardTouchDrag is false path, early return
 * @tc.type: FUNC
 * @tc.require: Issue the function sceneboard touch drag window early return handling
 */
HWTEST_F(GestureEventHubTestNg, ShowSceneBoardTouchDragWindow_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with isSceneBoardTouchDrag = false
     * @tc.expected: Enter the !ctx.preparedInfo.isSceneBoardTouchDrag branch and return early
     */
    DragStartContext ctx;
    ctx.preparedInfo.isSceneBoardTouchDrag = true;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(ctx.pipeline, nullptr);
    ctx.dragDropManager = ctx.pipeline->GetDragDropManager();
    gestureEventHub->ShowSceneBoardTouchDragWindow(ctx);
    ASSERT_NE(ctx.dragDropManager, nullptr);
}

/**
 * @tc.name: UpdateDragPreviewScale_001
 * @tc.desc: Test UpdateDragPreviewScale - isSceneBoardTouchDrag is false path, early return
 * @tc.type: FUNC
 * @tc.require: Issue the function sceneboard touch drag window early return handling
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragPreviewScale_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with isSceneBoardTouchDrag = false
     * @tc.expected: Enter the !ctx.preparedInfo.isSceneBoardTouchDrag branch and return early
     */
    DragStartContext ctx;
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(ctx.pipeline, nullptr);
    ctx.dragDropManager = ctx.pipeline->GetDragDropManager();
    ctx.preparedInfo.isMenuShow = false;
    gestureEventHub->UpdateDragPreviewScale(ctx);
    ASSERT_NE(ctx.dragDropManager, nullptr);
}

/**
 * @tc.name: PrepareFallbackDragPreview_005
 * @tc.desc: Test PrepareFallbackDragPreview - MOUSE_BUTTON final fallback path
 * @tc.type: FUNC
 * @tc.require: Issue the function default mouse drag image handling
 */
HWTEST_F(GestureEventHubTestNg, PrepareFallbackDragPreview_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode and GestureEventHub
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. Setup context with MOUSE_BUTTON event
     */
    DragStartContext ctx;
    ctx.info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    ctx.dragDropInfo.pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    /**
     * @tc.steps: step3. Call PrepareFallbackDragPreview
     * @tc.expected: Uses CreatePixelMapFromString with DEFAULT_MOUSE_DRAG_IMAGE
     */
    gestureEventHub->PrepareFallbackDragPreview(ctx);
    EXPECT_EQ(gestureEventHub->pixelMap_, nullptr);
}

/**
 * @tc.name: UpdateDragWindowVisibility_002
 * @tc.desc: Test UpdateDragWindowVisibility - UpdateDragWindowVisibility branch test
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. Setup context with all required fields initialized.
     * @tc.expected: All context fields are properly initialized to avoid null pointer access.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    // Initialize required fields to avoid null pointer dereference
    ctx.dragDropManager = pipeline->GetDragDropManager();
    ctx.overlayManager = pipeline->GetOverlayManager();
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.isSwitchedToSubWindow = false;
    ctx.info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    ctx.needChangeFwkForLeaveWindow = true;
    std::cout << "hushijie inputeventtype = " << static_cast<int>(ctx.info.GetInputEventType()) << std::endl;
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    ctx.needChangeFwkForLeaveWindow = false;
    ctx.isSwitchedToSubWindow = true;
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);
}

/**
 * @tc.name: UpdateDragWindowVisibility_003
 * @tc.desc: Test UpdateDragWindowVisibility - UpdateDragWindowVisibility branch test
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. Setup context with all required fields initialized.
     * @tc.expected: All context fields are properly initialized to avoid null pointer access.
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    // Initialize required fields to avoid null pointer dereference
    ctx.dragDropManager = pipeline->GetDragDropManager();
    ctx.overlayManager = pipeline->GetOverlayManager();
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.isSwitchedToSubWindow = false;
    ctx.info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    ctx.needChangeFwkForLeaveWindow = true;

    /**
     * @tc.steps: step4. call UpdateDragWindowVisibility.
     * @tc.expected: Function executes without crashing.
     */
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);

    ctx.isSwitchedToSubWindow = true;
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    EXPECT_FALSE(guestureEventHub->HandleResolvedDragPreview(ctx));

    ctx.subWindow = SubwindowManager::GetInstance()->ShowPreviewNG(true);
    guestureEventHub->HandleStartDragFailure(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);

    ctx.needChangeFwkForLeaveWindow = false;
    RefPtr<PipelineBase> context = NG::MockPipelineContext::pipeline_;
    guestureEventHub->PrepareDragStartSubWindowPreview(ctx, context);
    guestureEventHub->dragEventActuator_ = nullptr;
    guestureEventHub->PrepareDragStartData(ctx);
    EXPECT_FALSE(guestureEventHub->HandleResolvedDragPreview(ctx));
}

/**
 * @tc.name: UpdateDragWindowVisibility_005
 * @tc.desc: Test UpdateDragWindowVisibility - disableArkuiAnimation branch test
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. Setup context with disableArkuiAnimation = true.
     * @tc.expected: TransferTouchDragWindowToFramework is called.
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    ctx.dragDropManager = pipeline->GetDragDropManager();
    ctx.overlayManager = pipeline->GetOverlayManager();
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.preparedInfo.disableArkuiAnimation = true;
    ctx.isSwitchedToSubWindow = false;
    ctx.info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    ctx.needChangeFwkForLeaveWindow = false;

    /**
     * @tc.steps: step4. call UpdateDragWindowVisibility with disableArkuiAnimation = true.
     * @tc.expected: Function executes without crashing and transfers to framework.
     */
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);
}

/**
 * @tc.name: UpdateDragWindowVisibility_006
 * @tc.desc: Test UpdateDragWindowVisibility - disableArkuiAnimation with MOUSE_BUTTON
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, UpdateDragWindowVisibility_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->InitDragDropEvent();

    /**
     * @tc.steps: step2. updates event and pipeline attributes.
     */
    auto event = guestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);

    /**
     * @tc.steps: step3. Setup context with disableArkuiAnimation = true and MOUSE_BUTTON input.
     * @tc.expected: TransferTouchDragWindowToFramework is called regardless of device type.
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event1 = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    DragDropInfo dragPreviewInfo;
    DragStartContext ctx;
    ctx.info = info;
    ctx.frameNode = frameNode;
    ctx.dragDropInfo = dragDropInfo;
    ctx.event = event1;
    ctx.dragPreviewInfo = dragPreviewInfo;
    ctx.pipeline = pipeline;
    ctx.dragDropManager = pipeline->GetDragDropManager();
    ctx.overlayManager = pipeline->GetOverlayManager();
    ctx.preparedInfo.isSceneBoardTouchDrag = false;
    ctx.preparedInfo.disableArkuiAnimation = true;
    ctx.isSwitchedToSubWindow = false;
    ctx.info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    ctx.needChangeFwkForLeaveWindow = false;

    /**
     * @tc.steps: step4. call UpdateDragWindowVisibility with disableArkuiAnimation = true.
     * @tc.expected: Function executes without crashing and transfers to framework.
     */
    guestureEventHub->UpdateDragWindowVisibility(ctx);
    EXPECT_EQ(ctx.dragDropInfo.pixelMap, nullptr);
}
} // namespace OHOS::Ace::NG
