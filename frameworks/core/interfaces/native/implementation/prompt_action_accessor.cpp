/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components/toast/toast_theme.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace::NG {
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
#ifdef OHOS_STANDARD_SYSTEM
bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafely();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}

bool ContainerIsScenceBoard()
{
    auto container = Container::CurrentSafely();
    if (!container) {
        container = Container::GetActive();
    }
    return container;//&& container->IsScenceBoardWindow();
}
#endif

void RunTaskInOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            task(weak.Upgrade());
        },
        TaskExecutor::TaskType::UI, name);
}

void ShowToastCommon(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    auto task = [toastInfo, callbackParam = std::move(callback), containerId = Container::CurrentId()](
        const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        overlayManager->ShowToast(
            toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
    };
    RunTaskInOverlay(std::move(task), "ArkUIOverlayShowToast");
}
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
ToastInfo Convert(const Ark_ShowToastOptions& options)
{
    int32_t alignment = -1;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
        if (toastTheme) {
            alignment = toastTheme->GetAlign();
        }
    }
    auto toastInfo = NG::ToastInfo { .duration = -1, .showMode = NG::ToastShowMode::DEFAULT, .alignment = alignment };
    Converter::VisitUnion(options.message,
        [&toastInfo](const Ark_String& val) {
            toastInfo.message = Converter::Convert<std::string>(val);
        },
        [&toastInfo](const Ark_Resource& val) {
            auto msgResourceStr = Converter::OptConvert<std::string>(val);
            if (msgResourceStr) {
                toastInfo.message = msgResourceStr.value();
            }
        },
        []() {}
    );
    toastInfo.duration = std::clamp(toastInfo.duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    return toastInfo;
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PromptActionAccessor {
void ShowToastImpl(const Ark_ShowToastOptions* options)
{
    auto toastInfo = Converter::Convert<ToastInfo>(*options);
    std::function<void(int32_t)> toastCallback = nullptr;
#ifdef OHOS_STANDARD_SYSTEM
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) && !ContainerIsScenceBoard() &&
        toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        ShowToastCommon(toastInfo, std::move(toastCallback));
    }
    // else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
    //     OHOS::Ace::SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    // }
#else
    if (toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        ShowToastCommon(toastInfo, std::move(toastCallback));
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToast(toastInfo, std::move(toastCallback));
    }
#endif
}
} // PromptActionAccessor

const GENERATED_ArkUIPromptActionAccessor* GetPromptActionAccessor()
{
    static const GENERATED_ArkUIPromptActionAccessor PromptActionAccessorImpl {
        PromptActionAccessor::ShowToastImpl,
    };
    return &PromptActionAccessorImpl;
}
}