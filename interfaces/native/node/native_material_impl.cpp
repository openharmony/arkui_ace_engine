/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "native_material_impl.h"

#include "node_model.h"
#include "ui/base/utils/utils.h"

bool OH_ArkUI_NativeModule_GetSystemMaterialSupported()
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getNodeModifiers()->getMaterialModifier()->getDeviceSystemMaterialSupported();
}

ArkUI_MaterialLevel OH_ArkUI_NativeModule_GetGlobalMaterialLevel()
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto level = impl->getNodeModifiers()->getMaterialModifier()->getGlobalMaterialLevel();
    return static_cast<ArkUI_MaterialLevel>(level);
}

ArkUI_ImmersiveMaterialHandle OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ArkUI_ImmersiveStyle style)
{
    if (style < ARKUI_IMMERSIVE_STYLE_ULTRA_THIN || style > ARKUI_IMMERSIVE_STYLE_ULTRA_THICK) {
        return nullptr;
    }
    auto handle = new ArkUI_ImmersiveMaterial();
    handle->style = style;
    return handle;
}

void OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(ArkUI_ImmersiveMaterialHandle material)
{
    if (material) {
        delete material;
    }
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(ArkUI_ImmersiveMaterialHandle material,
    ArkUI_ImmersiveStyle style)
{
    CHECK_NULL_RETURN(material, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (style < ARKUI_IMMERSIVE_STYLE_ULTRA_THIN || style > ARKUI_IMMERSIVE_STYLE_ULTRA_THICK) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    material->style = style;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(ArkUI_ImmersiveMaterialHandle material,
    ArkUI_ImmersiveStyle* style)
{
    CHECK_NULL_RETURN(material && style, ARKUI_ERROR_CODE_PARAM_INVALID);
    *style = material->style;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(ArkUI_ImmersiveMaterialHandle material,
    uint32_t color)
{
    CHECK_NULL_RETURN(material, ARKUI_ERROR_CODE_PARAM_INVALID);
    material->materialColor = color;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(ArkUI_ImmersiveMaterialHandle material,
    uint32_t* color)
{
    CHECK_NULL_RETURN(material && color, ARKUI_ERROR_CODE_PARAM_INVALID);
    *color = material->materialColor;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(ArkUI_ImmersiveMaterialHandle material,
    bool applyShadow)
{
    CHECK_NULL_RETURN(material, ARKUI_ERROR_CODE_PARAM_INVALID);
    material->applyShadow = applyShadow;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(ArkUI_ImmersiveMaterialHandle material,
    bool* applyShadow)
{
    CHECK_NULL_RETURN(material && applyShadow, ARKUI_ERROR_CODE_PARAM_INVALID);
    *applyShadow = material->applyShadow;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(ArkUI_ImmersiveMaterialHandle material,
    bool interactive)
{
    CHECK_NULL_RETURN(material, ARKUI_ERROR_CODE_PARAM_INVALID);
    material->hasInteractive = true;
    material->interactive = interactive;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(ArkUI_ImmersiveMaterialHandle material,
    bool* interactive)
{
    CHECK_NULL_RETURN(material && interactive, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (!material->hasInteractive) {
        return ARKUI_ERROR_CODE_PARAM_ERROR;
    }
    *interactive = material->interactive;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_LightEffectOptionsHandle OH_ArkUI_NativeModule_LightEffectOptions_Create()
{
    return new ArkUI_LightEffectOptions();
}

void OH_ArkUI_NativeModule_LightEffectOptions_Destroy(ArkUI_LightEffectOptionsHandle options)
{
    if (options) {
        delete options;
    }
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_LightEffectOptions_SetColor(
    ArkUI_LightEffectOptionsHandle options, uint32_t color)
{
    CHECK_NULL_RETURN(options, ARKUI_ERROR_CODE_PARAM_INVALID);
    options->color = color;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(
    ArkUI_ImmersiveMaterialHandle material, const ArkUI_LightEffectOptionsHandle options)
{
    CHECK_NULL_RETURN(material, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (options) {
        material->hasLightEffect = true;
        material->disableLightEffect = false;
        material->lightEffectOptions.color = options->color;
    } else {
        material->hasLightEffect = false;
        material->disableLightEffect = true;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color)
{
    CHECK_NULL_RETURN(material && color, ARKUI_ERROR_CODE_PARAM_INVALID);
    if (material->disableLightEffect || !material->hasLightEffect) {
        return ARKUI_ERROR_CODE_PARAM_ERROR;
    }
    *color = material->lightEffectOptions.color;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
