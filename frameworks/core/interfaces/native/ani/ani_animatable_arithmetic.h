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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_ANIMATABLE_ARITHMETIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_ANIMATABLE_ARITHMETIC_H

#include "base/log/log_wrapper.h"
#include "core/components_ng/animation/animatable_arithmetic.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::NG {
class AniAnimatableArithmetic : public NG::CustomAnimatableArithmetic {
    DECLARE_ACE_TYPE(AniAnimatableArithmetic, NG::CustomAnimatableArithmetic)
public:
    AniAnimatableArithmetic() = default;
    ~AniAnimatableArithmetic() override
    {
        if (env_ && aniObject_ && DELETE_GLOBAL_REFERENCE_FUNC) {
            DELETE_GLOBAL_REFERENCE_FUNC(env_, aniObject_);
        }
        aniObject_ = nullptr;
        env_ = nullptr;
    }

    explicit AniAnimatableArithmetic(ani_object aniObject, ani_env* env) : env_(env)
    {
        if (env_ && aniObject && CREATE_GLOBAL_REFERENCE_FUNC) {
            aniObject_ = CREATE_GLOBAL_REFERENCE_FUNC(env_, aniObject);
        }
    }

    RefPtr<NG::CustomAnimatableArithmetic> Add(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_ || !ADD_FUNC) {
            return {};
        }
        auto rhsObject = rhs->GetObject();
        ani_object result = ADD_FUNC(env_, aniObject_, rhsObject);
        if (!result) {
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(result, env_);
    }

    RefPtr<NG::CustomAnimatableArithmetic> Minus(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_ || !MINUS_FUNC) {
            return {};
        }
        auto rhsObject = rhs->GetObject();
        ani_object result = MINUS_FUNC(env_, aniObject_, rhsObject);
        if (!result) {
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(result, env_);
    }

    RefPtr<NG::CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        if (!env_ || !MULTIPLY_FUNC) {
            return {};
        }
        ani_object result = MULTIPLY_FUNC(env_, aniObject_, scale);
        if (!result) {
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(result, env_);
    }

    bool IsEqual(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_ || !EQUAL_FUNC) {
            return false;
        }
        auto rhsObject = rhs->GetObject();
        bool result = EQUAL_FUNC(env_, aniObject_, rhsObject);
        return result;
    }

    ani_object GetObject() const
    {
        return aniObject_;
    }

    static void InitFuncs(const ArkUIAniAnimatableArithmeticFuncs& funcs)
    {
        if (initialized_) {
            return;
        }
        ADD_FUNC = funcs.addFunc;
        MINUS_FUNC = funcs.minusFunc;
        MULTIPLY_FUNC = funcs.multiplyFunc;
        EQUAL_FUNC = funcs.equalFunc;
        CREATE_GLOBAL_REFERENCE_FUNC = funcs.createFunc;
        DELETE_GLOBAL_REFERENCE_FUNC = funcs.deleteFunc;
        initialized_ = true;
    }

private:
    ani_object aniObject_ = nullptr;
    ani_env* env_ = nullptr;
    static ArkUIAniArithmeticAddFunction ADD_FUNC;
    static ArkUIAniArithmeticMinusFunction MINUS_FUNC;
    static ArkUIAniArithmeticMultiplyFunction MULTIPLY_FUNC;
    static ArkUIAniArithmeticEqualFunction EQUAL_FUNC;
    static ArkUIAniCreateObjectFunction CREATE_GLOBAL_REFERENCE_FUNC;
    static ArkUIAniDeleteObjectFunction DELETE_GLOBAL_REFERENCE_FUNC;
    static bool initialized_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_ANIMATABLE_ARITHMETIC_H
