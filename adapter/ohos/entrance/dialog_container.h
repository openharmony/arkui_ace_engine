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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_DIALOG_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_DIALOG_CONTAINER_H

#include <memory>
#include <mutex>

#include "adapter/ohos/entrance/ace_container.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"
#include "core/common/window.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace::Platform {
class DialogContainer : public AceContainer {
    DECLARE_ACE_TYPE(DialogContainer, AceContainer);

public:
    explicit DialogContainer(int32_t instanceId, FrontendType type = FrontendType::DECLARATIVE_JS);
    ~DialogContainer() override = default;

    bool IsDialogContainer() const override
    {
        return true;
    }

    static void ShowToast(int32_t instanceId, const NG::ToastInfo& toastInfo,
        std::function<void(int32_t)>&& callback);
    static void CloseToast(int32_t instanceId, const int32_t toastId, std::function<void(int32_t)>&& callback);
    static void ShowDialog(int32_t instanceId, const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    static void ShowDialog(int32_t instanceId, const PromptDialogAttr& dialogAttr,
        const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    static void ShowActionMenu(int32_t instanceId, const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    static bool ShowToastDialogWindow(
        int32_t instanceId, int32_t posX, int32_t posY, int32_t width, int32_t height, bool isToast = false);

    static bool OnBackPressed(int32_t instanceId);

#if defined(ACE_STATIC)
    static void ShowToastStatic(int32_t instanceId, const NG::ToastInfo& toastInfo,
        std::function<void(int32_t)>&& callback);
    static void CloseToastStatic(int32_t instanceId, const int32_t toastId, std::function<void(int32_t)>&& callback);
    static void ShowDialogStatic(int32_t instanceId, const DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback);
    static void ShowActionMenuStatic(int32_t instanceId, const DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback);
#endif
private:
    ACE_DISALLOW_COPY_AND_MOVE(DialogContainer);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_DIALOG_CONTAINER_H
