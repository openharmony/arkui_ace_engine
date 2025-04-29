/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#ifndef FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_STORAGE_MOCK_STORAGE_H
#define FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_STORAGE_MOCK_STORAGE_H

#include "base/utils/utils.h"
#include "core/common/storage/storage_proxy.h"

namespace OHOS::Ace {
const std::string FALSE_TEST = "false";

class MockDistributedStorage final : public Storage {
    DECLARE_ACE_TYPE(MockDistributedStorage, Storage);

public:
    std::string sessionId_;
    explicit MockDistributedStorage(const std::string& sessionId, const RefPtr<TaskExecutor>& taskExecutor)
        : Storage(), sessionId_(sessionId)
    {}
    ~MockDistributedStorage() override = default;

    bool Init(std::function<void(const std::string&)>&& notifier);

    void SetString(const std::string& key, const std::string& value) override {};
    std::string GetString(const std::string& key) override
    {
        return FALSE_TEST;
    }
    void SetDouble(const std::string& key, const double value) override {};
    bool GetDouble(const std::string& key, double& value) override
    {
        return false;
    }
    void SetBoolean(const std::string& key, const bool value) override {};
    bool GetBoolean(const std::string& key, bool& value) override
    {
        return false;
    }

    DataType GetDataType(const std::string& key) override
    {
        Storage::DataType dataType = Storage::DataType::NONE;
        return dataType;
    }
    void Clear() override {};
    void Delete(const std::string& key) override {};
};

class MockStorageImpl : public Storage {
    DECLARE_ACE_TYPE(MockStorageImpl, Storage);

public:
    MockStorageImpl();
    ~MockStorageImpl() override = default;
    void SetString(const std::string& key, const std::string& value) override {};
    std::string GetString(const std::string& key) override
    {
        return "false";
    }
    void SetDouble(const std::string& key, const double value) override {};
    bool GetDouble(const std::string& key, double& value) override
    {
        return false;
    }
    void SetBoolean(const std::string& key, const bool value) override {};
    bool GetBoolean(const std::string& key, bool& value) override
    {
        return false;
    }
    void Clear() override {};
    void Delete(const std::string& key) override {};
};

MockStorageImpl::MockStorageImpl() : Storage() {}

class MockStorageProxyImpl final : public StorageInterface {
public:
    MockStorageProxyImpl() = default;
    ~MockStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(int areaMode = -1) const override
    {
        return AceType::MakeRefPtr<MockStorageImpl>();
    }
};

class MockDistributedStorageProxyImpl final : public StorageInterface {
public:
    MockDistributedStorageProxyImpl() = default;
    ~MockDistributedStorageProxyImpl() override = default;

    RefPtr<Storage> GetStorage(const std::string& sessionId, std::function<void(const std::string&)>&& notifier,
        const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        return AceType::MakeRefPtr<MockDistributedStorage>(sessionId, taskExecutor);
    }
};
} // namespace OHOS::Ace
#endif