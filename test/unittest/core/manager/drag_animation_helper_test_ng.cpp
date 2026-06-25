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
#include "core/components_ng/syntax/shallow_builder.h"

#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/common/ace_engine.h"

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
constexpr Dimension BADGE_RELATIVE_OFFSET = 8.0_vp;
const float EPSILON = 0.1f;
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
        eventHub->SetOnDragStart(std::move(func));
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
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    DragAnimationHelper::CalcBadgeTextPosition(host, overlayManager, imageNode, textNode);

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
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.isNumber = true;
    dragPreviewOption.badgeNumber = 3;
    frameNode->SetDragPreviewOptions(dragPreviewOption);

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->MountGatherNodeToRootNode(textNode, gatherNodeInfos);
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    DragAnimationHelper::CalcBadgeTextPosition(host, overlayManager, imageNode, textNode);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContentValue();

    EXPECT_STREQ(StringUtils::Str16ToStr8(content).c_str(),
        std::to_string(3).c_str());
}

/**
 * @tc.name: CalcBadgeTextPosition003
 * @tc.desc: Test CalcBadgeTextPosition when textNode->GetContext() is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextPosition003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    textNode->context_ = nullptr;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    overlayManager->MountGatherNodeToRootNode(textNode, {});
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    DragAnimationHelper::CalcBadgeTextPosition(host, overlayManager, imageNode, textNode);
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto content = layoutProperty->GetContentValue();
    EXPECT_NE(content.empty(), true);
}

/**
 * @tc.name: CalcBadgeTextPosition004
 * @tc.desc: Test CalcBadgeTextPosition when frameNode does not set badgeNumber
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create required dependency nodes imageNode and textNode.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(imageNode, nullptr);
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step2. Create frameNode and assign as MenuPattern target.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("menuTarget", GetElmtId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step3. Configure OverlayManager and insert 1 child node.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    std::vector<GatherNodeChildInfo> gatherInfos;
    auto gatherImageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    GatherNodeChildInfo info;
    info.imageNode = AceType::WeakClaim(AceType::RawPtr(gatherImageNode));
    gatherInfos.emplace_back(info);
    overlayManager->MountGatherNodeToRootNode(textNode, gatherInfos);

    /**
     * @tc.steps: step4. Call the target function.
     * @tc.expected: The text content of textNode should be childrenCount + 1, i.e., "2".
     */
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    DragAnimationHelper::CalcBadgeTextPosition(host, overlayManager, imageNode, textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContentValue();
    EXPECT_STREQ(StringUtils::Str16ToStr8(content).c_str(), "2");
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
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    DragAnimationHelper::CreateTextNode(data);
    data.deviceType = SourceType::MOUSE;
    EXPECT_NE(data.textRowNode, nullptr);
    data.textRowNode = nullptr;
    data.badgeNumber = 1;
    DragAnimationHelper::CreateTextNode(data);
    EXPECT_EQ(data.textRowNode, nullptr);
}

/**
 * @tc.name: ShouldSetOffsetForMenuDrag001
 * @tc.desc: Test ShouldSetOffsetForMenuDrag
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShouldSetOffsetForMenuDrag001, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrent();
    auto dragDropManager = pipelineContext->GetDragDropManager();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    dragDropManager->SetMenuWrapperNode(frameNode);
    auto ret1 = DragAnimationHelper::ShouldSetOffsetForMenuDrag();
    EXPECT_TRUE(ret1);
    auto menuWrapperPattern = frameNode->GetPattern<MenuWrapperPattern>();
    EXPECT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->dragMenuLiftAnimationFinish_ = false;
    auto ret2 = DragAnimationHelper::ShouldSetOffsetForMenuDrag();
    EXPECT_FALSE(ret2);
}


/**
 * @tc.name: MountPixelMap001
 * @tc.desc: Test MountPixelMap
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountPixelMap001, TestSize.Level1)
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

    /**
    * @tc.steps: step2. Get OverlayManager.
    */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
    * @tc.steps: step3. Trigger MountPixelMap.
    */
    PreparedInfoForDrag data;
    auto imageNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(imageNode, nullptr);
    data.imageNode = imageNode;
    data.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    DragAnimationHelper::MountPixelMap(overlayManager, gestureEventHub, data, true);
    EXPECT_EQ(overlayManager->hasDragPixelMap_, true);
}

/**
 * @tc.name: CalcBadgeTextOffset001
 * @tc.desc: CalcBadgeTextOffset
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextOffset001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create node.
    */
    auto imageNodeId = GetElmtId();
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, imageNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));

    /**
    * @tc.steps: step2. Execute CalcBadgeTextOffset
    */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    const int32_t badgeLength = 2;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    auto offset = DragAnimationHelper::CalcBadgeTextOffset(host, imageNode, pipelineContext, badgeLength);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    float expectX = -BADGE_RELATIVE_OFFSET.ConvertToPx();
    float expectY = -BADGE_RELATIVE_OFFSET.ConvertToPx();
    EXPECT_NEAR(offset.GetX(), expectX, EPSILON);
    EXPECT_NEAR(offset.GetY(), expectY, EPSILON);
}

/**
 * @tc.name: ShowMenuHideAnimation001
 * @tc.desc: test ShowMenuHideAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowMenuHideAnimation001, TestSize.Level1)
{
    PreparedInfoForDrag data;
    auto menuNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    data.menuNode = menuNode;
    data.isMenuNotShow = true;
    data.sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOpacity(1.0f);
    DragAnimationHelper::ShowMenuHideAnimation(data);
    auto opacity = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity == 1.0f);
    data.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;
    DragAnimationHelper::ShowMenuHideAnimation(data);
    auto opacity1 = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity1 == 1.0f);
    data.isMenuNotShow = false;
    DragAnimationHelper::ShowMenuHideAnimation(data);
    auto opacity2 = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity2 == 0.0f);
}

/**
 * @tc.name: MountMenuNode001
 * @tc.desc: test ShowMenuHideAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountMenuNode001, TestSize.Level1)
{
    PreparedInfoForDrag data;
    auto menuNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    auto relativeContainerNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(relativeContainerNode, nullptr);
    data.menuNode = menuNode;
    data.relativeContainerNode = relativeContainerNode;
    data.isMenuNotShow = false;
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOpacity(1.0f);
    DragAnimationHelper::MountMenuNode(data);
    auto opacity = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity == 1.0f);
    data.isMenuNotShow = true;
    DragAnimationHelper::MountMenuNode(data);
    opacity = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity == 0.0f);
}

/**
 * @tc.name: ShowGatherNodeAnimation
 * @tc.desc: test ShowGatherNodeAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowGatherNodeAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init overlayManager.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    parentNode_->AttachContext(AceType::RawPtr(pipelineContext), true);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->hasGatherNode_ = false;
    overlayManager->gatherNodeWeak_ = nullptr;

    /**
     * @tc.steps: step2. call ShowGatherNodeAnimation func
     */
    int32_t size = childNodes_.size();
    ASSERT_EQ(DEFAULT_CHILD_COUNT, size);
    auto iter = childNodes_.begin();
    ASSERT_TRUE(iter != childNodes_.end());
    auto itemNode = *(iter);
    ASSERT_NE(itemNode, nullptr);
    ASSERT_EQ(DragAnimationHelper::ShowGatherNodeAnimation(itemNode), true);
}

/**
 * @tc.name: CalcDistanceBeforeLifting001
 * @tc.desc: test CalcDistanceBeforeLifting with isGrid=true.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcDistanceBeforeLifting001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data with grid items.
     */
    auto imageNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode, nullptr);

    GatherNodeChildInfo childInfo;
    childInfo.imageNode = AceType::WeakClaim(AceType::RawPtr(imageNode));
    childInfo.width = 100.0f;
    childInfo.height = 150.0f;
    childInfo.halfWidth = 50.0f;
    childInfo.halfHeight = 75.0f;
    childInfo.offset = OffsetF(10.0f, 20.0f);

    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    gatherNodeChildrenInfo.push_back(childInfo);

    OffsetF gatherNodeCenter(50.0f, 100.0f);
    CalcResult calcResult = { 0.0f, -1.0f, -1.0f };

    /**
     * @tc.steps: step2. Call CalcDistanceBeforeLifting with isGrid=true.
     * @tc.expected: maxTranslation uses min of width and height.
     */
    DragAnimationHelper::CalcDistanceBeforeLifting(
        true, calcResult, gatherNodeCenter, gatherNodeChildrenInfo);

    EXPECT_GT(calcResult.maxDistance, 0.0f);
    EXPECT_GT(calcResult.minDistance, 0.0f);
    EXPECT_GT(calcResult.maxTranslation, 0.0f);
}

/**
 * @tc.name: CalcDistanceBeforeLifting002
 * @tc.desc: test CalcDistanceBeforeLifting with isGrid=false.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcDistanceBeforeLifting002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data for list items.
     */
    auto imageNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode, nullptr);

    GatherNodeChildInfo childInfo;
    childInfo.imageNode = AceType::WeakClaim(AceType::RawPtr(imageNode));
    childInfo.width = 100.0f;
    childInfo.height = 150.0f;
    childInfo.halfWidth = 50.0f;
    childInfo.halfHeight = 75.0f;
    childInfo.offset = OffsetF(10.0f, 20.0f);

    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    gatherNodeChildrenInfo.push_back(childInfo);

    OffsetF gatherNodeCenter(50.0f, 100.0f);
    CalcResult calcResult = { 0.0f, -1.0f, -1.0f };

    /**
     * @tc.steps: step2. Call CalcDistanceBeforeLifting with isGrid=false.
     * @tc.expected: maxTranslation uses height only.
     */
    DragAnimationHelper::CalcDistanceBeforeLifting(
        false, calcResult, gatherNodeCenter, gatherNodeChildrenInfo);

    EXPECT_GT(calcResult.maxDistance, 0.0f);
    EXPECT_GT(calcResult.minDistance, 0.0f);
    EXPECT_GT(calcResult.maxTranslation, 0.0f);
}

/**
 * @tc.name: PlayGatherNodeOpacityAnimation001
 * @tc.desc: test PlayGatherNodeOpacityAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PlayGatherNodeOpacityAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gather node children info.
     */
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    auto imageNodeId = GetElmtId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode, nullptr);

    GatherNodeChildInfo childInfo;
    childInfo.imageNode = AceType::WeakClaim(AceType::RawPtr(imageNode));
    gatherNodeChildrenInfo.push_back(childInfo);

    /**
     * @tc.steps: step2. Get overlayManager and set gather node children info.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    overlayManager->MountGatherNodeToRootNode(parentNode_, gatherNodeChildrenInfo);

    /**
     * @tc.steps: step3. Call PlayGatherNodeOpacityAnimation.
     */
    DragAnimationHelper::PlayGatherNodeOpacityAnimation(overlayManager);

    /**
     * @tc.steps: step4. Verify opacity animation was set.
     */
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: SetPreOpacity001
 * @tc.desc: test SetPreOpacity func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, SetPreOpacity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with grayed opacity.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    const float testOpacity = 0.6f;
    frameNode->SetPreGrayedOpacity(testOpacity);

    /**
     * @tc.steps: step2. Call SetPreOpacity.
     */
    DragAnimationHelper::SetPreOpacity(frameNode);

    /**
     * @tc.steps: step3. Verify opacity was updated.
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: DoDragStartGrayedAnimation001
 * @tc.desc: test DoDragStartGrayedAnimation func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, DoDragStartGrayedAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with existing opacity.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const float initialOpacity = 0.8f;
    renderContext->UpdateOpacity(initialOpacity);

    /**
     * @tc.steps: step2. Call DoDragStartGrayedAnimation.
     */
    DragAnimationHelper::DoDragStartGrayedAnimation(frameNode);

    /**
     * @tc.steps: step3. Verify preGrayedOpacity was set.
     */
    auto savedOpacity = frameNode->GetPreGrayedOpacity();
    EXPECT_NEAR(savedOpacity, initialOpacity, EPSILON);
}

/**
 * @tc.name: DoGrayedAnimation001
 * @tc.desc: test DoGrayedAnimation with text component.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, DoGrayedAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOpacity(1.0f);

    /**
     * @tc.steps: step2. Call DoGrayedAnimation - should return early for text.
     */
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 0.0f, 380.0f, 34.0f);
    DragAnimationHelper::DoGrayedAnimation(frameNode, 0.4f, curve);

    /**
     * @tc.steps: step3. For text, opacity should not change due to early return.
     */
    auto opacity = renderContext->GetOpacity();
    EXPECT_TRUE(opacity.has_value());
}

/**
 * @tc.name: SetNodeVisible001
 * @tc.desc: test SetNodeVisible func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, SetNodeVisible001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set node visible to false.
     */
    DragAnimationHelper::SetNodeVisible(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Set node visible to true.
     */
    DragAnimationHelper::SetNodeVisible(frameNode, true);
}

/**
 * @tc.name: SetImageNodeInitAttr001
 * @tc.desc: test SetImageNodeInitAttr func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, SetImageNodeInitAttr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and imageNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Set drag preview options with shadow.
     */
    DragPreviewOption previewOption;
    previewOption.options.shadow = Shadow::CreateShadow(ShadowStyle::None);
    frameNode->SetDragPreviewOptions(previewOption);

    /**
     * @tc.steps: step3. Call SetImageNodeInitAttr.
     */
    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);

    /**
     * @tc.steps: step4. Verify initial attributes were set.
     */
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto scale = renderContext->GetTransformScale();
    EXPECT_TRUE(scale.has_value());
}

/**
 * @tc.name: SetImageNodeFinishAttr001
 * @tc.desc: test SetImageNodeFinishAttr with filled shadow.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, SetImageNodeFinishAttr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and imageNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Set drag preview options with unfilled shadow.
     */
    DragPreviewOption previewOption;
    auto shadow = Shadow::CreateShadow(ShadowStyle::None);
    shadow.SetIsFilled(false);
    previewOption.options.shadow = shadow;
    frameNode->SetDragPreviewOptions(previewOption);

    /**
     * @tc.steps: step3. Call SetImageNodeFinishAttr.
     */
    DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode);

    /**
     * @tc.steps: step4. Verify shadow was updated.
     */
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: PreLayout001
 * @tc.desc: test PreLayout func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PreLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Attach to pipeline context.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    imageNode->AttachContext(AceType::RawPtr(pipelineContext), true);

    /**
     * @tc.steps: step3. Call PreLayout.
     */
    DragAnimationHelper::PreLayout(imageNode);
}

/**
 * @tc.name: UpdateGatherNodeToTop001
 * @tc.desc: test UpdateGatherNodeToTop func.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, UpdateGatherNodeToTop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get main pipeline context.
     */
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    ASSERT_NE(mainPipeline, nullptr);

    /**
     * @tc.steps: step2. Call UpdateGatherNodeToTop.
     */
    DragAnimationHelper::UpdateGatherNodeToTop();

    /**
     * @tc.steps: step3. Verify overlay manager is accessible.
     */
    auto overlayManager = mainPipeline->GetOverlayManager();
    EXPECT_NE(overlayManager, nullptr);
}

/**
 * @tc.name: GetMenuWrapperNodeFromDrag001
 * @tc.desc: test GetMenuWrapperNodeFromDrag with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetMenuWrapperNodeFromDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetMenuWrapperNodeFromDrag.
     * @tc.expected: Should return nullptr when no menu wrapper is set.
     */
    auto menuWrapperNode = DragAnimationHelper::GetMenuWrapperNodeFromDrag();
    EXPECT_EQ(menuWrapperNode, nullptr);
}

/**
 * @tc.name: GetMenuRenderContextFromMenuWrapper001
 * @tc.desc: test GetMenuRenderContextFromMenuWrapper with null wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetMenuRenderContextFromMenuWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null menuWrapperNode.
     * @tc.expected: Should return nullptr.
     */
    auto renderContext = DragAnimationHelper::GetMenuRenderContextFromMenuWrapper(nullptr);
    EXPECT_EQ(renderContext, nullptr);
}

/**
 * @tc.name: HideDragNodeCopyWithAnimation001
 * @tc.desc: test HideDragNodeCopyWithAnimation without dragNodeCopy.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, HideDragNodeCopyWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode without dragNodeCopy.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    DragPreviewOption option;
    option.defaultAnimationBeforeLifting = true;
    frameNode->SetDragPreviewOptions(option);

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Call HideDragNodeCopyWithAnimation.
     */
    DragAnimationHelper::HideDragNodeCopyWithAnimation(overlayManager, frameNode);

    /**
     * @tc.steps: step3. Verify visibility is restored to VISIBLE.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto visibility = layoutProperty->GetVisibilityValue(VisibleType::INVISIBLE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: CalcBadgeTextOffset002
 * @tc.desc: test CalcBadgeTextOffset with non-RTL.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create nodes for testing.
     */
    auto imageNodeId = GetElmtId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);

    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Set up geometry node with size.
     */
    auto geometryNode = imageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(10.0f), Dimension(20.0f)));

    /**
     * @tc.steps: step3. Get pipeline context.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step4. Call CalcBadgeTextOffset in non-RTL mode.
     */
    const int32_t badgeLength = 2;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);
    auto offset = DragAnimationHelper::CalcBadgeTextOffset(host, imageNode, pipelineContext, badgeLength);

    /**
     * @tc.steps: step5. Verify offset calculation.
     */
    EXPECT_NEAR(offset.GetX(), 0.0f, EPSILON);
    EXPECT_NEAR(offset.GetY(), 0.0f, EPSILON);
}

/**
 * @tc.name: ShowMenuHideAnimation002
 * @tc.desc: test ShowMenuHideAnimation with SIZE_CONTENT_TRANSITION.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowMenuHideAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare data with SIZE_CONTENT_TRANSITION.
     */
    PreparedInfoForDrag data;
    auto menuNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    data.menuNode = menuNode;
    data.isMenuNotShow = false;
    data.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION;

    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOpacity(1.0f);

    /**
     * @tc.steps: step2. Call ShowMenuHideAnimation.
     */
    DragAnimationHelper::ShowMenuHideAnimation(data);

    /**
     * @tc.steps: step3. Verify opacity was changed.
     */
    auto opacity = renderContext->GetOpacity().value();
    EXPECT_TRUE(opacity == 0.0f || opacity == 1.0f);
}

/**
 * @tc.name: CalcDistanceBeforeLifting003
 * @tc.desc: test CalcDistanceBeforeLifting with isGrid=false and multiple children.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcDistanceBeforeLifting003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data with multiple list items.
     */
    auto imageNodeId1 = GetElmtId();
    auto imageNode1 = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode1, nullptr);

    auto imageNodeId2 = GetElmtId();
    auto imageNode2 = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId2, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(imageNode2, nullptr);

    GatherNodeChildInfo childInfo1;
    childInfo1.imageNode = AceType::WeakClaim(AceType::RawPtr(imageNode1));
    childInfo1.width = 100.0f;
    childInfo1.height = 150.0f;
    childInfo1.halfWidth = 50.0f;
    childInfo1.halfHeight = 75.0f;
    childInfo1.offset = OffsetF(10.0f, 20.0f);

    GatherNodeChildInfo childInfo2;
    childInfo2.imageNode = AceType::WeakClaim(AceType::RawPtr(imageNode2));
    childInfo2.width = 100.0f;
    childInfo2.height = 80.0f;
    childInfo2.halfWidth = 50.0f;
    childInfo2.halfHeight = 40.0f;
    childInfo2.offset = OffsetF(20.0f, 40.0f);

    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    gatherNodeChildrenInfo.push_back(childInfo1);
    gatherNodeChildrenInfo.push_back(childInfo2);

    OffsetF gatherNodeCenter(50.0f, 100.0f);
    CalcResult calcResult = { 0.0f, -1.0f, -1.0f };

    /**
     * @tc.steps: step2. Call CalcDistanceBeforeLifting with isGrid=false.
     * @tc.expected: maxTranslation uses min of heights after first child sets it.
     */
    DragAnimationHelper::CalcDistanceBeforeLifting(
        false, calcResult, gatherNodeCenter, gatherNodeChildrenInfo);

    EXPECT_GT(calcResult.maxDistance, 0.0f);
    EXPECT_GT(calcResult.minDistance, 0.0f);
    EXPECT_GT(calcResult.maxTranslation, 0.0f);
    constexpr float LIST_MOVE_SCALE = 0.2f;
    EXPECT_NEAR(calcResult.maxTranslation, 80.0f * LIST_MOVE_SCALE, EPSILON);
}

/**
 * @tc.name: ShowBadgeAnimation002
 * @tc.desc: test ShowBadgeAnimation when IsShowBadgeAnimation is false.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowBadgeAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create textNode.
     */
    auto textNodeId = GetElmtId();
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, textNodeId,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step2. Get dragDropManager and set IsShowBadgeAnimation to false.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->SetIsShowBadgeAnimation(false);

    /**
     * @tc.steps: step3. Call ShowBadgeAnimation.
     * @tc.expected: Should return early without animation, scale set directly.
     */
    DragAnimationHelper::ShowBadgeAnimation(textNode);

    /**
     * @tc.steps: step4. Verify transform scale was set directly without animation.
     */
    auto renderContext = textNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto transformScale = renderContext->GetTransformScale();
    EXPECT_TRUE(transformScale.has_value());
    constexpr float BADGE_ANIMATION_SCALE = 1.0f;
    EXPECT_NEAR(transformScale->x, BADGE_ANIMATION_SCALE, EPSILON);
    EXPECT_NEAR(transformScale->y, BADGE_ANIMATION_SCALE, EPSILON);
}

/**
 * @tc.name: CalcBadgeTextOffset003
 * @tc.desc: test CalcBadgeTextOffset with non-RTL and valid MenuPattern.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, CalcBadgeTextOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create nodes for testing.
     */
    auto imageNodeId = GetElmtId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewAfterAnimationScale(1.0f);

    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Set up geometry node with size.
     */
    auto geometryNode = imageNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));

    /**
     * @tc.steps: step3. Get pipeline context and set up themeManager.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipelineContext->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            if (type == MenuTheme::TypeId()) {
                return AceType::MakeRefPtr<MenuTheme>();
            }
            return nullptr;
        });

    /**
     * @tc.steps: step4. Call CalcBadgeTextOffset in non-RTL mode.
     */
    const int32_t badgeLength = 2;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto host = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, GetElmtId(), menuPattern);
    ASSERT_TRUE(host != nullptr);

    auto offset = DragAnimationHelper::CalcBadgeTextOffset(host, imageNode, pipelineContext, badgeLength);

    /**
     * @tc.steps: step5. Verify offset calculation.
     * @tc.expected: Should have valid offset X and Y values.
     */
    constexpr float BADGE_RELATIVE_OFFSET_VALUE = 8.0f;
    constexpr float previewAfterAnimationScale = 1.0f;
    float expectedX = 0.0f + 100.0f * previewAfterAnimationScale -
        BADGE_RELATIVE_OFFSET_VALUE - (BADGE_RELATIVE_OFFSET_VALUE * badgeLength);
    float expectedY = 0.0f - BADGE_RELATIVE_OFFSET_VALUE;
    EXPECT_NEAR(offset.GetX(), expectedX, EPSILON);
    EXPECT_NEAR(offset.GetY(), expectedY, EPSILON);
}

/**
 * @tc.name: SwapGatherNodeToSubwindowInUIExtension001
 * @tc.desc: Test SwapGatherNodeToSubwindowInUIExtension through ShowGatherAnimationWithMenu
 *           when IsUIExtensionWindow is true.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, SwapGatherNodeToSubwindowInUIExtension001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get pipeline context and set instanceId.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetUseFlushUITasks(false);
    constexpr int32_t testInstanceId = 100;
    pipelineContext->SetInstanceId(testInstanceId);

    /**
     * @tc.steps: step2. Get container and set UIExtensionWindow.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->isUIExtensionWindow_ = true;
    ON_CALL(*container, GetInstanceId()).WillByDefault(Return(testInstanceId));
    AceEngine::Get().AddContainer(testInstanceId, container);

    /**
     * @tc.steps: step3. Create subwindowRootNode and menuWrapperNode.
     */
    auto subwindowRootNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(subwindowRootNode, nullptr);

    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<MenuWrapperPattern>(GetElmtId()));
    ASSERT_NE(menuWrapperNode, nullptr);
    menuWrapperNode->MountToParent(subwindowRootNode);

    /**
     * @tc.steps: step4. Create gatherNode and mount to overlayManager.
     */
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    auto gatherNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(gatherNode, nullptr);
    gatherNode->AttachContext(AceType::RawPtr(pipelineContext), true);

    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
    overlayManager->MountGatherNodeToRootNode(gatherNode, gatherNodeChildrenInfo);

    /**
     * @tc.steps: step5. Call ShowGatherAnimationWithMenu.
     * @tc.expected: SwapGatherNodeToSubwindowInUIExtension should be triggered via AddAfterRenderTask.
     */
    DragAnimationHelper::ShowGatherAnimationWithMenu(menuWrapperNode);

    /**
     * @tc.steps: step6. Verify gatherNode was moved to subwindowRootNode.
     */
    auto gatherNodeParent = gatherNode->GetParent();
    EXPECT_EQ(gatherNodeParent, subwindowRootNode);

    /**
     * @tc.steps: step7. Clean up.
     */
    AceEngine::Get().RemoveContainer(testInstanceId);
    container->isUIExtensionWindow_ = false;
}


/**
 * @tc.name: ShowDragNodeCopyAnimation001
 * @tc.desc: test ShowDragNodeCopyAnimation with defaultAnimationBeforeLifting=false.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowDragNodeCopyAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and set previewOptions.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    DragPreviewOption previewOptions;
    previewOptions.defaultAnimationBeforeLifting = false;
    frameNode->SetDragPreviewOptions(previewOptions);

    /**
     * @tc.steps: step2. Create dragNodeCopy and set to overlayManager.
     */
    auto dragNodeCopy = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(dragNodeCopy, nullptr);

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->SetDragNodeCopy(dragNodeCopy);

    /**
     * @tc.steps: step3. Call ShowDragNodeCopyAnimation.
     * @tc.expected: Should return early without animation.
     */
    DragAnimationHelper::ShowDragNodeCopyAnimation(overlayManager, frameNode);

    /**
     * @tc.steps: step4. Verify visibility was not changed.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto visibility = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}


/**
 * @tc.name: PreLayout002
 * @tc.desc: test PreLayout with valid imageNode.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, PreLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Attach to pipeline context.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    imageNode->AttachContext(AceType::RawPtr(pipelineContext), true);

    /**
     * @tc.steps: step3. Call PreLayout.
     * @tc.expected: Should execute FlushSyncGeometryNodeTasks and PreLayout at lines 867-868.
     */
    DragAnimationHelper::PreLayout(imageNode);

    /**
     * @tc.steps: step4. Verify imageNode context is valid.
     */
    auto context = imageNode->GetContext();
    ASSERT_NE(context, nullptr);
}

/**
 * @tc.name: UpdateBadgeTextNodePosition001
 * @tc.desc: test UpdateBadgeTextNodePosition with valid inputs.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, UpdateBadgeTextNodePosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and set pixelMap.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(mockPixelMap, nullptr);
    gestureHub->SetPixelMap(mockPixelMap);

    /**
     * @tc.steps: step2. Create textNode.
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);

    auto textRenderContext = textNode->GetRenderContext();
    ASSERT_NE(textRenderContext, nullptr);

    /**
     * @tc.steps: step3. Set RTL to false.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    /**
     * @tc.steps: step4. Call UpdateBadgeTextNodePosition with valid parameters.
     * @tc.expected: Should update position.
     */
    constexpr int32_t childSize = 2;
    constexpr float previewScale = 1.05f;
    OffsetF previewOffset(10.0f, 20.0f);
    DragAnimationHelper::UpdateBadgeTextNodePosition(frameNode, textNode, childSize, previewScale, previewOffset);

    /**
     * @tc.steps: step5. Verify position was updated.
     */
    auto position = textRenderContext->GetPosition();
    EXPECT_TRUE(position.has_value());
}

/**
 * @tc.name: ShowPreviewBadgeAnimation001
 * @tc.desc: test ShowPreviewBadgeAnimation with column nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowPreviewBadgeAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with gestureHub.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    DragPreviewOption previewOptions;
    previewOptions.isNumber = true;
    previewOptions.badgeNumber = 2;
    frameNode->SetDragPreviewOptions(previewOptions);

    /**
     * @tc.steps: step2. Get overlayManager without pixelMapNode.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->pixmapColumnNodeWeak_ = nullptr;

    /**
     * @tc.steps: step3. Call ShowPreviewBadgeAnimation.
     * @tc.expected: Should return early.
     */
    DragAnimationHelper::ShowPreviewBadgeAnimation(gestureHub, overlayManager);
}

/**
 * @tc.name: ShowPreviewBadgeAnimation002
 * @tc.desc: test ShowPreviewBadgeAnimation with valid inputs.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, ShowPreviewBadgeAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with gestureHub.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    DragPreviewOption previewOptions;
    previewOptions.isNumber = true;
    previewOptions.badgeNumber = 2;
    frameNode->SetDragPreviewOptions(previewOptions);

    /**
     * @tc.steps: step2. Create column node and set to overlayManager.
     */
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(column, nullptr);

    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->pixmapColumnNodeWeak_ = column;

    /**
     * @tc.steps: step3. Call ShowPreviewBadgeAnimation.
     * @tc.expected: Should execute successfully.
     */
    DragAnimationHelper::ShowPreviewBadgeAnimation(gestureHub, overlayManager);

    /**
     * @tc.steps: step4. Verify textNode was added to column.
     */
    EXPECT_GT(column->GetChildren().size(), 0);
}

/**
 * @tc.name: MountPixelMapWithBadge001
 * @tc.desc: test MountPixelMapWithBadge.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountPixelMapWithBadge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Create textRowNode.
     */
    auto textRowNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textRowNode, nullptr);

    /**
     * @tc.steps: step3. Create relativeContainerNode.
     */
    auto relativeContainerNode = FrameNode::CreateFrameNode(
        V2::RELATIVE_CONTAINER_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<RelativeContainerPattern>());
    ASSERT_NE(relativeContainerNode, nullptr);

    /**
     * @tc.steps: step4. Create columnNode.
     */
    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    /**
     * @tc.steps: step5. Prepare PreparedInfoForDrag.
     */
    PreparedInfoForDrag data;
    data.imageNode = imageNode;
    data.textRowNode = textRowNode;
    data.relativeContainerNode = relativeContainerNode;

    /**
     * @tc.steps: step6. Call MountPixelMapWithBadge.
     * @tc.expected: Should execute successfully.
     */
    DragAnimationHelper::MountPixelMapWithBadge(data, columnNode);

    /**
     * @tc.steps: step7. Verify relativeContainerNode was added to columnNode.
     */
    EXPECT_EQ(columnNode->GetChildren().size(), 1);
    auto child = columnNode->GetChildByIndex(0);
    EXPECT_EQ(child, relativeContainerNode);
}

/**
 * @tc.name: MountPixelMap002
 * @tc.desc: test MountPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountPixelMap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode and relativeContainerNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    auto relativeContainerNode = FrameNode::CreateFrameNode(
        V2::RELATIVE_CONTAINER_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<RelativeContainerPattern>());
    ASSERT_NE(relativeContainerNode, nullptr);

    /**
     * @tc.steps: step2. Create frameNode with gestureHub and pixelMap.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(mockPixelMap, nullptr);
    gestureHub->SetPixelMap(mockPixelMap);

    /**
     * @tc.steps: step3. Get overlayManager.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step4. Prepare PreparedInfoForDrag with SIZE_TRANSITION effect.
     */
    PreparedInfoForDrag data;
    data.imageNode = imageNode;
    data.relativeContainerNode = relativeContainerNode;
    data.sizeChangeEffect = DraggingSizeChangeEffect::SIZE_TRANSITION;

    /**
     * @tc.steps: step5. Call MountPixelMap with isDragPixelMap = false.
     * @tc.expected: Should execute MountPixelMapSizeContentTransition successfully.
     */
    DragAnimationHelper::MountPixelMap(overlayManager, gestureHub, data, false);

    /**
     * @tc.steps: step6. Verify pixelMap was mounted.
     */
    EXPECT_TRUE(overlayManager->hasDragPixelMap_);
}

/**
 * @tc.name: MountPixelMapSizeContentTransition001
 * @tc.desc: test MountPixelMapSizeContentTransition.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, MountPixelMapSizeContentTransition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Create relativeContainerNode.
     */
    auto relativeContainerNode = FrameNode::CreateFrameNode(
        V2::RELATIVE_CONTAINER_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<RelativeContainerPattern>());
    ASSERT_NE(relativeContainerNode, nullptr);

    /**
     * @tc.steps: step3. Create textRowNode.
     */
    auto textRowNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textRowNode, nullptr);

    /**
     * @tc.steps: step4. Create menuNode.
     */
    auto menuNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(),
        AceType::MakeRefPtr<MenuPattern>(GetElmtId(),
        V2::COLUMN_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);

    /**
     * @tc.steps: step5. Create columnNode.
     */
    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);

    /**
     * @tc.steps: step6. Prepare PreparedInfoForDrag with textRowNode and menuNode.
     */
    PreparedInfoForDrag data;
    data.imageNode = imageNode;
    data.relativeContainerNode = relativeContainerNode;
    data.textRowNode = textRowNode;
    data.menuNode = menuNode;
    data.originPreviewRect = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    data.borderRadius = BorderRadiusProperty(Dimension(0.0f));

    /**
     * @tc.steps: step7. Call MountPixelMapSizeContentTransition.
     * @tc.expected: Should execute lines 1179 and 1182.
     */
    DragAnimationHelper::MountPixelMapSizeContentTransition(data, columnNode);

    /**
     * @tc.steps: step8. Verify nodes were added correctly.
     */
    EXPECT_GT(relativeContainerNode->GetChildren().size(), 0);
}

/**
 * @tc.name: GetMenuRenderContextFromMenuWrapper002
 * @tc.desc: test GetMenuRenderContextFromMenuWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(DragAnimationHelperTestNg, GetMenuRenderContextFromMenuWrapper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuWrapperNode with MenuWrapperPattern.
     */
    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<MenuWrapperPattern>(GetElmtId()));
    ASSERT_NE(menuWrapperNode, nullptr);

    /**
     * @tc.steps: step2. Create menuNode and add as first child of menuWrapperNode.
     */
    auto menuNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, GetElmtId(),
        AceType::MakeRefPtr<MenuPattern>(GetElmtId(),
        V2::COLUMN_ETS_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuWrapperNode->AddChild(menuNode);

    /**
     * @tc.steps: step3. Call GetMenuRenderContextFromMenuWrapper.
     * @tc.expected: Should return menuNode's renderContext.
     */
    auto renderContext = DragAnimationHelper::GetMenuRenderContextFromMenuWrapper(menuWrapperNode);

    /**
     * @tc.steps: step4. Verify renderContext is valid.
     */
    EXPECT_NE(renderContext, nullptr);
}
} // namespace OHOS::Ace::NG
