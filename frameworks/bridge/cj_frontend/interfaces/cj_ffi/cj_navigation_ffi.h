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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorNavigationItemHandle = void*;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkNavigationCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitle(const char* title);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetSubTitle(const char* subTitle);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMenus(VectorNavigationItemHandle menus);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMenusWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleMode(int32_t titleMode);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBar(VectorNavigationItemHandle toolBars);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBarWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideToolBar(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideTitleBar(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideBackButton(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetOnTitleModeChanged(void (*callback)(int32_t));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_FFI_H
