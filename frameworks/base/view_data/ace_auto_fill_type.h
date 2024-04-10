/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
enum class AceAutoFillType {
    ACE_UNSPECIFIED = 0,
    ACE_PASSWORD,
    ACE_USER_NAME,
    ACE_NEW_PASSWORD,
    ACE_FULL_STREET_ADDRESS,
    ACE_HOUSE_NUMBER,
    ACE_DISTRICT_ADDRESS,
    ACE_CITY_ADDRESS,
    ACE_PROVINCE_ADDRESS,
    ACE_COUNTRY_ADDRESS,
    ACE_PERSON_FULL_NAME,
    ACE_PERSON_LAST_NAME,
    ACE_PERSON_FIRST_NAME,
    ACE_PHONE_NUMBER,
    ACE_PHONE_COUNTRY_CODE,
    ACE_FULL_PHONE_NUMBER,
    ACE_EMAIL_ADDRESS,
    ACE_BANK_CARD_NUMBER,
    ACE_ID_CARD_NUMBER,
    ACE_PRECISE_TIME,
    ACE_HOUR_AND_MINUTE,
    ACE_DATE,
    ACE_MONTH,
    ACE_YEAR,
    ACE_NICKNAME,
    ACE_DETAIL_INFO_WITHOUT_STREET,
    ACE_FORMAT_ADDRESS,
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H