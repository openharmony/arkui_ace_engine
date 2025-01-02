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

#include "bridge/declarative_frontend/jsview/models/search_model_impl.h"

#include <utility>

#include "base/utils/utf_helper.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

namespace {
const TextInputAction INPUT_TEXTINPUTACTION_VALUE_DEFAULT = TextInputAction::UNSPECIFIED;
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = {
    "sans-serif",
};
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
Radius defaultRadius;
constexpr Dimension BOX_HOVER_RADIUS = 18.0_vp;
bool isPaddingChanged;
} // namespace

RefPtr<TextFieldControllerBase> SearchModelImpl::Create(const std::optional<std::u16string>& value,
    const std::optional<std::u16string>& placeholder, const std::optional<std::string>& icon)
{
    auto searchComponent = AceType::MakeRefPtr<OHOS::Ace::SearchComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(searchComponent);
    ViewStackProcessor::GetInstance()->Push(searchComponent);
    auto textFieldComponent = AceType::MakeRefPtr<OHOS::Ace::TextFieldComponent>();
    auto textFieldTheme = JSViewAbstract::GetTheme<TextFieldTheme>();
    auto searchTheme = JSViewAbstract::GetTheme<SearchTheme>();
    InitializeComponent(searchComponent, textFieldComponent, searchTheme, textFieldTheme);
    PrepareSpecializedComponent(searchComponent, textFieldComponent);
    if (value.has_value()) {
        textFieldComponent->SetValue(UtfUtils::Str16DebugToStr8(value.value()));
    }
    if (placeholder.has_value()) {
        textFieldComponent->SetPlaceholder(UtfUtils::Str16DebugToStr8(placeholder.value()));
    }
    if (icon.has_value()) {
        textFieldComponent->SetIconImage(icon.value());
    }
    return textFieldComponent->GetTextFieldController();
}

void SearchModelImpl::SetSearchButton(const std::string& text)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("component error");
        return;
    }
    searchComponent->SetSearchText(text);
}

void SearchModelImpl::SetPlaceholderColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    textFieldComponent->SetPlaceholderColor(color);
    textFieldComponent->SetFocusPlaceholderColor(color);
}

void SearchModelImpl::SetPlaceholderFont(const Font& font)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    TextStyle textStyle = searchComponent->GetPlaceHoldStyle();
    if (font.fontSize && font.fontSize->IsNonNegative()) {
        textStyle.SetFontSize(font.fontSize.value());
    }
    if (font.fontWeight) {
        textStyle.SetFontWeight(font.fontWeight.value());
    }
    if (font.fontStyle) {
        textStyle.SetFontStyle(font.fontStyle.value());
    }
    if (!font.fontFamilies.empty()) {
        textStyle.SetFontFamilies(font.fontFamilies);
    }
    textFieldComponent->SetPlaceHoldStyle(textStyle);
}

void SearchModelImpl::SetTextFont(const Font& font)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchComponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchComponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }
    TextStyle textStyle = searchComponent->GetEditingStyle();
    if (font.fontSize && font.fontSize->IsNonNegative()) {
        textStyle.SetFontSize(font.fontSize.value());
    }
    if (font.fontWeight) {
        textStyle.SetFontWeight(font.fontWeight.value());
    }
    if (font.fontStyle) {
        textStyle.SetFontStyle(font.fontStyle.value());
    }
    if (!font.fontFamilies.empty()) {
        textStyle.SetFontFamilies(font.fontFamilies);
    }
    textFieldComponent->SetEditingStyle(textStyle);
}

void SearchModelImpl::SetTextAlign(const TextAlign& textAlign)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto childComponent = component->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    textFieldComponent->SetTextAlign(textAlign);
}

void SearchModelImpl::SetCopyOption(const CopyOptions& copyOptions)
{
    JSViewSetProperty(&TextFieldComponent::SetCopyOption, copyOptions);
}

void SearchModelImpl::SetFocusable(bool focusable)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusable(focusable);
}

void SearchModelImpl::SetFocusNode(bool isFocusNode)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusNode(!isFocusNode);
}

void SearchModelImpl::SetHeight(const Dimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(searchComponent);
    auto childComponent = searchComponent->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    textFieldComponent->SetHeight(value);
}

void SearchModelImpl::SetMinFontScale(const float value) {}

void SearchModelImpl::SetMaxFontScale(const float value) {}

void SearchModelImpl::SetBackBorder()
{
    auto stack = ViewStackProcessor::GetInstance();
    auto searchComponent = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(searchComponent);
    auto childComponent = searchComponent->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    auto decoration = textFieldComponent->GetDecoration();
    CHECK_NULL_VOID(decoration);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto boxDecoration = box->GetBackDecoration();
    if (boxDecoration) {
        decoration->SetBorder(boxDecoration->GetBorder());
        Border border = {};
        boxDecoration->SetBorder(border);
    }
    textFieldComponent->SetOriginBorder(decoration->GetBorder());
}

void SearchModelImpl::SetOnSubmit(std::function<void(const std::string&)>&& onSubmit)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->SetOnSubmit(std::move(onSubmit));
}

void SearchModelImpl::SetOnChange(std::function<void(const std::u16string&, PreviewText&)>&& onChange)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto onChangeImpl = [onChange] (const std::string& value) {
        if (!onChange) {
            PreviewText previewText {};
            onChange(UtfUtils::Str8DebugToStr16(value), previewText);
        }
    };
    component->SetOnChange(std::move(onChangeImpl));
}

void SearchModelImpl::SetOnCopy(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto childComponent = component->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    auto onCopy = [func] (const std::string& value) {
        if (!func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    textFieldComponent->SetOnCopy(std::move(onCopy));
}

void SearchModelImpl::SetOnCut(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto childComponent = component->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    auto onCut = [func] (const std::string& value) {
        if (!func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    textFieldComponent->SetOnCut(std::move(onCut));
}

void SearchModelImpl::SetOnPaste(std::function<void(const std::u16string&)>&& func)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<SearchComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto childComponent = component->GetChild();
    CHECK_NULL_VOID(childComponent);
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    CHECK_NULL_VOID(textFieldComponent);
    auto onPaste = [func] (const std::string& value) {
        if (!func) {
            func(UtfUtils::Str8DebugToStr16(value));
        }
    };
    textFieldComponent->SetOnPaste(std::move(onPaste));
}

void SearchModelImpl::InitializeDefaultValue(const RefPtr<BoxComponent>& boxComponent,
    const RefPtr<TextFieldComponent>& component, const RefPtr<TextFieldTheme>& theme)
{
    component->SetAction(INPUT_TEXTINPUTACTION_VALUE_DEFAULT);
    component->SetCursorColor(theme->GetCursorColor());
    component->SetCursorRadius(theme->GetCursorRadius());
    component->SetPlaceholderColor(theme->GetPlaceholderColor());

    component->SetFocusBgColor(theme->GetFocusBgColor());
    component->SetFocusPlaceholderColor(theme->GetFocusPlaceholderColor());
    component->SetFocusTextColor(theme->GetFocusTextColor());
    component->SetBgColor(theme->GetBgColor());
    component->SetTextColor(theme->GetTextColor());
    component->SetSelectedColor(theme->GetSelectedColor());
    component->SetHoverColor(theme->GetHoverColor());
    component->SetPressColor(theme->GetPressColor());
    component->SetNeedFade(theme->NeedFade());
    component->SetShowEllipsis(theme->ShowEllipsis());

    TextStyle textStyle = component->GetTextStyle();
    textStyle.SetTextColor(theme->GetTextColor());
    textStyle.SetFontSize(theme->GetFontSize());
    textStyle.SetFontWeight(theme->GetFontWeight());
    textStyle.SetFontFamilies(INPUT_FONT_FAMILY_VALUE);
    component->SetTextStyle(textStyle);

    component->SetCountTextStyle(theme->GetCountTextStyle());
    component->SetOverCountStyle(theme->GetOverCountStyle());
    component->SetCountTextStyleOuter(theme->GetCountTextStyleOuter());
    component->SetOverCountStyleOuter(theme->GetOverCountStyleOuter());

    component->SetErrorTextStyle(theme->GetErrorTextStyle());
    component->SetErrorSpacing(theme->GetErrorSpacing());
    component->SetErrorIsInner(theme->GetErrorIsInner());
    component->SetErrorBorderWidth(theme->GetErrorBorderWidth());
    component->SetErrorBorderColor(theme->GetErrorBorderColor());

    RefPtr<Decoration> decoration = AceType::MakeRefPtr<Decoration>();
    decoration->SetPadding(theme->GetPadding());
    decoration->SetBackgroundColor(theme->GetBgColor());
    decoration->SetBorderRadius(theme->GetBorderRadius());
    defaultRadius = theme->GetBorderRadius();
    const auto& boxDecoration = boxComponent->GetBackDecoration();
    if (boxDecoration) {
        decoration->SetImage(boxDecoration->GetImage());
        decoration->SetGradient(boxDecoration->GetGradient());
    }
    component->SetDecoration(decoration);

    component->SetIconSize(theme->GetIconSize());
    component->SetIconHotZoneSize(theme->GetIconHotZoneSize());

    boxComponent->SetPadding(theme->GetPadding());
    component->SetHeight(theme->GetHeight());
}

void SearchModelImpl::UpdateDecorationStyle(const RefPtr<BoxComponent>& boxComponent,
    const RefPtr<TextFieldComponent>& component, const Border& boxBorder, bool hasBoxRadius)
{
    RefPtr<Decoration> decoration = component->GetDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
    }
    if (hasBoxRadius) {
        decoration->SetBorder(boxBorder);
    } else {
        Border border = decoration->GetBorder();
        border.SetLeftEdge(boxBorder.Left());
        border.SetRightEdge(boxBorder.Right());
        border.SetTopEdge(boxBorder.Top());
        border.SetBottomEdge(boxBorder.Bottom());
        border.SetBorderRadius(defaultRadius);
        decoration->SetBorder(border);
    }
    component->SetOriginBorder(decoration->GetBorder());

    if (!boxComponent) {
        return;
    }
    RefPtr<Decoration> boxDecoration = boxComponent->GetBackDecoration();
    if (boxDecoration && (boxDecoration->GetImage() || boxDecoration->GetGradient().IsValid())) {
        // clear box properties except background image and radius.
        boxDecoration->SetBackgroundColor(Color::TRANSPARENT);
        Border border;
        if (!hasBoxRadius) {
            border.SetBorderRadius(defaultRadius);
        } else {
            border.SetTopLeftRadius(boxBorder.TopLeftRadius());
            border.SetTopRightRadius(boxBorder.TopRightRadius());
            border.SetBottomLeftRadius(boxBorder.BottomLeftRadius());
            border.SetBottomRightRadius(boxBorder.BottomRightRadius());
        }
        boxDecoration->SetBorder(border);
    } else {
        RefPtr<Decoration> backDecoration = AceType::MakeRefPtr<Decoration>();
        backDecoration->SetBorderRadius(Radius(BOX_HOVER_RADIUS));
        boxComponent->SetBackDecoration(backDecoration);
    }
    boxComponent->SetPadding(Edge());
}

void SearchModelImpl::InitializeComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
    OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent,
    const OHOS::Ace::RefPtr<OHOS::Ace::SearchTheme>& searchTheme,
    const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme)
{
    textFieldComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    textFieldComponent->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    InitializeDefaultValue(boxComponent, textFieldComponent, textFieldTheme);
    boxComponent->SetBackDecoration(nullptr);
    boxComponent->SetPadding(Edge());
    textFieldComponent->SetIconSize(searchTheme->GetIconSize());
    textFieldComponent->SetIconHotZoneSize(searchTheme->GetCloseIconHotZoneSize());
    Edge decorationPadding;
    Dimension leftPadding = searchTheme->GetLeftPadding();
    Dimension rightPadding = searchTheme->GetRightPadding();
    decorationPadding = Edge(rightPadding.Value(), 0.0, leftPadding.Value(), 0.0, leftPadding.Unit());
    auto textFieldDecoration = textFieldComponent->GetDecoration();
    if (textFieldDecoration) {
        textFieldDecoration->SetPadding(decorationPadding);
        textFieldDecoration->SetBorderRadius(searchTheme->GetBorderRadius());
        textFieldComponent->SetOriginBorder(textFieldDecoration->GetBorder());
    }
    textFieldComponent->SetAction(TextInputAction::SEARCH);
    textFieldComponent->SetWidthReserved(searchTheme->GetTextFieldWidthReserved());
    textFieldComponent->SetTextColor(searchTheme->GetTextColor());
    textFieldComponent->SetFocusTextColor(searchTheme->GetFocusTextColor());
    textFieldComponent->SetPlaceholderColor(searchTheme->GetPlaceholderColor());
    textFieldComponent->SetFocusPlaceholderColor(searchTheme->GetFocusPlaceholderColor());
    textFieldComponent->SetBlockRightShade(searchTheme->GetBlockRightShade());

    auto textStyle = textFieldComponent->GetTextStyle();
    searchComponent->SetPlaceHoldStyle(textStyle);
    searchComponent->SetEditingStyle(textStyle);

    std::function<void(const std::string&)> submitEvent;
    searchComponent->SetSubmitEvent(submitEvent);
    searchComponent->SetChild(textFieldComponent);
    searchComponent->SetTextEditController(textFieldComponent->GetTextEditController());
    searchComponent->SetCloseIconSize(searchTheme->GetCloseIconSize());
    searchComponent->SetCloseIconHotZoneHorizontal(searchTheme->GetCloseIconHotZoneSize());
    searchComponent->SetHoverColor(textFieldTheme->GetHoverColor());
    searchComponent->SetPressColor(textFieldTheme->GetPressColor());
    isPaddingChanged = false;
}

void SearchModelImpl::PrepareSpecializedComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
    OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent)
{
    Border boxBorder;

    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();

    boxComponent->SetMouseAnimationType(HoverAnimationType::BOARD);
    if (boxComponent->GetBackDecoration()) {
        boxBorder = boxComponent->GetBackDecoration()->GetBorder();
    }
    UpdateDecorationStyle(boxComponent, textFieldComponent, boxBorder, false);
    if (GreatOrEqual(boxComponent->GetHeightDimension().Value(), 0.0)) {
        textFieldComponent->SetHeight(boxComponent->GetHeightDimension());
    }
    if (isPaddingChanged) {
        auto padding = textFieldComponent->GetDecoration()->GetPadding();
        if (searchComponent->GetTextDirection() == TextDirection::RTL) {
            padding.SetLeft(padding.Left() + searchComponent->GetCloseIconHotZoneHorizontal());
        } else {
            padding.SetRight(padding.Right() + searchComponent->GetCloseIconHotZoneHorizontal());
        }
        textFieldComponent->GetDecoration()->SetPadding(padding);
        searchComponent->SetDecoration(textFieldComponent->GetDecoration());
        isPaddingChanged = false;
    }
}

} // namespace OHOS::Ace::Framework
