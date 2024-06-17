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

#ifndef OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkImageCreateWithUrl(const char* url);
CJ_EXPORT void FfiOHOSAceFrameworkImageCreateWithPixelMap(int64_t pixelMapId);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetAlt(const char* url);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetObjectFit(int32_t objectFit);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetObjectRepeat(int32_t objectRepeat);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetInterpolation(int32_t interpolation);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetRenderMode(int32_t renderMode);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetSourceSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetSyncLoad(bool syncLoad);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetBorderRadius();
CJ_EXPORT void FfiOHOSAceFrameworkImageSetImageFill(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetAutoResize(bool autoResize);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetMatchTextDirection(bool isMatchTextDirection);
CJ_EXPORT void FfiOHOSAceFrameworkImageSetFitOriginalSize(bool isFitOriginalSize);
CJ_EXPORT void FfiOHOSAceFrameworkImageOnError(void (*callback)(CJImageError errorInfo));
CJ_EXPORT void FfiOHOSAceFrameworkImageOnFinish(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkImageOnComplete(void (*callback)(CJImageComplete completeInfo));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H
