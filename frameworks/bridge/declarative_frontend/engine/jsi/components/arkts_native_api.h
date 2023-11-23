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
    void (*SetBorder)(NodeHandle node, double* values, int32_t* units, uint32_t* colorAndStyle, int32_t size);
    void (*ResetBorder)(NodeHandle node);
    void (*SetBackgroundImagePosition)(
        NodeHandle node, const double* values, const int32_t* types, bool isAlign, int size);
    void (*ResetBackgroundImagePosition)(NodeHandle node);
    void (*SetBackgroundImageSize)(
        NodeHandle node, double valueWidth, double valueHeight, int32_t typeWidth, int32_t typeHeight);
    void (*ResetBackgroundImageSize)(NodeHandle node);
    void (*SetBackgroundImage)(NodeHandle node, const char* src, int32_t repeatIndex);
    void (*ResetBackgroundImage)(NodeHandle node);
    void (*SetTranslate)(NodeHandle node, const double* values, const int* units, int32_t length);
    void (*ResetTranslate)(NodeHandle node);
    void (*SetScale)(NodeHandle node, const double* values, int valLength, const int* units, int unitLength);
    void (*ResetScale)(NodeHandle node);
    void (*SetRotate)(NodeHandle node, const double* values, int32_t valLength, const int* units, int32_t unitLength);
    void (*ResetRotate)(NodeHandle node);
    void (*SetGeometryTransition)(NodeHandle node, const char* id);
    void (*ResetGeometryTransition)(NodeHandle node);
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

struct ArkUISelectModifierAPI {
    void (*SetSpace)(NodeHandle node, float value, int unit);
    void (*SetValue)(NodeHandle node, const char* value);
    void (*SetSelected)(NodeHandle node, int32_t idx);
    void (*SetSelectFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetArrowPosition)(NodeHandle node, const int32_t arrowPosition);
    void (*SetMenuAlign)(
        NodeHandle node, const int32_t alignType, const float* values, const int* units, const int32_t size);
    void (*SetFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*SetOptionFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*SetSelectedOptionFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*ResetSpace)(NodeHandle node);
    void (*ResetValue)(NodeHandle node);
    void (*ResetSelected)(NodeHandle node);
    void (*ResetSelectFontColor)(NodeHandle node);
    void (*ResetSelectedOptionBgColor)(NodeHandle node);
    void (*ResetOptionBgColor)(NodeHandle node);
    void (*ResetOptionFontColor)(NodeHandle node);
    void (*ResetSelectedOptionFontColor)(NodeHandle node);
    void (*ResetArrowPosition)(NodeHandle node);
    void (*ResetMenuAlign)(NodeHandle node);
    void (*ResetFont)(NodeHandle node);
    void (*ResetOptionFont)(NodeHandle node);
    void (*ResetSelectedOptionFont)(NodeHandle node);
};

struct ArkUICheckboxModifierAPI {
    void (*SetSelect)(NodeHandle node, bool isSelected);
    void (*SetSelectedColor)(NodeHandle node, uint32_t color);
    void (*SetUnSelectedColor)(NodeHandle node, uint32_t color);
    void (*SetCheckboxWidth)(NodeHandle node, double widthVal, int widthUnit);
    void (*SetCheckboxHeight)(NodeHandle node, double heightVal, int heightUnit);
    void (*SetMark)(NodeHandle node, uint32_t color, double sizeValue, double widthValue);
    
    void (*ResetSelect)(NodeHandle node);
    void (*ResetSelectedColor)(NodeHandle node);
    void (*ResetUnSelectedColor)(NodeHandle node);
    void (*ResetCheckboxWidth)(NodeHandle node);
    void (*ResetCheckboxHeight)(NodeHandle node);
    void (*ResetMark)(NodeHandle node);
};

struct ArkUITimepickerModifierAPI {
    void (*SetTimepickerBackgroundColor)(NodeHandle node, uint32_t color);
    void (*SetTimepickerDisappearTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*SetTimepickerTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*SetTimepickerSelectedTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*ResetTimepickerDisappearTextStyle)(NodeHandle node);
    void (*ResetTimepickerTextStyle)(NodeHandle node);
    void (*ResetTimepickerSelectedTextStyle)(NodeHandle node);
    void (*ResetTimepickerBackgroundColor)(NodeHandle node);
};

struct ArkUITextpickerModifierAPI {
    void (*SetTextpickerBackgroundColor)(NodeHandle node, uint32_t color);
    void (*SetTextpickerCanLoop)(NodeHandle node, bool value);
    void (*SetTextpickerSelected)(NodeHandle node, uint32_t index);
    void (*SetTextpickerSelectedIndex)(NodeHandle node, uint32_t* values, int size);
    void (*SetTextpickerTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*SetTextpickerSelectedTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*SetTextpickerDisappearTextStyle)(NodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal);
    void (*SetTextpickerDefaultPickerItemHeight)(NodeHandle node, float dVal, int dUnit);

    void (*ResetTextpickerCanLoop)(NodeHandle node);
    void (*ResetTextpickerSelected)(NodeHandle node);
    void (*ResetTextpickerSelectedIndex)(NodeHandle node);
    void (*ResetTextpickerTextStyle)(NodeHandle node);
    void (*ResetTextpickerSelectedTextStyle)(NodeHandle node);
    void (*ResetTextpickerDisappearTextStyle)(NodeHandle node);
    void (*ResetTextpickerDefaultPickerItemHeight)(NodeHandle node);
    void (*ResetTextpickerBackgroundColor)(NodeHandle node);
};

struct ArkUIRatingModifierAPI {
    void (*SetStars)(NodeHandle node, int32_t value);
    void (*SetRatingStepSize)(NodeHandle node, double value);
    void (*SetStarStyle)(
        NodeHandle node, const char* backgroundUri, const char* foregroundUri, const char* secondaryUri);
    void (*ResetStars)(NodeHandle node);
    void (*ResetRatingStepSize)(NodeHandle node);
    void (*ResetStarStyle)(NodeHandle node);
};

struct ArkUISliderModifierAPI {
    void (*SetShowTips)(NodeHandle node, bool isShow, const char* value);
    void (*ResetShowTips)(NodeHandle node);
    void (*SetSliderStepSize)(NodeHandle node,  float value, int unit);
    void (*ResetSliderStepSize)(NodeHandle node);
    void (*SetBlockSize)(
        NodeHandle node, float widthVal, int widthUnit, float heightVal, int heightUnit);
    void (*ResetBlockSize)(NodeHandle node);
    void (*SetTrackBorderRadius)(NodeHandle node, float value, int unit);
    void (*ResetTrackBorderRadius)(NodeHandle node);
    void (*SetStepColor)(NodeHandle node, uint32_t color);
    void (*ResetStepColor)(NodeHandle node);
    void (*SetBlockBorderColor)(NodeHandle node, uint32_t color);
    void (*ResetBlockBorderColor)(NodeHandle node);
    void (*SetBlockBorderWidth)(NodeHandle node, float value, int unit);
    void (*ResetBlockBorderWidth)(NodeHandle node);
    void (*SetBlockColor)(NodeHandle node, uint32_t color);
    void (*ResetBlockColor)(NodeHandle node);
    void (*SetTrackBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetTrackBackgroundColor)(NodeHandle node);
    void (*SetSelectColor)(NodeHandle node, uint32_t color);
    void (*ResetSelectColor)(NodeHandle node);
    void (*SetShowSteps)(NodeHandle node, bool showSteps);
    void (*ResetShowSteps)(NodeHandle node);
    void (*SetThickness)(NodeHandle node, float value, int unit);
    void (*ResetThickness)(NodeHandle node);
};

struct ArkUIRadioModifierAPI {
    void (*SetRadioChecked)(NodeHandle node, bool isCheck);
    void (*ResetRadioChecked)(NodeHandle node);
    void (*SetRadioStyle)(NodeHandle node,
        uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor);
    void (*ResetRadioStyle)(NodeHandle node);
};

struct ArkUIDividerModifierAPI {
    void (*SetDividerStrokeWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetDividerStrokeWidth)(NodeHandle node);
    void (*SetDividerLineCap)(NodeHandle node, int32_t lineCap);
    void (*ResetDividerLineCap)(NodeHandle node);
    void (*SetDividerColor)(NodeHandle node, uint32_t color);
    void (*ResetDividerColor)(NodeHandle node);
    void (*SetDividerVertical)(NodeHandle node, bool value);
    void (*ResetDividerVertical)(NodeHandle node);
};

struct ArkUINodeAPI {
    NodeHandle (*GetFrameNodeById)(int nodeId);
    ArkUICommonModifierAPI (*GetCommonModifier)();
    ArkUITextModifierAPI (*GetTextModifier)();
    ArkUIButtonModifierAPI (*GetButtonModifier)();
    ArkUIToggleModifierAPI (*GetToggleModifier)();
    ArkUIImageSpanModifierAPI (*GetImageSpanModifier)();
    ArkUIBlankModifierAPI (*GetBlankModifier)();
    ArkUISelectModifierAPI (*GetSelectModifier)();
    ArkUIRadioModifierAPI (*GetRadioModifier)();
    ArkUICheckboxModifierAPI (*GetCheckboxModifier)();
    ArkUITimepickerModifierAPI (*GetTimepickerModifier)();
    ArkUITextpickerModifierAPI (*GetTextpickerModifier)();
    ArkUIRatingModifierAPI (*GetRatingModifier)();
    ArkUISliderModifierAPI (*GetSliderModifier)();
    ArkUIDividerModifierAPI (*GetDividerModifier)();
};

ArkUINodeAPI* GetArkUIInternalNodeAPI(void);

#endif // FRAMEWORKS_INTERFACE_INNER_API_COMPONENTS_ARKTS_NATIVE_API_H
