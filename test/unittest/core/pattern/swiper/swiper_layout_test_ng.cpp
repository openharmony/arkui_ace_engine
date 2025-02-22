/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF()));

    /**
     * @tc.steps: step2. Add a item
     */
    TextModelNG textModel;
    textModel.Create(u"text");
    RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    currentFrameNode->MountToParent(frameNode_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF()));

    /**
     * @tc.steps: step3. Set size
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SWIPER_HEIGHT));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(SWIPER_WIDTH, SWIPER_HEIGHT)));

    /**
     * @tc.steps: step4. Change size
     * @tc.expected: swiper size are changed
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(300.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(500.f));
    FlushUITasks();
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
    EXPECT_EQ(pattern_->RealTotalCount(), 5);
    EXPECT_EQ(pattern_->itemPosition_.size(), 5);

    ChangeIndex(1);
    EXPECT_TRUE(CurrentIndex(1));
    const float itemWidth1 = (SWIPER_WIDTH - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth1);

    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(1000.0f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(300.0f));
    FlushUITasks();
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

    FlushUITasks();

    ChangeIndex(1);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    const float itemWidth1 = (400.0f - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth1);

    parent->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(800.0f), CalcLength(300.0f)));
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 800.0f);
    const float itemWidth2 = (800.0f - 2 * 20.0f) / 3.0f;
    CheckItems(0, 3, 20.0f, itemWidth2);
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive001
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmSetInactive001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    EXPECT_TRUE(frameNode_);
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

    FlushUITasks();
    EXPECT_EQ(GetChildSize(frameNode_, 0).Width(), 400.0f);
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);

    // ----currently doesn't work because Animation callbacks run synchronously
    // WillRepeatedly([]() { FlushUITasks() })

    pattern_->ShowNext();
    EXPECT_EQ(pattern_->currentIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_.at(1).startPos, 0);
    EXPECT_EQ(GetChildX(frameNode_, 0), -400);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0);
    EXPECT_EQ(GetChildWidth(frameNode_, 2), 0);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());

    // because FlushUITasks are not run, have to manually trigger offset update
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 0), -400);
    EXPECT_EQ(GetChildX(frameNode_, 1), -400);
    EXPECT_EQ(GetChildX(frameNode_, 2), 0);
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
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case2. Axis is HORIZONTAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(15.0f, 240.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(625.0f, 48.0f));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(8.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(448.0f, 388.0f)));

    /**
     * @tc.cases: case4. Axis is VERTICAL, arrow is in the switch.
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateShowIndicator(true);
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 50.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 100.0f));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));

    /**
     * @tc.cases: case5. Axis is VERTICAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 15.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 220.0f));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));

    /**
     * @tc.cases: case6. Axis is VERTICAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 8.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 448.0f)));
}

/**
 * @tc.name: SwiperLayoutSkipMeasure001
 * @tc.desc: Test skip measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutSkipMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();
    /**
     * @tc.steps: step2. contentMainSize need to be transmitted back to the pattern
     */
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));

    LayoutConstraintF layoutConstraint;
    float sizeTmp = 720.f;
    layoutConstraint.selfIdealSize = OptionalSizeF(sizeTmp, sizeTmp);
    layoutConstraint.maxSize = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.percentReference = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.parentIdealSize.SetSize(SizeF(sizeTmp, sizeTmp));

    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    swiperLayoutAlgorithm->mainSizeIsMeasured_ = false;
    swiperLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(pattern_->contentMainSize_, sizeTmp);
}

/**
 * @tc.name: SwiperLayoutGetHeightForDigit001
 * @tc.desc: Test GetHeightForDigit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutGetHeightForDigit001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF{10.f, 20.f});
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    float height = swiperLayoutAlgorithm->GetHeightForDigit(&layoutWrapper, geometryNode->GetFrameSize().Height());
    EXPECT_EQ(height, 20.f);
}
} // namespace OHOS::Ace::NG
