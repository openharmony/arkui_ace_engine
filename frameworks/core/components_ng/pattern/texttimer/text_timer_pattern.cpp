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

#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"

#include <stack>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
TextTimerPattern::TextTimerPattern()
{
    textTimerController_ = MakeRefPtr<TextTimerController>();
}

void TextTimerPattern::FireChangeEvent() const
{
    auto textTimerEventHub = GetEventHub<TextTimerEventHub>();
    CHECK_NULL_VOID(textTimerEventHub);
    textTimerEventHub->FireChangeEvent(GetMilliseconds(), elapsedTime_);
}

void TextTimerPattern::InitTextTimerController()
{
    if (textTimerController_) {
        if (textTimerController_->HasInitialized()) {
            return;
        }
        auto weak = AceType::WeakClaim(this);
        textTimerController_->OnStart([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandleStart();
            }
        });
        textTimerController_->OnPause([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandlePause();
            }
        });
        textTimerController_->OnReset([weak]() {
            auto timerRender = weak.Upgrade();
            if (timerRender) {
                timerRender->HandleReset();
            }
        });
    }
}

void TextTimerPattern::InitTimerDisplay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto weak = AceType::WeakClaim(this);
    if (!scheduler_) {
        auto&& callback = [weak](uint64_t duration) {
            auto timer = weak.Upgrade();
            if (timer) {
                timer->Tick(duration);
            }
        };
        scheduler_ = SchedulerBuilder::Build(callback, host->GetContext());
        auto count = isCountDown_ ? inputCount_ : 0;
        updateTextTimer(static_cast<uint32_t>(count));
    } else {
        HandleReset();
    }
}

void TextTimerPattern::Tick(uint64_t duration)
{
    elapsedTime_ += duration;
    FireChangeEvent();

    auto tmp_value = static_cast<double>(elapsedTime_);
    if (isCountDown_) {
        tmp_value =
            (inputCount_ >= static_cast<double>(elapsedTime_)) ? (inputCount_ - static_cast<double>(elapsedTime_)) : 0;
    }
    if (isCountDown_ && tmp_value <= 0) {
        updateTextTimer(0);
        HandlePause();
        return;
    }

    updateTextTimer(static_cast<uint32_t>(tmp_value));
}

void TextTimerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    ACE_DCHECK(textChild);
    textLayoutProperty_ = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty_);

    isCountDown_ = GetIsCountDown();
    inputCount_ = GetInputCount();

    InitTextTimerController();
    InitTimerDisplay();
}

void TextTimerPattern::updateTextTimer(uint32_t elapsedTime)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // format time text.
    std::string timerText = Localization::GetInstance()->FormatDuration(elapsedTime, GetFormat());
    if (textLayoutProperty_->GetContent() == timerText) {
        return; // needless to update
    }
    textLayoutProperty_->UpdateContent(timerText); // Update child node time text.
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

std::string TextTimerPattern::GetFormat() const
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(textTimerLayoutProperty, "hh:mm:ss.ms");
    return textTimerLayoutProperty->GetFormat().value_or("hh:mm:ss.ms");
}

bool TextTimerPattern::GetIsCountDown() const
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(textTimerLayoutProperty, false);
    return textTimerLayoutProperty->GetIsCountDown().value_or(false);
}

double TextTimerPattern::GetInputCount() const
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(textTimerLayoutProperty, 0.0);
    return textTimerLayoutProperty->GetInputCount().value_or(0.0);
}

void TextTimerPattern::HandleStart()
{
    if (scheduler_ && !scheduler_->IsActive()) {
        scheduler_->Start();
    }
}

void TextTimerPattern::HandlePause()
{
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
}

void TextTimerPattern::HandleReset()
{
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
    elapsedTime_ = 0;
    auto count = isCountDown_ ? inputCount_ : 0;
    updateTextTimer(static_cast<uint32_t>(count));
}
} // namespace OHOS::Ace::NG
