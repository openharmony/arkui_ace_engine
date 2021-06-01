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

#include "frameworks/bridge/js_frontend/js_frontend.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"

namespace OHOS::Ace {
namespace {

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

RefPtr<Frontend> Frontend::Create()
{
    return AceType::MakeRefPtr<JsFrontend>();
}

JsFrontend::~JsFrontend() noexcept
{
    // To guarantee the jsEngine_ and delegate_ released in js thread
    auto jsTaskExecutor = delegate_->GetAnimationJsTask();
    RefPtr<Framework::JsEngine> jsEngine;
    jsEngine.Swap(jsEngine_);
    RefPtr<Framework::FrontendDelegateImpl> delegate;
    delegate.Swap(delegate_);
    jsTaskExecutor.PostTask([jsEngine, delegate] {});
}

bool JsFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    LOGI("JsFrontend initialize begin.");
    type_ = type;
    ACE_DCHECK(type_ == FrontendType::JS);
    InitializeFrontendDelegate(taskExecutor);
    taskExecutor->PostTask(
        [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_), delegate = delegate_] {
            auto jsEngine = weakEngine.Upgrade();
            if (!jsEngine) {
                return;
            }
            jsEngine->Initialize(delegate);
        },
        TaskExecutor::TaskType::JS);

    LOGI("JsFrontend initialize end.");
    return true;
}

void JsFrontend::AttachPipelineContext(const RefPtr<PipelineContext>& context)
{
    handler_ = AceType::MakeRefPtr<JsEventHandler>(delegate_);
    context->RegisterEventHandler(handler_);
    delegate_->AttachPipelineContext(context);
}

void JsFrontend::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    delegate_->SetAssetManager(assetManager);
}

void JsFrontend::InitializeFrontendDelegate(const RefPtr<TaskExecutor>& taskExecutor)
{
    Framework::FrontendDelegateImplBuilder builder;
    builder.loadCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](const std::string& url,
                                   const RefPtr<Framework::JsAcePage>& jsPage, bool isMainPage) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->LoadJs(url, jsPage, isMainPage);
    };

    builder.transferCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                       const RefPtr<JsMessageDispatcher>& dispatcher) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->SetJsMessageDispatcher(dispatcher);
    };

    builder.asyncEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const std::string& eventId, const std::string& param) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireAsyncEvent(eventId, param);
    };

    builder.syncEventCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                        const std::string& eventId, const std::string& param) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->FireSyncEvent(eventId, param);
    };

    builder.updatePageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const RefPtr<Framework::JsAcePage>& jsPage) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->UpdateRunningPage(jsPage);
        jsEngine->UpdateStagingPage(jsPage);
    };

    builder.resetStagingPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)]() {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->ResetStagingPage();
    };

    builder.destroyPageCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](int32_t pageId) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DestroyPageInstance(pageId);
    };

    builder.destroyApplicationCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                                 const std::string& packageName) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->DestroyApplication(packageName);
    };

    builder.timerCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                    const std::string& callbackId, const std::string& delay, bool isInterval) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->TimerCallback(callbackId, delay, isInterval);
    };

    builder.mediaQueryCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                         const std::string& callbackId, const std::string& args) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->MediaQueryCallback(callbackId, args);
    };

    builder.requestAnimationCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                               const std::string& callbackId, uint64_t timeStamp) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->RequestAnimationCallback(callbackId, timeStamp);
    };

    builder.jsCallback = [weakEngine = WeakPtr<Framework::JsEngine>(jsEngine_)](
                                 const std::string& callbackId, const std::string& args) {
        auto jsEngine = weakEngine.Upgrade();
        if (!jsEngine) {
            return;
        }
        jsEngine->JsCallback(callbackId, args);
    };
    builder.taskExecutor = taskExecutor;
    builder.ability = ability_;
    delegate_ = AceType::MakeRefPtr<Framework::FrontendDelegateImpl>(builder);
    if (jsEngine_) {
        delegate_->SetGroupJsBridge(jsEngine_->GetGroupJsBridge());
    } else {
        LOGE("the js engine is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::JS_ENGINE_CREATE_ERR);
    }
}

void JsFrontend::RunPage(int32_t pageId, const std::string& url, const std::string& params)
{
    // Not use this pageId from backend, manage it in FrontendDelegateImpl.
    delegate_->RunPage(url, params);
}

void JsFrontend::PushPage(const std::string& url, const std::string& params)
{
    delegate_->Push(url, params);
}

void JsFrontend::SendCallbackMessage(const std::string& callbackId, const std::string& data) const
{
    delegate_->OnJsCallback(callbackId, data);
}

void JsFrontend::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    delegate_->SetJsMessageDispatcher(dispatcher);
}

void JsFrontend::TransferComponentResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    delegate_->TransferComponentResponseData(callbackId, code, std::move(data));
}

void JsFrontend::TransferJsResponseData(int callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    delegate_->TransferJsResponseData(callbackId, code, std::move(data));
}

void JsFrontend::TransferJsPluginGetError(int callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    delegate_->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
}

void JsFrontend::TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const
{
    delegate_->TransferJsEventData(callbackId, code, std::move(data));
}

void JsFrontend::LoadPluginJsCode(std::string&& jsCode) const
{
    delegate_->LoadPluginJsCode(std::move(jsCode));
}

void JsFrontend::UpdateState(Frontend::State state)
{
    switch (state) {
        case Frontend::State::ON_CREATE:
            break;
        case Frontend::State::ON_DESTROY:
            delegate_->OnApplicationDestroy(delegate_->GetAppID());
            break;
        default:
            LOGE("error State: %d", state);
    }
}

RefPtr<AccessibilityManager> JsFrontend::GetAccessibilityManager() const
{
    if (!delegate_) {
        LOGE("GetAccessibilityManager delegate is null");
        return nullptr;
    }
    return delegate_->GetJsAccessibilityManager();
}

const WindowConfig& JsFrontend::GetWindowConfig() const
{
    return delegate_->GetWindowConfig();
}

bool JsFrontend::OnBackPressed()
{
    return delegate_->OnPageBackPress();
}

void JsFrontend::OnShow()
{
    delegate_->OnForground();
    foregroundFrontend_ = true;
}

void JsFrontend::OnHide()
{
    delegate_->OnBackGround();
    foregroundFrontend_ = false;
}

void JsFrontend::OnConfigurationUpdated(const std::string& data)
{
    delegate_->OnConfigurationUpdated(data);
}

void JsFrontend::OnActive()
{
    delegate_->InitializeAccessibilityCallback();
    delegate_->OnActive();
}

void JsFrontend::OnInactive()
{
    delegate_->OnInactive();
}

bool JsFrontend::OnStartContinuation()
{
    return delegate_->OnStartContinuation();
}

void JsFrontend::OnCompleteContinuation(int32_t code)
{
    delegate_->OnCompleteContinuation(code);
}

void JsFrontend::OnSaveData(std::string& data)
{
    delegate_->OnSaveData(data);
}

bool JsFrontend::OnRestoreData(const std::string& data)
{
    return delegate_->OnRestoreData(data);
}

void JsFrontend::OnNewRequest(const std::string& data)
{
    delegate_->OnNewRequest(data);
}

void JsFrontend::CallRouterBack()
{
    delegate_->CallPopPage();
}

void JsFrontend::OnSurfaceChanged(int32_t width, int32_t height)
{
    delegate_->OnSurfaceChanged();
}

void JsFrontend::DumpFrontend() const
{
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);

    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("Path: " + routerPath);
        DumpLog::GetInstance().AddDesc("Length: " + std::to_string(routerIndex));
        DumpLog::GetInstance().Print(0, routerName, 0);
    }
}

void JsFrontend::TriggerGarbageCollection()
{
    jsEngine_->RunGarbageCollection();
}

void JsFrontend::RebuildAllPages()
{
    delegate_->RebuildAllPages();
}

void JsFrontend::SetColorMode(ColorMode colorMode)
{
    delegate_->SetColorMode(colorMode);
}

void JsEventHandler::HandleAsyncEvent(const EventMarker& eventMarker)
{
    LOGD("HandleAsyncEvent pageId: %{private}d, eventId: %{private}s, eventType: %{private}s",
        eventMarker.GetData().pageId, eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());
    std::string param = eventMarker.GetData().GetEventParam();
    delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param.append("null"), std::string(""));

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info)
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
    std::string param;
    auto adapter = TypeInfoHelper::DynamicCast<EventToJSONStringAdapter>(&info);
    if (adapter) {
        LOGD("HandleAsyncEvent pageId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
             eventMarker.GetData().eventId.c_str());
        param = adapter->ToJSONString();
    } else {
        param = eventMarker.GetData().GetEventParam();
        if (eventParam.empty()) {
            param.append("null");
        } else {
            param.append(eventParam);
        }
    }
    delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param, "");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result)
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
                            .append(std::to_string(static_cast<int32_t>(info.timeStamp)))
                            .append(",\"timestampStart\":")
                            .append(std::to_string(static_cast<int32_t>(info.timeStampStart)))
                            .append(",\"key\":\"")
                            .append(info.key)
                            .append("\"},");

    result = delegate_->FireSyncEvent(eventMarker.GetData().eventId, param, "");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = std::to_string(static_cast<int32_t>(info.code));
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, int32_t param)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param)
{
    LOGD("HandleAsyncEvent pageId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
        eventMarker.GetData().eventId.c_str());
    delegate_->FireAsyncEvent(eventMarker.GetData().eventId, param, "");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleSyncEvent(const EventMarker& eventMarker, bool& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}

void JsEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result)
{
    LOGW("js event handler does not support this event type!");
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    delegate_->FireAccessibilityEvent(accessibilityEvent);
    delegate_->FireSyncEvent(eventMarker.GetData().eventId, param, std::string(""), result);
}

} // namespace OHOS::Ace
