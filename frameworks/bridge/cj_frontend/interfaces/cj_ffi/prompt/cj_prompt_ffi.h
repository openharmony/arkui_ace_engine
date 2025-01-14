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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_alert_dialog_ffi.h"
#include "core/components_ng/property/transition_property.h"

extern "C" {
typedef struct CButtonInfo {
    const char* text;
    uint32_t textColor;
    bool primary;
} CButtonInfo;

struct NativeEdgeStyles {
    int32_t top;
    int32_t right;
    int32_t bottom;
    int32_t left;
};

struct NativeEdgeColor {
    uint32_t top;
    uint32_t right;
    uint32_t bottom;
    uint32_t left;
};

struct NativeShadowOptions {
    double radius;
    uint32_t shadowType;
    uint32_t color;
    double offsetX;
    double offsetY;
    bool fill;
};

struct CBorderRadiuses {
    double topLeftRadiuses;
    int32_t topLeftUnit;
    double topRightRadiuses;
    int32_t topRightUnit;
    double bottomLeftRadiuses;
    int32_t bottomLeftUnit;
    double bottomRightRadiuses;
    int32_t bottomRightUnit;
};

struct CJEdge {
    double top;
    int32_t topUnit;
    double right;
    int32_t rightUnit;
    double bottom;
    int32_t bottomUnit;
    double left;
    int32_t leftUnit;
};

struct NativeBaseOption {
    NativeRectangle maskRect;
    int32_t alignment;
    NativeOffset offset;
    bool isModal;
    bool showInSubWindow;
};

struct NativeCustomDialogOptions {
    NativeRectangle maskRect;
    int32_t alignment;
    NativeOffset offset;
    bool isModal;
    bool showInSubWindow;
    bool autoCancel;
    uint32_t maskColor;
    int64_t transition;
    void (*onDidAppear)();
    void (*onDidDisappear)();
    void (*onWillAppear)();
    void (*onWillDisappear)();
    int32_t keyboardAvoidMode;
    bool enableHoverMode;
    int32_t hoverModeArea;
    void (*builder)();
    uint32_t backgroundColor;
    CBorderRadiuses cornerRadius;
    CJEdge borderWidth;
    NativeEdgeColor borderColor;
    NativeEdgeStyles borderEdgeStyle;
    double widthValue;
    uint32_t widthUnit;
    double heightValue;
    uint32_t heightUnit;
    NativeShadowOptions shadowOption;
    int32_t shadowStyle;
    int32_t backgroundBlurStyle;
};

struct NativeShowToastOptions {
    const char* message;
    int32_t duration;
    const char* bottom;
    int32_t showMode;
    int32_t alignment;
    NativeOffset offset;
    uint32_t backgroundColor;
    uint32_t textColor;
    int32_t backgroundBlurStyle;
    int32_t shadowStyle;
    NativeShadowOptions shadowOption;
    bool enableHoverMode;
    int32_t hoverModeArea;
};

struct NativeShowDialogOptions {
    const char* title;
    const char* message;
    CButtonInfo* buttons;
    int32_t buttonsSize;
    int32_t alignment;
    NativeOffset offset;
    NativeRectangle maskRect;
    bool showInSubWindow;
    bool isModal;
    uint32_t backgroundColor;
    int32_t backgroundBlurStyle;
    NativeShadowOptions shadowOption;
    int32_t shadowStyle;
    bool enableHoverMode;
    int32_t hoverModeArea;
};

struct NativeActionMenuOptions {
    const char* title;
    CButtonInfo* buttons;
    int32_t buttonsSize;
    bool showInSubWindow;
    bool isModal;
};

using ShowDialogCallBack = void (*)(int32_t, int32_t);
using ShowActionMenuCallBack = void (*)(int32_t, int32_t);

CJ_EXPORT void* FfiPromptMallocButtons(int64_t size);
CJ_EXPORT void FfiPromptShowToast(const char* message, int32_t duration, const char* bottom, int32_t mode);
CJ_EXPORT void FfiPromptShowDialog(const char* title, const char* message, int32_t size,
    CButtonInfo* buttonsInfo, ShowDialogCallBack callback);
CJ_EXPORT void FfiPromptShowActionMenu(
    const char* title, int32_t buttonSize, CButtonInfo* buttonsInfo, ShowActionMenuCallBack callback);
CJ_EXPORT void FfiPromptOpenCustomDialog(void(*builder)(), NativeBaseOption options, void(*callback)(int32_t id));
CJ_EXPORT void FfiPromptCloseCustomDialog(int32_t id);

CJ_EXPORT void FfiPromptShowToastWithOption(NativeShowToastOptions options);
CJ_EXPORT void FfiPromptOpenCustomDialogWithOption(NativeCustomDialogOptions options, void(*callback)(int32_t));
CJ_EXPORT void FfiPromptShowActionMenuWithOption(NativeActionMenuOptions options, ShowActionMenuCallBack callbackRef);
CJ_EXPORT void FfiPromptShowDialogWithOption(NativeShowDialogOptions options, ShowDialogCallBack callbackRef);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H
