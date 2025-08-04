/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components/scroll/scroll_controller_base.h"
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
    void SetOnWillScroll(NG::ScrollEventWithReturn&& event) override;
    void SetOnDidScroll(NG::ScrollEventWithState&& event) override;
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
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge = EffectEdge::ALL) override;
    void SetHasWidth(bool hasWidth) override {}
    void SetHasHeight(bool hasHeight) override {}
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;
    void SetFriction(double friction) override;
    void SetScrollSnap(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide) override;
    void SetEnablePaging(bool enablePaging) override;
    void SetInitialOffset(const OffsetT<CalcDimension>& offset) override;
    void CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithResourceObjIntervalSize(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithResourceObjSnapPaginations(
        const std::vector<Dimension>& snapPaginations, std::vector<RefPtr<ResourceObject>>& resObjs) override;
    void CreateWithResourceObjScrollBarColor(const RefPtr<ResourceObject>& resObj) override;
    void SetMaxZoomScale(float scale) override;
    void SetMinZoomScale(float scale) override;
    void SetZoomScale(float scale) override;
    void ResetZoomScale() override;
    void SetZoomScaleChangeEvent(std::function<void(float)>&& event) override;
    void SetEnableBouncesZoom(bool enable) override;
    void SetOnDidZoom(std::function<void(float)>&& event) override;
    void SetOnZoomStart(std::function<void()>&& event) override;
    void SetOnZoomStop(std::function<void()>&& event) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetScrollController(
        FrameNode* frameNode, const RefPtr<ScrollControllerBase>& scroller, const RefPtr<ScrollProxy>& proxy);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static int32_t GetScrollEnabled(FrameNode* frameNode);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static float GetFriction(FrameNode* frameNode);
    static void SetFriction(FrameNode* frameNode, double friction);
    static ScrollSnapOptions GetScrollSnap(FrameNode* frameNode);
    static void SetScrollSnap(FrameNode* frameNode, ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide);
    static int32_t GetScrollBar(FrameNode* frameNode);
    static void SetScrollBar(FrameNode* frameNode, DisplayMode barState);
    static int32_t GetAxis(FrameNode* frameNode);
    static void SetAxis(FrameNode* frameNode, Axis axis);
    static uint32_t GetScrollBarColor(FrameNode* frameNode);
    static void SetScrollBarColor(FrameNode* frameNode, const Color& color);
    static float GetScrollBarWidth(FrameNode* frameNode);
    static void SetScrollBarWidth(FrameNode* frameNode, const Dimension& dimension);
    static int32_t GetEdgeEffect(FrameNode* frameNode);
    static int32_t GetEdgeEffectAlways(FrameNode* frameNode);
    static void SetEdgeEffect(
        FrameNode* frameNode, const EdgeEffect& edgeEffect, bool alwaysEnabled, EffectEdge edge);
    static int32_t GetEnablePaging(FrameNode* frameNode);
    static void SetEnablePaging(FrameNode* frameNode, bool enablePaging);
    static void SetOnScroll(FrameNode* frameNode, NG::ScrollEvent&& event);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& event);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& event);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& event);

    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static void SetOnScrollEdge(FrameNode* frameNode, NG::ScrollEdgeEvent&& event);
    static NestedScrollOptions GetNestedScroll(FrameNode* frameNode);
    static ScrollEdgeType GetOnScrollEdge(FrameNode* frameNode);
    static void CreateWithResourceObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void SetOnWillScroll(FrameNode* frameNode, NG::ScrollEventWithReturn&& event);
    static void SetOnDidScroll(FrameNode* frameNode, NG::ScrollEventWithState&& event);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetInitialOffset(FrameNode* frameNode, const OffsetT<CalcDimension>& offset);
    static void SetScrollBarProxy(FrameNode* frameNode, const RefPtr<ScrollProxy>& proxy);
    static void CreateWithResourceObjIntervalSize(FrameNode* frameNode, std::vector<RefPtr<ResourceObject>>& resObjs);
    static void CreateWithResourceObjSnapPaginations(FrameNode* frameNode,
        const std::vector<Dimension>& snapPaginations, std::vector<RefPtr<ResourceObject>>& resObjs);
    static void CreateWithResourceObjScrollBarColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void SetMaxZoomScale(FrameNode* frameNode, float scale);
    static float GetMaxZoomScale(FrameNode* frameNode);
    static void SetMinZoomScale(FrameNode* frameNode, float scale);
    static float GetMinZoomScale(FrameNode* frameNode);
    static void SetZoomScale(FrameNode* frameNode, float scale);
    static void ResetZoomScale(FrameNode* frameNode);
    static float GetZoomScale(FrameNode* frameNode);
    static void SetEnableBouncesZoom(FrameNode* frameNode, bool enable);
    static bool GetEnableBouncesZoom(FrameNode* frameNode);
    static void SetOnDidZoom(FrameNode* frameNode, std::function<void(float)>&& event);
    static void SetOnZoomStart(FrameNode* frameNode, std::function<void()>&& event);
    static void SetOnZoomStop(FrameNode* frameNode, std::function<void()>&& event);
private:
    static bool CheckSnapPaginations(const std::vector<Dimension>& snapPaginations);
    static bool HasResObj(const std::vector<RefPtr<ResourceObject>>& resObjs);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_MODEL_NG_H
