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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_LAYOUT_PROPERTY_H

#include "core/common/container.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DividerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(DividerLayoutProperty, LayoutProperty);

public:
    DividerLayoutProperty() = default;
    ~DividerLayoutProperty() override = default;
    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DividerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propVertical_ = CloneVertical();
        value->propStrokeWidth_ = CloneStrokeWidth();
        value->propStrokeWidthLimitation_ = CloneStrokeWidthLimitation();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetVertical();
        ResetStrokeWidth();
        ResetStrokeWidthLimitation();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("vertical", propVertical_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("strokeWidth",
            propStrokeWidth_
                .value_or(
                    Dimension(1, Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) ? DimensionUnit::PX
                                                                                                 : DimensionUnit::VP))
                .ToString()
                .c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UpdateVertical(json->GetString("vertical") == "true");
        UpdateStrokeWidth(Dimension::FromString(json->GetString("strokeWidth")));
        LayoutProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Vertical, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidthLimitation, bool, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(DividerLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_LAYOUT_PROPERTY_H
