/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ace_container.h"

#include <functional>

#include "ability_info.h"
#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
#include "adapter/ohos/entrance/ace_rosen_sync_task.h"
#endif
#include "flutter/lib/ui/ui_dart_state.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "adapter/ohos/entrance/file_asset_provider.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/frame_report.h"
#include "base/log/log.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container_scope.h"
#include "core/common/flutter/flutter_asset_manager.h"
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/hdc_register.h"
#include "core/common/platform_window.h"
#include "core/common/text_field_manager.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"

namespace OHOS::Ace::Platform {
namespace {

constexpr char QUICK_JS_ENGINE_SHARED_LIB[] = "libace_engine_qjs.z.so";
constexpr char ARK_ENGINE_SHARED_LIB[] = "libace_engine_ark.z.so";
constexpr char DECLARATIVE_JS_ENGINE_SHARED_LIB[] = "libace_engine_declarative.z.so";
constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";

#ifdef _ARM64_
const std::string ASSET_LIBARCH_PATH = "/lib/arm64";
#else
const std::string ASSET_LIBARCH_PATH = "/lib/arm";
#endif

const char* GetEngineSharedLibrary(bool isArkApp)
{
    if (isArkApp) {
        return ARK_ENGINE_SHARED_LIB;
    } else {
        return QUICK_JS_ENGINE_SHARED_LIB;
    }
}

const char* GetDeclarativeSharedLibrary(bool isArkApp)
{
    if (isArkApp) {
        return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
    } else {
        return DECLARATIVE_JS_ENGINE_SHARED_LIB;
    }
}

} // namespace

AceContainer::AceContainer(int32_t instanceId, FrontendType type, bool isArkApp,
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), isArkApp_(isArkApp), aceAbility_(aceAbility),
      useCurrentEventRunner_(useCurrentEventRunner)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
    }
    InitializeTask();
    platformEventCallback_ = std::move(callback);
    useStageModel_ = false;
}

AceContainer::AceContainer(int32_t instanceId, FrontendType type, bool isArkApp,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool isSubAceContainer)
    : instanceId_(instanceId), type_(type), isArkApp_(isArkApp), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer)
{
    ACE_DCHECK(callback);
    if (!isSubContainer_) {
        InitializeTask();
    }
    platformEventCallback_ = std::move(callback);
    useStageModel_ = true;
}

void AceContainer::InitializeTask()
{
    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();
    flutterTaskExecutor->InitPlatformThread(useCurrentEventRunner_);
    taskExecutor_ = flutterTaskExecutor;
    // No need to create JS Thread for DECLARATIVE_JS
    if (type_ == FrontendType::DECLARATIVE_JS) {
        GetSettings().useUIAsJSThread = true;
    } else {
        flutterTaskExecutor->InitJsThread();
    }
}

void AceContainer::Initialize()
{
    ContainerScope scope(instanceId_);
    // For DECLARATIVE_JS frontend use UI as JS Thread, so InitializeFrontend after UI thread created.
    if (type_ != FrontendType::DECLARATIVE_JS) {
        InitializeFrontend();
    }
}

void AceContainer::Destroy()
{
    ContainerScope scope(instanceId_);
    if (pipelineContext_ && taskExecutor_) {
        // 1. Destroy Pipeline on UI thread.
        RefPtr<PipelineBase> context;
        context.Swap(pipelineContext_);
        if (GetSettings().usePlatformAsUIThread) {
            context->Destroy();
        } else {
            taskExecutor_->PostTask([context]() { context->Destroy(); }, TaskExecutor::TaskType::UI);
        }

        if (isSubContainer_) {
            // SubAcecontainer just return.
            return;
        }
        
        // 2. Destroy Frontend on JS thread.
        RefPtr<Frontend> frontend;
        frontend_.Swap(frontend);
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

void AceContainer::DestroyView()
{
    ContainerScope scope(instanceId_);
    if (aceView_ != nullptr) {
        auto flutterAceView = static_cast<FlutterAceView*>(aceView_);
        if (flutterAceView) {
            flutterAceView->DecRefCount();
        }
        aceView_ = nullptr;
    }
}

void AceContainer::InitializeFrontend()
{
    auto aceAbility = aceAbility_.lock();
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        auto& loader = Framework::JsEngineLoader::Get(GetEngineSharedLibrary(isArkApp_));
        auto jsEngine = loader.CreateJsEngine(instanceId_);
        jsEngine->AddExtraNativeObject("ability", aceAbility.get());
        EngineHelper::AddEngine(instanceId_, jsEngine);
        jsFrontend->SetJsEngine(jsEngine);
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
    } else if (type_ == FrontendType::JS_CARD) {
        AceApplicationInfo::GetInstance().SetCardType();
        frontend_ = AceType::MakeRefPtr<CardFrontend>();
    } else if (type_ == FrontendType::DECLARATIVE_JS) {
        if (!isSubContainer_) {
            frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
            auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary(isArkApp_));
            RefPtr<Framework::JsEngine> jsEngine;
            if (GetSettings().usingSharedRuntime) {
                jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
                LOGI("Create engine using runtime, engine %{public}p", RawPtr(jsEngine));
            } else {
                jsEngine = loader.CreateJsEngine(instanceId_);
            }
            jsEngine->AddExtraNativeObject("ability", aceAbility.get());
            EngineHelper::AddEngine(instanceId_, jsEngine);
            declarativeFrontend->SetJsEngine(jsEngine);
            declarativeFrontend->SetPageProfile(pageProfile_);
            declarativeFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
            declarativeFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
        } else {
            frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
            return;
        }
    } else {
        LOGE("Frontend type not supported");
        EventReport::SendAppStartException(AppStartExcepType::FRONTEND_TYPE_ERR);
        return;
    }
    ACE_DCHECK(frontend_);
    auto abilityInfo = abilityInfo_.lock();
    std::shared_ptr<AppExecFwk::AbilityInfo> info = aceAbility ? aceAbility->GetAbilityInfo() : abilityInfo;
    if (info && info->isLauncherAbility) {
        frontend_->DisallowPopLastPage();
    }
    frontend_->Initialize(type_, taskExecutor_);
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (container != nullptr) {
        auto aceContainer = AceType::DynamicCast<AceContainer>(container);
        return aceContainer;
    }
    return nullptr;
}

bool AceContainer::OnBackPressed(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }

    // When the container is for menu, it need close the menu first.
    if (container->IsSubContainer()) {
        SubwindowManager::GetInstance()->CloseMenu();
        return true;
    }
    ContainerScope scope(instanceId);
    auto context = DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        return false;
    }
    if (context->PopPageStackOverlay()) {
        return true;
    }
    return context->CallRouterBackToPopPage();
}

void AceContainer::OnShow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("container is null, OnShow failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();

    // When it is subContainer, no need call the OnShow, because the frontend is the same the parent container.
    if (front && !container->IsSubContainer()) {
        front->UpdateState(Frontend::State::ON_SHOW);
        front->OnShow();
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null, OnShow failed.");
        return;
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineBase = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineBase);
            pipelineBase->OnShow();
            auto pipelineContext = DynamicCast<PipelineContext>(pipelineBase);
            if (!pipelineContext) {
                LOGE("pipeline context is null, SetForegroundCalled failed.");
                return;
            }
            pipelineContext->SetForegroundCalled(true);
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnHide(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("container is null, OnHide failed.");
        return;
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();

    // When it is subContainer, no need call the OnHide, because the frontend is the same the parent container.
    if (front && !container->IsSubContainer()) {
        front->UpdateState(Frontend::State::ON_HIDE);
        front->OnHide();
        auto taskExecutor = container->GetTaskExecutor();
        if (taskExecutor) {
            taskExecutor->PostTask([front]() { front->TriggerGarbageCollection(); }, TaskExecutor::TaskType::JS);
        }
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null, OnHide failed.");
        return;
    }
    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnHide failed.");
                return;
            }
            pipelineContext->OnHide();
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnActive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("container is null, OnActive failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();

    // When it is subContainer, no need call the OnActive, because the frontend is the same the parent container.
    if (front && !container->IsSubContainer()) {
        front->OnActive();
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null, OnActive failed.");
        return;
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnActive failed.");
                return;
            }
            pipelineContext->WindowFocus(true);
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnInactive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("container is null, OnInactive failed.");
        return;
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();

    // When it is subContainer, no need call the OnInactive, because the frontend is the same the parent container.
    if (front && !container->IsSubContainer()) {
        front->OnInactive();
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null, OnInactive failed.");
        return;
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnInactive failed.");
                return;
            }
            pipelineContext->WindowFocus(false);
            pipelineContext->RootLostFocus();
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnNewWant(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("container is null, OnNewWant failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGE("front is null, OnNewWant failed.");
        return;
    }

    front->OnNewWant(data);
}

bool AceContainer::OnStartContinuation(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnStartContinuation failed.");
        return false;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnStartContinuation failed.");
        return false;
    }
    return front->OnStartContinuation();
}

std::string AceContainer::OnSaveData(int32_t instanceId)
{
    std::string result = "false";
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnSaveData failed.");
        return result;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnSaveData failed.");
        return result;
    }
    front->OnSaveData(result);
    return result;
}

bool AceContainer::OnRestoreData(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnRestoreData failed.");
        return false;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnRestoreData failed.");
        return false;
    }
    return front->OnRestoreData(data);
}

void AceContainer::OnCompleteContinuation(int32_t instanceId, int result)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnCompleteContinuation failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnCompleteContinuation failed.");
        return;
    }
    front->OnCompleteContinuation(result);
}

void AceContainer::OnRemoteTerminated(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnRemoteTerminated failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnRemoteTerminated failed.");
        return;
    }
    front->OnRemoteTerminated();
}

void AceContainer::OnConfigurationUpdated(int32_t instanceId, const std::string& configuration)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGI("container is null, OnConfigurationUpdated failed.");
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        LOGI("front is null, OnConfigurationUpdated failed.");
        return;
    }
    front->OnConfigurationUpdated(configuration);
}

void AceContainer::OnNewRequest(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        front->OnNewRequest(data);
    }
}

void AceContainer::OnDialogUpdated(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        front->OnDialogUpdated(data);
    }
}

void AceContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();

    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& touchEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const TouchEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnTouchEvent(event);
                if (markProcess) {
                    markProcess();
                }
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);

    auto&& mouseEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const MouseEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnMouseEvent(event);
                if (markProcess) {
                    markProcess();
                }
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);

    auto&& axisEventCallback = [context = pipelineContext_, id = instanceId_](
                                   const AxisEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnAxisEvent(event);
                if (markProcess) {
                    markProcess();
                }
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterAxisEventCallback(axisEventCallback);

    auto&& keyEventCallback = [context = pipelineContext_, id = instanceId_](const KeyEvent& event) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnKeyEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterKeyEventCallback(keyEventCallback);

    auto&& rotationEventCallback = [context = pipelineContext_, id = instanceId_](const RotationEvent& event) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnRotationEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterRotationEventCallback(rotationEventCallback);

    auto&& viewChangeCallback = [context = pipelineContext_, id = instanceId_](
                                    int32_t width, int32_t height, WindowSizeChangeReason type) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("ViewChangeCallback(%d, %d)", width, height);
        context->GetTaskExecutor()->PostTask(
            [context, width, height, type]() { context->OnSurfaceChanged(width, height, type); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterViewChangeCallback(viewChangeCallback);

    auto&& viewPositionChangeCallback = [context = pipelineContext_, id = instanceId_](
        int32_t posX, int32_t posY) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("ViewPositionChangeCallback(%d, %d)", posX, posY);
        context->GetTaskExecutor()->PostTask(
            [context, posX, posY]() { context->OnSurfacePositionChanged(posX, posY); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterViewPositionChangeCallback(viewPositionChangeCallback);

    auto&& densityChangeCallback = [context = pipelineContext_, id = instanceId_](double density) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("DensityChangeCallback(%lf)", density);
        context->GetTaskExecutor()->PostTask(
            [context, density]() { context->OnSurfaceDensityChanged(density); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterDensityChangeCallback(densityChangeCallback);

    auto&& systemBarHeightChangeCallback = [context = pipelineContext_, id = instanceId_](
                                               double statusBar, double navigationBar) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("SystemBarHeightChangeCallback(%lf, %lf)", statusBar, navigationBar);
        context->GetTaskExecutor()->PostTask(
            [context, statusBar, navigationBar]() { context->OnSystemBarHeightChanged(statusBar, navigationBar); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);

    auto&& surfaceDestroyCallback = [context = pipelineContext_, id = instanceId_]() {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);

    auto&& dragEventCallback = [context = pipelineContext_, id = instanceId_](
                                   int32_t x, int32_t y, const DragEventAction& action) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, x, y, action]() { context->OnDragEvent(x, y, action); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterDragEventCallback(dragEventCallback);

    InitWindowCallback();
}

void AceContainer::CreateContainer(int32_t instanceId, FrontendType type, bool isArkApp,
    const std::string& instanceName, std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility,
    std::unique_ptr<PlatformEventCallback> callback, bool useCurrentEventRunner, bool useNewPipeline)
{
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(
        instanceId, type, isArkApp, aceAbility, std::move(callback), useCurrentEventRunner, useNewPipeline);
    AceEngine::Get().AddContainer(instanceId, aceContainer);

    HdcRegister::Get().StartHdcRegister(instanceId);
    ConnectServerManager::Get().AddInstance(instanceId);
    aceContainer->Initialize();
    ContainerScope scope(instanceId);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }

    auto jsFront = AceType::DynamicCast<JsFrontend>(front);
    if (!jsFront) {
        return;
    }
    jsFront->SetInstanceName(instanceName);
}

void AceContainer::DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("no AceContainer with id %{private}d in AceEngine", instanceId);
        return;
    }
    HdcRegister::Get().StopHdcRegister(instanceId);
    container->Destroy();
    // unregister watchdog before stop thread to avoid UI_BLOCK report
    AceEngine::Get().UnRegisterFromWatchDog(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    if (taskExecutor) {
        taskExecutor->PostSyncTask([] { LOGI("Wait UI thread..."); }, TaskExecutor::TaskType::UI);
        taskExecutor->PostSyncTask([] { LOGI("Wait JS thread..."); }, TaskExecutor::TaskType::JS);
    }
    container->DestroyView(); // Stop all threads(ui,gpu,io) for current ability.
    if (taskExecutor) {
        taskExecutor->PostTask(
            [instanceId, destroyCallback] {
                LOGI("Remove on Platform thread...");
                EngineHelper::RemoveEngine(instanceId);
                AceEngine::Get().RemoveContainer(instanceId);
                ConnectServerManager::Get().RemoveInstance(instanceId);
                if (destroyCallback) {
                    destroyCallback();
                }
            },
            TaskExecutor::TaskType::PLATFORM);
    }
}

void AceContainer::SetView(AceView* view, double density, int32_t width, int32_t height,
    sptr<OHOS::Rosen::Window> rsWindow, UIEnvCallback callback)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    std::unique_ptr<Window> window =
        std::make_unique<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId(), callback);
}

void AceContainer::SetViewNew(
    AceView* view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window> rsWindow)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    std::unique_ptr<Window> window =
        std::make_unique<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId(), nullptr);
}

void AceContainer::SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window> uiWindow)
{
    if (uiWindow == nullptr) {
        return;
    }

    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    container->SetUIWindowInner(uiWindow);
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindow(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return nullptr;
    }
    return container->GetUIWindowInner();
}

OHOS::AppExecFwk::Ability* AceContainer::GetAbility(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return nullptr;
    }
    return container->GetAbilityInner().lock().get();
}

bool AceContainer::RunPage(int32_t instanceId, int32_t pageId, const std::string& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        LOGD("RunPage content=[%{private}s]", content.c_str());
        front->RunPage(pageId, content, params);
        return true;
    }
    return false;
}

bool AceContainer::PushPage(int32_t instanceId, const std::string& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        front->PushPage(content, params);
        return true;
    }
    return false;
}

bool AceContainer::UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }
    return context->CallRouterBackToPopPage();
}

void AceContainer::SetHapPath(const std::string& hapPath)
{
    resourceInfo_.SetHapPath(hapPath);
    if (!hapPath.empty()) {
        SystemProperties::SetUnZipHap(false);
    }
}

void AceContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{
    return;
}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    auto front = GetFrontend();
    if (!front) {
        LOGE("the front is nullptr");
        return;
    }

    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [front, callbackId, errorCode, errorMessage = std::move(errorMessage)]() mutable {
            front->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
        },
        TaskExecutor::TaskType::BACKGROUND);
}

bool AceContainer::Dump(const std::vector<std::string>& params)
{
    ContainerScope scope(instanceId_);
    if (aceView_ && aceView_->Dump(params)) {
        return true;
    }

    if (pipelineContext_) {
        pipelineContext_->Dump(params);
        return true;
    }
    return false;
}

void AceContainer::TriggerGarbageCollection()
{
    ContainerScope scope(instanceId_);
#if !defined(OHOS_PLATFORM) || !defined(ENABLE_NATIVE_VIEW)
    // GPU and IO thread is standalone while disable native view
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::GPU);
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::IO);
#endif
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::UI);
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            if (sp) {
                sp->TriggerGarbageCollection();
            }
            PurgeMallocCache();
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::DumpHeapSnapshot(bool isPrivate)
{
    taskExecutor_->PostTask(
        [isPrivate, frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            if (sp) {
                sp->DumpHeapSnapshot(isPrivate);
            }
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::SetLocalStorage(NativeReference* storage, NativeReference* context)
{
    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_), storage, context, id = instanceId_] {
            auto sp = frontend.Upgrade();
            if (sp) {
                auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(sp);
                auto jsEngine = declarativeFrontend->GetJsEngine();
                if (context) {
                    jsEngine->SetContext(id, context);
                }
                if (storage) {
                    jsEngine->SetLocalStorage(id, storage);
                }
            }
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::AddAssetPath(
    int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }

    RefPtr<FlutterAssetManager> flutterAssetManager;
    if (container->assetManager_) {
        flutterAssetManager = AceType::DynamicCast<FlutterAssetManager>(container->assetManager_);
    } else {
        flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
        container->assetManager_ = flutterAssetManager;
        if (container->type_ != FrontendType::DECLARATIVE_JS) {
            container->frontend_->SetAssetManager(flutterAssetManager);
        }
    }
    if (flutterAssetManager && !packagePath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
        if (assetProvider->Initialize(packagePath, paths)) {
            LOGI("Push AssetProvider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }
}

void AceContainer::AddLibPath(int32_t instanceId, const std::string& libPath)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }

    RefPtr<FlutterAssetManager> flutterAssetManager;
    if (container->assetManager_) {
        flutterAssetManager = AceType::DynamicCast<FlutterAssetManager>(container->assetManager_);
    } else {
        flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
        container->assetManager_ = flutterAssetManager;
        if (container->type_ != FrontendType::DECLARATIVE_JS) {
            container->frontend_->SetAssetManager(flutterAssetManager);
        }
    }
    if (flutterAssetManager) {
        flutterAssetManager->SetLibPath(libPath);
    }
}

void AceContainer::AttachView(std::unique_ptr<Window> window, AceView* view, double density, int32_t width,
    int32_t height, int32_t windowId, UIEnvCallback callback)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    auto flutterTaskExecutor = AceType::DynamicCast<FlutterTaskExecutor>(taskExecutor_);
    if (!isSubContainer_) {
        auto state = flutter::UIDartState::Current()->GetStateById(instanceId);
        ACE_DCHECK(state != nullptr);
        flutterTaskExecutor->InitOtherThreads(state->GetTaskRunners());
        if (GetSettings().usePlatformAsUIThread) {
            ContainerScope::SetScopeNotify([](int32_t id) { flutter::UIDartState::Current()->SetCurInstance(id); });
        }
    }
    ContainerScope scope(instanceId);
    if (type_ == FrontendType::DECLARATIVE_JS) {
        // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
        flutterTaskExecutor->InitJsThread(false);
        InitializeFrontend();
        auto front = GetFrontend();
        if (front) {
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
            front->SetAssetManager(assetManager_);
        }
    } else if (type_ != FrontendType::JS_CARD) {
        aceView_->SetCreateTime(createTime_);
    }
    resRegister_ = aceView_->GetPlatformResRegister();
    if (useNewPipeline_) {
        LOGI("New pipeline version creating...");
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    } else {
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    }
    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowId(windowId);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(pipelineContext_);
    if (pipelineContext) {
        pipelineContext->SetWindowModal(windowModal_);
        pipelineContext->SetDrawDelegate(aceView_->GetDrawDelegate());
        if (isSubContainer_) {
            pipelineContext->SetIsSubPipeline(true);
        }
    }

    InitializeCallback();

    auto&& finishEventHandler = [weak = WeakClaim(this), instanceId] {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("FinishEventHandler container is null!");
            return;
        }
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        if (!context) {
            LOGE("FinishEventHandler context is null!");
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container)] {
                auto container = weak.Upgrade();
                if (!container) {
                    LOGE("Finish task, container is null!");
                    return;
                }
                container->OnFinish();
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetFinishEventHandler(finishEventHandler);

    auto&& startAbilityHandler = [weak = WeakClaim(this), instanceId](const std::string& address) {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("StartAbilityHandler container is null!");
            return;
        }
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        if (!context) {
            LOGE("StartAbilityHandler context is null!");
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), address]() {
                auto container = weak.Upgrade();
                if (!container) {
                    LOGE("Start ability task, container is null!");
                    return;
                }
                container->OnStartAbility(address);
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetStartAbilityHandler(startAbilityHandler);

    auto&& setStatusBarEventHandler = [weak = WeakClaim(this), instanceId](const Color& color) {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("StatusBarEventHandler container is null!");
            return;
        }
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        if (!context) {
            LOGE("StatusBarEventHandler context is null!");
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [weak, color = color.GetValue()]() {
                auto container = weak.Upgrade();
                if (!container) {
                    LOGE("StatusBarEventHandler container is null!");
                    return;
                }
                if (container->platformEventCallback_) {
                    container->platformEventCallback_->OnStatusBarBgColorChanged(color);
                }
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetStatusBarEventHandler(setStatusBarEventHandler);

    taskExecutor_->PostTask([] { FrameReport::GetInstance().Init(); }, TaskExecutor::TaskType::UI);

    ThemeConstants::InitDeviceType();
    // Load custom style at UI thread before frontend attach, to make sure style can be loaded before building dom tree.
    auto themeManager = AceType::MakeRefPtr<ThemeManager>();
    if (themeManager) {
        pipelineContext_->SetThemeManager(themeManager);
        // Init resource
        themeManager->InitResource(resourceInfo_);
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_] {
                ACE_SCOPED_TRACE("OHOS::LoadThemes()");
                LOGD("UIContent load theme");
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                themeManager->LoadResourceThemes();
            },
            TaskExecutor::TaskType::UI);
    }
    taskExecutor_->PostTask(
        [context = pipelineContext_, callback, isSubContainer = isSubContainer_]() {
            if (callback != nullptr) {
                callback(AceType::DynamicCast<PipelineContext>(context));
            }
            if (!isSubContainer) {
                context->SetupRootElement();
            }
        },
        TaskExecutor::TaskType::UI);
    aceView_->Launch();

    // Only MainWindow instance will be registered to watch dog.
    if (!isSubContainer_) {
        AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_, GetSettings().useUIAsJSThread);
        frontend_->AttachPipelineContext(pipelineContext_);
    } else {
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
        if (declarativeFrontend) {
            declarativeFrontend->AttachSubPipelineContext(AceType::DynamicCast<PipelineContext>(pipelineContext_));
        }
        return;
    }

    auto dataAbilityHelperImpl = [ability = GetAbilityInner(), runtimeContext = runtimeContext_,
                                     useStageModel = useStageModel_]() {
        return AceType::MakeRefPtr<DataAbilityHelperStandard>(ability.lock(), runtimeContext.lock(), useStageModel);
    };
    auto dataProviderManager = MakeRefPtr<DataProviderManagerStandard>(dataAbilityHelperImpl);
    pipelineContext_->SetDataProviderManager(dataProviderManager);

#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
    auto context = AceType::DynamicCast<PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(context);
    context->SetPostRTTaskCallBack([](std::function<void()>&& task) {
        auto syncTask = std::make_shared<AceRosenSyncTask>(std::move(task));
        Rosen::RSTransactionProxy::GetInstance()->ExecuteSynchronousTask(syncTask);
    });
#endif
}

void AceContainer::SetUIWindowInner(sptr<OHOS::Rosen::Window> uiWindow)
{
    uiWindow_ = uiWindow;
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindowInner() const
{
    return uiWindow_;
}

std::weak_ptr<OHOS::AppExecFwk::Ability> AceContainer::GetAbilityInner() const
{
    return aceAbility_;
}

void AceContainer::SetFontScale(int32_t instanceId, float fontScale)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("fail to set font style due to context is null");
        return;
    }
    pipelineContext->SetFontScale(fontScale);
}

void AceContainer::SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    ContainerScope scope(instanceId);
    container->SetWindowModal(windowModal);
    container->SetColorScheme(colorScheme);
}

void AceContainer::SetDialogCallback(int32_t instanceId, FrontendDialogCallback callback)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }
    auto front = container->GetFrontend();
    if (front && front->GetType() == FrontendType::JS) {
        front->SetDialogCallback(callback);
    }
}

std::string AceContainer::RestoreRouterStack(int32_t instanceId, const std::string& contentInfo)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return "";
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        return front->RestoreRouterStack(contentInfo);
    } else {
        return "";
    }
}

std::string AceContainer::GetContentInfo(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return "";
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        return front->GetContentInfo();
    } else {
        return "";
    }
}

void AceContainer::SetWindowPos(int32_t left, int32_t top)
{
    if (!frontend_ || IsSubContainer()) {
        return;
    }
    auto accessibilityManager = frontend_->GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->SetWindowPos(left, top);
}

void AceContainer::InitializeSubContainer(int32_t parentContainerId)
{
    auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
    if (!parentContainer) {
        LOGE("Parent container is null, InitializeSubContainer failed.");
        return;
    }

    auto taskExec = parentContainer->GetTaskExecutor();
    taskExecutor_ = AceType::DynamicCast<FlutterTaskExecutor>(std::move(taskExec));
    auto parentSettings = parentContainer->GetSettings();
    GetSettings().useUIAsJSThread = parentSettings.useUIAsJSThread;
    GetSettings().usePlatformAsUIThread = parentSettings.usePlatformAsUIThread;
    GetSettings().usingSharedRuntime = parentSettings.usingSharedRuntime;
}

void AceContainer::InitWindowCallback()
{
    LOGD("AceContainer InitWindowCallback");
    auto aceAbility = aceAbility_.lock();
    if (aceAbility == nullptr) {
        LOGD("AceContainer::InitWindowCallback failed, aceAbility is null.");
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(pipelineContext_);
    if (pipelineContext == nullptr) {
        LOGE("AceContainer::InitWindowCallback failed, pipelineContext_ is null.");
        return;
    }
    auto& window = aceAbility->GetWindow();
    if (window == nullptr) {
        LOGE("AceContainer::InitWindowCallback failed, window is null.");
        return;
    }
    std::shared_ptr<AppExecFwk::AbilityInfo> info = aceAbility->GetAbilityInfo();
    if (info != nullptr) {
        pipelineContext->SetAppLabelId(info->labelId);
        pipelineContext->SetAppIconId(info->iconId);
    }
    pipelineContext->SetWindowMinimizeCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Minimize()); });
    pipelineContext->SetWindowMaximizeCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Maximize()); });

    pipelineContext->SetWindowRecoverCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Recover()); });

    pipelineContext->SetWindowCloseCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Close()); });

    pipelineContext->SetWindowStartMoveCallBack([window]() { window->StartMove(); });

    pipelineContext->SetWindowSplitCallBack([window]() -> bool {
        return (
            OHOS::Rosen::WMError::WM_OK == window->SetWindowMode(OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY));
    });

    pipelineContext->SetWindowGetModeCallBack([window]() -> WindowMode { return (WindowMode)window->GetMode(); });
}

std::shared_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(const std::string& bundle,
    const std::string& module)
{
    auto context = runtimeContext_.lock();
    if (!context) {
        LOGE("runtimeContext is null.");
        return nullptr;
    }
    return context->CreateModuleContext(bundle, module);
}

void AceContainer::UpdateConfiguration(
    const std::string& colorMode, const std::string& deviceAccess, const std::string& languageTag)
{
    if (colorMode.empty() && deviceAccess.empty() && languageTag.empty()) {
        LOGW("AceContainer::OnConfigurationUpdated param is empty");
        return;
    }
    if (pipelineContext_ == nullptr) {
        LOGE("AceContainer::UpdateConfiguration pipeline is null");
        return;
    }
    auto themeManager = pipelineContext_->GetThemeManager();
    if (themeManager == nullptr) {
        LOGE("AceContainer::UpdateConfiguration themeManager is null");
        return;
    }
    auto resConfig = GetResourceConfiguration();
    if (!colorMode.empty()) {
        if (colorMode == "dark") {
            SystemProperties::SetColorMode(ColorMode::DARK);
            SetColorScheme(ColorScheme::SCHEME_DARK);
            resConfig.SetColorMode(ColorMode::DARK);
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
            SetColorScheme(ColorScheme::SCHEME_LIGHT);
            resConfig.SetColorMode(ColorMode::LIGHT);
        }
    }
    if (!deviceAccess.empty()) {
        // Event of accessing mouse or keyboard
        SystemProperties::SetDeviceAccess(deviceAccess == "true");
        resConfig.SetDeviceAccess(deviceAccess == "true");
    }
    if (!languageTag.empty()) {
        std::string language;
        std::string script;
        std::string region;
        Localization::ParseLocaleTag(languageTag, language, script, region, false);
        if (!language.empty() || !script.empty() || !region.empty()) {
            AceApplicationInfo::GetInstance().SetLocale(language, region, script, "");
        }
    }
    SetResourceConfiguration(resConfig);
    themeManager->UpdateConfig(resConfig);
    themeManager->LoadResourceThemes();
    UpdateFrondend(!deviceAccess.empty());
}

void AceContainer::UpdateFrondend(bool needReloadTransition)
{
    auto taskExecutor = GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("AceContainer::UpdateConfiguration taskExecutor is null.");
        return;
    }
    taskExecutor->PostTask([instanceId = instanceId_, weak = WeakClaim(this), needReloadTransition]() {
        ContainerScope scope(instanceId);
        auto container = weak.Upgrade();
        if (!container) {
            return;
        }
        auto frontend = container->GetFrontend();
        if (frontend) {
            LOGI("AceContainer::UpdateConfiguration frontend MarkNeedUpdate");
            frontend->FlushReload();
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        taskExecutor->PostTask([instanceId, weak, needReloadTransition]() {
            ContainerScope scope(instanceId);
            auto container = weak.Upgrade();
            if (!container) {
                return;
            }
            auto pipeline = container->GetPipelineContext();
            if (!pipeline) {
                return;
            }
            pipeline->FlushReload();
            if (needReloadTransition) {
                // reload transition animation
                pipeline->FlushReloadTransition();
            }
            }, TaskExecutor::TaskType::UI);
        }, TaskExecutor::TaskType::JS);
}
} // namespace OHOS::Ace::Platform
