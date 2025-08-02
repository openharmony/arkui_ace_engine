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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LinearLayoutProperty : public FlexLayoutProperty {
    DECLARE_ACE_TYPE(LinearLayoutProperty, FlexLayoutProperty);

public:
    explicit LinearLayoutProperty(bool isVertical) : isVertical_(isVertical)
    {
        UpdateFlexDirection(isVertical_ ? FlexDirection::COLUMN : FlexDirection::ROW);
    }

    ~LinearLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<LinearLayoutProperty>(isVertical_);
        Clone(value);
        return value;
    }

    void Reset() override
    {
        FlexLayoutProperty::Reset();
        isVertical_ = false;
    }

    void SetIsVertical(bool isVertical)
    {
        isVertical_ = isVertical;
    }

    bool IsVertical() const
    {
        return isVertical_;
    }

    std::pair<bool, bool> GetPercentSensitive() override
    {
        return LayoutProperty::GetPercentSensitive();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        std::string alignItems;
        auto flexAlignItems = GetCrossAxisAlign().value_or(FlexAlign::CENTER);
        if (isVertical_) {
            alignItems = "HorizontalAlign.Center";
            if (flexAlignItems == FlexAlign::FLEX_START) {
                alignItems = "HorizontalAlign.Start";
            } else if (flexAlignItems == FlexAlign::CENTER) {
                alignItems = "HorizontalAlign.Center";
            } else if (flexAlignItems == FlexAlign::FLEX_END) {
                alignItems = "HorizontalAlign.End";
            }
        } else {
            alignItems = "VerticalAlign.Center";
            if (flexAlignItems == FlexAlign::FLEX_START) {
                alignItems = "VerticalAlign.Top";
            } else if (flexAlignItems == FlexAlign::CENTER) {
                alignItems = "VerticalAlign.Center";
            } else if (flexAlignItems == FlexAlign::FLEX_END) {
                alignItems = "VerticalAlign.Bottom";
            }
        }
        json->PutExtAttr("space", GetSpaceValue(Dimension(0.0f)).ToString().c_str(), filter);
        json->PutExtAttr("alignItems", alignItems.c_str(), filter);
        auto justifyContent = V2::ConvertFlexAlignToStirng(GetMainAxisAlign().value_or(FlexAlign::FLEX_START));
        json->PutExtAttr("justifyContent", justifyContent.c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        static const std::unordered_map<std::string, FlexAlign> uMap {
            { "Start", FlexAlign::FLEX_START },
            { "Top", FlexAlign::FLEX_START },
            { "Center", FlexAlign::CENTER },
            { "End", FlexAlign::FLEX_END },
            { "Bottom", FlexAlign::FLEX_END },
        };

        UpdateSpace(Dimension::FromString(json->GetString("space")));
        auto alignItems = json->GetString("alignItems");
        auto pos = alignItems.find('.');
        if (pos != std::string::npos) {
            ++pos;
            alignItems = alignItems.substr(pos, alignItems.length() - pos);
            FlexAlign flexAlign = FlexAlign::CENTER;
            auto iter = uMap.find(alignItems);
            if (iter != uMap.end()) {
                flexAlign = iter->second;
            }
            UpdateCrossAxisAlign(flexAlign);
        }
        UpdateMainAxisAlign(V2::ConvertStringToFlexAlign(json->GetString("justifyContent")));

        LayoutProperty::FromJson(json);
    }

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<LinearLayoutProperty>(property);
        FlexLayoutProperty::Clone(value);
        value->isVertical_ = isVertical_;
    }

private:
    // This will call after ModifyLayoutConstraint.
    bool isVertical_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LinearLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
