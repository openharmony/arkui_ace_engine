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

#ifndef OHOS_ACE_FRAMEWORK_CJ_ALPHABET_INDEXER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_ALPHABET_INDEXER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorStringPtr = void*;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerCreate(VectorStringPtr vecContent, int32_t selected);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerSelectedColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerSelectedBackgroundColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupBackground(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerUsingPopup(bool usingPop);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerSelectedFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerItemSize(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerAlignStyle(int32_t alignStyle);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerSelected(int32_t selected);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupPosition(double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerOnSelected(void (*callback)(int32_t idx));
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerOnRequestPopupData(VectorStringHandle (*callback)(int32_t idx));
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerOnPopupSelected(void (*callback)(int32_t idx));
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerAutoCollapse(bool autoCollapse);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupTitleBackground(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupItemBackground(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupUnselectedColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupSelectedColor(int32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupBackgroundBlurStyle(int32_t indexerBlurStyle);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupItemFont(double size, int32_t unit, const char* weight);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerItemBorderRadius(double radius);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerPopupItemBorderRadius(double radius);
CJ_EXPORT void FfiOHOSAceFrameworkAlphabetIndexerEnableHapticFeedback(bool state);
};
#endif // OHOS_ACE_FRAMEWORK_CJ_ALPHABET_INDEXER_FFI_H
