/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_cached_image.h"

namespace OHOS::Ace::Framework {

static bool IsASTCResource(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }
    auto sources = jsObj->GetProperty("sources");
    auto column = jsObj->GetProperty("column");
    if (sources->IsEmpty() || column->IsEmpty()) {
        return false;
    }
    return true;
}

void JSCachedImage::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!IsASTCResource(info[0])) {
        JSImage::Create(info);
    }
}

void JSCachedImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSCachedImage>::Declare("CachedImage");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCachedImage>::StaticMethod("create", &JSCachedImage::Create, opt);
    JSClass<JSCachedImage>::InheritAndBind<JSImage>(globalObj);
}

void JSCachedImage::JSBindMediaCachedImage(BindingTarget globalObj)
{
    JSClass<JSCachedImage>::Declare("MediaCachedImage");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCachedImage>::StaticMethod("create", &JSCachedImage::Create, opt);
    JSClass<JSCachedImage>::InheritAndBind<JSImage>(globalObj);
}

} // namespace OHOS::Ace::Framework
