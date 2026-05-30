/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_TIME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_TIME_H

#include <string>

#include "base/utils/utils.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT PickerTime final {
public:
    PickerTime() = default;
    PickerTime(uint32_t hour, uint32_t minute, uint32_t second) : hour_(hour), minute_(minute), second_(second) {}

    ~PickerTime() = default;

    ACE_FORCE_EXPORT static PickerTime Current();

    uint32_t GetHour() const
    {
        return hour_;
    }
    void SetHour(uint32_t value)
    {
        hour_ = value;
    }

    uint32_t GetMinute() const
    {
        return minute_;
    }
    void SetMinute(uint32_t value)
    {
        minute_ = value;
    }

    uint32_t GetSecond() const
    {
        return second_;
    }
    void SetSecond(uint32_t value)
    {
        second_ = value;
    }

    ACE_FORCE_EXPORT std::string ToString(bool jsonFormat, bool hasSecond, int32_t status = -1) const;
    uint32_t ToMinutes() const;

private:
    uint32_t hour_ = 0;
    uint32_t minute_ = 0;
    uint32_t second_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_TIME_H
