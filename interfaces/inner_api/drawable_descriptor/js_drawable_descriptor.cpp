/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "js_drawable_descriptor.h"

#include <memory>

#ifndef PREVIEW
#include "pixel_map_napi.h"
#else
#include "image_source_preview.h"
#endif

#include "drawable_bridge.h"
#include "drawable_descriptor.h"
#include "base/error/error_code.h"

#include "drawable_log.h"

namespace OHOS {
namespace Ace {
namespace Napi {
namespace {
constexpr char DRAWABLE_DESCRIPTOR_NAME[] = "DrawableDescriptor";
constexpr char LAYERED_DRAWABLE_DESCRIPTOR_NAME[] = "LayeredDrawableDescriptor";
constexpr char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[] = "AnimatedDrawableDescriptor";
constexpr char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[] = "PixelMapDrawableDescriptor";

constexpr int32_t PARAMS_NUM_ONE = 1;
constexpr int32_t PARAMS_NUM_TWO = 2;
constexpr int32_t PARAMS_NUM_THREE = 3;
constexpr int32_t FOREGROUND_INDEX = 0;
constexpr int32_t BACKGROUND_INDEX = 1;
constexpr int32_t MASK_INDEX = 2;
constexpr uint32_t ANIMATED_TYPE = 2;
constexpr uint32_t PIXELMAP_TYPE = 3;
constexpr int32_t MAX_ARG_NUM = 10;

struct LoadAsyncContext {
    napi_env env;
    napi_async_work work;
    napi_deferred deferred;
    void* native;
    int32_t width = 0;
    int32_t height = 0;
    int32_t errorCode = 0;
};

struct JsEnumInt {
    std::string_view enumName;
    int32_t enumInt;  
};

const std::vector<struct JsEnumInt> g_animationStopMode = {
    { "FIRST_FRAME", 0 },
    { "LAST_FRAME", 1 },
};

napi_value CreateString(napi_env env, const std::string& str)
{
    napi_value value = nullptr;
    if (napi_create_string_utf8(env, str.c_str(), str.size(), &value) != napi_ok) {
        return nullptr;
    }
    return value;
}

void GetStringFromNapiValue(napi_env env, napi_value value, std::string& result)
{
    napi_valuetype valueType;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        result.clear();
        return;
    }
    size_t bufferSize = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &bufferSize);
    if (status != napi_ok || bufferSize == 0) {
        result.clear();
        return;
    }
    auto buffer = std::make_unique<char[]>(bufferSize + 1);
    size_t stringLength;
    status = napi_get_value_string_utf8(env, value, buffer.get(), bufferSize + 1, &stringLength);
    if (status == napi_ok && stringLength > 0) {
        result = std::string(buffer.get(), stringLength);
    } else {
        result.clear();
    }
}

bool CheckReleased(napi_env env, void* native, napi_escapable_handle_scope scope)
{
    if (native == nullptr) {
        HILOGW("CheckReleased: native is nullptr, throwing 111002");
        napi_throw_error(env, std::to_string(ERROR_CODE_DRAWABLE_RELEASED).c_str(),
            "The native memory referenced by the drawableDescriptor has been released.");
        if (scope != nullptr) {
            napi_close_escapable_handle_scope(env, scope);
        }
        return true;
    }
    return false;
}

} // namespace

thread_local napi_ref JsDrawableDescriptor::baseConstructor_;
thread_local napi_ref JsDrawableDescriptor::layeredConstructor_;
thread_local napi_ref JsDrawableDescriptor::animatedConstructor_;
thread_local napi_ref JsDrawableDescriptor::pixelMapConstructor_;

napi_value JsDrawableDescriptor::ToNapi(
    napi_env env, DrawableDescriptor* drawable, DrawableDescriptor::DrawableType type)
{
    if (!drawable) {
        return nullptr;
    }
    if (!baseConstructor_ || !layeredConstructor_ || !pixelMapConstructor_) {
        // init js class constructor by importing module manually
        napi_value globalValue;
        napi_get_global(env, &globalValue);
        napi_value func;
        napi_get_named_property(env, globalValue, "requireNapi", &func);

        napi_value module;
        napi_create_string_utf8(env, MODULE_NAME, NAPI_AUTO_LENGTH, &module);
        napi_value returnValue;
        napi_call_function(env, globalValue, func, 1, &module, &returnValue);
    }

    napi_value constructor = nullptr;
    napi_value result = nullptr;
    napi_status status;
    switch (type) {
        case DrawableDescriptor::DrawableType::LAYERED:
            status = napi_get_reference_value(env, layeredConstructor_, &constructor);
            break;
        case DrawableDescriptor::DrawableType::BASE:
        case DrawableDescriptor::DrawableType::PIXELMAP:
            status = napi_get_reference_value(env, baseConstructor_, &constructor);
            break;
        default:
            status = napi_status::napi_invalid_arg;
            break;
    }
    if (status != napi_status::napi_ok) {
        HILOGE("create reference failed, drawable constructor is null");
        return result;
    }
    NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &result));
    if (type == DrawableDescriptor::DrawableType::BASE || type == DrawableDescriptor::DrawableType::PIXELMAP) {
        TransferToNewDrawable(env, result, drawable);
    } else {
        NAPI_CALL(env, napi_wrap(env, result, drawable, Destructor, nullptr, nullptr));
    }

    return result;
}

void JsDrawableDescriptor::TransferToNewDrawable(napi_env env, napi_value result, DrawableDescriptor* drawable)
{
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        delete drawable;
        return;
    }
    void* native = nullptr;
    napi_unwrap(env, result, &native);
    if (native == nullptr) {
        delete drawable;
        return;
    }
    if (drawable->HasPixelMap()) {
        auto pixelMap = drawable->GetPixelMap();
        if (pixelMap) {
            modifier->setPixelMapByPixelMap(native, &pixelMap);
        }
    } else {
        auto rawLen = drawable->GetMediaDataLen();
        auto rawMediaData = drawable->TakeMediaData();
        if (rawMediaData && rawLen > 0) {
            modifier->setPixelRawData(native, rawMediaData.release(), rawLen);
        }
    }
    delete drawable;
}

napi_value JsDrawableDescriptor::CreatLayeredDrawable(napi_env env, void* native)
{
    if (native == nullptr) {
        return nullptr;
    }
    napi_value cons = nullptr;
    if (napi_create_object(env, &cons) != napi_ok) {
        return nullptr;
    }
    auto* layerDrawable = new LayeredDrawableDescriptor;
    if (layerDrawable == nullptr) {
        return nullptr;
    }
    auto napi_status = napi_wrap(env, cons, layerDrawable, Destructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete layerDrawable;
        return nullptr;
    }

    auto modifier = GetArkUIDrawableModifier();
    std::shared_ptr<OHOS::Media::PixelMap> pixelForeground;
    std::shared_ptr<OHOS::Media::PixelMap> pixelBackground;
    std::shared_ptr<OHOS::Media::PixelMap> pixelMask;
    if (modifier != nullptr) {
        modifier->getForegroundPixelMap(native, &pixelForeground);
        modifier->getBackgroundPixelMap(native, &pixelBackground);
        modifier->getMaskPixelMap(native, &pixelMask);
    }
    layerDrawable->SetForeground(pixelForeground);
    layerDrawable->SetBackground(pixelBackground);
    layerDrawable->SetMask(pixelMask);
    auto layeredDes = GetLayeredDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, layeredDes.size(), layeredDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreatAnimatedDrawable(napi_env env, void* native)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    if (native == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value cons = nullptr;
    if (napi_create_object(env, &cons) != napi_ok) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto napi_status = napi_wrap(env, cons, native, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    modifier->increaseRef(native);
    napi_escape_handle(env, scope, cons, &cons);
    napi_close_escapable_handle_scope(env, scope);

    auto animatedDes = GetAnimatedDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, animatedDes.size(), animatedDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreatPixelMapDrawable(napi_env env, void* native)
{
    if (native == nullptr) {
        return nullptr;
    }
    napi_value cons = nullptr;
    if (napi_create_object(env, &cons) != napi_ok) {
        return nullptr;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return nullptr;
    }
    auto* drawable = modifier->createDrawableDescriptorByType(PIXELMAP_TYPE);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
    modifier->getPixelMap(native, &pixelMap);
    if (pixelMap) {
        modifier->setPixelMapByPixelMap(drawable, &pixelMap);
    }
    auto napi_status = napi_wrap(env, cons, drawable, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        modifier->decreaseRef(drawable);
        return nullptr;
    }
    modifier->increaseRef(drawable);
    auto pixelDes = GetPixelMapDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, pixelDes.size(), pixelDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreateDrawableDescriptorTransfer(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    auto napi_status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    if (napi_status != napi_ok) {
        return nullptr;
    }
    if (argc != 1) {
        return nullptr;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType != napi_number) {
        return nullptr;
    }
    int64_t addr = 0;
    napi_get_value_int64(env, argv[0], &addr);
    auto* drawable = reinterpret_cast<void*>(addr);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return nullptr;
    }
    auto drawableType = modifier->getDrawableType(drawable);
    auto type = DrawableDescriptor::DrawableType(drawableType);
    napi_value cons = nullptr;
    switch (type) {
        case DrawableDescriptor::DrawableType::LAYERED: {
            cons = CreatLayeredDrawable(env, drawable);
            break;
        }
        case DrawableDescriptor::DrawableType::ANIMATED: {
            cons = CreatAnimatedDrawable(env, drawable);
            break;
        }
        case DrawableDescriptor::DrawableType::PIXELMAP: {
            cons = CreatPixelMapDrawable(env, drawable);
            break;
        }
        default:
            break;
    }
    return cons;
}

napi_value JsDrawableDescriptor::GetForeground(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto foreground = drawable->GetForeground();
    napi_value result = ToNapi(env, foreground.release(), DrawableDescriptor::DrawableType::PIXELMAP);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetBackground(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto background = drawable->GetBackground();
    napi_value result = ToNapi(env, background.release(), DrawableDescriptor::DrawableType::PIXELMAP);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetMask(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto mask = drawable->GetMask();
    napi_value result = ToNapi(env, mask.release(), DrawableDescriptor::DrawableType::BASE);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetMaskClipPath(napi_env env, napi_callback_info info)
{
    auto path = OHOS::Ace::Napi::LayeredDrawableDescriptor::GetStaticMaskClipPath();
    napi_value result = nullptr;
    if (napi_ok != napi_create_string_utf8(env, path.c_str(), NAPI_AUTO_LENGTH, &result)) {
        HILOGI("JsDrawableDescriptor Failed");
    }
    return result;
}

bool GetSingleParam(napi_env env, napi_callback_info info, napi_value* argv, napi_valuetype& valueType)
{
    size_t argc = 1;
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc != 1) {
        return false;
    }
    napi_typeof(env, argv[0], &valueType);
    return true;
}

napi_value JsDrawableDescriptor::SetBlendMode(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    if (napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr) != napi_ok) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value argv[1] = { 0 };
    napi_valuetype valueType = napi_undefined;
    if (!GetSingleParam(env, info, argv, valueType) || (valueType != napi_number)) {
        HILOGI("invalid number value for blendMode");
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    int32_t mode;
    napi_get_value_int32(env, argv[0], &mode);
    drawable->SetBlendMode(mode);
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
}

napi_value JsDrawableDescriptor::GetPixelMap(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    std::shared_ptr<Media::PixelMap> pixmap;
    if (type != LAYERED_DRAWABLE_DESCRIPTOR_NAME) {
        auto modifier = GetArkUIDrawableModifier();
        if (modifier == nullptr) {
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        modifier->getPixelMap(native, &pixmap);
    } else {
        auto* drawable = reinterpret_cast<DrawableDescriptor*>(native);
        if (drawable == nullptr) {
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        pixmap = drawable->GetPixelMap();
    }
    napi_value result = Media::PixelMapNapi::CreatePixelMap(env, pixmap);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::CreateLoadResult(napi_env env, int32_t width, int32_t height)
{
    napi_value loadResult = nullptr;
    napi_create_object(env, &loadResult);
    napi_value jsWidth;
    napi_value jsHeight;
    napi_create_int32(env, width, &jsWidth);
    napi_create_int32(env, height, &jsHeight);
    napi_set_named_property(env, loadResult, "imageWidth", jsWidth);
    napi_set_named_property(env, loadResult, "imageHeight", jsHeight);
    return loadResult;
}

void JsDrawableDescriptor::LoadExecute(napi_env env, void* data)
{
    if (data == nullptr) {
        HILOGE("load execute, data is nullptr");
        return;
    }
    auto context = static_cast<LoadAsyncContext*>(data);
    if (context == nullptr) {
        HILOGE("load execute, async context is nullptr");
        return;
    }
    int32_t width = 0;
    int32_t height = 0;
    int32_t errorCode = 0;
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        HILOGE("load execute, modifier is nullptr");
        return;
    }
    modifier->loadSync(context->native, &width, &height, &errorCode);
    context->errorCode = errorCode;
    context->width = width;
    context->height = height;
}

void JsDrawableDescriptor::LoadComplete(napi_env env, napi_status status, void* data)
{
    napi_value result[PARAMS_NUM_TWO];
    napi_get_undefined(env, &result[0]);
    napi_get_undefined(env, &result[1]);
    if (data == nullptr) {
        HILOGE("load complete, data is nullptr");
        return;
    }
    auto context = static_cast<LoadAsyncContext*>(data);
    if (context == nullptr) {
        HILOGE("load complete, async context is nullptr");
        return;
    }
    if (context->errorCode == 0) {
        result[1] = CreateLoadResult(env, context->width, context->height);
    } else {
        napi_value errorMsg;
        napi_value errorCode;
        napi_create_int32(env, context->errorCode, &errorCode);
        napi_create_string_utf8(env, "resource loading failed.", NAPI_AUTO_LENGTH, &errorMsg);
        napi_create_error(env, errorCode, errorMsg, &result[0]);
    }
    if (context->deferred) {
        if (context->errorCode == 0) {
            napi_resolve_deferred(env, context->deferred, result[1]);
        } else {
            napi_reject_deferred(env, context->deferred, result[0]);
        }
    }
    napi_delete_async_work(env, context->work);
    if (context != nullptr) {
        delete context;
        context = nullptr;
    }
}

napi_value JsDrawableDescriptor::Load(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    napi_value result;
    napi_get_undefined(env, &result);
    if (type != ANIMATED_DRAWABLE_DESCRIPTOR_NAME && type != PIXELMAP_DRAWABLE_DESCRIPTOR_NAME) {
        napi_escape_handle(env, scope, result, &result);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    auto asyncContext = std::make_unique<LoadAsyncContext>();
    asyncContext->native = native;
    napi_create_promise(env, &(asyncContext->deferred), &result);
    napi_value workName;
    napi_create_string_utf8(env, "AnimatedDrawableDescriptorLoad", NAPI_AUTO_LENGTH, &workName);
    status = napi_create_async_work(
        env, nullptr, workName, LoadExecute, LoadComplete, static_cast<void*>(asyncContext.get()), &asyncContext->work);
    if (status == napi_ok) {
        status = napi_queue_async_work_with_qos(env, asyncContext->work, napi_qos_user_initiated);
        if (status == napi_ok) {
            asyncContext.release();
        }
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::LoadSync(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (CheckReleased(env, native, scope)) {
        return nullptr;
    }
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    napi_value result = nullptr;
    if (type == ANIMATED_DRAWABLE_DESCRIPTOR_NAME || type == PIXELMAP_DRAWABLE_DESCRIPTOR_NAME) {
        int32_t width = 0;
        int32_t height = 0;
        int32_t errorCode = 0;
        auto modifier = GetArkUIDrawableModifier();
        if (modifier == nullptr) {
            napi_throw_error(env, std::to_string(errorCode).c_str(), "resource loading failed.");
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        modifier->loadSync(native, &width, &height, &errorCode);
        if (errorCode != 0) {
            napi_throw_error(env, std::to_string(errorCode).c_str(), "resource loading failed.");
        } else {
            result = CreateLoadResult(env, width, height);
        }
    } else {
        GET_AND_THROW_LAST_ERROR((env));
    }
    if (!result) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetAnimationController(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    if (native == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    std::string id {};
    if (argc == 1) {
        GetStringFromNapiValue(env, argv[0], id);
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    auto* controller = modifier->getAnimatedController(native, id.c_str());
    if (controller == nullptr) {
        napi_escape_handle(env, scope, result, &result);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    napi_create_object(env, &result);
    napi_wrap(env, result, controller, [](napi_env env, void* data, void* hint) {}, nullptr, nullptr);
    napi_property_descriptor des[] = {
        DECLARE_NAPI_FUNCTION("getStatus", GetStatus),
        DECLARE_NAPI_FUNCTION("start", Start),
        DECLARE_NAPI_FUNCTION("stop", Stop),
        DECLARE_NAPI_FUNCTION("pause", Pause),
        DECLARE_NAPI_FUNCTION("resume", Resume),
    };
    status = napi_define_properties(env, result, sizeof(des) / sizeof(des[0]), des);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::Start(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    modifier->startAnimated(native);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::Stop(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    modifier->stopAnimated(native);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::Pause(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    modifier->pauseAnimated(native);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::Resume(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    modifier->resumeAnimated(native);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetStatus(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    napi_value result;
    napi_get_boolean(env, false, &result);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    auto animationStatus = modifier->getAnimatedStatus(native);
    napi_create_int32(env, animationStatus, &result);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::Release(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    // Check _released flag to prevent repeated release
    napi_value internalReleased;
    status = napi_get_named_property(env, thisVar, "_released", &internalReleased);
    if (status == napi_ok) {
        bool released = false;
        napi_get_value_bool(env, internalReleased, &released);
        if (released) {
            HILOGW("JsDrawableDescriptor::Release already released, skip");
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
    }

    // Unbind JS ↔ native: napi_remove_wrap detaches the native pointer,
    // subsequent napi_unwrap will return nullptr
    void* native = nullptr;
    if (napi_remove_wrap(env, thisVar, &native) != napi_ok || native == nullptr) {
        HILOGE("JsDrawableDescriptor::Release napi_remove_wrap failed");
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    // Mark released on JS object
    napi_value trueValue;
    napi_get_boolean(env, true, &trueValue);
    napi_set_named_property(env, thisVar, "_released", trueValue);

    napi_close_escapable_handle_scope(env, scope);
    HILOGI("JsDrawableDescriptor::Release done");
    return nullptr;
}

napi_value JsDrawableDescriptor::IsReleased(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);

    // Check _released flag on JS object
    napi_value internalReleased;
    bool isReleased = false;
    napi_status status = napi_get_named_property(env, thisVar, "_released", &internalReleased);
    if (status == napi_ok) {
        napi_get_value_bool(env, internalReleased, &isReleased);
    }

    napi_value result = nullptr;
    napi_get_boolean(env, isReleased, &result);
    return result;
}

void JsDrawableDescriptor::Destructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    if (nativeObject == nullptr) {
        return;
    }
    auto* field = reinterpret_cast<DrawableDescriptor*>(nativeObject);
    delete field;
}

void JsDrawableDescriptor::NewDestructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return;
    }
    modifier->decreaseRef(nativeObject);
}

void JsDrawableDescriptor::ParseAnimationOptions(napi_env env, napi_value napiOptions, AnimationOptions& options)
{
    napi_value napiDuration;
    napi_value napiIterations;
    napi_value napiAutoPlay;
    napi_value napiStopMode;
    napi_value napiFrameDurations;
    int32_t duration = -1;
    int32_t iterations = 1;
    int32_t stopMode = 0;
    bool autoPlay = true;
    std::vector<int32_t> durations;
    napi_get_named_property(env, napiOptions, "duration", &napiDuration);
    napi_get_named_property(env, napiOptions, "iterations", &napiIterations);
    napi_get_named_property(env, napiOptions, "autoPlay", &napiAutoPlay);
    napi_get_named_property(env, napiOptions, "stopMode", &napiStopMode);
    napi_get_named_property(env, napiOptions, "frameDurations", &napiFrameDurations);
    napi_get_value_int32(env, napiDuration, &duration);
    napi_get_value_int32(env, napiIterations, &iterations);
    napi_get_value_int32(env, napiStopMode, &stopMode);
    napi_get_value_bool(env, napiAutoPlay, &autoPlay);
    options.autoPlay = autoPlay;
    options.duration = duration;
    options.iterations = iterations;
    options.stopMode = stopMode;
    bool isArray;
    napi_status status = napi_is_array(env, napiFrameDurations, &isArray);
    if (status != napi_ok || !isArray) {
        return;
    }
    uint32_t length;
    status = napi_get_array_length(env, napiFrameDurations, &length);
    if (status != napi_ok) {
        return;
    }
    for (uint32_t i = 0; i < length; i++) {
        napi_value element;
        status = napi_get_element(env, napiFrameDurations, i, &element);
        if (status != napi_ok) {
            return;
        }
        napi_valuetype valuetype;
        status = napi_typeof(env, element, &valuetype);
        if (status != napi_ok || valuetype != napi_number) {
            return;
        }
        double value;
        status = napi_get_value_double(env, element, &value);
        if (status != napi_ok) {
            return;
        }
        durations.push_back(static_cast<int32_t>(value));
    }
    options.durations = durations;
}

napi_value JsDrawableDescriptor::AnimatedConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    if (argc < 1) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto* animatedDrawable = modifier->createDrawableDescriptorByType(ANIMATED_TYPE);
    napi_valuetype valueType;
    napi_status status = napi_typeof(env, argv[0], &valueType);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    if (valueType == napi_string) {
        std::string src {};
        GetStringFromNapiValue(env, argv[0], src);
        if (!src.empty()) {
            modifier->setDrawablePath(animatedDrawable, src.c_str());
        }
    }
    if (valueType == napi_object) {
        bool isArray = false;
        napi_is_array(env, argv[0], &isArray);
        if (isArray) {
            auto pixelMapsPtr = Media::PixelMapNapi::GetPixelMaps(env, argv[0]);
            if (pixelMapsPtr) {
                modifier->setPixelMapList(animatedDrawable, pixelMapsPtr.get());
            }
        } else {
            auto resourceObject = ParseResourceObject(argv[0]);
            if (resourceObject != nullptr) {
                modifier->setDrawableResource(animatedDrawable, resourceObject);
            }
        }
    }
    AnimationOptions options;
    if (argc > 1 && argv[1]) {
        ParseAnimationOptions(env, argv[1], options);
    }
    modifier->setAnimatedDurations(animatedDrawable, &options.durations);
    modifier->setAnimatedTotalDuration(animatedDrawable, options.duration);
    modifier->setAnimatedIterations(animatedDrawable, options.iterations);
    modifier->setAnimatedAutoPlay(animatedDrawable, options.autoPlay);
    modifier->setAnimatedStopMode(animatedDrawable, options.stopMode);
    // wrap to napi_value
    auto napi_status = napi_wrap(env, thisVar, animatedDrawable, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        modifier->decreaseRef(animatedDrawable);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    modifier->increaseRef(animatedDrawable);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

void JsDrawableDescriptor::ParseLayeredArgs(
    napi_env env, size_t argc, napi_value argv[], LayeredDrawableDescriptor* layeredDrawable)
{
    auto modifier = GetArkUIDrawableModifier();
    std::shared_ptr<Media::PixelMap> foregroundPixelMap = nullptr;
    auto handleUndefined = [&layeredDrawable, &foregroundPixelMap](int32_t pos) {
        if (pos == MASK_INDEX) {
            auto resMgr = GetResourceManager();
            layeredDrawable->InitialMask(resMgr);
        } else if (pos == BACKGROUND_INDEX && foregroundPixelMap) {
            layeredDrawable->SetBackground(foregroundPixelMap);
        }
    };
    for (size_t i = 0; i < argc && i < PARAMS_NUM_THREE; i++) {
        auto pos = static_cast<int32_t>(i);
        if (argv[i] == nullptr) {
            continue;
        }
        napi_valuetype valueType;
        napi_status status = napi_typeof(env, argv[i], &valueType);
        if (status != napi_ok || valueType == napi_undefined) {
            handleUndefined(pos);
            continue;
        }
        void* native = nullptr;
        napi_unwrap(env, argv[i], &native);
        if (native == nullptr) {
            continue;
        }
        std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
        if (modifier != nullptr) {
            modifier->getPixelMap(native, &pixelMap);
        }
        if (!pixelMap) {
            handleUndefined(pos);
            continue;
        }
        if (pos == FOREGROUND_INDEX) {
            layeredDrawable->SetForeground(pixelMap);
            foregroundPixelMap = pixelMap;
        } else if (pos == BACKGROUND_INDEX) {
            layeredDrawable->SetBackground(pixelMap);
        } else if (pos == MASK_INDEX) {
            layeredDrawable->SetMask(pixelMap);
        }
    }
}

napi_value JsDrawableDescriptor::LayeredConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    size_t argc = PARAMS_NUM_THREE;
    napi_value argv[argc];
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto* layeredDrawable = new LayeredDrawableDescriptor;
    if (argc > 0) {
        ParseLayeredArgs(env, argc, argv, layeredDrawable);
    }
    napi_wrap(env, thisVar, layeredDrawable, Destructor, nullptr, nullptr);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

void JsDrawableDescriptor::ParsePixelMapConstructorArg(napi_env env, void* drawable, napi_value arg)
{
    napi_valuetype valueType;
    napi_status status = napi_typeof(env, arg, &valueType);
    if (status != napi_ok) {
        return;
    }
    if (valueType == napi_string) {
        std::string src {};
        GetStringFromNapiValue(env, arg, src);
        if (!src.empty()) {
            auto modifier = GetArkUIDrawableModifier();
            if (modifier != nullptr) {
                modifier->setDrawablePath(drawable, src.c_str());
            }
        }
        return;
    }
    if (valueType == napi_object) {
        auto pixelMap = Media::PixelMapNapi::GetPixelMap(env, arg);
        auto modifier = GetArkUIDrawableModifier();
        if (modifier == nullptr) {
            return;
        }
        if (pixelMap) {
            modifier->setPixelMapByPixelMap(drawable, &pixelMap);
            return;
        }
        auto resourceObject = ParseResourceObject(arg);
        if (resourceObject != nullptr) {
            modifier->setDrawableResource(drawable, resourceObject);
        }
    }
}

napi_value JsDrawableDescriptor::PixelMapConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    size_t argc = PARAMS_NUM_ONE;
    napi_value argv[argc];
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto* drawable = modifier->createDrawableDescriptorByType(PIXELMAP_TYPE);
    if (argc > 0 && argv[0] != nullptr) {
        ParsePixelMapConstructorArg(env, drawable, argv[0]);
    }
    modifier->increaseRef(drawable);
    auto napi_status = napi_wrap(env, thisVar, drawable, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        modifier->decreaseRef(drawable);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

napi_value JsDrawableDescriptor::DrawableConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto* drawable = modifier->createDrawableDescriptorByType(PIXELMAP_TYPE);
    modifier->increaseRef(drawable);
    auto napi_status = napi_wrap(env, thisVar, drawable, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        modifier->decreaseRef(drawable);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetBaseDrawableDescriptor(napi_env env)
{
    napi_value typeName = CreateString(env, std::string(PIXELMAP_DRAWABLE_DESCRIPTOR_NAME));
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load),
        DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("release", Release),
        DECLARE_NAPI_FUNCTION("isReleased", IsReleased),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetPixelMapDrawableDescriptor(napi_env env)
{
    napi_value typeName = CreateString(env, std::string(PIXELMAP_DRAWABLE_DESCRIPTOR_NAME));
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load),
        DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("release", Release),
        DECLARE_NAPI_FUNCTION("isReleased", IsReleased),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetLayeredDrawableDescriptor(napi_env env)
{
    napi_value typeName = CreateString(env, std::string(LAYERED_DRAWABLE_DESCRIPTOR_NAME));
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load),
        DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("getForeground", GetForeground),
        DECLARE_NAPI_FUNCTION("getBackground", GetBackground),
        DECLARE_NAPI_FUNCTION("getMask", GetMask),
        DECLARE_NAPI_STATIC_FUNCTION("getMaskClipPath", GetMaskClipPath),
        DECLARE_NAPI_FUNCTION("setBlendMode", SetBlendMode),
        DECLARE_NAPI_FUNCTION("release", Release),
        DECLARE_NAPI_FUNCTION("isReleased", IsReleased),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetAnimatedDrawableDescriptor(napi_env env)
{
    napi_value typeName = CreateString(env, std::string(ANIMATED_DRAWABLE_DESCRIPTOR_NAME));
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load),
        DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("getAnimationController", GetAnimationController),
        DECLARE_NAPI_FUNCTION("release", Release),
        DECLARE_NAPI_FUNCTION("isReleased", IsReleased),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

napi_value JsDrawableDescriptor::InitDrawable(napi_env env)
{
    napi_value cons = nullptr;
    auto baseDes = GetBaseDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_class(env, DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, DrawableConstructor, nullptr,
                       baseDes.size(), baseDes.data(), &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &baseConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitPixelMapDrawable(napi_env env)
{
    napi_value cons = nullptr;
    auto pixelDes = GetPixelMapDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_class(env, PIXELMAP_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, PixelMapConstructor,
                       nullptr, pixelDes.size(), pixelDes.data(), &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &pixelMapConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitLayeredDrawable(napi_env env)
{
    napi_value cons = nullptr;
    auto layeredDes = GetLayeredDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_class(env, LAYERED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, LayeredConstructor,
                       nullptr, layeredDes.size(), layeredDes.data(), &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &layeredConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitAnimatedDrawable(napi_env env)
{
    napi_value cons = nullptr;
    auto animatedDes = GetAnimatedDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_class(env, ANIMATED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, AnimatedConstructor,
                       nullptr, animatedDes.size(), animatedDes.data(), &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &animatedConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitAnimationStopMode(napi_env env, napi_value exports)
{
    const char* enumClassName = "AnimationStopMode";
    auto vecSize = g_animationStopMode.size();
    std::vector<napi_value> value(vecSize);
    std::vector<napi_property_descriptor> property(vecSize);
    for (size_t index = 0; index < vecSize; ++index) {
        napi_create_int32(env, g_animationStopMode[index].enumInt, &value[index]);
        property[index] = napi_property_descriptor DECLARE_NAPI_STATIC_PROPERTY(
            g_animationStopMode[index].enumName.data(), value[index]);
    }

    auto napiConstructor = [](napi_env env, napi_callback_info info) {
        napi_value jsThis = nullptr;
        napi_get_cb_info(env, info, nullptr, nullptr, &jsThis, nullptr);
        return jsThis;
    };

    napi_value result = nullptr;
    napi_status napiStatus = napi_define_class(
        env, enumClassName, NAPI_AUTO_LENGTH, napiConstructor, nullptr, property.size(), property.data(), &result);
    if (napiStatus != napi_ok) {
        return nullptr;
    }

    napiStatus = napi_set_named_property(env, exports, enumClassName, result);
    if (napiStatus != napi_ok) {
        return nullptr;
    }
    return exports;
}

napi_value JsDrawableDescriptor::Export(napi_env env, napi_value exports)
{
    napi_value cons = InitDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, DRAWABLE_DESCRIPTOR_NAME, cons));
    cons = InitPixelMapDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, PIXELMAP_DRAWABLE_DESCRIPTOR_NAME, cons));
    cons = InitLayeredDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, LAYERED_DRAWABLE_DESCRIPTOR_NAME, cons));
    cons = InitAnimatedDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, ANIMATED_DRAWABLE_DESCRIPTOR_NAME, cons));
    InitAnimationStopMode(env, exports);

    napi_property_descriptor createTransferDesc[] = { DECLARE_NAPI_FUNCTION(
        "__createTransfer__", CreateDrawableDescriptorTransfer) };
    NAPI_CALL(env, napi_define_properties(
        env, exports, sizeof(createTransferDesc) / sizeof(createTransferDesc[0]), createTransferDesc));
    return exports;
}
} // namespace Napi
} // namespace Ace
} // namespace OHOS
