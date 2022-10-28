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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_SUBWINDOW_OHOS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_SUBWINDOW_OHOS_H

#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow.h"

namespace OHOS::Ace {

class Component;

class SubwindowOhos : public Subwindow {
    DECLARE_ACE_TYPE(SubwindowOhos, Subwindow)

public:
    explicit SubwindowOhos(int32_t instanceId);
    ~SubwindowOhos() = default;
    RefPtr<SubwindowOhos> CreateSubwindow(int32_t instanceId);
    void ShowMenu(const RefPtr<Component>& newComponent) override {}
    void ShowMenuNG(const RefPtr<NG::FrameNode> menuNode, int32_t targetId, const NG::OffsetF& offset) override {}
    void HideMenuNG(int32_t targetId) override {}
    void ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent = true) override {}
    bool CancelPopup(const std::string& id) override
    {
        return false;
    }
    void CloseMenu() override {}
    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom) override {}
    void ShowDialog(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) override {}
    void ShowActionMenu(const std::string& title,
        const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback) override {}
    void InitContainer() override;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_SUBWINDOW_OHOS_H
