
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_nav_path_stack_ffi.h"

using VectorInt32Ptr = void*;
using VectorNavigationItemHandle = void*;

extern "C" {
struct CJNavDestinationContext {
    CJNavPathInfoFFi pathInfo;
    int64_t pathStack;
    uint64_t navDestinationId;
};

struct CJNavigationTitleOptions {
    // backgroundColor
    bool isBackgroundColorValid;
    uint32_t backgroundColor;
    // backgroundBlurStyle
    bool isBackgroundBlurStyleValid;
    int32_t backgroundBlurStyle;
    // barStyle
    bool isBarStyleValid;
    int32_t barStyle;
    // paddingStart
    bool isPaddingStartValid;
    double paddingStart;
    int32_t paddingStartUnit;
    // paddingEnd
    bool isPaddingEndValid;
    double paddingEnd;
    int32_t paddingEndUnit;
};

struct CJNavigationMenuItem {
    const char* value;
    const char* icon;
    bool isEnabled;
    void (*action)();
};

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnBackPressed(bool (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnReady(void (*callback)(CJNavDestinationContext context));

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithString(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithCommonTitle(const char* main, const char* sub);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithTitleHeight(void (*builder)(), int32_t titleHeightMode);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithHeight(void (*builder)(),
    double height, int32_t heightUnit);

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithStringOptions(const char* value,
    CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithBuilderOptions(void (*builder)(),
    CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithCommonTitleOptions(const char* main,
    const char* sub, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithTitleHeightOptions(void (*builder)(),
    int32_t titleHeightMode, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetTitleWithHeightOptions(void (*builder)(), double height,
    int32_t heightUnit, CJNavigationTitleOptions options);

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetHideTitleBar(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetBackButtonIconWithUrl(const char* url);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetBackButtonIconWithPixelMap(int64_t pixelMapId);

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetMenus(VectorNavigationItemHandle menuItemHandle);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetMenusWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationIgnoreLayoutSafeArea(VectorInt32Ptr types, VectorInt32Ptr edges);
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetSystemBarStyle(uint32_t styleColor);

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnShown(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnHidden(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnWillAppear(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnWillShow(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnWillHide(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnWillDisappear(void (*callback)());
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H
