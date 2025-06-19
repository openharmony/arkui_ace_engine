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
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"

namespace OHOS::Ace::NG {
class SwiperArrowTestNg : public SwiperTestNg {
public:
    RefPtr<TextLayoutProperty> GetSymbolProperty(const RefPtr<FrameNode>& arrowNode);
    RefPtr<MockRenderContext> GetArrowContext(const RefPtr<FrameNode>& arrowNode);
    void HandleMouseEvent(Offset mousePoint);
    AssertionResult VerifyArrowVisible(bool leftArrowVisible, bool rightArrowVisible);
};

RefPtr<TextLayoutProperty> SwiperArrowTestNg::GetSymbolProperty(const RefPtr<FrameNode>& arrowNode)
{
    auto buttonNode = AceType::DynamicCast<FrameNode>(arrowNode->GetFirstChild());
    auto symbolNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    return symbolNode->GetLayoutProperty<TextLayoutProperty>();
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
    return AssertionFailure() << "Actual: {" << leftMockRenderContext->isVisible_ << ", "
                              << rightMockRenderContext->isVisible_ << "} Expected: {" << leftArrowVisible << ", "
                              << rightArrowVisible << "}";
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
     * @tc.expected: Vertify symbol type/color
     */
    CreateWithArrow();
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    EXPECT_EQ(leftButtonNode->GetTag(), V2::BUTTON_ETS_TAG);
    auto leftSymbolNode = AceType::DynamicCast<FrameNode>(leftButtonNode->GetFirstChild());
    EXPECT_EQ(leftSymbolNode->GetTag(), V2::SYMBOL_ETS_TAG);

    auto leftSymbolProperty = GetSymbolProperty(leftArrowNode_);
    auto rightSymbolProperty = GetSymbolProperty(rightArrowNode_);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    EXPECT_EQ(leftSymbolProperty->GetSymbolSourceInfoValue(), SymbolSourceInfo(swiperTheme->GetLeftSymbolId()));
    EXPECT_EQ(rightSymbolProperty->GetSymbolSourceInfoValue(), SymbolSourceInfo(swiperTheme->GetRightSymbolId()));
    EXPECT_EQ(leftSymbolProperty->GetSymbolColorListValue({})[0], ARROW_PARAMETERS.arrowColor);
    EXPECT_EQ(leftSymbolProperty->GetSymbolColorList(), rightSymbolProperty->GetSymbolColorList());
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
     * @tc.expected: Vertify symbol type/color
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetEnabled(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto leftSymbol = GetSymbolProperty(leftArrowNode_);
    auto rightSymbol = GetSymbolProperty(rightArrowNode_);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    EXPECT_EQ(leftSymbol->GetSymbolSourceInfoValue(), SymbolSourceInfo(swiperIndicatorTheme->GetUpSymbolId()));
    EXPECT_EQ(rightSymbol->GetSymbolSourceInfoValue(), SymbolSourceInfo(swiperIndicatorTheme->GetDownSymbolId()));
    EXPECT_EQ(leftSymbol->GetSymbolColorListValue({})[0],
        ARROW_PARAMETERS.arrowColor.value().BlendOpacity(ARROW_DISABLED_ALPHA));
    EXPECT_EQ(leftSymbol->GetSymbolColorList(), rightSymbol->GetSymbolColorList());
}

/**
 * @tc.name: ClickArrow001
 * @tc.desc: Click arrow directly
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow001, TestSize.Level1)
{
    CreateWithArrow();
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
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: ClickArrow002
 * @tc.desc: Hover and click arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow002, TestSize.Level1)
{
    CreateWithArrow();
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
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: ClickArrow003
 * @tc.desc: Hover and move out arrow by touch
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrow003, TestSize.Level1)
{
    CreateWithArrow();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true);
    model.SetHoverShow(true); // when not hover, hide arrow
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayArrow(true);
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();

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
 * @tc.name: HoverShow003
 * @tc.desc: When loop:false and SwipeByGroup:true, arrow isVisible depend on currentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverShow003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetSwipeByGroup(true);
    model.SetLoop(false);
    model.SetDisplayArrow(true);
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems(6);
    CreateSwiperDone();

    EXPECT_EQ(pattern_->TotalCount(), 6);
    /**
     * @tc.steps: step1. CurrentIndex is in first page
     * @tc.expected: Can not swipe left, left arrow is inVisible
     */
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step2. CurrentIndex is in last page
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
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // hide indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();

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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Hover swiper
     * @tc.expected: Still hide arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: HoverEvent003
 * @tc.desc: When has no indicator, check hover event time sequence of swiper and arrow.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Hide indicator
     */
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // hide indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(false, false));

    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step2. Hover swiper
     * @tc.expected: Only show right arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step3. Hover from swiper to left arrow
     * @tc.expected: Only show right arrow
     */
    leftArrowPattern->ButtonOnHover(leftArrowNode_, true);
    pattern_->hoverEvent_->GetOnHoverEventFunc()(false);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step4. Hover from left arrow to swiper
     * @tc.expected: Only show right arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    leftArrowPattern->ButtonOnHover(leftArrowNode_, false);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step5. Hover from swiper to right arrow
     * @tc.expected: Only show right arrow
     */
    rightArrowPattern->ButtonOnHover(rightArrowNode_, true);
    pattern_->hoverEvent_->GetOnHoverEventFunc()(false);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step6. Hover out of arrow
     * @tc.expected: Do not show arrow
     */
    rightArrowPattern->ButtonOnHover(rightArrowNode_, false);
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: HoverEvent004
 * @tc.desc: When has indicator, check hover event time sequence of arrow and indicator.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show indicator
     */
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(true); // show indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(false, false));

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step2. Hover arrow
     * @tc.expected: Only show right arrow
     */
    leftArrowPattern->ButtonOnHover(leftArrowNode_, true);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step3. Hover from arrow to indicator
     * @tc.expected: Only show right arrow
     */
    indicatorPattern->HandleHoverEvent(true);
    leftArrowPattern->ButtonOnHover(leftArrowNode_, false);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step4. Hover from indicator to arrow
     * @tc.expected: Only show right arrow
     */
    leftArrowPattern->ButtonOnHover(leftArrowNode_, true);
    indicatorPattern->HandleHoverEvent(false);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step5. Hover out of arrow
     * @tc.expected: Do not show arrow
     */
    leftArrowPattern->ButtonOnHover(leftArrowNode_, false);
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: HoverEvent005
 * @tc.desc: When has indicator, test arrow status when hover attribute changes.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show indicator
     */
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(true); // show indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(false, false));

    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step2. Hover arrow
     * @tc.expected: Only show right arrow
     */
    rightArrowPattern->ButtonOnHover(rightArrowNode_, true);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step3. Change hover show to false
     * @tc.expected: Only show right arrow
     */
    layoutProperty_->UpdateHoverShow(false);
    frameNode_->MarkModifyDone();
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step4. Hover out of arrow
     * @tc.expected: Only show right arrow
     */
    rightArrowPattern->ButtonOnHover(rightArrowNode_, false);
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step5. Change hover show to true
     * @tc.expected: Do not show arrow
     */
    layoutProperty_->UpdateHoverShow(true);
    frameNode_->MarkModifyDone();
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: HoverEvent006
 * @tc.desc: Test arrow status when indicator changes.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, HoverEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Hide indicator
     */
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // hide indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(false, false));

    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step2. Hover swiper
     * @tc.expected: Only show right arrow
     */
    pattern_->hoverEvent_->GetOnHoverEventFunc()(true);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));

    /**
     * @tc.steps: step3. Show indicator
     * @tc.expected: Do not show arrow
     */
    layoutProperty_->UpdateShowIndicator(true);
    frameNode_->MarkModifyDone();
    EXPECT_TRUE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    /**
     * @tc.steps: step4. Hover arrow
     * @tc.expected: Only show right arrow
     */
    rightArrowPattern->ButtonOnHover(rightArrowNode_, true);
    EXPECT_FALSE(pattern_->IsHoverNone());
    EXPECT_TRUE(VerifyArrowVisible(false, true));
}

/**
 * @tc.name: MouseEvent001
 * @tc.desc: When has indicator and IsSidebarMiddle:false, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);    // show arrow only when hover
    auto arrowStyle = ARROW_PARAMETERS;
    arrowStyle.isSidebarMiddle = false;
    model.SetArrowStyle(arrowStyle);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL); // VERTICAL layout
    model.SetLoop(false);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);    // show arrow only when hover
    auto arrowStyle = ARROW_PARAMETERS;
    arrowStyle.isSidebarMiddle = false;
    model.SetArrowStyle(arrowStyle);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);
    auto arrowStyle = ARROW_PARAMETERS;
    arrowStyle.isSidebarMiddle = false;
    model.SetArrowStyle(arrowStyle);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // no indicator
    model.SetLoop(false);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(true);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);

    /**
     * @tc.steps: step1. Mouse in navigation(no navigation)
     * @tc.expected: Arrow is still hide because has no navigation
     */
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    HandleMouseEvent(inRegionPoint);
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: MouseEvent006
 * @tc.desc: When has no left/right button, test mouse event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, MouseEvent006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    Offset inRegionPoint = Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT - 10.f);

    /**
     * @tc.steps: step1. Mouse in navigation(no button)
     * @tc.expected: Nothing happened
     */
    HandleMouseEvent(inRegionPoint);
    EXPECT_EQ(leftArrowNode_, nullptr);
    EXPECT_EQ(rightArrowNode_, nullptr);
}

/**
 * @tc.name: Arrow001
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, Arrow001, TestSize.Level1)
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(swiperArrowParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    auto leftArrowLayoutProperty = leftArrowNode_->GetLayoutProperty<SwiperArrowLayoutProperty>();
    EXPECT_FALSE(leftArrowLayoutProperty->GetIsShowBackgroundValue());
    EXPECT_FALSE(leftArrowLayoutProperty->GetIsSidebarMiddleValue());
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundSizeValue(), Dimension(24.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundColorValue(), Color::FromString("#00000000"));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowSizeValue(), Dimension(18.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowColorValue(), Color::FromString("#182431"));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 5), RectF(165.f, 772.01f, 24.f, 24.f)));
}

/**
 * @tc.name: Arrow002
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, Arrow002, TestSize.Level1)
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(swiperArrowParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    auto leftArrowLayoutProperty = rightArrowNode_->GetLayoutProperty<SwiperArrowLayoutProperty>();
    EXPECT_TRUE(leftArrowLayoutProperty->GetIsShowBackgroundValue());
    EXPECT_TRUE(leftArrowLayoutProperty->GetIsSidebarMiddleValue());
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundSizeValue(), Dimension(32.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetBackgroundColorValue(), Color::FromString("#19182431"));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowSizeValue(), Dimension(24.f));
    EXPECT_EQ(leftArrowLayoutProperty->GetArrowColorValue(), Color::GREEN);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6), RectF(440.f, 384.f, 32.f, 32.f)));
}

/**
 * @tc.name: Arrow003
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, Arrow003, TestSize.Level1)
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
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(swiperArrowParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 5), RectF(448.01f, 317.f, 32.f, 32.f)));
}

/**
 * @tc.name: Arrow004
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, Arrow004, TestSize.Level1)
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
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(swiperArrowParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6), RectF(224.f, 760.f, 32.f, 32.f)));
}

/**
 * @tc.name: InitOnKeyEvent001
 * @tc.desc: Test InitOnKeyEvent method and callback is called.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitOnKeyEvent001, TestSize.Level1)
{
    auto arrowNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_LEFT_ARROW_ETS_TAG, 1, []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto pattern = arrowNode->GetPattern<SwiperArrowPattern>();
    arrowNode->GetOrCreateFocusHub();
    pattern->InitOnKeyEvent();
    auto focusHub = arrowNode->GetFocusHub();
    auto events = focusHub->onKeyEventsInternal_;
    auto it = events.find(OnKeyEventType::DEFAULT);
    ASSERT_NE(it, events.end());
    /**
     * @tc.steps: step1. Test key event with KeyCode::KEY_LEFT_KNOB and KeyAction::DOWN.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_LEFT_KNOB;
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(it->second(keyEvent));
    /**
     * @tc.steps: step2. Test key event with KeyCode::KEY_ENTER and KeyAction::DOWN.
     */
    keyEvent.code = KeyCode::KEY_ENTER;
    keyEvent.action = KeyAction::DOWN;
    EXPECT_TRUE(it->second(keyEvent));
    /**
     * @tc.steps: step3. Test key event with KeyCode::KEY_ENTER and KeyAction::UP.
     */
    keyEvent.code = KeyCode::KEY_ENTER;
    keyEvent.action = KeyAction::UP;
    EXPECT_FALSE(it->second(keyEvent));
}

/**
 * @tc.name: ClickArrowRTL001
 * @tc.desc: Test clicking the left and right arrows when the layout is RTL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ClickArrowRTL001, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
    /**
     * @tc.steps: step1. Click the left arrow in RTL layout.
     */
    leftArrowPattern->ButtonClickEvent();
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));
    /**
     * @tc.steps: step2. Click the right arrow in RTL layout.
     */
    rightArrowPattern->ButtonClickEvent();
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: InitButtonEventCallBack001
 * @tc.desc: Test InitButtonEvent method and all is callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitButtonEventCallBack001, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    /**
     * @tc.steps: step1. trigger touch event.
     */
    auto buttonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    ASSERT_NE(buttonNode, nullptr);
    auto arrowGestureHub = buttonNode->GetOrCreateGestureEventHub();
    auto actuator = arrowGestureHub->touchEventActuator_;
    auto events = actuator->touchEvents_;
    ASSERT_FALSE(events.empty());
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    leftArrowPattern->isTouch_ = false;
    auto event = events.front();
    ASSERT_NE(event, nullptr);
    auto callback = event->GetTouchEventCallback();
    ASSERT_NE(callback, nullptr);
    callback(touchEventInfo);
    EXPECT_TRUE(leftArrowPattern->isTouch_);
    /**
     * @tc.steps: step2 trigger hover event.
     */
    auto arrowInputEventHub = buttonNode->GetOrCreateInputEventHub();
    auto actuatorHover = arrowInputEventHub->hoverEventActuator_;
    auto eventsHover = actuatorHover->inputEvents_;
    leftArrowPattern->isHover_ = false;
    ASSERT_FALSE(eventsHover.empty());
    auto eventHover = eventsHover.front();
    ASSERT_NE(eventHover, nullptr);
    auto callbackHover = eventHover->GetOnHoverEventFunc();
    ASSERT_NE(callbackHover, nullptr);
    callbackHover(true);
    EXPECT_TRUE(leftArrowPattern->isHover_);
}

/**
 * @tc.name: InitButtonEventCallBack002
 * @tc.desc: Test InitButtonEvent method and all is callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitButtonEventCallBack002, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    auto buttonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    ASSERT_NE(buttonNode, nullptr);
    auto arrowGestureHub = buttonNode->GetOrCreateGestureEventHub();
    auto leftArrowGestureHub = leftArrowNode_->GetOrCreateGestureEventHub();
    /**
     * @tc.steps: step1 trigger click event.
     */
    ChangeIndex(2);
    GestureEvent info;
    info.SetSourceDevice(SourceType::KEYBOARD);
    auto actuatorClick = leftArrowGestureHub->clickEventActuator_;
    auto eventsClick = actuatorClick->clickEvents_;
    ASSERT_FALSE(eventsClick.empty());
    auto event = eventsClick.front();
    ASSERT_NE(event, nullptr);
    auto callback = event->GetGestureEventFunc();
    ASSERT_NE(callback, nullptr);
    callback(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: TotalCount001
 * @tc.desc: Test TotalCount method and return the correct value.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, TotalCount001, TestSize.Level1)
{
    CreateWithArrow();
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    /**
     * @tc.steps: step1 get totalCount.
     */
    EXPECT_EQ(leftArrowPattern->TotalCount(), 3);
}

/**
 * @tc.name: ChangeLoop001
 * @tc.desc: Test arrow visiblity when change loop.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ChangeLoop001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true);
    model.SetHoverShow(false);
    model.SetDisplayCount(2);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems(6);
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(true, true));

    controller_->ChangeIndex(5, false);
    FlushUITasks();

    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_TRUE(VerifyArrowVisible(true, false));
}

/**
 * @tc.name: ArrowVisiblity001
 * @tc.desc: Test arrow visiblity when displayCount >= totalCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ArrowVisiblity001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true);
    model.SetHoverShow(false);
    model.SetDisplayCount(1);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems(3);
    CreateSwiperDone();

    EXPECT_TRUE(VerifyArrowVisible(true, true));

    layoutProperty_->UpdateDisplayCount(3);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    layoutProperty_->UpdateDisplayCount(5);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_TRUE(VerifyArrowVisible(false, false));

    layoutProperty_->UpdateDisplayCount(1);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_TRUE(VerifyArrowVisible(true, true));
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->RemoveChildAtIndex(0);
    FlushUITasks();
    EXPECT_TRUE(VerifyArrowVisible(false, false));
}

/**
 * @tc.name: ArrowButtonType001
 * @tc.desc: Test arrow button type.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, ArrowButtonType001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true);
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();

    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    ASSERT_EQ(leftButtonNode->GetTag(), V2::BUTTON_ETS_TAG);
    auto leftButtonType = leftButtonNode->GetLayoutProperty<ButtonLayoutProperty>()->GetType();
    EXPECT_EQ(leftButtonType, ButtonType::CIRCLE);

    auto rightButtonNode = AceType::DynamicCast<FrameNode>(rightArrowNode_->GetFirstChild());
    ASSERT_EQ(rightButtonNode->GetTag(), V2::BUTTON_ETS_TAG);
    auto rightButtonType = rightButtonNode->GetLayoutProperty<ButtonLayoutProperty>()->GetType();
    EXPECT_EQ(rightButtonType, ButtonType::CIRCLE);
}

/**
 * @tc.name: Arrow005
 * @tc.desc: Test arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, Arrow005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. swiper type is DOT, BIND mode and Show set value arrow
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
    SwiperModelNG model = CreateSwiper();
    model.SetBindIndicator(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(swiperArrowParameters);
    model.SetShowIndicator(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_NE(frameNode_, nullptr);
    EXPECT_EQ(indicatorNode_, nullptr);
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    EXPECT_NE(rightArrowNode_, nullptr);
    auto swiperArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(swiperArrowPattern, nullptr);
    EXPECT_EQ(swiperArrowPattern->TotalCount(), 3);
    KeyEvent keyEvent(KeyCode::KEY_ENTER, KeyAction::DOWN);
    swiperArrowPattern->OnKeyEvent(keyEvent);
    swiperArrowPattern->DumpAdvanceInfo();
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto controller = indicatorPattern->GetIndicatorController();
    ASSERT_NE(controller, nullptr);
    controller->SetSwiperNode(frameNode_);
    EXPECT_TRUE(IsEqual(indicatorNode_->GetGeometryNode()->GetFrameRect(), RectF(0.f, 0.f, 0.f, 0.f)));
    indicatorPattern->SaveDotIndicatorProperty();
    FlushUITasks();
    EXPECT_TRUE(IsEqual(indicatorNode_->GetGeometryNode()->GetFrameRect(), RectF(0.0f, 0.f, 31.98f, 87.9f)));
}

/**
 * @tc.name: InitAccessibilityText001
 * @tc.desc: Test clicking the left arrows.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitAccessibilityText001, TestSize.Level1)
{
    CreateWithArrow();
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    auto buttonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    ASSERT_NE(buttonNode, nullptr);
    leftArrowPattern->InitAccessibilityText();
    auto buttonAccessibilityProperty = buttonNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(buttonAccessibilityProperty, nullptr);
    buttonAccessibilityProperty->SetAccessibilityText("left");
    auto text = buttonAccessibilityProperty->GetAccessibilityText();
    EXPECT_EQ(text, "left");
}

/**
 * @tc.name: InitAccessibilityText002
 * @tc.desc: Test clicking the right arrows.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitAccessibilityText002, TestSize.Level1)
{
    CreateWithArrow();
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
    auto buttonNode = AceType::DynamicCast<FrameNode>(rightArrowNode_->GetFirstChild());
    ASSERT_NE(buttonNode, nullptr);
    rightArrowPattern->InitAccessibilityText();
    auto buttonAccessibilityProperty = buttonNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(buttonAccessibilityProperty, nullptr);
    buttonAccessibilityProperty->SetAccessibilityText("right");
    auto text = buttonAccessibilityProperty->GetAccessibilityText();
    EXPECT_EQ(text, "right");
}

/**
 * @tc.name: InitOnKeyEvent002
 * @tc.desc: Test InitOnKeyEvent method and callback is called.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, InitOnKeyEvent002, TestSize.Level1)
{
    auto arrowNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_LEFT_ARROW_ETS_TAG, 1, []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto pattern = arrowNode->GetPattern<SwiperArrowPattern>();
    arrowNode->GetOrCreateFocusHub();
    pattern->InitOnKeyEvent();
    auto focusHub = arrowNode->GetFocusHub();
    auto events = focusHub->onKeyEventsInternal_;
    auto it = events.find(OnKeyEventType::DEFAULT);
    ASSERT_NE(it, events.end());
    /**
     * @tc.steps: step1. Test key event with KeyCode::KEY_LEFT_KNOB and KeyAction::DOWN.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_LEFT_KNOB;
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(it->second(keyEvent));
    /**
     * @tc.steps: step2. Test key event with KeyCode::KEY_ENTER and KeyAction::DOWN.
     */
    keyEvent.code = KeyCode::KEY_ENTER;
    keyEvent.action = KeyAction::DOWN;
    EXPECT_TRUE(it->second(keyEvent));
    /**
     * @tc.steps: step3. Test key event with KeyCode::KEY_ENTER and KeyAction::UP.
     */
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::UP;
    EXPECT_FALSE(it->second(keyEvent));
}

/**
 * @tc.name: UpdateArrowContent003
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent003, TestSize.Level1)
{
    g_isNeedSymbol = false;
    /**
     * @tc.steps: step1. Set arrow
     * @tc.expected: Vertify symbol type/color
     */
    CreateWithArrow();
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    EXPECT_EQ(leftButtonNode->GetTag(), V2::BUTTON_ETS_TAG);
    g_isNeedSymbol = true;
}

/**
 * @tc.name: UpdateArrowContent004
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, UpdateArrowContent004, TestSize.Level1)
{
    g_isNeedSymbol = false;
    /**
     * @tc.steps: step1. Set VERTICAL and enabled:false
     * @tc.expected: Vertify symbol type/color
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    model.SetEnabled(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto leftButtonNode = AceType::DynamicCast<FrameNode>(leftArrowNode_->GetFirstChild());
    EXPECT_EQ(leftButtonNode->GetTag(), V2::BUTTON_ETS_TAG);
    g_isNeedSymbol = true;
}

/**
 * @tc.name: SetLayoutDisplayCount001
 * @tc.desc: Test SetLayoutDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArrowTestNg, SetLayoutDisplayCount001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(AceType::RawPtr(frameNode_), 3);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->SetLayoutDisplayCount(frameNode_);
    auto leftArrowPattern = leftArrowNode_->GetPattern<SwiperArrowPattern>();
    EXPECT_EQ(leftArrowPattern->displayCount_, 3);
    auto rightArrowPattern = rightArrowNode_->GetPattern<SwiperArrowPattern>();
    EXPECT_EQ(rightArrowPattern->displayCount_, 3);
    /**
     * @tc.steps: step1 SetLayoutDisplayCount.
     */
    leftArrowPattern->SetLayoutDisplayCount(5);
    EXPECT_EQ(leftArrowPattern->displayCount_, 3);
    rightArrowPattern->SetLayoutDisplayCount(5);
    EXPECT_EQ(rightArrowPattern->displayCount_, 3);
}
} // namespace OHOS::Ace::NG
