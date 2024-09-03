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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
constexpr Dimension PORTRAIT_BOTTOM_SECURITY = 96.0_vp;
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
        props->propIsModal_ = CloneIsModal();
        props->propDialogButtonDirection_ = CloneDialogButtonDirection();
        props->propWidth_ = CloneWidth();
        props->propHeight_ = CloneHeight();
        props->propEnableHoverMode_ = CloneEnableHoverMode();
        props->propHoverModeArea_ = CloneHoverModeArea();
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
        ResetIsModal();
        ResetWidth();
        ResetHeight();
        ResetEnableHoverMode();
        ResetHoverModeArea();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogAlignment, DialogAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogOffset, DimensionOffset, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GridCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseCustomStyle, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoCancel, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsModal, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsScenceBoardDialog, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogButtonDirection, DialogButtonDirection, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Width, CalcDimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Height, CalcDimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableHoverMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverModeArea, HoverModeAreaType, PROPERTY_UPDATE_MEASURE);
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("alignment", DialogAlignmentUtils::ConvertDialogAlignmentToString(
                                         propDialogAlignment_.value_or(DialogAlignment::BOTTOM))
                                         .c_str(), filter);

        auto offsetValue = JsonUtil::Create(true);
        offsetValue->Put("dX", propDialogOffset_.value_or(DimensionOffset()).GetX().Value());
        offsetValue->Put("dY", propDialogOffset_.value_or(DimensionOffset()).GetY().Value());
        json->PutExtAttr("offset", offsetValue, filter);

        json->PutExtAttr("gridCount", std::to_string(propGridCount_.value_or(-1)).c_str(), filter);
        json->PutExtAttr("customStyle", propUseCustomStyle_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("autoCancel", propAutoCancel_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("showInSubWindow", propShowInSubWindow_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("isModal", propIsModal_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("isScenceBoardDialog", propIsScenceBoardDialog_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("buttonDirection", DialogButtonDirectionUtils::ConvertDialogButtonDirectionToString(
                                         propDialogButtonDirection_.value_or(DialogButtonDirection::AUTO))
                                         .c_str(), filter);
        json->PutExtAttr("width", propWidth_.value_or(CalcDimension(Dimension(-1))).Value(), filter);
        json->PutExtAttr("height", propHeight_.value_or(CalcDimension(Dimension(-1))).Value(), filter);
        json->PutExtAttr("enableHoverMode", propEnableHoverMode_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("HoverModeAreaType", GetHoverModeAreaValue(HoverModeAreaType::BOTTOM_SCREEN) ==
            HoverModeAreaType::BOTTOM_SCREEN ? "BOTTOM_SCREEN" : "TOP_SCREEN", filter);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(DialogLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_PROPERTY_H
