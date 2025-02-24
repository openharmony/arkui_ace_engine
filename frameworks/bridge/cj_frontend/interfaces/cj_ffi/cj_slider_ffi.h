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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SLIDER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SLIDER_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CJSliderCreate {
    double value;
    double min;
    double max;
    double step;
    int32_t style;
    int32_t direction;
    bool reverse;
};
CJ_EXPORT void FfiOHOSAceFrameworkSliderCreate(CJSliderCreate value);
CJ_EXPORT void FfiOHOSAceFrameworkSliderBlockColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSliderTrackColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSliderSelectedColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSliderShowSteps(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkSliderShowTips(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkSliderShowTipsNew(bool isShow, const char* content, bool contentExist);
CJ_EXPORT void FfiOHOSAceFrameworkSliderTrackThickness(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderMaxLabel(double value);
CJ_EXPORT void FfiOHOSAceFrameworkSliderMinLabel(double value);
CJ_EXPORT void FfiOHOSAceFrameworkSliderOnChange(void (*callback)(double value, int32_t mode));
CJ_EXPORT void FfiOHOSAceFrameworkSliderBlockBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSliderBlockBorderWidth(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderBlockSize(
    double widthVal, int32_t widthUnit, double heightVal, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderMinResponsiveDistance(float value);
CJ_EXPORT void FfiOHOSAceFrameworkSliderSelectedBorderRadius(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderInteractionMode(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSliderSlideRange(float from, float to, bool fromExist, bool toExist);
CJ_EXPORT void FfiOHOSAceFrameworkSliderStepColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSliderStepSize(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderTrackBorderRadius(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSliderContentModifier();
CJ_EXPORT void FfiOHOSAceFrameworkSliderBlockStyle(int32_t type, const char* image, int64_t shapeId);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SLIDER_FFI_H
