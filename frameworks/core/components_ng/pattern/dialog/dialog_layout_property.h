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
        auto props = MakeRefPtr<DialogLayoutProperty>();
        props->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        props->propDialogAlignment_ = CloneDialogAlignment();
        props->propDialogOffset_ = CloneDialogOffset();
        props->propGridCount_ = CloneGridCount();
        props->propUseCustomStyle_ = CloneUseCustomStyle();
        props->propAutoCancel_ = CloneAutoCancel();
        props->propShowInSubWindow_ = CloneShowInSubWindow();
        props->propDialogButtonDirection_ = CloneDialogButtonDirection();
        return props;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDialogAlignment();
        ResetDialogOffset();
        ResetGridCount();
        ResetUseCustomStyle();
        ResetAutoCancel();
        ResetShowInSubWindow();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogAlignment, DialogAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogOffset, DimensionOffset, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GridCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseCustomStyle, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoCancel, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogButtonDirection, DialogButtonDirection, PROPERTY_UPDATE_MEASURE);

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
        json->Put("customStyle", propUseCustomStyle_.value_or(false) ? "true" : "false");
        json->Put("autoCancel", propAutoCancel_.value_or(true) ? "true" : "false");
        json->Put("showInSubWindow", propShowInSubWindow_.value_or(false) ? "true" : "false");
        json->Put("buttonDirection", DialogButtonDirectionUtils::ConvertDialogButtonDirectionToString(
                                         propDialogButtonDirection_.value_or(DialogButtonDirection::AUTO))
                                         .c_str());
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(DialogLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_PROPERTY_H