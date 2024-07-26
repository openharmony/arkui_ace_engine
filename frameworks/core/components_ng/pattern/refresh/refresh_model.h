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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_H

#include <mutex>
#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/utils/macros.h"
#include "frameworks/core/components/common/properties/color.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT RefreshModel {
public:
    static RefreshModel* GetInstance();
    virtual ~RefreshModel() = default;

    virtual void Create() = 0;
    virtual void Pop() = 0;
    virtual void SetRefreshing(bool isRefreshing) = 0;
    virtual void SetRefreshDistance(const Dimension& refreshDistance) = 0;
    virtual void SetUseOffset(bool isUseOffset) = 0;
    virtual void SetIndicatorOffset(const Dimension& indicatorOffset) = 0;
    virtual void SetFriction(int32_t friction) = 0;
    virtual void IsRefresh(bool isRefresh) = 0;

    virtual void SetLoadingDistance(const Dimension& loadingDistance) = 0;
    virtual void SetProgressDistance(const Dimension& progressDistance) = 0;
    virtual void SetProgressDiameter(const Dimension& progressDiameter) = 0;
    virtual void SetMaxDistance(const Dimension& maxDistance) = 0;
    virtual void SetIsShowLastTime(bool IsShowLastTime) = 0;
    virtual void SetShowTimeDistance(const Dimension& showTimeDistance) = 0;

    virtual void SetTextStyle(const TextStyle& textStyle) = 0;
    virtual void SetProgressColor(const Color& progressColor) = 0;
    virtual void SetProgressBackgroundColor(const Color& backgroundColor) = 0;
    virtual void SetOnStateChange(std::function<void(const int32_t)>&& stateChange) = 0;
    virtual void SetOnRefreshing(std::function<void()>&& refreshing) = 0;
    virtual void SetOnOffsetChange(std::function<void(const float)>&& dragOffset) = 0;
    virtual void ResetOnOffsetChange() = 0;
    virtual void SetPullDownRatio(const std::optional<float>& pullDownRatio) {}
    virtual void SetChangeEvent(std::function<void(const std::string)>&& changeEvent) = 0;
    virtual void SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder) = 0;
    virtual void SetLoadingText(const std::string& loadingText) = 0;
    virtual void ResetLoadingText() {}
    virtual void SetRefreshOffset(const Dimension& offset) = 0;
    virtual void SetPullToRefresh(bool isPullToRefresh) = 0;
    virtual void SetIsCustomBuilderExist(bool isCustomBuilderExist) {}

private:
    static std::unique_ptr<RefreshModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_MODEL_H
