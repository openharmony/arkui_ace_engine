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

struct CJNavigationToolbarOptions {
    // backgroundColor
    bool isBackgroundColorValid;
    uint32_t backgroundColor;
    // backgroundBlurStyle
    bool isBackgroundBlurStyleValid;
    int32_t backgroundBlurStyle;
    // barStyle
    bool isBarStyleValid;
    int32_t barStyle;
};

CJ_EXPORT void FfiOHOSAceFrameworkNavigationCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavigationCreateWithPathInfos(int64_t pathInfos);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetNavDestination(void (*builder)(const char*));
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitle(const char* title);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetSubTitle(const char* subTitle);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithOptions(
    const char* title, bool withOptions, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithBuilderWithOptions(
    void (*builder)(), bool withOptions, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithCommon(
    const char* mainTitle, const char* subTitle, bool withOptions, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleWithCustom(
    void (*builder)(), double height, int32_t heightUnit, bool withOptions, CJNavigationTitleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMenus(VectorNavigationItemHandle menus);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMenusWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetTitleMode(int32_t titleMode);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBar(VectorNavigationItemHandle toolBars);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBarWithBuilder(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBarWithOptions(
    VectorNavigationItemHandle toolBars, bool withOptions, CJNavigationToolbarOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetToolBarWithBuilderWithOptions(
    void (*builder)(), bool withOptions, CJNavigationToolbarOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideToolBar(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideTitleBar(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideBackButton(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetNavBarWidth(double width, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetNavBarPosition(int32_t position);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetBackButtonIcon(const char* icon);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetBackButtonIconWithPixelMap(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetHideNavBar(bool isHide);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetNavBarWidthRange(
    double min, int32_t minUnit, double max, int32_t maxUnit);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetMinContentWidth(double min, int32_t minUnit);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetSystemBarStyle(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetOnTitleModeChanged(void (*callback)(int32_t));
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetOnNavBarStateChange(void (*callback)(bool));
CJ_EXPORT void FfiOHOSAceFrameworkNavigationSetOnNavigationModeChange(void (*callback)(int32_t));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAVIGATION_FFI_H
