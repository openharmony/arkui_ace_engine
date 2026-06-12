/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/ani/visual_effect_ani_modifier.h"

#include "core/components/common/properties/ui_material.h"

#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material_enums.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t UI_MATERIAL_STYLES_COUNT = 5;

bool CheckNotLegalStyle(UiMaterialStyle from)
{
    if (static_cast<int32_t>(from) < static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN) ||
        static_cast<int32_t>(from) > static_cast<int32_t>(UiMaterialStyle::MAX)) {
        return true;
    }
    return false;
}

UiMaterialStyle ConvertToECStyle(UiMaterialStyle from)
{
    int32_t style = static_cast<int32_t>(from);
    if (style >= static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN) &&
        style <= static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK)) {
        return static_cast<UiMaterialStyle>(style + UI_MATERIAL_STYLES_COUNT);
    } else if (style >= static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN_EC_SUB) &&
               style <= static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK_EC_SUB)) {
        return static_cast<UiMaterialStyle>(style - UI_MATERIAL_STYLES_COUNT);
    }
    return from;
}

UiMaterialStyle ConvertToECSubStyle(UiMaterialStyle from)
{
    int32_t style = static_cast<int32_t>(from);
    if (style >= static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN) &&
        style <= static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK)) {
        return static_cast<UiMaterialStyle>(style + UI_MATERIAL_STYLES_COUNT + UI_MATERIAL_STYLES_COUNT);
    } else if (style >= static_cast<int32_t>(UiMaterialStyle::ULTRA_THIN_EC) &&
               style <= static_cast<int32_t>(UiMaterialStyle::ULTRA_THICK_EC)) {
        return static_cast<UiMaterialStyle>(style + UI_MATERIAL_STYLES_COUNT);
    }
    return from;
}

void ConvertToImmersiveOptionsEC(std::shared_ptr<ImmersiveOptions>& newOptions)
{
    newOptions->style = ConvertToECStyle(newOptions->style);
    newOptions->materialColor = Color::TRANSPARENT;
    newOptions->applyShadow = false;
    newOptions->disableLightEffect = true;
    newOptions->interactive = false;
    newOptions->lightEffectOptions = std::nullopt;
    newOptions->colorResObj = nullptr;
}

void ConvertToImmersiveOptionsECSub(std::shared_ptr<ImmersiveOptions>& newOptions)
{
    newOptions->style = ConvertToECSubStyle(newOptions->style);
}

UiMaterial* ConstructMaterial(int32_t type)
{
    auto* material = new UiMaterial();
    material->SetType(type);
    material->IncRefCount();
    return material;
}

void DestroyMaterial(UiMaterial* materialPtr)
{
    CHECK_NULL_VOID(materialPtr);
    materialPtr->DecRefCount();
}

UiMaterial* ConvertToECMaterial(UiMaterial* materialPtr)
{
    CHECK_NULL_RETURN(materialPtr, nullptr);
    auto options = materialPtr->GetImmersiveOptions();
    if (materialPtr->GetType() != static_cast<int32_t>(MaterialType::IMMERSIVE) || !options) {
        return materialPtr;
    }
    if (CheckNotLegalStyle(options->style)) {
        return materialPtr;
    }
    auto newMaterial = materialPtr->Copy();
    newMaterial->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    newMaterial->IncRefCount();

    auto newOptions = newMaterial->GetImmersiveOptions();
    CHECK_NULL_RETURN(newOptions, materialPtr);
    ConvertToImmersiveOptionsEC(newOptions);
    return newMaterial.GetRawPtr();
}

UiMaterial* ConvertToECSubMaterial(UiMaterial* materialPtr)
{
    CHECK_NULL_RETURN(materialPtr, nullptr);
    auto options = materialPtr->GetImmersiveOptions();
    if (materialPtr->GetType() != static_cast<int32_t>(MaterialType::IMMERSIVE) || !options) {
        return materialPtr;
    }
    if (CheckNotLegalStyle(options->style)) {
        return materialPtr;
    }
    auto newMaterial = materialPtr->Copy();
    newMaterial->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    newMaterial->IncRefCount();

    auto newOptions = newMaterial->GetImmersiveOptions();
    CHECK_NULL_RETURN(newOptions, materialPtr);
    ConvertToImmersiveOptionsECSub(newOptions);
    return newMaterial.GetRawPtr();
}
} // namespace

const ArkUIAniVisualEffectModifier* GetVisualEffectAniModifier()
{
    static const ArkUIAniVisualEffectModifier impl = {
        .constructMaterial = OHOS::Ace::NG::ConstructMaterial,
        .destroyMaterial = OHOS::Ace::NG::DestroyMaterial,
        .convertToECMaterial = OHOS::Ace::NG::ConvertToECMaterial,
        .convertToECSubMaterial = OHOS::Ace::NG::ConvertToECSubMaterial,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
