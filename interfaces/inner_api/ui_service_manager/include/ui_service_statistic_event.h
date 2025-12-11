/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_STATISTIC_EVENT_H
#define FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_STATISTIC_EVENT_H

#include <map>
#include <queue>
#include <string>

#include "parcel.h"

namespace OHOS::Ace {

class AppInfoParcel : public Parcelable {
public:
    AppInfoParcel() = default;
    AppInfoParcel(const std::string& bundleName);
    bool Marshalling(Parcel& parcel) const override;
    static AppInfoParcel *Unmarshalling(Parcel& parcel);
    const std::string& GetBundleName() const;
private:
    std::string bundleName_;
};

struct StatisticEventInfoParcel : public Parcelable {
public:
    StatisticEventInfoParcel() = default;
    StatisticEventInfoParcel(const std::string& eventName, int32_t eventCount);
    bool Marshalling(Parcel& parcel) const override;
    static StatisticEventInfoParcel *Unmarshalling(Parcel& parcel);
    const std::string& GetEventName() const;
    int32_t GetEventCount() const;
    void SetEventCount(int32_t count);
private:
    std::string eventName_;
    int32_t eventCount_ = 0;
};
} // namespace OHOS::Ace
#endif  // FOUNDATION_ARKUI_ACE_ENGINE_INTERFACES_INNER_API_UI_SERVICE_MANAGER_UI_SERVICE_STATISTIC_EVENT_H