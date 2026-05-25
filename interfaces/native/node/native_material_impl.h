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

#ifndef FOUNDATION_ACE_INTERFACES_NATIVE_NODE_NATIVE_MATERIAL_IMPL_H
#define FOUNDATION_ACE_INTERFACES_NATIVE_NODE_NATIVE_MATERIAL_IMPL_H

#include "native_material.h"

struct ArkUI_LightEffectOptions {
    uint32_t color = 0xFFFFFFFF;
};

struct ArkUI_ImmersiveMaterial {
    ArkUI_ImmersiveStyle style = ARKUI_IMMERSIVE_STYLE_REGULAR;
    uint32_t materialColor = 0x00000000;
    bool applyShadow = true;
    bool hasInteractive = false;
    bool interactive = false;
    bool disableLightEffect = false;
    bool hasLightEffect = false;
    struct ArkUI_LightEffectOptions lightEffectOptions {};
};

#endif // FOUNDATION_ACE_INTERFACES_NATIVE_NODE_NATIVE_MATERIAL_IMPL_H
