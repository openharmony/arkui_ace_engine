/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_COMPONENTS_ARKTS_NATIVE_API_H
#define FRAMEWORKS_INTERFACE_INNER_API_COMPONENTS_ARKTS_NATIVE_API_H

#include <cstdint>

typedef void* NodeHandle;

struct ArkUICommonModifierAPI {
    void (*SetBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetBackgroundColor)(NodeHandle node);
    void (*SetWidth)(NodeHandle node, double value, int unit);
    void (*ResetWidth)(NodeHandle node);
    void (*SetHeight)(NodeHandle node, double value, int unit);
    void (*ResetHeight)(NodeHandle node);
    void (*SetBorderRadius)(NodeHandle node, const double* values, const int* units, int32_t length);
    void (*ResetBorderRadius)(NodeHandle node);
    void (*SetBorderWidth)(NodeHandle node, const double* values, const int* units, int32_t length);
    void (*ResetBorderWidth)(NodeHandle node);
    void (*SetTransform)(NodeHandle node, const float* matrix, int32_t length);
    void (*ResetTransform)(NodeHandle node);
    void (*SetBorderColor)(NodeHandle node, const uint32_t& leftColorInt, const uint32_t& rightColorInt,
        const uint32_t& topColorInt, const uint32_t& bottomColorInt);
    void (*ResetBorderColor)(NodeHandle node);
    void (*SetPosition)(NodeHandle node, double xValue, int xUnit, double yValue, int yUnit);
    void (*ResetPosition)(NodeHandle node);
    void (*SetBorderStyle)(NodeHandle node, const int32_t* styles, int32_t length);
    void (*ResetBorderStyle)(NodeHandle node);
    void (*SetBackShadow)(NodeHandle node, const double* shadows, int32_t length);
    void (*ResetBackShadow)(NodeHandle node);
    void (*SetHitTestBehavior)(NodeHandle node, uint32_t value);
    void (*ResetHitTestBehavior)(NodeHandle node);
    void (*SetZIndex)(NodeHandle node, int32_t value);
    void (*ResetZIndex)(NodeHandle node);
    void (*SetOpacity)(NodeHandle node, double opacity);
    void (*ResetOpacity)(NodeHandle node);
    void (*SetAlign)(NodeHandle node, int32_t align);
    void (*ResetAlign)(NodeHandle node);
    void (*SetBackdropBlur)(NodeHandle node, double value);
    void (*ResetBackdropBlur)(NodeHandle node);
    void (*SetHueRotate)(NodeHandle node, float deg);
    void (*ResetHueRotate)(NodeHandle node);
    void (*SetInvert)(NodeHandle node, double invert);
    void (*ResetInvert)(NodeHandle node);
    void (*SetSepia)(NodeHandle node, double sepia);
    void (*ResetSepia)(NodeHandle node);
    void (*SetSaturate)(NodeHandle node, double saturate);
    void (*ResetSaturate)(NodeHandle node);
    void (*SetColorBlend)(NodeHandle node, uint32_t color);
    void (*ResetColorBlend)(NodeHandle node);
    void (*SetGrayscale)(NodeHandle node, double grayScale);
    void (*ResetGrayscale)(NodeHandle node);
    void (*SetContrast)(NodeHandle node, double contrast);
    void (*ResetContrast)(NodeHandle node);
    void (*SetBrightness)(NodeHandle node, double brightness);
    void (*ResetBrightness)(NodeHandle node);
    void (*SetBlur)(NodeHandle node, double value);
    void (*ResetBlur)(NodeHandle node);
    void (*SetLinearGradient)(
        NodeHandle node, const double* values, int32_t valuesLength, const double* colors, int32_t colorsLength);
    void (*ResetLinearGradient)(NodeHandle node);
    void (*SetForegroundBlurStyle)(
        NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor, double scale);
    void (*ResetForegroundBlurStyle)(NodeHandle node);
    void (*SetLinearGradientBlur)(
        NodeHandle node, double blurRadius, const double* stops, int32_t stopsLength, int32_t directionValue);
    void (*ResetLinearGradientBlur)(NodeHandle node);
    void (*SetBackgroundBlurStyle)(
        NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor, double scale);
    void (*ResetBackgroundBlurStyle)(NodeHandle node);
};

struct ArkUITextModifierAPI {
    void (*SetFontWeight)(NodeHandle node, const char* weight);
    void (*ResetFontWeight)(NodeHandle node);
    void (*SetFontStyle)(NodeHandle node, uint32_t fontStyle);
    void (*ResetFontStyle)(NodeHandle node);
    void (*SetTextAlign)(NodeHandle node, uint32_t testAlign);
    void (*ResetTextAlign)(NodeHandle node);
    void (*SetFontColor)(NodeHandle node, uint32_t color);
    void (*ResetFontColor)(NodeHandle node);
    void (*SetFontSize)(NodeHandle node, double value, int unit);
    void (*ResetFontSize)(NodeHandle node);
};

struct ArkUIButtonModifierAPI {
    void (*SetButtonType)(NodeHandle node, int type);
    void (*ResetButtonType)(NodeHandle node);
    void (*SetButtonStateEffect)(NodeHandle node, bool stateEffect);
    void (*ResetButtonStateEffect)(NodeHandle node);
    void (*SetButtonFontColor)(NodeHandle node, uint32_t fontColor);
    void (*ResetButtonFontColor)(NodeHandle node);
    void (*SetButtonFontSize)(NodeHandle node, double fontSizeValue, int fontSizeUnit);
    void (*ResetButtonFontSize)(NodeHandle node);
    void (*SetButtonFontWeight)(NodeHandle node, const char* fontWeight);
    void (*ResetButtonFontWeight)(NodeHandle node);
    void (*SetButtonFontStyle)(NodeHandle node, int32_t fontStyle);
    void (*ResetButtonFontStyle)(NodeHandle node);
    void (*SetButtonFontFamily)(NodeHandle node, const char* fontFamily);
    void (*ResetButtonFontFamily)(NodeHandle node);
    void (*SetButtonLabelStyle)(NodeHandle node, const char* fontFamily, const double* valueArray,
        const double* dimensionValueArray, const int* dimensionUnitArray);
    void (*ResetButtonLabelStyle)(NodeHandle node);
};

struct ArkUIToggleModifierAPI {
    void (*SetToggleSelectedColor)(NodeHandle node, uint32_t selectedColor);
    void (*ResetToggleSelectedColor)(NodeHandle node);
    void (*SetToggleSwitchPointColor)(NodeHandle node, uint32_t switchPointColor);
    void (*ResetToggleSwitchPointColor)(NodeHandle node);
};

struct ArkUIImageSpanModifierAPI {
    void (*SetImageSpanVerticalAlign)(NodeHandle node, int32_t value);
    void (*ResetImageSpanVerticalAlign)(NodeHandle node);
    void (*SetImageSpanObjectFit)(NodeHandle node, int32_t value);
    void (*ResetImageSpanObjectFit)(NodeHandle node);
};

struct ArkUIBlankModifierAPI {
    void (*SetColor)(NodeHandle node, uint32_t value);
    void (*ResetColor)(NodeHandle node);
};

struct ArkUINodeAPI {
    NodeHandle (*GetFrameNodeById)(int nodeId);
    ArkUICommonModifierAPI (*GetCommonModifier)();
    ArkUITextModifierAPI (*GetTextModifier)();
    ArkUIButtonModifierAPI (*GetButtonModifier)();
    ArkUIToggleModifierAPI (*GetToggleModifier)();
    ArkUIImageSpanModifierAPI (*GetImageSpanModifier)();
    ArkUIBlankModifierAPI (*GetBlankModifier)();
};

ArkUINodeAPI* GetArkUIInternalNodeAPI(void);

#endif // FRAMEWORKS_INTERFACE_INNER_API_COMPONENTS_ARKTS_NATIVE_API_H
