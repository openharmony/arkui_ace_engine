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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
namespace OHOS::Ace::NG {

struct SwitchPaintParagraph {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SwitchPointColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CurrentOffset, float);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("selectedColor", propSelectedColor.value_or(Color()).ColorToString().c_str());
        json->Put("switchPointColor", propSwitchPointColor.value_or(Color()).ColorToString().c_str());
    }
};

struct SwitchAnimationStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Duration, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Curve, RefPtr<Curve>);
};

// PaintProperty are used to set paint properties.
class SwitchPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SwitchPaintProperty, PaintProperty)
public:
    SwitchPaintProperty() = default;
    ~SwitchPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<SwitchPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propSwitchPaintParagraph_ = CloneSwitchPaintParagraph();
        value->propIsOn_ = CloneIsOn();
        value->propSwitchAnimationStyle_ = CloneSwitchAnimationStyle();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetSwitchPaintParagraph();
        ResetIsOn();
        ResetSwitchAnimationStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        json->Put("type", "ToggleType.Switch");
        json->Put("isOn", propIsOn_.value_or(false) ? "true" : "false");
        ACE_PROPERTY_TO_JSON_VALUE(propSwitchPaintParagraph_, SwitchPaintParagraph);
    }

    ACE_DEFINE_PROPERTY_GROUP(SwitchAnimationStyle, SwitchAnimationStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchAnimationStyle, Duration, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchAnimationStyle, Curve, RefPtr<Curve>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(SwitchPaintParagraph, SwitchPaintParagraph);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SwitchPointColor, Color, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsOn, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H
