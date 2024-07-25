/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_TYPE_H

#include <cstdint>

namespace OHOS::Ace {

enum class TextInputType {
    BEGIN = -1,
    // Default type.
    UNSPECIFIED = BEGIN,
    TEXT = 0,
    // Specialized [TEXT] which support press Enter key to new line.
    MULTILINE = 1,
    NUMBER = 2,
    PHONE = 3,
    DATETIME = 4,
    EMAIL_ADDRESS = 5,
    URL = 6,
    VISIBLE_PASSWORD = 7,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    JS_ENUM_URL = 13,
    END = JS_ENUM_URL,
};

TextInputType CastToTextInputType(int32_t value);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_IME_TEXT_INPUT_TYPE_H
