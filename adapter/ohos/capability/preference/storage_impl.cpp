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
#include "application_context.h"

namespace OHOS::Ace {
StorageImpl::StorageImpl(int areaMode) : Storage()
{
    std::string fileName = "";
    // areaMode >= 0 means using global path
    if (areaMode >= 0) {
        auto appContext = OHOS::AbilityRuntime::Context::GetApplicationContext();
        if (appContext != nullptr) {
            auto defaultAreaMode = appContext->GetArea();
            appContext->SwitchArea(areaMode);
            fileName = appContext->GetFilesDir();
            appContext->SwitchArea(defaultAreaMode);
        } else {
            LOGE("appContext get failed in StorageImpl.");
        }
    } else {
        // areaMode < 0 means using module path
        fileName = AceApplicationInfo::GetInstance().GetDataFileDirPath();
    }
    if (fileName.empty()) {
        LOGE("Cannot get storage date file path.");
    }
    fileName_ = fileName + "/persistent_storage";
};

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
    pref->PutString(key, value);
    pref->Flush();
}

std::string StorageImpl::GetString(const std::string& key)
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_RETURN(pref, "");
    return pref->GetString(key, "");
}

void StorageImpl::Clear()
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_VOID(pref);
    pref->Clear();
    NativePreferences::PreferencesHelper::DeletePreferences(fileName_);
    preferences_.erase(fileName_);
}

void StorageImpl::Delete(const std::string& key)
{
    std::shared_ptr<NativePreferences::Preferences> pref = GetPreference(fileName_);
    CHECK_NULL_VOID(pref);
    pref->Delete(key);
    pref->FlushSync();
}

RefPtr<Storage> StorageProxyImpl::GetStorage(int areaMode) const
{
    return AceType::MakeRefPtr<StorageImpl>(areaMode);
}
} // namespace OHOS::Ace