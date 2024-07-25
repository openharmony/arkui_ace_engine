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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_NG_H

#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/utils/macros.h"
#include "frameworks/core/components/common/properties/color.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_model.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RefreshModelNG : public RefreshModel {
public:
    void Create() override;
    void SetRefreshing(bool isRefreshing) override;
    void SetIndicatorOffset(const Dimension& indicatorOffset) override;
    void SetFriction(int32_t friction) override;
    void SetProgressColor(const Color& progressColor) override;
    void SetOnStateChange(StateChangeEvent&& stateChange) override;
    void SetOnRefreshing(RefreshingEvent&& refreshing) override;
    void SetChangeEvent(RefreshChangeEvent&& changeEvent) override;
    void SetOnOffsetChange(OffsetChangeEvent&& dragOffset) override;
    void ResetOnOffsetChange() override;
    void SetPullDownRatio(const std::optional<float>& pullDownRatio) override;
    void SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder) override;
    void SetLoadingText(const std::string& loadingText) override;
    void ResetLoadingText() override;
    void SetRefreshOffset(const Dimension& offset) override;
    void SetPullToRefresh(bool isPullToRefresh) override;
    void SetIsCustomBuilderExist(bool isCustomBuilderExist) override;
    // @deprecated
    void Pop() override {}
    void SetRefreshDistance(const Dimension& refreshDistance) override {}
    void SetUseOffset(bool isUseOffset) override {}
    void IsRefresh(bool isRefresh) override {}
    void SetLoadingDistance(const Dimension& loadingDistance) override {}
    void SetProgressDistance(const Dimension& progressDistance) override {}
    void SetProgressDiameter(const Dimension& progressDiameter) override {}
    void SetMaxDistance(const Dimension& maxDistance) override {}
    void SetIsShowLastTime(bool IsShowLastTime) override {}
    void SetShowTimeDistance(const Dimension& showTimeDistance) override {}
    void SetTextStyle(const TextStyle& textStyle) override {}
    void SetProgressBackgroundColor(const Color& backgroundColor) override {}

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRefreshing(FrameNode* frameNode, bool isRefreshing);
    static bool GetRefreshing(FrameNode* frameNode);
    static void SetCustomBuilder(FrameNode* frameNode, FrameNode* customBuilder);
    static void SetOnStateChange(FrameNode* frameNode, StateChangeEvent&& stateChange);
    static void SetOnOffsetChange(FrameNode* frameNode, OffsetChangeEvent&& dragOffset);
    static void ResetOnOffsetChange(FrameNode* frameNode);
    static void SetOnRefreshing(FrameNode* frameNode, RefreshingEvent&& refreshing);
    static void SetRefreshOffset(FrameNode* frameNode, const Dimension& offset);
    static void SetPullToRefresh(FrameNode* frameNode, bool isPullToRefresh);
    static void SetPullDownRatio(FrameNode* frameNode, const std::optional<float>& pullDownRatio);
    static float GetPullDownRatio(FrameNode* frameNode);
    static Dimension GetRefreshOffset(FrameNode* frameNode);
    static bool GetPullToRefresh(FrameNode* frameNode);
    static void SetChangeEvent(FrameNode* frameNode, RefreshChangeEvent&& changeEvent);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_NG_H
