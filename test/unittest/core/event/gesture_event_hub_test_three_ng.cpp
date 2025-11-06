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

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "test/mock/core/render/mock_render_context.h"

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
    guestureEventHub->DoOnDragStartHandling(info, frameNode, dragDropInfo, event1, dragPreviewInfo, pipeline);
    EXPECT_EQ(dragDropInfo.pixelMap, 0);

    dragPreviewInfo.pixelMap = pixelMap;
    guestureEventHub->DoOnDragStartHandling(info, frameNode, dragDropInfo, event1, dragPreviewInfo, pipeline);
    EXPECT_TRUE(guestureEventHub->ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info));
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
    guestureEventHub->DoOnDragStartHandling(info, frameNode, dragDropInfo, event1, dragPreviewInfo, pipeline);
    EXPECT_EQ(dragDropInfo.pixelMap, 0);

    info.inputEventType_ = InputEventType::MOUSE_BUTTON;
    dragDropInfo.pixelMap = nullptr;
    guestureEventHub->pixelMap_ = nullptr;
    guestureEventHub->DoOnDragStartHandling(info, frameNode, dragDropInfo, event1, dragPreviewInfo, pipeline);
    EXPECT_EQ(dragDropInfo.pixelMap, 0);
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
} // namespace OHOS::Ace::NG