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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATA_H

#include <cstdint>

#include "base/utils/utils.h"

#include "core/components_ng/pattern/date_picker/picker_date.h"
#include "core/components_ng/pattern/date_picker/picker_time.h"
#include "core/components_ng/pattern/date_picker/picker_types.h"

namespace OHOS::Ace {

class LunarCalculator {
public:
    static uint32_t GetLunarLeapMonth(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t leapMonth = LUNAR_INFO[lunarYear - YEAR_START] & 0xf; // use 0xf to get leap month info
        return leapMonth == 0xf ? 0 : leapMonth;
    }

    static uint32_t GetLunarLeapDays(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START - 1 + LUNAR_INFO_SIZE) {
            return 0;
        }
        return GetLunarLeapMonth(lunarYear) > 0
                    ? ((LUNAR_INFO[lunarYear - YEAR_START + 1] & 0xf) == 0xf ? NUM_30 : NUM_29)
                    : 0; // big month 30 days other 29
    }

    static uint32_t GetLunarYearDays(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t totalDays = 348;                          // lunar year has (12 * 29 =) 348 days at least
        for (uint32_t i = 0x8000; i > 0x8; i >>= 1) { // get month info from bit of LUNAR_INFO
            totalDays += ((LUNAR_INFO[lunarYear - YEAR_START] & i) != 0) ? 1 : 0;
        }

        return totalDays + GetLunarLeapDays(lunarYear);
    }

    static uint32_t GetLunarMonthDays(uint32_t lunarYear, uint32_t lunarMonth)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t month = static_cast<uint32_t>(lunarMonth);
        // big month 30 days other 29
        return ((LUNAR_INFO[lunarYear - YEAR_START] & (0x10000u >> (month % MAX_MONTH))) != 0) ? NUM_30 : NUM_29;
    }

private:
    static constexpr uint32_t YEAR_START = 1897; // start year reference with LUNAR_INFO
    static constexpr int32_t LUNAR_INFO_SIZE = 207;
    static constexpr uint32_t MAX_MONTH = 13;
    static constexpr int NUM_29 = 29;
    static constexpr int NUM_30 = 30;
    ACE_FORCE_EXPORT static const uint16_t LUNAR_INFO[];
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATA_H
