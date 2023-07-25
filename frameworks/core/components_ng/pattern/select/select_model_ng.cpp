/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select/select_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void SetSelectDefaultSize(const RefPtr<FrameNode>& select)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto layoutProperty = select->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(theme->GetSelectMinWidth()), std::nullopt));
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme->GetSelectDefaultHeight())));
}
} // namespace

void SelectModelNG::Create(const std::vector<SelectParam>& params)
{
    LOGI("creating select component");
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto select = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ViewStackProcessor::GetInstance()->Push(select);

    SetSelectDefaultSize(select);
    auto pattern = select->GetPattern<SelectPattern>();
    pattern->BuildChild();
    // create menu node
    if (!pattern->GetMenuNode()) {
        auto menuWrapper = MenuView::Create(params, nodeId);
        pattern->SetMenuNode(menuWrapper);
        pattern->InitSelected();
    } else {
        auto menuNode = pattern->GetMenuNode();
        CHECK_NULL_VOID(menuNode);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        menuPattern->UpdateSelectParam(params);
    }
    // store option pointers in select
    auto menuContainer = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuContainer);
    pattern->ClearOptions();
    auto menuPattern = menuContainer->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    for (auto&& option : options) {
        pattern->AddOptionNode(option);
    }

    // delete menu when select node destroy
    auto destructor = [id = select->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    select->PushDestroyCallback(destructor);
}

void SelectModelNG::SetSelected(int32_t idx)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(idx);
}

void SelectModelNG::SetValue(const std::string& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetValue(value);
}

void SelectModelNG::SetFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontSize(value);
}

void SelectModelNG::SetFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontWeight(value);
}

void SelectModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontFamily(value);
}

void SelectModelNG::SetItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetItalicFontStyle(value);
}

void SelectModelNG::SetFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontColor(color);
}

void SelectModelNG::SetSelectedOptionBgColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionBgColor(color);
}

void SelectModelNG::SetSelectedOptionFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontSize(value);
}

void SelectModelNG::SetSelectedOptionFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontWeight(value);
}

void SelectModelNG::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontFamily(value);
}

void SelectModelNG::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionItalicFontStyle(value);
}

void SelectModelNG::SetSelectedOptionFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontColor(color);
}

void SelectModelNG::SetOptionBgColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionBgColor(color);
}

void SelectModelNG::SetOptionFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontSize(value);
}

void SelectModelNG::SetOptionFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontWeight(value);
}

void SelectModelNG::SetOptionFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontFamily(value);
}

void SelectModelNG::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionItalicFontStyle(value);
}

void SelectModelNG::SetOptionFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontColor(color);
}

void SelectModelNG::SetOnSelect(NG::SelectEvent&& onSelect)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectEvent(std::move(onSelect));
}

void SelectModelNG::SetWidth(Dimension& value)
{
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetWidth(NG::CalcLength(value));
}

void SelectModelNG::SetHeight(Dimension& value)
{
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetHeight(NG::CalcLength(value));
}

void SelectModelNG::SetSize(Dimension& width, Dimension& height)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }

    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetWidth(NG::CalcLength(width));
    ViewAbstract::SetHeight(NG::CalcLength(height));
}

void SelectModelNG::SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
    const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left = NG::CalcLength(
                left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right = NG::CalcLength(
                right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPadding(const CalcDimension& value)
{
    if (value.Unit() == DimensionUnit::CALC) {
        // padding must great or equal zero.
        ViewAbstract::SetPadding(
            NG::CalcLength(value.IsNonNegative() ? value.CalcValue() : CalcDimension().CalcValue()));
    } else {
        // padding must great or equal zero.
        ViewAbstract::SetPadding(NG::CalcLength(value.IsNonNegative() ? value : CalcDimension()));
    }
}

void SelectModelNG::SetPaddingLeft(const CalcDimension& leftValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    paddings.bottom = std::nullopt;

    if (!NearEqual(leftValue.Value(), 0.0)) {
        if (leftValue.Unit() == DimensionUnit::CALC) {
            paddings.left = NG::CalcLength(
                leftValue.IsNonNegative() ? leftValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(leftValue.IsNonNegative() ? leftValue : CalcDimension());
        }
    }
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingTop(const CalcDimension& topValue)
{
    NG::PaddingProperty paddings;
    if (!NearEqual(topValue.Value(), 0.0)) {
        if (topValue.Unit() == DimensionUnit::CALC) {
            paddings.top = NG::CalcLength(
                topValue.IsNonNegative() ? topValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(topValue.IsNonNegative() ? topValue : CalcDimension());
        }
    }
    paddings.bottom = std::nullopt;
    paddings.left = std::nullopt;
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingRight(const CalcDimension& rightValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    paddings.bottom = std::nullopt;
    paddings.left = std::nullopt;
    if (!NearEqual(rightValue.Value(), 0.0)) {
        if (rightValue.Unit() == DimensionUnit::CALC) {
            paddings.right = NG::CalcLength(
                rightValue.IsNonNegative() ? rightValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(rightValue.IsNonNegative() ? rightValue : CalcDimension());
        }
    }
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingBottom(const CalcDimension& buttomValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    if (!NearEqual(buttomValue.Value(), 0.0)) {
        if (buttomValue.Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                buttomValue.IsNonNegative() ? buttomValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(
                buttomValue.IsNonNegative() ? buttomValue : CalcDimension());
        }
    }
    paddings.left = std::nullopt;
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetSpace(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSpace(value);
}

void SelectModelNG::SetArrowPosition(const ArrowPosition value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetArrowPosition(value);
}

void SelectModelNG::SetMenuAlign(const MenuAlign& menuAlign)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuAlign(menuAlign);
}

void SelectModelNG::SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectChangeEvent(std::move(selectChangeEvent));
}

void SelectModelNG::SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetValueChangeEvent(std::move(valueChangeEvent));
}
} // namespace OHOS::Ace::NG
