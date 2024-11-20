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

#ifndef OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CAnimatorOptions {
    int32_t duration;
    char* easing;
    int32_t delay;
    char* fill;
    char* direction;
    int32_t iterations;
    double begin;
    double end;
};

CJ_EXPORT int64_t FfiAnimatorCreate(CAnimatorOptions option);
CJ_EXPORT int32_t FfiAnimatorReset(int64_t id, CAnimatorOptions option);
CJ_EXPORT int32_t FfiAnimatorPlay(int64_t id);
CJ_EXPORT int32_t FfiAnimatorFinish(int64_t id);
CJ_EXPORT int32_t FfiAnimatorCancel(int64_t id);
CJ_EXPORT int32_t FfiAnimatorPause(int64_t id);
CJ_EXPORT int32_t FfiAnimatorReverse(int64_t id);
CJ_EXPORT int32_t FfiAnimatorOnframe(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOncancel(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnfinish(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnrepeat(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnFrame(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnCancel(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnFinish(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorOnRepeat(int64_t id, int64_t funcId);
CJ_EXPORT int32_t FfiAnimatorSetExpectedFrameRateRange(int64_t id, int32_t minVal, int32_t maxVal, int32_t exceptedVal);
}

#endif // #define OHOS_ACE_FRAMEWORK_CJ_ANIMATOR_FFI_H