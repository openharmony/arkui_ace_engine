/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_PROXY_H

#include "core/components_ng/animation/animatable_arithmetic.h"

namespace OHOS::Ace::NG {
class AnimatableArithmeticProxy : public AnimatableArithmetic<AnimatableArithmeticProxy> {
public:
    AnimatableArithmeticProxy() = default;
    explicit AnimatableArithmeticProxy(RefPtr<CustomAnimatableArithmetic> object) : object_(object) {}
    virtual ~AnimatableArithmeticProxy() = default;

    AnimatableArithmeticProxy Add(const AnimatableArithmeticProxy& val) const override
    {
        if (!object_) {
            return {};
        }
        if (!val.object_) {
            return {};
        }

        return AnimatableArithmeticProxy(object_->Add(val.object_));
    }

    AnimatableArithmeticProxy Minus(const AnimatableArithmeticProxy& val) const override
    {
        if (!object_) {
            return {};
        }
        if (!val.object_) {
            return {};
        }
        return AnimatableArithmeticProxy(object_->Minus(val.object_));
    }

    AnimatableArithmeticProxy Multiply(const float scale) const override
    {
        if (!object_) {
            return {};
        }
        return AnimatableArithmeticProxy(object_->Multiply(scale));
    }

    bool IsEqual(const AnimatableArithmeticProxy& val) const override
    {
        if (!object_) {
            return {};
        }
        if (!val.object_) {
            return {};
        }
        return object_->IsEqual(val.object_);
    }

    RefPtr<CustomAnimatableArithmetic> GetObject() const
    {
        return object_;
    }

private:
    RefPtr<CustomAnimatableArithmetic> object_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_PROXY_H
