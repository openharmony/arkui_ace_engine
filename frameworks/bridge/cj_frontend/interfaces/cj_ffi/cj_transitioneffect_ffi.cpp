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


#include "cj_transitioneffect_ffi.h"

using namespace OHOS::FFI;

namespace OHOS::Ace::Framework {
extern "C" {
    int64_t FfiOHOSAceFrameworkTransitionEffectOpacity(double number)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Opacity(number);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectTranslate(CTranslateOptions options)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Translate(options);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectScale(CScaleOptions options)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Scale(options);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectRotate(CRotateOptions options)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Rotate(options);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectMove(int32_t edge)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Move(edge);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectAsymmetric(int64_t appearId, int64_t disappearId)
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Asymmetric(appearId, disappearId);
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    void FfiOHOSAceFrameworkTransitionEffectCombine(int64_t id, int64_t effectId)
    {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(id);
        if (nativeTransitionEffect == nullptr) {
            return;
        }
        auto tagEffect = FFIData::GetData<NativeTransitionEffect>(effectId);
        if (tagEffect == nullptr) {
            return;
        }
        nativeTransitionEffect->Combine(tagEffect);
    }

    void FfiOHOSAceFrameworkTransitionEffectAnimation(int64_t id, NativeAnimateParam param)
    {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(id);
        if (nativeTransitionEffect == nullptr) {
            return;
        }
        auto animationOptionResult = std::make_shared<AnimationOption>();
        ParseCjAnimation(param, *animationOptionResult);
        nativeTransitionEffect->Animation(animationOptionResult);
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectIdentity()
    {
        auto chainedTransitionEffect = NativeTransitionEffect::Identity();
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }

    int64_t FfiOHOSAceFrameworkTransitionEffectSlideSwitch()
    {
        auto chainedTransitionEffect = NativeTransitionEffect::SlideSwitch();
        auto nativeTransitionEffect = FFIData::Create<NativeTransitionEffect>(chainedTransitionEffect);
        if (nativeTransitionEffect == nullptr) {
            return FFI_ERROR_CODE;
        }
        return nativeTransitionEffect->GetID();
    }
};
}