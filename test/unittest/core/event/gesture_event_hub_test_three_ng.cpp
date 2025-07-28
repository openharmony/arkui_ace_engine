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
     * @tc.steps: step3. call CalcFrameNodeOffsetAndSize.
     */
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, true);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), 0.0);
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
} // namespace OHOS::Ace::NG