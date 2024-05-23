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

#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "bridge/declarative_frontend/jsview/js_rendering_context.h"

namespace OHOS::Ace::Framework {
void JSCanvasImageData::Constructor(const JSCallbackInfo& args)
{
    auto jsCanvasImageData = Referenced::MakeRefPtr<JSCanvasImageData>();
    jsCanvasImageData->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCanvasImageData));

    if (args.Length() < 2) {
        return;
    }
    int32_t width = 0;
    int32_t height = 0;
    int32_t unit = 0;
    if (args.GetInt32Arg(3, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        jsCanvasImageData->SetUnit(CanvasUnit::PX);
    }
    if (args[0]->IsNumber() && args[1]->IsNumber()) {
        JSViewAbstract::ParseJsInteger(args[0], width);
        JSViewAbstract::ParseJsInteger(args[1], height);
        double density = jsCanvasImageData->GetDensity();
        width *= density;
        height *= density;
        jsCanvasImageData->width_ = width;
        jsCanvasImageData->height_ = height;
    }

    if (args.Length() >= 3 && args[2]->IsUint8ClampedArray()) {
        jsCanvasImageData->colorArray_ = args[2];
    }
}

void JSCanvasImageData::Destructor(JSCanvasImageData* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSCanvasImageData::JSBind(BindingTarget globalObj)
{
    JSClass<JSCanvasImageData>::Declare("ImageData");
    JSClass<JSCanvasImageData>::CustomProperty("width", &JSCanvasImageData::JsGetWidth,
        &JSCanvasImageData::JsSetWidth);
    JSClass<JSCanvasImageData>::CustomProperty("height", &JSCanvasImageData::JsGetHeight,
        &JSCanvasImageData::JsSetHeight);
    JSClass<JSCanvasImageData>::CustomProperty("data", &JSCanvasImageData::JsGetData,
        &JSCanvasImageData::JsSetData);
    JSClass<JSCanvasImageData>::Bind(globalObj, JSCanvasImageData::Constructor, JSCanvasImageData::Destructor);
}

void JSCanvasImageData::JsGetWidth(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(width_));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSCanvasImageData::JsGetHeight(const JSCallbackInfo& info)
{
    auto returnValue = JSVal(ToJSValue(height_));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSCanvasImageData::JsGetData(const JSCallbackInfo& info)
{
    info.SetReturnValue(colorArray_);
}

void JSCanvasImageData::JsSetWidth(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasImageData::JsSetHeight(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasImageData::JsSetData(const JSCallbackInfo& info)
{
    return;
}
} // namespace OHOS::Ace::Framework
