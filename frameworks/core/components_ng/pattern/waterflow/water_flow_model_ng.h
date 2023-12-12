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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowModelNG : public WaterFlowModel {
public:
    void Create() override;
    void SetFooter(std::function<void()>&& footer) override;
    RefPtr<ScrollControllerBase> CreateScrollController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;
    void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) override;

    void SetColumnsTemplate(const std::string& value) override;
    void SetRowsTemplate(const std::string& value) override;

    void SetItemMinWidth(const Dimension& minWidth) override;
    void SetItemMinHeight(const Dimension& minHeight) override;
    void SetItemMaxWidth(const Dimension& maxWidth) override;
    void SetItemMaxHeight(const Dimension& maxHeight) override;

    void SetColumnsGap(const Dimension& value) override;
    void SetRowsGap(const Dimension& value) override;

    void SetLayoutDirection(FlexDirection value) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;

    void SetOnReachStart(OnReachEvent&& onReachStart) override;
    void SetOnReachEnd(OnReachEvent&& onReachEnd) override;
    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin) override;
    void SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll) override;
    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart) override;
    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop) override;
    void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex) override;

    void SetFriction(double friction) override;
    void SetCachedCount(int32_t value) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled) override;

    void SetScrollBarMode(DisplayMode value) override;
    void SetScrollBarColor(const std::string& value) override;
    void SetScrollBarWidth(const std::string& value) override;

    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetRowsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static void SetColumnsGap(FrameNode* frameNode, const Dimension& value);
    static void SetRowsGap(FrameNode* frameNode, const Dimension& value);
    static void SetItemMinWidth(FrameNode* frameNode, const Dimension& minWidth);
    static void SetItemMaxWidth(FrameNode* frameNode, const Dimension& maxWidth);
    static void SetItemMinHeight(FrameNode* frameNode, const Dimension& minHeight);
    static void SetItemMaxHeight(FrameNode* frameNode, const Dimension& maxHeight);
    static void SetLayoutDirection(FrameNode* frameNode, FlexDirection value);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetFriction(FrameNode* frameNode, double friction);

};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H