/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select/select_model_static.h"

#include "core/components_ng/pattern/menu/menu_view.h"

namespace OHOS::Ace::NG {

void SelectModelStatic::SetDivider(FrameNode* frameNode, const std::optional<NG::SelectDivider>& divider)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (divider.has_value()) {
        pattern->SetDivider(divider.value());
    } else {
        NG::SelectDivider defaultDivider;
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        Dimension defaultStrokeWidth = 0.0_vp;
        Dimension defaultMargin = -1.0_vp;
        Color defaultColor = Color::TRANSPARENT;
        // Set default strokeWidth and color
        if (selectTheme) {
            defaultStrokeWidth = selectTheme->GetDefaultDividerWidth();
            defaultColor = selectTheme->GetLineColor();
            defaultDivider.strokeWidth = defaultStrokeWidth;
            defaultDivider.color = defaultColor;
            defaultDivider.startMargin = defaultMargin;
            defaultDivider.endMargin = defaultMargin;
        }
        pattern->SetDivider(defaultDivider);
    }
    pattern->SetDividerMode(std::nullopt);
}

NG::SelectDivider SelectModelStatic::GetDefaultDivider(FrameNode* frameNode)
{
    NG::SelectDivider defaultDivider;
    CHECK_NULL_RETURN(frameNode, defaultDivider);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, defaultDivider);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(selectTheme, defaultDivider);
    defaultDivider.strokeWidth = selectTheme->GetDefaultDividerWidth();
    defaultDivider.color = selectTheme->GetLineColor();
    Dimension defaultMargin = -1.0_vp;
    defaultDivider.startMargin = defaultMargin;
    defaultDivider.endMargin = defaultMargin;
    return defaultDivider;
}

void SelectModelStatic::SetArrowPosition(FrameNode* frameNode, const std::optional<ArrowPosition>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    ArrowPosition arrowPosition = value.value_or(ArrowPosition::END);
    pattern->SetArrowPosition(arrowPosition);
}

void SelectModelStatic::SetSpace(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value) {
        pattern->SetSpace(value.value());
    } else {
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        pattern->SetSpace(selectTheme->GetContentSpinnerPadding());
    }
}

void SelectModelStatic::SetValue(FrameNode* frameNode, const std::optional<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetValue(value.value_or(""));
}

void SelectModelStatic::SetSelected(FrameNode* frameNode, const std::optional<int32_t>& idx)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(idx.value_or(0));
}

void SelectModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetFontSize(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        pattern->SetFontSize(selectTheme->GetFontSize());
    }
}

void SelectModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontWeight(value.value_or(FontWeight::MEDIUM));
}

void SelectModelStatic::SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetItalicFontStyle(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto textTheme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_VOID(textTheme);
        pattern->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    }
}

void SelectModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color.has_value()) {
        pattern->SetFontColor(color.value());
    } else {
        pattern->ResetFontColor();
    }
}

void SelectModelStatic::SetSelectedOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color.has_value()) {
        pattern->SetSelectedOptionBgColor(color.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        auto bgColor = selectTheme->GetSelectedColor();
        pattern->SetSelectedOptionBgColor(bgColor);
    }
}

void SelectModelStatic::SetOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetOptionFontSize(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        pattern->SetOptionFontSize(selectTheme->GetMenuFontSize());
    }
}

void SelectModelStatic::SetOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontWeight(value.value_or(FontWeight::REGULAR));
}

void SelectModelStatic::SetOptionItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetOptionItalicFontStyle(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto textTheme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_VOID(textTheme);
        pattern->SetOptionItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    }
}

void SelectModelStatic::SetOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color.has_value()) {
        pattern->SetOptionBgColor(color.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        auto bgColor = selectTheme->GetBackgroundColor();
        pattern->SetOptionBgColor(bgColor);
    }
}

void SelectModelStatic::SetSelectedOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color.has_value()) {
        pattern->SetSelectedOptionFontColor(color.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        auto textColor = selectTheme->GetSelectedColorText();
        pattern->SetSelectedOptionFontColor(textColor);
    }
}

void SelectModelStatic::SetSelectedOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetSelectedOptionFontSize(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto selectTheme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(selectTheme);
        pattern->SetSelectedOptionFontSize(selectTheme->GetMenuFontSize());
    }
}

void SelectModelStatic::SetSelectedOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontWeight(value.value_or(FontWeight::REGULAR));
}

void SelectModelStatic::SetSelectedOptionItalicFontStyle(
    FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->SetSelectedOptionItalicFontStyle(value.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto textTheme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_VOID(textTheme);
        pattern->SetSelectedOptionItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    }
}

void SelectModelStatic::SetOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color.has_value()) {
        pattern->SetOptionFontColor(color.value());
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        CHECK_NULL_VOID(theme);
        auto textColor = theme->GetMenuFontColor();
        pattern->SetOptionFontColor(textColor);
    }
}

void SelectModelStatic::SetOptionWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidth(value.value_or(Dimension()));
}

void SelectModelStatic::SetOptionHeight(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (value) {
        pattern->SetOptionHeight(value.value());
    }
}

void SelectModelStatic::SetOptionWidthFitTrigger(FrameNode* frameNode, std::optional<bool> isFitTrigger)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidthFitTrigger(isFitTrigger.value_or(false));
}

void SelectModelStatic::SetMenuBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuBackgroundColor(color.value_or(Color::TRANSPARENT));
}

void SelectModelStatic::SetSelectChangeEvent(FrameNode* frameNode, NG::SelectChangeEvent&& selectChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto hub = frameNode->GetEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectChangeEvent(std::move(selectChangeEvent));
}

void SelectModelStatic::SetValueChangeEvent(FrameNode* frameNode, NG::ValueChangeEvent&& valueChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto hub = frameNode->GetEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetValueChangeEvent(std::move(valueChangeEvent));
}

void SelectModelStatic::SetDividerStyle(
    FrameNode* frameNode, const std::optional<NG::SelectDivider>& divider, const std::optional<DividerMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    if (divider.has_value()) {
        pattern->SetDivider(divider.value());
        pattern->SetDividerMode(mode);
    } else {
        ResetDividerStyle(frameNode);
    }
}

void SelectModelStatic::ResetDividerStyle(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    NG::SelectDivider divider;
    Dimension defaultMargin = -1.0_vp;
    divider.strokeWidth = selectTheme->GetDefaultDividerWidth();
    divider.color = selectTheme->GetLineColor();
    divider.startMargin = defaultMargin;
    divider.endMargin = defaultMargin;
    pattern->SetDivider(divider);
    pattern->SetDividerMode(std::nullopt);
}

// void SelectModelStatic::SetAvoidance(FrameNode* frameNode, const std::optional<Avoidance>& avoidance)
// {
//     CHECK_NULL_VOID(frameNode);
//     auto pattern = frameNode->GetPattern<SelectPattern>();
//     CHECK_NULL_VOID(pattern);
//     pattern->SetAvoidance(avoidance.value_or(Avoidance()));
// }

void SelectModelStatic::SetMenuOutline(FrameNode* frameNode, const std::optional<MenuParam>& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuOutline(menuParam.value_or(MenuParam()));
}
void SelectModelStatic::SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (controlSize.has_value()) {
        pattern->SetControlSize(controlSize.value());
    } else {
        pattern->SetControlSize(ControlSize::NORMAL);
    }
}
} // namespace OHOS::Ace::NG
