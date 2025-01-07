/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#include "core/common/storage/storage_proxy.h"

namespace OHOS::Ace {

StorageProxy* StorageProxy::inst_ = nullptr;

StorageProxy* StorageProxy::GetInstance()
{
    if (inst_ == nullptr) {
        inst_ = new StorageProxy();
    }
    return (inst_);
}

void StorageProxy::SetDelegate(std::unique_ptr<StorageInterface>&& delegate)
{
    delegate_ = std::move(delegate);
}

void StorageProxy::SetDistributedDelegate(std::unique_ptr<StorageInterface>&& delegate)
{
    distributedDelegate_ = std::move(delegate);
}

RefPtr<Storage> StorageProxy::GetStorage(int areaMode) const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetStorage(areaMode);
}

RefPtr<Storage> StorageProxy::GetStorage(const std::string& sessionId,
    std::function<void(const std::string&)>&& notifier, const RefPtr<TaskExecutor>& taskExecutor) const
{
    CHECK_NULL_RETURN(distributedDelegate_, nullptr);
    return distributedDelegate_->GetStorage(sessionId, std::move(notifier), taskExecutor);
}

} // namespace OHOS::Ace
