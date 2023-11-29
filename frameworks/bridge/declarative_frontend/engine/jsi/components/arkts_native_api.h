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
#include "interfaces/inner_api/ace/macros.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"

typedef void *NodeHandle;
constexpr int32_t INVALID_FONT_STYLE = -1;
constexpr int32_t INVALID_COLOR_VALUE = -1;
struct StringAndDouble {
    double value;
    const char *valueStr;
};

struct ArkUIResourceColorType {
    uint32_t number;
    const char* string;
};

struct IconsStruct {
    const char* ShowIconInfo;
    const char* HiddenIconInfo;
    const char* SwitchingIconInfo;
};

struct FontStruct {
    const struct StringAndDouble* size;
    const struct StringAndInt32* weight;
    const char* family;
    int32_t style;
};

struct IconOptionsStruct {
    const struct StringAndDouble* size;
    int32_t color;
    const char* src;
};

struct SearchButtonOptionsStruct {
    const char* value;
    const struct StringAndDouble* fontSize;
    int32_t fontColor;
};

struct StringAndInt32 {
    int32_t value;
    const char* valueStr;
};

struct TextShadowStruct {
    double radius;
    uint32_t color;
    double offsetX;
    double offsetY;
    uint32_t fill;
};

struct ImagePropertiesStruct {
    const char* src;
    double number[4];
    int8_t unit[4];
    char* calc[4];
    int32_t duration;
};

struct ArkUIFontWeight {
    int32_t value;
    const char* valueStr;
};

typedef void* NodeHandle;
struct ArkUICommonModifierAPI {
    void (*SetBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetBackgroundColor)(NodeHandle node);
    void (*SetWidth)(NodeHandle node, double value, int unit, const char* calcVlaue);
    void (*ResetWidth)(NodeHandle node);
    void (*SetHeight)(NodeHandle node, double value, int unit, const char* calcVlaue);
    void (*ResetHeight)(NodeHandle node);
    void (*SetBorderRadius)(NodeHandle node, const double *values, const int *units, int32_t length);
    void (*ResetBorderRadius)(NodeHandle node);
    void (*SetBorderWidth)(NodeHandle node, const double *values, const int *units, int32_t length);
    void (*ResetBorderWidth)(NodeHandle node);
    void (*SetTransform)(NodeHandle node, const float *matrix, int32_t length);
    void (*ResetTransform)(NodeHandle node);
    void (*SetBorderColor)(NodeHandle node, const uint32_t &leftColorInt, const uint32_t &rightColorInt,
        const uint32_t &topColorInt, const uint32_t &bottomColorInt);
    void (*ResetBorderColor)(NodeHandle node);
    void (*SetPosition)(NodeHandle node, double xValue, int xUnit, double yValue, int yUnit);
    void (*ResetPosition)(NodeHandle node);
    void (*SetBorderStyle)(NodeHandle node, const int32_t *styles, int32_t length);
    void (*ResetBorderStyle)(NodeHandle node);
    void (*SetBackShadow)(NodeHandle node, const double *shadows, int32_t length);
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
    void (*SetLinearGradient)(NodeHandle node, const double *values, int32_t valuesLength, const double *colors,
        int32_t colorsLength);
    void (*ResetLinearGradient)(NodeHandle node);
    void (*SetSweepGradient)(
        NodeHandle node, const double* values, int32_t valuesLength, const double* colors, int32_t colorsLength);
    void (*ResetSweepGradient)(NodeHandle node);
    void (*SetRadialGradient)(
        NodeHandle node, const double* values, int32_t valuesLength, const double* colors, int32_t colorsLength);
    void (*ResetRadialGradient)(NodeHandle node);
    void (*SetForegroundBlurStyle)(
        NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor, double scale);
    void (*ResetForegroundBlurStyle)(NodeHandle node);
    void (*SetLinearGradientBlur)(NodeHandle node, double blurRadius, const double *stops, int32_t stopsLength,
        int32_t directionValue);
    void (*ResetLinearGradientBlur)(NodeHandle node);
    void (*SetBackgroundBlurStyle)(NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor,
        double scale);
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
    void (*SetPixelStretchEffect)(NodeHandle node, const double* values, const int* units, int32_t length);
    void (*ResetPixelStretchEffect)(NodeHandle node);
    void (*SetLightUpEffect)(NodeHandle node, double radio);
    void (*ResetLightUpEffect)(NodeHandle node);
    void (*SetSphericalEffect)(NodeHandle node, double radio);
    void (*ResetSphericalEffect)(NodeHandle node);
    void (*SetRenderGroup)(NodeHandle node, bool isRenderGroup);
    void (*ResetRenderGroup)(NodeHandle node);
    void (*SetRenderFit)(NodeHandle node, int32_t renderFit);
    void (*ResetRenderFit)(NodeHandle node);
    void (*SetUseEffect)(NodeHandle node, bool useEffect);
    void (*ResetUseEffect)(NodeHandle node);
    void (*SetForegroundColor)(NodeHandle node, bool isColor, uint32_t color);
    void (*ResetForegroundColor)(NodeHandle node);
    void (*SetMotionPath)(NodeHandle node, const char *path, float from, float to, bool rotatable);
    void (*ResetMotionPath)(NodeHandle node);
    void (*SetGroupDefaultFocus)(NodeHandle node, bool groupDefaultFocus);
    void (*ResetGroupDefaultFocus)(NodeHandle node);
    void (*SetFocusOnTouch)(NodeHandle node, bool focusOnTouch);
    void (*ResetFocusOnTouch)(NodeHandle node);
    void (*SetFocusable)(NodeHandle node, bool focusable);
    void (*ResetFocusable)(NodeHandle node);
    void (*SetTouchable)(NodeHandle node, bool touchable);
    void (*ResetTouchable)(NodeHandle node);
    void (*SetDefaultFocus)(NodeHandle node, bool defaultFocus);
    void (*ResetDefaultFocus)(NodeHandle node);
    void (*SetDisplayPriority)(NodeHandle node, double value);
    void (*ResetDisplayPriority)(NodeHandle node);
    void (*SetOffset)(NodeHandle node, const double *number, const int8_t *unit);
    void (*ResetOffset)(NodeHandle node);
    void (*SetPadding)(NodeHandle node, const struct StringAndDouble *top, const struct StringAndDouble *right,
        const struct StringAndDouble *bottom, const struct StringAndDouble *left);
    void (*ResetPadding)(NodeHandle node);
    void (*SetMargin)(NodeHandle node, const struct StringAndDouble *top, const struct StringAndDouble *right,
        const struct StringAndDouble *bottom, const struct StringAndDouble *left);
    void (*ResetMargin)(NodeHandle node);
    void (*SetMarkAnchor)(NodeHandle node, double xValue, int32_t xUnit, double yValue, int32_t yUnit);
    void (*ResetMarkAnchor)(NodeHandle node);
    void (*SetVisibility)(NodeHandle node, int32_t value);
    void (*ResetVisibility)(NodeHandle node);
    void (*SetAccessibilityText)(NodeHandle node, const char* value);
    void (*ResetAccessibilityText)(NodeHandle node);
    void (*SetAllowDrop)(NodeHandle node, const char** value, int32_t length);
    void (*ResetAllowDrop)(NodeHandle node);
    void (*SetAccessibilityLevel)(NodeHandle node, const char* value);
    void (*ResetAccessibilityLevel)(NodeHandle node);
    void (*SetAccessibilityDescription)(NodeHandle node, const char* value);
    void (*ResetAccessibilityDescription)(NodeHandle node);
    void (*SetId)(NodeHandle node, const char* id);
    void (*ResetId)(NodeHandle node);
    void (*SetKey)(NodeHandle node, const char* key);
    void (*ResetKey)(NodeHandle node);
    void (*SetRestoreId)(NodeHandle node, uint32_t id);
    void (*ResetRestoreId)(NodeHandle node);
    void (*SetTabIndex)(NodeHandle node, int32_t index);
    void (*ResetTabIndex)(NodeHandle node);
    void (*SetObscured)(NodeHandle node, const int32_t* reasons, int32_t length);
    void (*ResetObscured)(NodeHandle node);
    void (*SetResponseRegion)(NodeHandle node, const double* values, int32_t length);
    void (*ResetResponseRegion)(NodeHandle node);
    void (*SetMouseResponseRegion)(NodeHandle node, const double* values, int32_t length);
    void (*ResetMouseResponseRegion)(NodeHandle node);
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
    void (*SetTextLineHeight)(NodeHandle node, const double number, const int8_t unit);
    void (*ResetTextLineHeight)(NodeHandle node);
    void (*SetTextTextOverflow)(NodeHandle node, int32_t value);
    void (*ResetTextTextOverflow)(NodeHandle node);
    void (*SetTextDecoration)(NodeHandle node, const int32_t decoration, const uint32_t color, const int32_t style);
    void (*ResetTextDecoration)(NodeHandle node);
    void (*SetTextTextCase)(NodeHandle node, int32_t value);
    void (*ResetTextTextCase)(NodeHandle node);
    void (*SetTextMaxLines)(NodeHandle node, uint32_t maxLine);
    void (*ResetTextMaxLines)(NodeHandle node);
    void (*SetTextMinFontSize)(NodeHandle node, struct StringAndDouble* minFontSize);
    void (*ReSetTextMinFontSize)(NodeHandle node);
    void (*SetTextDraggable)(NodeHandle node, uint32_t draggable);
    void (*ResetTextDraggable)(NodeHandle node);
    void (*SetTextMaxFontSize)(NodeHandle node, struct StringAndDouble* maxFontSize);
    void (*ResetTextMaxFontSize)(NodeHandle node);
    void (*SetTextFontFamily)(NodeHandle node, const char** fontFamilies, uint32_t length);
    void (*ResetTextFontFamily)(NodeHandle node);
    void (*SetTextCopyOption)(NodeHandle node, const int32_t copyOption);
    void (*ResetTextCopyOption)(NodeHandle node);
    void (*SetTextTextShadow)(NodeHandle node, struct TextShadowStruct* shadows, uint32_t length);
    void (*ResetTextTextShadow)(NodeHandle node);
    void (*SetTextHeightAdaptivePolicy)(NodeHandle node, int32_t value);
    void (*ResetTextHeightAdaptivePolicy)(NodeHandle node);
    void (*SetTextTextIndent)(NodeHandle node, const struct StringAndDouble* value);
    void (*ResetTextTextIndent)(NodeHandle node);
    void (*SetTextBaselineOffset)(NodeHandle node, const struct StringAndDouble* offset);
    void (*ResetTextBaselineOffset)(NodeHandle node);
    void (*SetTextLetterSpacing)(NodeHandle node, const struct StringAndDouble* letterSpacingStruct);
    void (*ResetTextLetterSpacing)(NodeHandle node);
    void (*SetTextFont)(
        NodeHandle node, const struct StringAndDouble* size, const char* weight, const char* family, int32_t style);
    void (*ResetTextFont)(NodeHandle node);
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
    void (*SetButtonFontWeight)(NodeHandle node, const char *fontWeight);
    void (*ResetButtonFontWeight)(NodeHandle node);
    void (*SetButtonFontStyle)(NodeHandle node, int32_t fontStyle);
    void (*ResetButtonFontStyle)(NodeHandle node);
    void (*SetButtonFontFamily)(NodeHandle node, const char *fontFamily);
    void (*ResetButtonFontFamily)(NodeHandle node);
    void (*SetButtonLabelStyle)(NodeHandle node, const char *fontFamily, const double *valueArray,
        const double *dimensionValueArray, const int *dimensionUnitArray);
    void (*ResetButtonLabelStyle)(NodeHandle node);
};

struct ArkUIToggleModifierAPI {
    void (*SetToggleSelectedColor)(NodeHandle node, uint32_t selectedColor);
    void (*ResetToggleSelectedColor)(NodeHandle node);
    void (*SetToggleSwitchPointColor)(NodeHandle node, uint32_t switchPointColor);
    void (*ResetToggleSwitchPointColor)(NodeHandle node);
};

struct ArkUINavDestinationModifierAPI {
    void (*SetHideTitleBar)(NodeHandle node, bool hideTitle);
    void (*ResetHideTitleBar)(NodeHandle node);
};

struct ArkUICounterModifierAPI {
    void (*SetEnableInc)(NodeHandle node, bool value);
    void (*ReSetEnableInc)(NodeHandle node);
    void (*SetEnableDec)(NodeHandle node, bool value);
    void (*ReSetEnableDec)(NodeHandle node);
};

struct ArkUICheckboxGroupModifierAPI {
    void (*SetGroupSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetGroupSelectedColor)(NodeHandle node);
    void (*SetGroupUnSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetGroupUnSelectedColor)(NodeHandle node);
    void (*SetGroupSelectAll)(NodeHandle node, bool isSelected);
    void (*ResetGroupSelectAll)(NodeHandle node);
    void (*SetCheckboxGroupWidth)(NodeHandle node, double value, int unit);
    void (*ResetCheckboxGroupWidth)(NodeHandle node);
    void (*SetCheckboxGroupHeight)(NodeHandle node, double value, int unit);
    void (*ResetCheckboxGroupHeight)(NodeHandle node);
    void (*SetGroupMark)(NodeHandle node, uint32_t color, double sizeValue, double widthValue);
    void (*ResetGroupMark)(NodeHandle node);
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

struct ArkUISearchModifierAPI {
    void (*SetSearchPlaceholderColor)(NodeHandle node, uint32_t color);
    void (*ResetSearchPlaceholderColor)(NodeHandle node);
    void (*SetSearchTextFont)(NodeHandle node, const struct FontStruct* value);
    void (*ResetSearchTextFont)(NodeHandle node);
    void (*SetSearchSelectionMenuHidden)(NodeHandle node, uint32_t selectionMenuHidden);
    void (*ResetSearchSelectionMenuHidden)(NodeHandle node);
    void (*SetSearchCaretStyle)(NodeHandle node, const double number, const int8_t unit, uint32_t caretColor);
    void (*ResetSearchCaretStyle)(NodeHandle node);
    void (*SetSearchTextAlign)(NodeHandle node, int32_t value);
    void (*ResetSearchTextAlign)(NodeHandle node);
    void (*SetSearchCancelButton)(NodeHandle node,
        int32_t style, const struct StringAndDouble* size, uint32_t color, const char* src);
    void (*ResetSearchCancelButton)(NodeHandle node);
    void (*SetSearchEnableKeyboardOnFocus)(NodeHandle node, uint32_t value);
    void (*ResetSearchEnableKeyboardOnFocus)(NodeHandle node);
    void (*SetSearchPlaceholderFont)(NodeHandle node, const struct FontStruct* value);
    void (*ResetSearchPlaceholderFont)(NodeHandle node);
    void (*SetSearchSearchIcon)(NodeHandle node, const struct IconOptionsStruct* value);
    void (*ResetSearchSearchIcon)(NodeHandle node);
    void (*SetSearchSearchButton)(NodeHandle node, const struct SearchButtonOptionsStruct* value);
    void (*ResetSearchSearchButton)(NodeHandle node);
    void (*SetSearchFontColor)(NodeHandle node, uint32_t value);
    void (*ResetSearchFontColor)(NodeHandle node);
    void (*SetSearchCopyOption)(NodeHandle node, uint32_t value);
    void (*ResetSearchCopyOption)(NodeHandle node);
};

struct ArkUISelectModifierAPI {
    void (*SetSpace)(NodeHandle node, float value, int unit);
    void (*SetValue)(NodeHandle node, const char *value);
    void (*SetSelected)(NodeHandle node, int32_t idx);
    void (*SetSelectFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetArrowPosition)(NodeHandle node, const int32_t arrowPosition);
    void (*SetMenuAlign)(NodeHandle node, const int32_t alignType, const float *values, const int *units,
        const int32_t size);
    void (*SetFont)(NodeHandle node, const char *fontInfo, int32_t style);
    void (*SetOptionFont)(NodeHandle node, const char *fontInfo, int32_t style);
    void (*SetSelectedOptionFont)(NodeHandle node, const char *fontInfo, int32_t style);
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
    void (*SetTimepickerDisappearTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTimepickerTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTimepickerSelectedTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*ResetTimepickerDisappearTextStyle)(NodeHandle node);
    void (*ResetTimepickerTextStyle)(NodeHandle node);
    void (*ResetTimepickerSelectedTextStyle)(NodeHandle node);
    void (*ResetTimepickerBackgroundColor)(NodeHandle node);
};

struct ArkUIRowModifierAPI {
    void (*SetRowJustifyContent)(NodeHandle node, int32_t flexAlign);
    void (*ResetRowJustifyContent)(NodeHandle node);
    void (*SetRowAlignItems)(NodeHandle node, int32_t verticalAlign);
    void (*ResetRowAlignItems)(NodeHandle node);
};

struct ArkUIRowSplitModifierAPI {
    void (*SetRowSplitResizeable)(NodeHandle node, bool resizeable);
    void (*ResetRowSplitResizeable)(NodeHandle node);
};

struct ArkUITextpickerModifierAPI {
    void (*SetTextpickerBackgroundColor)(NodeHandle node, uint32_t color);
    void (*SetTextpickerCanLoop)(NodeHandle node, bool value);
    void (*SetTextpickerSelected)(NodeHandle node, uint32_t index);
    void (*SetTextpickerSelectedIndex)(NodeHandle node, uint32_t *values, int size);
    void (*SetTextpickerTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTextpickerSelectedTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTextpickerDisappearTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
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
    void (*SetStarStyle)(NodeHandle node, const char *backgroundUri, const char *foregroundUri,
        const char *secondaryUri);
    void (*ResetStars)(NodeHandle node);
    void (*ResetRatingStepSize)(NodeHandle node);
    void (*ResetStarStyle)(NodeHandle node);
};

struct ArkUISliderModifierAPI {
    void (*SetShowTips)(NodeHandle node, bool isShow, const char *value);
    void (*ResetShowTips)(NodeHandle node);
    void (*SetSliderStepSize)(NodeHandle node, float value, int unit);
    void (*ResetSliderStepSize)(NodeHandle node);
    void (*SetBlockSize)(NodeHandle node, float widthVal, int widthUnit, float heightVal, int heightUnit);
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
    void (*SetRadioStyle)(
        NodeHandle node, uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor);
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

struct ArkUIStackModifierAPI {
    void (*SetAlignContent)(NodeHandle node, int32_t alignment);
    void (*ResetAlignContent)(NodeHandle node);
};

struct ArkUIGridColModifierAPI {
    void (*SetSpan)(NodeHandle node, int32_t* containerSizeArray, int32_t size);
    void (*ResetSpan)(NodeHandle node);
    void (*SetGridColOffset)(NodeHandle node, int32_t* containerSizeArray, int32_t size);
    void (*ResetGridColOffset)(NodeHandle node);
    void (*SetOrder)(NodeHandle node, int32_t* containerSizeArray, int32_t size);
    void (*ResetOrder)(NodeHandle node);
};

struct ArkUIGridRowModifierAPI {
    void (*SetAlignItems)(NodeHandle node, int32_t alignItems);
    void (*ResetAlignItems)(NodeHandle node);
};

struct ArkUIPanelModifierAPI {
    void (*SetPanelMode)(NodeHandle node, int32_t mode);
    void (*ResetPanelMode)(NodeHandle node);
    void (*SetPanelFullHeight)(NodeHandle node, double value, int unit);
    void (*ResetPanelFullHeight)(NodeHandle node);
    void (*SetPanelHalfHeight)(NodeHandle node, double value, int unit);
    void (*ResetPanelHalfHeight)(NodeHandle node);
    void (*SetPanelMiniHeight)(NodeHandle node, double value, int unit);
    void (*ResetPanelMiniHeight)(NodeHandle node);
    void (*SetPanelBackgroundMask)(NodeHandle node, uint32_t color);
    void (*ResetPanelBackgroundMask)(NodeHandle node);
    void (*SetPanelType)(NodeHandle node, int32_t type);
    void (*ResetPanelType)(NodeHandle node);
    void (*SetPanelCustomHeight)(NodeHandle node, double value, int unit);
    void (*ResetPanelCustomHeight)(NodeHandle node);
    void (*SetShowCloseIcon)(NodeHandle node, bool value);
    void (*ResetShowCloseIcon)(NodeHandle node);
    void (*SetDragBar)(NodeHandle node, bool value);
    void (*ResetDragBar)(NodeHandle node);
    void (*SetShow)(NodeHandle node, bool value);
    void (*ResetShow)(NodeHandle node);
};

struct ArkUITextAreaModifierAPI {
    void (*SetTextAreaStyle)(NodeHandle node, int32_t style);
    void (*ResetTextAreaStyle)(NodeHandle node);
    void (*SetTextAreaSelectionMenuHidden)(NodeHandle node, uint32_t contextMenuHidden);
    void (*ResetTextAreaSelectionMenuHidden)(NodeHandle node);
    void (*SetTextAreaMaxLines)(NodeHandle node, uint32_t maxLine);
    void (*ResetTextAreaMaxLines)(NodeHandle node);
    void (*SetTextAreaCopyOption)(NodeHandle node, int32_t copyOptions);
    void (*ResetTextAreaCopyOption)(NodeHandle node);
    void (*SetTextAreaPlaceholderColor)(NodeHandle node, const struct ArkUIResourceColorType* colorType);
    void (*ResetTextAreaPlaceholderColor)(NodeHandle node);
    void (*SetTextAreaTextAlign)(NodeHandle node, int32_t value);
    void (*ResetTextAreaTextAlign)(NodeHandle node);
    void (*SetTextAreaPlaceholderFont)(NodeHandle node, const struct StringAndDouble* size,
        const struct ArkUIFontWeight* weight, const char* family, int32_t style);
    void (*ResetTextAreaPlaceholderFont)(NodeHandle node);
    void (*SetTextAreaBarState)(NodeHandle node, uint32_t barStateValue);
    void (*ResetTextAreaBarState)(NodeHandle node);
    void (*SetTextAreaEnableKeyboardOnFocus)(NodeHandle node, uint32_t keyboardOnFocusValue);
    void (*ResetTextAreaEnableKeyboardOnFocus)(NodeHandle node);
    void (*SetTextAreaFontFamily)(NodeHandle node, const char* fontFamily);
    void (*ResetTextAreaFontFamily)(NodeHandle node);
    void (*SetTextAreaShowCounter)(NodeHandle node, uint32_t value);
    void (*ResetTextAreaShowCounter)(NodeHandle node);
    void (*SetTextAreaCaretColor)(NodeHandle node, const struct ArkUIResourceColorType* colorType);
    void (*ResetTextAreaCaretColor)(NodeHandle node);
    void (*SetTextAreaMaxLength)(NodeHandle node, int32_t value);
    void (*ResetTextAreaMaxLength)(NodeHandle node);
    void (*SetTextAreaFontColor)(NodeHandle node, const struct ArkUIResourceColorType* colorType);
    void (*ResetTextAreaFontColor)(NodeHandle node);
    void (*SetTextAreaFontStyle)(NodeHandle node, uint32_t value);
    void (*ResetTextAreaFontStyle)(NodeHandle node);
    void (*SetTextAreaFontWeight)(NodeHandle node, uint32_t fontWeight);
    void (*ResetTextAreaFontWeight)(NodeHandle node);
    void (*SetTextAreaFontSize)(NodeHandle node, const struct StringAndDouble* size);
    void (*ResetTextAreaFontSize)(NodeHandle node);
};

struct ArkUINavigationModifierAPI {
    void (*SetHideToolBar)(NodeHandle node, bool hide);
    void (*ResetHideToolBar)(NodeHandle node);
    void (*SetHideNavBar)(NodeHandle node, bool hideNavBar);
    void (*ResetHideNavBar)(NodeHandle node);
    void (*SetTitleMode)(NodeHandle node, int32_t value);
    void (*ResetTitleMode)(NodeHandle node);
    void (*SetHideBackButton)(NodeHandle node, bool hideBackButton);
    void (*ResetHideBackButton)(NodeHandle node);
    void (*SetSubtitle)(NodeHandle node, const char* subtitle);
    void (*ResetSubtitle)(NodeHandle node);
    void (*ResetUsrNavigationMode)(NodeHandle node);
    void (*SetUsrNavigationMode)(NodeHandle node, int32_t value);
    void (*SetNavHideTitleBar)(NodeHandle node, bool hideTitle);
    void (*ResetNavHideTitleBar)(NodeHandle node);
    void (*SetNavBarPosition)(NodeHandle node, int32_t value);
    void (*ResetNavBarPosition)(NodeHandle node);
    void (*SetMinContentWidth)(NodeHandle node, double value, int unit);
    void (*ResetMinContentWidth)(NodeHandle node);
    void (*SetMaxNavBarWidth)(NodeHandle node, double maxValue, int maxUnit);
    void (*ResetMaxNavBarWidth)(NodeHandle node);
    void (*SetMinNavBarWidth)(NodeHandle node, double minValue, int minUnit);
    void (*ResetMinNavBarWidth)(NodeHandle node);
    void (*SetNavBarWidth)(NodeHandle node, double value, int unit);
    void (*ResetNavBarWidth)(NodeHandle node);
};

struct ArkUINavRouterModifierAPI {
    void (*SetNavRouteMode)(NodeHandle node, int32_t mode);
    void (*ResetNavRouteMode)(NodeHandle node);
};

struct ArkUINavigatorModifierAPI {
    void (*SetTarget)(NodeHandle node, const char* value);
    void (*ResetTarget)(NodeHandle node);
    void (*SetType)(NodeHandle node, int32_t value);
    void (*ResetType)(NodeHandle node);
    void (*SetActive)(NodeHandle node, bool active);
    void (*ResetActive)(NodeHandle node);
    void (*SetParams)(NodeHandle node, const char* args);
    void (*ResetParams)(NodeHandle node);
};

struct ArkUIColumnModifierAPI {
    void (*SetColumnJustifyContent)(NodeHandle node, int32_t flexAlign);
    void (*ResetColumnJustifyContent)(NodeHandle node);
    void (*SetColumnAlignItems)(NodeHandle node, int32_t value);
    void (*ResetColumnAlignItems)(NodeHandle node);
};

struct ArkUIRichEditorModifierAPI {
    void (*SetRichEditorCopyOptions)(NodeHandle node, int8_t copyOptionsValue);
    void (*ResetRichEditorCopyOptions)(NodeHandle node);
};

struct ArkUIImageModifierAPI {
    void (*SetCopyOption)(NodeHandle node, int32_t copyOption);
    void (*ResetCopyOption)(NodeHandle node);
    void (*SetAutoResize)(NodeHandle node, bool autoResize);
    void (*ResetAutoResize)(NodeHandle node);
    void (*SetObjectRepeat)(NodeHandle node, int32_t imageRepeat);
    void (*ResetObjectRepeat)(NodeHandle node);
    void (*SetRenderMode)(NodeHandle node, int32_t imageRenderMode);
    void (*ResetRenderMode)(NodeHandle node);
    void (*SetSyncLoad)(NodeHandle node, bool syncLoadValue);
    void (*ResetSyncLoad)(NodeHandle node);
    void (*SetObjectFit)(NodeHandle node, int32_t objectFitNumber);
    void (*ResetObjectFit)(NodeHandle node);
    void (*SetFitOriginalSize)(NodeHandle node, bool fitOriginalSizeValue);
    void (*ResetFitOriginalSize)(NodeHandle node);
    void (*SetSourceSize)(NodeHandle node, double width, double height);
    void (*ResetSourceSize)(NodeHandle node);
    void (*SetMatchTextDirection)(NodeHandle node, uint32_t value);
    void (*ResetMatchTextDirection)(NodeHandle node);
    void (*SetFillColor)(NodeHandle node, uint32_t value);
    void (*ResetFillColor)(NodeHandle node);
    void (*SetAlt)(NodeHandle node, const char *value);
    void (*ResetAlt)(NodeHandle node);
    void (*SetImageInterpolation)(NodeHandle node, int32_t value);
    void (*ResetImageInterpolation)(NodeHandle node);
    void (*SetColorFilter)(NodeHandle node, float *array, int length);
    void (*ResetColorFilter)(NodeHandle node);
    void (*SetImageSyncLoad)(NodeHandle node, bool syncLoadValue);
    void (*ResetImageSyncLoad)(NodeHandle node);
    void (*SetImageObjectFit)(NodeHandle node, int32_t objectFitNumber);
    void (*ResetImageObjectFit)(NodeHandle node);
    void (*SetImageFitOriginalSize)(NodeHandle node, bool fitOriginalSizeValue);
    void (*ResetImageFitOriginalSize)(NodeHandle node);
    void (*SetImageDraggable)(NodeHandle node, bool value);
    void (*ResetImageDraggable)(NodeHandle node);
};

struct ArkUIVideoModifierAPI {
    void (*SetAutoPlay)(NodeHandle node, uint32_t autoPlay);
    void (*ResetAutoPlay)(NodeHandle node);
    void (*SetVideoObjectFit)(NodeHandle node, int32_t objectFit);
    void (*ResetVideoObjectFit)(NodeHandle node);
    void (*SetVideoControls)(NodeHandle node, uint32_t controlsValue);
    void (*ResetVideoControls)(NodeHandle node);
    void (*SetVideoLoop)(NodeHandle node, uint32_t value);
    void (*ResetVideoLoop)(NodeHandle node);
    void (*SetVideoMuted)(NodeHandle node, uint32_t value);
    void (*ResetVideoMuted)(NodeHandle node);
};

struct ArkUIPatternLockModifierAPI {
    void (*SetPatternLockActiveColor)(NodeHandle node, uint32_t value);
    void (*ResetPatternLockActiveColor)(NodeHandle node);
    void (*SetPatternLockCircleRadius)(NodeHandle node, const struct StringAndDouble* value);
    void (*ResetPatternLockCircleRadius)(NodeHandle node);
    void (*SetPatternLockSelectedColor)(NodeHandle node, uint32_t value);
    void (*ResetPatternLockSelectedColor)(NodeHandle node);
    void (*SetPatternLockSideLength)(NodeHandle node, double number, int8_t unit);
    void (*ResetPatternLockSideLength)(NodeHandle node);
    void (*SetPatternLockAutoReset)(NodeHandle node, uint32_t value);
    void (*ResetPatternLockAutoReset)(NodeHandle node);
    void (*SetPatternLockPathStrokeWidth)(NodeHandle node, const struct StringAndDouble* pathStrokeWidthStruct);
    void (*ResetPatternLockPathStrokeWidth)(NodeHandle node);
    void (*SetPatternLockRegularColor)(NodeHandle node, uint32_t color);
    void (*ResetPatternLockRegularColor)(NodeHandle node);
    void (*SetPatternLockPathColor)(NodeHandle node, uint32_t color);
    void (*ResetPatternLockPathColor)(NodeHandle node);
};

struct ArkUIColumnSplitModifierAPI {
    void (*SetColumnSplitDivider)(NodeHandle node, double stVal, int32_t stUnit, double endVal, int32_t endUnit);
    void (*ResetColumnSplitDivider)(NodeHandle node);
    void (*SetColumnSplitResizeable)(NodeHandle node, bool resizeable);
    void (*ResetColumnSplitResizeable)(NodeHandle node);
};

struct ArkUISpanModifierAPI {
    void (*SetSpanTextCase)(NodeHandle node, int32_t value);
    void (*ResetSpanTextCase)(NodeHandle node);
    void (*SetSpanFontWeight)(NodeHandle node, const char* value);
    void (*ResetSpanFontWeight)(NodeHandle node);
    void (*SetSpanLineHeight)(NodeHandle node, struct StringAndDouble *lienHeight);
    void (*ReSetSpanLineHeight)(NodeHandle node);
    void (*SetSpanFontStyle)(NodeHandle node, int32_t fontStyle);
    void (*ReSetSpanFontStyle)(NodeHandle node);
    void (*SetSpanFontSize)(NodeHandle node, const double number, const int8_t unit);
    void (*ResetSpanFontSize)(NodeHandle node);
    void (*SetSpanFontFamily)(NodeHandle node, const char **fontFamilies, uint32_t length);
    void (*ResetSpanFontFamily)(NodeHandle node);
    void (*SetSpanDecoration)(NodeHandle node, const int32_t decoration, const uint32_t color, const uint32_t style);
    void (*ResetSpanDecoration)(NodeHandle node);
    void (*SetSpanFontColor)(NodeHandle node, uint32_t textColor);
    void (*ResetSpanFontColor)(NodeHandle node);
    void (*SetSpanLetterSpacing)(NodeHandle node, const struct StringAndDouble *letterSpacingValue);
    void (*ResetSpanLetterSpacing)(NodeHandle node);
    void (*SetSpanFont)(NodeHandle node, const struct StringAndDouble *size, const char* weight, const char *family,
        int32_t style);
    void (*ResetSpanFont)(NodeHandle node);
};

struct ArkUIImageAnimatorModifierAPI {
    void (*SetState)(NodeHandle node, int32_t state);
    void (*ResetState)(NodeHandle node);
    void (*SetDuration)(NodeHandle node, int32_t duration);
    void (*SetFixedSize)(NodeHandle node, uint32_t fixedSize);
    void (*ResetFixedSize)(NodeHandle node);
    void (*SetFillMode)(NodeHandle node, int32_t fillMode);
    void (*ResetFillMode)(NodeHandle node);
    void (*SetReverse)(NodeHandle node, uint32_t value);
    void (*ResetReverse)(NodeHandle node);
    void (*SetImages)(NodeHandle node, struct ImagePropertiesStruct* images, int32_t length);
    void (*ResetImages)(NodeHandle node);
    void (*SetImageAnimatorIteration)(NodeHandle node, int32_t value);
    void (*ResetImageAnimatorIteration)(NodeHandle node);
};

struct ArkUISideBarContainerModifierAPI {
    void (*SetSideBarWidth)(NodeHandle node, const struct StringAndDouble* sideBarWidth);
    void (*ResetSideBarWidth)(NodeHandle node);
    void (*SetMinSideBarWidth)(NodeHandle node, const struct StringAndDouble* minSideBarWidth);
    void (*ResetMinSideBarWidth)(NodeHandle node);
    void (*SetControlButton)(NodeHandle node, double* values, const struct IconsStruct* sideBarWidth);
    void (*ResetControlButton)(NodeHandle node);
    void (*SetShowControlButton)(NodeHandle node, bool isShow);
    void (*ResetShowControlButton)(NodeHandle node);
    void (*SetAutoHide)(NodeHandle node, uint32_t value);
    void (*ResetAutoHide)(NodeHandle node);
    void (*SetSideBarContainerMaxSideBarWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetSideBarContainerMaxSideBarWidth)(NodeHandle node);
    void (*SetSideBarContainerMinContentWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetSideBarContainerMinContentWidth)(NodeHandle node);
    void (*SetSideBarPosition)(NodeHandle node, int32_t sideBarPosition);
    void (*ResetSideBarPosition)(NodeHandle node);
    void (*SetShowSideBar)(NodeHandle node, bool isShow);
    void (*ResetShowSideBar)(NodeHandle node);
    void (*SetSideBarContainerDivider)(NodeHandle node, const struct StringAndDouble* strokeWidthStruct, uint32_t color,
        const struct StringAndDouble* startMarginStruct, const struct StringAndDouble* endMarginStruct);
    void (*ResetSideBarContainerDivider)(NodeHandle node);
};

struct ArkUINodeAPI {
    NodeHandle (*GetFrameNodeById)(int nodeId);
    ArkUICommonModifierAPI (*GetCommonModifier)();
    ArkUICheckboxGroupModifierAPI (*GetCheckboxGroupModifier)();
    ArkUICounterModifierAPI (*GetCounterModifier)();
    ArkUIRowModifierAPI (*GetRowModifier)();
    ArkUIRowSplitModifierAPI (*GetRowSplitModifier)();
    ArkUITextModifierAPI (*GetTextModifier)();
    ArkUIButtonModifierAPI (*GetButtonModifier)();
    ArkUIToggleModifierAPI (*GetToggleModifier)();
    ArkUIImageSpanModifierAPI (*GetImageSpanModifier)();
    ArkUIBlankModifierAPI (*GetBlankModifier)();
    ArkUISearchModifierAPI (*GetSearchModifier)();
    ArkUISelectModifierAPI (*GetSelectModifier)();
    ArkUIRadioModifierAPI (*GetRadioModifier)();
    ArkUICheckboxModifierAPI (*GetCheckboxModifier)();
    ArkUITimepickerModifierAPI (*GetTimepickerModifier)();
    ArkUITextpickerModifierAPI (*GetTextpickerModifier)();
    ArkUIRatingModifierAPI (*GetRatingModifier)();
    ArkUISliderModifierAPI (*GetSliderModifier)();
    ArkUIDividerModifierAPI (*GetDividerModifier)();
    ArkUIStackModifierAPI (*GetStackModifier)();
    ArkUINavDestinationModifierAPI (*GetNavDestinationModifier)();
    ArkUIGridColModifierAPI (*GetGridColModifier)();
    ArkUIGridRowModifierAPI (*GetGridRowModifier)();
    ArkUIPanelModifierAPI (*GetPanelModifier)();
    ArkUITextAreaModifierAPI (*GetTextAreaModifier)();
    ArkUINavigationModifierAPI (*GetNavigationModifier)();
    ArkUIColumnModifierAPI (*GetColumnModifier)();
    ArkUIRichEditorModifierAPI (*GetRichEditorModifier)();
    ArkUIImageModifierAPI (*GetImageModifier)();
    ArkUIVideoModifierAPI (*GetVideoModifier)();
    ArkUINavigatorModifierAPI (*GetNavigatorModifier)();
    ArkUINavRouterModifierAPI (*GetNavRouterModifier)();
    ArkUIPatternLockModifierAPI (*GetPatternLockModifier)();
    ArkUIColumnSplitModifierAPI (*GetColumnSplitModifier)();
    ArkUISpanModifierAPI (*GetSpanModifier)();
    ArkUIImageAnimatorModifierAPI (*GetImageAnimatorModifier)();
    ArkUISideBarContainerModifierAPI (*GetSideBarContainerModifier)();
};
ArkUINodeAPI* GetArkUIInternalNodeAPI(void);
#endif // FRAMEWORKS_INTERFACE_INNER_API_COMPONENTS_ARKTS_NATIVE_API_H