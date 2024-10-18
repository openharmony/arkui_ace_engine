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

#include "bridge/declarative_frontend/jsview/canvas/js_render_image.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/container.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif

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
    auto* wrapper = (JSRenderImage*)value;
    if (wrapper == nullptr) {
        LOGW("Invalid context.");
        return nullptr;
    }

    napi_value imageBitmap = nullptr;
    napi_create_object(env, &imageBitmap);
    napi_value isImageBitmap = nullptr;
    napi_create_int32(env, 1, &isImageBitmap);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_GETTER_SETTER("width", JSRenderImage::JsGetWidth, JSRenderImage::JsSetWidth),
        DECLARE_NAPI_GETTER_SETTER("height", JSRenderImage::JsGetHeight, JSRenderImage::JsSetHeight),
        DECLARE_NAPI_FUNCTION("close", JSRenderImage::JsClose),
        DECLARE_NAPI_PROPERTY("isImageBitmap", isImageBitmap),
    };
    napi_define_properties(env, imageBitmap, sizeof(desc) / sizeof(*desc), desc);

    napi_coerce_to_native_binding_object(env, imageBitmap, DetachImageBitmap, AttachImageBitmap, value, nullptr);
    napi_wrap_with_size(env, imageBitmap, value, JSRenderImage::Finalizer, nullptr, nullptr, wrapper->GetBindingSize());
    wrapper->IncRefCount();
    return imageBitmap;
}

JSRenderImage::JSRenderImage() {}

void JSRenderImage::Finalizer(napi_env env, void* data, void* hint)
{
    auto wrapper = reinterpret_cast<JSRenderImage*>(data);
    if (wrapper) {
        wrapper->DecRefCount();
    }
}

napi_value JSRenderImage::Constructor(napi_env env, napi_callback_info info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    size_t argc = 0;
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, nullptr, &thisVar, nullptr));
    auto wrapper = AceType::MakeRefPtr<JSRenderImage>();
    wrapper->SetInstanceId(OHOS::Ace::Container::CurrentId());
    if (argc <= 0) {
        napi_coerce_to_native_binding_object(
            env, thisVar, DetachImageBitmap, AttachImageBitmap, AceType::RawPtr(wrapper), nullptr);
        napi_wrap(env, thisVar, AceType::RawPtr(wrapper), Finalizer, nullptr, nullptr);
        wrapper->IncRefCount();
        return thisVar;
    }
    napi_value argv[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc == 2) {  // 2: args count
        int32_t unit = 0;
        napi_get_value_int32(env, argv[1], &unit);
        if (static_cast<CanvasUnit>(unit) == CanvasUnit::PX) {
            wrapper->SetUnit(CanvasUnit::PX);
        }
    }
    size_t textLen = 0;
    auto status = napi_get_value_string_utf8(env, argv[0], nullptr, 0, &textLen);
    if (status == napi_ok) {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(context, nullptr);
        std::string textString = GetSrcString(env, argv[0], textLen);
        if (context->IsFormRender() && NotFormSupport(textString)) {
            LOGE("Not supported src : %{public}s when form render", textString.c_str());
            return nullptr;
        }
        wrapper->LoadImage(textString);
    } else {
#ifdef PIXEL_MAP_SUPPORTED
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto pixelMap = GetPixelMap(env, argv[0]);
            CHECK_NULL_RETURN(pixelMap, nullptr);
            wrapper->LoadImage(pixelMap);
        }
#endif
    }
    napi_coerce_to_native_binding_object(
        env, thisVar, DetachImageBitmap, AttachImageBitmap, AceType::RawPtr(wrapper), nullptr);
    napi_wrap_with_size(env, thisVar, AceType::RawPtr(wrapper), Finalizer, nullptr, nullptr, wrapper->GetBindingSize());
    wrapper->IncRefCount();
    return thisVar;
}

bool JSRenderImage::NotFormSupport(const std::string& textString)
{
    SrcType srcType = ImageSourceInfo::ResolveURIType(textString);
    return (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
}

std::string JSRenderImage::GetSrcString(napi_env env, napi_value value, size_t textLen)
{
    std::unique_ptr<char[]> text = std::make_unique<char[]>(textLen + 1);
    auto status = napi_get_value_string_utf8(env, value, text.get(), textLen + 1, &textLen);
    if ((status == napi_ok) && (text != nullptr)) {
        return text.get();
    }
    return "";
}

#ifdef PIXEL_MAP_SUPPORTED
RefPtr<PixelMap> JSRenderImage::GetPixelMap(napi_env env, napi_value value)
{
    Media::PixelMapNapi* napiPixelMap = nullptr;
    auto status = napi_unwrap(env, value, reinterpret_cast<void**>(&napiPixelMap));
    if ((status != napi_ok) || (napiPixelMap == nullptr)) {
        return nullptr;
    }
    return PixelMap::CreatePixelMap(napiPixelMap->GetPixelMap());
}
#endif

napi_value JSRenderImage::InitImageBitmap(napi_env env)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    napi_value isImageBitmap = nullptr;
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
    double density = GetDensity();
    width = width_;
    width /= density;
    napi_value jsWidth = nullptr;
    napi_create_double(env, width, &jsWidth);
    return jsWidth;
}

napi_value JSRenderImage::OnGetHeight(napi_env env)
{
    double height = 0.0;
    double density = GetDensity();
    height = height_;
    height /= density;
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

void JSRenderImage::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    width_ = loadingCtx_->GetImageSize().Width();
    height_ = loadingCtx_->GetImageSize().Height();
    loadingCtx_->MakeCanvasImageIfNeed(loadingCtx_->GetImageSize(), true, ImageFit::NONE);
}

void JSRenderImage::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    image_ = loadingCtx_->MoveCanvasImage();
    CHECK_NULL_VOID(image_);
    imageObj_ = loadingCtx_->MoveImageObject();
    CHECK_NULL_VOID(imageObj_);
    pixelMap_ = image_->GetPixelMap();
    svgDom_ = imageObj_->GetSVGDom();
    imageFit_ = loadingCtx_->GetImageFit();
    imageSize_ = loadingCtx_->GetImageSize();
    bindingSize_ = pixelMap_ ? static_cast<size_t>(pixelMap_->GetByteCount()) : 0;
}

void JSRenderImage::OnImageLoadFail(const std::string& errorMsg)
{
    width_ = 0;
    height_ = 0;
    pixelMap_ = nullptr;
    svgDom_ = nullptr;
}

void JSRenderImage::LoadImage(const std::string& src)
{
    src_ = src;
    auto sourceInfo = ImageSourceInfo(src);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}

void JSRenderImage::LoadImage(const RefPtr<PixelMap>& pixmap)
{
    auto sourceInfo = ImageSourceInfo(pixmap);
    sourceInfo_ = sourceInfo;
    LoadImage(sourceInfo);
}

void JSRenderImage::LoadImage(const ImageSourceInfo& sourceInfo)
{
    auto dataReadyCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto jsRenderImage = weak.Upgrade();
        CHECK_NULL_VOID(jsRenderImage);
        jsRenderImage->OnImageDataReady();
    };
    auto loadSuccessCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto jsRenderImage = weak.Upgrade();
        CHECK_NULL_VOID(jsRenderImage);
        jsRenderImage->OnImageLoadSuccess();
    };
    auto loadFailCallback = [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo, const std::string& errorMsg) {
        auto jsRenderImage = weak.Upgrade();
        CHECK_NULL_VOID(jsRenderImage);
        jsRenderImage->OnImageLoadFail(errorMsg);
    };
    NG::LoadNotifier loadNotifier(dataReadyCallback, loadSuccessCallback, loadFailCallback);
    loadingCtx_ = AceType::MakeRefPtr<NG::ImageLoadingContext>(sourceInfo, std::move(loadNotifier), true);
    loadingCtx_->LoadImageData();
}

std::string JSRenderImage::GetSrc()
{
    return src_;
}

double JSRenderImage::GetWidth()
{
    return width_;
}

void JSRenderImage::SetWidth(double width)
{
    width_ = width;
}

double JSRenderImage::GetHeight()
{
    return height_;
}

void JSRenderImage::SetHeight(double height)
{
    height_ = height;
}

void JSRenderImage::SetCloseCallback(std::function<void()>&& callback)
{
    closeCallbacks_.emplace_back(std::move(callback));
}

bool JSRenderImage::CreateJSRenderImage(napi_env env, RefPtr<PixelMap> pixelMap, napi_value& renderImage)
{
    napi_value global = nullptr;
    napi_status status = napi_get_global(env, &global);
    if (status != napi_ok) {
        return false;
    }
    napi_value constructor = nullptr;
    status = napi_get_named_property(env, global, "ImageBitmap", &constructor);
    if (status != napi_ok) {
        return false;
    }
#ifdef PIXEL_MAP_SUPPORTED
    CHECK_NULL_RETURN(pixelMap, false);
    auto pixelmapSharedPtr = pixelMap->GetPixelMapSharedPtr();
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelmapSharedPtr);
    status = napi_new_instance(env, constructor, 1, &napiValue, &renderImage);
#else
    status = napi_new_instance(env, constructor, 0, nullptr, &renderImage);
#endif
    return status == napi_ok;
}
} // namespace OHOS::Ace::Framework