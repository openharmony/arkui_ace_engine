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

#include "test/unittest/core/pattern/relative_container/relative_container_base_test_ng.h"

#include "core/components/common/layout/position_param.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "frameworks/base/memory/type_info_base.h"
#include "frameworks/core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;

const std::string FIRST_ITEM_ID = "bt1";
const std::string SECOND_ITEM_ID = "bt2";
const std::string THIRD_ITEM_ID = "bt3";
const std::string FOURTH_ITEM_ID = "bt4";
const std::string FIFTH_ITEM_ID = "bt5";
const std::string CONTAINER_ID = "__container__";

const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const std::vector<Dimension> DIMENSIONS = {
    Dimension(50.0, DimensionUnit::VP),
    Dimension(-10.0, DimensionUnit::VP),
    Dimension(0.5, DimensionUnit::PERCENT),
    Dimension(-0.1, DimensionUnit::PERCENT)
};

const std::string ROW_FRAME_NODE = "rowFrameNode";
const std::string FIRST_FRAME_NODE = "TabContent";
const std::string FIRST_CHILD_FRAME_NODE = "firstChildFrameNode";
const std::string SECOND_CHILD_FRAME_NODE = "secondChildFrameNode";
const std::string THIRD_CHILD_FRAME_NODE = "thirdChildFrameNode";

} // namespace
class RelativeContainerNewTestNG : public RelativeContainerBaseTestNG {};
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm(RefPtr<FrameNode>& frameNode)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    std::optional<CalcLength> width = CalcLength(CONTAINER_WIDTH);
    std::optional<CalcLength> height = CalcLength(CONTAINER_HEIGHT);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = CalcSize(width, height);
    relativeContainerFrameNode->UpdateLayoutConstraint(layoutConstraint);
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);

    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    auto layoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    relativeContainerFrameNode->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    relativeContainerFrameNode->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = relativeContainerFrameNode->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    std::map<AlignDirection, AlignRule> firstAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstAlignRules);

    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    firstFrameNode->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);

    relativeContainerFrameNode->AddChild(firstFrameNode);
    frameNode = relativeContainerFrameNode;

    return layoutAlgorithm;
}
/**
 * @tc.name: RelativeContainerLayoutAlgorithm001
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm001, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcSize> selfIdealSize;
    float containerWidth = 200.0f;
    GuidelineInfo guidelineInfo;
    relativeContainerLayoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.id = "TOP";
    guidelineInfo.direction = LineDirection::VERTICAL;
    guidelineInfo.start = DIMENSIONS[0];
    relativeContainerLayoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.start = Dimension(2.0f, DimensionUnit::PERCENT);
    relativeContainerLayoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.start.reset();
    guidelineInfo.end = Dimension(2.0f, DimensionUnit::PERCENT);
    relativeContainerLayoutAlgorithm->CalcHorizontalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    EXPECT_NE(relativeContainerLayoutAlgorithm->guidelines_.find("TOP"),
        relativeContainerLayoutAlgorithm->guidelines_.end());
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm002
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm002, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcSize> selfIdealSize;
    float containerWidth = 200.0f;
    GuidelineInfo guidelineInfo;
    relativeContainerLayoutAlgorithm->CalcVerticalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.id = "TOP";
    guidelineInfo.direction = LineDirection::VERTICAL;
    guidelineInfo.start = DIMENSIONS[0];
    relativeContainerLayoutAlgorithm->CalcVerticalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.start = Dimension(2.0f, DimensionUnit::PERCENT);
    relativeContainerLayoutAlgorithm->CalcVerticalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    guidelineInfo.start.reset();
    guidelineInfo.end = Dimension(2.0f, DimensionUnit::PERCENT);
    relativeContainerLayoutAlgorithm->CalcVerticalGuideline(selfIdealSize, containerWidth, guidelineInfo);
    EXPECT_NE(relativeContainerLayoutAlgorithm->guidelines_.find("TOP"),
        relativeContainerLayoutAlgorithm->guidelines_.end());
}
/**
 * @tc.name: RelativeContainerLayoutAlgorithm003
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm003, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 10.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 10.0f);
    relativeContainerLayoutAlgorithm->guidelines_["LEFT"] = std::make_pair(LineDirection::HORIZONTAL, 10.0f);
    relativeContainerLayoutAlgorithm->guidelines_["RIGHT"] = std::make_pair(LineDirection::VERTICAL, 50.0f);
    relativeContainerLayoutAlgorithm->guidelines_["TOP"] = std::make_pair(LineDirection::HORIZONTAL, 10.0f);
    relativeContainerLayoutAlgorithm->guidelines_["BOTTOM"] = std::make_pair(LineDirection::VERTICAL, 50.0f);
    relativeContainerLayoutAlgorithm->recordOffsetMap_["LEFT"] = OffsetF(0, 10);
    relativeContainerLayoutAlgorithm->recordOffsetMap_["RIGHT"] = OffsetF(100, 0);
    relativeContainerLayoutAlgorithm->recordOffsetMap_["TOP"] = OffsetF(0, 10);
    relativeContainerLayoutAlgorithm->recordOffsetMap_["BOTTOM"] = OffsetF(50, 0);
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["test"] = bp1;
    relativeContainerLayoutAlgorithm->barriers_["vertical"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = std::make_pair(BarrierDirection::TOP, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["BOTTOM"] = std::make_pair(BarrierDirection::BOTTOM, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["RIGHT"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["DEFAULT"] = std::make_pair(BarrierDirection::END, referencedIds);
    relativeContainerLayoutAlgorithm->MeasureBarrier("DEFAULT");
    auto barrierRect = relativeContainerLayoutAlgorithm->GetBarrierRectByReferencedIds(referencedIds);
    EXPECT_EQ(barrierRect.minLeft, 50);
    EXPECT_EQ(barrierRect.maxRight, 100);
    EXPECT_EQ(barrierRect.minTop, 10);
    EXPECT_EQ(barrierRect.maxBottom, 10);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm004
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm004, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = bp1;
    AlignRule alignRule;
    alignRule.anchor = "test";
    auto retf = relativeContainerLayoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
    alignRule.anchor = "TOP";
    auto frameNode = FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto testWrapper = frameNode->GetOrCreateChildByIndex(0, false);
    relativeContainerLayoutAlgorithm->CalcSizeParam(AceType::RawPtr(testWrapper), "test");
    retf = relativeContainerLayoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm005
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm005, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = bp1;
    AlignRule alignRule;
    alignRule.anchor = "test";
    auto retf = relativeContainerLayoutAlgorithm->GetVerticalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
    alignRule.anchor = "TOP";
    retf = relativeContainerLayoutAlgorithm->GetVerticalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm006
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm006, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = bp1;

    const std::string anchorName = "test";
    auto retb = relativeContainerLayoutAlgorithm->IsAnchorLegal(anchorName);
    EXPECT_EQ(retb, false);
    const std::string anchorName2 = "test2";
    retb = relativeContainerLayoutAlgorithm->IsAnchorLegal(anchorName2);
    EXPECT_EQ(retb, false);
    float anchorHeight = 0.1f;
    float flexItemHeight = 0.1f;
    auto retf = relativeContainerLayoutAlgorithm->CalcVerticalOffsetAlignBottom(
        VerticalAlign::CENTER, anchorHeight, flexItemHeight);
    EXPECT_EQ(retf, -0.05f);
    retf = relativeContainerLayoutAlgorithm->CalcVerticalOffsetAlignBottom(
        VerticalAlign::NONE, anchorHeight, flexItemHeight);
    EXPECT_EQ(retf, 0.0f);
    retf = relativeContainerLayoutAlgorithm->CalcVerticalOffsetAlignBottom(
        VerticalAlign::BOTTOM, anchorHeight, flexItemHeight);
    EXPECT_EQ(retf, 0.0f);
    retf = relativeContainerLayoutAlgorithm->CalcVerticalOffsetAlignCenter(
        VerticalAlign::NONE, anchorHeight, flexItemHeight);
    EXPECT_EQ(retf, 0.0f);
    retf = relativeContainerLayoutAlgorithm->CalcVerticalOffsetAlignTop(VerticalAlign::NONE, anchorHeight);
    EXPECT_EQ(retf, 0.0f);
    auto barrierDirectionRtl = relativeContainerLayoutAlgorithm->BarrierDirectionRtl(BarrierDirection::START);
    EXPECT_EQ(barrierDirectionRtl, BarrierDirection::LEFT);
    barrierDirectionRtl = relativeContainerLayoutAlgorithm->BarrierDirectionRtl(BarrierDirection::END);
    EXPECT_EQ(barrierDirectionRtl, BarrierDirection::RIGHT);
    barrierDirectionRtl = relativeContainerLayoutAlgorithm->BarrierDirectionRtl(BarrierDirection::BOTTOM);
    EXPECT_NE(barrierDirectionRtl, BarrierDirection::RIGHT);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm004
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm007, TestSize.Level1)
{
    RefPtr<FrameNode> relativeContainerFrameNode = nullptr;
    auto relativeContainerLayoutAlgorithm = CreateLayoutAlgorithm(relativeContainerFrameNode);
    auto layoutProperty = AccessibilityManager::DynamicCast<RelativeContainerLayoutProperty>(
        relativeContainerFrameNode->GetLayoutProperty());
    std::vector<GuidelineInfo> guidelineInfos;
    GuidelineInfo guidelineInfoItem;
    guidelineInfoItem.id = std::string("guideline.id");
    guidelineInfoItem.direction = LineDirection::HORIZONTAL;
    guidelineInfos.emplace_back(guidelineInfoItem);
    GuidelineInfo guidelineInfoItem2;
    guidelineInfoItem.id = std::string("guideline.id2");
    guidelineInfoItem.direction = LineDirection::VERTICAL;
    guidelineInfos.emplace_back(guidelineInfoItem2);
    layoutProperty->UpdateGuideline(guidelineInfos);
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    auto relativeContainerLayoutAlgorithm2 =
        AccessibilityManager::DynamicCast<RelativeContainerLayoutAlgorithm>(relativeContainerLayoutAlgorithm);
    relativeContainerLayoutAlgorithm2->versionGreatorOrEqualToEleven_ = true;
    AlignRule alignRule;
    alignRule.anchor = "test";
    alignRule.horizontal = HorizontalAlign::START;
    LayoutWrapper* layoutWrapper = nullptr;
    relativeContainerLayoutAlgorithm2->CalcHorizontalLayoutParam(
        AlignDirection::RIGHT, alignRule, layoutWrapper, "test");
    relativeContainerLayoutAlgorithm2->CalcVerticalLayoutParam(AlignDirection::RIGHT, alignRule, layoutWrapper, "test");
    relativeContainerLayoutAlgorithm2->CalcGuideline(AceType::RawPtr(relativeContainerFrameNode));
    TwoAlignedValues twoAlignedValues = { 3.14f, 2.71f };
    relativeContainerLayoutAlgorithm2->UpdateTwoAlignValues(twoAlignedValues, alignRule, LineDirection::HORIZONTAL);
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    relativeContainerLayoutAlgorithm2->horizontalChains_["test"] = chainParam;
    std::string chainName;
    EXPECT_EQ(relativeContainerLayoutAlgorithm2->IsNodeInHorizontalChain("testnode", chainName), false);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm008
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm008, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "LEFT", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["LEFT"] = std::make_pair(LineDirection::VERTICAL, 11.0f);
    relativeContainerLayoutAlgorithm->recordOffsetMap_["LEFT"] = OffsetF(11, 0);
    relativeContainerLayoutAlgorithm->barriers_["LEFT"] = std::make_pair(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["vertical"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = std::make_pair(BarrierDirection::TOP, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["BOTTOM"] = std::make_pair(BarrierDirection::BOTTOM, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["RIGHT"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeContainerLayoutAlgorithm->barriers_["DEFAULT"] = std::make_pair(BarrierDirection::END, referencedIds);
    relativeContainerLayoutAlgorithm->MeasureBarrier("DEFAULT");
    auto barrierRect = relativeContainerLayoutAlgorithm->GetBarrierRectByReferencedIds(referencedIds);
    EXPECT_EQ(barrierRect.minLeft, 1);
    EXPECT_EQ(barrierRect.maxRight, 11);
    EXPECT_EQ(barrierRect.minTop, Infinity<float>());
    EXPECT_EQ(barrierRect.maxBottom, 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm009
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm009, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper currMeasureWrapper;
    currMeasureWrapper.id = "currentNode";
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    childMeasureWrapper.id = "nextNode";
    relativeContainerLayoutAlgorithm->idNodeMap_["nextNode"] = childMeasureWrapper;
    relativeContainerLayoutAlgorithm->idNodeMap_["currentNode"] = currMeasureWrapper;
    std::string currentNode = "currentNode";
    std::string nextNode = "nextNode";
    AlignRule alignRule;
    alignRule.anchor = "nextNode";
    alignRule.horizontal = HorizontalAlign::END;
    AlignRulesItem currentAlignRules;
    currentAlignRules[AlignDirection::RIGHT] = alignRule;
    std::vector<std::string> chainNodes;
    AlignRule rightAnchor;
    rightAnchor.anchor = "nextNode";
    float totalChainWeight;
    relativeContainerLayoutAlgorithm->CheckNodeInHorizontalChain(
        currentNode, currentAlignRules, chainNodes, rightAnchor, totalChainWeight);
    EXPECT_NE(currentAlignRules.size(), 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm010
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm010, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto frameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isActive_ = false;
    BorderWidthProperty borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->UpdateBorderWidth(borderWidth);
    layoutProperty->layoutConstraint_ = layoutConstraintF;
    layoutProperty->contentConstraint_ = layoutConstraintF;
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->SetActive(true);
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper currMeasureWrapper;
    currMeasureWrapper.id = "currentNode";
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    childMeasureWrapper.id = "nextNode";
    relativeContainerLayoutAlgorithm->idNodeMap_["nextNode"] = childMeasureWrapper;
    relativeContainerLayoutAlgorithm->idNodeMap_["currentNode"] = currMeasureWrapper;
    std::string currentNode = "currentNode";
    std::string nextNode = "nextNode";
    AlignRule alignRule;
    alignRule.anchor = "nextNode";
    alignRule.horizontal = HorizontalAlign::START;
    AlignRulesItem currentAlignRules;
    currentAlignRules[AlignDirection::RIGHT] = alignRule;
    std::vector<std::string> chainNodes;
    AlignRule rightAnchor;
    relativeContainerLayoutAlgorithm->idNodeMap_[nextNode].layoutWrapper = layoutWrapper;
    auto nextNodeWrapper = relativeContainerLayoutAlgorithm->idNodeMap_[nextNode].layoutWrapper;
    const auto& nextNodeFlexItem = nextNodeWrapper->GetLayoutProperty()->GetFlexItemProperty();
    float totalChainWeight;
    rightAnchor.anchor = "nextNode";
    relativeContainerLayoutAlgorithm->CheckNodeInHorizontalChain(
        currentNode, currentAlignRules, chainNodes, rightAnchor, totalChainWeight);
    layoutProperty = nextNodeWrapper->GetLayoutProperty();
    layoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    alignRule.anchor = "LEFT";
    std::map<AlignDirection, AlignRule> tempMap = { { AlignDirection::LEFT, alignRule } };
    nextNodeFlexItem->propAlignRules_ = tempMap;
    relativeContainerLayoutAlgorithm->CheckNodeInHorizontalChain(
        currentNode, currentAlignRules, chainNodes, rightAnchor, totalChainWeight);
    EXPECT_NE(currentAlignRules.size(), 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm011
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm011, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcSize> selfIdealSize;
    float anchorWidth = CONTAINER_WIDTH;
    float flexItemWidth = CONTAINER_HEIGHT;
    auto ret =
        relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignLeft(static_cast<HorizontalAlign>(-1), anchorWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignMiddle(
        static_cast<HorizontalAlign>(-1), anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignRight(
        static_cast<HorizontalAlign>(-1), anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignRight(
        HorizontalAlign::CENTER, anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, -150.0f);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm012
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm012, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::optional<CalcSize> selfIdealSize;
    float anchorWidth = CONTAINER_WIDTH;
    float flexItemWidth = CONTAINER_HEIGHT;
    auto ret =
        relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignLeft(static_cast<HorizontalAlign>(-1), anchorWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignMiddle(
        static_cast<HorizontalAlign>(-1), anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignRight(
        static_cast<HorizontalAlign>(-1), anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, 0.0f);
    ret = relativeContainerLayoutAlgorithm->CalcHorizontalOffsetAlignRight(
        HorizontalAlign::CENTER, anchorWidth, flexItemWidth);
    EXPECT_EQ(ret, -150.0f);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm013
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm013, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);

    auto frameNode = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                CONTAINER_ID, static_cast<AlignDirection>(-1), static_cast<HorizontalAlign>(-1), firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text2");
            std::map<AlignDirection, AlignRule> secondTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                "text1", AlignDirection::LEFT, HorizontalAlign::END, secondTextAlignRules);
            ViewAbstract::SetAlignRules(secondTextAlignRules);
        });
        auto text3 = CreateText(u"text3", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text3");
            std::map<AlignDirection, AlignRule> thirdTextAlignRules;
            RelativeContainerTestUtilsNG::AddAlignRule(
                "barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
            ViewAbstract::SetAlignRules(thirdTextAlignRules);
        });
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    EXPECT_EQ(frameNode->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 200.0f);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm014
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm014, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = bp1;
    AlignRule alignRule;
    alignRule.anchor = "__container__";
    auto retf = relativeContainerLayoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
    alignRule.horizontal = HorizontalAlign::CENTER;
    retf = relativeContainerLayoutAlgorithm->GetHorizontalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm015
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm015, TestSize.Level1)
{
    auto relativeContainerLayoutAlgorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::vector<std::string> referencedIds = { "test", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeContainerLayoutAlgorithm->versionGreatorOrEqualToEleven_ = true;
    BarrierParams bp1(BarrierDirection::LEFT, referencedIds);
    relativeContainerLayoutAlgorithm->guidelines_["test"] = std::make_pair(LineDirection::HORIZONTAL, 0.0f);
    relativeContainerLayoutAlgorithm->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeContainerLayoutAlgorithm->barriers_["TOP"] = bp1;
    AlignRule alignRule;
    alignRule.anchor = "__container__";
    auto retf = relativeContainerLayoutAlgorithm->GetVerticalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
    alignRule.horizontal = HorizontalAlign::CENTER;
    retf = relativeContainerLayoutAlgorithm->GetVerticalAnchorValueByAlignRule(alignRule);
    EXPECT_EQ(retf, 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm016
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm016, TestSize.Level1)
{
    RefPtr<FrameNode> relativeContainerFrameNode = nullptr;
    auto relativeContainerLayoutAlgorithm = CreateLayoutAlgorithm(relativeContainerFrameNode);

    std::vector<GuidelineInfo> guidelineInfos;
    GuidelineInfo guidelineInfoItem;
    guidelineInfoItem.id = std::string("guideline.id");
    guidelineInfoItem.direction = LineDirection::HORIZONTAL;
    guidelineInfos.emplace_back(guidelineInfoItem);
    auto layoutProperty = AccessibilityManager::DynamicCast<RelativeContainerLayoutProperty>(
        relativeContainerFrameNode->GetLayoutProperty());
    layoutProperty->UpdateGuideline(guidelineInfos);
    layoutProperty->UpdateVisibility(VisibleType::GONE);

    auto frameNode = FrameNode::CreateFrameNode("tag", 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->SetActive(true);

    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper currMeasureWrapper;
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    currMeasureWrapper.id = "currentNode";
    childMeasureWrapper.id = "nextNode";
    auto relativeAlg2 =
        AccessibilityManager::DynamicCast<RelativeContainerLayoutAlgorithm>(relativeContainerLayoutAlgorithm);
    relativeAlg2->versionGreatorOrEqualToEleven_ = true;
    relativeAlg2->idNodeMap_["nextNode"] = childMeasureWrapper;
    relativeAlg2->idNodeMap_["currentNode"] = currMeasureWrapper;
    relativeAlg2->idNodeMap_["nextNode"].layoutWrapper = layoutWrapper;

    auto childLayoutProperty = layoutWrapper->GetLayoutProperty();
    childLayoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();

    AlignRule alignRule;
    alignRule.anchor = "nextNode";
    alignRule.horizontal = HorizontalAlign::START;
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    firstItemAlignRules[AlignDirection::LEFT] = alignRule;
    childLayoutProperty->UpdateAlignRules(firstItemAlignRules);
    childLayoutProperty->flexItemProperty_->propFlexGrow = 1.0f;

    std::vector<std::string> referencedIds = { "nextNode", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeAlg2->guidelines_["nextNode"] = std::make_pair(LineDirection::HORIZONTAL, 10.0f);
    relativeAlg2->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeAlg2->barriers_["nextNode"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeAlg2->barriers_["RIGHT"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeAlg2->recordOffsetMap_["nextNode"] = OffsetF(100, 100);

    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    relativeAlg2->CalcHorizontalLayoutParam(AlignDirection::RIGHT, alignRule, nullptr, "nextNode");
    EXPECT_EQ(childFlexItemProperty->GetAlignRight(), 0);
    relativeAlg2->CalcVerticalLayoutParam(AlignDirection::RIGHT, alignRule, nullptr, "nextNode");
    EXPECT_EQ(childFlexItemProperty->GetAlignRight(), 100);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm017
 * @tc.desc: test RelativeContainerLayout Algorithm.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm017, TestSize.Level1)
{
    RefPtr<FrameNode> relativeContainerFrameNode = nullptr;
    auto relativeContainerLayoutAlgorithm = CreateLayoutAlgorithm(relativeContainerFrameNode);

    std::vector<GuidelineInfo> guidelineInfos;
    GuidelineInfo guidelineInfoItem;
    guidelineInfoItem.id = std::string("guideline.id");
    guidelineInfoItem.direction = LineDirection::HORIZONTAL;
    guidelineInfos.emplace_back(guidelineInfoItem);
    auto layoutProperty = AccessibilityManager::DynamicCast<RelativeContainerLayoutProperty>(
        relativeContainerFrameNode->GetLayoutProperty());
    layoutProperty->UpdateGuideline(guidelineInfos);
    layoutProperty->UpdateVisibility(VisibleType::GONE);

    auto frameNode = FrameNode::CreateFrameNode("tag", 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->SetActive(true);

    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper currMeasureWrapper;
    RelativeContainerLayoutAlgorithm::ChildMeasureWrapper childMeasureWrapper;
    currMeasureWrapper.id = "currentNode";
    childMeasureWrapper.id = "nextNode";

    auto relativeAlg2 =
        AccessibilityManager::DynamicCast<RelativeContainerLayoutAlgorithm>(relativeContainerLayoutAlgorithm);
    relativeAlg2->versionGreatorOrEqualToEleven_ = true;
    relativeAlg2->idNodeMap_["nextNode"] = childMeasureWrapper;
    relativeAlg2->idNodeMap_["currentNode"] = currMeasureWrapper;
    relativeAlg2->idNodeMap_["nextNode"].layoutWrapper = layoutWrapper;

    auto childLayoutProperty = layoutWrapper->GetLayoutProperty();
    childLayoutProperty->flexItemProperty_ = std::make_unique<FlexItemProperty>();

    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    AlignRule alignRule;
    alignRule.anchor = "nextNode";
    alignRule.horizontal = HorizontalAlign::START;
    firstItemAlignRules[AlignDirection::LEFT] = alignRule;
    childLayoutProperty->UpdateAlignRules(firstItemAlignRules);
    childLayoutProperty->flexItemProperty_->propFlexGrow = 1.0f;

    std::vector<std::string> referencedIds = { "nextNode", "vertical", "TOP", "BOTTOM", "RIGHT" };
    relativeAlg2->guidelines_["nextNode"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeAlg2->guidelines_["vertical"] = std::make_pair(LineDirection::VERTICAL, 0.0f);
    relativeAlg2->barriers_["nextNode"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeAlg2->barriers_["RIGHT"] = std::make_pair(BarrierDirection::RIGHT, referencedIds);
    relativeAlg2->recordOffsetMap_["nextNode"] = OffsetF(100, 100);

    const auto& childFlexItemProperty = childLayoutProperty->GetFlexItemProperty();
    relativeAlg2->CalcHorizontalLayoutParam(AlignDirection::RIGHT, alignRule, nullptr, "nextNode");
    EXPECT_EQ(childFlexItemProperty->GetAlignRight(), 100);
    relativeAlg2->CalcVerticalLayoutParam(AlignDirection::RIGHT, alignRule, nullptr, "nextNode");
    EXPECT_EQ(childFlexItemProperty->GetAlignRight(), 0);
}

/**
 * @tc.name: RelativeContainerLayoutAlgorithm018
 * @tc.desc: test RelativeContainerLayout Algorithm IsNodeInChain();.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerNewTestNG, RelativeContainerLayoutAlgorithm018, TestSize.Level1)
{
    auto algorithm = std::make_shared<RelativeContainerLayoutAlgorithm>();
    std::string nodeName = "testNodeName1";
    algorithm->horizontalChainNodeMap_[nodeName] = "horizontalChainName";
    algorithm->horizontalChains_["horizontalChainName"] = *new RelativeContainerLayoutAlgorithm::ChainParam();
    algorithm->versionGreatorOrEqualToEleven_ = true;
    std::string chainName;
    auto nodeInHChainResult = algorithm->IsNodeInChain(nodeName, chainName, LineDirection::HORIZONTAL);
    EXPECT_EQ(nodeInHChainResult, true);
    auto nodeNotInVChainResult = algorithm->IsNodeInChain(nodeName, chainName, LineDirection::VERTICAL);
    EXPECT_EQ(nodeNotInVChainResult, false);
    algorithm->versionGreatorOrEqualToEleven_ = false;
    auto nodeInHChainResultApi10 = algorithm->IsNodeInChain(nodeName, chainName, LineDirection::HORIZONTAL);
    EXPECT_EQ(nodeInHChainResultApi10, false);
    auto nodeInVChainResultApi10 = algorithm->IsNodeInChain(nodeName, chainName, LineDirection::VERTICAL);
    EXPECT_EQ(nodeInVChainResultApi10, false);
    algorithm->versionGreatorOrEqualToEleven_ = true;
    std::string nodeNameNotExist = "testNodeNameNotExist";
    auto nodeNotInHChainResult = algorithm->IsNodeInChain(nodeNameNotExist, chainName, LineDirection::HORIZONTAL);
    EXPECT_EQ(nodeNotInHChainResult, false);
    algorithm->horizontalChainNodeMap_[nodeNameNotExist] = "horizontalChainNameNotExist";
    auto nodeInMapNotInHChainResult = algorithm->IsNodeInChain(nodeNameNotExist, chainName, LineDirection::HORIZONTAL);
    EXPECT_EQ(nodeInMapNotInHChainResult, false);
    algorithm->verticalChainNodeMap_[nodeName] = "verticalChainName";
    algorithm->verticalChains_["verticalChainName"] = *new RelativeContainerLayoutAlgorithm::ChainParam();
    auto nodeInVChainResult = algorithm->IsNodeInChain(nodeName, chainName, LineDirection::VERTICAL);
    EXPECT_EQ(nodeInVChainResult, true);
}
} // namespace OHOS::Ace::NG