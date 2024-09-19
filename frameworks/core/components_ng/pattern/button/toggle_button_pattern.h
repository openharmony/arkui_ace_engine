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
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

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

    bool UseContentModifier() const override
    {
        return contentModifierNode_ != nullptr;
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

    RefPtr<TouchEventImpl>& GetTouchListener()
    {
        return touchListener_;
    }

    void SetToggleBuilderFunc(SwitchMakeCallback&& toggleMakeFunc);

    int32_t GetBuilderId() const override
    {
        return nodeId_;
    }
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void OnClick();
    void OnColorConfigurationUpdate() override;
    void MarkIsSelected(bool isSelected);
    void SetButtonPress(bool value);

private:
    void OnAttachToFrameNode() override;
    void InitParameters();
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void InitClickEvent();
    void InitButtonAndText();
    void InitOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);
    void SetAccessibilityAction();
    void UpdateSelectStatus(bool isSelected);
    void InitTouchEvent();
    void OnTouchDown();
    void OnTouchUp();
    void FireBuilder();

    RefPtr<FrameNode> BuildContentModifierNode();
    std::optional<SwitchMakeCallback> toggleMakeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    RefPtr<TouchEventImpl> touchListener_;
    int32_t nodeId_ = -1;

    RefPtr<ClickEvent> clickListener_;
    std::optional<bool> isOn_;
    Color checkedColor_;
    Color unCheckedColor_;
    Color backgroundColor_;
    float disabledAlpha_ { 1.0f };
    Dimension textMargin_;
    Dimension buttonMargin_;
    Dimension buttonHeight_;
    Dimension buttonRadius_;
    Dimension textFontSize_;
    Color textColor_;
    bool isPress_ = false;
    bool isSetClickedColor_ = false;
    bool IsNeedToHandleHoverOpacity();
    bool isTouchPreventDefault_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(ToggleButtonPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_PATTERN_H
