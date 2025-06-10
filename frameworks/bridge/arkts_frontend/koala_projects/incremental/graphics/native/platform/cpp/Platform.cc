/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "common-interop.h"

KInt impl_skoala_Platform_currentOS() {
#ifdef SK_BUILD_FOR_OHOS
    return 1;
#endif
#ifdef SK_BUILD_FOR_ANDROID
    return 3;
#endif
#ifdef SK_BUILD_FOR_LINUX
    return 4;
#endif
#ifdef SK_BUILD_FOR_WIN
    return 5;
#endif
#ifdef SK_BUILD_FOR_MAC
    return 6;
#endif
#ifdef SK_BUILD_FOR_IOS
    return 7;
#endif
#ifdef KOALA_WASM
    return 8;
#endif
    return 0;
}
KOALA_INTEROP_0(skoala_Platform_currentOS, KInt)

KInt impl_skoala_Platform_currentCPU() {
#ifdef KOALA_WASM
    return 1;
#endif
#if defined(__x86_64__) || defined(_M_X64)
    return 2;
#endif
#if defined(__arm64__) || defined(__aarch64__)
    return 3;
#endif
#if defined(__arm__)
    return 4;
#endif
    return 0;
}
KOALA_INTEROP_0(skoala_Platform_currentCPU, KInt)
