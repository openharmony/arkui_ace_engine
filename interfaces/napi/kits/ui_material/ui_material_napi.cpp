/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "interfaces/napi/kits/ui_material/ui_material_napi.h"

#include "ui/properties/ui_material.h"

namespace OHOS::Ace::Napi {

namespace {
napi_module ui_material_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = UiMaterialNapi::Init,
    .nm_modname = "arkui.uiMaterial",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};
const std::string TYPE_NAME = "type";
struct JsEnumInt {
    std::string_view enumName;
    int32_t enumInt;
};
const std::vector<struct JsEnumInt> g_materialTypes = {
    { "NONE", 0 },
    { "SEMI_TRANSPARENT", 1 },
};
} // namespace

void UiMaterialNapi::WrapMaterialObject(napi_env env, napi_value jsThis, int32_t materialType)
{
    UiMaterial* uiMaterial = new(std::nothrow) UiMaterial();
    uiMaterial->SetType(materialType);
    napi_status status = napi_wrap(env, jsThis, uiMaterial, UiMaterialNapi::Destructor, nullptr, nullptr);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "wrap MaterialObject failed");
        delete uiMaterial;
        return;
    }
    uiMaterial->IncRefCount();
}

napi_valuetype UiMaterialNapi::GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }
 
    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}
 
napi_value UiMaterialNapi::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        return nullptr;
    }

    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

int32_t UiMaterialNapi::GetCInt32(napi_value value, napi_env env)
{
    int32_t num = 0;
    napi_get_value_int32(env, value, &num);
    return num;
}

napi_value UiMaterialNapi::Constructor(napi_env env, napi_callback_info info)
{
    static constexpr int32_t ARG_COUNT_1 = 1;
    size_t argCount = ARG_COUNT_1;
    napi_value argValue[ARG_COUNT_1] = {0};
    napi_value jsThis = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argCount, argValue, &jsThis, nullptr);
    int32_t type = 0; // NONE
    if (status != napi_ok || argCount < ARG_COUNT_1) {
        WrapMaterialObject(env, jsThis, type);
        return jsThis;
    }
    if (GetValueType(env, argValue[0]) != napi_object) {
        WrapMaterialObject(env, jsThis, type);
        return jsThis;
    }
    napi_value napiType = GetNamedProperty(env, argValue[0], TYPE_NAME);
    if (GetValueType(env, napiType) != napi_number) {
        WrapMaterialObject(env, jsThis, type);
        return jsThis;
    }
    type = GetCInt32(napiType, env);
    WrapMaterialObject(env, jsThis, type);
    return jsThis;
}

void UiMaterialNapi::Destructor(napi_env env, void* nativeObject, void* finalize)
{
    UiMaterial *uiMaterial = reinterpret_cast<UiMaterial*>(nativeObject);
    if (uiMaterial) {
        uiMaterial->DecRefCount();
    }
}

napi_value UiMaterialNapi::JsEnumIntInit(napi_env env, napi_value exports)
{
    const char* enumClassName = "MaterialType";
    auto vecSize = g_materialTypes.size();
    std::vector<napi_value> value(vecSize);
    std::vector<napi_property_descriptor> property(vecSize);
    for (size_t index = 0; index < vecSize; ++index) {
        napi_create_int32(env, g_materialTypes[index].enumInt, &value[index]);
        property[index] = napi_property_descriptor DECLARE_NAPI_STATIC_PROPERTY(
            g_materialTypes[index].enumName.data(), value[index]);
    }
 
    auto napiConstructor = [](napi_env env, napi_callback_info info) {
        napi_value jsThis = nullptr;
        napi_get_cb_info(env, info, nullptr, nullptr, &jsThis, nullptr);
        return jsThis;
    };
 
    napi_value result = nullptr;
    napi_status napiStatus = napi_define_class(env, enumClassName, NAPI_AUTO_LENGTH, napiConstructor,
        nullptr, property.size(), property.data(), &result);
    if (napiStatus != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial Failed to define enum");
        return nullptr;
    }
 
    napiStatus = napi_set_named_property(env, exports, enumClassName, result);
    if (napiStatus != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial Failed to set result");
        return nullptr;
    }
    return exports;
}

napi_value UiMaterialNapi::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor static_prop[] = {};
    napi_value constructor = nullptr;
    napi_status status =
        napi_define_class(env, "Material", NAPI_AUTO_LENGTH, Constructor, nullptr, 0, static_prop, &constructor);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial define class failed, %{public}d", status);
        return nullptr;
    }
    NAPI_CALL(env, napi_set_named_property(env, exports, "Material", constructor));
    JsEnumIntInit(env, exports);
    return exports;
}

extern "C" __attribute__((constructor)) void UiMaterialRegister()
{
    napi_module_register(&ui_material_module);
}
} // namespace OHOS::Ace::Napi
