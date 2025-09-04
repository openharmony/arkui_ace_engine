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
#include "drawable_descriptor.h"
#include "resource_manager.h"

#include "base/log.h"

namespace OHOS {
namespace Ace {
namespace Napi {
namespace {
constexpr char DRAWABLE_DESCRIPTOR_NAME[] = "DrawableDescriptor";
constexpr char LAYERED_DRAWABLE_DESCRIPTOR_NAME[] = "LayeredDrawableDescriptor";
constexpr char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[] = "AnimatedDrawableDescriptor";
constexpr char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[] = "PixelMapDrawableDescriptor";
constexpr int32_t PARAMS_NUM_ONE = 1;
constexpr int32_t PARAMS_NUM_THREE = 3;
constexpr int32_t FOREGROUND_INDEX = 0;
constexpr int32_t BACKGROUND_INDEX = 1;
constexpr int32_t MASK_INDEX = 2;

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

bool GetPixelMapArray(napi_env env, napi_value arg, std::vector<std::shared_ptr<Media::PixelMap>>& pixelMaps)
{
    bool isArray = false;
    uint32_t length = 0;
    napi_is_array(env, arg, &isArray);
    if (!isArray) {
        return false;
    }
    napi_get_array_length(env, arg, &length);
    if (length < 1) {
        return false;
    }
    for (uint32_t i = 0; i < length; i++) {
        napi_value pixelMapValue = nullptr;
        napi_get_element(env, arg, i, &pixelMapValue);
        if (pixelMapValue == nullptr) {
            continue;
        }
        auto pixelmap = Media::PixelMapNapi::GetPixelMap(env, pixelMapValue);
        if (pixelmap == nullptr) {
            continue;
        }
        pixelMaps.push_back(pixelmap);
    }
    return !pixelMaps.empty();
}

napi_value CreateString(napi_env env, const std::string& str)
{
    napi_value value = nullptr;
    if (napi_create_string_utf8(env, str.c_str(), str.size(), &value) != napi_ok) {
        return nullptr;
    }
    return value;
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

napi_value JsDrawableDescriptor::Export(napi_env env, napi_value exports)
{
    // export base class
    napi_value cons = InitDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, DRAWABLE_DESCRIPTOR_NAME, cons));
    cons = InitPixelMapDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, PIXELMAP_DRAWABLE_DESCRIPTOR_NAME, cons));
    // export child class
    cons = InitLayeredDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, LAYERED_DRAWABLE_DESCRIPTOR_NAME, cons));
    // export child class
    cons = InitAnimatedDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, ANIMATED_DRAWABLE_DESCRIPTOR_NAME, cons));
    return exports;
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
    auto* drawable = reinterpret_cast<DrawableDescriptor*>(native);
    if (!drawable) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto pixmap = drawable->GetPixelMap();

    napi_value result = Media::PixelMapNapi::CreatePixelMap(env, pixmap);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

napi_value JsDrawableDescriptor::GetOriginalWidth(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::GetOriginalHeight(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::Fetch(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::FetchSync(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::IsRunning(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::Start(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value JsDrawableDescriptor::Stop(napi_env env, napi_callback_info info)
{
    return nullptr;
}

void JsDrawableDescriptor::Destructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    auto* field = reinterpret_cast<DrawableDescriptor*>(nativeObject);
    delete field;
}

void JsDrawableDescriptor::NewDestructor(napi_env /* env */, void* nativeObject, void* /* finalize */) {}

napi_value JsDrawableDescriptor::AnimatedConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);

    size_t argc = 2;
    napi_value argv[2] = { nullptr };
    napi_value thisVar = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    if (status != napi_ok) {
        GET_AND_THROW_LAST_ERROR((env));
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    if (argc < 1) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    if (!GetPixelMapArray(env, argv[0], pixelMaps)) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    // napi_get_named_property
    napi_value napiDuration;
    napi_value napiIterations;
    int32_t duration = -1;
    int32_t iterations = 1;
    if (argc > 1 && argv[1]) {
        napi_get_named_property(env, argv[1], "duration", &napiDuration);
        napi_get_named_property(env, argv[1], "iterations", &napiIterations);
        napi_get_value_int32(env, napiDuration, &duration);
        napi_get_value_int32(env, napiIterations, &iterations);
    }
    // create JsDrawable
    auto* animatedDrawable = new AnimatedDrawableDescriptor(pixelMaps, duration, iterations);
    // wrap to napi_value
    auto napi_status = napi_wrap(env, thisVar, animatedDrawable, Destructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete animatedDrawable;
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
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
    napi_value typeName = CreateString(env, std::string("DrawableDescriptor"));
    napi_property_descriptor baseDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
    NAPI_CALL(env, napi_define_class(env, DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, DrawableConstructor, nullptr,
                       sizeof(baseDes) / sizeof(napi_property_descriptor), baseDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &baseConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitPixelMapDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string("PixelMapDrawableDescriptor"));
    napi_property_descriptor pixelDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
    NAPI_CALL(env, napi_define_class(env, PIXELMAP_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, PixelMapConstructor,
                       nullptr, sizeof(pixelDes) / sizeof(napi_property_descriptor), pixelDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &pixelMapConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitLayeredDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string("LayeredDrawableDescriptor"));
    napi_property_descriptor layeredDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_FUNCTION("getForeground", GetForeground),
        DECLARE_NAPI_FUNCTION("getBackground", GetBackground),
        DECLARE_NAPI_FUNCTION("getMask", GetMask),
        DECLARE_NAPI_STATIC_FUNCTION("getMaskClipPath", GetMaskClipPath),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
    NAPI_CALL(env, napi_define_class(env, LAYERED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, LayeredConstructor,
                       nullptr, sizeof(layeredDes) / sizeof(napi_property_descriptor), layeredDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &layeredConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitAnimatedDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_value typeName = CreateString(env, std::string("AnimatedDrawableDescriptor"));
    napi_property_descriptor animatedDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_FUNCTION("isRunning", IsRunning),
        DECLARE_NAPI_FUNCTION("start", Start),
        DECLARE_NAPI_FUNCTION("stop", Stop),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
    NAPI_CALL(env, napi_define_class(env, ANIMATED_DRAWABLE_DESCRIPTOR_NAME, NAPI_AUTO_LENGTH, AnimatedConstructor,
                       nullptr, sizeof(animatedDes) / sizeof(napi_property_descriptor), animatedDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &animatedConstructor_));
    return cons;
}
} // namespace Napi
} // namespace Ace
} // namespace OHOS
