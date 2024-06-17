/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabsLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TabsLayoutProperty, LayoutProperty);

public:
    TabsLayoutProperty() = default;
    ~TabsLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TabsLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propTabBarPosition_ = CloneTabBarPosition();
        value->propAxis_ = CloneAxis();
        value->propTabBarMode_ = CloneTabBarMode();
        value->propDivider_ = CloneDivider();
        value->propBarWidth_ = CloneBarWidth();
        value->propBarHeight_ = CloneBarHeight();
        value->propIndex_ = CloneIndex();
        value->propBarOverlap_ = CloneBarOverlap();
        value->propWidthAuto_ = CloneWidthAuto();
        value->propHeightAuto_ = CloneHeightAuto();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetTabBarPosition();
        ResetAxis();
        ResetTabBarMode();
        ResetDivider();
        ResetBarWidth();
        ResetBarHeight();
        ResetIndex();
        ResetBarOverlap();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("vertical", propAxis_.value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL ?
            "false" : "true", filter);
        json->PutExtAttr("barPosition", propTabBarPosition_.value_or(BarPosition::START) == BarPosition::START
                                     ? "BarPosition.Start"
                                     : "BarPosition.End", filter);
        if (propDivider_.has_value()) {
            auto divider = JsonUtil::Create(true);
            if (!propDivider_.value().isNull) {
                divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
                divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
                divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
                divider->Put("color", propDivider_.value().color.ColorToString().c_str());
            } else {
                TabsItemDivider emptyDivider;
                emptyDivider.strokeWidth.Reset();
                emptyDivider.startMargin.Reset();
                emptyDivider.endMargin.Reset();
                divider->Put("strokeWidth", emptyDivider.strokeWidth.ToString().c_str());
                divider->Put("startMargin", emptyDivider.startMargin.ToString().c_str());
                divider->Put("endMargin", emptyDivider.endMargin.ToString().c_str());
                divider->Put("color", emptyDivider.color.ColorToString().c_str());
            }
            json->PutExtAttr("divider", divider, filter);
        } else {
            auto divider = JsonUtil::Create(true);
            json->PutExtAttr("divider", divider, filter);
        }
        json->PutExtAttr("barOverlap", propBarOverlap_.value_or(false) ? "true" : "false", filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        static const std::unordered_map<std::string, BarPosition> uMap {
            { "BarPosition.Start", BarPosition::START },
            { "BarPosition.End", BarPosition::END },
        };

        UpdateAxis(json->GetBool("vertical") ? Axis::VERTICAL : Axis::HORIZONTAL);
        auto barPosition = json->GetString("barPosition");
        BarPosition barPositionEnum = BarPosition::START;
        auto iter = uMap.find(barPosition);
        if (iter != uMap.end()) {
            barPositionEnum = iter->second;
        }
        UpdateTabBarPosition(barPositionEnum);
        LayoutProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TabBarPosition, BarPosition, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TabBarMode, TabBarMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, TabsItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BarHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BarOverlap, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(WidthAuto, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HeightAuto, bool, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_LAYOUT_PROPERTY_H
