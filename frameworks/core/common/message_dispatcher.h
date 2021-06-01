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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MESSAGE_DISPATCHER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MESSAGE_DISPATCHER_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {

class MessageDispatcher : public virtual AceType {
    DECLARE_ACE_TYPE(MessageDispatcher, AceType);

public:
    MessageDispatcher() = default;
    ~MessageDispatcher() override = default;

    virtual void Dispatch(const std::string& channel, std::vector<uint8_t>&& data, int32_t id,
        int32_t groupType, bool replyToComponent = false) const = 0;

    virtual void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MESSAGE_DISPATCHER_H
