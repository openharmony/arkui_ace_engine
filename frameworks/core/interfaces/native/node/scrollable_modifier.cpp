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

ArkUI_Int32 GetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    (*values)[0] = ScrollableModelNG::GetEdgeEffect(frameNode);
    (*values)[1] = ScrollableModelNG::GetAlwaysEnabled(frameNode);
    return 2;
}

void SetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
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
} // namespace

namespace NodeModifier {
const ArkUIScrollableModifier* GetScrollableModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIScrollableModifier modifier = {
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
