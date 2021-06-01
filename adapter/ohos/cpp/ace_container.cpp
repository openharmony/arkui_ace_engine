/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "adapter/common/cpp/file_asset_provider.h"
#include "adapter/ohos/cpp/ace_application_info.h"
#include "adapter/ohos/cpp/ace_container.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/watch_dog/watch_dog.h"
#include "core/common/ace_engine.h"
#include "core/common/platform_window.h"
#include "core/common/text_field_manager.h"
#include "core/common/window.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/pipeline_context.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"

#include "flutter/lib/ui/ui_dart_state.h"

#include "adapter/common/cpp/flutter_asset_manager.h"
#include "adapter/common/cpp/flutter_task_executor.h"

namespace OHOS::Ace::Platform {

AceContainer::AceContainer(int32_t instanceId, FrontendType type, AceAbility* aceAbility,
    std::unique_ptr<PlatformEventCallback> callback) : instanceId_(instanceId), type_(type), aceAbility_(aceAbility)
{
    ACE_DCHECK(callback);
    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();
    flutterTaskExecutor->InitPlatformThread();
    flutterTaskExecutor->InitJsThread();
    taskExecutor_ = flutterTaskExecutor;
    if (type_ != FrontendType::DECLARATIVE_JS) {
        InitializeFrontend();
    }

    platformEventCallback_ = std::move(callback);
}

void AceContainer::InitializeFrontend()
{
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        jsFrontend->SetJsEngine(Framework::JsEngineLoader::Get().CreateJsEngine(instanceId_));
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
        jsFrontend->SetAbility(aceAbility_);
    } else if (type_ == FrontendType::DECLARATIVE_JS) {
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
        declarativeFrontend->SetJsEngine(Framework::JsEngineLoader::GetDeclarative().CreateJsEngine(instanceId_));
    } else {
        LOGE("Frontend type not supported");
        EventReport::SendAppStartException(AppStartExcepType::FRONTEND_TYPE_ERR);
        return;
    }
    ACE_DCHECK(frontend_);
    frontend_->Initialize(type_, taskExecutor_);
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (container != nullptr) {
        auto aceContainer = AceType::DynamicCast<AceContainer>(container);
        return aceContainer;
    } else {
        return nullptr;
    }
}

bool AceContainer::OnBackPressed(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }

    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }
    return context->CallRouterBackToPopPage();
}

void AceContainer::OnShow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    auto front = container->GetFrontend();
    if (front) {
        front->OnShow();
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        return;
    }
#ifndef WEARABLE_PRODUCT
    context->OnShow();
#endif
}

void AceContainer::OnHide(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }
    auto front = container->GetFrontend();
    if (front) {
        front->OnHide();
        auto taskExecutor = container->GetTaskExecutor();
        if (taskExecutor) {
            taskExecutor->PostTask([front]() { front->TriggerGarbageCollection(); }, TaskExecutor::TaskType::JS);
        }
    }

    auto context = container->GetPipelineContext();
    if (!context) {
        return;
    }
#ifndef WEARABLE_PRODUCT
    context->OnHide();
#endif
}

void AceContainer::OnActive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    auto front = container->GetFrontend();
    if (front) {
        front->OnActive();
    }
}

void AceContainer::OnInactive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    auto front = container->GetFrontend();
    if (front) {
        front->OnInactive();
    }
}

std::string AceContainer::OnSaveData(int32_t instanceId)
{
    std::string result = "false";
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (container) {
        auto front = container->GetFrontend();
        if (front) {
            front->OnSaveData(result);
        }
    }

    return result;
}

bool AceContainer::OnRestoreData(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }

    auto front = container->GetFrontend();
    if (front) {
        if (!data.empty()) {
            auto result = front->OnRestoreData(data);
            return result;
        }
    }

    return false;
}

void AceContainer::OnNewRequest(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }

    auto front = container->GetFrontend();
    if (front) {
        front->OnNewRequest(data);
    }
}

void AceContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();

    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& touchEventCallback = [context = pipelineContext_](const TouchPoint& event) {
        context->GetTaskExecutor()->PostTask(
            [context, event]() { context->OnTouchEvent(event); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);

    auto&& keyEventCallback = [context = pipelineContext_](const KeyEvent& event) {
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnKeyEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterKeyEventCallback(keyEventCallback);

    auto&& mouseEventCallback = [context = pipelineContext_](const MouseEvent& event) {
        context->GetTaskExecutor()->PostTask(
            [context, event]() { context->OnMouseEvent(event); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);

    auto&& rotationEventCallback = [context = pipelineContext_](const RotationEvent& event) {
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnRotationEvent(event); }, TaskExecutor::TaskType::UI);
        return result;
    };
    aceView_->RegisterRotationEventCallback(rotationEventCallback);

    auto&& viewChangeCallback = [context = pipelineContext_](int32_t width, int32_t height) {
        ACE_SCOPED_TRACE("ViewChangeCallback(%d, %d)", width, height);
        context->GetTaskExecutor()->PostTask(
            [context, width, height]() { context->OnSurfaceChanged(width, height); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterViewChangeCallback(viewChangeCallback);

    auto&& densityChangeCallback = [context = pipelineContext_](double density) {
        ACE_SCOPED_TRACE("DensityChangeCallback(%lf)", density);
        context->GetTaskExecutor()->PostTask(
            [context, density]() { context->OnSurfaceDensityChanged(density); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterDensityChangeCallback(densityChangeCallback);

    auto&& systemBarHeightChangeCallback = [context = pipelineContext_](double statusBar, double navigationBar) {
        ACE_SCOPED_TRACE("SystemBarHeightChangeCallback(%lf, %lf)", statusBar, navigationBar);
        context->GetTaskExecutor()->PostTask(
            [context, statusBar, navigationBar]() { context->OnSystemBarHeightChanged(statusBar, navigationBar); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);

    auto&& surfaceDestroyCallback = [context = pipelineContext_]() {
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);

    auto&& idleCallback = [context = pipelineContext_](int64_t deadline) {
        context->GetTaskExecutor()->PostTask(
            [context, deadline]() { context->OnIdle(deadline); }, TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterIdleCallback(idleCallback);

    auto&& viewDestoryCallback = [context = pipelineContext_](AceView::ViewReleaseCallback&& callback) {
        context->GetTaskExecutor()->PostTask(
            [context, callback = std::move(callback)]() {
                context->GetTaskExecutor()->PostTask(
                    [callback = std::move(callback)]() { callback(); }, TaskExecutor::TaskType::PLATFORM);
            },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterViewDestroyCallback(viewDestoryCallback);
}

void AceContainer::CreateContainer(int32_t instanceId, FrontendType type, AceAbility* aceAbility,
    std::unique_ptr<PlatformEventCallback> callback)
{
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(instanceId, type, aceAbility, std::move(callback));
    AceEngine::Get().AddContainer(instanceId, aceContainer);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }
}

void AceContainer::DestroyContainer(int32_t instanceId)
{
    LOGI("DestroyContainer with id %{private}d", instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("no AceContainer with id %{private}d", instanceId);
        return;
    }
    auto context = container->GetPipelineContext();
    if (context) {
        auto taskExecutor = context->GetTaskExecutor();
        if (taskExecutor) {
            taskExecutor->PostTask([context]() { context->Destroy(); }, TaskExecutor::TaskType::UI);
        }
    }
    AceEngine::Get().RemoveContainer(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_DESTROY);
    }
}

void AceContainer::SetView(AceView* view, double density, int32_t width, int32_t height)
{
    if (view == nullptr) {
        return;
    }

    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    if (!container) {
        return;
    }
    auto platformWindow = PlatformWindow::Create(view);
    if (!platformWindow) {
        LOGE("Create PlatformWindow failed!");
        return;
    }
    std::unique_ptr<Window> window = std::make_unique<Window>(std::move(platformWindow));
    container->AttachView(std::move(window), view, density, width, height);
}

bool AceContainer::RunPage(int32_t instanceId, int32_t pageId, const std::string& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    auto front = container->GetFrontend();
    if (front) {
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
    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }
    return context->CallRouterBackToPopPage();
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

    taskExecutor_->PostTask(
        [front, callbackId, errorCode, errorMessage = std::move(errorMessage)]() mutable {
            front->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
        },
        TaskExecutor::TaskType::BACKGROUND);
}

bool AceContainer::Dump(const std::vector<std::string>& params)
{
    if (aceView_ && aceView_->Dump(params)) {
        return true;
    }

    if (pipelineContext_) {
        pipelineContext_->Dump(params);
        return true;
    }
    return false;
}

void AceContainer::AddAssetPath(
    int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }

    AceEngine::Get().SetPackagePath(packagePath);
    for (auto path: paths) {
        AceEngine::Get().SetAssetBasePath(path);
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
        auto assetProvider = std::make_unique<FileAssetProvider>();
        if (assetProvider->Initialize(packagePath, paths)) {
            LOGI("Push AssetProvider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }
}

void AceContainer::AttachView(
    std::unique_ptr<Window> window, AceView* view, double density, int32_t width, int32_t height)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    auto state = flutter::UIDartState::Current()->GetStateById(instanceId);
    ACE_DCHECK(state != nullptr);
    auto flutterTaskExecutor = AceType::DynamicCast<FlutterTaskExecutor>(taskExecutor_);
    flutterTaskExecutor->InitOtherThreads(state->GetTaskRunners());

    if (type_ == FrontendType::DECLARATIVE_JS) {
        // For DECLARATIVE_JS or UJOINT_JS frontend display UI in JS thread temporarily.
        flutterTaskExecutor->InitJsThread(false);
        InitializeFrontend();
        auto front = GetFrontend();
        if (front) {
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
            front->SetAssetManager(assetManager_);
        }
    }

    resRegister_ = aceView_->GetPlatformResRegister();
    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(std::move(window),
                                                            taskExecutor_,
                                                            assetManager_,
                                                            resRegister_,
                                                            frontend_,
                                                            instanceId);
    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowModal(windowModal_);
    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    InitializeCallback();

    auto&& finishEventHandler = [weak = WeakClaim(this)] {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("FinishEventHandler container is null!");
            return;
        }
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

    auto&& setStatusBarEventHandler = [weak = WeakClaim(this)](const Color& color) {
        auto container = weak.Upgrade();
        if (!container) {
            LOGE("StatusBarEventHandler container is null!");
            return;
        }
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

    // Load custom style at UI thread before frontend attach, to make sure style can be loaded before building dom tree.
    auto themeManager = pipelineContext_->GetThemeManager();
    if (themeManager) {
        taskExecutor_->PostTask(
            [ themeManager, assetManager = assetManager_, colorScheme = colorScheme_] {
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
            },
            TaskExecutor::TaskType::UI);
    }

    taskExecutor_->PostTask(
        [context = pipelineContext_]() { context->SetupRootElement(); }, TaskExecutor::TaskType::UI);
    aceView_->Launch();
    frontend_->AttachPipelineContext(pipelineContext_);

    AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_);
}

void AceContainer::SetFontScale(int32_t instanceId, float fontScale)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }
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
    container->SetWindowModal(windowModal);
    container->SetColorScheme(colorScheme);
}
} // namespace OHOS::Ace::Platform
