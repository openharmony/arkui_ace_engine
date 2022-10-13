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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"
namespace OHOS::Ace::NG {
class SelectPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SelectPaintProperty, PaintProperty)

public:
    SelectPaintProperty() = default;

    ~SelectPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<SelectPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propSelectSelected_ = CloneSelectSelected();
        paintProperty->propSelectSelectedOptionBgColor_ = CloneSelectSelectedOptionBgColor();
        paintProperty->propSelectOptionBgColor_ = CloneSelectOptionBgColor();
        
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetSelectSelected();
        ResetSelectSelectedOptionBgColor();
        ResetSelectOptionBgColor();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectSelected, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectSelectedOptionBgColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectOptionBgColor, Color, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif