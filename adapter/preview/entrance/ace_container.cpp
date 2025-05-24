/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include <functional>

#include "base/log/log.h"

#ifndef ENABLE_ROSEN_BACKEND
#include "flutter/lib/ui/ui_dart_state.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "core/common/asset_manager_impl.h"
#else // ENABLE_ROSEN_BACKEND == true
#include "adapter/preview/entrance/rs_dir_asset_provider.h"
#include "core/common/rosen/rosen_asset_manager.h"
#endif

#include "native_engine/native_engine.h"
#include "previewer/include/window.h"

#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/ace_preview_helper.h"
#include "adapter/preview/osal/stage_card_parser.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/card_frontend/card_frontend.h"
#include "bridge/card_frontend/card_frontend_declarative.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/engine/common/js_engine_loader.h"
#include "bridge/js_frontend/js_frontend.h"
#include "core/common/ace_engine.h"
#include "core/common/ace_view.h"
#include "core/common/container_scope.h"
#include "core/common/platform_bridge.h"
#include "core/common/platform_window.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/task_executor_impl.h"
#include "core/common/text_field_manager.h"
#include "core/common/window.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/simulator/ability_simulator/include/ability_context.h"

namespace OHOS::Ace::Platform {
namespace {
const char LANGUAGE_TAG[] = "language";
const char COUNTRY_TAG[] = "countryOrRegion";
const char DIRECTION_TAG[] = "dir";
const char UNICODE_SETTING_TAG[] = "unicodeSetting";
const char LOCALE_DIR_LTR[] = "ltr";
const char LOCALE_DIR_RTL[] = "rtl";
const char LOCALE_KEY[] = "locale";

void ReleaseStorageReference(void* sharedRuntime, NativeReference* storage)
{
    if (sharedRuntime && storage) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(sharedRuntime);
        auto env = reinterpret_cast<napi_env>(nativeEngine);
        napi_delete_reference(env, reinterpret_cast<napi_ref>(storage));
    }
}

std::string EncodeBundleAndModule(const std::string& bundleName, const std::string& moduleName)
{
    return bundleName + " " + moduleName;
}

void SaveResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
    RefPtr<ResourceAdapter>& resourceAdapter)
{
    auto defaultBundleName = "";
    auto defaultModuleName = "";
    ResourceManager::GetInstance().AddResourceAdapter(
        defaultBundleName, defaultModuleName, instanceId, resourceAdapter);
    LOGI("Save default adapter");

    if (!bundleName.empty() && !moduleName.empty()) {
        LOGI("Save resource adapter bundle: %{public}s, module: %{public}s", bundleName.c_str(), moduleName.c_str());
        ResourceManager::GetInstance().AddResourceAdapter(bundleName, moduleName, instanceId, resourceAdapter);
    }
}
} // namespace

std::once_flag AceContainer::onceFlag_;
bool AceContainer::isComponentMode_ = false;
AceContainer::AceContainer(int32_t instanceId, FrontendType type, bool useNewPipeline, bool useCurrentEventRunner)
    : instanceId_(instanceId), messageBridge_(AceType::MakeRefPtr<PlatformBridge>()), type_(type)
{
    LOGI("Using %{public}s pipeline context ...", (useNewPipeline ? "new" : "old"));
    if (useNewPipeline) {
        SetUseNewPipeline();
    }
    ThemeConstants::InitDeviceType();
    auto taskExecutorImpl = Referenced::MakeRefPtr<TaskExecutorImpl>();
    taskExecutorImpl->InitPlatformThread(useCurrentEventRunner);
    if (type_ != FrontendType::DECLARATIVE_JS && type_ != FrontendType::ETS_CARD) {
        taskExecutorImpl->InitJsThread();
    } else {
        GetSettings().useUIAsJSThread = true;
    }
    taskExecutor_ = taskExecutorImpl;
}

void AceContainer::Initialize()
{
    ContainerScope scope(instanceId_);
    if (type_ != FrontendType::DECLARATIVE_JS && type_ != FrontendType::ETS_CARD) {
        InitializeFrontend();
    }
}

void AceContainer::Destroy()
{
    ContainerScope scope(instanceId_);
    if (!pipelineContext_) {
        return;
    }
    if (!taskExecutor_) {
        return;
    }
    auto weak = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weak]() {
            auto context = weak.Upgrade();
            if (context == nullptr) {
                return;
            }
            context->Destroy();
        },
        TaskExecutor::TaskType::UI, "ArkUIPipelineDestroy");

    RefPtr<Frontend> frontend;
    frontend_.Swap(frontend);
    if (frontend && taskExecutor_) {
        taskExecutor_->PostTask(
            [frontend]() {
                frontend->UpdateState(Frontend::State::ON_DESTROY);
                frontend->Destroy();
            },
            TaskExecutor::TaskType::JS, "ArkUIFrontendDestroy");
    }

    messageBridge_.Reset();
    resRegister_.Reset();
    assetManager_.Reset();
    pipelineContext_.Reset();
    aceView_ = nullptr;
}

void AceContainer::DestroyView()
{
    if (aceView_ != nullptr) {
        aceView_ = nullptr;
    }
}

void AceContainer::InitializeFrontend()
{
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        auto jsEngine = Framework::JsEngineLoader::Get().CreateJsEngine(GetInstanceId());
        EngineHelper::AddEngine(instanceId_, jsEngine);
        jsFrontend->SetJsEngine(jsEngine);
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
    } else if (type_ == FrontendType::DECLARATIVE_JS) {
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
        auto& loader = Framework::JsEngineLoader::GetDeclarative();
        RefPtr<Framework::JsEngine> jsEngine;
        if (GetSettings().usingSharedRuntime) {
            jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
        } else {
            jsEngine = loader.CreateJsEngine(instanceId_);
        }
        EngineHelper::AddEngine(instanceId_, jsEngine);
        declarativeFrontend->SetJsEngine(jsEngine);
        declarativeFrontend->SetPageProfile(pageProfile_);
        if (PkgContextInfo_) {
            declarativeFrontend->SetPkgNameList(PkgContextInfo_->GetPkgNameMap());
            declarativeFrontend->SetPkgAliasList(PkgContextInfo_->GetPkgAliasMap());
            declarativeFrontend->SetpkgContextInfoList(PkgContextInfo_->GetPkgContextInfoMap());
        }
    } else if (type_ == FrontendType::JS_CARD) {
        AceApplicationInfo::GetInstance().SetCardType();
        frontend_ = AceType::MakeRefPtr<CardFrontend>();
    } else if (type_ == FrontendType::ETS_CARD) {
        frontend_ = AceType::MakeRefPtr<FormFrontendDeclarative>();
        auto cardFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
        auto jsEngine = Framework::JsEngineLoader::GetDeclarative().CreateJsEngine(instanceId_);
        EngineHelper::AddEngine(instanceId_, jsEngine);
        cardFrontend->SetJsEngine(jsEngine);
        cardFrontend->SetPageProfile(pageProfile_);
        cardFrontend->SetRunningCardId(0);
        cardFrontend->SetIsFormRender(true);
        cardFrontend->SetTaskExecutor(taskExecutor_);
        if (PkgContextInfo_) {
            cardFrontend->SetPkgNameList(PkgContextInfo_->GetPkgNameMap());
            cardFrontend->SetPkgAliasList(PkgContextInfo_->GetPkgAliasMap());
            cardFrontend->SetpkgContextInfoList(PkgContextInfo_->GetPkgContextInfoMap());
        }
        SetIsFRSCardContainer(true);
    }
    ACE_DCHECK(frontend_);
    frontend_->DisallowPopLastPage();
    frontend_->Initialize(type_, taskExecutor_);
    if (assetManager_) {
        frontend_->SetAssetManager(assetManager_);
    }
}

void AceContainer::RunNativeEngineLoop()
{
    taskExecutor_->PostTask([frontend = frontend_]() { frontend->RunNativeEngineLoop(); }, TaskExecutor::TaskType::JS,
        "ArkUIRunNativeEngineLoop");
    // After the JS thread executes frontend ->RunNativeEngineLoop(),
    // it is thrown back into the Platform thread queue to form a loop.
    taskExecutor_->PostTask([this]() { RunNativeEngineLoop(); },
        TaskExecutor::TaskType::PLATFORM, "ArkUIRunNativeEngineLoop");
}

void AceContainer::InitializeAppConfig(const std::string& assetPath, const std::string& bundleName,
    const std::string& moduleName, const std::string& compileMode)
{
    bool isBundle = (compileMode != "esmodule");
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
    CHECK_NULL_VOID(declarativeFrontend);
    declarativeFrontend->InitializeModuleSearcher(bundleName, moduleName, assetPath, isBundle);

    auto formFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
    CHECK_NULL_VOID(formFrontend);
    formFrontend->SetBundleName(bundleName);
    formFrontend->SetModuleName(moduleName);
    formFrontend->SetIsBundle(isBundle);
}

void AceContainer::SetHspBufferTrackerCallback()
{
    if (GetSettings().usingSharedRuntime) {
        LOGI("The callback has been set by ability in the light simulator.");
        return;
    }
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
    CHECK_NULL_VOID(frontend);
    auto weak = WeakPtr(frontend->GetJsEngine());
    taskExecutor_->PostTask(
        [weak, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(weak.Upgrade());
            CHECK_NULL_VOID(jsEngine);
            jsEngine->SetHspBufferTrackerCallback(AcePreviewHelper::GetInstance()->GetCallbackOfHspBufferTracker());
        },
        TaskExecutor::TaskType::JS, "ArkUISetHspBufferTracker");
}

void AceContainer::SetMockModuleListToJsEngine()
{
    if (GetSettings().usingSharedRuntime) {
        LOGI("The callback has been set by ability in the light simulator.");
        return;
    }
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
    CHECK_NULL_VOID(frontend);
    auto weak = WeakPtr(frontend->GetJsEngine());
    taskExecutor_->PostTask(
        [weak, instanceId = instanceId_, mockJsonInfo = mockJsonInfo_]() {
            ContainerScope scope(instanceId);
            auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(weak.Upgrade());
            CHECK_NULL_VOID(jsEngine);
            jsEngine->SetMockModuleList(mockJsonInfo);
        },
        TaskExecutor::TaskType::JS, "ArkUISetMockModuleList");
}

void AceContainer::SetStageCardConfig(const std::string& pageProfile, const std::string& selectUrl)
{
    std::string fullPageProfile = pageProfile + ".json";
    std::string formConfigs;
    RefPtr<StageCardParser> stageCardParser = AceType::MakeRefPtr<StageCardParser>();
    if (!Framework::GetAssetContentImpl(assetManager_, fullPageProfile, formConfigs)) {
        LOGW("Can not load the form config, formConfigs is %{public}s", formConfigs.c_str());
        return;
    }
    const std::string prefix("./js/");
    stageCardParser->Parse(formConfigs, prefix + selectUrl);
    auto cardFront = static_cast<CardFrontend*>(RawPtr(frontend_));
    if (cardFront) {
        cardFront->SetFormSrc(selectUrl);
        cardFront->SetCardWindowConfig(stageCardParser->GetWindowConfig());
    }
}

void AceContainer::SetPkgContextInfo(const RefPtr<StagePkgContextInfo>& PkgContextInfo)
{
    PkgContextInfo_ = PkgContextInfo;
}

void AceContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();

    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);

    auto weak = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    auto&& touchEventCallback = [weak, id = instanceId_](
                                    const TouchEvent& event, const std::function<void()>& ignoreMark,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [context, event]() { context->OnTouchEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerTouchEvent");
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);

    auto&& keyEventCallback = [weak, id = instanceId_](const KeyEvent& event) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return false;
        }
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnNonPointerEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerKeyEvent");
        return result;
    };
    aceView_->RegisterKeyEventCallback(keyEventCallback);

    auto&& mouseEventCallback = [weak, id = instanceId_](
                                    const MouseEvent& event, const std::function<void()>& ignoreMark,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [context, event]() { context->OnMouseEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerMouseEvent");
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);

    auto&& axisEventCallback = [weak, id = instanceId_](
                                   const AxisEvent& event, const std::function<void()>& ignoreMark,
                                   const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [context, event]() { context->OnAxisEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerAxisEvent");
    };
    aceView_->RegisterAxisEventCallback(axisEventCallback);

    auto&& crownEventCallback = [weak, id = instanceId_](
        const CrownEvent& event, const std::function<void()>& ignoreMark) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return false;
        }
        context->GetTaskExecutor()->PostTask(
            [context, event, id]() {
                ContainerScope scope(id);
                context->OnNonPointerEvent(event);
            },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerCrownEvent");
        return true;
    };
    aceView_->RegisterCrownEventCallback(crownEventCallback);

    auto&& rotationEventCallback = [weak, id = instanceId_](const RotationEvent& event) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return false;
        }
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnRotationEvent(event); },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerRotationEvent");
        return result;
    };
    aceView_->RegisterRotationEventCallback(rotationEventCallback);

    auto&& cardViewPositionCallback = [weak, instanceId = instanceId_](int id, float offsetX, float offsetY) {
        ContainerScope scope(instanceId);
        auto context = AceType::DynamicCast<PipelineContext>(weak.Upgrade());
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostSyncTask(
            [context, id, offsetX, offsetY]() { context->SetCardViewPosition(id, offsetX, offsetY); },
            TaskExecutor::TaskType::UI, "ArkUISetCardViewPosition");
    };
    aceView_->RegisterCardViewPositionCallback(cardViewPositionCallback);

    auto&& cardViewParamsCallback = [weak, id = instanceId_](const std::string& key, bool focus) {
        ContainerScope scope(id);
        auto context = AceType::DynamicCast<PipelineContext>(weak.Upgrade());
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostSyncTask(
            [context, key, focus]() { context->SetCardViewAccessibilityParams(key, focus); },
            TaskExecutor::TaskType::UI, "ArkUISetCardViewAccessibilityParams");
    };
    aceView_->RegisterCardViewAccessibilityParamsCallback(cardViewParamsCallback);

    auto&& viewChangeCallback = [weak, id = instanceId_](int32_t width, int32_t height, WindowSizeChangeReason type,
                                    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        ACE_SCOPED_TRACE("ViewChangeCallback(%d, %d)", width, height);
        context->GetTaskExecutor()->PostTask(
            [context, width, height, type, rsTransaction]() {
                context->OnSurfaceChanged(width, height, type, rsTransaction);
            },
            TaskExecutor::TaskType::UI, "ArkUISurfaceChanged");
    };
    aceView_->RegisterViewChangeCallback(viewChangeCallback);

    auto&& densityChangeCallback = [weak, id = instanceId_](double density) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        ACE_SCOPED_TRACE("DensityChangeCallback(%lf)", density);
        context->GetTaskExecutor()->PostTask(
            [context, density]() { context->OnSurfaceDensityChanged(density); },
            TaskExecutor::TaskType::UI, "ArkUIDensityChanged");
    };
    aceView_->RegisterDensityChangeCallback(densityChangeCallback);

    auto&& systemBarHeightChangeCallback = [weak, id = instanceId_](double statusBar, double navigationBar) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        ACE_SCOPED_TRACE("SystemBarHeightChangeCallback(%lf, %lf)", statusBar, navigationBar);
        context->GetTaskExecutor()->PostTask(
            [context, statusBar, navigationBar]() { context->OnSystemBarHeightChanged(statusBar, navigationBar); },
            TaskExecutor::TaskType::UI, "ArkUISystemBarHeightChanged");
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);

    auto&& surfaceDestroyCallback = [weak, id = instanceId_]() {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); },
            TaskExecutor::TaskType::UI, "ArkUISurfaceDestroyed");
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);

    auto&& idleCallback = [weak, id = instanceId_](int64_t deadline) {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [context, deadline]() { context->OnIdle(deadline); }, TaskExecutor::TaskType::UI, "ArkUIIdleTask");
    };
    aceView_->RegisterIdleCallback(idleCallback);
}

void AceContainer::CreateContainer(
    int32_t instanceId, FrontendType type, bool useNewPipeline, bool useCurrentEventRunner)
{
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(instanceId, type, useNewPipeline, useCurrentEventRunner);
    AceEngine::Get().AddContainer(aceContainer->GetInstanceId(), aceContainer);
    aceContainer->Initialize();
    ContainerScope scope(instanceId);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }
    auto platMessageBridge = aceContainer->GetMessageBridge();
    platMessageBridge->SetJsMessageDispatcher(aceContainer);
}

void AceContainer::DestroyContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return;
    }
    container->Destroy();
    // unregister watchdog before stop thread to avoid UI_BLOCK report
    AceEngine::Get().UnRegisterFromWatchDog(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    if (taskExecutor) {
        taskExecutor->PostSyncTask([] { LOGI("Wait UI thread..."); }, TaskExecutor::TaskType::UI, "ArkUIWaitLog");
        taskExecutor->PostSyncTask([] { LOGI("Wait JS thread..."); }, TaskExecutor::TaskType::JS, "ArkUIWaitLog");
    }
    container->DestroyView(); // Stop all threads(ui,gpu,io) for current ability.
    EngineHelper::RemoveEngine(instanceId);
    AceEngine::Get().RemoveContainer(instanceId);
}

UIContentErrorCode AceContainer::RunPage(
    int32_t instanceId, const std::string& url, const std::string& params, bool isNamedRouter)
{
    ACE_FUNCTION_TRACE();
    auto container = AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        return UIContentErrorCode::NULL_POINTER;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, UIContentErrorCode::NULL_POINTER);
    auto type = front->GetType();
    if ((type == FrontendType::JS) || (type == FrontendType::DECLARATIVE_JS) || (type == FrontendType::JS_CARD) ||
        (type == FrontendType::ETS_CARD)) {
        if (isNamedRouter) {
            return front->RunPageByNamedRouter(url, params);
        }
        return front->RunPage(url, params);
    } else {
        LOGE("Frontend type not supported when runpage");
    }
    return UIContentErrorCode::NULL_POINTER;
}

void AceContainer::UpdateResourceConfiguration(const std::string& jsonStr)
{
    ContainerScope scope(instanceId_);
    uint32_t updateFlags = 0;
    auto resConfig = resourceInfo_.GetResourceConfiguration();
    if (!resConfig.UpdateFromJsonString(jsonStr, updateFlags) || !updateFlags) {
        return;
    }
    resourceInfo_.SetResourceConfiguration(resConfig);
    if (ResourceConfiguration::TestFlag(updateFlags, ResourceConfiguration::COLOR_MODE_UPDATED_FLAG)) {
        SetColorMode(resConfig.GetColorMode());
        if (frontend_) {
            frontend_->SetColorMode(resConfig.GetColorMode());
        }
    }
    if (!pipelineContext_) {
        return;
    }
    auto themeManager = pipelineContext_->GetThemeManager();
    if (!themeManager) {
        return;
    }
    themeManager->UpdateConfig(resConfig);
    if (SystemProperties::GetResourceDecoupling()) {
        ResourceManager::GetInstance().UpdateResourceConfig(resConfig);
    }
    taskExecutor_->PostTask(
        [weakThemeManager = WeakPtr<ThemeManager>(themeManager), colorScheme = colorScheme_, config = resConfig,
            weakContext = WeakPtr<PipelineBase>(pipelineContext_)]() {
            auto themeManager = weakThemeManager.Upgrade();
            auto context = weakContext.Upgrade();
            if (!themeManager || !context) {
                return;
            }
            themeManager->LoadResourceThemes();
            themeManager->ParseSystemTheme();
            themeManager->SetColorScheme(colorScheme);
            context->RefreshRootBgColor();
            context->UpdateFontWeightScale();
            context->SetFontScale(config.GetFontRatio());
        },
        TaskExecutor::TaskType::UI, "ArkUIUpdateResourceConfig");
    if (frontend_) {
        frontend_->RebuildAllPages();
    }
}

void AceContainer::NativeOnConfigurationUpdated(int32_t instanceId)
{
    auto container = GetContainerInstance(instanceId);
    if (!container) {
        return;
    }
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    if (!front) {
        return;
    }

    std::unique_ptr<JsonValue> value = JsonUtil::Create(true);
    value->Put("fontScale", container->GetResourceConfiguration().GetFontRatio());
    value->Put("colorMode", container->GetColorMode() == ColorMode::LIGHT ? "light" : "dark");
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(front);
    if (declarativeFrontend) {
        container->UpdateResourceConfiguration(value->ToString());
        declarativeFrontend->OnConfigurationUpdated(value->ToString());
        return;
    }

    std::unique_ptr<JsonValue> localeValue = JsonUtil::Create(true);
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
        return;
    }
    ContainerScope scope(instanceId_);
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
        return;
    }
}

void AceContainer::CallCurlFunction(const RequestData requestData, const int32_t callbackId) const
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(ACE_INSTANCE_ID));
    if (!container) {
        return;
    }

    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [container, requestData, callbackId]() mutable {
            ResponseData responseData;
            if (FetchManager::GetInstance().Fetch(requestData, callbackId, responseData)) {
                container->FetchResponse(responseData, callbackId);
            }
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUICallCurlFunction");
}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    auto front = GetFrontend();
    if (!front) {
        return;
    }

    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [front, callbackId, errorCode, errorMessage = std::move(errorMessage)]() mutable {
            front->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIDispatchPluginError");
}

void AceContainer::AddRouterChangeCallback(int32_t instanceId, const OnRouterChangeCallback& onRouterChangeCallback)
{
    auto container = GetContainerInstance(instanceId);
    if (!container) {
        return;
    }
    ContainerScope scope(instanceId);
    if (!container->pipelineContext_) {
        LOGW("container pipelineContext not init");
        return;
    }
    container->pipelineContext_->AddRouterChangeCallback(onRouterChangeCallback);
}

#ifndef ENABLE_ROSEN_BACKEND
void AceContainer::AddAssetPath(
    int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths)
{
    auto container = GetContainerInstance(instanceId);
    CHECK_NULL_VOID(container);
    if (!container->assetManager_) {
        RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
        container->assetManager_ = assetManagerImpl;
        if (container->frontend_) {
            container->frontend_->SetAssetManager(assetManagerImpl);
        }
    }
    auto fileAssetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
    if (fileAssetProvider->Initialize("", paths)) {
        LOGI("Push AssetProvider to queue.");
        container->assetManager_->PushBack(std::move(fileAssetProvider));
    }
}
#else
void AceContainer::AddAssetPath(
    int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths)
{
    auto container = GetContainerInstance(instanceId);
    CHECK_NULL_VOID(container);

    if (!container->assetManager_) {
        RefPtr<RSAssetManager> rsAssetManager = Referenced::MakeRefPtr<RSAssetManager>();
        container->assetManager_ = rsAssetManager;
        if (container->frontend_) {
            container->frontend_->SetAssetManager(rsAssetManager);
        }
    }

    for (const auto& path : paths) {
        auto dirAssetProvider = AceType::MakeRefPtr<RSDirAssetProvider>(path);
        container->assetManager_->PushBack(std::move(dirAssetProvider));
    }
}
#endif

void AceContainer::SetResourcesPathAndThemeStyle(int32_t instanceId, const std::string& systemResourcesPath,
    const std::string& hmsResourcesPath, const std::string& appResourcesPath, const int32_t& themeId,
    const ColorMode& colorMode)
{
    auto container = GetContainerInstance(instanceId);
    if (!container) {
        return;
    }
    ContainerScope scope(instanceId);
    auto resConfig = container->resourceInfo_.GetResourceConfiguration();
    resConfig.SetColorMode(static_cast<OHOS::Ace::ColorMode>(colorMode));
    container->resourceInfo_.SetResourceConfiguration(resConfig);
    container->resourceInfo_.SetPackagePath(appResourcesPath);
    container->resourceInfo_.SetSystemPackagePath(systemResourcesPath);
    if (!hmsResourcesPath.empty()) {
        container->resourceInfo_.SetHmsPackagePath(hmsResourcesPath);
    }
    container->resourceInfo_.SetThemeId(themeId);
}

void AceContainer::UpdateDeviceConfig(const DeviceConfig& deviceConfig)
{
    ContainerScope scope(instanceId_);
    SystemProperties::InitDeviceType(deviceConfig.deviceType);
    SystemProperties::SetDeviceOrientation(deviceConfig.orientation == DeviceOrientation::PORTRAIT ? 0 : 1);
    SystemProperties::SetResolution(deviceConfig.density);
    SetColorMode(deviceConfig.colorMode);
    auto resConfig = resourceInfo_.GetResourceConfiguration();
    if (resConfig.GetDeviceType() == deviceConfig.deviceType &&
        resConfig.GetOrientation() == deviceConfig.orientation && resConfig.GetDensity() == deviceConfig.density &&
        resConfig.GetColorMode() == deviceConfig.colorMode && resConfig.GetFontRatio() == deviceConfig.fontRatio) {
        return;
    } else {
        resConfig.SetDeviceType(deviceConfig.deviceType);
        resConfig.SetOrientation(deviceConfig.orientation);
        resConfig.SetDensity(deviceConfig.density);
        resConfig.SetColorMode(deviceConfig.colorMode);
        resConfig.SetFontRatio(deviceConfig.fontRatio);
        if (frontend_) {
            frontend_->SetColorMode(deviceConfig.colorMode);
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
    if (SystemProperties::GetResourceDecoupling()) {
        ResourceManager::GetInstance().UpdateResourceConfig(resConfig);
    }
    taskExecutor_->PostTask(
        [weakThemeManager = WeakPtr<ThemeManager>(themeManager), colorScheme = colorScheme_,
            weakContext = WeakPtr<PipelineBase>(pipelineContext_)]() {
            auto themeManager = weakThemeManager.Upgrade();
            auto context = weakContext.Upgrade();
            if (!themeManager || !context) {
                return;
            }
            themeManager->LoadResourceThemes();
            themeManager->ParseSystemTheme();
            themeManager->SetColorScheme(colorScheme);
            context->RefreshRootBgColor();
        },
        TaskExecutor::TaskType::UI, "ArkUILoadTheme");
}

#ifndef ENABLE_ROSEN_BACKEND
void AceContainer::SetView(AceViewPreview* view, double density, int32_t width, int32_t height)
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

    auto window = std::make_shared<Window>(std::move(platformWindow));
    container->AttachView(std::move(window), view, density, width, height);
}
#else
void AceContainer::SetView(AceViewPreview* view, sptr<Rosen::Window> rsWindow, double density, int32_t width,
    int32_t height, UIEnvCallback callback)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    window->Init();
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_VOID(rsUIDirector);
    rsUIDirector->SetFlushEmptyCallback(AcePreviewHelper::GetInstance()->GetCallbackFlushEmpty());
    container->AttachView(std::move(window), view, density, width, height, callback);
}
#endif

#ifndef ENABLE_ROSEN_BACKEND
void AceContainer::AttachView(
    std::shared_ptr<Window> window, AceViewPreview* view, double density, int32_t width, int32_t height)
{
    ContainerScope scope(instanceId_);
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();

    auto state = flutter::UIDartState::Current()->GetStateById(instanceId);
    ACE_DCHECK(state != nullptr);
    auto taskExecutorImpl = AceType::DynamicCast<TaskExecutorImpl>(taskExecutorImpl_);
    taskExecutorImpl->InitOtherThreads(state->GetTaskRunners());
    if (type_ == FrontendType::DECLARATIVE_JS) {
        // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
        taskExecutorImpl->InitJsThread(false);
    }
    if (type_ == FrontendType::DECLARATIVE_JS) {
        InitializeFrontend();
        auto front = GetFrontend();
        if (front) {
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
        }
    }
    resRegister_ = aceView_->GetPlatformResRegister();
    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>(
        std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    pipelineContext->SetRootSize(density, width, height);
    pipelineContext->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    pipelineContext->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext->SetMessageBridge(messageBridge_);
    pipelineContext->SetWindowModal(windowModal_);
    pipelineContext->SetDrawDelegate(aceView_->GetDrawDelegate());
    pipelineContext->SetIsJsCard(type_ == FrontendType::JS_CARD);
    pipelineContext_ = pipelineContext;
    InitializeCallback();

    ThemeConstants::InitDeviceType();
    // Only init global resource here, construct theme in UI thread
    auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();

    if (SystemProperties::GetResourceDecoupling()) {
        auto resourceAdapter = ResourceAdapter::Create();
        resourceAdapter->Init(resourceInfo);
        SaveResourceAdapter(bundleName_, moduleName_, instanceId_, resourceAdapter);
        themeManager = AceType::MakeRefPtr<ThemeManagerImpl>(resourceAdapter);
    }
    if (themeManager) {
        pipelineContext_->SetThemeManager(themeManager);
        // Init resource, load theme map.
        if (!SystemProperties::GetResourceDecoupling()) {
            themeManager->InitResource(resourceInfo_);
        }
        themeManager->LoadSystemTheme(resourceInfo_.GetThemeId());
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_,
                pipelineContext = pipelineContext_]() {
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                // get background color from theme
                pipelineContext->SetAppBgColor(themeManager->GetBackgroundColor());
            },
            TaskExecutor::TaskType::UI, "ArkUISetBackgroundColor");
    }

    auto weak = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weak]() {
            auto context = weak.Upgrade();
            if (context == nullptr) {
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI, "ArkUISetupRootElement");
    aceView_->Launch();

    frontend_->AttachPipelineContext(pipelineContext_);
    auto cardFronted = AceType::DynamicCast<CardFrontend>(frontend_);
    if (cardFronted) {
        cardFronted->SetDensity(static_cast<double>(density));
        taskExecutor_->PostTask(
            [weak, width, height]() {
                auto context = weak.Upgrade();
                if (context == nullptr) {
                    return;
                }
                context->OnSurfaceChanged(width, height);
            },
            TaskExecutor::TaskType::UI, "ArkUISurfaceChanged");
    }

    AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_, GetSettings().useUIAsJSThread);
}
#else
void AceContainer::AttachView(std::shared_ptr<Window> window, AceViewPreview* view, double density, int32_t width,
    int32_t height, UIEnvCallback callback)
{
    ContainerScope scope(instanceId_);
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();

    auto taskExecutorImpl = AceType::DynamicCast<TaskExecutorImpl>(taskExecutor_);
    CHECK_NULL_VOID(taskExecutorImpl);
    taskExecutorImpl->InitOtherThreads(aceView_->GetThreadModelImpl());
    if (type_ == FrontendType::DECLARATIVE_JS || type_ == FrontendType::ETS_CARD) {
        // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
        taskExecutorImpl->InitJsThread(false);
    }
    if (type_ == FrontendType::DECLARATIVE_JS || type_ == FrontendType::ETS_CARD) {
        InitializeFrontend();
        SetHspBufferTrackerCallback();
        SetMockModuleListToJsEngine();
        auto front = AceType::DynamicCast<DeclarativeFrontend>(GetFrontend());
        if (front) {
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
            auto weak = WeakPtr(front->GetJsEngine());
            taskExecutor_->PostTask(
                [weak, containerSdkPath = containerSdkPath_]() {
                    auto jsEngine = weak.Upgrade();
                    CHECK_NULL_VOID(jsEngine);
                    auto* nativeEngine = jsEngine->GetNativeEngine();
                    CHECK_NULL_VOID(nativeEngine);
                    auto* moduleManager = nativeEngine->GetModuleManager();
                    CHECK_NULL_VOID(moduleManager);
                    moduleManager->SetPreviewSearchPath(containerSdkPath);
                },
                TaskExecutor::TaskType::JS, "ArkUISetPreviewSearchPath");
        }
    }
    resRegister_ = aceView_->GetPlatformResRegister();
    if (useNewPipeline_) {
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<NG::TextFieldManagerNG>());
    } else {
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    }
    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetMessageBridge(messageBridge_);
    pipelineContext_->SetWindowModal(windowModal_);
    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    pipelineContext_->SetIsJsCard(type_ == FrontendType::JS_CARD);
    if (installationFree_ && !isComponentMode_) {
        pipelineContext_->SetInstallationFree(installationFree_);
        pipelineContext_->SetAppLabelId(labelId_);
    }
    pipelineContext_->OnShow();
    pipelineContext_->WindowFocus(true);
    InitializeCallback();

    auto cardFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
    if (cardFrontend) {
        pipelineContext_->SetIsFormRender(true);
        cardFrontend->SetLoadCardCallBack(WeakPtr<PipelineBase>(pipelineContext_));
    }

    ThemeConstants::InitDeviceType();
    // Only init global resource here, construct theme in UI thread
    auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();

    if (SystemProperties::GetResourceDecoupling()) {
        auto resourceAdapter = ResourceAdapter::Create();
        resourceAdapter->Init(resourceInfo_);
        SaveResourceAdapter(bundleName_, moduleName_, instanceId_, resourceAdapter);
        themeManager = AceType::MakeRefPtr<ThemeManagerImpl>(resourceAdapter);
    }

    if (themeManager) {
        pipelineContext_->SetThemeManager(themeManager);
        // Init resource, load theme map.
        if (!SystemProperties::GetResourceDecoupling()) {
            themeManager->InitResource(resourceInfo_);
        }
        themeManager->LoadSystemTheme(resourceInfo_.GetThemeId());
        taskExecutor_->PostTask(
            [themeManager, assetManager = assetManager_, colorScheme = colorScheme_,
                pipelineContext = pipelineContext_]() {
                themeManager->ParseSystemTheme();
                themeManager->SetColorScheme(colorScheme);
                themeManager->LoadCustomTheme(assetManager);
                // get background color from theme
                pipelineContext->SetAppBgColor(themeManager->GetBackgroundColor());
            },
            TaskExecutor::TaskType::UI, "ArkUISetBackgroundColor");
    }
    if (!useNewPipeline_) {
        taskExecutor_->PostTask(
            [context = pipelineContext_, callback]() {
                CHECK_NULL_VOID(callback);
                callback(AceType::DynamicCast<PipelineContext>(context));
            },
            TaskExecutor::TaskType::UI, "ArkUIEnvCallback");
    }

    auto weak = AceType::WeakClaim(AceType::RawPtr(pipelineContext_));
    taskExecutor_->PostTask(
        [weak]() {
            auto context = weak.Upgrade();
            if (context == nullptr) {
                return;
            }
            context->SetupRootElement();
        },
        TaskExecutor::TaskType::UI, "ArkUISetupRootElement");
    aceView_->Launch();

    frontend_->AttachPipelineContext(pipelineContext_);
    auto cardFronted = AceType::DynamicCast<CardFrontend>(frontend_);
    if (cardFronted) {
        cardFronted->SetDensity(static_cast<double>(density));
        taskExecutor_->PostTask(
            [weak, width, height]() {
                auto context = weak.Upgrade();
                if (context == nullptr) {
                    return;
                }
                context->OnSurfaceChanged(width, height);
            },
            TaskExecutor::TaskType::UI, "ArkUISurfaceChanged");
    }

    AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_, GetSettings().useUIAsJSThread);
}
#endif

RefPtr<AceContainer> AceContainer::GetContainerInstance(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    return container;
}

std::string AceContainer::GetContentInfo(int32_t instanceId, ContentInfoType type)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, "");
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, "");
    return front->GetContentInfo(type);
}

void AceContainer::LoadDocument(const std::string& url, const std::string& componentName)
{
    ContainerScope scope(instanceId_);
    if (type_ != FrontendType::DECLARATIVE_JS) {
        LOGE("Component Preview failed: 1.0 not support");
        return;
    }
    auto frontend = AceType::DynamicCast<OHOS::Ace::DeclarativeFrontend>(frontend_);
    if (!frontend) {
        LOGE("Component Preview failed: the frontend is nullptr");
        return;
    }
    auto jsEngine = frontend->GetJsEngine();
    if (!jsEngine) {
        LOGE("Component Preview failed: the jsEngine is nullptr");
        return;
    }
    taskExecutor_->PostTask(
        [front = frontend, componentName, url, jsEngine]() {
            front->SetPagePath(url);
            jsEngine->ReplaceJSContent(url, componentName);
        },
        TaskExecutor::TaskType::JS, "ArkUIReplaceJsContent");
}

void AceContainer::NotifyConfigurationChange(bool, const ConfigurationChange& configurationChange)
{
    taskExecutor_->PostTask(
        [weakContext = WeakPtr<PipelineBase>(pipelineContext_), configurationChange]() {
            auto pipeline = weakContext.Upgrade();
            CHECK_NULL_VOID(pipeline);
            pipeline->NotifyConfigurationChange();
            pipeline->FlushReload(configurationChange);
        },
        TaskExecutor::TaskType::UI, "ArkUINotifyConfigurationChange");
}

void AceContainer::SetLocalStorage(
    NativeReference* storage, const std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    ContainerScope scope(instanceId_);
    taskExecutor_->PostSyncTask(
        [frontend = WeakPtr<Frontend>(frontend_), storage,
            contextWeak = std::weak_ptr<OHOS::AbilityRuntime::Context>(context), id = instanceId_,
            sharedRuntime = sharedRuntime_] {
            auto sp = frontend.Upgrade();
            auto contextRef = contextWeak.lock();
            if (!sp || !contextRef) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
#ifdef NG_BUILD
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(sp);
#else
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(sp);
#endif
            if (!declarativeFrontend) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
            auto jsEngine = declarativeFrontend->GetJsEngine();
            if (!jsEngine) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
            if (contextRef->GetBindingObject() && contextRef->GetBindingObject()->Get<NativeReference>()) {
                jsEngine->SetContext(id, contextRef->GetBindingObject()->Get<NativeReference>());
            }
            if (storage) {
                jsEngine->SetLocalStorage(id, storage);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUISetLocalStorage");
}

std::shared_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    auto context = runtimeContext_.lock();
    CHECK_NULL_RETURN(context, nullptr);
    if (!bundle.empty() && !module.empty()) {
        std::string encode = EncodeBundleAndModule(bundle, module);
        if (taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            RecordResAdapter(encode);
        } else {
            taskExecutor_->PostTask(
                [encode, instanceId = instanceId_]() -> void {
                    auto container = AceContainer::GetContainerInstance(instanceId);
                    CHECK_NULL_VOID(container);
                    container->RecordResAdapter(encode);
                },
                TaskExecutor::TaskType::UI, "ArkUIRecordResAdapter");
        }
    }
    return context->CreateModuleContext(bundle, module);
}

void AceContainer::SetAbilityContext(const std::weak_ptr<OHOS::AbilityRuntime::Context>& context)
{
    runtimeContext_ = context;
}
} // namespace OHOS::Ace::Platform
