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

#ifndef FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_RES_DATA_STRUCT_H
#define FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_RES_DATA_STRUCT_H

#include <string>
#include <unordered_map>

#include "base/utils/system_properties.h"

namespace OHOS::Ace {
enum class KeyType : int32_t {
    MCC = 0,
    MNC = 1,
    MNC_SHORT_LEN = 2,
    ORIENTATION = 3,
    COLOR_MODE = 4,
    DEVICETYPE = 5,
    RESOLUTION = 6,
};

struct KeyParam {
    KeyType keyType;
    int32_t value;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_COMMON_CPP_ACE_RES_DATA_STRUCT_H