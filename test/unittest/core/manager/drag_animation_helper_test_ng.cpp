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

#include "test/unittest/core/manager/drag_animation_helper_test_ng.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr size_t DEFAULT_CHILD_COUNT = 4;
constexpr float GRID_WIDTH = 480.0f;
constexpr float GRID_HEIGHT = 800.0f;
constexpr float ITEM_WIDTH = 120.0f;
constexpr float ITEM_HEIGHT = 200.0f;
constexpr float PIXELMAP_DRAG_SCALE_MULTIPLE = 1.05f;
constexpr int32_t DEFAULT_BADGE_NUM = 2;
} // namespace

void DragAnimationHelperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void DragAnimationHelperTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void DragAnimationHelperTestNg::SetUp()
{
    ResetElmtId();
    auto [gridNode, gridItemNodes] = CreateGridNodeWithChild(DEFAULT_CHILD_COUNT);
    parentNode_ = gridNode;
    auto pattern = gridNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->info_.endIndex_ = DEFAULT_CHILD_COUNT;
    CHECK_NULL_VOID(parentNode_);
    childNodes_ = gridItemNodes;
}

void DragAnimationHelperTestNg::TearDown()
{
    parentNode_ = nullptr;
    childNodes_.clear();
}

std::pair<RefPtr<FrameNode>, std::list<RefPtr<FrameNode>>> DragAnimationHelperTestNg::CreateGridNodeWithChild(
    size_t childCount, const GridItemStyle& gridItemStyle)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId,
        []() {return AceType::MakeRefPtr<GridPattern>(); });
    ViewAbstract::SetWidth(Referenced::RawPtr(frameNode), CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(Referenced::RawPtr(frameNode), CalcLength(GRID_HEIGHT));
    std::list<RefPtr<FrameNode>> childNodes;

    for (size_t i = 0; i < childCount; ++i) {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        auto itemNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ITEM_ETS_TAG, itemNodeId,
            [itemStyle = gridItemStyle]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });
        if (!childNode) {
            continue;
        }
        ViewAbstract::SetWidth(Referenced::RawPtr(childNode), CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(Referenced::RawPtr(childNode), CalcLength(ITEM_HEIGHT));

        auto gridItemPattern = childNode->GetPattern<GridItemPattern>();
        if (gridItemPattern) {
            gridItemPattern->SetSelected(true);
        }

        auto dragPreviewOption = childNode->GetDragPreviewOption();
        dragPreviewOption.isMultiSelectionEnabled = true;
        childNode->SetDragPreviewOptions(dragPreviewOption);

        auto dragPreviewInfo = childNode->GetDragPreview();
        dragPreviewInfo.pixelMap = AceType::MakeRefPtr<MockPixelMap>();
        childNode->SetDragPreview(dragPreviewInfo);

        auto gestureHub = childNode->GetOrCreateGestureEventHub();
        if (!gestureHub) {
            continue;
        }
        auto eventHub = gestureHub->eventHub_.Upgrade();
        if (!eventHub) {
            continue;
        }
        auto func = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) { return DragDropInfo(); };
        eventHub->onDragStart_ = func;
        childNode->MountToParent(frameNode);
        childNodes.emplace_back(childNode);
    }
    return { frameNode, childNodes };
}

/**
 * @tc.name: PlayGatherAnimationBeforeLifting001
 * @tc.desc: test PlayGatherAnimationBeforeLifting func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PlayGatherAnimationBeforeLifting001, TestSize.Level1)
{
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto gestureHub = (*iter)->GetOrCreateGestureEventHub();
    auto actuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    actuator->FindItemParentNode(*(childNodes_.begin()));
    DragAnimationHelper::PlayGatherAnimationBeforeLifting(actuator);

    for (const auto& child : childNodes_) {
        ASSERT_TRUE(child != nullptr);
        auto gridItemPattern = child->GetPattern<GridItemPattern>();
        ASSERT_TRUE(gridItemPattern != nullptr);
        gridItemPattern->SetSelected(true);
    }
    actuator->isSelectedItemNode_ = true;
    auto gridPattern = parentNode_->GetPattern<GridPattern>();
    GatherNodeChildInfo gatherNodeInfo;
    auto imageNodeId = GetElmtId();
    auto gatherNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    auto gatherNode = FrameNode::GetOrCreateFrameNode("gatherNode", gatherNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    gatherNodeInfo.imageNode =  AceType::WeakClaim(AceType::RawPtr(imageNode));
    actuator->PushBackGatherNodeChild(gatherNodeInfo);
    actuator->SetGatherNode(gatherNode);
    ASSERT_TRUE(gridPattern != nullptr);
    gridPattern->info_.endIndex_ = DEFAULT_CHILD_COUNT;
    DragAnimationHelper::PlayGatherAnimationBeforeLifting(actuator);
    ASSERT_NE(actuator->GetGatherNode(), nullptr);
}

/**
 * @tc.name: CalcOffsetToTarget001
 * @tc.desc: test CalcOffsetToTarget func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcOffsetToTarget001, TestSize.Level1)
{
    CalcResult result;
    auto offset = DragAnimationHelper::CalcOffsetToTarget(OffsetF(), OffsetF(), result);
    EXPECT_TRUE(IsEqual(offset, OffsetF(0.0f, 0.0f)));

    result.maxDistance = 10.0f;
    result.minDistance =5.0f;
    result.maxTranslation =1.0f;
    offset = DragAnimationHelper::CalcOffsetToTarget(OffsetF(), OffsetF(), result);
    EXPECT_TRUE(IsEqual(offset, OffsetF(0.0f, 0.0f)));

    offset = DragAnimationHelper::CalcOffsetToTarget(OffsetF(), OffsetF(3.0f, 4.0f), result);
    EXPECT_EQ(result.maxTranslation, 1.0f);
}

/**
 * @tc.name: PlayNodeAnimationBeforeLifting001
 * @tc.desc: test PlayNodeAnimationBeforeLifting func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PlayNodeAnimationBeforeLifting001, TestSize.Level1)
{
    ASSERT_TRUE(parentNode_ != nullptr);
    DragPreviewOption option;
    option.defaultAnimationBeforeLifting = false;
    parentNode_->SetDragPreviewOptions(option);
    DragAnimationHelper::PlayNodeAnimationBeforeLifting(parentNode_);

    option.defaultAnimationBeforeLifting = true;
    parentNode_->SetDragPreviewOptions(option);
    DragAnimationHelper::PlayNodeAnimationBeforeLifting(parentNode_);
    auto vector = parentNode_->GetRenderContext()->GetTransformScale();
    ASSERT_TRUE(vector.has_value());
}

/**
 * @tc.name: PlayNodeAnimationBeforeLifting001
 * @tc.desc: test PlayNodeResetAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PlayNodeResetAnimation001, TestSize.Level1)
{
    ASSERT_TRUE(parentNode_ != nullptr);
    DragPreviewOption option;
    option.defaultAnimationBeforeLifting = false;
    parentNode_->SetDragPreviewOptions(option);
    auto gestureHub = parentNode_->GetOrCreateGestureEventHub();
    auto actuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    DragAnimationHelper::PlayNodeResetAnimation(actuator);

    option.defaultAnimationBeforeLifting = true;
    parentNode_->SetDragPreviewOptions(option);
    DragAnimationHelper::PlayNodeResetAnimation(actuator);
    auto type = parentNode_->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE);
    ASSERT_TRUE(type == VisibleType::VISIBLE);
}

/**
 * @tc.name: PlayGatherAnimation001
 * @tc.desc: test PlayGatherAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PlayGatherAnimation001, TestSize.Level1)
{
    ASSERT_TRUE(parentNode_ != nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfos;
    GatherNodeChildInfo gatherNodeInfo;
    auto imageNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    gatherNodeInfo.imageNode =  AceType::WeakClaim(AceType::RawPtr(imageNode));
    gatherNodeInfos.emplace_back(gatherNodeInfo);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_TRUE(pipelineContext != nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_TRUE(overlayManager != nullptr);
    overlayManager->MountGatherNodeToRootNode(parentNode_, gatherNodeInfos);
    DragAnimationHelper::PlayGatherAnimation(parentNode_, overlayManager);

    auto renderContext = imageNode->GetRenderContext();
    ASSERT_TRUE(renderContext != nullptr);
    auto borderRadius = renderContext->GetBorderRadius();
    ASSERT_TRUE(borderRadius.has_value());
    EXPECT_FALSE(borderRadius.value().multiValued);
}

/**
 * @tc.name: GetLiftingNodeScale001
 * @tc.desc: test GetLiftingNodeScale func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetLiftingNodeScale001, TestSize.Level1)
{
    auto scale = DragAnimationHelper::GetLiftingNodeScale(nullptr);
    EXPECT_EQ(scale, PIXELMAP_DRAG_SCALE_MULTIPLE);
    auto imageNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const float customScale = 2.0f;
    renderContext->UpdateTransformScale({ customScale, customScale });
    scale = DragAnimationHelper::GetLiftingNodeScale(renderContext);
    EXPECT_EQ(scale, customScale);
}

/**
 * @tc.name: ShowBadgeAnimation001
 * @tc.desc: test ShowBadgeAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowBadgeAnimation001, TestSize.Level1)
{
    auto textNodeId = GetElmtId();
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });

    DragAnimationHelper::ShowBadgeAnimation(textNode);
    auto renderContext = textNode->GetRenderContext();
    ASSERT_TRUE(renderContext != nullptr);
    auto transformScale = renderContext->GetTransformScale();
    EXPECT_TRUE(transformScale.has_value());
}

/**
 * @tc.name: CalcBadgeTextPosition001
 * @tc.desc: test CalcBadgeTextPosition func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextPosition001, TestSize.Level1)
{
    std::vector<GatherNodeChildInfo> gatherNodeInfos;
    GatherNodeChildInfo gatherNodeInfo;
    auto imageNodeId = GetElmtId();
    auto textNodeId = GetElmtId();
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_TRUE(frameNode != nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textNodeId,
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });

    gatherNodeInfo.imageNode =  AceType::WeakClaim(AceType::RawPtr(imageNode));
    gatherNodeInfos.emplace_back(gatherNodeInfo);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_TRUE(pipelineContext != nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_TRUE(overlayManager != nullptr);
    overlayManager->MountGatherNodeToRootNode(textNode, gatherNodeInfos);
    DragAnimationHelper::CalcBadgeTextPosition(menuPattern, overlayManager, imageNode, textNode);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty != nullptr);
    auto content = textLayoutProperty->GetContentValue();
    EXPECT_STREQ(StringUtils::Str16ToStr8(content).c_str(),
        std::to_string(overlayManager->GetGatherNodeChildrenInfo().size() + 1).c_str());
}

/**
 * @tc.name: CalcBadgeTextPosition002
 * @tc.desc: test CalcBadgeTextPosition func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextPosition002, TestSize.Level1)
{
    std::vector<GatherNodeChildInfo> gatherNodeInfos;
    GatherNodeChildInfo gatherNodeInfo;
    auto imageNodeId = GetElmtId();
    auto textNodeId = GetElmtId();
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textNodeId,
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(menuPattern, nullptr);

    gatherNodeInfo.imageNode =  AceType::WeakClaim(AceType::RawPtr(imageNode));
    gatherNodeInfos.emplace_back(gatherNodeInfo);
    frameNode->previewOption_.isNumber = true;
    frameNode->previewOption_.badgeNumber = 3;

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->MountGatherNodeToRootNode(textNode, gatherNodeInfos);
    DragAnimationHelper::CalcBadgeTextPosition(menuPattern, overlayManager, imageNode, textNode);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContentValue();

    EXPECT_STREQ(StringUtils::Str16ToStr8(content).c_str(),
        std::to_string(3).c_str());
}

/**
 * @tc.name: CreateImageNode
 * @tc.desc: test CreateImageNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CreateImageNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pixelMap.
     * @tc.expected: pixelMap is not null.
     */
    RefPtr<MockPixelMap> mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(mockPixelMap, nullptr);

    /**
     * @tc.steps: step2. create imageNode.
     * @tc.expected: imageNode is not null.
     */
    auto imageNode = DragAnimationHelper::CreateImageNode(mockPixelMap);
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step3. check imageNode attr
     */
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    auto opacity = imageContext->GetOpacity().value_or(0);
    EXPECT_EQ(opacity, 1.0f);
}

/**
 * @tc.name: CreateGatherImageNode
 * @tc.desc: test CreateGatherImageNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CreateGatherImageNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherChildNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    GatherNodeChildInfo gatherNodeChildInfo;
    auto gatherChildNode = DragAnimationHelper::CreateGatherImageNode(itemNode, gatherNodeChildInfo);
    ASSERT_NE(gatherChildNode, nullptr);
}

/**
 * @tc.name: CreateGatherNode
 * @tc.desc: test CreateGatherNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CreateGatherNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gatherNode = DragAnimationHelper::CreateGatherNode(itemNode, gatherNodeInfo);
    ASSERT_NE(gatherNode, nullptr);

    /**
     * @tc.steps: step2. check gatherNodeInfo size
     */
    auto gatherChildSize = gatherNodeInfo.size();
    EXPECT_EQ(gatherChildSize + 1, size);
}

/**
 * @tc.name: GetOrCreateGatherNode
 * @tc.desc: test GetOrCreateGatherNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetOrCreateGatherNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gestureHub = itemNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Get overlayManager
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->RemoveGatherNode();

    /**
     * @tc.steps: step2. check gatherNodeInfo size
     */
    auto actuator = AceType::MakeRefPtr<DragEventActuator>(
    AceType::WeakClaim(AceType::RawPtr(gestureHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(actuator, nullptr);
    actuator->itemParentNode_ = parentNode_;
    actuator->isSelectedItemNode_ = true;
    auto gatherNode = DragAnimationHelper::GetOrCreateGatherNode(overlayManager, actuator, gatherNodeInfo);
    ASSERT_NE(gatherNode, nullptr);

    auto gatherChildSize = gatherNodeInfo.size();
    EXPECT_EQ(gatherChildSize + 1, size);
}

/**
 * @tc.name: GetOrCreateGatherNode
 * @tc.desc: test GetOrCreateGatherNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetOrCreateGatherNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gatherNode = DragAnimationHelper::CreateGatherNode(itemNode, gatherNodeInfo);
    ASSERT_NE(gatherNode, nullptr);

    /**
     * @tc.steps: step2. Get overlayManager
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->RemoveGatherNode();

    /**
     * @tc.steps: step3. Call MountGatherNode
     */
    DragAnimationHelper::MountGatherNode(overlayManager, itemNode, gatherNode, gatherNodeInfo);
    EXPECT_NE(overlayManager->GetGatherNode(), nullptr);
    auto gatherChildSize = overlayManager->GetGatherNodeChildrenInfo().size();
    EXPECT_EQ(gatherChildSize + 1, size);

    /**
     * @tc.steps: step4. call GetOrCreateGatherNode
     */
    auto gestureHub = itemNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto actuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(actuator, nullptr);
    actuator->itemParentNode_ = parentNode_;
    actuator->isSelectedItemNode_ = true;
    auto newGatherNode = DragAnimationHelper::GetOrCreateGatherNode(overlayManager, actuator, gatherNodeInfo);
    ASSERT_EQ(gatherNode, newGatherNode);
}


/**
 * @tc.name: MountGatherNode
 * @tc.desc: test MountGatherNode func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountGatherNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gatherNode = DragAnimationHelper::CreateGatherNode(itemNode, gatherNodeInfo);
    ASSERT_NE(gatherNode, nullptr);

    /**
     * @tc.steps: step2. Get overlayManager
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step3. Call MountGatherNode
     */
    DragAnimationHelper::MountGatherNode(overlayManager, itemNode, gatherNode, gatherNodeInfo);
    EXPECT_NE(overlayManager->GetGatherNode(), nullptr);
    auto gatherChildSize = overlayManager->GetGatherNodeChildrenInfo().size();
    EXPECT_EQ(gatherChildSize + 1, size);
}

/**
 * @tc.name: InitGatherNodeAttr
 * @tc.desc: test InitGatherNodeAttr func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, InitGatherNodeAttr, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gatherNode.
     * @tc.expected: gatherNode is not null.
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gatherNode = DragAnimationHelper::CreateGatherNode(itemNode, gatherNodeInfo);
    ASSERT_NE(gatherNode, nullptr);

    /**
     * @tc.steps: step2. InitGatherNodeAttr
     */
    DragAnimationHelper::InitGatherNodeAttr(gatherNode, gatherNodeInfo);
    auto renderContext = gatherNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetPosition(), std::nullopt);
    EXPECT_EQ(renderContext->GetPosition()->GetX().Value(), 0);
    EXPECT_EQ(renderContext->GetPosition()->GetY().Value(), 0);
}

/**
 * @tc.name: HideDragNodeCopy
 * @tc.desc: test HideDragNodeCopy func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, HideDragNodeCopy, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragNodeCopy
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->dragNodeCopyWeak_ = frameNode;
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateOpacity(1.0f);
    ASSERT_NE(renderContext, nullptr);
    auto opacity = renderContext->GetOpacity().value_or(0);
    EXPECT_EQ(opacity, 1.0f);

    /**
     * @tc.steps: step2. Call HideDragNodeCopy
     */
    DragAnimationHelper::HideDragNodeCopy(overlayManager);
    opacity = renderContext->GetOpacity().value_or(0);
    EXPECT_EQ(opacity, 0.0f);
}

/**
 * @tc.name: DragStartAnimation
 * @tc.desc: Test DragStartAnimation func with Offset(10.0, 10.0). TranslateOptions value will be right after drag
 * animation.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, DragStartAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlayManager and dragDropManager.
     * @tc.expected: overlayManager and dragDropManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Create imageNode and dragPreviewInfo.
     * @tc.expected: dragPreviewInfo's imageNode is not nullptr.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto imageNode = DragAnimationHelper::CreateImageNode(refPixelMap);
    ASSERT_NE(imageNode, nullptr);
    DragDropManager::DragPreviewInfo dragPreviewInfo;
    dragPreviewInfo.imageNode = imageNode;
    ASSERT_NE(dragPreviewInfo.imageNode, nullptr);
    dragDropManager->SetDragPreviewInfo(dragPreviewInfo);

    /**
     * @tc.steps: step3. Call DragStartAnimation with Offset(10.0, 10.0).
     * @tc.expected: TranslateOptions x value is 10.0f.
     */
    auto newOffset = Offset(10.0, 10.0);
    auto gatherNodeCenter =
        NG::DragDropFuncWrapper::GetPaintRectCenter(dragDropManager->GetDragPreviewInfo().imageNode);
    Point point = { 0, 0 };
    DragAnimationHelper::DragStartAnimation(newOffset, overlayManager, gatherNodeCenter, point, containerId);
    auto renderContext = imageNode->GetRenderContext();
    TranslateOptions result = renderContext->GetTransformTranslate().value();
    TranslateOptions expectValue { 10.0f, 10.0f, 0.0f };
    EXPECT_EQ(result.x.CalcValue(), expectValue.x.CalcValue());
}

/**
 * @tc.name: CreateBadgeTextNodeTest001
 * @tc.desc: Test CreateBadgeTextNode function.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CreateBadgeTextNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
    ASSERT_NE(dragEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke CreateBadgeTextNode.
     */
    auto textNode = DragAnimationHelper::CreateBadgeTextNode(2);
    EXPECT_NE(textNode, nullptr);
}

/**
 * @tc.name: CreateTextNode001
 * @tc.desc: Test CreateTextNode
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CreateTextNode001, TestSize.Level1)
{
    PreparedInfoForDrag data;
    data.badgeNumber = DEFAULT_BADGE_NUM;
    EXPECT_EQ(data.textRowNode, nullptr);
    DragAnimationHelper::CreateTextNode(data);
    data.deviceType = SourceType::MOUSE;
    EXPECT_NE(data.textRowNode, nullptr);
}
} // namespace OHOS::Ace::NG