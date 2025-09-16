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

#include "ani.h"
#include "ani_utils.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/animation/animatable_arithmetic.h"

namespace OHOS::Ace::NG {
class AniAnimatableArithmetic : public NG::CustomAnimatableArithmetic {
    DECLARE_ACE_TYPE(AniAnimatableArithmetic, NG::CustomAnimatableArithmetic)
public:
    AniAnimatableArithmetic() = default;
    ~AniAnimatableArithmetic() override
    {
        if (env_ && aniObject_) {
            env_->GlobalReference_Delete(static_cast<ani_ref>(aniObject_));
        }
        aniObject_ = nullptr;
        env_ = nullptr;
    }

    explicit AniAnimatableArithmetic(ani_object aniObject, ani_env* env) : env_(env)
    {
        ani_ref globalRef;
        if (env_) {
            env_->GlobalReference_Create(static_cast<ani_ref>(aniObject), &globalRef);
            aniObject_ = static_cast<ani_object>(globalRef);
        }
    }

    RefPtr<NG::CustomAnimatableArithmetic> Add(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_) {
            return {};
        }
        auto rhsObject = rhs->GetObject();
        ani_ref rhsRef = static_cast<ani_ref>(rhsObject);
        ani_ref result;
        ani_status status = env_->Object_CallMethodByName_Ref(aniObject_, "plus", nullptr, &result, rhsRef);
        if (status != ANI_OK) {
            TAG_LOGW(
                AceLogTag::ACE_ANIMATION, "AniAnimatableArithmetic call plus func fail, errorCode:%{public}d", status);
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(static_cast<ani_object>(result), env_);
    }

    RefPtr<NG::CustomAnimatableArithmetic> Minus(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_) {
            return {};
        }
        auto rhsObject = rhs->GetObject();
        ani_ref rhsRef = static_cast<ani_ref>(rhsObject);
        ani_ref result;
        ani_status status = env_->Object_CallMethodByName_Ref(aniObject_, "subtract", nullptr, &result, rhsRef);
        if (status != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "AniAnimatableArithmetic call subtract func fail, errorCode:%{public}d",
                status);
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(static_cast<ani_object>(result), env_);
    }

    RefPtr<NG::CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        if (!env_) {
            return {};
        }
        ani_float aniScale = scale;
        ani_ref result;
        ani_status status = env_->Object_CallMethodByName_Ref(aniObject_, "multiply", nullptr, &result, aniScale);
        if (status != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "AniAnimatableArithmetic call multiply func fail, errorCode:%{public}d",
                status);
            return {};
        }
        return MakeRefPtr<AniAnimatableArithmetic>(static_cast<ani_object>(result), env_);
    }

    bool IsEqual(const RefPtr<NG::CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<AniAnimatableArithmetic> rhs = AceType::DynamicCast<AniAnimatableArithmetic>(value);
        if (!rhs || !env_) {
            return false;
        }
        auto rhsObject = rhs->GetObject();
        ani_ref rhsRef = static_cast<ani_ref>(rhsObject);
        ani_boolean result;
        ani_status status = env_->Object_CallMethodByName_Boolean(aniObject_, "equals", nullptr, &result, rhsRef);
        if (status != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "AniAnimatableArithmetic call equals func fail, errorCode:%{public}d",
                status);
            return false;
        }
        return static_cast<bool>(result);
    }

    ani_object GetObject() const
    {
        return aniObject_;
    }

private:
    ani_object aniObject_ = nullptr;
    ani_env* env_ = nullptr;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_ANIMATABLE_ARITHMETIC_H
