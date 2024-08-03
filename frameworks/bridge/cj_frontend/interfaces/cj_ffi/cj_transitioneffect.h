/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_H
#define OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_H

#include <cstdint>
#include <string>

#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components_ng/property/transition_property.h"
#include "cj_animate_param_ffi.h"

namespace OHOS::Ace::Framework {

struct CTranslateOptions {
    double x;
    uint32_t xType;
    double y;
    uint32_t yType;
    double z;
    uint32_t zType;
};

struct CScaleOptions {
    float x;
    float y;
    float z;
    double centerX;
    uint32_t centerXType;
    double centerY;
    uint32_t centerYType;
};

struct CRotateOptions {
    float angle;
    float x;
    float y;
    float z;
    double centerX;
    uint32_t centerXType;
    double centerY;
    uint32_t centerYType;
    double centerZ;
    uint32_t centerZType;
    float perspective;
};

class ACE_EXPORT NativeTransitionEffect: public OHOS::FFI::FFIData {
    DECL_TYPE(NativeTransitionEffect, OHOS::FFI::FFIData)

public:
    explicit NativeTransitionEffect(RefPtr<NG::ChainedTransitionEffect> effect);

    static RefPtr<NG::ChainedTransitionEffect> Opacity(double number)
    {
        double opacity = number;
        if ((LessNotEqual(opacity, 0.0)) || opacity > 1.0) {
            opacity = 1.0;
        }
        return AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    }

    static RefPtr<NG::ChainedTransitionEffect> Translate(CTranslateOptions options)
    {
        // default: x, y, z (0.0, 0.0, 0.0)
        NG::TranslateOptions translate;
        translate.x = CalcDimension(options.x, DimensionUnit(options.xType));
        translate.y = CalcDimension(options.y, DimensionUnit(options.yType));
        translate.z = CalcDimension(options.z, DimensionUnit(options.zType));
        return AceType::MakeRefPtr<NG::ChainedTranslateEffect>(translate);
    }

    static RefPtr<NG::ChainedTransitionEffect> Scale(CScaleOptions options)
    {
        // default: x, y, z (1.0, 1.0, 1.0), centerX, centerY 50% 50%;
        NG::ScaleOptions scale(options.x, options.y, options.z,
            CalcDimension(options.centerX, DimensionUnit(options.centerXType)),
            CalcDimension(options.centerY, DimensionUnit(options.centerYType)));
        return AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    }

    static RefPtr<NG::ChainedTransitionEffect> Rotate(CRotateOptions options)
    {
        NG::RotateOptions rotate(options.x, options.y, options.z, options.angle,
            CalcDimension(options.centerX, DimensionUnit(options.centerXType)),
            CalcDimension(options.centerY, DimensionUnit(options.centerYType)),
            CalcDimension(options.centerZ, DimensionUnit(options.centerZType)),
            options.perspective);
        return AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
    }

    static RefPtr<NG::ChainedTransitionEffect> Move(int32_t edge)
    {
        return AceType::MakeRefPtr<NG::ChainedMoveEffect>(static_cast<NG::TransitionEdge>(edge));
    }

    
    static RefPtr<NG::ChainedTransitionEffect> Asymmetric(int64_t appearId, int64_t disappearId)
    {
        auto appear = FFIData::GetData<NativeTransitionEffect>(appearId);
        if (appear == nullptr) {
            return nullptr;
        }
        auto disappear = FFIData::GetData<NativeTransitionEffect>(disappearId);
        if (disappear == nullptr) {
            return nullptr;
        }
        auto appearEffect = appear->effect;
        auto disappearEffect = disappear->effect;
        return AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearEffect, disappearEffect);
    }

    static RefPtr<NG::ChainedTransitionEffect> Identity()
    {
        return AceType::MakeRefPtr<NG::ChainedIdentityEffect>();
    }

    static RefPtr<NG::ChainedTransitionEffect> SlideSwitch()
    {
        return AceType::MakeRefPtr<NG::ChainedSlideSwitchEffect>();
    }

    void Combine(sptr<OHOS::Ace::Framework::NativeTransitionEffect> tagEffect);

    void Animation(const std::shared_ptr<AnimationOption> option);

    RefPtr<NG::ChainedTransitionEffect> effect;
};
} // namespace OHOS::Ace::Framework

#endif // OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_H