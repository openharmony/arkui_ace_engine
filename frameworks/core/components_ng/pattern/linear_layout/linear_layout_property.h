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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_styles.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LinearLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(LinearLayoutProperty, LayoutProperty);

public:
    explicit LinearLayoutProperty(bool isVertical) : isVertical_(isVertical) {}

    ~LinearLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<LinearLayoutProperty>(isVertical_);
        Clone(value);
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        isVertical_ = false;
        ResetLinearLayoutAttribute();
    }

    ACE_DEFINE_PROPERTY_GROUP(LinearLayoutAttribute, LinearLayoutAttribute)

    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LinearLayoutAttribute, CrossAxisAlign, FlexAlign, PROPERTY_UPDATE_LAYOUT);

    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LinearLayoutAttribute, MainAxisAlign, FlexAlign, PROPERTY_UPDATE_LAYOUT);

    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(LinearLayoutAttribute, Space, Dimension, PROPERTY_UPDATE_MEASURE);

    bool IsVertical() const
    {
        return isVertical_;
    }

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<LinearLayoutProperty>(property);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propLinearLayoutAttribute_ = CloneLinearLayoutAttribute();
        value->isVertical_ = isVertical_;
    }

private:
    // This will call after ModifyLayoutConstraint.
    bool isVertical_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LinearLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
