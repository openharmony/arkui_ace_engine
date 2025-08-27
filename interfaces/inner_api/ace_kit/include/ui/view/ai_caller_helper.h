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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_UI_SESSION_AI_CALLER_HELPER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_UI_SESSION_AI_CALLER_HELPER_H

#include <string>

#include "ui/base/macros.h"

namespace OHOS::Ace {
// the interface class for AI assistant, the ai assistante instance should be setted in FrameNode.
class ACE_FORCE_EXPORT AICallerHelper {
public:
    AICallerHelper() = default;
    virtual ~AICallerHelper() = default;

    /**
     * @description: this callback triggered by ai assistant by ui_session proxy.
     * @param funcName function name of the target function.
     * @param params params for target function in json format.
     */
    virtual bool onAIFunctionCaller(const std::string& funcName, const std::string& params) = 0;
};
}
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_UI_SESSION_AI_CALLER_HELPER_H
