/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_NG_H

#include "core/components_ng/pattern/scroll/scroll_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ScrollModelNG : public ScrollModel {
public:
    ScrollModelNG() = default;
    ~ScrollModelNG() override = default;

    void Create() override;
    RefPtr<ScrollControllerBase> GetOrCreateController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;
    void SetAxis(Axis axis) override;
    void SetOnScrollBegin(OnScrollBeginEvent&& event) override;
    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event) override;
    void SetOnScroll(NG::ScrollEvent&& event) override;
    void SetOnScrollEdge(NG::ScrollEdgeEvent&& event) override;
    void SetOnScrollEnd(NG::ScrollEndEvent&& event) override;
    void SetOnScrollStart(OnScrollStartEvent&& event) override;
    void SetOnScrollStop(OnScrollStopEvent&& event) override;
    void SetOnReachStart(OnReachEvent&& onReachStart) override;
    void SetOnReachEnd(OnReachEvent&& onReachEnd) override;
    void SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy) override;
    void InitScrollBar(const RefPtr<ScrollBarTheme>& theme, const std::pair<bool, Color>& color,
        const std::pair<bool, Dimension>& width, EdgeEffect effect) override;
    void SetDisplayMode(int displayMode) override;
    void SetScrollBarWidth(const Dimension& dimension) override;
    void SetScrollBarColor(const Color& color) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled) override;
    void SetHasWidth(bool hasWidth) override {}
    void SetHasHeight(bool hasHeight) override {}
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;
    void SetFriction(double friction) override;
    void SetScrollSnap(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide) override;

    static RefPtr<FrameNode> CreateScroll(int32_t nodeId);
    static void SetScrollController(
        FrameNode* frameNode, const RefPtr<ScrollControllerBase>& scroller, const RefPtr<ScrollProxy>& proxy);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static void SetFriction(FrameNode* frameNode, double friction);
    static void SetScrollSnap(FrameNode* frameNode, ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide);
    static void SetScrollBar(FrameNode* frameNode, DisplayMode barState);
    static void SetAxis(FrameNode* frameNode, Axis axis);
    static void SetScrollBarColor(FrameNode* frameNode, const Color& color);
    static void SetScrollBarWidth(FrameNode* frameNode, const Dimension& dimension);
    static void SetEdgeEffect(FrameNode* frameNode, const EdgeEffect& edgeEffect, bool alwaysEnabled);
    static void SetOnScroll(FrameNode* frameNode, NG::ScrollEvent&& event);
    void SetEnablePaging(bool enablePaging) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_NG_H
