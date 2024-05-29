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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_ffi.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

extern "C" {
void FfiOHOSAceFrameworkImageCreateWithUrl(const char* url) {}

void FfiOHOSAceFrameworkImageCreateWithPixelMap(int64_t id) {}

void FfiOHOSAceFrameworkImageSetAlt(const char* url) {}

void FfiOHOSAceFrameworkImageSetObjectFit(int32_t objectFit) {}

void FfiOHOSAceFrameworkImageSetObjectRepeat(int32_t objectRepeat) {}

void FfiOHOSAceFrameworkImageSetInterpolation(int32_t interpolation) {}

void FfiOHOSAceFrameworkImageSetRenderMode(int32_t renderMode) {}

void FfiOHOSAceFrameworkImageSetSourceSize(double width, int32_t widthUnit, double height, int32_t heightUnit) {}

void FfiOHOSAceFrameworkImageSetSyncLoad(bool syncLoad) {}

void FfiOHOSAceFrameworkImageSetImageFill(uint32_t color) {}

void FfiOHOSAceFrameworkImageSetAutoResize(bool autoResize) {}

void FfiOHOSAceFrameworkImageSetMatchTextDirection(bool isMatchTextDirection) {}

void FfiOHOSAceFrameworkImageSetFitOriginalSize(bool isFitOriginalSize) {}

void FfiOHOSAceFrameworkImageOnError(void (*callback)(CJImageError errorInfo)) {}

void FfiOHOSAceFrameworkImageOnFinish(void (*callback)()) {}

void FfiOHOSAceFrameworkImageOnComplete(void (*callback)(CJImageComplete completeInfo)) {}
}
