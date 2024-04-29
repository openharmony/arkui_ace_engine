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
    RefPtr<MockRenderContext> GetArrowContext(const RefPtr<FrameNode>& arrowNode);
    void HandleMouseEvent(Offset mousePoint);
    AssertionResult VerifyArrowVisible(bool leftArrowVisible, bool rightArrowVisible);
};

ImageSourceInfo SwiperArrowTestNg::GetImageInfo(const RefPtr<FrameNode>& arrowNode)
{
    auto buttonNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    auto imageNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    return imageSourceInfo.value();
}

RefPtr<MockRenderContext> SwiperArrowTestNg::GetArrowContext(const RefPtr<FrameNode>& arrowNode)
{
    auto buttonNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(buttonNode->renderContext_);
    return mockRenderContext;
}

void SwiperArrowTestNg::HandleMouseEvent(Offset mousePoint)
{
    MouseInfo info;
    info.SetLocalLocation(mousePoint);
    pattern_->mouseEvent_->GetOnMouseEventFunc()(info);
}

AssertionResult SwiperArrowTestNg::VerifyArrowVisible(bool leftArrowVisible, bool rightArrowVisible)
{
    auto leftMockRenderContext = GetArrowContext(leftArrowNode_);
    auto rightMockRenderContext = GetArrowContext(rightArrowNode_);
    if (leftMockRenderContext->isVisible_ == leftArrowVisible &&
        rightMockRenderContext->isVisible_ == rightArrowVisible) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Actual: {" << leftMockRenderContext->isVisible_ << ", " <<
        rightMockRenderContext->isVisible_<< "} Expected: {" << leftArrowVisible << ", " << rightArrowVisible << "}";
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
    auto leftImageInfo = GetImageInfo(leftArrowNode_);
    auto rightImageInfo = GetImageInfo(rightArrowNode_);
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
    auto leftImageInfo = GetImageInfo(leftArrowNode_);
    auto rightImageInfo = GetImageInfo(rightArrowNode_);
    EXPECT_EQ(leftImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG);
    EXPECT_EQ(rightImageInfo.GetResourceId(), InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    EXPECT_EQ(leftImageInfo.GetFillColor(), ARROW_PARAMETERS.arrowColor.value().BlendOpacity(ARROW_DISABLED_ALPHA));
    EXPECT_EQ(leftImageInfo.GetFillColor(), rightImageInfo.GetFillColor());
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
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
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
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode_->GetFirstChild());
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
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
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode_->GetFirstChild());
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
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
    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode_->GetFirstChild());
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
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

    /**
     * @tc.steps: step1. CurrentIndex is 0
     * @tc.expected: Can not swipe left, left arrow is inVisible
     */
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step2. CurrentIndex is last index
     * @tc.expected: Can not swipe right, right arrow is inVisible
     */
    ChangeIndex(3);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(VerifyArrowVisible(true, false));
}

/**
 * @tc.name: HoverEvent001
 * @tc.desc: When has no indicator and hover swiper, will show arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Hide indicator
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetShowIndicator(false); // hide indicator
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });

    /**
     * @tc.steps: step2. Hover swiper
     * @tc.expected: Show arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    EXPECT_TRUE(VerifyArrowVisible(true, true));

    /**
     * @tc.steps: step3. No hvoer swiper
     * @tc.expected: Hide arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(false);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: HoverEvent002
 * @tc.desc: When has indicator, arrow visible depend on others
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });

    /**
     * @tc.steps: step1. Hover swiper
     * @tc.expected: Still hide arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent001
 * @tc.desc: When has indicator and IsSidebarMiddle:false, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true); // show arrow only when hover
        auto arrowStyle = ARROW_PARAMETERS;
        arrowStyle.isSidebarMiddle = false;
        model.SetArrowStyle(arrowStyle);
    });
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);
    Offset outRegionPoint = Offset(1.f, 1.f);

    /**
     * @tc.steps: step1. Mouse in and out navigation at first page
     * @tc.expected: Arrow is default hide,
     * show arrow(expect left arrow) when mouse in navigation, hide arrow when mouse out
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step2. Mouse in and out navigation at middle page
     * @tc.expected: Arrow is default hide, show arrow when mouse in navigation, hide arrow when mouse out
     */
    ChangeIndex(2);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step3. Mouse in and out navigation at last page
     * @tc.expected: Arrow is default hide,
     * show arrow(expect right arrow) when mouse in navigation, hide arrow when mouse out
     */
    ChangeIndex(3);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, false));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent002
 * @tc.desc: When has indicator and IsSidebarMiddle:false, test mouse event in VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL); // VERTICAL layout
        model.SetLoop(false);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true); // show arrow only when hover
        auto arrowStyle = ARROW_PARAMETERS;
        arrowStyle.isSidebarMiddle = false;
        model.SetArrowStyle(arrowStyle);
    });
    Offset inRegionPoint = Offset(SWIPER_WIDTH - 10.f, SWIPER_HEIGHT / 2);
    Offset outRegionPoint = Offset(1.f, 1.f);

    /**
     * @tc.steps: step1. Mouse in and out navigation at first page
     * @tc.expected: Arrow is default hide,
     * show arrow(expect left arrow) when mouse in navigation, hide arrow when mouse out
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step2. Mouse in and out navigation at middle page
     * @tc.expected: Arrow is default hide, show arrow when mouse in navigation, hide arrow when mouse out
     */
    ChangeIndex(2);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step3. Mouse in and out navigation at last page
     * @tc.expected: Arrow is default hide,
     * show arrow(expect right arrow) when mouse in navigation, hide arrow when mouse out
     */
    ChangeIndex(3);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, false));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent003
 * @tc.desc: When loop:true, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true);
        auto arrowStyle = ARROW_PARAMETERS;
        arrowStyle.isSidebarMiddle = false;
        model.SetArrowStyle(arrowStyle);
    });
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);
    Offset outRegionPoint = Offset(1.f, 1.f);

    /**
     * @tc.steps: step1. Mouse in and out navigation at first page
     * @tc.expected: Arrow is default hide, show arrow when mouse in navigation, hide arrow when mouse out
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step2. Mouse in and out navigation at last page
     * @tc.expected: Arrow is default hide, show arrow when mouse in navigation, hide arrow when mouse out
     */
    ChangeIndex(3);
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(true, true));

    HandleMouseEvent(outRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent004
 * @tc.desc: When IsSidebarMiddle:true, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);
    MouseInfo info;

    /**
     * @tc.steps: step1. Mouse in navigation
     * @tc.expected: Arrow is still hide because IsSidebarMiddle:true
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent005
 * @tc.desc: When has no indicator, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetShowIndicator(false); // no indicator
        model.SetLoop(false);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(true);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);

    /**
     * @tc.steps: step1. Mouse in navigation(no navigation)
     * @tc.expected: Arrow is still hide because has no navigation
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}
} // namespace OHOS::Ace::NG
