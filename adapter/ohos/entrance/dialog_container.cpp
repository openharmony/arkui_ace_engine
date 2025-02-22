/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/dialog_container.h"

#include <mutex>

#include "adapter/ohos/entrance/ace_application_info.h"
#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
#include "adapter/ohos/entrance/ace_rosen_sync_task.h"
#endif
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "base/log/frame_report.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/task_executor_impl.h"
#include "core/common/text_field_manager.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/subwindow/subwindow_manager.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"

namespace OHOS::Ace::Platform {
DialogContainer::DialogContainer(int32_t instanceId, FrontendType type) : AceContainer(instanceId, type)
{}

void DialogContainer::ShowToast(int32_t instanceId, const std::string& message, int32_t duration,
    const std::string& bottom, std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->SetToastStopListenerCallback([instanceId = instanceId]() {
        if (ContainerScope::CurrentId() >= 0) {
            AceContainer::HideWindow(instanceId);
        }
    });
    auto toastInfo = NG::ToastInfo { .message = message,
        .duration = duration,
        .bottom = bottom,
        .showMode = NG::ToastShowMode::DEFAULT,
        .alignment = -1,
        .offset = std::nullopt };
    delegate->ShowToast(toastInfo, std::move(callback));
}

void DialogContainer::CloseToast(int32_t instanceId, int32_t toastId, std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);

    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);

    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->SetToastStopListenerCallback([instanceId = instanceId]() {
        if (ContainerScope::CurrentId() >= 0) {
            AceContainer::HideWindow(instanceId);
        }
    });

    delegate->CloseToast(toastId, std::move(callback));
}

void DialogContainer::ShowDialog(int32_t instanceId, const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowDialog(
        title, message, buttons, autoCancel, std::move(callback), callbacks, [instanceId = instanceId](bool isShow) {
            TAG_LOGI(
                AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
            if (!isShow) {
                AceContainer::HideWindow(instanceId);
            }
        });
}

void DialogContainer::ShowDialog(int32_t instanceId, const PromptDialogAttr& dialogAttr,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog with attr begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowDialog(dialogAttr, buttons, std::move(callback), callbacks, [instanceId = instanceId](bool isShow) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
        if (!isShow) {
            AceContainer::HideWindow(instanceId);
        }
    });
}

void DialogContainer::ShowActionMenu(int32_t instanceId, const std::string& title,
    const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowActionMenu(title, button, std::move(callback), [instanceId = instanceId](bool isShow) {
        if (!isShow) {
            AceContainer::HideWindow(instanceId);
        }
    });
}

bool DialogContainer::ShowToastDialogWindow(
    int32_t instanceId, int32_t posX, int32_t posY, int32_t width, int32_t height, bool isToast)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowToastDialogWindow begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    window->SetTransparent(true);
    if (isToast) {
        window->SetTouchable(false);
    }
    window->SetNeedDefaultAnimation(false);
    OHOS::Rosen::WMError ret = window->MoveTo(posX, posY);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGW(AceLogTag::ACE_DIALOG, "DialogContainer ShowToastDialogWindow MoveTo window failed code: %{public}d",
            static_cast<int32_t>(ret));
        return false;
    }
    ret = window->Resize(width, height);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGW(AceLogTag::ACE_DIALOG, "DialogContainer ShowToastDialogWindow Resize window failed code: %{public}d",
            static_cast<int32_t>(ret));
        return false;
    }
    ret = window->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "DialogContainer ShowToastDialogWindow Show window failed code: %{public}d",
            static_cast<int32_t>(ret));
        return false;
    }
    return true;
}


bool DialogContainer::OnBackPressed(int32_t instanceId)
{
    return AceContainer::CloseWindow(instanceId);
}

} // namespace OHOS::Ace::Platform
