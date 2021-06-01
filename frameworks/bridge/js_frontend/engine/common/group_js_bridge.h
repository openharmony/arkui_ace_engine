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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_BRIDGE_H

#include <string>
#include <vector>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {

class GroupJsBridge : public virtual AceType {
    DECLARE_ACE_TYPE(GroupJsBridge, AceType)
public:
    virtual void TriggerModuleJsCallback(int32_t callbackId, int32_t code,
        std::vector<uint8_t>&& messageData) = 0;

    virtual void TriggerModulePluginGetErrorCallback(
        int32_t callbackId, int32_t errorCode, std::string&& errorMessage) = 0;

    virtual void TriggerEventJsCallback(int32_t callbackId, int32_t code, std::vector<uint8_t>&& eventData) = 0;

    virtual void LoadPluginJsCode(std::string&& jsCode) {}

    virtual void Destroy() {}
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_BRIDGE_H
