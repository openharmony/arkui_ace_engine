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

#include "adapter/preview/entrance/ace_container.h"

#include "flutter/assets/directory_asset_bundle.h"
#include "flutter/lib/ui/ui_dart_state.h"

#include "adapter/common/cpp/flutter_asset_manager.h"
#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/flutter_task_executor.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/ace_view.h"
#include "core/common/platform_bridge.h"
#include "core/common/platform_window.h"
#include "core/common/text_field_manager.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/card_frontend/card_frontend.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"

#ifdef USE_GLFW_WINDOW
#include "flutter/shell/platform/embedder/embedder.h"
#endif

namespace OHOS::Ace::Platform {

std::once_flag AceContainer::onceFlag_;

AceContainer::AceContainer(int32_t instanceId, FrontendType type) : instanceId_(instanceId), type_(type)
{
    ThemeConstants::InitDeviceType();

    auto state = flutter::UIDartState::Current()->GetStateById(instanceId);
    taskExecutor_ = Referenced::MakeRefPtr<FlutterTaskExecutor>(state->GetTaskRunners());

    InitializeFrontend();
}

void AceContainer::InitializeFrontend()
{
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        jsFrontend->SetJsEngine(Framework::JsEngineLoader::Get().CreateJsEngine(GetInstanceId()));
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
    } else if (type_ == FrontendType::JS_CARD) {
        AceApplicationInfo::GetInstance().SetCardType();
        frontend_ = AceType::MakeRefPtr<CardFrontend>();
    } else {
        LOGE("Frontend type not supported");
        return;
    }
    ACE_DCHECK(frontend_);
    frontend_->Initialize(type_, taskExecutor_);
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

    auto&& cardViewPositionCallback = [context = pipelineContext_](int id, float offsetX, float offsetY) {
        context->GetTaskExecutor()->PostSyncTask(
            [context, id, offsetX, offsetY]() { context->SetCardViewPosition(id, offsetX, offsetY); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterCardViewPositionCallback(cardViewPositionCallback);

    auto&& cardViewParamsCallback = [context = pipelineContext_](const std::string& key, bool focus) {
        context->GetTaskExecutor()->PostSyncTask(
            [context, key, focus]() { context->SetCardViewAccessibilityParams(key, focus); },
            TaskExecutor::TaskType::UI);
    };
    aceView_->RegisterCardViewAccessibilityParamsCallback(cardViewParamsCallback);

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

void AceContainer::CreateContainer(int32_t instanceId, FrontendType type)
{
#ifdef USE_GLFW_WINDOW
    std::call_once(onceFlag_, [] {
        FlutterEngineRegisterHandleTouchEventCallback([](std::unique_ptr<flutter::PointerDataPacket>& packet) -> bool {
            auto container = AceContainer::GetContainerInstance(0);
            if (!container || !container->GetAceView()) {
                return false;
            }
            return container->GetAceView()->HandleTouchEvent(std::move(packet));
        });
    });
#endif
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(instanceId, type);
    AceEngine::Get().AddContainer(aceContainer->GetInstanceId(), aceContainer);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }
}

void AceContainer::DestroyContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        LOGE("no AceContainer with id %{private}d in AceEngine", instanceId);
        return;
    }
    auto context = container->GetPipelineContext();
    if (context) {
        context->Destroy();
    }
    AceEngine::Get().RemoveContainer(instanceId);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_DESTROY);
    }

    auto taskExecutor = AceType::DynamicCast<FlutterTaskExecutor>(container->GetTaskExecutor());
    if (taskExecutor) {
        taskExecutor->DestroyJsThread();
    }

    auto aceView = AceType::DynamicCast<AceContainer>(container)->GetAceView();
    if (aceView) {
        LOGI("NotifyViewDestroyed");
        aceView->NotifyViewDestroyed([aceView]() { aceView->DecRefCount(); });
    }
}

bool AceContainer::RunPage(int32_t instanceId, int32_t pageId, const std::string& url, const std::string& params)
{
    ACE_FUNCTION_TRACE();

    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return false;
    }
    auto front = container->GetFrontend();
    if (front) {
        auto type = front->GetType();
        if ((type == FrontendType::JS) || (type == FrontendType::JS_CARD)) {
            front->RunPage(pageId, url, params);
            return true;
        } else {
            LOGE("Frontend type not supported when runpage");
            EventReport::SendAppStartException(AppStartExcepType::FRONTEND_TYPE_ERR);
            return false;
        }
    }
    return false;
}

void AceContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const {}

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

    for (const auto& path : paths) {
        AceEngine::Get().SetPackagePath(packagePath);
        AceEngine::Get().SetAssetBasePath(path);

        RefPtr<FlutterAssetManager> flutterAssetManager;
        if (container->assetManager_) {
            flutterAssetManager = AceType::DynamicCast<FlutterAssetManager>(container->assetManager_);
        } else {
            flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
            container->assetManager_ = flutterAssetManager;
            container->frontend_->SetAssetManager(flutterAssetManager);
        }

        if (flutterAssetManager) {
            LOGD("Current path is: %s", path.c_str());
            flutterAssetManager->PushBack(std::make_unique<flutter::DirectoryAssetBundle>(
                fml::OpenDirectory(path.c_str(), false, fml::FilePermission::kRead)));
        }
    }
}

void AceContainer::SetResourcesPathAndThemeStyle(int32_t instanceId, const std::string& resourcesPath,
                                                 const ThemeId& themeId, const ColorMode& colorMode)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    container->deviceResourceInfo_.deviceConfig.colorMode = static_cast<OHOS::Ace::ColorMode>(colorMode);
    container->deviceResourceInfo_.packagePath = resourcesPath;
    container->deviceResourceInfo_.themeId = static_cast<int32_t>(themeId);
}

void AceContainer::SetView(FlutterAceView* view, double density, int32_t width, int32_t height)
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

void AceContainer::AttachView(
    std::unique_ptr<Window> window, FlutterAceView* view, double density, int32_t width, int32_t height)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();

    resRegister_ = aceView_->GetPlatformResRegister();
    pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
        std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowModal(windowModal_);
    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    pipelineContext_->SetIsJsCard(type_ == FrontendType::JS_CARD);
    InitializeCallback();

    // Only init global resource here, construct theme in UI thread
    auto themeManager = pipelineContext_->GetThemeManager();
    if (themeManager) {
        // Init resource, load theme map.
        themeManager->InitResource(deviceResourceInfo_);
        themeManager->LoadSystemTheme(deviceResourceInfo_.themeId);
        // get background color from theme
        aceView_->SetBackgroundColor(themeManager->GetBackgroundColor());

        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_]() {
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
            },
            TaskExecutor::TaskType::UI);
    }

    taskExecutor_->PostTask(
        [context = pipelineContext_]() { context->SetupRootElement(); }, TaskExecutor::TaskType::UI);
    aceView_->Launch();

    frontend_->AttachPipelineContext(pipelineContext_);
    auto cardFronted = AceType::DynamicCast<CardFrontend>(frontend_);
    if (cardFronted) {
        cardFronted->SetDensity(static_cast<double>(density));
        taskExecutor_->PostTask(
            [context = pipelineContext_, width, height]() { context->OnSurfaceChanged(width, height); },
            TaskExecutor::TaskType::UI);
    }

    AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_);
}

RefPtr<AceContainer> AceContainer::GetContainerInstance(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    return container;
}

} // namespace OHOS::Ace::Platform
