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
DialogContainer::DialogContainer(int32_t instanceId, FrontendType type) : instanceId_(instanceId), type_(type)
{
    auto taskExecutorImpl = Referenced::MakeRefPtr<TaskExecutorImpl>();
    taskExecutorImpl->InitPlatformThread(true);
    taskExecutor_ = taskExecutorImpl;
    GetSettings().useUIAsJSThread = true;
    GetSettings().usePlatformAsUIThread = true;
    GetSettings().usingSharedRuntime = true;
}

void DialogContainer::InitializeTouchEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& touchEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const TouchEvent& event, const std::function<void()>& markProcess,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnTouchEvent(event);
                context->NotifyDispatchTouchEventDismiss(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI, "ArkUIDialogTouchEvent");
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);
}

void DialogContainer::InitializeMouseEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& mouseEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const MouseEvent& event, const std::function<void()>& markProcess,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnMouseEvent(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI, "ArkUIDialogMouseEvent");
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);
}

void DialogContainer::InitializeAxisEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& axisEventCallback = [context = pipelineContext_, id = instanceId_](
                                   const AxisEvent& event, const std::function<void()>& markProcess,
                                   const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnAxisEvent(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI, "ArkUIDialogAxisEvent");
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
            [context, event, &result]() { result = context->OnKeyEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIDialogKeyEvent");
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
            [context, event, &result]() { result = context->OnRotationEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIDialogRotationEvent");
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
            TaskExecutor::TaskType::UI, "ArkUIDialogSurfaceChanged");
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
            [context, density]() { context->OnSurfaceDensityChanged(density); },
            TaskExecutor::TaskType::UI, "ArkUIDialogSurfaceDensityChanged");
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
            TaskExecutor::TaskType::UI, "ArkUIDialogSystemBarHeightChanged");
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);
}

void DialogContainer::InitializeSurfaceDestroyCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& surfaceDestroyCallback = [context = pipelineContext_, id = instanceId_]() {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); },
            TaskExecutor::TaskType::UI, "ArkUIDialogSurfaceDestroyed");
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);
}

void DialogContainer::InitializeDragEventCallback()
{
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& dragEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const PointerEvent& pointerEvent, const DragEventAction& action,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, pointerEvent, action, node]() { context->OnDragEvent(pointerEvent, action, node); },
            TaskExecutor::TaskType::UI, "ArkUIDialogDragEvent");
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
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer DestroyContainer begin %{public}d", instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    container->Destroy();
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [] { TAG_LOGI(AceLogTag::ACE_DIALOG,  "Wait UI thread..."); },
        TaskExecutor::TaskType::UI, "ArkUIDialogWaitLog");
    taskExecutor->PostSyncTask(
        [] { TAG_LOGI(AceLogTag::ACE_DIALOG,  "Wait JS thread..."); },
        TaskExecutor::TaskType::JS, "ArkUIDialogWaitLog");
    container->DestroyView(); // Stop all threads(ui,gpu,io) for current ability.
    taskExecutor->PostTask(
        [instanceId, destroyCallback] {
            TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer DestroyContainer Remove on Platform thread...");
            EngineHelper::RemoveEngine(instanceId);
            AceEngine::Get().RemoveContainer(instanceId);
            CHECK_NULL_VOID(destroyCallback);
            destroyCallback();
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIDialogContainerDestroy");
}

void DialogContainer::Destroy()
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer Destroy begin");
    ContainerScope scope(instanceId_);
    if (pipelineContext_ && taskExecutor_) {
        // 1. Destroy Pipeline on UI thread.
        RefPtr<PipelineBase>& context = pipelineContext_;
        if (GetSettings().usePlatformAsUIThread) {
            context->Destroy();
        } else {
            taskExecutor_->PostTask([context]() { context->Destroy(); },
                TaskExecutor::TaskType::UI, "ArkUIDialogDestoryPipeline");
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
                TaskExecutor::TaskType::JS, "ArkUIDialogFrontendDestroy");
        }
    }
    DestroyToastSubwindow(instanceId_);
    resRegister_.Reset();
    assetManager_.Reset();
}

void DialogContainer::DestroyView()
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer DestroyView begin");
    ContainerScope scope(instanceId_);
    std::lock_guard<std::mutex> lock(viewMutex_);
    aceView_ = nullptr;
}

void DialogContainer::SetView(
    const RefPtr<AceView>& view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window>& rsWindow)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
#ifdef ENABLE_ROSEN_BACKEND
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
#else
    auto platformWindow = PlatformWindow::Create(view);
    CHECK_NULL_VOID(platformWindow);
    auto window = std::make_shared<Window>(std::move(platformWindow));
#endif
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId());
}

void DialogContainer::SetViewNew(
    const RefPtr<AceView>& view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window>& rsWindow)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId());
#endif
}

void DialogContainer::AttachView(std::shared_ptr<Window> window, const RefPtr<AceView>& view, double density,
    int32_t width, int32_t height, uint32_t windowId)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    auto taskExecutorImpl = AceType::DynamicCast<TaskExecutorImpl>(taskExecutor_);
    auto aceView = AceType::DynamicCast<AceViewOhos>(aceView_);
    ACE_DCHECK(aceView != nullptr);
    taskExecutorImpl->InitOtherThreads(aceView->GetThreadModelImpl());
    ContainerScope scope(instanceId);
    // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
    taskExecutorImpl->InitJsThread(false);
    InitializeFrontend();
    SetUseNewPipeline();

    InitPipelineContext(std::move(window), instanceId, density, width, height, windowId);
    InitializeCallback();
    CheckAndSetFontFamily();

    taskExecutor_->PostTask([] { FrameReport::GetInstance().Init(); },
        TaskExecutor::TaskType::UI, "ArkUIDialogFrameReportInit");
    ThemeConstants::InitDeviceType();
    // Load custom style at UI thread before frontend attach, to make sure style can be loaded before building dom tree.
    RefPtr<ThemeManagerImpl> themeManager = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        auto resAdapter = ResourceAdapter::CreateV2();
        themeManager = AceType::MakeRefPtr<ThemeManagerImpl>(resAdapter);
    } else {
        themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
    }
    if (themeManager) {
        pipelineContext_->SetThemeManager(themeManager);
        // Init resource
        themeManager->InitResource(resourceInfo_);
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_] {
                ACE_SCOPED_TRACE("OHOS::LoadThemes()");
                TAG_LOGI(AceLogTag::ACE_DIALOG, "UIContent load theme");
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                themeManager->LoadResourceThemes();
            },
            TaskExecutor::TaskType::UI, "ArkUIDialogLoadTheme");
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

void DialogContainer::InitPipelineContext(std::shared_ptr<Window> window, int32_t instanceId, double density,
    int32_t width, int32_t height, uint32_t windowId)
{
#ifdef NG_BUILD
    TAG_LOGI(AceLogTag::ACE_DIALOG, "New pipeline version creating...");
    pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
        std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
#else
    if (useNewPipeline_) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "New pipeline version creating...");
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
        TaskExecutor::TaskType::JS, "ArkUIDialogDumpHeapSnapshot");
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

void DialogContainer::ShowToast(int32_t instanceId, const std::string& message, int32_t duration,
    const std::string& bottom, std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->SetToastStopListenerCallback([instanceId = instanceId]() {
        if (ContainerScope::CurrentId() >= 0) {
            DialogContainer::HideWindow(instanceId);
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
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);

    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);

    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->SetToastStopListenerCallback([instanceId = instanceId]() {
        if (ContainerScope::CurrentId() >= 0) {
            DialogContainer::HideWindow(instanceId);
        }
    });

    delegate->CloseToast(toastId, std::move(callback));
}

void DialogContainer::ShowDialog(int32_t instanceId, const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
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
                DialogContainer::HideWindow(instanceId);
            }
        });
}

void DialogContainer::ShowDialog(int32_t instanceId, const PromptDialogAttr& dialogAttr,
    const std::vector<ButtonInfo>& buttons, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog with attr begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    CHECK_NULL_VOID(frontend);
    auto delegate = frontend->GetDelegate();
    CHECK_NULL_VOID(delegate);
    delegate->ShowDialog(dialogAttr, buttons, std::move(callback), callbacks, [instanceId = instanceId](bool isShow) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowDialog HideWindow instanceId = %{public}d", instanceId);
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
    delegate->ShowActionMenu(title, button, std::move(callback), [instanceId = instanceId](bool isShow) {
        if (!isShow) {
            DialogContainer::HideWindow(instanceId);
        }
    });
}

bool DialogContainer::ShowToastDialogWindow(
    int32_t instanceId, int32_t posX, int32_t posY, int32_t width, int32_t height, bool isToast)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer ShowToastDialogWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
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

bool DialogContainer::HideWindow(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer HideWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Hide();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "DialogContainer HideWindow Failed to hide the window.");
        return false;
    }
    sptr<OHOS::Rosen::Window> uiWindow = nullptr;
    DialogContainer::SetUIWindow(instanceId, uiWindow);
    return true;
}

bool DialogContainer::CloseWindow(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "DialogContainer CloseWindow begin");
    auto container = AceType::DynamicCast<DialogContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Close();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "DialogContainer CloseWindow Failed to close the window.");
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

void DialogContainer::SetFontScaleAndWeightScale(int32_t instanceId)
{
    float fontScale = SystemProperties::GetFontScale();
    float fontWeightScale = SystemProperties::GetFontWeightScale();
    Container::SetFontScale(instanceId, fontScale);
    Container::SetFontWeightScale(instanceId, fontWeightScale);
}

void DialogContainer::UpdateConfiguration(const ParsedConfig& parsedConfig)
{
    if (!parsedConfig.IsValid()) {
        LOGW("DialogContainer::OnConfigurationUpdated param is empty");
        return;
    }

    CHECK_NULL_VOID(pipelineContext_);
    auto themeManager = pipelineContext_->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto resConfig = GetResourceConfiguration();
    if (!parsedConfig.colorMode.empty()) {
        if (parsedConfig.colorMode == "dark") {
            SystemProperties::SetColorMode(ColorMode::DARK);
            resConfig.SetColorMode(ColorMode::DARK);
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
            resConfig.SetColorMode(ColorMode::LIGHT);
        }
    }

    SetResourceConfiguration(resConfig);
    themeManager->UpdateConfig(resConfig);
    themeManager->LoadResourceThemes();
    // change color mode and theme to clear image cache
    pipelineContext_->ClearImageCache();
}

void DialogContainer::CheckAndSetFontFamily()
{
    CHECK_NULL_VOID(pipelineContext_);
    auto fontManager = pipelineContext_->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (fontManager->IsUseAppCustomFont()) {
        return;
    }
    std::string familyName = "";
    std::string path = "/data/themes/a/app";
    if (!IsFontFileExistInPath(path)) {
        path = "/data/themes/b/app";
        if (!IsFontFileExistInPath(path)) {
            return;
        }
    }
    path = path.append("/fonts/");
    familyName = GetFontFamilyName(path);
    if (familyName.empty()) {
        return;
    }
    path = path.append(familyName);
    fontManager->SetFontFamily(familyName.c_str(), path.c_str());
}
} // namespace OHOS::Ace::Platform
