/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H

#include <mutex>

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace {
class WaterFlowModel {
public:
    static WaterFlowModel* GetInstance();
    virtual ~WaterFlowModel() = default;

    virtual void Create() = 0;
    virtual void SetFooter(std::function<void()>&& footer) = 0;
    virtual void SetFooterWithFrameNode(const RefPtr<NG::UINode>& footer) = 0;
    virtual RefPtr<ScrollControllerBase> CreateScrollController() = 0;
    virtual RefPtr<ScrollProxy> CreateScrollBarProxy() = 0;
    virtual void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) = 0;
    virtual void SetLayoutMode(NG::WaterFlowLayoutMode mode) = 0;

    virtual void SetColumnsTemplate(const std::string& value) = 0;
    virtual void SetRowsTemplate(const std::string& value) = 0;

    // itemConstraintSize
    virtual void SetItemMinWidth(const Dimension& minWidth) = 0;
    virtual void SetItemMinHeight(const Dimension& minHeight) = 0;
    virtual void SetItemMaxWidth(const Dimension& maxWidth) = 0;
    virtual void SetItemMaxHeight(const Dimension& maxHeight) = 0;

    virtual void SetColumnsGap(const Dimension& value) = 0;
    virtual void SetRowsGap(const Dimension& value) = 0;

    virtual void SetLayoutDirection(FlexDirection value) = 0;
    virtual void SetNestedScroll(const NestedScrollOptions& nestedOpt) = 0;
    virtual void SetScrollEnabled(bool scrollEnabled) = 0;

    virtual void SetOnReachStart(OnReachEvent&& onReachStart) = 0;
    virtual void SetOnReachEnd(OnReachEvent&& onReachEnd) = 0;
    virtual void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin) = 0;
    virtual void SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll) = 0;
    virtual void SetOnScrollStart(std::function<void()>&& onScrollStart) = 0;
    virtual void SetOnScrollStop(std::function<void()>&& onScrollStop) = 0;
    virtual void SetOnScrollIndex(std::function<void(int32_t, int32_t)>&& onScrollIndex) = 0;

    virtual void SetFriction(double friction) = 0;
    virtual void SetCachedCount(int32_t value, bool show = false) = 0;

    virtual void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge = EffectEdge::ALL) = 0;
    EdgeEffect GetEdgeEffect() const
    {
        return EdgeEffect::NONE;
    }
    bool GetAlwaysEnableEdgeEffect() const
    {
        return false;
    }
    static DisplayMode GetDisplayMode()
    {
        return DisplayMode::OFF;
    }
    virtual void SetScrollBarMode(DisplayMode value) = 0;
    virtual void SetScrollBarColor(const std::string& value) = 0;
    virtual void SetScrollBarWidth(const std::string& value) = 0;
    virtual RefPtr<NG::WaterFlowSections> GetOrCreateWaterFlowSections()
    {
        return nullptr;
    }

    virtual void ResetSections() {}

private:
    static std::unique_ptr<WaterFlowModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H
