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

#include "flutter/lib/ui/ui_dart_state.h"

#include "adapter/common/cpp/flutter_asset_manager.h"
#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/dir_asset_provider.h"
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
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"

#ifdef USE_GLFW_WINDOW
#include "flutter/shell/platform/embedder/embedder.h"
#endif

namespace OHOS::Ace::Platform {
namespace {
const char LANGUAGE_TAG[] = "language";
const char COUNTRY_TAG[] = "countryOrRegion";
const char DIRECTION_TAG[] = "dir";
const char UNICODE_SETTING_TAG[] = "unicodeSetting";
const char LOCALE_DIR_LTR[] = "ltr";
const char LOCALE_DIR_RTL[] = "rtl";
const char LOCALE_KEY[] = "locale";
}

std::once_flag AceContainer::onceFlag_;

AceContainer::AceContainer(int32_t instanceId, FrontendType type)
    : instanceId_(instanceId), messageBridge_(AceType::MakeRefPtr<PlatformBridge>()), type_(type)
{
    ThemeConstants::InitDeviceType();

    auto state = flutter::UIDartState::Current()->GetStateById(instanceId);
    taskExecutor_ = Referenced::MakeRefPtr<FlutterTaskExecutor>(state->GetTaskRunners());
    taskExecutor_->PostTask([instanceId]() { Container::InitForThread(instanceId); }, TaskExecutor::TaskType::JS);
    taskExecutor_->PostTask([instanceId]() { Container::InitForThread(instanceId); }, TaskExecutor::TaskType::UI);
}

void AceContainer::Initialize()
{
    InitializeFrontend();
}

void AceContainer::Destroy()
{
    if (pipelineContext_ && taskExecutor_) {
        taskExecutor_->PostTask([context = pipelineContext_]() { context->Destroy(); }, TaskExecutor::TaskType::UI);
    }

    if (frontend_ && taskExecutor_) {
        taskExecutor_->PostTask(
            [front = frontend_]() { front->UpdateState(Frontend::State::ON_DESTROY); }, TaskExecutor::TaskType::JS);
    }

    if (aceView_) {
        aceView_->DecRefCount();
    }

    resRegister_.Reset();
    assetManager_.Reset();
    messageBridge_.Reset();
    frontend_.Reset();
    pipelineContext_.Reset();
}

void AceContainer::InitializeFrontend()
{
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        jsFrontend->SetJsEngine(Framework::JsEngineLoader::Get().CreateJsEngine(GetInstanceId()));
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
    } else if (type_ == FrontendType::DECLARATIVE_JS) {
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
        declarativeFrontend->SetJsEngine(Framework::JsEngineLoader::GetDeclarative().CreateJsEngine(instanceId_));
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
    Container::InitForThread(INSTANCE_ID_PLATFORM);
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(instanceId, type);
    AceEngine::Get().AddContainer(aceContainer->GetInstanceId(), aceContainer);
    aceContainer->Initialize();
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
    container->Destroy();
    auto taskExecutor = container->GetTaskExecutor();
    if (taskExecutor) {
        taskExecutor->PostSyncTask([] { LOGI("Wait UI thread..."); }, TaskExecutor::TaskType::UI);
        taskExecutor->PostSyncTask([] { LOGI("Wait JS thread..."); }, TaskExecutor::TaskType::JS);
    }
    AceEngine::Get().RemoveContainer(instanceId);
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
        if ((type == FrontendType::JS) || (type == FrontendType::DECLARATIVE_JS) || (type == FrontendType::JS_CARD)) {
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

void AceContainer::UpdateResourceConfiguration(const std::string& jsonStr)
{
    bool isConfigurationUpdated = false;
    auto resConfig = resourceInfo_.GetResourceConfiguration();
    if (!resConfig.UpdateFromJsonString(jsonStr, isConfigurationUpdated) || !isConfigurationUpdated) {
        return;
    }
    resourceInfo_.SetResourceConfiguration(resConfig);
    if (!pipelineContext_) {
        return;
    }
    auto themeManager = pipelineContext_->GetThemeManager();
    if (!themeManager) {
        return;
    }
    themeManager->UpdateConfig(resConfig);
    taskExecutor_->PostTask(
        [weakThemeManager = WeakPtr<ThemeManager>(themeManager), colorScheme = colorScheme_, config = resConfig,
            weakContext = WeakPtr<PipelineContext>(pipelineContext_)]() {
            auto themeManager = weakThemeManager.Upgrade();
            auto context = weakContext.Upgrade();
            if (!themeManager || !context) {
                return;
            }
            themeManager->ReloadThemes();
            themeManager->ParseSystemTheme();
            themeManager->SetColorScheme(colorScheme);
            context->RefreshRootBgColor();
            context->UpdateFontWeightScale();
            context->SetFontScale(config.GetFontRatio());
        },
        TaskExecutor::TaskType::UI);
    if (frontend_) {
        frontend_->RebuildAllPages();
    }
}

void AceContainer::NativeOnConfigurationUpdated(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    auto front = container->GetFrontend();
    if (!front) {
        return;
    }

    std::unique_ptr<JsonValue> value = JsonUtil::Create(true);
    value->Put("fontScale", container->GetResourceConfiguration().GetFontRatio());
    value->Put("colorMode", SystemProperties::GetColorMode() == ColorMode::LIGHT ? "light" : "dark");
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(front);
    if (declarativeFrontend) {
        container->UpdateResourceConfiguration(value->ToString());
        declarativeFrontend->OnConfigurationUpdated(value->ToString());
        return;
    }

    std::unique_ptr<JsonValue> localeValue = JsonUtil::Create(false);
    localeValue->Put(LANGUAGE_TAG, AceApplicationInfo::GetInstance().GetLanguage().c_str());
    localeValue->Put(COUNTRY_TAG, AceApplicationInfo::GetInstance().GetCountryOrRegion().c_str());
    localeValue->Put(
        DIRECTION_TAG, AceApplicationInfo::GetInstance().IsRightToLeft() ? LOCALE_DIR_RTL : LOCALE_DIR_LTR);
    localeValue->Put(UNICODE_SETTING_TAG, AceApplicationInfo::GetInstance().GetUnicodeSetting().c_str());
    value->Put(LOCALE_KEY, localeValue);
    front->OnConfigurationUpdated(value->ToString());
}

void AceContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{}

void AceContainer::FetchResponse(const ResponseData responseData, const int32_t callbackId) const
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(0));
    if (!container) {
        LOGE("FetchResponse container is null!");
        return;
    }
    auto front = container->GetFrontend();
    auto type = container->GetType();
    if (type == FrontendType::JS) {
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(front);
        if (jsFrontend) {
            jsFrontend->TransferJsResponseDataPreview(callbackId, ACTION_SUCCESS, responseData);
        }
    } else if (type == FrontendType::DECLARATIVE_JS) {
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(front);
        if (declarativeFrontend) {
            declarativeFrontend->TransferJsResponseDataPreview(callbackId, ACTION_SUCCESS, responseData);
        }
    } else {
        LOGE("Frontend type not supported");
        return;
    }
}

void AceContainer::CallCurlFunction(const RequestData requestData, const int32_t callbackId) const
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(ACE_INSTANCE_ID));
    if (!container) {
        LOGE("CallCurlFunction container is null!");
        return;
    }
    taskExecutor_->PostTask(
        [container, requestData, callbackId]() mutable {
            ResponseData responseData;
            if (FetchManager::GetInstance().Fetch(requestData, callbackId, responseData)) {
                container->FetchResponse(responseData, callbackId);
            }
        },
        TaskExecutor::TaskType::BACKGROUND);
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

void AceContainer::AddRouterChangeCallback(int32_t instanceId, const OnRouterChangeCallback& onRouterChangeCallback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    if (!container->pipelineContext_) {
        LOGE("container pipelineContext not init");
        return;
    }
    container->pipelineContext_->AddRouterChangeCallback(onRouterChangeCallback);
}

void AceContainer::AddAssetPath(
    int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }

    for (const auto& path : paths) {
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
            auto dirAssetProvider = AceType::MakeRefPtr<DirAssetProvider>(
                path, std::make_unique<flutter::DirectoryAssetBundle>(
                          fml::OpenDirectory(path.c_str(), false, fml::FilePermission::kRead)));
            flutterAssetManager->PushBack(std::move(dirAssetProvider));
        }
    }
}

void AceContainer::SetResourcesPathAndThemeStyle(
    int32_t instanceId, const std::string& resourcesPath, const int32_t& themeId, const ColorMode& colorMode)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    if (!container) {
        return;
    }
    auto resConfig = container->resourceInfo_.GetResourceConfiguration();
    resConfig.SetColorMode(static_cast<OHOS::Ace::ColorMode>(colorMode));
    container->resourceInfo_.SetResourceConfiguration(resConfig);
    container->resourceInfo_.SetPackagePath(resourcesPath);
    container->resourceInfo_.SetThemeId(themeId);
}

void AceContainer::UpdateColorMode(ColorMode newColorMode)
{
    auto resConfig = resourceInfo_.GetResourceConfiguration();

    OHOS::Ace::ColorMode colorMode = static_cast<OHOS::Ace::ColorMode>(newColorMode);
    SystemProperties::SetColorMode(colorMode);
    if (resConfig.GetColorMode() == colorMode) {
        return;
    } else {
        resConfig.SetColorMode(colorMode);
        if (frontend_) {
            frontend_->SetColorMode(colorMode);
        }
    }
    resourceInfo_.SetResourceConfiguration(resConfig);
    if (!pipelineContext_) {
        return;
    }
    auto themeManager = pipelineContext_->GetThemeManager();
    if (!themeManager) {
        return;
    }
    themeManager->UpdateConfig(resConfig);
    taskExecutor_->PostTask(
        [weakThemeManager = WeakPtr<ThemeManager>(themeManager), colorScheme = colorScheme_,
            weakContext = WeakPtr<PipelineContext>(pipelineContext_)]() {
            auto themeManager = weakThemeManager.Upgrade();
            auto context = weakContext.Upgrade();
            if (!themeManager || !context) {
                return;
            }
            themeManager->ReloadThemes();
            themeManager->ParseSystemTheme();
            themeManager->SetColorScheme(colorScheme);
            context->RefreshRootBgColor();
        },
        TaskExecutor::TaskType::UI);
    if (frontend_) {
        frontend_->RebuildAllPages();
    }
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
    pipelineContext_->SetMessageBridge(messageBridge_);
    pipelineContext_->SetWindowModal(windowModal_);
    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    pipelineContext_->SetIsJsCard(type_ == FrontendType::JS_CARD);
    InitializeCallback();

    // Only init global resource here, construct theme in UI thread
    auto themeManager = pipelineContext_->GetThemeManager();
    if (themeManager) {
        // Init resource, load theme map.
        themeManager->InitResource(resourceInfo_);
        themeManager->LoadSystemTheme(resourceInfo_.GetThemeId());
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_, aceView = aceView_]() {
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                // get background color from theme
                aceView->SetBackgroundColor(themeManager->GetBackgroundColor());
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
