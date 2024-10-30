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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkToggleCreate(int type, bool isOn);
CJ_EXPORT void FfiOHOSAceFrameworkToggleWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkToggleHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkToggleSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkTogglePadding(double left, int32_t leftUnit, double top, int32_t topUnit,
    double right, int32_t rightUnit, double bottom, int32_t bottomUnit);
CJ_EXPORT void FfiOHOSAceFrameworkToggleSelectedColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkToggleSwitchPointColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkToggleOnChange(void (*callback)(bool isOn));
CJ_EXPORT void FfiOHOSAceFrameworkTogglePop();
CJ_EXPORT void FfiToggleSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiToggleSetResponseRegionArray(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkToggleSwitchStyle(
    double pointRadius, uint32_t unselectedColor,
    uint32_t pointColor, double trackBorderRadius);
CJ_EXPORT void FfiOHOSAceFrameworkToggleBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkToggleHoverEffect(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkToggleRadius(double radius, int32_t unit);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H
