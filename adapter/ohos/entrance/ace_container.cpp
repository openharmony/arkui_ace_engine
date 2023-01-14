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

#include "adapter/ohos/entrance/ace_container.h"

#include <functional>

#include "ability_info.h"

#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
#include "adapter/ohos/entrance/ace_rosen_sync_task.h"
#endif
#include "flutter/lib/ui/ui_dart_state.h"
#include "wm/wm_common.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "adapter/ohos/entrance/file_asset_provider.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "adapter/ohos/entrance/hap_asset_provider.h"
#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/frame_report.h"
#include "base/log/log.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/card_frontend/card_frontend.h"
#include "bridge/card_frontend/card_frontend_declarative.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/js_frontend/engine/common/js_engine_loader.h"
#include "bridge/js_frontend/js_frontend.h"
#include "core/common/ace_engine.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container_scope.h"
#include "core/common/flutter/flutter_asset_manager.h"
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/hdc_register.h"
#include "core/common/platform_window.h"
#include "core/common/text_field_manager.h"
#include "core/common/window.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/render/adapter/form_render_window.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Platform {
namespace {

constexpr char ARK_ENGINE_SHARED_LIB[] = "libace_engine_ark.z.so";
constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";

#ifdef _ARM64_
const std::string ASSET_LIBARCH_PATH = "/lib/arm64";
#else
const std::string ASSET_LIBARCH_PATH = "/lib/arm";
#endif

const char* GetEngineSharedLibrary()
{
    return ARK_ENGINE_SHARED_LIB;
}

const char* GetDeclarativeSharedLibrary()
{
    return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
}

} // namespace
std::shared_ptr<void> AceContainer::formSurfaceNode_ = nullptr;
AceContainer::AceContainer(int32_t instanceId, FrontendType type, std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility,
    std::unique_ptr<PlatformEventCallback> callback, bool useCurrentEventRunner, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), aceAbility_(aceAbility), useCurrentEventRunner_(useCurrentEventRunner)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
    }
    InitializeTask();
    platformEventCallback_ = std::move(callback);
    useStageModel_ = false;
    auto ability = aceAbility_.lock();
    if (ability) {
        abilityInfo_ = ability->GetAbilityInfo();
    }
}

AceContainer::AceContainer(int32_t instanceId, FrontendType type,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool isSubAceContainer, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
    }
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
    LOGE("Kee AceContainer::Initialize");
    ContainerScope scope(instanceId_);
    // For DECLARATIVE_JS frontend use UI as JS Thread, so InitializeFrontend after UI thread created.
    if (type_ != FrontendType::DECLARATIVE_JS) {
        LOGE("Kee AceContainer::Initialize 1");
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
            // SubAceContainer just return.
            return;
        }

        // 2. Destroy Frontend on JS thread.
        RefPtr<Frontend> frontend;
        frontend_.Swap(frontend);
        if (GetSettings().usePlatformAsUIThread && GetSettings().useUIAsJSThread) {
            frontend->UpdateState(Frontend::State::ON_DESTROY);
            frontend->Destroy();
        } else {
            frontend->UpdateState(Frontend::State::ON_DESTROY);
            taskExecutor_->PostTask([frontend]() { frontend->Destroy(); }, TaskExecutor::TaskType::JS);
        }
    }
    resRegister_.Reset();
    assetManager_.Reset();
}

void AceContainer::DestroyView()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID_NOLOG(aceView_);
    auto flutterAceView = static_cast<FlutterAceView*>(aceView_);
    if (flutterAceView) {
        flutterAceView->DecRefCount();
    }
    aceView_ = nullptr;
}

void AceContainer::InitializeFrontend()
{
    auto aceAbility = aceAbility_.lock();
    if (type_ == FrontendType::JS) {
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        auto& loader = Framework::JsEngineLoader::Get(GetEngineSharedLibrary());
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
            if (isCardContainer_) {
                LOGE("Kee AceContainer::InitializeFrontend Container pageProfile_ = %{public}s", pageProfile_.c_str());
                frontend_ = AceType::MakeRefPtr<CardFrontendDeclarative>();
                if (frontend_) {
                    LOGE("Kee AceContainer::InitializeFrontend frontend_");
                } else {
                    LOGE("Kee AceContainer::InitializeFrontend frontend_ nullptr");
                }
                auto cardFrontend = AceType::DynamicCast<CardFrontendDeclarative>(frontend_);
                auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
                RefPtr<Framework::JsEngine> jsEngine;
                if (GetSettings().usingSharedRuntime) {
                    jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
                    LOGI("Kee Create engine using runtime, engine %{public}p", RawPtr(jsEngine));
                } else {
                    LOGI("Kee Create engine using runtime, CreateJsEngine");
                    jsEngine = loader.CreateJsEngine(instanceId_);
                }
                LOGE("Kee AceContainer::InitializeFrontend 11 instanceId_ = %{public}d", instanceId_);
                jsEngine->AddExtraNativeObject("ability", aceAbility.get()); // Card TODO
                LOGE("Kee AceContainer::InitializeFrontend 12");
                EngineHelper::AddEngine(instanceId_, jsEngine);
                LOGE("Kee AceContainer::InitializeFrontend 13");
                cardFrontend->SetJsEngine(jsEngine);
                cardFrontend->SetPageProfile(pageProfile_);
                cardFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
                cardFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
                LOGE("Kee AceContainer::InitializeFrontend 14");
                // Card front
                std::string formSrc = "./ets/widget/pages/card";
                std::string data = "{\"temperature\":\"24\",\"time\":\"00:40:47\"}";
                if (formSrc.compare(0, 2, "./") == 0) {       // 2:length of "./"
                    cardFrontend->SetFormSrc(formSrc.substr(2)); // 2:length of "./"
                } else {
                    cardFrontend->SetFormSrc(formSrc);
                }
                LOGE("Kee AceContainer::InitializeFrontend 15");
                // pipelineContext_->OnSurfaceChanged(400, 400);
                LOGE("Kee AceContainer::InitializeFrontend 16");
                // cardFrontend->SetLoadCardCallBack(WeakPtr<PipelineBase>(pipelineContext_));
                LOGE("Kee AceContainer::InitializeFrontend 17");
                cardFrontend->SetRunningCardId(0); // Card TODO: nodeId, Host->FMS->FRS->innersdk
                cardFrontend->isCardfront_ = true;
                // cardFrontend->RunPage(0, formSrc, data);
                LOGE("Kee AceContainer::InitializeFrontend 18");
            } else {
                LOGE("Kee AceContainer::InitializeFrontend Container pageProfile_ = %{public}s", pageProfile_.c_str());
                frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
                auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
                auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
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
            }
        } else {
            frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
            return;
        }
    } else {
        LOGE("Frontend type not supported");
        EventReport::SendAppStartException(AppStartExcepType::FRONTEND_TYPE_ERR);
        return;
    }
    LOGE("Kee AceContainer::InitializeFrontend 1");
    ACE_DCHECK(frontend_);
    LOGE("Kee AceContainer::InitializeFrontend 2");
    auto abilityInfo = abilityInfo_.lock();
    LOGE("Kee AceContainer::InitializeFrontend 3");
    std::shared_ptr<AppExecFwk::AbilityInfo> info = aceAbility ? aceAbility->GetAbilityInfo() : abilityInfo;
    LOGE("Kee AceContainer::InitializeFrontend 4");
    if (info && info->isLauncherAbility) {
        LOGE("Kee AceContainer::InitializeFrontend 5");
        frontend_->DisallowPopLastPage();
    }
    LOGE("Kee AceContainer::InitializeFrontend 6");
    if (frontend_) {
        LOGE("Kee AceContainer::InitializeFrontend 7");
        frontend_->Initialize(type_, taskExecutor_);
    } else {
        LOGE("Kee AceContainer::InitializeFrontend 8");
    }
    LOGE("Kee AceContainer::InitializeFrontend 9");
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, nullptr);
    auto aceContainer = AceType::DynamicCast<AceContainer>(container);
    return aceContainer;
}

bool AceContainer::OnBackPressed(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, false);
    // When the container is for menu, it need close the menu first.
    if (container->IsSubContainer()) {
        SubwindowManager::GetInstance()->CloseMenu();
        return true;
    }
    ContainerScope scope(instanceId);
    auto baseContext = container->GetPipelineContext();
    auto contextNG = DynamicCast<NG::PipelineContext>(baseContext);
    if (contextNG) {
        return contextNG->OnBackPressed();
    }
    auto context = DynamicCast<PipelineContext>(baseContext);
    CHECK_NULL_RETURN_NOLOG(context, false);
    if (context->PopPageStackOverlay()) {
        return true;
    }
    return context->CallRouterBackToPopPage();
}

void AceContainer::OnShow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (!container->UpdateState(Frontend::State::ON_SHOW)) {
        return;
    }
    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    frontend->UpdateState(Frontend::State::ON_SHOW);
                    frontend->OnShow();
                }
            },
            TaskExecutor::TaskType::JS);
    }

    taskExecutor->PostTask(
        [container]() {
            std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap;
            container->GetCardFrontendMap(cardFrontendMap);
            for (const auto& [_, weakCardFront] : cardFrontendMap) {
                auto cardFront = weakCardFront.Upgrade();
                if (!cardFront) {
                    LOGE("cardFront is null");
                    continue;
                }
                cardFront->OnShow();
            }
            auto pipelineBase = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineBase);
            pipelineBase->OnShow();
            pipelineBase->SetForegroundCalled(true);
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnHide(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (!container->UpdateState(Frontend::State::ON_HIDE)) {
        return;
    }
    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    frontend->UpdateState(Frontend::State::ON_HIDE);
                    frontend->OnHide();
                    frontend->TriggerGarbageCollection();
                }
            },
            TaskExecutor::TaskType::JS);
    }

    taskExecutor->PostTask(
        [container]() {
            auto taskExecutor = container->GetTaskExecutor();
            std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap;
            container->GetCardFrontendMap(cardFrontendMap);
            for (const auto& [_, weakCardFront] : cardFrontendMap) {
                auto cardFront = weakCardFront.Upgrade();
                if (!cardFront) {
                    LOGE("cardFront is null");
                    continue;
                }
                cardFront->OnHide();
                if (taskExecutor) {
                    taskExecutor->PostTask(
                        [cardFront]() { cardFront->TriggerGarbageCollection(); }, TaskExecutor::TaskType::JS);
                }
            }
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->OnHide();
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnActive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    frontend->UpdateState(Frontend::State::ON_ACTIVE);
                    frontend->OnActive();
                }
            },
            TaskExecutor::TaskType::JS);
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
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
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    frontend->UpdateState(Frontend::State::ON_INACTIVE);
                    frontend->OnInactive();
                }
            },
            TaskExecutor::TaskType::JS);
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnInactive failed.");
                return;
            }
            pipelineContext->WindowFocus(false);
        },
        TaskExecutor::TaskType::UI);
}

void AceContainer::OnNewWant(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnNewWant(data);
}

bool AceContainer::OnStartContinuation(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    return front->OnStartContinuation();
}

std::string AceContainer::OnSaveData(int32_t instanceId)
{
    std::string result = "false";
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, result);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, result);
    front->OnSaveData(result);
    return result;
}

bool AceContainer::OnRestoreData(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    return front->OnRestoreData(data);
}

void AceContainer::OnCompleteContinuation(int32_t instanceId, int result)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnCompleteContinuation(result);
}

void AceContainer::OnRemoteTerminated(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnRemoteTerminated();
}

void AceContainer::OnConfigurationUpdated(int32_t instanceId, const std::string& configuration)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnConfigurationUpdated(configuration);
}

void AceContainer::OnNewRequest(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID_NOLOG(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID_NOLOG(front);
    front->OnNewRequest(data);
}

void AceContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();

    // pipelineContext_->GetTaskExecutor()->PostTask(
    //     []() {
    //         LOGE("Kee TaskExecutor::TaskType::UI");
    //     },
    //     TaskExecutor::TaskType::UI);

    // pipelineContext_->GetTaskExecutor()->PostTask(
    //     []() {
    //         LOGE("Kee TaskExecutor::TaskType::JS");
    //     },
    //     TaskExecutor::TaskType::JS);

    // pipelineContext_->GetTaskExecutor()->PostTask(
    //     []() {
    //         LOGE("Kee TaskExecutor::TaskType::PLATFORM");
    //     },
    //     TaskExecutor::TaskType::PLATFORM);

    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto&& touchEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const TouchEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context, event, markProcess]() {
                context->OnTouchEvent(event);
                CHECK_NULL_VOID_NOLOG(markProcess);
                markProcess();
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
                CHECK_NULL_VOID_NOLOG(markProcess);
                markProcess();
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
                CHECK_NULL_VOID_NOLOG(markProcess);
                markProcess();
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

    auto&& viewPositionChangeCallback = [context = pipelineContext_, id = instanceId_](int32_t posX, int32_t posY) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("ViewPositionChangeCallback(%d, %d)", posX, posY);
        context->GetTaskExecutor()->PostTask(
            [context, posX, posY]() { context->OnSurfacePositionChanged(posX, posY); }, TaskExecutor::TaskType::UI);
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
}

void AceContainer::CreateContainer(int32_t instanceId, FrontendType type, const std::string& instanceName,
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool useNewPipeline)
{
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(
        instanceId, type, aceAbility, std::move(callback), useCurrentEventRunner, useNewPipeline);
    AceEngine::Get().AddContainer(instanceId, aceContainer);
    ConnectServerManager::Get().SetDebugMode();
    HdcRegister::Get().StartHdcRegister(instanceId);
    aceContainer->Initialize();
    ContainerScope scope(instanceId);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }

    auto jsFront = AceType::DynamicCast<JsFrontend>(front);
    CHECK_NULL_VOID_NOLOG(jsFront);
    jsFront->SetInstanceName(instanceName);
}

void AceContainer::DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
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
    auto removeContainerTask = [instanceId, destroyCallback] {
        LOGI("Remove on Platform thread...");
        EngineHelper::RemoveEngine(instanceId);
        AceEngine::Get().RemoveContainer(instanceId);
        ConnectServerManager::Get().RemoveInstance(instanceId);
        CHECK_NULL_VOID_NOLOG(destroyCallback);
        destroyCallback();
    };
    if (container->GetSettings().usePlatformAsUIThread) {
        removeContainerTask();
    } else {
        taskExecutor->PostTask(removeContainerTask, TaskExecutor::TaskType::PLATFORM);
    }
}

void AceContainer::SetView(AceView* view, double density, int32_t width, int32_t height,
    sptr<OHOS::Rosen::Window> rsWindow, UIEnvCallback callback)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
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
    AceContainer::SetUIWindow(view->GetInstanceId(), rsWindow);
    container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId(), callback);
}

void AceContainer::SetViewNew(
    AceView* view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window> rsWindow)
{
#ifdef ENABLE_ROSEN_BACKEND
    LOGE("Kee AceContainer::SetViewNew view = %{public}p density = %{public}lf width = %{public}d height = %{public}d rsWindow = %{public}p", view, density, width, height, rsWindow.GetRefPtr());
    CHECK_NULL_VOID(view);
    LOGE("Kee AceContainer::SetViewNew view GetInstanceId = %{public}d", view->GetInstanceId());
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    AceContainer::SetUIWindow(view->GetInstanceId(), rsWindow);

    std::unique_ptr<Window> window;
    if (container->isCardContainer_) {
        auto formRenderWindow = std::make_unique<FormRenderWindow>(taskExecutor, view->GetInstanceId());
        formSurfaceNode_ = formRenderWindow->GetRSSurfaceNode();
        window = std::move(formRenderWindow);
        window->SetIsEtsCard(container->isCardContainer_);
        LOGE("Kee AceContainer::SetViewNew isCardContainer_ AttachView window = %{public}p", window.get());
        container->AttachView(std::move(window), view, density, width, height, view->GetInstanceId(), nullptr); // 为了避免contentImpl->Init()的crash
    } else {
        window = std::make_unique<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
        window->SetIsEtsCard(container->isCardContainer_);
        LOGE("Kee AceContainer::SetViewNew AttachView window = %{public}p", window.get());
        container->AttachView(std::move(window), view, density, width, height, rsWindow->GetWindowId(), nullptr);
    }
#endif
}

void AceContainer::SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window> uiWindow)
{
    CHECK_NULL_VOID_NOLOG(uiWindow);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID_NOLOG(container);
    container->SetUIWindowInner(uiWindow);
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindow(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN_NOLOG(container, nullptr);
    return container->GetUIWindowInner();
}

OHOS::AppExecFwk::Ability* AceContainer::GetAbility(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN_NOLOG(container, nullptr);
    return container->GetAbilityInner().lock().get();
}

bool AceContainer::RunPage(int32_t instanceId, int32_t pageId, const std::string& content, const std::string& params)
{
    LOGE("Kee AceContainer::RunPage:%{public}d pageId:%{public}d content:%{public}s params:%{public}s", instanceId, pageId, content.c_str(), params.c_str());
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN_NOLOG(front, false);
    LOGD("RunPage content=[%{private}s]", content.c_str());
    front->RunPage(pageId, content, params);
    return true;
}

bool AceContainer::PushPage(int32_t instanceId, const std::string& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN_NOLOG(front, false);
    front->PushPage(content, params);
    return true;
}

bool AceContainer::UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, false);
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN_NOLOG(context, false);
    return context->CallRouterBackToPopPage();
}

void AceContainer::SetHapPath(const std::string& hapPath)
{
    if (hapPath.empty()) {
        LOGI("SetHapPath, Use .index to load resource");
        return;
    }
    LOGI("SetHapPath, Use hap path to load resource");
    webHapPath_ = hapPath;
    resourceInfo_.SetHapPath(hapPath);
    SystemProperties::SetUnZipHap(false);
}

void AceContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{
    return;
}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    auto front = GetFrontend();
    CHECK_NULL_VOID(front);
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

    CHECK_NULL_RETURN_NOLOG(pipelineContext_, false);
    pipelineContext_->Dump(params);
    return true;
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
            CHECK_NULL_VOID_NOLOG(sp);
            sp->DumpHeapSnapshot(isPrivate);
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::SetLocalStorage(NativeReference* storage, NativeReference* context)
{
    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_), storage, context, id = instanceId_] {
            auto sp = frontend.Upgrade();
            CHECK_NULL_VOID_NOLOG(sp);
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(sp);
            auto jsEngine = declarativeFrontend->GetJsEngine();
            if (context) {
                jsEngine->SetContext(id, context);
            }
            if (storage) {
                jsEngine->SetLocalStorage(id, storage);
            }
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::string& hapPath,
    const std::vector<std::string>& paths)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID_NOLOG(container);
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
    CHECK_NULL_VOID_NOLOG(flutterAssetManager);
    if (!hapPath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<HapAssetProvider>();
        if (assetProvider->Initialize(hapPath, paths)) {
            LOGI("Push AssetProvider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }
    if (!packagePath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
        if (assetProvider->Initialize(packagePath, paths)) {
            LOGI("Push AssetProvider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    }
}

void AceContainer::AddLibPath(int32_t instanceId, const std::vector<std::string>& libPath)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID_NOLOG(container);
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
    CHECK_NULL_VOID_NOLOG(flutterAssetManager);
    flutterAssetManager->SetLibPath("default", libPath);
}

void AceContainer::AttachView(std::unique_ptr<Window> window, AceView* view, double density, int32_t width,
    int32_t height, int32_t windowId, UIEnvCallback callback)
{
    LOGE("Kee AceContainer::AttachView window = %{public}p windowId = %{public}d", window.get(), windowId);
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    LOGE("Kee AceContainer::AttachView instanceId = %{public}d", instanceId);
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
        LOGE("Kee AceContainer::AttachView InitializeFrontend");
        InitializeFrontend();
        auto front = GetFrontend();
        if (front) {
            LOGE("Kee AceContainer::AttachView front SetAssetManager");
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
            front->SetAssetManager(assetManager_);
        }
    } else if (type_ != FrontendType::JS_CARD) {
        aceView_->SetCreateTime(createTime_);
    }
    resRegister_ = aceView_->GetPlatformResRegister();

    taskExecutor_->PostTask(
    []() {
        LOGE("Kee TaskExecutor::TaskType::UI");
    },
    TaskExecutor::TaskType::UI);

    taskExecutor_->PostTask(
        []() {
            LOGE("Kee TaskExecutor::TaskType::JS");
        },
        TaskExecutor::TaskType::JS);

    taskExecutor_->PostTask(
        []() {
            LOGE("Kee TaskExecutor::TaskType::PLATFORM");
        },
        TaskExecutor::TaskType::PLATFORM);

    if (useNewPipeline_) {
        LOGE("Kee New pipeline version creating... window = %{public}p, instanceId = %{public}d", window.get(), instanceId);
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<NG::TextFieldManagerNG>());
    } else {
        LOGE("Kee Old pipeline version creating... window = %{public}p, instanceId = %{public}d", window.get(), instanceId);
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    }

    if (isCardContainer_) {
        LOGE("Kee AttachView set width = 400 height = 400");
        width = 400;
        height = 400;
        if (frontend_) {
            LOGE("Kee AceContainer::AttachView 1 frontend_");
        } else {
            LOGE("Kee AceContainer::AttachView 2 frontend_ = nullptr");
        }
        auto cardFrontend = AceType::DynamicCast<CardFrontendDeclarative>(frontend_);
        if (cardFrontend) {
            LOGE("Kee AceContainer::AttachView 3 cardFrontend");
            // cardFrontend->Initialize(type_, taskExecutor_);
            cardFrontend->SetLoadCardCallBack(WeakPtr<PipelineBase>(pipelineContext_));
        } else {
            LOGE("Kee AceContainer::AttachView 4 cardFrontend nullptr");
        }
    }

    LOGE("Kee AttachView isCardContainer_ = %{public}d, density = %{public}lf, width = %{public}d, height = %{public}d", isCardContainer_, density, width, height);
    pipelineContext_->SetIsEtsCard(isCardContainer_);

    pipelineContext_->SetRootSize(density, width, height);
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowId(windowId); // In Card pipeline, windowId = container instanceId for temp
    pipelineContext_->SetWindowModal(windowModal_);
    if (isCardContainer_) {
        LOGE("Kee AttachView pipelineContext->SetDrawDelegate ets card");
        pipelineContext_->SetDrawDelegate(std::move(PipelineBase::gDelegate));
    }

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(pipelineContext_);
    if (pipelineContext) {
        pipelineContext->SetDrawDelegate(aceView_->GetDrawDelegate());
        if (isSubContainer_) {
            pipelineContext->SetIsSubPipeline(true);
        }
    }
    InitWindowCallback();
    InitializeCallback();

    auto&& finishEventHandler = [weak = WeakClaim(this), instanceId] {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container)] {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnFinish();
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetFinishEventHandler(finishEventHandler);

    auto&& startAbilityHandler = [weak = WeakClaim(this), instanceId](const std::string& address) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), address]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbility(address);
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetStartAbilityHandler(startAbilityHandler);

    auto&& setStatusBarEventHandler = [weak = WeakClaim(this), instanceId](const Color& color) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak, color = color.GetValue()]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                if (container->platformEventCallback_) {
                    container->platformEventCallback_->OnStatusBarBgColorChanged(color);
                }
            },
            TaskExecutor::TaskType::PLATFORM);
    };
    pipelineContext_->SetStatusBarEventHandler(setStatusBarEventHandler);
    if (GetSettings().usePlatformAsUIThread) {
        FrameReport::GetInstance().Init();
    } else {
        taskExecutor_->PostTask([] { FrameReport::GetInstance().Init(); }, TaskExecutor::TaskType::UI);
    }

    // Load custom style at UI thread before frontend attach, for loading style before building tree.
    auto initThemeManagerTask = [pipelineContext = pipelineContext_, assetManager = assetManager_,
                                    colorScheme = colorScheme_, resourceInfo = resourceInfo_]() {
        ACE_SCOPED_TRACE("OHOS::LoadThemes()");
        LOGD("UIContent load theme");
        ThemeConstants::InitDeviceType();
        auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
        pipelineContext->SetThemeManager(themeManager);
        themeManager->InitResource(resourceInfo);
        themeManager->SetColorScheme(colorScheme);
        themeManager->LoadCustomTheme(assetManager);
        themeManager->LoadResourceThemes();
    };

    auto setupRootElementTask = [context = pipelineContext_, callback, isSubContainer = isSubContainer_]() {
        if (callback != nullptr) {
            callback(AceType::DynamicCast<PipelineContext>(context));
        }
        if (!isSubContainer) {
            LOGE("Kee AceContainer::AttachView context->SetupRootElement");
            context->SetupRootElement();
        }
    };
    if (GetSettings().usePlatformAsUIThread) {
        LOGE("Kee AceContainer::AttachView usePlatformAsUIThread");
        initThemeManagerTask();
        setupRootElementTask();
    } else {
        LOGE("Kee AceContainer::AttachView setupRootElementTask UI");
        taskExecutor_->PostTask(initThemeManagerTask, TaskExecutor::TaskType::UI);
        taskExecutor_->PostTask(setupRootElementTask, TaskExecutor::TaskType::UI);
    }
    LOGE("Kee AttachView aceView_->Launch");
    aceView_->Launch();

    if (!isSubContainer_) {
        // Only MainWindow instance in FA model will be registered to watch dog.
        if (!GetSettings().usingSharedRuntime && !AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint()) {
            AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_, GetSettings().useUIAsJSThread);
        }
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
    pipelineContext_->SetPostRTTaskCallBack([](std::function<void()>&& task) {
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
    CHECK_NULL_VOID_NOLOG(container);
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFontScale(fontScale);
}

void AceContainer::SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID_NOLOG(container);
    ContainerScope scope(instanceId);
    container->SetWindowModal(windowModal);
    container->SetColorScheme(colorScheme);
}

void AceContainer::SetDialogCallback(int32_t instanceId, FrontendDialogCallback callback)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID_NOLOG(container);
    auto front = container->GetFrontend();
    if (front && front->GetType() == FrontendType::JS) {
        front->SetDialogCallback(callback);
    }
}

std::string AceContainer::RestoreRouterStack(int32_t instanceId, const std::string& contentInfo)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, "");
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN_NOLOG(front, "");
    return front->RestoreRouterStack(contentInfo);
}

std::string AceContainer::GetContentInfo(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN_NOLOG(container, "");
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN_NOLOG(front, "");
    return front->GetContentInfo();
}

void AceContainer::SetWindowPos(int32_t left, int32_t top)
{
    CHECK_NULL_VOID_NOLOG(frontend_);
    auto accessibilityManager = frontend_->GetAccessibilityManager();
    CHECK_NULL_VOID_NOLOG(accessibilityManager);
    accessibilityManager->SetWindowPos(left, top, windowId_);
}

void AceContainer::InitializeSubContainer(int32_t parentContainerId)
{
    auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
    CHECK_NULL_VOID(parentContainer);
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
    if (windowModal_ == WindowModal::CONTAINER_MODAL && pipelineContext_) {
        auto& windowManager = pipelineContext_->GetWindowManager();
        std::shared_ptr<AppExecFwk::AbilityInfo> info = abilityInfo_.lock();
        if (info != nullptr) {
            windowManager->SetAppLabelId(info->labelId);
            windowManager->SetAppIconId(info->iconId);
        }
        windowManager->SetWindowMinimizeCallBack([window = uiWindow_]() { window->Minimize(); });
        windowManager->SetWindowMaximizeCallBack([window = uiWindow_]() { window->Maximize(); });
        windowManager->SetWindowRecoverCallBack([window = uiWindow_]() { window->Recover(); });
        windowManager->SetWindowCloseCallBack([window = uiWindow_]() { window->Close(); });
        windowManager->SetWindowStartMoveCallBack([window = uiWindow_]() { window->StartMove(); });
        windowManager->SetWindowSplitCallBack(
            [window = uiWindow_]() { window->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY); });
        windowManager->SetWindowGetModeCallBack(
            [window = uiWindow_]() -> WindowMode { return static_cast<WindowMode>(window->GetMode()); });
    }

    pipelineContext_->SetGetWindowRectImpl([window = uiWindow_]() -> Rect {
        Rect rect;
        CHECK_NULL_RETURN_NOLOG(window, rect);
        auto windowRect = window->GetRect();
        rect.SetRect(windowRect.posX_, windowRect.posY_, windowRect.width_, windowRect.height_);
        return rect;
    });
}

std::shared_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    auto context = runtimeContext_.lock();
    CHECK_NULL_RETURN(context, nullptr);
    return context->CreateModuleContext(bundle, module);
}

void AceContainer::UpdateConfiguration(
    const std::string& colorMode, const std::string& deviceAccess, const std::string& languageTag)
{
    if (colorMode.empty() && deviceAccess.empty() && languageTag.empty()) {
        LOGW("AceContainer::OnConfigurationUpdated param is empty");
        return;
    }
    CHECK_NULL_VOID(pipelineContext_);
    auto themeManager = pipelineContext_->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
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
    NotifyConfigurationChange(!deviceAccess.empty());
}

void AceContainer::NotifyConfigurationChange(bool needReloadTransition)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [instanceId = instanceId_, weak = WeakClaim(this), needReloadTransition]() {
            ContainerScope scope(instanceId);
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto frontend = container->GetFrontend();
            if (frontend) {
                LOGI("AceContainer::UpdateConfiguration frontend MarkNeedUpdate");
                frontend->FlushReload();
            }
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [instanceId, weak, needReloadTransition]() {
                    ContainerScope scope(instanceId);
                    auto container = weak.Upgrade();
                    CHECK_NULL_VOID(container);
                    auto pipeline = container->GetPipelineContext();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->NotifyConfigurationChange();
                    pipeline->FlushReload();
                    if (needReloadTransition) {
                        // reload transition animation
                        pipeline->FlushReloadTransition();
                    }
                },
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::JS);
}

void AceContainer::SetToken(sptr<IRemoteObject>& token)
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    if (token) {
        token_ = token;
    }
}

sptr<IRemoteObject> AceContainer::GetToken()
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    if (token_) {
        return token_;
    }
    LOGE("fail to get Token");
    return nullptr;
}

std::shared_ptr<void> AceContainer::GetFormSurfaceNode()
{
    if (!formSurfaceNode_) {
        LOGE("Kee form surface node is null");
        return nullptr;
    }
    return formSurfaceNode_;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_HotReloadPage()
{
    AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
        auto ace = AceType::DynamicCast<AceContainer>(container);
        if (ace) {
            ace->NotifyConfigurationChange(true);
        }
        LOGI("frontend rebuild finished");
    });
}

} // namespace OHOS::Ace::Platform
