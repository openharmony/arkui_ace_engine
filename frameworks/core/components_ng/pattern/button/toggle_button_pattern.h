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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_PATTERN_H

#include <optional>

#include "core/components/common/properties/color.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_accessibility_property.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"

namespace OHOS::Ace::NG {
class ToggleButtonPattern : public ButtonPattern {
    DECLARE_ACE_TYPE(ToggleButtonPattern, ButtonPattern);

public:
    ToggleButtonPattern() = default;

    ~ToggleButtonPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ToggleButtonEventHub>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ToggleButtonPaintProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ToggleButtonAccessibilityProperty>();
    }
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void OnClick();

private:
    void OnAttachToFrameNode() override;
    void InitParameters();
    void OnModifyDone() override;
    void HandleEnabled();
    void InitClickEvent();
    void InitButtonAndText();
    void InitOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);

    RefPtr<ClickEvent> clickListener_;
    std::optional<bool> isOn_;
    Color checkedColor_;
    Color unCheckedColor_;
    float disabledAlpha_ { 1.0f };
    Dimension textMargin_;
    Dimension buttonMargin_;
    Dimension buttonHeight_;
    Dimension buttonRadius_;
    Dimension textFontSize_;
    Color textColor_;

    ACE_DISALLOW_COPY_AND_MOVE(ToggleButtonPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_PATTERN_H
