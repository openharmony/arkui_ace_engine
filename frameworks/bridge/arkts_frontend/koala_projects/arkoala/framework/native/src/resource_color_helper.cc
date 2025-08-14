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

#include "Serializers.h"
#include "interop-logging.h"

namespace OHOS::Ace {
std::vector<Ark_ResourceColor> GetResourceColorArray(int64_t thisArray, int32_t thisLength)
{
    Deserializer thisDeserializer(reinterpret_cast<KSerializerBuffer>(thisArray), static_cast<int32_t>(thisLength));
    auto colorArraySize = thisDeserializer.readInt32();
    std::vector<Ark_ResourceColor> array_resource_color_buf;
    for (int i = 0; i < colorArraySize; i++) {
        Ark_ResourceColor value_buf = DeserializerResourceColor(thisDeserializer);
        array_resource_color_buf.push_back(value_buf);
    }

    return array_resource_color_buf;
}

Ark_ResourceColor DeserializerResourceColor(Deserializer& deserializer)
{
    const Ark_Int8 value_buf_selector = deserializer.readInt8();
    Ark_ResourceColor value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        value_buf.value0 = static_cast<Ark_Color>(deserializer.readInt32());
    } else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        value_buf.value1 = static_cast<Ark_Number>(deserializer.readNumber());
    } else if (value_buf_selector == 2) {
        value_buf.selector = 2;
        value_buf.value2 = static_cast<Ark_String>(deserializer.readString());
    } else if (value_buf_selector == 3) {
        value_buf.selector = 3;
        value_buf.value3 = deserializer.readResource();
    } else {
        LOGI("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    return value_buf;
}
} // namespace OHOS::Ace
