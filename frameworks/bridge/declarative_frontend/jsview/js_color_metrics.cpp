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

#include "bridge/declarative_frontend/jsview/js_color_metrics.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr uint8_t MAX_RGBA_VALUE = 255;
constexpr uint8_t INFO_LENTH_HAS_ALPHA = 4;
constexpr uint8_t INFO_LENTH_DEFAULT = 3;
constexpr uint8_t RED_INDEX = 0;
constexpr uint8_t GREEN_INDEX = 1;
constexpr uint8_t BLUE_INDEX = 2;
constexpr uint8_t ALPHA_INDEX = 3;
}

void JSColorMetrics::JSBind(BindingTarget globalObj)
{
    JSClass<JSColorMetrics>::Declare("ColorMetrics");
    JSClass<JSColorMetrics>::StaticMethod("numeric", &JSColorMetrics::JsNumericColor);
    JSClass<JSColorMetrics>::StaticMethod("rgba", &JSColorMetrics::JsRGBAColor);
    JSClass<JSColorMetrics>::StaticMethod("resourceColor", &JSColorMetrics::JsResourceColor);
    JSClass<JSColorMetrics>::CustomMethod("blendColor", &JSColorMetrics::JsBlendColor);
    JSClass<JSColorMetrics>::CustomProperty(
        "color", &JSColorMetrics::JsGetColor, &JSColorMetrics::JsSetColor);
    JSClass<JSColorMetrics>::CustomProperty(
        "red", &JSColorMetrics::JsGetRed, &JSColorMetrics::JsSetRed);
    JSClass<JSColorMetrics>::CustomProperty(
        "green", &JSColorMetrics::JsGetGreen, &JSColorMetrics::JsSetGreen);
    JSClass<JSColorMetrics>::CustomProperty(
        "blue", &JSColorMetrics::JsGetBlue, &JSColorMetrics::JsSetBlue);
    JSClass<JSColorMetrics>::CustomProperty(
        "alpha", &JSColorMetrics::JsGetAlpha, &JSColorMetrics::JsSetAlpha);
       
    JSClass<JSColorMetrics>::Bind(globalObj, JSColorMetrics::Constructor, JSColorMetrics::Destructor);
}

void JSColorMetrics::Constructor(const JSCallbackInfo& info)
{
    auto jsColorMetricsPtr = Referenced::MakeRefPtr<JSColorMetrics>();
    jsColorMetricsPtr->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(jsColorMetricsPtr));
}

void JSColorMetrics::Destructor(JSColorMetrics* jsColorMetricsPtr)
{
    if (jsColorMetricsPtr != nullptr) {
        jsColorMetricsPtr->DecRefCount();
    }
}

void JSColorMetrics::JsSetColor(const JSCallbackInfo& info)
{
    return;
}

void JSColorMetrics::JsGetColor(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(color_.ColorToString()));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSColorMetrics::JsSetRed(const JSCallbackInfo& info)
{
    return;
}

void JSColorMetrics::JsGetRed(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(color_.GetRed()));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSColorMetrics::JsSetBlue(const JSCallbackInfo& info)
{
    return;
}

void JSColorMetrics::JsGetBlue(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(color_.GetBlue()));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSColorMetrics::JsSetGreen(const JSCallbackInfo& info)
{
    return;
}

void JSColorMetrics::JsGetGreen(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(color_.GetGreen()));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSColorMetrics::JsSetAlpha(const JSCallbackInfo& info)
{
    return;
}

void JSColorMetrics::JsGetAlpha(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(color_.GetAlpha()));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSColorMetrics::JsResourceColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    Color color;
    if (!JSViewAbstract::CheckColor(info[0], color, "ColorMetrics", "ResourceColor")) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    JSRef<JSObject> obj = JSClass<JSColorMetrics>::NewInstance();
    auto jsColorMetrics = Referenced::Claim(obj->Unwrap<JSColorMetrics>());
    jsColorMetrics->SetColor(color);
    info.SetReturnValue(obj);
}

void JSColorMetrics::JsNumericColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    Color color;
    if (!JSViewAbstract::CheckColor(info[0], color, "ColorMetrics", "ResourceColor")) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    JSRef<JSObject> obj = JSClass<JSColorMetrics>::NewInstance();
    auto jsColorMetrics = Referenced::Claim(obj->Unwrap<JSColorMetrics>());
    jsColorMetrics->SetColor(color);
    info.SetReturnValue(obj);
}

void JSColorMetrics::JsRGBAColor(const JSCallbackInfo& info)
{
    if (info.Length() < INFO_LENTH_DEFAULT || info.Length() > INFO_LENTH_HAS_ALPHA) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    std::vector<uint8_t> array;
    for (int i = 0; i < info.Length(); i++) {
        if (!info[i]->IsNumber()) {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
            return;
        }
        array.emplace_back(info[i]->ToNumber<uint8_t>());
    }
    Color color;
    if (array.size() > INFO_LENTH_DEFAULT) {
        color = Color::FromARGB(array[ALPHA_INDEX], array[RED_INDEX], array[GREEN_INDEX], array[BLUE_INDEX]);
    } else {
        color = Color::FromARGB(MAX_RGBA_VALUE, array[RED_INDEX], array[GREEN_INDEX], array[BLUE_INDEX]);
    }
    JSRef<JSObject> obj = JSClass<JSColorMetrics>::NewInstance();
    auto jsColorMetrics = Referenced::Claim(obj->Unwrap<JSColorMetrics>());
    jsColorMetrics->SetColor(color);
    info.SetReturnValue(obj);
}

void JSColorMetrics::JsBlendColor(const JSCallbackInfo& info)
{
    JSColorMetrics* overlayColor = JSRef<JSObject>::Cast(info[0])->Unwrap<JSColorMetrics>();
    if (info.Length() < 1 || !info[0]->IsObject() || !overlayColor) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto blendColor = color_.BlendColor(overlayColor->color_);
    JSRef<JSObject> obj = JSClass<JSColorMetrics>::NewInstance();
    auto jsColorMetrics = Referenced::Claim(obj->Unwrap<JSColorMetrics>());
    jsColorMetrics->SetColor(blendColor);
    info.SetReturnValue(obj);
}
} // namespace OHOS::Ace::Framework
