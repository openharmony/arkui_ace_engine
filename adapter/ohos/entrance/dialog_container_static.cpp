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

#include "adapter/ohos/entrance/dialog_container.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/overlay/dialog_manager_static.h"

namespace OHOS::Ace::Platform {
void DialogContainer::ShowToastStatic(int32_t instanceId, const NG::ToastInfo& toastInfo,
    std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto toastInfoNew = toastInfo;
    toastInfoNew.showMode = NG::ToastShowMode::DEFAULT;
    NG::DialogManagerStatic::ShowToastStatic(toastInfoNew, std::move(callback), instanceId);
}

void DialogContainer::CloseToastStatic(int32_t instanceId, int32_t toastId, std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    NG::DialogManagerStatic::CloseToastStatic(toastId, std::move(callback), instanceId);
}

void DialogContainer::ShowDialogStatic(int32_t instanceId, const DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog with attr begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto dialogPropsNew = dialogProps;
    dialogPropsNew.onStatusChanged = [instanceId = instanceId](bool isShow) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
        if (!isShow) {
            AceContainer::HideWindow(instanceId);
        }
    };
    NG::DialogManagerStatic::ShowDialogStatic(dialogPropsNew, std::move(callback), instanceId);
}

void DialogContainer::ShowActionMenuStatic(int32_t instanceId, const DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto dialogPropsNew = dialogProps;
    dialogPropsNew.onStatusChanged = [instanceId = instanceId](bool isShow) {
        if (!isShow) {
            AceContainer::HideWindow(instanceId);
        }
    };
    NG::DialogManagerStatic::ShowActionMenuStatic(dialogPropsNew, std::move(callback), instanceId);
}
} // namespace OHOS::Ace::Platform
