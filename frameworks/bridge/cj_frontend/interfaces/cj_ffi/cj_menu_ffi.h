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

#ifndef OHOS_ACE_FRAMEWORK_CJ_MENU_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_MENU_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

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
struct DividerParams {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

CJ_EXPORT void FfiOHOSAceFrameworkMenuCreate();
CJ_EXPORT void FfiOHOSAceFrameworkMenuFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetRadiusByLength(double size, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetRadiusByBorderRadiuses(CBorderRadiuses radius);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetItemDivider(DividerParams dividerParams, bool hasValue);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetItemGroupDivider(DividerParams dividerParams, bool hasValue);
CJ_EXPORT void FfiOHOSAceFrameworkMenuSetExpandingMode(int32_t mode);
}
#endif // OHOS_ACE_FRAMEWORK_CJ_MENU_FFI_H
