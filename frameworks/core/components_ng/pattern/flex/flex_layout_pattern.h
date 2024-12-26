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
#include "core/components_ng/base/inspector_filter.h"
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

    bool IsNeedPercent() const override
    {
        return true;
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
        bool isVertical = false;
        if (property->GetFlexDirection().has_value()) {
            isVertical = property->GetFlexDirection().value() == FlexDirection::COLUMN ||
                         property->GetFlexDirection().value() == FlexDirection::COLUMN_REVERSE;
        }
        return { isVertical, true, isWrap_ ? ScopeType::PROJECT_AREA : ScopeType::FLEX };
    }

    void SetDialogStretch(bool stretch)
    {
        isDialogStretch_ = stretch;
    }

    void DumpInfo() override
    {
        DumpLog::GetInstance().AddDesc(std::string("Type: ").append(isWrap_ ? "Wrap" : "NoWrap"));
        DumpLog::GetInstance().AddDesc(std::string("FlexMeasureLayoutPaired: ")
                                           .append(std::to_string(static_cast<int>(GetMeasureLayoutPaired())).c_str()));
        DumpLog::GetInstance().AddDesc(std::string("FlexFrontSpace: ")
                                           .append(std::to_string(layoutResult_.frontSpace).c_str())
                                           .append(std::string(" FlexBetweenSpace: "))
                                           .append(std::to_string(layoutResult_.betweenSpace).c_str()));
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = DynamicCast<FlexLayoutProperty>(host->GetLayoutProperty());
        CHECK_NULL_VOID(layoutProperty);
        auto space = layoutProperty->GetSpace();
        if (space.has_value()) {
            DumpLog::GetInstance().AddDesc(std::string("space: ").append(space.value().ToString().c_str()));
        }
    }

    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override
    {
        json->Put("Type", isWrap_ ? "Wrap" : "NoWrap");
        json->Put("FlexMeasureLayoutPaired", GetMeasureLayoutPaired());
        json->Put("FlexFrontSpace", static_cast<double>(layoutResult_.frontSpace));
        json->Put("FlexBetweenSpace", static_cast<double>(layoutResult_.betweenSpace));
    }

    bool GetIsWrap() const
    {
        return isWrap_;
    }

    void SetIsWrap(bool isWrap)
    {
        isWrap_ = isWrap;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto property = GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(property);
        auto jsonConstructor = JsonUtil::Create(true);
        auto direction = property->GetFlexDirection().value_or(FlexDirection::ROW);
        jsonConstructor->Put("direction", V2::ConvertFlexDirectionToStirng(direction).c_str());
        if (!isWrap_) {
            jsonConstructor->Put("wrap", "FlexWrap.NoWrap");
            jsonConstructor->Put("justifyContent",
                V2::ConvertFlexAlignToStirng(property->GetMainAxisAlign().value_or(FlexAlign::FLEX_START)).c_str());
            jsonConstructor->Put("alignItems",
                V2::ConvertItemAlignToStirng(property->GetCrossAxisAlign().value_or(FlexAlign::FLEX_START)).c_str());
            jsonConstructor->Put("alignContent", "FlexAlign.Start");
        } else {
            auto wrapDirection = property->GetWrapDirection().value_or(WrapDirection::HORIZONTAL);
            if (static_cast<int32_t>(direction) <= 1) {
                auto wrap = (static_cast<int32_t>(wrapDirection) - static_cast<int32_t>(direction)) / 2 + 1;
                jsonConstructor->Put("wrap", wrap == 1 ? "FlexWrap.Wrap" : "FlexWrap.WrapReverse");
            } else {
                auto wrap = (static_cast<int32_t>(wrapDirection) + static_cast<int32_t>(direction)) / 2 + 1;
                jsonConstructor->Put("wrap", wrap == 1 ? "FlexWrap.Wrap" : "FlexWrap.WrapReverse");
            }
            jsonConstructor->Put("justifyContent",
                V2::ConvertWrapAlignmentToStirng(property->GetMainAlignment().value_or(WrapAlignment::START)).c_str());
            jsonConstructor->Put("alignItems",
                V2::ConvertItemAlignToStirng(property->GetCrossAlignment().value_or(WrapAlignment::START)).c_str());
            jsonConstructor->Put("alignContent",
                V2::ConvertWrapAlignmentToStirng(property->GetAlignment().value_or(WrapAlignment::START)).c_str());
        }
        json->PutExtAttr("constructor", jsonConstructor, filter);
        json->PutExtAttr("space", SpaceToString().c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        auto property = GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_VOID(property);
        if (json->Contains("constructor")) {
            auto constructor = json->GetValue("constructor");
            property->UpdateFlexDirection(V2::ConvertStringToFlexDirection(constructor->GetString("direction")));
            property->UpdateMainAxisAlign(V2::ConvertStringToFlexAlign(constructor->GetString("justifyContent")));
            property->UpdateCrossAxisAlign(V2::ConvertStringToFlexAlign(constructor->GetString("alignItems")));
            if (constructor->GetString("wrap") == "FlexWrap.NoWrap") {
                SetIsWrap(false);
                property->UpdateMainAxisAlign(V2::ConvertStringToFlexAlign(constructor->GetString("justifyContent")));
                property->UpdateCrossAxisAlign(V2::ConvertStringToItemAlign(constructor->GetString("alignItems")));
            }
        }
        Pattern::FromJson(json);
    }

    std::string SpaceToString() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, Dimension().ToString());
        auto layoutProperty = host->GetLayoutProperty<FlexLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, Dimension().ToString());
        return layoutProperty->GetSpaceValue(Dimension()).ToString();
    }

    void SetFlexMeasureResult(FlexMeasureResult measureResult, uintptr_t addr)
    {
        measureResult_ = measureResult;
        measuredAddress_ = addr;
    }

    FlexMeasureResult GetFlexMeasureResult()
    {
        return measureResult_;
    }

    void SetFlexLayoutResult(FlexLayoutResult layoutResult, uintptr_t addr)
    {
        layoutResult_ = layoutResult;
        layoutedAddress_ = addr;
    }

    bool GetMeasureLayoutPaired()
    {
        return (measuredAddress_ && layoutedAddress_ && (measuredAddress_.value() == layoutedAddress_.value()));
    }

private:
    bool isWrap_ = false;
    bool isDialogStretch_ = false;
    FlexMeasureResult measureResult_;
    FlexLayoutResult layoutResult_;
    std::optional<uintptr_t> measuredAddress_;
    std::optional<uintptr_t> layoutedAddress_;

    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PATTERN_H
