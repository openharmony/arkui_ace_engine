/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/style_string/js_span_object.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "core/components/text/text_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

void JSFontSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSFontSpan>::Declare("TextStyle");
    JSClass<JSFontSpan>::CustomProperty("fontColor", &JSFontSpan::GetFontColor, &JSFontSpan::SetFontColor);
    JSClass<JSFontSpan>::Bind(globalObj, JSFontSpan::Constructor, JSFontSpan::Destructor);
}

void JSFontSpan::Constructor(const JSCallbackInfo& args)
{
    auto fontSpan = Referenced::MakeRefPtr<JSFontSpan>();
    fontSpan->IncRefCount();

    RefPtr<FontSpan> span;
    if (args.Length() <= 0) {
        Font font;
        span = AceType::MakeRefPtr<FontSpan>(font);
    } else {
        span = JSFontSpan::ParseJsFontSpan(JSRef<JSObject>::Cast(args[0]));
    }
    fontSpan->fontSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(fontSpan));
}

void JSFontSpan::Destructor(JSFontSpan* fontSpan)
{
    if (fontSpan != nullptr) {
        fontSpan->DecRefCount();
    }
}

RefPtr<FontSpan> JSFontSpan::ParseJsFontSpan(const JSRef<JSObject>& obj)
{
    Font font;
    Color color;
    JSRef<JSVal> colorObj = JSRef<JSVal>::Cast(obj->GetProperty("fontColor"));
    if (!colorObj->IsNull() && JSViewAbstract::ParseJsColor(colorObj, color)) {
        font.fontColor = color;
    } else {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_RETURN(context, AceType::MakeRefPtr<FontSpan>(font));
        auto theme = context->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, AceType::MakeRefPtr<FontSpan>(font));
        font.fontColor = theme->GetTextStyle().GetTextColor();
    }
    return AceType::MakeRefPtr<FontSpan>(font);
}

void JSFontSpan::GetFontColor(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontColor.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(fontSpan_->GetFont().fontColor.value().ColorToString())));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontColor(const JSCallbackInfo& info) {}

RefPtr<FontSpan>& JSFontSpan::GetFontSpan()
{
    return fontSpan_;
}

void JSFontSpan::SetFontSpan(const RefPtr<FontSpan>& fontSpan)
{
    fontSpan_ = fontSpan;
}

void JSGestureSpan::Constructor(const JSCallbackInfo& args)
{
    auto gestureSpan = Referenced::MakeRefPtr<JSGestureSpan>();
    gestureSpan->IncRefCount();

    RefPtr<GestureSpan> span;
    if (args.Length() <= 0) {
        GestureStyle gestureInfo;
        span = AceType::MakeRefPtr<GestureSpan>(gestureInfo);
    } else {
        span = JSGestureSpan::ParseJSGestureSpan(args);
    }
    gestureSpan->gestureSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(gestureSpan));
}

void JSGestureSpan::Destructor(JSGestureSpan* gestureSpan)
{
    if (gestureSpan != nullptr) {
        gestureSpan->DecRefCount();
    }
}

void JSGestureSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSGestureSpan>::Declare("GestureStyle");
    JSClass<JSGestureSpan>::Bind(globalObj, JSGestureSpan::Constructor, JSGestureSpan::Destructor);
}

RefPtr<GestureSpan> JSGestureSpan::ParseJSGestureSpan(const JSCallbackInfo& args)
{
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args[0]);
    GestureStyle gestureInfo;

    auto clickFunc = object->GetProperty("onClick");
    if (!clickFunc->IsFunction() || clickFunc->IsUndefined()) {
        gestureInfo.onClick = std::nullopt;
    } else {
        auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(clickFunc));
        auto onClick = [execCtx = args.GetExecutionContext(), func = jsOnClickFunc](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            const auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            ACE_SCORING_EVENT("SpanString.onClick");
            func->Execute(*clickInfo);
        };
        auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
        gestureInfo.onClick = std::move(tmpClickFunc);
    }

    auto longPressFunc = object->GetProperty("onLongPress");
    if (!longPressFunc->IsFunction() || longPressFunc->IsUndefined()) {
        gestureInfo.onLongPress = std::nullopt;
    } else {
        auto jsOnLongPressFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(longPressFunc));
        auto onLongPress = [execCtx = args.GetExecutionContext(), func = jsOnLongPressFunc](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            const auto* longPressInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
            ACE_SCORING_EVENT("SpanString.onLongPress");
            func->Execute(*longPressInfo);
        };
        auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
        gestureInfo.onLongPress = std::move(tmpLongPressFunc);
    }

    return AceType::MakeRefPtr<GestureSpan>(gestureInfo);
}

RefPtr<GestureSpan>& JSGestureSpan::GetGestureSpan()
{
    return gestureSpan_;
}

void JSGestureSpan::SetGestureSpan(const RefPtr<GestureSpan>& gestureSpan)
{
    gestureSpan_ = gestureSpan;
}
} // namespace OHOS::Ace::Framework