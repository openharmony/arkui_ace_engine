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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set paint properties.
class ButtonPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ButtonPaintProperty, PaintProperty)

public:
    ButtonPaintProperty() = default;

    ~ButtonPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ButtonPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propStateEffect_ = CloneStateEffect();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetStateEffect();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StateEffect, bool, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_PAINT_PROPERTY_H
