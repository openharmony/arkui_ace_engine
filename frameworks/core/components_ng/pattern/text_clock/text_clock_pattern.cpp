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

#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

#include <ctime>
#include <string>
#include <sys/time.h>

#include "base/i18n/localization.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
constexpr int32_t TOTAL_SECONDS_OF_HOUR = 60 * 60;
constexpr int32_t BASE_YEAR = 1900;
constexpr int32_t INTERVAL_OF_U_SECOND = 1000000;
constexpr int32_t MICROSECONDS_OF_MILLISECOND = 1000;
const std::string DEFAULT_FORMAT = "hms";

int32_t GetSystemTimeZone()
{
    struct timeval currentTime {};
    struct timezone timeZone {};
    gettimeofday(&currentTime, &timeZone);
    int32_t hoursWest = timeZone.tz_minuteswest / TOTAL_MINUTE_OF_HOUR;
    return hoursWest;
}
} // namespace

TextClockPattern::TextClockPattern()
{
    textClockController_ = MakeRefPtr<TextClockController>();
}

void TextClockPattern::OnAttachToFrameNode()
{
    InitTextClockController();
    InitUpdateTimeTextCallBack();
}

void TextClockPattern::UpdateTextLayoutProperty(
    RefPtr<TextClockLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (layoutProperty->GetFontSize().has_value()) {
        textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
    }
    if (layoutProperty->GetFontWeight().has_value()) {
        textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value());
    }
    if (layoutProperty->GetTextColor().has_value()) {
        textLayoutProperty->UpdateTextColor(layoutProperty->GetTextColor().value());
    }
    if (layoutProperty->GetFontFamily().has_value()) {
        textLayoutProperty->UpdateFontFamily(layoutProperty->GetFontFamily().value());
    }
    if (layoutProperty->GetItalicFontStyle().has_value()) {
        textLayoutProperty->UpdateItalicFontStyle(layoutProperty->GetItalicFontStyle().value());
    }
}

void TextClockPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textClockProperty = host->GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_VOID(textClockProperty);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    UpdateTextLayoutProperty(textClockProperty, textLayoutProperty);
    hourWest_ = GetHoursWest();
    UpdateTimeText();
}

void TextClockPattern::InitTextClockController()
{
    CHECK_NULL_VOID_NOLOG(textClockController_);
    if (textClockController_->HasInitialized()) {
        return;
    }
    textClockController_->OnStart([wp = WeakClaim(this)]() {
        auto textClock = wp.Upgrade();
        if (textClock) {
            textClock->isStart_ = true;
            textClock->UpdateTimeText();
        }
    });
    textClockController_->OnStop([wp = WeakClaim(this)]() {
        auto textClock = wp.Upgrade();
        if (textClock) {
            textClock->isStart_ = false;
        }
    });
}

void TextClockPattern::InitUpdateTimeTextCallBack()
{
    if (!timeCallback_) {
        timeCallback_ = ([wp = WeakClaim(this)]() {
            auto textClock = wp.Upgrade();
            if (textClock) {
                textClock->UpdateTimeText();
            } else {
                LOGE("textClock is empty.");
            }
        });
    }
}

void TextClockPattern::UpdateTimeText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    std::string currentTime = GetCurrentFormatDateTime();
    if (currentTime.empty()) {
        LOGE("Get current format date time failed.");
        return;
    }
    textLayoutProperty->UpdateContent(currentTime); // update time text.
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->SetClipToFrame(false);
    textContext->UpdateClipEdge(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    textNode->MarkModifyDone();
    if (isStart_) {
        RequestUpdateForNextSecond();
    }
}

void TextClockPattern::RequestUpdateForNextSecond()
{
    struct timeval currentTime {};
    gettimeofday(&currentTime, nullptr);
    /**
     * 1 second = 1000 millisecond = 1000000 microsecond.
     * Millisecond is abbreviated as msec. Microsecond is abbreviated as usec.
     * unit of [delayTime] is msec, unit of [tv_usec] is usec
     * when [tv_usec] is 000100, (INTERVAL_OF_U_SECOND - timeUsec) / MICROSECONDS_OF_MILLISECOND = 999 msec
     * which will cause the delay task still arriving in current second, because 999000 + 000100 = 999100 < 1 second
     * so add an additional millisecond to modify the loss of precision during division
     */
    int32_t delayTime =
        (INTERVAL_OF_U_SECOND - static_cast<int32_t>(currentTime.tv_usec)) / MICROSECONDS_OF_MILLISECOND +
        1; // millisecond

    auto context = UINode::GetContext();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostDelayedTask(
        [wp = WeakClaim(this)] {
            auto textClock = wp.Upgrade();
            CHECK_NULL_VOID_NOLOG(textClock);
            if (!textClock->isStart_) {
                return;
            }
            textClock->UpdateTimeTextCallBack();
        },
        TaskExecutor::TaskType::UI, delayTime);
}

void TextClockPattern::UpdateTimeTextCallBack()
{
    if (timeCallback_) {
        timeCallback_();
    }
    FireChangeEvent();
}

std::string TextClockPattern::GetCurrentFormatDateTime()
{
    time_t utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    time_t localTime = (hourWest_ == GetSystemTimeZone()) ? utc : utc - (hourWest_ * TOTAL_SECONDS_OF_HOUR);

    auto* timeZoneTime = std::localtime(&localTime);
    CHECK_NULL_RETURN(timeZoneTime, "");
    // This is for i18n date time.
    DateTime dateTime;
    dateTime.year = timeZoneTime->tm_year + BASE_YEAR;
    dateTime.month = timeZoneTime->tm_mon;
    dateTime.day = timeZoneTime->tm_mday;
    dateTime.hour = timeZoneTime->tm_hour;
    dateTime.minute = timeZoneTime->tm_min;
    dateTime.second = timeZoneTime->tm_sec;

    std::string time = Localization::GetInstance()->FormatDateTime(dateTime, GetFormat());
    return time;
}

void TextClockPattern::FireChangeEvent() const
{
    auto textClockEventHub = GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(textClockEventHub);
    textClockEventHub->FireChangeEvent(std::to_string(GetMilliseconds() / MICROSECONDS_OF_MILLISECOND));
}

std::string TextClockPattern::GetFormat() const
{
    auto textClockLayoutProperty = GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_RETURN(textClockLayoutProperty, DEFAULT_FORMAT);
    return textClockLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
}

int32_t TextClockPattern::GetHoursWest() const
{
    auto textClockLayoutProperty = GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_RETURN(textClockLayoutProperty, GetSystemTimeZone());
    if (textClockLayoutProperty->GetHoursWest().has_value()) {
        return NearEqual(textClockLayoutProperty->GetHoursWest().value(), INT_MAX)
                   ? GetSystemTimeZone()
                   : textClockLayoutProperty->GetHoursWest().value();
    }
    return GetSystemTimeZone();
}

RefPtr<FrameNode> TextClockPattern::GetTextNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_RETURN(textNode, nullptr);
    if (textNode->GetTag() != V2::TEXT_ETS_TAG) {
        return nullptr;
    }
    return textNode;
}
} // namespace OHOS::Ace::NG
