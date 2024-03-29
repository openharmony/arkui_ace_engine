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
#include "core/interfaces/native/node/node_refresh_modifier.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/element_register.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/properties/alignment.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

namespace OHOS::Ace::NG {
namespace {

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
} // namespace
namespace NodeModifier {

const ArkUIRefreshModifier* GetRefreshModifier()
{
    static const ArkUIRefreshModifier modifier = { SetRefreshing, GetRefreshing, SetRefreshOffset, ResetRefreshOffset,
        SetPullToRefresh, ResetPullToRefresh, SetRefreshContent };
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
        SendArkUIAsyncEvent(&event);
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
        SendArkUIAsyncEvent(&event);
    };
    RefreshModelNG::SetOnRefreshing(frameNode, std::move(onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
