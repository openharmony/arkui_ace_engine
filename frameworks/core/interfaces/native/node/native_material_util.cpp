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

#include "native_material_util.h"

#include "ui/base/utils/utils.h"

using namespace OHOS::Ace;

RefPtr<UiMaterial> CreateUiMaterialFromHandle(ArkUI_ImmersiveMaterialHandle handle)
{
    CHECK_NULL_RETURN(handle, nullptr);
    auto uiMaterial = AceType::MakeRefPtr<UiMaterial>();
    uiMaterial->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ImmersiveOptions options {};
    options.style = static_cast<UiMaterialStyle>(handle->style);
    options.materialColor = Color(handle->materialColor);
    options.applyShadow = handle->applyShadow;
    if (handle->hasInteractive) {
        options.interactive = handle->interactive;
    }
    if (handle->disableLightEffect) {
        options.DisableLightEffect();
    } else if (handle->hasLightEffect) {
        LightEffectOptions lightEffect { .color = Color(handle->lightEffectOptions.color) };
        options.lightEffectOptions = lightEffect;
    }
    uiMaterial->SetImmersiveOptions(options);
    return uiMaterial;
}

bool CreateHandleFromUiMaterial(const RefPtr<UiMaterial>& material, ArkUI_ImmersiveMaterialHandle out)
{
    CHECK_NULL_RETURN(material && out, false);
    auto options = material->GetImmersiveOptions();
    CHECK_NULL_RETURN(options, false);
    // here applies default value.
    *out = ArkUI_ImmersiveMaterial();
    out->style = static_cast<ArkUI_ImmersiveStyle>(static_cast<int32_t>(options->style));
    out->materialColor = options->materialColor.GetValue();
    out->applyShadow = options->applyShadow;
    if (options->interactive.has_value()) {
        out->hasInteractive = true;
        out->interactive = options->interactive.value();
    }
    if (options->disableLightEffect) {
        out->disableLightEffect = true;
    } else if (options->lightEffectOptions.has_value()) {
        out->hasLightEffect = true;
        out->lightEffectOptions.color = options->lightEffectOptions->color.GetValue();
    }
    return true;
}
