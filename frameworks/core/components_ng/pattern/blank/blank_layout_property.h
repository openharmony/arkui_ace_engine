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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BLANK_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BLANK_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BlankLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(BlankLayoutProperty, LayoutProperty);

public:
    BlankLayoutProperty() = default;

    ~BlankLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<BlankLayoutProperty>();
        copy->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        copy->propMinSize_ = CloneMinSize();
        copy->propHeight_ = CloneHeight();
        return copy;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetMinSize();
        ResetHeight();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinSize, Dimension, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Height, Dimension, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("min", GetMinSizeValue(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("height", GetHeightValue(Dimension()).ToString().c_str(), filter);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(BlankLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BLANK_LAYOUT_PROPERTY_H
