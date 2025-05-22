/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"
#include "bridge/declarative_frontend/jsview/canvas/js_matrix2d.h"
#include "bridge/declarative_frontend/jsview/canvas/js_render_image.h"

namespace OHOS::Ace::Framework {
constexpr int32_t ARGS_COUNT_ONE = 1;
constexpr int32_t ARGS_COUNT_TWO = 2;

void* DetachOffscreenCanvas(napi_env env, void* value, void* hint)
{
    if (value == nullptr) {
        LOGW("Invalid parameter.");
        return nullptr;
    }
    JSOffscreenCanvas* workCanvas = (JSOffscreenCanvas*)value;
    if (workCanvas->IsGetContext()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s",
            "An OffscreenCanvas could not be transferred because it had a rendering context.");
        return nullptr;
    }
    if (workCanvas->IsDetached()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s",
            "An OffscreenCanvas could not be transferred because the object is detached.");
        return nullptr;
    }
    workCanvas->SetDetachStatus(true);

    auto result = new JSOffscreenCanvas();
    result->SetWidth(workCanvas->GetWidth());
    result->SetHeight(workCanvas->GetHeight());
    result->SetUnit(workCanvas->GetUnit());
    return result;
}

napi_value AttachOffscreenCanvas(napi_env env, void* value, void*)
{
    if (value == nullptr) {
        LOGW("Invalid parameter.");
        return nullptr;
    }
    JSOffscreenCanvas* workCanvas = (JSOffscreenCanvas*)value;
    if (workCanvas == nullptr) {
        LOGW("Invalid context.");
        return nullptr;
    }
    auto offscreenCanvasPattern = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(
        workCanvas->GetWidth(), workCanvas->GetHeight());
    workCanvas->SetOffscreenPattern(offscreenCanvasPattern);
    auto bitmapSize = offscreenCanvasPattern->GetBitmapSize();

    napi_value offscreenCanvas = nullptr;
    napi_create_object(env, &offscreenCanvas);

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_GETTER_SETTER("width", JSOffscreenCanvas::JsGetWidth, JSOffscreenCanvas::JsSetWidth),
        DECLARE_NAPI_GETTER_SETTER("height", JSOffscreenCanvas::JsGetHeight, JSOffscreenCanvas::JsSetHeight),
        DECLARE_NAPI_FUNCTION("transferToImageBitmap", JSOffscreenCanvas::JsTransferToImageBitmap),
        DECLARE_NAPI_FUNCTION("getContext", JSOffscreenCanvas::JsGetContext),
    };
    napi_define_properties(env, offscreenCanvas, sizeof(desc) / sizeof(*desc), desc);

    napi_coerce_to_native_binding_object(
        env, offscreenCanvas, DetachOffscreenCanvas, AttachOffscreenCanvas, value, nullptr);
    napi_wrap_with_size(
        env, offscreenCanvas, value,
        [](napi_env env, void* data, void* hint) {
            LOGD("Finalizer for offscreen canvas is called");
            auto wrapper = reinterpret_cast<JSOffscreenCanvas*>(data);
            delete wrapper;
            wrapper = nullptr;
        },
        nullptr, nullptr, bitmapSize);
    return offscreenCanvas;
}

napi_value JSOffscreenCanvas::InitOffscreenCanvas(napi_env env)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_GETTER_SETTER("width", JsGetWidth, JsSetWidth),
        DECLARE_NAPI_GETTER_SETTER("height", JsGetHeight, JsSetHeight),
        DECLARE_NAPI_FUNCTION("transferToImageBitmap", JsTransferToImageBitmap),
        DECLARE_NAPI_FUNCTION("getContext", JsGetContext),
    };
    napi_status status = napi_define_class(
        env, "OffscreenCanvas", NAPI_AUTO_LENGTH, Constructor, nullptr, sizeof(desc) / sizeof(*desc), desc, &object);
    if (status != napi_ok) {
        LOGW("Initialize offscreen canvas failed");
        return nullptr;
    }
    return object;
}

void JSOffscreenCanvas::JSBind(BindingTarget globalObj, void* nativeEngine)
{
    if (!nativeEngine) {
        return;
    }
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value jsGlobalObj = nullptr;
    napi_get_global(env, &jsGlobalObj);

    napi_value result = InitOffscreenCanvas(env);
    napi_set_named_property(env, jsGlobalObj, "OffscreenCanvas", result);
}

napi_value JSOffscreenCanvas::Constructor(napi_env env, napi_callback_info info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    size_t argc = 3;
    napi_value thisVar = nullptr;
    napi_value argv[3] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    if (argc < ARGS_COUNT_TWO || argv[0] == nullptr || argv[1] == nullptr) {
        LOGW("Invalid args.");
        return nullptr;
    }
    double fWidth = 0.0;
    double fHeight = 0.0;
    auto workCanvas = new JSOffscreenCanvas();
    if (argv[2] != nullptr) {
        int32_t unit = 0;
        napi_get_value_int32(env, argv[2], &unit);
        if (static_cast<CanvasUnit>(unit) == CanvasUnit::PX) {
            workCanvas->SetUnit(CanvasUnit::PX);
        }
    }
    double density = workCanvas->GetDensity();
    if (napi_get_value_double(env, argv[0], &fWidth) == napi_ok) {
        fWidth *= density;
        workCanvas->SetWidth(fWidth);
    }
    if (napi_get_value_double(env, argv[1], &fHeight) == napi_ok) {
        fHeight *= density;
        workCanvas->SetHeight(fHeight);
    }
    workCanvas->offscreenCanvasPattern_ = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(
        static_cast<int32_t>(fWidth), static_cast<int32_t>(fHeight));
    auto bitmapSize = workCanvas->offscreenCanvasPattern_->GetBitmapSize();
    napi_coerce_to_native_binding_object(
        env, thisVar, DetachOffscreenCanvas, AttachOffscreenCanvas, workCanvas, nullptr);
    napi_wrap_with_size(
        env, thisVar, workCanvas,
        [](napi_env env, void* data, void* hint) {
            LOGD("Finalizer for offscreen canvas is called");
            auto workCanvas = reinterpret_cast<JSOffscreenCanvas*>(data);
            delete workCanvas;
            workCanvas = nullptr;
        },
        nullptr, nullptr, bitmapSize);
    return thisVar;
}

napi_value JSOffscreenCanvas::JsGetWidth(napi_env env, napi_callback_info info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    napi_value defaultWidth = nullptr;
    napi_create_double(env, 0.0, &defaultWidth);
    return (me != nullptr && !me->isDetached_) ? me->OnGetWidth(env) : defaultWidth;
}

napi_value JSOffscreenCanvas::JsGetHeight(napi_env env, napi_callback_info info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    napi_value defaultHeight = nullptr;
    napi_create_double(env, 0.0, &defaultHeight);
    return (me != nullptr && !me->isDetached_) ? me->OnGetHeight(env) : defaultHeight;
}

napi_value JSOffscreenCanvas::JsSetWidth(napi_env env, napi_callback_info info)
{
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr && !me->isDetached_) ? me->OnSetWidth(env, info) : nullptr;
}

napi_value JSOffscreenCanvas::JsSetHeight(napi_env env, napi_callback_info info)
{
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr && !me->isDetached_) ? me->OnSetHeight(env, info) : nullptr;
}
napi_value JSOffscreenCanvas::JsTransferToImageBitmap(napi_env env, napi_callback_info info)
{
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    if (me != nullptr && me->isDetached_) {
        JSException::Throw("%s", "Failed to execute 'transferToImageBitmap' on 'OffscreenCanvas': Cannot transfer an "
                                 "ImageBitmap from a detached OffscreenCanvas");
        return nullptr;
    }
    napi_value defaultImage = nullptr;
    napi_create_object(env, &defaultImage);
    return (me != nullptr) ? me->onTransferToImageBitmap(env) : defaultImage;
}

napi_value JSOffscreenCanvas::JsGetContext(napi_env env, napi_callback_info info)
{
    JSOffscreenCanvas* me = static_cast<JSOffscreenCanvas*>(GetNapiCallbackInfoAndThis(env, info));
    if (me != nullptr && me->isDetached_) {
        JSException::Throw(
            "%s", "Failed to execute 'getContext' on 'OffscreenCanvas': OffscreenCanvas object is detached");
        return nullptr;
    }
    napi_value defaultContext = nullptr;
    napi_create_object(env, &defaultContext);
    return (me != nullptr) ? me->onGetContext(env, info) : defaultContext;
}

napi_value JSOffscreenCanvas::OnGetWidth(napi_env env)
{
    double fWidth = GetWidth();
    double density = GetDensity();
    fWidth /= density;
    napi_value width = nullptr;
    napi_create_double(env, fWidth, &width);
    return width;
}

napi_value JSOffscreenCanvas::OnGetHeight(napi_env env)
{
    double fHeight = GetHeight();
    double density = GetDensity();
    fHeight /= density;
    napi_value height = nullptr;
    napi_create_double(env, fHeight, &height);
    return height;
}

napi_value JSOffscreenCanvas::OnSetWidth(napi_env env, napi_callback_info info)
{
    CHECK_NULL_RETURN(offscreenCanvasPattern_, nullptr);
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc != ARGS_COUNT_ONE) {
        LOGD("Invalid args.");
        return nullptr;
    }
    double width = 0.0;
    NAPI_CALL(env, napi_get_value_double(env, argv[0], &width));
    double density = GetDensity();
    width *= density;

    if (width_ != width) {
        width_ = width;
        offscreenCanvasPattern_->UpdateSize(width_, height_);
        if (offscreenCanvasContext_ != nullptr) {
            offscreenCanvasContext_->SetWidth(width_);
        }
    }
    return nullptr;
}

napi_value JSOffscreenCanvas::OnSetHeight(napi_env env, napi_callback_info info)
{
    CHECK_NULL_RETURN(offscreenCanvasPattern_, nullptr);
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc != ARGS_COUNT_ONE) {
        LOGD("Invalid args.");
        return nullptr;
    }
    double height = 0.0;
    NAPI_CALL(env, napi_get_value_double(env, argv[0], &height));
    double density = GetDensity();
    height *= density;

    if (height_ != height) {
        height_ = height;
        offscreenCanvasPattern_->UpdateSize(width_, height_);
        if (offscreenCanvasContext_ != nullptr) {
            offscreenCanvasContext_->SetHeight(height_);
        }
    }
    return nullptr;
}

napi_value JSOffscreenCanvas::onTransferToImageBitmap(napi_env env)
{
    if (offscreenCanvasPattern_ == nullptr || offscreenCanvasContext_ == nullptr) {
        return nullptr;
    }
    napi_value renderImage = nullptr;
    napi_create_object(env, &renderImage);
    auto pixelMap = offscreenCanvasPattern_->TransferToImageBitmap();
    if (!JSRenderImage::CreateJSRenderImage(env, pixelMap, renderImage)) {
        return nullptr;
    }
    void* nativeObj = nullptr;
    NAPI_CALL(env, napi_unwrap(env, renderImage, &nativeObj));
    auto jsImage = (JSRenderImage*)nativeObj;
    CHECK_NULL_RETURN(jsImage, nullptr);
#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = offscreenCanvasPattern_->GetImageData(0, 0, width_, height_);
    if (imageData == nullptr) {
        return nullptr;
    }
    jsImage->SetImageData(std::make_shared<Ace::ImageData>(*imageData));
#endif
    jsImage->SetUnit(GetUnit());
    jsImage->SetWidth(GetWidth());
    jsImage->SetHeight(GetHeight());
    return renderImage;
}

napi_value JSOffscreenCanvas::onGetContext(napi_env env, napi_callback_info info)
{
    isGetContext_ = true;
    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_value offscreenCanvas = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &offscreenCanvas, nullptr));
    if (argc < ARGS_COUNT_ONE || argc > ARGS_COUNT_TWO) {
        LOGD("Invalid args.");
        return nullptr;
    }
    if (argv[0] == nullptr) {
        return nullptr;
    }
    if (!Container::IsCurrentUseNewPipeline()) {
        return nullptr;
    }

    size_t textLen = 0;
    std::string contextType = "";
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &textLen);
    std::unique_ptr<char[]> text = std::make_unique<char[]>(textLen + 1);
    napi_get_value_string_utf8(env, argv[0], text.get(), textLen + 1, &textLen);
    contextType = text.get();
    if (contextType == "2d") {
        contextType_ = ContextType::CONTEXT_2D;
        auto jsInfo = reinterpret_cast<panda::JsiRuntimeCallInfo*>(info);
        auto* vm = jsInfo->GetVM();
        CHECK_NULL_RETURN(vm, nullptr);
        napi_value contextObj = CreateContext2d(env, GetWidth(), GetHeight(), vm);
        if (contextObj == nullptr) {
            return nullptr;
        }
        SetAntiAlias(argv[1]);
        offscreenCanvasContext_->SetUnit(GetUnit());
        offscreenCanvasContext_->SetDensity();
        return contextObj;
    }
    return nullptr;
}

void JSOffscreenCanvas::SetAntiAlias(napi_value argv)
{
    if (argv != nullptr) {
        panda::Local<panda::ObjectRef> localValue = NapiValueToLocalValue(argv);
        JSObject jsObject(localValue);
        offscreenCanvasSettings_ = jsObject.Unwrap<JSRenderingContextSettings>();
        if (offscreenCanvasSettings_ != nullptr && offscreenCanvasContext_ != nullptr) {
            bool anti = offscreenCanvasSettings_->GetAntialias();
            offscreenCanvasContext_->SetAnti(anti);
            offscreenCanvasContext_->SetAntiAlias();
        }
    }
}

napi_value JSOffscreenCanvas::CreateContext2d(napi_env env, double width, double height, const EcmaVM* vm)
{
    napi_value global = nullptr;
    NAPI_CALL(env, napi_get_global(env, &global));
    napi_value constructor = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, global, "OffscreenCanvasRenderingContext2D", &constructor));

    napi_value thisVal = nullptr;
    napi_create_object(env, &thisVal);
    NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &thisVal));
    if (offscreenCanvasPattern_ == nullptr) {
        return thisVal;
    }
    JSObject jsObject(vm, NapiValueToLocalValue(thisVal)->ToEcmaObject(vm));
    offscreenCanvasContext_ = Referenced::Claim(jsObject.Unwrap<JSOffscreenRenderingContext>());
    offscreenCanvasContext_->SetOffscreenPattern(offscreenCanvasPattern_);
    offscreenCanvasContext_->AddOffscreenCanvasPattern(offscreenCanvasPattern_);
    offscreenCanvasContext_->SetWidth(width_);
    offscreenCanvasContext_->SetHeight(height_);
    return thisVal;
}
} // namespace OHOS::Ace::Framework
