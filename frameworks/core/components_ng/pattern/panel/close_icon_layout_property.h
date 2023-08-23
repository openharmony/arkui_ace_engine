/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CloseIconLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(CloseIconLayoutProperty, LayoutProperty);

public:
    CloseIconLayoutProperty() = default;
    ~CloseIconLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<CloseIconLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propCloseIconWidth_ = CloneCloseIconWidth();
        value->propCloseIconHeight_ = CloneCloseIconHeight();
        value->propCloseIconMarginTop_ = CloneCloseIconMarginTop();
        value->propCloseIconMarginRight_ = CloneCloseIconMarginRight();
        value->propCloseIconRadius_ = CloneCloseIconRadius();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetCloseIconWidth();
        ResetCloseIconHeight();
        ResetCloseIconMarginTop();
        ResetCloseIconMarginRight();
        ResetCloseIconRadius();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CloseIconWidth, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CloseIconHeight, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CloseIconMarginTop, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CloseIconMarginRight, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CloseIconRadius, Dimension, PROPERTY_UPDATE_MEASURE_SELF);

private:
    ACE_DISALLOW_COPY_AND_MOVE(CloseIconLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_LAYOUT_PROPERTY_H
