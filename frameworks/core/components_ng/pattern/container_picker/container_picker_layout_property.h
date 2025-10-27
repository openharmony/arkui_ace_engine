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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {

enum class PickerIndicatorType {
    BACKGROUND = 0,
    DIVIDER
};

struct PickerIndicatorStyle {
    int32_t type;
    std::optional<Dimension> strokeWidth;
    std::optional<Color> dividerColor;
    std::optional<Dimension> startMargin;
    std::optional<Dimension> endMargin;
    std::optional<Color> backgroundColor;
    std::optional<BorderRadiusProperty> borderRadius;
    bool isDefaultDividerWidth = true;
    bool isDefaultDividerColor = true;
    bool isDefaultStartMargin = true;
    bool isDefaultEndMargin = true;
    bool isDefaultBackgroundColor = true;
    bool isDefaultBorderRadius = true;
    RefPtr<ResourceObject> borderRadiusResObj;
};

class ACE_EXPORT ContainerPickerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ContainerPickerLayoutProperty, LayoutProperty);
public:
    ContainerPickerLayoutProperty() = default;
    ~ContainerPickerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ContainerPickerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propCanLoop_ = CloneCanLoop();
        value->propEnableHapticFeedback_ = CloneEnableHapticFeedback();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetCanLoop();
        ResetEnableHapticFeedback();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        json->PutExtAttr("canLoop", V2::ConvertBoolToString(GetCanLoopValue(true)).c_str(), filter);
        json->PutExtAttr(
            "enableHapticFeedback", V2::ConvertBoolToString(GetEnableHapticFeedbackValue(true)).c_str(), filter);
        
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto pickerTheme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_VOID(pickerTheme);
        Dimension defaultDividerWidth = pickerTheme->GetDividerThickness();
        Color defaultDividerColor = pickerTheme->GetDividerColor();
        Color defaultIndicatorBackgroundColor = pickerTheme->GetSelectedBackgroundColor();
        Dimension defaultIndicatorBorderRadius = 12.0_vp;

        auto pickerIndicatorStyle = JsonUtil::Create(true);
        pickerIndicatorStyle->Put("type", std::to_string(GetIndicatorType().value_or(0)).c_str());
        pickerIndicatorStyle->Put("strokeWidth",
            GetIndicatorDividerWidth().value_or(defaultDividerWidth).ToString().c_str());
        pickerIndicatorStyle->Put("dividerColor",
            GetIndicatorDividerColor().value_or(defaultDividerColor).ColorToString().c_str());
        pickerIndicatorStyle->Put("startMargin", GetIndicatorStartMargin().value_or(Dimension()).ToString().c_str());
        pickerIndicatorStyle->Put("endMargin", GetIndicatorEndMargin().value_or(Dimension()).ToString().c_str());
        pickerIndicatorStyle->Put("backgroundColor",
            GetIndicatorBackgroundColor().value_or(defaultIndicatorBackgroundColor).ColorToString().c_str());
        pickerIndicatorStyle->Put("borderRadius", GetIndicatorBorderRadius().value_or(
            BorderRadiusProperty(defaultIndicatorBorderRadius)).ToString().c_str());
        json->PutExtAttr("pickerIndicatorStyle", pickerIndicatorStyle, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedIndex, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CanLoop, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableHapticFeedback, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorType, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorDividerWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorDividerColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorStartMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorEndMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorBackgroundColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorBorderRadius, BorderRadiusProperty, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_LAYOUT_PROPERTY_H
