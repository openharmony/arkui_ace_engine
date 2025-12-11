/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/button/button_theme.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
void SwiperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SWIPER);
    auto swiperIndicatorTheme = SwiperIndicatorTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(SwiperIndicatorTheme::TypeId())).WillRepeatedly(Return(swiperIndicatorTheme));
    swiperIndicatorTheme->color_ = Color::FromString("#182431");
    swiperIndicatorTheme->selectedColor_ = Color::FromString("#007DFF");
    swiperIndicatorTheme->hoverArrowBackgroundColor_ = HOVER_ARROW_COLOR;
    swiperIndicatorTheme->clickArrowBackgroundColor_ = CLICK_ARROW_COLOR;
    swiperIndicatorTheme->arrowDisabledAlpha_ = ARROW_DISABLED_ALPHA;
    swiperIndicatorTheme->size_ = Dimension(6.f);
    TextStyle textStyle;
    textStyle.SetTextColor(INDICATOR_TEXT_FONT_COLOR);
    textStyle.SetFontSize(INDICATOR_TEXT_FONT_SIZE);
    textStyle.SetFontWeight(INDICATOR_TEXT_FONT_WEIGHT);
    swiperIndicatorTheme->digitalIndicatorTextStyle_ = textStyle;
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::SetUp();
}

void SwiperTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockContainer::TearDown();
}

void SwiperTestNg::SetUp() {}

void SwiperTestNg::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    controller_ = nullptr;
    indicatorNode_ = nullptr;
    leftArrowNode_ = nullptr;
    rightArrowNode_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

void SwiperTestNg::GetSwiper()
{
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    eventHub_ = frameNode_->GetEventHub<SwiperEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    controller_ = pattern_->GetSwiperController();
}

void SwiperTestNg::CreateSwiperDone()
{
    CreateDone();
    int index = pattern_->RealTotalCount();
    if (pattern_->IsShowIndicator() && pattern_->HasIndicatorNode()) {
        indicatorNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasLeftButtonNode()) {
        leftArrowNode_ = GetChildFrameNode(frameNode_, index);
        index += 1;
    }
    if (pattern_->HasRightButtonNode()) {
        rightArrowNode_ = GetChildFrameNode(frameNode_, index);
    }
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->paintRect_ = RectF(0.f, 0.f, SWIPER_WIDTH, SWIPER_HEIGHT);
}

SwiperModelNG SwiperTestNg::CreateSwiper()
{
    SwiperModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    GetSwiper();
    return model;
}

SwiperModelNG SwiperTestNg::CreateArcSwiper()
{
    SwiperModelNG model;
    model.Create(true);
    model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    GetSwiper();
    return model;
}

void SwiperTestNg::CreateSwiperItems(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ButtonModelNG buttonModelNG;
        buttonModelNG.CreateWithLabel("label");
        ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
        ViewStackProcessor::GetInstance()->Pop();
    }
}

RefPtr<FrameNode> SwiperTestNg::CreateSwiper(const std::function<void(SwiperModelNG)>& callback)
{
    SwiperModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

void SwiperTestNg::CreateItemWithSize(float width, float height)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel("label");
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

void SwiperTestNg::CreateWithArrow()
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
}

void SwiperTestNg::ShowNext()
{
    controller_->ShowNext();
    FlushUITasks();
}

void SwiperTestNg::ShowPrevious()
{
    controller_->ShowPrevious();
    FlushUITasks();
}

void SwiperTestNg::ChangeIndex(int32_t index, bool useAnimation)
{
    controller_->ChangeIndex(index, useAnimation);
    FlushUITasks();
}

void SwiperTestNg::ChangeIndex(int32_t index, SwiperAnimationMode mode)
{
    controller_->ChangeIndex(index, mode);
    FlushUITasks();
}

void SwiperTestNg::SwipeTo(int32_t index)
{
    controller_->SwipeTo(index);
    FlushUITasks();
}

void SwiperTestNg::SwipeToWithoutAnimation(int32_t index)
{
    controller_->SwipeToWithoutAnimation(index);
    FlushUITasks();
}

void SwiperTestNg::RemoveSwiperItem(int32_t index)
{
    frameNode_->RemoveChildAtIndex(index);
    FlushUITasks();
}

void SwiperTestNg::AddSwiperItem(int32_t slot)
{
    RefPtr<FrameNode> testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    frameNode_->AddChild(testNode, slot);
    FlushUITasks();
}

AssertionResult SwiperTestNg::DigitText(std::u16string expectDigit)
{
    auto currentIndexNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetFirstChild());
    auto totalCountNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetLastChild());
    auto currentIndexText = currentIndexNode->GetLayoutProperty<TextLayoutProperty>();
    auto totalCountText = totalCountNode->GetLayoutProperty<TextLayoutProperty>();
    std::u16string actualDigit = currentIndexText->GetContentValue() + totalCountText->GetContentValue();
    if (actualDigit == expectDigit) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Actual: " << UtfUtils::Str16ToStr8(actualDigit)
                              << " Expected: " << UtfUtils::Str16ToStr8(expectDigit);
}

AssertionResult SwiperTestNg::CurrentIndex(int32_t expectIndex)
{
    if (pattern_->GetCurrentIndex() != expectIndex) {
        return IsEqual(pattern_->GetCurrentIndex(), expectIndex);
    }
    if (!GetChildFrameNode(frameNode_, expectIndex)) {
        return AssertionFailure() << "There is no item at expectIndex: " << expectIndex;
    }
    if (!GetChildFrameNode(frameNode_, expectIndex)->IsActive()) {
        return AssertionFailure() << "The expectIndex item is not active";
    }
    if (GetChildFrameNode(frameNode_, expectIndex)->GetLayoutProperty()->GetVisibility() != VisibleType::GONE) {
        if (NearZero(GetChildWidth(frameNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item width is 0";
        }
        if (NearZero(GetChildHeight(frameNode_, expectIndex))) {
            return AssertionFailure() << "The expectIndex item height is 0";
        }
    }
    return AssertionSuccess();
}

void SwiperTestNg::InitCaptureTest()
{
    const int32_t displayCount = 3;
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(displayCount);
    layoutProperty_->UpdatePrevMargin(Dimension(CAPTURE_MARGIN_SIZE));
    layoutProperty_->UpdateNextMargin(Dimension(CAPTURE_MARGIN_SIZE));
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasCachedCapture_);
}
} // namespace OHOS::Ace::NG