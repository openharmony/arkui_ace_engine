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
#include "core/common/container.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
namespace OHOS::Ace::NG {
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

    FocusPattern GetFocusPattern() const override
    {
        if (buttonType_ == ComponentButtonType::POPUP || buttonType_ == ComponentButtonType::STEPPER) {
            FocusPaintParam focusPaintParam;
            focusPaintParam.SetPaintColor(focusBorderColor_);
            return { FocusType::NODE, true, FocusStyleType::INNER_BORDER, focusPaintParam };
        }
        if (buttonType_ == ComponentButtonType::NAVIGATION) {
            FocusPaintParam focusPaintParam;
            focusPaintParam.SetPaintColor(focusBorderColor_);
            focusPaintParam.SetPaintWidth(focusBorderWidth_);
            return { FocusType::NODE, true, FocusStyleType::INNER_BORDER, focusPaintParam };
        }
        return { FocusType::NODE, true, FocusStyleType::OUTER_BORDER };
    }

    bool IsNeedAdjustByAspectRatio() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto layoutProperty = host->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_RETURN(host, false);
        auto isNeedAdjust = layoutProperty->HasAspectRatio() &&
               layoutProperty->GetType().value_or(ButtonType::CAPSULE) != ButtonType::CIRCLE;

        return isNeedAdjust;
    }

    void SetClickedColor(const Color& color)
    {
        clickedColor_ = color;
        isSetClickedColor_ = true;
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        Pattern::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto buttonTheme = context->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto textStyle = buttonTheme->GetTextStyle();
        auto buttonType = layoutProperty->GetType().value_or(ButtonType::CAPSULE);
        json->PutExtAttr("type", host->GetTag() == "Toggle" ? "ToggleType.Button" :
            ConvertButtonTypeToString(buttonType).c_str(), filter);
        json->PutExtAttr("fontSize",
            layoutProperty->GetFontSizeValue(layoutProperty->HasLabel() ? textStyle.GetFontSize() : Dimension(0))
                .ToString()
                .c_str(), filter);
        json->PutExtAttr("fontWeight", V2::ConvertWrapFontWeightToStirng(
            layoutProperty->GetFontWeight().value_or(FontWeight::MEDIUM)).c_str(), filter);
        json->PutExtAttr("fontColor", layoutProperty->GetFontColor()
                                   .value_or(layoutProperty->HasLabel() ? textStyle.GetTextColor() : Color::BLACK)
                                   .ColorToString()
                                   .c_str(), filter);
        json->PutExtAttr("fontStyle",
            layoutProperty->GetFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL ?
                "FontStyle.Normal" : "FontStyle.Italic", filter);
        json->PutExtAttr("label", layoutProperty->GetLabelValue("").c_str(), filter);
        auto eventHub = host->GetEventHub<ButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        json->PutExtAttr("stateEffect", eventHub->GetStateEffect() ? "true" : "false", filter);

        auto optionJson = JsonUtil::Create(true);
        optionJson->Put(
            "type", ConvertButtonTypeToString(layoutProperty->GetType().value_or(ButtonType::CAPSULE)).c_str());

        optionJson->Put("stateEffect", eventHub->GetStateEffect() ? "true" : "false");
        json->PutExtAttr("options", optionJson->ToString().c_str(), filter);
        ToJsonValueAttribute(json, filter);
    }

    void ToJsonValueAttribute(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto fontFamilyVector =
            layoutProperty->GetFontFamily().value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
        std::string fontFamily;
        if (!fontFamilyVector.empty()) {
            fontFamily = fontFamilyVector.at(0);
            for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
                fontFamily += ',' + fontFamilyVector.at(i);
            }
        }
        json->PutExtAttr("fontFamily", fontFamily.c_str(), filter);
        auto fontJsValue = JsonUtil::Create(true);
        fontJsValue->Put("size", layoutProperty->GetFontSizeValue(Dimension(0)).ToString().c_str());
        fontJsValue->Put("weight",
            V2::ConvertWrapFontWeightToStirng(layoutProperty->GetFontWeight().value_or(FontWeight::MEDIUM)).c_str());
        fontJsValue->Put("family", fontFamily.c_str());
        fontJsValue->Put(
            "style", layoutProperty->GetFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                         ? "FontStyle.Normal"
                         : "FontStyle.Italic");
        auto labelJsValue = JsonUtil::Create(true);
        labelJsValue->Put("overflow",
            V2::ConvertWrapTextOverflowToString(layoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP))
                .c_str());
        labelJsValue->Put("maxLines", std::to_string(layoutProperty->GetMaxLines().value_or(DEFAULT_MAXLINES)).c_str());
        labelJsValue->Put("minFontSize", layoutProperty->GetMinFontSizeValue(Dimension(0)).ToString().c_str());
        labelJsValue->Put("maxFontSize", layoutProperty->GetMaxFontSizeValue(Dimension(0)).ToString().c_str());
        labelJsValue->Put("heightAdaptivePolicy",
            V2::ConvertWrapTextHeightAdaptivePolicyToString(
                layoutProperty->GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST))
                .c_str());
        labelJsValue->Put("font", fontJsValue->ToString().c_str());
        json->PutExtAttr("labelStyle", labelJsValue->ToString().c_str(), filter);

        json->PutExtAttr("buttonStyle",
            ConvertButtonStyleToString(layoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE))
            .c_str(), filter);
        json->PutExtAttr("controlSize",
            ConvertControlSizeToString(layoutProperty->GetControlSize().value_or(ControlSize::NORMAL))
            .c_str(), filter);
        json->PutExtAttr(
            "role", ConvertButtonRoleToString(layoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL))
            .c_str(), filter);
    }

    static std::string ConvertButtonRoleToString(ButtonRole buttonRole)
    {
        std::string result;
        switch (buttonRole) {
            case ButtonRole::NORMAL:
                result = "ButtonRole.NORMAL";
                break;
            case ButtonRole::ERROR:
                result = "ButtonRole.ERROR";
                break;
            default:
                break;
        }
        return result;
    }

    static std::string ConvertButtonTypeToString(ButtonType buttonType)
    {
        std::string result;
        switch (buttonType) {
            case ButtonType::NORMAL:
                result = "ButtonType.Normal";
                break;
            case ButtonType::CAPSULE:
                result = "ButtonType.Capsule";
                break;
            case ButtonType::CIRCLE:
                result = "ButtonType.Circle";
                break;
            case ButtonType::ROUNDED_RECTANGLE:
                result = "ButtonType.ROUNDED_RECTANGLE";
                break;
            default:
                break;
        }
        return result;
    }

    static std::string ConvertButtonStyleToString(ButtonStyleMode buttonStyle)
    {
        std::string result;
        switch (buttonStyle) {
            case ButtonStyleMode::NORMAL:
                result = "ButtonStyleMode.NORMAL";
                break;
            case ButtonStyleMode::EMPHASIZE:
                result = "ButtonStyleMode.EMPHASIZED";
                break;
            case ButtonStyleMode::TEXT:
                result = "ButtonStyleMode.TEXTUAL";
                break;
            default:
                break;
        }
        return result;
    }

    static std::string ConvertControlSizeToString(ControlSize controlSize)
    {
        std::string result;
        switch (controlSize) {
            case ControlSize::SMALL:
                result = "ControlSize.SMALL";
                break;
            case ControlSize::NORMAL:
                result = "ControlSize.NORMAL";
                break;
            default:
                break;
        }
        return result;
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

    RefPtr<InputEvent>& GetHoverListener()
    {
        return hoverListener_;
    }

    RefPtr<TouchEventImpl>& GetTouchListener()
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

    bool IsDynamicSwitchButtonStyle(const BorderColorProperty& color, RefPtr<ButtonTheme>& buttonTheme);

    bool IsDynamicSwitchButtonStyle(const BorderWidthProperty& width, RefPtr<ButtonTheme>& buttonTheme);

protected:
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void OnAttachToFrameNode() override;
    void InitTouchEvent();
    void InitHoverEvent();
    void OnTouchDown();
    void OnTouchUp();
    void HandleHoverEvent(bool isHover);
    void HandleBackgroundColor();
    void UpdateTexOverflow(bool isMarqueeStart);
    void HandleEnabled();
    void InitButtonLabel();
    void CheckLocalizedBorderRadiuses();
    Color GetColorFromType(const RefPtr<ButtonTheme>& theme, const int32_t& type);
    void AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, int32_t typeFrom, int32_t typeTo, int32_t duration,
        const RefPtr<Curve>& curve);
    Color clickedColor_;

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
    Color backgroundColor_;
    Color focusBorderColor_;
    Color themeBgColor_;
    Color themeTextColor_;
    bool isSetClickedColor_ = false;
    ComponentButtonType buttonType_ = ComponentButtonType::BUTTON;
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    GestureEventFunc tapEventFunc_;
    std::optional<ButtonMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    std::optional<GestureEventFunc> clickEventFunc_;
    int32_t nodeId_ = -1;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> hoverListener_;
    bool isHover_ = false;
    bool isFocus_ = false;
    bool isPress_ = false;
    bool isApplyShadow_ = true;
    bool isLayoutUpdate_ = false;

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
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
