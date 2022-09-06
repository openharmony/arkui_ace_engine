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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/texttimer/texttimer_controller.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_event_hub.h"
#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class TextTimerPattern : public Pattern {
    DECLARE_ACE_TYPE(TextTimerPattern, Pattern);

public:
    TextTimerPattern();
    ~TextTimerPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextTimerLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextTimerEventHub>();
    }

    RefPtr<TextTimerController> GetTextTimerController() const
    {
        return textTimerController_;
    }

private:
    void OnModifyDone() override;

    void InitTextTimerController();
    void InitTimerDisplay();
    void updateTextTimer(uint32_t elapsedTime);
    void Tick(uint64_t duration);
    void FireChangeEvent() const;

    void HandleStart();
    void HandlePause();
    void HandleReset();

    std::string GetFormat() const;
    bool GetIsCountDown() const;
    double GetInputCount() const;

    RefPtr<TextTimerController> textTimerController_;
    RefPtr<TextLayoutProperty> textLayoutProperty_;
    RefPtr<Scheduler> scheduler_;
    uint64_t elapsedTime_ = 0; // millisecond.
    bool isCountDown_ = false;
    double inputCount_ = 0.0;

    ACE_DISALLOW_COPY_AND_MOVE(TextTimerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_PATTERN_H
