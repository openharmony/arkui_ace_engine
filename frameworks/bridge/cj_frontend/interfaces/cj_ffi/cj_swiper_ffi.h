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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_INTERFACES_CJ_FFI_CJ_SWIPER_FFI_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_INTERFACES_CJ_FFI_CJ_SWIPER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkSwiperCreate(int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetAutoplay(bool autoPlay);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetDigital(bool digitalIndicator);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetDuration(uint32_t duration);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetIndex(uint32_t index);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetInterval(uint32_t interval);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetLoop(bool loop);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetVertical(bool isVertical);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetIndicator(bool showIndicator);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetCancelSwipeOnOtherAxis(bool cancel);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit);

struct CJIndicatorStyle {
    double left;
    int32_t leftUnit;
    double top;
    int32_t topUnit;
    double right;
    int32_t rightUnit;
    double bottom;
    int32_t bottomUnit;
    double size;
    int32_t sizeUnit;
    uint32_t color;
    uint32_t selectedColor;
    bool mask;
};
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetIndicatorStyle(CJIndicatorStyle value);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetItemSpace(double itemSpace, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetDisplayMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetEffectMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetDisplayCount(int32_t count);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetCachedCount(int32_t cachedCount);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetEnabled(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetDisableSwipe(bool disable);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetCurve(const char* curveStr);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperSetOnChange(void (*callback)(int32_t index));
CJ_EXPORT int64_t FfiOHOSAceFrameworkSwiperControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkSwiperControllerShowNext(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperControllerShowPrevious(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperControllerFinishAnimation(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkSwiperControllerFinishAnimationWithCallback(int64_t selfId, void (*callback)());
}

#endif
