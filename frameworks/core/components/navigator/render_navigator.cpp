/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/navigator/render_navigator.h"

#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

RenderNavigator::RenderNavigator()
{
    Initialize();
}

RefPtr<RenderNode> RenderNavigator::Create()
{
    return AceType::MakeRefPtr<RenderNavigator>();
}

void RenderNavigator::Initialize()
{
    auto wp = AceType::WeakClaim(this);
    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer_->SetOnClick([wp](const ClickInfo&) {
        auto navigator = wp.Upgrade();
        if (navigator) {
            LOGI("navigator OnClick called");
            navigator->NavigatePage();
        }
    });
}

void RenderNavigator::NavigatePage()
{
    auto pipelineContext = GetContext().Upgrade();
    if (!pipelineContext) {
        LOGE("pipelineContext is null");
        return;
    }
    pipelineContext->NavigatePage(static_cast<uint8_t>(type_), uri_);
}

void RenderNavigator::Update(const RefPtr<Component>& component)
{
    const RefPtr<NavigatorComponent> navigator = AceType::DynamicCast<NavigatorComponent>(component);
    if (navigator) {
        LOGI("navigator Update uri = %{public}s", navigator->GetUri().c_str());
        uri_ = navigator->GetUri();
        type_ = navigator->GetType();
        active_ = navigator->GetActive();
    }
    if (active_ == true) {
        NavigatePage();
    }
    MarkNeedLayout();
}

void RenderNavigator::PerformLayout()
{
    LOGD("RenderNavigator PerformLayout");
    if (!GetChildren().empty()) {
        auto child = GetChildren().front();
        child->Layout(GetLayoutParam());
        SetLayoutSize(child->GetLayoutSize());
    }
}

void RenderNavigator::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!clickRecognizer_) {
        return;
    }
    result.emplace_back(clickRecognizer_);
}

} // namespace OHOS::Ace
