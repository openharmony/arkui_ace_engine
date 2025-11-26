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

#include "ui_service_statistic_event.h"

namespace OHOS::Ace {
AppInfoParcel::AppInfoParcel(const std::string& bundleName, const std::string& abilityName,
    const std::string& versionName, const std::string& versionCode)
{
    bundleName_ = bundleName;
    abilityName_ = abilityName;
    versionName_ = versionName;
    versionCode_ = versionCode;
}

const std::string& AppInfoParcel::GetBundleName() const
{
    return bundleName_;
}

const std::string& AppInfoParcel::GetAbilityName() const
{
    return abilityName_;
}

const std::string& AppInfoParcel::GetVersionName() const
{
    return versionName_;
}

const std::string& AppInfoParcel::GetVersionCode() const
{
    return versionCode_;
}

bool AppInfoParcel::Marshalling(Parcel& parcel) const
{
    if (!parcel.WriteString(bundleName_)) {
        return false;
    }
    if (!parcel.WriteString(abilityName_)) {
        return false;
    }
    if (!parcel.WriteString(versionName_)) {
        return false;
    }
    if (!parcel.WriteString(versionCode_)) {
        return false;
    }
    return true;
}

AppInfoParcel *AppInfoParcel::Unmarshalling(Parcel& parcel)
{
    std::string bundleName;
    if (!parcel.ReadString(bundleName)) {
        return nullptr;
    }
    std::string abilityName;
    if (!parcel.ReadString(abilityName)) {
        return nullptr;
    }
    std::string versionName;
    if (!parcel.ReadString(versionName)) {
        return nullptr;
    }
    std::string versionCode;
    if (!parcel.ReadString(versionCode)) {
        return nullptr;
    }
    AppInfoParcel* appInfoParcel = new AppInfoParcel(bundleName, abilityName, versionName, versionCode);
    return appInfoParcel;
}

bool AppInfoParcel::EqualTo(const AppInfoParcel& appInfo)
{
    return GetBundleName() == appInfo.GetBundleName() &&
        GetAbilityName() == appInfo.GetAbilityName() &&
        GetVersionName() == appInfo.GetVersionName() &&
        GetVersionCode() == appInfo.GetVersionCode();
}

StatisticEventInfoParcel::StatisticEventInfoParcel(const std::string& eventName, int32_t eventCount)
{
    eventName_ = eventName;
    eventCount_ = eventCount;
}

bool StatisticEventInfoParcel::Marshalling(Parcel& parcel) const
{
    if (!parcel.WriteString(eventName_)) {
        return false;
    }
    if (!parcel.WriteInt32(eventCount_)) {
        return false;
    }
    return true;
}

StatisticEventInfoParcel *StatisticEventInfoParcel::Unmarshalling(Parcel& parcel)
{
    std::string eventName;
    if (!parcel.ReadString(eventName)) {
        return nullptr;
    }
    int32_t eventCount;
    if (!parcel.ReadInt32(eventCount)) {
        return nullptr;
    }
    StatisticEventInfoParcel* statisticEventParcel = new StatisticEventInfoParcel(eventName, eventCount);
    return statisticEventParcel;
}

const std::string& StatisticEventInfoParcel::GetEventName() const
{
    return eventName_;
}

int32_t StatisticEventInfoParcel::GetEventCount() const
{
    return eventCount_;
}

void StatisticEventInfoParcel::SetEventCount(int32_t count)
{
    eventCount_ = count;
}
}