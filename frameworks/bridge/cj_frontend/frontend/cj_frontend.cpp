/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/frontend/cj_frontend.h"

#include "bridge/cj_frontend/frontend/cj_page_router.h"

namespace OHOS::Ace::Framework {
void CJFrontend::InternalInitialize()
{
    LOGE("CJFrontend InternalInitialize begin.");
    classicRouter_ = MakeRefPtr<CJPageRouter>(WeakClaim(this));
    pageRouterManager_ = classicRouter_;
    pageRouterManager_->SetManifestParser(manifestParser_);
    handler_ = MakeRefPtr<CJEventHandler>(WeakClaim(this));
}

void CJFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    CJFrontendAbstract::AttachPipelineContext(context);
    auto pipeline = DynamicCast<PipelineContext>(context);
    if (pipeline) {
        pipeline->RegisterEventHandler(handler_);
    }
}

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
    const auto swipeInfo = TypeInfoHelper::DynamicCast<SwipeEventInfo>(&info);
    if (swipeInfo != nullptr) {
        eventParam = swipeInfo->ToJsonParamInfo();
    }
}

} // namespace

void CJEventHandler::HandleAsyncEvent(const OHOS::Ace::EventMarker& eventMarker)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    LOGI("HandleAsyncEvent pageId: %{private}d, eventId: %{private}s, eventType: %{private}s",
        eventMarker.GetData().pageId, eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());

    std::string param = eventMarker.GetData().GetEventParam();
    frontend->GetTaskExecutor()->PostTask([eventMarker] {
            eventMarker.CallUiFunction();
        }, TaskExecutor::TaskType::UI, "CJHandleAsyncEvent");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleAsyncEvent(const OHOS::Ace::EventMarker& eventMarker, const BaseEventInfo& info)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

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
    frontend->GetTaskExecutor()->PostTask([eventMarker, info = CopyEventInfo(info)] {
            eventMarker.CallUiArgFunction(info.get());
        }, TaskExecutor::TaskType::UI, "CJHandleAsyncEvent");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    frontend->GetTaskExecutor()->PostTask([eventMarker, info] {
            eventMarker.CallUiArgFunction(info.get());
        }, TaskExecutor::TaskType::UI, "CJHandleAsyncEvent");
}

void CJEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, int32_t param)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param)
{
    LOGD("HandleAsyncEvent pageId: %{public}d, eventId: %{public}s", eventMarker.GetData().pageId,
        eventMarker.GetData().eventId.c_str());
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    std::string fixParam(param);
    std::string::size_type startPos = param.find_first_of("{");
    std::string::size_type endPos = param.find_last_of("}");
    if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
        fixParam = fixParam.substr(startPos, endPos - startPos + 1);
    }

    frontend->GetTaskExecutor()->PostTask([eventMarker, fixParam] {
            eventMarker.CallUiStrFunction(fixParam);
        }, TaskExecutor::TaskType::UI, "CJHandleAsyncEvent");

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result)
{
    LOGD("HandleSyncEvent pageId: %{public}d, eventId: %{public}s, eventType: %{public}s", eventMarker.GetData().pageId,
        eventMarker.GetData().eventId.c_str(), eventMarker.GetData().eventType.c_str());
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

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

    result = false;

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = std::to_string(static_cast<int32_t>(info.code));
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleSyncEvent(const EventMarker& eventMarker, bool& result)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    result = false;

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    frontend->GetTaskExecutor()->PostTask([eventMarker, info] {
            eventMarker.CallUiArgFunction(info.get());
        }, TaskExecutor::TaskType::UI, "CJHandleAsyncEvent");
}

void CJEventHandler::HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::string& param, std::string& result)
{
    auto frontend = frontend_.Upgrade();
    CHECK_NULL_VOID(frontend);

    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.nodeId = StringUtils::StringToInt(eventMarker.GetData().eventId);
    accessibilityEvent.eventType = eventMarker.GetData().eventType;
    frontend->GetAccessibilityManager()->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void CJEventHandler::HandleSyncEvent(
    const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId, const bool isDestroy)
{
}

}