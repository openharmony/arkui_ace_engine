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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_PROPERTY_H

#include "base/geometry/dimension_offset.h"
#include "base/geometry/offset.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DialogLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(DialogLayoutProperty, LayoutProperty);

public:
    DialogLayoutProperty() = default;
    ~DialogLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DialogLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDialogAlignment_ = CloneDialogAlignment();
        value->propDialogOffset_ = CloneDialogOffset();
        value->propGridCount_ = CloneGridCount();
        value->propUseCustom_ = CloneUseCustom();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDialogAlignment();
        ResetDialogOffset();
        ResetGridCount();
        ResetUseCustom();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogAlignment, DialogAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogOffset, DimensionOffset, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GridCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseCustom, bool, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        json->Put("alignment", DialogAlignmentUtils::ConvertDialogAlignmentToString(
                                         propDialogAlignment_.value_or(DialogAlignment::BOTTOM))
                                         .c_str());

        auto offsetValue = JsonUtil::Create(true);
        offsetValue->Put("dX", propDialogOffset_.value_or(DimensionOffset()).GetX().Value());
        offsetValue->Put("dY", propDialogOffset_.value_or(DimensionOffset()).GetY().Value());
        json->Put("offset", offsetValue);

        json->Put("gridCount", std::to_string(propGridCount_.value_or(-1)).c_str());
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(DialogLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_PROPERTY_H