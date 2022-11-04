/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H

#include "base/utils/noncopyable.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
// PagePattern is the base class for page render node.
class LinearLayoutPattern : public Pattern {
    DECLARE_ACE_TYPE(LinearLayoutPattern, Pattern);

public:
    explicit LinearLayoutPattern(bool isVertical) : isVertical_(isVertical) {};
    ~LinearLayoutPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(isVertical_);
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { isVertical_, true, ScopeType::FLEX };
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        auto property = GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(property);
        static const char* HORIZONTALALIGN[] = { "HorizontalAlign.Start", "HorizontalAlign.Center",
            "HorizontalAlign.End" };
        static const char* VERTICALALIGN[] = { "VerticalAlign.Top", "VerticalAlign.Center", "VerticalAlign.Bottom" };
        json->Put("space", property->GetSpace().value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
        if (isVertical_) {
            json->Put("alignItems",
                HORIZONTALALIGN[static_cast<int32_t>(property->GetCrossAxisAlign().value_or(FlexAlign::FLEX_START))]);
        } else {
            json->Put("alignItems",
                VERTICALALIGN[static_cast<int32_t>(property->GetCrossAxisAlign().value_or(FlexAlign::FLEX_START))]);
        }
        std::string result = "";
        result = V2::ConvertFlexAlignToStirng(property->GetMainAxisAlign().value_or(FlexAlign::FLEX_START));
        json->Put("justifyContent", result.c_str());
    }

private:
    bool isVertical_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LinearLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H
