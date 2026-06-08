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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_TIME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_TIME_H

#include <string>

#include "core/components_ng/pattern/picker/picker_date.h"
#include "core/components_ng/pattern/picker/picker_time.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT PickerDateTime final {
public:
    PickerDateTime() = default;
    PickerDateTime(const PickerDate& date, const PickerTime& time) : date_(date), time_(time) {}

    ~PickerDateTime() = default;

    ACE_FORCE_EXPORT static PickerDateTime Current();

    const PickerDate& GetDate() const
    {
        return date_;
    }
    void SetDate(const PickerDate& value)
    {
        date_ = value;
    }

    const PickerTime& GetTime() const
    {
        return time_;
    }
    void SetTime(const PickerTime& value)
    {
        time_ = value;
    }

    ACE_FORCE_EXPORT std::string ToString(bool jsonFormat, int32_t status = -1) const;

private:
    PickerDate date_;
    PickerTime time_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_TIME_H
