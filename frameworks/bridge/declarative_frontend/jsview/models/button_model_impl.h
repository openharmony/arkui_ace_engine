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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BUTTON_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BUTTON_MODEL_IMPL_H

#include "core/components/button/button_component.h"
#include "core/components/text/text_component.h"
#include "core/components_ng/pattern/button/button_model.h"

namespace OHOS::Ace::Framework {
class ButtonModelImpl : public OHOS::Ace::ButtonModel {
public:
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(const Ace::FontWeight& fontWeight) override;
    void SetFontStyle(const Ace::FontStyle& fontStyle) override;
    void SetFontFamily(const std::vector<std::string>& fontFamily) override;
    void SetFontColor(const Color& textColor) override;
    void SetType(const int value) override;
    void SetStateEffect(const bool stateEffect) override;
    void CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) override;
    void CreateWithChild(const CreateWithPara& para) override;
    void Padding(const NG::PaddingProperty& paddingNew, const Edge& paddingOld) override;
    void OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override;
    void BackgroundColor(const Color& color, const bool& colorFlag) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetAspectRatio(const double& ratio) override;
    void SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height) override;
    void SetBorderRadius(const Dimension& radius) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) override {};
    void SetRemoteMessage(RemoteCallback&& remoteCallback) override;

private:
    static RefPtr<TextComponent> GetTextComponent();
    static void ResetButtonHeight();
    static void SetTypeAndStateEffect(const std::optional<ButtonType>& type, const std::optional<bool>& stateEffect,
        const RefPtr<ButtonComponent>& buttonComponent);
    static void SetDefaultAttributes(const RefPtr<ButtonComponent>& buttonComponent);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_BUTTON_MODEL_IMPL_H
