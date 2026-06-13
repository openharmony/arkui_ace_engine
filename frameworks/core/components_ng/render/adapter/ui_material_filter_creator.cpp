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

#include "core/components_ng/render/ui_material_filter_creator.h"

#include "render_service_client/core/ui_effect/property/include/rs_ui_filter_base.h"
#include "render_service_client/core/ui_effect/property/include/rs_ui_filter_to_para.h"
#include "render_service_client/core/ui_effect/property/include/rs_ui_shader_base.h"
#include "render_service_client/core/ui_effect/filter/include/filter.h"
#include "ui/properties/ui_material_structs.h"

#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/render/adapter/rosen_effect_converter.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t UI_MATERIAL_STYLES_COUNT = 5;

constexpr FrostedGlassParam Gentle_Regular_Transparency3_Light {
    .blurParams = { 12.0f, 6.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.7f },
    .bgRates = { 0.2526f, -0.663f },
    .bgKBS = { 0.9099f, 0.498f, 1.5f },
    .bgPos = { 0.1f, 1.0f, 0.5f },
    .bgNeg = { 1.5f, 1.5f, 2.0f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.0f, 0.2268f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 6.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.5259f, 0.07f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_Regular_Transparency3_Dark {
    .blurParams = { 12.0f, 6.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.6f },
    .bgRates = {},
    .bgKBS = { 0.5259f, 0.07f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.2f, 0.294f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 6.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.5259f, 0.07f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_Regular_Transparency4_Light {
    .blurParams = { 20.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.2988f, 0.7059f, 1.5f },
    .bgPos = { 2.0f, 1.5f, 1.0f },
    .bgNeg = { 2.0f, 3.0f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 20.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Regular_Transparency4_Dark {
    .blurParams = { 20.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 20.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Regular_Transparency5_Light {
    .blurParams = { 40.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.2988f, 0.7059f, 1.5f },
    .bgPos = { 2.0f, 1.5f, 1.0f },
    .bgNeg = { 2.0f, 3.0f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 40.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Regular_Transparency5_Dark {
    .blurParams = { 40.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 40.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency3_Light {
    .blurParams = { 5.0f, 20.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.7f },
    .bgRates = { 0.1789f, -0.6972f },
    .bgKBS = { 1.4384f, 0.0718f, 1.2f },
    .bgPos = { 0.3f, 0.5f, 1.0f },
    .bgNeg = { 0.5f, 0.5f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.62f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.0f, 0.1568f, 1.2f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 5.0f, 20.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { 0.0023f, -0.0176f },
    .darkModeBgKBS = { 0.8414f, 0.0765f, 1.2f },
    .darkModeBgPos = { 0.3f, 1.0f, 1.0f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.0f, 0.2268f, 1.2f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency3_Dark {
    .blurParams = { 5.0f, 20.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.6f },
    .bgRates = { 0.0023f, -0.0176f },
    .bgKBS = { 0.8414f, 0.0765f, 1.2f },
    .bgPos = { 0.3f, 1.0f, 1.0f },
    .bgNeg = { 1.2f, 2.5f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.62f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.0f, 0.2268f, 1.2f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 5.0f, 20.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { 0.0023f, -0.0176f },
    .darkModeBgKBS = { 0.8414f, 0.0765f, 1.2f },
    .darkModeBgPos = { 0.3f, 1.0f, 1.0f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.0f, 0.2268f, 1.2f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency4_Light {
    .blurParams = { 10.0f, 20.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { 0.2526f, -0.663f },
    .bgKBS = { 0.9099f, 0.498f, 1.5f },
    .bgPos = { 0.1f, 1.0f, 0.5f },
    .bgNeg = { 1.5f, 1.5f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 10.0f, 20.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency4_Dark {
    .blurParams = { 10.0f, 20.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 10.0f, 20.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency5_Light {
    .blurParams = { 20.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { 0.2526f, -0.663f },
    .bgKBS = { 0.9099f, 0.498f, 1.5f },
    .bgPos = { 0.1f, 1.0f, 0.5f },
    .bgNeg = { 1.5f, 1.5f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 20.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_UltraThin_Transparency5_Dark {
    .blurParams = { 20.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 20.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency3_Light {
    .blurParams = { 12.0f, 6.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.7f },
    .bgRates = { 0.1789f, -0.6972f },
    .bgKBS = { 1.4384f, 0.0718f, 1.2f },
    .bgPos = { 0.3f, 0.5f, 1.0f },
    .bgNeg = { 0.5f, 0.5f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.62f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.0f, 0.1568f, 1.2f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 6.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { 0.0023f, -0.0176f },
    .darkModeBgKBS = { 0.8414f, 0.0765f, 1.2f },
    .darkModeBgPos = { 0.3f, 1.0f, 1.0f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.0f, 0.2268f, 1.2f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency3_Dark {
    .blurParams = { 12.0f, 6.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.6f },
    .bgRates = { 0.0023f, -0.0176f },
    .bgKBS = { 0.8414f, 0.0765f, 1.2f },
    .bgPos = { 0.3f, 1.0f, 1.0f },
    .bgNeg = { 1.2f, 2.5f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.62f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.0f, 0.2268f, 1.2f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 6.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { 0.0023f, -0.0176f },
    .darkModeBgKBS = { 0.8414f, 0.0765f, 1.2f },
    .darkModeBgPos = { 0.3f, 1.0f, 1.0f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.0f, 0.2268f, 1.2f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency4_Light {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { 0.2526f, -0.663f },
    .bgKBS = { 0.9099f, 0.498f, 1.5f },
    .bgPos = { 0.1f, 1.0f, 0.5f },
    .bgNeg = { 1.5f, 1.5f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency4_Dark {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency5_Light {
    .blurParams = { 24.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { 0.2526f, -0.663f },
    .bgKBS = { 0.9099f, 0.498f, 1.5f },
    .bgPos = { 0.1f, 1.0f, 0.5f },
    .bgNeg = { 1.5f, 1.5f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 24.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_Thin_Transparency5_Dark {
    .blurParams = { 24.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = { -0.0056f, 0.0721f },
    .bgKBS = { 0.3752f, 0.1296f, 1.5f },
    .bgPos = { 1.5f, 3.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 0.5f },
    .refractParams = {},
    .darkModeBlurParams = { 24.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = { -0.0056f, 0.0721f },
    .darkModeBgKBS = { 0.3752f, 0.1296f, 1.5f },
    .darkModeBgPos = { 1.5f, 3.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 0.5f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency3_Light {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.4f },
    .bgRates = {},
    .bgKBS = { 0.1f, 0.88f, 2.3f },
    .bgPos = { 0.8f, 0.7f, 1.0f },
    .bgNeg = { 1.0f, 1.2f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 85.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 0.8f, 0.3922f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 1.7f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency3_Dark {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.7f },
    .bgRates = {},
    .bgKBS = { 0.1f, 0.12f, 1.7f },
    .bgPos = { 0.5f, 0.7f, 2.0f },
    .bgNeg = { 1.0f, 1.0f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.2f, 0.294f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 1.7f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency4_Light {
    .blurParams = { 25.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.1f, 0.88f, 2.3f },
    .bgPos = { 0.8f, 0.7f, 1.0f },
    .bgNeg = { 1.0f, 1.2f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 25.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 2.0f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency4_Dark {
    .blurParams = { 25.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.1f, 0.12f, 2.0f },
    .bgPos = { 0.5f, 0.7f, 2.0f },
    .bgNeg = { 1.0f, 1.0f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 25.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 2.0f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency5_Light {
    .blurParams = { 50.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.1f, 0.88f, 2.3f },
    .bgPos = { 0.8f, 0.7f, 1.0f },
    .bgNeg = { 1.0f, 1.2f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 50.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 2.0f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
};
constexpr FrostedGlassParam Gentle_UltraThick_Transparency5_Dark {
    .blurParams = { 50.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.1f, 0.12f, 2.0f },
    .bgPos = { 0.5f, 0.7f, 2.0f },
    .bgNeg = { 1.0f, 1.0f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 50.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.1f, 0.12f, 2.0f },
    .darkModeBgPos = { 0.5f, 0.7f, 2.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 1.0f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency3_Light {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.4f },
    .bgRates = {},
    .bgKBS = { 0.2988f, 0.7059f, 1.5f },
    .bgPos = { 2.0f, 1.5f, 1.0f },
    .bgNeg = { 2.0f, 3.0f, 2.0f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 85.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 0.8f, 0.3922f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.3230f, 0.07054f, 1.8f },
    .darkModeBgPos = { 1.7f, 1.5f, 1.5f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency3_Dark {
    .blurParams = { 12.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = { 1.0f, 0.7f },
    .bgRates = {},
    .bgKBS = { 0.3230f, 0.07054f, 1.8f },
    .bgPos = { 1.7f, 1.5f, 1.5f },
    .bgNeg = { 1.2f, 2.5f, 1.0f },
    .refractParams = {},
    .edLightParams = { 0.83f, 0.92f },
    .edLightAngles = { 75.0f, 120.0f },
    .edLightDir = { 0.0f, -1.0f },
    .edLightRates = {},
    .edLightKBS = { 1.2f, 0.294f, 1.5f },
    .edLightPos = { 1.0f, 1.5f, 2.0f },
    .edLightNeg = { 1.7f, 3.0f, 1.0f },
    .darkModeBlurParams = { 12.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.3230f, 0.07054f, 1.8f },
    .darkModeBgPos = { 1.7f, 1.5f, 1.5f },
    .darkModeBgNeg = { 1.2f, 2.5f, 1.0f },
    .darkModeEdLightAngles = { 75.0f, 120.0f },
    .darkModeEdLightKBS = { 1.2f, 0.294f, 1.5f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency4_Light {
    .blurParams = { 25.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.196f, 0.8f, 2.3f },
    .bgPos = { 0.8f, 0.7f, 1.0f },
    .bgNeg = { 1.0f, 1.2f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 25.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.31f, 0.18f, 1.6f },
    .darkModeBgPos = { 2.3f, 4.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 2.0f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency4_Dark {
    .blurParams = { 25.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.31f, 0.18f, 1.6f },
    .bgPos = { 2.3f, 4.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 25.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.31f, 0.18f, 1.6f },
    .darkModeBgPos = { 2.3f, 4.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 2.0f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency5_Light {
    .blurParams = { 50.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.196f, 0.8f, 2.3f },
    .bgPos = { 0.8f, 0.7f, 1.0f },
    .bgNeg = { 1.0f, 1.2f, 1.0f },
    .refractParams = {},
    .darkModeBlurParams = { 50.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.31f, 0.18f, 1.6f },
    .darkModeBgPos = { 2.3f, 4.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 2.0f },
};
constexpr FrostedGlassParam Gentle_Thick_Transparency5_Dark {
    .blurParams = { 50.0f, 1.0f },
    .weightsEmboss = {},
    .weightsEdl = {},
    .bgRates = {},
    .bgKBS = { 0.31f, 0.18f, 1.6f },
    .bgPos = { 2.3f, 4.0f, 1.0f },
    .bgNeg = { 1.0f, 1.0f, 2.0f },
    .refractParams = {},
    .darkModeBlurParams = { 50.0f, 1.0f },
    .darkModeWeightsEmboss = {},
    .darkModeBgRates = {},
    .darkModeBgKBS = { 0.31f, 0.18f, 1.6f },
    .darkModeBgPos = { 2.3f, 4.0f, 1.0f },
    .darkModeBgNeg = { 1.0f, 1.0f, 2.0f },
};

const std::unordered_map<UiMaterialMapKey, const FrostedGlassParam*, UiMaterialMapKeyHasher> MATERIAL_PARAM_MAP = {
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_THIN, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency3_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_THIN, ColorMode::DARK },
        &Gentle_UltraThin_Transparency3_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency4_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::DARK },
        &Gentle_UltraThin_Transparency4_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_THICK, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency5_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::GENTLE_THICK, ColorMode::DARK },
        &Gentle_UltraThin_Transparency5_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_THIN, ColorMode::LIGHT },
        &Gentle_Thin_Transparency3_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_THIN, ColorMode::DARK },
        &Gentle_Thin_Transparency3_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::LIGHT },
        &Gentle_Thin_Transparency4_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::DARK },
        &Gentle_Thin_Transparency4_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_THICK, ColorMode::LIGHT },
        &Gentle_Thin_Transparency5_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THIN, UiMaterialTransparency::GENTLE_THICK, ColorMode::DARK },
        &Gentle_Thin_Transparency5_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_THIN, ColorMode::LIGHT },
        &Gentle_Regular_Transparency3_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_THIN, ColorMode::DARK },
        &Gentle_Regular_Transparency3_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::LIGHT },
        &Gentle_Regular_Transparency4_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::DARK },
        &Gentle_Regular_Transparency4_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_THICK, ColorMode::LIGHT },
        &Gentle_Regular_Transparency5_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::REGULAR, UiMaterialTransparency::GENTLE_THICK, ColorMode::DARK },
        &Gentle_Regular_Transparency5_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_THIN, ColorMode::LIGHT },
        &Gentle_Thick_Transparency3_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_THIN, ColorMode::DARK },
        &Gentle_Thick_Transparency3_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::LIGHT },
        &Gentle_Thick_Transparency4_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::DARK },
        &Gentle_Thick_Transparency4_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_THICK, ColorMode::LIGHT },
        &Gentle_Thick_Transparency5_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::THICK, UiMaterialTransparency::GENTLE_THICK, ColorMode::DARK },
        &Gentle_Thick_Transparency5_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_THIN, ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency3_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_THIN, ColorMode::DARK },
        &Gentle_UltraThick_Transparency3_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_NORMAL,
        ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency4_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_NORMAL, ColorMode::DARK },
        &Gentle_UltraThick_Transparency4_Dark },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_THICK, ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency5_Light },
    { { UiMaterialLevel::GENTLE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::GENTLE_THICK, ColorMode::DARK },
        &Gentle_UltraThick_Transparency5_Dark },
    // for EXQUISITE
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::THIN, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency3_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::THIN, ColorMode::DARK },
        &Gentle_UltraThin_Transparency3_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::NORMAL, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency4_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::NORMAL, ColorMode::DARK },
        &Gentle_UltraThin_Transparency4_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::THICK, ColorMode::LIGHT },
        &Gentle_UltraThin_Transparency5_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THIN, UiMaterialTransparency::THICK, ColorMode::DARK },
        &Gentle_UltraThin_Transparency5_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::THIN, ColorMode::LIGHT },
        &Gentle_Thin_Transparency3_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::THIN, ColorMode::DARK },
        &Gentle_Thin_Transparency3_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::NORMAL, ColorMode::LIGHT },
        &Gentle_Thin_Transparency4_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::NORMAL, ColorMode::DARK },
        &Gentle_Thin_Transparency4_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::THICK, ColorMode::LIGHT },
        &Gentle_Thin_Transparency5_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THIN, UiMaterialTransparency::THICK, ColorMode::DARK },
        &Gentle_Thin_Transparency5_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::THIN, ColorMode::LIGHT },
        &Gentle_Regular_Transparency3_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::THIN, ColorMode::DARK },
        &Gentle_Regular_Transparency3_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::NORMAL, ColorMode::LIGHT },
        &Gentle_Regular_Transparency4_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::NORMAL, ColorMode::DARK },
        &Gentle_Regular_Transparency4_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::THICK, ColorMode::LIGHT },
        &Gentle_Regular_Transparency5_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::REGULAR, UiMaterialTransparency::THICK, ColorMode::DARK },
        &Gentle_Regular_Transparency5_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::THIN, ColorMode::LIGHT },
        &Gentle_Thick_Transparency3_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::THIN, ColorMode::DARK },
        &Gentle_Thick_Transparency3_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::NORMAL, ColorMode::LIGHT },
        &Gentle_Thick_Transparency4_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::NORMAL, ColorMode::DARK },
        &Gentle_Thick_Transparency4_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::THICK, ColorMode::LIGHT },
        &Gentle_Thick_Transparency5_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::THICK, UiMaterialTransparency::THICK, ColorMode::DARK },
        &Gentle_Thick_Transparency5_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::THIN, ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency3_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::THIN, ColorMode::DARK },
        &Gentle_UltraThick_Transparency3_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::NORMAL, ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency4_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::NORMAL, ColorMode::DARK },
        &Gentle_UltraThick_Transparency4_Dark },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::THICK, ColorMode::LIGHT },
        &Gentle_UltraThick_Transparency5_Light },
    { { UiMaterialLevel::EXQUISITE, UiMaterialStyle::ULTRA_THICK, UiMaterialTransparency::THICK, ColorMode::DARK },
        &Gentle_UltraThick_Transparency5_Dark },
};
}

std::shared_ptr<Rosen::RSNGFilterBase> UiMaterialFilterCreator::ConvertToUiMaterialFilter(
    const ImmersiveMaterialConfig& params)
{
    std::shared_ptr<Rosen::RSNGFilterBase> filter;
    if (!MaterialUtils::GetUiMaterialFilter(params, filter)) {
        auto iter = MATERIAL_PARAM_MAP.find(params.key);
        if (iter == MATERIAL_PARAM_MAP.end()) {
            return nullptr;
        }
        filter = RosenEffectConverter::ConvertToFrostedGlassFilter(*(iter->second), params.dipScale);
    }
#if defined(CROSS_PLATFORM)
    return filter;
#else
    auto glassFilter = std::static_pointer_cast<Rosen::RSNGFrostedGlassFilter>(filter);
    CHECK_NULL_RETURN(glassFilter, nullptr);
    auto& materialColor = params.materialColor;
    Rosen::Vector4f rsColor { materialColor.GetRed() / 255.0f, materialColor.GetGreen() / 255.0f,
        materialColor.GetBlue() / 255.0f, materialColor.GetAlpha() / 255.0f };
    glassFilter->Setter<Rosen::FrostedGlassMaterialColorTag>(rsColor);
    return filter;
#endif
}

std::shared_ptr<Rosen::RSNGFilterBase> UiMaterialFilterCreator::ConvertToUiMaterialECFilter(
    const ImmersiveMaterialConfig& params)
{
    int32_t style = static_cast<int32_t>(params.key.style);
    ImmersiveMaterialConfig newConfig = params;
    newConfig.key.style = static_cast<UiMaterialStyle>(style % UI_MATERIAL_STYLES_COUNT);

    std::shared_ptr<Rosen::RSNGFilterBase> filter;
    if (!MaterialUtils::GetUiMaterialFilterEC(newConfig, filter)) {
        auto iter = MATERIAL_PARAM_MAP.find(newConfig.key);
        if (iter == MATERIAL_PARAM_MAP.end()) {
            return nullptr;
        }
        filter = RosenEffectConverter::ConvertToFrostedGlassFilterEC(*(iter->second), newConfig.dipScale);
    }
    return filter;
}
std::shared_ptr<Rosen::RSNGShaderBase> UiMaterialFilterCreator::ConvertToUiMaterialECSubShader(
    const ImmersiveMaterialConfig& params)
{
    int32_t style = static_cast<int32_t>(params.key.style);
    ImmersiveMaterialConfig newConfig = params;
    newConfig.key.style = static_cast<UiMaterialStyle>(style % UI_MATERIAL_STYLES_COUNT);

    std::shared_ptr<Rosen::RSNGShaderBase> shader;
    if (!MaterialUtils::GetUiMaterialShaderECSub(newConfig, shader)) {
        auto iter = MATERIAL_PARAM_MAP.find(newConfig.key);
        if (iter == MATERIAL_PARAM_MAP.end()) {
            return nullptr;
        }
        shader = RosenEffectConverter::ConvertToRSNGFrostedGlassEffectECSub(*(iter->second), newConfig.dipScale);
    }
#if defined(CROSS_PLATFORM)
    return shader;
#else
    auto glassEffect = std::static_pointer_cast<Rosen::RSNGFrostedGlassEffect>(shader);
    CHECK_NULL_RETURN(glassEffect, nullptr);
    auto& materialColor = newConfig.materialColor;
    Rosen::Vector4f rsColor { materialColor.GetRed() / 255.0f, materialColor.GetGreen() / 255.0f,
        materialColor.GetBlue() / 255.0f, materialColor.GetAlpha() / 255.0f };
    glassEffect->Setter<Rosen::FrostedGlassEffectMaterialColorTag>(rsColor);
    return shader;
#endif
}

std::shared_ptr<OHOS::Rosen::Filter> UiMaterialFilterCreator::CreateRosenFilter(
    const ImmersiveMaterialConfig& params)
{
    auto filterBase = ConvertToUiMaterialFilter(params);
    CHECK_NULL_RETURN(filterBase, nullptr);
    auto para = Rosen::RSNGFilterToParaHelper::ConvertFilterToPara(filterBase);
    CHECK_NULL_RETURN(para, nullptr);
    auto rosenFilter = std::make_shared<Rosen::Filter>();
    rosenFilter->AddPara(para);
    return rosenFilter;
}
} // namespace OHOS::Ace::NG
