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

#ifndef INTERFACES_INNER_API_ACE_CONSTANTS_H
#define INTERFACES_INNER_API_ACE_CONSTANTS_H

namespace OHOS::Ace {
enum UIContentErrorCode : uint16_t {
    NO_ERRORS = 0,
    NULL_WINDOW,
    NULL_POINTER,
    PARSE_MANIFEST_FAILED,
    NULL_PAGE_ROUTER,
    STAGING_PAGE_EXIST,
    NULL_CARD_CALLBACK,
    NULL_CARD_RES,
    CARD_PAGE_NOT_READY,
    INVALID_PAGE_ID,
    NULL_URL,
    WRONG_PAGE_ROUTER,
    NO_STAGE,
    INVALID_URL,
};

enum class ContentInfoType : int32_t {
    NONE = 0,                        // invalid contentInfo
    CONTINUATION = 1,                // distribute
    APP_RECOVERY = 2,                // app recovery
    RESOURCESCHEDULE_RECOVERY = 3,   // app is killed due to resource schedule
};

enum class UIContentType {
    UNDEFINED,
    NORMA,                     // app
    FORM,                      // form
    UI_EXTENSION,              // ui extension
    SECURITY_UI_EXTENSION,     // security ui extension
};
} // namespace OHOS::Ace

#endif // INTERFACES_INNER_API_ACE_CONSTANTS_H
