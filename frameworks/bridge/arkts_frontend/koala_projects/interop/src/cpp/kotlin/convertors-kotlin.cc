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

#include "koala-types.h"
#include "common-interop.h"
#include "interop-logging.h"

typedef KInt (*KoalaCallbackDispatcher_t)(KInt id, KInt length, KSerializerBuffer buffer);
static KoalaCallbackDispatcher_t g_koalaKotlinCallbackDispatcher = nullptr;

void callKoalaKotlinCallbackVoid(KInt id, KInt length, KSerializerBuffer buffer) {
    g_koalaKotlinCallbackDispatcher(id, length, buffer);
}

KInt callKoalaKotlinCallbackInt(KInt id, KInt length, KSerializerBuffer buffer) {
    return g_koalaKotlinCallbackDispatcher(id, length, buffer);
}

void impl_SetKoalaKotlinCallbackDispatcher(KNativePointer ptr) {
    g_koalaKotlinCallbackDispatcher = reinterpret_cast<KoalaCallbackDispatcher_t>(ptr);
}
KOALA_INTEROP_V1(SetKoalaKotlinCallbackDispatcher, KNativePointer)
