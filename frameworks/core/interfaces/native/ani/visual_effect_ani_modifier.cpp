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

namespace OHOS::Ace::NG {

namespace {
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
} // namespace

const ArkUIAniVisualEffectModifier* GetVisualEffectAniModifier()
{
    static const ArkUIAniVisualEffectModifier impl = {
        .constructMaterial = OHOS::Ace::NG::ConstructMaterial,
        .destroyMaterial = OHOS::Ace::NG::DestroyMaterial,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
