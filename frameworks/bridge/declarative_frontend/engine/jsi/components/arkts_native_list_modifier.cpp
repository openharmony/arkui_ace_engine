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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_list_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr bool DEFAULT_SCROLL_ENABLE = true;
constexpr int32_t DEFAULT_STICKY_STYLE = 0;
constexpr int32_t DEFAULT_DIRECTION = 0;
constexpr int32_t DEFAULT_SCROLL_BAR = 1;

constexpr int32_t DEFAULT_EDGE_EFFECT = 0;

void SetListLanes(NodeHandle node, int32_t lanesNum, Dimension minLength, Dimension maxLength, Dimension gutter)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (lanesNum > 0) {
        ListModelNG::SetLanes(frameNode, lanesNum);
    } else {
        ListModelNG::SetLaneConstrain(frameNode, minLength, maxLength);
    }

    ListModelNG::SetLaneGutter(frameNode, gutter);
}

void ResetListLanes(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetLanes(frameNode, 1);
    ListModelNG::SetLaneGutter(frameNode, Dimension(0));
}

void SetEditMode(NodeHandle node, bool editMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEditMode(frameNode, editMode);
}

void ResetEditMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEditMode(frameNode, false);
}

void SetMultiSelectable(NodeHandle node, bool selectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetMultiSelectable(frameNode, selectable);
}

void ResetMultiSelectable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetMultiSelectable(frameNode, false);
}

void SetChainAnimation(NodeHandle node, bool chainAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetChainAnimation(frameNode, chainAnimation);
}

void ResetChainAnimation(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetChainAnimation(frameNode, false);
}

void SetCachedCount(NodeHandle node, int32_t cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (cachedCount < 0) {
        cachedCount = 1;
    }
    ListModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
}

void SetEnableScrollInteraction(NodeHandle node, bool enableScrollInteraction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollEnabled(frameNode, enableScrollInteraction);
}

void ResetEnableScrollInteraction(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollEnabled(frameNode, DEFAULT_SCROLL_ENABLE);
}

void SetSticky(NodeHandle node, int32_t stickyStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetSticky(frameNode, stickyStyle);
}

void ResetSticky(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetSticky(frameNode, DEFAULT_STICKY_STYLE);
}

void SetListEdgeEffect(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

void ResetListEdgeEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, DEFAULT_EDGE_EFFECT, false);
}

void SetListDirection(NodeHandle node, int32_t axis)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListDirection(frameNode, axis);
}

void ResetListDirection(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListDirection(frameNode, DEFAULT_DIRECTION);
}

void SetListFriction(NodeHandle node, double friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListFriction(frameNode, friction);
}

void ResetListFriction(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double friction = -1.0;
    ListModelNG::SetListFriction(frameNode, friction);
}

void SetListNestedScroll(NodeHandle node, int32_t forward, int32_t backward)
{
    NestedScrollOptions opt = {
        .forward = static_cast<NestedScrollMode>(forward),
        .backward = static_cast<NestedScrollMode>(backward),
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListNestedScroll(frameNode, opt);
}

void ResetListNestedScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    ListModelNG::SetListNestedScroll(frameNode, nestedOpt);
}

void SetListScrollBar(NodeHandle node, int32_t barState)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBar(frameNode, barState);
}

void ResetListScrollBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBar(frameNode, DEFAULT_SCROLL_BAR);
}

void SetAlignListItem(NodeHandle node, int32_t listItemAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListItemAlign(frameNode, static_cast<V2::ListItemAlign>(listItemAlign));
}

void ResetAlignListItem(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListItemAlign(frameNode, V2::ListItemAlign::START);
}

void SetScrollSnapAlign(NodeHandle node, int32_t scrollSnapAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, static_cast<V2::ScrollSnapAlign>(scrollSnapAlign));
}

void ResetScrollSnapAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, V2::ScrollSnapAlign::NONE);
}

void ListSetDivider(NodeHandle node, double strokeWidth, const uint32_t color, double startMargin,
    double endMargin, int32_t strokeWidth_size, int32_t startMargin_size, int32_t endMargin_size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    V2::ItemDivider divider;
    divider.color = Color(color);
    divider.strokeWidth = Dimension(strokeWidth, static_cast<OHOS::Ace::DimensionUnit>(strokeWidth_size));
    divider.startMargin = Dimension(startMargin, static_cast<OHOS::Ace::DimensionUnit>(startMargin_size));
    divider.endMargin = Dimension(endMargin, static_cast<OHOS::Ace::DimensionUnit>(endMargin_size));

    ListModelNG::SetDivider(frameNode, divider);
}

void ListResetDivider(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const V2::ItemDivider divider;

    ListModelNG::SetDivider(frameNode, divider);
}

void SetChainAnimationOptions(NodeHandle node, double minSpace, double maxSpace,
    double conductivity, double intensity, int32_t edgeEffect, double stiffness, double damping,
    int32_t minSpace_size, int32_t maxSpace_size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ChainAnimationOptions options;
    options.minSpace = CalcDimension(minSpace, static_cast<OHOS::Ace::DimensionUnit>(minSpace_size));
    options.maxSpace = CalcDimension(minSpace, static_cast<OHOS::Ace::DimensionUnit>(maxSpace_size));
    options.conductivity = conductivity;
    options.intensity = intensity;
    options.edgeEffect = edgeEffect;
    options.stiffness = stiffness;
    options.damping = damping;
    ListModelNG::SetChainAnimationOptions(frameNode, options);
}

void ResetChainAnimationOptions(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension minSpace;
    CalcDimension maxSpace;
    ChainAnimationOptions options;
    options.minSpace = minSpace;
    options.maxSpace = maxSpace;
    options.conductivity = 0;
    options.intensity = 0;
    options.edgeEffect = 0;
    options.stiffness = 0;
    options.damping = 0;

    ListModelNG::SetChainAnimationOptions(frameNode, options);
}

ArkUIListModifierAPI GetListModifier()
{
    static const ArkUIListModifierAPI modifier = { SetListLanes, ResetListLanes, SetEditMode,
        ResetEditMode, SetMultiSelectable, ResetMultiSelectable, SetChainAnimation, ResetChainAnimation,
        SetCachedCount, ResetCachedCount, SetEnableScrollInteraction, ResetEnableScrollInteraction, SetSticky,
        ResetSticky, SetListEdgeEffect, ResetListEdgeEffect, SetListDirection,
        ResetListDirection, SetListFriction, ResetListFriction, SetListNestedScroll, ResetListNestedScroll,
        SetListScrollBar, ResetListScrollBar, SetAlignListItem, ResetAlignListItem, SetScrollSnapAlign,
        ResetScrollSnapAlign, ListSetDivider, ListResetDivider, SetChainAnimationOptions,
        ResetChainAnimationOptions };
    return modifier;
}
} // namespace OHOS::Ace::NG