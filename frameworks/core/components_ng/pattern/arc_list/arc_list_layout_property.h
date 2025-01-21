/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_PROPERTY_H

#include "core/components_ng/pattern/list/list_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ArcListLayoutProperty : public ListLayoutProperty {
    DECLARE_ACE_TYPE(ArcListLayoutProperty, ListLayoutProperty);

public:
    ArcListLayoutProperty()
    {
        ResetArcListProperty();
    }

    ~ArcListLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ArcListLayoutProperty>();
        value->ListLayoutProperty::UpdateLayoutProperty(DynamicCast<ListLayoutProperty>(this));
        return value;
    }

    void Reset() override
    {
        ListLayoutProperty::Reset();
        ResetArcListProperty();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    void ScrollSnapPropToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

protected:
    void ResetArcListProperty()
    {
        propListDirection_ = Axis::VERTICAL;
        propListItemAlign_ = V2::ListItemAlign::CENTER;
        propScrollSnapAlign_ = ScrollSnapAlign::CENTER;
        propEditMode_ = false;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_LAYOUT_PROPERTY_H
