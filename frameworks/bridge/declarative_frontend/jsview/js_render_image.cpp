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
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Framework {

void BindNativeFunction(napi_env env, napi_value object, const char* name, napi_callback func)
{
    std::string funcName(name);
    napi_value result = nullptr;
    napi_create_function(env, funcName.c_str(), funcName.length(), func, nullptr, &result);
    napi_set_named_property(env, object, name, result);
}

void* GetNapiCallbackInfoAndThis(napi_env env, napi_callback_info info)
{
    napi_value value = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &value, nullptr);
    if (status != napi_ok) {
        return nullptr;
    }
    void* result = nullptr;
    status = napi_unwrap(env, value, &result);
    if (status != napi_ok) {
        return nullptr;
    }
    return result;
}

void* DetachImageBitmap(napi_env env, void* value, void* hint)
{
    return value;
}

napi_value AttachImageBitmap(napi_env env, void* value, void*)
{
    if (value == nullptr) {
        LOGW("Invalid parameter.");
        return nullptr;
    }
    auto image = reinterpret_cast<std::weak_ptr<JSRenderImage>*>(value)->lock();
    if (image == nullptr) {
        LOGW("Invalid context.");
        return nullptr;
    }

    napi_value imageBitmap = nullptr;
    napi_create_object(env, &imageBitmap);
    double width = image->GetWidth();
    napi_value jsWidth = nullptr;
    napi_create_double(env, width, &jsWidth);
    double height = image->GetHeight();
    napi_value jsHeight = nullptr;
    napi_create_double(env, height, &jsHeight);
    napi_value isImageBitmap = nullptr;
    napi_create_int32(env, 1, &isImageBitmap);

    napi_set_named_property(env, imageBitmap, "width", jsWidth);
    napi_set_named_property(env, imageBitmap, "height", jsHeight);
    napi_set_named_property(env, imageBitmap, "isImageBitmap", isImageBitmap);
    BindNativeFunction(env, imageBitmap, "close", JSRenderImage::JsClose);

    napi_coerce_to_native_binding_object(env, imageBitmap, DetachImageBitmap, AttachImageBitmap, value, nullptr);
    napi_wrap(
        env, imageBitmap, value,
        [](napi_env env, void* data, void* hint) {
            LOGD("Finalizer for image bitmap is called");
            auto wrapper = reinterpret_cast<JSRenderImage*>(data);
            delete wrapper;
            wrapper = nullptr;
        },
        nullptr, nullptr);
    return imageBitmap;
}

JSRenderImage::JSRenderImage() {}

napi_value JSRenderImage::Constructor(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, nullptr));
    if (argc <= 0 || argv == nullptr) {
        LOGW("Invalid args.");
        return nullptr;
    }
    size_t textLen = 0;
    std::string textString = "";
    napi_get_value_string_utf8(env, argv, nullptr, 0, &textLen);
    std::unique_ptr<char[]> text = std::make_unique<char[]>(textLen + 1);
    napi_get_value_string_utf8(env, argv, text.get(), textLen + 1, &textLen);
    textString = text.get();
    auto context = PipelineBase::GetCurrentContext();
    if (!context) {
        LOGW("Invalid context.");
        return nullptr;
    }
    if (context->IsFormRender()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(textString);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            LOGE("Not supported src : %{public}s when form render", textString.c_str());
            return nullptr;
        }
    }
    auto wrapper = new (std::nothrow) JSRenderImage();
    wrapper->src_ = textString;
    
    napi_coerce_to_native_binding_object(env, thisVar, DetachImageBitmap, AttachImageBitmap, wrapper, nullptr);
    napi_wrap(
        env, thisVar, wrapper,
        [](napi_env env, void* data, void* hint) {
            LOGD("Finalizer for image bitmap is called");
            auto wrapper = reinterpret_cast<JSRenderImage*>(data);
            delete wrapper;
            wrapper = nullptr;
        },
        nullptr, nullptr);
    return thisVar;
}

napi_value JSRenderImage::InitImageBitmap(napi_env env)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    napi_value isImageBitmap = nullptr;
    napi_create_object(env, &isImageBitmap);
    napi_create_int32(env, 1, &isImageBitmap);

    napi_property_descriptor desc[] = {
        DECLARE_NAPI_GETTER_SETTER("width", JsGetWidth, JsSetWidth),
        DECLARE_NAPI_GETTER_SETTER("height", JsGetHeight, JsSetHeight),
        DECLARE_NAPI_FUNCTION("close", JsClose),
        DECLARE_NAPI_PROPERTY("isImageBitmap", isImageBitmap),
    };
    napi_status status = napi_define_class(
        env, "ImageBitmap", NAPI_AUTO_LENGTH, Constructor, nullptr, sizeof(desc) / sizeof(*desc), desc, &object);
    if (status != napi_ok) {
        LOGW("Initialize image bitmap failed");
        return nullptr;
    }
    return object;
}

void JSRenderImage::JSBind(BindingTarget globalObj, void* nativeEngine)
{
    if (!nativeEngine) {
        return;
    }
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value jsGlobalObj = nullptr;
    napi_get_global(env, &jsGlobalObj);

    napi_value result = InitImageBitmap(env);
    napi_set_named_property(env, jsGlobalObj, "ImageBitmap", result);
}

napi_value JSRenderImage::JsGetWidth(napi_env env, napi_callback_info info)
{
    JSRenderImage* me = static_cast<JSRenderImage*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr) ? me->OnGetWidth(env) : nullptr;
}

napi_value JSRenderImage::JsGetHeight(napi_env env, napi_callback_info info)
{
    JSRenderImage* me = static_cast<JSRenderImage*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr) ? me->OnGetHeight(env) : nullptr;
}

napi_value JSRenderImage::JsClose(napi_env env, napi_callback_info info)
{
    JSRenderImage* me = static_cast<JSRenderImage*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr) ? me->OnClose() : nullptr;
}

napi_value JSRenderImage::JsSetWidth(napi_env env, napi_callback_info info)
{
    JSRenderImage* me = static_cast<JSRenderImage*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr) ? me->OnSetWidth() : nullptr;
}

napi_value JSRenderImage::JsSetHeight(napi_env env, napi_callback_info info)
{
    JSRenderImage* me = static_cast<JSRenderImage*>(GetNapiCallbackInfoAndThis(env, info));
    return (me != nullptr) ? me->OnSetHeight() : nullptr;
}

napi_value JSRenderImage::OnGetWidth(napi_env env)
{
    double width = 0.0;
    width = width_;
    width = PipelineBase::Px2VpWithCurrentDensity(width);
    napi_value jsWidth = nullptr;
    napi_create_double(env, width, &jsWidth);
    return jsWidth;
}

napi_value JSRenderImage::OnGetHeight(napi_env env)
{
    double height = 0.0;
    height = height_;
    napi_value jsHeight = nullptr;
    napi_create_double(env, height, &jsHeight);
    return jsHeight;
}

napi_value JSRenderImage::OnSetWidth()
{
    return nullptr;
}

napi_value JSRenderImage::OnSetHeight()
{
    return nullptr;
}

napi_value JSRenderImage::OnClose()
{
    for (const auto& closeCallback : closeCallbacks_) {
        if (!closeCallback) {
            continue;
        }
        closeCallback();
    }
    width_ = 0;
    height_ = 0;
    return nullptr;
}

std::string JSRenderImage::GetSrc()
{
    return src_;
}

double JSRenderImage::GetWidth()
{
    return width_;
}

double JSRenderImage::GetHeight()
{
    return height_;
}

void JSRenderImage::SetCloseCallback(std::function<void()>&& callback)
{
    closeCallbacks_.emplace_back(std::move(callback));
}
} // namespace OHOS::Ace::Framework
