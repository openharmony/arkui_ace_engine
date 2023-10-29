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
    if (args[0]->IsNumber() && args[1]->IsNumber()) {
        JSViewAbstract::ParseJsInteger(args[0], width);
        JSViewAbstract::ParseJsInteger(args[1], height);
        width = SystemProperties::Vp2Px(width);
        height = SystemProperties::Vp2Px(height);
        jsCanvasImageData->width_ = width;
        jsCanvasImageData->height_ = height;
    }

    if (args.Length() >= 3 && args[2]->IsArray()) {
        std::vector<uint32_t> array;
        JSViewAbstract::ParseJsIntegerArray(args[2], array);

        uint32_t count = 0;
        JSRef<JSArray> colorArray = JSRef<JSArray>::New();

        int64_t tmp = static_cast<int64_t>(4) * ((int64_t)width * (int64_t)height + (int64_t)width)
            + static_cast<int64_t>(3);
        if ((int64_t)((int32_t)tmp) != tmp) {
            return;
        }

        for (int32_t i = 0; i < height; ++i) {
            for (int32_t j = 0; j < width; ++j) {
                int32_t flag = j + width * i;
                if (array.size() > static_cast<uint32_t>(4 * flag + 3)) {
                    colorArray->SetValueAt(count, JSRef<JSVal>::Make(ToJSValue(array[4 * flag])));
                    colorArray->SetValueAt(count + 1, JSRef<JSVal>::Make(ToJSValue(array[4 * flag + 1])));
                    colorArray->SetValueAt(count + 2, JSRef<JSVal>::Make(ToJSValue(array[4 * flag + 2])));
                    colorArray->SetValueAt(count + 3, JSRef<JSVal>::Make(ToJSValue(array[4 * flag + 3])));
                    count += 4;
                }
            }
        }
        jsCanvasImageData->colorArray_ = colorArray;
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