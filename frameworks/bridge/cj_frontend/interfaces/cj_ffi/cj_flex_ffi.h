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

#ifndef OHOS_ACE_FRAMEWORK_CJ_FLEX_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_FLEX_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CJFlexParams {
    int32_t direction;
    int32_t wrap;
    int32_t justifyContent;
    int32_t alignItems;
    int32_t alignContent;
};

CJ_EXPORT void FfiOHOSAceFrameworkFlexCreate();
CJ_EXPORT void FfiOHOSAceFrameworkFlexCreateWithParams(CJFlexParams params);
CJ_EXPORT void FfiOHOSAceFrameworkFlexSetFlexWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkFlexSetFlexHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkFlexSetFlexSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
}

namespace OHOS::Ace {
void FlexCreateFlexComponent(CJFlexParams params);
void FlexCreateWrapComponent(CJFlexParams params);
} // namespace OHOS::Ace

#endif // OHOS_ACE_FRAMEWORK_CJ_FLEX_FFI_H
