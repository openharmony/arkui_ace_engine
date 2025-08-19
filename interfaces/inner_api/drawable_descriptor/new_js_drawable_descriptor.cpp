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

#include "new_js_drawable_descriptor.h"

#ifdef OHOS_PLATFORM
#include <dlfcn.h>
#endif
#include <memory>

#ifndef PREVIEW
#include "pixel_map_napi.h"
#else
#include "image_source_preview.h"
#endif
#include "resource_manager.h"

#include "base/log.h"
#include "base/resource.h"
#include "base/source_info.h"
#include "core/drawable_descriptor_base.h"
#include "core/pixelmap_drawable_descriptor.h"
#include "utils/napi_utils.h"

namespace OHOS {
namespace Ace {
namespace Napi {
namespace {
constexpr char DRAWABLE_DESCRIPTOR_NAME[] = "DrawableDescriptor";
constexpr char LAYERED_DRAWABLE_DESCRIPTOR_NAME[] = "LayeredDrawableDescriptor";
constexpr char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[] = "AnimatedDrawableDescriptor";
constexpr char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[] = "PixelMapDrawableDescriptor";
#ifdef OHOS_PLATFORM
constexpr char DRAWBLE_GET_DRAWBLE_TYPE[] = "OHOS_ACE_DrawableDescriptor_GetDrawableType";
constexpr char DRAWBLE_GET_PIXEL_MAP[] = "OHOS_ACE_DrawableDescriptor_GetPixelMap";
constexpr char LAYER_GET_FOREGROUND[] = "OHOS_ACE_LayeredDrawableDescriptor_GetForeground";
constexpr char LAYER_GET_BACKGROUND[] = "OHOS_ACE_LayeredDrawableDescriptor_GetBackground";
constexpr char LAYER_GET_MASK[] = "OHOS_ACE_LayeredDrawableDescriptor_GetMask";
constexpr char ANIMATED_GET_PARAMS[] = "OHOS_ACE_AnimatedDrawableDescriptor_GetParams";
constexpr char PIXEL_MAP_GET_PIXEL_MAP[] = "OHOS_ACE_PixelMapDrawableDescriptor_GetPixelMap";
constexpr char LIBACE_MODULE[] = "libace_compatible.z.so";

using DrawableGetDrawableTypeFunc = void (*)(void*, size_t*);
using DrawableGetPixelMapFunc = void (*)(void*, std::shared_ptr<OHOS::Media::PixelMap>&);
using LayeredGetForegroundFunc = void (*)(void*, std::shared_ptr<OHOS::Media::PixelMap>&);
using LayeredGetBackgroundFunc = void (*)(void*, std::shared_ptr<OHOS::Media::PixelMap>&);
using LayeredGetMaskFunc = void (*)(void*, std::shared_ptr<OHOS::Media::PixelMap>&);
using PixelMapGetPixelMapFunc = void (*)(void*, std::shared_ptr<OHOS::Media::PixelMap>&);
using AnimatedGetParamsFunc = void (*)(
    void* object, std::vector<std::shared_ptr<OHOS::Media::PixelMap>>&, size_t*, size_t*);
#endif
constexpr size_t ESTIMATE_DRAWABLE_SIZE = 10 * 1024 * 1024;
constexpr int32_t PARAMS_NUM_TWO = 2;
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
        OHOS::Media::PixelMapNapi* pixmapNapi = nullptr;
        napi_unwrap(env, pixelMapValue, reinterpret_cast<void**>(&pixmapNapi));
        if (pixmapNapi == nullptr) {
            continue;
        }
        auto* pixelmap = pixmapNapi->GetPixelMap();
        if (pixelmap == nullptr) {
            continue;
        }
        pixelMaps.push_back(*(pixelmap));
    }
    return !pixelMaps.empty();
}

std::shared_ptr<Media::PixelMap> GetPixelMapFromJsPixelMap(napi_env env, napi_value value)
{
    OHOS::Media::PixelMapNapi* pixelMapNapi = nullptr;
    napi_unwrap(env, value, reinterpret_cast<void**>(&pixelMapNapi));
    if (pixelMapNapi == nullptr) {
        HILOGW("Failed to unwrap napi pixel map from js pixel map");
        return nullptr;
    }
    auto pixelMap = *(pixelMapNapi->GetPixelMap());
    if (pixelMap == nullptr) {
        HILOGW("Native pixel map is nullptr");
        return nullptr;
    }
    return pixelMap;
}

std::shared_ptr<Media::PixelMap> GetPixelMapFromJsDrawable(napi_env env, napi_value value)
{
    OHOS::Ace::Drawable::DrawableDescriptor* drawable = nullptr;
    napi_unwrap(env, value, reinterpret_cast<void**>(&drawable));
    if (drawable == nullptr) {
        HILOGW("Failed to unwrap native drawable from js drawable");
        return nullptr;
    }
    auto pixelMap = drawable->GetPixelMap();
    if (pixelMap == nullptr) {
        HILOGW("Failed to get pixel map from drawable");
        return nullptr;
    }
    return pixelMap;
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
    if (!baseConstructor_ || !layeredConstructor_ || !animatedConstructor_ || !pixelMapConstructor_) {
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
        case DrawableDescriptor::DrawableType::ANIMATED:
            status = napi_get_reference_value(env, animatedConstructor_, &constructor);
            break;
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

size_t JsDrawableDescriptor::DrawableGetDrawableTypeC(void* drawable)
{
    size_t drawableType = 0;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    if (handle == nullptr) {
        return 0;
    }
    auto entry = reinterpret_cast<DrawableGetDrawableTypeFunc>(dlsym(handle, DRAWBLE_GET_DRAWBLE_TYPE));
    if (entry == nullptr) {
        dlclose(handle);
        return 0;
    }
    entry(drawable, &drawableType);
#endif
    return drawableType;
}

std::shared_ptr<OHOS::Media::PixelMap> JsDrawableDescriptor::DrawableGetPixelMapC(void* drawable)
{
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    if (handle == nullptr) {
        return nullptr;
    }
    auto entry = reinterpret_cast<DrawableGetPixelMapFunc>(dlsym(handle, DRAWBLE_GET_PIXEL_MAP));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }
    entry(drawable, pixelMap);
#endif
    return pixelMap;
}

std::shared_ptr<OHOS::Media::PixelMap> JsDrawableDescriptor::LayeredGetForegroundC(void* drawable)
{
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    CHECK_NULL_RETURN(handle, nullptr);
    auto entry = reinterpret_cast<LayeredGetForegroundFunc>(dlsym(handle, LAYER_GET_FOREGROUND));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }
    entry(drawable, pixelMap);
#endif
    return pixelMap;
}

std::shared_ptr<OHOS::Media::PixelMap> JsDrawableDescriptor::LayeredGetBackgroundC(void* drawable)
{
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    CHECK_NULL_RETURN(handle, nullptr);
    auto entry = reinterpret_cast<LayeredGetBackgroundFunc>(dlsym(handle, LAYER_GET_BACKGROUND));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }
    entry(drawable, pixelMap);
#endif
    return pixelMap;
}

std::shared_ptr<OHOS::Media::PixelMap> JsDrawableDescriptor::LayeredGetMaskC(void* drawable)
{
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    CHECK_NULL_RETURN(handle, nullptr);
    auto entry = reinterpret_cast<LayeredGetMaskFunc>(dlsym(handle, LAYER_GET_MASK));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }
    entry(drawable, pixelMap);
#endif
    return pixelMap;
}

void JsDrawableDescriptor::AnimatedGetParamsC(void* drawable,
    std::vector<std::shared_ptr<OHOS::Media::PixelMap>>& pixelMapVec, size_t* duration, size_t* iterations)
{
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    CHECK_NULL_VOID(handle);
    auto entry = reinterpret_cast<AnimatedGetParamsFunc>(dlsym(handle, ANIMATED_GET_PARAMS));
    if (entry == nullptr) {
        dlclose(handle);
        return;
    }
    entry(drawable, pixelMapVec, duration, iterations);
#endif
}

std::shared_ptr<OHOS::Media::PixelMap> JsDrawableDescriptor::PixelMapGetPixelMapC(void* drawable)
{
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap;
#ifdef OHOS_PLATFORM
    void* handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
    if (handle == nullptr) {
        return nullptr;
    }
    auto entry = reinterpret_cast<PixelMapGetPixelMapFunc>(dlsym(handle, PIXEL_MAP_GET_PIXEL_MAP));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }
    entry(drawable, pixelMap);
#endif
    return pixelMap;
}

napi_value JsDrawableDescriptor::CreatDrawable(napi_env env, void* native)
{
    if (native == nullptr) {
        return nullptr;
    }
    napi_value cons = nullptr;
    napi_create_object(env, &cons);
    auto* drawable = new Drawable::DrawableDescriptor;
    auto napi_status = napi_wrap(env, cons, drawable, Destructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete drawable;
        return nullptr;
    }
    auto pixelMap = DrawableGetPixelMapC(native);
    drawable->SetPixelMap(pixelMap);
    auto baseDes = GetBaseDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, baseDes.size(), baseDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreatLayeredDrawable(napi_env env, void* native)
{
    if (native == nullptr) {
        return nullptr;
    }
    napi_value cons = nullptr;
    napi_create_object(env, &cons);
    auto* layerDrawable = new LayeredDrawableDescriptor;
    auto napi_status = napi_wrap(env, cons, layerDrawable, OldDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete layerDrawable;
        return nullptr;
    }

    auto pixelForeground = LayeredGetForegroundC(native);
    auto pixelBackground = LayeredGetBackgroundC(native);
    auto pixelMask = LayeredGetMaskC(native);
    layerDrawable->SetForeground(pixelForeground);
    layerDrawable->SetBackground(pixelBackground);
    layerDrawable->SetMask(pixelMask);
    auto layeredDes = GetLayeredDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, layeredDes.size(), layeredDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreatAnimatedDrawable(napi_env env, void* native)
{
    if (native == nullptr) {
        return nullptr;
    }
    napi_value cons = nullptr;
    napi_create_object(env, &cons);

    std::vector<std::shared_ptr<OHOS::Media::PixelMap>> pixelMapVec;
    size_t duration = -1;
    size_t iterations = -1;

    AnimatedGetParamsC(native, pixelMapVec, &duration, &iterations);
    auto* animatedDrawable = new AnimatedDrawableDescriptor(pixelMapVec, duration, iterations);
    auto napi_status = napi_wrap(env, cons, animatedDrawable, OldDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete animatedDrawable;
        return nullptr;
    }

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
    napi_create_object(env, &cons);
    auto* drawable = new Drawable::PixelmapDrawableDescriptor;
    auto napi_status = napi_wrap(env, cons, drawable, Destructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete drawable;
        return nullptr;
    }
    auto pixelMap = PixelMapGetPixelMapC(native);
    drawable->SetPixelMap(pixelMap);
    Drawable::SourceInfo sourceInfo;
    sourceInfo.SetSrcType(Drawable::SrcType::PIXMAP);
    drawable->SetSourceInfo(sourceInfo);
    auto pixelDes = GetPixelMapDrawableDescriptor(env);
    NAPI_CALL(env, napi_define_properties(env, cons, pixelDes.size(), pixelDes.data()));
    return cons;
}

napi_value JsDrawableDescriptor::CreateDrawableDescriptorTransfer(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv;
    napi_get_cb_info(env, info, &argc, &argv, NULL, NULL);
    if (argc != 1) {
        return nullptr;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType != napi_number) {
        return nullptr;
    }
    int64_t addr = 0;
    napi_get_value_int64(env, argv, &addr);
    auto* drawable = reinterpret_cast<void*>(addr);
    auto drawableType = DrawableGetDrawableTypeC(drawable);
    auto type = DrawableDescriptor::DrawableType(drawableType);
    napi_value cons = nullptr;
    switch (type) {
        case DrawableDescriptor::DrawableType::BASE: {
            cons = CreatDrawable(env, drawable);
            break;
        }
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

    napi_property_descriptor createTransferDesc[] = { DECLARE_NAPI_FUNCTION(
        "__createTransfer__", CreateDrawableDescriptorTransfer) };
    NAPI_CALL(env, napi_define_properties(
        env, exports, sizeof(createTransferDesc) / sizeof(createTransferDesc[0]), createTransferDesc));
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
    napi_value result = ToNapi(env, foreground.release(), DrawableDescriptor::DrawableType::BASE);
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
    napi_value result = ToNapi(env, background.release(), DrawableDescriptor::DrawableType::BASE);
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
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto* drawable = reinterpret_cast<DrawableDescriptor*>(native);
    if (drawable == nullptr) {
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
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto* drawable = reinterpret_cast<Drawable::DrawableDescriptor*>(native);
    if (drawable) {
        drawable->Fetch();
    }
    return nullptr;
}

napi_value JsDrawableDescriptor::FetchSync(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    void* native = nullptr;
    napi_unwrap(env, thisVar, &native);
    auto* drawable = reinterpret_cast<Drawable::DrawableDescriptor*>(native);
    if (drawable) {
        drawable->FetchSync();
    }
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
    auto* field = reinterpret_cast<Drawable::DrawableDescriptor*>(nativeObject);
    delete field;
}

void JsDrawableDescriptor::OldDestructor(napi_env /* env */, void* nativeObject, void* /* finalize */)
{
    auto* field = reinterpret_cast<DrawableDescriptor*>(nativeObject);
    delete field;
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
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps;
    if (!GetPixelMapArray(env, argv[0], pixelMaps)) {
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
    auto napi_status = napi_wrap(env, thisVar, animatedDrawable, OldDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete animatedDrawable;
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
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    auto pos = -1;
    auto* layeredDrawable = new LayeredDrawableDescriptor;
    if (argc == 0) {
        auto napi_status = napi_wrap(env, thisVar, layeredDrawable, OldDestructor, nullptr, nullptr);
        if (napi_status != napi_ok) {
            delete layeredDrawable;
            return thisVar;
        }
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
        auto pixelMap = GetPixelMapFromJsDrawable(env, arg);
        if (!pixelMap) {
            updateUndefinedPixelMap();
        } else {
            UpdateLayeredParam(layeredDrawable, pos, pixelMap);
            if (pos == FOREGROUND_INDEX)
                foregroundPixelMap = std::move(pixelMap);
        }
    }
    auto napi_status = napi_wrap(env, thisVar, layeredDrawable, OldDestructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete layeredDrawable;
        return thisVar;
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
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    // create JsDrawable
    auto* drawable = new Drawable::DrawableDescriptor;
    // wrap to napi_value
    auto napi_status = napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
    if (napi_status != napi_ok) {
        delete drawable;
        return nullptr;
    }
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

napi_value JsDrawableDescriptor::PixelMapConstructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    size_t argc = PARAMS_NUM_TWO;
    napi_value argv[argc];
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr));
    auto* drawable = new Drawable::PixelmapDrawableDescriptor;
    if (argc == 0) {
        auto napi_status = napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
        if (napi_status != napi_ok) {
            delete drawable;
            return thisVar;
        }
        napi_escape_handle(env, scope, thisVar, &thisVar);
        napi_close_escapable_handle_scope(env, scope);
        return thisVar;
    }

    napi_value res = argv[0];
    napi_valuetype type = Drawable::NapiUtils::ParseJsType(env, res);

    Drawable::SourceInfo sourceInfo;
    if (type == napi_string) {
        auto src = Drawable::NapiUtils::ParseJsString(env, res);
        sourceInfo.SetSrc(src);
    }

    if (type == napi_object) {
        auto pixelMap = GetPixelMapFromJsPixelMap(env, res);
        if (pixelMap) {
            drawable->SetPixelMap(pixelMap);
            sourceInfo.SetSrcType(Drawable::SrcType::PIXMAP);
        } else {
            auto resource = Drawable::NapiUtils::ParseJsResource(env, res);
            sourceInfo.SetResource(resource);
            sourceInfo.SetSrcType(Drawable::SrcType::RESOURCE);
        }
    }

    drawable->SetSourceInfo(sourceInfo);
    if (argc == 2) {
        napi_value res = argv[1];
        napi_valuetype type = Drawable::NapiUtils::ParseJsType(env, res);
        if (type == napi_object) {
            napi_value jsFetchSync = Drawable::NapiUtils::GetNamedProperty(env, res, "fetchWhenConstructingWithUri");
            auto fetchSync = Drawable::NapiUtils::ParseJsBool(env, jsFetchSync);
            if (fetchSync) {
                drawable->FetchSync();
            }
        }
    }
    // wrap to napi_value
    auto napi_status =
        napi_wrap_with_size(env, thisVar, drawable, Destructor, nullptr, nullptr, ESTIMATE_DRAWABLE_SIZE);
    if (napi_status != napi_ok) {
        delete drawable;
        return thisVar;
    }
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetBaseDrawableDescriptor(napi_env env)
{
    napi_value typeName = Drawable::NapiUtils::CreateString(env, "DrawableDescriptor");
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetPixelMapDrawableDescriptor(napi_env env)
{
    napi_value typeName = Drawable::NapiUtils::CreateString(env, "PixelMapDrawableDescriptor");
    return {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getOriginalWidth", GetOriginalWidth),
        DECLARE_NAPI_FUNCTION("getOriginalHeight", GetOriginalHeight),
        DECLARE_NAPI_FUNCTION("fetch", Fetch),
        DECLARE_NAPI_FUNCTION("fetchSync", FetchSync),
        DECLARE_NAPI_PROPERTY("typeName", typeName)
    };
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetLayeredDrawableDescriptor(napi_env env)
{
    napi_value typeName = Drawable::NapiUtils::CreateString(env, "LayeredDrawableDescriptor");
    return {
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
}

std::vector<napi_property_descriptor> JsDrawableDescriptor::GetAnimatedDrawableDescriptor(napi_env env)
{
    napi_value typeName = Drawable::NapiUtils::CreateString(env, "AnimatedDrawableDescriptor");
    return {
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
} // namespace Napi
} // namespace Ace
} // namespace OHOS
