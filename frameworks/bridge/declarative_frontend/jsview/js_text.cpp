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

#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

#include <sstream>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "core/components/declaration/text/text_declaration.h"
#include "core/components/text/text_theme.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr Dimension DEFAULT_FONT_SZIE = 30.0_px;
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::LEFT,
    TextAlign::RIGHT, TextAlign::JUSTIFY };

}; // namespace

void JSText::SetFontSize(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetFontWeight(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(ConvertStrToFontWeight(value));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetTextColor(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(Color::FromString(value));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetTextOverflow(const JSCallbackInfo& info)
{
    auto component = GetComponent();
    if (info[0]->IsObject() && component) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> overflowValue = obj->GetProperty("overflow");

        if (overflowValue->IsNumber()) {
            auto overflow = overflowValue->ToNumber<int32_t>();
            if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
                auto textStyle = component->GetTextStyle();
                textStyle.SetTextOverflow(TEXT_OVERFLOWS[overflow]);
                component->SetTextStyle(std::move(textStyle));
            } else {
                LOGE("Text: textOverflow(%d) illegal value", overflow);
            }
        }
    }
    info.SetReturnValue(info.This());
}

void JSText::SetMaxLines(int32_t value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetMaxLines(value);
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetFontStyle(int32_t value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        auto textStyle = component->GetTextStyle();
        textStyle.SetFontStyle(FONT_STYLES[value]);
        component->SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text fontStyle(%d) illega value", value);
    }
}

void JSText::SetTextAlign(int32_t value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        auto textStyle = component->GetTextStyle();
        textStyle.SetTextAlign(TEXT_ALIGNS[value]);
        component->SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text: TextAlign(%d) expected positive number", value);
    }
}

void JSText::SetLineHeight(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetLineHeight(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetFontFamily(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    std::vector<std::string> fontFamilies = ConvertStrToFontFamilies(value);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(fontFamilies);
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetMinFontSize(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetAdaptMinFontSize(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetMaxFontSize(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetAdaptMaxFontSize(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetLetterSpacing(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetLetterSpacing(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetTextCase(int32_t value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    if (value >= 0 && value < static_cast<int32_t>(TEXT_CASES.size())) {
        auto textStyle = component->GetTextStyle();
        textStyle.SetTextCase(TEXT_CASES[value]);
        component->SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text textCase(%d) illega value", value);
    }
}

void JSText::SetBaselineOffset(const std::string& value)
{
    auto component = GetComponent();
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetTextStyle();
    textStyle.SetBaselineOffset(StringToDimensionWithUnit(value, DimensionUnit::FP));
    component->SetTextStyle(std::move(textStyle));
}

void JSText::SetDecoration(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        auto component = GetComponent();
        if (component) {
            auto textStyle = component->GetTextStyle();

            JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
            JSRef<JSVal> typeValue = obj->GetProperty("type");
            JSRef<JSVal> colorValue = obj->GetProperty("color");

            if (typeValue->IsNumber()) {
                textStyle.SetTextDecoration(TextDecoration(typeValue->ToNumber<int32_t>()));
            }
            if (colorValue->IsString()) {
                textStyle.SetTextDecorationColor(Color::FromString(colorValue->ToString()));
            }
            component->SetTextStyle(std::move(textStyle));
        }
    }
    info.SetReturnValue(info.This());
}

void JSText::JsOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onClickId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc)]
            (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            LOGD("About to call onclick method on js");
            auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            func->Execute(*clickInfo);
        });
        auto click = ViewStackProcessor::GetInstance()->GetClickGestureListenerComponent();
        if (click) {
            click->SetOnClickId(onClickId);
        }
        auto component = GetComponent();
        if (component) {
            component->SetOnClick(onClickId);
        }
    }
}

void JSText::JSBind(BindingTarget globalObj)
{
    JSClass<JSText>::Declare("Text");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSText>::StaticMethod("create", &JSText::Create, opt);
    JSClass<JSText>::StaticMethod("fontColor", &JSText::SetTextColor, opt);
    JSClass<JSText>::StaticMethod("fontSize", &JSText::SetFontSize, opt);
    JSClass<JSText>::StaticMethod("fontWeight", &JSText::SetFontWeight, opt);
    JSClass<JSText>::StaticMethod("maxLines", &JSText::SetMaxLines, opt);
    JSClass<JSText>::StaticMethod("textOverflow", &JSText::SetTextOverflow, opt);
    JSClass<JSText>::StaticMethod("fontStyle", &JSText::SetFontStyle, opt);
    JSClass<JSText>::StaticMethod("textAlign", &JSText::SetTextAlign, opt);
    JSClass<JSText>::StaticMethod("lineHeight", &JSText::SetLineHeight, opt);
    JSClass<JSText>::StaticMethod("fontFamily", &JSText::SetFontFamily, opt);
    JSClass<JSText>::StaticMethod("minFontSize", &JSText::SetMinFontSize, opt);
    JSClass<JSText>::StaticMethod("maxFontSize", &JSText::SetMaxFontSize, opt);
    JSClass<JSText>::StaticMethod("letterSpacing", &JSText::SetLetterSpacing, opt);
    JSClass<JSText>::StaticMethod("textCase", &JSText::SetTextCase, opt);
    JSClass<JSText>::StaticMethod("baselineOffset", &JSText::SetBaselineOffset, opt);
    JSClass<JSText>::StaticMethod("decoration", &JSText::SetDecoration);
    JSClass<JSText>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSText>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSText>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSText>::StaticMethod("onClick", &JSText::JsOnClick);
    JSClass<JSText>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSText>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSText>::Inherit<JSContainerBase>();
    JSClass<JSText>::Inherit<JSViewAbstract>();
    JSClass<JSText>::Bind<>(globalObj);
}

void JSText::Create(const JSCallbackInfo& info)
{
    std::string data;
    if (info.Length() > 0 && info[0]->IsString()) {
        data = info[0]->ToString();
    }
    auto textComponent = AceType::MakeRefPtr<OHOS::Ace::TextComponentV2>(data);
    ViewStackProcessor::GetInstance()->Push(textComponent);

    // Init text style, allowScale is not supported in declarative.
    auto textStyle = textComponent->GetTextStyle();
    textStyle.SetAllowScale(false);
    textStyle.SetFontSize(DEFAULT_FONT_SZIE);
    textComponent->SetTextStyle(std::move(textStyle));
}

RefPtr<TextComponentV2> JSText::GetComponent()
{
    auto stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<TextComponentV2>(stack->GetMainComponent());
    return component;
}

} // namespace OHOS::Ace::Framework
