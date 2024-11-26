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

#include <securec.h>

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_image_data.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"

namespace OHOS::Ace::Framework {
constexpr size_t FIRST_PARAM = 0;
constexpr size_t SECOND_PARAM = 1;
constexpr size_t THIRD_PARAM = 2;
constexpr size_t FOURTH_PARAM = 3;
constexpr double DIFF = 1e-10;
constexpr int32_t PIXEL_SIZE = 4;
void JSCanvasImageData::Constructor(const JSCallbackInfo& args)
{
    auto jsCanvasImageData = Referenced::MakeRefPtr<JSCanvasImageData>();
    jsCanvasImageData->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCanvasImageData));

    if (args.Length() < 2) { // Invalid argument, the arguments should be at least 2: width, height
        return;
    }
    int32_t finalWidth = 0;
    int32_t finalHeight = 0;
    int32_t unit = 0;

    if (args.GetInt32Arg(FOURTH_PARAM, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        jsCanvasImageData->SetUnit(CanvasUnit::PX);
    }
    if (!jsCanvasImageData->GetImageDataSize(args, finalWidth, finalHeight)) {
        return;
    }
    int32_t result = finalWidth * finalHeight * PIXEL_SIZE;
    jsCanvasImageData->width_ = finalWidth;
    jsCanvasImageData->height_ = finalHeight;

    if (args.Length() == 2) { // 2 arguments: width, height
        JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(result);
        args.SetSize(static_cast<size_t>(arrayBuffer->ByteLength()));
        // return the transparent black image
        auto* buffer = static_cast<uint32_t*>(arrayBuffer->GetBuffer());
        if ((arrayBuffer->ByteLength() != 0) &&
            (memset_s(buffer, arrayBuffer->ByteLength(), 0, arrayBuffer->ByteLength()))) {
            return;
        }
        jsCanvasImageData->colorArray_ =
            JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());
    } else if (args.Length() >= 3 && args[THIRD_PARAM]->IsUint8ClampedArray()) { // 3 arguments: width, height, data
        JSRef<JSUint8ClampedArray> data = JSRef<JSUint8ClampedArray>::Cast(args[THIRD_PARAM]);
        auto buffer = data->GetArrayBuffer();
        args.SetSize(static_cast<size_t>(buffer->ByteLength()));
        if ((static_cast<CanvasUnit>(unit) == CanvasUnit::PX) && (buffer->ByteLength() != result)) {
            TAG_LOGE(AceLogTag::ACE_CANVAS,
                "Failed to construct 'ImageData': The input data length is not equal to (4 * widthPX * heightPX).");
            return;
        }
        jsCanvasImageData->colorArray_ = data;
    }
}

bool JSCanvasImageData::GetImageDataSize(const JSCallbackInfo& args, int32_t& finalWidth, int32_t& finalHeight)
{
    double width = 0.0;
    double height = 0.0;
    double density = GetDensity();
    args.GetDoubleArg(FIRST_PARAM, width);
    args.GetDoubleArg(SECOND_PARAM, height);
    width *= density;
    height *= density;
    if (NonPositive(width) || NonPositive(height)) {
        TAG_LOGE(AceLogTag::ACE_CANVAS,
            "Failed to construct 'ImageData': The input 'width' or 'height' is non-positive number or not number.");
        return false;
    }
    // Integer Overflow.
    width += DIFF;
    height += DIFF;
    if ((width > INT32_MAX) || (height > INT32_MAX) || ((width > 0) && (height > (INT32_MAX / width / PIXEL_SIZE)))) {
        return false;
    }
    finalWidth = static_cast<int32_t>(width);
    finalHeight = static_cast<int32_t>(height);
    return true;
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
    JSClass<JSCanvasImageData>::CustomProperty("width", &JSCanvasImageData::JsGetWidth, &JSCanvasImageData::JsSetWidth);
    JSClass<JSCanvasImageData>::CustomProperty(
        "height", &JSCanvasImageData::JsGetHeight, &JSCanvasImageData::JsSetHeight);
    JSClass<JSCanvasImageData>::CustomProperty("data", &JSCanvasImageData::JsGetData, &JSCanvasImageData::JsSetData);
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
