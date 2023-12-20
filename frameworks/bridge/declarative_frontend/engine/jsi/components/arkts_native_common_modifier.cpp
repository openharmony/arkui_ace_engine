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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_common_modifier.h"

#include "base/geometry/ng/vector.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr VisibleType DEFAULT_VISIBILITY = static_cast<VisibleType>(0);
constexpr float MAX_ANGLE = 360.0f;
constexpr double PERCENT_100 = 100.0;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int NUM_14 = 14;
constexpr int NUM_15 = 15;
constexpr int NUM_16 = 16;
constexpr int NUM_24 = 24;
constexpr int DEFAULT_LENGTH = 4;
constexpr double ROUND_UNIT = 360.0;
constexpr TextDirection DEFAULT_COMMON_DIRECTION = TextDirection::AUTO;
constexpr int32_t DEFAULT_COMMON_LAYOUTWEIGHT = 0;
constexpr int32_t MAX_ALIGN_VALUE = 8;
constexpr int32_t DEFAULT_GRIDSPAN = 1;
constexpr uint32_t DEFAULT_ALIGN_VALUE = 2;
constexpr uint32_t DEFAULT_ALIGN_RULES_SIZE = 6;
constexpr uint8_t DEFAULT_SAFE_AREA_TYPE = 0b111;
constexpr uint8_t DEFAULT_SAFE_AREA_EDGE = 0b1111;
constexpr Dimension DEFAULT_FLEX_BASIS { 0.0, DimensionUnit::AUTO };
constexpr int32_t DEFAULT_DISPLAY_PRIORITY = 0;
constexpr int32_t DEFAULT_ID = 0;

BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

Alignment ParseAlignment(int32_t align)
{
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case NUM_0:
            alignment = Alignment::TOP_LEFT;
            break;
        case NUM_1:
            alignment = Alignment::TOP_CENTER;
            break;
        case NUM_2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case NUM_3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case NUM_4:
            alignment = Alignment::CENTER;
            break;
        case NUM_5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case NUM_6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case NUM_7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case NUM_8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            break;
    }
    return alignment;
}

/**
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetGradientColors(NG::Gradient &gradient, const double *colors, int32_t colorsLength)
{
    if ((colors == nullptr) || (colorsLength % NUM_3) != 0) {
        return;
    }
    for (int32_t index = 0; index < colorsLength; index += NUM_3) {
        auto colorValue = colors[index];
        auto colorHasDimension = colors[index + NUM_1];
        auto colorDimension = colors[index + NUM_2];
        auto color = static_cast<uint32_t>(colorValue);
        auto hasDimension = static_cast<bool>(colorHasDimension);
        auto dimension = colorDimension;
        NG::GradientColor gradientColor;
        gradientColor.SetColor(Color(color));
        gradientColor.SetHasValue(hasDimension);
        if (hasDimension) {
            gradientColor.SetDimension(CalcDimension(dimension * PERCENT_100, DimensionUnit::PERCENT));
        }
        gradient.AddColor(gradientColor);
    }
}

void SetLinearGradientDirectionTo(std::shared_ptr<LinearGradient> &linearGradient, const GradientDirection direction)
{
    switch (direction) {
        case GradientDirection::LEFT:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            linearGradient->linearX = NG::GradientDirection::LEFT;
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            linearGradient->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            linearGradient->linearX = NG::GradientDirection::RIGHT;
            linearGradient->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 */
void SetLinearGradientValues(NG::Gradient &gradient, const double *values, int32_t valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_4)) {
        return;
    }
    auto angleHasValue = values[NUM_0];
    auto angleValue = values[NUM_1];
    auto directionValue = values[NUM_2];
    auto repeating = values[NUM_3];
    auto linearGradient = gradient.GetLinearGradient();
    if (linearGradient == nullptr) {
        return;
    }
    if (static_cast<bool>(angleHasValue)) {
        linearGradient->angle = CalcDimension(angleValue, DimensionUnit::PX);
    }
    SetLinearGradientDirectionTo(linearGradient, static_cast<GradientDirection>(directionValue));
    gradient.SetRepeat(static_cast<bool>(repeating));
}

float CheckAngle(const float angle)
{
    if (LessNotEqual(angle, 0.0f)) {
        return 0.0f;
    } else if (GreatNotEqual(angle, MAX_ANGLE)) {
        return MAX_ANGLE;
    }
    return angle;
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7] : start: hasValue, start degree value
 * values[8], values[9] : end: hasValue, end degree value
 * values[10], values[11] : rotation: hasValue, rotation degree value
 * values[12] : repeating
 * @param valuesLength values length
 */
void SetSweepGradientValues(NG::Gradient& gradient, const double* values, int32_t valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_13)) {
        return;
    }
    auto centerXHasValue = values[NUM_0];
    auto centerXValue = values[NUM_1];
    auto centerXUnit = values[NUM_2];
    auto centerYHasValue = values[NUM_3];
    auto centerYValue = values[NUM_4];
    auto centerYUnit = values[NUM_5];
    auto startHasValue = values[NUM_6];
    auto startValue = values[NUM_7];
    auto endHasValue = values[NUM_8];
    auto endValue = values[NUM_9];
    auto rotationHasValue = values[NUM_10];
    auto rotationValue = values[NUM_11];
    auto repeating = values[NUM_12];
    if (static_cast<bool>(centerXHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerXUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerXValue * PERCENT_100) : centerXValue;
        gradient.GetSweepGradient()->centerX = CalcDimension(value, unit);
    }
    if (static_cast<bool>(centerYHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerYUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerYValue * PERCENT_100) : centerYValue;
        gradient.GetSweepGradient()->centerY = CalcDimension(value, unit);
    }
    if (static_cast<bool>(startHasValue)) {
        gradient.GetSweepGradient()->startAngle = CalcDimension(CheckAngle(startValue), DimensionUnit::PX);
    }
    if (static_cast<bool>(endHasValue)) {
        gradient.GetSweepGradient()->endAngle = CalcDimension(CheckAngle(endValue), DimensionUnit::PX);
    }
    if (static_cast<bool>(rotationHasValue)) {
        gradient.GetSweepGradient()->rotation = CalcDimension(CheckAngle(rotationValue), DimensionUnit::PX);
    }
    gradient.SetRepeat(static_cast<bool>(repeating));
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7], values[8] : radius: Dimension: hasValue, value, unit
 * values[9] : repeating
 * @param valuesLength values length
 */
void SetRadialGradientValues(NG::Gradient& gradient, const double* values, int32_t valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_10)) {
        return;
    }
    auto centerXHasValue = values[NUM_0];
    auto centerXValue = values[NUM_1];
    auto centerXUnit = values[NUM_2];
    auto centerYHasValue = values[NUM_3];
    auto centerYValue = values[NUM_4];
    auto centerYUnit = values[NUM_5];
    auto radiusHasValue = values[NUM_6];
    auto radiusValue = values[NUM_7];
    auto radiusUnit = values[NUM_8];
    auto repeating = values[NUM_9];
    if (static_cast<bool>(centerXHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerXUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerXValue * PERCENT_100) : centerXValue;
        gradient.GetRadialGradient()->radialCenterX = CalcDimension(value, unit);
    }
    if (static_cast<bool>(centerYHasValue)) {
        auto unit = static_cast<DimensionUnit>(centerYUnit);
        auto value = (unit == DimensionUnit::PERCENT) ? (centerYValue * PERCENT_100) : centerYValue;
        gradient.GetRadialGradient()->radialCenterY = CalcDimension(value, unit);
    }
    if (static_cast<bool>(radiusHasValue)) {
        auto unit = static_cast<DimensionUnit>(radiusUnit);
        auto value = CheckAngle(radiusValue);
        gradient.GetRadialGradient()->radialVerticalSize = CalcDimension(value, unit);
        gradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(value, unit);
    }
    gradient.SetRepeat(static_cast<bool>(repeating));
}

bool SetCalcDimension(std::optional<CalcDimension>& optDimension,
    const StringAndDouble* options, int32_t optionsLength, int32_t offset)
{
    if ((options == nullptr) || (offset < 0) || ((offset + NUM_3) >= optionsLength)) {
        return false;
    }
    auto hasValue = options[offset];
    auto value = options[offset + NUM_1];
    auto unit = options[offset + NUM_2];
    if (static_cast<bool>(hasValue.value)) {
        DimensionUnit unitValue = static_cast<DimensionUnit>(unit.value);
        if (unitValue == DimensionUnit::CALC) {
            std::string str;
            if (value.valueStr != nullptr) {
                str = value.valueStr;
            }
            CalcDimension calcDimension(str, unitValue);
            optDimension = calcDimension;
        } else {
            CalcDimension calcDimension(value.value, unitValue);
            optDimension = calcDimension;
        }
    }
    return true;
}

void SetOptionalBorder(
    std::optional<Dimension>& optioalDimension, const double* values, int32_t valuesSize, int32_t& offset)
{
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optioalDimension =
            Dimension(values[offset + NUM_1], static_cast<OHOS::Ace::DimensionUnit>(values[offset + NUM_2]));
    }
    offset = offset + NUM_3;
}

void SetOptionalBorderColor(
    std::optional<Color>& optioalColor, const uint32_t* values, int32_t valuesSize, int32_t& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optioalColor = Color(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetOptionalBorderStyle(
    std::optional<BorderStyle>& optioaStyle, const uint32_t* values, int32_t valuesSize, int32_t& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optioaStyle = ConvertBorderStyle(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetBorderImageSlice(RefPtr<BorderImage>& borderImage,
    const std::vector<BorderImageDirection> directions,
    const StringAndDouble* options, int32_t optionsLength, int32_t& offset)
{
    for (unsigned int index = 0; index < NUM_12; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, optionsLength, offset + index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            borderImage->SetEdgeSlice(direction, optDimension.value());
        }
    }
    offset += NUM_12;
}

void SetBorderImageRepeat(RefPtr<BorderImage>& borderImage,
    const StringAndDouble* options, int32_t optionsLength, int32_t& offset)
{
    if ((options == nullptr) || (offset < 0) || ((offset + NUM_2) >= optionsLength)) {
        return;
    }
    auto hasValue = options[offset];
    auto value = options[offset + NUM_1];
    if (static_cast<bool>(hasValue.value)) {
        auto repeatMode = static_cast<BorderImageRepeat>(value.value);
        borderImage->SetRepeatMode(repeatMode);
    }
    offset += NUM_2;
}

void SetBorderImageWidth(RefPtr<BorderImage>& borderImage,
    const std::vector<BorderImageDirection> directions,
    const StringAndDouble* options, int32_t optionsLength, int32_t& offset)
{
    for (unsigned int index = 0; index < NUM_12; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, optionsLength, offset + index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            borderImage->SetEdgeWidth(direction, optDimension.value());
        }
    }
    offset += NUM_12;
}

void SetBorderImageOutset(RefPtr<BorderImage>& borderImage,
    const std::vector<BorderImageDirection> directions,
    const StringAndDouble* options, int32_t optionsLength, int32_t& offset)
{
    for (unsigned int index = 0; index < NUM_12; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, optionsLength, offset + index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            borderImage->SetEdgeOutset(direction, optDimension.value());
        }
    }
    offset += NUM_12;
}

void SetBorderImageFill(RefPtr<BorderImage>& borderImage,
    const StringAndDouble* options, int32_t optionsLength, int32_t& offset)
{
    if ((options == nullptr) || (offset < 0) || ((offset + NUM_2) >= optionsLength)) {
        return;
    }
    auto hasValue = options[offset];
    auto value = options[offset + NUM_1];
    if (static_cast<bool>(hasValue.value)) {
        borderImage->SetNeedFillCenter(static_cast<bool>(value.value));
    }
    offset += NUM_2;
}

void SetBorderImage(FrameNode* frameNode, const RefPtr<BorderImage>& borderImage, uint8_t bitset)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(borderImage);
    if (bitset | BorderImage::SOURCE_BIT) {
        ViewAbstract::SetBorderImageSource(frameNode, borderImage->GetSrc());
    }
    if (bitset | BorderImage::OUTSET_BIT) {
        ViewAbstract::SetHasBorderImageOutset(frameNode, true);
    }
    if (bitset | BorderImage::SLICE_BIT) {
        ViewAbstract::SetHasBorderImageSlice(frameNode, true);
    }
    if (bitset | BorderImage::REPEAT_BIT) {
        ViewAbstract::SetHasBorderImageRepeat(frameNode, true);
    }
    if (bitset | BorderImage::WIDTH_BIT) {
        ViewAbstract::SetHasBorderImageWidth(frameNode, true);
    }
    ViewAbstract::SetBorderImage(frameNode, borderImage);
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 */
void SetBorderImageGradientValues(NG::Gradient& gradient, const double* values, int32_t valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_4)) {
        return;
    }
    auto angleHasValue = values[NUM_0];
    auto angleValue = values[NUM_1];
    auto directionValue = values[NUM_2];
    auto repeating = values[NUM_3];
    auto linearGradient = gradient.GetLinearGradient();
    if (linearGradient == nullptr) {
        return;
    }
    if (static_cast<bool>(angleHasValue)) {
        linearGradient->angle = CalcDimension(angleValue, DimensionUnit::PX);
    }
    SetLinearGradientDirectionTo(linearGradient, static_cast<GradientDirection>(directionValue));
    gradient.SetRepeat(static_cast<bool>(repeating));
}

void SetBgImgPosition(const DimensionUnit& typeX, const DimensionUnit& typeY, const double valueX, const double valueY,
    BackgroundImagePosition& bgImgPosition)
{
    OHOS::Ace::AnimationOption option;
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
}
} // namespace

void SetBackgroundColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundColor(frameNode, Color(color));
}

void ResetBackgroundColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

void SetWidth(NodeHandle node, double value, int unit, const char* calcVlaue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetWidth(
            frameNode, CalcLength(CalcLength(std::string(calcVlaue))));
    } else {
        ViewAbstract::SetWidth(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetWidth(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}
void SetHeight(NodeHandle node, double value, int unit, const char* calcVlaue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(
            frameNode, CalcLength(CalcLength(std::string(calcVlaue))));
    } else {
        ViewAbstract::SetHeight(frameNode, CalcLength(value, unitEnum));
    }
}
void ResetHeight(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}
/**
 * @param values radius values
 * value[0] : radius value for TopLeft，value[1] : radius value for TopRight
 * value[2] : radius value for BottomLeft，value[3] : radius value for BottomRight
 * @param units adius units
 * units[0]: radius unit for TopLeft ,units[1] : radius unit for TopRight
 * units[2]: radius unit for BottomLeft, units[3] : radius unit for TopRight
 */
void SetBorderRadius(NodeHandle node, const double *values, const int *units, int32_t length)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    borderRadius.multiValued = true;
    ViewAbstract::SetBorderRadius(frameNode, borderRadius);
}

void ResetBorderRadius(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    ViewAbstract::SetBorderRadius(frameNode, reset);
}

/**
 * @param values radius values, -1 means no this border width
 * value[0] : BorderWidth value for left，value[1] : BorderWidth value for right
 * value[2] : BorderWidth value for top，value[3] : BorderWidth value for bottom
 * @param units adius units
 * units[0]: BorderWidth unit for left ,units[1] : BorderWidth unit for right
 * units[2]: BorderWidth unit for top, units[3] : BorderWidth unit for bottom
 */
void SetBorderWidth(NodeHandle node, const double* values, const int* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    std::optional<CalcDimension> leftDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> bottomDimen;

    if (values[NUM_0] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]) != OHOS::Ace::DimensionUnit::INVALID) {
        leftDimen = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    }
    if (values[NUM_1] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]) != OHOS::Ace::DimensionUnit::INVALID) {
        rightDimen = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    }
    if (values[NUM_2] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]) != OHOS::Ace::DimensionUnit::INVALID) {
        topDimen = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    }
    if (values[NUM_3] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]) != OHOS::Ace::DimensionUnit::INVALID) {
        bottomDimen = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    }

    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = leftDimen;
    borderWidth.rightDimen = rightDimen;
    borderWidth.topDimen = topDimen;
    borderWidth.bottomDimen = bottomDimen;
    borderWidth.multiValued = true;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void ResetBorderWidth(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::Dimension borderWidth;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void SetTransform(NodeHandle node, const float *matrix, int32_t length)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (length != matrix4Len) {
        return;
    }
    NG::ViewAbstract::SetTransformMatrix(frameNode, Matrix4(matrix[NUM_0], matrix[NUM_4], matrix[NUM_8], matrix[NUM_12],
        matrix[NUM_1], matrix[NUM_5], matrix[NUM_9], matrix[NUM_13], matrix[NUM_2], matrix[NUM_6], matrix[NUM_10],
        matrix[NUM_14], matrix[NUM_3], matrix[NUM_7], matrix[NUM_11], matrix[NUM_15]));
}

void ResetTransform(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        double value = 1.0;
        matrix[i] = static_cast<float>(value);
    }
    NG::ViewAbstract::SetTransformMatrix(frameNode, Matrix4(matrix[NUM_0], matrix[NUM_4], matrix[NUM_8], matrix[NUM_12],
        matrix[NUM_1], matrix[NUM_5], matrix[NUM_9], matrix[NUM_13], matrix[NUM_2], matrix[NUM_6], matrix[NUM_10],
        matrix[NUM_14], matrix[NUM_3], matrix[NUM_7], matrix[NUM_11], matrix[NUM_15]));
}
void SetBorderColor(NodeHandle node, const uint32_t &leftColorInt, const uint32_t &rightColorInt,
    const uint32_t &topColorInt, const uint32_t &bottomColorInt)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderColorProperty borderColors;
    borderColors.leftColor = Color(leftColorInt);
    borderColors.rightColor = Color(rightColorInt);
    borderColors.topColor = Color(topColorInt);
    borderColors.bottomColor = Color(bottomColorInt);
    borderColors.multiValued = true;

    ViewAbstract::SetBorderColor(frameNode, borderColors);
}

void ResetBorderColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
}

/**
 * @param xValue position x value
 * @param xUnit position x unit
 * @param yValue position y unit
 * @param yUnit position y unit
 */
void SetPosition(NodeHandle node, double xValue, int xUnit, double yValue, int yUnit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    ViewAbstract::SetPosition(frameNode, { Dimension(xValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit)),
        Dimension(yValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit)) });
}

void ResetPosition(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPosition(frameNode, { 0.0_vp, 0.0_vp });
}

/**
 * @param styles styles value
 * styles[0] : styleLeft, styles[1] : styleRight, styles[2] : styleTop, styles[3] : styleBottom
 * @param length styles length
 */
void SetBorderStyle(NodeHandle node, const int32_t *styles, int32_t length)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        ViewAbstract::SetBorderStyle(frameNode, ConvertBorderStyle(styles[NUM_0]));
        return;
    }
    if (length == NUM_4) {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = ConvertBorderStyle(styles[NUM_3]);
        borderStyles.styleRight = ConvertBorderStyle(styles[NUM_1]);
        borderStyles.styleTop = ConvertBorderStyle(styles[NUM_0]);
        borderStyles.styleBottom = ConvertBorderStyle(styles[NUM_2]);
        borderStyles.multiValued = true;
        ViewAbstract::SetBorderStyle(frameNode, borderStyles);
    }
}

void ResetBorderStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
}

bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    auto colorMode = SystemProperties::GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

/**
 * @param shadows shadow value
 * shadows[0] : BlurRadius, shadows[1] : SpreadRadius
 * shadows[2] : OffsetX, offset[3] : OffsetY
 * shadows[4] : ShadowType, shadows[5] : Color, shadows[6] : IsFilled
 * @param length shadows length
 */
void SetBackShadow(NodeHandle node, const double *shadows, int32_t length)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        Shadow shadow;
        auto shadowStyle = static_cast<ShadowStyle>(shadows[NUM_0]);
        auto style = static_cast<ShadowStyle>(shadowStyle);
        if (GetShadowFromTheme(style, shadow)) {
            ViewAbstract::SetBackShadow(frameNode, shadow);
        }
    }
    if (length != NUM_7) {
        return;
    }
    auto blurRadius = shadows[NUM_0];                        // BlurRadius
    auto spreadRadius = shadows[NUM_1];                      // SpreadRadius
    auto offsetX = shadows[NUM_2];                           // OffsetX
    auto offsetY = shadows[NUM_3];                           // OffsetY
    auto shadowType = static_cast<uint32_t>(shadows[NUM_4]); // ShadowType
    auto color = static_cast<uint32_t>(shadows[NUM_5]);      // Color
    auto isFilled = static_cast<uint32_t>(shadows[NUM_6]);   // IsFilled
    Shadow shadow(blurRadius, spreadRadius, Offset(offsetX, offsetY), Color(color));
    shadow.SetShadowType(static_cast<ShadowType>(shadowType));
    shadow.SetIsFilled(static_cast<bool>(isFilled));
    ViewAbstract::SetBackShadow(frameNode, shadow);
}

void ResetBackShadow(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    ViewAbstract::SetBackShadow(frameNode, shadow);
}

void SetHitTestBehavior(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::HitTestMode hitTestModeNG = static_cast<NG::HitTestMode>(value);
    ViewAbstract::SetHitTestMode(frameNode, hitTestModeNG);
}

void ResetHitTestBehavior(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHitTestMode(frameNode, NG::HitTestMode::HTMDEFAULT);
}

void SetZIndex(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetZIndex(frameNode, value);
}

void ResetZIndex(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetZIndex(frameNode, 0);
}

void SetOpacity(NodeHandle node, double opacity)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetOpacity(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetAlign(NodeHandle node, int32_t align)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Alignment alignment = ParseAlignment(align);
    ViewAbstract::SetAlign(frameNode, alignment);
}

void ResetAlign(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlign(frameNode, Alignment::CENTER);
}

void SetBackdropBlur(NodeHandle node, double value)
{
    float blur = 0.0f;
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstract::SetBackdropBlur(frameNode, dimensionRadius);
}

void ResetBackdropBlur(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    double blur = 0.0;
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstract::SetBackdropBlur(frameNode, dimensionRadius);
}

void SetHueRotate(NodeHandle node, float deg)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    deg = std::fmod(deg, ROUND_UNIT);
    if (deg < 0.0f) {
        deg += ROUND_UNIT;
    }
    ViewAbstract::SetHueRotate(frameNode, deg);
}

void ResetHueRotate(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    float deg = 0.0f;
    ViewAbstract::SetHueRotate(frameNode, deg);
}

void SetInvert(NodeHandle node, double invert)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invertVariant = static_cast<float>(invert);
    ViewAbstract::SetInvert(frameNode, invertVariant);
}

void ResetInvert(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invert = 0.0f;
    ViewAbstract::SetInvert(frameNode, invert);
}

void SetSepia(NodeHandle node, double sepia)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(sepia, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSepia(frameNode, value);
}

void ResetSepia(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    ViewAbstract::SetSepia(frameNode, value);
}

void SetSaturate(NodeHandle node, double saturate)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(saturate, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSaturate(frameNode, value);
}

void ResetSaturate(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetSaturate(frameNode, value);
}

void SetColorBlend(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetColorBlend(frameNode, Color(color));
}

void ResetColorBlend(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Color colorBlend = Color::TRANSPARENT;
    ViewAbstract::SetColorBlend(frameNode, colorBlend);
}

void SetGrayscale(NodeHandle node, double grayScale)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(grayScale, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    if (GreatNotEqual(value.Value(), 1.0)) {
        value.SetValue(1.0);
    }
    ViewAbstract::SetGrayScale(frameNode, value);
}

void ResetGrayscale(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    ViewAbstract::SetGrayScale(frameNode, value);
}

void SetContrast(NodeHandle node, double contrast)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(contrast, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetContrast(frameNode, value);
}

void ResetContrast(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetContrast(frameNode, value);
}

void SetBrightness(NodeHandle node, double brightness)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(brightness, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetBrightness(frameNode, value);
}

void ResetBrightness(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetBrightness(frameNode, value);
}

void SetBlur(NodeHandle node, double value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    float blur = 0.0f;
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur);
}

void ResetBlur(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    double blur = 0.0;
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur);
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetLinearGradient(NodeHandle node, const double *values, int32_t valuesLength, const double *colors,
    int32_t colorsLength)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_4) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    SetLinearGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    ViewAbstract::SetLinearGradient(frameNode, gradient);
}

void ResetLinearGradient(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    ViewAbstract::SetLinearGradient(frameNode, gradient);
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7] : start: hasValue, start degree value
 * values[8], values[9] : end: hasValue, end degree value
 * values[10], values[11] : rotation: hasValue, rotation degree value
 * values[12] : repeating
 * @param valuesLength values length
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetSweepGradient(NodeHandle node, const double* values, int32_t valuesLength,
    const double* colors, int32_t colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_13) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    SetSweepGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    ViewAbstract::SetSweepGradient(frameNode, gradient);
}

void ResetSweepGradient(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    ViewAbstract::SetSweepGradient(frameNode, gradient);
}

/**
 * @param values value value
 * values[0], values[1], values[2] : centerX Dimension: hasValue, value, unit
 * values[3], values[4], values[5] : centerY Dimension: hasValue, value, unit
 * values[6], values[7], values[8] : radius: Dimension: hasValue, value, unit
 * values[9] : repeating
 * @param valuesLength values length
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetRadialGradient(NodeHandle node, const double* values, int32_t valuesLength,
    const double* colors, int32_t colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_10) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    SetRadialGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
}

void ResetRadialGradient(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
}

/**
 * @param text text value
 * @param options option value
 * option[0], option[1]: align(hasValue, value)
 * option[2], option[3], option[4]: offsetX(hasValue, value, unit)
 * option[5], option[6], option[7]: offsetY(hasValue, value, unit)
 * option[8]: hasOptions
 * option[9]: hasOffset
 * @param optionsLength options length
 */
void SetOverlay(NodeHandle node, const char* text, const double* options, int32_t optionsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((options == nullptr) || (optionsLength != NUM_10)) {
        return;
    }
    auto alignHasValue = options[NUM_0];
    auto alignValue = options[NUM_1];
    auto offsetXHasValue = options[NUM_2];
    auto offsetXValue = options[NUM_3];
    auto offsetXUnit = options[NUM_4];
    auto offsetYHasValue = options[NUM_5];
    auto offsetYValue = options[NUM_6];
    auto offsetYUnit = options[NUM_7];
    auto hasOptions = options[NUM_8];
    auto hasOffset = options[NUM_9];
    NG::OverlayOptions overlay;
    if (text != nullptr) {
        overlay.content = text;
    }
    if (static_cast<bool>(hasOptions)) {
        if (static_cast<bool>(alignHasValue)) {
            overlay.align = ParseAlignment(static_cast<int32_t>(alignValue));
        } else {
            overlay.align = Alignment::TOP_LEFT;
        }
        if (static_cast<bool>(hasOffset)) {
            if (static_cast<bool>(offsetXHasValue)) {
                overlay.x = CalcDimension(offsetXValue, static_cast<DimensionUnit>(offsetXUnit));
            }
            if (static_cast<bool>(offsetYHasValue)) {
                overlay.y = CalcDimension(offsetYValue, static_cast<DimensionUnit>(offsetYUnit));
            }
        }
    } else {
        overlay.align = Alignment::CENTER;
        overlay.x = CalcDimension(0);
        overlay.y = CalcDimension(0);
    }
    ViewAbstract::SetOverlay(frameNode, overlay);
}

void ResetOverlay(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OverlayOptions overlay;
    overlay.align = Alignment::TOP_LEFT;
    overlay.x = CalcDimension(0);
    overlay.y = CalcDimension(0);
    ViewAbstract::SetOverlay(frameNode, overlay);
}

/**
 * @param src source value
 * @param options option value
 * option[offset + 0], option[offset + 1], option[offset + 2]: sliceTop(hasValue, value, unit)
 * option[offset + 3], option[offset + 4], option[offset + 5]: sliceRight(hasValue, value, unit)
 * option[offset + 6], option[offset + 7], option[offset + 8]: sliceBottom(hasValue, value, unit)
 * option[offset + 9], option[offset + 10], option[offset + 11]: sliceLeft(hasValue, value, unit)
 * option[offset + 12], option[offset + 13]: repeat(hasValue, value)
 * option[offset + 14], option[offset + 15], option[offset + 16]: widthTop(hasValue, value, unit)
 * option[offset + 17], option[offset + 18], option[offset + 19]: widthRight(hasValue, value, unit)
 * option[offset + 20], option[offset + 21], option[offset + 22]: widthBottom(hasValue, value, unit)
 * option[offset + 23], option[offset + 24], option[offset + 25]: widthLeft(hasValue, value, unit)
 * option[offset + 26], option[offset + 27], option[offset + 28]: outsetTop(hasValue, value, unit)
 * option[offset + 29], option[offset + 30], option[offset + 31]: outsetRight(hasValue, value, unit)
 * option[offset + 32], option[offset + 33], option[offset + 34]: outsetBottom(hasValue, value, unit)
 * option[offset + 35], option[offset + 36], option[offset + 37]: outsetLeft(hasValue, value, unit)
 * option[offset + 38], option[offset + 39]: fill(hasValue, value)
 * option[offset + 40]: bitset
 * @param optionsLength options length
 */
void SetBorderImage(NodeHandle node, const char* src, const StringAndDouble* options, int32_t optionsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // slice:12 double, repeat:2 double, width:12 double, outset:12 double, fill:2 double, bitset:1 double
    auto desireLength = NUM_12 + NUM_2 + NUM_12 + NUM_12 + NUM_2 + NUM_1;
    if ((options == nullptr) || (optionsLength != desireLength)) {
        return;
    }
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    if (src != nullptr) {
        borderImage->SetSrc(std::string(src));
    }
    int32_t loc = 0;
    std::vector<BorderImageDirection> directions = { BorderImageDirection::TOP,
        BorderImageDirection::RIGHT, BorderImageDirection::BOTTOM, BorderImageDirection::LEFT };
    SetBorderImageSlice(borderImage, directions, options, optionsLength, loc); // read 12 double
    SetBorderImageRepeat(borderImage, options, optionsLength, loc); // read 2 double
    SetBorderImageWidth(borderImage, directions, options, optionsLength, loc); // read 12 double
    SetBorderImageOutset(borderImage, directions, options, optionsLength, loc); // read 12 double
    SetBorderImageFill(borderImage, options, optionsLength, loc); // read 2 double
    auto bitsetValue = options[loc].value;
    SetBorderImage(frameNode, borderImage, static_cast<uint8_t>(bitsetValue));
}

void ResetBorderImage(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;
    SetBorderImage(frameNode, borderImage, imageBorderBitsets);
}

void SetBorderImageGradient(NodeHandle node, const double* values, int32_t valuesLength,
    const double* colors, int32_t colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesLength != NUM_4) || ((colorsLength % NUM_3) != 0)) {
        return;
    }
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    SetBorderImageGradientValues(gradient, values, valuesLength);
    SetGradientColors(gradient, colors, colorsLength);
    ViewAbstract::SetBorderImageGradient(frameNode, gradient);
}

void SetForegroundBlurStyle(NodeHandle node, int32_t blurStyle, int32_t colorMode,
    int32_t adaptiveColor, double scale)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption fgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::BACKGROUND_ULTRA_THICK)) {
            fgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((colorMode < 0) && (adaptiveColor < 0) && (scale < 0));
    if (isHasOptions) {
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            fgBlurStyle.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            fgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        if (scale >= 0) {
            fgBlurStyle.scale = std::clamp(scale, 0.0, 1.0);
        }
    }
    ViewAbstract::SetForegroundBlurStyle(frameNode, fgBlurStyle);
}

void ResetForegroundBlurStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption styleOption;
    ViewAbstract::SetForegroundBlurStyle(frameNode, styleOption);
}

/**
 * @param blurRadius blurRadius value
 * @param stops stop value
 * stops[0], stops[1] : fractionStops pair[0]
 * stops[2], stops[3] : fractionStops pair[1] ...
 * @param stopsLength stops length
 * @param directionValue direction value
 */
void SetLinearGradientBlur(NodeHandle node, double blurRadius, const double *stops, int32_t stopsLength,
    int32_t directionValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    blurRadius = std::clamp(blurRadius, 0.0, 60.0); // 60.0 represents largest blur radius;
    std::vector<std::pair<float, float>> fractionStops;
    if ((stopsLength & 0x1) == 0) {
        float tmpPos = -1.0f;
        for (int32_t index = 0; index < stopsLength; index += NUM_2) {
            auto first = stops[index];
            auto second = stops[index + NUM_1];
            std::pair<float, float> fractionStop;
            fractionStop.first = static_cast<float>(std::clamp(first, 0.0, 1.0));
            fractionStop.second = static_cast<float>(std::clamp(second, 0.0, 1.0));
            if (fractionStop.second <= tmpPos) {
                fractionStops.clear();
                break;
            }
            tmpPos = fractionStop.second;
            fractionStops.push_back(fractionStop);
        }
    }
    if (static_cast<int32_t>(fractionStops.size()) <= 1) {
        fractionStops.clear();
        fractionStops.push_back(std::pair<float, float>(0.0f, 0.0f));
        fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    }
    if (directionValue < static_cast<int8_t>(GradientDirection::LEFT) ||
        directionValue >= static_cast<int8_t>(GradientDirection::NONE)) {
        directionValue = static_cast<int8_t>(GradientDirection::BOTTOM);
    }
    auto direction = static_cast<GradientDirection>(directionValue);
    Dimension dimensionRadius(blurRadius, DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, direction);
    ViewAbstract::SetLinearGradientBlur(frameNode, blurPara);
}

void ResetLinearGradientBlur(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 0.0f));
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    Dimension dimensionRadius(0.0f, DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, GradientDirection::BOTTOM);
    ViewAbstract::SetLinearGradientBlur(frameNode, blurPara);
}

void SetBackgroundBlurStyle(NodeHandle node, int32_t blurStyle, int32_t colorMode, int32_t adaptiveColor, double scale)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption bgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::BACKGROUND_ULTRA_THICK)) {
            bgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((colorMode < 0) && (adaptiveColor < 0) && (scale < 0));
    if (isHasOptions) {
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            bgBlurStyle.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            bgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        bgBlurStyle.scale = std::clamp(scale, 0.0, 1.0);
    }
    ViewAbstract::SetBackgroundBlurStyle(frameNode, bgBlurStyle);
}

void ResetBackgroundBlurStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption bgBlurStyle;
    ViewAbstract::SetBackgroundBlurStyle(frameNode, bgBlurStyle);
}

/**
 * @param src source borderWidthand and BorderRadius value
 * @param options option value
 * values[offset + 0], option[offset + 1], option[offset + 2]: borderWidth left(hasValue, value, unit)
 * values[offset + 3], option[offset + 4], option[offset + 5]: borderWidth right(hasValue, value, unit)
 * values[offset + 6], option[offset + 7], option[offset + 8]: borderWidth top(hasValue, value, unit)
 * values[offset + 9], option[offset + 10], option[offset + 11]: borderWidth bottom(hasValue, value, unit)
 * values[offset + 12], option[offset + 13], option[offset + 14] : BorderRadius TopLeft(hasValue, value, unit)
 * values[offset + 15], option[offset + 16], option[offset + 17] : BorderRadius TopRight(hasValue, value, unit)
 * values[offset + 18], option[offset + 19], option[offset + 20] : BorderRadius BottomLeft(hasValue, value, unit)
 * values[offset + 21], option[offset + 22], option[offset + 23] : BorderRadius BottomRight(hasValue, value, unit)
 * @param optionsLength options valuesSize
 * @param src source color and Style value
 * colorAndStyle[offset + 0], option[offset + 1]: borderColors leftColor(hasValue, value)
 * colorAndStyle[offset + 2], option[offset + 3]: borderColors rightColor(hasValue, value)
 * colorAndStyle[offset + 4], option[offset + 5]: borderColors topColor(hasValue, value)
 * colorAndStyle[offset + 6], option[offset + 7]: borderColors bottomColor(hasValue, value)
 * colorAndStyle[offset + 8], option[offset + 9]: borderStyles styleLeft(hasValue, value)
 * colorAndStyle[offset + 10], option[offset + 11]: borderStyles styleRight(hasValue, value)
 * colorAndStyle[offset + 12], option[offset + 12]: borderStyles styleTop(hasValue, value)
 * colorAndStyle[offset + 14], option[offset + 15]: borderStyles styleBottom(hasValue, value)
 * @param optionsLength options colorAndStyleSize
 */
void SetBorder(NodeHandle node,
    const double* values, int32_t valuesSize, const uint32_t* colorAndStyle, int32_t colorAndStyleSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_24) || (colorAndStyle == nullptr) || colorAndStyleSize != NUM_16) {
        return;
    }

    int32_t offset = NUM_0;
    NG::BorderWidthProperty borderWidth;

    SetOptionalBorder(borderWidth.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.bottomDimen, values, valuesSize, offset);
    borderWidth.multiValued = true;
    if (borderWidth.leftDimen.has_value() || borderWidth.rightDimen.has_value() || borderWidth.topDimen.has_value() ||
        borderWidth.bottomDimen.has_value()) {
        ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    }

    NG::BorderRadiusProperty borderRadius;
    SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, offset);

    borderRadius.multiValued = true;
    if (borderRadius.radiusTopLeft.has_value() || borderRadius.radiusTopRight.has_value() ||
        borderRadius.radiusBottomLeft.has_value() || borderRadius.radiusBottomRight.has_value()) {
        ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    }

    int32_t colorAndStyleOffset = NUM_0;
    NG::BorderColorProperty borderColors;
    SetOptionalBorderColor(borderColors.leftColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.rightColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.topColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.bottomColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    borderColors.multiValued = true;
    ViewAbstract::SetBorderColor(frameNode, borderColors);

    NG::BorderStyleProperty borderStyles;
    SetOptionalBorderStyle(borderStyles.styleLeft, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleRight, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleTop, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleBottom, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    borderStyles.multiValued = true;
    ViewAbstract::SetBorderStyle(frameNode, borderStyles);
}

void ResetBorder(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension borderWidth;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
    ViewAbstract::SetBorderRadius(frameNode, borderWidth);
    ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
}

void SetBackgroundImagePosition(NodeHandle node, const double* values, const int32_t* types, bool isAlign, int size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (size != NUM_2) {
        return;
    }
    BackgroundImagePosition bgImgPosition;
    double valueX = values[NUM_0];
    double valueY = values[NUM_1];
    DimensionUnit typeX = static_cast<OHOS::Ace::DimensionUnit>(types[NUM_0]);
    DimensionUnit typeY = static_cast<OHOS::Ace::DimensionUnit>(types[NUM_1]);
    SetBgImgPosition(typeX, typeY, valueX, valueY, bgImgPosition);
    bgImgPosition.SetIsAlign(isAlign);
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}

void ResetBackgroundImagePosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImagePosition bgImgPosition;
    SetBgImgPosition(DimensionUnit::PX, DimensionUnit::PX, 0.0, 0.0, bgImgPosition);
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}

void SetBackgroundImageSize(NodeHandle node,
    double valueWidth, double valueHeight, int32_t typeWidth, int32_t typeHeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeWidth));
    bgImgSize.SetSizeValueX(valueWidth);
    bgImgSize.SetSizeTypeY(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeHeight));
    bgImgSize.SetSizeValueY(valueHeight);
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void ResetBackgroundImageSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
    bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void SetBackgroundImage(NodeHandle node, const char* src, const char* bundle, const char* module, int32_t repeatIndex)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr(src);
    std::string bundleStr(bundle);
    std::string moduleStr(module);
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { srcStr, bundleStr, moduleStr });
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    if (repeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && repeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, repeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
}

void ResetBackgroundImage(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr;
    std::string bundle;
    std::string module;
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { srcStr, bundle, module });
    ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
}
void SetTranslate(NodeHandle node, const double* values, const int* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != NUM_3) {
        return;
    }
    auto translateX = CalcDimension(0.0);
    auto translateY = CalcDimension(0.0);
    auto translateZ = CalcDimension(0.0);
    translateX = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    translateY = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    translateZ = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));

    ViewAbstract::SetTranslate(frameNode, TranslateOptions(translateX, translateY, translateZ));
}

void ResetTranslate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto x = CalcDimension(0.0);
    auto y = CalcDimension(0.0);
    auto z = CalcDimension(0.0);
    ViewAbstract::SetTranslate(frameNode, TranslateOptions(x, y, z));
}
/**
 * @param values
 * values[0] : centerX value; values[1] : centerY value;
 * units[0] : centerY unit; units[1] : centerY unit
 * values[2]: scaleX;values[3]: scaleY;values[4]: scaleZ
 * @param length shadows length
 */
void SetScale(NodeHandle node, const double* values, int valLength, const int* units, int unitLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (valLength != NUM_5 || unitLength != NUM_2) {
        return;
    }
    auto x = values[NUM_2];
    auto y = values[NUM_3];
    // NOT support Z in source code
    if (x < 0) {
        x = 1;
    }
    if (y < 0) {
        y = 1;
    }
    VectorF scale(x, y);
    ViewAbstract::SetScale(frameNode, scale);

    auto centerX = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    auto centerY = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    auto centerZ = Dimension(0.0, OHOS::Ace::DimensionUnit::VP);

    DimensionOffset center(centerX, centerY);
    if (!NearZero(centerZ.Value())) {
        center.SetZ(centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

void ResetScale(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(frameNode, scale);

    DimensionOffset center(0.5_pct, 0.5_pct);
    auto centerZ = Dimension(0.0, OHOS::Ace::DimensionUnit::VP);
    if (!NearZero(centerZ.Value())) {
        center.SetZ(centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

/**
 * @param values
 * values[0] : centerX value; values[1] : centerY value; values[3] : centerZ value
 * units[0] : centerY unit; units[1] : centerY unit; units[3] : centerZ unit
 * values[4]: xDirection;values[5]: yDirection;values[6]: zDirection
 * values[7]: angle;values[8]:perspective
 * @param length shadows length
 */
void SetRotate(NodeHandle node, const double* values, int32_t valLength, const int* units, int32_t unitLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (valLength != NUM_8 || unitLength != NUM_3) {
        return;
    }
    auto centerX = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    auto centerY = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    auto centerZ = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    auto xDirection = values[NUM_3];
    auto yDirection = values[NUM_4];
    auto zDirection = values[NUM_5];
    auto angle = values[NUM_6];
    auto perspective = values[NUM_7];
    ViewAbstract::SetRotate(frameNode, NG::Vector5F(xDirection, yDirection, zDirection, angle, perspective));

    DimensionOffset center(centerX, centerY);
    if (!NearZero(centerZ.Value())) {
        center.SetZ(centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

void ResetRotate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct, 0.0f, 0.0f);
    ViewAbstract::SetRotate(frameNode,
        NG::Vector5F(rotate.xDirection, rotate.yDirection, rotate.zDirection, 0.0, rotate.perspective));

    DimensionOffset center(rotate.centerX, rotate.centerY);
    if (!NearZero(rotate.centerZ.Value())) {
        center.SetZ(rotate.centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

void SetGeometryTransition(NodeHandle node, const char* id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string idStr(id);
    ViewAbstract::SetGeometryTransition(frameNode, idStr, false);
}

void ResetGeometryTransition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetOffset(NodeHandle node, const double *number, const int8_t *unit)
{
    CHECK_NULL_VOID(number);
    CHECK_NULL_VOID(unit);
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xVal(*(number + 0), static_cast<DimensionUnit>(*(unit + 0)));
    Dimension yVal(*(number + 1), static_cast<DimensionUnit>(*(unit + 1)));
    ViewAbstract::SetOffset(frameNode, { xVal, yVal });
}

void ResetOffset(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xVal(0.0, DimensionUnit::VP);
    Dimension yVal(0.0, DimensionUnit::VP);
    ViewAbstract::SetOffset(frameNode, { xVal, yVal });
}
void SetPadding(NodeHandle node, const struct ArkUISizeType *top, const struct ArkUISizeType *right,
    const struct ArkUISizeType *bottom, const struct ArkUISizeType *left)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    if (top->string != nullptr) {
        topDimen = CalcLength(top->string);
    } else {
        topDimen = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDimen = CalcLength(right->string);
    } else {
        rightDimen = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDimen = CalcLength(bottom->string);
    } else {
        bottomDimen = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDimen = CalcLength(left->string);
    } else {
        leftDimen = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    ViewAbstract::SetPadding(frameNode, paddings);
}

void ResetPadding(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    ViewAbstract::SetPadding(frameNode, paddings);
}

/**
 * @param values value value
 * values[0] : left, values[1] : top, values[2] : right, values[3] : bottom
 * @param units unit value
 * units[0] : left, units[1] : top, units[2] : right, units[3] : bottom
 * @param length values length
 */
void SetPixelStretchEffect(NodeHandle node, const double* values, const int* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != NUM_4) {
        return;
    }
    auto leftValue = values[NUM_0];
    auto leftUnit = units[NUM_0];
    auto topValue = values[NUM_1];
    auto topUnit = units[NUM_1];
    auto rightValue = values[NUM_2];
    auto rightUnit = units[NUM_2];
    auto bottomValue = values[NUM_3];
    auto bottomUnit = units[NUM_3];
    Dimension left(leftValue, static_cast<DimensionUnit>(leftUnit));
    Dimension top(topValue, static_cast<DimensionUnit>(topUnit));
    Dimension right(rightValue, static_cast<DimensionUnit>(rightUnit));
    Dimension bottom(bottomValue, static_cast<DimensionUnit>(bottomUnit));
    bool illegalInput = false;
    if (left.Unit() == DimensionUnit::PERCENT || right.Unit() == DimensionUnit::PERCENT ||
        top.Unit() == DimensionUnit::PERCENT || bottom.Unit() == DimensionUnit::PERCENT) {
        if ((NearEqual(left.Value(), 0.0) || left.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(top.Value(), 0.0) || top.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(right.Value(), 0.0) || right.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(bottom.Value(), 0.0) || bottom.Unit() == DimensionUnit::PERCENT)) {
            left.SetUnit(DimensionUnit::PERCENT);
            top.SetUnit(DimensionUnit::PERCENT);
            right.SetUnit(DimensionUnit::PERCENT);
            bottom.SetUnit(DimensionUnit::PERCENT);
        } else {
            illegalInput = true;
        }
    }
    PixStretchEffectOption option;
    if ((left.IsNonNegative() && top.IsNonNegative() && right.IsNonNegative() && bottom.IsNonNegative()) ||
        (left.IsNonPositive() && top.IsNonPositive() && right.IsNonPositive() && bottom.IsNonPositive())) {
        option.left = left;
        option.top = top;
        option.right = right;
        option.bottom = bottom;
    } else {
        illegalInput = true;
    }
    if (illegalInput) {
        option.ResetValue();
    }
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
}

void ResetPixelStretchEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
}

void SetLightUpEffect(NodeHandle node, double radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    radio = std::clamp(radio, 0.0, 1.0);
    ViewAbstract::SetLightUpEffect(frameNode, radio);
}

void ResetLightUpEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightUpEffect(frameNode, 1.0);
}

void SetSphericalEffect(NodeHandle node, double radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    radio = std::clamp(radio, 0.0, 1.0);
    ViewAbstract::SetSphericalEffect(frameNode, radio);
}

void ResetSphericalEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSphericalEffect(frameNode, 0.0);
}

void SetRenderGroup(NodeHandle node, bool isRenderGroup)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderGroup(frameNode, isRenderGroup);
}

void ResetRenderGroup(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderGroup(frameNode, false);
}

void SetRenderFit(NodeHandle node, int32_t renderFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderFit = RenderFit::TOP_LEFT;
    if (renderFitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
        renderFitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
        renderFit = static_cast<RenderFit>(renderFitNumber);
    }
    ViewAbstract::SetRenderFit(frameNode, renderFit);
}

void ResetRenderFit(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderFit(frameNode, RenderFit::TOP_LEFT);
}

void SetUseEffect(NodeHandle node, bool useEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetUseEffect(frameNode, useEffect);
}

void ResetUseEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetUseEffect(frameNode, false);
}

void SetForegroundColor(NodeHandle node, bool isColor, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isColor) {
        ViewAbstract::SetForegroundColor(frameNode, Color(color));
    } else {
        auto strategy = static_cast<ForegroundColorStrategy>(color);
        ViewAbstract::SetForegroundColorStrategy(frameNode, strategy);
    }
}

void ResetForegroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}


void SetMotionPath(NodeHandle node, const char* path, float from, float to, bool rotatable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::MotionPathOption motionPathOption;
    std::string pathString = path;
    motionPathOption.SetPath(pathString);
    motionPathOption.SetBegin(from);
    motionPathOption.SetEnd(to);
    motionPathOption.SetRotate(rotatable);
    ViewAbstract::SetMotionPath(frameNode, motionPathOption);
}

void ResetMotionPath(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::MotionPathOption motionPathOption = MotionPathOption();
    ViewAbstract::SetMotionPath(frameNode, motionPathOption);
}

void SetGroupDefaultFocus(NodeHandle node, bool groupDefaultFocus)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGroupDefaultFocus(frameNode, groupDefaultFocus);
}

void ResetGroupDefaultFocus(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool groupDefaultFocus = false;
    ViewAbstract::SetGroupDefaultFocus(frameNode, groupDefaultFocus);
}

void SetFocusOnTouch(NodeHandle node, bool focusOnTouch)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusOnTouch(frameNode, focusOnTouch);
}

void ResetFocusOnTouch(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool focusOnTouch = false;
    ViewAbstract::SetFocusOnTouch(frameNode, focusOnTouch);
}
void SetFocusable(NodeHandle node, bool focusable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, focusable);
}

void ResetFocusable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool focusable = false;
    ViewAbstract::SetFocusable(frameNode, focusable);
}

void SetTouchable(NodeHandle node, bool touchable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTouchable(frameNode, touchable);
}

void ResetTouchable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool touchable = true;
    ViewAbstract::SetTouchable(frameNode, touchable);
}

void SetDefaultFocus(NodeHandle node, bool defaultFocus)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDefaultFocus(frameNode, defaultFocus);
}

void ResetDefaultFocus(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool defaultFocus = false;
    ViewAbstract::SetDefaultFocus(frameNode, defaultFocus);
}

void SetDisplayPriority(NodeHandle node, double value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDisplayIndex(frameNode, static_cast<int32_t>(value));
}

void ResetDisplayPriority(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDisplayIndex(frameNode, DEFAULT_DISPLAY_PRIORITY);
}

void SetMargin(NodeHandle node, const struct ArkUISizeType *top, const struct ArkUISizeType *right,
    const struct ArkUISizeType *bottom, const struct ArkUISizeType *left)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    if (top->string != nullptr) {
        topDimen = CalcLength(top->string);
    } else {
        topDimen = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDimen = CalcLength(right->string);
    } else {
        rightDimen = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDimen = CalcLength(bottom->string);
    } else {
        bottomDimen = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDimen = CalcLength(left->string);
    } else {
        leftDimen = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    ViewAbstract::SetMargin(frameNode, paddings);
}

void ResetMargin(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetMargin(frameNode, NG::CalcLength(0.0));
}

void SetMarkAnchor(NodeHandle node, double xValue, int32_t xUnit, double yValue, int32_t yUnit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xDimension { xValue, static_cast<DimensionUnit>(xUnit) };
    Dimension yDimension { yValue, static_cast<DimensionUnit>(yUnit) };
    OffsetT<Dimension> value = { xDimension, yDimension };
    ViewAbstract::MarkAnchor(frameNode, value);
}

void ResetMarkAnchor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::MarkAnchor(frameNode, { Dimension(0.0_vp), Dimension(0.0_vp) });
}

void SetVisibility(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType value_visibleType = static_cast<VisibleType>(value);
    ViewAbstract::SetVisibility(frameNode, value_visibleType);
}

void ResetVisibility(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, DEFAULT_VISIBILITY);
}

void SetAccessibilityText(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityText(frameNode, valueStr);
}

void ResetAccessibilityText(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityText(frameNode, "");
}

void SetAllowDrop(NodeHandle node, const char** allowDropCharArray, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::set<std::string> allowDropSet;
    allowDropSet.clear();
    std::string allowDropStr;
    for (int32_t i = 0; i < length; i++) {
        allowDropStr = allowDropCharArray[i];
        allowDropSet.insert(allowDropStr);
    }
    ViewAbstract::SetAllowDrop(frameNode, allowDropSet);
}

void ResetAllowDrop(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::set<std::string> allowDrop;
    ViewAbstract::SetAllowDrop(frameNode, allowDrop);
}

void SetAccessibilityLevel(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, valueStr);
}

void ResetAccessibilityLevel(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, "");
}

void SetDirection(NodeHandle node, int32_t direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutDirection(frameNode, static_cast<TextDirection>(direction));
}

void ResetDirection(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutDirection(frameNode, DEFAULT_COMMON_DIRECTION);
}

void SetLayoutWeight(NodeHandle node, int32_t layoutWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutWeight(frameNode, layoutWeight);
}

void ResetLayoutWeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutWeight(frameNode, DEFAULT_COMMON_LAYOUTWEIGHT);
}

void SetMinWidth(NodeHandle node, const struct ArkUISizeType *minWidth)
{
    CHECK_NULL_VOID(minWidth);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result(minWidth->value, static_cast<DimensionUnit>(minWidth->unit));
    ViewAbstract::SetMinWidth(frameNode, CalcLength(result));
}

void ResetMinWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMinSize(frameNode, true);
}

void SetMaxWidth(NodeHandle node, const struct ArkUISizeType* maxWidth)
{
    CHECK_NULL_VOID(maxWidth);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result(maxWidth->value, static_cast<DimensionUnit>(maxWidth->unit));
    ViewAbstract::SetMaxWidth(frameNode, CalcLength(result));
}

void ResetMaxWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMaxSize(frameNode, true);
}

void SetMinHeight(NodeHandle node, const struct ArkUISizeType* minHeight)
{
    CHECK_NULL_VOID(minHeight);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result(minHeight->value, static_cast<DimensionUnit>(minHeight->unit));
    ViewAbstract::SetMinHeight(frameNode, CalcLength(result));
}

void ResetMinHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMinSize(frameNode, false);
}

void SetMaxHeight(NodeHandle node, const struct ArkUISizeType* maxHeight)
{
    CHECK_NULL_VOID(maxHeight);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result(maxHeight->value, static_cast<DimensionUnit>(maxHeight->unit));
    ViewAbstract::SetMaxHeight(frameNode, CalcLength(result));
}

void ResetMaxHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMaxSize(frameNode, false);
}

void SetSize(NodeHandle node, const double* number, const int8_t* unit, const char** calc)
{
    CHECK_NULL_VOID(number);
    CHECK_NULL_VOID(unit);
    int widthIndex = 0, heightIndex = 1;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (*(unit + widthIndex) == static_cast<int8_t>(DimensionUnit::CALC) && *(calc + widthIndex) != nullptr) {
        ViewAbstract::SetWidth(frameNode, CalcLength(std::string(*(calc + widthIndex))));
    } else {
        ViewAbstract::SetWidth(
            frameNode, CalcLength(*(number + widthIndex), static_cast<DimensionUnit>(*(unit + widthIndex))));
    }
    if (*(unit + heightIndex) == static_cast<int8_t>(DimensionUnit::CALC) && *(calc + heightIndex) != nullptr) {
        ViewAbstract::SetHeight(frameNode, CalcLength(std::string(*(calc + heightIndex))));
    } else {
        ViewAbstract::SetHeight(
            frameNode, CalcLength(*(number + heightIndex), static_cast<DimensionUnit>(*(unit + heightIndex))));
    }
}

void ResetSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetWidth(frameNode, CalcLength(0.0, DimensionUnit::VP));
    ViewAbstract::SetHeight(frameNode, CalcLength(0.0, DimensionUnit::VP));
}

void ClearWidthOrHeight(NodeHandle node, bool isWidth)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
}

void SetAlignSelf(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= MAX_ALIGN_VALUE) {
        ViewAbstract::SetAlignSelf(frameNode, static_cast<FlexAlign>(value));
    } else {
        ViewAbstract::SetAlignSelf(frameNode, FlexAlign::AUTO);
    }
}

void ResetAlignSelf(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlignSelf(frameNode, FlexAlign::AUTO);
}

void SetAspectRatio(NodeHandle node, double value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    double result = value;
    if (LessOrEqual(result, 0.0)) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            ViewAbstract::ResetAspectRatio(frameNode);
            return;
        } else {
            result = 1.0;
        }
    }

    ViewAbstract::SetAspectRatio(frameNode, static_cast<float>(result));
}

void ResetAspectRatio(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ViewAbstract::ResetAspectRatio(frameNode);
    } else {
        ViewAbstract::SetAspectRatio(frameNode, static_cast<float>(1.0));
    }
}

void SetFlexGrow(NodeHandle node, double value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    double result = value;
    if (result < 0.0) {
        result = 0.0;
    }
    ViewAbstract::SetFlexGrow(frameNode, static_cast<float>(result));
}

void ResetFlexGrow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexGrow(static_cast<float>(0.0));
}

void SetFlexShrink(NodeHandle node, double value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (value < 0.0) {
        ViewAbstract::ResetFlexShrink(frameNode);
        return;
    }
    ViewAbstract::SetFlexShrink(frameNode, static_cast<float>(value));
}

void ResetFlexShrink(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetFlexShrink(frameNode);
}

void SetGridOffset(NodeHandle node, int32_t offset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, std::nullopt, offset, GridSizeType::UNDEFINED);
}

void ResetGridOffset(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, std::nullopt, DEFAULT_GRID_OFFSET, GridSizeType::UNDEFINED);
}

void SetGridSpan(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, value, std::nullopt);
}

void ResetGridSpan(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, DEFAULT_GRIDSPAN, std::nullopt);
}

void SetExpandSafeArea(NodeHandle node, const char* typeStr, const char* edgesStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts {
        .type = NG::SAFE_AREA_TYPE_ALL,
        .edges = NG::SAFE_AREA_EDGE_ALL
    };
    uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    std::string safeAreaTypeStr = std::string(typeStr);
    std::string safeAreaEdgeStr = std::string(edgesStr);
    std::string delimiter = "|";
    size_t pos = 0;
    std::string type;
    std::string edges;
    while ((pos = safeAreaTypeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaTypeStr.substr(0, pos);
        safeAreaType |= StringUtils::StringToInt(type);
        safeAreaTypeStr.erase(0, pos + delimiter.length());
    }
    safeAreaType |= StringUtils::StringToInt(safeAreaTypeStr);
    while ((pos = safeAreaEdgeStr.find(delimiter)) != std::string::npos) {
        edges = safeAreaEdgeStr.substr(0, pos);
        safeAreaEdge |= StringUtils::StringToInt(edges);
        safeAreaEdgeStr.erase(0, pos + delimiter.length());
    }
    safeAreaEdge |= StringUtils::StringToInt(safeAreaEdgeStr);
    opts.type = safeAreaType;
    opts.edges = safeAreaEdge;
    ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}

void ResetExpandSafeArea(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts;
    opts.type = DEFAULT_SAFE_AREA_TYPE;
    opts.edges = DEFAULT_SAFE_AREA_EDGE;
    ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}

void SetFlexBasis(NodeHandle node, const struct StringAndDouble* flexBasisValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension result;
    if (flexBasisValue->valueStr != nullptr) {
        result = StringUtils::StringToDimensionWithUnit(std::string(flexBasisValue->valueStr), DimensionUnit::VP);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            // flexbasis don't support percent case.
            if (result.Unit() == DimensionUnit::PERCENT) {
                result.SetUnit(DimensionUnit::AUTO);
            }
        }
    } else {
        result = Dimension(flexBasisValue->value, DimensionUnit::VP);
    }
    ViewAbstract::SetFlexBasis(frameNode, result);
}

void ResetFlexBasis(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexBasis(frameNode, DEFAULT_FLEX_BASIS);
}

void SetAlignRules(NodeHandle node, char** anchors, int8_t* direction, int32_t length)
{
    CHECK_NULL_VOID(anchors);
    CHECK_NULL_VOID(direction);
    if (length != DEFAULT_ALIGN_RULES_SIZE) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::map<AlignDirection, AlignRule> rulesMap;
    for (int index = 0; index < length; index++) {
        AlignRule alignRule;
        alignRule.anchor = std::string(*(anchors + index) == nullptr ? "" : *(anchors + index));
        if (index < HORIZONTAL_DIRECTION_RANGE) {
            alignRule.horizontal = static_cast<HorizontalAlign>(*(direction + index));
        } else {
            alignRule.vertical = static_cast<VerticalAlign>(*(direction + index));
        }
        rulesMap[static_cast<AlignDirection>(index)] = alignRule;
    }
    ViewAbstract::SetAlignRules(frameNode, rulesMap);
}

void ResetAlignRules(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const char* keys[] = { "left", "middle", "right", "top", "center", "bottom" };
    std::map<AlignDirection, AlignRule> alignRules;
    for (uint32_t i = 0; i < sizeof(keys) / sizeof(const char *); i++) {
        AlignRule alignRule;
        alignRule.anchor = "__container__";
        alignRule.horizontal = static_cast<HorizontalAlign>(DEFAULT_ALIGN_VALUE);
        alignRule.vertical = static_cast<VerticalAlign>(DEFAULT_ALIGN_VALUE);
        alignRules[static_cast<AlignDirection>(i)] = alignRule;
    }
    ViewAbstract::SetAlignRules(frameNode, alignRules);
}

void SetAccessibilityDescription(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, valueStr);
}

void ResetAccessibilityDescription(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, "");
}

void SetId(NodeHandle node, const char* id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = id;
    ViewAbstract::SetInspectorId(frameNode, valueStr);
}

void ResetId(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string id = "";
    ViewAbstract::SetInspectorId(frameNode, id);
}

void SetKey(NodeHandle node, const char* key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = key;
    ViewAbstract::SetInspectorId(frameNode, valueStr);
}

void ResetKey(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string key = "";
    ViewAbstract::SetInspectorId(frameNode, key);
}

void SetRestoreId(NodeHandle node, uint32_t id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRestoreId(frameNode, id);
}

void ResetRestoreId(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRestoreId(frameNode, DEFAULT_ID);
}

void SetTabIndex(NodeHandle node, int32_t index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTabIndex(frameNode, index);
}

void ResetTabIndex(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t index = 0;
    ViewAbstract::SetTabIndex(frameNode, index);
}

void SetObscured(NodeHandle node, const int32_t* reason, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ObscuredReasons> reasons(length);
    reasons.clear();
    for (int32_t i = 0; i < length; i++) {
            reasons.emplace_back(static_cast<ObscuredReasons>(reason[i]));
    }

    ViewAbstract::SetObscured(frameNode, reasons);
}

void ResetObscured(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ObscuredReasons> reasons(0);
    ViewAbstract::SetObscured(frameNode, reasons);
}

void SetResponseRegion(NodeHandle node, const double* values, const int32_t* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (int32_t i = 0; i < length / NUM_4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * NUM_4 + NUM_0], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_0]));
        CalcDimension yDimen =
            CalcDimension(values[i * NUM_4 + NUM_1], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_1]));
        CalcDimension widthDimen =
            CalcDimension(values[i * NUM_4 + NUM_2], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i * NUM_4 + NUM_3], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    ViewAbstract::SetResponseRegion(frameNode, region);
}

void ResetResponseRegion(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    ViewAbstract::SetResponseRegion(frameNode, region);
}

void SetMouseResponseRegion(NodeHandle node, const double* values, const int32_t* units, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (int32_t i = 0; i < length / NUM_4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * NUM_4 + NUM_0], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_0]));
        CalcDimension yDimen =
            CalcDimension(values[i * NUM_4 + NUM_1], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_1]));
        CalcDimension widthDimen =
            CalcDimension(values[i * NUM_4 + NUM_2], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i * NUM_4 + NUM_3], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    ViewAbstract::SetMouseResponseRegion(frameNode, region);
}

void ResetMouseResponseRegion(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    ViewAbstract::SetMouseResponseRegion(frameNode, region);
}

void SetEnabled(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, value);
}

void ResetEnabled(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, true);
}

void SetDraggable(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, value);
}

void ResetDraggable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, false);
}

void SetAccessibilityGroup(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, value);
}

void ResetAccessibilityGroup(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, false);
}

void SetHoverEffect(NodeHandle node, int32_t hoverEffectValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::HoverEffectType hoverEffect = OHOS::Ace::HoverEffectType::AUTO;
    hoverEffect = static_cast<OHOS::Ace::HoverEffectType>(hoverEffectValue);
    ViewAbstract::SetHoverEffect(frameNode, hoverEffect);
}

void ResetHoverEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHoverEffect(frameNode, OHOS::Ace::HoverEffectType::AUTO);
}

void SetClickEffect(NodeHandle node, const int32_t levelValue, float scaleValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::ClickEffectLevel level = OHOS::Ace::ClickEffectLevel::UNDEFINED;
    level = static_cast<OHOS::Ace::ClickEffectLevel>(levelValue);
    ViewAbstract::SetClickEffectLevel(frameNode, level, scaleValue);
}

void ResetClickEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClickEffectLevel(frameNode, OHOS::Ace::ClickEffectLevel::UNDEFINED, 0.9f);
}

void SetKeyBoardShortCut(NodeHandle node, const char* value, const int32_t* keysIntArray, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = value;
    std::vector<OHOS::Ace::ModifierKey> keysVector(length);
    keysVector.clear();
    for (int32_t i = 0; i < length; i++) {
        keysVector.emplace_back(static_cast<OHOS::Ace::ModifierKey>(keysIntArray[i]));
    }
    ViewAbstractModelNG::SetKeyboardShortcut(frameNode, valueStr, keysVector, nullptr);
}

void ResetKeyBoardShortCut(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetKeyboardShortcut(frameNode, "", std::vector<OHOS::Ace::ModifierKey>(), nullptr);
}
ArkUICommonModifierAPI GetCommonModifier()
{
    static const ArkUICommonModifierAPI modifier = { SetBackgroundColor, ResetBackgroundColor, SetWidth, ResetWidth,
        SetHeight, ResetHeight, SetBorderRadius, ResetBorderRadius, SetBorderWidth, ResetBorderWidth, SetTransform,
        ResetTransform, SetBorderColor, ResetBorderColor, SetPosition, ResetPosition, SetBorderStyle, ResetBorderStyle,
        SetBackShadow, ResetBackShadow, SetHitTestBehavior, ResetHitTestBehavior, SetZIndex, ResetZIndex, SetOpacity,
        ResetOpacity, SetAlign, ResetAlign, SetBackdropBlur, ResetBackdropBlur, SetHueRotate, ResetHueRotate, SetInvert,
        ResetInvert, SetSepia, ResetSepia, SetSaturate, ResetSaturate, SetColorBlend, ResetColorBlend, SetGrayscale,
        ResetGrayscale, SetContrast, ResetContrast, SetBrightness, ResetBrightness, SetBlur, ResetBlur,
        SetLinearGradient, ResetLinearGradient, SetSweepGradient, ResetSweepGradient, SetRadialGradient,
        ResetRadialGradient,
        SetOverlay, ResetOverlay,
        SetBorderImage, ResetBorderImage, SetBorderImageGradient,
        SetForegroundBlurStyle, ResetForegroundBlurStyle, SetLinearGradientBlur,
        ResetLinearGradientBlur, SetBackgroundBlurStyle, ResetBackgroundBlurStyle, SetBorder, ResetBorder,
        SetBackgroundImagePosition, ResetBackgroundImagePosition, SetBackgroundImageSize, ResetBackgroundImageSize,
        SetBackgroundImage, ResetBackgroundImage, SetTranslate, ResetTranslate, SetScale, ResetScale, SetRotate,
        ResetRotate, SetGeometryTransition, ResetGeometryTransition,
        SetPixelStretchEffect, ResetPixelStretchEffect,
        SetLightUpEffect, ResetLightUpEffect,
        SetSphericalEffect, ResetSphericalEffect,
        SetRenderGroup, ResetRenderGroup,
        SetRenderFit, ResetRenderFit,
        SetUseEffect, ResetUseEffect,
        SetForegroundColor, ResetForegroundColor, SetMotionPath, ResetMotionPath,
        SetGroupDefaultFocus, ResetGroupDefaultFocus, SetFocusOnTouch, ResetFocusOnTouch, SetFocusable,
        ResetFocusable, SetTouchable, ResetTouchable, SetDefaultFocus, ResetDefaultFocus,
        SetDisplayPriority, ResetDisplayPriority, SetOffset, ResetOffset,
        SetPadding, ResetPadding, SetMargin, ResetMargin, SetMarkAnchor, ResetMarkAnchor,
        SetVisibility, ResetVisibility, SetAccessibilityText, ResetAccessibilityText,
        SetAllowDrop, ResetAllowDrop, SetAccessibilityLevel, ResetAccessibilityLevel,
        SetDirection, ResetDirection, SetLayoutWeight, ResetLayoutWeight,
        SetMinWidth, ResetMinWidth, SetMaxWidth, ResetMaxWidth, SetMinHeight, ResetMinHeight, SetMaxHeight,
        ResetMaxHeight, SetSize, ResetSize, ClearWidthOrHeight, SetAlignSelf, ResetAlignSelf,
        SetAspectRatio, ResetAspectRatio, SetFlexGrow, ResetFlexGrow, SetFlexShrink, ResetFlexShrink,
        SetGridOffset, ResetGridOffset, SetGridSpan, ResetGridSpan, SetExpandSafeArea, ResetExpandSafeArea,
        SetFlexBasis, ResetFlexBasis, SetAlignRules, ResetAlignRules,
        SetAccessibilityDescription, ResetAccessibilityDescription, SetId, ResetId, SetKey, ResetKey, SetRestoreId,
        ResetRestoreId, SetTabIndex, ResetTabIndex, SetObscured, ResetObscured, SetResponseRegion, ResetResponseRegion,
        SetMouseResponseRegion, ResetMouseResponseRegion, SetEnabled, ResetEnabled,
        SetDraggable, ResetDraggable, SetAccessibilityGroup, ResetAccessibilityGroup, SetHoverEffect, ResetHoverEffect,
        SetClickEffect, ResetClickEffect, SetKeyBoardShortCut, ResetKeyBoardShortCut};

    return modifier;
}
} // namespace OHOS::Ace::NG
