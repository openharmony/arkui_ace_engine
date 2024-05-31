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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PANEL_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PANEL_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkPanelCreate(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkPanelType(int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkPanelMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkPanelDragBar(bool val);
CJ_EXPORT void FfiOHOSAceFrameworkPanelFullHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPanelHalfHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPanelMiniHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPanelShow(bool isShow);
CJ_EXPORT void FfiOHOSAceFrameworkPanelShowCloseIcon(bool showCloseIcon);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBackgroundMask(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPanelOnChange(void (*callback)(double width, double height, int32_t mode));
CJ_EXPORT void FfiOHOSAceFrameworkPanelOnHeightChange(void (*callback)(double height));
CJ_EXPORT void FfiOHOSAceFrameworkPanelBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBorder(CJBorder params);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBorderWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBorderRadius(double radius, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPanelBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkPanelPop();
};

#endif // OHOS_ACE_FRAMEWORK_CJ_PANEL_FFI_H
