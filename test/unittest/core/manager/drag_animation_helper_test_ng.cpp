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
    ViewAbstract::SetWidth(frameNode.GetRawPtr(), CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(frameNode.GetRawPtr(), CalcLength(GRID_HEIGHT));
    std::list<RefPtr<FrameNode>> childNodes;

    for (size_t i = 0; i < childCount; ++i) {
        ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
        auto itemNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::GRID_ITEM_ETS_TAG, itemNodeId,
            [itemStyle = gridItemStyle]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });
        ViewAbstract::SetWidth(childNode.GetRawPtr(), CalcLength(ITEM_WIDTH));
        ViewAbstract::SetHeight(childNode.GetRawPtr(), CalcLength(ITEM_HEIGHT));
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
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::MENU);
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
    auto content = textLayoutProperty->GetContentValue(u"2");
    EXPECT_STREQ(StringUtils::Str16ToStr8(content).c_str(),
        std::to_string(overlayManager->GetGatherNodeChildrenInfo().size() + 1).c_str());
}
} // namespace OHOS::Ace::NG