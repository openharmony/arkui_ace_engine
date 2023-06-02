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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOAST_TOAST_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOAST_TOAST_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ToastLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ToastLayoutProperty, LayoutProperty);

public:
    ToastLayoutProperty() = default;
    ~ToastLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto props = MakeRefPtr<ToastLayoutProperty>();
        props->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        props->propBottom_ = CloneBottom();
        return props;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBottom();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Bottom, Dimension, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        json->Put("Bottom", GetBottom()->ToString().c_str());
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ToastLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOAST_TOAST_LAYOUT_PROPERTY_H
