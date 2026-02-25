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

#ifndef OHOS_ACE_FRAMEWORK_CJ_BADGE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_BADGE_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CJBadgeStyle {
    uint32_t color;
    double fontSize;
    double badgeSize;
    uint32_t badgeColor;
};

struct CJBadgeStyleV2 {
    uint32_t color;
    double fontSize;
    double badgeSize;
    uint32_t badgeColor;
    uint32_t fontWeight;
    uint32_t borderColor;
    double borderWidth;
    uint32_t borderWidthUnit;
};

struct CJBadgeStyleV3 {
    uint32_t color;
    double fontSize;
    int32_t fontSizeUnit;
    double badgeSize;
    int32_t badgeSizeUnit;
    uint32_t badgeColor;
    char* fontWeight;
    uint32_t borderColor;
    double borderWidth;
    int32_t borderWidthUnit;
    uint32_t outerBorderColor;
    double outerBorderWidth;
    uint32_t outerBorderWidthUnit;
    bool enableAutoAvoidance;
};

CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreate(int32_t count, CJBadgeStyle style, int32_t position, int32_t maxCount);
CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreateV2(
    int32_t count, CJBadgeStyleV2 style, int32_t position, int32_t maxCount);
CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreateV3(
    int32_t count, CJBadgeStyleV3 style, int32_t position, int32_t maxCount);
CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreateText(const char* value, CJBadgeStyle style, int32_t position);
CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreateTextV2(const char* value, CJBadgeStyleV2 style, int32_t position);
CJ_EXPORT void FfiOHOSAceFrameworkBadgeCreateTextV3(const char* value, CJBadgeStyleV3 style, int32_t position);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_BADGE_FFI_H
