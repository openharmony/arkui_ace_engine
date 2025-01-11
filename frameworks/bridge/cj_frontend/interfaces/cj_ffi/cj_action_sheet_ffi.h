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

#ifndef OHOS_ACE_FRAMEWORK_CJ_ACTION_SHEET_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_ACTION_SHEET_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

using VectorSheetInfoHandle = void*;
extern "C" {
struct NativeConfirm {
    const char* value;
    void (*action)();
    bool enabled;
    bool defaultFocus;
    int32_t style;
};

struct NativeSheetInfo {
    const char* title;
    const char* icon;
    void (*action)();
};

struct NativeSheetInfoArray {
    int64_t size;
    NativeSheetInfo* sheetInfo;
};

struct NativeEdgeStyle {
    int32_t top;
    int32_t right;
    int32_t bottom;
    int32_t left;
};

struct NativeOptionConfirm {
    bool hasValue;
    NativeConfirm value;
};

struct NativeOptionOffset {
    bool hasValue;
    NativeOffset value;
};

struct NativeOptionRect {
    bool hasValue;
    NativeRectangle value;
};

struct NativeOptionCallback1Param {
    bool hasValue;
    void (*value)(int32_t reason);
};

struct NativeBorderRadiuses {
    double topLeftRadiuses;
    int32_t topLeftUnit;
    double topRightRadiuses;
    int32_t topRightUnit;
    double bottomLeftRadiuses;
    int32_t bottomLeftUnit;
    double bottomRightRadiuses;
    int32_t bottomRightUnit;
};

struct NativeOptionEdgeStyle {
    bool hasValue;
    NativeEdgeStyle value;
};

struct NativeOptionRadius {
    bool hasValue;
    NativeBorderRadiuses value;
};

struct NativeActionSheetOptions {
    const char* title;
    const char* message;
    NativeSheetInfoArray sheets;
    NativeOptionCString subtitle;
    NativeOptionConfirm confirm;
    NativeOptionBool autoCancel;
    NativeOptionCallBack cancel;
    NativeOptionInt32 alignment;
    NativeOptionOffset offset;
    NativeOptionRect maskRect;
    NativeOptionBool showInSubWindow;
    NativeOptionBool isModal;
    NativeOptionUInt32 backgroundColor;
    NativeOptionInt32 backgroundBlurStyle;
    NativeOptionCallback1Param onWillDismiss;
    NativeOptionRadius cornerRadius;
    NativeOptionLength borderWidth;
    NativeOptionUInt32 borderColor;
    NativeOptionEdgeStyle borderStyle;
    NativeOptionLength width;
    NativeOptionLength height;
    NativeOptionInt64 transition;
};

struct NativeShadowOptions {
    double radius;
    int32_t shadowType;
    uint32_t color;
    double offsetX;
    double offsetY;
    bool fill;
};

CJ_EXPORT void FfiOHOSAceFrameworkActionSheetShowWithShadowOptions(
    NativeActionSheetOptions options, NativeShadowOptions shadowOptions);
CJ_EXPORT void FfiOHOSAceFrameworkActionSheetShowWithShadowStyle(NativeActionSheetOptions options, int32_t shadowSytle);
CJ_EXPORT void FfiOHOSAceFrameworkActionSheetShow(NativeActionSheetOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkActionSheetDismiss();
}

#endif // OHOS_ACE_FRAMEWORK_CJ_ACTION_SHEET_FFI_H
