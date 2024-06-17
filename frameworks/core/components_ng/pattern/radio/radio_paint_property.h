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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RADIO_RADIO_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RADIO_RADIO_PAINT_PROPERTY_H

#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class RadioPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(RadioPaintProperty, PaintProperty)

public:
    RadioPaintProperty() = default;
    ~RadioPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<RadioPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propRadioCheck_ = CloneRadioCheck();
        paintProperty->propRadioCheckedBackgroundColor_ = CloneRadioCheckedBackgroundColor();
        paintProperty->propRadioUncheckedBorderColor_ = CloneRadioUncheckedBorderColor();
        paintProperty->propRadioIndicatorColor_ = CloneRadioIndicatorColor();
        paintProperty->propRadioIndicator_ = CloneRadioIndicator();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetRadioCheck();
        ResetRadioCheckedBackgroundColor();
        ResetRadioUncheckedBorderColor();
        ResetRadioIndicatorColor();
        ResetRadioIndicator();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto radioTheme = pipeline->GetTheme<RadioTheme>();
        json->PutExtAttr("checked", GetRadioCheck().value_or(false) ? "true" : "false", filter);
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("checkedBackgroundColor",
            GetRadioCheckedBackgroundColor().value_or(radioTheme->GetActiveColor()).ColorToString().c_str());
        jsonValue->Put("uncheckedBorderColor",
            GetRadioUncheckedBorderColor().value_or(radioTheme->GetInactiveColor()).ColorToString().c_str());
        jsonValue->Put(
            "indicatorColor", GetRadioIndicatorColor().value_or(radioTheme->GetPointColor()).ColorToString().c_str());
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            static const char* INDICATRO_TYPE[] = { "TICK", "DOT", "CUSTOM" };
            json->PutExtAttr("indicatorType",
                INDICATRO_TYPE[static_cast<int32_t>(GetRadioIndicator().value_or(0))], filter);
        }
        json->PutExtAttr("radioStyle", jsonValue->ToString().c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RadioCheck, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RadioCheckedBackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RadioUncheckedBorderColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RadioIndicatorColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RadioIndicator, int32_t, PROPERTY_UPDATE_RENDER);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RADIO_RADIO_PAINT_PROPERTY_H
