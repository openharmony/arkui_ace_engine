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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_PROPERTY_H

#include "linear_split_model.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LinearSplitLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(LinearSplitLayoutProperty, LayoutProperty);

public:
    LinearSplitLayoutProperty() = default;

    ~LinearSplitLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<LinearSplitLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propResizable_ = CloneResizable();
        value->propDivider_ = CloneDivider();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetResizable();
        ResetDivider();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("resizeable", propResizable_.value_or(false) ? "true" : "false", filter);
        if (propDivider_.has_value()) {
            auto divider = JsonUtil::Create(true);
            divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
            divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
            json->PutExtAttr("divider", divider, filter);
        } else {
            auto divider = JsonUtil::Create(true);
            json->PutExtAttr("divider", divider, filter);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Resizable, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, ItemDivider, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(LinearSplitLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_LAYOUT_PROPERTY_H
