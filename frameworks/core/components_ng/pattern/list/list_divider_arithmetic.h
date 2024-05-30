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
using ListDividerMap = std::map<int32_t, ListDivider>;

class RefDividerMap : public AceType {
    DECLARE_ACE_TYPE(RefDividerMap, AceType);
public:
    void SetMap(const ListDividerMap& map)
    {
        refMap_ = map;
        for (auto& div : refMap_) {
            div.second.isDelta = false;
        }
    }
    const ListDividerMap& GetMap() const
    {
        return  refMap_;
    }
private:
    ListDividerMap refMap_;
};

class ListDividerArithmetic : public CustomAnimatableArithmetic {
    DECLARE_ACE_TYPE(ListDividerArithmetic, CustomAnimatableArithmetic);
public:
    ListDividerArithmetic() = default;
    ~ListDividerArithmetic() override = default;
   
    ListDividerArithmetic(const ListDividerMap& dividerMap, RefPtr<RefDividerMap> ref)
        : dividermap_(dividerMap), refDivider_(ref) {}

    RefPtr<CustomAnimatableArithmetic> Add(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        return Calculate(value, true);
    }

    RefPtr<CustomAnimatableArithmetic> Minus(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        return Calculate(value, false);
    }

    RefPtr<CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        if (!refDivider_) {
            return {};
        }
        ListDividerMap result;
        for (const auto& child : refDivider_->GetMap()) {
            auto it = dividermap_.find(child.first);
            if (it == dividermap_.end() || !it->second.isDelta) {
                result.emplace(child.first, child.second);
                continue;
            }
            ListDivider divider = {
                .isDelta = true,
                .offset = it->second.offset * scale,
                .length = it->second.length * scale,
            };
            result.emplace(child.first, divider);
        }
        return MakeRefPtr<ListDividerArithmetic>(result, refDivider_);
    }

    bool IsEqual(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<ListDividerArithmetic> rhs = AceType::DynamicCast<ListDividerArithmetic>(value);
        if (!rhs) {
            return false;
        }
        const ListDividerMap& another = rhs->GetDividerMap();
        if (another.size() != dividermap_.size()) {
            return false;
        }
        for (const auto& child : dividermap_) {
            auto it = another.find(child.first);
            if (it == another.end() || it->second.offset != child.second.offset ||
                it->second.length != child.second.length) {
                return false;
            }
        }
        return true;
    }

    ListDividerMap GetDividerMap() const
    {
        return dividermap_;
    }

private:
    RefPtr<CustomAnimatableArithmetic> Calculate(const RefPtr<CustomAnimatableArithmetic>& value, bool isAdd) const
    {
        if (!refDivider_) {
            return {};
        }
        RefPtr<ListDividerArithmetic> rhs = AceType::DynamicCast<ListDividerArithmetic>(value);
        if (!rhs) {
            return {};
        }
        const ListDividerMap& another = rhs->GetDividerMap();
        ListDividerMap result;
        for (const auto& child : refDivider_->GetMap()) {
            auto it1 = dividermap_.find(child.first);
            if (it1 == dividermap_.end() || !it1->second.isDelta) {
                result.emplace(child.first, child.second);
                continue;
            }
            auto it2 = another.find(child.first);
            if (it2 == another.end() || !it2->second.isDelta) {
                result.emplace(child.first, child.second);
                continue;
            }
            if (isAdd) {
                ListDivider divider = {
                    .isDelta = true,
                    .offset = it1->second.offset + it2->second.offset,
                    .length = it1->second.length + it2->second.length,
                };
                result.emplace(child.first, divider);
            } else {
                ListDivider divider = {
                    .isDelta = true,
                    .offset = it1->second.offset - it2->second.offset,
                    .length = it1->second.length - it2->second.length,
                };
                result.emplace(child.first, divider);
            }
        }
        return MakeRefPtr<ListDividerArithmetic>(result, refDivider_);
    }
    ListDividerMap dividermap_;
    RefPtr<RefDividerMap> refDivider_;

    ACE_DISALLOW_COPY_AND_MOVE(ListDividerArithmetic);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_DIVIDER_ARITHMETIC_H
