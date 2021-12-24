/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
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

#include "core/components/text_clock/render_text_clock.h"

#include <chrono>
#include <sys/time.h>

#include "base/utils/string_utils.h"
#include "core/components/image/image_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace{
constexpr int32_t BASE_YEAR = 1900;
}

RenderTextClock::RenderTextClock()
{
    timeTextComponent_ = AceType::MakeRefPtr<TextComponent>(std::string(""));
    renderTimeText_ = AceType::DynamicCast<RenderText>(RenderText::Create());
    AddChild(renderTimeText_);
}

void RenderTextClock::Update(const RefPtr<Component>& component)
{
    textClockComponent_ = AceType::DynamicCast<TextClockComponent>(component);
    if (textClockComponent_ == nullptr) {
        LOGE("textClockComponent is null!");
        return;
    }
    format_ = textClockComponent_->GetFormat();
    textStyle_ = textClockComponent_->GetTextStyle();
    hoursWest_ = textClockComponent_->GetHoursWest();
    isStart_ = textClockComponent_->GetStatus();
    if (textClockComponent_->GetOnDateChange()) {
        onDateChange = *textClockComponent_->GetOnDateChange();
    }
    UpdateTimeText();

    timeCallback_ = ([wp = WeakClaim(this)]() {
        auto renderTextClock = wp.Upgrade();
        if (renderTextClock) {
            renderTextClock->UpdateTimeText();
        } else {
            LOGE("renderTextClock is empty");
        }
    });
}

void RenderTextClock::UpdateTimeText()
{
    currentTimeText_ = GetFormatDateTime(format_);
    timeTextComponent_->SetData(currentTimeText_);
    timeTextComponent_->SetTextStyle(textStyle_);
    renderTimeText_->Attach(GetContext());
    renderTimeText_->Update(timeTextComponent_);
}

void RenderTextClock::UpdateTimeTextCallBack()
{
    if (timeCallback_) {
        timeCallback_();
    }
    if (!onDateChange) {
        LOGE("func is Null");
        return;
    } else {
        currentMillisecond_ = GetMilliseconds();
        onDateChange(currentMillisecond_);
    }
}

void RenderTextClock::PerformLayout()
{
    if (GetChildren().size() != 1) {
        return;
    }
    const auto& timeTextChild = GetChildren().front();
    LayoutParam layoutParam = GetLayoutParam();
    if (!timeTextChild) {
        return;
    }
    timeTextChild->Layout(layoutParam);
    SetLayoutSize(GetLayoutParam().Constrain(timeTextChild->GetLayoutSize()));
}

DateTime RenderTextClock::GetDateTime() const
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    if (local == nullptr) {
        LOGE("Get localtime failed.");
        return DateTime();
    }
    // This is for i18n date time
    DateTime dateTime;
    dateTime.year = local->tm_year + BASE_YEAR;
    dateTime.month = local->tm_mon;
    dateTime.day = local->tm_mday;
    TimeOfNow timeOfNow = GetTimeOfNow(hoursWest_);
    dateTime.hour = timeOfNow.hour24_;
    dateTime.minute = timeOfNow.minute_;
    dateTime.second = timeOfNow.second_;
    return dateTime;
}

std::string RenderTextClock::GetFormatDateTime(const std::string& format) const
{
    DateTime dateTime = GetDateTime();
    std::string time = Localization::GetInstance()->FormatDateTime(dateTime, format);
    return time;
}
} // namespace OHOS::Ace