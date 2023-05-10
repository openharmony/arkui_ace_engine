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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_H

#include <memory>

#include "base/memory/ace_type.h"
namespace OHOS::Ace::NG {
template<typename T>
class ACE_EXPORT Arithmetic {
public:
    Arithmetic() = default;
    virtual ~Arithmetic() = default;

    virtual bool IsEqual(const T& value) const = 0;

    bool operator==(const T& value) const
    {
        return IsEqual(value);
    }

    bool operator!=(const T& value) const
    {
        return !IsEqual(value);
    }
};

template<typename T>
class ACE_EXPORT AnimatableArithmetic : public Arithmetic<T> {
public:
    AnimatableArithmetic() = default;
    virtual ~AnimatableArithmetic() = default;

    virtual T Add(const T& value) const = 0;
    virtual T Minus(const T& value) const = 0;
    virtual T Multiply(const float scale) const = 0;

    T operator+(const T& value) const
    {
        return Add(value);
    }
    T operator+=(const T& value) const
    {
        return Add(value);
    }
    T operator-(const T& value) const
    {
        return Minus(value);
    }
    T operator-=(const T& value) const
    {
        return Minus(value);
    }
    T operator*(const float scale) const
    {
        return Multiply(scale);
    }
    T operator*=(const float scale) const
    {
        return Multiply(scale);
    }
};

class ACE_EXPORT CustomAnimatableArithmetic : public AceType,
                                              public AnimatableArithmetic<RefPtr<CustomAnimatableArithmetic>> {
    DECLARE_ACE_TYPE(CustomAnimatableArithmetic, AceType)
public:
    CustomAnimatableArithmetic() = default;
    ~CustomAnimatableArithmetic() override = default;

    RefPtr<CustomAnimatableArithmetic> Add(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        return {};
    };
    RefPtr<CustomAnimatableArithmetic> Minus(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        return {};
    }
    RefPtr<CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        return {};
    }
    bool IsEqual(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        return true;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ANIMATABLE_ARITHMETIC_H
