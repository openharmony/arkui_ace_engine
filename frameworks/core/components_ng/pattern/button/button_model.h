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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_request_data.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ButtonModel {
public:
    static ButtonModel* GetInstance();
    virtual ~ButtonModel() = default;

    virtual void SetFontSize(const Dimension& fontSize) = 0;
    virtual void SetFontWeight(const Ace::FontWeight& fontWeight) = 0;
    virtual void SetFontStyle(const Ace::FontStyle& fontStyle) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& fontFamily) = 0;
    virtual void SetFontColor(const Color& textColor) = 0;
    virtual void SetType(const int value) = 0;
    virtual void SetStateEffect(const bool stateEffect) = 0;
    virtual void SetLabelStyle(ButtonParameters& buttonParameters) {}
    virtual void CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) = 0;
    virtual void Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren) = 0;
    virtual void CreateWithChild(const CreateWithPara& para) = 0;
    virtual void Padding(const NG::PaddingProperty& paddingNew, const Edge& paddingOld) = 0;
    virtual void OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
        double distanceThreshold) = 0;
    virtual void BackgroundColor(const Color& color, const bool& colorFlag) = 0;
    virtual void SetWidth(const Dimension& width) {}
    virtual void SetHeight(const Dimension& height) {}
    virtual void SetAspectRatio(const double& ratio) {}
    virtual void SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height) = 0;
    virtual void SetBorderRadius(const Dimension& radius) = 0;
    virtual void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) = 0;
    virtual void SetLocalizedBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) {}
    virtual void ResetBorderRadius() {}
    virtual void SetRemoteMessage(RemoteCallback&& remoteCallback) {}
    virtual void SetButtonStyle(const std::optional<ButtonStyleMode>& buttonStyle) {}
    virtual void SetControlSize(const std::optional<ControlSize>& controlSize) {}
    virtual void SetRole(const std::optional<ButtonRole>& buttonRole) {}
    virtual void SetCreateWithLabel(bool isLabelButton) {}

private:
    static std::unique_ptr<ButtonModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_MODEL_H
