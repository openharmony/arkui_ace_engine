/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_MODEL_IMPL_H

#include "core/components_ng/pattern/grid/grid_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class GridModelImpl : public OHOS::Ace::GridModel {
public:
    void Create(
        const RefPtr<ScrollControllerBase>& positionController, const RefPtr<ScrollProxy>& scrollBarProxy) override;
    void Pop() override;
    void SetLayoutOptions(GridLayoutOptions options) override {};
    void SetColumnsTemplate(const std::string& value) override;
    void SetRowsTemplate(const std::string& value) override;
    void SetColumnsGap(const Dimension& value) override;
    void SetRowsGap(const Dimension& value) override;
    void SetGridHeight(const Dimension& value) override;
    void SetScrollBarMode(DisplayMode value) override;
    void SetScrollBarColor(const std::string& value) override;
    void SetScrollBarWidth(const std::string& value) override;
    void SetCachedCount(int32_t value, bool show) override;
    void SetIsRTL(TextDirection direction) override;
    void SetLayoutDirection(FlexDirection value) override;
    void SetMaxCount(int32_t value) override;
    void SetMinCount(int32_t value) override;
    void SetCellLength(int32_t value) override;
    void SetEditable(bool value) override;
    void SetMultiSelectable(bool value) override;
    void SetSupportAnimation(bool value) override;
    void SetSupportDragAnimation(bool value) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override {};
    void SetScrollEnabled(bool scrollEnabled) override {};
    void SetFriction(double friction) override {};
    void SetAlignItems(GridItemAlignment itemAlign) override {};
    void SetOnScrollToIndex(std::function<void(const BaseEventInfo*)>&& value) override;
    void SetOnScrollBarUpdate(
        std::function<std::pair<std::optional<float>, std::optional<float>>(int32_t, Dimension)>&& value) override;
    void SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value) override;
    void SetOnItemDragEnter(std::function<void(const ItemDragInfo&)>&& value) override;
    void SetOnItemDragMove(std::function<void(const ItemDragInfo&, int32_t, int32_t)>&& value) override;
    void SetOnItemDragLeave(std::function<void(const ItemDragInfo&, int32_t)>&& value) override;
    void SetOnItemDrop(std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>&& value) override;

    void SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll) override {};
    void SetOnScrollIndex(std::function<void(int32_t, int32_t)>&& onScrollIndex) override {};
    void SetOnScrollFrameBegin(
        std::function<ScrollFrameResult(Dimension, ScrollState)>&& onScrollFrameBegin) override {};
    void SetOnScrollStart(std::function<void()>&& onScrollStart) override {};
    void SetOnScrollStop(std::function<void()>&& onScrollStop) override {};
    void SetOnReachStart(std::function<void()>&& onReachStart) override {};
    void SetOnReachEnd(std::function<void()>&& onReachEnd) override {};

    DisplayMode GetDisplayMode() const override
    {
        return DisplayMode::OFF;
    };

    RefPtr<ScrollControllerBase> CreatePositionController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GRID_MODEL_IMPL_H
