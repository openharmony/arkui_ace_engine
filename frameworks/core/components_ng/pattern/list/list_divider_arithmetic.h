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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DIVIDER_ARITHMETIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DIVIDER_ARITHMETIC_H

#include "core/components_ng/animation/animatable_arithmetic.h"

namespace OHOS::Ace::NG {
using OHOS::Ace::NG::CustomAnimatableArithmetic;
struct ListDivider {
    bool isDelta = true;
    OffsetF offset;
    float length = 0.0f;
};

class ListDividerArithmetic : public CustomAnimatableArithmetic {
    DECLARE_ACE_TYPE(ListDividerArithmetic, CustomAnimatableArithmetic);
public:
    using DividerMap = std::map<int32_t, ListDivider>;
    ListDividerArithmetic() = default;
    ~ListDividerArithmetic() override = default;
   
    explicit ListDividerArithmetic(const DividerMap& dividerMap) : dividermap_(dividerMap) {}

    RefPtr<CustomAnimatableArithmetic> Add(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<ListDividerArithmetic> rhs = AceType::DynamicCast<ListDividerArithmetic>(value);
        if (!rhs) {
            return {};
        }
        DividerMap another = rhs->GetDividerMap();
        DividerMap one = another;
        for (auto& child : one) {
            auto it = dividermap_.find(child.first);
            if (it != dividermap_.end()) {
                child.second.length = child.second.length + it->second.length;
                child.second.offset = child.second.offset + it->second.offset;
            }
        }
        return MakeRefPtr<ListDividerArithmetic>(one);
    }

    RefPtr<CustomAnimatableArithmetic> Minus(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<ListDividerArithmetic> rhs = AceType::DynamicCast<ListDividerArithmetic>(value);
        if (!rhs) {
            return {};
        }
        DividerMap another = rhs->GetDividerMap();
        rhs->ResetDividerMap();
        DividerMap one = dividermap_;
        for (auto& child : one) {
            auto it = another.find(child.first);
            if (it != another.end()) {
                child.second.length = child.second.length - it->second.length;
                child.second.offset = child.second.offset - it->second.offset;
            } else {
                child.second.isDelta = false;
            }
        }
        return MakeRefPtr<ListDividerArithmetic>(one);
    }

    RefPtr<CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        DividerMap one = dividermap_;
        for (auto& child : one) {
            if (child.second.isDelta == true) {
                child.second.length = child.second.length * scale;
                child.second.offset = child.second.offset * scale;
            }
        }
        return MakeRefPtr<ListDividerArithmetic>(one);
    }

    bool IsEqual(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<ListDividerArithmetic> rhs = AceType::DynamicCast<ListDividerArithmetic>(value);
        if (!rhs) {
            return false;
        }
        DividerMap another = rhs->GetDividerMap();
        DividerMap one = dividermap_;

        if (another.size() != one.size()) {
            return false;
        }
        auto iterAnother = another.begin();
        auto iterOne = one.begin();
        for (; iterAnother != another.end(); ++iterAnother, ++iterOne) {
            if (iterAnother->first != iterOne->first ||
                iterAnother->second.offset != iterOne->second.offset ||
                iterAnother->second.length != iterOne->second.length) {
                return false;
            }
        }
        return true;
    }

    DividerMap GetDividerMap() const
    {
        return dividermap_;
    }

    void ResetDividerMap()
    {
        for (auto& child : dividermap_) {
            child.second.isDelta = true;
        }
    }

private:
    DividerMap dividermap_;

    ACE_DISALLOW_COPY_AND_MOVE(ListDividerArithmetic);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DIVIDER_ARITHMETIC_H
