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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_CODE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_CODE_H

#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace {

class GroupJsCode final {
public:
    GroupJsCode() = delete;
    ~GroupJsCode() = delete;

    ACE_EXPORT static void LoadJsCode(std::string& jsCode);

private:
    static void LoadGlobalObjJsCode(std::string& jsCode);

    static void LoadModuleGroupJsCode(std::string& jsCode);

    // FA(Feature ability) Js code contains Js interfaces to call ability, such as callAbility, which
    // provides another mechanism like channel plugin. And it's based on the channel plugin.
    static void LoadFeatureAbilityJsCode(std::string& jsCode);

    static void LoadInvokeInterfaceJsCode(std::string& jsCode);

    // the Group Messenger is designed for Module group and Event Group,
    // to send and receive the message for the JS side.
    static void LoadGroupMessengerJsCode(std::string& jsCode);

    // Provide common callback process
    static void LoadCommonCallbackJsCode(std::string& jsCode);

    // Provide common external callback process
    static void LoadCommonCallbackExJsCode(std::string& jsCode);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_GROUP_JS_CODE_H
