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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_span.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_model_ng.h"

namespace OHOS::Ace::Framework {

void JSContainerSpan::SetTextBackgroundStyle(const JSCallbackInfo& info)
{
    auto textBackgroundStyle = JSContainerSpan::ParseTextBackgroundStyle(info);
    SpanModel::GetInstance()->SetTextBackgroundStyle(textBackgroundStyle);
}

TextBackgroundStyle JSContainerSpan::ParseTextBackgroundStyle(const JSCallbackInfo& info)
{
    TextBackgroundStyle textBackgroundStyle;
    auto jsValue = info[0];
    if (!jsValue->IsObject()) {
        return textBackgroundStyle;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
    return ParseTextBackgroundStyle(obj);
}

TextBackgroundStyle JSContainerSpan::ParseTextBackgroundStyle(const JSRef<JSObject>& obj)
{
    TextBackgroundStyle textBackgroundStyle;
    JSRef<JSVal> colorValue = obj->GetProperty("color");
    Color colorVal;
    RefPtr<ResourceObject> colorResObj;
    if (ParseJsColor(colorValue, colorVal, colorResObj)) {
        textBackgroundStyle.backgroundColor = colorVal;
    }
    if (SystemProperties::ConfigChangePerform() && colorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, TextBackgroundStyle& textBackgroundStyle) {
            Color color;
            ResourceParseUtils::ParseResColor(colorResObj, color);
            textBackgroundStyle.backgroundColor = color;
        };
        textBackgroundStyle.AddResource("textBackgroundStyle.color", colorResObj, std::move(updateFunc));
    }
    JSRef<JSVal> radiusValue = obj->GetProperty("radius");
    if (!radiusValue->IsString() && !radiusValue->IsNumber() && !radiusValue->IsObject()) {
        return textBackgroundStyle;
    }
    CalcDimension radius;
    RefPtr<ResourceObject> radiusResObj;
    if (ParseJsDimensionVp(radiusValue, radius, radiusResObj)) {
        if (radius.Unit() == DimensionUnit::PERCENT) {
            radius.Reset();
        }
        textBackgroundStyle.backgroundRadius = { radius, radius, radius, radius };
        textBackgroundStyle.backgroundRadius->multiValued = false;
        if (SystemProperties::ConfigChangePerform() && radiusResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& radiusResObj,
                TextBackgroundStyle& textBackgroundStyle) {
                CalcDimension radius;
                ResourceParseUtils::ParseResDimensionVp(radiusResObj, radius);
                textBackgroundStyle.backgroundRadius = { radius, radius, radius, radius };
                textBackgroundStyle.backgroundRadius->multiValued = false;
            };
            textBackgroundStyle.AddResource("textBackgroundStyle.radius", radiusResObj, std::move(updateFunc));
        }
    } else if (radiusValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(radiusValue);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight, textBackgroundStyle);
        textBackgroundStyle.backgroundRadius = { topLeft, topRight, bottomRight, bottomLeft };
        textBackgroundStyle.backgroundRadius->multiValued = true;
    }
    return textBackgroundStyle;
}

void JSContainerSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSContainerSpan>::Declare("ContainerSpan");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSContainerSpan>::StaticMethod("create", &JSContainerSpan::Create, opt);
    JSClass<JSContainerSpan>::StaticMethod("textBackgroundStyle", &JSContainerSpan::SetTextBackgroundStyle, opt);
    JSClass<JSContainerSpan>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSContainerSpan::Create(const JSCallbackInfo& info)
{
    SpanModel::GetInstance()->CreateContainSpan();
}
} // namespace OHOS::Ace::Framework
