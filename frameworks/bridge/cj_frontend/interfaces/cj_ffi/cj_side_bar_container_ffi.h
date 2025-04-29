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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SIDE_BAR_CONTAINER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SIDE_BAR_CONTAINER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CJSideBarIconStyle {
    const char* shown;
    const char* hidden;
    const char* switching;
};

struct CJSideBarButtonStyle {
    double left;
    double top;
    double width;
    double height;
    CJSideBarIconStyle icons;
};

struct CJDividerStyle {
    double strokeWidth;
    int32_t strokeWidthUnit;
    bool hasColor;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

CJ_EXPORT void FfiOHOSAceFrameworkSideBarCreate(int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarShowSideBar(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarControlButton(CJSideBarButtonStyle style);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarShowControlButton(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarOnChange(void (*callback)(bool isShow));
CJ_EXPORT void FfiOHOSAceFrameworkSideBarSideBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarMinSideBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarMaxSideBarWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarAutoHide(bool autoHide);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarSideBarPosition(int32_t position);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarPop();
CJ_EXPORT void FfiOHOSAceFrameworkSideBarDividerNull();
CJ_EXPORT void FfiOHOSAceFrameworkSideBarDivider(CJDividerStyle info);
CJ_EXPORT void FfiOHOSAceFrameworkSideBarMinContentWidth(double width, int32_t unit);
};

#endif // OHOS_ACE_FRAMEWORK_CJ_SIDE_BAR_CONTAINER_FFI_H
