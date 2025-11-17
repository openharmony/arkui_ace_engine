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

namespace OHOS::Ace::NG {
Ark_Resource CreateResource(int64_t id, ResourceType type)
{
    return Converter::ArkCreate<Ark_Resource>(id, type);
}

Ark_Resource CreateResource(const std::string& name, ResourceType type)
{
    static Converter::ConvContext s_ctx;
    return Converter::ArkCreate<Ark_Resource>(name, type, &s_ctx);
}
} // namespace OHOS::Ace::NG
