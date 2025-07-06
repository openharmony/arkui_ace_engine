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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_MODEL_H

#include <memory>
#include <mutex>

#include "core/components/common/layout/constants.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

class ScrollBarTheme;
class ScrollControllerBase;

class ACE_FORCE_EXPORT ScrollModel {
public:
    static ScrollModel* GetInstance();
    virtual ~ScrollModel() = default;

    virtual void Create() = 0;
    virtual RefPtr<ScrollControllerBase> GetOrCreateController() = 0;
    virtual RefPtr<ScrollProxy> CreateScrollBarProxy() = 0;
    virtual void SetAxis(Axis axis) = 0;
    virtual void SetOnScrollBegin(OnScrollBeginEvent&& event) = 0;
    virtual void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event) = 0;
    virtual void SetOnScroll(NG::ScrollEvent&& event) = 0;
    virtual void SetOnWillScroll(NG::ScrollEventWithReturn&& event) {};
    virtual void SetOnDidScroll(NG::ScrollEventWithState&& event) {};
    virtual void SetOnScrollEdge(NG::ScrollEdgeEvent&& event) = 0;
    virtual void SetOnScrollEnd(NG::ScrollEndEvent&& event) = 0;
    virtual void SetOnScrollStart(OnScrollStartEvent&& event) = 0;
    virtual void SetOnScrollStop(OnScrollStopEvent&& event) = 0;
    virtual void SetOnReachStart(OnReachEvent&& onReachStart) = 0;
    virtual void SetOnReachEnd(OnReachEvent&& onReachEnd) = 0;
    virtual void SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy) = 0;
    virtual void InitScrollBar(const RefPtr<ScrollBarTheme>& theme, const std::pair<bool, Color>& color,
        const std::pair<bool, Dimension>& width, EdgeEffect effect) = 0;
    virtual void SetDisplayMode(int displayMode) = 0;
    virtual void SetScrollBarWidth(const Dimension& dimension) = 0;
    virtual void SetScrollBarColor(const Color& color) = 0;
    virtual void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge = EffectEdge::ALL) = 0;
    virtual void SetHasWidth(bool hasWidth) = 0;
    virtual void SetHasHeight(bool hasHeight) = 0;
    virtual void SetNestedScroll(const NestedScrollOptions& nestedOpt) = 0;
    virtual void SetScrollEnabled(bool scrollEnabled) = 0;
    virtual void SetFriction(double friction) = 0;
    virtual void SetScrollSnap(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide) = 0;
    virtual void SetEnablePaging(bool enablePaging) = 0;
    virtual void SetInitialOffset(const NG::OffsetT<CalcDimension>& offset) = 0;
    virtual void CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithResourceObjIntervalSize(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithResourceObjSnapPaginations(std::vector<RefPtr<ResourceObject>>& resObjs) {};
    virtual void SetMaxZoomScale(float scale) {};
    virtual void SetMinZoomScale(float scale) {};
    virtual void SetZoomScale(float scale) {};
    virtual void ResetZoomScale() {};
    virtual void SetEnableBouncesZoom(bool enable) {};
    virtual void SetOnDidZoom(std::function<void(float)>&& event) {};
    virtual void SetOnZoomStart(std::function<void(void)>&& event) {};
    virtual void SetOnZoomStop(std::function<void(void)>&& event) {};

private:
    static std::unique_ptr<ScrollModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_MODEL_H
