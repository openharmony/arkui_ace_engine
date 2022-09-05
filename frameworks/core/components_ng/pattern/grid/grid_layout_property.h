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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(GridLayoutProperty, LayoutProperty);

public:
    GridLayoutProperty() = default;
    ~GridLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetColumnsTemplate();
        ResetRowsTemplate();
    }
    bool IsVertical() const
    {
        bool columnsTemplateValid = propColumnsTemplate_.has_value() && !propColumnsTemplate_.value().empty();
        bool rowsTemplateValid = propRowsTemplate_.has_value() && !propRowsTemplate_.value().empty();
        return columnsTemplateValid ||
               (!columnsTemplateValid && !rowsTemplateValid); // TODO: take layoutDirection into account
    }
    bool IsConfiguredScrollable() const
    {
        bool columnsTemplateSet = !propColumnsTemplate_.value_or("").empty();
        bool rowsTemplateSet = !propRowsTemplate_.value_or("").empty();
        bool verticalScrollable = (columnsTemplateSet && !rowsTemplateSet);
        bool horizontalScrollable = (!columnsTemplateSet && rowsTemplateSet);
        return verticalScrollable || horizontalScrollable;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnsTemplate, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RowsTemplate, std::string, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H
