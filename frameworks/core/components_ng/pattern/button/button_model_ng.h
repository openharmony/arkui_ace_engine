/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/pattern/button/button_model.h"
#include "core/components/button/button_theme.h"

namespace OHOS::Ace::NG {
class ButtonConfiguration : public CommonConfiguration {
    public:
        ButtonConfiguration(const std::string& label, bool pressed, bool enabled)
            : CommonConfiguration(enabled), label_(label), pressed_(pressed)
        {}
        std::string label_;
        bool pressed_;
};
using ButtonMakeCallback =
    std::function<RefPtr<FrameNode>(const ButtonConfiguration& buttonConfiguration)>;
class ACE_EXPORT ButtonModelNG : public OHOS::Ace::ButtonModel {
public:
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(const Ace::FontWeight& fontWeight) override;
    void SetFontStyle(const Ace::FontStyle& fontStyle) override;
    void SetFontFamily(const std::vector<std::string>& fontFamily) override;
    void SetFontColor(const Color& textColor) override;
    void SetType(const int value) override;
    void SetStateEffect(const bool stateEffect) override;
    void SetLabelStyle(ButtonParameters& buttonParameters) override;
    void CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void CreateWithChild(const CreateWithPara& para) override;
    void Padding(const PaddingProperty& paddingNew, const Edge& paddingOld) override;
    void OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc, double distanceThreshold) override;
    void BackgroundColor(const Color& color, const bool& colorFlag) override;
    void SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height) override;
    void SetBorderRadius(const Dimension& radius) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override;
    void SetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopStart,
        const std::optional<Dimension>& radiusTopEnd, const std::optional<Dimension>& radiusBottomStart,
        const std::optional<Dimension>& radiusBottomEnd) override;
    void ResetBorderRadius() override;
    void SetButtonStyle(const std::optional<ButtonStyleMode>& buttonStyle) override;
    void SetControlSize(const std::optional<ControlSize>& controlSize) override;
    void SetRole(const std::optional<ButtonRole>& buttonRole) override;
    void SetCreateWithLabel(bool createWithLabel) override;
    void SetMinFontScale(float minFontScale) override;
    void SetMaxFontScale(float maxFontScale) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetFontSize(FrameNode* frameNode, const Dimension& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const Ace::FontWeight& fontWeight);
    static void SetFontStyle(FrameNode* frameNode, const Ace::FontStyle& fontStyle);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& fontFamily);
    static void SetFontColor(FrameNode* frameNode, const Color& textColor);
    static void SetType(FrameNode* frameNode, const int value);
    static void SetStateEffect(FrameNode* frameNode, const bool stateEffect);
    static void SetLabelStyle(FrameNode* frameNode, const ButtonParameters& buttonParameters);
    static void BackgroundColor(FrameNode* frameNode, const Color& color, const bool& colorFlag);
    static void SetBorderRadius(FrameNode* frameNode, const Dimension& radius);
    static void SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight);
    static void SetSize(
        FrameNode* frameNode, const std::optional<Dimension>& width, const std::optional<Dimension>& height);
    static void SetLabel(FrameNode* frameNode, const char* label);
    static std::string GetLabel(FrameNode* frameNode);
    static Dimension GetFontSize(FrameNode* frameNode);
    static Ace::FontWeight GetFontWeight(FrameNode* frameNode);
    static Color GetFontColor(FrameNode* frameNode);
    static void SetRole(FrameNode* frameNode, const std::optional<ButtonRole>& buttonRole);
    static void SetButtonStyle(FrameNode* frameNode, const std::optional<ButtonStyleMode>& buttonStyle);
    static void SetBuilderFunc(FrameNode* frameNode, NG::ButtonMakeCallback&& jsMake);
    static void TriggerClick(FrameNode* frameNode, double xPos, double yPos);
    static void SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize);
    static ButtonType GetType(FrameNode* frameNode);
    static void ApplyTheme(FrameNode* frameNode, ButtonStyleMode buttonStyle, ButtonRole buttonRole);
    static void SetLabelWithCheck(FrameNode* frameNode, const char* label);
    static void SetCreateWithLabel(FrameNode* frameNode, bool createWithLabel);
    static bool GetAutoDisable(FrameNode* frameNode);
    static void SetMinFontScale(FrameNode* frameNode, float minFontScale);
    static void SetMaxFontScale(FrameNode* frameNode, float maxFontScale);
    static float GetMinFontScale(FrameNode* frameNode);
    static float GetMaxFontScale(FrameNode* frameNode);

private:
    static void CreateWithLabel(const std::string& label);
    static void Create(const std::string& tagName);
    static void SetTypeAndStateEffect(const std::optional<ButtonType>& type, const std::optional<bool>& stateEffect);
    static void SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label);
    static void SetButtonSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize,
        RefPtr<ButtonTheme> buttonTheme);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_NG_H
