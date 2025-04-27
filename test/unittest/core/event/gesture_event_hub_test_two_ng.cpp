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

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr size_t DEFAULT_CHILD_COUNT = 4;
constexpr float GRID_WIDTH = 480.0f;
constexpr float GRID_HEIGHT = 800.0f;
constexpr float ITEM_WIDTH = 120.0f;
constexpr float ITEM_HEIGHT = 200.0f;

RefPtr<FrameNode> CreateGridNodeWithChild(size_t childCount, const GridItemStyle& gridItemStyle)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() {return AceType::MakeRefPtr<GridPattern>(); });
    ViewAbstract::SetWidth(Referenced::RawPtr(frameNode), CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(Referenced::RawPtr(frameNode), CalcLength(GRID_HEIGHT));
    std::list<RefPtr<FrameNode>> childNodes;

    for (size_t i = 0; i < childCount; ++i) {
        auto chidNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ITEM_ETS_TAG, chidNodeId,
            [itemStyle = gridItemStyle]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });
        ViewAbstract::SetWidth(Referenced::RawPtr(childNode), CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(Referenced::RawPtr(childNode), CalcLength(ITEM_HEIGHT));
        childNode->MountToParent(frameNode);
        childNodes.emplace_back(childNode);
    }
    return frameNode;
}

RefPtr<FrameNode> ProcessDragItemGroupScene()
{
    auto gridNode = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT, GridItemStyle::NONE);
    CHECK_NULL_RETURN(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, nullptr);

    for (const auto& child : gridNode->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (!childNode) {
            continue;
        }
        auto gridItemPattern = childNode->GetPattern<GridItemPattern>();
        if (!gridItemPattern) {
            continue;
        }
        gridItemPattern->SetSelected(true);
    }
    auto gridItem = AceType::DynamicCast<FrameNode>(gridNode->GetChildByIndex(0));
    CHECK_NULL_RETURN(gridItem, nullptr);
    auto pattern = gridNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->info_.endIndex_ = DEFAULT_CHILD_COUNT;

    gestureEventHub->InitDragDropEvent();
    auto actuator = gestureEventHub->GetDragEventActuator();
    CHECK_NULL_RETURN(actuator, nullptr);
    actuator->isSelectedItemNode_ = true;
    actuator->FindItemParentNode(gridItem);
    return gridNode;
}
}

/**
 * @tc.name: DragForbidden001
 * @tc.desc: Test DragForbidden
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DragForbidden001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->SetDragForbiddenForcely(true);
    EXPECT_EQ(guestureEventHub->IsDragForbidden(), true);
    guestureEventHub->SetDragForbiddenForcely(false);
    EXPECT_EQ(guestureEventHub->IsDragForbidden(), false);
}

/**
 * @tc.name: RemoveGesturesByTag002
 * @tc.desc: Test RemoveGesturesByTag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, RemoveGesturesByTag002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    longPressGestureOne->SetTag(CHECK_TAG_1);
    gestureEventHub->AttachGesture(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto longPressGestureThree = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestures.emplace_back(longPressGestureThree);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureEventHub->AttachGesture(group);

    gestureEventHub->RemoveGesturesByTag(CHECK_TAG_2);
    EXPECT_EQ(gestureEventHub->modifierGestures_.size(), 2);
}

/**
 * @tc.name: ClearJSFrameNodeOnTouch001
 * @tc.desc: Test ClearJSFrameNodeOnTouch
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, ClearJSFrameNodeOnTouch001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->ClearJSFrameNodeOnTouch();
    EXPECT_FALSE(guestureEventHub->touchEventActuator_);
}

/**
 * @tc.name: SetDragGatherPixelMaps003
 * @tc.desc: Test SetDragGatherPixelMaps when input type is not mouse button.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragGatherPixelMaps003, TestSize.Level1)
{
    auto gridNode = ProcessDragItemGroupScene();
    ASSERT_NE(gridNode, nullptr);
    auto gestureEventHub = gridNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto dragDropManager = context->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    GatherNodeChildInfo gatherNodeChildInfo;
    gatherNodeChildInfo.imageNode = imageNode;
    GatherNodeChildInfo gatherNodeChildInfo1;
    gatherNodeChildInfo1.imageNode = imageNode;
    std::vector<GatherNodeChildInfo> gatherNodeChildInfos;
    gatherNodeChildInfos.emplace_back(gatherNodeChildInfo);
    gatherNodeChildInfos.emplace_back(gatherNodeChildInfo1);
    ASSERT_NE(gestureEventHub->GetFrameNode(), nullptr);
    overlayManager->MountGatherNodeToRootNode(gestureEventHub->GetFrameNode(), gatherNodeChildInfos);

    GestureEvent info;
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gestureEventHub->SetDragGatherPixelMaps(info);
    EXPECT_TRUE(dragDropManager->gatherPixelMaps_.empty());
}

/**
 * @tc.name: GetUnifiedData003
 * @tc.desc: Test GetUnifiedData function.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GetUnifiedData003, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto defaultOnDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        dragDropInfo.extraInfo = "default extraInfo";
        return dragDropInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());

    DragDropInfo dragDropInfo;
    dragDropInfo.extraInfo.append("name");
    gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "name");

    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    dragEvent->SetData(unifiedData);
    dragDropInfo.extraInfo = "user set extraInfo";
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());
    PanDirection panDirection;
    gestureEventHub->dragEventActuator_ = AceType::MakeRefPtr<DragEventActuator>(nullptr, panDirection, 0, 0.0f);
    gestureEventHub->dragEventActuator_->SetIsDefaultOnDragStartExecuted(false);
    gestureEventHub->GetUnifiedData("TextArea", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "user set extraInfo");
    DragDropInfo dragDropInfo1;
    gestureEventHub->GetUnifiedData("TextArea", dragDropInfo1, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo1.extraInfo, "");
    gestureEventHub->dragEventActuator_->SetIsDefaultOnDragStartExecuted(true);
    gestureEventHub->GetUnifiedData("TextArea", dragDropInfo1, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo1.extraInfo, "");
}

/**
 * @tc.name: GestureEventHubGetPixelMapOffset002
 * @tc.desc: Test GetPixelMapOffset
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapOffset002, TestSize.Level1)
{
    auto frameNode1 = FrameNode::CreateFrameNode("MyButton", 102, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode1->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNode1);
    ASSERT_NE(eventHub, nullptr);

    constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
    constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
    GestureEvent info = GestureEvent();
    auto size = SizeF(1, 1);
    gestureEventHub->frameNodeOffset_.SetX(1);
    gestureEventHub->frameNodeOffset_.SetY(1);
    PreparedInfoForDrag data;
    gestureEventHub->GetPixelMapOffset(info, size, data, -1.0f);
    auto frameNode2 = gestureEventHub->GetFrameNode();
    EXPECT_NE(frameNode2, nullptr);
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_FALSE(NearZero(size.Width()));
    EXPECT_FALSE(result.GetX() >= 0.0f);
    EXPECT_FALSE(result.GetX() + size.Width() <= 0.0f);
    EXPECT_FALSE(result.GetY() >= 0.0f);
    EXPECT_FALSE(result.GetY() + size.Height() <= 0.0f);
}

/**
 * @tc.name: GestureEventHubGetPixelMapOffset003
 * @tc.desc: Test GetPixelMapOffset
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubGetPixelMapOffset003, TestSize.Level1)
{
    auto frameNodeTest = FrameNode::CreateFrameNode("MyButton", 102, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNodeTest->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto eventHub = gestureEventHub->eventHub_.Upgrade();
    eventHub->AttachHost(frameNodeTest);
    ASSERT_NE(eventHub, nullptr);

    constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
    constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
    GestureEvent info = GestureEvent();
    auto size = SizeF(1, 1);
    gestureEventHub->frameNodeOffset_.SetX(1);
    gestureEventHub->frameNodeOffset_.SetY(1);
    PreparedInfoForDrag data;
    data.isNeedCreateTiled = true;
    gestureEventHub->GetPixelMapOffset(info, size, data, -1.0f);
    auto frameNode = gestureEventHub->GetFrameNode();
    EXPECT_NE(frameNode, nullptr);
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    EXPECT_FALSE(result.GetX() + size.Width() <= 0.0f);
    EXPECT_FALSE(result.GetY() + size.Height() <= 0.0f);
}

/**
 * @tc.name: MonopolizeEvents001
 * @tc.desc: Test MonopolizeEvents
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, MonopolizeEvents001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->SetMonopolizeEvents(true);
    EXPECT_EQ(guestureEventHub->GetMonopolizeEvents(), true);
    guestureEventHub->SetMonopolizeEvents(false);
    EXPECT_EQ(guestureEventHub->GetMonopolizeEvents(), false);
}

/**
 * @tc.name: OnTouchInterceptFunc001
 * @tc.desc: Test Set and Get OnTouchIntercept function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, OnTouchInterceptFunc001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto onTouchInterceptfunc = [](TouchEventInfo& info) -> NG::HitTestMode { return NG::HitTestMode::HTMTRANSPARENT; };
    guestureEventHub->SetOnTouchIntercept(std::move(onTouchInterceptfunc));
    auto onGetTouchInterceptfunc = guestureEventHub->GetOnTouchIntercept();
    ASSERT_NE(onGetTouchInterceptfunc, nullptr);
    OHOS::Ace::TouchEventInfo info("unknown");
    auto funcRet = onGetTouchInterceptfunc(info);
    EXPECT_EQ(funcRet, NG::HitTestMode::HTMTRANSPARENT);
}

/**
 * @tc.name: GestureRecognizerJudgeFunc001
 * @tc.desc: Test Set and Get GestureRecognizerJudgeFunc function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureRecognizerJudgeFunc001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto func = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                    const std::list<RefPtr<NGGestureRecognizer>>& others) { return GestureJudgeResult(); };

    guestureEventHub->SetOnGestureRecognizerJudgeBegin(std::move(func));
    EXPECT_NE(guestureEventHub->GetOnGestureRecognizerJudgeBegin(), nullptr);
}

/**
 * @tc.name: SetDragData001
 * @tc.desc: Test SetDragData function when user has not set the onDragStart callback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetDragData001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. set OnDragStart for eventHub
     *            case: user not set onDragStart callback function
     */
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto defaultOnDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& dragEvent, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
        dragEvent->SetData(unifiedData);
        dragDropInfo.extraInfo = "default extraInfo";
        return dragDropInfo;
    };
    eventHub->SetDefaultOnDragStart(std::move(defaultOnDragStart));
    EXPECT_TRUE(eventHub->GetDefaultOnDragStart());

    /**
     * @tc.steps: step3. Call GetUnifiedData function
     *            case: Do not set default onDragStart function
     * @tc.expected: unifiedData is not null, extraInfo is not empty.
     */
    DragDropInfo dragDropInfo;
    auto unifiedData = gestureEventHub->GetUnifiedData("", dragDropInfo, dragEvent);
    EXPECT_TRUE(dragEvent->GetData());
    EXPECT_EQ(dragDropInfo.extraInfo, "default extraInfo");

    auto newUnifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(newUnifiedData, nullptr);
    std::string udKey;
    auto ret = gestureEventHub->SetDragData(newUnifiedData, udKey);
    EXPECT_NE(ret, -1);
}
/**
 * @tc.name: SetMouseDragMonitorState
 * @tc.desc: Test SetMouseDragMonitorState function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetMouseDragMonitorState001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->SetMouseDragMonitorState(true);

    NG::ShouldBuiltInRecognizerParallelWithFunc shouldBuiltInRecognizerParallelWithFunc;
    guestureEventHub->SetShouldBuildinRecognizerParallelWithFunc(std::move(shouldBuiltInRecognizerParallelWithFunc));
    guestureEventHub->GetParallelInnerGestureToFunc();
}

/**
 * @tc.name: AccessibilityRecursionSearchRecognizer
 * @tc.desc: Test AccessibilityRecursionSearchRecognizer group function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, AccessibilityRecursionSearchRecognizer001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer1);
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 2);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer2);
    auto clickRecognizer3 = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 3);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer3);

    gestureEventHub->IsAccessibilityClickable();
    EXPECT_EQ(gestureEventHub->gestureHierarchy_.size(), 3);
    gestureEventHub->gestureHierarchy_.clear();
}

std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> InitFrameNodes(const std::string& tag)
{
    auto rootNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
    rootNode->GetOrCreateFocusHub();
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto childImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<ImagePattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1.0f, 2.0f));
    childImageNode->SetGeometryNode(geometryNode);
    columnNode->AddChild(childImageNode);
    return std::make_pair(rootNode, columnNode);
}
/**
 * @tc.name: OnDragStart002
 * @tc.desc: Test DragPreviewOption
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, OnDragStart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create webFrameNode and overlayManager
     */
    auto [webFrameNode, columnNode] = InitFrameNodes(V2::WEB_ETS_TAG);
    auto pipline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = pipline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    pipline->SetupRootElement();
    webFrameNode->GetOrCreateFocusHub();
    overlayManager->SetIsMenuShow(true);
     /**
     * @tc.steps: step2. create columnNode and image node
     */
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto gestureHub = webFrameNode->GetOrCreateGestureEventHub();
    gestureHub->InitDragDropEvent();
    overlayManager->MountPixelMapToRootNode(columnNode);
    overlayManager->isMenuShow_ = true;
    /**
     * @tc.steps: step3. mock pixelmap and subwindow
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(testing::Return(4.0f));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(testing::Return(5.0f));
    gestureHub->SetPixelMap(pixelMap);

    auto containerId = Container::CurrentId();
    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindow);
    MockContainer::SetUp();
    MockContainer::Current();
    /**
     * @tc.steps: step4. create OnDragStart params
     */
    GestureEvent info;
    auto dragDropManager = pipline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->SetIsDragWithContextMenu(true);
    dragDropManager->PushGatherPixelMap(pixelMap);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo = {customNode, pixelMap};
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    event->SetData(unifiedData);
    NG::DragPreviewOption option { true, false, true, true};
    webFrameNode->SetDragPreviewOptions(option);
    gestureHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
     /**
     * @tc.steps: step5. call OnDragStart
     */
    gestureHub->OnDragStart(info, pipline, webFrameNode, dragDropInfo, event);
    EXPECT_NE(gestureHub->pixelMap_, nullptr);
    EXPECT_NE(gestureHub->dragEventActuator_, nullptr);
    EXPECT_NE(gestureHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    MockContainer::TearDown();
}

/**
 * @tc.name: OnDragStart003
 * @tc.desc: Test DragPreviewOption
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, OnDragStart003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create webFrameNode and overlayManager
     */
    auto [buttonFrameNode, columnNode] = InitFrameNodes("myButton");
    auto pipline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = pipline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    pipline->SetupRootElement();
    buttonFrameNode->GetOrCreateFocusHub();
    overlayManager->SetIsMenuShow(true);
     /**
     * @tc.steps: step2. init overlayManager infos
     */
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto gestureHub = buttonFrameNode->GetOrCreateGestureEventHub();
    SystemProperties::dragDropFrameworkStatus_ = 3;
    gestureHub->InitDragDropEvent();
    overlayManager->MountPixelMapToRootNode(columnNode);
    overlayManager->isMenuShow_ = true;
    /**
     * @tc.steps: step3. mock pixelmap and subwindow
     */
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(testing::Return(256.0f));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(testing::Return(2.0f));
    gestureHub->SetPixelMap(pixelMap);
    auto containerId = Container::CurrentId();
    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindow);
    EXPECT_CALL(*subwindow, ShowPreviewNG(false)).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*subwindow, GetOverlayManager()).WillRepeatedly(testing::Return(overlayManager));
    MockContainer::SetUp();
    MockContainer::Current();
    /**
     * @tc.steps: step4. create OnDragStart params
     */
    GestureEvent info;
    auto dragDropManager = pipline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->SetIsDragWithContextMenu(true);
    dragDropManager->PushGatherPixelMap(pixelMap);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo = {customNode, pixelMap};
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    NG::DragPreviewOption option { true, false, true, true};
    option.badgeNumber = 4;
    buttonFrameNode->SetDragPreviewOptions(option);
    gestureHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;

    GestureEvent infoEvent = GestureEvent();
    gestureHub->dragEventActuator_->userCallback_->actionEnd_(infoEvent);
    gestureHub->dragEventActuator_->userCallback_->actionStart_(infoEvent);
    gestureHub->dragEventActuator_->userCallback_->actionCancel_();
    gestureHub->dragEventActuator_->userCallback_->actionUpdate_(infoEvent);
     /**
     * @tc.steps: step5. call OnDragStart
     */
    gestureHub->OnDragStart(info, pipline, buttonFrameNode, dragDropInfo, event);
    ASSERT_NE(gestureHub->pixelMap_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    EXPECT_NE(gestureHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    MockContainer::TearDown();
}

/**
 * @tc.name: OnDragStart004
 * @tc.desc: Test DragStart
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, OnDragStart004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create webFrameNode and overlayManager
     */
    auto [buttonFrameNode, columnNode] = InitFrameNodes("myButton");
    auto pipline = PipelineContext::GetMainPipelineContext();
    pipline->SetupRootElement();
    buttonFrameNode->GetOrCreateFocusHub();
    auto gestureHub = buttonFrameNode->GetOrCreateGestureEventHub();
    gestureHub->InitDragDropEvent();
    /**
     * @tc.steps: step4. create OnDragStart params
     */
    GestureEvent info;
    info.SetInputEventType(InputEventType::MOUSE_BUTTON);
    DragDropInfo dragDropInfo;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
     /**
     * @tc.steps: step5. call OnDragStart abnormal
     */
    event->SetResult(DragRet::DRAG_FAIL);
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    gestureHub->OnDragStart(info, pipline, buttonFrameNode, dragDropInfo, event);
    EXPECT_EQ(event->GetResult(), DragRet::DRAG_FAIL);
    EXPECT_EQ(info.GetInputEventType(), InputEventType::MOUSE_BUTTON);
}

RefPtr<FrameNode> CreateFrameNodeGroup(int32_t targetId, size_t childCount)
{
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, targetId, pagePattern);
    for (size_t i = 0; i < childCount; ++i) {
        ++targetId;
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, targetId, nullptr);
        childNode->MountToParent(pageNode);
    }
    return pageNode;
}

RefPtr<NG::NGGestureRecognizer> CreateRecognizerGroup(const RefPtr<NG::FrameNode>& parentNode)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    std::list<RefPtr<NGGestureRecognizer>> recognizers;
    for (const auto& childNode : parentNode->GetChildren()) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(childNode);
        if (childFrameNode) {
            auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
            clickRecognizer->AttachFrameNode(childFrameNode);
            recognizers.emplace_back(clickRecognizer);
        }
    }
    auto recognizerGroup = AceType::MakeRefPtr<NG::ParallelRecognizer>(std::move(recognizers));
    if (recognizerGroup) {
        recognizerGroup->AttachFrameNode(parentNode);
    }
    return recognizerGroup;
}

/**
 * @tc.name: AccessibilityRecursionSearchRecognizer
 * @tc.desc: Test AccessibilityRecursionSearchRecognizer group function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, AccessibilityRecursionSearchRecognizer002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    int32_t nodeId = 16;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);
    eventHub->AttachHost(parentNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);
    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer1);
    gestureEventHub->gestureHierarchy_.emplace_back(recognizerGroup);
    gestureEventHub->IsAccessibilityClickable();
    EXPECT_EQ(gestureEventHub->gestureHierarchy_.size(), 2);
    gestureEventHub->gestureHierarchy_.clear();
}

/**
 * @tc.name: SetMouseDragMonitorState002
 * @tc.desc: Test SetMouseDragMonitorState function
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetMouseDragMonitorState002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 102, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);

    auto mock = AceType::DynamicCast<MockInteractionInterface>(InteractionInterface::GetInstance());
    ASSERT_NE(mock, nullptr);
    EXPECT_CALL(*mock, SetMouseDragMonitorState(testing::_)).Times(1).WillOnce(Return(false));
    guestureEventHub->SetMouseDragMonitorState(false);
    EXPECT_CALL(*mock, SetMouseDragMonitorState(testing::_)).WillRepeatedly(Return(true));
    guestureEventHub->SetMouseDragMonitorState(true);
}

/**
 * @tc.name: FireCustomerOnDragEnd002
 * @tc.desc: Test FireCustomerOnDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, FireCustomerOnDragEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gestureEventHub.
     * @tc.expected: instance is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    auto context = PipelineContext::GetCurrentContext();

    gestureEventHub->FireCustomerOnDragEnd(context, nullptr);
    gestureEventHub->FireCustomerOnDragEnd(nullptr, eventHub);
    context->dragDropManager_ = nullptr;
    gestureEventHub->FireCustomerOnDragEnd(context, eventHub);
}

/**
 * @tc.name: OnDragStart005
 * @tc.desc: Test DragPreviewOption
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, OnDragStart005, TestSize.Level1)
{
    auto [webFrameNode, columnNode] = InitFrameNodes(V2::WEB_ETS_TAG);
    auto pipline = PipelineContext::GetMainPipelineContext();
    auto overlayManager = pipline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    pipline->SetupRootElement();
    webFrameNode->GetOrCreateFocusHub();
    overlayManager->SetIsMenuShow(true);
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto gestureHub = webFrameNode->GetOrCreateGestureEventHub();
    gestureHub->InitDragDropEvent();
    overlayManager->MountPixelMapToRootNode(columnNode);
    overlayManager->isMenuShow_ = true;
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    EXPECT_CALL(*pixelMap, GetWidth()).WillRepeatedly(testing::Return(4.0f));
    EXPECT_CALL(*pixelMap, GetHeight()).WillRepeatedly(testing::Return(5.0f));
    gestureHub->SetPixelMap(pixelMap);
    auto containerId = Container::CurrentId();
    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    SubwindowManager::GetInstance()->AddSubwindow(containerId, subwindow);
    SubwindowManager::GetInstance()->SetCurrentSubwindow(subwindow);
    EXPECT_CALL(*subwindow, ShowPreviewNG(false)).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*subwindow, GetOverlayManager()).WillRepeatedly(testing::Return(overlayManager));
    EXPECT_CALL(*subwindow, GetMenuPreviewCenter(_)).WillRepeatedly(testing::Return(true));
    MockContainer::SetUp();
    MockContainer::Current();
    GestureEvent info;
    auto dragDropManager = pipline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->SetIsDragWithContextMenu(true);
    dragDropManager->PushGatherPixelMap(pixelMap);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo = { customNode };
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    event->SetData(unifiedData);
    EXPECT_CALL(*unifiedData, GetSize()).WillRepeatedly(testing::Return(4));
    NG::DragPreviewOption option { true, false, true, true };
    webFrameNode->SetDragPreviewOptions(option);
    gestureHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
    gestureHub->OnDragStart(info, pipline, webFrameNode, dragDropInfo, event);
    ASSERT_NE(gestureHub->pixelMap_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    EXPECT_NE(gestureHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->SetCurrentSubwindow(nullptr);
    MockContainer::TearDown();
}

/**
 * @tc.name: DragItemGrayEffectTest001
 * @tc.desc: Test GetGrayedState And SetGrayedState
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DragItemGrayEffectTest001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto grayedState = dragDropManager->GetGrayedState();
    EXPECT_EQ(grayedState, false);

    dragDropManager->SetGrayedState(true);
    grayedState = dragDropManager->GetGrayedState();
    EXPECT_EQ(grayedState, true);

    dragDropManager->SetGrayedState(false);
    grayedState = dragDropManager->GetGrayedState();
    EXPECT_EQ(grayedState, false);
}

/**
 * @tc.name: DragItemGrayEffectTest002
 * @tc.desc: Test HandleDragThroughMouse And HandleDragEndAction
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DragItemGrayEffectTest002, TestSize.Level1)
{
    auto pipline = PipelineContext::GetMainPipelineContext();
    pipline->dragDropManager_->SetGrayedState(false);
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    frameNode->GetRenderContext()->UpdateOpacity(1.0f);
    auto grayedOpacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(grayedOpacity, 1.0f);

    NG::DragPreviewOption dragPreviewOptions;
    dragPreviewOptions.isDefaultDragItemGrayEffectEnabled = true;
    frameNode->SetDragPreviewOptions(dragPreviewOptions);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->HandleDragThroughMouse(frameNode);
    grayedOpacity = frameNode->GetPreGrayedOpacity();
    EXPECT_EQ(grayedOpacity, 1.0f);
    auto renderOpacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(renderOpacity, 0.4f);

    gestureEventHub->HandleDragEndAction(gestureEventHub->dragframeNodeInfo_);
    auto opacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(opacity, 1.0f);
}

/**
 * @tc.name: DragItemGrayEffectTest003
 * @tc.desc: Test HandleDragThroughTouch And HandleDragEndAction
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, DragItemGrayEffectTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    frameNode->GetRenderContext()->UpdateOpacity(1.0f);
    auto grayedOpacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(grayedOpacity, 1.0f);

    NG::DragPreviewOption dragPreviewOptions;
    dragPreviewOptions.isDefaultDragItemGrayEffectEnabled = true;
    frameNode->SetDragPreviewOptions(dragPreviewOptions);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->HandleDragThroughTouch(frameNode);
    grayedOpacity = frameNode->GetPreGrayedOpacity();
    EXPECT_EQ(grayedOpacity, 1.0f);
    auto renderOpacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(renderOpacity, 0.4f);

    gestureEventHub->HandleDragEndAction(gestureEventHub->dragframeNodeInfo_);
    auto opacity = frameNode->GetRenderContext()->GetOpacityValue();
    EXPECT_EQ(opacity, 1.0f);
}

/**
 * @tc.name: SetMouseDragGatherPixelMaps002
 * @tc.desc: Test SetMouseDragGatherPixelMaps
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, SetMouseDragGatherPixelMaps002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 101, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    auto eventHub = guestureEventHub->eventHub_.Upgrade();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ClearGatherPixelMap();
    auto mainPipeline = PipelineContext::GetMainPipelineContext();

    mainPipeline->overlayManager_ = nullptr;
    guestureEventHub->SetNotMouseDragGatherPixelMaps();
    pipeline->dragDropManager_ = nullptr;
    guestureEventHub->SetNotMouseDragGatherPixelMaps();
    pipeline = nullptr;
    guestureEventHub->SetNotMouseDragGatherPixelMaps();
}

/**
 * @tc.name: GestureEventHubTest034
 * @tc.desc: Test ProcessTouchTestHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest034, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    TouchRestrict touchRestrict;
    std::list<RefPtr<NGGestureRecognizer>> innerTargets;
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    std::vector<RefPtr<NGGestureRecognizer>> vc;
    vc.push_back(AceType::MakeRefPtr<ClickRecognizer>());
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(vc);
    std::vector<RefPtr<NGGestureRecognizer>> parallelVc;
    parallelVc.push_back(AceType::MakeRefPtr<ClickRecognizer>());
    auto parallelRecognizer = AceType::MakeRefPtr<ParallelRecognizer>(parallelVc);
    gestureEventHub->externalExclusiveRecognizer_.push_back(exclusiveRecognizer);
    gestureEventHub->externalParallelRecognizer_.push_back(parallelRecognizer);
    gestureEventHub->ProcessTouchTestHierarchy(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, nullptr, responseLinkResult);
    EXPECT_TRUE(finalResult.empty());
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Low
    innerTargets.emplace_back(clickRecognizer);
    gestureEventHub->gestureHierarchy_.emplace_back(nullptr);
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1);
    clickRecognizer2->SetPriorityMask(GestureMask::IgnoreInternal);           // current will assigned to this
    auto clickRecognizer3 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::High
    clickRecognizer3->SetPriority(GesturePriority::High);
    auto clickRecognizer4 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Parallel
    clickRecognizer4->SetPriority(GesturePriority::Parallel);
    auto clickRecognizer5 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Parallel
    clickRecognizer5->SetPriority(GesturePriority::Parallel);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer4);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer2);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer3);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer5);
    clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1);
    innerTargets.emplace_back(clickRecognizer);
    std::list<RefPtr<NGGestureRecognizer>> innerTargets3;
    innerTargets3.emplace_back(clickRecognizer);
    int32_t nodeId = 16;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);
    eventHub->AttachHost(parentNode);
    gestureEventHub->gestureHierarchy_.emplace_back(recognizerGroup);
    gestureEventHub->ProcessTouchTestHierarchy(
        COORDINATE_OFFSET, touchRestrict, innerTargets3, finalResult, TOUCH_ID, nullptr, responseLinkResult);
}
} // namespace OHOS::Ace::NG
