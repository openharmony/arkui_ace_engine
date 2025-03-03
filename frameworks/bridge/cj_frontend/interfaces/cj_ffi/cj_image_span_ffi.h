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

#ifndef OHOS_ACE_FRAMEWORK_CJ_IMAGE_SPAN_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_IMAGE_SPAN_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_ffi.h"

struct CBorderRadiuses {
    double topLeftRadiuses;
    int32_t topLeftUnit;
    double topRightRadiuses;
    int32_t topRightUnit;
    double bottomLeftRadiuses;
    int32_t bottomLeftUnit;
    double bottomRightRadiuses;
    int32_t bottomRightUnit;
};

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanCreateWithUrl(const char* url);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanCreateWithPixelMap(int64_t pixelMapId);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanVerticalAlign(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanObjectFit(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanTextBackgroundStyle(uint32_t color, double radius, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanTextBackgroundStyleBorder(uint32_t color, CBorderRadiuses radius);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanSetColorFilter(void* vectorHandle);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanAlt(int64_t pixelMapId);
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanOnComplete(void (*callback)(CJImageComplete completeInfo));
CJ_EXPORT void FfiOHOSAceFrameworkImageSpanOnError(void (*callback)(CJImageError errorInfo));
}
 
#endif // OHOS_ACE_FRAMEWORK_CJ_IMAGE_SPAN_FFI_H
