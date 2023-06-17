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

#include "core/components_ng/pattern/button/button_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ButtonModelNG : public OHOS::Ace::ButtonModel {
public:
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(const Ace::FontWeight& fontWeight) override;
    void SetFontStyle(const Ace::FontStyle& fontStyle) override;
    void SetFontFamily(const std::vector<std::string>& fontFamily) override;
    void SetFontColor(const Color& textColor) override;
    void SetType(const int value) override;
    void SetStateEffect(const bool stateEffect) override;
    void SetLableStyle(ButtonParameters& buttonParameters) override;
    void CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void CreateWithChild(const CreateWithPara& para) override;
    void Padding(const PaddingProperty& paddingNew, const Edge& paddingOld) override;
    void OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override;
    void BackgroundColor(const Color& color, const bool& colorFlag) override;
    void SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height) override;
    void SetBorderRadius(const Dimension& radius) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override;
    void SetHoverEffect(const int32_t& hoverEffectNum) override;

private:
    static void CreateWithLabel(const std::string& label);
    static void Create(const std::string& tagName);
    static void SetTypeAndStateEffect(const std::optional<ButtonType>& type, const std::optional<bool>& stateEffect);
    static void SetTextDefaultStyle(const RefPtr<FrameNode>& textNode, const std::string& label);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_NG_H
