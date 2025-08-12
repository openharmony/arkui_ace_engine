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

#include "core/components_ng/pattern/patternlock/patternlock_model_static.h"

#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"

namespace OHOS::Ace::NG {
void PatternLockModelStatic::SetActiveColor(FrameNode* frameNode, const std::optional<Color>& activeColor)
{
    if (activeColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, activeColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, frameNode);
    }
}

void PatternLockModelStatic::SetCircleRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, frameNode);
    }
}

void PatternLockModelStatic::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, frameNode);
    }
}

void PatternLockModelStatic::SetSideLength(FrameNode* frameNode, const std::optional<Dimension>& sideLength)
{
    if (sideLength.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, frameNode);
    }
}

void PatternLockModelStatic::SetAutoReset(FrameNode* frameNode, const std::optional<bool>& isAutoReset)
{
    if (isAutoReset.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, frameNode);
    }
}

void PatternLockModelStatic::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& lineWidth)
{
    if (lineWidth.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, lineWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, frameNode);
    }
}

void PatternLockModelStatic::SetRegularColor(FrameNode* frameNode, const std::optional<Color>& regularColor)
{
    if (regularColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, frameNode);
    }
}

void PatternLockModelStatic::SetPathColor(FrameNode* frameNode, const std::optional<Color>& pathColor)
{
    if (pathColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, frameNode);
    }
}

void PatternLockModelStatic::SetActiveCircleColor(FrameNode* frameNode, const std::optional<Color>& activeCircleColor)
{
    if (activeCircleColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            PatternLockPaintProperty, ActiveCircleColor, activeCircleColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, frameNode);
    }
}

void PatternLockModelStatic::SetActiveCircleRadius(
    FrameNode* frameNode, const std::optional<Dimension>& activeCircleRadius)
{
    if (activeCircleRadius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            PatternLockPaintProperty, ActiveCircleRadius, activeCircleRadius.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, frameNode);
    }
}

void PatternLockModelStatic::SetEnableWaveEffect(FrameNode* frameNode, const std::optional<bool>& enableWaveEffect)
{
    if (enableWaveEffect.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, enableWaveEffect.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, frameNode);
    }
}
} // namespace OHOS::Ace::NG
