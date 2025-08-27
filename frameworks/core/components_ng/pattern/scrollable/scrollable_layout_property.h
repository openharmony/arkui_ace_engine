/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT ScrollableLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ScrollableLayoutProperty, LayoutProperty);

public:
    ScrollableLayoutProperty() = default;
    ~ScrollableLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ScrollableLayoutProperty>();
        Clone(value);
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetContentStartOffset();
        ResetContentEndOffset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ContentStartOffset, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ContentEndOffset, float, PROPERTY_UPDATE_MEASURE);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = MakeRefPtr<ScrollableLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propContentStartOffset_ = CloneContentStartOffset();
        value->propContentEndOffset_ = CloneContentEndOffset();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ScrollableLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_LAYOUT_PROPERTY_H
