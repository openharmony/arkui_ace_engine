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

#include "bridge/declarative_frontend/jsview/js_view_abstract_bridge.h"

#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

void JSViewAbstractBridge::GetBackgroundBlurStyleOption(napi_value napiVal, BlurStyleOption& styleOption)
{
    JSRef<JSVal> value = JsConverter::ConvertNapiValueToJsVal(napiVal);
    if (value.IsEmpty() || !value->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(value);
    JSViewAbstract::ParseBlurStyleOption(object, styleOption);
}

void JSViewAbstractBridge::GetBackgroundEffect(napi_value napiVal, EffectOption& styleOption)
{
    JSRef<JSVal> value = JsConverter::ConvertNapiValueToJsVal(napiVal);
    if (value.IsEmpty() || !value->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(value);
    JSViewAbstract::ParseEffectOption(object, styleOption);
}
} // namespace OHOS::Ace::Framework