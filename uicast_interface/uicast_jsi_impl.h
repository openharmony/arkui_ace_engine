/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef ACE_UICAST_IMPL_UICAST_JSI_IMPL_H
#define ACE_UICAST_IMPL_UICAST_JSI_IMPL_H

#include <string>

#include "base/utils/macros.h"

namespace panda {
class JsiRuntimeCallInfo;

namespace ecmascript {
class EcmaVM;
} // namespace ecmascript
} // namespace panda

namespace OHOS::Ace::Framework {
class JsiCallbackInfo;

class ACE_EXPORT UICastJsiImpl {
public:
    UICastJsiImpl() = delete;
    static void CacheAceCmd(const std::string& cmd, bool isVoid, bool hasArguments, bool singleArg,
        panda::JsiRuntimeCallInfo* runtimeCallInfo, panda::ecmascript::EcmaVM* vm);
    static void CacheAceCmd(const std::string& cmd, const JsiCallbackInfo& info);
    static void UpdateRootView();
    static void HandleRouterPageCall(const std::string& operation, const std::string& url);
};
} // namespace OHOS::Ace::Framework

#endif // ACE_UICAST_IMPL_UICAST_JSI_IMPL_H