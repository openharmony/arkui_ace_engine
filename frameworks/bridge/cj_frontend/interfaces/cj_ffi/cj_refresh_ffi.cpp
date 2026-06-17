/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_refresh_ffi.h"

#include <optional>

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
NG::RefreshModelNG* GetRefreshModel()
{
    static NG::RefreshModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Refresh");
        if (module == nullptr) {
            LOGF_ABORT("Can't find Refresh dynamic module");
        }
        cachedModel = reinterpret_cast<NG::RefreshModelNG*>(module->GetModel());
    }
    return cachedModel;
}

} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkRefreshCreate(bool refreshing, double offsetValue, int32_t offsetUnit, int32_t friction)
{
    RefPtr<RefreshTheme> theme = GetTheme<RefreshTheme>();
    if (!theme) {
        LOGE("Refresh Theme is null");
        return;
    }
    if (GetRefreshModel() == nullptr) {
        LOGE("Refresh Instance is null");
        return;
    }
    GetRefreshModel()->Create();
    GetRefreshModel()->SetLoadingDistance(theme->GetLoadingDistance());
    GetRefreshModel()->SetRefreshDistance(theme->GetRefreshDistance());
    GetRefreshModel()->SetProgressDistance(theme->GetProgressDistance());
    GetRefreshModel()->SetProgressDiameter(theme->GetProgressDiameter());
    GetRefreshModel()->SetMaxDistance(theme->GetMaxDistance());
    GetRefreshModel()->SetShowTimeDistance(theme->GetShowTimeDistance());
    GetRefreshModel()->SetTextStyle(theme->GetTextStyle());
    GetRefreshModel()->SetProgressColor(theme->GetProgressColor());
    GetRefreshModel()->SetProgressBackgroundColor(theme->GetBackgroundColor());

    GetRefreshModel()->SetRefreshing(refreshing);

    Dimension offset(offsetValue, static_cast<DimensionUnit>(offsetUnit));
    if (offset.Value() <= 0.0) {
        GetRefreshModel()->SetRefreshDistance(theme->GetRefreshDistance());
    } else {
        GetRefreshModel()->SetUseOffset(true);
        GetRefreshModel()->SetIndicatorOffset(offset);
    }

    GetRefreshModel()->SetFriction(friction);
    if (friction <= 0) {
        GetRefreshModel()->IsRefresh(true);
    }
}

void FfiOHOSAceFrameworkRefreshCreateWithChangeEvent(
    bool refreshing, double offsetValue, int32_t offsetUnit, int32_t friction, void (*callback)(bool isRefreshing))
{
    RefPtr<RefreshTheme> theme = GetTheme<RefreshTheme>();
    if (!theme) {
        LOGE("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent, Refresh Theme is null");
        return;
    }
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->Create();
    GetRefreshModel()->SetLoadingDistance(theme->GetLoadingDistance());
    GetRefreshModel()->SetRefreshDistance(theme->GetRefreshDistance());
    GetRefreshModel()->SetProgressDistance(theme->GetProgressDistance());
    GetRefreshModel()->SetProgressDiameter(theme->GetProgressDiameter());
    GetRefreshModel()->SetTextStyle(theme->GetTextStyle());
    GetRefreshModel()->SetProgressColor(theme->GetProgressColor());
    GetRefreshModel()->SetMaxDistance(theme->GetMaxDistance());
    GetRefreshModel()->SetShowTimeDistance(theme->GetShowTimeDistance());
    GetRefreshModel()->SetProgressBackgroundColor(theme->GetBackgroundColor());

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto changeEvent = [lambda = CJLambda::Create(callback), node = targetNode](const std::string& value) -> void {
        LOGI("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent refreshing is %{public}s", value.c_str());
        PipelineContext::SetCallBackNode(node);
        bool newValue = value == "true";
        lambda(newValue);
    };
    GetRefreshModel()->SetChangeEvent(std::move(changeEvent));
    GetRefreshModel()->SetRefreshing(refreshing);

    Dimension offset(offsetValue, static_cast<DimensionUnit>(offsetUnit));
    if (offset.Value() <= 0.0) {
        GetRefreshModel()->SetRefreshDistance(theme->GetRefreshDistance());
    } else {
        LOGI("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent, offset value > 0");
        GetRefreshModel()->SetUseOffset(true);
        GetRefreshModel()->SetIndicatorOffset(offset);
    }

    GetRefreshModel()->SetFriction(friction);
    if (friction <= 0) {
        GetRefreshModel()->IsRefresh(true);
    }
}

void FfiOHOSAceFrameworkRefreshPop()
{
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshPop, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->Pop();
}

void FfiOHOSAceFrameworkRefreshOnStateChange(void (*callback)(const int32_t value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onStateChange = [func = CJLambda::Create(callback), node = targetNode](const int32_t& key) {
        LOGI("Refresh.OnStateChange");
        PipelineContext::SetCallBackNode(node);
        func(key);
    };
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshOnStateChange, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetOnStateChange(std::move(onStateChange));
}

void FfiOHOSAceFrameworkRefreshOnRefreshing(void (*callback)())
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onRefreshing = [func = CJLambda::Create(callback), node = targetNode]() {
        LOGI("Refresh.OnRefreshing");
        PipelineContext::SetCallBackNode(node);
        func();
    };
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshOnRefreshing, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetOnRefreshing(std::move(onRefreshing));
}

void FfiOHOSAceFrameworkRefreshOnOffsetChange(void (*callback)(const float value))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onOffsetChange = [func = CJLambda::Create(callback), node = targetNode](const float value) {
        LOGI("Refresh.OnRefreshing");
        PipelineContext::SetCallBackNode(node);
        func(value);
    };
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshOnOffsetChange, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetOnOffsetChange(std::move(onOffsetChange));
}

void FfiOHOSAceFrameworkRefreshOffset(double offsetValue, int32_t offsetUnit)
{
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshOffset, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetRefreshOffset(Dimension(offsetValue, static_cast<OHOS::Ace::DimensionUnit>(offsetUnit)));
}

void FfiOHOSAceFrameworkRefreshPullToRefresh(bool value)
{
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshPullToRefresh, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetPullToRefresh(value);
}

void FfiOHOSAceFrameworkRefreshPullDownRatio(double ratio)
{
    float value = 0.0;
    if (LessNotEqual(ratio, 0.0)) {
        value = 0.0;
    } else if (GreatNotEqual(ratio, 1.0)) {
        value = 1.0;
    }
    value = ratio;
    std::optional<float> ratioValue = value;
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshPullDownRatio, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetPullDownRatio(ratioValue);
}

void FfiOHOSAceFrameworkRefreshResetPullDownRatio()
{
    std::optional<float> ratioValue = std::nullopt;
    if (GetRefreshModel() == nullptr) {
        LOGE("FfiOHOSAceFrameworkRefreshResetPullDownRatio, Refresh Instance is null");
        return;
    }
    GetRefreshModel()->SetPullDownRatio(ratioValue);
}
}
