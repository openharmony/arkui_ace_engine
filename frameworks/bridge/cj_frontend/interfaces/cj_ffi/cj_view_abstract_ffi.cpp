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
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_progressmask_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/matrix4/cj_matrix4_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "pixel_map_impl.h"
#include "core/components/common/properties/border_image.h"

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
constexpr Dimension ARROW_ZERO_PERCENT_VALUE = 0.0_pct;
constexpr Dimension ARROW_HALF_PERCENT_VALUE = 0.5_pct;
constexpr Dimension ARROW_FULL_PERCENT_VALUE = 1.0_pct;
constexpr float DEFAULT_SCALE_LIGHT = 0.9f;
constexpr float DEFAULT_SCALE_MIDDLE_OR_HEAVY = 0.95f;

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
const std::vector<FontStyle> FONT_STYLES = {FontStyle::NORMAL, FontStyle::ITALIC};
const std::vector<BackgroundImageSizeType> IMAGE_SIZES = { BackgroundImageSizeType::CONTAIN,
    BackgroundImageSizeType::COVER, BackgroundImageSizeType::AUTO, BackgroundImageSizeType::FILL };
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

const std::vector<PixelRoundCalcPolicy> PIXEL_ROUND_CALC_POLICIES = { PixelRoundCalcPolicy::NO_FORCE_ROUND,
    PixelRoundCalcPolicy::FORCE_CEIL, PixelRoundCalcPolicy::FORCE_FLOOR };

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

void SetPopupParams(CJBindPopupParams bindPopupParams, const RefPtr<PopupParam>& popupParam)
{
    popupParam->SetMessage(bindPopupParams.message);
    popupParam->SetPlacement(bindPopupParams.placementOnTop ? Placement::TOP : Placement::BOTTOM);
    popupParam->SetPlacement(static_cast<Placement>(bindPopupParams.placement));
    popupParam->SetShowInSubWindow(bindPopupParams.showInSubWindow);
    popupParam->SetTextColor(Color(bindPopupParams.textColor));
    popupParam->SetFontWeight(ConvertStrToFontWeight(bindPopupParams.fontWeight));
    CalcDimension fontSizeDim(bindPopupParams.fontSize, static_cast<DimensionUnit>(bindPopupParams.fontSizeUnit));
    popupParam->SetFontSize(fontSizeDim);
    if (bindPopupParams.fontStyle < 0 ||  bindPopupParams.fontStyle > static_cast<int32_t>(FONT_STYLES.size())) {
        return;
    }
    popupParam->SetFontStyle(FONT_STYLES[bindPopupParams.fontStyle]);
    CalcDimension targetSpaceDim(bindPopupParams.targetSpace,
        static_cast<DimensionUnit>(bindPopupParams.targetSpaceUnit));
    CalcDimension arrowOffsetDim(bindPopupParams.arrowOffset,
        static_cast<DimensionUnit>(bindPopupParams.arrowOffsetUnit));
    CalcDimension widthDim(bindPopupParams.width, static_cast<DimensionUnit>(bindPopupParams.widthUnit));
    CalcDimension arrowWidthDim(bindPopupParams.arrowWidth, static_cast<DimensionUnit>(bindPopupParams.arrowWidthUnit));
    CalcDimension arrowHeightDim(bindPopupParams.arrowHeight,
        static_cast<DimensionUnit>(bindPopupParams.arrowHeightUnit));
    CalcDimension radiusDim(bindPopupParams.radius, static_cast<DimensionUnit>(bindPopupParams.radiusUnit));
    Offset offset(bindPopupParams.offsetX, bindPopupParams.offsetY);
    popupParam->SetArrowOffset(arrowOffsetDim);
    popupParam->SetTargetSpace(targetSpaceDim);
    popupParam->SetBackgroundColor(Color(bindPopupParams.popupColor));
    popupParam->SetMaskColor(Color(bindPopupParams.mask));
    popupParam->SetHasAction(!bindPopupParams.autoCancel);
    if (bindPopupParams.width > 0) {
        popupParam->SetChildWidth(widthDim);
    }
    if (bindPopupParams.radius > 0) {
        popupParam->SetRadius(radiusDim);
    }
    popupParam->SetArrowWidth(arrowWidthDim);
    popupParam->SetArrowHeight(arrowHeightDim);
    popupParam->SetShadow(Shadow::CreateShadow(static_cast<ShadowStyle>(bindPopupParams.shadow)));
    popupParam->SetTargetOffset(offset);
    popupParam->SetFollowTransformOfTarget(bindPopupParams.followTransformOfTarget);
    if (std::strcmp(bindPopupParams.arrowPointPosition, "Start") == 0) {
        popupParam->SetArrowOffset(ARROW_ZERO_PERCENT_VALUE);
    }
    if (std::strcmp(bindPopupParams.arrowPointPosition, "Center") == 0) {
        popupParam->SetArrowOffset(ARROW_HALF_PERCENT_VALUE);
    }
    if (std::strcmp(bindPopupParams.arrowPointPosition, "End") == 0) {
        popupParam->SetArrowOffset(ARROW_FULL_PERCENT_VALUE);
    }
}

void DealBindPopupParams(bool isShow, const CJBindPopupParams& bindPopupParams,
    const std::function<void(bool)>& onStateChangeFunc, const std::function<void()>& primaryActionFunc,
    const std::function<void()>& secondaryActionFunc)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(isShow);
    SetPopupParams(bindPopupParams, popupParam);
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };
    popupParam->SetOnStateChange(onStateChangeCallback);
    if (bindPopupParams.onWillDismiss.hasValue) {
        std::function<void(const int32_t& info)> onWillDismissFunc =
            [nativeFunc = CJLambda::Create(bindPopupParams.onWillDismiss.value)]
            (const int32_t& info) {nativeFunc(info);};
        popupParam->SetOnWillDismiss(onWillDismissFunc);
    }
    if (bindPopupParams.transition.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(bindPopupParams.transition.value);
        if (nativeTransitionEffect) {
            popupParam->SetHasTransition(true);
            popupParam->SetTransitionEffects(nativeTransitionEffect->effect);
        }
    }
    if (bindPopupParams.backgroundBlurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
        bindPopupParams.backgroundBlurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        popupParam->SetBlurStyle(static_cast<BlurStyle>(bindPopupParams.backgroundBlurStyle));
    }
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

namespace OHOS::Ace::Framework {

RefPtr<PipelineBase> GetPipelineContext()
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, nullptr);
    return currentObj->GetPipelineContext();
}

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkPopupDismiss()
{
#ifndef ARKUI_WEARABLE
    ViewAbstractModel::GetInstance()->DismissDialog();
#endif
}

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

void FfiOHOSAceFrameworkViewAbstractSetPixelRound(CJPixelRoundPolicy cjValue)
{
    uint16_t value = 0;
    int32_t startValue = cjValue.start;
    if (Utils::CheckParamsValid(startValue, PIXEL_ROUND_CALC_POLICIES.size())) {
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START);
        }
    }


    int32_t topValue = cjValue.top;
    if (Utils::CheckParamsValid(topValue, PIXEL_ROUND_CALC_POLICIES.size())) {
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP);
        }
    }

    int32_t endValue = cjValue.end;
    if (Utils::CheckParamsValid(endValue, PIXEL_ROUND_CALC_POLICIES.size())) {
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END);
        }
    }

    int32_t bottomValue = cjValue.bottom;
    if (Utils::CheckParamsValid(bottomValue, PIXEL_ROUND_CALC_POLICIES.size())) {
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);
        }
    }

    ViewAbstractModel::GetInstance()->SetPixelRound(value);
}

void FfiOHOSAceFrameworkViewAbstractSetMotionBlur(CJMotionBlurOptions value)
{
    MotionBlurOption option;
    double radius = value.radius;
    double x = value.anchor.x;
    double y = value.anchor.y;
    if (radius < 0.0) {
        radius = 0.0;
    }
    if (x < 0.0) {
        x = 0.0;
    }
    if (y < 0.0) {
        y = 0.0;
    }
    option.radius = radius;
    option.anchor.x = std::clamp(x, 0.0, 1.0);
    option.anchor.y = std::clamp(y, 0.0, 1.0);
    ViewAbstractModel::GetInstance()->SetMotionBlur(option);
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

    styleOption.scale = options.scale < 0.0 || options.scale > 1.0 ? 1.0 : options.scale;
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

void FfiOHOSAceFrameworkViewAbstractTransitionWithBack(int64_t id, void (*onFinish)(bool transitionIn))
{
    auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(id);
    if (nativeTransitionEffect == nullptr) {
        return;
    }
    auto chainedEffect = nativeTransitionEffect->effect;
    auto lambda = CJLambda::Create(onFinish);
    auto finishCallback = [lambda](bool isTransitionIn) {
        lambda(isTransitionIn);
    };
    ViewAbstractModel::GetInstance()->SetChainedTransition(chainedEffect, std::move(finishCallback));
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

void FfiOHOSAceFrameworkViewAbstractSetChainMode(CJChainInfo option)
{
    ChainInfo chainInfo;
    chainInfo.direction = static_cast<LineDirection>(option.direction);
    chainInfo.style = static_cast<ChainStyle>(option.style);
    ViewAbstractModel::GetInstance()->SetChainStyle(chainInfo);
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

void FfiOHOSAceFrameworkViewAbstractSetLinearGradientBlur(
    double radius, int32_t direction, VectorFloat64Ptr blurVec, VectorFloat64Ptr positionVec)
{
    double blurRadius = radius;
    std::vector<std::pair<float, float>> fractionStops;
    const auto& blurVector = *reinterpret_cast<std::vector<double>*>(blurVec);
    const auto& positionVector = *reinterpret_cast<std::vector<double>*>(positionVec);
    if (blurVector.size() <= 1) {
        return;
    }
    float tmpPos = -1.0f;
    for (size_t i = 0; i < blurVector.size(); i++) {
        std::pair<float, float> fractionStop;
        fractionStop.first = static_cast<float>(std::clamp(blurVector[i], 0.0, 1.0));
        fractionStop.second = static_cast<float>(std::clamp(positionVector[i], 0.0, 1.0));
        if (fractionStop.second <= tmpPos) {
            fractionStops.clear();
            return;
        }
        tmpPos = fractionStop.second;
        fractionStops.push_back(fractionStop);
    }
    // Parse direction
    CalcDimension dimensionRadius(static_cast<float>(blurRadius), DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, static_cast<NG::GradientDirection>(direction));
    ViewAbstractModel::GetInstance()->SetLinearGradientBlur(blurPara);
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

void FfiOHOSAceFrameworkViewAbstractSetInvertWithOptions(
    double low, double high, double threshold, double thresholdRange)
{
    InvertVariant invert = 0.0f;
    InvertOption option;
    option.low_ = std::clamp(low, 0.0, 1.0);
    option.high_ = std::clamp(high, 0.0, 1.0);
    option.threshold_ = std::clamp(threshold, 0.0, 1.0);
    option.thresholdRange_ = std::clamp(thresholdRange, 0.0, 1.0);
    invert = option;
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

void FfiOHOSAceFrameworkViewAbstractSetBlendMode(int32_t value, int32_t type)
{
    BlendMode blendMode = BlendMode::NONE;
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    // for backward compatible, we temporary add a magic number to trigger offscreen, will remove soon
    constexpr int backwardCompatMagicNumberOffscreen = 1000;
    constexpr int backwardCompatSourceInNumberOffscreen = 2000;
    constexpr int backwardCompatDestinationInNumberOffscreen = 3000;
    constexpr int backwardCompatMagicNumberSrcIn = 5000;

    if (value >= 0 && value < static_cast<int>(BlendMode::MAX)) {
        blendMode = static_cast<BlendMode>(value);
    } else if (value == backwardCompatMagicNumberOffscreen) {
        // backward compatibility code, will remove soon
        blendMode = BlendMode::SRC_OVER;
        blendApplyType = BlendApplyType::OFFSCREEN;
    } else if (value == backwardCompatSourceInNumberOffscreen) {
        // backward compatibility code, will remove soon
        blendMode = BlendMode::SRC_IN;
        blendApplyType = BlendApplyType::OFFSCREEN;
    } else if (value == backwardCompatDestinationInNumberOffscreen) {
        // backward compatibility code, will remove soon
        blendMode = BlendMode::DST_IN;
        blendApplyType = BlendApplyType::OFFSCREEN;
    } else if (value == backwardCompatMagicNumberSrcIn) {
        blendMode = BlendMode::BACK_COMPAT_SOURCE_IN;
    }
    blendApplyType = static_cast<BlendApplyType>(type);

    ViewAbstractModel::GetInstance()->SetBlendMode(blendMode);
    ViewAbstractModel::GetInstance()->SetBlendApplyType(blendApplyType);
}

void FfiOHOSAceFrameworkViewAbstractSetUseShadowBatching(bool value)
{
    ViewAbstractModel::GetInstance()->SetUseShadowBatching(value);
}

void FfiOHOSAceFrameworkViewAbstractSetSphericalEffect(double value)
{
    ViewAbstractModel::GetInstance()->SetSphericalEffect(std::clamp(value, 0.0, 1.0));
}

void FfiOHOSAceFrameworkViewAbstractSetLightUpEffect(double value)
{
    ViewAbstractModel::GetInstance()->SetLightUpEffect(std::clamp(value, 0.0, 1.0));
}

void FfiOHOSAceFrameworkViewAbstractSetPixelStretchEffect(CJEdge params)
{
    Dimension top(params.top, static_cast<DimensionUnit>(params.topUnit));
    Dimension right(params.right, static_cast<DimensionUnit>(params.rightUnit));
    Dimension bottom(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    Dimension left(params.left, static_cast<DimensionUnit>(params.leftUnit));

    PixStretchEffectOption option;
    if ((left.IsNonNegative() && top.IsNonNegative() && right.IsNonNegative() && bottom.IsNonNegative()) ||
        (left.IsNonPositive() && top.IsNonPositive() && right.IsNonPositive() && bottom.IsNonPositive())) {
        option.top = top;
        option.right = right;
        option.bottom = bottom;
        option.left = left;
    } else {
        option.ResetValue();
    }
    ViewAbstractModel::GetInstance()->SetPixelStretchEffect(option);
}

void FfiOHOSAceFrameworkViewAbstractSetSystemBarEffect()
{
    ViewAbstractModel::GetInstance()->SetSystemBarEffect(true);
}

void FfiOHOSAceFrameworkViewAbstractSetFreeze(bool value)
{
    ViewAbstractModel::GetInstance()->SetFreeze(value);
}

void FfiOHOSAceFrameworkViewAbstractSetRenderGroup(bool value)
{
    ViewAbstractModel::GetInstance()->SetRenderGroup(value);
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineStyle(int32_t style)
{
    ViewAbstractModel::GetInstance()->SetOuterBorderStyle(BORDER_STYLES[style]);
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineStyles(
    int32_t styleTop, int32_t styleRight, int32_t styleBottom, int32_t styleLeft)
{
    ViewAbstractModel::GetInstance()->SetOuterBorderStyle(
        BORDER_STYLES[styleLeft], BORDER_STYLES[styleRight], BORDER_STYLES[styleTop], BORDER_STYLES[styleBottom]);
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    CalcDimension outlineWidth = CalcDimension(value);
    if (!outlineWidth.IsNegative() && outlineWidth.Unit() != DimensionUnit::PERCENT) {
        ViewAbstractModel::GetInstance()->SetOuterBorderWidth(value);
    }
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineWidths(CJEdge params)
{
    Dimension topDimen(params.top, static_cast<DimensionUnit>(params.topUnit));
    CalcDimension top = CalcDimension(topDimen);
    if (top.IsNegative() || top.Unit() == DimensionUnit::PERCENT) {
        topDimen = Dimension(0);
    }
    Dimension rightDimen(params.right, static_cast<DimensionUnit>(params.rightUnit));
    CalcDimension right = CalcDimension(rightDimen);
    if (right.IsNegative() || right.Unit() == DimensionUnit::PERCENT) {
        rightDimen = Dimension(0);
    }
    Dimension bottomDimen(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    CalcDimension bottom = CalcDimension(bottomDimen);
    if (bottom.IsNegative() || bottom.Unit() == DimensionUnit::PERCENT) {
        bottomDimen = Dimension(0);
    }
    Dimension leftDimen(params.left, static_cast<DimensionUnit>(params.leftUnit));
    CalcDimension left = CalcDimension(leftDimen);
    if (left.IsNegative() || left.Unit() == DimensionUnit::PERCENT) {
        leftDimen = Dimension(0);
    }
    ViewAbstractModel::GetInstance()->SetOuterBorderWidth(leftDimen, rightDimen, topDimen, bottomDimen);
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineColor(uint32_t value)
{
    ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color(value));
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineColors(
    uint32_t colorTop, uint32_t colorRight, uint32_t colorBottom, uint32_t colorLeft)
{
    ViewAbstractModel::GetInstance()->SetOuterBorderColor(
        Color(colorLeft), Color(colorRight), Color(colorTop), Color(colorBottom));
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineRadius(double radius, int32_t unit)
{
    Dimension value(radius, static_cast<DimensionUnit>(unit));
    CalcDimension outlineRadius = CalcDimension(value);
    if (outlineRadius.Unit() != DimensionUnit::PERCENT) {
        ViewAbstractModel::GetInstance()->SetOuterBorderRadius(value);
    }
}

void FfiOHOSAceFrameworkViewAbstractSetOutlineRadiuses(CJOutlineRadius params)
{
    CalcDimension topLeft(params.topLeft, static_cast<DimensionUnit>(params.topLeftUnit));
    CalcDimension topRight(params.topRight, static_cast<DimensionUnit>(params.topRightUnit));
    CalcDimension bottomLeft(params.bottomLeft, static_cast<DimensionUnit>(params.bottomLeftUnit));
    CalcDimension bottomRight(params.bottomRight, static_cast<DimensionUnit>(params.bottomRightUnit));
    ViewAbstractModel::GetInstance()->SetOuterBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
}

void FfiOHOSAceFrameworkViewAbstractSetOutline(CJOutline params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension radiusDime(params.radius, static_cast<DimensionUnit>(params.radiusUnit));
    if (!Utils::CheckParamsValid(params.style, BORDER_STYLES.size())) {
        LOGE("invalid value for outline style");
        return;
    }

    ViewAbstractModel::GetInstance()->SetOuterBorderStyle(BORDER_STYLES[params.style]);
    ViewAbstractModel::GetInstance()->SetOuterBorderWidth(widthDime);
    ViewAbstractModel::GetInstance()->SetOuterBorderColor(Color(params.color));
    ViewAbstractModel::GetInstance()->SetOuterBorderRadius(radiusDime);
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

void FfiOHOSAceFrameworkViewAbstractSetBackground(void (*builder)(), int32_t align)
{
    auto buildFunc = CJLambda::Create(builder);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto buildCallback = [func = std::move(buildFunc), node = frameNode]() {
        ACE_SCORING_EVENT("BindBackground");
        PipelineContext::SetCallBackNode(node);
        func();
    };

    if (!Utils::CheckParamsValid(align, ALIGNMENT_LIST.size())) {
        LOGE("set align error, invalid value for alignment");
        return;
    }

    Alignment alignmentValue = ALIGNMENT_LIST[align];
    ViewAbstractModel::GetInstance()->BindBackground(std::move(buildCallback), alignmentValue);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundBlurStyleOption(
    int32_t blurStyle, CJBackgroundBlurStyleOptions options)
{
    BlurStyleOption styleOption;

    // Set blur style
    if (blurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }

    // Set color mode
    auto colorMode = options.colorMode;
    if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
        colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
        styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
    }

    // Set adaptive color
    auto adaptiveColor = options.adaptiveColor;
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    // Set policy
    auto policy = options.policy;
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        styleOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // Set inactive color
    styleOption.inactiveColor = Color(options.inactiveColor);
    styleOption.isValidColor = true;

    // Set scale
    styleOption.scale = std::clamp(options.scale, 0.0f, 1.0f);

    BlurOption blurOption;
    int vectorSize = 2;
    std::vector<float> greyVec(vectorSize);
    greyVec[0] = options.blurOptions.grayscale[0];
    greyVec[1] = options.blurOptions.grayscale[1];
    blurOption.grayscale = greyVec;
    styleOption.blurOption = blurOption;
    ViewAbstractModel::GetInstance()->SetBackgroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundBlurStyle(int32_t blurStyle)
{
    BlurStyleOption styleOption;

    // Set blur style
    if (blurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    ViewAbstractModel::GetInstance()->SetBackgroundBlurStyle(styleOption);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundImageResizable(CJEdge slice)
{
    ImageResizableSlice sliceResult;

    Dimension leftDim(slice.left, static_cast<DimensionUnit>(slice.leftUnit));
    Dimension rightDim(slice.right, static_cast<DimensionUnit>(slice.rightUnit));
    Dimension topDim(slice.top, static_cast<DimensionUnit>(slice.topUnit));
    Dimension bottomDim(slice.bottom, static_cast<DimensionUnit>(slice.bottomUnit));

    if (LessNotEqual(leftDim.Value(), 0.0)) {
        leftDim.SetValue(0.0);
    }
    if (LessNotEqual(rightDim.Value(), 0.0)) {
        rightDim.SetValue(0.0);
    }
    if (LessNotEqual(topDim.Value(), 0.0)) {
        topDim.SetValue(0.0);
    }
    if (LessNotEqual(bottomDim.Value(), 0.0)) {
        bottomDim.SetValue(0.0);
    }

    sliceResult.left = leftDim;
    sliceResult.right = rightDim;
    sliceResult.top = topDim;
    sliceResult.bottom = bottomDim;
    ViewAbstractModel::GetInstance()->SetBackgroundImageResizableSlice(sliceResult);
}

void FfiOHOSAceFrameworkViewAbstractSetBackgroundBrightness(double rate, double lightUpDegree)
{
    if (rate < 0.0) {
        rate = 0.0;
    }
    lightUpDegree = std::clamp(lightUpDegree, -1.0, 1.0);
    ViewAbstractModel::GetInstance()->SetDynamicLightUp(rate, lightUpDegree);
}
void FfiOHOSAceFrameworkViewAbstractSetBackgroundEffect(CJBackgroundEffectOptions value)
{
    EffectOption option;

    // Set radius
    CalcDimension radiusDimension(value.radius, DimensionUnit::VP);
    option.radius = radiusDimension;

    // Set saturation and brightness
    auto saturation = value.saturation;
    auto brightness = value.brightness;
    option.saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    option.brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;

    // Set color
    option.color = Color(value.color);

    // Set adaptive color
    auto adaptiveColor = value.adaptiveColor;
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        option.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    // Set policy
    auto policy = value.policy;
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        option.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // Set inactive color
    option.inactiveColor = Color(value.inactiveColor);
    option.isValidColor = true;

    // Set blur options
    BlurOption blurOption;
    int vectorSize = 2;
    std::vector<float> greyVec(vectorSize);
    greyVec[0] = value.blurOptions.grayscale[0];
    greyVec[1] = value.blurOptions.grayscale[1];
    blurOption.grayscale = greyVec;
    option.blurOption = blurOption;

    ViewAbstractModel::GetInstance()->SetBackgroundEffect(option);
}

void FfiOHOSAceFrameworkViewAbstractSetMaskByProgressMask(int64_t progressId)
{
    auto nativeMask = FFIData::GetData<NativeProgressMask>(progressId);
    if (nativeMask == nullptr) {
        LOGI("set mask error, Cannot get NativeProgressMask by id: %{public}" PRId64, progressId);
        return;
    }
    ViewAbstractModel::GetInstance()->SetProgressMask(nativeMask->GetProgressMask());
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

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityDescription(const char* value)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityDescription(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityText(const char* value)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityText(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityGroup(bool value)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityGroup(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityLevel(const char* value)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityImportance(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityTextHint(const char* value)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityTextHint(value);
}

void FfiOHOSAceFrameworkViewAbstractSetAccessibilityVirtualNode(void (*builder)())
{
    ViewAbstractModel::GetInstance()->SetAccessibilityVirtualNode(CJLambda::Create(builder));
}

void FfiOHOSAceFrameworkViewAbstractSetClickEffect(int32_t level, float scale)
{
    if (level < static_cast<int32_t>(ClickEffectLevel::LIGHT) ||
        level > static_cast<int32_t>(ClickEffectLevel::HEAVY)) {
        level = 0;
    }

    if (scale < 0.0 || scale > 1.0) {
        if (level == 0) {
            scale = DEFAULT_SCALE_LIGHT;
        } else {
            scale = DEFAULT_SCALE_MIDDLE_OR_HEAVY;
        }
    }
    ViewAbstractModel::GetInstance()->SetClickEffectLevel(static_cast<ClickEffectLevel>(level), scale);
}

void FfiOHOSAceFrameworkViewAbstractSetMotionPath(CJMotionPathOptions options)
{
    MotionPathOption motionPathOption;
    if (options.path != nullptr && strlen(options.path) > 0) {
        motionPathOption.SetPath(std::string(options.path));
        double from = options.from;
        double to = options.to;
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
        motionPathOption.SetRotate(options.rotatable);
    }
    ViewAbstractModel::GetInstance()->SetMotionPath(motionPathOption);
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

void SetCustomPopupParams(CJBindCustomPopup& value, const RefPtr<PopupParam>& popupParam)
{
    popupParam->SetPlacement(static_cast<Placement>(value.placement));
    popupParam->SetMaskColor(Color(value.maskColor));
    popupParam->SetBackgroundColor(Color(value.backgroundColor));
    popupParam->SetEnableArrow(value.enableArrow);
    popupParam->SetHasAction(!value.autoCancel);
    popupParam->SetShowInSubWindow(value.showInSubWindow);
    CalcDimension targetSpaceDim(value.targetSpace,
        static_cast<DimensionUnit>(value.targetSpaceUnit));
    CalcDimension arrowOffsetDim(value.arrowOffset,
        static_cast<DimensionUnit>(value.arrowOffsetUnit));
    CalcDimension widthDim(value.width, static_cast<DimensionUnit>(value.widthUnit));
    CalcDimension arrowWidthDim(value.arrowWidth, static_cast<DimensionUnit>(value.arrowWidthUnit));
    CalcDimension arrowHeightDim(value.arrowHeight, static_cast<DimensionUnit>(value.arrowHeightUnit));
    CalcDimension radiusDim(value.radius, static_cast<DimensionUnit>(value.radiusUnit));
    Offset offset(value.offsetX, value.offsetY);
    popupParam->SetArrowOffset(arrowOffsetDim);
    popupParam->SetTargetSpace(targetSpaceDim);
    popupParam->SetBackgroundColor(Color(value.popupColor));
    popupParam->SetMaskColor(Color(value.maskColor));
    popupParam->SetMaskColor(Color(value.mask));
    popupParam->SetArrowWidth(arrowWidthDim);
    popupParam->SetArrowHeight(arrowHeightDim);
    if (value.width > 0) {
        popupParam->SetChildWidth(widthDim);
    }
    if (value.radius > 0) {
        popupParam->SetRadius(radiusDim);
    }
    popupParam->SetShadow(Shadow::CreateShadow(static_cast<ShadowStyle>(value.shadow)));
    popupParam->SetTargetOffset(offset);
    popupParam->SetFocusable(value.focusable);
    popupParam->SetFollowTransformOfTarget(value.followTransformOfTarget);
    if (std::strcmp(value.arrowPointPosition, "Start") == 0) {
        popupParam->SetArrowOffset(ARROW_ZERO_PERCENT_VALUE);
    }
    if (std::strcmp(value.arrowPointPosition, "Center") == 0) {
        popupParam->SetArrowOffset(ARROW_HALF_PERCENT_VALUE);
    }
    if (std::strcmp(value.arrowPointPosition, "End") == 0) {
        popupParam->SetArrowOffset(ARROW_FULL_PERCENT_VALUE);
    }
    if (value.backgroundBlurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
        value.backgroundBlurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        popupParam->SetBlurStyle(static_cast<BlurStyle>(value.backgroundBlurStyle));
    }
}

void FfiOHOSAceFrameworkViewAbstractBindCustomPopup(CJBindCustomPopup value)
{
    std::function<void(bool)> onStateChangeFunc = (reinterpret_cast<int64_t>(value.onStateChange) == 0)
                                                      ? ([](bool) -> void {})
                                                      : CJLambda::Create(value.onStateChange);
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(value.isShow);
    popupParam->SetUseCustomComponent(true);
    popupParam->SetOnStateChange(onStateChangeCallback);
    SetCustomPopupParams(value, popupParam);
    if (value.onWillDismiss.hasValue) {
        std::function<void(const int32_t& info)> onWillDismissFunc =
            [nativeFunc = CJLambda::Create(value.onWillDismiss.value)]
            (const int32_t& info) {nativeFunc(info);};

        popupParam->SetOnWillDismiss(onWillDismissFunc);
    }
    if (value.transition.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(value.transition.value);
        if (nativeTransitionEffect) {
            popupParam->SetHasTransition(true);
            popupParam->SetTransitionEffects(nativeTransitionEffect->effect);
        }
    }
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

void GetMenuShowInSubwindow(NG::MenuParam& menuParam)
{
    menuParam.isShowInSubWindow = false;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuParam.isShowInSubWindow = theme->GetExpandDisplay();
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
    GetMenuShowInSubwindow(options);
    ViewAbstractModel::GetInstance()->BindMenu(std::move(params), nullptr, options);
}

void FfiOHOSAceFrameworkViewAbstractBindCustomMenu(void (*builder)())
{
    NG::MenuParam params;
    GetMenuShowInSubwindow(params);
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

void ParseContentPreviewAnimationOptionsParam(NativeOptionCallBack preview,
    NativeOptionCJContextMenuAnimationOptions previewAnimationOptions, NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    // Parse preview
    if (preview.hasValue) {
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
        previewBuildFunc = CJLambda::Create(preview.value);
    } else {
        menuParam.previewMode = MenuPreviewMode::NONE;
        previewBuildFunc = ([]() -> void {});
    }
    if (previewAnimationOptions.hasValue) {
        CJContextMenuAnimationOptions animationOptions = previewAnimationOptions.value;
        menuParam.previewAnimationOptions.scaleFrom = -1.0f;
        menuParam.previewAnimationOptions.scaleTo = -1.0f;
        if (animationOptions.scaleFrom.hasValue) {
            double scaleFromVal = animationOptions.scaleFrom.value;
            double scaleToVal = animationOptions.scaleTo.value;
            menuParam.previewAnimationOptions.scaleFrom = LessOrEqual(scaleFromVal, 0.0) ? -1.0f : scaleFromVal;
            menuParam.previewAnimationOptions.scaleTo = LessOrEqual(scaleToVal, 0.0) ? -1.0f : scaleToVal;
        }
        menuParam.hasPreviewTransitionEffect = false;
        if (animationOptions.transition.hasValue) {
            menuParam.hasPreviewTransitionEffect = true;
            auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(animationOptions.transition.value);
            if (nativeTransitionEffect) {
                menuParam.previewTransition = nativeTransitionEffect->effect;
            }
        }
        if (menuParam.previewMode != MenuPreviewMode::CUSTOM || menuParam.hasPreviewTransitionEffect ||
            menuParam.hasTransitionEffect ||
            menuParam.contextMenuRegisterType == NG::ContextMenuRegisterType::CUSTOM_TYPE) {
            return;
        }
        menuParam.hoverImageAnimationOptions.scaleFrom = -1.0f;
        menuParam.hoverImageAnimationOptions.scaleTo = -1.0f;
        menuParam.isShowHoverImage = false;
        if (animationOptions.hoverScaleFrom.hasValue) {
            double hoverScaleFromVal = animationOptions.hoverScaleFrom.value;
            double hoverScaleToVal = animationOptions.hoverScaleTo.value;
            menuParam.hoverImageAnimationOptions.scaleFrom =
                LessOrEqual(hoverScaleFromVal, 0.0) ? -1.0f : hoverScaleFromVal;
            menuParam.hoverImageAnimationOptions.scaleTo =
                LessOrEqual(hoverScaleToVal, 0.0) ? -1.0f : hoverScaleToVal;
            menuParam.isShowHoverImage = true;
        }
    }
}

void ParseMenuCallback(NativeOptionCallBack onAppear, NativeOptionCallBack onDisappear,
    NativeOptionCallBack aboutToAppear, NativeOptionCallBack aboutToDisappear, NG::MenuParam& menuParam)
{
    // Parse onAppear
    std::function<void()> onAppearCallback;
    if (onAppear.hasValue) {
        onAppearCallback = CJLambda::Create(onAppear.value);
        menuParam.onAppear = std::move(onAppearCallback);
    }
    // Parse onDisappear
    std::function<void()> onDisappearCallback;
    if (onDisappear.hasValue) {
        onDisappearCallback = CJLambda::Create(onDisappear.value);
        menuParam.onDisappear = std::move(onDisappearCallback);
    }
    // Parse aboutToAppear
    std::function<void()> aboutToAppearCallback;
    if (aboutToAppear.hasValue) {
        aboutToAppearCallback = CJLambda::Create(aboutToAppear.value);
        menuParam.aboutToAppear = std::move(aboutToAppearCallback);
    }
    // Parse aboutToDisappear
    std::function<void()> aboutToDisappearCallback;
    if (aboutToDisappear.hasValue) {
        aboutToDisappearCallback = CJLambda::Create(aboutToDisappear.value);
        menuParam.aboutToDisappear = std::move(aboutToDisappearCallback);
    }
}

// Parse transition
void ParseMenuTransition(NativeOptionInt64 transition, NG::MenuParam& menuParam)
{
    menuParam.hasTransitionEffect = false;
    if (transition.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(transition.value);
        if (nativeTransitionEffect) {
            menuParam.hasTransitionEffect = true;
            menuParam.transition = nativeTransitionEffect->effect;
        }
    }
}

void ParseMenuArrowParam(bool enableArrow, NativeLength arrowOffset, NG::MenuParam& menuParam)
{
    // Parse enableArrow
    menuParam.enableArrow = enableArrow;
    // Parse arrowOffsetDime
    menuParam.arrowOffset = Dimension(arrowOffset.value, static_cast<DimensionUnit>(arrowOffset.unitType));
    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
}

// Parse borderRadius
void ParseMenuBorderRadius(NativeOptionRadius borderRadius, NG::MenuParam& menuParam)
{
    if (borderRadius.hasValue) {
        NativeBorderRadiuses nativeBorderRadiuses = borderRadius.value;
        NG::BorderRadiusProperty radius;
        CalcDimension topLeft(
            nativeBorderRadiuses.topLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topLeftUnit));
        CalcDimension topRight(
            nativeBorderRadiuses.topRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topRightUnit));
        CalcDimension bottomLeft(
            nativeBorderRadiuses.bottomLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomLeftUnit));
        CalcDimension bottomRight(
            nativeBorderRadiuses.bottomRightRadiuses,
            static_cast<DimensionUnit>(nativeBorderRadiuses.bottomRightUnit));
        radius.radiusTopLeft = topLeft;
        radius.radiusTopRight = topRight;
        radius.radiusBottomLeft = bottomLeft;
        radius.radiusBottomRight = bottomRight;
        radius.multiValued = true;
        menuParam.borderRadius = radius;
    }
}

// Parse layoutRegionMargin
void ParseMenuLayoutRegionMarginParam(NativeOptionMargin layoutRegionMargin, NG::MenuParam& menuParam)
{
    if (layoutRegionMargin.hasValue) {
        NativeMargin margin = layoutRegionMargin.value;
        NG::PaddingProperty margins;
        Dimension top(margin.top, static_cast<DimensionUnit>(margin.topUnit));
        Dimension left(margin.left, static_cast<DimensionUnit>(margin.leftUnit));
        Dimension right(margin.right, static_cast<DimensionUnit>(margin.rightUnit));
        Dimension bottom(margin.bottom, static_cast<DimensionUnit>(margin.bottomUnit));
        margins.top = NG::CalcLength(top);
        margins.left = NG::CalcLength(left);
        margins.right = NG::CalcLength(right);
        margins.bottom = NG::CalcLength(bottom);
        menuParam.layoutRegionMargin = margins;
    }
}

void ParseContextMenuParam(CJContextMenuOptions options, NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    // Parse offset
    Dimension dx = Dimension(options.offset.x, DimensionUnit::VP);
    Dimension dy = Dimension(options.offset.y, DimensionUnit::VP);
    menuParam.positionOffset.SetX(dx.ConvertToPx());
    menuParam.positionOffset.SetY(dy.ConvertToPx());
    // Parse placement
    if (options.placement.hasValue) {
        menuParam.placement = static_cast<Placement>(options.placement.value);
    }
    // Parse backgroundColor
    menuParam.backgroundColor = Color(options.backgroundColor);
    // Parse backgroundBlurStyle
    menuParam.backgroundBlurStyle = options.backgroundBlurStyle;
    ParseMenuCallback(options.onAppear, options.onDisappear, options.aboutToAppear, options.aboutToDisappear,
        menuParam);
    ParseMenuTransition(options.transition, menuParam);
    ParseMenuArrowParam(options.enableArrow, options.arrowOffset, menuParam);
    ParseMenuBorderRadius(options.borderRadius, menuParam);
    ParseMenuLayoutRegionMarginParam(options.layoutRegionMargin, menuParam);
    ParseContentPreviewAnimationOptionsParam(options.preview, options.previewAnimationOptions, menuParam,
        previewBuildFunc);
}

void ParseMenuParam(CJMenuOptions options, NG::MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    // Parse offset
    Dimension dx = Dimension(options.offset.x, DimensionUnit::VP);
    Dimension dy = Dimension(options.offset.y, DimensionUnit::VP);
    menuParam.positionOffset.SetX(dx.ConvertToPx());
    menuParam.positionOffset.SetY(dy.ConvertToPx());
    // Parse placement
    if (options.placement.hasValue) {
        menuParam.placement = static_cast<Placement>(options.placement.value);
    }
    // Parse backgroundColor
    menuParam.backgroundColor = Color(options.backgroundColor);
    // Parse backgroundBlurStyle
    menuParam.backgroundBlurStyle = options.backgroundBlurStyle;
    ParseMenuCallback(options.onAppear, options.onDisappear, options.aboutToAppear, options.aboutToDisappear,
        menuParam);
    ParseMenuTransition(options.transition, menuParam);
    GetMenuShowInSubwindow(menuParam);
    if (menuParam.isShowInSubWindow) {
        if (options.showInSubWindow.hasValue) {
            menuParam.isShowInSubWindow = options.showInSubWindow.value;
        }
    }
    ParseMenuArrowParam(options.enableArrow, options.arrowOffset, menuParam);
    ParseMenuBorderRadius(options.borderRadius, menuParam);
    ParseMenuLayoutRegionMarginParam(options.layoutRegionMargin, menuParam);
    ParseContentPreviewAnimationOptionsParam(options.preview, options.previewAnimationOptions, menuParam,
        previewBuildFunc);
}

void FfiOHOSAceFrameworkViewAbstractBindMenuElement(CArrNativeMenuElement elements, CJMenuOptions options)
{
    std::vector<NG::OptionParam> params(elements.size);
    for (size_t i = 0; i < static_cast<size_t>(elements.size); ++i) {
        auto element = elements.head[i];
        params[i].value = element.value.value;
        params[i].action = CJLambda::Create(element.action.value);
        params[i].enabled = element.enabled.value;
        if (element.icon.hasValue) {
            params[i].icon = element.icon.value;
        }
    }
    NG::MenuParam menuParam;
    if (options.title.hasValue) {
        menuParam.title = std::string(options.title.value);
    }
    std::function<void()> previewBuildFunc;
    ParseMenuParam(options, menuParam, previewBuildFunc);
    ViewAbstractModel::GetInstance()->BindMenu(std::move(params), nullptr, menuParam);
}

void FfiOHOSAceFrameworkViewAbstractBindContextMenuOption(
    void (*builder)(), int32_t responseType, CJContextMenuOptions options)
{
    if (!Utils::CheckParamsValid(responseType, RESPONSE_TYPES.size())) {
        LOGE("bindContextMenu error, invalid value for responseType");
        return;
    }
    NG::MenuParam menuParam { .type = NG::MenuType::CONTEXT_MENU };
    auto buildFunc = CJLambda::Create(builder);
    std::function<void()> previewBuildFunc;
    ParseContextMenuParam(options, menuParam, previewBuildFunc);
    ResponseType responseTypeValue = static_cast<OHOS::Ace::ResponseType>(responseType);
    if (responseTypeValue != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.isShowHoverImage = false;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    // arrow is disabled for contextMenu with preview
    if (menuParam.previewMode != MenuPreviewMode::NONE) {
        menuParam.enableArrow = false;
    }
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    ViewAbstractModel::GetInstance()->BindContextMenu(responseTypeValue, buildFunc, menuParam, previewBuildFunc);
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(menuParam);
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

void FfiOHOSAceFrameworkViewAbstractDismiss()
{
    ViewAbstractModel::GetInstance()->DismissSheet();
}

void FfiOHOSAceFrameworkViewAbstractSpringBack()
{
    ViewAbstractModel::GetInstance()->SheetSpringBack();
}

void ParseSheetCallback(CJSheetOptions options, std::function<void()>& onAppear,
    std::function<void()>& onDisappear, std::function<void()>& shouldDismiss, std::function<void()>& onWillAppear,
    std::function<void()>& onWillDisappear)
{
    if (options.onAppear.hasValue) {
        onAppear =  CJLambda::Create(options.onAppear.value);
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
        onWillDisappear =  CJLambda::Create(options.onWillDisappear.value);
    }
}

void ParseSheetCallbackV2(CJSheetOptionsV2 options, std::function<void()>& onAppear, std::function<void()>& onDisappear,
    std::function<void()>& shouldDismiss, std::function<void()>& onWillAppear, std::function<void()>& onWillDisappear,
    std::function<void(const int32_t info)>& onWillDismiss, std::function<void()>& sheetSpringBack,
    std::function<void(const float)>& onHeightDidChange, std::function<void(const float)>& onDetentsDidChange,
    std::function<void(const float)>& onWidthDidChange, std::function<void(const float)>& onTypeDidChange)
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
    if (options.onWillDismiss.hasValue) {
        onWillDismiss = [lambda = CJLambda::Create(options.onWillDismiss.value)](const int32_t info) { lambda(info); };
    }
    if (options.onWillSpringBackWhenDismiss.hasValue) {
        sheetSpringBack = CJLambda::Create(options.onWillSpringBackWhenDismiss.value);
    }
    if (options.onHeightDidChange.hasValue) {
        onHeightDidChange = [lambda = CJLambda::Create(options.onHeightDidChange.value)](
                                const float value) { lambda(value); };
    }
    if (options.onDetentsDidChange.hasValue) {
        onDetentsDidChange = [lambda = CJLambda::Create(options.onDetentsDidChange.value)](
                                 const float value) { lambda(value); };
    }
    if (options.onWidthDidChange.hasValue) {
        onWidthDidChange = [lambda = CJLambda::Create(options.onWidthDidChange.value)](
                               const float value) { lambda(value); };
    }
    if (options.onTypeDidChange.hasValue) {
        onTypeDidChange = [lambda = CJLambda::Create(options.onTypeDidChange.value)](
                              const float value) { lambda(value); };
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

void ParseSheetBorderProps(CJSheetOptionsV2 option, NG::SheetStyle& sheetStyle)
{
    if (option.borderWidth.hasValue) {
        auto nativeBorderWidth = option.borderWidth.value;
        auto borderWidth = Dimension(nativeBorderWidth.value, static_cast<DimensionUnit>(nativeBorderWidth.unitType));
        auto borderWidthProp = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
        sheetStyle.borderWidth = borderWidthProp;
    }
    if (option.borderColor.hasValue) {
        NG::BorderColorProperty colorProperty;
        Color borderColor = Color(ColorAlphaAdapt(option.borderColor.value));
        colorProperty.SetColor(borderColor);
        sheetStyle.borderColor = colorProperty;
    }
    if (option.borderStyle.hasValue) {
        NG::BorderStyleProperty borderStyle;
        auto nativeBorderSytle = option.borderStyle.value;
        borderStyle.styleLeft = static_cast<BorderStyle>(nativeBorderSytle.left);
        borderStyle.styleRight = static_cast<BorderStyle>(nativeBorderSytle.right);
        borderStyle.styleTop = static_cast<BorderStyle>(nativeBorderSytle.top);
        borderStyle.styleBottom = static_cast<BorderStyle>(nativeBorderSytle.bottom);
        borderStyle.multiValued = true;
        sheetStyle.borderStyle = borderStyle;
    }
}

void ParseScrollSizeMode(const NativeOptionUInt32 scrollSizeMode, NG::SheetStyle& sheetStyle)
{
    if (!scrollSizeMode.hasValue) {
        return;
    }
    sheetStyle.scrollSizeMode = NG::ScrollSizeMode::FOLLOW_DETENT;
    if (scrollSizeMode.value >= static_cast<int>(NG::ScrollSizeMode::FOLLOW_DETENT) &&
        scrollSizeMode.value <= static_cast<int>(NG::ScrollSizeMode::CONTINUOUS)) {
        sheetStyle.scrollSizeMode = static_cast<NG::ScrollSizeMode>(scrollSizeMode.value);
    }
}

void ParseShadow(NativeShadow nativeShadow, NG::SheetStyle& sheetStyle)
{
    if (!nativeShadow.hasValue) {
        return;
    }
    Shadow shadow;
    NativeShadowOptions shadowOptions = nativeShadow.value;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(ColorAlphaAdapt(shadowOptions.color));
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    sheetStyle.shadow = shadow;
}

void ParseBlurStyle(const int32_t blurStyle, NG::SheetStyle& sheetStyle)
{
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::NO_MATERIAL;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
    }
    sheetStyle.backgroundBlurStyle = styleOption;
}

void ParsePreferType(const int32_t sheetType, NG::SheetStyle& sheetStyle)
{
    if (sheetType >= static_cast<int>(NG::SheetType::SHEET_BOTTOM) &&
        sheetType <= static_cast<int>(NG::SheetType::SHEET_POPUP)) {
        sheetStyle.sheetType = static_cast<NG::SheetType>(sheetType);
    }
}

void ParseSheetHeight(const int height, NG::SheetStyle& sheetStyle)
{
    NG::SheetHeight sheetDetent;
    ParseSheetDetentHeight(height, sheetDetent);
    sheetStyle.sheetHeight.sheetMode = sheetDetent.sheetMode;
    sheetStyle.sheetHeight.height = sheetDetent.height;
}

void ParseSheetStyle(CJSheetOptions option, NG::SheetStyle& sheetStyle)
{
    std::vector<NG::SheetHeight> detents;
    if (option.detents.hasValue && ParseSheetDetents(option.detents.value, detents)) {
        sheetStyle.detents = detents;
    }
    if (option.blurStyle.hasValue) {
        ParseBlurStyle(option.blurStyle.value, sheetStyle);
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
        ParsePreferType(option.preferType.value, sheetStyle);
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
        sheetStyle.sheetHeight.sheetMode = sheetDetent.sheetMode;
        sheetStyle.sheetHeight.height = sheetDetent.height;
    }
}

void ParseSheetStyleV2(CJSheetOptionsV2 option, NG::SheetStyle& sheetStyle)
{
    std::vector<NG::SheetHeight> detents;
    if (option.detents.hasValue && ParseSheetDetents(option.detents.value, detents)) {
        sheetStyle.detents = detents;
    }
    if (option.blurStyle.hasValue) {
        ParseBlurStyle(option.blurStyle.value, sheetStyle);
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
        ParsePreferType(option.preferType.value, sheetStyle);
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
        sheetStyle.sheetHeight.sheetMode = sheetDetent.sheetMode;
        sheetStyle.sheetHeight.height = sheetDetent.height;
    }
    if (option.mode.hasValue) {
        auto sheetLevel = option.mode.value;
        sheetStyle.showInPage = (sheetLevel == static_cast<uint32_t>(NG::SheetLevel::EMBEDDED));
    }
    if (option.width.hasValue) {
        sheetStyle.width =
            CalcDimension(option.width.value.value, static_cast<DimensionUnit>(option.width.value.unitType));
    }
    ParseScrollSizeMode(option.scrollSizeMode, sheetStyle);
    ParseShadow(option.shadow, sheetStyle);
    ParseSheetBorderProps(option, sheetStyle);
}

void ParseSheetTitle(
    NativeOptionCallBack title, NG::SheetStyle& sheetStyle, std::function<void()>& titleBuilderFunction)
{
    sheetStyle.isTitleBuilder = true;
    titleBuilderFunction = title.hasValue ? CJLambda::Create(title.value) : ([]() -> void {});
}

void FfiOHOSAceFrameworkViewAbstractbindSheetParam(bool isShow, void (*builder)(), CJSheetOptions option)
{
    auto buildFunc = CJLambda::Create(builder);
    NG::SheetStyle sheetStyle;
    DoubleBindCallback callback = nullptr;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
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
    ParseSheetCallback(option, onAppearCallback, onDisappearCallback, shouldDismissFunc,
        onWillAppearCallback, onWillDisappearCallback);
    ParseSheetStyle(option, sheetStyle);
    ParseSheetTitle(option.title, sheetStyle, titleBuilderFunction);
    ViewAbstractModel::GetInstance()->BindSheet(isShow, std::move(callback), std::move(buildFunc),
        std::move(titleBuilderFunction), sheetStyle, std::move(onAppearCallback), std::move(onDisappearCallback),
        std::move(shouldDismissFunc), std::move(onWillDismissCallback),  std::move(onWillAppearCallback),
        std::move(onWillDisappearCallback), std::move(onHeightDidChangeCallback),
        std::move(onDetentsDidChangeCallback), std::move(onWidthDidChangeCallback),
        std::move(onTypeDidChangeCallback), std::move(sheetSpringBackFunc));
    return;
}

void FfiOHOSAceFrameworkViewAbstractbindSheetParamV2(bool isShow, void (*builder)(), CJSheetOptionsV2 option)
{
    auto buildFunc = CJLambda::Create(builder);
    NG::SheetStyle sheetStyle;
    DoubleBindCallback callback = nullptr;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
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
    ParseSheetCallbackV2(option, onAppearCallback, onDisappearCallback, shouldDismissFunc, onWillAppearCallback,
        onWillDisappearCallback, onWillDismissCallback, sheetSpringBackFunc, onHeightDidChangeCallback,
        onDetentsDidChangeCallback, onWidthDidChangeCallback, onTypeDidChangeCallback);
    ParseSheetStyleV2(option, sheetStyle);
    ParseSheetTitle(option.title, sheetStyle, titleBuilderFunction);
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

void ParseModalTransition(uint32_t transVal, NativeOptionUInt32 bgColor, NG::ModalStyle& modalStyle)
{
    modalStyle.modalTransition = NG::ModalTransition::DEFAULT;
    auto modalTransition = transVal;
    auto transitionNumber = static_cast<int32_t>(modalTransition);
    modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
    if (bgColor.hasValue) {
        auto backgroundColor = static_cast<uint32_t>(bgColor.value);
        modalStyle.backgroundColor = Color(backgroundColor);
    }
}

void FFIOHOSAceFrameworkBindContentCoverV2(bool isShow, void (*builder)(), CJContentCoverOptionsV2 options)
{
    // parse builder
    auto buildFunc = CJLambda::Create(builder);

    // parse ModalTransition
    NG::ModalStyle modalStyle;
    ParseModalTransition(options.modalTransition, options.backgroundColor, modalStyle);
    std::function<void()> onWillShowCallback =
        options.onWillAppear.hasValue ? CJLambda::Create(options.onWillAppear.value) : ([]() -> void {});
    std::function<void()> onWillDismissCallback =
        options.onWillDisappear.hasValue ? CJLambda::Create(options.onWillDisappear.value) : ([]() -> void {});
    NG::ContentCoverParam contentCoverParam;
    std::function<void(const int32_t&)> onWillDismissFunc;
    // parse callback
    std::function<void()> onShowCallback =
        options.onAppear.hasValue ? CJLambda::Create(options.onAppear.value) : ([]() -> void {});
    std::function<void()> onDismissCallback =
        options.onDisappear.hasValue ? CJLambda::Create(options.onDisappear.value) : ([]() -> void {});

    auto transitionEffectValue = options.transition;
    if (transitionEffectValue.hasValue) {
        auto nativeTransitionEffect = FFIData::GetData<NativeTransitionEffect>(transitionEffectValue.value);
        if (nativeTransitionEffect != nullptr) {
            auto chainedEffect = nativeTransitionEffect->effect;
            contentCoverParam.transitionEffect = chainedEffect;
        }
    }
    auto onWillDismiss = options.onWillDismiss;
    if (onWillDismiss.hasValue) {
        auto callback = onWillDismiss.value;
        auto lambda = CJLambda::Create(callback);
        auto onWillDismissFunc = [lambda](const int32_t& info) {
            auto dismissContentCoverLambda = []() {
                ViewAbstractModel::GetInstance()->DismissContentCover();
            };
            CJDismissContentCoverAction dismissAction = {
                .reason = info,
                .dismissContentCover = dismissContentCoverLambda };
            lambda(dismissAction);
        };
        contentCoverParam.onWillDismiss = std::move(onWillDismissFunc);
    }

    ViewAbstractModel::GetInstance()->BindContentCover(isShow, nullptr, std::move(buildFunc), modalStyle,
        std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
        std::move(onWillDismissCallback), contentCoverParam);
}

void FFIOHOSAceFrameworkBindContentCover(bool isShow, void (*builder)(), CJContentCoverOptions options)
{
    // parse builder
    auto buildFunc = CJLambda::Create(builder);

    // parse ModalTransition
    NG::ModalStyle modalStyle;
    ParseModalTransition(options.modalTransition, options.backgroundColor, modalStyle);
    std::function<void()> onWillShowCallback =
        options.onWillAppear.hasValue ? CJLambda::Create(options.onWillAppear.value) : ([]() -> void {});
    std::function<void()> onWillDismissCallback =
        options.onWillDisappear.hasValue ? CJLambda::Create(options.onWillDisappear.value) : ([]() -> void {});
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

void FFIOHOSAceFrameworkSetCursor(int32_t pointerStyle)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        LOGE("pipeline context is non-valid");
        return;
    }
    if (!pipelineContext->GetTaskExecutor()) {
        LOGE("TaskExecutor is non-valid");
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, pointerStyle]() { pipelineContext->SetCursor(pointerStyle); }, TaskExecutor::TaskType::UI,
        "ArkUICjSetCursor");
}

void FFIOHOSAceFrameworkRestoreDefault()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        LOGE("pipeline context is non-valid");
        return;
    }
    if (!pipelineContext->GetTaskExecutor()) {
        LOGE("TaskExecutor is non-valid");
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask([pipelineContext]() { pipelineContext->RestoreDefault(); },
        TaskExecutor::TaskType::UI, "ArkUICjRestoreDefault");
}

void FFIOHOSAceFrameworkMonopolizeEvents(bool monopolize)
{
    ViewAbstractModel::GetInstance()->SetMonopolizeEvents(monopolize);
}

void FfiOHOSAceFrameworkViewAbstractSetDraggable(bool value)
{
    ViewAbstractModel::GetInstance()->SetDraggable(value);
}

void FfiOHOSAceFrameworkViewAbstractSetDragPreviewWithBuilder(void (*builder)())
{
    NG::DragDropInfo dragPreviewInfo;
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    dragPreviewInfo.customNode = AceType::DynamicCast<NG::UINode>(customNode);
    ViewAbstractModel::GetInstance()->SetDragPreview(dragPreviewInfo);
}

void FfiOHOSAceFrameworkViewAbstractSetDragPreviewWithDragItemInfo(CJDragItemInfo value)
{
    NG::DragDropInfo dragPreviewInfo;

    if (value.builder == nullptr) {
        dragPreviewInfo.customNode = nullptr;
    } else {
        auto buildFunc = CJLambda::Create(value.builder);
        RefPtr<AceType> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            buildFunc();
            customNode = ViewStackModel::GetInstance()->Finish();
        }
        dragPreviewInfo.customNode = AceType::DynamicCast<NG::UINode>(customNode);
    }

#if defined(PIXEL_MAP_SUPPORTED)
    dragPreviewInfo.pixelMap = ParseDragPreviewPixelMap(value.pixelMapId);
#else
    dragPreviewInfo.pixelMap = nullptr;
#endif

    dragPreviewInfo.extraInfo = std::string(value.extraInfo);
    ViewAbstractModel::GetInstance()->SetDragPreview(dragPreviewInfo);
}

void FfiOHOSAceFrameworkViewAbstractSetDragPreviewWithString(const char* value)
{
    NG::DragDropInfo dragPreviewInfo;
    dragPreviewInfo.inspectorId = std::string(value);
    ViewAbstractModel::GetInstance()->SetDragPreview(dragPreviewInfo);
}

void FfiOHOSAceFrameworkViewAbstractHitTestBehavior(int32_t hitTestMode)
{
    ViewAbstractModel::GetInstance()->SetHitTestMode(static_cast<NG::HitTestMode>(hitTestMode));
}

void FFiOHOSAceFrameworkViewAbstractHoverEffect(int32_t hoverEffectValue)
{
    ViewAbstractModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(hoverEffectValue));
}

void FfiOHOSAceFrameworkViewAbstractSetBorderImageWithString(
    const char* source, CBorderImageOption option)
{
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;

    borderImage->SetSrc(std::string(source));
    imageBorderBitsets |= BorderImage::SOURCE_BIT;

    ParceBorderImageParam(borderImage, imageBorderBitsets, option);
    ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
}

void FfiOHOSAceFrameworkViewAbstractSetBorderImageWithLinearGradient(
    LinearGradientParam source, CBorderImageOption option)
{
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;

    NG::Gradient lineGradient;
    NewCjLinearGradient(source, lineGradient);
    ViewAbstractModel::GetInstance()->SetBorderImageGradient(lineGradient);
    imageBorderBitsets |= BorderImage::GRADIENT_BIT;

    ParceBorderImageParam(borderImage, imageBorderBitsets, option);
    ViewAbstractModel::GetInstance()->SetBorderImage(borderImage, imageBorderBitsets);
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

void ParceBorderImageParam(RefPtr<BorderImage>& borderImage, uint8_t& bitset, CBorderImageOption& option)
{
    borderImage->SetEdgeOutset(
        BorderImageDirection::LEFT,
        Dimension(option.outset.left, static_cast<DimensionUnit>(option.outset.leftUnit)));
    borderImage->SetEdgeOutset(
        BorderImageDirection::RIGHT,
        Dimension(option.outset.right, static_cast<DimensionUnit>(option.outset.rightUnit)));
    borderImage->SetEdgeOutset(
        BorderImageDirection::TOP,
        Dimension(option.outset.top, static_cast<DimensionUnit>(option.outset.topUnit)));
    borderImage->SetEdgeOutset(
        BorderImageDirection::BOTTOM,
        Dimension(option.outset.bottom, static_cast<DimensionUnit>(option.outset.bottomUnit)));
    bitset |= BorderImage::OUTSET_BIT;

    borderImage->SetEdgeWidth(
        BorderImageDirection::LEFT,
        Dimension(option.width.left, static_cast<DimensionUnit>(option.width.leftUnit)));
    borderImage->SetEdgeWidth(
        BorderImageDirection::RIGHT,
        Dimension(option.width.right, static_cast<DimensionUnit>(option.width.rightUnit)));
    borderImage->SetEdgeWidth(
        BorderImageDirection::TOP,
        Dimension(option.width.top, static_cast<DimensionUnit>(option.width.topUnit)));
    borderImage->SetEdgeWidth(
        BorderImageDirection::BOTTOM,
        Dimension(option.width.bottom, static_cast<DimensionUnit>(option.width.bottomUnit)));
    bitset |= BorderImage::WIDTH_BIT;

    borderImage->SetEdgeSlice(
        BorderImageDirection::LEFT,
        Dimension(option.slice.left, static_cast<DimensionUnit>(option.slice.leftUnit)));
    borderImage->SetEdgeSlice(
        BorderImageDirection::RIGHT,
        Dimension(option.slice.right, static_cast<DimensionUnit>(option.slice.rightUnit)));
    borderImage->SetEdgeSlice(
        BorderImageDirection::TOP,
        Dimension(option.slice.top, static_cast<DimensionUnit>(option.slice.topUnit)));
    borderImage->SetEdgeSlice(
        BorderImageDirection::BOTTOM,
        Dimension(option.slice.bottom, static_cast<DimensionUnit>(option.slice.bottomUnit)));
    bitset |= BorderImage::SLICE_BIT;

    borderImage->SetRepeatMode(static_cast<BorderImageRepeat>(option.repeat));
    bitset |= BorderImage::REPEAT_BIT;

    borderImage->SetNeedFillCenter(option.fill);
}

RefPtr<PixelMap> ParseDragPreviewPixelMap(int64_t pixelMapId)
{
    if (pixelMapId == 0) {
        return nullptr;
    }
    auto pixelMapImpl = FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (pixelMapImpl == nullptr) {
        LOGE("DragPreview error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
        return nullptr;
    }
    auto pixMap = pixelMapImpl->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("DragPreview error, Cannot get pixMap in PixelMapProxy");
        return nullptr;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("DragPreview error, Cannot create PixelMapOhos by pixMap");
        return nullptr;
    }

    return pixMapOhos;
}
} // namespace OHOS::Ace
