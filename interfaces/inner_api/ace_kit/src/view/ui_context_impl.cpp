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

#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"

#include "iremote_object.h"

#include "ui/base/utils/utils.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "interfaces/inner_api/ace_kit/src/view/overlay/overlay_manager_impl.h"

#include "base/geometry/ng/rect_t.h"
#include "base/thread/task_executor.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_application_info.h"
#include "core/common/container_scope.h"
#include "core/common/display_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Kit {
constexpr int32_t API_VERSION_LIMIT = 1000;

RefPtr<UIContext> UIContext::Current()
{
    const auto& pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetUIContext();
}

UIContextImpl::~UIContextImpl()
{
    Reset();
}

void UIContextImpl::Reset()
{
    context_ = nullptr;
}

void UIContextImpl::RunScopeUITaskSync(Task&& task, const std::string& name)
{
    CHECK_NULL_VOID(context_);
    const auto& taskExecutor = context_->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(context_->GetInstanceId());
    taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
}

void UIContextImpl::RunScopeUITask(Task&& task, const std::string& name)
{
    CHECK_NULL_VOID(context_);
    const auto& taskExecutor = context_->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(context_->GetInstanceId());
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void UIContextImpl::RunScopeUIDelayedTask(Task&& task, const std::string& name, uint32_t delayTime)
{
    CHECK_NULL_VOID(context_);
    const auto& taskExecutor = context_->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(context_->GetInstanceId());
    taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, delayTime, name);
}

void UIContextImpl::OnBackPressed()
{
    CHECK_NULL_VOID(context_);
    bool result = context_->OnBackPressed();
    if (!result) {
        auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->Back("");
    }
}

ColorMode UIContextImpl::GetLocalColorMode()
{
    CHECK_NULL_RETURN(context_, ColorMode::COLOR_MODE_UNDEFINED);
    return static_cast<ColorMode>(context_->GetLocalColorMode());
}

ColorMode UIContextImpl::GetColorMode()
{
    CHECK_NULL_RETURN(context_, ColorMode::COLOR_MODE_UNDEFINED);
    return static_cast<ColorMode>(context_->GetColorMode());
}

float UIContextImpl::GetFontScale()
{
    CHECK_NULL_RETURN(context_, 1.0f);
    return context_->GetFontScale();
}

RefPtr<OverlayManager> UIContextImpl::GetOverlayManager()
{
    if (overlayManager_) {
        return overlayManager_;
    }
    CHECK_NULL_RETURN(context_, nullptr);
    overlayManager_ = AceType::MakeRefPtr<OverlayManagerImpl>(context_);
    return overlayManager_;
}

void UIContextImpl::AddAfterLayoutTask(Task&& task, bool isFlushInImplicitAnimationTask)
{
    CHECK_NULL_VOID(context_);
    context_->AddAfterLayoutTask(std::move(task), isFlushInImplicitAnimationTask);
}

void UIContextImpl::RequestFrame()
{
    CHECK_NULL_VOID(context_);
    context_->RequestFrame();
}

int32_t UIContextImpl::GetApiTargetVersion()
{
    return AceApplicationInfo::GetInstance().GetApiTargetVersion() % API_VERSION_LIMIT;
}

bool UIContextImpl::GreatOrEqualTargetAPIVersion(int32_t version)
{
    return AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(static_cast<PlatformVersion>(version));
}

int32_t UIContextImpl::GetContainerModalTitleHeight()
{
    CHECK_NULL_RETURN(context_, 0);
    return context_->GetContainerModalTitleHeight();
}

int32_t UIContextImpl::GetContainerModalButtonsWidth()
{
    CHECK_NULL_RETURN(context_, 0);
    Ace::NG::RectF containerModal;
    Ace::NG::RectF buttonsRect;
    context_->GetContainerModalButtonsRect(containerModal, buttonsRect);
    return static_cast<int32_t>(buttonsRect.Width());
}

void UIContextImpl::RegisterArkUIObjectLifecycleCallback(ArkUIObjectLifecycleCallback&& callback)
{
    CHECK_NULL_VOID(context_);
    context_->RegisterArkUIObjectLifecycleCallback(std::move(callback));
}

void UIContextImpl::UnregisterArkUIObjectLifecycleCallback()
{
    CHECK_NULL_VOID(context_);
    context_->UnregisterArkUIObjectLifecycleCallback();
}

NG::OffsetF UIContextImpl::GetContainerModalButtonsOffset()
{
    Ace::NG::RectF buttonsRect;
    CHECK_NULL_RETURN(context_, buttonsRect.GetOffset());
    Ace::NG::RectF containerModal;
    context_->GetContainerModalButtonsRect(containerModal, buttonsRect);
    return buttonsRect.GetOffset();
}

sptr<IRemoteObject> UIContextImpl::GetToken()
{
    CHECK_NULL_RETURN(context_, nullptr);
    ContainerScope scope(context_->GetInstanceId());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetToken();
}

RefPtr<DisplayInfo> UIContextImpl::GetDisplayInfo()
{
    CHECK_NULL_RETURN(context_, nullptr);
    ContainerScope scope(context_->GetInstanceId());
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetDisplayInfo();
}

WindowMode UIContextImpl::GetWindowMode()
{
    CHECK_NULL_RETURN(context_, WindowMode::WINDOW_MODE_UNDEFINED);
    auto windowManager = context_->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, WindowMode::WINDOW_MODE_UNDEFINED);
    return windowManager->GetWindowMode();
}
bool UIContextImpl::GetIsMidScene()
{
    CHECK_NULL_RETURN(context_, false);
    auto windowManager = context_->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, false);
    bool isMidScene = false;
    windowManager->GetIsMidScene(isMidScene);
    return isMidScene;
}
bool UIContextImpl::IsAccessibilityEnabled()
{
    return AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
}

int32_t UIContextImpl::RegisterSurfaceChangedCallback(
    std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>&& callback)
{
    CHECK_NULL_RETURN(context_, 0);
    return context_->RegisterSurfaceChangedCallback(std::move(callback));
}

void UIContextImpl::UnregisterSurfaceChangedCallback(int32_t callbackId)
{
    CHECK_NULL_VOID(context_);
    context_->UnregisterSurfaceChangedCallback(callbackId);
}

int32_t UIContextImpl::RegisterFoldStatusChangedCallback(std::function<void(FoldStatus)>&& callback)
{
    CHECK_NULL_RETURN(context_, 0);
    return context_->RegisterFoldStatusChangedCallback(std::move(callback));
}

void UIContextImpl::UnRegisterFoldStatusChangedCallback(int32_t callbackId)
{
    CHECK_NULL_VOID(context_);
    context_->UnRegisterFoldStatusChangedCallback(callbackId);
}

int32_t UIContextImpl::RegisterRotationEndCallback(std::function<void()>&& callback)
{
    CHECK_NULL_RETURN(context_, 0);
    return context_->RegisterRotationEndCallback(std::move(callback));
}

void UIContextImpl::UnregisterRotationEndCallback(int32_t callbackId)
{
    CHECK_NULL_VOID(context_);
    context_->UnregisterRotationEndCallback(callbackId);
}

void UIContextImpl::AddWindowSizeChangeCallback(int32_t nodeId)
{
    CHECK_NULL_VOID(context_);
    context_->AddWindowSizeChangeCallback(nodeId);
}

} // namespace OHOS::Ace::Kit
