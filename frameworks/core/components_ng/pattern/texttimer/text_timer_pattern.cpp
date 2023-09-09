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
#include <string>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
constexpr int32_t TOTAL_SECONDS_OF_HOUR = 60 * 60;
constexpr int32_t SECONDS_OF_MILLISECOND = 1000;
constexpr double DEFAULT_COUNT = 60000.0;
const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
} // namespace

TextTimerPattern::TextTimerPattern()
{
    textTimerController_ = MakeRefPtr<TextTimerController>();
}

void TextTimerPattern::FireChangeEvent()
{
    auto textTimerEventHub = GetEventHub<TextTimerEventHub>();
    CHECK_NULL_VOID(textTimerEventHub);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto format = layoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
    char lastWord = format.back();
    auto millSeconds = GetMilliseconds();
    auto utcTime = millSeconds;
    auto elapsedTime = elapsedTime_;
    switch (lastWord) {
        case 's':
            utcTime = millSeconds / SECONDS_OF_MILLISECOND;
            elapsedTime = elapsedTime_ / SECONDS_OF_MILLISECOND;
            break;
        case 'm':
            utcTime = millSeconds / (SECONDS_OF_MILLISECOND * TOTAL_MINUTE_OF_HOUR);
            elapsedTime = elapsedTime_ / (SECONDS_OF_MILLISECOND * TOTAL_MINUTE_OF_HOUR);
            break;
        case 'h':
            utcTime = millSeconds / (SECONDS_OF_MILLISECOND * TOTAL_SECONDS_OF_HOUR);
            elapsedTime = elapsedTime_ / (SECONDS_OF_MILLISECOND * TOTAL_SECONDS_OF_HOUR);
            break;
        default:
            break;
    }
    if (utcTime - lastReportingTime_ >= 1) {
        textTimerEventHub->FireChangeEvent(std::to_string(utcTime), std::to_string(elapsedTime));
    }
    lastReportingTime_ = utcTime;
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
            } else {
                LOGW("empty timer, skip tick callback.");
            }
        };
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        scheduler_ = SchedulerBuilder::Build(callback, context);
        auto count = isCountDown_ ? inputCount_ : 0;
        UpdateTextTimer(static_cast<uint32_t>(count));
    } else {
        HandleReset();
    }
}

void TextTimerPattern::Tick(uint64_t duration)
{
    elapsedTime_ += duration;
    FireChangeEvent();

    auto tmpValue = static_cast<double>(elapsedTime_);
    if (isCountDown_) {
        tmpValue =
            (inputCount_ >= static_cast<double>(elapsedTime_)) ? (inputCount_ - static_cast<double>(elapsedTime_)) : 0;
    }
    if (isCountDown_ && tmpValue <= 0) {
        UpdateTextTimer(0);
        HandlePause();
        return;
    }

    UpdateTextTimer(static_cast<uint32_t>(tmpValue));
}

void TextTimerPattern::UpdateTextLayoutProperty(
    RefPtr<TextTimerLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty)
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

void TextTimerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textTimerProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(textTimerProperty);
    textTimerProperty->UpdateAlignment(Alignment::CENTER_LEFT);
}

void TextTimerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    if (textLayoutProperty->GetPositionProperty()) {
        textLayoutProperty->UpdateAlignment(
            textLayoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    }
    auto textTimerProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(textTimerProperty);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    UpdateTextLayoutProperty(textTimerProperty, textLayoutProperty);
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->SetClipToFrame(false);
    textContext->UpdateClipEdge(false);
    isCountDown_ = GetIsCountDown();
    inputCount_ = GetInputCount();

    InitTextTimerController();
    InitTimerDisplay();
    textNode->MarkModifyDone();
    RegisterVisibleAreaChangeCallback();
}

void TextTimerPattern::RegisterVisibleAreaChangeCallback()
{
    if (isRegisteredAreaCallback_) {
        return;
    }
    isRegisteredAreaCallback_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnVisibleAreaChange(visible);
    };
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback, false);
}

void TextTimerPattern::OnVisibleAreaChange(bool visible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (visible) {
        CHECK_NULL_VOID(textNode_);
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        if (!childNode) {
            host->AddChild(textNode_);
            host->RebuildRenderContextTree();
        }
    } else {
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        CHECK_NULL_VOID(childNode);
        bool isTextNode = AceType::InstanceOf<TextPattern>(childNode->GetPattern());
        if (!isTextNode) {
            return;
        }
        textNode_ = childNode;
        host->RemoveChild(childNode);
        host->RebuildRenderContextTree();
    }
}

void TextTimerPattern::UpdateTextTimer(uint32_t elapsedTime)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    // format time text.
    std::string timerText = Localization::GetInstance()->FormatDuration(elapsedTime, GetFormat());
    if (timerText.empty()) {
        timerText = Localization::GetInstance()->FormatDuration(elapsedTime, DEFAULT_FORMAT);
    }
    if (textLayoutProperty->GetContent() == timerText) {
        return; // needless to update
    }

    textLayoutProperty->UpdateContent(timerText); // Update time text.
    textNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

std::string TextTimerPattern::GetFormat() const
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(textTimerLayoutProperty, DEFAULT_FORMAT);
    return textTimerLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
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
    CHECK_NULL_RETURN(textTimerLayoutProperty, DEFAULT_COUNT);
    return textTimerLayoutProperty->GetInputCount().value_or(DEFAULT_COUNT);
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
    UpdateTextTimer(static_cast<uint32_t>(count));
}

RefPtr<FrameNode> TextTimerPattern::GetTextNode()
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
