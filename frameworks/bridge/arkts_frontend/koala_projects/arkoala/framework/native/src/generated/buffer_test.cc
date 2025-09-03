/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <cstdint>
#define KOALA_INTEROP_MODULE TestNativeModule
#include "common-interop.h"
#include "arkoala_api_generated.h"
#include "Serializers.h"

void impl_TestReadAndMutateManagedBuffer(uint8_t* thisArray, int32_t thisLength) {
    Deserializer thisDeserializer((KSerializerBuffer)thisArray, thisLength);
    Ark_Buffer buffer = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    buffer.resource.hold(buffer.resource.resourceId);
    for (int32_t i = 0; i < buffer.length; ++i) {
        uint8_t* array = reinterpret_cast<uint8_t*>(buffer.data);
        array[i] = array[i] * 2;
    }
    buffer.resource.release(buffer.resource.resourceId);
}
KOALA_INTEROP_V2(TestReadAndMutateManagedBuffer, KByte*, KInt)
