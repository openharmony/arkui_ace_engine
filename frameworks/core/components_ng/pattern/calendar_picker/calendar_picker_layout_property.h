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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_LAYOUT_PROPERTY_H

#include <string>

#include "core/components/calendar/calendar_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CalendarPickerLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(CalendarPickerLayoutProperty, LinearLayoutProperty);

public:
    CalendarPickerLayoutProperty() : LinearLayoutProperty(false) {};
    ~CalendarPickerLayoutProperty() override = default;

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetDialogAlignType();
        ResetDialogOffset();
        ResetTextStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
        CHECK_NULL_VOID(calendarTheme);
        auto dialogALignType = GetDialogAlignType().value_or(CalendarEdgeAlign::EDGE_ALIGN_END);
        std::string alignType = "CalendarAlign.END";
        switch (dialogALignType) {
            case CalendarEdgeAlign::EDGE_ALIGN_START:
                alignType = "CalendarAlign.START";
                break;
            case CalendarEdgeAlign::EDGE_ALIGN_CENTER:
                alignType = "CalendarAlign.CENTER";
                break;
            default:
                break;
        }
        auto dialogOffset = GetDialogOffset().value_or(DimensionOffset());
        auto jsonDialogAlign = JsonUtil::Create(true);
        CHECK_NULL_VOID(jsonDialogAlign);
        jsonDialogAlign->Put("alignType", alignType.c_str());
        auto jsonOffset = JsonUtil::Create(true);
        CHECK_NULL_VOID(jsonOffset);
        jsonOffset->Put("dx", dialogOffset.GetX().ToString().c_str());
        jsonOffset->Put("dy", dialogOffset.GetY().ToString().c_str());
        jsonDialogAlign->Put("offset", jsonOffset);
        json->PutExtAttr("edgeAlign", jsonDialogAlign, filter);

        auto font = JsonUtil::Create(true);
        CHECK_NULL_VOID(font);
        font->Put("size", GetFontSize().value_or(calendarTheme->GetEntryFontSize()).ToString().c_str());
        font->Put("weight", V2::ConvertWrapFontWeightToStirng(GetWeight().value_or(FontWeight::NORMAL)).c_str());
        auto textStyle = JsonUtil::Create(true);
        CHECK_NULL_VOID(textStyle);
        textStyle->Put("color", GetColor().value_or(calendarTheme->GetEntryFontColor()).ColorToString().c_str());
        textStyle->Put("font", font);
        json->PutExtAttr("textStyle", textStyle, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogAlignType, CalendarEdgeAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DialogOffset, DimensionOffset, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(TextStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, FontSize, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, TextColor, Color, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, FontWeight, Weight, FontWeight, PROPERTY_UPDATE_MEASURE);

protected:
    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<CalendarPickerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propDialogAlignType_ = CloneDialogAlignType();
        value->propDialogOffset_ = CloneDialogOffset();
        value->propTextStyle_ = CloneTextStyle();
        return value;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(CalendarPickerLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_CALENDAR_PICKER_LAYOUT_PROPERTY_H
