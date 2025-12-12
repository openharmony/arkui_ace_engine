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

#include "bridge/declarative_frontend/jsview/js_color_metrics_linear_gradient.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

void JSColorMetricsLinearGradient::JSBind(BindingTarget globalObj)
{
    JSClass<JSColorMetricsLinearGradient>::Declare("ColorMetricsLinearGradient");
    JSClass<JSColorMetricsLinearGradient>::Bind(
        globalObj, JSColorMetricsLinearGradient::Constructor, JSColorMetricsLinearGradient::Destructor);
}

void JSColorMetricsLinearGradient::Constructor(const JSCallbackInfo& args)
{
    auto jsColorMetricsLinearGradientPtr = Referenced::MakeRefPtr<JSColorMetricsLinearGradient>();
    jsColorMetricsLinearGradientPtr->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsColorMetricsLinearGradientPtr));

    if (args.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!args[0]->IsArray()) {
        LOGE("The arg is wrong, the first arg is supposed to be an array");
        return;
    }

    auto paramArray = JSRef<JSArray>::Cast(args[0]);
    size_t length = paramArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = paramArray->GetValueAt(i);
        if (!item->IsObject()) {
            return;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        
        ColorMetricsStop stop;
        if (!ParseColorMetricsStop(itemObject, stop)) {
            return;
        }
        jsColorMetricsLinearGradientPtr->colorMetricsGradient_.push_back(stop);
    }
}

void JSColorMetricsLinearGradient::Destructor(JSColorMetricsLinearGradient* jsColorMetricsLinearGradientPtr)
{
    if (jsColorMetricsLinearGradientPtr != nullptr) {
        jsColorMetricsLinearGradientPtr->DecRefCount();
    }
}

bool JSColorMetricsLinearGradient::ParseColorMetricsStop(const JSRef<JSObject>& itemObject, ColorMetricsStop& stop)
{
    JSRef<JSVal> jsColor = itemObject->GetProperty("color");
    Color color;
    if (!JSViewAbstract::ParseColorMetricsToColor(jsColor, color)) {
        return false;
    }
    stop.color = color;
    JSRef<JSVal> jsOffset = itemObject->GetProperty("offset");
    CalcDimension offset;
    if (!JSViewAbstract::ParseJsDimensionVp(jsOffset, offset)) {
        return false;
    }

    if (Negative(offset.Value())) {
        offset = Dimension(0.0);
    }
    if (GreatNotEqual(offset.Value(), 1.0)) {
        offset = Dimension(1.0);
    }
    stop.offset = offset;
    return true;
}
} // namespace OHOS::Ace::Framework