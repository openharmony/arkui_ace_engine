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

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "core/components/common/properties/ui_material.h"

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
const char STYLE_NAME[] = "style";
const char MATERIAL_COLOR_NAME[] = "materialColor";
const char COLOR_INVERT_NAME[] = "colorInvert";
const char APPLY_SHADOW_NAME[] = "applyShadow";
struct JsEnumInt {
    std::string_view enumName;
    int32_t enumInt;
};

napi_status EnumInit(napi_env env, napi_value exports, const char* name, const std::vector<JsEnumInt>& enumStructs)
{
    auto vecSize = enumStructs.size();
    std::vector<napi_value> value(vecSize);
    std::vector<napi_property_descriptor> property(vecSize);
    for (size_t index = 0; index < vecSize; ++index) {
        napi_create_int32(env, enumStructs[index].enumInt, &value[index]);
        property[index] =
            napi_property_descriptor DECLARE_NAPI_STATIC_PROPERTY(enumStructs[index].enumName.data(), value[index]);
    }

    auto napiConstructor = [](napi_env env, napi_callback_info info) {
        napi_value jsThis = nullptr;
        napi_get_cb_info(env, info, nullptr, nullptr, &jsThis, nullptr);
        return jsThis;
    };

    napi_value result = nullptr;
    napi_status napiStatus = napi_define_class(
        env, name, NAPI_AUTO_LENGTH, napiConstructor, nullptr, property.size(), property.data(), &result);
    if (napiStatus != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial Failed to define enum %{public}s", name);
        return napiStatus;
    }

    napiStatus = napi_set_named_property(env, exports, name, result);
    if (napiStatus != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial Failed to set %{public}s result", name);
        return napiStatus;
    }
    return napi_ok;
}
} // namespace

UiMaterial* UiMaterialNapi::WrapMaterialObject(napi_env env, napi_value jsThis, int32_t materialType)
{
    UiMaterial* uiMaterial = new (std::nothrow) UiMaterial();
    if (!uiMaterial) {
        napi_throw_error(env, nullptr, "Failed to allocate memory for UiMaterial.");
        return nullptr;
    }
    uiMaterial->SetType(materialType);
    napi_status status =
        napi_wrap_s(env, jsThis, uiMaterial, UiMaterialNapi::Destructor, nullptr, &UI_MATERIAL_TYPE_TAG, nullptr);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "wrap MaterialObject failed");
        delete uiMaterial;
        return nullptr;
    }
    uiMaterial->IncRefCount();
    return uiMaterial;
}

UiMaterial* UiMaterialNapi::WrapImmersiveMaterialObject(
    napi_env env, napi_value jsThis, const ImmersiveOptions& options)
{
    auto material = WrapMaterialObject(env, jsThis, static_cast<int32_t>(MaterialType::IMMERSIVE));
    if (material) {
        material->SetImmersiveOptions(options);
    }
    return material;
}

ImmersiveOptions UiMaterialNapi::ParseImmersiveOptions(napi_env env, napi_value value)
{
    ImmersiveOptions options {};
    if (GetValueType(env, value) != napi_object) {
        return options;
    }
    napi_value napiStyleParam = GetNamedProperty(env, value, STYLE_NAME);
    if (GetValueType(env, napiStyleParam) == napi_number) {
        int32_t style = GetCInt32(napiStyleParam, env);
        if (style >= static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN) &&
            style <= static_cast<int32_t>(UiMaterialStyle::MAX)) {
            options.style = static_cast<UiMaterialStyle>(style);
        }
    }
    napi_value napiColorInvertParam = GetNamedProperty(env, value, COLOR_INVERT_NAME);
    if (GetValueType(env, napiColorInvertParam) == napi_boolean) {
        bool colorInvert = false;
        napi_get_value_bool(env, napiColorInvertParam, &colorInvert);
        options.colorInvert = colorInvert;
    }
    napi_value napiMaterialColorParam = GetNamedProperty(env, value, MATERIAL_COLOR_NAME);
    Color materialColor;
    RefPtr<ResourceObject> colorResObj;
    if (ParseNapiColor(env, napiMaterialColorParam, materialColor, colorResObj)) {
        options.materialColor = materialColor;
        options.colorResObj = colorResObj;
    }
    napi_value napiApplyShadowParam = GetNamedProperty(env, value, APPLY_SHADOW_NAME);
    if (GetValueType(env, napiApplyShadowParam) == napi_boolean) {
        bool applyShadow = false;
        napi_get_value_bool(env, napiApplyShadowParam, &applyShadow);
        options.applyShadow = applyShadow;
    }
    return options;
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

napi_value UiMaterialNapi::MaterialConstructor(napi_env env, napi_callback_info info)
{
    static constexpr int32_t ARG_COUNT_1 = 1;
    size_t argCount = ARG_COUNT_1;
    napi_value argValue[ARG_COUNT_1] = { 0 };
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
    napi_value napiTypeParam = GetNamedProperty(env, argValue[0], TYPE_NAME);
    if (GetValueType(env, napiTypeParam) != napi_number) {
        WrapMaterialObject(env, jsThis, type);
        return jsThis;
    }
    type = GetCInt32(napiTypeParam, env);
    WrapMaterialObject(env, jsThis, type);
    return jsThis;
}

napi_value UiMaterialNapi::ImmersiveMaterialConstructor(napi_env env, napi_callback_info info)
{
    static constexpr int32_t ARG_COUNT_1 = 1;
    size_t argCount = ARG_COUNT_1;
    napi_value argValue[ARG_COUNT_1] = { 0 };
    napi_value jsThis = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argCount, argValue, &jsThis, nullptr);
    ImmersiveOptions options {};
    if (status != napi_ok || argCount < ARG_COUNT_1) {
        WrapImmersiveMaterialObject(env, jsThis, options);
        return jsThis;
    }
    options = ParseImmersiveOptions(env, argValue[0]);
    WrapImmersiveMaterialObject(env, jsThis, options);
    return jsThis;
}

napi_value UiMaterialNapi::JSGetImmersiveLevel(napi_env env, napi_callback_info info)
{
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    napi_value result = nullptr;
    NAPI_CALL(env, napi_create_int32(env, static_cast<int32_t>(materialLevel), &result));
    return result;
}

napi_value UiMaterialNapi::JSGetMaterialInfo(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_create_object(env, &result);
    auto state = MaterialUtils::GetConfiguredMaterialState();
    napi_value napiState = nullptr;
    napi_create_int32(env, static_cast<int32_t>(state), &napiState);
    napi_set_named_property(env, result, "state", napiState);
    auto type = MaterialUtils::GetConfiguredMaterialType();
    napi_value napiType = nullptr;
    napi_create_int32(env, static_cast<int32_t>(type), &napiType);
    napi_set_named_property(env, result, "type", napiType);
    return result;
}

napi_value UiMaterialNapi::JSGetEmpty(napi_env env, napi_callback_info info)
{
    napi_value constructor = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, &constructor, nullptr);
    napi_value result = nullptr;
    napi_new_instance(env, constructor, 0, nullptr, &result);
    UiMaterial* nativeMaterial = nullptr;
    napi_status status =
        napi_unwrap_s(env, result, &UI_MATERIAL_TYPE_TAG, reinterpret_cast<void**>(&nativeMaterial));
    if (status == napi_ok && nativeMaterial) {
        nativeMaterial->SetEmpty(true);
    }
    return result;
}

void UiMaterialNapi::Destructor(napi_env env, void* nativeObject, void* finalize)
{
    UiMaterial* uiMaterial = reinterpret_cast<UiMaterial*>(nativeObject);
    if (uiMaterial) {
        uiMaterial->DecRefCount();
    }
}

napi_status UiMaterialNapi::EnumMaterialTypeInit(napi_env env, napi_value exports)
{
    const char* enumClassName = "MaterialType";
    const std::vector<struct JsEnumInt> enumStructs = {
        { "NONE", 0 },
        { "SEMI_TRANSPARENT", 1 },
        { "IMMERSIVE", 2 },
    };
    return EnumInit(env, exports, enumClassName, enumStructs);
}

napi_status UiMaterialNapi::EnumImmersiveStyleInit(napi_env env, napi_value exports)
{
    const char* enumClassName = "ImmersiveStyle";
    const std::vector<struct JsEnumInt> enumStructs = {
        { "ULTRA_THIN", static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN) },
        { "THIN", static_cast<int32_t>(UiMaterialStyle::THIN) },
        { "REGULAR", static_cast<int32_t>(UiMaterialStyle::REGULAR) },
        { "THICK", static_cast<int32_t>(UiMaterialStyle::THICK) },
        { "ULTRA_THICK", static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK) },
    };
    return EnumInit(env, exports, enumClassName, enumStructs);
}

napi_status UiMaterialNapi::EnumImmersiveLevelInit(napi_env env, napi_value exports)
{
    const char* enumClassName = "MaterialLevel";
    const std::vector<struct JsEnumInt> enumStructs = {
        { "EXQUISITE", static_cast<int32_t>(UiMaterialLevel::EXQUISITE) },
        { "GENTLE", static_cast<int32_t>(UiMaterialLevel::GENTLE) },
        { "SMOOTH", static_cast<int32_t>(UiMaterialLevel::SMOOTH) },
    };
    return EnumInit(env, exports, enumClassName, enumStructs);
}

napi_status UiMaterialNapi::EnumMaterialStateInit(napi_env env, napi_value exports)
{
    const char* enumClassName = "MaterialState";
    const std::vector<struct JsEnumInt> enumStructs = {
        { "DEFAULT", 0 },
        { "ENABLE", 1 },
        { "DISABLE", 2 },
    };
    return EnumInit(env, exports, enumClassName, enumStructs);
}

napi_status UiMaterialNapi::ImmersiveMaterialInit(napi_env env, napi_value exports, napi_value baseCtr)
{
    napi_property_descriptor static_prop[] = {};
    napi_value constructor = nullptr;
    napi_status status = napi_define_class(env, "ImmersiveMaterial", NAPI_AUTO_LENGTH, ImmersiveMaterialConstructor,
        nullptr, 0, static_prop, &constructor);
    if (status != napi_ok) {
        return status;
    }
    napi_value basePrototype = nullptr;
    status = napi_get_named_property(env, baseCtr, "prototype", &basePrototype);
    if (status != napi_ok) {
        return status;
    }
    napi_value prototype = nullptr;
    status = napi_get_named_property(env, constructor, "prototype", &prototype);
    if (status != napi_ok) {
        return status;
    }
    status = napi_set_named_property(env, prototype, "__proto__", basePrototype);
    if (status != napi_ok) {
        return status;
    }
    status = napi_set_named_property(env, exports, "ImmersiveMaterial", constructor);
    return status;
}

napi_value UiMaterialNapi::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor static_prop[] = {
        { "empty", nullptr, nullptr, JSGetEmpty, nullptr, nullptr, napi_static, nullptr },
    };
    napi_value constructor = nullptr;
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("getGlobalMaterialLevel", JSGetImmersiveLevel),
        DECLARE_NAPI_FUNCTION("getMaterialInfo", JSGetMaterialInfo),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    napi_status status = napi_define_class(
        env, "Material", NAPI_AUTO_LENGTH, MaterialConstructor, nullptr,
        sizeof(static_prop) / sizeof(static_prop[0]), static_prop, &constructor);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial define class failed, %{public}d", status);
        return nullptr;
    }
    napi_value basePrototype = nullptr;
    status = napi_get_named_property(env, constructor, "prototype", &basePrototype);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial get prototype failed, %{public}d", status);
        return nullptr;
    }
    napi_value trueNapiValue = nullptr;
    napi_get_boolean(env, true, &trueNapiValue);
    status = napi_set_named_property(env, basePrototype, "__MATERIAL_REFERENCE__", trueNapiValue);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_VISUAL_EFFECT, "UIMaterial set __MATERIAL_REFERENCE__ property failed, %{public}d", status);
        return nullptr;
    }
    NAPI_CALL(env, napi_set_named_property(env, exports, "Material", constructor));
    NAPI_CALL(env, EnumMaterialTypeInit(env, exports));
    NAPI_CALL(env, EnumImmersiveStyleInit(env, exports));
    NAPI_CALL(env, EnumImmersiveLevelInit(env, exports));
    NAPI_CALL(env, EnumMaterialStateInit(env, exports));
    NAPI_CALL(env, ImmersiveMaterialInit(env, exports, constructor));
    return exports;
}

extern "C" __attribute__((constructor)) void UiMaterialRegister()
{
    napi_module_register(&ui_material_module);
}
} // namespace OHOS::Ace::Napi
