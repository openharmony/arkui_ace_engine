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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_event_hub.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RefreshModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRefreshing(FrameNode* frameNode, const std::optional<bool>& isRefreshing);
    static void SetLoadingText(FrameNode* frameNode, const std::optional<std::string>& loadingText);
    static void SetCustomBuilder(FrameNode* frameNode, const RefPtr<NG::UINode>& customBuilder);
    static void SetIsCustomBuilderExist(FrameNode* frameNode, bool isCustomBuilderExist);
    static void SetRefreshOffset(FrameNode* frameNode, const std::optional<Dimension>& offset);
    static void SetPullToRefresh(FrameNode* frameNode, const std::optional<bool>& isPullToRefresh);
    static void SetPullDownRatio(FrameNode* frameNode, const std::optional<float>& pullDownRatio);
    static void SetOnStateChange(FrameNode* frameNode, StateChangeEvent&& stateChange);
    static void SetOnOffsetChange(FrameNode* frameNode, OffsetChangeEvent&& dragOffset);
    static void ResetOnOffsetChange(FrameNode* frameNode);
    static void SetOnRefreshing(FrameNode* frameNode, RefreshingEvent&& refreshing);
    static void SetChangeEvent(FrameNode* frameNode, RefreshChangeEvent&& changeEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_MODEL_STATIC_H
