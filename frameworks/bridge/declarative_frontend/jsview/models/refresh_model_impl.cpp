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

#include "frameworks/bridge/declarative_frontend/jsview/models/refresh_model_impl.h"

#include <utility>

#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void RefreshModelImpl::Create()
{
    auto refreshComponent = AceType::MakeRefPtr<RefreshComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(refreshComponent);
    ViewStackProcessor::GetInstance()->Push(refreshComponent);
}

RefPtr<RefreshComponent> RefreshModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<RefreshComponent>(stack->GetMainComponent());
    return component;
}

void RefreshModelImpl::Pop()
{
    JSContainerBase::Pop();
}

void RefreshModelImpl::SetRefreshing(bool isRefreshing)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetRefreshing(isRefreshing);
}

void RefreshModelImpl::SetRefreshDistance(const Dimension& refreshDistance)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetRefreshDistance(refreshDistance);
}

void RefreshModelImpl::SetUseOffset(bool isUseOffset)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetUseOffset(isUseOffset);
}

void RefreshModelImpl::SetIndicatorOffset(const Dimension& indicatorOffset)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetIndicatorOffset(indicatorOffset);
}

void RefreshModelImpl::SetFriction(int32_t friction)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetFriction(friction);
}

void RefreshModelImpl::IsRefresh(bool isRefresh)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->IsRefresh(isRefresh);
}

void RefreshModelImpl::SetLoadingDistance(const Dimension& loadingDistance)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetLoadingDistance(loadingDistance);
}

void RefreshModelImpl::SetProgressDistance(const Dimension& progressDistance)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetProgressDistance(progressDistance);
}

void RefreshModelImpl::SetProgressDiameter(const Dimension& progressDiameter)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetProgressDiameter(progressDiameter);
}

void RefreshModelImpl::SetMaxDistance(const Dimension& maxDistance)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetMaxDistance(maxDistance);
}

void RefreshModelImpl::SetIsShowLastTime(bool IsShowLastTime)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetShowLastTime(IsShowLastTime);
}

void RefreshModelImpl::SetShowTimeDistance(const Dimension& showTimeDistance)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetShowTimeDistance(showTimeDistance);
}

void RefreshModelImpl::SetTextStyle(const TextStyle& textStyle)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetTextStyle(textStyle);
}

void RefreshModelImpl::SetProgressColor(const Color& progressColor)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetProgressColor(progressColor);
}

void RefreshModelImpl::SetProgressBackgroundColor(const Color& backgroundColor)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetBackgroundColor(backgroundColor);
}

void RefreshModelImpl::SetOnStateChange(std::function<void(const int32_t)>&& stateChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnStateChange(std::move(stateChange));
}

void RefreshModelImpl::SetOnRefreshing(std::function<void()>&& refreshing)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnRefreshing(std::move(refreshing));
}

void RefreshModelImpl::SetOnOffsetChange(std::function<void(const float)>&& offsetChange) {}

void RefreshModelImpl::ResetOnOffsetChange() {}

void RefreshModelImpl::SetChangeEvent(std::function<void(const std::string)>&& changeEvent)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto eventMarker = EventMarker(changeEvent);
    component->SetChangeEvent(eventMarker);
}

void RefreshModelImpl::SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder) {}
void RefreshModelImpl::SetLoadingText(const std::string& loadingText) {}
} // namespace OHOS::Ace::Framework
