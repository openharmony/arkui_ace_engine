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
#include "resource_manager.h"

#include "base/log.h"
#include "base/marcos.h"

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

struct LoadAsyncContext {
    napi_env env;
    napi_async_work work;
    napi_deferred deferred;
    void* native;
    int32_t width = 0;
    int32_t height = 0;
    int32_t errorCode = 0;
};

void UpdateLayeredParam(
    LayeredDrawableDescriptor* layeredDrawable, int32_t pos, std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    if (!layeredDrawable || !pixelMap) {
        return;
    }
    switch (pos) {
        case FOREGROUND_INDEX:
            layeredDrawable->SetForeground(pixelMap);
            break;
        case BACKGROUND_INDEX:
            layeredDrawable->SetBackground(pixelMap);
            break;
        case MASK_INDEX:
            layeredDrawable->SetMask(pixelMap);
            break;
        default:
            HILOGW("Arg[%{public}d] index error", pos);
    }
}

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
            status = napi_get_reference_value(env, baseConstructor_, &constructor);
            break;
        case DrawableDescriptor::DrawableType::PIXELMAP:
            status = napi_get_reference_value(env, pixelMapConstructor_, &constructor);
            break;
        default:
            status = napi_status::napi_invalid_arg;
            break;
    }
    if (status == napi_status::napi_ok) {
        NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &result));
        NAPI_CALL(env, napi_wrap(env, result, drawable, Destructor, nullptr, nullptr));
    } else {
        HILOGI("create reference failed, drawable constructor is null");
    }

    return result;
}

napi_value JsDrawableDescriptor::GetForeground(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
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
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
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
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(native);
    if (!drawable) {
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
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    std::shared_ptr<Media::PixelMap> pixmap;
    if (type == "AnimatedDrawableDescriptor") {
        GetPixelMapC(native, pixmap);
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
    AnimatedLoadSync(context->native, width, height, errorCode);
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
        napi_create_string_utf8(env, "resource loading failed.", NAPI_AUTO_LENGTH, &result[0]);
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
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    napi_value result;
    napi_get_undefined(env, &result);
    if (type != "AnimatedDrawableDescriptor") {
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
    napi_value typeName;
    napi_get_named_property(env, thisVar, "typeName", &typeName);
    std::string type;
    GetStringFromNapiValue(env, typeName, type);
    if (type == "AnimatedDrawableDescriptor") {
        int32_t width = 0;
        int32_t height = 0;
        int32_t errorCode = 0;
        AnimatedLoadSync(native, width, height, errorCode);
        if (errorCode != 0) {
            napi_throw_error(env, std::to_string(errorCode).c_str(), "resource loading failed");
            napi_close_escapable_handle_scope(env, scope);
            return nullptr;
        }
        auto result = CreateLoadResult(env, width, height);
        napi_escape_handle(env, scope, result, &result);
        napi_close_escapable_handle_scope(env, scope);
        return result;
    }
    GET_AND_THROW_LAST_ERROR((env));
    napi_close_escapable_handle_scope(env, scope);
    return nullptr;
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
    // with id
    std::string id {};
    if (argc == 1) {
        GetStringFromNapiValue(env, argv[0], id);
    }
    auto* controller = AnimatedGetController(native, id.c_str());
    if (controller == nullptr) {
        return result;
    }
    napi_value jsController = nullptr;
    napi_create_object(env, &jsController);
    napi_wrap(env, jsController, controller, [](napi_env env, void* data, void* hint) {}, nullptr, nullptr);
    napi_property_descriptor des[] = {
        DECLARE_NAPI_FUNCTION("getStatus", GetStatus),
        DECLARE_NAPI_FUNCTION("start", Start),
        DECLARE_NAPI_FUNCTION("stop", Stop),
        DECLARE_NAPI_FUNCTION("pause", Pause),
        DECLARE_NAPI_FUNCTION("resume", Resume),
    };
    NAPI_CALL(env, napi_define_properties(env, jsController, sizeof(des) / sizeof(des[0]), des));
    napi_close_escapable_handle_scope(env, scope);
    return jsController;
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
    AnimatedStartC(native);
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
    AnimatedStopC(native);
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
    AnimatedPauseC(native);
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
    AnimatedResumeC(native);
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
    auto animationStatus = AnimatedGetStatusC(native);
    napi_create_int32(env, animationStatus, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

void JsDrawableDescriptor::Destructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    auto* field = reinterpret_cast<DrawableDescriptor*>(nativeObject);
    delete field;
}

void JsDrawableDescriptor::NewDestructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    DecreaseRefCountDrawableC(nativeObject);
}

void JsDrawableDescriptor::ParseAnimationOptions(napi_env env, napi_value napiOptions, AnimationOptions& options)
{
    napi_value napiDuration;
    napi_value napiIterations;
    napi_value napiAutoPlay;
    napi_value napiFrameDurations;
    int32_t duration = -1;
    int32_t iterations = 1;
    bool autoPlay = true;
    std::vector<int32_t> durations;
    napi_get_named_property(env, napiOptions, "duration", &napiDuration);
    napi_get_named_property(env, napiOptions, "iterations", &napiIterations);
    napi_get_named_property(env, napiOptions, "autoPlay", &napiAutoPlay);
    napi_get_named_property(env, napiOptions, "frameDurations", &napiFrameDurations);
    napi_get_value_int32(env, napiDuration, &duration);
    napi_get_value_int32(env, napiIterations, &iterations);
    napi_get_value_bool(env, napiAutoPlay, &autoPlay);
    options.autoPlay = autoPlay;
    options.duration = duration;
    options.iterations = iterations;
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
        return nullptr;
    }
    auto* animatedDrawable = CreateDrawableC(ANIMATED_TYPE);
    bool isArray = false;
    napi_is_array(env, argv[0], &isArray);
    if (isArray) {
        auto pixelMapsPtr = Media::PixelMapNapi::GetPixelMaps(env, argv[0]);
        std::vector<void*> rawPixelMaps;
        if (pixelMapsPtr) {
            for (auto& sharedPixelMap : *pixelMapsPtr) {
                rawPixelMaps.push_back(reinterpret_cast<void*>(&sharedPixelMap));
            }
        }
        AnimatedSetPixelMapListC(animatedDrawable, rawPixelMaps);
    } else {
        std::string src {};
        GetStringFromNapiValue(env, argv[0], src);
        if (!src.empty()) {
            AnimatedSetPath(animatedDrawable, src.c_str());
        } else {
            // parse resources
            auto resourceObject = ParseResourceObject(argv[0]);
            if (resourceObject != nullptr) {
                AnimatedSetResource(animatedDrawable, resourceObject);
            }
        }
    }
    AnimationOptions options;
    if (argc > 1 && argv[1]) {
        ParseAnimationOptions(env, argv[1], options);
    }
    AnimatedSetDurationsC(animatedDrawable, options.durations);
    AnimatedSetTotalDurationC(animatedDrawable, options.duration);
    AnimatedSetIterationsC(animatedDrawable, options.iterations);
    AnimatedSetAutoPlayC(animatedDrawable, options.autoPlay);
    // wrap to napi_value
    auto napi_status = napi_wrap(env, thisVar, animatedDrawable, NewDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        DecreaseRefCountDrawableC(animatedDrawable);
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    IncreaseRefCountDrawableC(animatedDrawable);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
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
    auto pos = -1;
    auto* layeredDrawable = new LayeredDrawableDescriptor;
    if (argc == 0) {
        napi_wrap(env, thisVar, layeredDrawable, Destructor, nullptr, nullptr);
        napi_escape_handle(env, scope, thisVar, &thisVar);
        napi_close_escapable_handle_scope(env, scope);
        return thisVar;
    }
    std::shared_ptr<Media::PixelMap> foregroundPixelMap = nullptr;
    auto updateUndefinedPixelMap = [&pos, &layeredDrawable, &foregroundPixelMap]() -> void {
        if (pos == MASK_INDEX) {
            std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
            layeredDrawable->InitialMask(resMgr);
        } else if (pos == BACKGROUND_INDEX && foregroundPixelMap) {
            UpdateLayeredParam(layeredDrawable, pos, foregroundPixelMap);
        }
    };
    napi_valuetype type;
    for (const auto& arg : argv) {
        pos++;
        napi_typeof(env, arg, &type);
        if (type == napi_undefined) {
            updateUndefinedPixelMap();
            continue;
        }
        // parse pixelmap drawable descriptor
        void* drawable = nullptr;
        napi_unwrap(env, arg, &drawable);
        auto drawableDescritor = reinterpret_cast<DrawableDescriptor*>(drawable);
        if (drawableDescritor) {
            auto pixelMap = drawableDescritor->GetPixelMap();
            if (!pixelMap) {
                updateUndefinedPixelMap();
            } else {
                UpdateLayeredParam(layeredDrawable, pos, pixelMap);
                if (pos == FOREGROUND_INDEX)
                    foregroundPixelMap = std::move(pixelMap);
            }
        }
    }
    napi_wrap(env, thisVar, layeredDrawable, Destructor, nullptr, nullptr);
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
    // create JsDrawable
    auto* drawable = new DrawableDescriptor;
    // wrap to napi_value
    napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
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
    auto* drawable = new DrawableDescriptor;
    if (argc == 0) {
        HILOGW("JsDrawableDescriptor::PixelMapConstructor get null pixelMap param");
        napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
        napi_escape_handle(env, scope, thisVar, &thisVar);
        napi_close_escapable_handle_scope(env, scope);
        return thisVar;
    }
    napi_value argPixelMap = argv[0];
    napi_valuetype type;
    napi_typeof(env, argPixelMap, &type);
    if (type == napi_object) {
        auto pixelMap = Media::PixelMapNapi::GetPixelMap(env, argPixelMap);
        if (pixelMap) {
            drawable->SetPixelMap(pixelMap);
        }
    }

    // wrap to napi_value
    napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

napi_value JsDrawableDescriptor::InitDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string(DRAWABLE_DESCRIPTOR_NAME));
    napi_property_descriptor baseDes[] = { DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load), DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName) };
    NAPI_CALL(env, napi_define_class(env, DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, DrawableConstructor, nullptr,
                       sizeof(baseDes) / sizeof(napi_property_descriptor), baseDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &baseConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitPixelMapDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string(PIXELMAP_DRAWABLE_DESCRIPTOR_NAME));
    napi_property_descriptor pixelDes[] = { DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load), DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName) };
    NAPI_CALL(env, napi_define_class(env, PIXELMAP_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, PixelMapConstructor,
                       nullptr, sizeof(pixelDes) / sizeof(napi_property_descriptor), pixelDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &pixelMapConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitLayeredDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string(LAYERED_DRAWABLE_DESCRIPTOR_NAME));
    napi_property_descriptor layeredDes[] = { DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load), DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("getForeground", GetForeground), DECLARE_NAPI_FUNCTION("getBackground", GetBackground),
        DECLARE_NAPI_FUNCTION("getMask", GetMask), DECLARE_NAPI_STATIC_FUNCTION("getMaskClipPath", GetMaskClipPath),
        DECLARE_NAPI_PROPERTY("typeName", typeName) };
    NAPI_CALL(env, napi_define_class(env, LAYERED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, LayeredConstructor,
                       nullptr, sizeof(layeredDes) / sizeof(napi_property_descriptor), layeredDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &layeredConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitAnimatedDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string(ANIMATED_DRAWABLE_DESCRIPTOR_NAME));
    napi_property_descriptor animatedDes[] = { DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("load", Load), DECLARE_NAPI_FUNCTION("loadSync", LoadSync),
        DECLARE_NAPI_FUNCTION("getAnimationController", GetAnimationController),
        DECLARE_NAPI_PROPERTY("typeName", typeName) };
    NAPI_CALL(env, napi_define_class(env, ANIMATED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, AnimatedConstructor,
                       nullptr, sizeof(animatedDes) / sizeof(napi_property_descriptor), animatedDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &animatedConstructor_));
    return cons;
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
    return exports;
}
} // namespace Napi
} // namespace Ace
} // namespace OHOS
