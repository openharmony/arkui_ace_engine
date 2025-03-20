/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_WEBSOCKET_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_WEBSOCKET_MANAGER_H

#include <string>
#include <functional>

#include "base/utils/macros.h"
#include "base/log/log.h"
using ServerConnectCallback = void(*)(void);
using AddInstanceCallBack = void(*)(int32_t);
using SendInstanceMessageCallBack = void(*)(int32_t);

namespace OHOS::Ace {
class ACE_EXPORT WebSocketManager final {
public:
    static void SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr);
    static void SendMessage(const std::string& message);
    static bool SetRecordCallback(
        const std::function<void(void)>& startRecordFunc, const std::function<void(void)>& stopRecordFunc);
    static void RegisterConnectServerCallback(const ServerConnectCallback& connectServerCallback);
    static void SetRecordResults(const std::string& jsonArrayStr);
    static void SetProfilerCallBack(const std::function<void(bool)>& setStateProfilerStatus);
    static void SetSwitchCallback(const std::function<void(int32_t)>& createLayoutInfo, int32_t instanceId);
    static void RegisterAddInstanceCallback(const AddInstanceCallBack& addInstanceCallback);
    static void RegisterSendInstanceMessageCallback(const SendInstanceMessageCallBack& sendInstanceMessageCallback);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_HICHECKER_H
