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
#include "core/interfaces/native/node/list_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr bool DEFAULT_SCROLL_ENABLE = true;
constexpr int32_t DEFAULT_STICKY_STYLE = 0;
constexpr int32_t DEFAULT_DIRECTION = 0;
constexpr int32_t DEFAULT_SCROLL_BAR = 1;
constexpr int32_t DEFAULT_DIVIDER_VALUES_COUNT = 3;

constexpr int32_t DEFAULT_EDGE_EFFECT = 0;

constexpr int32_t CALL_STROKE_WIDTH = 0;
constexpr int32_t CALL_START_MARGIN = 1;
constexpr int32_t CALL_END_MARGIN = 2;

void SetListLanes(NodeHandle node, int32_t lanesNum, const struct ArkUIDimensionType* minLengthType,
    const struct ArkUIDimensionType* maxLengthType, const struct ArkUIDimensionType* gutterType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (lanesNum > 0) {
        ListModelNG::SetLanes(frameNode, lanesNum);
        Dimension minLength =
            Dimension(minLengthType->value, static_cast<OHOS::Ace::DimensionUnit>(minLengthType->units));
        Dimension maxLength =
            Dimension(maxLengthType->value, static_cast<OHOS::Ace::DimensionUnit>(maxLengthType->units));
        ListModelNG::SetLaneConstrain(frameNode, minLength, maxLength);
    } else {
        Dimension minLength =
            Dimension(minLengthType->value, static_cast<OHOS::Ace::DimensionUnit>(minLengthType->units));
        Dimension maxLength =
            Dimension(maxLengthType->value, static_cast<OHOS::Ace::DimensionUnit>(maxLengthType->units));
        ListModelNG::SetLaneConstrain(frameNode, minLength, maxLength);
        ListModelNG::SetLanes(frameNode, 1);
    }

    Dimension gutter = Dimension(gutterType->value, static_cast<OHOS::Ace::DimensionUnit>(gutterType->units));
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

void ListSetDivider(NodeHandle node, uint32_t color, const double* values, const int32_t* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_DIVIDER_VALUES_COUNT) {
        return;
    }
    
    V2::ItemDivider divider;
    divider.color = Color(color);
    divider.strokeWidth =
        Dimension(values[CALL_STROKE_WIDTH], static_cast<OHOS::Ace::DimensionUnit>(units[CALL_STROKE_WIDTH]));
    divider.startMargin =
        Dimension(values[CALL_START_MARGIN], static_cast<OHOS::Ace::DimensionUnit>(units[CALL_START_MARGIN]));
    divider.endMargin =
        Dimension(values[CALL_END_MARGIN], static_cast<OHOS::Ace::DimensionUnit>(units[CALL_END_MARGIN]));

    ListModelNG::SetDivider(frameNode, divider);
}

void ListResetDivider(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const V2::ItemDivider divider;

    ListModelNG::SetDivider(frameNode, divider);
}

void SetChainAnimationOptions(NodeHandle node, const struct ArkUIChainAnimationOptionsType* chainAnimationOptions)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ChainAnimationOptions options;
    options.minSpace = CalcDimension(
        chainAnimationOptions->minSpace, static_cast<OHOS::Ace::DimensionUnit>(chainAnimationOptions->minSpaceUnits));
    options.maxSpace = CalcDimension(
        chainAnimationOptions->maxSpace, static_cast<OHOS::Ace::DimensionUnit>(chainAnimationOptions->maxSpaceUnits));
    options.conductivity = chainAnimationOptions->conductivity;
    options.intensity = chainAnimationOptions->intensity;
    options.edgeEffect = chainAnimationOptions->edgeEffect;
    options.stiffness = chainAnimationOptions->stiffness;
    options.damping = chainAnimationOptions->damping;
    ListModelNG::SetChainAnimationOptions(frameNode, options);
}

void ResetChainAnimationOptions(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
    CHECK_NULL_VOID(listTheme);
    ChainAnimationOptions options = {
        .minSpace = listTheme->GetChainMinSpace(),
        .maxSpace = listTheme->GetChainMaxSpace(),
        .conductivity = listTheme->GetChainConductivity(),
        .intensity = listTheme->GetChainIntensity(),
        .edgeEffect = 0,
        .stiffness = listTheme->GetChainStiffness(),
        .damping = listTheme->GetChainDamping(),
    };

    ListModelNG::SetChainAnimationOptions(frameNode, options);
}

ArkUIListModifierAPI GetListModifier()
{
    static const ArkUIListModifierAPI modifier = { SetListLanes, ResetListLanes, SetEditMode, ResetEditMode,
        SetMultiSelectable, ResetMultiSelectable, SetChainAnimation, ResetChainAnimation, SetCachedCount,
        ResetCachedCount, SetEnableScrollInteraction, ResetEnableScrollInteraction, SetSticky, ResetSticky,
        SetListEdgeEffect, ResetListEdgeEffect, SetListDirection, ResetListDirection, SetListFriction,
        ResetListFriction, SetListNestedScroll, ResetListNestedScroll, SetListScrollBar, ResetListScrollBar,
        SetAlignListItem, ResetAlignListItem, SetScrollSnapAlign, ResetScrollSnapAlign, ListSetDivider,
        ListResetDivider, SetChainAnimationOptions, ResetChainAnimationOptions };
    return modifier;
}
} // namespace OHOS::Ace::NG