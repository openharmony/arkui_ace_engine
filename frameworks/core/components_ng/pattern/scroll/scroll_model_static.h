/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_STATIC_H

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ScrollModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static RefPtr<ScrollProxy> GetOrCreateScrollBarProxy(FrameNode* frameNode);

    static void SetAxis(FrameNode* frameNode, const std::optional<Axis>& axis);
    static void SetScrollBar(FrameNode* frameNode, const std::optional<DisplayMode> barState);
    static void SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& dimension);
    static void SetNestedScroll(FrameNode* frameNode,
        const std::optional<NestedScrollMode>& forward, const std::optional<NestedScrollMode>& backward);
    static void SetScrollEnabled(FrameNode* frameNode, const std::optional<bool> scrollEnabled);
    static void SetFriction(FrameNode* frameNode, const std::optional<float> friction);
    static void SetScrollSnap(FrameNode* frameNode, std::optional<ScrollSnapAlign> scrollSnapAlignOpt,
        const std::optional<Dimension>& intervalSize, const std::vector<Dimension>& snapPaginations,
        const std::optional<bool>& enableSnapToStart, const std::optional<bool>& enableSnapToEnd);
    static void SetEnablePaging(FrameNode* frameNode, const std::optional<bool> enablePaging);
    static void SetInitialOffset(FrameNode* frameNode, const std::optional<OffsetT<CalcDimension>>& offset);
    static void SetEdgeEffect(FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect,
        const std::optional<bool>& alwaysEnabled, EffectEdge edge = EffectEdge::ALL);

    static void SetOnScroll(FrameNode* frameNode, NG::ScrollEvent&& event);
    static void SetOnWillScroll(FrameNode* frameNode, NG::ScrollEventWithReturn&& event);
    static void SetOnDidScroll(FrameNode* frameNode, NG::ScrollEventWithState&& event);
    static void SetOnScrollEdge(FrameNode* frameNode, NG::ScrollEdgeEvent&& event);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& event);
    static void SetOnScrollEnd(FrameNode* frameNode, ScrollEndEvent&& event);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& event);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& event);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_STATIC_H