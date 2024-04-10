/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_CONTENT_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_CONTENT_TYPE_H

#include <cstdint>

namespace OHOS::Ace::NG {
enum class TextContentType {
    BEGIN = -1,
    // Default type.
    UNSPECIFIED = BEGIN,
    USER_NAME = 0,
    VISIBLE_PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    PRECISE_TIME = 18,
    HOUR_AND_MINUTE = 19,
    DATE = 20,
    MONTH = 21,
    YEAR = 22,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25,
    END = FORMAT_ADDRESS,
};
TextContentType CastToTextContentType(int32_t value);
};      // namespace OHOS::Ace::NG
#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_CONTENT_TYPE_H