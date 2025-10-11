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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_PATTERN_H

#include <functional>
#include <unordered_map>

#include "core/components_ng/base/xbar_proxy_wrapper.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalStaticPattern : public ContainerModalPatternEnhance {
    DECLARE_ACE_TYPE(ContainerModalStaticPattern, ContainerModalPatternEnhance);

public:
    ContainerModalStaticPattern() = default;
    ~ContainerModalStaticPattern() override = default;

    void SetAppTitle(const std::string& title) override;
    void SetAppIcon(const RefPtr<PixelMap>& icon) override;
    void ChangeCustomTitle(bool isFocus) override;
    void ChangeFloatingTitle(bool isFocus) override;
    void ChangeControlButtons(bool isFocus) override;
    void CallMenuWidthChange(int32_t resId) override;
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;
    void SetColorConfigurationUpdate() override;
    void SetCloseButtonStatus(bool isEnabled) override;
    void SetMaximizeIconIsRecover() override;
    void OnContainerModalEvent(const std::string& name, const std::string& value) override;

    std::shared_ptr<XbarComponent> GetCustomTitle()
    {
        return customTitle_;
    }

    std::shared_ptr<XbarComponent> GetCustomFloatingTitle()
    {
        return customFloatingTitle_;
    }

    std::shared_ptr<XbarComponent> GetCustomButton()
    {
        return customButton_;
    }

    void SetCustomTitle(const std::shared_ptr<XbarComponent>& component)
    {
        customTitle_ = component;
    }

    void SetCustomFloatingTitle(const std::shared_ptr<XbarComponent>& component)
    {
        customFloatingTitle_ = component;
    }

    void SetCustomButton(const std::shared_ptr<XbarComponent>& component)
    {
        customButton_ = component;
    }

private:
    std::shared_ptr<XbarComponent> customTitle_;
    std::shared_ptr<XbarComponent> customFloatingTitle_;
    std::shared_ptr<XbarComponent> customButton_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_STATIC_PATTERN_H
