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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
enum class ToastShowMode {
    DEFAULT = 0,
    TOP_MOST = 1,
    SYSTEM_TOP_MOST = 2,
};
struct ToastInfo {
    std::string message;
    int32_t duration = 0;
    std::string bottom;
    bool isRightToLeft = false;
    ToastShowMode showMode = ToastShowMode::DEFAULT;
    int32_t alignment = 0;
    std::optional<DimensionOffset> offset;
    std::optional<Color> backgroundColor;
    std::optional<Color> textColor;
    std::optional<int32_t> backgroundBlurStyle;
    std::optional<Shadow> shadow;
    bool enableHoverMode = false;
    HoverModeAreaType hoverModeArea = HoverModeAreaType::BOTTOM_SCREEN;
    bool isTypeStyleShadow = true;
};
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
        props->propShowMode_ = CloneShowMode();
        props->propEnableHoverMode_ = CloneEnableHoverMode();
        props->propHoverModeArea_ = CloneHoverModeArea();
        return props;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBottom();
        ResetShowMode();
        ResetEnableHoverMode();
        ResetHoverModeArea();
    }

    enum class SelectStatus {
        OFF = 0,
        ON,
        NONE,
    };

    SelectStatus& GetSelectStatus()
    {
        return propStatus_;
    }

    void SetSelectStatus(const SelectStatus& status)
    {
        propStatus_ = status;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ToastAlignment, Alignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ToastOffset, DimensionOffset, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Bottom, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowMode, ToastShowMode, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableHoverMode, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverModeArea, HoverModeAreaType, PROPERTY_UPDATE_LAYOUT);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("Bottom", GetBottom()->ToString().c_str(), filter);
        json->PutExtAttr("ToastShowMode",
            GetShowModeValue(ToastShowMode::DEFAULT) == ToastShowMode::DEFAULT ? "DEFAULT" : "TOP_MOST", filter);
        if (HasToastAlignment()) {
            json->PutExtAttr("alignment", GetToastAlignmentValue(Alignment::BOTTOM_CENTER)
                .GetAlignmentStr(TextDirection::AUTO).c_str(), filter);
        }
        auto offsetValue = JsonUtil::Create(true);
        offsetValue->Put("dX", propToastOffset_.value_or(DimensionOffset()).GetX().ConvertToVp());
        offsetValue->Put("dY", propToastOffset_.value_or(DimensionOffset()).GetY().ConvertToVp());
        json->PutExtAttr("offset", offsetValue, filter);
        json->PutExtAttr("EnableHoverMode", propEnableHoverMode_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("HoverModeAreaType",
            GetHoverModeAreaValue(HoverModeAreaType::BOTTOM_SCREEN) ==
                HoverModeAreaType::BOTTOM_SCREEN ? "BOTTOM_SCREEN" : "TOP_SCREEN", filter);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ToastLayoutProperty);
    SelectStatus propStatus_ = SelectStatus::NONE;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TOAST_TOAST_LAYOUT_PROPERTY_H
