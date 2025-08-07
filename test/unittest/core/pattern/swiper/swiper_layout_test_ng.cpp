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

/**
 * @tc.name: CalcCurrentPageStatusOnRTL001
 * @tc.desc: Test CalcCurrentPageStatusOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, CalcCurrentPageStatusOnRTL001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    pattern_->itemPosition_.clear();
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -240.0f;
    swiperItemInfo1.endPos = 240.0f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = 240.0f;
    swiperItemInfo2.endPos = 720.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo2));
    auto additionalOffset = 0.0f;
    auto isTouchBottom = false;
    pattern_->currentFirstIndex_ = 0;
    auto pageRate = pattern_->CalcCurrentPageStatusOnRTL(additionalOffset, isTouchBottom).first;
    EXPECT_EQ(pageRate, -0.5f);

    isTouchBottom = true;
    pageRate = pattern_->CalcCurrentPageStatusOnRTL(additionalOffset, isTouchBottom).first;
    EXPECT_EQ(pageRate, -0.5f);

    layoutProperty_->UpdateItemSpace(Dimension(50.0f, DimensionUnit::PX));
    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -240.0f;
    swiperItemInfo1.endPos = 240.0f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    swiperItemInfo2.startPos = 290.0f;
    swiperItemInfo2.endPos = 770.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo2));
    pageRate = pattern_->CalcCurrentPageStatusOnRTL(additionalOffset, isTouchBottom).first;
    EXPECT_EQ(pageRate, -0.5f);
}

/**
 * @tc.name: CalcCurrentPageStatusOnRTL002
 * @tc.desc: Test CalcCurrentPageStatusOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, CalcCurrentPageStatusOnRTL002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. The precision is thousandths.
     */
    pattern_->itemPosition_.clear();
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = 479.999f;
    swiperItemInfo1.endPos = 959.999f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    auto additionalOffset = 0.0f;
    auto isTouchBottom = false;
    pattern_->currentFirstIndex_ = -1;
    auto firstIndex = pattern_->CalcCurrentPageStatusOnRTL(additionalOffset, isTouchBottom).second;
    EXPECT_EQ(firstIndex, -1);

    /**
     * @tc.steps: step3. The precision is percentile.
     */
    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = 479.98f;
    swiperItemInfo1.endPos = 959.98f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    pattern_->currentFirstIndex_ = -1;
    firstIndex = pattern_->CalcCurrentPageStatusOnRTL(additionalOffset, isTouchBottom).second;
    EXPECT_EQ(firstIndex, 0);
}

/**
 * @tc.name: CalcCurrentPageStatus001
 * @tc.desc: Test CalcCurrentPageStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, CalcCurrentPageStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. The precision is thousandths.
     */
    pattern_->itemPosition_.clear();
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -479.999f;
    swiperItemInfo1.endPos = 0.001f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    auto additionalOffset = 0.0f;
    pattern_->currentFirstIndex_ = -1;
    auto firstIndex = pattern_->CalcCurrentPageStatus(additionalOffset).second;
    EXPECT_EQ(firstIndex, -1);

    /**
     * @tc.steps: step3. The precision is percentile.
     */
    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -479.98f;
    swiperItemInfo1.endPos = 0.02f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    pattern_->currentFirstIndex_ = -1;
    firstIndex = pattern_->CalcCurrentPageStatus(additionalOffset).second;
    EXPECT_EQ(firstIndex, 0);
}

/**
 * @tc.name: AdjustOffsetOnBackward001
 * @tc.desc: Test AdjustOffsetOnBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnBackward001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->canOverScroll_ = false;
    swiperLayoutAlgorithm->currentOffset_ = 0.f;
    float currentStartPos = 2.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentStartPos);
    EXPECT_EQ(swiperLayoutAlgorithm->currentOffset_, 2.f);
}

/**
 * @tc.name: AdjustOffsetOnBackward002
 * @tc.desc: Test AdjustOffsetOnBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnBackward002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->jumpIndex_ = 10;
    swiperLayoutAlgorithm->currentOffset_ = 0.f;
    float currentStartPos = 2.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentStartPos);
    EXPECT_EQ(swiperLayoutAlgorithm->currentOffset_, 2.f);
}

/**
 * @tc.name: AdjustOffsetOnBackward003
 * @tc.desc: Test AdjustOffsetOnBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnBackward003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->jumpIndex_ = 10;
    swiperLayoutAlgorithm->currentOffset_ = 0.f;
    swiperLayoutAlgorithm->contentMainSize_ = -10.f;
    swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 10;
    float currentStartPos = 20.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentStartPos);
    EXPECT_EQ(swiperLayoutAlgorithm->endMainPos_, 10.f);
}

/**
 * @tc.name: AdjustOffsetOnBackward004
 * @tc.desc: Test AdjustOffsetOnBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnBackward004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->jumpIndex_ = 10;
    swiperLayoutAlgorithm->currentOffset_ = 0.f;
    swiperLayoutAlgorithm->contentMainSize_ = -10.f;
    swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
    swiperLayoutAlgorithm->totalItemCount_ = 10;
    float currentStartPos = 20.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentStartPos);
    EXPECT_EQ(swiperLayoutAlgorithm->endMainPos_, 10.f);
}

/**
 * @tc.name: AdjustOffsetOnBackward005
 * @tc.desc: Test AdjustOffsetOnBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnBackward005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->jumpIndex_ = 10;
    swiperLayoutAlgorithm->currentOffset_ = 0.f;
    swiperLayoutAlgorithm->contentMainSize_ = -10.f;
    swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    float currentStartPos = 20.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentStartPos);
    EXPECT_EQ(swiperLayoutAlgorithm->endMainPos_, 10.f);
}

/**
 * @tc.name: AdjustOffsetOnForward001
 * @tc.desc: Test AdjustOffsetOnForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnForward001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->contentMainSize_ = 10.f;
    swiperLayoutAlgorithm->canOverScroll_ = false;
    float currentEndPos = 100.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentEndPos);
    EXPECT_EQ(swiperLayoutAlgorithm->currentOffset_, 100);
}

/**
 * @tc.name: AdjustOffsetOnForward002
 * @tc.desc: Test AdjustOffsetOnForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnForward002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->contentMainSize_ = 10.f;
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->jumpIndex_ = 10;
    float currentEndPos = 100.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentEndPos);
    EXPECT_EQ(swiperLayoutAlgorithm->currentOffset_, 100);
}

/**
 * @tc.name: AdjustOffsetOnForward003
 * @tc.desc: Test AdjustOffsetOnForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnForward003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->contentMainSize_ = 100.f;
    swiperLayoutAlgorithm->canOverScroll_ = true;
    swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
    float currentEndPos = 30.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentEndPos);
    EXPECT_EQ(swiperLayoutAlgorithm->startMainPos_, 30);
    EXPECT_EQ(swiperLayoutAlgorithm->contentMainSize_, 100);
}

/**
 * @tc.name: AdjustOffsetOnForward004
 * @tc.desc: Test AdjustOffsetOnForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustOffsetOnForward004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->contentMainSize_ = 100.f;
    swiperLayoutAlgorithm->canOverScroll_ = false;
    swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
    float currentEndPos = 30.0f;
    swiperLayoutAlgorithm->AdjustOffsetOnBackward(currentEndPos);
    EXPECT_EQ(swiperLayoutAlgorithm->startMainPos_, 30);
    EXPECT_EQ(swiperLayoutAlgorithm->contentMainSize_, 100);
}

/**
 * @tc.name: AdjustStartInfoOnSwipeByGroup001
 * @tc.desc: Test AdjustStartInfoOnSwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustStartInfoOnSwipeByGroup001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->swipeByGroup_ = true;
    swiperLayoutAlgorithm->isFrameAnimation_ = true;
    int32_t startIndex = 0;
    int32_t startIndexInVisibleWindow = 0;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->AdjustStartInfoOnSwipeByGroup(startIndex, itemPosition, startIndexInVisibleWindow, startPos);
    EXPECT_EQ(startPos, 0.f);
}

/**
 * @tc.name: AdjustStartInfoOnSwipeByGroup002
 * @tc.desc: Test AdjustStartInfoOnSwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustStartInfoOnSwipeByGroup002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 10;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->swipeByGroup_ = true;
    swiperLayoutAlgorithm->isFrameAnimation_ = false;
    int32_t startIndex = 3;
    int32_t startIndexInVisibleWindow = 0;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->AdjustStartInfoOnSwipeByGroup(startIndex, itemPosition, startIndexInVisibleWindow, startPos);
    EXPECT_EQ(startPos, 0.f);
}

/**
 * @tc.name: AdjustItemPositionOnCachedShow001
 * @tc.desc: Test AdjustItemPositionOnCachedShow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustItemPositionOnCachedShow001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->cachedShow_ = true;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->cachedStartIndex_ = 1;
    swiperLayoutAlgorithm->AdjustItemPositionOnCachedShow();
    EXPECT_EQ(swiperLayoutAlgorithm->itemPosition_.size(), 0);
}

/**
 * @tc.name: AdjustItemPositionOnCachedShow002
 * @tc.desc: Test AdjustItemPositionOnCachedShow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, AdjustItemPositionOnCachedShow002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->cachedShow_ = true;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->cachedStartIndex_ = 0;
    swiperLayoutAlgorithm->cachedEndIndex_ = 0;
    swiperLayoutAlgorithm->AdjustItemPositionOnCachedShow();
    EXPECT_EQ(swiperLayoutAlgorithm->itemPosition_.size(), 1);
}

/**
 * @tc.name: SwiperLayoutGetHeightForDigit002
 * @tc.desc: Test SwiperLayoutGetHeightForDigit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutGetHeightForDigit002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF { 10.f, 20.f });
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->currentIndex_ = 50.f;
    float height = swiperLayoutAlgorithm->GetCurrentFirstIndexInWindow(&layoutWrapper);
    EXPECT_EQ(height, 50.f);
}

/**
 * @tc.name: GetCurrentLastIndexInWindow001
 * @tc.desc: Test GetCurrentLastIndexInWindow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, GetCurrentLastIndexInWindow001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF { 10.f, 20.f });
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm));
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->currentIndex_ = 50.f;
    float height = swiperLayoutAlgorithm->GetCurrentLastIndexInWindow(&layoutWrapper);
    EXPECT_EQ(height, 50.f);
}

/**
 * @tc.name: LayoutBackwardItem001
 * @tc.desc: Test LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutBackwardItem001, TestSize.Level1)
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
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutBackwardItem002
 * @tc.desc: Test LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutBackwardItem002, TestSize.Level1)
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
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->mainSizeIsMeasured_ = false;
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutBackwardItem003
 * @tc.desc: Test LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutBackwardItem003, TestSize.Level1)
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
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(0, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->mainSizeIsMeasured_ = false;
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: LayoutForwardItem001
 * @tc.desc: Test LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutForwardItem001, TestSize.Level1)
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
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutForwardItem002
 * @tc.desc: Test LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutForwardItem002, TestSize.Level1)
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
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(0, item1));
    itemPosition.insert(std::make_pair(1, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->mainSizeIsMeasured_ = false;
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutForwardItem003
 * @tc.desc: Test LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutForwardItem003, TestSize.Level1)
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
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(2, item1));
    itemPosition.insert(std::make_pair(2, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->mainSizeIsMeasured_ = false;
    swiperLayoutAlgorithm->hasCachedCapture_ = false;
    swiperLayoutAlgorithm->isLoop_ = true;
    swiperLayoutAlgorithm->totalItemCount_ = 20;
    swiperLayoutAlgorithm->isMeasureOneMoreItem_ = true;
    int32_t currentIndex = 1;
    float endPos = 0.0f;
    float startPos = 0.0f;
    auto result =
        swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, currentIndex, endPos, startPos);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive002
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, SwiperLayoutAlgorithmSetInactive002, TestSize.Level1)
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
    float endMainPos = 10.0f;
    swiperLayoutAlgorithm->measured_ = true;
    swiperLayoutAlgorithm->currentOffset_ = 0.0f;
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
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, std::nullopt);
            startMainPos = 3;
        }
        swiperLayoutAlgorithm->prevMargin_ = 1.0;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, std::nullopt);
            endMainPos = 3;
        }
        swiperLayoutAlgorithm->nextMargin_ = 1.0;
    }
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: GetLoopIndex001
 * @tc.desc: GetLoopIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, GetLoopIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(swiperLayoutAlgorithm, nullptr);
    swiperLayoutAlgorithm->totalItemCount_ = 0;
    int32_t originalIndex = 10;
    int32_t result = swiperLayoutAlgorithm->GetLoopIndex(originalIndex);
    EXPECT_EQ(result, 10);
}

/**
 * @tc.name: CaptureMeasure001
 * @tc.desc: CaptureMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, CaptureMeasure001, TestSize.Level1)
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
    float sizeTmp = 480.f;
    layoutConstraint.selfIdealSize = OptionalSizeF(sizeTmp, sizeTmp);
    layoutConstraint.maxSize = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.percentReference = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.parentIdealSize.SetSize(SizeF(sizeTmp, sizeTmp));

    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    auto nodeId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node1 = FrameNode::CreateFrameNode("node", nodeId1, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item1;
    item1.startPos = 0;
    item1.endPos = 20;
    item1.node = node1;
    auto nodeId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto node2 = FrameNode::CreateFrameNode("node", nodeId2, AceType::MakeRefPtr<ArcSwiperPattern>());
    SwiperItemInfo item2;
    item2.startPos = 21;
    item2.endPos = 40;
    item2.node = node2;
    itemPosition.insert(std::make_pair(2, item1));
    itemPosition.insert(std::make_pair(2, item2));
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->hasCachedCapture_ = true;
    swiperLayoutAlgorithm->isCaptureReverse_ = true;
    swiperLayoutAlgorithm->CaptureMeasure(&layoutWrapper, layoutConstraint);
    EXPECT_EQ(pattern_->contentMainSize_, sizeTmp);
}

/**
 * @tc.name: CaptureMeasure002
 * @tc.desc: CaptureMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, CaptureMeasure002, TestSize.Level1)
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
    float sizeTmp = 480.f;
    layoutConstraint.selfIdealSize = OptionalSizeF(sizeTmp, sizeTmp);
    layoutConstraint.maxSize = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.percentReference = SizeF(sizeTmp, sizeTmp);
    layoutConstraint.parentIdealSize.SetSize(SizeF(sizeTmp, sizeTmp));

    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    SwiperLayoutAlgorithm::PositionMap itemPosition;
    swiperLayoutAlgorithm->itemPosition_ = itemPosition;
    swiperLayoutAlgorithm->hasCachedCapture_ = true;
    swiperLayoutAlgorithm->CaptureMeasure(&layoutWrapper, layoutConstraint);
    EXPECT_EQ(pattern_->contentMainSize_, sizeTmp);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    auto swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        swiperInner = CreateSwiper([this](SwiperModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(swiper, nullptr);
    CreateLayoutTask(swiper);

    // Expect swiper's width is 500, height is 300 land offset is [0.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    auto swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        swiperInner = CreateSwiper([this](SwiperModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(swiper, nullptr);
    CreateLayoutTask(swiper);

    // Expect swiper's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(460.0f, 260.0f));
    EXPECT_EQ(offset1, OffsetF(20.0f, 20.0f));
}

/**
 * @tc.name: LayoutPolicyTest003
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    RefPtr<FrameNode> swiperOutter;
    RefPtr<FrameNode> swiper;
    swiperOutter = CreateSwiper([this, &swiper, &swiperInner](SwiperModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f));
        ViewAbstract::SetHeight(CalcLength(500.0f));
        swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            swiperInner = CreateSwiper([this](SwiperModelNG model) {
                ViewAbstract::SetWidth(CalcLength(100.0f));
                ViewAbstract::SetHeight(CalcLength(100.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(swiperOutter, nullptr);
    CreateLayoutTask(swiperOutter);

    // Expect swiperOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = swiperOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(500.0f, 500.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect swiper's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 500.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(500.0f, 100.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    auto swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        swiperInner = CreateSwiper([this](SwiperModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
        });
    });
    ASSERT_NE(swiper, nullptr);
    CreateLayoutTask(swiper);

    // Expect swiper's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting wrapContent and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest005, TestSize.Level1)
{
/**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    RefPtr<FrameNode> swiperOutter;
    RefPtr<FrameNode> swiper;
    swiperOutter = CreateSwiper([this, &swiper, &swiperInner](SwiperModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            swiperInner = CreateSwiper([this](SwiperModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(swiperOutter, nullptr);
    CreateLayoutTask(swiperOutter);

    // Expect swiperOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = swiperOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect swiper's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting wrapContent and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, LayoutPolicyTest006, TestSize.Level1)
{
/**
     * @tc.steps: step1. Create default swiper
     */
    RefPtr<FrameNode> swiperInner;
    RefPtr<FrameNode> swiperOutter;
    RefPtr<FrameNode> swiper;
    swiperOutter = CreateSwiper([this, &swiper, &swiperInner](SwiperModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        swiper = CreateSwiper([this, &swiperInner](SwiperModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            swiperInner = CreateSwiper([this](SwiperModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
            });
        });
    });
    ASSERT_NE(swiperOutter, nullptr);
    CreateLayoutTask(swiperOutter);

    // Expect swiperOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = swiperOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect swiper's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = swiper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect swiperInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = swiperInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}
} // namespace OHOS::Ace::NG
