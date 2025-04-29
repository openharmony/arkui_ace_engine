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

#ifndef OHOS_ACE_FRAMEWORK_CJ_BUTTON_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_BUTTON_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
struct ButtonOptions {
    int32_t shape;
    bool stateEffect;
    int32_t buttonStyle;
    int32_t controlSize;
    int32_t role;
};

struct CJLabelStyle {
    int32_t overflow;
    uint32_t maxLines;
    bool minFontFlag;
    double minFontSize;
    int32_t minFontSize_unit;
    bool maxFontFlag;
    double maxFontSize;
    int32_t maxFontSize_unit;
    int32_t heightAdaptivePolicy;
    double fontSize;
    int32_t fontSize_unit;
    const char* fontWeight;
    const char* fontFamiliy;
    int32_t fontStyle;
};

CJ_EXPORT void FfiOHOSAceFrameworkButtonCreateWithChild();
CJ_EXPORT void FfiOHOSAceFrameworkButtonCreateWithChildAndOptions(ButtonOptions buttonOptions);
CJ_EXPORT void FfiOHOSAceFrameworkButtonCreateWithButtonOptions(ButtonOptions buttonOptions);
CJ_EXPORT void FfiOHOSAceFrameworkButtonCreateWithLabel(const char* label);
CJ_EXPORT void FfiOHOSAceFrameworkButtonCreateWithLabelAndOptions(const char* label, ButtonOptions buttonOptions);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetFontStyle(int32_t fontStyle);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetPadding(double top, int32_t topUnit, double right, int32_t rightUnit,
    double bottom, int32_t bottomUnit, double left, int32_t leftUnit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetRadius(double radius, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetAllBorderRadius(CJBorderRadius value);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetBorder(CJBorder params);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetType(int32_t shape);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetStateEffect(bool stateEffect);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetRole(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetControlSize(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetButtonStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkButtonSetLabelStyle(CJLabelStyle labelStyle);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_BUTTON_FFI_H
