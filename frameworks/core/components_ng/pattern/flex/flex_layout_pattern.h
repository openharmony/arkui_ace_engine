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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PATTERN_H

#include <string>

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class FlexLayoutPattern : public Pattern {
    DECLARE_ACE_TYPE(FlexLayoutPattern, Pattern);

public:
    FlexLayoutPattern() = default;
    explicit FlexLayoutPattern(bool wrap) : isWrap_(wrap) {};
    ~FlexLayoutPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<FlexLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        if (isWrap_) {
            return MakeRefPtr<WrapLayoutAlgorithm>(isDialogStretch_);
        }
        return MakeRefPtr<FlexLayoutAlgorithm>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        auto property = GetLayoutProperty<FlexLayoutProperty>();
        if (!property) {
            return {};
        }
        bool isVertical = true;
        if (property->GetFlexDirection().has_value()) {
            isVertical = property->GetFlexDirection().value() == FlexDirection::COLUMN ||
                         property->GetFlexDirection().value() == FlexDirection::COLUMN_REVERSE;
        }
        return { isVertical, true, ScopeType::FLEX };
    }

    void SetDialogStretch(bool stretch)
    {
        isDialogStretch_ = stretch;
    }

    void DumpInfo() override
    {
        DumpLog::GetInstance().AddDesc(std::string("Type: ").append(isWrap_ ? "Wrap" : "NoWrap"));
    }

    bool GetIsWrap() const
    {
        return isWrap_;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        auto property = GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(property);
        static const char* FLEXDIRECTION[] = { "FlexDirection.ROW", "FlexDirection.COLUMN", "FlexDirection.ROW_REVERSE",
            "FlexDirection.COLUMN_REVERSE" };
        static const char* FLEXALIGN[] = { "FlexAlign.AUTO", "FlexAlign.FLEX_START", "FlexAlign.CENTER",
            "FlexAlign.FLEX_END", "FlexAlign.STRETCH", "FlexAlign.BASELINE", "FlexAlign.SPACE_BETWEEN",
            "FlexAlign.SPACE_AROUND", "FlexAlign.SPACE_EVENLY", "FlexAlign.SPACE_CUSTOMIZATION" };
        if (!isWrap_) {
            json->Put("direction",
                FLEXDIRECTION[static_cast<int32_t>(property->GetFlexDirection().value_or(FlexDirection::ROW))]);
            json->Put("wrap", "FlexWrap.NoWrap");
            json->Put("justifyContent",
                FLEXALIGN[static_cast<int32_t>(property->GetMainAxisAlign().value_or(FlexAlign::FLEX_START))]);
            json->Put("alignItems",
                FLEXALIGN[static_cast<int32_t>(property->GetCrossAxisAlign().value_or(FlexAlign::FLEX_START))]);
            json->Put("alignContent", "FlexAlign.FLEX_START");
            return;
        }

        auto direction = property->GetFlexDirection().value_or(FlexDirection::ROW);
        json->Put("direction", FLEXDIRECTION[static_cast<int32_t>(direction)]);
        auto wrapDirection = property->GetWrapDirection().value_or(WrapDirection::HORIZONTAL);
        if (static_cast<int32_t>(direction) <= 1) {
            auto wrap = (static_cast<int32_t>(wrapDirection) - static_cast<int32_t>(direction)) / 2 + 1;
            json->Put("wrap", wrap == 1 ? "FlexWrap.Wrap" : "FlexWrap.WrapReverse");
        } else {
            auto wrap = (static_cast<int32_t>(wrapDirection) + static_cast<int32_t>(direction)) / 2 + 1;
            json->Put("wrap", wrap == 1 ? "FlexWrap.Wrap" : "FlexWrap.WrapReverse");
        }
        static const char* WRAPALIGNMENT[] = { "WrapAlignment.START", "WrapAlignment.CENTER", "WrapAlignment.END",
            "WrapAlignment.SPACE_AROUND", "WrapAlignment.SPACE_BETWEEN", "WrapAlignment.STRETCH",
            "WrapAlignment.SPACE_EVENLY", "WrapAlignment.BASELINE" };
        json->Put("justifyContent",
            WRAPALIGNMENT[static_cast<int32_t>(property->GetMainAlignment().value_or(WrapAlignment::START))]);
        json->Put("alignItems",
            WRAPALIGNMENT[static_cast<int32_t>(property->GetCrossAlignment().value_or(WrapAlignment::START))]);
        json->Put("alignContent",
            WRAPALIGNMENT[static_cast<int32_t>(property->GetAlignment().value_or(WrapAlignment::START))]);
    }

private:
    bool isWrap_ = false;
    bool isDialogStretch_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PATTERN_H
