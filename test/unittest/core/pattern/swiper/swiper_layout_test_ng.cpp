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

namespace OHOS::Ace::NG {

namespace {} // namespace

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
    GetInstance();
    FlushLayoutTask(frameNode_);
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

/**
 * @tc.name: Arrow001
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, Arrow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show default value arrow
     * @tc.expected: check properties
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperArrowParameters.isShowBackground = false;
    swiperArrowParameters.isSidebarMiddle = false;
    swiperArrowParameters.backgroundSize = Dimension(24.f);
    swiperArrowParameters.backgroundColor = Color::FromString("#00000000");
    swiperArrowParameters.arrowSize = Dimension(18.f);
    swiperArrowParameters.arrowColor = Color::FromString("#182431");

    /**
     * @tc.steps: step2. HORIZONTAL and isShowIndicatorArrow
     * @tc.expected: check arrow rect
     */
    CreateWithItem([=](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(swiperArrowParameters);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowLayoutProperty = leftArrowNode->GetLayoutProperty<SwiperArrowLayoutProperty>();
    EXPECT_FALSE(leftArrowLayoutProperty->GetIsShowBackgroundValue());
    EXPECT_FALSE(leftArrowLayoutProperty->GetIsSidebarMiddleValue());
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundSizeValue(), Dimension(24.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundColorValue(), Color::FromString("#00000000"));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowSizeValue(), Dimension(18.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowColorValue(), Color::FromString("#182431"));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 5), RectF(201.f, 772.01f, 24.f, 24.f)));
}

/**
 * @tc.name: Arrow002
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, Arrow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show set value arrow
     * @tc.expected: check properties
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.isSidebarMiddle = true;
    swiperArrowParameters.backgroundSize = Dimension(32.f);
    swiperArrowParameters.backgroundColor = Color::FromString("#19182431");
    swiperArrowParameters.arrowSize = Dimension(24.f);
    swiperArrowParameters.arrowColor = Color::GREEN;
    
    /**
     * @tc.steps: step2. HORIZONTAL and !isShowIndicatorArrow
     * @tc.expected: check arrow rect
     */
    CreateWithItem([=](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(swiperArrowParameters);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto leftArrowLayoutProperty = rightArrowNode->GetLayoutProperty<SwiperArrowLayoutProperty>();
    EXPECT_TRUE(leftArrowLayoutProperty->GetIsShowBackgroundValue());
    EXPECT_TRUE(leftArrowLayoutProperty->GetIsSidebarMiddleValue());
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundSizeValue(), Dimension(32.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundColorValue(), Color::FromString("#19182431"));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowSizeValue(), Dimension(24.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowColorValue(), Color::GREEN);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6), RectF(448.f, 384.f, 32.f, 32.f)));
}

/**
 * @tc.name: Arrow003
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, Arrow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show set value arrow
     * @tc.expected: check properties
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.isSidebarMiddle = false;
    swiperArrowParameters.backgroundSize = Dimension(32.f);
    swiperArrowParameters.backgroundColor = Color::FromString("#19182431");
    swiperArrowParameters.arrowSize = Dimension(24.f);
    swiperArrowParameters.arrowColor = Color::GREEN;
    
    /**
     * @tc.steps: step2. VERTICAL and isShowIndicatorArrow
     * @tc.expected: check arrow rect
     */
    CreateWithItem([=](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(swiperArrowParameters);
    });
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 5), RectF(448.01f, 353.f, 32.f, 32.f)));
}

/**
 * @tc.name: Arrow004
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperLayoutTestNg, Arrow004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show set value arrow
     * @tc.expected: check properties
     */
    SwiperArrowParameters swiperArrowParameters;
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.isSidebarMiddle = true;
    swiperArrowParameters.backgroundSize = Dimension(32.f);
    swiperArrowParameters.backgroundColor = Color::FromString("#19182431");
    swiperArrowParameters.arrowSize = Dimension(24.f);
    swiperArrowParameters.arrowColor = Color::GREEN;
    
    /**
     * @tc.steps: step2. VERTICAL and !isShowIndicatorArrow
     * @tc.expected: check arrow rect
     */
    CreateWithItem([=](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(swiperArrowParameters);
    });
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6), RectF(224.f, 768.f, 32.f, 32.f)));
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
    CreateWithItem(
        [](SwiperModelNG model) {
            model.SetDirection(Axis::HORIZONTAL);
            model.SetDisplayCount(3);
            model.SetPreviousMargin(Dimension(20));
            model.SetNextMargin(Dimension(20));
        },
        5);
    EXPECT_EQ(pattern_->itemPosition_.size(), 4);

    pattern_->SwipeToWithoutAnimation(1);
    FlushLayoutTask(frameNode_);
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
    CreateWithItem(
        [](SwiperModelNG model) {
            model.SetDirection(Axis::HORIZONTAL);
            model.SetDisplayCount(3);
            model.SetPreviousMargin(Dimension(20));
            model.SetNextMargin(Dimension(20));
        },
        5);
    layoutProperty_->ClearUserDefinedIdealSize(true, true);

    auto parent = FrameNode::CreateFrameNode("parent", -1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    parent->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(300.0f)));
    frameNode_->MountToParent(parent);

    FlushLayoutTask(parent);

    pattern_->SwipeToWithoutAnimation(1);
    FlushLayoutTask(frameNode_);
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
    CreateWithItem(
        [](SwiperModelNG model) {
            model.SetDirection(Axis::HORIZONTAL);
            model.SetDisplayCount(1);
        },
        5);
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

    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(3);
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
} // namespace OHOS::Ace::NG
