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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
class SwiperLayoutTestNg : public SwiperTestNg {
public:
    void CheckItems(int32_t start, int32_t end, float prevMargin, float itemWidth);
};

/**
 * @tc.name: ChangeSwiperSize001
 * @tc.desc: Test change swiper size
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, ChangeSwiperSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set size and item
     */
    SwiperModelNG swiperModel;
    swiperModel.Create();
    GetSwiper();
    CreateSwiperDone();
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(0.f, 0.f)));

    /**
     * @tc.steps: step2. Add a item
     */
    TextModelNG textModel;
    textModel.Create("text");
    RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    currentFrameNode->MountToParent(frameNode_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(0.f, 0.f)));

    /**
     * @tc.steps: step3. Set size
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SWIPER_HEIGHT));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(SWIPER_WIDTH, SWIPER_HEIGHT)));

    /**
     * @tc.steps: step4. Change size
     * @tc.expected: swiper size are changed
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(300.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(500.f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(300.f, 500.f)));
}

void SwiperLayoutTestNg::CheckItems(int32_t start, int32_t end, float prevMargin, float itemWidth)
{
    float offset = prevMargin - itemWidth;
    float startPos = -itemWidth;
    for (int i = start; i <= end; ++i) {
        EXPECT_EQ(pattern_->itemPosition_.at(i).startPos, startPos);
        EXPECT_EQ(pattern_->itemPosition_.at(i).endPos, startPos + itemWidth);
        EXPECT_EQ(GetChildOffset(frameNode_, i).GetX(), offset);
        startPos += itemWidth;
        offset += itemWidth;
    }
}

/**
 * @tc.name: SwiperChangeWidth001
 * @tc.desc: Test Swiper changing width and re-layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperChangeWidth001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems(5);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.size(), 5);

    ChangeIndex(1);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    const float itemWidth1 = (SWIPER_WIDTH - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth1);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1000.0f), CalcLength(300.0f)));
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 1000.0f);
    const float itemWidth2 = (1000.0f - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth2);
}

/**
 * @tc.name: SwiperChangeWidth002
 * @tc.desc: Test Swiper's parent changing width and re-layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperChangeWidth002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems(5);
    CreateSwiperDone();
    layoutProperty_->ClearUserDefinedIdealSize(true, true);

    auto parent = FrameNode::CreateFrameNode("parent", -1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    parent->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(300.0f)));
    frameNode_->MountToParent(parent);

    FlushLayoutTask(parent);

    ChangeIndex(1);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    const float itemWidth1 = (400.0f - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth1);

    parent->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(800.0f), CalcLength(300.0f)));
    FlushLayoutTask(parent);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 800.0f);
    const float itemWidth2 = (800.0f - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth2);
}

/**
 * @tc.name: SwiperFlex001
 * @tc.desc: Test Swiper with Flex parent and layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperFlex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(1);
    CreateSwiperItems(5);
    CreateSwiperDone();
    layoutProperty_->UpdateFlexGrow(2.0f);
    layoutProperty_->UpdateFlexShrink(1.0f);
    layoutProperty_->ClearUserDefinedIdealSize(true, true);

    auto parent = FrameNode::CreateFrameNode("parent", -1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    parent->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(300.0f)));
    frameNode_->MountToParent(parent);
    // sibling node
    auto sibling = FrameNode::CreateFrameNode("sibling", -1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    sibling->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100.0f), CalcLength(300.0f)));
    sibling->MountToParent(parent);
    parent->MarkModifyDone();

    FlushLayoutTask(parent);
    EXPECT_EQ(GetChildSize(frameNode_, 0).Width(), 400.0f);
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);

    // ----currently doesn't work because Animation callbacks run synchronously
    // WillRepeatedly([]() { FlushLayoutTask(parent) })

    pattern_->ShowNext();
    FlushLayoutTask(parent);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_.at(1).startPos, 400.0f);
    EXPECT_EQ(GetChildOffset(frameNode_, 1).GetX(), 400.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());

    // because FlushUITasks are not run, have to manually trigger offset update
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushLayoutTask(parent);
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildOffset(frameNode_, 1).GetX(), 0.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout003
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayout003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateLeft(dimension);
    layoutProperty_->UpdateTop(dimension);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 20.0, 20.0 .
     */
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout004
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateRight(dimension);
    layoutProperty_->UpdateBottom(dimension);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout005
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayout005, TestSize.Level1)
{
    CreateWithArrow();
    auto indicatorGeometryNode = indicatorNode_->GetGeometryNode();
    auto leftArrowGeometryNode = leftArrowNode_->GetGeometryNode();
    auto rightArrowGeometryNode = rightArrowNode_->GetGeometryNode();

    /**
     * @tc.cases: case1. Axis is HORIZONTAL, arrow is in the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(250.0f, 190.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(144.0f, 48.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case2. Axis is HORIZONTAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(15.0f, 240.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(625.0f, 48.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case4. Axis is VERTICAL, arrow is in the switch.
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateShowIndicator(true);
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 50.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 100.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));

    /**
     * @tc.cases: case5. Axis is VERTICAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 15.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 220.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));

    /**
     * @tc.cases: case6. Axis is VERTICAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasure001
 * @tc.desc: Test SwiperLayoutAlgorithm Measure with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithArrow();

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(leftArrowNode_->GetGeometryNode()->GetFrameSize(), SizeF(3.0f, 3.0f));
    EXPECT_EQ(rightArrowNode_->GetGeometryNode()->GetFrameSize(), SizeF(3.0f, 3.0f));
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm001
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperPatternCreateLayoutAlgorithm001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->jumpIndex_ = 0;
    pattern_->targetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = 1.0f;

    /**
     * @tc.steps: step3. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CreateLayoutAlgorithm();
            layoutProperty_->UpdateLoop(false);
        }
        pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackwardItem001
 * @tc.desc: LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutBackwardItem001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t currentIndex = 1;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutBackwardItem.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        currentIndex = 0;
    }

    currentIndex = 1;
    indicatorNode_->tag_ = V2::SWIPER_LEFT_ARROW_ETS_TAG;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
            if (i == 1) {
                indicatorNode_->tag_ = V2::SWIPER_RIGHT_ARROW_ETS_TAG;
                continue;
            }
            indicatorNode_->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
        }
        indicatorNode_->tag_ = V2::SWIPER_ETS_TAG;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward001
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward001
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutBackward001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t endIndex = 1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, endIndex, endPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive001
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmSetInactive001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    CreateDefaultSwiper();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty_);
    float startMainPos = 0.1f;
    float endMainPos = 0.0f;
    int32_t targetIndex = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0;
    swiperLayoutAlgorithm->nextMargin_ = 0.0;

    /**
     * @tc.steps: step2. call SetInactive.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            startMainPos = 3;
        }
        swiperLayoutAlgorithm->prevMargin_ = 1.0;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            endMainPos = 3;
        }
        swiperLayoutAlgorithm->nextMargin_ = 1.0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward002
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(false);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(1);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(0);
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->overScrollFeature_ = false;
            }
            swiperLayoutAlgorithm->overScrollFeature_ = true;
        }
        swiperLayoutAlgorithm->canOverScroll_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward002
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutBackward002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t endIndex = -1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetIsLoop(false);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.clear();
    layoutWrapper.currentChildCount_ = 2;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, endIndex, endPos);
            if (i == 1) {
                endIndex = 1;
                auto indicatorNode_test =
                    FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
                layoutWrapper.childrenMap_.emplace(
                    std::make_pair(1, AceType::MakeRefPtr<LayoutWrapperNode>(
                                          indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
                continue;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
        }
        swiperLayoutAlgorithm->SetIsLoop(false);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmPlaceDigitChild001
 * @tc.desc: PlaceDigitChild
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmPlaceDigitChild001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto indicatorWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(lastLayoutWrapper);
    layoutProperty->UpdateLeft(Dimension(1));
    layoutProperty->UpdateTop(Dimension(1));
    indicatorWrapper->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.parentIdealSize = OptionalSizeF(0.1f, 0.2f);
    indicatorWrapper->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    indicatorWrapper->currentChildCount_ = 1;

    /**
     * @tc.steps: step2. call PlaceDigitChild.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->PlaceDigitChild(indicatorWrapper, layoutProperty);
            if (i == 1) {
                layoutProperty->UpdateDirection(Axis::VERTICAL);
                continue;
            }
            indicatorWrapper->currentChildCount_ = 2;
            layoutProperty->padding_ = std::make_unique<PaddingProperty>();
            layoutProperty->UpdateLeft(Dimension(0));
            layoutProperty->UpdateRight(Dimension(1));
            layoutProperty->UpdateTop(Dimension(0));
            layoutProperty->UpdateBottom(Dimension(1));
        }
        layoutProperty->UpdateRight(Dimension(0));
        layoutProperty->UpdateBottom(Dimension(0));
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001
 * @tc.desc: GetNodeLayoutWrapperByTag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    string tagName = V2::SWIPER_INDICATOR_ETS_TAG;
    layoutWrapper.currentChildCount_ = 0;
    indicatorNode_->pattern_ = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(indicatorNode_->pattern_, nullptr);
    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->indicatorId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->leftButtonId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->rightButtonId_ = 1;

    /**
     * @tc.steps: step2. call GetNodeLayoutWrapperByTag.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (i == 1 && j == 1) {
                AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->indicatorId_.reset();
                AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->leftButtonId_ = 1;
            }
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
                if (i == 0 && j == 1) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->leftButtonId_.reset();
                    continue;
                } else if (i == 1 && j == 0) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->indicatorId_ = 1;
                    continue;
                } else if (i == 1 && j == 1) {
                    break;
                }
                layoutWrapper.currentChildCount_ = 1;
            }
            AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->indicatorId_.reset();
        }
        AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->rightButtonId_.reset();
    }
    AceType::DynamicCast<SwiperPattern>(indicatorNode_->pattern_)->leftButtonId_.reset();
    swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize001
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmGetChildMaxSize001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        0, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty())));
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        1, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, nullptr, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    bool isMainAxis = true;
    swiperLayoutAlgorithm->totalItemCount_ = 3;

    /**
     * @tc.steps: step2. call GetChildMaxSize.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->GetChildMaxSize(&layoutWrapper, isMainAxis);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        isMainAxis = false;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper001
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmMeasureSwiper001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutAlgorithm->totalItemCount_ = 2;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
            if (i == 1) {
                int32_t targetIndex_test = 1;
                swiperLayoutAlgorithm->SetTargetIndex(targetIndex_test);
                continue;
            }
            swiperLayoutAlgorithm->prevMargin_ = 1.0f;
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, -1 }));
        }
        swiperLayoutAlgorithm->isLoop_ = false;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    continue;
                }
                if (i == 1) {
                    break;
                }
                swiperLayoutAlgorithm->jumpIndex_ = 1;
                swiperLayoutAlgorithm->startMainPos_ = 1.0f;
            }
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->jumpIndex_ = 0;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
        swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    }

    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                swiperLayoutAlgorithm->startMainPos_ = 2.0f;
                swiperLayoutAlgorithm->spaceWidth_ = -2.0f;
            }
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            if (i == 1 && j == 1) {
                break;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        swiperLayoutAlgorithm->prevMargin_ = -1.0f;
    }

    swiperLayoutAlgorithm->jumpIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
                if (i == 1 && j == 0) {
                    swiperLayoutAlgorithm->endMainPos_ = -2.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    swiperLayoutAlgorithm->prevMargin_ = 1.0f;
                    continue;
                }
                if (i == 1 && j == 1 && k == 1) {
                    break;
                }
                swiperLayoutAlgorithm->targetIndex_ = 1;
                swiperLayoutAlgorithm->itemPosition_.clear();
            }
            if (i == 1) {
                swiperLayoutAlgorithm->targetIndex_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->targetIndex_ = -1.0f;
    }

    swiperLayoutAlgorithm->targetIndex_.reset();
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
                if (j == 1) {
                    swiperLayoutAlgorithm->itemPosition_.clear();
                    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
                    continue;
                }
                swiperLayoutAlgorithm->itemPosition_.clear();
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 3, 1 }));
                swiperLayoutAlgorithm->currentOffset_ = -1.0f;
            }
            swiperLayoutAlgorithm->itemPosition_.clear();
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 3, 1 }));
        }
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
            if (i == 1) {
                swiperLayoutAlgorithm->endMainPos_ = 1.0f;
                continue;
            }
            swiperLayoutAlgorithm->endMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 3, 1 }));
    }
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    swiperLayoutAlgorithm->currentOffset_ = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
            if (i == 1) {
                swiperLayoutAlgorithm->startMainPos_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 4;
        }
        swiperLayoutAlgorithm->itemPosition_.clear();
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper002
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmMeasureSwiper002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm002
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperPatternCreateLayoutAlgorithm002, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->jumpIndex_.reset();
    pattern_->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CreateLayoutAlgorithm();
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm003
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperPatternCreateLayoutAlgorithm003, TestSize.Level1)
{
    CreateDefaultSwiper();
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->UpdateAnimationProperty(velocity);
        pattern_->isDragging_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper003
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmMeasureSwiper003, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = -1.0f;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem001
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForwardItem001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode_->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward004
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutBackward004, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    indicatorNode_->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t endIndex = -1;
    float endPos = 2.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->startMainPos_ = 0.0f;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
    swiperLayoutAlgorithm->totalItemCount_ = 1;
    swiperLayoutAlgorithm->nextMargin_ = 0.0f;
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;
    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    int32_t currentIndex = 0;
    EXPECT_FALSE(
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, 0.0f, endPos));
    EXPECT_FLOAT_EQ(endPos, 2.0f);
    swiperLayoutAlgorithm->contentMainSize_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->startMainPos_, 0.0f);
    EXPECT_TRUE(GreatNotEqual(endPos, swiperLayoutAlgorithm->startMainPos_));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->contentMainSize_, 1.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward003
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward003, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
        layoutProperty_->UpdateMinSize(Dimension(0));
        layoutProperty_->UpdateDisplayCount(0);
        layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward004
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward004, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    swiperLayoutAlgorithm->SetCanOverScroll(false);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(0));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 1.0f }));

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        layoutProperty_->UpdateMinSize(Dimension(1));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->endMainPos_, 480.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward005
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward005, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    auto currentIndex = startIndex - 1;
    auto result = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper, layoutConstraint, currentIndex, currentStartPos, currentEndPos);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
        startIndex = 2;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward006
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward006, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 1.0f }));
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
            swiperLayoutAlgorithm->endMainPos_ = 1.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_.reset();
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward007
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForward007, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode_->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0f;
    swiperLayoutAlgorithm->contentMainSize_ = 0.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, startIndex, startPos);
    EXPECT_FALSE(swiperLayoutAlgorithm->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure001
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperPatternAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->mainSizeIsMeasured_);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(frameNode_->isConstraintNotChanged_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout006
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayout006, TestSize.Level1)
{
    CreateWithArrow();
    auto indicatorGeometryNode = indicatorNode_->GetGeometryNode();
    indicatorGeometryNode->SetFrameOffset(OffsetF(250.0f, 190.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(144.0f, 48.0f));

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    FlushLayoutTask(frameNode_);

    pattern_->leftButtonId_.emplace(1);
    pattern_->rightButtonId_.emplace(1);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem002
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmLayoutForwardItem002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorNode_ =
        FrameNode::GetOrCreateFrameNode("test", 1, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode_->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem in different layoutWrapper and make the return value false.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto swiperNode2 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_RIGHT_ARROW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper2 = LayoutWrapperNode(swiperNode2, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, currentIndex, endPos, startPos);
    auto result2 =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result2);
    currentIndex = 0;
    auto swiperNode3 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_LEFT_ARROW_ETS_TAG, 3, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper3 = LayoutWrapperNode(swiperNode3, geometryNode, swiperNode3->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper3, layoutConstraint, currentIndex, endPos, startPos);
    auto result3 =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper3, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result3);
    currentIndex = 0;
    auto swiperNode4 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, 4, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper4 = LayoutWrapperNode(swiperNode4, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper4, layoutConstraint, currentIndex, endPos, startPos);
    auto result4 =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result4);

    /**
     * @tc.steps: step3. call LayoutForwardItem in different layoutWrapper and make the return value ture.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto wrapper = layoutWrapper.GetOrCreateChildByIndex(1);
    auto layoutProperty = wrapper->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    auto result =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_NE(result, true);
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize002
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmGetChildMaxSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateDefaultSwiper();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());

    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        0, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty())));
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        1, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_, nullptr, indicatorNode_->GetLayoutProperty())));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);

    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    bool isMainAxis = true;
    swiperLayoutAlgorithm->totalItemCount_ = 3;

    /**
     * @tc.steps: step2. call GetChildMaxSize.
     * @tc.expected: GetChildMaxSize->itemPosition_ not empty
     */
    swiperLayoutAlgorithm->itemPosition_.clear();
    swiperLayoutAlgorithm->GetChildMaxSize(&layoutWrapper, isMainAxis);
    EXPECT_TRUE(swiperLayoutAlgorithm->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure003
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperPatternAlgorithmMeasure003, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->mainSizeIsMeasured_);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(frameNode_->isConstraintNotChanged_);

    /**
     * @tc.steps: step1. Set totalItemCount_ Equal to 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_== 0 condition is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 0;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ == 0);

    /**
     * @tc.steps: step1. Set totalItem Count_ Greater than 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_ Condition greater than 0 is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 10;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ > 0);
}

/**
 * @tc.name: ItemWidth001
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, ItemWidth001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemWidth002
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, ItemWidth002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight001
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, ItemHeight001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight002
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, ItemHeight002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth001
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SelectedItemWidth001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth002
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SelectedItemWidth002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight001
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SelectedItemHeight001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight002
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SelectedItemHeight002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}
} // namespace OHOS::Ace::NG
