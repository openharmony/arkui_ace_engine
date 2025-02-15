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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONNECT_SERVER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONNECT_SERVER_MANAGER_H

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ConnectServerManager {
public:
    ~ConnectServerManager();
    static ConnectServerManager& Get();
    void SetDebugMode();
    void AddInstance(
        int32_t instanceId, const std::string& language = "", const std::string& instanceName = "PandaDebugger");
    void SendInspector(const std::string& jsonTreeStr, const std::string& jsonSnapshotStr);
    void RemoveInstance(int32_t instanceId);
    void SetLayoutInspectorCallback(const std::function<void(int32_t)>& createLayoutInfo);
    std::function<void(int32_t)> GetLayoutInspectorCallback();
    void StartConnectServerWithSocketPair(int32_t socketFd);
    void StopConnectServer();

private:
    ConnectServerManager();
    bool InitFunc();
    void InitConnectServer();
    void CloseConnectServerSo();
    bool CheckDebugVersion();
    std::string GetInstanceMapMessage(const char* messageType, int32_t instanceId, const std::string& language = "");

    mutable std::mutex mutex_;
    bool isDebugVersion_;
    void* handlerConnectServerSo_;
    std::string packageName_;
    std::unordered_map<int32_t, std::string> instanceMap_;
    std::function<void(int32_t)> createLayoutInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(ConnectServerManager);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONNECT_SERVER_MANAGER_H