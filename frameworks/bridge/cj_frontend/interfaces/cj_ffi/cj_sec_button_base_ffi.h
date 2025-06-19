/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SEC_BUTTON_BASE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SEC_BUTTON_BASE_FFI_H

#include <cstdint>
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
    struct  CJEdge {
        double top;
        int32_t topUnit;
        double right;
        int32_t rightUnit;
        double bottom;
        int32_t bottomUnit;
        double left;
        int32_t leftUnit;
    };

    struct CJConstraintSize {
        double minWidth;
        int32_t minWidthUnit;
        double maxWidth;
        int32_t maxWidthUnit;
        double minHeight;
        int32_t minHeightUnit;
        double maxHeight;
        int32_t maxHeightUnit;
    };

    CJ_EXPORT void FfiOHOSAceFrameworkSecButtonBasePop();
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetWidth(double width, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetHeight(double height, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetSize(double width, int32_t widthUnit,
        double height, int32_t heightUnit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundColor(uint32_t color);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderRadius(double radius, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetPosition(double x, int32_t xUnit, double y, int32_t yUnit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetConstraintSize(CJConstraintSize value);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderWidth(double width, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderColor(uint32_t color);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetOffset(double x, int32_t xUnit, double y, int32_t yUnit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetFontColor(uint32_t color);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetFontSize(double fontSize, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderStyle(int32_t style);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetIconSize(double width, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseMarkAnchor(double x, int32_t xUnit, double y, int32_t yUnit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetIconColor(uint32_t color);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundPadding(double padding, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundPaddings(CJEdge params);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetFontWeight(const char* value);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetTextIconSpace(double width, int32_t unit);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetFontFamily(const char* fontFamily);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetFontStyle(int32_t fontstyle);
    CJ_EXPORT void FfiOHOSAceFrameWorkSecButtonBaseSetLayoutDirection(int32_t value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SEC_BUTTON_BASE_FFI_H