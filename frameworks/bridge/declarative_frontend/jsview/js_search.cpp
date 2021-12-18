/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_search.h"

#include "core/components/search/search_component.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/text_field_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

namespace {

const TextInputAction INPUT_TEXTINPUTACTION_VALUE_DEFAULT = TextInputAction::UNSPECIFIED;
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = {
    "sans-serif",
};

Radius defaultRadius;
constexpr Dimension BOX_HOVER_RADIUS = 18.0_vp;
bool isPaddingChanged;

void InitializeDefaultValue(const RefPtr<BoxComponent>& boxComponent,
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

void UpdateDecorationStyle(const RefPtr<BoxComponent>& boxComponent,
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

void InitializeComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
                         OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent,
                         const OHOS::Ace::RefPtr<OHOS::Ace::SearchTheme>& searchTheme,
                         const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme)
{
    textFieldComponent->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    textFieldComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());

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

    std::function<void(const std::string&)> submitEvent;
    searchComponent->SetSubmitEvent(submitEvent);
    searchComponent->SetChild(textFieldComponent);
    searchComponent->SetTextEditController(textFieldComponent->GetTextEditController());
    searchComponent->SetCloseIconSize(searchTheme->GetCloseIconSize());
    searchComponent->SetCloseIconHotZoneHorizontal(searchTheme->GetCloseIconHotZoneSize());
    searchComponent->SetHoverColor(textFieldTheme->GetHoverColor());
    searchComponent->SetPressColor(textFieldTheme->GetPressColor());
    isPaddingChanged = true;
}

void PrepareSpecializedComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
                                 OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent)
{
    Border boxBorder;

    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();

    boxComponent->SetMouseAnimationType(HoverAnimationType::OPACITY);
    if (boxComponent->GetBackDecoration()) {
        boxBorder = boxComponent->GetBackDecoration()->GetBorder();
    }
    searchComponent->SetTextDirection(TextDirection::RTL);
    textFieldComponent->SetTextDirection(TextDirection::RTL);
    UpdateDecorationStyle(boxComponent, textFieldComponent, boxBorder, true);
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

}

void JSSearch::JSBind(BindingTarget globalObj)
{
    JSClass<JSSearch>::Declare("Search");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSSearch>::StaticMethod("create", &JSSearch::Create, opt);
    JSClass<JSSearch>::StaticMethod("searchButton", &JSSearch::SetSearchButton, opt);
    JSClass<JSSearch>::StaticMethod("placeholderColor", &JSSearch::SetPlaceholderColor, opt);
    JSClass<JSSearch>::StaticMethod("placeholderFont", &JSSearch::SetPlaceholderFont, opt);
    JSClass<JSSearch>::StaticMethod("onSubmit", &JSSearch::OnSubmit, opt);
    JSClass<JSSearch>::StaticMethod("onChange", &JSSearch::OnChange, opt);

    JSClass<JSSearch>::Inherit<JSViewAbstract>();
    JSClass<JSSearch>::Bind(globalObj);
}

void JSSearch::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to be an object");
        return;
    }

    auto searchComponent = AceType::MakeRefPtr<OHOS::Ace::SearchComponent>();
    auto textFieldComponent = AceType::MakeRefPtr<OHOS::Ace::TextFieldComponent>();

    auto textFieldTheme = GetTheme<TextFieldTheme>();
    auto searchTheme = GetTheme<SearchTheme>();

    InitializeComponent(searchComponent, textFieldComponent, searchTheme, textFieldTheme);

    PrepareSpecializedComponent(searchComponent, textFieldComponent);

    auto param = JSRef<JSObject>::Cast(info[0]);
    auto value = param->GetProperty("value");
    if (!value->IsNull() && value->IsString()) {
        auto key = value->ToString();
        textFieldComponent->SetValue(key);
    }

    auto placeholde = param->GetProperty("placeholder");
    if (!placeholde->IsNull() && placeholde->IsString()) {
        auto tip = placeholde->ToString();
        textFieldComponent->SetPlaceholder(tip);
    }

    auto icon = param->GetProperty("icon");
    if (!icon->IsNull() && icon->IsString()) {
        auto src = icon->ToString();
        searchComponent->SetCloseIconSrc(src);
    }

    ViewStackProcessor::GetInstance()->Push(searchComponent);
}

void JSSearch::SetSearchButton(const std::string& text)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchcomponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchcomponent) {
        LOGE("component error");
        return;
    }

    searchcomponent->SetSearchText(text);
}

void JSSearch::SetPlaceholderColor(const JSCallbackInfo& info)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchcomponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchcomponent) {
        LOGE("search component error");
        return;
    }

    auto childComponent = searchcomponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }

    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }

    auto value = JSRef<JSVal>::Cast(info[0]);

    Color colorVal;
    if (ParseJsColor(value, colorVal)) {
        textFieldComponent->SetPlaceholderColor(colorVal);
        textFieldComponent->SetFocusPlaceholderColor(colorVal);
    }
}

void JSSearch::SetPlaceholderFont(const JSCallbackInfo& info)
{
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto searchcomponent = AceType::DynamicCast<SearchComponent>(component);
    if (!searchcomponent) {
        LOGE("search component error");
        return;
    }
    auto childComponent = searchcomponent->GetChild();
    if (!childComponent) {
        LOGE("component error");
        return;
    }
    auto textFieldComponent = AceType::DynamicCast<TextFieldComponent>(childComponent);
    if (!textFieldComponent) {
        LOGE("text component error");
        return;
    }

    auto size = param->GetProperty("size");
    TextStyle textStyle = textFieldComponent->GetTextStyle();

    if (!size->IsNull() && size->IsNumber()) {
        Dimension fontSize;
        if (ParseJsDimensionFp(size, fontSize)) {
            textStyle.SetFontSize(fontSize);
        }
    }

    auto weight = param->GetProperty("weight");
    if (!weight->IsNull() && weight->IsNumber()) {
        FontWeight weightVal = static_cast<FontWeight>(weight->ToNumber<int32_t>());
        textStyle.SetFontWeight(weightVal);
    }

    auto family = param->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        textStyle.SetFontFamilies(ConvertStrToFontFamilies(familyVal));
    }

    auto style = param->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        FontStyle styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        textStyle.SetFontStyle(styleVal);
    }
    textFieldComponent->SetTextStyle(textStyle);
}

void JSSearch::OnSubmit(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&SearchComponent::SetOnSubmit, info)) {
        LOGE("Failed to bind event");
    }
    info.ReturnSelf();
}

void JSSearch::OnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&SearchComponent::SetOnChange, info)) {
        LOGE("Failed to bind event");
    }
    info.ReturnSelf();
}

}