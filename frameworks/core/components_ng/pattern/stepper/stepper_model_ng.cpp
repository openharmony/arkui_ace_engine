/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

#include "base/i18n/localization.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void StepperModelNG::Create(uint32_t index)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto stepperNode = StepperNode::GetOrCreateStepperNode(
        V2::STEPPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto stepperTheme = themeManager->GetTheme<StepperTheme>();
    bool hasSwiperNode = stepperNode->HasSwiperNode();
    bool hasLeftButton = stepperNode->HasLeftButtonNode();
    bool hasRightButton = stepperNode->HasRightButtonNode();
    auto swiperId = stepperNode->GetSwiperId();
    auto leftButtonId = stepperNode->GetLeftButtonId();
    auto rightButtonId = stepperNode->GetRightButtonId();
    if (!hasSwiperNode) {
        auto swiperNode = CreateSwiperChild(swiperId, index);
        swiperNode->MountToParent(stepperNode);
    }

    if (!hasLeftButton) {
        std::string buttonText = "< " + Localization::GetInstance()->GetEntryLetters("stepper.back");
        auto leftButtonNode = CreateButtonChild(leftButtonId, buttonText, stepperTheme);
        leftButtonNode->MountToParent(stepperNode);
    }
    if (!hasRightButton) {
        std::string buttonText = Localization::GetInstance()->GetEntryLetters("stepper.start");
        auto rightButtonNode = CreateButtonChild(rightButtonId, buttonText, stepperTheme);
        rightButtonNode->MountToParent(stepperNode);
    }

    stack->Push(stepperNode);
    ACE_UPDATE_LAYOUT_PROPERTY(StepperLayoutProperty, Index, index);
}

void StepperModelNG::SetOnFinish(RoutineCallbackEvent&& eventOnFinish)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetFinishEvent(std::move(eventOnFinish));
}

void StepperModelNG::SetOnSkip(RoutineCallbackEvent&& eventOnSkip)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSkipEvent(std::move(eventOnSkip));
}

void StepperModelNG::SetOnChange(IndexCallbackEvent&& eventOnChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(eventOnChange));
}

void StepperModelNG::SetOnNext(IndexCallbackEvent&& eventOnNext)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetNextEvent(std::move(eventOnNext));
}

void StepperModelNG::SetOnPrevious(IndexCallbackEvent&& eventOnPrevious)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetPreviousEvent(std::move(eventOnPrevious));
}

RefPtr<FrameNode> StepperModelNG::CreateSwiperChild(int32_t id, uint32_t index)
{
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, id, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateLoop(false);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    swiperPaintProperty->UpdateDisableSwipe(true);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateCachedCount(0);
    swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(static_cast<int32_t>(index));
    swiperNode->MarkModifyDone();

    return swiperNode;
}

RefPtr<FrameNode> StepperModelNG::CreateButtonChild(
    int32_t id, const std::string& symbol, const RefPtr<StepperTheme>& theme)
{
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, id, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    if (theme) {
        buttonNode->GetLayoutProperty()->UpdateBorderWidth({ theme->GetControlMargin(), theme->GetControlMargin(),
            theme->GetControlMargin(), theme->GetControlMargin() });
        buttonNode->GetRenderContext()->UpdateBorderRadius(
            { theme->GetRadius(), theme->GetRadius(), theme->GetRadius(), theme->GetRadius() });
        buttonNode->GetRenderContext()->UpdateBorderColor(
            { Color::TRANSPARENT, Color::TRANSPARENT, Color::TRANSPARENT, Color::TRANSPARENT });
    }
    buttonNode->MarkModifyDone();

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(symbol);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextColor(Color::BLACK);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    if (theme) {
        textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateMaxLines(theme->GetTextMaxLines());
    }
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->MarkModifyDone();

    textNode->MountToParent(buttonNode);
    return buttonNode;
}

} // namespace OHOS::Ace::NG