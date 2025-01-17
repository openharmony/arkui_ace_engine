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

#ifndef OHOS_ACE_FRAMEWORK_CJ_RELATIVE_CONTAINER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_RELATIVE_CONTAINER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
    struct CLength {
        double value;
        int32_t unit;
    };

    struct CGuideLinePosition {
        CLength start;
        CLength end;
    };

    struct CGuideLineStyle {
        char* id;
        int32_t direction;
        CGuideLinePosition position;
    };

    struct CGuideLineInfos {
        int64_t size;
        CGuideLineStyle* guideline;
    };

    struct CArrString {
        char** head;
        int64_t size;
    };

    struct CBarrierStyle {
        char* id;
        int32_t direction;
        CArrString referencedId;
    };

    struct CBarrierInfos {
        int64_t size;
        CBarrierStyle* barrier;
    };

    struct CLocalizedBarrierStyle {
        char* id;
        int32_t localizedDirection;
        CArrString referencedId;
    };

    struct CLocalizedBarrierInfos {
        int64_t size;
        CLocalizedBarrierStyle* localizedBarrier;
    };

    CJ_EXPORT void FfiOHOSAceFrameworkRelativeContainerCreate();
    CJ_EXPORT void FfiOHOSAceFrameworkReletiveContainerGuideLine(CGuideLineInfos guidelines);
    CJ_EXPORT void FfiOHOSAceFrameworkReletiveContainerBarrier(CBarrierInfos barriers);
    CJ_EXPORT void FfiOHOSAceFrameworkReletiveContainerLocalizedBarrier(CLocalizedBarrierInfos barriers);
}
#endif // OHOS_ACE_FRAMEWORK_CJ_RELATIVE_CONTAINER_FFI_H
