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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_panel_modifier.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_PANEL_MODE = 1;
constexpr double DEFAULT_HEIGHT = 48;
constexpr uint32_t DEFAULT_PANEL_BACKGROUND_COLOR = 0x08182431;
constexpr int32_t DEFAULT_PANEL_TYPE = 1;
constexpr double DEFAULT_CUSTOM_HEIGHT = 0;

void SetPanelMode(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(value);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void ResetPanelMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(DEFAULT_PANEL_MODE);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void SetPanelFullHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelFullHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelFullHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelFullHeight(frameNode);
}

void SetPanelHalfHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelHalfHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelHalfHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelHalfHeight(frameNode);
}

void SetPanelMiniHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetPanelMiniHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(DEFAULT_HEIGHT, DimensionUnit::VP));
}

void SetPanelBackgroundMask(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(color));
}

void ResetPanelBackgroundMask(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(DEFAULT_PANEL_BACKGROUND_COLOR));
}

void SetPanelType(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(value);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void ResetPanelType(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(DEFAULT_PANEL_TYPE);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void SetPanelCustomHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(
        frameNode, CalcDimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelCustomHeightByString(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(value));
}

void ResetPanelCustomHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(DEFAULT_CUSTOM_HEIGHT));
}

void SetShowCloseIcon(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, value);
}

void ResetShowCloseIcon(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, false);
}

void SetDragBar(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, value);
}

void ResetDragBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, true);
}

void SetShow(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, value);
}

void ResetShow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, true);
}

ArkUIPanelModifierAPI GetPanelModifier()
{
    static const ArkUIPanelModifierAPI modifier = { SetPanelMode, ResetPanelMode, SetPanelFullHeight,
        ResetPanelFullHeight, SetPanelHalfHeight, ResetPanelHalfHeight, SetPanelMiniHeight, ResetPanelMiniHeight,
        SetPanelBackgroundMask, ResetPanelBackgroundMask, SetPanelType, ResetPanelType, SetPanelCustomHeight,
        SetPanelCustomHeightByString, ResetPanelCustomHeight, SetShowCloseIcon, ResetShowCloseIcon, SetDragBar,
        ResetDragBar, SetShow, ResetShow };

    return modifier;
}
} // namespace OHOS::Ace::NG