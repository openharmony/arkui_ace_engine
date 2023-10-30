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

#include "core/components_ng/pattern/button/toggle_button_pattern.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void ToggleButtonPattern::OnAttachToFrameNode()
{
    InitParameters();
}

void ToggleButtonPattern::InitParameters()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(toggleTheme);
    checkedColor_ = toggleTheme->GetCheckedColor();
    unCheckedColor_ = toggleTheme->GetBackgroundColor();
    textMargin_ = toggleTheme->GetTextMargin();
    buttonMargin_ = toggleTheme->GetButtonMargin();
    buttonHeight_ = toggleTheme->GetButtonHeight();
    buttonRadius_ = toggleTheme->GetButtonRadius();
    textFontSize_ = toggleTheme->GetTextFontSize();
    textColor_ = toggleTheme->GetTextColor();
    disabledAlpha_ = toggleTheme->GetDisabledAlpha();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    clickedColor_ = buttonTheme->GetClickedColor();
}

void ToggleButtonPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }

    auto buttonPaintProperty = GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(buttonPaintProperty);
    if (!isOn_.has_value()) {
        isOn_ = buttonPaintProperty->GetIsOnValue();
    }
    bool changed = false;
    if (buttonPaintProperty->HasIsOn()) {
        bool isOn = buttonPaintProperty->GetIsOnValue();
        changed = isOn ^ isOn_.value();
        isOn_ = isOn;
    }
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (isOn_.value()) {
        auto selectedColor = buttonPaintProperty->GetSelectedColor().value_or(checkedColor_);
        renderContext->UpdateBackgroundColor(selectedColor);
    } else {
        auto bgColor = buttonPaintProperty->GetBackgroundColor().value_or(unCheckedColor_);
        renderContext->UpdateBackgroundColor(bgColor);
    }

    if (changed) {
        auto toggleButtonEventHub = GetEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(toggleButtonEventHub);
        toggleButtonEventHub->UpdateChangeEvent(isOn_.value());
    }
    InitButtonAndText();
    HandleEnabled();
    InitTouchEvent();
    InitHoverEvent();
    InitOnKeyEvent();
}

void ToggleButtonPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(theme);
    auto backgroundColor = renderContext->GetBackgroundColor().value_or(theme->GetCheckedColor());
    if (!enabled) {
        if (host->GetFirstChild()) {
            auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
            CHECK_NULL_VOID(textNode);
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            auto color = textLayoutProperty->GetTextColorValue(textColor_);
            textLayoutProperty->UpdateTextColor(color.BlendOpacity(disabledAlpha_));
        }
        renderContext->OnBackgroundColorUpdate(backgroundColor.BlendOpacity(disabledAlpha_));
    } else {
        renderContext->OnBackgroundColorUpdate(backgroundColor);
    }
}

void ToggleButtonPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto buttonPattern = weak.Upgrade();
        buttonPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void ToggleButtonPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isLastSelected = false;
    if (paintProperty->HasIsOn()) {
        isLastSelected = paintProperty->GetIsOnValue();
    }
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Color selectedColor;
    auto buttonPaintProperty = host->GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(buttonPaintProperty);
    if (isLastSelected) {
        selectedColor = buttonPaintProperty->GetBackgroundColor().value_or(unCheckedColor_);
    } else {
        selectedColor = buttonPaintProperty->GetSelectedColor().value_or(checkedColor_);
    }
    paintProperty->UpdateIsOn(!isLastSelected);
    isOn_ = !isLastSelected;
    renderContext->UpdateBackgroundColor(selectedColor);
    auto buttonEventHub = GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->UpdateChangeEvent(!isLastSelected);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ToggleButtonPattern::InitButtonAndText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if ((!layoutProperty->GetCalcLayoutConstraint() ||
            !layoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height().has_value())) {
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(buttonHeight_)));
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!renderContext->HasBorderRadius()) {
        renderContext->UpdateBorderRadius({ buttonRadius_, buttonRadius_, buttonRadius_, buttonRadius_ });
    }
    if (!host->GetFirstChild()) {
        return;
    }
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (!textLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(textFontSize_);
    } else {
        layoutProperty->UpdateFontSize(textLayoutProperty->GetFontSizeValue(textFontSize_));
    }
    layoutProperty->UpdateLabel(textLayoutProperty->GetContentValue(""));
    textLayoutProperty->UpdateTextColor(textColor_);

    if (!textLayoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.left = CalcLength(textMargin_.ConvertToPx());
        margin.right = CalcLength(textMargin_.ConvertToPx());
        textLayoutProperty->UpdateMargin(margin);
    }
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
}

void ToggleButtonPattern::InitOnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (!pattern) {
            return false;
        }
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool ToggleButtonPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER) {
        OnClick();
        return true;
    }
    return false;
}

std::string ToggleButtonPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    jsonObj->Put("IsOn", isOn_.value_or(false));
    return jsonObj->ToString();
}

void ToggleButtonPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto toggleButtonPaintProperty = GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(toggleButtonPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("IsOn");
    toggleButtonPaintProperty->UpdateIsOn(jsonIsOn->GetBool());
    OnModifyDone();
}

void ToggleButtonPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(toggleTheme);
    checkedColor_ = toggleTheme->GetCheckedColor();
    unCheckedColor_ = toggleTheme->GetBackgroundColor();
    OnModifyDone();
}
} // namespace OHOS::Ace::NG
