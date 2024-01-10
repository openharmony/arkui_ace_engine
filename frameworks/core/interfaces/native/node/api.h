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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H

#include <cstdint>
#include "interfaces/inner_api/ace/macros.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/event/mouse_event.h"
#include "core/components/common/properties/decoration.h"

typedef void *NodeHandle;
constexpr int32_t INVALID_FONT_STYLE = -1;
constexpr int32_t INVALID_COLOR_VALUE = -1;

template<typename T>
static OHOS::Ace::RefPtr<T> GetTheme()
{
    auto pipelineContext = OHOS::Ace::PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<T>();
}

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
    double value;
    int8_t unit;
    const struct StringAndInt32* weight;
    const char* family;
    int32_t style;
};

struct IconOptionsStruct {
    double value;
    int8_t unit;
    int32_t color;
    const char* src;
};

struct SearchButtonOptionsStruct {
    const char* value;
    double sizeValue;
    int8_t sizeUnit;
    int32_t fontColor;
};

struct Int32AndInt32 {
    int32_t number1;
    int32_t number2;
};

struct ListLanesStruct {
    int32_t number;
    int32_t minLength;
    int32_t maxlength;
};

struct ArkUISizeType {
    double value;
    int8_t unit;
    const char* string;
};

struct StringAndInt32 {
    int32_t value;
    const char* valueStr;
};

struct TextShadowStruct {
    double radius;
    uint32_t type;
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

struct ArkUILengthType {
    const char* string;
    double number;
    int8_t unit;
};

struct ArkUIFontStruct {
    double fontSizeNumber;
    int8_t fontSizeUnit;
    uint8_t fontWeight;
    uint8_t fontStyle;
    const char** fontFamilies;
    uint32_t familyLength;
};

struct ArkUIResourceLength {
    double value;
    int32_t Uint;
    const char* string;
};

struct ArkUIPasswordIconType {
    const char* showResult;
    const char* showBundleName;
    const char* showModuleName;
    const char* hideResult;
    const char* hideBundleName;
    const char* hideModuleName;
};

struct ArkUIPlaceholderFontType {
    const struct ArkUILengthType* size;
    const char* weight;
    const char** fontFamilies;
    uint32_t length;
    int32_t style;
};

struct ArkUIProgressStyle {
    double strokeWidthValue;
    int8_t strokeWidthUnit;
    double borderWidthValue;
    int8_t borderWidthUnit;
    int32_t scaleCount;
    int8_t status;
    double scaleWidthValue;
    int8_t scaleWidthUnit;
    double strokeRadiusValue;
    int8_t strokeRadiusUnit;
    bool enableSmoothEffect;
    double borderColor;
    const char* content;
    double fontColor;
    bool enableScanEffect;
    bool shadow;
    bool showDefaultPercentage;
    ArkUIFontStruct fontInfo;
};

struct ArkUIGradientType {
    const uint32_t* color;
    const ArkUILengthType* offset;
    const float* weight;
    const uint32_t* gradientLength;
    uint32_t length;
    uint32_t type;
};

struct ArkUIDimensionType {
    double value;
    int32_t units;
};

struct ArkUIChainAnimationOptionsType {
    double minSpace;
    double maxSpace;
    double conductivity;
    double intensity;
    double stiffness;
    double damping;
    int32_t edgeEffect;
    int32_t minSpaceUnits;
    int32_t maxSpaceUnits;
};

typedef void* NodeHandle;
struct ArkUICommonModifierAPI {
    void (*SetBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetBackgroundColor)(NodeHandle node);
    void (*SetWidth)(NodeHandle node, double value, int32_t unit, const char* calcVlaue);
    void (*ResetWidth)(NodeHandle node);
    void (*SetHeight)(NodeHandle node, double value, int32_t unit, const char* calcVlaue);
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
    void (*SetOverlay)(NodeHandle node, const char* text, const double* options, int32_t optionsLength);
    void (*ResetOverlay)(NodeHandle node);
    void (*SetBorderImage)(NodeHandle node, const char* src, const StringAndDouble* options, int32_t optionsLength);
    void (*ResetBorderImage)(NodeHandle node);
    void (*SetBorderImageGradient)(
        NodeHandle node, const double* values, int32_t valuesLength, const double* colors, int32_t colorsLength);
    void (*SetForegroundBlurStyle)(
        NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor, double scale);
    void (*ResetForegroundBlurStyle)(NodeHandle node);
    void (*SetLinearGradientBlur)(NodeHandle node, double blurRadius, const double *stops, size_t stopsLength,
        int32_t directionValue);
    void (*ResetLinearGradientBlur)(NodeHandle node);
    void (*SetBackgroundBlurStyle)(NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor,
        double scale);
    void (*ResetBackgroundBlurStyle)(NodeHandle node);
    void (*SetBorder)(NodeHandle node,
        const double* values, int32_t valuesSize, const uint32_t* colorAndStyle, int32_t colorAndStyleSize);
    void (*ResetBorder)(NodeHandle node);
    void (*SetBackgroundImagePosition)(
        NodeHandle node, const double* values, const int32_t* types, bool isAlign, int size);
    void (*ResetBackgroundImagePosition)(NodeHandle node);
    void (*SetBackgroundImageSize)(
        NodeHandle node, double valueWidth, double valueHeight, int32_t typeWidth, int32_t typeHeight);
    void (*ResetBackgroundImageSize)(NodeHandle node);
    void (*SetBackgroundImage)(
        NodeHandle node, const char* src, const char* bundle, const char* module, int32_t repeatIndex);
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
    void (*SetPadding)(NodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*ResetPadding)(NodeHandle node);
    void (*SetMargin)(NodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
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
    void (*SetDirection)(NodeHandle node, int32_t direction);
    void (*ResetDirection)(NodeHandle node);
    void (*SetLayoutWeight)(NodeHandle node, int32_t layoutWeight);
    void (*ResetLayoutWeight)(NodeHandle node);
    void (*SetMinWidth)(NodeHandle node, const struct ArkUISizeType* minWidth);
    void (*ResetMinWidth)(NodeHandle node);
    void (*SetMaxWidth)(NodeHandle node, const struct ArkUISizeType* maxWidth);
    void (*ResetMaxWidth)(NodeHandle node);
    void (*SetMinHeight)(NodeHandle node, const struct ArkUISizeType* minHeight);
    void (*ResetMinHeight)(NodeHandle node);
    void (*SetMaxHeight)(NodeHandle node, const struct ArkUISizeType* maxHeight);
    void (*ResetMaxHeight)(NodeHandle node);
    void (*SetSize)(NodeHandle node, const double* number, const int8_t* unit, const char** calc);
    void (*ResetSize)(NodeHandle node);
    void (*ClearWidthOrHeight)(NodeHandle node, bool isWidth);
    void (*SetAlignSelf)(NodeHandle node, int32_t value);
    void (*ResetAlignSelf)(NodeHandle node);
    void (*SetAspectRatio)(NodeHandle node, double value);
    void (*ResetAspectRatio)(NodeHandle node);
    void (*SetFlexGrow)(NodeHandle node, double value);
    void (*ResetFlexGrow)(NodeHandle node);
    void (*SetFlexShrink)(NodeHandle node, double value);
    void (*ResetFlexShrink)(NodeHandle node);
    void (*SetGridOffset)(NodeHandle node, int32_t offset);
    void (*ResetGridOffset)(NodeHandle node);
    void (*SetGridSpan)(NodeHandle node, int32_t value);
    void (*ResetGridSpan)(NodeHandle node);
    void (*SetExpandSafeArea)(NodeHandle node, const char* typeStr, const char* edgesStr);
    void (*ResetExpandSafeArea)(NodeHandle node);
    void (*SetFlexBasis)(NodeHandle node, const struct StringAndDouble* flexBasisValue);
    void (*ResetFlexBasis)(NodeHandle node);
    void (*SetAlignRules)(NodeHandle node, char** anchors, int8_t* direction, int32_t length);
    void (*ResetAlignRules)(NodeHandle node);
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
    void (*SetResponseRegion)(NodeHandle node, const double* values, const int32_t* units, int32_t length);
    void (*ResetResponseRegion)(NodeHandle node);
    void (*SetMouseResponseRegion)(NodeHandle node, const double* values, const int32_t* units, int32_t length);
    void (*ResetMouseResponseRegion)(NodeHandle node);
    void (*SetEnabled)(NodeHandle node, bool value);
    void (*ResetEnabled)(NodeHandle node);
    void (*SetDraggable)(NodeHandle node, bool value);
    void (*ResetDraggable)(NodeHandle node);
    void (*SetAccessibilityGroup)(NodeHandle node, bool value);
    void (*ResetAccessibilityGroup)(NodeHandle node);
    void (*SetHoverEffect)(NodeHandle node, int32_t hoverEffectValue);
    void (*ResetHoverEffect)(NodeHandle node);
    void (*SetOutlineColor)(NodeHandle node, const uint32_t* values, int32_t valuesSize);
    void (*ResetOutlineColor)(NodeHandle node);
    void (*SetOutlineRadius)(NodeHandle node, const double* values, int32_t valuesSize);
    void (*ResetOutlineRadius)(NodeHandle node);
    void (*SetOutlineWidth)(NodeHandle node, const double* values, int32_t valuesSize);
    void (*ResetOutlineWidth)(NodeHandle node);
    void (*SetOutlineStyle)(NodeHandle node, const uint32_t* values, int32_t valuesSize);
    void (*ResetOutlineStyle)(NodeHandle node);
    void (*SetOutline)(NodeHandle node, const double* values, int32_t valuesSize, const uint32_t* colorAndStyle,
        int32_t colorAndStyleSize);
    void (*ResetOutline)(NodeHandle node);
    void (*SetClickEffect)(NodeHandle node, const int32_t level, float scaleValue);
    void (*ResetClickEffect)(NodeHandle node);
    void (*SetKeyBoardShortCut)(NodeHandle node, const char* value, const int32_t* keysIntArray, int32_t length);
    void (*ResetKeyBoardShortCut)(NodeHandle node);
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
    void (*SetTextMinFontSize)(NodeHandle node, const double number, const int8_t unit);
    void (*ReSetTextMinFontSize)(NodeHandle node);
    void (*SetTextDraggable)(NodeHandle node, uint32_t draggable);
    void (*ResetTextDraggable)(NodeHandle node);
    void (*SetTextMaxFontSize)(NodeHandle node, const double number, const int8_t unit);
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
    void (*SetTextFont)(NodeHandle node, const struct ArkUIFontStruct *fontInfo);
    void (*ResetTextFont)(NodeHandle node);
    void (*SetWordBreak)(NodeHandle node, const uint32_t wordBreak);
    void (*ResetWordBreak)(NodeHandle node);
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
    void (*SetButtonLabelStyle)(NodeHandle node, const char** stringParameters, const int32_t* valueArray,
        const double* dimensionArray, const size_t* dataCountArray);
    void (*ResetButtonLabelStyle)(NodeHandle node);
    void (*SetButtonBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetButtonBackgroundColor)(NodeHandle node);
    void (*SetButtonBorderRadius)(NodeHandle node, const double* values, int32_t valuesSize);
    void (*ResetButtonBorderRadius)(NodeHandle node);
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
    void (*SetCounterHeight)(NodeHandle node, double value, int unit);
    void (*ResetCounterHeight)(NodeHandle node);
    void (*SetCounterWidth)(NodeHandle node, double value, int unit);
    void (*ResetCounterWidth)(NodeHandle node);
    void (*SetCounterBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetCounterBackgroundColor)(NodeHandle node);
};

struct ArkUICheckboxGroupModifierAPI {
    void (*SetCheckboxGroupSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetCheckboxGroupSelectedColor)(NodeHandle node);
    void (*SetCheckboxGroupUnSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetCheckboxGroupUnSelectedColor)(NodeHandle node);
    void (*SetCheckboxGroupSelectAll)(NodeHandle node, bool isSelected);
    void (*ResetCheckboxGroupSelectAll)(NodeHandle node);
    void (*SetCheckboxGroupWidth)(NodeHandle node, double value, int unit);
    void (*ResetCheckboxGroupWidth)(NodeHandle node);
    void (*SetCheckboxGroupHeight)(NodeHandle node, double value, int unit);
    void (*ResetCheckboxGroupHeight)(NodeHandle node);
    void (*SetCheckboxGroupMark)(NodeHandle node, uint32_t color, double sizeValue, double widthValue);
    void (*ResetCheckboxGroupMark)(NodeHandle node);
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
        int32_t style, const struct ArkUISizeType* size, uint32_t color, const char* src);
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
    void (*SetSpace)(NodeHandle node, float value, int32_t unit);
    void (*SetValue)(NodeHandle node, const char *value);
    void (*SetSelected)(NodeHandle node, int32_t idx);
    void (*SetSelectFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionBgColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetSelectedOptionFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*SetArrowPosition)(NodeHandle node, const int32_t arrowPosition);
    void (*SetMenuAlign)(
        NodeHandle node, const int32_t alignType, const float* values, const int32_t* units, const int32_t size);
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

    void (*SetSelectWidth)(NodeHandle node, double value, int32_t unit, const char* calcVlaue);
    void (*ResetSelectWidth)(NodeHandle node);
    void (*SetSelectHeight)(NodeHandle node, double value, int32_t unit, const char* calcVlaue);
    void (*ResetSelectHeight)(NodeHandle node);
    void (*SetSelectSize)(NodeHandle node, const double* number, const int8_t* unit, const char** calc);
    void (*ResetSelectSize)(NodeHandle node);
    void (*SetOptionWidthFitTrigger)(NodeHandle node, bool trigger);
    void (*SetOptionWidth)(NodeHandle node, const char* width);
    void (*ResetOptionWidth)(NodeHandle node);
    void (*SetOptionHeight)(NodeHandle node, const char* height);
    void (*ResetOptionHeight)(NodeHandle node);
};

struct ArkUICheckboxModifierAPI {
    void (*SetSelect)(NodeHandle node, bool isSelected);
    void (*SetSelectedColor)(NodeHandle node, uint32_t color);
    void (*SetUnSelectedColor)(NodeHandle node, uint32_t color);
    void (*SetCheckboxWidth)(NodeHandle node, double widthVal, int widthUnit);
    void (*SetCheckboxHeight)(NodeHandle node, double heightVal, int heightUnit);
    void (*SetMark)(NodeHandle node, uint32_t color, double sizeValue, double widthValue);
    void (*SetCheckboxPadding)(NodeHandle node, const double* values, const int* units);
    void (*SetCheckboxResponseRegion)(NodeHandle node, const double* values, const int32_t* units, uint32_t length);

    void (*ResetSelect)(NodeHandle node);
    void (*ResetSelectedColor)(NodeHandle node);
    void (*ResetUnSelectedColor)(NodeHandle node);
    void (*ResetCheckboxWidth)(NodeHandle node);
    void (*ResetCheckboxHeight)(NodeHandle node);
    void (*ResetMark)(NodeHandle node);
    void (*ResetCheckboxPadding)(NodeHandle node);
    void (*ResetCheckboxResponseRegion)(NodeHandle node);
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
    void (*SetTextpickerSelectedIndex)(NodeHandle node, uint32_t *values, int32_t size);
    void (*SetTextpickerTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTextpickerSelectedTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTextpickerDisappearTextStyle)(NodeHandle node, uint32_t color, const char *fontInfo, int32_t styleVal);
    void (*SetTextpickerDefaultPickerItemHeight)(NodeHandle node, double dVal, int32_t dUnit);
    void (*ResetTextpickerCanLoop)(NodeHandle node);
    void (*ResetTextpickerSelected)(NodeHandle node);
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
    void (*SetSliderStepSize)(NodeHandle node, double value, int unit);
    void (*ResetSliderStepSize)(NodeHandle node);
    void (*SetBlockSize)(NodeHandle node, double widthVal, int widthUnit, double heightVal, int heightUnit);
    void (*ResetBlockSize)(NodeHandle node);
    void (*SetTrackBorderRadius)(NodeHandle node, double value, int unit);
    void (*ResetTrackBorderRadius)(NodeHandle node);
    void (*SetStepColor)(NodeHandle node, uint32_t color);
    void (*ResetStepColor)(NodeHandle node);
    void (*SetBlockBorderColor)(NodeHandle node, uint32_t color);
    void (*ResetBlockBorderColor)(NodeHandle node);
    void (*SetBlockBorderWidth)(NodeHandle node, double value, int unit);
    void (*ResetBlockBorderWidth)(NodeHandle node);
    void (*SetBlockColor)(NodeHandle node, uint32_t color);
    void (*ResetBlockColor)(NodeHandle node);
    void (*SetTrackBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetTrackBackgroundColor)(NodeHandle node);
    void (*SetSelectColor)(NodeHandle node, uint32_t color);
    void (*ResetSelectColor)(NodeHandle node);
    void (*SetShowSteps)(NodeHandle node, bool showSteps);
    void (*ResetShowSteps)(NodeHandle node);
    void (*SetThickness)(NodeHandle node, double value, int unit);
    void (*ResetThickness)(NodeHandle node);
};

struct ArkUIRadioModifierAPI {
    void (*SetRadioChecked)(NodeHandle node, bool isCheck);
    void (*ResetRadioChecked)(NodeHandle node);
    void (*SetRadioStyle)(
        NodeHandle node, uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor);
    void (*ResetRadioStyle)(NodeHandle node);
    void (*SetRadioWidth)(NodeHandle node, double value, uint32_t unit);
    void (*ResetRadioWidth)(NodeHandle node);
    void (*SetRadioHeight)(NodeHandle node, double value, uint32_t unit);
    void (*ResetRadioHeight)(NodeHandle node);
    void (*SetRadioSize)(
        NodeHandle node, double widthValue, int32_t widthUnit, double heightValue, int32_t heightUnit);
    void (*ResetRadioSize)(NodeHandle node);
    void (*SetRadioHoverEffect)(NodeHandle node, int32_t hoverEffectValue);
    void (*ResetRadioHoverEffect)(NodeHandle node);
    void (*SetRadioPadding)(
        NodeHandle node, const struct ArkUISizeType *top, const struct ArkUISizeType *right,
            const struct ArkUISizeType *bottom, const struct ArkUISizeType *left);
    void (*ResetRadioPadding)(NodeHandle node);
    void (*SetRadioResponseRegion)(NodeHandle node, const double* values, const int32_t* units, uint32_t length);
    void (*ResetRadioResponseRegion)(NodeHandle node);
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

struct ArkUIGridModifierAPI {
    void (*SetGridColumnsTemplate)(NodeHandle node, const char* columnsTemplate);
    void (*ResetGridColumnsTemplate)(NodeHandle node);
    void (*SetGridRowsTemplate)(NodeHandle node, const char* rowsTemplate);
    void (*ResetGridRowsTemplate)(NodeHandle node);
    void (*SetGridColumnsGap)(NodeHandle node, const struct ArkUIResourceLength* columnsGap);
    void (*ResetGridColumnsGap)(NodeHandle node);
    void (*SetGridRowsGap)(NodeHandle node, const struct ArkUIResourceLength* rowsGap);
    void (*ResetGridRowsGap)(NodeHandle node);
    void (*SetGridScrollBar)(NodeHandle node, const int32_t scrollBar);
    void (*ResetGridScrollBar)(NodeHandle node);
    void (*SetGridScrollBarWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetGridScrollBarWidth)(NodeHandle node);
    void (*SetGridScrollBarColor)(NodeHandle node, uint32_t scrollBarColor);
    void (*ResetGridScrollBarColor)(NodeHandle node);
    void (*SetGridCachedCount)(NodeHandle node, const int32_t cachedCount);
    void (*ResetGridCachedCount)(NodeHandle node);
    void (*SetGridEditMode)(NodeHandle node, bool editMode);
    void (*ResetGridEditMode)(NodeHandle node);
    void (*SetGridMultiSelectable)(NodeHandle node, bool multiSelectable);
    void (*ResetGridMultiSelectable)(NodeHandle node);
    void (*SetGridMaxCount)(NodeHandle node, int32_t maxCount);
    void (*ResetGridMaxCount)(NodeHandle node);
    void (*SetGridMinCount)(NodeHandle node, int32_t minCount);
    void (*ResetGridMinCount)(NodeHandle node);
    void (*SetGridCellLength)(NodeHandle node, int32_t cellLength);
    void (*ResetGridCellLength)(NodeHandle node);
    void (*SetGridLayoutDirection)(NodeHandle node, int32_t layoutDirection);
    void (*ResetGridLayoutDirection)(NodeHandle node);
    void (*SetGridSupportAnimation)(NodeHandle node, bool supportAnimation);
    void (*ResetGridSupportAnimation)(NodeHandle node);

    void (*SetEdgeEffect)(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled);
    void (*ResetEdgeEffect)(NodeHandle node);
    void (*SetNestedScroll)(NodeHandle node, int32_t forward, int32_t backward);
    void (*ResetNestedScroll)(NodeHandle node);
    void (*SetEnableScroll)(NodeHandle node, bool ScrollEnabled);
    void (*ResetEnableScroll)(NodeHandle node);
    void (*SetFriction)(NodeHandle node, double friction);
    void (*ResetFriction)(NodeHandle node);
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
    void (*SetPanelCustomHeightByString)(NodeHandle node, const char* value);
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
    void (*SetTextAreaPlaceholderColor)(NodeHandle node, uint32_t color);
    void (*ResetTextAreaPlaceholderColor)(NodeHandle node);
    void (*SetTextAreaTextAlign)(NodeHandle node, int32_t value);
    void (*ResetTextAreaTextAlign)(NodeHandle node);
    void (*SetTextAreaPlaceholderFont)(NodeHandle node, const struct ArkUIResourceLength* size,
        const char* weight, const char* family, int32_t style);
    void (*ResetTextAreaPlaceholderFont)(NodeHandle node);
    void (*SetTextAreaBarState)(NodeHandle node, uint32_t barStateValue);
    void (*ResetTextAreaBarState)(NodeHandle node);
    void (*SetTextAreaEnableKeyboardOnFocus)(NodeHandle node, uint32_t keyboardOnFocusValue);
    void (*ResetTextAreaEnableKeyboardOnFocus)(NodeHandle node);
    void (*SetTextAreaFontFamily)(NodeHandle node, const char* fontFamily);
    void (*ResetTextAreaFontFamily)(NodeHandle node);
    void (*SetTextAreaShowCounter)(NodeHandle node, uint32_t value);
    void (*ResetTextAreaShowCounter)(NodeHandle node);
    void (*SetTextAreaCaretColor)(NodeHandle node, uint32_t color);
    void (*ResetTextAreaCaretColor)(NodeHandle node);
    void (*SetTextAreaMaxLength)(NodeHandle node, int32_t value);
    void (*ResetTextAreaMaxLength)(NodeHandle node);
    void (*SetTextAreaFontColor)(NodeHandle node, uint32_t color);
    void (*ResetTextAreaFontColor)(NodeHandle node);
    void (*SetTextAreaFontStyle)(NodeHandle node, uint32_t value);
    void (*ResetTextAreaFontStyle)(NodeHandle node);
    void (*SetTextAreaFontWeight)(NodeHandle node, const char* fontWeight);
    void (*ResetTextAreaFontWeight)(NodeHandle node);
    void (*SetTextAreaFontSize)(NodeHandle node, const struct ArkUIResourceLength* size);
    void (*ResetTextAreaFontSize)(NodeHandle node);
    void (*SetCounterType)(NodeHandle node, int32_t value);
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

struct ArkUINodeContainerModifierAPI {
    void (*Rebuild)(int32_t nodeId);
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
    void (*SetAlt)(NodeHandle node, const char *src, const char *bundleName, const char *moduleName);
    void (*ResetAlt)(NodeHandle node);
    void (*SetImageInterpolation)(NodeHandle node, int32_t value);
    void (*ResetImageInterpolation)(NodeHandle node);
    void (*SetColorFilter)(NodeHandle node, const float *array, int length);
    void (*ResetColorFilter)(NodeHandle node);
    void (*SetImageSyncLoad)(NodeHandle node, bool syncLoadValue);
    void (*ResetImageSyncLoad)(NodeHandle node);
    void (*SetImageObjectFit)(NodeHandle node, int32_t objectFitNumber);
    void (*ResetImageObjectFit)(NodeHandle node);
    void (*SetImageFitOriginalSize)(NodeHandle node, bool fitOriginalSizeValue);
    void (*ResetImageFitOriginalSize)(NodeHandle node);
    void (*SetImageDraggable)(NodeHandle node, bool value);
    void (*ResetImageDraggable)(NodeHandle node);
    void (*SetImageBorderRadius)(NodeHandle node, const double* values, const int* units, int32_t length);
    void (*ResetImageBorderRadius)(NodeHandle node);
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
    void (*SetPatternLockCircleRadius)(NodeHandle node, double number, int8_t unit);
    void (*ResetPatternLockCircleRadius)(NodeHandle node);
    void (*SetPatternLockSelectedColor)(NodeHandle node, uint32_t value);
    void (*ResetPatternLockSelectedColor)(NodeHandle node);
    void (*SetPatternLockSideLength)(NodeHandle node, double number, int8_t unit);
    void (*ResetPatternLockSideLength)(NodeHandle node);
    void (*SetPatternLockAutoReset)(NodeHandle node, uint32_t value);
    void (*ResetPatternLockAutoReset)(NodeHandle node);
    void (*SetPatternLockPathStrokeWidth)(NodeHandle node, double number, int8_t unit);
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

struct ArkUILineModifierAPI {
    void (*SetStartPoint)(NodeHandle node, double* pointValues, int32_t* pointUnits, const char* pointStr[]);
    void (*ResetStartPoint)(NodeHandle node);
    void (*SetEndPoint)(NodeHandle node, double* pointValues, int32_t* pointUnits, const char* pointStr[]);
    void (*ResetEndPoint)(NodeHandle node);
};

struct ArkUIPathModifierAPI {
    void (*SetPathCommands)(NodeHandle node, const char* commands);
    void (*ResetPathCommands)(NodeHandle node);
};

struct ArkUIPolygonModifierAPI {
    void (*SetPolygonPoints)(NodeHandle node, const double* pointX, const double* pointY, int32_t length);
    void (*ResetPolygonPoints)(NodeHandle node);
};

struct ArkUIPolylineModifierAPI {
    void (*SetPoints)(NodeHandle node, const double* pointX, const double* pointY, int32_t length);
    void (*ResetPoints)(NodeHandle node);
};

struct ArkUISpanModifierAPI {
    void (*SetSpanTextCase)(NodeHandle node, int32_t value);
    void (*ResetSpanTextCase)(NodeHandle node);
    void (*SetSpanFontWeight)(NodeHandle node, const char* value);
    void (*ResetSpanFontWeight)(NodeHandle node);
    void (*SetSpanLineHeight)(NodeHandle node, const double number, const int8_t unit);
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
    void (*SetSpanFont)(NodeHandle node, const struct ArkUIFontStruct *fontInfo);
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
    void (*SetSideBarWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetSideBarWidth)(NodeHandle node);
    void (*SetMinSideBarWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetMinSideBarWidth)(NodeHandle node);
    void (*SetControlButton)(
        NodeHandle node, double* values, int32_t valueLength, const struct IconsStruct* sideBarWidth);
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
    void (*SetSideBarContainerDivider)(NodeHandle node, double* values, int32_t* units, int32_t length, uint32_t color);
    void (*ResetSideBarContainerDivider)(NodeHandle node);
};

struct ArkUICalendarPickerModifierAPI {
    void (*SetTextStyle)(NodeHandle node, uint32_t color, const char* fontSize, const char* fontweight);
    void (*ResetTextStyle)(NodeHandle node);
    void (*SetEdgeAlign)(NodeHandle node, const double* values, const int* units, int32_t size, int32_t alignType);
    void (*ResetEdgeAlign)(NodeHandle node);
    void (*SetCalendarPickerPadding)(NodeHandle node, const struct ArkUISizeType* top,
        const struct ArkUISizeType* right, const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*ResetCalendarPickerPadding)(NodeHandle node);
    void (*SetCalendarPickerBorder)(NodeHandle node, const uint32_t color);
    void (*ResetCalendarPickerBorder)(NodeHandle node);
};

struct ArkUITextInputModifierAPI {
    void (*SetTextInputCaretColor)(NodeHandle node, uint32_t color);
    void (*ResetTextInputCaretColor)(NodeHandle node);
    void (*SetTextInputType)(NodeHandle node, int32_t value);
    void (*ResetTextInputType)(NodeHandle node);
    void (*SetTextInputMaxLines)(NodeHandle node, int32_t value);
    void (*ResetTextInputMaxLines)(NodeHandle node);
    void (*SetTextInputPlaceholderColor)(NodeHandle node, uint32_t color);
    void (*ResetTextInputPlaceholderColor)(NodeHandle node);
    void (*SetTextInputCaretPosition)(NodeHandle node, int32_t caretPosition);
    void (*ResetTextInputCaretPosition)(NodeHandle node);
    void (*SetTextInputCopyOption)(NodeHandle node, int32_t copyOption);
    void (*ResetTextInputCopyOption)(NodeHandle node);
    void (*SetTextInputShowPasswordIcon)(NodeHandle node, uint32_t showPasswordIcon);
    void (*ResetTextInputShowPasswordIcon)(NodeHandle node);
    void (*SetTextInputPasswordIcon)(NodeHandle node, const struct ArkUIPasswordIconType* passwordIcon);
    void (*ResetTextInputPasswordIcon)(NodeHandle node);
    void (*SetTextInputTextAlign)(NodeHandle node, int32_t textAlign);
    void (*ResetTextInputTextAlign)(NodeHandle node);
    void (*SetTextInputStyle)(NodeHandle node, int32_t style);
    void (*ResetTextInputStyle)(NodeHandle node);
    void (*SetTextInputSelectionMenuHidden)(NodeHandle node, uint32_t menuHiddenValue);
    void (*ResetTextInputSelectionMenuHidden)(NodeHandle node);
    void (*SetTextInputShowUnderline)(NodeHandle node, uint32_t showUnderLine);
    void (*ResetTextInputShowUnderline)(NodeHandle node);
    void (*SetTextInputCaretStyle)(NodeHandle node, const ArkUILengthType* value);
    void (*ResetTextInputCaretStyle)(NodeHandle node);
    void (*SetTextInputEnableKeyboardOnFocus)(NodeHandle node, uint32_t value);
    void (*ResetTextInputEnableKeyboardOnFocus)(NodeHandle node);
    void (*SetTextInputBarState)(NodeHandle node, int32_t value);
    void (*ResetTextInputBarState)(NodeHandle node);
    void (*SetTextInputEnterKeyType)(NodeHandle node, int32_t value);
    void (*ResetTextInputEnterKeyType)(NodeHandle node);
    void (*SetTextInputFontWeight)(NodeHandle node, const char* fontWeight);
    void (*ResetTextInputFontWeight)(NodeHandle node);
    void (*SetTextInputFontSize)(NodeHandle node, const struct ArkUILengthType* value);
    void (*ResetTextInputFontSize)(NodeHandle node);
    void (*SetTextInputMaxLength)(NodeHandle node, uint32_t value);
    void (*ResetTextInputMaxLength)(NodeHandle node);
    void (*SetTextInputSelectedBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetTextInputSelectedBackgroundColor)(NodeHandle node);
    void (*SetTextInputShowError)(NodeHandle node, const char* error, uint32_t visible);
    void (*ResetTextInputShowError)(NodeHandle node);
    void (*SetTextInputPlaceholderFont)(NodeHandle node, const struct ArkUIPlaceholderFontType* placeholderFont);
    void (*ResetTextInputPlaceholderFont)(NodeHandle node);
    void (*SetTextInputFontColor)(NodeHandle node, uint32_t color);
    void (*ResetTextInputFontColor)(NodeHandle node);
    void (*SetTextInputFontStyle)(NodeHandle node, uint32_t value);
    void (*ResetTextInputFontStyle)(NodeHandle node);
    void (*SetTextInputFontFamily)(NodeHandle node, const char** fontFamilies, uint32_t length);
    void (*ResetTextInputFontFamily)(NodeHandle node);
};

struct ArkUITabsModifierAPI {
    void (*SetTabBarMode)(NodeHandle node, int32_t tabsBarMode);
    void (*SetScrollableBarModeOptions)(NodeHandle node, const double value, const int unit, const int layoutStyle);
    void (*SetBarGridAlign)(
        NodeHandle node, const double* values, int32_t valuesLength, const int* units, int32_t unitsLength);
    void (*SetDivider)(NodeHandle node, uint32_t color, const double* values, const int32_t* units, int32_t length);
    void (*SetFadingEdge)(NodeHandle node, bool fadingEdge);
    void (*SetBarBackgroundColor)(NodeHandle node, uint32_t color);
    void (*SetBarOverlap)(NodeHandle node, bool overlap);
    void (*SetIsVertical)(NodeHandle node, bool isVertical);
    void (*SetTabBarPosition)(NodeHandle node, int32_t barVal);
    void (*SetScrollable)(NodeHandle node, bool scrollable);
    void (*SetTabBarWidth)(NodeHandle node, double value, int unit);
    void (*SetTabBarHeight)(NodeHandle node, double value, int unit);
    void (*SetBarAdaptiveHeight)(NodeHandle node, bool value);
    void (*SetAnimationDuration)(NodeHandle node, float duration);
    void (*ResetTabBarMode)(NodeHandle node);
    void (*ResetScrollableBarModeOptions)(NodeHandle node);
    void (*ResetBarGridAlign)(NodeHandle node);
    void (*ResetDivider)(NodeHandle node);
    void (*ResetFadingEdge)(NodeHandle node);
    void (*ResetBarBackgroundColor)(NodeHandle node);
    void (*ResetBarOverlap)(NodeHandle node);
    void (*ResetIsVertical)(NodeHandle node);
    void (*ResetTabBarPosition)(NodeHandle node);
    void (*ResetScrollable)(NodeHandle node);
    void (*ResetTabBarWidth)(NodeHandle node);
    void (*ResetTabBarHeight)(NodeHandle node);
    void (*ResetBarAdaptiveHeight)(NodeHandle node);
    void (*ResetAnimationDuration)(NodeHandle node);
    void (*SetTabClip)(NodeHandle node, bool clipEdge);
    void (*ResetTabClip)(NodeHandle node);
};

struct ArkUIStepperItemModifierAPI {
    void (*SetNextLabel)(NodeHandle node, const char* rightLabel);
    void (*ResetNextLabel)(NodeHandle node);
};

struct ArkUIHyperlinkModifierAPI {
    void (*SetHyperlinkColor)(NodeHandle node, uint32_t color);
    void (*ResetHyperlinkColor)(NodeHandle node);
};

struct ArkUIMenuItemModifierAPI {
    void (*SetMenuItemSelected)(NodeHandle node, bool value);
    void (*ResetMenuItemSelected)(NodeHandle node);
    void (*SetLabelFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*ResetLabelFontColor)(NodeHandle node);
    void (*SetContentFontColor)(NodeHandle node, const uint32_t colorVal);
    void (*ResetContentFontColor)(NodeHandle node);
    void (*SetLabelFont)(NodeHandle node, const char* fontInfo, int32_t styleVal);
    void (*ResetLabelFont)(NodeHandle node);
    void (*SetContentFont)(NodeHandle node, const char* fontInfo, int32_t styleVal);
    void (*ResetContentFont)(NodeHandle node);
};

struct ArkUIMenuModifierAPI {
    void (*SetMenuFontColor)(NodeHandle node, uint32_t colorVal);
    void (*ResetMenuFontColor)(NodeHandle node);
    void (*SetFont)(NodeHandle node, const char* fontInfo, int32_t styleVal);
    void (*ResetFont)(NodeHandle node);
    void (*SetRadius)(NodeHandle node, const double* values, const int* units);
    void (*ResetRadius)(NodeHandle node);
};

struct ArkUIWaterFlowModifierAPI {
    void (*ResetColumnsTemplate)(NodeHandle node);
    void (*SetColumnsTemplate)(NodeHandle node, const char* value);
    void (*ResetRowsTemplate)(NodeHandle node);
    void (*SetRowsTemplate)(NodeHandle node, const char* value);
    void (*ResetWaterFlowEnableScrollInteraction)(NodeHandle node);
    void (*SetWaterFlowEnableScrollInteraction)(NodeHandle node, bool value);
    void (*SetColumnsGap)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetColumnsGap)(NodeHandle node);
    void (*SetRowsGap)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetRowsGap)(NodeHandle node);
    void (*SetItemMinWidth)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetItemMinWidth)(NodeHandle node);
    void (*SetItemMaxWidth)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetItemMaxWidth)(NodeHandle node);
    void (*SetItemMinHeight)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetItemMinHeight)(NodeHandle node);
    void (*SetItemMaxHeight)(NodeHandle node, double value, int32_t unit, const char* calcValue);
    void (*ResetItemMaxHeight)(NodeHandle node);
    void (*SetLayoutDirection)(NodeHandle node, int32_t value);
    void (*ResetLayoutDirection)(NodeHandle node);
    void (*SetWaterFlowNestedScroll)(NodeHandle node, int32_t scrollForward, int32_t scrollBackward);
    void (*ResetWaterFlowNestedScroll)(NodeHandle node);
    void (*SetWaterFlowFriction)(NodeHandle node, double friction);
    void (*ResetWaterFlowFriction)(NodeHandle node);
};

struct ArkUIMarqueeModifierAPI {
    void (*SetMarqueeFontSize)(NodeHandle node, double value, int unit);
    void (*ResetMarqueeFontSize)(NodeHandle node);
    void (*SetMarqueeFontColor)(NodeHandle node, uint32_t color);
    void (*ResetMarqueeFontColor)(NodeHandle node);
    void (*SetMarqueeAllowScale)(NodeHandle node, bool allowScale);
    void (*ResetMarqueeAllowScale)(NodeHandle node);
    void (*SetMarqueeFontWeight)(NodeHandle node, const char *fontWeight);
    void (*ResetMarqueeFontWeight)(NodeHandle node);
    void (*SetMarqueeFontFamily)(NodeHandle node, const char *fontFamily);
    void (*ResetMarqueeFontFamily)(NodeHandle node);
};

struct ArkUIDatePickerModifierAPI {
    void (*SetSelectedTextStyle)(
        NodeHandle node, const char* fontInfo, uint32_t color, int32_t style);
    void (*ResetSelectedTextStyle)(NodeHandle node);
    void (*SetDatePickerTextStyle)(
        NodeHandle node, const char* fontInfo, uint32_t color, int32_t style);
    void (*ResetDatePickerTextStyle)(NodeHandle node);
    void (*SetDisappearTextStyle)(
        NodeHandle node, const char* fontInfo, uint32_t color, int32_t style);
    void (*ResetDisappearTextStyle)(NodeHandle node);
    void (*SetLunar)(NodeHandle node, bool isLunar);
    void (*ResetLunar)(NodeHandle node);
    void (*SetDatePickerBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetDatePickerBackgroundColor)(NodeHandle node);
};

struct ArkUIAlphabetIndexerModifierAPI {
    void (*SetPopupItemFont)(NodeHandle node, double size, int unit, const char* weight);
    void (*ResetPopupItemFont)(NodeHandle node);
    void (*SetSelectedFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*ResetSelectedFont)(NodeHandle node);
    void (*SetPopupFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*ResetPopupFont)(NodeHandle node);
    void (*SetAlphabetIndexerFont)(NodeHandle node, const char* fontInfo, int32_t style);
    void (*ResetAlphabetIndexerFont)(NodeHandle node);
    void (*SetPopupItemBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetPopupItemBackgroundColor)(NodeHandle node);
    void (*SetAlphabetIndexerColor)(NodeHandle node, uint32_t color);
    void (*ResetAlphabetIndexerColor)(NodeHandle node);
    void (*SetPopupColor)(NodeHandle node, uint32_t color);
    void (*ResetPopupColor)(NodeHandle node);
    void (*SetAlphabetIndexerSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetAlphabetIndexerSelectedColor)(NodeHandle node);
    void (*SetPopupBackground)(NodeHandle node, uint32_t color);
    void (*ResetPopupBackground)(NodeHandle node);
    void (*SetSelectedBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetSelectedBackgroundColor)(NodeHandle node);
    void (*SetPopupUnselectedColor)(NodeHandle node, uint32_t color);
    void (*ResetPopupUnselectedColor)(NodeHandle node);
    void (*SetAlignStyle)(NodeHandle node, int32_t value);
    void (*ResetAlignStyle)(NodeHandle node);
    void (*SetUsingPopup)(NodeHandle node, bool value);
    void (*ResetUsingPopup)(NodeHandle node);
    void (*SetAlphabetIndexerSelected)(NodeHandle node, int32_t value);
    void (*ResetAlphabetIndexerSelected)(NodeHandle node);
    void (*SetPopupHorizontalSpace)(NodeHandle node, double value, int unit);
    void (*ResetPopupHorizontalSpace)(NodeHandle node);
    void (*SetPopupSelectedColor)(NodeHandle node, uint32_t color);
    void (*ResetPopupSelectedColor)(NodeHandle node);
    void (*SetItemSize)(NodeHandle node, double value, int unit);
    void (*ResetItemSize)(NodeHandle node);
    void (*SetPopupPosition)(NodeHandle node, double xValue, int xUnit, double yValue, int yUnit);
    void (*ResetPopupPosition)(NodeHandle node);
};

struct ArkUISwiperModifierAPI {
    void (*SetSwiperNextMargin)(NodeHandle node, double nextMarginValue, int32_t nextMarginUnit);
    void (*ResetSwiperNextMargin)(NodeHandle node);
    void (*SetSwiperPrevMargin)(NodeHandle node, double prevMarginValue, int32_t prevMarginUnit);
    void (*ResetSwiperPrevMargin)(NodeHandle node);
    void (*SetSwiperDisplayCount)(NodeHandle node, const char* displayCountChar, const char* displayCountType);
    void (*ResetSwiperDisplayCount)(NodeHandle node);
    void (*SetSwiperDisplayArrow)(NodeHandle node, const char* displayArrowStr);
    void (*ResetSwiperDisplayArrow)(NodeHandle node);
    void (*SetSwiperCurve)(NodeHandle node, const char* curveChar);
    void (*ResetSwiperCurve)(NodeHandle node);
    void (*SetSwiperDisableSwipe)(NodeHandle node, bool disableSwipe);
    void (*ResetSwiperDisableSwipe)(NodeHandle node);
    void (*SetSwiperEffectMode)(NodeHandle node, int32_t edgeEffect);
    void (*ResetSwiperEffectMode)(NodeHandle node);
    void (*SetSwiperCachedCount)(NodeHandle node, int32_t cachedCount);
    void (*ResetSwiperCachedCount)(NodeHandle node);
    void (*SetSwiperDisplayMode)(NodeHandle node, int32_t displayMode);
    void (*ResetSwiperDisplayMode)(NodeHandle node);
    void (*SetSwiperItemSpace)(NodeHandle node, double itemSpaceValue, int32_t itemSpaceUnit);
    void (*ResetSwiperItemSpace)(NodeHandle node);
    void (*SetSwiperVertical)(NodeHandle node, bool isVertical);
    void (*ResetSwiperVertical)(NodeHandle node);
    void (*SetSwiperLoop)(NodeHandle node, bool loop);
    void (*ResetSwiperLoop)(NodeHandle node);
    void (*SetSwiperInterval)(NodeHandle node, int32_t interval);
    void (*ResetSwiperInterval)(NodeHandle node);
    void (*SetSwiperAutoPlay)(NodeHandle node, bool autoPlay);
    void (*ResetSwiperAutoPlay)(NodeHandle node);
    void (*SetSwiperIndex)(NodeHandle node, int32_t index);
    void (*ResetSwiperIndex)(NodeHandle node);
    void (*SetSwiperIndicator)(NodeHandle node, const char* indicatorStr);
    void (*ResetSwiperIndicator)(NodeHandle node);
    void (*SetSwiperDuration)(NodeHandle node, int32_t duration);
    void (*ResetSwiperDuration)(NodeHandle node);
    void (*SetSwiperEnabled)(NodeHandle node, bool enabled);
    void (*ResetSwiperEnabled)(NodeHandle node);
};

struct ArkUIDataPanelModifierAPI {
    void (*SetCloseEffect)(NodeHandle node, bool value);
    void (*ResetCloseEffect)(NodeHandle node);
    void (*SetDataPanelTrackBackgroundColor)(NodeHandle node, uint32_t value);
    void (*ResetDataPanelTrackBackgroundColor)(NodeHandle node);
    void (*SetDataPanelStrokeWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetDataPanelStrokeWidth)(NodeHandle node);
    void (*SetValueColors)(NodeHandle node, const struct ArkUIGradientType* gradient);
    void (*ResetValueColors)(NodeHandle node);
    void (*SetTrackShadow)(
        NodeHandle node, const struct ArkUIGradientType* gradient, double radius, double offsetX, double offsetY);
    void (*SetNullTrackShadow)(NodeHandle node);
    void (*ResetTrackShadow)(NodeHandle node);
};

struct ArkUIGaugeModifierAPI {
    void (*SetGaugeVaule)(NodeHandle node, float vaule);
    void (*ResetGaugeVaule)(NodeHandle node);
    void (*SetGaugeStartAngle)(NodeHandle node, float vaule);
    void (*ResetGaugeStartAngle)(NodeHandle node);
    void (*SetGaugeEndAngle)(NodeHandle node, float vaule);
    void (*ResetGaugeEndAngle)(NodeHandle node);
    void (*SetGaugeStrokeWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetGaugeStrokeWidth)(NodeHandle node);
    void (*SetShadowOptions)(NodeHandle node, double radius, double offsetX, double offsetY, bool isShadowVisible);
    void (*ResetShadowOptions)(NodeHandle node);
    void (*SetIsShowIndicator)(NodeHandle node, bool isShowIndicator);
    void (*SetIndicatorIconPath)(NodeHandle node, const char* iconPath,
        const char* bundleName, const char* moduleName);
    void (*ResetIndicatorIconPath)(NodeHandle node);
    void (*SetIndicatorSpace)(NodeHandle node, const char* spaceStrValue, double spaceValue, int32_t spaceUnit);
    void (*ResetIndicatorSpace)(NodeHandle node);
    void (*SetColors)(NodeHandle node, const uint32_t* colors, const float* weight, uint32_t length);
    void (*ResetColors)(NodeHandle node);
    void (*SetGradientColors)(NodeHandle node, const struct ArkUIGradientType* gradient, uint32_t weightLength);
    void (*ResetGradientColors)(NodeHandle node);
};

struct ArkUIScrollModifierAPI {
    void (*SetScrollNestedScroll)(NodeHandle node, int32_t scrollForward, int32_t scrollBackward);
    void (*ResetScrollNestedScroll)(NodeHandle node);
    void (*SetScrollEnableScroll)(NodeHandle node, bool value);
    void (*ResetScrollEnableScroll)(NodeHandle node);
    void (*SetScrollFriction)(NodeHandle node, double value);
    void (*ResetScrollFriction)(NodeHandle node);
    void (*SetScrollScrollSnap)(NodeHandle node, const double* paginationValue, int32_t paginationSize,
        const int32_t* paginationParam, int32_t paramSize);
    void (*ResetScrollScrollSnap)(NodeHandle node);
    void (*SetScrollScrollBar)(NodeHandle node, int32_t value);
    void (*ResetScrollScrollBar)(NodeHandle node);
    void (*SetScrollScrollable)(NodeHandle node, int32_t scrollDirection);
    void (*ResetScrollScrollable)(NodeHandle node);
    void (*SetScrollScrollBarColor)(NodeHandle node, uint32_t scrollBarColor);
    void (*ResetScrollScrollBarColor)(NodeHandle node);
    void (*SetScrollScrollBarWidth)(NodeHandle node, double value, int32_t unit);
    void (*ResetScrollScrollBarWidth)(NodeHandle node);
    void (*SetScrollEdgeEffect)(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled);
    void (*ResetScrollEdgeEffect)(NodeHandle node);
};

struct ArkUIListItemModifierAPI {
    void (*SetListItemSelected)(NodeHandle node, bool selected);
    void (*ResetListItemSelected)(NodeHandle node);
    void (*SetSelectable)(NodeHandle node, bool selectable);
    void (*ResetSelectable)(NodeHandle node);
};

struct ArkUIProgressModifierAPI {
    void (*SetProgressValue)(NodeHandle node, double value);
    void (*ResetProgressValue)(NodeHandle node);
    void (*SetProgressGradientColor)(NodeHandle node, const struct ArkUIGradientType* gradient, int32_t length);
    void (*SetProgressColor)(NodeHandle node, uint32_t color);
    void (*ResetProgressColor)(NodeHandle node);
    void (*SetProgressStyle)(NodeHandle node, ArkUIProgressStyle *value);
    void (*ResetProgressStyle)(NodeHandle node);
    void (*SetProgressBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetProgressBackgroundColor)(NodeHandle node);
};

#ifdef PLUGIN_COMPONENT_SUPPORTED
struct ArkUIPluginModifierAPI {
    void (*SetPluginWidth)(NodeHandle node, double widthVal, int32_t widthUnit);
    void (*SetPluginHeight)(NodeHandle node, double heightVal, int32_t heightUnit);
    void (*SetPluginSize)(NodeHandle node, double widthVal, double heightVal, int32_t widthUnit, int32_t heightUnit);
    void (*ResetPluginWidth)(NodeHandle node);
    void (*ResetPluginHeight)(NodeHandle node);
    void (*ResetPluginSize)(NodeHandle node);
};
#endif

struct ArkUIListModifierAPI {
    void (*SetListLanes)(NodeHandle node, int32_t lanesNum, const struct ArkUIDimensionType *minLength,
        const struct ArkUIDimensionType *maxLength, const struct ArkUIDimensionType *gutter);
    void (*ResetListLanes)(NodeHandle node);
    void (*SetEditMode)(NodeHandle node, bool editMode);
    void (*ResetEditMode)(NodeHandle node);
    void (*SetMultiSelectable)(NodeHandle node, bool selectable);
    void (*ResetMultiSelectable)(NodeHandle node);
    void (*SetChainAnimation)(NodeHandle node, bool chainAnimation);
    void (*ResetChainAnimation)(NodeHandle node);
    void (*SetCachedCount)(NodeHandle node, int32_t cachedCount);
    void (*ResetCachedCount)(NodeHandle node);
    void (*SetEnableScrollInteraction)(NodeHandle node, bool enableScrollInteraction);
    void (*ResetEnableScrollInteraction)(NodeHandle node);
    void (*SetSticky)(NodeHandle node, int32_t stickyStyle);
    void (*ResetSticky)(NodeHandle node);
    void (*SetListEdgeEffect)(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled);
    void (*ResetListEdgeEffect)(NodeHandle node);
    void (*SetListDirection)(NodeHandle node, int32_t axis);
    void (*ResetListDirection)(NodeHandle node);
    void (*SetListFriction)(NodeHandle node, double friction);
    void (*ResetListFriction)(NodeHandle node);
    void (*SetListNestedScroll)(NodeHandle node, int32_t forward, int32_t backward);
    void (*ResetListNestedScroll)(NodeHandle node);
    void (*SetListScrollBar)(NodeHandle node, int32_t barState);
    void (*ResetListScrollBar)(NodeHandle node);
    void (*SetAlignListItem)(NodeHandle node, int32_t listItemAlign);
    void (*ResetAlignListItem)(NodeHandle node);
    void (*SetScrollSnapAlign)(NodeHandle node, int32_t scrollSnapAlign);
    void (*ResetScrollSnapAlign)(NodeHandle node);
    void (*ListSetDivider)(
        NodeHandle node, const uint32_t color, const double* values, const int32_t* units, int32_t length);
    void (*ListResetDivider)(NodeHandle node);
    void (*SetChainAnimationOptions)(
        NodeHandle node, const struct ArkUIChainAnimationOptionsType *chainAnimationOptions);
    void (*ResetChainAnimationOptions)(NodeHandle node);
};

struct ArkUIGridItemModifierAPI {
    void (*SetGridItemSelectable)(NodeHandle node, bool selectable);
    void (*ResetGridItemSelectable)(NodeHandle node);
    void (*SetGridItemSelected)(NodeHandle node, bool selected);
    void (*ResetGridItemSelected)(NodeHandle node);
    void (*SetGridItemRowStart)(NodeHandle node, int32_t rowStart);
    void (*ResetGridItemRowStart)(NodeHandle node);
    void (*SetGridItemRowEnd)(NodeHandle node, int32_t rowEnd);
    void (*ResetGridItemRowEnd)(NodeHandle node);
    void (*SetGridItemColumnStart)(NodeHandle node, int32_t columnStart);
    void (*ResetGridItemColumnStart)(NodeHandle node);
    void (*SetGridItemColumnEnd)(NodeHandle node, int32_t columnEnd);
    void (*ResetGridItemColumnEnd)(NodeHandle node);
};

struct ArkUIListItemGroupModifierAPI {
    void (*ListItemGroupSetDivider)(
        NodeHandle node, uint32_t color, const double* values, const int* units, int32_t length);
    void (*ListItemGroupResetDivider)(NodeHandle node);
};

struct ArkUIQRCodeModifierAPI {
    void (*SetQRColor)(NodeHandle node, uint32_t color);
    void (*ResetQRColor)(NodeHandle node);
    void (*SetQRBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetQRBackgroundColor)(NodeHandle node);
    void (*SetContentOpacity)(NodeHandle node, double opacity);
    void (*ResetContentOpacity)(NodeHandle node);
};

#ifdef FORM_SUPPORTED
struct ArkUIFormComponentModifierAPI {
    void (*SetFormVisibility)(NodeHandle node, int32_t visible);
    void (*AllowUpdate)(NodeHandle node, bool value);
    void (*SetDimension)(NodeHandle node, int32_t dimension);
    void (*SetModuleName)(NodeHandle node, const char* value);
    void (*SetFormSize)(
        NodeHandle node, double widthValue, int32_t widthUnit, double heightValue, int32_t heightUnit);
    void (*ResetFormVisibility)(NodeHandle node);
    void (*DisallowUpdate)(NodeHandle node);
    void (*ResetDimension)(NodeHandle node);
    void (*ResetModuleName)(NodeHandle node);
    void (*ResetFormSize)(NodeHandle node);
};
#endif

struct ArkUICommonShapeModifierAPI {
    void (*SetStrokeDashArray)(NodeHandle node, double* dashArray, int32_t* dimUnits, int32_t size);
    void (*ResetStrokeDashArray)(NodeHandle node);
    void (*SetStrokeMiterLimit)(NodeHandle node, const double miterLimit);
    void (*ResetStrokeMiterLimit)(NodeHandle node);
    void (*SetFillOpacity)(NodeHandle node, const double fillOpacity);
    void (*ResetFillOpacity)(NodeHandle node);
    void (*SetStrokeOpacity)(NodeHandle node, const double strokeOpacity);
    void (*ResetStrokeOpacity)(NodeHandle node);
    void (*SetStrokeWidth)(NodeHandle node, double value, int unit);
    void (*ResetStrokeWidth)(NodeHandle node);
    void (*SetAntiAlias)(NodeHandle node, const bool antiAlias);
    void (*ResetAntiAlias)(NodeHandle node);
    void (*SetStroke)(NodeHandle node, const uint32_t stroke);
    void (*ResetStroke)(NodeHandle node);
    void (*SetFill)(NodeHandle node, const uint32_t fill);
    void (*ResetFill)(NodeHandle node);
    void (*SetStrokeDashOffset)(NodeHandle node, double value, int unit);
    void (*ResetStrokeDashOffset)(NodeHandle node);
    void (*SetStrokeLineCap)(NodeHandle node, const int strokeLineCap);
    void (*ResetStrokeLineCap)(NodeHandle node);
    void (*SetStrokeLineJoin)(NodeHandle node, const int lineJoinStyle);
    void (*ResetStrokeLineJoin)(NodeHandle node);
    void (*SetShapeWidth)(NodeHandle node);
    void (*ResetShapeWidth)(NodeHandle node);
    void (*SetShapeHeight)(NodeHandle node);
    void (*ResetShapeHeight)(NodeHandle node);
    void (*SetShapeForegroundColor)(NodeHandle node, bool isColor, uint32_t color);
    void (*ResetShapeForegroundColor)(NodeHandle node);
};

struct ArkUIShapeModifierAPI {
    void (*SetShapeViewPort)(NodeHandle node, double* dimValues, int32_t* dimUnits);
    void (*ResetShapeViewPort)(NodeHandle node);
    void (*SetShapeMesh)(NodeHandle node, const double* mesh, size_t arrayItemCount, int32_t column, int32_t row);
    void (*ResetShapeMesh)(NodeHandle node);
};

struct ArkUIRectModifierAPI {
    void (*SetRectRadiusWidth)(NodeHandle node, double radiusWidthValue, int32_t radiusWidthUnit);
    void (*ResetRectRadiusWidth)(NodeHandle node);
    void (*SetRectRadiusHeight)(NodeHandle node, double radiusHeightValue, int32_t radiusHeightUnit);
    void (*ResetRectRadiusHeight)(NodeHandle node);
    void (*SetRectRadiusWithArray)(NodeHandle node, double* radiusValues, int32_t* radiusUnits,
        uint32_t* radiusValidPairs, size_t radiusValidPairsSize);
    void (*SetRectRadiusWithValue)(NodeHandle node, double radiusValue, int32_t radiusUnit);
    void (*ResetRectRadius)(NodeHandle node);
};

struct ArkUITextTimerModifierAPI {
    void (*SetFontColor)(NodeHandle node, uint32_t color);
    void (*ResetFontColor)(NodeHandle node);
    void (*SetFontSize)(NodeHandle node, double value, int32_t unit);
    void (*ResetFontSize)(NodeHandle node);
    void (*SetFontStyle)(NodeHandle node, uint32_t fontStyle);
    void (*ResetFontStyle)(NodeHandle node);
    void (*SetFontWeight)(NodeHandle node, const char* weight);
    void (*ResetFontWeight)(NodeHandle node);
    void (*SetFontFamily)(NodeHandle node, const char *fontFamily);
    void (*ResetFontFamily)(NodeHandle node);
    void (*SetTextTimerFormat)(NodeHandle node, const char* format);
    void (*ResetTextTimerFormat)(NodeHandle node);
};

struct ArkUILoadingProgressModifierAPI {
    void (*SetColor)(NodeHandle node, uint32_t color);
    void (*ResetColor)(NodeHandle node);
    void (*SetEnableLoading)(NodeHandle node, bool value);
    void (*ResetEnableLoading)(NodeHandle node);
};

struct ArkUITextClockModifierAPI {
    void (*SetFormat)(NodeHandle node, const char* format);
    void (*ResetFormat)(NodeHandle node);
    void (*SetFontColor)(NodeHandle node, uint32_t color);
    void (*ResetFontColor)(NodeHandle node);
    void (*SetFontSize)(NodeHandle node, double value, int unit);
    void (*ResetFontSize)(NodeHandle node);
    void (*SetFontStyle)(NodeHandle node, uint32_t fontStyle);
    void (*ResetFontStyle)(NodeHandle node);
    void (*SetFontWeight)(NodeHandle node, const char* weight);
    void (*ResetFontWeight)(NodeHandle node);
    void (*SetFontFamily)(NodeHandle node, const char *fontFamily);
    void (*ResetFontFamily)(NodeHandle node);
};
#ifdef XCOMPONENT_SUPPORTED
struct ArkUIXComponentModifierAPI {
    void (*SetXComponentBackgroundColor)(NodeHandle node, uint32_t color);
    void (*ResetXComponentBackgroundColor)(NodeHandle node);
    void (*SetXComponentOpacity)(NodeHandle node, double opacity);
    void (*ResetXComponentOpacity)(NodeHandle node);
};
#endif

struct ArkUIRenderNodeModifierAPI {
    void (*AppendChild)(NodeHandle node, NodeHandle child);
    void (*InsertChildAfter)(NodeHandle node, NodeHandle child, NodeHandle sibling);
    void (*RemoveChild)(NodeHandle node, NodeHandle child);
    void (*ClearChildren)(NodeHandle node);
    void (*SetClipToFrame)(NodeHandle node, bool useClip);
    void (*SetRotation)(NodeHandle node, double rotationX, double rotationY, double rotationZ);
    void (*SetShadowColor)(NodeHandle node, uint32_t color);
    void (*SetShadowOffset)(NodeHandle node, double offsetX, double offsetY);
    void (*SetShadowAlpha)(NodeHandle node, float alpha);
    void (*SetShadowElevation)(NodeHandle node, float elevation);
    void (*SetShadowRadius)(NodeHandle node, float radius);
    void (*Invalidate)(NodeHandle node);
    void (*SetScale)(NodeHandle node, float scaleX, float scaleY);
    void (*SetRenderNodeBackgroundColor)(NodeHandle node, uint32_t colorValue);
    void (*SetPivot)(NodeHandle node, float pivotX, float pivotY);
    void (*SetFrame)(NodeHandle node, float positionX, float positionY, float width, float height);
    void (*SetSize)(NodeHandle node, float width, float height);
    void (*SetOpacity)(NodeHandle node, float opacity);
    void (*SetTranslate)(NodeHandle node, float translateX, float translateY, float translateZ);
};

struct ArkUINodeAPI {
    NodeHandle (*GetFrameNodeById)(int nodeId);
    int64_t (*GetUIState)(NodeHandle node);
    void (*SetSupportedUIState)(NodeHandle node, uint64_t state);
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
    ArkUIGridModifierAPI (*GetGridModifier)();
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
    ArkUINodeContainerModifierAPI (*GetNodeContainerModifier)();
    ArkUIPatternLockModifierAPI (*GetPatternLockModifier)();
    ArkUIColumnSplitModifierAPI (*GetColumnSplitModifier)();
    ArkUILineModifierAPI (*GetLineModifier)();
    ArkUIPathModifierAPI (*GetPathModifier)();
    ArkUIPolygonModifierAPI (*GetPolygonModifier)();
    ArkUIPolylineModifierAPI (*GetPolylineModifier)();
    ArkUISpanModifierAPI (*GetSpanModifier)();
    ArkUIImageAnimatorModifierAPI (*GetImageAnimatorModifier)();
    ArkUISideBarContainerModifierAPI (*GetSideBarContainerModifier)();
    ArkUICalendarPickerModifierAPI (*GetCalendarPickerModifier)();
    ArkUITextInputModifierAPI (*GetTextInputModifier)();
    ArkUITabsModifierAPI (*GetTabsModifier)();
    ArkUIStepperItemModifierAPI (*GetStepperItemModifier)();
    ArkUIHyperlinkModifierAPI (*GetHyperlinkModifier)();
    ArkUIMarqueeModifierAPI (*GetMarqueeModifier)();
    ArkUIMenuItemModifierAPI (*GetMenuItemModifier)();
    ArkUIMenuModifierAPI (*GetMenuModifier)();
    ArkUIDatePickerModifierAPI (*GetDatePickerModifier)();
    ArkUIWaterFlowModifierAPI (*GetWaterFlowModifier)();
    ArkUIAlphabetIndexerModifierAPI (*GetAlphabetIndexerModifier)();
    ArkUIDataPanelModifierAPI (*GetDataPanelModifier)();
    ArkUIGaugeModifierAPI (*GetGaugeModifier)();
    ArkUIScrollModifierAPI (*GetScrollModifier)();
    ArkUIGridItemModifierAPI (*GetGridItemModifier)();
    ArkUIProgressModifierAPI (*GetProgressModifier)();
    ArkUICommonShapeModifierAPI(*GetCommonShapeModifier)();
    ArkUIShapeModifierAPI(*GetShapeModifier)();
    ArkUIRectModifierAPI (*GetRectModifier)();
    ArkUISwiperModifierAPI (*GetSwiperModifier)();
    ArkUIListItemModifierAPI (*GetListItemModifier)();
    ArkUIListModifierAPI (*GetListModifier)();
    ArkUIListItemGroupModifierAPI(*GetListItemGroupModifier)();
    ArkUIQRCodeModifierAPI (*GetQRCodeModifier)();
    ArkUILoadingProgressModifierAPI (*GetLoadingProgressModifier)();
    ArkUITextClockModifierAPI (*GetTextClockModifier)();
    ArkUITextTimerModifierAPI (*GetTextTimerModifier)();
    ArkUIRenderNodeModifierAPI (*GetRenderNodeModifier)();

#ifdef PLUGIN_COMPONENT_SUPPORTED
    ArkUIPluginModifierAPI (*GetPluginModifier)();
#endif
#ifdef XCOMPONENT_SUPPORTED
    ArkUIXComponentModifierAPI (*GetXComponentModifier)();
#endif
#ifdef FORM_SUPPORTED
    ArkUIFormComponentModifierAPI (*GetFormComponentModifier)();
#endif
};
ArkUINodeAPI* GetArkUIInternalNodeAPI();
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H