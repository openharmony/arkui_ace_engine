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

#include "core/common/environment/environment_proxy.h"

#include "base/memory/ace_type.h"
#include "core/common/environment/environment_impl.h"

namespace OHOS::Ace {

EnvironmentProxy* EnvironmentProxy::inst_ = nullptr;

std::mutex EnvironmentProxy::mutex_;

EnvironmentProxy* EnvironmentProxy::GetInstance()
{
    if (inst_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (inst_ == nullptr) {
            inst_ = new EnvironmentProxy();
        }
    }
    return (inst_);
}

RefPtr<Environment> EnvironmentProxy::GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const
{
    return AceType::MakeRefPtr<EnvironmentImpl>(taskExecutor);
}

} // namespace OHOS::Ace
