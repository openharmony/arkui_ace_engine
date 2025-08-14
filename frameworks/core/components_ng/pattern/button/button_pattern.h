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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H

#include <optional>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
namespace OHOS::Ace::NG {
struct InspectorConfig;
class InspectorFilter;
enum class ComponentButtonType { POPUP, BUTTON, STEPPER, NAVIGATION };
class ButtonPattern : public Pattern {
    DECLARE_ACE_TYPE(ButtonPattern, Pattern);

public:
    ButtonPattern() = default;

    ~ButtonPattern() override = default;

    void SetApplyShadow(bool shadow)
    {
        isApplyShadow_ = shadow;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ButtonEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ButtonLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ButtonLayoutProperty>();
    }

    void SetClickedColor(const Color& color)
    {
        clickedColor_ = color;
    }

    void SetBlendColor(const std::optional<Color>& blendClickColor, const std::optional<Color>& blendHoverColor)
    {
        blendClickColor_ = blendClickColor;
        blendHoverColor_ = blendHoverColor;
    }

    void SetFocusBorderColor(const Color& color)
    {
        focusBorderColor_ = color;
    }

    void SetFocusBorderWidth(const Dimension& width)
    {
        focusBorderWidth_ = width;
    }

    void setComponentButtonType(const ComponentButtonType& buttonType)
    {
        buttonType_ = buttonType;
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;

    void SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
    }

    const Offset& GetLocalLocation() const
    {
        return localLocation_;
    }

    void SetInHover(bool inHover)
    {
        isInHover_ = inHover;
    }

    bool GetIsInHover() const
    {
        return isInHover_;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    RefPtr<InputEvent>& GetHoverListener()
    {
        return hoverListener_;
    }

    std::function<void(UIState)>& GetTouchListener()
    {
        return touchListener_;
    }

    void SetBuilderFunc(ButtonMakeCallback&& makeFunc);

    virtual int32_t GetBuilderId() const
    {
        return nodeId_;
    }

    void SetButtonPress(double xPos, double yPos);

    virtual bool UseContentModifier() const
    {
        return contentModifierNode_ != nullptr;
    }

    void OnColorConfigurationUpdate() override;

    void SetSkipColorConfigurationUpdate()
    {
        isColorUpdateFlag_ = true;
    }

    void SetPreFrameSize(const SizeF& frameSize)
    {
        preFrameSize_.SetSizeT(frameSize);
    }

    const SizeF& GetPreFrameSize() const
    {
        return preFrameSize_;
    }

    void SetHasCustomPadding(bool hasCustomPadding)
    {
        hasCustomPadding_ = hasCustomPadding;
    }

    bool GetHasCustomPadding()
    {
        return hasCustomPadding_;
    }

    void SetIsFocus(bool isFocus)
    {
        isFocus_ = isFocus;
    }

    FocusPattern GetFocusPattern() const override;

    bool IsNeedAdjustByAspectRatio() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void ToJsonValueAttribute(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    static std::string ConvertButtonRoleToString(ButtonRole buttonRole);

    static std::string ConvertButtonTypeToString(ButtonType buttonType);

    static std::string ConvertButtonStyleToString(ButtonStyleMode buttonStyle);

    static std::string ConvertControlSizeToString(ControlSize controlSize);

    bool IsDynamicSwitchButtonStyle(const BorderColorProperty& color, RefPtr<ButtonTheme>& buttonTheme);

    bool IsDynamicSwitchButtonStyle(const BorderWidthProperty& width, RefPtr<ButtonTheme>& buttonTheme);

    void DumpInfo() override;

    void DumpSubInfo(RefPtr<ButtonLayoutProperty> layoutProperty);

    void HandleBackgroundColor();

    void UpdateComponentColor(const Color& color, const ButtonColorType buttonColorType);

    void UpdateComponentString(const std::string& value, const ButtonStringType buttonStringType);

    void UpdateComponentDimension(const CalcDimension value, const ButtonDimensionType buttonDimensionType);

    void UpdateComponentDouble(const double value, const ButtonDoubleType buttonDoubleType);

    void UpdateComponentFamilies(const std::vector<std::string>& value, const ButtonStringType buttonStringType);

    std::string VectorToString(const std::vector<std::string>& vec, const std::string& delimiter = " ");

    std::vector<std::string> StringToVector(const std::string& str, char delimiter = ' ');

protected:
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void InitTouchEvent();
    void InitHoverEvent();
    void HandlePressedStyle();
    void HandleNormalStyle();
    void HandleHoverEvent(bool isHover);
    void UpdateTexOverflow(bool isMarqueeStart);
    void HandleEnabled();
    void InitButtonLabel();
    void CheckLocalizedBorderRadiuses();
    Color GetColorFromType(const RefPtr<ButtonTheme>& theme, const int32_t& type);
    void AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, int32_t typeFrom, int32_t typeTo, int32_t duration,
        const RefPtr<Curve>& curve);
    std::optional<Color> clickedColor_ = std::nullopt;

private:
    static void UpdateTextLayoutProperty(
        RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty);
    static void UpdateTextStyle(
        RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty);
    static bool NeedAgingUpdateText(RefPtr<ButtonLayoutProperty>& layoutProperty);
    bool IsNeedToHandleHoverOpacity();
    static void UpdateTextFontScale(
        RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty);
    void OnFontScaleConfigurationUpdate() override;
    void InitButtonAlphaOffscreen();
    Color backgroundColor_;
    Color focusBorderColor_;
    Color themeBgColor_;
    Color themeTextColor_;
    ComponentButtonType buttonType_ = ComponentButtonType::BUTTON;
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    GestureEventFunc tapEventFunc_;
    std::optional<ButtonMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    std::optional<GestureEventFunc> clickEventFunc_;
    int32_t nodeId_ = -1;
    std::function<void(UIState)> touchListener_;
    RefPtr<InputEvent> hoverListener_;
    bool isHover_ = false;
    bool isFocus_ = false;
    bool isPress_ = false;
    bool isApplyShadow_ = true;
    bool isLayoutUpdate_ = false;
    bool isInitButtonAlphaOffscreen_ = false;

    bool isInHover_ = false;
    Offset localLocation_;
    Dimension focusBorderWidth_;

    std::optional<Color> blendClickColor_ = std::nullopt;
    std::optional<Color> blendHoverColor_ = std::nullopt;

    bool isTextFadeOut_ = false;
    bool isColorUpdateFlag_ = false;
    SizeF preFrameSize_;
    bool hasCustomPadding_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(ButtonPattern);
    bool focusTextColorModify_ = false;
    bool bgColorModify_ = false;
    bool scaleModify_ = false;
    bool shadowModify_ = false;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    void HandleBorderAndShadow();
    void HandleFocusStatusStyle();
    void HandleFocusStyleTask();
    void HandleBlurStyleTask();
    void UpdateButtonStyle();
    void SetFocusButtonStyle(RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme,
        RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<FrameNode>& textNode);
    void SetBlurButtonStyle(RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme,
        RefPtr<ButtonLayoutProperty>& layoutProperty, RefPtr<FrameNode>& textNode);
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void HandleShadowStyle(ButtonStyleMode buttonStyle, ShadowStyle shadowStyle,
        RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme);
    Shadow GetShadowFromTheme(ShadowStyle shadowStyle);
    void HandleFocusActiveStyle();
    void SetButtonScale(RefPtr<RenderContext>& renderContext, RefPtr<ButtonTheme>& buttonTheme);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
