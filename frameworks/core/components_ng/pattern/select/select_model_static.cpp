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
    pattern->SetDivider(divider);
    pattern->SetDividerMode(std::nullopt);
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
    pattern->SetSelected(idx.value_or(-1));
}

void SelectModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontSize(value);
}

void SelectModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontWeight(value);
}

void SelectModelStatic::SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetItalicFontStyle(value);
}

void SelectModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    if (color) {
        pattern->SetFontColor(color);
    } else {
        pattern->ResetFontColor();
    }
}

void SelectModelStatic::SetSelectedOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionBgColor(color);
}

void SelectModelStatic::SetOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontSize(value);
}

void SelectModelStatic::SetOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontWeight(value);
}

void SelectModelStatic::SetOptionItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionItalicFontStyle(value);
}

void SelectModelStatic::SetOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionBgColor(color);
}

void SelectModelStatic::SetSelectedOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontColor(color);
}

void SelectModelStatic::SetSelectedOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontSize(value);
}

void SelectModelStatic::SetSelectedOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontWeight(value);
}

void SelectModelStatic::SetSelectedOptionItalicFontStyle(
    FrameNode* frameNode, const std::optional<Ace::FontStyle>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionItalicFontStyle(value);
}

void SelectModelStatic::SetOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontColor(color);
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
    pattern->SetMenuBackgroundColor(color);
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

void SelectModelStatic::SetDividerStyle(
    FrameNode* frameNode, const std::optional<NG::SelectDivider>& divider, const std::optional<DividerMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDivider(divider);
    pattern->SetDividerMode(mode);
}

void SelectModelStatic::SetAvoidance(FrameNode* frameNode, const std::optional<Avoidance>& avoidance)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAvoidance(avoidance.value_or(Avoidance()));
}

void SelectModelStatic::SetMenuOutline(FrameNode* frameNode, const std::optional<MenuParam>& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuOutline(menuParam.value_or(MenuParam()));
}
} // namespace OHOS::Ace::NG
