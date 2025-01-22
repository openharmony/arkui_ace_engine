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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_TYPE_HELPERS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_TYPE_HELPERS_H

#pragma once

#include "core/interfaces/native/utility/generated/converter_generated.h"

namespace OHOS::Ace::NG::TypeHelper {
template<typename T, typename = std::void_t<decltype(T().tag), decltype(T().value)>>
decltype(T().value)& WriteTo(T& value)
{
    value.tag = INTEROP_TAG_OBJECT;
    return value.value;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value0)>, int> = SELECTOR_ID_0>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_0;
    return value.value0;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value1)>, int> = SELECTOR_ID_1>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_1;
    return value.value1;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value2)>, int> = SELECTOR_ID_2>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_2;
    return value.value2;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value3)>, int> = SELECTOR_ID_3>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_3;
    return value.value3;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value4)>, int> = SELECTOR_ID_4>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_4;
    return value.value4;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value5)>, int> = SELECTOR_ID_5>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_5;
    return value.value5;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value6)>, int> = SELECTOR_ID_6>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_6;
    return value.value6;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value7)>, int> = SELECTOR_ID_7>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_7;
    return value.value7;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value8)>, int> = SELECTOR_ID_8>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_8;
    return value.value8;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value9)>, int> = SELECTOR_ID_9>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_9;
    return value.value9;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value10)>, int> = SELECTOR_ID_10>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_10;
    return value.value10;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value11)>, int> = SELECTOR_ID_11>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_11;
    return value.value11;
}
template<typename Which, typename To,
    std::enable_if_t<std::is_same_v<Which, decltype(To().value12)>, int> = SELECTOR_ID_12>
Which& WriteToUnion(To& value)
{
    value.selector = SELECTOR_ID_12;
    return value.value12;
}
} // namespace OHOS::Ace::NG::TypeHelper

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_TYPE_HELPERS_H
