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

#ifndef OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H
#define OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "frameworks/core/components/grid_layout/grid_layout_component.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkGridCreate();
CJ_EXPORT void FfiOHOSAceFrameworkGridCreateScroller(int64_t scrollerID);
CJ_EXPORT void FfiOHOSAceFrameworkGridSetCachedCount(int32_t cachedCount);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsTemplate(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsTemplate(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsGapWithString(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsGapWithNum(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsGapWithString(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsGapWithNum(int32_t value);

CJ_EXPORT void FfiOHOSAceFrameworkGridScrollBar(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridScrollBarColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkGridScrollBarWidth(double value, int32_t valueUnit);
CJ_EXPORT void FfiOHOSAceFrameworkGridCachedCount(int32_t cacheCount, bool show);
CJ_EXPORT void FfiOHOSAceFrameworkGridEditMode(bool isEditMode);
CJ_EXPORT void FfiOHOSAceFrameworkGridLayoutDirection(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridMaxCount(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridMinCount(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridCellLength(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridMultiSelectable(bool isSelectable);
CJ_EXPORT void FfiOHOSAceFrameworkGridSupportAnimation(bool isSupportAnimation);
CJ_EXPORT void FfiOHOSAceFrameworkGridEdgeEffect(int32_t value, bool isEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkGridEnableScrollInteraction(bool isEnable);
CJ_EXPORT void FfiOHOSAceFrameworkGridNestedScroll(int32_t forward, int32_t backward);
CJ_EXPORT void FfiOHOSAceFrameworkGridFriction(double value);
CJ_EXPORT void FfiOHOSAceFrameworkGridAlignItems(int32_t value);

CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollIndex(void (*callback)(uint32_t index));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollIndex2(void (*callback)(uint32_t first, uint32_t last));

struct CJItemDragInfo {
    double x;
    double y;
};
CJ_EXPORT void FfiOHOSAceFrameworkGridOnItemDragStart(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnItemDragEnter(void (*callback)(CJItemDragInfo dragInfo));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnItemDragMove(
    void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex, int32_t insertIndex));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnItemDragLeave(void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnItemDrop(
    void (*callback)(CJItemDragInfo dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess));

struct CJComputedBarAttribute {
    double totalOffset;
    double totalLength;
};
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollBarUpdate(
    CJComputedBarAttribute (*callback)(int32_t index, double offset));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnReachStart(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkGridOnReachEnd(void (*callback)());

struct CJOffsetRemain {
    double offsetRemain;
};
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollFrameBegin(CJOffsetRemain (*callback)(double offset, int32_t state));
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollStart(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollStop(void (*callback)());
}

#endif // OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H
