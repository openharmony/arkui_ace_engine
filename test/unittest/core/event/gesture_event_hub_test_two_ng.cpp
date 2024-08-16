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
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/event/gesture_event_hub_test_ng.h"
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/core/common/mock_container.h"

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
    ViewAbstract::SetWidth(frameNode.GetRawPtr(), CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(frameNode.GetRawPtr(), CalcLength(GRID_HEIGHT));
    std::list<RefPtr<FrameNode>> childNodes;

    for (size_t i = 0; i < childCount; ++i) {
        auto chidNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ITEM_ETS_TAG, chidNodeId,
            [itemStyle = gridItemStyle]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });
        ViewAbstract::SetWidth(childNode.GetRawPtr(), CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(childNode.GetRawPtr(), CalcLength(ITEM_HEIGHT));
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
    pattern->gridLayoutInfo_.endIndex_ = DEFAULT_CHILD_COUNT;

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
    ASSERT_EQ(guestureEventHub->IsDragForbidden(), true);
    guestureEventHub->SetDragForbiddenForcely(false);
    ASSERT_EQ(guestureEventHub->IsDragForbidden(), false);
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
    EXPECT_FALSE(dragDropManager->gatherPixelMaps_.empty());
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
    gestureEventHub->GetPixelMapOffset(info, size, -1.0f, true);
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
    ASSERT_EQ(guestureEventHub->GetMonopolizeEvents(), true);
    guestureEventHub->SetMonopolizeEvents(false);
    ASSERT_EQ(guestureEventHub->GetMonopolizeEvents(), false);
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
    ASSERT_EQ(funcRet, NG::HitTestMode::HTMTRANSPARENT);
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
    ASSERT_NE(guestureEventHub->GetOnGestureRecognizerJudgeBegin(), nullptr);
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

    std::string udKey;
    auto ret = gestureEventHub->SetDragData(unifiedData, udKey);
    ASSERT_NE(ret, 0);
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
    EXPECT_CALL(*subwindow, ShowPreviewNG()).WillRepeatedly(testing::Return(true));
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
    webFrameNode->SetDragPreviewOptions(option);
    gestureHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
     /**
     * @tc.steps: step5. call OnDragStart
     */
    gestureHub->OnDragStart(info, pipline, webFrameNode, dragDropInfo, event);
    ASSERT_NE(gestureHub->pixelMap_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    ASSERT_NE(gestureHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);
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
    EXPECT_CALL(*subwindow, ShowPreviewNG()).WillRepeatedly(testing::Return(true));
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
    buttonFrameNode->SetDragPreviewOptions(option);
    gestureHub->dragEventActuator_->preScaledPixelMap_ = pixelMap;
     /**
     * @tc.steps: step5. call OnDragStart
     */
    gestureHub->OnDragStart(info, pipline, buttonFrameNode, dragDropInfo, event);
    ASSERT_NE(gestureHub->pixelMap_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    ASSERT_NE(gestureHub->GetPreScaledPixelMapIfExist(1.0f, pixelMap), nullptr);
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    MockContainer::TearDown();
}
} // namespace OHOS::Ace::NG
