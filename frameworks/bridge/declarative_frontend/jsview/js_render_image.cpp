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

#include "bridge/declarative_frontend/jsview/js_render_image.h"
#include "bridge/declarative_frontend/jsview/js_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

JSRenderImage::JSRenderImage()
{
}

void JSRenderImage::Constructor(const JSCallbackInfo& args)
{
    auto jsCalendarController = Referenced::MakeRefPtr<JSRenderImage>();
    jsCalendarController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCalendarController));
    if (args.Length() > 0) {
        std::string text = "";
        if (args[0]->IsString()) {
            JSViewAbstract::ParseJsString(args[0], text);
            jsCalendarController->src_ = text;
        }
    }
}

void JSRenderImage::Destructor(JSRenderImage* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSRenderImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSRenderImage>::Declare("ImageBitmap");
    JSClass<JSRenderImage>::CustomProperty("width", &JSRenderImage::JsGetWidth,
        &JSRenderImage::JsSetWidth);
    JSClass<JSRenderImage>::CustomProperty("height", &JSRenderImage::JsGetHeight,
        &JSRenderImage::JsSetHeight);
    JSClass<JSRenderImage>::CustomMethod("close", &JSRenderImage::JsClose);
    JSClass<JSRenderImage>::Bind(globalObj, JSRenderImage::Constructor, JSRenderImage::Destructor);
}

std::string JSRenderImage::GetSrc()
{
    return src_;
}

void JSRenderImage::JsSetWidth(const JSCallbackInfo& info)
{
    return;
}

void JSRenderImage::JsSetHeight(const JSCallbackInfo& info)
{
    return;
}

void JSRenderImage::JsGetWidth(const JSCallbackInfo& info)
{
    double width = 0.0;
    width = width_;
    width = SystemProperties::Px2Vp(width);
    auto returnValue = JSVal(ToJSValue(width));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSRenderImage::JsGetHeight(const JSCallbackInfo& info)
{
    double height = 0.0;
    height = height_;

    height = SystemProperties::Px2Vp(height);
    auto returnValue = JSVal(ToJSValue(height));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSRenderImage::JsClose(const JSCallbackInfo& info)
{
    return;
}

double JSRenderImage::GetWidth()
{
    return width_;
}

double JSRenderImage::GetHeight()
{
    return height_;
}

} // namespace OHOS::Ace::Framework