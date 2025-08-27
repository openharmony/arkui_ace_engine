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

#include <string>

#include "base/log/dump_log.h"
#include "base/i18n/localization.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
constexpr int32_t TOTAL_SECONDS_OF_HOUR = 60 * 60;
constexpr int32_t SECONDS_OF_MILLISECOND = 1000;
constexpr int32_t SECONDS_OF_HUNDRED = 100;
constexpr int32_t SECONDS_OF_TEN = 10;
constexpr int32_t DEFAULT_SCALE = 1;
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
    auto utcTime = GetFormatDuration(GetMilliseconds());
    auto elapsedTime = GetFormatDuration(elapsedTime_);
    if (elapsedTime - lastElapsedTime_ >= 1) {
        textTimerEventHub->FireChangeEvent(utcTime, elapsedTime);
        lastElapsedTime_ = elapsedTime;
    }
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
    if (!scheduler_) {
        resetCount_ = false;
        auto weak = AceType::WeakClaim(this);
        auto&& callback = [weak](uint64_t duration) {
            auto timer = weak.Upgrade();
            if (timer) {
                timer->Tick(duration);
            }
        };
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        scheduler_ = SchedulerBuilder::Build(callback, context);
        auto count = isCountDown_ ? inputCount_ : 0;
        UpdateTextTimer(static_cast<uint32_t>(count));
        return;
    }
    if (resetCount_) {
        resetCount_ = false;
        HandleReset();
    }
}

void TextTimerPattern::Tick(uint64_t duration)
{
    elapsedTime_ += duration;
    FireChangeEvent();

    auto tmpValue = static_cast<double>(elapsedTime_);
    if (isCountDown_) {
        auto elapsedTime = GetMillisecondsDuration(GetFormatDuration(elapsedTime_));
        tmpValue =
            (inputCount_ >= static_cast<double>(elapsedTime_)) ? (inputCount_ - static_cast<double>(elapsedTime)) : 0;
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
    if (layoutProperty->GetTextShadow().has_value()) {
        textLayoutProperty->UpdateTextShadow(layoutProperty->GetTextShadow().value());
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

    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        Pattern::OnModifyDone();
    }

    if (!textNode_) {
        textNode_ = GetTextNode();
    }
    CHECK_NULL_VOID(textNode_);
    auto textLayoutProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();
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
    auto textContext = textNode_->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->SetClipToFrame(false);
    textContext->UpdateClipEdge(false);
    isCountDown_ = GetIsCountDown();
    inputCount_ = GetInputCount();

    InitTextTimerController();
    InitTimerDisplay();
    textNode_->MarkModifyDone();
    RegisterVisibleAreaChangeCallback();
    FireBuilder();
}

void TextTimerPattern::RegisterVisibleAreaChangeCallback()
{
    if (isRegisteredAreaCallback_) {
        return;
    }
    isRegisteredAreaCallback_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnVisibleAreaChange(visible);
    };
    std::vector<double> ratioList = {0.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, true);
}

void TextTimerPattern::OnVisibleAreaChange(bool visible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(textNode_);
    if (visible) {
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        if (!childNode) {
            host->AddChild(textNode_);
            host->RebuildRenderContextTree();
            if (SystemProperties::ConfigChangePerform()) {
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        }
    } else {
        host->RemoveChild(textNode_);
        host->RebuildRenderContextTree();
    }
}

void TextTimerPattern::UpdateTextTimer(uint32_t elapsedTime)
{
    if (UseContentModifier()) {
        FireBuilder();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(textNode_);
    auto textLayoutProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    // format time text.
    std::string timerText = Localization::GetInstance()->FormatDuration(elapsedTime, GetFormat());
    if (timerText.empty()) {
        timerText = Localization::GetInstance()->FormatDuration(elapsedTime, DEFAULT_FORMAT);
    }
    textLayoutProperty->UpdateContent(timerText); // Update time text.
    if (CheckMeasureFlag(textLayoutProperty->GetPropertyChangeFlag()) ||
        CheckLayoutFlag(textLayoutProperty->GetPropertyChangeFlag())) {
        textNode_->MarkModifyDone();
        textNode_->MarkDirtyNode();
    }
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
    lastElapsedTime_ = 0;
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

uint64_t TextTimerPattern::GetFormatDuration(uint64_t duration) const
{
    return duration / GetMillisecondsDuration(DEFAULT_SCALE);
}

uint64_t TextTimerPattern::GetMillisecondsDuration(uint64_t duration) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, duration);
    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, duration);
    auto format = layoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
    if (format.find("SSS") != std::string::npos) {
        return duration;
    } else if (format.find("SS") != std::string::npos) {
        return duration * SECONDS_OF_TEN;
    } else if (format.find('S') != std::string::npos) {
        return duration * SECONDS_OF_HUNDRED;
    } else if (format.find('s') != std::string::npos) {
        duration = duration * SECONDS_OF_MILLISECOND;
    } else if (format.find('m') != std::string::npos) {
        duration = duration * (SECONDS_OF_MILLISECOND * TOTAL_MINUTE_OF_HOUR);
    } else if (format.find('H') != std::string::npos) {
        duration = duration * (SECONDS_OF_MILLISECOND * TOTAL_SECONDS_OF_HOUR);
    }
    return duration;
}

void TextTimerPattern::ResetCount()
{
    resetCount_ = true;
}

void TextTimerPattern::FireBuilder()
{
    if (!makeFunc_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChildAtIndex(0);
    contentModifierNode_ = BuildContentModifierNode();
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> TextTimerPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetEventHub<TextTimerEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_RETURN(textTimerLayoutProperty, nullptr);
    auto count = textTimerLayoutProperty->GetInputCount().value_or(DEFAULT_COUNT);
    auto isCountDown = textTimerLayoutProperty->GetIsCountDown().value_or(false);
    auto started = scheduler_ && scheduler_->IsActive();
    auto elapsedTime = GetFormatDuration(elapsedTime_);
    TextTimerConfiguration textTimerConfiguration(count, isCountDown, started, elapsedTime, enabled);
    return (makeFunc_.value())(textTimerConfiguration);
}

void TextTimerPattern::DumpInfo()
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(textTimerLayoutProperty);
    auto isCountDown = textTimerLayoutProperty->GetIsCountDown().value_or(false);
    isCountDown ? DumpLog::GetInstance().AddDesc("isCountDown: true") :
        DumpLog::GetInstance().AddDesc("isCountDown: false");
    auto format = textTimerLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
    DumpLog::GetInstance().AddDesc("format: ", format);
    auto elapsedTime = GetFormatDuration(elapsedTime_);
    DumpLog::GetInstance().AddDesc("elapsedTime: ", elapsedTime);
}

void TextTimerPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto textTimerLayoutProperty = GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(textTimerLayoutProperty);
    json->Put("isCountDown", textTimerLayoutProperty->GetIsCountDown().value_or(false));
    json->Put("format", textTimerLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT).c_str());
    json->Put("elapsedTime", std::to_string(GetFormatDuration(elapsedTime_)).c_str());
}

void TextTimerPattern::UpdateTextColor(const Color& color, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (isFirstLoad || pipelineContext->IsSystmColorChange()) {
        layoutProperty->UpdateTextColor(color);
        renderContext->UpdateForegroundColor(color);
        renderContext->ResetForegroundColorStrategy();
        renderContext->UpdateForegroundColorFlag(true);
    }
}

void TextTimerPattern::UpdateFontWeight(const FontWeight& value, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (isFirstLoad || pipelineContext->IsSystmColorChange()) {
        layoutProperty->UpdateFontWeight(value);
    }
}

void TextTimerPattern::UpdateFontSize(const Dimension& value, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (isFirstLoad || pipelineContext->IsSystmColorChange()) {
        layoutProperty->UpdateFontSize(value);
    }
}

void TextTimerPattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (host->GetRerenderable()) {
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TextTimerPattern::UpdateFontFamily(const std::vector<std::string>& fontFamilies, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (isFirstLoad || pipelineContext->IsSystmColorChange()) {
        layoutProperty->UpdateFontFamily(fontFamilies);
    }
}

void TextTimerPattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);

    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    auto pops = host->GetLayoutProperty<TextTimerLayoutProperty>();
    CHECK_NULL_VOID(pops);

    if (!pops->HasTextColorSetByUser() || (pops->HasTextColorSetByUser() && !pops->GetTextColorSetByUserValue())) {
        UpdateTextColor(theme->GetTextStyle().GetTextColor(), false);
    }
    if (!pops->GetTextFontSizeSetByUserValue(false)) {
        UpdateFontSize(theme->GetTextStyle().GetFontSize(), false);
    }
    if (!pops->GetTextFontWeightSetByUserValue(false)) {
        UpdateFontWeight(theme->GetTextStyle().GetFontWeight(), false);
    }
    if (!pops->GetTextFontFamilySetByUserValue(false)) {
        UpdateFontFamily(theme->GetTextStyle().GetFontFamilies(), false);
    }
}
} // namespace OHOS::Ace::NG
