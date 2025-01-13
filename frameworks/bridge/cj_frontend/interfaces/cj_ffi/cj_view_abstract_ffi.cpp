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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_pixel_unit_convert_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/matrix4/cj_matrix4_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Matrix4;
using namespace OHOS::Ace::Framework;

namespace {
using DoubleBindCallback = std::function<void(const std::string&)>;
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr float ROUND_UNIT = 360.0;
constexpr float DEFAULT_BIAS = 0.5f;
constexpr double HUNDRED = 100.0;
constexpr int SHEET_HEIGHT_MEDIUM = 0;
constexpr int SHEET_HEIGHT_LARGE = 1;
constexpr int SHEET_HEIGHT_FITCONTENT = 2;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<ImageRepeat> IMAGES_REPEATS = { ImageRepeat::NO_REPEAT, ImageRepeat::REPEAT_X, ImageRepeat::REPEAT_Y,
    ImageRepeat::REPEAT };
const std::vector<BackgroundImageSizeType> IMAGE_SIZES = { BackgroundImageSizeType::CONTAIN,
    BackgroundImageSizeType::COVER, BackgroundImageSizeType::AUTO };
const std::vector<TextDirection> TEXT_DIRECTIONS = { TextDirection::LTR, TextDirection::RTL, TextDirection::AUTO };
const std::vector<WindowBlurStyle> WINDOW_BLUR_STYLES = { WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT,
    WindowBlurStyle::STYLE_BACKGROUND_MEDIUM_LIGHT, WindowBlurStyle::STYLE_BACKGROUND_LARGE_LIGHT,
    WindowBlurStyle::STYLE_BACKGROUND_XLARGE_LIGHT, WindowBlurStyle::STYLE_BACKGROUND_SMALL_DARK,
    WindowBlurStyle::STYLE_BACKGROUND_MEDIUM_DARK, WindowBlurStyle::STYLE_BACKGROUND_LARGE_DARK,
    WindowBlurStyle::STYLE_BACKGROUND_XLARGE_DARK };
const std::vector<FlexAlign> ITEM_ALIGNS = { FlexAlign::AUTO, FlexAlign::FLEX_START, FlexAlign::CENTER,
    FlexAlign::FLEX_END, FlexAlign::STRETCH, FlexAlign::BASELINE };
const std::vector<VisibleType> VISIBILITIES = {
    VisibleType::VISIBLE,
    VisibleType::INVISIBLE,
    VisibleType::GONE,
};
const std::vector<OHOS::Ace::Framework::CJResponseType> RESPONSE_TYPES = {
    OHOS::Ace::Framework::CJResponseType::RIGHT_CLICK, OHOS::Ace::Framework::CJResponseType::LONGPRESS
};

const std::vector<Align> ALIGNS = { Align::TOP_LEFT, Align::TOP_CENTER, Align::TOP_RIGHT, Align::CENTER_LEFT,
    Align::CENTER, Align::CENTER_RIGHT, Align::BOTTOM_LEFT, Align::BOTTOM_CENTER, Align::BOTTOM_RIGHT };

const std::vector<Alignment> ALIGNMENT_LIST = { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };

const std::vector<RenderFit> RENDERFITS = { RenderFit::CENTER, RenderFit::TOP, RenderFit::BOTTOM, RenderFit::LEFT,
    RenderFit::RIGHT, RenderFit::TOP_LEFT, RenderFit::TOP_RIGHT, RenderFit::BOTTOM_LEFT, RenderFit::BOTTOM_RIGHT,
    RenderFit::RESIZE_FILL, RenderFit::RESIZE_CONTAIN, RenderFit::RESIZE_CONTAIN_TOP_LEFT,
    RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT, RenderFit::RESIZE_COVER, RenderFit::RESIZE_COVER_TOP_LEFT,
    RenderFit::RESIZE_COVER_BOTTOM_RIGHT };

// Regex for match the placeholder.
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);

void UpdateBackgroundImagePosition(const DimensionUnit& typeX, const DimensionUnit& typeY, const double valueX,
    const double valueY, BackgroundImagePosition& bgImgPosition)
{
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY));
}

void UpdateBackgroundImagePosition(const Align& align, BackgroundImagePosition& bgImgPosition)
{
    switch (static_cast<Align>(align)) {
        case Align::TOP_LEFT:
            UpdateBackgroundImagePosition(DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, 0.0, bgImgPosition);
            break;
        case Align::TOP_CENTER:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, 0.0, bgImgPosition);
            break;
        case Align::TOP_RIGHT:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, 0.0, bgImgPosition);
            break;
        case Align::CENTER_LEFT:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, HALF_DIMENSION, bgImgPosition);
            break;
        case Align::CENTER:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, HALF_DIMENSION, bgImgPosition);
            break;
        case Align::CENTER_RIGHT:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, HALF_DIMENSION, bgImgPosition);
            break;
        case Align::BOTTOM_LEFT:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, 0.0, FULL_DIMENSION, bgImgPosition);
            break;
        case Align::BOTTOM_CENTER:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, HALF_DIMENSION, FULL_DIMENSION, bgImgPosition);
            break;
        case Align::BOTTOM_RIGHT:
            UpdateBackgroundImagePosition(
                DimensionUnit::PERCENT, DimensionUnit::PERCENT, FULL_DIMENSION, FULL_DIMENSION, bgImgPosition);
            break;
        default:
            break;
    }
}

void DealBindPopupParams(bool isShow, const CJBindPopupParams& bindPopupParams,
    const std::function<void(bool)>& onStateChangeFunc, const std::function<void()>& primaryActionFunc,
    const std::function<void()>& secondaryActionFunc)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(isShow);
    popupParam->SetMessage(bindPopupParams.message);
    popupParam->SetPlacement(bindPopupParams.placementOnTop ? Placement::TOP : Placement::BOTTOM);
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };
    popupParam->SetOnStateChange(onStateChangeCallback);
    std::string primaryString = bindPopupParams.primaryValue;
    if (!primaryString.empty()) {
        ButtonProperties propertiesPrimary;
        propertiesPrimary.value = primaryString;
        auto touchPrimaryCallback = [primaryActionFunc](TouchEventInfo&) { primaryActionFunc(); };
        auto onNewClick = [primaryActionFunc](const GestureEvent& info) -> void { primaryActionFunc(); };
        propertiesPrimary.touchFunc = touchPrimaryCallback;
        propertiesPrimary.action = AceType::MakeRefPtr<NG::ClickEvent>(onNewClick);
        propertiesPrimary.showButton = true;
        popupParam->SetPrimaryButtonProperties(propertiesPrimary);
    }

    std::string secondaryString = bindPopupParams.secondaryValue;
    if (!secondaryString.empty()) {
        ButtonProperties propertiesSecondary;
        propertiesSecondary.value = secondaryString;
        auto touchSecondaryCallback = [secondaryActionFunc](TouchEventInfo&) { secondaryActionFunc(); };
        auto onNewClick = [secondaryActionFunc](const GestureEvent& info) -> void { secondaryActionFunc(); };
        propertiesSecondary.touchFunc = touchSecondaryCallback;
        propertiesSecondary.action = AceType::MakeRefPtr<NG::ClickEvent>(onNewClick);
        propertiesSecondary.showButton = true;
        popupParam->SetSecondaryButtonProperties(propertiesSecondary);
    }
    ViewAbstractModel::GetInstance()->BindPopup(popupParam, nullptr);
}

/**
 * Method for replacing placeholders reserved in advance by actual content.
 * @example "hello %s" -> "hello world"
 * @param originStr
 * @param param
 * @todo Replacing multiple placeholders at the same time
 */
void ReplaceHolder(std::string& originStr, const std::string& param)
{
    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matchs;
    bool shortHolderType = false;
    bool firstMatch = true;
    while (std::regex_search(start, end, matchs, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matchs[2];
        std::string type = matchs[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (shortHolderType ^ (pos.length() == 0)) {
                LOGE("wrong place holder,stop parse string");
                return;
            }
        }
        originStr.replace(matchs[0].first - originStr.begin(), matchs[0].length(), param);
        start = originStr.begin() + matchs.prefix().length() + param.length();
        end = originStr.end();
    }
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkViewAbstractSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetWidth(value);
}

void FfiOHOSAceFrameworkViewAbstractSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetHeight(value);
}

void FFISetWidthWithEmpty()
{
    ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
}

void FFISetHeightWithEmpty()
{
    ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
}

void FfiOHOSAceFrameworkViewAbstractSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));

    if (LessNotEqual(widthDime.Value(), 0.0)) {
        widthDime.SetValue(0.0);
    }
    if (LessNotEqual(heightDime.Value(), 0.0)) {
        heightDime.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetWidth(widthDime);
    ViewAbstractModel::GetInstance()->SetHeight(heightDime);
}

void FfiOHOSAceFrameworkViewAbstractSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
}

void FfiOHOSAceFrameworkViewAbstractSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    ViewAbstractModel::GetInstance()->SetResponseRegion(result);
}

void FfiOHOSAceFrameworkViewAbstractSetConstraintSize(CJConstraintSize value)
{
    Dimension minWidthDime(value.minWidth, static_cast<DimensionUnit>(value.minWidthUnit));
    Dimension maxWidthDime(value.maxWidth, static_cast<DimensionUnit>(value.maxWidthUnit));
    Dimension minHeightDime(value.minHeight, static_cast<DimensionUnit>(value.minHeightUnit));
    Dimension maxHeightDime(value.maxHeight, static_cast<DimensionUnit>(value.maxHeightUnit));

    ViewAbstractModel::GetInstance()->SetMinWidth(minWidthDime);
    ViewAbstractModel::GetInstance()->SetMaxWidth(maxWidthDime);
    ViewAbstractModel::GetInstance()->SetMinHeight(minHeightDime);
    ViewAbstractModel::GetInstance()->SetMaxHeight(maxHeightDime);
}

void FfiOHOSAceFrameworkViewAbstractSetLayoutPriority(int32_t value)
{
    ViewAbstractModel::GetInstance()->SetLayoutPriority(value);
}

void FfiOHOSAceFrameworkViewAbstractSetLayoutWeight(int32_t value)
{
    ViewAbstractModel::GetInstance()->SetLayoutWeight(value);
}

void FfiOHOSAceFrameworkViewAbstractSetBorder(CJBorder params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension radiusDime(params.radius, static_cast<DimensionUnit>(params.radiusUnit));
    if (!Utils::CheckParamsValid(params.style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }

    ViewAbstractModel::GetInstance()->SetBorderWidth(widthDime);
    ViewAbstractModel::GetInstance()->SetBorderColor(Color(params.color));
    ViewAbstractModel::GetInstance()->SetBorderRadius(radiusDime);
    ViewAbstractModel::GetInstance()->SetBorderStyle(BORDER_STYLES[params.style]);
}

void FfiOHOSAceFrameworkViewAbstractSetBorderWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));

    ViewAbstractModel::GetInstance()->SetBorderWidth(value);
}

void FfiOHOSAceFrameworkViewAbstractSetBorderWidthWithCJEdge(CJEdge params)
{
    std::optional<CalcDimension> leftDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> bottomDimen;
    CalcDimension left(params.left, static_cast<DimensionUnit>(params.leftUnit));
    CalcDimension right(params.right, static_cast<DimensionUnit>(params.rightUnit));
    CalcDimension top(params.top, static_cast<DimensionUnit>(params.topUnit));
    CalcDimension bottom(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));

    if (left.Unit() == DimensionUnit::PERCENT || left.IsNegative()) {
        left.Reset();
    }
    leftDimen = left;

    if (right.Unit() == DimensionUnit::PERCENT || right.IsNegative()) {
        right.Reset();
    }
    rightDimen = right;

    if (top.Unit() == DimensionUnit::PERCENT || top.IsNegative()) {
        top.Reset();
    }
    topDimen = top;

    if (bottom.Unit() == DimensionUnit::PERCENT || bottom.IsNegative()) {
        bottom.Reset();
    }
    bottomDimen = bottom;

    ViewAbstractModel::GetInstance()->SetBorderWidth(leftDimen, rightDimen, topDimen, bottomDimen);
}

void FfiOHOSAceFrameworkViewAbstractSetBorderColor(uint32_t color)
{
    ViewAbstractModel::GetInstance()->SetBorderColor(Color(color));
}

void FfiOHOSAceFrameworkViewAbstractSetBorderRadius(double radius, int32_t unit)
{
    Dimension value(radius, static_cast<DimensionUnit>(unit));

    ViewAbstractModel::GetInstance()->SetBorderRadius(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAllBorderRadius(CJBorderRadius value)
{
    CalcDimension topLeft(value.topLeft, static_cast<DimensionUnit>(value.topLeftUnit));
    CalcDimension topRight(value.topRight, static_cast<DimensionUnit>(value.topRightUnit));
    CalcDimension bottomLeft(value.bottomLeft, static_cast<DimensionUnit>(value.bottomLeftUnit));
    CalcDimension bottomRight(value.bottomRight, static_cast<DimensionUnit>(value.bottomRightUnit));
    ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
}

void FfiOHOSAceFrameworkViewAbstractSetBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for border style");
        return;
    }

    ViewAbstractModel::GetInstance()->SetBorderStyle(BORDER_STYLES[style]);
}

void FfiOHOSAceFrameworkViewAbstractSetMargin(double margin, int32_t unit)
{
    Dimension value(margin, static_cast<DimensionUnit>(unit));

    ViewAbstractModel::GetInstance()->SetMargin(value);
}

void FfiOHOSAceFrameworkViewAbstractSetMargins(CJEdge params)
{
    Dimension topDime(params.top, static_cast<DimensionUnit>(params.topUnit));
    Dimension rightDime(params.right, static_cast<DimensionUnit>(params.rightUnit));
    Dimension bottomDime(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    Dimension leftDime(params.left, static_cast<DimensionUnit>(params.leftUnit));

    ViewAbstractModel::GetInstance()->SetMargins(topDime, bottomDime, leftDime, rightDime);
}

void FfiOHOSAceFrameworkViewAbstractSetPadding(double padding, int32_t unit)
{
    Dimension value(padding, static_cast<DimensionUnit>(unit));

    ViewAbstractModel::GetInstance()->SetPadding(value);
}

void FfiOHOSAceFrameworkViewAbstractSetPaddings(CJEdge params)
{
    Dimension topDime(params.top, static_cast<DimensionUnit>(params.topUnit));
    Dimension rightDime(params.right, static_cast<DimensionUnit>(params.rightUnit));
    Dimension bottomDime(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    Dimension leftDime(params.left, static_cast<DimensionUnit>(params.leftUnit));

    ViewAbstractModel::GetInstance()->SetPaddings(topDime, bottomDime, leftDime, rightDime);
}

void FfiOHOSAceFrameworkViewAbstractSetForegroundBlurStyleOption(int32_t blurStyle, CJForegroundBlurStyle options)
{
    BlurStyleOption styleOption;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }

    auto colorMode = options.colorMode;
    if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
        colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
        styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
    }

    auto adaptiveColor = options.adaptiveColor;
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    BlurOption blurOption;
    std::vector<float> greyVec(2); // 2 number
    greyVec[0] = options.blurOptions.grayscale[0];
    greyVec[1] = options.blurOptions.grayscale[1];
    blurOption.grayscale = greyVec;
    styleOption.blurOption = blurOption;
    ViewAbstractModel::GetInstance()->SetForegroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkViewAbstractSetForegroundBlurStyle(int32_t blurStyle)
{
    BlurStyleOption styleOption;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    ViewAbstractModel::GetInstance()->SetForegroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkViewAbstractSetForegroundColor(char* strategy)
{
    if (strcmp(strategy, "invert") == 0) {
        ForegroundColorStrategy cStrategy = ForegroundColorStrategy::INVERT;
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(cStrategy);
    }
}

void FfiOHOSAceFrameworkViewAbstractSetForegroundResourceColor(uint32_t color)
{
    ViewAbstractModel::GetInstance()->SetForegroundColor(Color(color));
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundColor(uint32_t color)
{
    ViewAbstractModel::GetInstance()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImage(const char* src, int32_t repeat)
{
    if (!Utils::CheckParamsValid(repeat, IMAGES_REPEATS.size())) {
        LOGE("invalid value for image repeat");
        return;
    }

    ImageSourceInfo info(src);
    ViewAbstractModel::GetInstance()->SetBackgroundImage(info, nullptr);
    ViewAbstractModel::GetInstance()->SetBackgroundImageRepeat(IMAGES_REPEATS[repeat]);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImageSizeType(int32_t imageSize)
{
    if (!Utils::CheckParamsValid(imageSize, IMAGE_SIZES.size())) {
        LOGE("invalid value for image repeat");
        return;
    }
    BackgroundImageSize bgImgSize;

    bgImgSize.SetSizeTypeX(IMAGE_SIZES[imageSize]);
    bgImgSize.SetSizeTypeY(IMAGE_SIZES[imageSize]);

    ViewAbstractModel::GetInstance()->SetBackgroundImageSize(bgImgSize);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImageSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));

    BackgroundImageSize bgImgSize;

    double valueWidth = widthDime.ConvertToPx();
    double valueHeight = heightDime.ConvertToPx();
    BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
    BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
    if (widthDime.Unit() == DimensionUnit::PERCENT) {
        typeWidth = BackgroundImageSizeType::PERCENT;
        valueWidth = widthDime.Value() * FULL_DIMENSION;
    }
    if (heightDime.Unit() == DimensionUnit::PERCENT) {
        typeHeight = BackgroundImageSizeType::PERCENT;
        valueHeight = heightDime.Value() * FULL_DIMENSION;
    }
    bgImgSize.SetSizeTypeX(typeWidth);
    bgImgSize.SetSizeValueX(valueWidth);
    bgImgSize.SetSizeTypeY(typeHeight);
    bgImgSize.SetSizeValueY(valueHeight);

    ViewAbstractModel::GetInstance()->SetBackgroundImageSize(bgImgSize);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImagePositionAlign(int32_t align)
{
    if (!Utils::CheckParamsValid(align, ALIGNS.size())) {
        LOGE("invalid value for align");
        return;
    }
    BackgroundImagePosition bgImgPosition;
    bgImgPosition.SetIsAlign(true);
    UpdateBackgroundImagePosition(static_cast<Align>(align), bgImgPosition);
    ViewAbstractModel::GetInstance()->SetBackgroundImagePosition(bgImgPosition);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImagePositionXY(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension xDime(x, static_cast<DimensionUnit>(xUnit));
    Dimension yDime(y, static_cast<DimensionUnit>(yUnit));

    BackgroundImagePosition bgImgPosition;

    DimensionUnit typeX = xDime.Unit();
    DimensionUnit typeY = yDime.Unit();
    double valueX = xDime.ConvertToPx();
    double valueY = yDime.ConvertToPx();
    if (xDime.Unit() == DimensionUnit::LPX) {
        valueX = FfiOHOSAceFrameworkLpx2Px(xDime.Value());
    }
    if (yDime.Unit() == DimensionUnit::LPX) {
        valueY = FfiOHOSAceFrameworkLpx2Px(yDime.Value());
    }
    if (xDime.Unit() == DimensionUnit::PERCENT) {
        valueX = xDime.Value();
    }
    if (yDime.Unit() == DimensionUnit::PERCENT) {
        valueY = yDime.Value();
    }
    UpdateBackgroundImagePosition(typeX, typeY, valueX, valueY, bgImgPosition);

    ViewAbstractModel::GetInstance()->SetBackgroundImagePosition(bgImgPosition);
}

void FfiOHOSAceFrameworkViewAbstractSetScale(CJSetScale value)
{
    Dimension centerXValue(value.centerX, static_cast<DimensionUnit>(value.centerXUnit));
    Dimension centerYValue(value.centerY, static_cast<DimensionUnit>(value.centerYUnit));
    ViewAbstractModel::GetInstance()->SetScale(value.scaleX, value.scaleY, value.scaleZ);
    ViewAbstractModel::GetInstance()->SetPivot(centerXValue, centerYValue, Dimension(0));
}

void FfiOHOSAceFrameworkViewAbstractSetScaleSingle(float scale)
{
    ViewAbstractModel::GetInstance()->SetScale(scale, scale, 1.0f);
}

void FfiOHOSAceFrameworkViewAbstractSetScaleX(float scaleVal)
{
    ViewAbstractModel::GetInstance()->SetScale(scaleVal, 1.0f, 1.0f);
}

void FfiOHOSAceFrameworkViewAbstractSetScaleY(float scaleVal)
{
    ViewAbstractModel::GetInstance()->SetScale(1.0f, scaleVal, 1.0f);
}

void FfiOHOSAceFrameworkViewAbstractSetOpacity(double opacity)
{
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
}

void FfiOHOSAceFrameworkViewAbstractSetRotate(CJSetRotate value)
{
    Dimension centerXValue(value.centerX, static_cast<DimensionUnit>(value.centerXUnit));
    Dimension centerYValue(value.centerY, static_cast<DimensionUnit>(value.centerYUnit));
    ViewAbstractModel::GetInstance()->SetRotate(value.dx, value.dy, value.dz, value.angle);
    ViewAbstractModel::GetInstance()->SetPivot(centerXValue, centerYValue, Dimension(0));
}

void FfiOHOSAceFrameworkViewAbstractSetRotateSingle(float rotateZ)
{
    ViewAbstractModel::GetInstance()->SetRotate(0.0f, 0.0f, 1.0f, rotateZ);
}

void FfiOHOSAceFrameworkViewAbstractSetRotateX(float rotateVal)
{
    ViewAbstractModel::GetInstance()->SetRotate(1.0f, 0.0f, 0.0f, rotateVal);
}

void FfiOHOSAceFrameworkViewAbstractSetRotateY(float rotateVal)
{
    ViewAbstractModel::GetInstance()->SetRotate(0.0f, 1.0f, 0.0f, rotateVal);
}

void FfiOHOSAceFrameworkViewAbstractSetTranslate(CJTranslate value)
{
    Dimension translateX(value.x, static_cast<DimensionUnit>(value.xUnit));
    Dimension translateY(value.y, static_cast<DimensionUnit>(value.yUnit));
    Dimension translateZ(value.z, static_cast<DimensionUnit>(value.zUnit));
    ViewAbstractModel::GetInstance()->SetTranslate(translateX, translateY, translateZ);
}

void FfiOHOSAceFrameworkViewAbstractSetTranslateSingle(double translateValue, int32_t translateUnit)
{
    Dimension translate(translateValue, static_cast<DimensionUnit>(translateUnit));
    ViewAbstractModel::GetInstance()->SetTranslate(translate, translate, translate);
}

void FfiOHOSAceFrameworkViewAbstractSetTranslateX(double translateValue, int32_t translateUnit)
{
    Dimension translate(translateValue, static_cast<DimensionUnit>(translateUnit));
    ViewAbstractModel::GetInstance()->SetTranslate(translate, 0.0_px, 0.0_px);
}

void FfiOHOSAceFrameworkViewAbstractSetTranslateY(double translateValue, int32_t translateUnit)
{
    Dimension translate(translateValue, static_cast<DimensionUnit>(translateUnit));
    ViewAbstractModel::GetInstance()->SetTranslate(0.0_px, translate, 0.0_px);
}

void FfiOHOSAceFrameworkViewAbstractSetTransition()
{
    ViewAbstractModel::GetInstance()->SetTransition(NG::TransitionOptions::GetDefaultTransition(TransitionType::ALL));
}

void FfiOHOSAceFrameworkViewAbstractTransition(int64_t id)
{
    auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(id);
    if (nativeTransitionEffect == nullptr) {
        return;
    }
    auto chainedEffect = nativeTransitionEffect->effect;
    ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect);
}

void FfiOHOSAceFrameworkViewAbstractSetTransform(int64_t id)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto matrix4 = nativeMatrix->GetMatrix4();
        const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
        std::vector<float> matrixVector(matrix4Len);
        for (int32_t i = 0; i < matrix4Len; i++) {
            matrixVector[i] = matrix4[i];
        }
        ViewAbstractModel::GetInstance()->SetTransformMatrix(matrixVector);
    } else {
        LOGE("FfiOHOSMatrix4Translate: invalid id of Matrix");
    }
}

void FfiOHOSAceFrameworkViewAbstractSetAlign(int32_t value)
{
    if (!Utils::CheckParamsValid(value, ALIGNMENT_LIST.size())) {
        LOGE("set align error, invalid value for alignment");
        return;
    }
    ViewAbstractModel::GetInstance()->SetAlign(ALIGNMENT_LIST[value]);
}

void FfiOHOSAceFrameworkViewAbstractSetDirection(int32_t dirValue)
{
    if (!Utils::CheckParamsValid(dirValue, TEXT_DIRECTIONS.size())) {
        LOGE("invalid value for text direction");
        return;
    }
    ViewAbstractModel::GetInstance()->SetLayoutDirection(TEXT_DIRECTIONS[dirValue]);
}

void FfiOHOSAceFrameworkViewAbstractSetPosition(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->SetPosition(dx, dy);
}

void FfiOHOSAceFrameworkViewAbstractSetMarkAnchor(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->MarkAnchor(dx, dy);
}

void FfiOHOSAceFrameworkViewAbstractSetOffset(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->SetOffset(dx, dy);
}

void FfiOHOSAceFrameworkViewAbstractSetAlignRules(CJAlignRuleOption option)
{
    std::map<AlignDirection, AlignRule> alignRules;
    BiasPair biasPair(DEFAULT_BIAS, DEFAULT_BIAS);
    if (option.leftAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.leftAnchor);
        alignRule.horizontal = static_cast<HorizontalAlign>(option.leftHorizontalAlign);
        alignRules[AlignDirection::LEFT] = alignRule;
    }
    if (option.middleAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.middleAnchor);
        alignRule.horizontal = static_cast<HorizontalAlign>(option.middleHorizontalAlign);
        alignRules[AlignDirection::MIDDLE] = alignRule;
    }
    if (option.rightAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.rightAnchor);
        alignRule.horizontal = static_cast<HorizontalAlign>(option.rightHorizontalAlign);
        alignRules[AlignDirection::RIGHT] = alignRule;
    }
    if (option.topAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.topAnchor);
        alignRule.vertical = static_cast<VerticalAlign>(option.topVerticalAlign);
        alignRules[AlignDirection::TOP] = alignRule;
    }
    if (option.centerAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.centerAnchor);
        alignRule.vertical = static_cast<VerticalAlign>(option.centerVerticalAlign);
        alignRules[AlignDirection::CENTER] = alignRule;
    }
    if (option.bottomAnchor != nullptr) {
        AlignRule alignRule;
        alignRule.anchor = std::string(option.bottomAnchor);
        alignRule.vertical = static_cast<VerticalAlign>(option.bottomVerticalAlign);
        alignRules[AlignDirection::BOTTOM] = alignRule;
    }
    if (option.horizontalBias != nullptr) {
        biasPair.first = *option.horizontalBias;
    }
    if (option.verticalBias != nullptr) {
        biasPair.second = *option.verticalBias;
    }

    ViewAbstractModel::GetInstance()->SetAlignRules(alignRules);
    ViewAbstractModel::GetInstance()->SetBias(biasPair);
}

void FfiOHOSAceFrameworkViewAbstractSetEnabled(bool value)
{
    ViewAbstractModel::GetInstance()->SetEnabled(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAspectRatio(double value)
{
    ViewAbstractModel::GetInstance()->SetAspectRatio(static_cast<float>(value));
}

void FfiOHOSAceFrameworkViewAbstractSetDisplayPriority(int32_t value)
{
    ViewAbstractModel::GetInstance()->SetDisplayIndex(value);
}

void FfiOHOSAceFrameworkViewAbstractSetSharedTransition(char* shareId, CJSharedTransitionOptions option)
{
    std::shared_ptr<SharedTransitionOption> sharedOption;
    sharedOption = std::make_shared<SharedTransitionOption>();

    sharedOption->duration = option.duration;
    sharedOption->curve = CreateCurve(std::string(option.curve), false);

    MotionPathOption motionPathOption;
    if (!std::string(option.motionPathOption.path).empty()) {
        motionPathOption.SetPath(std::string(option.motionPathOption.path));
        double from = option.motionPathOption.from;
        double to = option.motionPathOption.to;
        if (from > 1.0 || from < 0.0) {
            from = 0.0;
        }
        if (to > 1.0 || to < 0.0) {
            from = 1.0;
        } else if (to < from) {
            to = from;
        }
        motionPathOption.SetBegin(static_cast<float>(from));
        motionPathOption.SetEnd(static_cast<float>(to));
        motionPathOption.SetRotate(option.motionPathOption.rotatable);
        sharedOption->motionPathOption = motionPathOption;
    }

    sharedOption->delay = option.delay;
    sharedOption->zIndex = option.zIndex;
    sharedOption->type = static_cast<SharedTransitionEffectType>(option.type);

    ViewAbstractModel::GetInstance()->SetSharedTransition(std::string(shareId), sharedOption);
}

void FfiOHOSAceFrameworkViewAbstractSetGeometryTransition(char* id, CJGeometryTransitionOptions option)
{
    bool followWithoutTransition = option.follow;
    bool doRegisterSharedTransition = true;
    switch (option.hierarchyStrategy) {
        case 0:
            doRegisterSharedTransition = false;
            break;
        case 1:
            doRegisterSharedTransition = true;
            break;
        default:
            break;
    }
    ViewAbstractModel::GetInstance()->SetGeometryTransition(
        std::string(id), followWithoutTransition, doRegisterSharedTransition);
}

void FfiOHOSAceFrameworkViewAbstractSetBlur(double value)
{
    Dimension radius(value, DimensionUnit::PX);
    BlurOption options;
    ViewAbstractModel::GetInstance()->SetFrontBlur(radius, options);
}

void FfiOHOSAceFrameworkViewAbstractSetColorBlend(uint32_t color)
{
    ViewAbstractModel::GetInstance()->SetColorBlend(Color(color));
}

void FfiOHOSAceFrameworkViewAbstractSetBackdropBlur(double value)
{
    Dimension radius(value, DimensionUnit::PX);
    BlurOption options;
    ViewAbstractModel::GetInstance()->SetBackdropBlur(radius, options);
}

void FfiOHOSAceFrameworkViewAbstractSetWindowBlur(float progress, int32_t styleValue)
{
    if (!Utils::CheckParamsValid(styleValue, WINDOW_BLUR_STYLES.size())) {
        LOGE("invalid value for window blur style");
        return;
    }
    ViewAbstractModel::GetInstance()->SetWindowBlur(progress, WINDOW_BLUR_STYLES[styleValue]);
}

void FfiOHOSAceFrameworkViewAbstractSetShadow(double radius, uint32_t color, double offsetX, double offsetY)
{
    Dimension dOffsetX(offsetX, DimensionUnit::VP);
    Dimension dOffsetY(offsetY, DimensionUnit::VP);
    if (LessOrEqual(radius, 0.0)) {
        LOGE("Shadow Parse radius failed, radius = %{public}lf", radius);
        return;
    }
    std::vector<Shadow> shadows(1);
    shadows.begin()->SetBlurRadius(radius);
    shadows.begin()->SetOffsetX(dOffsetX.Value());
    shadows.begin()->SetOffsetY(dOffsetY.Value());
    shadows.begin()->SetColor(Color(color));
    ViewAbstractModel::GetInstance()->SetBackShadow(shadows);
}

void FfiOHOSAceFrameworkViewAbstractSetGrayScale(double value)
{
    Dimension dValue(value, DimensionUnit::VP);
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    if (GreatNotEqual(dValue.Value(), 1.0)) {
        dValue.SetValue(1.0);
    }
    ViewAbstractModel::GetInstance()->SetGrayScale(dValue);
}

void FfiOHOSAceFrameworkViewAbstractSetBrightness(double value)
{
    Dimension dValue(value, DimensionUnit::VP);
    ViewAbstractModel::GetInstance()->SetBrightness(dValue);
}

void FfiOHOSAceFrameworkViewAbstractSetSaturate(double value)
{
    Dimension dValue(value, DimensionUnit::VP);
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetSaturate(dValue);
}

void FfiOHOSAceFrameworkViewAbstractSetContrast(double value)
{
    Dimension dValue(value, DimensionUnit::VP);
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetContrast(dValue);
}

void FfiOHOSAceFrameworkViewAbstractSetInvert(double value)
{
    InvertVariant invert = static_cast<float>(value);
    if (LessNotEqual(value, 0.0)) {
        invert = static_cast<float>(0.0);
    }
    ViewAbstractModel::GetInstance()->SetInvert(invert);
}

void FfiOHOSAceFrameworkViewAbstractSetSepia(double value)
{
    Dimension dValue(value, DimensionUnit::VP);
    if (LessNotEqual(dValue.Value(), 0.0)) {
        dValue.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetSepia(dValue);
}

void FfiOHOSAceFrameworkViewAbstractSetHueRotate(float deg)
{
    deg = std::fmod(deg, ROUND_UNIT);
    if (deg < 0.0) {
        deg += ROUND_UNIT;
    }
    ViewAbstractModel::GetInstance()->SetHueRotate(deg);
}

void FfiOHOSAceFrameworkViewAbstractSetFlexBasis(double value, int32_t unit)
{
    Dimension radius(value, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetFlexBasis(radius);
}

void FfiOHOSAceFrameworkViewAbstractSetFlexGrow(double value)
{
    ViewAbstractModel::GetInstance()->SetFlexGrow(static_cast<float>(value));
}

void FfiOHOSAceFrameworkViewAbstractSetFlexShrink(double value)
{
    ViewAbstractModel::GetInstance()->SetFlexShrink(static_cast<float>(value));
}

void FfiOHOSAceFrameworkViewAbstractSetAlignSelf(int32_t alignValue)
{
    if (!Utils::CheckParamsValid(alignValue, ITEM_ALIGNS.size())) {
        LOGE("invalid value for image repeat");
        return;
    }
    ViewAbstractModel::GetInstance()->SetAlignSelf(ITEM_ALIGNS[alignValue]);
}

void FfiOHOSAceFrameworkViewAbstractSetZIndex(int32_t zIndex)
{
    ViewAbstractModel::GetInstance()->SetZIndex(zIndex);
}

void FfiOHOSAceFrameworkViewAbstractSetVisibility(int32_t visibility)
{
    if (!Utils::CheckParamsValid(visibility, VISIBILITIES.size())) {
        LOGE("invalid value for visibility");
        return;
    }
    ViewAbstractModel::GetInstance()->SetVisibility(VISIBILITIES[visibility], [](int32_t visible) {});
}

void FfiOHOSAceFrameworkViewAbstractSetClip(bool isClip)
{
    ViewAbstractModel::GetInstance()->SetClipEdge(isClip);
}

void FfiOHOSAceFrameworkViewAbstractSetClipByShape(int64_t shapeId)
{
    auto context = FFIData::GetData<NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        ViewAbstractModel::GetInstance()->SetClipShape(context->GetBasicShape());
    } else {
        LOGI("set clip error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkViewAbstractSetMaskByShape(int64_t shapeId)
{
    auto context = FFIData::GetData<NativeShapeAbstract>(shapeId);
    if (context != nullptr) {
        ViewAbstractModel::GetInstance()->SetMask(context->GetBasicShape());
    } else {
        LOGI("set mask error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
    }
}

void FfiOHOSAceFrameworkViewAbstractPop()
{
    ViewStackModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameworkViewAbstractSetOverlay(const char* title, int32_t align, double x, double y)
{
    if (!Utils::CheckParamsValid(align, ALIGNMENT_LIST.size())) {
        LOGE("set align error, invalid value for alignment");
        return;
    }
    Dimension offsetX(x, DimensionUnit::VP);
    Dimension offsetY(y, DimensionUnit::VP);
    ViewAbstractModel::GetInstance()->SetOverlay(
        title, nullptr, nullptr, ALIGNMENT_LIST[align], offsetX, offsetY, NG::OverlayType::TEXT);
}

void FfiOHOSAceFrameworkViewAbstractBindPopup(bool isShow, CJBindPopupParams bindPopupParams)
{
    std::function<void(bool)> onStateChangeFunc = (reinterpret_cast<int64_t>(bindPopupParams.onStateChange) == 0)
                                                      ? ([](bool) -> void {})
                                                      : CJLambda::Create(bindPopupParams.onStateChange);
    std::function<void()> primaryActionFunc = (reinterpret_cast<int64_t>(bindPopupParams.primaryAction) == 0)
                                                  ? ([]() -> void {})
                                                  : CJLambda::Create(bindPopupParams.primaryAction);
    std::function<void()> secondaryActionFunc = (reinterpret_cast<int64_t>(bindPopupParams.secondaryAction) == 0)
                                                    ? ([]() -> void {})
                                                    : CJLambda::Create(bindPopupParams.secondaryAction);

    DealBindPopupParams(isShow, bindPopupParams, onStateChangeFunc, primaryActionFunc, secondaryActionFunc);
}

void FfiOHOSAceFrameworkViewAbstractKeyShortcut(
    std::string& value, int32_t* keysArray, int64_t size, void (*callback)(void))
{
    std::vector<ModifierKey> keys(size);
    keys.clear();
    for (size_t i = 0; i < static_cast<size_t>(size); i++) {
        keys.emplace_back(static_cast<ModifierKey>(keysArray[i]));
    }
    int64_t funcId = reinterpret_cast<int64_t>(callback);
    if (funcId == 0) {
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut(value, keys, nullptr);
        return;
    }
    auto onKeyboardShortcutAction = [func = CJLambda::Create(callback)]() { func(); };
    ViewAbstractModel::GetInstance()->SetKeyboardShortcut(value, keys, std::move(onKeyboardShortcutAction));
    return;
}

void FfiOHOSAceFrameworkViewAbstractKeyShortcutByFuncKey(
    int32_t value, int32_t* keysArray, int64_t size, void (*callback)(void))
{
    if (size == 0) {
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut("", std::vector<ModifierKey>(), nullptr);
        return;
    }
    std::string keyValue = Utils::GetFunctionKey(value);
    FfiOHOSAceFrameworkViewAbstractKeyShortcut(keyValue, keysArray, size, callback);
}

void FfiOHOSAceFrameworkViewAbstractKeyShortcutByChar(
    const char* value, int32_t* keysArray, int64_t size, void (*callback)(void))
{
    std::string keyValue(value);
    if (size == 0 || keyValue.empty()) {
        ViewAbstractModel::GetInstance()->SetKeyboardShortcut("", std::vector<ModifierKey>(), nullptr);
        return;
    }
    if (keyValue.size() > 1) {
        return;
    }
    FfiOHOSAceFrameworkViewAbstractKeyShortcut(keyValue, keysArray, size, callback);
}

void FfiOHOSAceFrameworkViewAbstractBindCustomPopup(CJBindCustomPopup value)
{
    std::function<void(bool)> onStateChangeFunc = (reinterpret_cast<int64_t>(value.onStateChange) == 0)
                                                      ? ([](bool) -> void {})
                                                      : CJLambda::Create(value.onStateChange);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(value.isShow);
    popupParam->SetUseCustomComponent(true);
    popupParam->SetPlacement(static_cast<Placement>(value.placement));
    popupParam->SetMaskColor(Color(value.maskColor));
    popupParam->SetBackgroundColor(Color(value.backgroundColor));
    popupParam->SetEnableArrow(value.enableArrow);
    popupParam->SetHasAction(!value.autoCancel);
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };
    popupParam->SetOnStateChange(onStateChangeCallback);
    if (popupParam->IsShow()) {
        auto builderFunc = CJLambda::Create(value.builder);
        RefPtr<AceType> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            builderFunc();
            customNode = ViewStackModel::GetInstance()->Finish();
        }
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, customNode);
    } else {
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, nullptr);
    }
}

void FfiOHOSAceFrameworkViewAbstractBindMenu(
    VectorMenuValuePtr vectorMenuValue, void (*menuActionCallback)(const char*))
{
    auto vectorValue = *reinterpret_cast<std::vector<std::string>*>(vectorMenuValue);
    std::function<void(const std::string&)> menuActionHandle =
        [ffiMenuActionCallback = CJLambda::Create(menuActionCallback)](
            const std::string& value) -> void { ffiMenuActionCallback(value.c_str()); };
    std::vector<NG::OptionParam> params(vectorValue.size());
    for (size_t i = 0; i < vectorValue.size(); ++i) {
        auto label = vectorValue[i];
        params[i].value = label;
        LOGD("option #%{public}d is %{public}s", static_cast<int>(i), params[i].value.c_str());
        params[i].action = [menuActionHandle, label]() { menuActionHandle(label); };
    }
    NG::MenuParam options;
    ViewAbstractModel::GetInstance()->BindMenu(std::move(params), nullptr, options);
}

void FfiOHOSAceFrameworkViewAbstractBindCustomMenu(void (*builder)())
{
    NG::MenuParam params;
    ViewAbstractModel::GetInstance()->BindMenu({}, CJLambda::Create(builder), params);
}

void FfiOHOSAceFrameworkViewAbstractBindContextMenu(void (*builder)(), int32_t responseType)
{
    if (!Utils::CheckParamsValid(responseType, RESPONSE_TYPES.size())) {
        LOGE("bindContextMenu error, invalid value for responseType");
        return;
    }
    NG::MenuParam options { .type = NG::MenuType::CONTEXT_MENU };
    auto buildFunc = CJLambda::Create(builder);
    auto emptyFunc = std::function([] {});
    ViewAbstractModel::GetInstance()->BindContextMenu(
        static_cast<OHOS::Ace::ResponseType>(responseType), buildFunc, options, emptyFunc);
}

static void NewGetCjGradientColorStops(NG::Gradient& gradient, CArrCColors cjColors)
{
    int64_t length = cjColors.size;
    for (int64_t i = 0; i < length; i++) {
        NG::GradientColor gradientColor;
        // color
        uint32_t realColor = cjColors.header[i].color;
        Color color = Color(realColor);
        gradientColor.SetColor(color);
        gradientColor.SetHasValue(false);
        // stop value
        double value = 0.0;
        value = cjColors.header[i].location;
        value = std::clamp(value, 0.0, 1.0);
        gradientColor.SetHasValue(true);
        gradientColor.SetDimension(CalcDimension(value * HUNDRED, DimensionUnit::PERCENT));
        gradient.AddColor(gradientColor);
    }
}

static void NewCjLinearGradient(LinearGradientParam linearGradientParam, NG::Gradient& newGradient)
{
    newGradient.CreateGradientWithType(NG::GradientType::LINEAR);
    // angle
    double* angle = linearGradientParam.angle;
    if (angle != nullptr) {
        newGradient.GetLinearGradient()->angle = CalcDimension(*angle, DimensionUnit::PX);
    }
    // direction
    auto direction = static_cast<GradientDirection>(linearGradientParam.direction);
    switch (direction) {
        case GradientDirection::LEFT:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
            newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
    newGradient.SetRepeat(linearGradientParam.repeating);
    NewGetCjGradientColorStops(newGradient, linearGradientParam.colors);
}

void FfiOHOSAceFrameworkViewAbstractLinearGradient(LinearGradientParam linearGradientParam)
{
    NG::Gradient newGradient;
    NewCjLinearGradient(linearGradientParam, newGradient);
    ViewAbstractModel::GetInstance()->SetLinearGradient(newGradient);
}

static void NewCjSweepGradient(SweepGradientParam sweepGradientParam, NG::Gradient& newGradient)
{
    newGradient.CreateGradientWithType(NG::GradientType::SWEEP);
    // center
    CTupleLength center = sweepGradientParam.center;
    DimensionUnit rowUnitType = static_cast<DimensionUnit>(center.rowUnitType);
    newGradient.GetSweepGradient()->centerX = CalcDimension(center.rowValue, rowUnitType);
    double hundredPercent = 100.0;
    if (static_cast<DimensionUnit>(center.rowUnitType) == DimensionUnit::PERCENT) {
        // [0,1] -> [0, 100]
        double rowValue = center.rowValue * hundredPercent;
        newGradient.GetSweepGradient()->centerX = CalcDimension(rowValue, DimensionUnit::PERCENT);
    }
    DimensionUnit columnUnitType = static_cast<DimensionUnit>(center.columnUnitType);
    newGradient.GetSweepGradient()->centerY = CalcDimension(center.columnValue, columnUnitType);
    if (static_cast<DimensionUnit>(center.columnUnitType) == DimensionUnit::PERCENT) {
        // [0,1] -> [0, 100]
        double columnValue = center.columnValue * hundredPercent;
        newGradient.GetSweepGradient()->centerY = CalcDimension(columnValue, DimensionUnit::PERCENT);
    }
    // start
    double start = sweepGradientParam.start;
    newGradient.GetSweepGradient()->startAngle = CalcDimension(start, DimensionUnit::PX);
    // end
    double end = sweepGradientParam.end;
    newGradient.GetSweepGradient()->endAngle = CalcDimension(end, DimensionUnit::PX);
    // rotation
    double rotation = sweepGradientParam.rotation;
    newGradient.GetSweepGradient()->rotation = CalcDimension(rotation, DimensionUnit::PX);
    // repeating
    newGradient.SetRepeat(sweepGradientParam.repeating);
    // color stops
    NewGetCjGradientColorStops(newGradient, sweepGradientParam.colors);
}

void FfiOHOSAceFrameworkViewAbstractSweepGradient(SweepGradientParam sweepGradientParam)
{
    NG::Gradient newGradient;
    NewCjSweepGradient(sweepGradientParam, newGradient);
    ViewAbstractModel::GetInstance()->SetSweepGradient(newGradient);
}

static void NewCjRadialGradient(RadialGradientParam radialGradientParam, NG::Gradient& newGradient)
{
    newGradient.CreateGradientWithType(NG::GradientType::RADIAL);
    // center
    CTupleLength center = radialGradientParam.center;
    DimensionUnit rowUnitType = static_cast<DimensionUnit>(center.rowUnitType);
    newGradient.GetRadialGradient()->radialCenterX = CalcDimension(center.rowValue, rowUnitType);
    double hundredPercent = 100.0;
    if (static_cast<DimensionUnit>(center.rowUnitType) == DimensionUnit::PERCENT) {
        // [0,1] -> [0, 100]
        double rowValue = center.rowValue * hundredPercent;
        newGradient.GetRadialGradient()->radialCenterX = CalcDimension(rowValue, DimensionUnit::PERCENT);
    }

    DimensionUnit columnUnitType = static_cast<DimensionUnit>(center.columnUnitType);
    newGradient.GetRadialGradient()->radialCenterY = CalcDimension(center.columnValue, columnUnitType);
    if (static_cast<DimensionUnit>(center.columnUnitType) == DimensionUnit::PERCENT) {
        // [0,1] -> [0, 100]
        double columnValue = center.columnValue * hundredPercent;
        newGradient.GetRadialGradient()->radialCenterY = CalcDimension(columnValue, DimensionUnit::PERCENT);
    }
    // radius
    newGradient.GetRadialGradient()->radialVerticalSize =
        Dimension(radialGradientParam.radius, static_cast<DimensionUnit>(radialGradientParam.radiusUnit));
    newGradient.GetRadialGradient()->radialHorizontalSize =
        Dimension(radialGradientParam.radius, static_cast<DimensionUnit>(radialGradientParam.radiusUnit));
    // repeating
    newGradient.SetRepeat(radialGradientParam.repeating);
    // color stops
    NewGetCjGradientColorStops(newGradient, radialGradientParam.colors);
}

void FfiOHOSAceFrameworkViewAbstractRadialGradient(RadialGradientParam radialGradientParam)
{
    NG::Gradient newGradient;
    NewCjRadialGradient(radialGradientParam, newGradient);
    ViewAbstractModel::GetInstance()->SetRadialGradient(newGradient);
}

void FfiOHOSAceFrameworkViewAbstractRenderFit(int32_t fitMode)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(fitMode, RENDERFITS.size())) {
        LOGE("invalid value for fitMode");
        return;
    }
    ViewAbstractModel::GetInstance()->SetRenderFit(RENDERFITS[fitMode]);
}

void FfiOHOSAceFrameworkViewAbstractSetInspectorKey(const char* key)
{
    ViewAbstractModel::GetInstance()->SetInspectorId(key);
}

void FfiOHOSAceFrameworkViewAbstractSetId(const char* id)
{
    ViewAbstractModel::GetInstance()->SetInspectorId(id);
}

VectorNativeRectangleHandle FFICJCreateVectorNativeRectangle(int64_t size)
{
    LOGE("Create NativeRectangle Vector");
    return new std::vector<NativeRectangle>(size);
}

void FFICJVectorNativeRectangleDelete(VectorNativeRectangleHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeRectangle>*>(vec);
    delete actualVec;
}

void FFICJVectorNativeRectangleSetElement(VectorNativeRectangleHandle vec, int64_t index, NativeRectangle rect)
{
    LOGE("NativeRectangle Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeRectangle>*>(vec);
    (*actualVec)[index] = rect;
    LOGE("NativeRectangle Vector Set Element Success");
}

ExternalString FFIOHOSAceFrameworkGetResourceStr(int64_t id, uint32_t type, const char* param)
{
    std::string result;
    if (!ParseCjString(id, static_cast<ResourceType>(type), param, result)) {
        LOGE("Parse String Failed.");
    }
    return ::Utils::MallocCString(result);
}

ExternalString FFIOHOSAceFrameworkGetResourcePluralStr(int64_t id, uint32_t type, int64_t count, const char* plural)
{
    std::string result;
    if (!ParseCjString(id, static_cast<ResourceType>(type), count, plural, result)) {
        LOGE("Parse String Failed.");
    }
    return ::Utils::MallocCString(result);
}

RetDimension FFIOHOSAceFrameworkGetResourceDimension(int64_t id)
{
    Dimension result;
    RetDimension ret = { .value = 0.0, .unit = 0 };
    if (!ParseCjDimension(id, result)) {
        LOGE("Parse Dimension Failed.");
    }
    ret.value = result.Value();
    ret.unit = static_cast<int32_t>(result.Unit());
    return ret;
}

uint32_t FFIOHOSAceFrameworkGetResourceColor(int64_t id)
{
    Color color;
    uint32_t result;
    if (!ParseColorById(id, color)) {
        LOGE("Parse Color Failed.");
    }
    result = color.GetValue();
    return result;
}

ExternalString FFIOHOSAceFrameworkGetResourceMedia(int64_t id, uint32_t type, const char* param)
{
    std::string result;
    if (!ParseCjMedia(id, static_cast<ResourceType>(type), param, result)) {
        LOGE("Parse Media Failed.");
    }
    return ::Utils::MallocCString(result);
}

void FfiOHOSAceFrameworkViewAbstractExpandSafeArea(uint32_t types, uint32_t edges)
{
    NG::SafeAreaExpandOpts opts { .type = types, .edges = edges };
    ViewAbstractModel::GetInstance()->UpdateSafeAreaExpandOpts(opts);
}

void ParseSheetCallback(CJSheetOptions options, std::function<void()>& onAppear, std::function<void()>& onDisappear,
    std::function<void()>& shouldDismiss, std::function<void()>& onWillAppear, std::function<void()>& onWillDisappear)
{
    if (options.onAppear.hasValue) {
        onAppear = CJLambda::Create(options.onAppear.value);
    }
    if (options.onDisappear.hasValue) {
        onDisappear = CJLambda::Create(options.onDisappear.value);
    }
    if (options.shouldDismiss.hasValue) {
        shouldDismiss = CJLambda::Create(options.shouldDismiss.value);
    }
    if (options.onWillAppear.hasValue) {
        onWillAppear = CJLambda::Create(options.onWillAppear.value);
    }
    if (options.onWillDisappear.hasValue) {
        onWillDisappear = CJLambda::Create(options.onWillDisappear.value);
    }
}

void ParseSheetDetentHeight(const int args, NG::SheetHeight& detent)
{
    if (args == SHEET_HEIGHT_MEDIUM) {
        detent.sheetMode = NG::SheetMode::MEDIUM;
        detent.height.reset();
        return;
    }
    if (args == SHEET_HEIGHT_LARGE) {
        detent.sheetMode = NG::SheetMode::LARGE;
        detent.height.reset();
        return;
    }
    if (args == SHEET_HEIGHT_FITCONTENT) {
        detent.sheetMode = NG::SheetMode::AUTO;
        detent.height.reset();
        return;
    }
}

bool ParseSheetDetents(const CArrInt32 array, std::vector<NG::SheetHeight>& sheetDetents)
{
    int* intArr = static_cast<int*>(array.head);
    std::vector<int> intVec(intArr, intArr + array.size);
    NG::SheetHeight sheetDetent;
    for (size_t i = 0; i < intVec.size(); i++) {
        ParseSheetDetentHeight(intVec[i], sheetDetent);
        if ((!sheetDetent.height.has_value()) && (!sheetDetent.sheetMode.has_value())) {
            continue;
        }
        sheetDetents.emplace_back(sheetDetent);
        sheetDetent.height.reset();
        sheetDetent.sheetMode.reset();
    }
    return true;
}

void ParseSheetStyle(CJSheetOptions option, NG::SheetStyle& sheetStyle)
{
    std::vector<NG::SheetHeight> detents;
    if (option.detents.hasValue && ParseSheetDetents(option.detents.value, detents)) {
        sheetStyle.detents = detents;
    }
    if (option.blurStyle.hasValue) {
        BlurStyleOption styleOption;
        int32_t blurStyle = option.blurStyle.value;
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
            sheetStyle.backgroundBlurStyle = styleOption;
        }
    }
    if (option.showClose.hasValue) {
        sheetStyle.showCloseIcon = option.showClose.value;
    }
    if (option.dragBarl.hasValue) {
        sheetStyle.showDragBar = option.dragBarl.value;
    } else {
        sheetStyle.showDragBar = true;
    }
    if (option.enableOutsideInteractive.hasValue) {
        sheetStyle.interactive = option.enableOutsideInteractive.value;
    }
    if (option.enableOutsideInteractive.hasValue) {
        sheetStyle.interactive = option.enableOutsideInteractive.value;
    }
    if (option.preferType.hasValue) {
        auto sheetType = option.preferType.value;
        if (sheetType >= static_cast<int>(NG::SheetType::SHEET_BOTTOM) &&
            sheetType <= static_cast<int>(NG::SheetType::SHEET_POPUP)) {
            sheetStyle.sheetType = static_cast<NG::SheetType>(sheetType);
        }
    }
    if (option.backgroundColor.hasValue) {
        sheetStyle.backgroundColor = Color(ColorAlphaAdapt(option.backgroundColor.value));
    }
    if (option.maskColor.hasValue) {
        sheetStyle.maskColor = Color(ColorAlphaAdapt(option.maskColor.value));
    }
    NG::SheetHeight sheetDetent;
    if (option.height.hasValue) {
        ParseSheetDetentHeight(option.height.value, sheetDetent);
        sheetStyle.sheetMode = sheetDetent.sheetMode;
        sheetStyle.height = sheetDetent.height;
    }
}

void ParseSheetTitle(CJSheetOptions option, NG::SheetStyle& sheetStyle, std::function<void()>& titleBuilderFunction)
{
    sheetStyle.isTitleBuilder = true;
    titleBuilderFunction = option.title.hasValue ? CJLambda::Create(option.title.value) : ([]() -> void {});
}
void FfiOHOSAceFrameworkViewAbstractbindSheetParam(bool isShow, void (*builder)(), CJSheetOptions option)
{
    auto buildFunc = CJLambda::Create(builder);
    NG::SheetStyle sheetStyle;
    DoubleBindCallback callback = nullptr;
    sheetStyle.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    std::function<void()> onAppearCallback;
    std::function<void()> onDisappearCallback;
    std::function<void()> onWillAppearCallback;
    std::function<void()> onWillDisappearCallback;
    std::function<void()> shouldDismissFunc;
    std::function<void(const int32_t)> onWillDismissCallback;
    std::function<void(const float)> onHeightDidChangeCallback;
    std::function<void(const float)> onDetentsDidChangeCallback;
    std::function<void(const float)> onWidthDidChangeCallback;
    std::function<void(const float)> onTypeDidChangeCallback;
    std::function<void()> titleBuilderFunction;
    std::function<void()> sheetSpringBackFunc;
    ParseSheetCallback(option, onAppearCallback, onDisappearCallback, shouldDismissFunc, onWillAppearCallback,
        onWillDisappearCallback);
    ParseSheetStyle(option, sheetStyle);
    ParseSheetTitle(option, sheetStyle, titleBuilderFunction);
    ViewAbstractModel::GetInstance()->BindSheet(isShow, std::move(callback), std::move(buildFunc),
        std::move(titleBuilderFunction), sheetStyle, std::move(onAppearCallback), std::move(onDisappearCallback),
        std::move(shouldDismissFunc), std::move(onWillDismissCallback), std::move(onWillAppearCallback),
        std::move(onWillDisappearCallback), std::move(onHeightDidChangeCallback), std::move(onDetentsDidChangeCallback),
        std::move(onWidthDidChangeCallback), std::move(onTypeDidChangeCallback), std::move(sheetSpringBackFunc));
    return;
}

void FFIOHOSAceFrameworkFocusable(bool isFocusable)
{
    ViewAbstractModel::GetInstance()->SetFocusable(isFocusable);
}

void FFIOHOSAceFrameworkTabIndex(int32_t index)
{
    ViewAbstractModel::GetInstance()->SetTabIndex(index);
}

void FFIOHOSAceFrameworkDefaultFocus(bool isDefaultFocus)
{
    ViewAbstractModel::GetInstance()->SetDefaultFocus(isDefaultFocus);
}

void FFIOHOSAceFrameworkGroupDefaultFocus(bool isGroupDefaultFocus)
{
    ViewAbstractModel::GetInstance()->SetGroupDefaultFocus(isGroupDefaultFocus);
}

void FFIOHOSAceFrameworkFocusOnTouch(bool isFocusOnTouch)
{
    ViewAbstractModel::GetInstance()->SetFocusOnTouch(isFocusOnTouch);
}
bool FFIOHOSAceFrameworkRequestFocus(const char* inspectorKey)
{
    bool result = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        LOGE("pipeline context is non-valid");
        return result;
    }
    if (!pipelineContext->GetTaskExecutor()) {
        LOGE("TaskExecutor is non-valid");
        return result;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI, "ArkUICjRequestFocus");
    return result;
}

void FFIOHOSAceFrameworkFocusBox(CJFocusBoxStyle cjStyle)
{
    NG::FocusBoxStyle style;

    if (cjStyle.hasMargin) {
        CalcDimension margin(cjStyle.margin, static_cast<DimensionUnit>(cjStyle.marginUnit));
        style.margin = margin;
    }

    if (cjStyle.hasStrokeColor) {
        style.strokeColor = Color(cjStyle.strokeColor);
    }

    if (cjStyle.hasStrokeWidth && GreatOrEqual(cjStyle.strokeWidth, 0.0f)) {
        CalcDimension strokeWidth(cjStyle.strokeWidth, static_cast<DimensionUnit>(cjStyle.strokeWidthUnit));
        style.strokeWidth = strokeWidth;
    }

    ViewAbstractModel::GetInstance()->SetFocusBoxStyle(style);
}

void FFIOHOSAceFrameworkFocusScopePriority(const char* scopeId, int32_t priority)
{
    ViewAbstractModel::GetInstance()->SetFocusScopePriority(scopeId, priority);
}

void FFIOHOSAceFrameworkFocusScopeId(const char* id, bool isGroup, bool arrowStepOut)
{
    ViewAbstractModel::GetInstance()->SetFocusScopeId(id, isGroup, arrowStepOut);
}

uint32_t FFIOHOSAceFrameworkBlendColor(uint32_t color, uint32_t overlayColor)
{
    return Color(color).BlendColor(Color(overlayColor)).GetValue();
}

void ParseModalTransition(CJContentCoverOptions options, NG::ModalStyle& modalStyle)
{
    modalStyle.modalTransition = NG::ModalTransition::DEFAULT;
    auto modalTransition = options.modalTransition;
    auto transitionNumber = static_cast<int32_t>(modalTransition);
    modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
    if (options.backgroundColor.hasValue) {
        auto backgroundColor = static_cast<uint32_t>(options.backgroundColor.value);
        modalStyle.backgroundColor = Color(backgroundColor);
    }
}

void FFIOHOSAceFrameworkBindContentCover(bool isShow, void (*builder)(), CJContentCoverOptions options)
{
    // parse builder
    auto buildFunc = CJLambda::Create(builder);

    // parse ModalTransition
    NG::ModalStyle modalStyle;
    ParseModalTransition(options, modalStyle);
    std::function<void()> onWillShowCallback;
    std::function<void()> onWillDismissCallback;
    NG::ContentCoverParam contentCoverParam;
    std::function<void(const int32_t&)> onWillDismissFunc;
    // parse callback
    std::function<void()> onShowCallback =
        options.onAppear.hasValue ? CJLambda::Create(options.onAppear.value) : ([]() -> void {});
    std::function<void()> onDismissCallback =
        options.onDisappear.hasValue ? CJLambda::Create(options.onDisappear.value) : ([]() -> void {});

    ViewAbstractModel::GetInstance()->BindContentCover(isShow, nullptr, std::move(buildFunc), modalStyle,
        std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
        std::move(onWillDismissCallback), contentCoverParam);
}

ExternalString FFIGetResourceString(NativeResourceObject obj)
{
    std::string result;
    if (!ViewAbstract::ParseCjString(obj, result)) {
        LOGE("Parse string failed.");
    }
    return ::Utils::MallocCString(result);
}

ExternalString FFIGetResourceMedia(NativeResourceObject obj)
{
    std::string result;
    if (!ViewAbstract::ParseCjMedia(obj, result)) {
        LOGE("Parse media failed.");
    }
    return ::Utils::MallocCString(result);
}

uint32_t FFIGetResourceSymbolId(NativeResourceObject obj)
{
    uint32_t symbolId;
    if (!ViewAbstract::ParseCjSymbolId(obj, symbolId)) {
        LOGE("Parse symbol id failed.");
    }
    return symbolId;
}

uint32_t FFIGetResourceColor(NativeResourceObject obj)
{
    Color color;
    if (!ViewAbstract::ParseCjColor(obj, color)) {
        LOGE("Parse color failed.");
    }
    return color.GetValue();
}

RetDimension FFIGetResourceDimension(NativeResourceObject obj)
{
    CalcDimension result;
    RetDimension ret = { .value = 0.0, .unit = 0 };
    if (!ViewAbstract::ParseCjDimension(obj, result, DimensionUnit::VP)) {
        LOGE("Parse dimension failed.");
    }
    ret.value = result.Value();
    ret.unit = static_cast<int32_t>(result.Unit());
    return ret;
}

double FFIGetResourceDouble(NativeResourceObject obj)
{
    double result;
    if (!ViewAbstract::ParseCjDouble(obj, result)) {
        LOGE("Parse double failed.");
    }
    return result;
}

int32_t FFIGetResourceInt32(NativeResourceObject obj)
{
    int32_t result;
    if (!ViewAbstract::ParseCjInteger(obj, result)) {
        LOGE("Parse int32 failed.");
    }
    return result;
}

uint32_t FFIGetResourceUInt32(NativeResourceObject obj)
{
    uint32_t result;
    if (!ViewAbstract::ParseCjInteger(obj, result)) {
        LOGE("Parse uint32 failed.");
    }
    return result;
}

bool FFIGetResourceBool(NativeResourceObject obj)
{
    bool result;
    if (!ViewAbstract::ParseCjBool(obj, result)) {
        LOGE("Parse bool failed.");
    }
    return result;
}

VectorUInt32Handle FFIGetResourceVectorUInt32(NativeResourceObject obj)
{
    auto result = new std::vector<uint32_t>;
    if (!ViewAbstract::ParseCjIntegerArray(obj, *result)) {
        LOGE("Parse uint32 array failed.");
    }
    return result;
}

VectorStringHandle FFIGetResourceVectorString(NativeResourceObject obj)
{
    auto result = new std::vector<std::string>;
    if (!ViewAbstract::ParseCjStringArray(obj, *result)) {
        LOGE("Parse string array failed.");
    }
    return result;
}
}

namespace OHOS::Ace {
bool ParseCjDimension(int64_t id, Dimension& result)
{
    auto themeConstants = ViewAbstract::GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetDimension(static_cast<uint32_t>(id));
    return true;
}

bool ParseCjMedia(int64_t id, ResourceType type, const std::string& params, std::string& result)
{
    auto themeConstants = ViewAbstract::GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    if (type == ResourceType::MEDIA) {
        result = themeConstants->GetMediaPath(static_cast<uint32_t>(id));
        return true;
    }
    if (type == ResourceType::RAWFILE) {
        if (params.empty()) {
            LOGW("param is empty");
            return false;
        }
        result = themeConstants->GetRawfile(params);
        return true;
    }
    LOGE("CJImage::Create ParseCjMedia type is wrong");
    return false;
}

bool ParseCjString(int64_t id, ResourceType type, const std::string& params, std::string& result)
{
    auto themeConstants = ViewAbstract::GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type == ResourceType::STRING) {
        auto originStr = themeConstants->GetString(static_cast<uint32_t>(id));
        ReplaceHolder(originStr, params);
        result = originStr;
    } else {
        LOGE("Resource type invalid");
        return false;
    }
    return true;
}

bool ParseCjString(int64_t id, ResourceType type, int64_t count, const std::string& plural, std::string& result)
{
    auto themeConstants = ViewAbstract::GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type == ResourceType::PLURAL) {
        auto pluralStr = themeConstants->GetPluralString(static_cast<uint32_t>(id), count);
        ReplaceHolder(pluralStr, plural);
        result = pluralStr;
    } else {
        LOGE("Resource type invalid");
        return false;
    }
    return true;
}

bool ParseColorById(int64_t id, Color& color)
{
    auto themeConstants = ViewAbstract::GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    color = themeConstants->GetColor(static_cast<uint32_t>(id));
    return true;
}

void ParseCJResponseRegion(CJResponseRegion value, std::vector<DimensionRect>& result)
{
    Dimension xDime(value.x, static_cast<DimensionUnit>(value.xUnit));
    Dimension yDime(value.y, static_cast<DimensionUnit>(value.yUnit));
    Dimension widthDime(value.width, static_cast<DimensionUnit>(value.widthUnit));
    Dimension heightDime(value.height, static_cast<DimensionUnit>(value.heightUnit));
    DimensionOffset offsetDimen(xDime, yDime);
    DimensionRect dimenRect(widthDime, heightDime, offsetDimen);
    result.emplace_back(dimenRect);
}

void ParseVectorStringPtr(VectorStringPtr vecContent, std::vector<DimensionRect>& result)
{
    auto nativeRectangleVec = *reinterpret_cast<std::vector<NativeRectangle>*>(vecContent);
    for (size_t i = 0; i < nativeRectangleVec.size(); i++) {
        Dimension xDimen = Dimension(nativeRectangleVec[i].x, static_cast<DimensionUnit>(nativeRectangleVec[i].xUnit));
        Dimension yDimen = Dimension(nativeRectangleVec[i].y, static_cast<DimensionUnit>(nativeRectangleVec[i].yUnit));
        Dimension widthDimen =
            Dimension(nativeRectangleVec[i].width, static_cast<DimensionUnit>(nativeRectangleVec[i].widthUnit));
        Dimension heightDimen =
            Dimension(nativeRectangleVec[i].height, static_cast<DimensionUnit>(nativeRectangleVec[i].heightUnit));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        result.emplace_back(dimenRect);
    }
}

} // namespace OHOS::Ace
