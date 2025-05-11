/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/scrollable_modifier.h"

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_BACKTOTOP = false;
ArkUI_Int32 GetContentClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    return static_cast<int32_t>(ScrollableModelNG::GetContentClip(frameNode));
}

void SetContentClip(ArkUINodeHandle node, ArkUI_Int32 mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto val = static_cast<ContentClipMode>(mode);
    if (val < ContentClipMode::CONTENT_ONLY || val > ContentClipMode::SAFE_AREA) {
        val = ContentClipMode::DEFAULT;
    }
    ScrollableModelNG::SetContentClip(frameNode, static_cast<ContentClipMode>(mode), nullptr);
}

void ResetContentClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ScrollableModelNG::SetContentClip(frameNode, ContentClipMode::DEFAULT, nullptr);
}

void SetOnReachStartCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onReachStart = reinterpret_cast<OnReachEvent*>(extraParam);
        ScrollableModelNG::SetOnReachStart(frameNode, std::move(*onReachStart));
    } else {
        ScrollableModelNG::SetOnReachStart(frameNode, nullptr);
    }
}

void ResetOnReachStartCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnReachStart(frameNode, nullptr);
}

void SetOnReachEndCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onReachEnd = reinterpret_cast<OnReachEvent*>(extraParam);
        ScrollableModelNG::SetOnReachEnd(frameNode, std::move(*onReachEnd));
    } else {
        ScrollableModelNG::SetOnReachEnd(frameNode, nullptr);
    }
}

void ResetOnReachEndCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnReachEnd(frameNode, nullptr);
}

void SetOnWillScrollCallBack(ArkUINodeHandle node, void* extraParam)
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

void ResetOnWillScrollCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
}

void SetOnDidScrollCallBack(ArkUINodeHandle node, void* extraParam)
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

void ResetOnDidScrollCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
}

void SetOnScrollFrameBeginCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollFrameBegin = reinterpret_cast<OnScrollFrameBeginEvent*>(extraParam);
        ScrollableModelNG::SetOnScrollFrameBegin(frameNode, std::move(*onScrollFrameBegin));
    } else {
        ScrollableModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
    }
}

void ResetOnScrollFrameBeginCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
}

void SetOnScrollStartCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollStart = reinterpret_cast<OnScrollStartEvent*>(extraParam);
        ScrollableModelNG::SetOnScrollStart(frameNode, std::move(*onScrollStart));
    } else {
        ScrollableModelNG::SetOnScrollStart(frameNode, nullptr);
    }
}

void ResetOnScrollStartCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnScrollStart(frameNode, nullptr);
}

void SetOnScrollStopCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollStop = reinterpret_cast<OnScrollStopEvent*>(extraParam);
        ScrollableModelNG::SetOnScrollStop(frameNode, std::move(*onScrollStop));
    } else {
        ScrollableModelNG::SetOnScrollStop(frameNode, nullptr);
    }
}

void ResetOnScrollStopCallBack(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnScrollStop(frameNode, nullptr);
}

ArkUI_Int32 GetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    (*values)[0] = ScrollableModelNG::GetEdgeEffect(frameNode);
    (*values)[1] = ScrollableModelNG::GetAlwaysEnabled(frameNode);
    return 2;
}

void SetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetEdgeEffect(
        frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetEdgeEffect(frameNode, EdgeEffect::SPRING, false);
}

void SetFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    constexpr Dimension DEFAULT_FADING_EDGE_LENGTH(32.0f, DimensionUnit::VP);
    ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}

void GetFadingEdge(ArkUINodeHandle node, ArkUIInt32orFloat32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    (*values)[0].i32 = static_cast<int32_t>(ScrollableModelNG::GetFadingEdge(frameNode));
    (*values)[1].f32 = ScrollableModelNG::GetFadingEdgeLength(frameNode);
}

void SetFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 maxSpeed)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, maxSpeed);
}

void ResetFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, -1.0);
}

float GetFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1.0f);
    return ScrollableModelNG::GetMaxFlingSpeed(frameNode);
}

void SetBackToTop(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetBackToTop(frameNode, value);
}

void ResetBackToTop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::ResetBackToTop(frameNode);
}

int32_t GetBackToTop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_BACKTOTOP);
    return ScrollableModelNG::GetBackToTop(frameNode);
}

void SetScrollBarMargin(ArkUINodeHandle node, ArkUI_Float32 marginStart, ArkUI_Int32 marginStartLengthUnit,
    ArkUI_Float32 marginEnd, ArkUI_Int32 marginEndLengthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarMargin scrollBarMargin;
    scrollBarMargin.start_ = Dimension(marginStart, static_cast<OHOS::Ace::DimensionUnit>(marginStartLengthUnit));
    scrollBarMargin.end_ = Dimension(marginEnd, static_cast<OHOS::Ace::DimensionUnit>(marginEndLengthUnit));
    ScrollableModelNG::SetScrollBarMargin(frameNode, scrollBarMargin);
}

void ResetScrollBarMargin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::ResetScrollBarMargin(frameNode);
}

void GetScrollBarMargin(ArkUINodeHandle node, ArkUIInt32orFloat32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollBarMargin scrollBarMargin;
    ScrollableModelNG::GetScrollBarMargin(frameNode, scrollBarMargin);
    (*values)[0].i32 = scrollBarMargin.start_.ConvertToVp();
    (*values)[1].i32 = scrollBarMargin.end_.ConvertToVp();
}
} // namespace

namespace NodeModifier {
const ArkUIScrollableModifier* GetScrollableModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIScrollableModifier modifier = {
        .getContentClip = GetContentClip,
        .setContentClip = SetContentClip,
        .resetContentClip = ResetContentClip,
        .getEdgeEffect = GetEdgeEffect,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setFadingEdge = SetFadingEdge,
        .resetFadingEdge = ResetFadingEdge,
        .getFadingEdge = GetFadingEdge,
        .setOnReachStartCallBack = SetOnReachStartCallBack,
        .resetOnReachStartCallBack = ResetOnReachStartCallBack,
        .setOnReachEndCallBack = SetOnReachEndCallBack,
        .resetOnReachEndCallBack = ResetOnReachEndCallBack,
        .setOnWillScrollCallBack = SetOnWillScrollCallBack,
        .resetOnWillScrollCallBack = ResetOnWillScrollCallBack,
        .setOnDidScrollCallBack = SetOnDidScrollCallBack,
        .resetOnDidScrollCallBack = ResetOnDidScrollCallBack,
        .setOnScrollFrameBeginCallBack = SetOnScrollFrameBeginCallBack,
        .resetOnScrollFrameBeginCallBack = ResetOnScrollFrameBeginCallBack,
        .setOnScrollStartCallBack = SetOnScrollStartCallBack,
        .resetOnScrollStartCallBack = ResetOnScrollStartCallBack,
        .setOnScrollStopCallBack = SetOnScrollStopCallBack,
        .resetOnScrollStopCallBack = ResetOnScrollStopCallBack,
        .getFlingSpeedLimit = GetFlingSpeedLimit,
        .setFlingSpeedLimit = SetFlingSpeedLimit,
        .resetFlingSpeedLimit = ResetFlingSpeedLimit,
        .setBackToTop = SetBackToTop,
        .resetBackToTop = ResetBackToTop,
        .getBackToTop = GetBackToTop,
        .setScrollBarMargin = SetScrollBarMargin,
        .resetScrollBarMargin = ResetScrollBarMargin,
        .getScrollBarMargin = GetScrollBarMargin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
