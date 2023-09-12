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

#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"

#include <memory>

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/thread_checker.h"
#include "core/components/navigator/navigator_component.h"
#include "frameworks/bridge/card_frontend/form_frontend_delegate_declarative.h"
namespace OHOS::Ace {
namespace {

/*
 * NOTE:
 * This function is needed to copy the values from BaseEventInfo
 * It is observed, that the owner of BaseEventInfo will delete the pointer before it is ultimately
 * processed by the EventMarker callback. In order to avoid this, a copy of all data needs to be made.
 */
std::shared_ptr<BaseEventInfo> CopyEventInfo(const BaseEventInfo& info)
{
    const auto* touchInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(&info);
    if (touchInfo != nullptr) {
        return std::make_shared<TouchEventInfo>(*touchInfo);
    }

    const auto* dragStartInfo = TypeInfoHelper::DynamicCast<DragStartInfo>(&info);
    if (dragStartInfo != nullptr) {
        return std::make_shared<DragStartInfo>(*dragStartInfo);
    }

    const auto* dragUpdateInfo = TypeInfoHelper::DynamicCast<DragUpdateInfo>(&info);
    if (dragUpdateInfo != nullptr) {
        return std::make_shared<DragUpdateInfo>(*dragUpdateInfo);
    }

    const auto* dragEndInfo = TypeInfoHelper::DynamicCast<DragEndInfo>(&info);
    if (dragEndInfo != nullptr) {
        return std::make_shared<DragEndInfo>(*dragEndInfo);
    }

    const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(&info);
    if (clickInfo != nullptr) {
        return std::make_shared<ClickInfo>(*clickInfo);
    }
    return nullptr;
}

void TouchInfoToString(const BaseEventInfo& info, std::string& eventParam)
{
    eventParam.append("{\"touches\":[{");
    const auto touchInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(&info);
    if (touchInfo) {
        auto touchList = touchInfo->GetTouches();
        for (const auto& location : touchList) {
            auto globalLocation = location.GetGlobalLocation();
            eventParam.append("\"globalX\":")
                .append(std::to_string(globalLocation.GetX()))
                .append(",\"globalY\":")
                .append(std::to_string(globalLocation.GetY()))
                .append(",");
            auto localLocation = location.GetLocalLocation();
            eventParam.append("\"localX\":")
                .append(std::to_string(localLocation.GetX()))
                .append(",\"localY\":")
                .append(std::to_string(localLocation.GetY()))
                .append(",");
            eventParam.append("\"size\":").append(std::to_string(location.GetSize())).append(",");
        }
        if (eventParam.back() == ',') {
            eventParam.pop_back();
        }
        eventParam.append("}],\"changedTouches\":[{");
        auto changeTouch = touchInfo->GetChangedTouches();
        for (const auto& change : changeTouch) {
            auto globalLocation = change.GetGlobalLocation();
            eventParam.append("\"globalX\":")
                .append(std::to_string(globalLocation.GetX()))
                .append(",\"globalY\":")
                .append(std::to_string(globalLocation.GetY()))
                .append(",");
            auto localLocation = change.GetLocalLocation();
            eventParam.append("\"localX\":")
                .append(std::to_string(localLocation.GetX()))
                .append(",\"localY\":")
                .append(std::to_string(localLocation.GetY()))
                .append(",");
            eventParam.append("\"size\":").append(std::to_string(change.GetSize())).append(",");
        }
        if (eventParam.back() == ',') {
            eventParam.pop_back();
        }
    }
    eventParam.append("}]}");
}

void MouseInfoToString(const BaseEventInfo& info, std::string& eventParam)
{
    const auto mouseInfo = TypeInfoHelper::DynamicCast<MouseEventInfo>(&info);
    eventParam.append("{\"mouse\":{");
    if (mouseInfo) {
        auto globalMouse = mouseInfo->GetGlobalMouse();
        eventParam.append("\"globalX\":")
            .append(std::to_string(globalMouse.x))
            .append(",\"globalY\":")
            .append(std::to_string(globalMouse.y))
            .append(",\"globalZ\":")
            .append(std::to_string(globalMouse.z))
            .append(",\"localX\":")
            .append(std::to_string(globalMouse.x))
            .append(",\"localY\":")
            .append(std::to_string(globalMouse.y))
            .append(",\"localZ\":")
            .append(std::to_string(globalMouse.z))
            .append(",\"deltaX\":")
            .append(std::to_string(globalMouse.deltaX))
            .append(",\"deltaY\":")
            .append(std::to_string(globalMouse.deltaY))
            .append(",\"deltaZ\":")
            .append(std::to_string(globalMouse.deltaZ))
            .append(",\"scrollX\":")
            .append(std::to_string(globalMouse.scrollX))
            .append(",\"scrollY\":")
            .append(std::to_string(globalMouse.scrollY))
            .append(",\"scrollZ\":")
            .append(std::to_string(globalMouse.scrollZ))
            .append(",\"action\":")
            .append(std::to_string(static_cast<int32_t>(globalMouse.action)))
            .append(",\"button\":")
            .append(std::to_string(static_cast<int32_t>(globalMouse.button)))
            .append(",\"pressedButtons\":")
            .append(std::to_string(globalMouse.pressedButtons));
    }
    eventParam.append("}}");
}

void SwipeInfoToString(const BaseEventInfo& info, std::string& eventParam)
{
    const auto& swipeInfo = TypeInfoHelper::DynamicCast<SwipeEventInfo>(&info);
    eventParam = swipeInfo->ToJsonParamInfo();
}

} // namespace

DeclarativeFrontend::~DeclarativeFrontend() noexcept
{
    LOG_DESTROY();
}

void DeclarativeFrontend::Destroy()
{
    CHECK_RUN_ON(JS);
    LOGI("DeclarativeFrontend Destroy begin.");
    // To guarantee the jsEngine_ and delegate_ released in js thread
    delegate_.Reset();
    handler_.Reset();
    if (jsEngine_) {
        jsEngine_->Destroy();
    }
    jsEngine_.Reset();
    LOGI("DeclarativeFrontend Destroy end.");
}

bool DeclarativeFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    LOGD("DeclarativeFrontend initialize begin.");
    type_ = type;
    taskExecutor_ = taskExecutor;
    ACE_DCHECK(type_ == FrontendType::DECLARATIVE_JS);
    InitializeFrontendDelegate(taskExecutor);

    bool needPostJsTask = true;
    auto container = Container::Current();
    if (container) {
        const auto& setting = container->GetSettings();
        needPostJsTask = !(setting.usePlatformAsUIThread && setting.useUIAsJSThread);
    }
    auto initJSEngineTask = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_), delegate = delegate_] {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->Initialize(delegate);
    };
    if (needPostJsTask) {
        taskExecutor->PostTask(initJSEngineTask, TaskExecutor::TaskType::JS);
    } else {
        initJSEngineTask();
    }

    LOGD("DeclarativeFrontend initialize end.");
    return true;
}

void DeclarativeFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    LOGD("DeclarativeFrontend AttachPipelineContext.");
    if (!delegate_) {
        return;
    }
    handler_ = AceType::MakeRefPtr<DeclarativeEventHandler>(delegate_);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(context);
    if (pipelineContext) {
        pipelineContext->RegisterEventHandler(handler_);
    }
    delegate_->AttachPipelineContext(context);
}

void DeclarativeFrontend::AttachSubPipelineContext(const RefPtr<PipelineBase>& context)
{
    LOGI("DeclarativeFrontend AttachSubPipelineContext.");
    if (!context) {
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(context);
    if (pipelineContext) {
        pipelineContext->RegisterEventHandler(handler_);
    }
    if (!delegate_) {
        return;
    }
    delegate_->AttachSubPipelineContext(context);
}

void DeclarativeFrontend::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    LOGI("DeclarativeFrontend SetAssetManager.");
    if (delegate_) {
        delegate_->SetAssetManager(assetManager);
    }
}

void DeclarativeFrontend::InitializeFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor)
{
    const auto& loadCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& url,
                                   const RefPtr<Framework::JsAcePage>& jsPage, bool isMainPage) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->LoadJs(url, jsPage, isMainPage);
    };

    const auto& setPluginMessageTransferCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                       const RefPtr<JsMessageDispatcher>& dispatcher) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->SetJsMessageDispatcher(dispatcher);
    };

    const auto& asyncEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const std::string& eventId, const std::string& param) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireAsyncEvent(eventId, param);
    };

    const auto& syncEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                        const std::string& eventId, const std::string& param) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireSyncEvent(eventId, param);
    };

    const auto& updatePageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const RefPtr<Framework::JsAcePage>& jsPage) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->UpdateRunningPage(jsPage);
        jsEngine->UpdateStagingPage(jsPage);
    };

    const auto& resetStagingPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->ResetStagingPage();
    };

    const auto& destroyPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](int32_t pageId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DestroyPageInstance(pageId);
    };

    const auto& destroyApplicationCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                 const std::string& packageName) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DestroyApplication(packageName);
    };

    const auto& updateApplicationStateCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                     const std::string& packageName, Frontend::State state) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->UpdateApplicationState(packageName, state);
    };

    const auto& onWindowDisplayModeChangedCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                         bool isShownInMultiWindow, const std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnWindowDisplayModeChanged(isShownInMultiWindow, data);
    };

    const auto& onSaveAbilityStateCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            LOGE("the js engine is nullptr");
            return;
        }
        jsEngine->OnSaveAbilityState(data);
    };
    const auto& onRestoreAbilityStateCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                    const std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            LOGE("the js engine is nullptr");
            return;
        }
        jsEngine->OnRestoreAbilityState(data);
    };

    const auto& onNewWantCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            LOGE("the js engine is nullptr");
            return;
        }
        jsEngine->OnNewWant(data);
    };

    const auto& onConfigurationUpdatedCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                     const std::string& data) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnConfigurationUpdated(data);
    };

    const auto& timerCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                    const std::string& callbackId, const std::string& delay, bool isInterval) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->TimerCallback(callbackId, delay, isInterval);
    };

    const auto& mediaQueryCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const std::string& callbackId, const std::string& args) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->MediaQueryCallback(callbackId, args);
    };

    const auto& layoutInspectorCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                              const std::string& componentId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->LayoutInspectorCallback(componentId);
    };

    const auto& drawInspectorCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                            const std::string& componentId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DrawInspectorCallback(componentId);
    };

    const auto& requestAnimationCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                               const std::string& callbackId, uint64_t timeStamp) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->RequestAnimationCallback(callbackId, timeStamp);
    };

    const auto& jsCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                 const std::string& callbackId, const std::string& args) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->JsCallback(callbackId, args);
    };

    const auto& onMemoryLevelCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const int32_t level) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnMemoryLevel(level);
    };

    const auto& onStartContinuationCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() -> bool {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->OnStartContinuation();
    };
    const auto& onCompleteContinuationCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](int32_t code) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnCompleteContinuation(code);
    };
    const auto& onRemoteTerminatedCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnRemoteTerminated();
    };
    const auto& onSaveDataCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](std::string& savedData) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->OnSaveData(savedData);
    };
    const auto& onRestoreDataCallBack = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                            const std::string& data) -> bool {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return false;
        }
        return jsEngine->OnRestoreData(data);
    };

    const auto& externalEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                            const std::string& componentId, const uint32_t nodeId,
                                            const bool isDestroy) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireExternalEvent(componentId, nodeId, isDestroy);
    };

    if (isFormRender_) {
        LOGI("Init Form Delegate");
        delegate_ = AceType::MakeRefPtr<Framework::FormFrontendDelegateDeclarative>(taskExecutor, loadCallback,
            setPluginMessageTransferCallback, asyncEventCallback, syncEventCallback, updatePageCallback,
            resetStagingPageCallback, destroyPageCallback, destroyApplicationCallback, updateApplicationStateCallback,
            timerCallback, mediaQueryCallback, layoutInspectorCallback, drawInspectorCallback, requestAnimationCallback,
            jsCallback, onWindowDisplayModeChangedCallBack, onConfigurationUpdatedCallBack, onSaveAbilityStateCallBack,
            onRestoreAbilityStateCallBack, onNewWantCallBack, onMemoryLevelCallBack, onStartContinuationCallBack,
            onCompleteContinuationCallBack, onRemoteTerminatedCallBack, onSaveDataCallBack, onRestoreDataCallBack,
            externalEventCallback);
    } else {
        delegate_ = AceType::MakeRefPtr<Framework::FrontendDelegateDeclarative>(taskExecutor, loadCallback,
            setPluginMessageTransferCallback, asyncEventCallback, syncEventCallback, updatePageCallback,
            resetStagingPageCallback, destroyPageCallback, destroyApplicationCallback, updateApplicationStateCallback,
            timerCallback, mediaQueryCallback, layoutInspectorCallback, drawInspectorCallback, requestAnimationCallback,
            jsCallback, onWindowDisplayModeChangedCallBack, onConfigurationUpdatedCallBack, onSaveAbilityStateCallBack,
            onRestoreAbilityStateCallBack, onNewWantCallBack, onMemoryLevelCallBack, onStartContinuationCallBack,
            onCompleteContinuationCallBack, onRemoteTerminatedCallBack, onSaveDataCallBack, onRestoreDataCallBack,
            externalEventCallback);
    }

    if (disallowPopLastPage_) {
        delegate_->DisallowPopLastPage();
    }
    if (!jsEngine_) {
        LOGE("the js engine is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::JS_ENGINE_CREATE_ERR);
        return;
    }
    delegate_->SetGroupJsBridge(jsEngine_->GetGroupJsBridge());
    if (Container::IsCurrentUseNewPipeline()) {
        auto loadPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& url,
                                    const std::function<void(const std::string&, int32_t)>& errorCallback) {
            auto jsEngine = weakEngine.Upgrade();
            if (!jsEngine) {
                return false;
            }
            return jsEngine->LoadPageSource(url, errorCallback);
        };
        auto loadNamedRouterCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                           const std::string& namedRouter, bool isTriggeredByJs) {
            auto jsEngine = weakEngine.Upgrade();
            if (!jsEngine) {
                return false;
            }
            return jsEngine->LoadNamedRouterSource(namedRouter, isTriggeredByJs);
        };
        delegate_->InitializeRouterManager(std::move(loadPageCallback), std::move(loadNamedRouterCallback));
    }
}

void DeclarativeFrontend::RunPage(const std::string& url, const std::string& params)
{
    auto container = Container::Current();
    auto isStageModel = container ? container->IsUseStageModel() : false;
    if (!isStageModel && Container::IsCurrentUseNewPipeline()) {
        // In NG structure and fa mode, first load app.js
        auto taskExecutor = container ? container->GetTaskExecutor() : nullptr;
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weak = AceType::WeakClaim(this)]() {
                auto frontend = weak.Upgrade();
                CHECK_NULL_VOID(frontend);
                CHECK_NULL_VOID(frontend->jsEngine_);
                frontend->jsEngine_->LoadFaAppSource();
            },
            TaskExecutor::TaskType::JS);
    }

    if (delegate_) {
        if (isFormRender_) {
            auto delegate = AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
            delegate->RunCard(url, params, pageProfile_, 0);
        } else {
            delegate_->RunPage(url, params, pageProfile_);
        }
    }
}

void DeclarativeFrontend::RunPageByNamedRouter(const std::string& name)
{
    if (delegate_) {
        delegate_->RunPage(name, "", pageProfile_, true);
    }
}

void DeclarativeFrontend::ReplacePage(const std::string& url, const std::string& params)
{
    if (delegate_) {
        delegate_->Replace(url, params);
    }
}

void DeclarativeFrontend::PushPage(const std::string& url, const std::string& params)
{
    if (delegate_) {
        delegate_->Push(url, params);
    }
}

void DeclarativeFrontend::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params)
{
    if (!delegate_) {
        return;
    }
    switch (static_cast<NavigatorType>(type)) {
        case NavigatorType::PUSH:
            delegate_->Push(target, params);
            break;
        case NavigatorType::REPLACE:
            delegate_->Replace(target, params);
            break;
        case NavigatorType::BACK:
            delegate_->BackWithTarget(target, params);
            break;
        default:
            LOGE("Navigator type is invalid!");
            delegate_->BackWithTarget(target, params);
    }
}

std::string DeclarativeFrontend::GetCurrentPageUrl() const
{
    CHECK_NULL_RETURN(delegate_, "");
    return delegate_->GetCurrentPageUrl();
}

// Get the currently running JS page information in NG structure.
RefPtr<Framework::RevSourceMap> DeclarativeFrontend::GetCurrentPageSourceMap() const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetCurrentPageSourceMap();
}

// Get the currently running JS page information in NG structure.
RefPtr<Framework::RevSourceMap> DeclarativeFrontend::GetFaAppSourceMap() const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetFaAppSourceMap();
}

void DeclarativeFrontend::GetStageSourceMap(
    std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMap) const
{
    if (delegate_) {
        delegate_->GetStageSourceMap(sourceMap);
    }
}

RefPtr<NG::PageRouterManager> DeclarativeFrontend::GetPageRouterManager() const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetPageRouterManager();
}

std::string DeclarativeFrontend::RestoreRouterStack(const std::string& contentInfo)
{
    if (delegate_) {
        return delegate_->RestoreRouterStack(contentInfo);
    }
    return "";
}

std::string DeclarativeFrontend::GetContentInfo() const
{
    if (delegate_) {
        return delegate_->GetContentInfo();
    }
    return "";
}

int32_t DeclarativeFrontend::GetRouterSize() const
{
    if (delegate_) {
        return delegate_->GetStackSize();
    }
    return -1;
}

void DeclarativeFrontend::SendCallbackMessage(const std::string& callbackId, const std::string& data) const
{
    if (delegate_) {
        delegate_->OnJSCallback(callbackId, data);
    }
}

void DeclarativeFrontend::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    if (delegate_) {
        delegate_->SetJsMessageDispatcher(dispatcher);
    }
}

void DeclarativeFrontend::TransferComponentResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    if (delegate_) {
        delegate_->TransferComponentResponseData(callbackId, code, std::move(data));
    }
}

void DeclarativeFrontend::TransferJsResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    if (delegate_) {
        delegate_->TransferJsResponseData(callbackId, code, std::move(data));
    }
}

NativeValue* DeclarativeFrontend::GetContextValue()
{
    return jsEngine_->GetContextValue();
}

#if defined(PREVIEW)
void DeclarativeFrontend::TransferJsResponseDataPreview(int callbackId, int32_t code, ResponseData responseData) const
{
    delegate_->TransferJsResponseDataPreview(callbackId, code, responseData);
}

RefPtr<Component> DeclarativeFrontend::GetNewComponentWithJsCode(const std::string& jsCode, const std::string& viewID)
{
    if (jsEngine_) {
        return jsEngine_->GetNewComponentWithJsCode(jsCode, viewID);
    }
    return nullptr;
}
#endif

void DeclarativeFrontend::TransferJsPluginGetError(int callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    if (delegate_) {
        delegate_->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
    }
}

void DeclarativeFrontend::TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    if (delegate_) {
        delegate_->TransferJsEventData(callbackId, code, std::move(data));
    }
}

void DeclarativeFrontend::LoadPluginJsCode(std::string&& jsCode) const
{
    if (delegate_) {
        delegate_->LoadPluginJsCode(std::move(jsCode));
    }
}

void DeclarativeFrontend::LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const
{
    if (delegate_) {
        delegate_->LoadPluginJsByteCode(std::move(jsCode), std::move(jsCodeLen));
    }
}

void DeclarativeFrontend::UpdateState(Frontend::State state)
{
    if (!delegate_ || state == Frontend::State::ON_CREATE) {
        return;
    }
    bool needPostJsTask = true;
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    const auto& setting = container->GetSettings();
    needPostJsTask = !(setting.usePlatformAsUIThread && setting.useUIAsJSThread);
    if (needPostJsTask) {
        delegate_->UpdateApplicationState(delegate_->GetAppID(), state);
        return;
    }
    if (jsEngine_) {
        jsEngine_->UpdateApplicationState(delegate_->GetAppID(), state);
    }
}

void DeclarativeFrontend::OnWindowDisplayModeChanged(bool isShownInMultiWindow, const std::string& data)
{
    delegate_->OnWindowDisplayModeChanged(isShownInMultiWindow, data);
}

void DeclarativeFrontend::OnSaveAbilityState(std::string& data)
{
    if (delegate_) {
        delegate_->OnSaveAbilityState(data);
    }
}

void DeclarativeFrontend::OnRestoreAbilityState(const std::string& data)
{
    if (delegate_) {
        delegate_->OnRestoreAbilityState(data);
    }
}

void DeclarativeFrontend::OnNewWant(const std::string& data)
{
    if (delegate_) {
        delegate_->OnNewWant(data);
    }
}

RefPtr<AccessibilityManager> DeclarativeFrontend::GetAccessibilityManager() const
{
    if (!delegate_) {
        LOGE("GetAccessibilityManager delegate is null");
        return nullptr;
    }
    return delegate_->GetJSAccessibilityManager();
}

WindowConfig& DeclarativeFrontend::GetWindowConfig()
{
    if (!delegate_) {
        static WindowConfig windowConfig;
        LOGW("delegate is null, return default config");
        return windowConfig;
    }
    return delegate_->GetWindowConfig();
}

bool DeclarativeFrontend::OnBackPressed()
{
    if (!delegate_) {
        LOGW("delegate is null, return false");
        return false;
    }
    return delegate_->OnPageBackPress();
}

void DeclarativeFrontend::OnShow()
{
    if (delegate_) {
        foregroundFrontend_ = true;
        delegate_->OnForeground();
    }
}

void DeclarativeFrontend::OnHide()
{
    if (delegate_) {
        delegate_->OnBackGround();
        foregroundFrontend_ = false;
    }
}

void DeclarativeFrontend::OnConfigurationUpdated(const std::string& data)
{
    if (delegate_) {
        delegate_->OnConfigurationUpdated(data);
    }
}

void DeclarativeFrontend::OnActive()
{
    if (delegate_) {
        foregroundFrontend_ = true;
        delegate_->InitializeAccessibilityCallback();
    }
}

void DeclarativeFrontend::OnInactive() {}

bool DeclarativeFrontend::OnStartContinuation()
{
    if (!delegate_) {
        LOGW("delegate is null, return false");
        return false;
    }
    return delegate_->OnStartContinuation();
}

void DeclarativeFrontend::OnCompleteContinuation(int32_t code)
{
    if (delegate_) {
        delegate_->OnCompleteContinuation(code);
    }
}

void DeclarativeFrontend::OnMemoryLevel(const int32_t level)
{
    if (delegate_) {
        delegate_->OnMemoryLevel(level);
    }
}

void DeclarativeFrontend::OnSaveData(std::string& data)
{
    if (delegate_) {
        delegate_->OnSaveData(data);
    }
}

void DeclarativeFrontend::GetPluginsUsed(std::string& data)
{
    if (delegate_) {
        delegate_->GetPluginsUsed(data);
    }
}

bool DeclarativeFrontend::OnRestoreData(const std::string& data)
{
    if (!delegate_) {
        LOGW("delegate is null, return false");
        return false;
    }
    return delegate_->OnRestoreData(data);
}

void DeclarativeFrontend::OnRemoteTerminated()
{
    if (delegate_) {
        delegate_->OnRemoteTerminated();
    }
}

void DeclarativeFrontend::OnNewRequest(const std::string& data)
{
    if (delegate_) {
        delegate_->OnNewRequest(data);
    }
}

void DeclarativeFrontend::CallRouterBack()
{
    if (delegate_) {
        if (delegate_->GetStackSize() == 1 && isSubWindow_) {
            LOGW("Can't back because this is the last page of sub window!");
            return;
        }
        delegate_->CallPopPage();
    }
}

void DeclarativeFrontend::OnSurfaceChanged(int32_t width, int32_t height)
{
    if (delegate_) {
        delegate_->OnSurfaceChanged();
    }
}

void DeclarativeFrontend::OnLayoutCompleted(const std::string& componentId)
{
    if (delegate_) {
        delegate_->OnLayoutCompleted(componentId);
    }
}

void DeclarativeFrontend::OnDrawCompleted(const std::string& componentId)
{
    if (delegate_) {
        delegate_->OnDrawCompleted(componentId);
    }
}

void DeclarativeFrontend::HotReload()
{
    auto manager = GetPageRouterManager();
    CHECK_NULL_VOID(manager);
    manager->FlushFrontend();
}

void DeclarativeFrontend::FlushReload()
{
    if (jsEngine_) {
        jsEngine_->FlushReload();
    }
}

void DeclarativeFrontend::DumpFrontend() const
{
    if (!delegate_) {
        return;
    }
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);

    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("Components: " + std::to_string(delegate_->GetComponentsCount()));
        DumpLog::GetInstance().AddDesc("Path: " + routerPath);
        DumpLog::GetInstance().AddDesc("Length: " + std::to_string(routerIndex));
        DumpLog::GetInstance().Print(0, routerName, 0);
    }
}

std::string DeclarativeFrontend::GetPagePath() const
{
    if (!delegate_) {
        return "";
    }
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);
    return routerPath + routerName;
}

void DeclarativeFrontend::TriggerGarbageCollection()
{
    if (jsEngine_) {
        jsEngine_->RunGarbageCollection();
    }
}

void DeclarativeFrontend::DumpHeapSnapshot(bool isPrivate)
{
    if (jsEngine_) {
        jsEngine_->DumpHeapSnapshot(isPrivate);
    }
}

void DeclarativeFrontend::SetColorMode(ColorMode colorMode)
{
    if (delegate_) {
        delegate_->SetColorMode(colorMode);
    }
}

void DeclarativeFrontend::RebuildAllPages()
{
    if (delegate_) {
        delegate_->RebuildAllPages();
    }
}

void DeclarativeFrontend::NotifyAppStorage(const std::string& key, const std::string& value)
{
    if (!delegate_) {
        LOGW("delegate is null, return false");
        return;
    }
    delegate_->NotifyAppStorage(jsEngine_, key, value);
}

void DeclarativeEventHandler::HandleAsyncEvent(const EventMarker& eventMarker)
{
    LOGI("HandleAsyncEvent pageId: %{private}d, eventId: %{private}s, eventType: %{private}s",
        eventMarker.GetData().pageId, eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());
    std::string param = eventMarker.GetData().GetEventParam();
    if (eventMarker.GetData().isDeclarativeUi) {
        if (delegate_) {
            delegate_->GetUiTask().PostTask([eventMarker] { eventMarker.CallUiFunction(); });
        }
    } else {
        delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param.append("null"), std::string(""));
    }

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info)
{
    std::string eventParam;
    if (eventMarker.GetData().eventType.find("touch") != std::string::npos) {
        TouchInfoToString(info, eventParam);
    } else if (eventMarker.GetData().eventType.find("mouse") != std::string::npos) {
        MouseInfoToString(info, eventParam);
    } else if (eventMarker.GetData().eventType == "swipe") {
        SwipeInfoToString(info, eventParam);
    }

    LOGD("HandleAsyncEvent pageId: %{public}d, eventId: %{public}s, eventType: %{public}s",
        eventMarker.GetData().pageId, eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());
    std::string param = eventMarker.GetData().GetEventParam();
    if (eventParam.empty()) {
        param.append("null");
    } else {
        param.append(eventParam);
    }

    if (eventMarker.GetData().isDeclarativeUi) {
        if (delegate_) {
            auto cinfo = CopyEventInfo(info);
            delegate_->GetUiTask().PostTask([eventMarker, cinfo] { eventMarker.CallUiArgFunction(cinfo.get()); });
        }
    } else {
        delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param, "");
    }

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleAsyncEvent(
    const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info)
{
    if (eventMarker.GetData().isDeclarativeUi) {
        if (delegate_) {
            delegate_->GetUiTask().PostTask([eventMarker, info] { eventMarker.CallUiArgFunction(info.get()); });
        }
    }
}

void DeclarativeEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result)
{
    LOGD("HandleSyncEvent pageId: %{public}d, eventId: %{public}s, eventType: %{public}s", eventMarker.GetData().pageId,
        eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());
    std::string param = std::string("\"")
                            .append(eventMarker.GetData().eventType)
                            .append("\",{\"code\":")
                            .append(std::to_string(static_cast<int32_t>(info.code)))
                            .append(",\"action\":")
                            .append(std::to_string(static_cast<int32_t>(info.action)))
                            .append(",\"repeatCount\":")
                            .append(std::to_string(static_cast<int32_t>(info.repeatTime)))
                            .append(",\"timestamp\":")
                            .append(std::to_string(info.timeStamp.time_since_epoch().count()))
                            .append(",\"key\":\"")
                            .append(info.key)
                            .append("\"},");

    result = delegate_->FireSyncEvent(eventMarker.GetData().eventId, param, "");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = std::to_string(static_cast<int32_t>(info.code));
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, int32_t param)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param)
{
    LOGD("HandleAsyncEvent pageId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
        eventMarker.GetData().eventId.c_str());

    if (eventMarker.GetData().isDeclarativeUi) {
        std::string fixParam(param);
        std::string::size_type startPos = param.find_first_of("{");
        std::string::size_type endPos = param.find_last_of("}");
        if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
            fixParam = fixParam.substr(startPos, endPos - startPos + 1);
        }
        if (delegate_) {
            delegate_->GetUiTask().PostTask([eventMarker, fixParam] { eventMarker.CallUiStrFunction(fixParam); });
        }
    } else {
        delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param, "");
    }

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleSyncEvent(const EventMarker& eventMarker, bool& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info)
{
    if (delegate_) {
        delegate_->GetUiTask().PostSyncTask([eventMarker, info] { eventMarker.CallUiArgFunction(info.get()); });
    }
}

void DeclarativeEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void DeclarativeEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::string& param, std::string& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
    delegate_->FireSyncEvent(eventMarker.GetData().eventId, param, std::string(""), result);
}

void DeclarativeEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId, const bool isDestroy)
{
    if (delegate_) {
        delegate_->FireExternalEvent(eventMarker.GetData().eventId, componentId, nodeId, isDestroy);
    }
}

} // namespace OHOS::Ace
