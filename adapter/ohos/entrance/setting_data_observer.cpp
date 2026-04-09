/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/setting_data_observer.h"

#include "core/common/setting_data_manager.h"

namespace OHOS::Ace {

SettingDataObserver::SettingDataObserver() : userId_(SettingDataManager::INVALID_USER_ID) {}

void SettingDataObserver::OnChange()
{
    if (updateFunc_) {
        updateFunc_(key_, userId_);
    }
}

void SettingDataObserver::SetKey(const std::string& key)
{
    key_ = key;
}

const std::string& SettingDataObserver::GetKey() const
{
    return key_;
}

void SettingDataObserver::SetUpdateFunc(const UpdateFunc& updateFunc)
{
    updateFunc_ = updateFunc;
}

void SettingDataObserver::SetUserId(const int32_t userId)
{
    userId_ = userId;
}

int32_t SettingDataObserver::GetUserId() const
{
    return userId_;
}
} // namespace OHOS::Ace
