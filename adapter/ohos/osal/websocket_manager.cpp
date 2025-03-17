/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/websocket/websocket_manager.h"
#include "connect_server_manager.h"

namespace OHOS::Ace {

#ifdef OHOS_PLATFORM

void WebSocketManager::SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(jsonTreeStr, jsonSnapshotStr);
}

void WebSocketManager::SendMessage(const std::string &message)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SendMessage(message);
}

bool WebSocketManager::SetRecordCallback(const std::function<void(void)> &startRecordFunc,
    const std::function<void(void)> &stopRecordFunc)
{
    return OHOS::AbilityRuntime::ConnectServerManager::Get().SetRecordCallback(startRecordFunc, stopRecordFunc);
}

void WebSocketManager::RegisterConnectServerCallback(const ServerConnectCallback &connectServerCallback)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterConnectServerCallback(connectServerCallback);
}

void WebSocketManager::SetRecordResults(const std::string &jsonArrayStr)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SetRecordResults(jsonArrayStr);
}

void WebSocketManager::SetProfilerCallBack(const std::function<void(bool)>& setStateProfilerStatus)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SetProfilerCallBack(setStateProfilerStatus);
}

void WebSocketManager::SetSwitchCallback(const std::function<void(int32_t)>& createLayoutInfo, int32_t instanceId)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().SetSwitchCallback(createLayoutInfo, instanceId);
}

void WebSocketManager::RegisterAddInstanceCallback(const AddInstanceCallBack& addInstanceCallback)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterAddInstanceCallback(addInstanceCallback);
}

void WebSocketManager::RegisterSendInstanceMessageCallback(
    const SendInstanceMessageCallBack& sendInstanceMessageCallback)
{
    OHOS::AbilityRuntime::ConnectServerManager::Get().RegisterSendInstanceMessageCallback(sendInstanceMessageCallback);
}

#else
void WebSocketManager::SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr) {}
void WebSocketManager::SendMessage(const std::string& message) {}
bool WebSocketManager::SetRecordCallback(
    const std::function<void(void)>& startRecordFunc, const std::function<void(void)>& stopRecordFunc)
{
    return true;
}

void WebSocketManager::RegisterConnectServerCallback(const ServerConnectCallback& connectServerCallback) {}
void WebSocketManager::SetRecordResults(const std::string& jsonArrayStr) {}
void WebSocketManager::SetProfilerCallBack(const std::function<void(bool)>& setStateProfilerStatus) {}
void WebSocketManager::SetSwitchCallback(const std::function<void(int32_t)>& createLayoutInfo, int32_t instanceId) {}
void WebSocketManager::RegisterAddInstanceCallback(const AddInstanceCallBack& addInstanceCallback) {}
void WebSocketManager::RegisterSendInstanceMessageCallback(
    const SendInstanceMessageCallBack& sendInstanceMessageCallback) {}
#endif
}
