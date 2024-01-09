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

#include "core/interfaces/native/node/api.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"
#include "core/pipeline/base/element_register.h"

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
void SetSideBarWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension sideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetSideBarWidth(frameNode, sideBarWidthDimension);
}

void ResetSideBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetSideBarWidth(frameNode, DEFAULT_SIDE_BAR_WIDTH);
}

void SetMinSideBarWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension minSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, minSideBarWidthDimension);
}

void ResetMinSideBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH_V10);
        return;
    }
    SideBarContainerModelNG::SetMinSideBarWidth(frameNode, DEFAULT_MIN_SIDE_BAR_WIDTH);
}

void SetControlButton(NodeHandle node, double* values, int32_t valueLength, const struct IconsStruct* iconsStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension left = Dimension(values[0], DimensionUnit::VP);
    Dimension top = Dimension(values[1], DimensionUnit::VP);
    Dimension width = Dimension(values[2], DimensionUnit::VP);
    Dimension heigth = Dimension(values[3], DimensionUnit::VP);
    SideBarContainerModelNG::SetControlButtonLeft(frameNode, left);
    SideBarContainerModelNG::SetControlButtonTop(frameNode, top);
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, width);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, heigth);
    CHECK_NULL_VOID(iconsStruct);
    if (iconsStruct->HiddenIconInfo) {
        SideBarContainerModelNG::SetControlButtonShowIconInfo(frameNode, iconsStruct->HiddenIconInfo, false, nullptr);
    }
    if (iconsStruct->ShowIconInfo) {
        SideBarContainerModelNG::SetControlButtonHiddenIconInfo(frameNode, iconsStruct->ShowIconInfo, false, nullptr);
    }
    if (iconsStruct->SwitchingIconInfo) {
        SideBarContainerModelNG::SetControlButtonSwitchingIconInfo(
            frameNode, iconsStruct->SwitchingIconInfo, false, nullptr);
    }
}

void ResetControlButton(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
        SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
        SideBarContainerModelNG::ResetControlButtonLeft(frameNode);
        SideBarContainerModelNG::SetControlButtonTop(frameNode, DEFAULT_CONTROL_BUTTON_TOP);
        return;
    }
    SideBarContainerModelNG::SetControlButtonWidth(frameNode, DEFAULT_CONTROL_BUTTON_WIDTH);
    SideBarContainerModelNG::SetControlButtonHeight(frameNode, DEFAULT_CONTROL_BUTTON_HEIGHT);
}

void SetShowControlButton(NodeHandle node, bool isShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, isShow);
}

void ResetShowControlButton(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowControlButton(frameNode, DEFAULT_SHOW_CONTROL_BUTTON);
}

void SetAutoHide(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, static_cast<bool>(value));
}

void ResetAutoHide(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetAutoHide(frameNode, DEFAULT_AUTO_HIDE);
}

void SetSideBarContainerMaxSideBarWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, maxSideBarWidthDimension);
}

void ResetSideBarContainerMaxSideBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetMaxSideBarWidth(frameNode, DEFAULT_SIDE_BAR_CONTAINER_MAX_SIDE_BAR_WIDTH);
}

void SetSideBarContainerMinContentWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension maxSideBarWidthDimension(value, static_cast<DimensionUnit>(unit));
    SideBarContainerModelNG::SetMinContentWidth(frameNode, maxSideBarWidthDimension);
}

void ResetSideBarContainerMinContentWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetMinContentWidth(frameNode, -1.0_vp);
}

void SetSideBarPosition(NodeHandle node, int32_t sideBarPosition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, static_cast<SideBarPosition>(sideBarPosition));
}

void ResetSideBarPosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetSideBarPosition(frameNode, DEFAULT_SIDE_BAR_POSITION);
}

void SetShowSideBar(NodeHandle node, bool isShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, isShow);
}

void ResetShowSideBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetShowSideBar(frameNode, DEFAULT_SHOW_SIDE_BAR);
}

void SetSideBarContainerDivider(NodeHandle node, double* values, int32_t* units, int32_t length, uint32_t color)
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

void ResetSideBarContainerDivider(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SideBarContainerModelNG::SetDividerStrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
    SideBarContainerModelNG::SetDividerColor(frameNode, Color(DEFAULT_SIDE_BAR_DIVIDER_COLOR));
    SideBarContainerModelNG::SetDividerStartMargin(frameNode, DEFAULT_START_MARGIN);
    SideBarContainerModelNG::SetDividerEndMargin(frameNode, DEFAULT_END_MARGIN);
}

ArkUISideBarContainerModifierAPI GetSideBarContainerModifier()
{
    static const ArkUISideBarContainerModifierAPI modifier = { SetSideBarWidth, ResetSideBarWidth, SetMinSideBarWidth,
        ResetMinSideBarWidth, SetControlButton, ResetControlButton, SetShowControlButton, ResetShowControlButton,
        SetAutoHide, ResetAutoHide, SetSideBarContainerMaxSideBarWidth, ResetSideBarContainerMaxSideBarWidth,
        SetSideBarContainerMinContentWidth, ResetSideBarContainerMinContentWidth, SetSideBarPosition,
        ResetSideBarPosition, SetShowSideBar, ResetShowSideBar, SetSideBarContainerDivider,
        ResetSideBarContainerDivider };
    return modifier;
}
} // namespace OHOS::Ace::NG