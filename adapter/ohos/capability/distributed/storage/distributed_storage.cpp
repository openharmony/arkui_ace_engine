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

#include "adapter/ohos/capability/distributed/storage/distributed_storage.h"

#include "distributed_object.h"
#include "distributed_objectstore.h"
#include "objectstore_errors.h"

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace {

class DistributedObjectWatcher final : public OHOS::ObjectStore::ObjectWatcher {
public:
    explicit DistributedObjectWatcher(OnDataChangeCallback&& onChange)
    {
        onChange_ = std::move(onChange);
    }

    void OnChanged(const std::string& sessionid, const std::vector<std::string>& changedData) override
    {
        CHECK_NULL_VOID_NOLOG(onChange_);
        onChange_(sessionid, changedData);
    }

private:
    OnDataChangeCallback onChange_;
};

class DistributedObjectStatusNotifier final : public OHOS::ObjectStore::StatusNotifier {
public:
    explicit DistributedObjectStatusNotifier(ObjectStatusNotifyCallback&& onNotify)
    {
        onNotify_ = std::move(onNotify);
    }
    void OnChanged(const std::string& sessionId, const std::string& networkId, const std::string& onlineStatus) override
    {
        LOGI("DistributedObjectStatusNotifier [%{public}s-%{public}s]", sessionId.c_str(), onlineStatus.c_str());
        CHECK_NULL_VOID_NOLOG(onNotify_);
        onNotify_(sessionId, onlineStatus);
    }

private:
    ObjectStatusNotifyCallback onNotify_;
};

DistributedObjectPtr::DistributedObjectPtr(const std::string& sessionId, OnDataChangeCallback&& onChange)
{
    std::string bundleName = AceApplicationInfo::GetInstance().GetProcessName();
    if (bundleName.empty()) {
        LOGE("DistributedObjectStore bundleName is empty!");
        return;
    }
    OHOS::ObjectStore::DistributedObjectStore* store =
        OHOS::ObjectStore::DistributedObjectStore::GetInstance(bundleName);
    CHECK_NULL_VOID(store);
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [store]() {
        auto callback = [](const std::string& sessionId, const std::string& onlineStatus) {
            DistributedStorage::OnStatusNotify(sessionId, onlineStatus);
        };
        store->SetStatusNotifier(std::make_shared<DistributedObjectStatusNotifier>(callback));
    });

    uint32_t ret = store->Get(sessionId, &object_);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGW("DistributedObjectStore get object[%{private}s] failed, try to create", sessionId.c_str());
        object_ = store->CreateObject(sessionId);
        CHECK_NULL_VOID(object_);
    }

    sessionId_ = sessionId;
    watcher_ = std::make_shared<DistributedObjectWatcher>(std::move(onChange));
    ret = store->Watch(object_, watcher_);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("DistributedObjectStore Watch failed!, err=[%{private}u", ret);
    }
    LOGI("DistributedObjectPtr init success[%{public}s]", sessionId_.c_str());
    invalid_ = false;
}

DistributedObjectPtr::~DistributedObjectPtr()
{
    if (object_ != nullptr) {
        std::string bundleName = AceApplicationInfo::GetInstance().GetProcessName();
        OHOS::ObjectStore::DistributedObjectStore* store =
            OHOS::ObjectStore::DistributedObjectStore::GetInstance(bundleName);
        CHECK_NULL_VOID(store);
        uint32_t ret = store->UnWatch(object_);
        if (ret != OHOS::ObjectStore::SUCCESS) {
            LOGE("DistributedObjectStore UnWatch failed!, err=[%{private}u]", ret);
        }
        ret = store->DeleteObject(sessionId_);
        if (ret != OHOS::ObjectStore::SUCCESS) {
            LOGE("DistributedObjectStore DeleteObject failed!, err=[%{private}u]", ret);
        }
    }
    DistributedStorage::DeleteStorage(sessionId_);
}

OHOS::ObjectStore::DistributedObject* DistributedObjectPtr::GetRawPtr()
{
    return object_;
}

std::map<std::string, RefPtr<DistributedStorage>> DistributedStorage::storageMap_;

void DistributedStorage::AddStorage(const std::string& sessionId, RefPtr<DistributedStorage> storage)
{
    storageMap_.try_emplace(sessionId, storage);
}

void DistributedStorage::DeleteStorage(const std::string& sessionId)
{
    storageMap_.erase(sessionId);
}

void DistributedStorage::OnStatusNotify(const std::string& sessionId, const std::string& status)
{
    auto storage = storageMap_.find(sessionId);
    if (storage != storageMap_.end()) {
        storage->second->NotifyStatus(status);
    }
}

bool DistributedStorage::Init(std::function<void(const std::string&)>&& notifyCallback)
{
    notifyCallback_ = std::move(notifyCallback);
    auto onChangeCallback = [weak = WeakClaim(this)](
                                const std::string& sessionid, const std::vector<std::string>& changedData) {
        auto storage = weak.Upgrade();
        for (auto& key : changedData) {
            storage->OnDataChange(key);
        }
    };
    objectPtr_ = std::make_unique<DistributedObjectPtr>(sessionId_, std::move(onChangeCallback));

    return true;
}

void DistributedStorage::SetString(const std::string& key, const std::string& value)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Set string failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return;
    }

    auto ret = objectPtr_->GetRawPtr()->PutString(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Set string failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
    }
}

std::string DistributedStorage::GetString(const std::string& key)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Get string failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return "";
    }
    std::string value;
    auto ret = objectPtr_->GetRawPtr()->GetString(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Get string failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
    }
    return value;
}

void DistributedStorage::SetDouble(const std::string& key, const double value)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Set double failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return;
    }
    auto ret = objectPtr_->GetRawPtr()->PutDouble(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Set double failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
    }
}

bool DistributedStorage::GetDouble(const std::string& key, double& value)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Get double failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return false;
    }
    auto ret = objectPtr_->GetRawPtr()->GetDouble(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Get double failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
        return false;
    }
    return true;
}

void DistributedStorage::SetBoolean(const std::string& key, const bool value)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Set boolean failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return;
    }
    auto ret = objectPtr_->GetRawPtr()->PutBoolean(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Set boolean failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
    }
}

bool DistributedStorage::GetBoolean(const std::string& key, bool& value)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Get boolean failed, distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return false;
    }
    auto ret = objectPtr_->GetRawPtr()->GetBoolean(key, value);
    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Get boolean failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
        return false;
    }
    return true;
}

Storage::DataType DistributedStorage::GetDataType(const std::string& key)
{
    if (objectPtr_->IsInvalid()) {
        LOGE("Get type failed! distributed object is invalid! sessionId=[%{private}s], key=[%{private}s]",
            sessionId_.c_str(), key.c_str());
        return Storage::DataType::NONE;
    }
    OHOS::ObjectStore::Type type = OHOS::ObjectStore::Type::TYPE_STRING;
    auto ret = objectPtr_->GetRawPtr()->GetType(key, type);

    if (ret != OHOS::ObjectStore::SUCCESS) {
        LOGE("Get type failed! sessionId=[%{private}s], key=[%{private}s], err=[%{private}u]", sessionId_.c_str(),
            key.c_str(), ret);
        return Storage::DataType::NONE;
    }

    Storage::DataType dataType = Storage::DataType::NONE;
    switch (type) {
        case OHOS::ObjectStore::Type::TYPE_STRING:
            dataType = Storage::DataType::STRING;
            break;
        case OHOS::ObjectStore::Type::TYPE_BOOLEAN:
            dataType = Storage::DataType::BOOLEAN;
            break;
        case OHOS::ObjectStore::Type::TYPE_DOUBLE:
            dataType = Storage::DataType::DOUBLE;
            break;
        default:
            break;
    }
    return dataType;
}

void DistributedStorage::NotifyStatus(const std::string& status)
{
    CHECK_NULL_VOID_NOLOG(taskExecutor_);
    LOGI("DistributedStorage::NotifyStatus [%{public}s-%{public}s]", sessionId_.c_str(), status.c_str());
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), status] {
            auto storage = weak.Upgrade();
            if (storage && storage->notifyCallback_) {
                storage->notifyCallback_(status);
            }
        },
        TaskExecutor::TaskType::JS);
}

} // namespace OHOS::Ace