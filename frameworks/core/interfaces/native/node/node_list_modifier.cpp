/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_list_modifier.h"
#include <cstdint>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr bool DEFAULT_SCROLL_ENABLE = true;
constexpr int32_t DEFAULT_STICKY_STYLE = 0;
constexpr int32_t DEFAULT_DIRECTION = 0;
constexpr int32_t DEFAULT_SCROLL_BAR = 1;
constexpr int32_t DEFAULT_DIVIDER_VALUES_COUNT = 3;
constexpr float DEFAULT_OFFSET = 0.0f;

constexpr int32_t DEFAULT_EDGE_EFFECT = 0;

constexpr int32_t ERROR_INT_CODE = -1;
constexpr int32_t CALL_STROKE_WIDTH = 0;
constexpr int32_t CALL_START_MARGIN = 1;
constexpr int32_t CALL_END_MARGIN = 2;
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;

void SetListLanes(ArkUINodeHandle node, ArkUI_Int32 lanesNum, const struct ArkUIDimensionType* minLengthType,
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

void ResetListLanes(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetLanes(frameNode, 1);
    ListModelNG::SetLaneGutter(frameNode, Dimension(0));
}

void SetEditMode(ArkUINodeHandle node, ArkUI_Bool editMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEditMode(frameNode, editMode);
}

void ResetEditMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEditMode(frameNode, false);
}

void SetMultiSelectable(ArkUINodeHandle node, ArkUI_Bool selectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetMultiSelectable(frameNode, selectable);
}

void ResetMultiSelectable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetMultiSelectable(frameNode, false);
}

void SetChainAnimation(ArkUINodeHandle node, ArkUI_Bool chainAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetChainAnimation(frameNode, chainAnimation);
}

void ResetChainAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetChainAnimation(frameNode, false);
}

void SetCachedCount(ArkUINodeHandle node, ArkUI_Int32 cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (cachedCount < 0) {
        cachedCount = 1;
    }
    ListModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
}

ArkUI_Bool GetEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetScrollEnabled(frameNode);
}

void SetEnableScrollInteraction(ArkUINodeHandle node, ArkUI_Bool enableScrollInteraction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollEnabled(frameNode, enableScrollInteraction);
}

void ResetEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollEnabled(frameNode, DEFAULT_SCROLL_ENABLE);
}

ArkUI_Int32 GetSticky(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetSticky(frameNode);
}

void SetSticky(ArkUINodeHandle node, ArkUI_Int32 stickyStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetSticky(frameNode, stickyStyle);
}

void ResetSticky(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetSticky(frameNode, DEFAULT_STICKY_STYLE);
}

ArkUI_Float32 GetListSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetListSpace(frameNode);
}

void SetListSpace(ArkUINodeHandle node, ArkUI_Float32 space)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListSpace(frameNode, Dimension(space, DimensionUnit::VP));
}

void ResetListSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListSpace(frameNode, Dimension(0, DimensionUnit::VP));
}

ArkUI_Int32 GetListEdgeEffect(ArkUINodeHandle node, ArkUI_Int32* values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    values[INDEX_0] = ListModelNG::GetEdgeEffect(frameNode);
    values[INDEX_1] = ListModelNG::GetEdgeEffectAlways(frameNode);
    return INDEX_2;
}

void SetListEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

void ResetListEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, DEFAULT_EDGE_EFFECT, false);
}

ArkUI_Int32 GetListDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetListDirection(frameNode);
}

void SetListDirection(ArkUINodeHandle node, ArkUI_Int32 axis)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListDirection(frameNode, axis);
}

void ResetListDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListDirection(frameNode, DEFAULT_DIRECTION);
}

ArkUI_Float32 GetListFriction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetListFriction(frameNode);
}

void SetListFriction(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListFriction(frameNode, friction);
}

void ResetListFriction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double friction = -1.0;
    ListModelNG::SetListFriction(frameNode, friction);
}

void SetListNestedScroll(ArkUINodeHandle node, ArkUI_Int32 forward, ArkUI_Int32 backward)
{
    NestedScrollOptions opt = {
        .forward = static_cast<NestedScrollMode>(forward),
        .backward = static_cast<NestedScrollMode>(backward),
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListNestedScroll(frameNode, opt);
}

void ResetListNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    ListModelNG::SetListNestedScroll(frameNode, nestedOpt);
}

ArkUI_Int32 GetListScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetListScrollBar(frameNode);
}

void SetListScrollBar(ArkUINodeHandle node, ArkUI_Int32 barState)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBar(frameNode, barState);
}

void ResetListScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBar(frameNode, DEFAULT_SCROLL_BAR);
}

ArkUI_Float32 GetListScrollBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetScrollBarWidth(frameNode);
}

void SetListScrollBarWidth(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBarWidth(frameNode, value);
}

void ResetListScrollBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBarWidth(frameNode, "0vp");
}

ArkUI_Uint32 GetListScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetScrollBarColor(frameNode);
}

void SetListScrollBarColor(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBarColor(frameNode, value);
}

void ResetListScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListScrollBarColor(frameNode, "#FF000000");
}

ArkUI_Int32 GetAlignListItem(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetListItemAlign(frameNode);
}

void SetAlignListItem(ArkUINodeHandle node, ArkUI_Int32 listItemAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListItemAlign(frameNode, static_cast<V2::ListItemAlign>(listItemAlign));
}

void ResetAlignListItem(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListItemAlign(frameNode, V2::ListItemAlign::START);
}

void SetScrollSnapAlign(ArkUINodeHandle node, ArkUI_Int32 scrollSnapAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, static_cast<V2::ScrollSnapAlign>(scrollSnapAlign));
}

void ResetScrollSnapAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, V2::ScrollSnapAlign::NONE);
}

void SetContentStartOffset(ArkUINodeHandle node, ArkUI_Float32 startOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetContentStartOffset(frameNode, startOffset);
}

void ResetContentStartOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetContentStartOffset(frameNode, DEFAULT_OFFSET);
}

void SetContentEndOffset(ArkUINodeHandle node, ArkUI_Float32 endOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetContentEndOffset(frameNode, endOffset);
}

void ResetContentEndOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetContentEndOffset(frameNode, DEFAULT_OFFSET);
}

void ListSetDivider(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
    const int32_t* units, ArkUI_Int32 length)
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

void ListResetDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const V2::ItemDivider divider;

    ListModelNG::SetDivider(frameNode, divider);
}

void SetChainAnimationOptions(ArkUINodeHandle node, const struct ArkUIChainAnimationOptionsType* chainAnimationOptions)
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

void ResetChainAnimationOptions(ArkUINodeHandle node)
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
} // namespace

namespace NodeModifier {
const ArkUIListModifier* GetListModifier()
{
    static const ArkUIListModifier modifier = { SetListLanes, ResetListLanes, SetEditMode, ResetEditMode,
        SetMultiSelectable, ResetMultiSelectable, SetChainAnimation, ResetChainAnimation, SetCachedCount,
        ResetCachedCount, GetEnableScrollInteraction, SetEnableScrollInteraction, ResetEnableScrollInteraction,
        GetSticky, SetSticky, ResetSticky, GetListEdgeEffect, SetListEdgeEffect, ResetListEdgeEffect, GetListDirection,
        SetListDirection, ResetListDirection, GetListFriction, SetListFriction, ResetListFriction, nullptr,
        SetListNestedScroll, ResetListNestedScroll, GetListScrollBar, SetListScrollBar, ResetListScrollBar,
        GetListScrollBarWidth, SetListScrollBarWidth, ResetListScrollBarWidth, GetListScrollBarColor,
        SetListScrollBarColor, ResetListScrollBarColor, GetAlignListItem, SetAlignListItem, ResetAlignListItem,
        SetScrollSnapAlign, ResetScrollSnapAlign, SetContentStartOffset, ResetContentStartOffset, SetContentEndOffset,
        ResetContentEndOffset, ListSetDivider, ListResetDivider, SetChainAnimationOptions,
        ResetChainAnimationOptions, GetListSpace, SetListSpace, ResetListSpace };
    return &modifier;
}

void SetOnListScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScroll = [node, extraParam](Dimension scrollOffset, ScrollState scrollState) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL;
        event.componentAsyncEvent.data[0].f32 = static_cast<float>(scrollOffset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(scrollState);
        SendArkUIAsyncEvent(&event);
    };
    ListModelNG::SetOnScroll(frameNode, std::move(onScroll));
}

void SetOnListScrollFrameBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollFrameBegin = [nodeId, node, extraParam](const Dimension& offset, const ScrollState& state) ->
            ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_FRAME_BEGIN;
        event.componentAsyncEvent.data[0].f32 = static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUIAsyncEvent(&event);
        scrollRes.offset = Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    ListModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}

void SetOnListScrollStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStart = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_START;
        SendArkUIAsyncEvent(&event);
    };
    ListModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}

void SetOnListScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStop = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_STOP;
        SendArkUIAsyncEvent(&event);
    };
    ListModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG