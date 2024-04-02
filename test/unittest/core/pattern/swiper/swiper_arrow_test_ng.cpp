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

class SwiperArrowTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: ArrowOnModifyDone001
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ArrowOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: leftArrowPattern->isFirstCreate_ is false.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);
}

/**
 * @tc.name: ArrowOnModifyDone002
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ArrowOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    leftSwiperArrowLayoutProperty->UpdateIsShowBackground(true);
    leftSwiperArrowLayoutProperty->UpdateEnabled(false);
    leftSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    leftArrowPattern->OnModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: UpdateArrowContent001
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG.
     */
    leftArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
}

/**
 * @tc.name: UpdateArrowContent002
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(rightArrowPattern, nullptr);
    auto rightSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(rightArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(rightSwiperArrowLayoutProperty, nullptr);
    rightSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    rightSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    rightSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    rightSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    rightArrowPattern->OnModifyDone();
    EXPECT_FALSE(rightArrowPattern->isFirstCreate_);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG.
     */
    rightArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: SwiperPatternArrowHover001
 * @tc.desc: ArrowHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, SwiperPatternArrowHover001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool hoverFlag = true;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    /**
     * @tc.steps: step2. call ArrowHover.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ArrowHover(hoverFlag);
            if (i == 1) {
                pattern_->leftButtonId_.reset();
            }
            pattern_->leftButtonId_ = 1;
        }
        pattern_->rightButtonId_ = 1;
    }
}

/**
 * @tc.name: SwiperPatternCheckAndSetArrowHoverState001
 * @tc.desc: CheckAndSetArrowHoverState
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, SwiperPatternCheckAndSetArrowHoverState001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    auto mousePoint = PointF(0.0f, 0.0f);
   
    /**
     * @tc.steps: step2. call CheckAndSetArrowHoverState.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->CheckAndSetArrowHoverState(mousePoint);
                if (j == 1) {
                    pattern_->leftButtonId_ = 1;
                    continue;
                }
                pattern_->leftButtonId_.reset();
            }
            pattern_->rightButtonId_.reset();
        }
        pattern_->indicatorId_.reset();
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    frameNode_->AddChild(leftArrowNode);
    frameNode_->AddChild(indicatorNode);
    frameNode_->AddChild(rightArrowNode);
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateIsSidebarMiddle(true);
    pattern_->CheckAndSetArrowHoverState(mousePoint);
    layoutProperty_->UpdateIsSidebarMiddle(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CheckAndSetArrowHoverState(mousePoint);
            if (i == 1) {
                pattern_->currentIndex_ = 1;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    for (int i = 0; i <= 1; i++) {
        pattern_->CheckAndSetArrowHoverState(mousePoint);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperInitArrow001
 * @tc.desc: Test SwiperPattern SwiperInitArrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, SwiperInitArrow001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    layoutProperty_->UpdateDisplayArrow(true);
    layoutProperty_->UpdateHoverShow(true);
    layoutProperty_->UpdateIsShowBackground(true);
    layoutProperty_->UpdateBackgroundSize(Dimension(1));
    layoutProperty_->UpdateBackgroundColor(Color(1));
    layoutProperty_->UpdateArrowSize(Dimension(1));
    layoutProperty_->UpdateArrowColor(Color(1));
    layoutProperty_->UpdateIsSidebarMiddle(true);

    /**
     * @tc.steps: step3. call InitArrow.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->InitArrow();
            if (i == 1) {
                break;
            }
            pattern_->leftButtonId_ = 1;
        }
        layoutProperty_->UpdateDisplayArrow(false);
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->InitArrow();
    EXPECT_TRUE(pattern_->HasLeftButtonNode());
    EXPECT_TRUE(pattern_->HasRightButtonNode());
}

/**
 * @tc.name: SetButtonVisible001
 * @tc.desc: Test SetButtonVisible
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, SetButtonVisible001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    /**
     * @tc.cases: case3.1 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftArrowPattern->index_ = 1;
    leftSwiperArrowLayoutProperty->UpdateHoverShow(true);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.2 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftSwiperArrowLayoutProperty->UpdateHoverShow(false);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.3 Selected point is first point and loop value is false RenderContext.SetVisible() will be
     * called..
     */
    leftArrowPattern->index_ = 0;
    leftSwiperArrowLayoutProperty->UpdateLoop(false);
    leftArrowPattern->SetButtonVisible(true);

    /**
     * @tc.cases: case3.4 Selected point is first point and loop value is true RenderContext.SetVisible() will be
     * called.
     */
    leftSwiperArrowLayoutProperty->UpdateLoop(true);
    leftArrowPattern->SetButtonVisible(false);
}

/**
 * @tc.name: ButtonOnHover001
 * @tc.desc: Test ButtonOnHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ButtonOnHover001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, false);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, false);
}
} // namespace OHOS::Ace::NG
