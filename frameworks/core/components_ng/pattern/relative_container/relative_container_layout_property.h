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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

using AlignRulesItem = std::map<AlignDirection, AlignRule>;

class ACE_EXPORT RelativeContainerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(RelativeContainerLayoutProperty, LayoutProperty);

public:
    RelativeContainerLayoutProperty() = default;

    ~RelativeContainerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<RelativeContainerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propBarrier_ = CloneBarrier();
        value->propGuideline_ = CloneGuideline();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBarrier();
        ResetGuideline();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Barrier, std::vector<BarrierInfo>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Guideline, std::vector<GuidelineInfo>, PROPERTY_UPDATE_MEASURE);
    
    std::unique_ptr<OHOS::Ace::JsonValue> GuidelineInfoToJsonObject(GuidelineInfo& info) const
    {
        auto json = JsonUtil::Create(true);
        json->Put("id", info.id.c_str());
        std::string direction;
        if (info.direction == LineDirection::VERTICAL) {
            direction = "Axis.Vertical";
        }
        if (info.direction == LineDirection::HORIZONTAL) {
            direction = "Axis.Horizontal";
        }
        json->Put("direction", direction.c_str());
        auto jsonPos = JsonUtil::Create(true);
        jsonPos->Put("start", info.start->ToString().c_str());
        jsonPos->Put("end", info.end->ToString().c_str());
        json->Put("position", jsonPos);

        return json;
    }

    std::unique_ptr<OHOS::Ace::JsonValue> GuidelineToJsonObject() const
    {
        auto array = JsonUtil::CreateArray();
        if (!HasGuideline()) {
            return array;
        }
        auto value = GetGuidelineValue();
        for (int i = 0; i < value.size(); i++)
        {
            array->Put(GuidelineInfoToJsonObject(value[i]));
        }
        return array;
    }

    std::string BarrierDirectionToString(BarrierDirection value) const
    {
        switch (value)
        {
            case BarrierDirection::LEFT: return "BarrierDirection.LEFT";
            case BarrierDirection::RIGHT: return "BarrierDirection.RIGHT";
            case BarrierDirection::TOP: return "BarrierDirection.TOP";
            case BarrierDirection::BOTTOM: return "BarrierDirection.BOTTOM";
            case BarrierDirection::START: return "BarrierDirection.START";
            case BarrierDirection::END: return "BarrierDirection.END";
        }
    }

    std::unique_ptr<OHOS::Ace::JsonValue> BarrierInfoToJsonObject(const BarrierInfo& info) const
    {
        auto json = JsonUtil::Create(true);
        json->Put("id", info.id.c_str());
        json->Put("direction", BarrierDirectionToString(info.direction).c_str());
        auto array = JsonUtil::CreateArray();
        for (int i = 0; i < info.referencedId.size(); i++) {
            array->Put(std::to_string(i).c_str(), info.referencedId[i].c_str());
        }
        json->Put("referencedId", array);
        return json;
    }

    std::unique_ptr<OHOS::Ace::JsonValue> BarrierToJsonObject() const
    {
        auto array = JsonUtil::CreateArray();
        if (!HasBarrier()) {
            return array;
        }
        auto value = GetBarrierValue();
        for (int i = 0; i < value.size(); i++) {
            array->Put(BarrierInfoToJsonObject(value[i]));
        }
        return array;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->Put("barrier", BarrierToJsonObject());
        json->Put("guideLine", GuidelineToJsonObject());
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H
