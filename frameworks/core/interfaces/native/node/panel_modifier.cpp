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
#include "core/interfaces/native/node/panel_modifier.h"

#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_PANEL_MODE = 1;
constexpr double DEFAULT_HEIGHT = 48;
constexpr uint32_t DEFAULT_PANEL_BACKGROUND_COLOR = 0x08182431;
constexpr int32_t DEFAULT_PANEL_TYPE = 1;
constexpr double DEFAULT_CUSTOM_HEIGHT = 0;

void SetPanelMode(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(value);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void ResetPanelMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<PanelMode>(DEFAULT_PANEL_MODE);
    SlidingPanelModelNG::SetPanelMode(frameNode, mode);
}

void SetPanelFullHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelFullHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelFullHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelFullHeight(frameNode);
}

void SetPanelHalfHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelHalfHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}
void ResetPanelHalfHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::ResetPanelHalfHeight(frameNode);
}

void SetPanelMiniHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetPanelMiniHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelMiniHeight(frameNode, Dimension(DEFAULT_HEIGHT, DimensionUnit::VP));
}

void SetPanelBackgroundMask(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(color));
}

void ResetPanelBackgroundMask(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelBackgroundMask(frameNode, Color(DEFAULT_PANEL_BACKGROUND_COLOR));
}

void SetPanelType(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(value);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void ResetPanelType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = static_cast<PanelType>(DEFAULT_PANEL_TYPE);
    SlidingPanelModelNG::SetPanelType(frameNode, type);
}

void SetPanelCustomHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(
        frameNode, CalcDimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetPanelCustomHeightByString(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(value));
}

void ResetPanelCustomHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetPanelCustomHeight(frameNode, CalcDimension(DEFAULT_CUSTOM_HEIGHT));
}

void SetShowCloseIcon(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, value);
}

void ResetShowCloseIcon(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetShowCloseIcon(frameNode, false);
}

void SetDragBar(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, value);
}

void ResetDragBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetHasDragBar(frameNode, true);
}

void SetShow(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, value);
}

void ResetShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SlidingPanelModelNG::SetIsShow(frameNode, true);
}

namespace NodeModifier {
const ArkUIPanelModifier* GetPanelModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIPanelModifier modifier = {
        .setPanelMode = SetPanelMode,
        .resetPanelMode = ResetPanelMode,
        .setPanelFullHeight = SetPanelFullHeight,
        .resetPanelFullHeight = ResetPanelFullHeight,
        .setPanelHalfHeight = SetPanelHalfHeight,
        .resetPanelHalfHeight = ResetPanelHalfHeight,
        .setPanelMiniHeight = SetPanelMiniHeight,
        .resetPanelMiniHeight = ResetPanelMiniHeight,
        .setPanelBackgroundMask = SetPanelBackgroundMask,
        .resetPanelBackgroundMask = ResetPanelBackgroundMask,
        .setPanelType = SetPanelType,
        .resetPanelType = ResetPanelType,
        .setPanelCustomHeight = SetPanelCustomHeight,
        .setPanelCustomHeightByString = SetPanelCustomHeightByString,
        .resetPanelCustomHeight = ResetPanelCustomHeight,
        .setShowCloseIcon = SetShowCloseIcon,
        .resetShowCloseIcon = ResetShowCloseIcon,
        .setDragBar = SetDragBar,
        .resetDragBar = ResetDragBar,
        .setShow = SetShow,
        .resetShow = ResetShow,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIPanelModifier* GetCJUIPanelModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIPanelModifier modifier = {
        .setPanelMode = SetPanelMode,
        .resetPanelMode = ResetPanelMode,
        .setPanelFullHeight = SetPanelFullHeight,
        .resetPanelFullHeight = ResetPanelFullHeight,
        .setPanelHalfHeight = SetPanelHalfHeight,
        .resetPanelHalfHeight = ResetPanelHalfHeight,
        .setPanelMiniHeight = SetPanelMiniHeight,
        .resetPanelMiniHeight = ResetPanelMiniHeight,
        .setPanelBackgroundMask = SetPanelBackgroundMask,
        .resetPanelBackgroundMask = ResetPanelBackgroundMask,
        .setPanelType = SetPanelType,
        .resetPanelType = ResetPanelType,
        .setPanelCustomHeight = SetPanelCustomHeight,
        .setPanelCustomHeightByString = SetPanelCustomHeightByString,
        .resetPanelCustomHeight = ResetPanelCustomHeight,
        .setShowCloseIcon = SetShowCloseIcon,
        .resetShowCloseIcon = ResetShowCloseIcon,
        .setDragBar = SetDragBar,
        .resetDragBar = ResetDragBar,
        .setShow = SetShow,
        .resetShow = ResetShow,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
