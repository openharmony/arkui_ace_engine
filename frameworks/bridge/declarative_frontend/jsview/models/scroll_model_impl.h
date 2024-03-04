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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SCROLL_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SCROLL_MODEL_IMPL_H

#include "core/components_ng/pattern/scroll/scroll_model.h"

namespace OHOS::Ace::Framework {

class ScrollModelImpl : public ScrollModel {
public:
    ScrollModelImpl() = default;
    ~ScrollModelImpl() override = default;

    void Create() override;
    RefPtr<ScrollControllerBase> GetOrCreateController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;
    void SetAxis(Axis axis) override;
    void SetOnScrollBegin(OnScrollBeginEvent&& event) override;
    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event) override;
    void SetOnScroll(NG::ScrollEvent&& event) override;
    void SetOnScrollEdge(NG::ScrollEdgeEvent&& event) override;
    void SetOnScrollEnd(NG::ScrollEndEvent&& event) override;
    void SetOnScrollStart(OnScrollStartEvent&& event) override {}
    void SetOnScrollStop(OnScrollStopEvent&& event) override {}
    void SetOnReachStart(OnReachEvent&& onReachStart) override {};
    void SetOnReachEnd(OnReachEvent&& onReachEnd) override {};
    void SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy) override;
    void InitScrollBar(const RefPtr<ScrollBarTheme>& theme, const std::pair<bool, Color>& color,
        const std::pair<bool, Dimension>& width, EdgeEffect effect) override;
    void SetDisplayMode(int displayMode) override;
    void SetScrollBarWidth(const Dimension& dimension) override;
    void SetScrollBarColor(const Color& color) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled) override;
    void SetHasWidth(bool hasWidth) override;
    void SetHasHeight(bool hasHeight) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override {};
    void SetScrollEnabled(bool scrollEnabled) override {};
    void SetFriction(double friction) override {};
    void SetScrollSnap(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide) override {};
    void SetEnablePaging(bool enablePaging) override {};
    void SetInitialOffset(const NG::OffsetT<CalcDimension>& offset) override {};
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SCROLL_MODEL_IMPL_H
