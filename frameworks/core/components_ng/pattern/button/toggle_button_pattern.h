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
#include "core/components/toggle/toggle_theme.h"

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

    void SetIsFocus(bool focus)
    {
        isFocus_ = focus;
    }
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void OnClick();
    void OnColorConfigurationUpdate() override;
    void MarkIsSelected(bool isSelected);
    void SetButtonPress(bool value);
    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;
    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

private:
    void OnAttachToFrameNode() override;
    void InitParameters();
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void InitClickEvent();
    void InitButtonAndText();
    void InitOnKeyEvent();
    void HandleBlurEvent();
    void HandleFocusEvent();
    bool OnKeyEvent(const KeyEvent& event);
    void SetAccessibilityAction();
    void UpdateSelectStatus(bool isSelected);
    void InitTouchEvent();
    void OnTouchDown();
    void OnTouchUp();
    void FireBuilder();
    void HandleOnOffStyle(bool isOnToOff, bool isFocus);
    void HandleOverlayStyle();
    void HandleBorderAndShadow();
    void HandleFocusStyle();
    void UpdateButtonStyle();
    void SetBlurButtonStyle(RefPtr<FrameNode>& textNode, RefPtr<TextLayoutProperty>& textLayoutProperty,
        bool isOnValueFalse, RefPtr<RenderContext>& renderContext);
    void SetFocusButtonStyle(RefPtr<FrameNode>& textNode, RefPtr<TextLayoutProperty>& textLayoutProperty,
        bool isOnValueFalse, RefPtr<RenderContext>& renderContext);
    void HandleFocusShadowStyle(bool isOffState, RefPtr<RenderContext>& renderContext,
        Shadow shadowValue, bool isbgColorFocus);
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void GetIsTextFade();
    void UpdateTexOverflow(bool isMarqueeStart, RefPtr<TextLayoutProperty>& textLayoutProperty);
    void InitHoverEvent();
    void HandleHoverEvent(bool isHover);
    void InitEvent();

    RefPtr<FrameNode> BuildContentModifierNode();
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    std::optional<SwitchMakeCallback> toggleMakeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> hoverListener_;
    int32_t nodeId_ = -1;

    RefPtr<ClickEvent> clickListener_;
    RefPtr<ToggleTheme> toggleTheme_;
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
    bool isShadow_ = false;
    bool isScale_ = false;
    bool isTextColor_ = false;
    bool isCheckedShadow_ = false;
    bool isbgColorFocus_ = false;
    bool isFocus_ = false;
    bool isPress_ = false;
    bool isSetClickedColor_ = false;
    bool IsNeedToHandleHoverOpacity();
    bool isTextFadeOut_ = false;
    bool isHover_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(ToggleButtonPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_PATTERN_H
