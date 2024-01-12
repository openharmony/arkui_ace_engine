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
    void SetChangeEvent(ChangeEvent&& changeEvent) override;
    void SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder) override;
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

    static void SetOnStateChange(FrameNode* frameNode, StateChangeEvent&& stateChange);
    static void SetOnRefreshing(FrameNode* frameNode, RefreshingEvent&& refreshing);

};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_NG_H
