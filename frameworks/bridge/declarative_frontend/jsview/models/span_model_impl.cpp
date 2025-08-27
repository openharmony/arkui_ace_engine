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

#include "bridge/declarative_frontend/jsview/models/span_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void SpanModelImpl::Create(const std::string& content)
{
    auto spanComponent = AceType::MakeRefPtr<TextSpanComponent>(content);
    ViewStackProcessor::GetInstance()->ClaimElementId(spanComponent);
    ViewStackProcessor::GetInstance()->Push(spanComponent);

    // Init text style, allowScale is not supported in declarative.
    auto textStyle = spanComponent->GetTextStyle();
    textStyle.SetAllowScale(false);
    spanComponent->SetTextStyle(textStyle);
}

void SpanModelImpl::Create(const std::u16string& content)
{
    Create(UtfUtils::Str16DebugToStr8(content));
}

void SpanModelImpl::Create(const std::u16string& content, RefPtr<ResourceObject>& resObj)
{
    Create(UtfUtils::Str16DebugToStr8(content));
}

void SpanModelImpl::SetFont(const Font& value) {}

void SpanModelImpl::SetFontSize(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetFontSize(true);
    }
}

void SpanModelImpl::SetTextColor(const Color& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(value);
    component->SetTextStyle(textStyle);
    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetFontColor(true);
    }
}

void SpanModelImpl::SetItalicFontStyle(Ace::FontStyle value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontStyle(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetFontStyle(true);
    }
}

void SpanModelImpl::SetFontWeight(Ace::FontWeight value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetFontWeight(true);
    }
}

void SpanModelImpl::SetFontFamily(const std::vector<std::string>& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetFontFamily(true);
    }
}

void SpanModelImpl::SetTextDecoration(Ace::TextDecoration value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecoration(value);
    component->SetTextStyle(textStyle);
}

void SpanModelImpl::SetTextDecorationColor(const Color& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecorationColor(value);
    component->SetTextStyle(textStyle);
}

void SpanModelImpl::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextDecorationStyle(value);
    component->SetTextStyle(textStyle);
}

void SpanModelImpl::SetTextCase(Ace::TextCase value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextCase(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetTextCase(true);
    }
}

void SpanModelImpl::SetLetterSpacing(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetLetterSpacing(value);
    component->SetTextStyle(textStyle);

    auto declaration = component->GetDeclaration();
    if (declaration) {
        declaration->SetHasSetLetterSpacing(true);
    }
}

void SpanModelImpl::SetBaselineOffset(const Dimension& value) {}

RefPtr<TextSpanComponent> SpanModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    return AceType::DynamicCast<TextSpanComponent>(stack->GetMainComponent());
}

void SpanModelImpl::SetOnClick(std::function<void(BaseEventInfo*)>&& click)
{
    auto component = GetComponent();
    if (component) {
        component->SetOnClick(EventMarker(std::move(click)));
    }
}

void SpanModelImpl::SetLineHeight(const Dimension& value) {}

} // namespace OHOS::Ace::Framework
