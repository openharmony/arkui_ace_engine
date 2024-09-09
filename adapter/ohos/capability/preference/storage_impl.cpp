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

#include "storage_impl.h"

namespace OHOS::Ace {
std::shared_ptr<NativePreferences::Preferences> StorageImpl::GetPreference(const std::string& fileName)
{
    auto it = preferences_.find(fileName);
    if (it != preferences_.end()) {
        return it->second;
    }
    auto pref = NativePreferences::PreferencesHelper::GetPreferences(fileName, errCode_);
    preferences_.insert(std::make_pair(fileName, pref));
    return pref;
}

void StorageImpl::SetString(const std::string& key, const std::string& value)
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_VOID(pref);
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "Set preference with key %{public}s, value %{public}s",
        key.c_str(), value.c_str());
    pref->PutString(key, value);
    pref->Flush();
}

std::string StorageImpl::GetString(const std::string& key)
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_RETURN(pref, "");
    LOGD("Get preference with key %{public}s", key.c_str());
    return pref->GetString(key, "");
}

void StorageImpl::Clear()
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_VOID(pref);
    pref->Clear();
    LOGD("StorageImpl: Clear preferences");
    NativePreferences::PreferencesHelper::DeletePreferences(fileName_);
    preferences_.erase(fileName_);
}

void StorageImpl::Delete(const std::string& key)
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_VOID(pref);
    LOGD("StorageImpl: Delete preference with key %{public}s", key.c_str());
    pref->Delete(key);
    pref->FlushSync();
}

RefPtr<Storage> StorageProxyImpl::GetStorage() const
{
    return AceType::MakeRefPtr<StorageImpl>();
}
} // namespace OHOS::Ace