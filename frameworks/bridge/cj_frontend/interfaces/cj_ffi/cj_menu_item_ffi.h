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

#ifndef OHOS_ACE_FRAMEWORK_CJ_MENU_ITEM_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_MENU_ITEM_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemCreateByBuilder(void(*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemCreateByOption(const char* startIcon,
    const char* content, const char* endIcon, const char* labelInfo, void(*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemIsSelected(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemSelectIconByBool(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemSelectIconByResource(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemContentFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemContentFontColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemLabelFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemLabelFontColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkMenuItemOnChange(void (*callback)(bool isChecked));
}
#endif // OHOS_ACE_FRAMEWORK_CJ_MENU_ITEM_FFI_H