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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BASE_RESOURCE_DATA_PROVIDER_MANAGER_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BASE_RESOURCE_DATA_PROVIDER_MANAGER_H

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <type_traits>

#include "base/memory/ace_type.h"
#include "base/resource/data_ability_helper.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

class DataProviderRes {
public:
    DataProviderRes(std::unique_ptr<void, decltype(&std::free)>&& data, int64_t size)
        : data_(std::move(data)), size_(size)
    {}
    ~DataProviderRes() = default;

    std::unique_ptr<void, decltype(&std::free)>&& GetData()
    {
        return std::move(data_);
    }
    int64_t GetSize() const
    {
        return size_;
    }

private:
    std::unique_ptr<void, decltype(&std::free)> data_;
    int64_t size_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(DataProviderRes);
};

class DataProviderManagerInterface : public AceType {
    DECLARE_ACE_TYPE(DataProviderManagerInterface, AceType)

public:
    DataProviderManagerInterface() = default;
    ~DataProviderManagerInterface() override = default;

    virtual std::unique_ptr<DataProviderRes> GetDataProviderResFromUri(const std::string& uriStr) = 0;
    virtual void* GetDataProviderThumbnailResFromUri(const std::string& uriStr) = 0;
    virtual int32_t GetDataProviderFile(const std::string& uriStr, const std::string& mode) = 0;

    ACE_DISALLOW_COPY_AND_MOVE(DataProviderManagerInterface);
};

using DataProviderImpl = std::function<std::unique_ptr<DataProviderRes>(const std::string& uriStr)>;
class DataProviderManager : public DataProviderManagerInterface {
    DECLARE_ACE_TYPE(DataProviderManager, DataProviderManagerInterface)
public:
    explicit DataProviderManager(DataProviderImpl dataProvider) : platformImpl_(std::move(dataProvider)) {}
    ~DataProviderManager() override = default;

    std::unique_ptr<DataProviderRes> GetDataProviderResFromUri(const std::string& uriStr) override;
    void* GetDataProviderThumbnailResFromUri(const std::string& /* uriStr */) override
    {
        return nullptr;
    };
    int32_t GetDataProviderFile(const std::string& /* uriStr */, const std::string& /* mode */) override
    {
        return -1;
    }

private:
    DataProviderImpl platformImpl_;

    ACE_DISALLOW_COPY_AND_MOVE(DataProviderManager);
};

using DataAbilityHelperImpl = std::function<RefPtr<DataAbilityHelper>()>;
class ACE_FORCE_EXPORT DataProviderManagerStandard : public DataProviderManagerInterface {
    DECLARE_ACE_TYPE(DataProviderManagerStandard, DataProviderManagerInterface)

public:
    explicit DataProviderManagerStandard(DataAbilityHelperImpl dataAbilityHelperImpl)
        : dataAbilityHelperImpl_(std::move(dataAbilityHelperImpl))
    {}

    ~DataProviderManagerStandard() override = default;

    std::unique_ptr<DataProviderRes> GetDataProviderResFromUri(const std::string& uriStr) override;
    void* GetDataProviderThumbnailResFromUri(const std::string& uriStr) override;

    int32_t GetDataProviderFile(const std::string& uriStr, const std::string& mode) override;
    int32_t ReadMovingPhotoVideo(const std::string &uri);
    std::string GetMovingPhotoImageUri(const std::string& uri);
    int64_t GetMovingPhotoDateModified(const std::string& uri);

private:
    void InitHelper();

    std::shared_mutex helperMutex_;
    DataAbilityHelperImpl dataAbilityHelperImpl_;
    RefPtr<DataAbilityHelper> helper_;

    ACE_DISALLOW_COPY_AND_MOVE(DataProviderManagerStandard);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BASE_RESOURCE_DATA_PROVIDER_MANAGER_H
