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

#include "uicast_interface/uicast_jsi_impl.h"

namespace OHOS::Ace::Framework {
void UICastJsiImpl::CacheAceCmd(const std::string& cmd, bool isVoid, bool hasArguments, bool singleArg,
    panda::JsiRuntimeCallInfo* runtimeCallInfo, panda::ecmascript::EcmaVM* vm)
{}

void UICastJsiImpl::CacheAceCmd(const std::string& cmd, const JsiCallbackInfo& info) {}

void UICastJsiImpl::UpdateRootView() {}

void UICastJsiImpl::HandleRouterPageCall(const std::string& operation, const std::string& url) {}
} // namespace OHOS::Ace::Framework