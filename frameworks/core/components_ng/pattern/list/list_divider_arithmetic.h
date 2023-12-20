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
    float length;
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
        DividerMap one;
        for (auto child : another) {
            if (child.second.isDelta == true && dividermap_.find(child.first) == dividermap_.end()) {
                continue;
            } else if (child.second.isDelta == false) {
                one[child.first].isDelta = false;
                one[child.first].offset = child.second.offset;
                one[child.first].length = child.second.length;
            }
        }
        for (auto child : dividermap_) {
            if (another.find(child.first) != another.end() && another[child.first].isDelta == true) {
                one[child.first].isDelta = true;
                one[child.first].offset = child.second.offset + another[child.first].offset;
                one[child.first].length = child.second.length + another[child.first].length;
            } else if (child.second.isDelta == true && another.find(child.first) == another.end()) {
                continue;
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
        DividerMap one;
        for (auto child : dividermap_) {
            if (another.find(child.first) != another.end() && another[child.first].isDelta == true) {
                one[child.first].isDelta = true;
                one[child.first].offset = child.second.offset - another[child.first].offset;
                one[child.first].length = child.second.length - another[child.first].length;
            } else {
                one[child.first].isDelta = false;
                one[child.first].offset = child.second.offset;
                one[child.first].length = child.second.length;
            }
        }
        return MakeRefPtr<ListDividerArithmetic>(one);
    }

    RefPtr<CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        DividerMap one;
        for (auto child : dividermap_) {
            if (child.second.isDelta == true) {
                one[child.first].isDelta = child.second.isDelta;
                one[child.first].offset = child.second.offset * scale;
                one[child.first].length = child.second.length * scale;
            } else {
                one[child.first].isDelta = child.second.isDelta;
                one[child.first].offset = child.second.offset;
                one[child.first].length = child.second.length;
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
                iterAnother->second.isDelta != iterOne->second.isDelta ||
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

private:
    DividerMap dividermap_;

    ACE_DISALLOW_COPY_AND_MOVE(ListDividerArithmetic);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DIVIDER_ARITHMETIC_H
