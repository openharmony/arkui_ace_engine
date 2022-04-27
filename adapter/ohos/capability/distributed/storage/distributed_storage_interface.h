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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_INTERFACE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_INTERFACE_H

#include "adapter/ohos/capability/distributed/storage/distributed_storage.h"
#include "base/memory/referenced.h"
#include "core/common/storage/storage_interface.h"

namespace OHOS::Ace {

class DistributedStorageInterface final : public StorageInterface {
public:
    ~DistributedStorageInterface() override = default;

    RefPtr<Storage> GetStorage(const std::string& sessionId, std::function<void(const std::string&)>&& notifier,
        const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        auto storage = Referenced::MakeRefPtr<DistributedStorage>(sessionId, taskExecutor);
        if (!storage->Init(std::move(notifier))) {
            return nullptr;
        }
        DistributedStorage::AddStorage(sessionId, storage);
        return storage;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_INTERFACE_H
