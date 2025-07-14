/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_STATIC_H

#include "core/components_ng/pattern/button/button_model.h"
#include "core/components/button/button_theme.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ButtonModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& fontWeight);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& fontStyle);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamily);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& textColor);
    static void SetType(FrameNode* frameNode, const std::optional<int> value);
    static void SetStateEffect(FrameNode* frameNode, const std::optional<bool> stateEffect);
    static void SetLabelStyle(FrameNode* frameNode, const std::optional<ButtonParameters>& buttonParameters);
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
    static void TriggerClick(FrameNode* frameNode, double xPos, double yPos);
    static void SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize);
    static ButtonType GetType(FrameNode* frameNode);
    static void ApplyTheme(FrameNode* frameNode, ButtonStyleMode buttonStyle, ButtonRole buttonRole);
    static void SetLabelWithCheck(FrameNode* frameNode, const char* label);
    static void SetCreateWithLabel(FrameNode* frameNode, bool createWithLabel);
    static bool GetAutoDisable(FrameNode* frameNode);
    static void SetMinFontScale(FrameNode* frameNode, const std::optional<float>& minFontScale);
    static void SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& maxFontScale);
    static float GetMinFontScale(FrameNode* frameNode);
    static float GetMaxFontScale(FrameNode* frameNode);

private:
    static void SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label);
    static void SetButtonSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize,
        RefPtr<ButtonTheme> buttonTheme);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_STATIC_H
