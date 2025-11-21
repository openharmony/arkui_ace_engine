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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_COMMON_MODIFIERS_TEST_UTILS_H

#include <string>
#include <tuple>

#include "frameworks/core/components_ng/base/frame_node.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
inline Ark_Object ArkCreate(int32_t id)
{
    return {
        .resource = {
            .resourceId = id,
            .hold = [](InteropInt32){},
            .release = [](InteropInt32){},
        }
    };
}
} // namespace Converter

// Resource functions
using NamedResourceId = std::tuple<const char *, ResourceType>;
using IntResourceId = std::tuple<uint32_t, ResourceType>;

Ark_Resource CreateResource(int64_t id, ResourceType type);
Ark_Resource CreateResource(const std::string& name, ResourceType type);

inline Ark_Resource CreateResource(NamedResourceId id)
{
    return CreateResource(std::get<0>(id), std::get<1>(id));
}

inline Ark_Resource CreateResource(IntResourceId id)
{
    return CreateResource(std::get<0>(id), std::get<1>(id));
}

template<typename T, typename U>
T CreateResourceUnion(const U& resId)
{
    return Converter::ArkUnion<T, Ark_Resource>(CreateResource(resId));
}

} // namespace OHOS::Ace::NG
#endif
