/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_REFRESH_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_REFRESH_MODEL_IMPL_H

#include <optional>
#include <string>

#include "frameworks/core/components/refresh/refresh_component.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT RefreshModelImpl : public RefreshModel {
public:
    void Create() override;
    void Pop() override;
    void SetRefreshing(bool isRefreshing) override;
    void SetRefreshDistance(const Dimension& refreshDistance) override;
    void SetUseOffset(bool isUseOffset) override;
    void SetIndicatorOffset(const Dimension& indicatorOffset) override;
    void SetFriction(int32_t friction) override;
    void IsRefresh(bool isRefresh) override;
    void SetLoadingDistance(const Dimension& loadingDistance) override;
    void SetProgressDistance(const Dimension& progressDistance) override;
    void SetProgressDiameter(const Dimension& progressDiameter) override;
    void SetMaxDistance(const Dimension& maxDistance) override;
    void SetIsShowLastTime(bool IsShowLastTime) override;
    void SetShowTimeDistance(const Dimension& showTimeDistance) override;
    void SetTextStyle(const TextStyle& textStyle) override;
    void SetProgressColor(const Color& progressColor) override;
    void SetProgressBackgroundColor(const Color& backgroundColor) override;
    void SetOnStateChange(std::function<void(const int32_t)>&& stateChange) override;
    void SetOnRefreshing(std::function<void()>&& refreshing) override;
    void SetOnOffsetChange(std::function<void(const float)>&& offsetChange) override;
    void ResetOnOffsetChange() override;
    void SetChangeEvent(std::function<void(const std::string)>&& changeEvent) override;
    void SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder) override;
    void SetLoadingText(const std::string& loadingText) override;
    void SetRefreshOffset(const Dimension& offset) override {};
    void SetPullToRefresh(bool isPullToRefresh) override {};
private:
    static RefPtr<RefreshComponent> GetComponent();
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_REFRESH_MODEL_IMPL_H
