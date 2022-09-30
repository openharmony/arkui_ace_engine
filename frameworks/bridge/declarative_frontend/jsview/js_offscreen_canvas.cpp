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

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_canvas.h"

namespace OHOS::Ace::Framework {
void JSOffscreenCanvas::JSBind(BindingTarget globalObj)
{
    JSClass<JSOffscreenCanvas>::Declare("OffscreenCanvas");
    JSClass<JSOffscreenCanvas>::CustomProperty("width", &JSOffscreenCanvas::JsGetWidth,
                                            &JSOffscreenCanvas::JsSetWidth);
    JSClass<JSOffscreenCanvas>::CustomProperty("height", &JSOffscreenCanvas::JsGetHeight,
                                            &JSOffscreenCanvas::JsSetHeight);
    JSClass<JSOffscreenCanvas>::CustomMethod("transferToImageBitmap",
        &JSOffscreenCanvas::JsTransferToImageBitmap);
    JSClass<JSOffscreenCanvas>::Bind(globalObj, JSOffscreenCanvas::Constructor,
        JSOffscreenCanvas::Destructor);
}

void JSOffscreenCanvas::Constructor(const JSCallbackInfo& args)
{
    auto jsRenderContext = Referenced::MakeRefPtr<JSOffscreenCanvas>();
    jsRenderContext->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsRenderContext));
}

void JSOffscreenCanvas::Destructor(JSOffscreenCanvas* context)
{
    if (context != nullptr) {
        context->DecRefCount();
    } else {
        LOGE("context is null");
        return;
    }
}

void JSOffscreenCanvas::JsGetWidth(const JSCallbackInfo& info)
{
    double width = 0.0;
    auto returnValue = JSVal(ToJSValue(width));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSOffscreenCanvas::JsGetHeight(const JSCallbackInfo& info)
{
    double height = 0.0;
    auto returnValue = JSVal(ToJSValue(height));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSOffscreenCanvas::JsSetWidth(const JSCallbackInfo& info)
{
    return;
}

void JSOffscreenCanvas::JsSetHeight(const JSCallbackInfo& info)
{
    return;
}

void JSOffscreenCanvas::JsTransferToImageBitmap(const JSCallbackInfo& info)
{
    auto retObj = JSRef<JSObject>::New();
    info.SetReturnValue(retObj);
}

} // namespace OHOS::Ace::Framework
