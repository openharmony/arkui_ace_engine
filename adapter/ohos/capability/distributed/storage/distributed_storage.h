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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_H

#include <map>

#include "core/common/storage/storage.h"

namespace OHOS::ObjectStore {
class DistributedObject;
class ObjectWatcher;
} // namespace OHOS::ObjectStore

namespace OHOS::Ace {

using OnDataChangeCallback = std::function<void(const std::string&, const std::vector<std::string>&)>;
using ObjectStatusNotifyCallback = std::function<void(const std::string&, const std::string&)>;

class DistributedObjectPtr final {
public:
    DistributedObjectPtr(const std::string& sessionId, OnDataChangeCallback&& onChange);
    ~DistributedObjectPtr();

    OHOS::ObjectStore::DistributedObject* GetRawPtr();
    bool IsInvalid() const
    {
        return invalid_;
    }

private:
    std::string sessionId_;
    OHOS::ObjectStore::DistributedObject* object_ = nullptr;
    std::shared_ptr<OHOS::ObjectStore::ObjectWatcher> watcher_;
    bool invalid_ = true;
};

class DistributedStorage final : public Storage {
    DECLARE_ACE_TYPE(DistributedStorage, Storage);

public:
    explicit DistributedStorage(const std::string& sessionId, const RefPtr<TaskExecutor>& taskExecutor)
        : Storage(taskExecutor), sessionId_(sessionId)
    {}
    ~DistributedStorage() override = default;

    bool Init(std::function<void(const std::string&)>&& notifier);

    void SetString(const std::string& key, const std::string& value) override;
    std::string GetString(const std::string& key) override;
    void SetDouble(const std::string& key, const double value) override;
    bool GetDouble(const std::string& key, double& value) override;
    void SetBoolean(const std::string& key, const bool value) override;
    bool GetBoolean(const std::string& key, bool& value) override;
    DataType GetDataType(const std::string& key) override;
    void Clear() override {}
    void Delete(const std::string& key) override {}
    void NotifyStatus(const std::string& status);

    static void AddStorage(const std::string& sessionId, RefPtr<DistributedStorage> storage);
    static void DeleteStorage(const std::string& sessionId);
    static void OnStatusNotify(const std::string& sessionId, const std::string& status);

private:
    std::unique_ptr<DistributedObjectPtr> objectPtr_;
    std::string sessionId_;
    std::function<void(const std::string&)> notifyCallback_;

    static std::map<std::string, RefPtr<DistributedStorage>> storageMap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CAPABILITY_DISTRIBUTED_STORAGE_DISTRIBUTED_STORAGE_H