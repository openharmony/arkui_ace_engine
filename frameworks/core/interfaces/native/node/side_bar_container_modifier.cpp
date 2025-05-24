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
#include "core/interfaces/native/node/side_bar_container_modifier.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
const Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
const Dimension DEFAULT_SIDE_BAR_WIDTH_V10 = 240.0_vp;
const Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
const Dimension DEFAULT_MIN_SIDE_BAR_WIDTH_V10 = 240.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
const Dimension DEFAULT_SIDE_BAR_CONTAINER_MAX_SIDE_BAR_WIDTH(280.0, DimensionUnit::VP);
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
const bool DEFAULT_SHOW_SIDE_BAR = true;
const bool DEFAULT_SHOW_CONTROL_BUTTON = true;
const bool DEFAULT_AUTO_HIDE = true;
constexpr SideBarPosition DEFAULT_SIDE_BAR_POSITION = SideBarPosition::START;
constexpr uint32_t DEFAULT_SIDE_BAR_DIVIDER_COLOR = 0x08000000;
const Dimension DEFAULT_START_MARGIN(0.0, DimensionUnit::VP);
const Dimension DEFAULT_END_MARGIN(0.0, DimensionUnit::VP);
void SetSideBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension sideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetSideBarWidth(frameNode, sideBarWidthDimension);
}

void ResetSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH);
}

void SetMinSideBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension minSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, minSideBarWidthDimension);
}

void ResetMinSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH);
}

void SetControlButton(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valueLength,
    const struct ArkUIIconsStruct* iconsStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension left = Dimension(values[0], DimensionUnit::VP);
    Dimension top = Dimension(values[1], DimensionUnit::VP);
    Dimension width = Dimension(values[2], DimensionUnit::VP);
    Dimension height = Dimension(values[3], DimensionUnit::VP);
    SideBarContainerModelNG::SetControlButtonLeft(frameNode, left);
    SideBarContainerModelNG::SetControlButtonTop(frameNode, top);
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, width);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, height);
    CHECK_NULL_VOID(iconsStruct);
    if (iconsStruct->HiddenIconInfo) {
        SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, iconsStruct->HiddenIconInfo, false, nullptr);
    }
    if (iconsStruct->ShowIconInfo) {
        SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, iconsStruct->ShowIconInfo, false, nullptr);
    }
    if (iconsStruct->SwitchingIconInfo) {
        SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(
            frameNode, iconsStruct->SwitchingIconInfo, false, nullptr);
    }
}

void ResetControlButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
        SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
        SideBarContainerModelNG::ResetControlButtonLeft(frameNode);
        SideBarContainerModelNG::SetControlButtonTop(frameNode, DEFAULT_CONTROL_BUTTON_TOP);
        SideBarContainerModelNG::ResetControlButtonIconInfo(frameNode);
        return;
    }
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
}

void SetShowControlButton(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, isShow);
}

void ResetShowControlButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, DEFAULT_SHOW_CONTROL_BUTTON);
}

void SetAutoHide(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, static_cast<bool>(value));
}

void ResetAutoHide(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, DEFAULT_AUTO_HIDE);
}

void SetSideBarContainerMaxSideBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, maxSideBarWidthDimension);
}

void ResetSideBarContainerMaxSideBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, DEFAULT_SIDE_BAR_CONTAINER_MAX_SIDE_BAR_WIDTH);
}

void SetSideBarContainerMinContentWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMinContentWidth(frameNode, maxSideBarWidthDimension);
}

void ResetSideBarContainerMinContentWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetMinContentWidth(frameNode, -1.0_vp);
}

void SetSideBarPosition(ArkUINodeHandle node, ArkUI_Int32 sideBarPosition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, static_cast<SideBarPosition>(sideBarPosition));
}

void ResetSideBarPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, DEFAULT_SIDE_BAR_POSITION);
}

void SetShowSideBar(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, isShow);
}

void ResetShowSideBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, DEFAULT_SHOW_SIDE_BAR);
}

void SetSideBarContainerDivider(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    if (length != NUM_3) {
        return;
    }
    Dimension strokeWidth(values[NUM_0], static_cast<DimensionUnit>(units[NUM_0]));
    Dimension startMargin(values[NUM_1], static_cast<DimensionUnit>(units[NUM_1]));
    Dimension endMargin(values[NUM_2], static_cast<DimensionUnit>(units[NUM_2]));
    SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, strokeWidth);
    SideBarContainerModelNG::SetDividerColor(frameNode, Color(color));
    SideBarContainerModelNG::SetDividerStartMargin(frameNode, startMargin);
    SideBarContainerModelNG::SetDividerEndMargin(frameNode, endMargin);
}

void ResetSideBarContainerDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
    SideBarContainerModelNG::SetDividerColor(frameNode, Color(DEFAULT_SIDE_BAR_DIVIDER_COLOR));
    SideBarContainerModelNG::SetDividerStartMargin(frameNode, DEFAULT_START_MARGIN);
    SideBarContainerModelNG::SetDividerEndMargin(frameNode, DEFAULT_END_MARGIN);
}

void SetSideBarOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto sideBarOnChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        SideBarContainerModelNG::SetOnChange(frameNode, std::move(*sideBarOnChange));
    } else {
        SideBarContainerModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSideBarOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetOnChange(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUISideBarContainerModifier* GetSideBarContainerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISideBarContainerModifier modifier = {
        .setSideBarWidth = SetSideBarWidth,
        .resetSideBarWidth = ResetSideBarWidth,
        .setMinSideBarWidth = SetMinSideBarWidth,
        .resetMinSideBarWidth = ResetMinSideBarWidth,
        .setControlButton = SetControlButton,
        .resetControlButton = ResetControlButton,
        .setShowControlButton = SetShowControlButton,
        .resetShowControlButton = ResetShowControlButton,
        .setAutoHide = SetAutoHide,
        .resetAutoHide = ResetAutoHide,
        .setSideBarContainerMaxSideBarWidth = SetSideBarContainerMaxSideBarWidth,
        .resetSideBarContainerMaxSideBarWidth = ResetSideBarContainerMaxSideBarWidth,
        .setSideBarContainerMinContentWidth = SetSideBarContainerMinContentWidth,
        .resetSideBarContainerMinContentWidth = ResetSideBarContainerMinContentWidth,
        .setSideBarPosition = SetSideBarPosition,
        .resetSideBarPosition = ResetSideBarPosition,
        .setShowSideBar = SetShowSideBar,
        .resetShowSideBar = ResetShowSideBar,
        .setSideBarContainerDivider = SetSideBarContainerDivider,
        .resetSideBarContainerDivider = ResetSideBarContainerDivider,
        .setSideBarOnChange = SetSideBarOnChange,
        .resetSideBarOnChange = ResetSideBarOnChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUISideBarContainerModifier* GetCJUISideBarContainerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISideBarContainerModifier modifier = {
        .setSideBarWidth = SetSideBarWidth,
        .resetSideBarWidth = ResetSideBarWidth,
        .setMinSideBarWidth = SetMinSideBarWidth,
        .resetMinSideBarWidth = ResetMinSideBarWidth,
        .setControlButton = SetControlButton,
        .resetControlButton = ResetControlButton,
        .setShowControlButton = SetShowControlButton,
        .resetShowControlButton = ResetShowControlButton,
        .setAutoHide = SetAutoHide,
        .resetAutoHide = ResetAutoHide,
        .setSideBarContainerMaxSideBarWidth = SetSideBarContainerMaxSideBarWidth,
        .resetSideBarContainerMaxSideBarWidth = ResetSideBarContainerMaxSideBarWidth,
        .setSideBarContainerMinContentWidth = SetSideBarContainerMinContentWidth,
        .resetSideBarContainerMinContentWidth = ResetSideBarContainerMinContentWidth,
        .setSideBarPosition = SetSideBarPosition,
        .resetSideBarPosition = ResetSideBarPosition,
        .setShowSideBar = SetShowSideBar,
        .resetShowSideBar = ResetShowSideBar,
        .setSideBarContainerDivider = SetSideBarContainerDivider,
        .resetSideBarContainerDivider = ResetSideBarContainerDivider,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
