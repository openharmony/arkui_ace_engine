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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_PATTERN_H

#include <functional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/text_clock/text_clock_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_clock/text_clock_accessibility_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_event_hub.h"
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
using TimeCallback = std::function<void()>;
class TextClockPattern : public Pattern {
    DECLARE_ACE_TYPE(TextClockPattern, Pattern);

public:
    TextClockPattern();
    ~TextClockPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextClockLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextClockAccessibilityProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextClockEventHub>();
    }

    RefPtr<TextClockController> GetTextClockController() const
    {
        return textClockController_;
    }

    int32_t GetTextId()
    {
        if (!textId_.has_value()) {
            textId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return textId_.value();
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void InitTextClockController();
    void UpdateTimeTextCallBack();

    void InitUpdateTimeTextCallBack();
    void UpdateTimeText();
    void RequestUpdateForNextSecond();
    void FireChangeEvent() const;
    std::string GetCurrentFormatDateTime();
    static void UpdateTextLayoutProperty(
        RefPtr<TextClockLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty);
    std::vector<std::string> ParseInputFormat(
        bool& is24H, int32_t& weekType, int32_t& month, int32_t& day, bool& isMilliSecond);
    static std::vector<std::string> ParseDateTimeValue(const std::string& strDateTimeValue);
    static std::string GetAmPm(const std::string& dateTimeValue);
    static std::string Abstract(const std::string& strSource, const bool& abstractItem);
    static int32_t GetDigitNumber(const std::string& strSource);
    static std::string GetWeek(const bool& isShortType, const int32_t& week);
    static std::string SpliceDateTime(
        const std::vector<std::string>& curDateTime, const std::vector<std::string>& inputFormatSplitter);
    static std::string CheckDateTimeElement(const std::vector<std::string>& curDateTime, const std::string& str,
        const char& element, const int32_t& elementIndex);

    std::string GetFormat() const;
    int32_t GetHoursWest() const;
    RefPtr<FrameNode> GetTextNode();

    RefPtr<TextClockController> textClockController_;
    TimeCallback timeCallback_;
    bool isStart_ = true;
    int32_t hourWest_ = 0;
    std::optional<int32_t> textId_;

    ACE_DISALLOW_COPY_AND_MOVE(TextClockPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_PATTERN_H
