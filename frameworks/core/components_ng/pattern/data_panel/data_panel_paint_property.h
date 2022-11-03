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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class DataPanelPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(DataPanelPaintProperty, PaintProperty)

public:
    DataPanelPaintProperty() = default;
    ~DataPanelPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<DataPanelPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propValues_ = CloneValues();
        paintProperty->propMax_ = CloneMax();
        paintProperty->propDataPanelType_ = CloneDataPanelType();
        paintProperty->propEffect_ = CloneEffect();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetValues();
        ResetMax();
        ResetDataPanelType();
        ResetEffect();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        auto jsonDashArray = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < propValues_.value().size(); ++i) {
            auto index = std::to_string(i);
            double value = propValues_.value()[i];
            jsonDashArray->Put(index.c_str(), value);
        }
        bool closeEffect = true;
        if (propEffect_.has_value()) {
            closeEffect = !propEffect_.value();
        }
        json->Put("max", std::to_string(propMax_.value_or(100)).c_str());
        json->Put("closeEffect", closeEffect ? "true" : "false");
        json->Put("type", propDataPanelType_ == 1 ? "DataPanelType.Line" : "DataPanelType.Circle");
        json->Put("values", jsonDashArray);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<double>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Max, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DataPanelType, size_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Effect, bool, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(DataPanelPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H
