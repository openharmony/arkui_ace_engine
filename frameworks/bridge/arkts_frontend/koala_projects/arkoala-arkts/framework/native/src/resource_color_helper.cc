/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define KOALA_INTEROP_MODULE ArkUINativeModule

#include "resource_color_helper.h"

#include "interop-logging.h"

namespace OHOS::Ace {
Ark_ResourceColor GetResourceColor(int64_t arrayBuff, int32_t length)
{
    Ark_ResourceColor value_buf = {};
    return value_buf;
}

std::vector<Ark_ResourceColor> GetResourceColorArray(int64_t thisArray, int32_t thisLength)
{
    Ark_ResourceColor value_buf = {};
    return { value_buf };
}

} // namespace OHOS::Ace
