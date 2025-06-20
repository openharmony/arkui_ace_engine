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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/texttimer/texttimer_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_accessibility_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_event_hub.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_algorithm.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
using TextTimerMakeCallback =
    std::function<RefPtr<FrameNode>(const TextTimerConfiguration& textTimerConfiguration)>;
class TextTimerPattern : public Pattern {
    DECLARE_ACE_TYPE(TextTimerPattern, Pattern);

public:
    TextTimerPattern();
    ~TextTimerPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextTimerLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TextTimerLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextTimerAccessibilityProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextTimerEventHub>();
    }

    RefPtr<TextTimerController> GetTextTimerController() const
    {
        return textTimerController_;
    }

    void SetJSTextTimerController(const RefPtr<Referenced>& jsController)
    {
        jsTextTimerController_ = jsController;
    }

    RefPtr<Referenced> GetJSTextTimerController()
    {
        return jsTextTimerController_.Upgrade();
    }

    int32_t GetTextId()
    {
        if (!textId_.has_value()) {
            textId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return textId_.value();
    }
    void ResetCount();

    void SetBuilderFunc(TextTimerMakeCallback&& makeFunc)
    {
        if (makeFunc == nullptr) {
            makeFunc_ = std::nullopt;
            contentModifierNode_ = nullptr;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
    }

    bool UseContentModifier() const
    {
        return contentModifierNode_ != nullptr;
    }

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void OnColorConfigurationUpdate() override;

    void UpdateTextColor(const Color& color, bool isFirstLoad = false);
    void UpdateFontWeight(const FontWeight& value, bool isFirstLoad = false);
    void OnColorModeChange(uint32_t colorMode) override;
    void UpdateFontSize(const Dimension& value, bool isFirstLoad = false);
    void UpdateFontFamily(const std::vector<std::string>& fontFamilies, bool isFirstLoad);

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void Tick(uint64_t duration);
    void InitTextTimerController();

    void InitTimerDisplay();
    void UpdateTextTimer(uint32_t elapsedTime);
    void FireChangeEvent();

    void HandleStart();
    void HandlePause();
    void HandleReset();
    uint64_t GetFormatDuration(uint64_t duration) const;
    uint64_t GetMillisecondsDuration(uint64_t duration) const;

    static void UpdateTextLayoutProperty(
        RefPtr<TextTimerLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty);
    std::string GetFormat() const;
    bool GetIsCountDown() const;
    double GetInputCount() const;
    RefPtr<FrameNode> GetTextNode();
    void RegisterVisibleAreaChangeCallback();
    void OnVisibleAreaChange(bool visible);
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();

    std::optional<TextTimerMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    RefPtr<TextTimerController> textTimerController_;
    WeakPtr<Referenced> jsTextTimerController_;
    RefPtr<Scheduler> scheduler_;
    RefPtr<FrameNode> textNode_;
    uint64_t elapsedTime_ = 0; // millisecond.
    uint64_t lastElapsedTime_ = 0;
    bool isCountDown_ = false;
    double inputCount_ = 0.0;
    std::optional<int32_t> textId_;
    bool isRegisteredAreaCallback_ = false;
    bool resetCount_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TextTimerPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H
