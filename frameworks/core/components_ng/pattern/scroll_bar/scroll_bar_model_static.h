/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollBarModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<ScrollProxy> SetScrollBarProxy(FrameNode* frameNode, const RefPtr<ScrollProxy>& proxy);
    static void SetDirection(FrameNode* frameNode, const std::optional<Axis>& direction);
    static void SetState(FrameNode* frameNode, const std::optional<DisplayMode>& state);
    static void SetEnableNestedScroll(FrameNode* frameNode, const std::optional<bool>& enable);
    static void SetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern);
    static void UnSetNestedScroll(RefPtr<FrameNode>& frameNode, RefPtr<ScrollablePattern>& pattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_MODEL_STATIC_H
 