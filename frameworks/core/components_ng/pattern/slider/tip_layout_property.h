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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_TIP_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_TIP_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TipLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TipLayoutProperty, LayoutProperty);

public:
    TipLayoutProperty() = default;
    ~TipLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TipLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDirection_ = CloneDirection();
        value->propPadding_ = ClonePadding();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDirection();
        ResetPadding();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, Axis, PROPERTY_UPDATE_MEASURE)
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Padding, Dimension, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(TipLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_TIP_LAYOUT_PROPERTY_H
