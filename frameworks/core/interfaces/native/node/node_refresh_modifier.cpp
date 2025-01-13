/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/node_refresh_modifier.h"

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"

namespace OHOS::Ace::NG {
namespace {
const float ERROR_FLOAT_CODE = -1.0f;

void SetRefreshing(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshing(frameNode, static_cast<bool>(value));
}

ArkUI_Bool GetRefreshing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(RefreshModelNG::GetRefreshing(frameNode));
}

void SetRefreshOffset(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshOffset(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetRefreshOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetRefreshOffset(frameNode, Dimension(0.0f, DimensionUnit::VP));
}

void SetPullToRefresh(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullToRefresh(frameNode, value);
}

void ResetPullToRefresh(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetPullToRefresh(frameNode, true);
}

void SetRefreshContent(ArkUINodeHandle node, ArkUINodeHandle content)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto contentNode = reinterpret_cast<FrameNode*>(content);
    CHECK_NULL_VOID(contentNode);
    RefreshModelNG::SetCustomBuilder(frameNode, contentNode);
}

void SetPullDownRatio(ArkUINodeHandle node, ArkUI_Float32 ratio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    float value = 0.0;
    if (LessNotEqual(ratio, 0.0)) {
        value = 0.0;
    } else if (GreatNotEqual(ratio, 1.0)) {
        value = 1.0;
    }
    value = ratio ;
    std::optional<float> ratioValue = value;
    RefreshModelNG::SetPullDownRatio(frameNode, ratioValue);
}

void ResetPullDownRatio(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> ratioValue = std::nullopt;
    RefreshModelNG::SetPullDownRatio(frameNode, ratioValue);
}

ArkUI_Float32 GetPullDownRatio(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return RefreshModelNG::GetPullDownRatio(frameNode);
}

ArkUI_Float32 GetRefreshOffset(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return RefreshModelNG::GetRefreshOffset(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Bool GetPullToRefresh(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(RefreshModelNG::GetPullToRefresh(frameNode));
}
} // namespace
namespace NodeModifier {

const ArkUIRefreshModifier* GetRefreshModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIRefreshModifier modifier = {
        .setRefreshing = SetRefreshing,
        .getRefreshing = GetRefreshing,
        .setRefreshOffset = SetRefreshOffset,
        .resetRefreshOffset = ResetRefreshOffset,
        .setPullToRefresh = SetPullToRefresh,
        .resetPullToRefresh = ResetPullToRefresh,
        .setRefreshContent = SetRefreshContent,
        .setPullDownRatio = SetPullDownRatio,
        .resetPullDownRatio = ResetPullDownRatio,
        .getPullDownRatio = GetPullDownRatio,
        .getRefreshOffset = GetRefreshOffset,
        .getPullToRefresh = GetPullToRefresh,
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

const CJUIRefreshModifier* GetCJUIRefreshModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIRefreshModifier modifier = {
        .setRefreshing = SetRefreshing,
        .getRefreshing = GetRefreshing,
        .setRefreshContent = SetRefreshContent,
        .setRefreshOffset = SetRefreshOffset,
        .resetRefreshOffset = ResetRefreshOffset,
        .setPullToRefresh = SetPullToRefresh,
        .resetPullToRefresh = ResetPullToRefresh,
        .setPullDownRatio = SetPullDownRatio,
        .resetPullDownRatio = ResetPullDownRatio,
        .getPullDownRatio = GetPullDownRatio,
        .getRefreshOffset = GetRefreshOffset,
        .getPullToRefresh = GetPullToRefresh,
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

void SetRefreshOnStateChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const int32_t value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_STATE_CHANGE;
        event.componentAsyncEvent.data[0].i32 = value;
        SendArkUISyncEvent(&event);
    };
    RefreshModelNG::SetOnStateChange(frameNode, std::move(onEvent));
}

void SetOnRefreshing(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_REFRESHING;
        SendArkUISyncEvent(&event);
    };
    RefreshModelNG::SetOnRefreshing(frameNode, std::move(onEvent));
}

void SetRefreshOnOffsetChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const float value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_ON_OFFSET_CHANGE;
        event.componentAsyncEvent.data[0].f32 = value;
        SendArkUISyncEvent(&event);
    };
    RefreshModelNG::SetOnOffsetChange(frameNode, std::move(onEvent));
}

void SetRefreshChangeEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const std::string& value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_REFRESH_CHANGE_EVENT;
        bool newValue = value == "true";
        event.componentAsyncEvent.data[0].u32 = newValue;
        SendArkUISyncEvent(&event);
    };
    RefreshModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}

void ResetRefreshOnStateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnStateChange(frameNode, nullptr);
}
void ResetOnRefreshing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnRefreshing(frameNode, nullptr);
}
void ResetRefreshOnOffsetChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetOnOffsetChange(frameNode, nullptr);
}
void ResetRefreshChangeEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefreshModelNG::SetChangeEvent(frameNode, nullptr);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
