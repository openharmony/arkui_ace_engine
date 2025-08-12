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

#include "interfaces/native/node/list_option.h"
#include "interfaces/native/node/node_model.h"

#include "core/components/list/list_theme.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr bool DEFAULT_CACHED_IS_SHOWN = false;
constexpr bool DEFAULT_SCROLL_ENABLE = true;
constexpr int32_t DEFAULT_STICKY_STYLE = 0;
constexpr int32_t DEFAULT_DIRECTION = 0;
constexpr int32_t DEFAULT_SCROLL_BAR = 1;
constexpr int32_t DEFAULT_DIVIDER_VALUES_COUNT = 3;
constexpr float DEFAULT_OFFSET = 0.0f;

constexpr int32_t DEFAULT_EDGE_EFFECT = 0;
constexpr Dimension DEFAULT_FADING_EDGE_LENGTH = Dimension(32.0f, DimensionUnit::VP); // default value

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

void ResetlistLaneMinAndMaxLength(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension minLength = Dimension(-1, DimensionUnit::VP);
    Dimension maxLength = Dimension(-1, DimensionUnit::VP);
    ListModelNG::SetLaneConstrain(frameNode, minLength, maxLength);
}

ArkUI_Int32 GetListLanes(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ListModelNG::GetLanes(frameNode));
}

ArkUI_Float32 GetlistLaneMinLength(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Float32>(ListModelNG::GetLaneMinLength(frameNode));
}

ArkUI_Float32 GetListLaneMaxLength(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Float32>(ListModelNG::GetLaneMaxLength(frameNode));
}

ArkUI_Float32 GetListLaneGutter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto ret = static_cast<ArkUI_Float32>(ListModelNG::GetLaneGutter(frameNode));
    return ret;
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

void SetCachedIsShown(ArkUINodeHandle node, ArkUI_Bool isShown)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetShowCached(frameNode, isShown);
}

void ResetCachedIsShown(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetShowCached(frameNode, DEFAULT_CACHED_IS_SHOWN);
}

ArkUI_Int32 GetCachedIsShown(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ListModelNG::GetShowCached(frameNode));
}

void SetCacheRange(ArkUINodeHandle node, ArkUI_Int32 min, ArkUI_Int32 max)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetCacheRange(frameNode, min, max);
}

void ResetCacheRange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::ResetCacheRange(frameNode);
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

ArkUI_Int32 GetListEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    (*values)[INDEX_0] = ListModelNG::GetEdgeEffect(frameNode);
    (*values)[INDEX_1] = ListModelNG::GetEdgeEffectAlways(frameNode);
    return INDEX_2;
}

void SetListEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, static_cast<EffectEdge>(edge));
}

void ResetListEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEdgeEffect(frameNode, DEFAULT_EDGE_EFFECT, false, EffectEdge::ALL);
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
    if (SystemProperties::ConfigChangePerform()) {
        ListModelNG::CreateWithResourceObjFriction(frameNode, nullptr);
    }
    double friction = -1.0;
    ListModelNG::SetListFriction(frameNode, friction);
}

void GetListNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions options = ListModelNG::GetListNestedScroll(frameNode);
    (*values)[0] = static_cast<ArkUI_Int32>(options.forward);
    (*values)[1] = static_cast<ArkUI_Int32>(options.backward);
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

void CreateWithResourceObjScrollBarColor(ArkUINodeHandle node, void* resObj)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::CreateWithResourceObjScrollBarColor(frameNode, AceType::Claim(resourceObj));
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

    CreateWithResourceObjScrollBarColor(node, nullptr);
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
    ListModelNG::SetScrollSnapAlign(frameNode, static_cast<ScrollSnapAlign>(scrollSnapAlign));
}

void ResetScrollSnapAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, ScrollSnapAlign::NONE);
}

ArkUI_Int32 GetScrollSnapAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetScrollSnapAlign(frameNode);
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

ArkUI_Float32 GetContentStartOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetContentStartOffset(frameNode);
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

ArkUI_Float32 GetContentEndOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ListModelNG::GetContentEndOffset(frameNode);
}

void ListSetDivider(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const int32_t* units, ArkUI_Int32 length)
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

    if (SystemProperties::ConfigChangePerform()) {
        ListModelNG::ParseResObjDividerStrokeWidth(frameNode, nullptr);
        ListModelNG::ParseResObjDividerColor(frameNode, nullptr);
        ListModelNG::ParseResObjDividerStartMargin(frameNode, nullptr);
        ListModelNG::ParseResObjDividerEndMargin(frameNode, nullptr);
        ListModel::GetInstance()->SetDividerColorByUser(false);
    }
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

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto totalChildCount = frameNode->TotalChildCount();
    if (totalChildCount > 0) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_CHILD_NODE_EXIST;
    }
    NodeAdapter::GetNodeAdapterAPI()->attachHostNode(handle, node);
    return ERROR_CODE_NO_ERROR;
}

void ResetNodeAdapter(ArkUINodeHandle node)
{
    NodeAdapter::GetNodeAdapterAPI()->detachHostNode(node);
}

ArkUINodeAdapterHandle GetNodeAdapter(ArkUINodeHandle node)
{
    return NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(node);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return ListModelNG::GetCachedCount(frameNode);
}

void SetScrollToIndex(
    ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment, float options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> extraOffset = options;
    ListModelNG::SetScrollToIndex(frameNode, index, animation, alignment, extraOffset);
}

void SetScrollBy(ArkUINodeHandle node, ArkUI_Float64 x, ArkUI_Float64 y)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollBy(frameNode, x, y);
}

void SetInitialIndex(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetInitialIndex(frameNode, index);
}

void ResetInitialIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetInitialIndex(frameNode, 0);
}

void SetListChildrenMainSize(ArkUINodeHandle node, ArkUIListChildrenMainSize option, ArkUI_Int32 unit)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    for (uint32_t i = 0; i < option->mainSize.size(); i++) {
        if (option->mainSize[i] > 0) {
            option->mainSize[i] =
                Dimension(option->mainSize[i], static_cast<OHOS::Ace::DimensionUnit>(unit)).ConvertToPx();
        }
    }
    if (option->defaultMainSize > 0) {
        option->defaultMainSize =
            Dimension(option->defaultMainSize, static_cast<OHOS::Ace::DimensionUnit>(unit)).ConvertToPx();
    }
    ListModelNG::SetListChildrenMainSize(frameNode, option->defaultMainSize, option->mainSize);
}

void ResetListChildrenMainSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::ResetListChildrenMainSize(frameNode);
}

void SetListCloseAllSwipeActions(ArkUINodeHandle node, void* userData, void (onFinish) (void* userData))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ScrollControllerBase> scrollControllerBase = ListModelNG::GetOrCreateController(frameNode);
    if (onFinish) {
        auto onEvent = [userData, onFinish]() {
            onFinish(userData);
        };
        scrollControllerBase->CloseAllSwipeActions(std::move(onEvent));
    } else {
        scrollControllerBase->CloseAllSwipeActions(nullptr);
    }
}

void SetListFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 maxSpeed)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, maxSpeed);
}

void ResetListFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, -1.0);
}

ArkUI_Int32 GetInitialIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return ListModelNG::GetInitialIndex(frameNode);
}

void GetlistDivider(ArkUINodeHandle node, ArkUIdividerOptions* option, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto divider = ListModelNG::GetDivider(frameNode);
    option->color = divider.color.GetValue();
    option->strokeWidth = divider.strokeWidth.GetNativeValue(static_cast<DimensionUnit>(unit));
    option->startMargin = divider.startMargin.GetNativeValue(static_cast<DimensionUnit>(unit));
    option->endMargin = divider.endMargin.GetNativeValue(static_cast<DimensionUnit>(unit));
}

void SetInitialScroller(ArkUINodeHandle node, ArkUINodeHandle controller, ArkUINodeHandle proxy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto listProxy = AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy));
    auto listController = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller));
    ListModelNG::SetScroller(frameNode, listController, listProxy);
}

void ResetInitialScroller(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ScrollControllerBase> listController;
    RefPtr<ScrollProxy> listProxy;
    ListModelNG::SetScroller(frameNode, listController, listProxy);
}

void SetScrollToItemInGroup(
    ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 indexInGroup, ArkUI_Bool smooth, ArkUI_Int32 align)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollAlign scrollAlign = static_cast<OHOS::Ace::ScrollAlign>(align);
    ListModelNG::ScrollToItemInGroup(frameNode, index, indexInGroup, smooth, scrollAlign);
}

void SetListMaintainVisibleContentPosition(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListMaintainVisibleContentPosition(frameNode, enabled);
}

void ResetListMaintainVisibleContentPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListMaintainVisibleContentPosition(frameNode, false);
}

ArkUI_Bool GetListMaintainVisibleContentPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ListModelNG::GetListMaintainVisibleContentPosition(frameNode);
}

void SetListStackFromEnd(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListStackFromEnd(frameNode, enabled);
}

void ResetListStackFromEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListStackFromEnd(frameNode, false);
}

ArkUI_Bool GetListStackFromEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ListModelNG::GetListStackFromEnd(frameNode);
}

void SetListSyncLoad(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListSyncLoad(frameNode, enabled);
}

void ResetListSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListSyncLoad(frameNode, true);
}

ArkUI_Bool GetListSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return ListModelNG::GetListSyncLoad(frameNode);
}

void SetListFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    NG::ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetListFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}

ArkUI_Int32 GetListFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto mode = ListModelNG::GetFocusWrapMode(frameNode);
    if (mode == FocusWrapMode::WRAP_WITH_ARROW) {
        return 1; // 1 means wrap with arrow
    } else {
        return 0; // 0 means default
    }
}

void SetListFocusWrapMode(ArkUINodeHandle node, int32_t focusWrapMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FocusWrapMode mode = static_cast<FocusWrapMode>(focusWrapMode);
    ListModelNG::SetFocusWrapMode(frameNode, mode);
}

void ResetListFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetFocusWrapMode(frameNode, FocusWrapMode::DEFAULT);
}

void SetShowCached(ArkUINodeHandle node, ArkUI_Bool show)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetShowCached(frameNode, show);
}

void ResetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetShowCached(frameNode, false);
}

ArkUI_Bool GetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ListModelNG::GetShowCached(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIListModifier* GetListModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIListModifier modifier = {
        .setListLanes = SetListLanes,
        .resetListLanes = ResetListLanes,
        .resetlistLaneMinAndMaxLength = ResetlistLaneMinAndMaxLength,
        .getListLanes = GetListLanes,
        .getlistLaneMinLength = GetlistLaneMinLength,
        .getListLaneMaxLength = GetListLaneMaxLength,
        .getListLaneGutter = GetListLaneGutter,
        .setEditMode = SetEditMode,
        .resetEditMode = ResetEditMode,
        .setMultiSelectable = SetMultiSelectable,
        .resetMultiSelectable = ResetMultiSelectable,
        .setChainAnimation = SetChainAnimation,
        .resetChainAnimation = ResetChainAnimation,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .setCachedIsShown = SetCachedIsShown,
        .resetCachedIsShown = ResetCachedIsShown,
        .setCacheRange = SetCacheRange,
        .resetCacheRange = ResetCacheRange,
        .getListFocusWrapMode = GetListFocusWrapMode,
        .setListFocusWrapMode = SetListFocusWrapMode,
        .resetListFocusWrapMode = ResetListFocusWrapMode,
        .getCachedIsShown = GetCachedIsShown,
        .getEnableScrollInteraction = GetEnableScrollInteraction,
        .setEnableScrollInteraction = SetEnableScrollInteraction,
        .resetEnableScrollInteraction = ResetEnableScrollInteraction,
        .getSticky = GetSticky,
        .setSticky = SetSticky,
        .resetSticky = ResetSticky,
        .getListEdgeEffect = GetListEdgeEffect,
        .setListEdgeEffect = SetListEdgeEffect,
        .resetListEdgeEffect = ResetListEdgeEffect,
        .getListDirection = GetListDirection,
        .setListDirection = SetListDirection,
        .resetListDirection = ResetListDirection,
        .getListFriction = GetListFriction,
        .setListFriction = SetListFriction,
        .resetListFriction = ResetListFriction,
        .getListNestedScroll = GetListNestedScroll,
        .setListNestedScroll = SetListNestedScroll,
        .resetListNestedScroll = ResetListNestedScroll,
        .getListScrollBar = GetListScrollBar,
        .setListScrollBar = SetListScrollBar,
        .resetListScrollBar = ResetListScrollBar,
        .getListScrollBarWidth = GetListScrollBarWidth,
        .setListScrollBarWidth = SetListScrollBarWidth,
        .resetListScrollBarWidth = ResetListScrollBarWidth,
        .getListScrollBarColor = GetListScrollBarColor,
        .setListScrollBarColor = SetListScrollBarColor,
        .resetListScrollBarColor = ResetListScrollBarColor,
        .getAlignListItem = GetAlignListItem,
        .setAlignListItem = SetAlignListItem,
        .resetAlignListItem = ResetAlignListItem,
        .setScrollSnapAlign = SetScrollSnapAlign,
        .resetScrollSnapAlign = ResetScrollSnapAlign,
        .getScrollSnapAlign = GetScrollSnapAlign,
        .setContentStartOffset = SetContentStartOffset,
        .resetContentStartOffset = ResetContentStartOffset,
        .getContentStartOffset = GetContentStartOffset,
        .setContentEndOffset = SetContentEndOffset,
        .resetContentEndOffset = ResetContentEndOffset,
        .getContentEndOffset = GetContentEndOffset,
        .listSetDivider = ListSetDivider,
        .listResetDivider = ListResetDivider,
        .setChainAnimationOptions = SetChainAnimationOptions,
        .resetChainAnimationOptions = ResetChainAnimationOptions,
        .getListSpace = GetListSpace,
        .setListSpace = SetListSpace,
        .resetListSpace = ResetListSpace,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .getCachedCount = GetCachedCount,
        .setScrollToIndex = SetScrollToIndex,
        .setScrollBy = SetScrollBy,
        .setInitialIndex = SetInitialIndex,
        .resetInitialIndex = ResetInitialIndex,
        .setListChildrenMainSize = SetListChildrenMainSize,
        .resetListChildrenMainSize = ResetListChildrenMainSize,
        .setListCloseAllSwipeActions = SetListCloseAllSwipeActions,
        .getInitialIndex = GetInitialIndex,
        .getlistDivider = GetlistDivider,
        .setInitialScroller = SetInitialScroller,
        .resetInitialScroller = ResetInitialScroller,
        .setScrollToItemInGroup = SetScrollToItemInGroup,
        .setListMaintainVisibleContentPosition = SetListMaintainVisibleContentPosition,
        .resetListMaintainVisibleContentPosition = ResetListMaintainVisibleContentPosition,
        .getListMaintainVisibleContentPosition = GetListMaintainVisibleContentPosition,
        .setListStackFromEnd = SetListStackFromEnd,
        .resetListStackFromEnd = ResetListStackFromEnd,
        .getListStackFromEnd = GetListStackFromEnd,
        .setListSyncLoad = SetListSyncLoad,
        .resetListSyncLoad = ResetListSyncLoad,
        .getListSyncLoad = GetListSyncLoad,
        .setListFadingEdge = SetListFadingEdge,
        .resetListFadingEdge = ResetListFadingEdge,
        .setShowCached = SetShowCached,
        .resetShowCached = ResetShowCached,
        .getShowCached = GetShowCached,
        .setOnListScrollIndexCallBack = SetOnListScrollIndexCallBack,
        .setOnScrollVisibleContentChange = SetOnScrollVisibleContentChange,
        .setOnItemMove = SetOnItemMove,
        .setOnItemDragStart = SetOnItemDragStart,
        .setOnItemDragEnter = SetOnItemDragEnter,
        .setOnItemDragMove = SetOnItemDragMove,
        .setOnItemDragLeave = SetOnItemDragLeave,
        .setOnItemDrop = SetOnItemDrop,
        .setOnListScrollFrameBeginCallBack = SetOnListScrollFrameBeginCallBack,
        .setOnListWillScrollCallBack = SetOnListWillScrollCallBack,
        .setOnListDidScrollCallBack = SetOnListDidScrollCallBack,
        .setOnListReachStartCallBack = SetOnListReachStartCallBack,
        .setOnListReachEndCallBack = SetOnListReachEndCallBack,
        .setOnListScrollStartCallBack = SetOnListScrollStartCallBack,
        .setOnListScrollStopCallBack = SetOnListScrollStopCallBack,
        .resetOnListScrollIndex = ResetOnListScrollIndex,
        .resetOnScrollVisibleContentChange = ResetOnScrollVisibleContentChange,
        .resetOnItemMove = ResetOnItemMove,
        .resetOnItemDragStart = ResetOnItemDragStart,
        .resetOnItemDragEnter = ResetOnItemDragEnter,
        .resetOnItemDragMove = ResetOnItemDragMove,
        .resetOnItemDragLeave = ResetOnItemDragLeave,
        .resetOnItemDrop = ResetOnItemDrop,
        .resetOnListScrollStart = ResetOnListScrollStart,
        .resetOnListScrollStop = ResetOnListScrollStop,
        .resetOnListScrollFrameBegin = ResetOnListScrollFrameBegin,
        .resetOnListWillScroll = ResetOnListWillScroll,
        .resetOnListDidScroll = ResetOnListDidScroll,
        .resetOnListReachStart = ResetOnListReachStart,
        .resetOnListReachEnd = ResetOnListReachEnd,
        .createWithResourceObjFriction = CreateWithResourceObjFriction,
        .parseResObjDividerStrokeWidth = ParseResObjDividerStrokeWidth,
        .parseResObjDividerColor = ParseResObjDividerColor,
        .parseResObjDividerStartMargin = ParseResObjDividerStartMargin,
        .parseResObjDividerEndMargin = ParseResObjDividerEndMargin,
        .createWithResourceObjLaneConstrain = CreateWithResourceObjLaneConstrain,
        .createWithResourceObjScrollBarColor = CreateWithResourceObjScrollBarColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIListModifier* GetCJUIListModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIListModifier modifier = {
        .setListLanes = SetListLanes,
        .resetListLanes = ResetListLanes,
        .setEditMode = SetEditMode,
        .resetEditMode = ResetEditMode,
        .setMultiSelectable = SetMultiSelectable,
        .resetMultiSelectable = ResetMultiSelectable,
        .setChainAnimation = SetChainAnimation,
        .resetChainAnimation = ResetChainAnimation,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .getEnableScrollInteraction = GetEnableScrollInteraction,
        .setEnableScrollInteraction = SetEnableScrollInteraction,
        .resetEnableScrollInteraction = ResetEnableScrollInteraction,
        .getSticky = GetSticky,
        .setSticky = SetSticky,
        .resetSticky = ResetSticky,
        .getListEdgeEffect = GetListEdgeEffect,
        .setListEdgeEffect = SetListEdgeEffect,
        .resetListEdgeEffect = ResetListEdgeEffect,
        .getListDirection = GetListDirection,
        .setListDirection = SetListDirection,
        .resetListDirection = ResetListDirection,
        .getListFriction = GetListFriction,
        .setListFriction = SetListFriction,
        .resetListFriction = ResetListFriction,
        .getListFocusWrapMode = GetListFocusWrapMode,
        .setListFocusWrapMode = SetListFocusWrapMode,
        .resetListFocusWrapMode = ResetListFocusWrapMode,
        .getListNestedScroll = GetListNestedScroll,
        .setListNestedScroll = SetListNestedScroll,
        .resetListNestedScroll = ResetListNestedScroll,
        .getListScrollBar = GetListScrollBar,
        .setListScrollBar = SetListScrollBar,
        .resetListScrollBar = ResetListScrollBar,
        .getListScrollBarWidth = GetListScrollBarWidth,
        .setListScrollBarWidth = SetListScrollBarWidth,
        .resetListScrollBarWidth = ResetListScrollBarWidth,
        .getListScrollBarColor = GetListScrollBarColor,
        .setListScrollBarColor = SetListScrollBarColor,
        .resetListScrollBarColor = ResetListScrollBarColor,
        .getAlignListItem = GetAlignListItem,
        .setAlignListItem = SetAlignListItem,
        .resetAlignListItem = ResetAlignListItem,
        .setScrollSnapAlign = SetScrollSnapAlign,
        .resetScrollSnapAlign = ResetScrollSnapAlign,
        .setContentStartOffset = SetContentStartOffset,
        .resetContentStartOffset = ResetContentStartOffset,
        .setContentEndOffset = SetContentEndOffset,
        .resetContentEndOffset = ResetContentEndOffset,
        .listSetDivider = ListSetDivider,
        .listResetDivider = ListResetDivider,
        .setChainAnimationOptions = SetChainAnimationOptions,
        .resetChainAnimationOptions = ResetChainAnimationOptions,
        .getListSpace = GetListSpace,
        .setListSpace = SetListSpace,
        .resetListSpace = ResetListSpace,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .getCachedCount = GetCachedCount,
        .setScrollToIndex = SetScrollToIndex,
        .setScrollBy = SetScrollBy,
        .setInitialIndex = SetInitialIndex,
        .resetInitialIndex = ResetInitialIndex,
        .setListChildrenMainSize = SetListChildrenMainSize,
        .resetListChildrenMainSize = ResetListChildrenMainSize,
        .setListCloseAllSwipeActions = SetListCloseAllSwipeActions,
        .setListFlingSpeedLimit = SetListFlingSpeedLimit,
        .resetListFlingSpeedLimit = ResetListFlingSpeedLimit,
        .getInitialIndex = GetInitialIndex,
        .getlistDivider = GetlistDivider,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
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
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnScroll(frameNode, std::move(onScroll));
}

void SetOnListScrollFrameBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollFrameBegin = [nodeId, node, extraParam](
                                  const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_FRAME_BEGIN;
        event.componentAsyncEvent.data[0].f32 = static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUISyncEvent(&event);
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
        SendArkUISyncEvent(&event);
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
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

void SetOnListWillScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onWillScroll = [nodeId, node, extraParam](const Dimension& offset, const ScrollState& state,
                            ScrollSource source) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_WILL_SCROLL;
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        event.componentAsyncEvent.data[2].i32 = static_cast<int>(source);
        SendArkUISyncEvent(&event);
        scrollRes.offset =
            Dimension(event.componentAsyncEvent.data[0].f32, usePx ? DimensionUnit::PX : DimensionUnit::VP);
        return scrollRes;
    };
    ScrollableModelNG::SetOnWillScroll(frameNode, std::move(onWillScroll));
}

void SetOnListDidScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDidScroll = [nodeId, node, extraParam](const Dimension& offset, const ScrollState& state) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.subKind = ON_LIST_DID_SCROLL;
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int32_t>(state);
        SendArkUISyncEvent(&event);
    };
    ScrollableModelNG::SetOnDidScroll(frameNode, std::move(onDidScroll));
}

void SetOnListScrollIndex(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollIndex = [nodeId, node, extraParam](int32_t first, int32_t last, int32_t center) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_INDEX;
        event.componentAsyncEvent.data[0].i32 = first;
        event.componentAsyncEvent.data[1].i32 = last;
        event.componentAsyncEvent.data[2].i32 = center;
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}

void SetOnListReachStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachStart = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_REACH_START;
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void SetOnListReachEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachEnd = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_REACH_END;
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}

void SetOnListScrollVisibleContentChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollVisibleContentChange = [node, extraParam](const ListItemIndex start, const ListItemIndex end) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_SCROLL_VISIBLE_CONTENT_CHANGE;
        event.componentAsyncEvent.data[0].i32 = start.index;
        event.componentAsyncEvent.data[1].i32 = start.area;
        event.componentAsyncEvent.data[2].i32 = start.indexInGroup;
        event.componentAsyncEvent.data[3].i32 = end.index;
        event.componentAsyncEvent.data[4].i32 = end.area;
        event.componentAsyncEvent.data[5].i32 = end.indexInGroup;
        SendArkUISyncEvent(&event);
    };
    ListModelNG::SetOnScrollVisibleContentChange(frameNode, std::move(onScrollVisibleContentChange));
}

void SetOnListScrollIndexCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollIndex = reinterpret_cast<OnScrollIndexEvent*>(extraParam);
        ListModelNG::SetOnScrollIndex(frameNode, std::move(*onScrollIndex));
    } else {
        ListModelNG::SetOnScrollIndex(frameNode, nullptr);
    }
}

void SetOnScrollVisibleContentChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollVisibleContentChange = reinterpret_cast<OnScrollVisibleContentChangeEvent*>(extraParam);
        ListModelNG::SetOnScrollVisibleContentChange(frameNode, std::move(*onScrollVisibleContentChange));
    } else {
        ListModelNG::SetOnScrollVisibleContentChange(frameNode, nullptr);
    }
}

void SetOnItemMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemMove = reinterpret_cast<OnItemMoveEvent*>(extraParam);
        ListModelNG::SetOnItemMove(frameNode, std::move(*onItemMove));
    } else {
        ListModelNG::SetOnItemMove(frameNode, nullptr);
    }
}

void SetOnItemDragStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragStart = reinterpret_cast<OnItemDragStartFunc*>(extraParam);
        ListModelNG::SetOnItemDragStart(frameNode, std::move(*onItemDragStart));
    } else {
        ListModelNG::SetOnItemDragStart(frameNode, nullptr);
    }
}

void SetOnItemDragEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragEnter = reinterpret_cast<OnItemDragEnterFunc*>(extraParam);
        ListModelNG::SetOnItemDragEnter(frameNode, std::move(*onItemDragEnter));
    } else {
        ListModelNG::SetOnItemDragEnter(frameNode, nullptr);
    }
}

void SetOnItemDragMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragMove = reinterpret_cast<OnItemDragMoveFunc*>(extraParam);
        ListModelNG::SetOnItemDragMove(frameNode, std::move(*onItemDragMove));
    } else {
        ListModelNG::SetOnItemDragMove(frameNode, nullptr);
    }
}

void SetOnItemDragLeave(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragLeave = reinterpret_cast<OnItemDragLeaveFunc*>(extraParam);
        ListModelNG::SetOnItemDragLeave(frameNode, std::move(*onItemDragLeave));
    } else {
        ListModelNG::SetOnItemDragLeave(frameNode, nullptr);
    }
}

void SetOnItemDrop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDrop = reinterpret_cast<OnItemDropFunc*>(extraParam);
        ListModelNG::SetOnItemDrop(frameNode, std::move(*onItemDrop));
    } else {
        ListModelNG::SetOnItemDrop(frameNode, nullptr);
    }
}

void SetOnListScrollFrameBeginCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollFrameBegin = reinterpret_cast<OnScrollFrameBeginEvent*>(extraParam);
        ListModelNG::SetOnScrollFrameBegin(frameNode, std::move(*onScrollFrameBegin));
    } else {
        ListModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
    }
}

void SetOnListWillScrollCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onWillScroll = reinterpret_cast<OnWillScrollEvent*>(extraParam);
        ScrollableModelNG::SetOnWillScroll(frameNode, std::move(*onWillScroll));
    } else {
        ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
    }
}

void SetOnListDidScrollCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onDidScroll = reinterpret_cast<OnScrollEvent*>(extraParam);
        ScrollableModelNG::SetOnDidScroll(frameNode, std::move(*onDidScroll));
    } else {
        ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
    }
}

void SetOnListReachStartCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onReachStart = reinterpret_cast<OnReachEvent*>(extraParam);
        ListModelNG::SetOnReachStart(frameNode, std::move(*onReachStart));
    } else {
        ListModelNG::SetOnReachStart(frameNode, nullptr);
    }
}

void SetOnListReachEndCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onReachEnd = reinterpret_cast<OnReachEvent*>(extraParam);
        ListModelNG::SetOnReachEnd(frameNode, std::move(*onReachEnd));
    } else {
        ListModelNG::SetOnReachEnd(frameNode, nullptr);
    }
}

void SetOnListScrollStartCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollStart = reinterpret_cast<OnScrollStartEvent*>(extraParam);
        ListModelNG::SetOnScrollStart(frameNode, std::move(*onScrollStart));
    } else {
        ListModelNG::SetOnScrollStart(frameNode, nullptr);
    }
}

void SetOnListScrollStopCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollStop = reinterpret_cast<OnScrollStopEvent*>(extraParam);
        ListModelNG::SetOnScrollStop(frameNode, std::move(*onScrollStop));
    } else {
        ListModelNG::SetOnScrollStop(frameNode, nullptr);
    }
}

void ResetOnListScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScroll(frameNode, nullptr);
}

void ResetOnListScrollIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScrollIndex(frameNode, nullptr);
}

void ResetOnScrollVisibleContentChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScrollVisibleContentChange(frameNode, nullptr);
}

void ResetOnItemMove(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemMove(frameNode, nullptr);
}

void ResetOnItemDragStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemDragStart(frameNode, nullptr);
}

void ResetOnItemDragEnter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemDragEnter(frameNode, nullptr);
}

void ResetOnItemDragMove(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemDragMove(frameNode, nullptr);
}

void ResetOnItemDragLeave(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemDragLeave(frameNode, nullptr);
}

void ResetOnItemDrop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnItemDrop(frameNode, nullptr);
}

void ResetOnListScrollStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScrollStart(frameNode, nullptr);
}

void ResetOnListScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScrollStop(frameNode, nullptr);
}

void ResetOnListScrollFrameBegin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
}

void ResetOnListWillScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
}

void ResetOnListDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
}

void ResetOnListReachStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnReachStart(frameNode, nullptr);
}

void ResetOnListReachEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetOnReachEnd(frameNode, nullptr);
}

void CreateWithResourceObjFriction(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::CreateWithResourceObjFriction(frameNode, AceType::Claim(resourceObj));
}

void ParseResObjDividerStrokeWidth(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::ParseResObjDividerStrokeWidth(frameNode, AceType::Claim(resourceObj));
}

void ParseResObjDividerColor(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::ParseResObjDividerColor(frameNode, AceType::Claim(resourceObj));
    ListModelNG::SetDividerColorByUser(frameNode, false);
}

void ParseResObjDividerStartMargin(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::ParseResObjDividerStartMargin(frameNode, AceType::Claim(resourceObj));
}

void ParseResObjDividerEndMargin(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ListModelNG::ParseResObjDividerEndMargin(frameNode, AceType::Claim(resourceObj));
}

void CreateWithResourceObjLaneConstrain(ArkUINodeHandle node, void* resObjMinLengthValue, void* resObjMaxLengthValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourcObjMinLengthValue = reinterpret_cast<ResourceObject*>(resObjMinLengthValue);
    auto* resourceObjMaxLengthValue = reinterpret_cast<ResourceObject*>(resObjMaxLengthValue);
    ListModelNG::CreateWithResourceObjLaneConstrain(
        frameNode, AceType::Claim(resourcObjMinLengthValue), AceType::Claim(resourceObjMaxLengthValue));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
