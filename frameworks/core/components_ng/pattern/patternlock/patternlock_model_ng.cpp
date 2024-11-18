/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"

#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<V2::PatternLockController> PatternLockModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PATTERN_LOCK_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PATTERN_LOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PatternLockPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->SetPatternLockController(AceType::MakeRefPtr<V2::PatternLockController>());
    return pattern->GetPatternLockController();
}

void PatternLockModelNG::SetPatternComplete(NG::PatternLockCompleteEvent&& onComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(onComplete));
}

void PatternLockModelNG::SetDotConnect(std::function<void(int32_t)>&& onDotConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDotConnect(std::move(onDotConnect));
}

void PatternLockModelNG::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor);
}

void PatternLockModelNG::SetAutoReset(bool isAutoReset)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset);
}

void PatternLockModelNG::SetPathColor(const Color& pathColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor);
}

void PatternLockModelNG::SetActiveColor(const Color& activeColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, activeColor);
}

void PatternLockModelNG::SetRegularColor(const Color& regularColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor);
}

void PatternLockModelNG::SetCircleRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius);
}

void PatternLockModelNG::SetSideLength(const Dimension& sideLength)
{
    ACE_UPDATE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength);
}

void PatternLockModelNG::SetStrokeWidth(const Dimension& lineWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, lineWidth);
}

void PatternLockModelNG::SetActiveCircleColor(const Color& activeCircleColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, activeCircleColor);
}

void PatternLockModelNG::SetActiveCircleRadius(const Dimension& activeCircleRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, activeCircleRadius);
}

void PatternLockModelNG::SetEnableWaveEffect(bool enableWaveEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, enableWaveEffect);
}

RefPtr<FrameNode> PatternLockModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PATTERN_LOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PatternLockPattern>(); });
    CHECK_NULL_RETURN(frameNode, frameNode);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->SetPatternLockController(AceType::MakeRefPtr<V2::PatternLockController>());
    return frameNode;
}

const RefPtr<V2::PatternLockController> PatternLockModelNG::GetController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetPatternLockController();
}

void PatternLockModelNG::SetActiveColor(FrameNode* frameNode, const std::optional<Color>& activeColor)
{
    if (activeColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor,
            activeColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, frameNode);
    }
}

void PatternLockModelNG::SetCircleRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    if (radius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, frameNode);
    }
}

void PatternLockModelNG::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    if (selectedColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor,
            selectedColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, frameNode);
    }
}

void PatternLockModelNG::SetSideLength(FrameNode* frameNode, const std::optional<Dimension>& sideLength)
{
    if (sideLength.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, frameNode);
    }
}

void PatternLockModelNG::SetAutoReset(FrameNode* frameNode, const std::optional<bool>& isAutoReset)
{
    if (isAutoReset.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, frameNode);
    }
}

void PatternLockModelNG::SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& lineWidth)
{
    if (lineWidth.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth,
            lineWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, frameNode);
    }
}

void PatternLockModelNG::SetRegularColor(FrameNode* frameNode, const std::optional<Color>& regularColor)
{
    if (regularColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor,
            regularColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, frameNode);
    }
}

void PatternLockModelNG::SetPathColor(FrameNode* frameNode, const std::optional<Color>& pathColor)
{
    if (pathColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor,
            pathColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, frameNode);
    }
}

void PatternLockModelNG::SetActiveCircleColor(FrameNode* frameNode, const std::optional<Color>& activeCircleColor)
{
    if (activeCircleColor.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor,
            activeCircleColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, frameNode);
    }
}

void PatternLockModelNG::SetActiveCircleRadius(FrameNode* frameNode, const std::optional<Dimension>& activeCircleRadius)
{
    if (activeCircleRadius.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius,
            activeCircleRadius.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, frameNode);
    }
}

void PatternLockModelNG::SetEnableWaveEffect(FrameNode* frameNode, const std::optional<bool>& enableWaveEffect)
{
    if (enableWaveEffect.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect,
            enableWaveEffect.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, frameNode);
    }
}

} // namespace OHOS::Ace::NG
