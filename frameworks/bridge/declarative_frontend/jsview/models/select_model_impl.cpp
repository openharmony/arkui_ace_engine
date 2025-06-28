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

#include "bridge/declarative_frontend/jsview/models/select_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/select/select_component.h"
#include "core/components/select/select_theme.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void SelectModelImpl::Create(const std::vector<SelectParam>& params)
{
    auto selectTheme = JSViewAbstract::GetTheme<SelectTheme>();
    auto selectComponent = AceType::MakeRefPtr<SelectComponent>();
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetTheme(selectTheme);

    auto tipText = AceType::MakeRefPtr<TextComponent>("");
    selectComponent->SetTipText(tipText);

    for (size_t i = 0; i < params.size(); i++) {
        auto optionTheme = JSViewAbstract::GetTheme<SelectTheme>();
            if (!optionTheme) {
                LOGE("JSSelect: Get option theme is null.");
                continue;
            }
            auto optionComponent = AceType::MakeRefPtr<OHOS::Ace::OptionComponent>(optionTheme);
            auto textComponent = AceType::MakeRefPtr<OHOS::Ace::TextComponent>(params[i].text);
            if (!params[i].icon.empty()) {
                optionComponent->SetIcon(AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(params[i].icon));
            }
            optionComponent->SetTheme(optionTheme);
            optionComponent->SetText(textComponent);
            optionComponent->SetTextStyle(optionTheme->GetTitleStyle());
            optionComponent->SetSelectedTextStyle(optionTheme->GetTitleStyle());
            optionComponent->SetSelectedBackgroundColor(optionTheme->GetSelectedColor());
            optionComponent->SetValue(params[i].text);
            selectComponent->AppendSelectOption(optionComponent);
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(selectComponent);
    ViewStackProcessor::GetInstance()->Push(selectComponent);
}

void SelectModelImpl::SetSelected(int32_t idx)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    if (idx >= static_cast<int32_t>(option.size())) {
        LOGE("Input selected index error, use the default value");
        idx = 0;
    }

    auto tipText = selectComponent->GetTipText();
    auto optionComponent = selectComponent->GetSelectOption(idx);
    CHECK_NULL_VOID(optionComponent);
    optionComponent->SetSelected(true);

    auto optionText = optionComponent->GetText();
    CHECK_NULL_VOID(optionText);
    if (!selectComponent->HasSetTipText()) {
        tipText->SetData(optionText->GetData());
    }
}

void SelectModelImpl::SetValue(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto tipText = selectComponent->GetTipText();
    if (!value.empty()) {
        selectComponent->SetTipText(true);
    }
    tipText->SetData(value);
}

void SelectModelImpl::SetFontSize(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);

    TextStyle textStyle = selectComponent->GetSelectStyle();
    textStyle.SetFontSize(value);
    selectComponent->SetSelectStyle(std::move(textStyle));
}

void SelectModelImpl::SetFontWeight(const FontWeight& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);

    TextStyle textStyle = selectComponent->GetSelectStyle();
    textStyle.SetFontWeight(value);
    selectComponent->SetSelectStyle(std::move(textStyle));
}

void SelectModelImpl::SetFontFamily(const std::vector<std::string>& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);

    TextStyle textStyle = selectComponent->GetSelectStyle();
    textStyle.SetFontFamilies(value);
    selectComponent->SetSelectStyle(std::move(textStyle));
}

void SelectModelImpl::SetItalicFontStyle(const Ace::FontStyle& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);

    TextStyle textStyle = selectComponent->GetSelectStyle();
    textStyle.SetFontStyle(value);
    selectComponent->SetSelectStyle(std::move(textStyle));
}

void SelectModelImpl::SetFontColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);

    auto textStyle = selectComponent->GetSelectStyle();
    textStyle.SetTextColor(color);
    selectComponent->SetSelectStyle(std::move(textStyle));
}

void SelectModelImpl::SetSelectedOptionBgColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        if (optionItem) {
            optionItem->SetSelectedBackgroundColor(color);
        }
    }
}

void SelectModelImpl::SetSelectedOptionFontSize(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetSelectedTextStyle();
        textStyle.SetFontSize(value);
        optionItem->SetSelectedTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetSelectedOptionFontWeight(const FontWeight& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetSelectedTextStyle();
        textStyle.SetFontWeight(value);
        optionItem->SetSelectedTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetSelectedTextStyle();
        textStyle.SetFontFamilies(value);
        optionItem->SetSelectedTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetSelectedTextStyle();
        textStyle.SetFontStyle(value);
        optionItem->SetSelectedTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetSelectedOptionFontColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        if (optionItem) {
            TextStyle textStyle = optionItem->GetSelectedTextStyle();
            textStyle.SetTextColor(color);
            optionItem->SetSelectedTextStyle(textStyle);
        }
    }
}

void SelectModelImpl::SetOptionBgColor(const Color& color, bool isNormal)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        if (optionItem) {
            optionItem->SetBackgroundColor(color);
        }
    }
}

void SelectModelImpl::SetOptionFontSize(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetTextStyle();
        textStyle.SetFontSize(value);
        optionItem->SetTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetOptionFontWeight(const FontWeight& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetTextStyle();
        textStyle.SetFontWeight(value);
        optionItem->SetTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetOptionFontFamily(const std::vector<std::string>& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetTextStyle();
        textStyle.SetFontFamilies(value);
        optionItem->SetTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        TextStyle textStyle = optionItem->GetTextStyle();
        textStyle.SetFontStyle(value);
        optionItem->SetTextStyle(std::move(textStyle));
    }
}

void SelectModelImpl::SetOptionFontColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    auto popup = selectComponent->GetPopup();
    CHECK_NULL_VOID(popup);
    auto option = popup->GetSelectOptions();
    for (auto& optionItem : option) {
        if (optionItem) {
            TextStyle textStyle = optionItem->GetTextStyle();
            textStyle.SetTextColor(color);
            optionItem->SetTextStyle(textStyle);
        }
    }
}

void SelectModelImpl::SetOnSelect(NG::SelectEvent&& onSelect)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(component);
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetOnSelected(std::move(onSelect));
}

void SelectModelImpl::SetWidth(Dimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetWidth(value);
}

void SelectModelImpl::SetHeight(Dimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetHeight(value);
}

void SelectModelImpl::SetSize(Dimension& width, Dimension& height)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetWidth(width);
    selectComponent->SetHeight(height);
}

void SelectModelImpl::SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
    const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    CalcDimension topDimen;
    topDimen.SetValue(top.value().Value());
    selectComponent->SetTopPadding(topDimen);
    CalcDimension leftDimen;
    leftDimen.SetValue(left.value().Value());
    selectComponent->SetLeftPadding(leftDimen);
    CalcDimension rightDimen;
    rightDimen.SetValue(right.value().Value());
    selectComponent->SetRightPadding(rightDimen);
    CalcDimension bottomDimen;
    bottomDimen.SetValue(bottom.value().Value());
    selectComponent->SetBottomPadding(bottomDimen);
}

void SelectModelImpl::SetPadding(const CalcDimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetLeftPadding(value);
    selectComponent->SetTopPadding(value);
    selectComponent->SetRightPadding(value);
    selectComponent->SetBottomPadding(value);
}

void SelectModelImpl::SetPaddingLeft(const CalcDimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetLeftPadding(value);
}

void SelectModelImpl::SetPaddingTop(const CalcDimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetTopPadding(value);
}

void SelectModelImpl::SetPaddingRight(const CalcDimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetRightPadding(value);
}

void SelectModelImpl::SetPaddingBottom(const CalcDimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetBottomPadding(value);
}

void SelectModelImpl::SetSpace(const Dimension& value) {}

void SelectModelImpl::SetArrowPosition(const ArrowPosition value) {}

void SelectModelImpl::SetMenuAlign(const MenuAlign& menuAlign) {}

void SelectModelImpl::SetAvoidance(AvoidanceMode mode) {}

void SelectModelImpl::SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent) {}

void SelectModelImpl::SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent) {}

void SelectModelImpl::SetOptionWidth(const Dimension& value) {}

void SelectModelImpl::SetOptionHeight(const Dimension& value) {}

void SelectModelImpl::SetOptionWidthFitTrigger(bool isFitTrigger) {}

void SelectModelImpl::SetHasOptionWidth(bool haveOptionWidth) {}

void SelectModelImpl::SetMenuBackgroundColor(const Color& color) {}

void SelectModelImpl::SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle) {}

void SelectModelImpl::SetLayoutDirection(TextDirection value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto selectComponent = AceType::DynamicCast<SelectComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(selectComponent);
    selectComponent->SetTextDirection(value);
}

void SelectModelImpl::SetMenuOutline(const NG::MenuParam& menuParam) {}
} // namespace OHOS::Ace::Framework
