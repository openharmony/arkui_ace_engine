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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_HANDLER_H

#include <map>
#include <sstream>
#include <unordered_map>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
struct HandlerData {
public:
    int32_t actionCode = -1;
    std::map<std::string, std::string> params;
};

struct HandlerReply {
public:
    std::map<std::string, std::string> replyParams;

    template<typename T>
    T GetParam(const std::string& matchString, const T& defaultValue)
    {
        auto it = replyParams.find(matchString);
        if (it != replyParams.end()) {
            std::istringstream iss(it->second);
            T value;
            if (iss >> value) {
                return value;
            } else {
                return defaultValue;
            }
        }
        return defaultValue;
    }

    template<typename T>
    void SetParam(const std::string& keyString, const T& value)
    {
        std::ostringstream oss;
        oss << value;
        replyParams.emplace(keyString, oss.str());
    }
};

struct HostConfig {
    bool isReportFrameEvent = false;
};

class ContainerHandler : public virtual AceType {
    DECLARE_ACE_TYPE(ContainerHandler, AceType);

public:
    ContainerHandler() = default;
    ~ContainerHandler() override = default;

    bool SendDataToHost(const HandlerData& data, HandlerReply& reply)
    {
        return OnReciveData(data, reply);
    }

    virtual bool OnReciveData(const HandlerData& data, HandlerReply& reply) { return false; }

    const HostConfig& GetHostConfig() const
    {
        return hostConfig_;
    }

protected:
    HostConfig hostConfig_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_HANDLER_H
