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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_accessibility_property.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
enum class ComponentButtonType { POPUP, BUTTON };
class ButtonPattern : public Pattern {
    DECLARE_ACE_TYPE(ButtonPattern, Pattern);

public:
    ButtonPattern() = default;

    ~ButtonPattern() override = default;

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

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ButtonAccessibilityProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::OUTER_BORDER };
    }

    void SetClickedColor(const Color& color)
    {
        clickedColor_ = color;
        isSetClickedColor_ = true;
    }

    void SetFocusBorderColor(const Color& color)
    {
        FocusBorderColor_ = color;
    }

    void setComponentButtonType(const ComponentButtonType& buttonType)
    {
        buttonType_ = buttonType;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        Pattern::ToJsonValue(json);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        json->Put(
            "type", host->GetTag() == "Toggle"
                        ? "ToggleType.Button"
                        : ConvertButtonTypeToString(layoutProperty->GetType().value_or(ButtonType::CAPSULE)).c_str());
        json->Put("fontSize", layoutProperty->GetFontSizeValue(Dimension(0)).ToString().c_str());
        json->Put("fontWeight",
            V2::ConvertWrapFontWeightToStirng(layoutProperty->GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
        json->Put("fontColor", layoutProperty->GetFontColor().value_or(Color::BLACK).ColorToString().c_str());
        auto fontFamilyVector =
            layoutProperty->GetFontFamily().value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
        std::string fontFamily = fontFamilyVector.at(0);
        for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
            fontFamily += ',' + fontFamilyVector.at(i);
        }
        json->Put("fontFamily", fontFamily.c_str());
        json->Put("fontStyle", layoutProperty->GetFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                                   ? "FontStyle.Normal"
                                   : "FontStyle.Italic");
        json->Put("label", layoutProperty->GetLabelValue("").c_str());
        auto eventHub = host->GetEventHub<ButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        json->Put("stateEffect", eventHub->GetStateEffect() ? "true" : "false");
        auto optionJson = JsonUtil::Create(true);
        optionJson->Put(
            "type", ConvertButtonTypeToString(layoutProperty->GetType().value_or(ButtonType::CAPSULE)).c_str());
        optionJson->Put("stateEffect", eventHub->GetStateEffect() ? "true" : "false");
        json->Put("options", optionJson->ToString().c_str());
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
            default:
                LOGD("The input does not match any ButtonType");
        }
        return result;
    }

protected:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void InitTouchEvent();
    void OnTouchDown();
    void OnTouchUp();
    void HandleEnabled();
    void InitButtonLabel();
    void AnimateTouchEffectBoard(float startOpacity, float endOpacity, int32_t duration, const RefPtr<Curve>& curve);
    Color clickedColor_;

private:
    static void SetDefaultAttributes(const RefPtr<FrameNode>& buttonNode, const RefPtr<PipelineBase>& pipeline);

    Color backgroundColor_;
    Color FocusBorderColor_;
    bool isSetClickedColor_ = false;
    ComponentButtonType buttonType_ = ComponentButtonType::BUTTON;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> mouseEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(ButtonPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
