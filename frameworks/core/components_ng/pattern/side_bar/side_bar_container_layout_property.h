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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_PROPERTY_H

#include <string>

#include "core/components/declaration/button/button_declaration.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {

struct ControlButtonStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonLeft, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonTop, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonShowIconStr, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonHiddenIconStr, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ControlButtonSwitchingIconStr, std::string);
};

class ACE_EXPORT SideBarContainerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SideBarContainerLayoutProperty, LayoutProperty);

public:
    SideBarContainerLayoutProperty() = default;
    ~SideBarContainerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SideBarContainerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propSideBarContainerType_ = CloneSideBarContainerType();
        value->propShowSideBar_ = CloneShowSideBar();
        value->propShowControlButton_ = CloneShowControlButton();
        value->propSideBarWidth_ = CloneSideBarWidth();
        value->propMinSideBarWidth_ = CloneMinSideBarWidth();
        value->propMaxSideBarWidth_ = CloneMaxSideBarWidth();
        value->propAutoHide_ = CloneAutoHide();
        value->propSideBarPosition_ = CloneSideBarPosition();
        value->propControlButtonStyle_ = CloneControlButtonStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSideBarContainerType();
        ResetShowSideBar();
        ResetShowControlButton();
        ResetSideBarWidth();
        ResetMinSideBarWidth();
        ResetMaxSideBarWidth();
        ResetAutoHide();
        ResetSideBarPosition();
        ResetControlButtonStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);

        constexpr Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
        constexpr Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
        constexpr Dimension DEFAULT_CONTROL_BUTTON_LEFT = 16.0_vp;
        constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
        constexpr Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
        constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
        constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;

        auto left = propControlButtonStyle_->propControlButtonLeft.value_or(DEFAULT_CONTROL_BUTTON_LEFT);
        auto top = propControlButtonStyle_->propControlButtonTop.value_or(DEFAULT_CONTROL_BUTTON_TOP);
        auto width = propControlButtonStyle_->propControlButtonWidth.value_or(DEFAULT_CONTROL_BUTTON_WIDTH);
        auto height = propControlButtonStyle_->propControlButtonHeight.value_or(DEFAULT_CONTROL_BUTTON_HEIGHT);
        auto type = propSideBarContainerType_.value_or(SideBarContainerType::EMBED);
        auto sideBarWidth = propSideBarWidth_.value_or(DEFAULT_SIDE_BAR_WIDTH);
        auto minSideBarWidth = propMinSideBarWidth_.value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
        auto maxSideBarWidth = propMaxSideBarWidth_.value_or(DEFAULT_MAX_SIDE_BAR_WIDTH);
        auto sideBarPosition = propSideBarPosition_.value_or(SideBarPosition::START);

        auto jsonControl = JsonUtil::Create(true);
        jsonControl->Put("left", std::to_string(left.Value()).c_str());
        jsonControl->Put("top", std::to_string(top.Value()).c_str());
        jsonControl->Put("width", std::to_string(width.Value()).c_str());
        jsonControl->Put("height", std::to_string(height.Value()).c_str());

        auto jsonIcon = JsonUtil::Create(true);
        jsonIcon->Put("shown", propControlButtonStyle_->propControlButtonShowIconStr->c_str());
        jsonIcon->Put("hidden", propControlButtonStyle_->propControlButtonHiddenIconStr->c_str());
        jsonIcon->Put("switching", propControlButtonStyle_->propControlButtonSwitchingIconStr->c_str());

        jsonControl->Put("icon", jsonIcon);
        json->Put("controlButton", jsonControl->ToString().c_str());
        json->Put("type",
            type == SideBarContainerType::EMBED ? "SideBarContainerType.Embed" : "SideBarContainerType.OVERLAY");
        json->Put("showSideBar", propShowSideBar_.value_or(true) ? "true" : "false");
        json->Put("showControlButton", propShowControlButton_.value_or(true) ? "true" : "false");
        json->Put("sideBarWidth", std::to_string(sideBarWidth.Value()).c_str());
        json->Put("minSideBarWidth", std::to_string(minSideBarWidth.Value()).c_str());
        json->Put("maxSideBarWidth", std::to_string(maxSideBarWidth.Value()).c_str());
        json->Put("sideBarPosition",
            sideBarPosition == SideBarPosition::START ? "SideBarPosition.Start" : "SideBarPosition.End");
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SideBarContainerType, SideBarContainerType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowSideBar, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowControlButton, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SideBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinSideBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxSideBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoHide, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SideBarPosition, SideBarPosition, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(ControlButtonStyle, ControlButtonStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ControlButtonStyle, ControlButtonWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ControlButtonStyle, ControlButtonHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ControlButtonStyle, ControlButtonLeft, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ControlButtonStyle, ControlButtonTop, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ControlButtonStyle, ControlButtonShowIconStr, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ControlButtonStyle, ControlButtonHiddenIconStr, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ControlButtonStyle, ControlButtonSwitchingIconStr, std::string, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerLayoutProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_PROPERTY_H
