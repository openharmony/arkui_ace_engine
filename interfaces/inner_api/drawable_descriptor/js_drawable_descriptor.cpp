/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "drawable_descriptor.h"
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#ifndef PREVIEW
#include "pixel_map_napi.h"
#endif
#include "base/utils/utils.h"

namespace {
constexpr char DRAWABLE_BASE[] = "DrawableDescriptor";
constexpr char DRAWABLE_LAYERED[] = "LayeredDrawableDescriptor";
} // namespace

namespace OHOS::Ace::Napi {
thread_local napi_ref JsDrawableDescriptor::baseConstructor_;
thread_local napi_ref JsDrawableDescriptor::layeredConstructor_;

napi_value JsDrawableDescriptor::Constructor(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    // create JsDrawable
    auto* drawable = new DrawableDescriptor;
    // wrap to napi_value
    napi_wrap(env, thisVar, drawable, Destructor, nullptr, nullptr);
    napi_escape_handle(env, scope, thisVar, &thisVar);
    napi_close_escapable_handle_scope(env, scope);
    return thisVar;
}

void JsDrawableDescriptor::Destructor(napi_env /* env */, void* data, void* /* hint */)
{
    auto* field = reinterpret_cast<DrawableDescriptor*>(data);
    delete field;
}

napi_value JsDrawableDescriptor::InitDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_property_descriptor baseDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
    };
    NAPI_CALL(env, napi_define_class(env, DRAWABLE_BASE, NAPI_AUTO_LENGTH, Constructor, nullptr,
                       sizeof(baseDes) / sizeof(napi_property_descriptor), baseDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &baseConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::InitLayeredDrawable(napi_env env)
{
    napi_value cons = nullptr;
    napi_property_descriptor layeredDes[] = {
        DECLARE_NAPI_FUNCTION("getPixelMap", GetPixelMap),
        DECLARE_NAPI_FUNCTION("getForeground", GetForeground),
        DECLARE_NAPI_FUNCTION("getBackground", GetBackground),
        DECLARE_NAPI_FUNCTION("getMask", GetMask),
        DECLARE_NAPI_STATIC_FUNCTION("getMaskClipPath", GetMaskClipPath),
    };
    NAPI_CALL(env, napi_define_class(env, DRAWABLE_LAYERED, NAPI_AUTO_LENGTH, Constructor, nullptr,
                       sizeof(layeredDes) / sizeof(napi_property_descriptor), layeredDes, &cons));
    NAPI_CALL(env, napi_create_reference(env, cons, 1, &layeredConstructor_));
    return cons;
}

napi_value JsDrawableDescriptor::ToNapi(
    napi_env env, DrawableDescriptor* drawable, DrawableDescriptor::DrawableType type)
{
    if (!drawable) {
        return nullptr;
    }
    if (!baseConstructor_ || !layeredConstructor_) {
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
        default:
            status = napi_status::napi_invalid_arg;
            break;
    }
    if (status == napi_status::napi_ok) {
        NAPI_CALL(env, napi_new_instance(env, constructor, 0, nullptr, &result));
        NAPI_CALL(env, napi_wrap(env, result, drawable, Destructor, nullptr, nullptr));
    } else {
        HILOG_INFO("create reference failed, drawable constructor is null");
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
    auto pixmap = drawable->GetPixelMap();

    napi_value result = Media::PixelMapNapi::CreatePixelMap(env, pixmap);
    napi_escape_handle(env, scope, result, &result);
    napi_close_escapable_handle_scope(env, scope);
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
        HILOG_INFO("JsDrawableDescriptor Failed");
    }
    return result;
}

napi_value JsDrawableDescriptor::Export(napi_env env, napi_value exports)
{
    // export base class
    napi_value cons = InitDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, DRAWABLE_BASE, cons));

    // export child class
    cons = InitLayeredDrawable(env);
    NAPI_CALL(env, napi_set_named_property(env, exports, DRAWABLE_LAYERED, cons));
    return exports;
}
} // namespace OHOS::Ace::Napi
