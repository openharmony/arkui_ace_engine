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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GIRD_ROW_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_GIRD_ROW_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorFloat64Handle = void*;
using VectorInt32Handle = void*;

extern "C" {
struct GridRowCreateWithFloat64Int32 {
    double gutterValue;
    int32_t gutterUnit;
    int32_t columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

struct GridRowColumnOption {
    int32_t xs;
    int32_t sm;
    int32_t md;
    int32_t lg;
    int32_t xl;
    int32_t xxl;
};

struct AtCGridRowSizeOption {
    struct Unit {
        double value;
        int32_t unit;
    };
    Unit data[6];
};

struct GridRowCreateWithFloat64ColumnOption {
    double gutterValue;
    int32_t gutterUnit;
    GridRowColumnOption columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

struct GridRowCreateWithFloat64OptionColumnOption {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    GridRowColumnOption columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

struct GridRowCreateWithSizeOptionColumnOption {
    AtCGridRowSizeOption x;
    AtCGridRowSizeOption y;
    GridRowColumnOption columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

struct GridRowCreateWithFloat64OptionInt32 {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    int32_t columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

struct GridRowCreateWithSizeOptionInt32 {
    AtCGridRowSizeOption x;
    AtCGridRowSizeOption y;
    int32_t columns;
    VectorFloat64Handle breakpointVals;
    VectorInt32Handle breakpointUnits;
    int32_t breakpointReference;
    int32_t direction;
};

CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreate();
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithFloat64Int32(GridRowCreateWithFloat64Int32 createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithFloat64ColumnOption(
    GridRowCreateWithFloat64ColumnOption createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithFloat64OptionColumnOption(
    GridRowCreateWithFloat64OptionColumnOption createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithSizeOptionColumnOption(
    GridRowCreateWithSizeOptionColumnOption createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithFloat64OptionInt32(GridRowCreateWithFloat64OptionInt32 createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowCreateWithSizeOptionInt32(GridRowCreateWithSizeOptionInt32 createOption);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowSetHeight(double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowBreakpointEvent(void (*callback)(const char*));
CJ_EXPORT void FfiOHOSAceFrameworkGridRowAlignItem(int32_t alignItem);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_GIRD_ROW_FFI_H
