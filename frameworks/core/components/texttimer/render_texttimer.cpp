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

#include "core/components/texttimer/render_texttimer.h"

#include "base/i18n/localization.h"
#include "core/components/stack/stack_element.h"
#include "core/components/text/render_text.h"
#include "core/components/texttimer/texttimer_component.h"

namespace OHOS::Ace {
RenderTextTimer::RenderTextTimer(){}

RenderTextTimer::~RenderTextTimer()
{
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
}

void RenderTextTimer::Update(const RefPtr<Component>& component)
{
    auto timerComponent = AceType::DynamicCast<TextTimerComponent>(component);
    if (!timerComponent) {
        LOGE("input timerComponent is incorrect type or null.");
        return;
    }

    textComponent_ = timerComponent->GetTextComponent();
    inputCount_ = timerComponent->GetInputCount();
    isCountDown_ = timerComponent->GetIsCountDown();
    format_ = timerComponent->GetFormat();

    const auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        if (timerComponent->GetOnTimer()) {
            onTimer_ = *timerComponent->GetOnTimer();
        }
    }

    const auto& timerController = timerComponent->GetTextTimerController();
    if (timerController) {
        auto weak = AceType::WeakClaim(this);
        timerController->OnStart([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandleStart();
            }
        });
        timerController->OnPause([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandlePause();
            }
        });
        timerController->OnReset([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandleReset();
            }
        });
    }

    auto weak = AceType::WeakClaim(this);
    if (!scheduler_) {
        auto&& callback = [weak](uint64_t duration) {
            auto timer = weak.Upgrade();
            if (timer) {
                timer->Tick(duration);
            } else {
                LOGW("empty timer, skip tick callback.");
            }
        };
        scheduler_ = SchedulerBuilder::Build(callback, context);
    }

    textTimerComponent_ = timerComponent;
    MarkNeedLayout();
}

void RenderTextTimer::PerformLayout()
{
    if (!renderText_) {
        LOGE("render text is null.");
        return;
    }

    renderText_->Layout(GetLayoutParam());
    Size textSize = renderText_->GetLayoutSize();
    realSize_ = renderText_->GetLayoutSize();
    realSize_.SetWidth(textSize.Width());
    realSize_.SetHeight(textSize.Height());
    double maxWidth = GetLayoutParam().GetMaxSize().Width();
    if (realSize_.Width() > maxWidth) {
        realSize_.SetWidth(maxWidth);
    }

    LayoutParam textLayout;
    textLayout.SetFixedSize(textSize);
    double textX = (realSize_.Width() - textSize.Width()) / 2.0; // place center

    double textY = (realSize_.Height() - textSize.Height()) / 2.0; // place center
    renderText_->SetPosition(Offset(textX, textY));
    renderText_->Layout(textLayout);

    SetLayoutSize(realSize_);
}

void RenderTextTimer::UpdateRenders()
{
    ClearRenders();
    GetRenders();
}

void RenderTextTimer::GetRenders(const RefPtr<RenderNode>& render)
{
    if (!render) {
        LOGE("render node is null.");
        return;
    }

    if (AceType::InstanceOf<RenderText>(render)) {
        renderText_ = AceType::DynamicCast<RenderText>(render);
        return;
    }

    for (const auto& child : render->GetChildren()) {
        GetRenders(child);
    }
}

void RenderTextTimer::GetRenders()
{
    GetRenders(AceType::Claim(this));
}

void RenderTextTimer::ClearRenders()
{
    renderText_ = nullptr;
}

void RenderTextTimer::UpdateValue(uint32_t elapsedTime)
{
    std::string timerText = Localization::GetInstance()->FormatDuration(elapsedTime, format_);

    if (!textComponent_) {
        LOGE("(RenderTextTimer::UpdateValue)texttimer component is null.");
        return;
    }

    if (textComponent_->GetData() == timerText) {
        return; // needless to update
    }

    textComponent_->SetData(timerText);
    if (!renderText_) {
        LOGE("(RenderTextTimer::UpdateValue)render texttimer is null.");
        return;
    }
    renderText_->Update(textComponent_);
}

void RenderTextTimer::Tick(uint64_t duration)
{
    elapsedTime_ += duration;

    if (onTimer_) {
        onTimer_(GetMilliseconds(), elapsedTime_);
    }

    double tmp_value = static_cast<double>(elapsedTime_);
    if (isCountDown_) {
        tmp_value = (inputCount_ >= elapsedTime_) ? (inputCount_ - elapsedTime_) : 0;
    }

    if (isCountDown_ && tmp_value <= 0) {
        UpdateValue(0);
        HandlePause();
        return;
    }

    UpdateValue(static_cast<uint32_t>(tmp_value));
}

void RenderTextTimer::HandleStart()
{
    if (scheduler_ && !scheduler_->IsActive()) {
        scheduler_->Start();
    }
}

void RenderTextTimer::HandlePause()
{
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
}

void RenderTextTimer::HandleReset()
{
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
    elapsedTime_ = 0;
    UpdateValue(isCountDown_ ? inputCount_ : 0);
}
} // namespace OHOS::Ace