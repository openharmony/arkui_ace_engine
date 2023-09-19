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
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/text_field_manager.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/subwindow/subwindow_manager.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"

namespace OHOS::Ace::Platform {
DialogContainer::DialogContainer(int32_t instanceId, FrontendType type) : instanceId_(instanceId), type_(type)
{
    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();
    flutterTaskExecutor->InitPlatformThread(true);
    taskExecutor_ = flutterTaskExecutor;
    GetSettings().useUIAsJSThread = true;
    GetSettings().usePlatformAsUIThread = true;
    GetSettings().usingSharedRuntime = true;
}

void DialogContainer::InitializeTouchEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& touchEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const TouchEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess, id]() {
                context->OnTouchEvent(event);
                context->NotifyDispatchTouchEventDismiss(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);
}

void DialogContainer::InitializeMouseEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& mouseEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const MouseEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess, id]() {
                context->OnMouseEvent(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);
}

void DialogContainer::InitializeAxisEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& axisEventCallback = [context = pipelineContext_, id = instanceId_](
                                   const AxisEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess, id]() {
                context->OnAxisEvent(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterAxisEventCallback(axisEventCallback);
}

void DialogContainer::InitializeKeyEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& keyEventCallback = [context = pipelineContext_, id = instanceId_](const KeyEvent& event) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnKeyEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterKeyEventCallback(keyEventCallback);
}

void DialogContainer::InitializeRotationEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& rotationEventCallback = [context = pipelineContext_, id = instanceId_](const RotationEvent& event) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnRotationEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterRotationEventCallback(rotationEventCallback);
}

void DialogContainer::InitializeViewChangeCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& viewChangeCallback = [context = pipelineContext_, id = instanceId_](int32_t width, int32_t height,
                                    WindowSizeChangeReason type,
                                    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("ViewChangeCallback(%d, %d)", width, height);
        context->GetTaskExecutor()->PostTask(
            [context, width, height, type, rsTransaction]() {
                context->OnSurfaceChanged(width, height, type, rsTransaction);
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterViewChangeCallback(viewChangeCallback);
}

void DialogContainer::InitializeDensityChangeCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& densityChangeCallback = [context = pipelineContext_, id = instanceId_](double density) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("DensityChangeCallback(%lf)", density);
        context->GetTaskExecutor()->PostTask(
            [context, density]() { context->OnSurfaceDensityChanged(density); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterDensityChangeCallback(densityChangeCallback);
}

void DialogContainer::InitializeSystemBarHeightChangeCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& systemBarHeightChangeCallback = [context = pipelineContext_, id = instanceId_](
                                               double statusBar, double navigationBar) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("SystemBarHeightChangeCallback(%lf, %lf)", statusBar, navigationBar);
        context->GetTaskExecutor()->PostTask(
            [context, statusBar, navigationBar]() { context->OnSystemBarHeightChanged(statusBar, navigationBar); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);
}

void DialogContainer::InitializeSurfaceDestroyCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& surfaceDestroyCallback = [context = pipelineContext_, id = instanceId_]() {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);
}

void DialogContainer::InitializeDragEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& dragEventCallback = [context = pipelineContext_, id = instanceId_](
                                   int32_t x, int32_t y, const DragEventAction& action) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, x, y, action]() { context->OnDragEvent(x, y, action); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterDragEventCallback(dragEventCallback);
}

void DialogContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();
    InitializeTouchEventCallback();
    InitializeMouseEventCallback();
    InitializeAxisEventCallback();
    InitializeKeyEventCallback();
    InitializeRotationEventCallback();
    InitializeViewChangeCallback();
    InitializeDensityChangeCallback();
    InitializeSystemBarHeightChangeCallback();
    InitializeSurfaceDestroyCallback();
    InitializeDragEventCallback();
}

RefPtr<DialogContainer> DialogContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto dialogContainer = AceType::DynamicCast<DialogContainer>(container);
    return dialogContainer;
}

void DialogContainer::DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback)
{
    LOGI("DialogContainer DestroyContainer begin %{public}d", instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    container->Destroy();
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask([] { LOGI("Wait UI thread..."); }, TaskExecutor::TaskType::UI);
    taskExecutor->PostSyncTask([] { LOGI("Wait JS thread..."); }, TaskExecutor::TaskType::JS);
    container->DestroyView(); // Stop all threads(ui,gpu,io) for current ability.
    taskExecutor->PostTask(
        [instanceId, destroyCallback] {
            LOGI("DialogContainer DestroyContainer Remove on Platform thread...");
            EngineHelper::RemoveEngine(instanceId);
            AceEngine::Get().RemoveContainer(instanceId);
            CHECK_NULL_VOID(destroyCallback);
            destroyCallback();
        },
        TaskExecutor::TaskType::PLATFORM);
}

void DialogContainer::Destroy()
{
    LOGI("DialogContainer Destroy begin");
    ContainerScope scope(instanceId_);
    if (pipelineContext_ && taskExecutor_) {
        // 1. Destroy Pipeline on UI thread.
        RefPtr<PipelineBase>& context = pipelineContext_;
        if (GetSettings().usePlatformAsUIThread) {
            context->Destroy();
        } else {
            taskExecutor_->PostTask([context]() { context->Destroy(); }, TaskExecutor::TaskType::UI);
        }
        // 2. Destroy Frontend on JS thread.
        RefPtr<Frontend>& frontend = frontend_;
        if (GetSettings().usePlatformAsUIThread && GetSettings().useUIAsJSThread) {
            frontend->UpdateState(Frontend::State::ON_DESTROY);
            frontend->Destroy();
        } else {
            taskExecutor_->PostTask(
                [frontend]() {
                    frontend->UpdateState(Frontend::State::ON_DESTROY);
                    frontend->Destroy();
                },
                TaskExecutor::TaskType::JS);
        }
    }
    resRegister_.Reset();
    assetManager_.Reset();
}

void DialogContainer::DestroyView()
{
    LOGI("DialogContainer DestroyView begin");
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(aceView_);
    auto* aceView = static_cast<AceViewOhos*>(aceView_);
    if (aceView) {
        aceView->DecRefCount();
    }
    aceView_ = nullptr;
}

void DialogContainer::SetView(
    AceView* view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window>& rsWindow)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
#ifdef ENABLE_ROSEN_BACKEND
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    std::unique_ptr<Window> window = std::make_unique<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
#else
    auto platformWindow = PlatformWindow::Create(view);
    CHECK_NULL_VOID(platformWindow);
    std::unique_ptr<Window> window = std::make_unique<Window>(std::move(platformWindow));
#endif
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId());
}

void DialogContainer::SetViewNew(
    AceView* view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window>& rsWindow)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    std::unique_ptr<Window> window = std::make_unique<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId());
#endif
}

void DialogContainer::AttachView(
    std::unique_ptr<Window> window, AceView* view, double density, int32_t width, int32_t height, uint32_t windowId)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    auto flutterTaskExecutor = AceType::DynamicCast<FlutterTaskExecutor>(taskExecutor_);
    auto* aceView = static_cast<AceViewOhos*>(aceView_);
    ACE_DCHECK(aceView != nullptr);
    flutterTaskExecutor->InitOtherThreads(aceView->GetThreadModel());
    ContainerScope scope(instanceId);
    // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
    flutterTaskExecutor->InitJsThread(false);
    InitializeFrontend();
    SetUseNewPipeline();

    InitPipelineContext(std::move(window), instanceId, density, width, height, windowId);
    InitializeCallback();

    taskExecutor_->PostTask([] { FrameReport::GetInstance().Init(); }, TaskExecutor::TaskType::UI);
    ThemeConstants::InitDeviceType();
    // Load custom style at UI thread before frontend attach, to make sure style can be loaded before building dom tree.
    auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
    if (themeManager) {
        pipelineContext_->SetThemeManager(themeManager);
        // Init resource
        themeManager->InitResource(resourceInfo_);
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_] {
                ACE_SCOPED_TRACE("OHOS::LoadThemes()");
                LOGI("UIContent load theme");
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                themeManager->LoadResourceThemes();
            },
            TaskExecutor::TaskType::UI);
    }
    aceView_->Launch();
    // Only MainWindow instance will be registered to watch dog.
    frontend_->AttachPipelineContext(pipelineContext_);
#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
    pipelineContext_->SetPostRTTaskCallBack([](std::function<void()>&& task) {
        auto syncTask = std::make_shared<AceRosenSyncTask>(std::move(task));
        Rosen::RSTransactionProxy::GetInstance()->ExecuteSynchronousTask(syncTask);
    });
#endif
}

void DialogContainer::InitPipelineContext(std::unique_ptr<Window> window, int32_t instanceId, double density,
    int32_t width, int32_t height, uint32_t windowId)
{
#ifdef NG_BUILD
    LOGI("New pipeline version creating...");
    pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
        std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
#else
    if (useNewPipeline_) {
        LOGI("New pipeline version creating...");
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    } else {
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    }
#endif
    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowId(windowId);
    pipelineContext_->SetWindowModal(windowModal_);
    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    pipelineContext_->SetIsSubPipeline(true);
}

void DialogContainer::InitializeFrontend()
{
    frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
    CHECK_NULL_VOID(frontend_);
    frontend_->Initialize(type_, taskExecutor_);
    auto front = GetFrontend();
    CHECK_NULL_VOID(front);
    front->UpdateState(Frontend::State::ON_CREATE);
    front->SetJsMessageDispatcher(AceType::Claim(this));
    front->SetAssetManager(assetManager_);
}

void DialogContainer::DumpHeapSnapshot(bool isPrivate)
{
    taskExecutor_->PostTask(
        [isPrivate, frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            CHECK_NULL_VOID(sp);
            sp->DumpHeapSnapshot(isPrivate);
        },
        TaskExecutor::TaskType::JS);
}
void DialogContainer::SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window>& uiWindow)
{
    CHECK_NULL_VOID(uiWindow);
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    container->SetUIWindowInner(uiWindow);
}

sptr<OHOS::Rosen::Window> DialogContainer::GetUIWindow(int32_t instanceId)
{
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetUIWindowInner();
}

void DialogContainer::SetUIWindowInner(sptr<OHOS::Rosen::Window> uiWindow)
{
    uiWindow_ = std::move(uiWindow);
}

sptr<OHOS::Rosen::Window> DialogContainer::GetUIWindowInner() const
{
    return uiWindow_;
}

void DialogContainer::ShowToast(
    int32_t instanceId, const std::string& message, int32_t duration, const std::string& bottom)
{
    LOGI("DialogContainer ShowToast begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->SetToastStopListenerCallback([instanceId = instanceId]() {
        LOGI("DialogContainer::ShowToast HideWindow instanceId = %{public}d", instanceId);
        if (ContainerScope::CurrentId() >= 0) {
            DialogContainer::HideWindow(instanceId);
        }
    });
    delegate->ShowToast(message, duration, bottom);
}

void DialogContainer::ShowDialog(int32_t instanceId, const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    LOGI("DialogContainer ShowDialog begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowDialog(
        title, message, buttons, autoCancel, std::move(callback), callbacks, [instanceId = instanceId](bool isShow) {
            LOGI("DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
            if (!isShow) {
                DialogContainer::HideWindow(instanceId);
            }
        });
}

void DialogContainer::ShowDialog(int32_t instanceId, const PromptDialogAttr& dialogAttr,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    LOGI("DialogContainer ShowDialog begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowDialog(
        dialogAttr, buttons, std::move(callback), callbacks, [instanceId = instanceId](bool isShow) {
            LOGI("DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
            if (!isShow) {
                DialogContainer::HideWindow(instanceId);
            }
        });
}

void DialogContainer::ShowActionMenu(int32_t instanceId, const std::string& title,
    const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    LOGI("show action menu begin");
    delegate->ShowActionMenu(title, button, std::move(callback), [instanceId = instanceId](bool isShow) {
        LOGI("DialogContainer ShowActionMenu HideWindow instanceId = %{public}d", instanceId);
        if (!isShow) {
            DialogContainer::HideWindow(instanceId);
        }
    });
}

bool DialogContainer::ShowToastDialogWindow(
    int32_t instanceId, int32_t posX, int32_t posY, int32_t width, int32_t height, bool isToast)
{
    LOGI("DialogContainer ShowToastDialogWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    window->SetTransparent(true);
    if (isToast) {
        window->SetTouchable(false);
    }
    window->SetNeedDefaultAnimation(false);
    OHOS::Rosen::WMError ret = window->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DialogContainer ShowToastDialogWindow Show window failed code: %{public}d", static_cast<int32_t>(ret));
        return false;
    }
    ret = window->MoveTo(posX, posY);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DialogContainer ShowToastDialogWindow MoveTo window failed code: %{public}d", static_cast<int32_t>(ret));
        return false;
    }
    ret = window->Resize(width, height);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DialogContainer ShowToastDialogWindow Resize window failed code: %{public}d", static_cast<int32_t>(ret));
        return false;
    }
    return true;
}

bool DialogContainer::HideWindow(int32_t instanceId)
{
    LOGI("DialogContainer HideWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Hide();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DialogContainer HideWindow Failed to hide the window.");
        return false;
    }
    sptr<OHOS::Rosen::Window> uiWindow = nullptr;
    DialogContainer::SetUIWindow(instanceId, uiWindow);
    return true;
}

bool DialogContainer::CloseWindow(int32_t instanceId)
{
    LOGI("DialogContainer CloseWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Close();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DialogContainer CloseWindow Failed to close the window.");
        return false;
    }
    sptr<OHOS::Rosen::Window> uiWindow = nullptr;
    DialogContainer::SetUIWindow(instanceId, uiWindow);
    return true;
}

bool DialogContainer::OnBackPressed(int32_t instanceId)
{
    return DialogContainer::CloseWindow(instanceId);
}
} // namespace OHOS::Ace::Platform
