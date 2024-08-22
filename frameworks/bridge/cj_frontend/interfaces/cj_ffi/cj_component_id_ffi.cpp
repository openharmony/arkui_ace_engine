/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "bridge/cj_frontend/interfaces/cj_ffi/cj_component_id_ffi.h"

#include "core/components_ng/base/inspector.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace::V2;

extern "C" {
ExternalString FfiOHOSAceFrameworkComponentIdGetInspectorByKey(const char* id)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return {};
    }
    std::string key = id;
    auto resultStr = NG::Inspector::GetInspectorNodeByKey(key);
    return Utils::MallocCString(resultStr);
}

ExternalString FfiOHOSAceFrameworkComponentIdGetInspectorTree()
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return {};
    }
    auto nodeInfos = NG::Inspector::GetInspector();
    return Utils::MallocCString(nodeInfos);
}

bool FfiOHOSAceFrameworkComponentIdSendEventByKey(char* id, int action, char* params)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return false;
    }
    std::string key = id;
    std::string s_params = params;
    auto result = NG::Inspector::SendEventByKey(key, action, s_params);
    return result;
}

static TouchEvent GetTouchPointFromCJ(const CJTouchInfo& cJTouchInfo)
{
    TouchEvent touchPoint;
    touchPoint.type = static_cast<TouchType>(cJTouchInfo.type);
    touchPoint.id = cJTouchInfo.fingerId;
    touchPoint.x = cJTouchInfo.localX;
    touchPoint.y = cJTouchInfo.localY;
    touchPoint.time = std::chrono::high_resolution_clock::now();
    return touchPoint;
}

static KeyEvent GetKeyEventFromCJ(const CJKeyEvent& cJKeyEvent)
{
    auto action = static_cast<KeyAction>(cJKeyEvent.type);
    auto code = static_cast<KeyCode>(cJKeyEvent.keyCode);
    KeyEvent keyEvent(code, action);
    keyEvent.sourceType = static_cast<SourceType>(cJKeyEvent.keySource);
    keyEvent.deviceId = cJKeyEvent.deviceId;
    keyEvent.metaKey = cJKeyEvent.metaKey;
    auto timeStamp = cJKeyEvent.timestamp;
    keyEvent.SetTimeStamp(timeStamp);
    return keyEvent;
}

static MouseEvent GetMouseEventFromCJ(const CJMouseEvent& cJMouseEvent)
{
    MouseEvent mouseEvent;
    mouseEvent.action = static_cast<MouseAction>(cJMouseEvent.action);
    mouseEvent.button = static_cast<MouseButton>(cJMouseEvent.button);
    mouseEvent.x = cJMouseEvent.x;
    mouseEvent.deltaX = mouseEvent.x;
    mouseEvent.y = cJMouseEvent.y;
    mouseEvent.deltaY = mouseEvent.y;
    mouseEvent.time = std::chrono::high_resolution_clock::now();
    mouseEvent.sourceType = SourceType::MOUSE;
    return mouseEvent;
}

bool FfiOHOSAceFrameworkComponentIdSendTouchEvent(CJTouchInfo cJTouchInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return false;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return false;
    }
    TouchEvent touchPoint = GetTouchPointFromCJ(cJTouchInfo);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, touchPoint]() { pipelineContext->OnTouchEvent(touchPoint); }, TaskExecutor::TaskType::UI,
        "FfiOHOSAceFrameworkComponentIdSendTouchEvent");
    return result;
}

bool FfiOHOSAceFrameworkComponentIdSendKeyEvent(CJKeyEvent cJKeyEvent)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return false;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return false;
    }
    KeyEvent keyEvent = GetKeyEventFromCJ(cJKeyEvent);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, keyEvent]() { pipelineContext->OnKeyEvent(keyEvent); }, TaskExecutor::TaskType::UI,
        "FfiOHOSAceFrameworkComponentIdSendKeyEvent");
    return result;
}

bool FfiOHOSAceFrameworkComponentIdSendMouseEvent(CJMouseEvent cJMouseEvent)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    auto container = Container::Current();
    if (!container) {
        return false;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return false;
    }
    MouseEvent mouseEvent = GetMouseEventFromCJ(cJMouseEvent);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, mouseEvent]() { pipelineContext->OnMouseEvent(mouseEvent); }, TaskExecutor::TaskType::UI,
        "FfiOHOSAceFrameworkComponentIdSendMouseEvent");
    return result;
}
}