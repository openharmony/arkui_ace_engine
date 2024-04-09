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
    ImageSourceInfo GetImageInfo(const RefPtr<FrameNode>& arrowNode);
};

ImageSourceInfo SwiperArrowTestNg::GetImageInfo(const RefPtr<FrameNode>& arrowNode)
{
    auto buttonNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    auto imageNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    return imageSourceInfo.value();
}

/**
 * @tc.name: UpdateArrowContent001
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set arrow
     * @tc.expected: Vertify imageInfo
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto leftImageInfo = GetImageInfo(leftArrowNode);
    auto rightImageInfo = GetImageInfo(rightArrowNode);
    EXPECT_EQ(leftImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
    EXPECT_EQ(rightImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
    EXPECT_EQ(leftImageInfo.GetFillColor(), ARROW_PARAMETERS.arrowColor.value());
    EXPECT_EQ(leftImageInfo.GetFillColor(), rightImageInfo.GetFillColor());
}

/**
 * @tc.name: UpdateArrowContent002
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set VERTICAL and enabled:false
     * @tc.expected: Vertify imageInfo
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
        model.SetEnabled(false);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto leftImageInfo = GetImageInfo(leftArrowNode);
    auto rightImageInfo = GetImageInfo(rightArrowNode);
    EXPECT_EQ(leftImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG);
    EXPECT_EQ(rightImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    EXPECT_EQ(leftImageInfo.GetFillColor(), ARROW_PARAMETERS.arrowColor.value().BlendOpacity(ARROW_DISABLED_ALPHA));
    EXPECT_EQ(leftImageInfo.GetFillColor(), rightImageInfo.GetFillColor());
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
 * @tc.name: ClickArrow001
 * @tc.desc: Click arrow directly
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftMockRenderContext = AceType::DynamicCast<MockRenderContext>(leftButtonNode->renderContext_);
    EXPECT_TRUE(leftMockRenderContext->isVisible_);

    /**
     * @tc.steps: step1. Touch down button
     * @tc.expected: change bgColor to clickColor
     */
    leftArrowPattern->ButtonTouchEvent(leftButtonNode, TouchType::DOWN);
    EXPECT_EQ(leftMockRenderContext->blendColor_, CLICK_ARROW_COLOR);

    /**
     * @tc.steps: step2. Touch up button
     * @tc.expected: reset bgColor
     */
    leftArrowPattern->ButtonTouchEvent(leftButtonNode, TouchType::UP);
    EXPECT_EQ(leftMockRenderContext->blendColor_, Color::TRANSPARENT);

    /**
     * @tc.steps: step3. Click button
     * @tc.expected: Swipe to pre item
     */
    leftArrowPattern->ButtonClickEvent();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: ClickArrow002
 * @tc.desc: Hover and click arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    auto rightMockRenderContext = AceType::DynamicCast<MockRenderContext>(rightButtonNode->renderContext_);
    EXPECT_TRUE(rightMockRenderContext->isVisible_);

    /**
     * @tc.steps: step1. Not hover button
     * @tc.expected: BgColor is default
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, false);
    EXPECT_EQ(rightMockRenderContext->blendColor_, Color::TRANSPARENT);

    /**
     * @tc.steps: step2. Hover button
     * @tc.expected: change bgColor to hoverColor
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, true);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR);

    /**
     * @tc.steps: step3. Touch down button
     * @tc.expected: change bgColor to hoverColor+clickColor
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::DOWN);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR.BlendColor(CLICK_ARROW_COLOR));

    /**
     * @tc.steps: step4. Touch up button
     * @tc.expected: change bgColor to hoverColor
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::UP);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR);

    /**
     * @tc.steps: step5. Click button
     * @tc.expected: Swipe to next item
     */
    rightArrowPattern->ButtonClickEvent();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: ClickArrow003
 * @tc.desc: Hover and move out arrow by touch
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    auto rightMockRenderContext = AceType::DynamicCast<MockRenderContext>(rightButtonNode->renderContext_);
    EXPECT_TRUE(rightMockRenderContext->isVisible_);

    /**
     * @tc.steps: step1. Hover button
     * @tc.expected: change bgColor to hoverColor
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, true);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR);

    /**
     * @tc.steps: step2. Touch down button
     * @tc.expected: change bgColor to hoverColor+clickColor
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::DOWN);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR.BlendColor(CLICK_ARROW_COLOR));

    /**
     * @tc.steps: step3. Hover button
     * @tc.expected: bgColor not change
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, true);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR.BlendColor(CLICK_ARROW_COLOR));

    /**
     * @tc.steps: step1. Move out of button
     * @tc.expected: bgColor not change
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, false);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR.BlendColor(CLICK_ARROW_COLOR));

    /**
     * @tc.steps: step4. Touch cancel outside button
     * @tc.expected: change bgColor to default
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::CANCEL);
    EXPECT_EQ(rightMockRenderContext->blendColor_, Color::TRANSPARENT);
}

/**
 * @tc.name: HoverShow001
 * @tc.desc: When hover arrow, show arrow. when not hover, hide arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverShow001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true);
        model.SetHoverShow(true); // when not hover, hide arrow
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    auto rightMockRenderContext = AceType::DynamicCast<MockRenderContext>(rightButtonNode->renderContext_);
    EXPECT_FALSE(rightMockRenderContext->isVisible_);

    /**
     * @tc.steps: step1. Touch down button
     * @tc.expected: BgColor not change because not hover, the button is inVisible
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::DOWN);
    EXPECT_EQ(rightMockRenderContext->blendColor_, Color::TRANSPARENT);

    /**
     * @tc.steps: step2. Hover button
     * @tc.expected: Show arrow
     */
    rightArrowPattern->ButtonOnHover(rightButtonNode, true);
    EXPECT_TRUE(rightMockRenderContext->isVisible_);

    /**
     * @tc.steps: step3. Touch down button
     * @tc.expected: change bgColor to hoverColor+clickColor because hover, the button is visible
     */
    rightArrowPattern->ButtonTouchEvent(rightButtonNode, TouchType::DOWN);
    EXPECT_EQ(rightMockRenderContext->blendColor_, HOVER_ARROW_COLOR.BlendColor(CLICK_ARROW_COLOR));
}

/**
 * @tc.name: HoverShow002
 * @tc.desc: When loop:false, arrow isVisible depend on currentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverShow002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetDisplayArrow(true);
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    auto leftMockRenderContext = AceType::DynamicCast<MockRenderContext>(leftButtonNode->renderContext_);

    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    auto rightMockRenderContext = AceType::DynamicCast<MockRenderContext>(rightButtonNode->renderContext_);

    /**
     * @tc.steps: step1. CurrentIndex is 0
     * @tc.expected: Can not swipe left, left arrow is inVisible
     */
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_FALSE(leftMockRenderContext->isVisible_);
    EXPECT_TRUE(rightMockRenderContext->isVisible_);

    /**
     * @tc.steps: step2. CurrentIndex is last index
     * @tc.expected: Can not swipe right, right arrow is inVisible
     */
    controller_->ChangeIndex(3, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(leftMockRenderContext->isVisible_);
    EXPECT_FALSE(rightMockRenderContext->isVisible_);
}
} // namespace OHOS::Ace::NG
