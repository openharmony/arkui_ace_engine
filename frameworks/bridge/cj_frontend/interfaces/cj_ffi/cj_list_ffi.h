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

#ifndef OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct DividerParams {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

struct FfiOffsetRemain {
    double dxRemain;
    double dyRemain;
};

CJ_EXPORT void FfiOHOSAceFrameworkListCreate(double space, int32_t unit, int32_t initialIndex, int64_t scrollerID);
CJ_EXPORT void FfiOHOSAceFrameworkListSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetDirection(int32_t direction);
CJ_EXPORT void FfiOHOSAceFrameworkListSetDivider(DividerParams params);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEditMode(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetEdgeEffect(int32_t edgeEffect);
CJ_EXPORT void FfiOHOSAceFrameworkListSetCachedCount(int32_t cachedCount);
CJ_EXPORT void FfiOHOSAceFrameworkListSetScrollBar(int32_t barState);
CJ_EXPORT void FfiOHOSAceFrameworkListSetChainAnimation(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetMultiSelectable(bool flag);
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanes(int32_t lanes);
CJ_EXPORT void FfiOHOSAceFrameworkListSetLanesByLengthConstrain(
    double min, int32_t minUnit, double max, int32_t maxUnit);
CJ_EXPORT void FfiOHOSAceFrameworkListSetAlignListItem(int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkListSetSticky(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkListSetNestedScroll(int32_t scrollForward, int32_t scrollBackward);
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollFrameBegin(double (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkListSetItemDeleteCallback(bool (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkListSetScrollIndexCallback(void (*callback)(int32_t firstIndex, int32_t lastIndex));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollCallback(void (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnReachStartCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnReachEndCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollStartCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollStopCallback(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkListSetOnScrollBeginCallback(FfiOffsetRemain (*callback)(double dx, double dy));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_LIST_FFI_H
