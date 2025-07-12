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

#include "accessor_test_utils.h"

#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

namespace OHOS::Ace::NG {
Ark_Resource CreateResource(uint32_t id, OHOS::Ace::NG::Converter::ResourceType type)
{
    return {
        .id = Converter::ArkValue<Ark_Number>(id),
        .type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(type)),
        .moduleName = Converter::ArkValue<Ark_String>(""),
        .bundleName = Converter::ArkValue<Ark_String>(""),
        .params = Converter::ArkValue<Opt_Array_String>(),
    };
}

Ark_Resource CreateResource(const char *name, OHOS::Ace::NG::Converter::ResourceType type)
{
    static std::vector<std::unique_ptr<Ark_String>> s_strCache;
    s_strCache.emplace_back(std::make_unique<Ark_String>(Converter::ArkValue<Ark_String>(name)));
    Array_String params = {.length = 1, .array = s_strCache.back().get()};
    return {
        .id = Converter::ArkValue<Ark_Number>(-1),
        .type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(type)),
        .moduleName = Converter::ArkValue<Ark_String>(""),
        .bundleName = Converter::ArkValue<Ark_String>(""),
        .params = Converter::ArkValue<Opt_Array_String>(params),
    };
}

} // namespace OHOS::Ace::NG
