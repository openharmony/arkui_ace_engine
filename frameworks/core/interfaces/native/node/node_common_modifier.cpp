/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_common_modifier.h"

#include "interfaces/native/node/node_model.h"

#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curves.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/axis_event.h"
#include "core/image/image_source_info.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_drag_modifier.h"
#include "core/interfaces/native/node/touch_event_convertor.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr VisibleType DEFAULT_VISIBILITY = static_cast<VisibleType>(0);
constexpr float MAX_ANGLE = 360.0f;
constexpr float DEFAULT_ANGLE = 180.0f;
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
constexpr int NUM_36 = 36;
constexpr int DEFAULT_LENGTH = 4;
constexpr double ROUND_UNIT = 360.0;
constexpr TextDirection DEFAULT_COMMON_DIRECTION = TextDirection::AUTO;
constexpr int32_t DEFAULT_COMMON_LAYOUTWEIGHT = 0;
constexpr int32_t MAX_ALIGN_VALUE = 8;
// default gridSpan is 1 on doc
constexpr int32_t DEFAULT_GRIDSPAN = 1;
constexpr uint32_t DEFAULT_ALIGN_RULES_SIZE = 6;
constexpr uint8_t DEFAULT_SAFE_AREA_TYPE = 0b111;
constexpr uint8_t DEFAULT_SAFE_AREA_EDGE = 0b1111;
constexpr Dimension DEFAULT_FLEX_BASIS { 0.0, DimensionUnit::AUTO };
constexpr int32_t DEFAULT_DISPLAY_PRIORITY = 0;
constexpr int32_t DEFAULT_ID = 0;
constexpr int32_t X_INDEX = 0;
constexpr int32_t Y_INDEX = 1;
constexpr int32_t Z_INDEX = 2;
constexpr int32_t ARRAY_SIZE = 3;
constexpr float HALF = 0.5f;
constexpr float DEFAULT_BIAS = 0.5f;
constexpr float DEFAULT_SATURATE = 1.0f;
constexpr float DEFAULT_BRIGHTNESS = 1.0f;
constexpr int32_t OUTLINE_LEFT_WIDTH_INDEX = 0;
constexpr int32_t OUTLINE_TOP_WIDTH_INDEX = 1;
constexpr int32_t OUTLINE_RIGHT_WIDTH_INDEX = 2;
constexpr int32_t OUTLINE_BOTTOM_WIDTH_INDEX = 3;
constexpr int32_t OUTLINE_WIDTH_VECTOR_SIZE = 4;
const int32_t ERROR_INT_CODE = -1;
const double DEFAULT_DASH_DIMENSION = -1;
const float ERROR_FLOAT_CODE = -1.0f;
constexpr int32_t MAX_POINTS = 10;
constexpr int32_t MAX_HISTORY_EVENT_COUNT = 20;
const std::vector<OHOS::Ace::RefPtr<OHOS::Ace::Curve>> CURVES = {
    OHOS::Ace::Curves::LINEAR,
    OHOS::Ace::Curves::EASE,
    OHOS::Ace::Curves::EASE_IN,
    OHOS::Ace::Curves::EASE_OUT,
    OHOS::Ace::Curves::EASE_IN_OUT,
    OHOS::Ace::Curves::FAST_OUT_SLOW_IN,
    OHOS::Ace::Curves::LINEAR_OUT_SLOW_IN,
    OHOS::Ace::Curves::FAST_OUT_LINEAR_IN,
    OHOS::Ace::Curves::EXTREME_DECELERATION,
    OHOS::Ace::Curves::SHARP,
    OHOS::Ace::Curves::RHYTHM,
    OHOS::Ace::Curves::SMOOTH,
    OHOS::Ace::Curves::FRICTION,
};

enum TransitionEffectType {
    TRANSITION_EFFECT_OPACITY = 0,
    TRANSITION_EFFECT_TRANSLATE,
    TRANSITION_EFFECT_SCALE,
    TRANSITION_EFFECT_ROTATE,
    TRANSITION_EFFECT_MOVE,
    TRANSITION_EFFECT_ASYMMETRIC,
};

const std::vector<AnimationDirection> DIRECTION_LIST = {
    AnimationDirection::NORMAL,
    AnimationDirection::REVERSE,
    AnimationDirection::ALTERNATE,
    AnimationDirection::ALTERNATE_REVERSE,
};

constexpr int32_t DEFAULT_DURATION = 1000;
std::string g_strValue;

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

int32_t ConvertAlignmentToInt(Alignment alignment)
{
    if (alignment == Alignment::TOP_LEFT) {
        return NUM_0;
    }
    if (alignment == Alignment::TOP_CENTER) {
        return NUM_1;
    }
    if (alignment == Alignment::TOP_RIGHT) {
        return NUM_2;
    }
    if (alignment == Alignment::CENTER_LEFT) {
        return NUM_3;
    }
    if (alignment == Alignment::CENTER) {
        return NUM_4;
    }
    if (alignment == Alignment::CENTER_RIGHT) {
        return NUM_5;
    }
    if (alignment == Alignment::BOTTOM_LEFT) {
        return NUM_6;
    }
    if (alignment == Alignment::BOTTOM_CENTER) {
        return NUM_7;
    }
    if (alignment == Alignment::BOTTOM_RIGHT) {
        return NUM_8;
    }
    return NUM_4;
}

int32_t ParseAlignmentToIndex(Alignment align)
{
    if (align == Alignment::TOP_LEFT) {
        return NUM_0;
    }
    if (align == Alignment::TOP_CENTER) {
        return NUM_1;
    }
    if (align == Alignment::TOP_RIGHT) {
        return NUM_2;
    }
    if (align == Alignment::CENTER_LEFT) {
        return NUM_3;
    }
    if (align == Alignment::CENTER) {
        return NUM_4;
    }
    if (align == Alignment::CENTER_RIGHT) {
        return NUM_5;
    }
    if (align == Alignment::BOTTOM_LEFT) {
        return NUM_6;
    }
    if (align == Alignment::BOTTOM_CENTER) {
        return NUM_7;
    }
    if (align == Alignment::BOTTOM_RIGHT) {
        return NUM_8;
    }
    return ERROR_INT_CODE;
}

/**
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetGradientColors(NG::Gradient& gradient, const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
{
    if ((colors == nullptr) || (colorsLength % NUM_3) != 0) {
        return;
    }
    for (int32_t index = 0; index < colorsLength; index += NUM_3) {
        auto colorValue = colors[index].u32;
        auto colorHasDimension = colors[index + NUM_1].i32;
        auto colorDimension = colors[index + NUM_2].f32;
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

void SetLinearGradientDirectionTo(std::shared_ptr<LinearGradient>& linearGradient, const GradientDirection direction)
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

GradientDirection convertToLinearGradientDirection(std::shared_ptr<LinearGradient> linearGradient)
{
    auto linearX = linearGradient->linearX;
    auto linearY = linearGradient->linearY;
    if (!linearX.has_value() && !linearY.has_value()) {
        return GradientDirection::BOTTOM;
    }
    if (linearX.has_value() && !linearY.has_value()) {
        return linearX.value();
    }
    if (!linearX.has_value() && linearY.has_value()) {
        return linearY.value();
    }

    if (linearX.value() == NG::GradientDirection::LEFT && linearY.value() == NG::GradientDirection::TOP) {
        return GradientDirection::LEFT_TOP;
    }
    if (linearX.value() == NG::GradientDirection::LEFT && linearY.value() == NG::GradientDirection::BOTTOM) {
        return GradientDirection::LEFT_BOTTOM;
    }
    if (linearX.value() == NG::GradientDirection::RIGHT && linearY.value() == NG::GradientDirection::TOP) {
        return GradientDirection::RIGHT_TOP;
    }
    if (linearX.value() == NG::GradientDirection::RIGHT && linearY.value() == NG::GradientDirection::BOTTOM) {
        return GradientDirection::RIGHT_BOTTOM;
    }
    return GradientDirection::BOTTOM;
}

/**
 * @param values value value
 * values[0], values[1] : angle: hasValue, angle value
 * values[2] : direction
 * values[3] : repeating
 * @param valuesLength values length
 */
void SetLinearGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_4)) {
        return;
    }
    auto angleHasValue = values[NUM_0].i32;
    auto angleValue = values[NUM_1].f32;
    auto directionValue = values[NUM_2].i32;
    auto repeating = values[NUM_3].i32;
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

ArkUI_Float32 CheckAngle(const ArkUI_Float32 angle)
{
    if (LessNotEqual(angle, 0.0f)) {
        return 0.0f;
    }
    if (GreatNotEqual(angle, MAX_ANGLE)) {
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
void SetSweepGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_13)) {
        return;
    }
    auto centerXHasValue = values[NUM_0].i32;
    auto centerXValue = values[NUM_1].f32;
    auto centerXUnit = values[NUM_2].i32;
    auto centerYHasValue = values[NUM_3].i32;
    auto centerYValue = values[NUM_4].f32;
    auto centerYUnit = values[NUM_5].i32;
    auto startHasValue = values[NUM_6].i32;
    auto startValue = values[NUM_7].f32;
    auto endHasValue = values[NUM_8].i32;
    auto endValue = values[NUM_9].f32;
    auto rotationHasValue = values[NUM_10].i32;
    auto rotationValue = values[NUM_11].f32;
    auto repeating = values[NUM_12].i32;
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
void SetRadialGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_10)) {
        return;
    }

    auto centerXHasValue = values[NUM_0].i32;
    auto centerXValue = values[NUM_1].f32;
    auto centerXUnit = values[NUM_2].i32;
    auto centerYHasValue = values[NUM_3].i32;
    auto centerYValue = values[NUM_4].f32;
    auto centerYUnit = values[NUM_5].i32;
    auto radiusHasValue = values[NUM_6].i32;
    auto radiusValue = values[NUM_7].f32;
    auto radiusUnit = values[NUM_8].i32;
    auto repeating = values[NUM_9].i32;

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

bool SetCalcDimension(std::optional<CalcDimension>& optDimension, const ArkUIStringAndFloat* options,
    ArkUI_Int32 optionsLength, ArkUI_Int32 offset)
{
    if ((options == nullptr) || (offset < 0) || ((offset + NUM_3) >= optionsLength)) {
        return false;
    }
    auto hasValue = options[offset];
    auto value = options[offset + NUM_1];
    auto unit = options[offset + NUM_2];
    if (static_cast<bool>(hasValue.value)) {
        auto unitValue = static_cast<DimensionUnit>(unit.value);
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

void SetOptionalBorder(std::optional<Dimension>& optionalDimension, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
    ArkUI_Int32& offset)
{
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optionalDimension =
            Dimension(values[offset + NUM_1], static_cast<OHOS::Ace::DimensionUnit>(values[offset + NUM_2]));
    }
    offset = offset + NUM_3;
}

void SetOptionalBorderColor(
    std::optional<Color>& optionalColor, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optionalColor = Color(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetOptionalBorderStyle(
    std::optional<BorderStyle>& optionalStyle, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optionalStyle = ConvertBorderStyle(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetBorderImageSlice(RefPtr<BorderImage>& borderImage, const std::vector<BorderImageDirection>& directions,
    const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength, ArkUI_Int32& offset)
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

void SetBorderImageRepeat(RefPtr<BorderImage>& borderImage, const ArkUIStringAndFloat* options,
    ArkUI_Int32 optionsLength, ArkUI_Int32& offset)
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

void SetBorderImageWidth(RefPtr<BorderImage>& borderImage, const std::vector<BorderImageDirection>& directions,
    const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength, ArkUI_Int32& offset)
{
    for (int32_t index = 0; index < NUM_12; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, optionsLength, offset + index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            borderImage->SetEdgeWidth(direction, optDimension.value());
        }
    }
    offset += NUM_12;
}

void SetBorderImageOutset(RefPtr<BorderImage>& borderImage, const std::vector<BorderImageDirection>& directions,
    const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength, ArkUI_Int32& offset)
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

void SetBorderImageFill(RefPtr<BorderImage>& borderImage, const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength,
    ArkUI_Int32& offset)
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

void SetBorderImage(FrameNode* frameNode, const RefPtr<BorderImage>& borderImage, ArkUI_Uint32 bitset)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(borderImage);
    if (bitset & BorderImage::SOURCE_BIT) {
        ViewAbstract::SetBorderImageSource(frameNode, borderImage->GetSrc());
    }
    if (bitset & BorderImage::OUTSET_BIT) {
        ViewAbstract::SetHasBorderImageOutset(frameNode, true);
    }
    if (bitset & BorderImage::SLICE_BIT) {
        ViewAbstract::SetHasBorderImageSlice(frameNode, true);
    }
    if (bitset & BorderImage::REPEAT_BIT) {
        ViewAbstract::SetHasBorderImageRepeat(frameNode, true);
    }
    if (bitset & BorderImage::WIDTH_BIT) {
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
void SetBorderImageGradientValues(NG::Gradient& gradient, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength)
{
    if ((values == nullptr) || (valuesLength != NUM_4)) {
        return;
    }
    auto angleHasValue = values[NUM_0].i32;
    auto angleValue = values[NUM_1].f32;
    auto directionValue = values[NUM_2].i32;
    auto repeating = values[NUM_3].i32;
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

void SetBgImgPosition(const DimensionUnit& typeX, const DimensionUnit& typeY, ArkUI_Float32 valueX,
    ArkUI_Float32 valueY, BackgroundImagePosition& bgImgPosition)
{
    OHOS::Ace::AnimationOption option;
    auto animatableDimensionX = AnimatableDimension(valueX, typeX, option);
    auto animatableDimensionY = AnimatableDimension(valueY, typeY, option);
    if (typeX == DimensionUnit::VP || typeX == DimensionUnit::FP) {
        animatableDimensionX.SetValue(animatableDimensionX.ConvertToPx());
        animatableDimensionX.SetUnit(DimensionUnit::PX);
    }
    if (typeY == DimensionUnit::VP || typeY == DimensionUnit::FP) {
        animatableDimensionY.SetValue(animatableDimensionY.ConvertToPx());
        animatableDimensionY.SetUnit(DimensionUnit::PX);
    }
    bgImgPosition.SetSizeX(animatableDimensionX);
    bgImgPosition.SetSizeY(animatableDimensionY);
}

void SetBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundColor(frameNode, Color(color));
}

void ResetBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

void SetWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetWidth(frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetWidth(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}
void SetHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(frameNode, CalcLength(CalcLength(std::string(calcValue))));
    } else {
        ViewAbstract::SetHeight(frameNode, CalcLength(value, unitEnum));
    }
}
void ResetHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}
/**
 * @param values radius values
 * value[0] : radius value for TopLeft，value[1] : radius value for TopRight
 * value[2] : radius value for BottomLeft，value[3] : radius value for BottomRight
 * @param units radius units
 * units[0]: radius unit for TopLeft, units[1] : radius unit for TopRight
 * units[2]: radius unit for BottomLeft, units[3] : radius unit for TopRight
 */
void SetBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::CalcDimension reset;
    ViewAbstract::SetBorderRadius(frameNode, reset);
}

/**
 * @param values radius values, -1 means no this border width
 * value[0] : BorderWidth value for left，value[1] : BorderWidth value for right
 * value[2] : BorderWidth value for top，value[3] : BorderWidth value for bottom
 * @param units radius units
 * units[0]: BorderWidth unit for left, units[1] : BorderWidth unit for right
 * units[2]: BorderWidth unit for top, units[3] : BorderWidth unit for bottom
 */
void SetBorderWidth(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> bottomDimen;
    std::optional<CalcDimension> leftDimen;

    if (values[NUM_0] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]) != OHOS::Ace::DimensionUnit::INVALID) {
        topDimen = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    }
    if (values[NUM_1] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]) != OHOS::Ace::DimensionUnit::INVALID) {
        rightDimen = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    }
    if (values[NUM_2] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]) != OHOS::Ace::DimensionUnit::INVALID) {
        bottomDimen = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    }
    if (values[NUM_3] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]) != OHOS::Ace::DimensionUnit::INVALID) {
        leftDimen = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    }

    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = leftDimen;
    borderWidth.rightDimen = rightDimen;
    borderWidth.topDimen = topDimen;
    borderWidth.bottomDimen = bottomDimen;
    borderWidth.multiValued = true;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void ResetBorderWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::Dimension borderWidth;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void SetTransform(ArkUINodeHandle node, const ArkUI_Float32* matrix, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (length != matrix4Len) {
        return;
    }
    NG::ViewAbstract::SetTransformMatrix(
        frameNode, Matrix4(matrix[NUM_0], matrix[NUM_4], matrix[NUM_8], matrix[NUM_12], matrix[NUM_1], matrix[NUM_5],
            matrix[NUM_9], matrix[NUM_13], matrix[NUM_2], matrix[NUM_6], matrix[NUM_10], matrix[NUM_14],
                matrix[NUM_3], matrix[NUM_7], matrix[NUM_11], matrix[NUM_15]));
}

void ResetTransform(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        double value = 1.0;
        matrix[i] = static_cast<float>(value);
    }
    NG::ViewAbstract::SetTransformMatrix(
        frameNode, Matrix4(matrix[NUM_0], matrix[NUM_4], matrix[NUM_8], matrix[NUM_12], matrix[NUM_1], matrix[NUM_5],
            matrix[NUM_9], matrix[NUM_13], matrix[NUM_2], matrix[NUM_6], matrix[NUM_10], matrix[NUM_14],
                matrix[NUM_3], matrix[NUM_7], matrix[NUM_11], matrix[NUM_15]));
}

void SetBorderColor(
    ArkUINodeHandle node, uint32_t topColorInt, uint32_t rightColorInt, uint32_t bottomColorInt, uint32_t leftColorInt)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderColorProperty borderColors;
    borderColors.topColor = Color(topColorInt);
    borderColors.rightColor = Color(rightColorInt);
    borderColors.bottomColor = Color(bottomColorInt);
    borderColors.leftColor = Color(leftColorInt);
    borderColors.multiValued = true;

    ViewAbstract::SetBorderColor(frameNode, borderColors);
}

void ResetBorderColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
}

/**
 * @param xValue position x value
 * @param xUnit position x unit
 * @param yValue position y unit
 * @param yUnit position y unit
 */
void SetPosition(ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue, ArkUI_Int32 yUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ViewAbstract::SetPosition(frameNode, { Dimension(xValue, static_cast<OHOS::Ace::DimensionUnit>(xUnit)),
                                             Dimension(yValue, static_cast<OHOS::Ace::DimensionUnit>(yUnit)) });
}

void ResetPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetPosition(frameNode);
}

bool ParseEdges(OHOS::Ace::EdgesParam& edges, const ArkUIStringAndFloat* options)
{
    bool result = false;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> bottom;
    std::optional<CalcDimension> right;
    SetCalcDimension(top, options, NUM_13, NUM_0);
    SetCalcDimension(left, options, NUM_13, NUM_3);
    SetCalcDimension(bottom, options, NUM_13, NUM_6);
    SetCalcDimension(right, options, NUM_13, NUM_9);
    if (top.has_value()) {
        result = true;
        edges.SetTop(top.value());
    }
    if (left.has_value()) {
        result = true;
        edges.SetLeft(left.value());
    }
    if (bottom.has_value()) {
        result = true;
        edges.SetBottom(bottom.value());
    }
    if (right.has_value()) {
        result = true;
        edges.SetRight(right.value());
    }
    return result;
}

void SetPositionEdges(ArkUINodeHandle node, const int32_t useEdges, const ArkUIStringAndFloat* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool vaild = false;

    if (useEdges) {
        OHOS::Ace::EdgesParam edges;
        if (ParseEdges(edges, options)) {
            ViewAbstract::SetPositionEdges(frameNode, edges);
        } else {
            ViewAbstract::ResetPosition(frameNode);
        }
    } else {
        OffsetT<Dimension> offset;
        std::optional<CalcDimension> x;
        std::optional<CalcDimension> y;
        SetCalcDimension(x, options, NUM_7, NUM_0);
        SetCalcDimension(y, options, NUM_7, NUM_3);
        if (x.has_value()) {
            vaild = true;
            offset.SetX(x.value());
        }
        if (y.has_value()) {
            vaild = true;
            offset.SetY(y.value());
        }
        if (vaild) {
            ViewAbstract::SetPosition(frameNode, offset);
        } else {
            ViewAbstract::ResetPosition(frameNode);
        }
    }
}

void ResetPositionEdges(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        ViewAbstract::ResetPosition();
    } else {
        ViewAbstract::SetPosition(frameNode, { 0.0_vp, 0.0_vp });
    }
}

/**
 * @param styles styles value
 * styles[0] : styleLeft, styles[1] : styleRight, styles[2] : styleTop, styles[3] : styleBottom
 * @param length styles length
 */
void SetBorderStyle(ArkUINodeHandle node, const ArkUI_Int32* styles, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetBorderStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
 * shadows[0] : BlurRadius, shadows[1] : 1: has ColorStrategy; 2: has Color
 * shadows[2] : OffsetX, offset[3] : OffsetY
 * shadows[4] : ShadowType, shadows[5] : Color, shadows[6] : IsFilled
 * @param length shadows length
 */
void SetBackShadow(ArkUINodeHandle node, const ArkUIInt32orFloat32* shadows, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        Shadow shadow;
        auto shadowStyle = static_cast<ShadowStyle>(shadows[NUM_0].i32);
        auto style = static_cast<ShadowStyle>(shadowStyle);
        if (GetShadowFromTheme(style, shadow)) {
            ViewAbstract::SetBackShadow(frameNode, shadow);
        }
    }
    if (length != NUM_7) {
        return;
    }
    auto blurRadius = shadows[NUM_0].f32;                          // BlurRadius
    auto hasColorValue = static_cast<int32_t>(shadows[NUM_1].i32); // 1: has ColorStrategy; 2: has Color
    auto offsetX = shadows[NUM_2].f32;                             // OffsetX
    auto offsetY = shadows[NUM_3].f32;                             // OffsetY
    auto shadowType = shadows[NUM_4].i32;                          // ShadowType
    auto color = static_cast<uint32_t>(shadows[NUM_5].u32);        // Color
    auto isFilled = static_cast<uint32_t>(shadows[NUM_6].i32);     // IsFilled
    Shadow shadow;
    shadow.SetBlurRadius(blurRadius);
    shadow.SetOffsetX(offsetX);
    shadow.SetOffsetY(offsetY);
    if (hasColorValue == 1) { // 1: has ColorStrategy
        shadow.SetShadowColorStrategy(static_cast<ShadowColorStrategy>(color));
    } else if (hasColorValue == 2) { // 2: has Color
        shadow.SetColor(Color(color));
    }
    shadow.SetShadowType(static_cast<ShadowType>(shadowType));
    shadow.SetIsFilled(static_cast<bool>(isFilled));
    ViewAbstract::SetBackShadow(frameNode, shadow);
}

void ResetBackShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    ViewAbstract::SetBackShadow(frameNode, shadow);
}

void SetHitTestBehavior(ArkUINodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::HitTestMode hitTestModeNG = static_cast<NG::HitTestMode>(value);
    ViewAbstract::SetHitTestMode(frameNode, hitTestModeNG);
}

void ResetHitTestBehavior(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHitTestMode(frameNode, NG::HitTestMode::HTMDEFAULT);
}

void SetZIndex(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetZIndex(frameNode, value);
}

void ResetZIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetZIndex(frameNode, 0);
}

void SetOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (opacity > 1.0f || LessNotEqual(opacity, 0.0f)) {
            opacity = 1.0f;
        }
    } else {
        opacity = std::clamp(opacity, 0.0f, 1.0f);
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetAlign(ArkUINodeHandle node, ArkUI_Int32 align)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Alignment alignment = ParseAlignment(align);
    ViewAbstract::SetAlign(frameNode, alignment);
}

void ResetAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlign(frameNode, Alignment::CENTER);
}

void SetBackdropBlur(
    ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize)
{
    ArkUI_Float32 blur = 0.0f;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value > 0) {
        blur = value;
    }
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstract::SetBackdropBlur(frameNode, dimensionRadius, blurOption);
}

void ResetBackdropBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double blur = 0.0;
    BlurOption option;
    CalcDimension dimensionRadius(blur, DimensionUnit::PX);
    ViewAbstract::SetBackdropBlur(frameNode, dimensionRadius, option);
}

void SetHueRotate(ArkUINodeHandle node, ArkUI_Float32 deg)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    deg = std::fmod(deg, ROUND_UNIT);
    if (deg < 0.0f) {
        deg += ROUND_UNIT;
    }
    ViewAbstract::SetHueRotate(frameNode, deg);
}

void ResetHueRotate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 deg = 0.0f;
    ViewAbstract::SetHueRotate(frameNode, deg);
}

void SetInvert(ArkUINodeHandle node, ArkUI_Float32* invert, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invertVariant;
    if (length == NUM_4) {
        InvertOption option;
        option.low_ = invert[NUM_0];
        option.high_ = invert[NUM_1];
        option.threshold_ = invert[NUM_2];
        option.thresholdRange_ = invert[NUM_3];
        invertVariant = option;
    } else {
        invertVariant = invert[NUM_0];
    }
    ViewAbstract::SetInvert(frameNode, invertVariant);
}

void ResetInvert(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invert = 0.0f;
    ViewAbstract::SetInvert(frameNode, invert);
}

void SetSepia(ArkUINodeHandle node, ArkUI_Float32 sepia)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(sepia, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSepia(frameNode, value);
}

void ResetSepia(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    ViewAbstract::SetSepia(frameNode, value);
}

void SetSaturate(ArkUINodeHandle node, ArkUI_Float32 saturate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(saturate, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSaturate(frameNode, value);
}

void ResetSaturate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetSaturate(frameNode, value);
}

void SetColorBlend(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetColorBlend(frameNode, Color(color));
}

void ResetColorBlend(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color colorBlend = Color::TRANSPARENT;
    ViewAbstract::SetColorBlend(frameNode, colorBlend);
}

ArkUI_Uint32 GetColorBlend(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ViewAbstract::GetColorBlend(frameNode).GetValue();
}

void SetGrayscale(ArkUINodeHandle node, ArkUI_Float64 grayScale)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetGrayscale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    ViewAbstract::SetGrayScale(frameNode, value);
}

void SetContrast(ArkUINodeHandle node, ArkUI_Float64 contrast)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(contrast, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetContrast(frameNode, value);
}

void ResetContrast(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetContrast(frameNode, value);
}

void SetBrightness(ArkUINodeHandle node, ArkUI_Float64 brightness)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(brightness, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetBrightness(frameNode, value);
}

void ResetBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetBrightness(frameNode, value);
}

void SetBlur(ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 blur = 0.0f;
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, blurOption);
}

void ResetBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double blur = 0.0;
    BlurOption option;
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, option);
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
void SetLinearGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetLinearGradient(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
void SetSweepGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
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

void ResetSweepGradient(ArkUINodeHandle node)
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
void SetRadialGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
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

void ResetRadialGradient(ArkUINodeHandle node)
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
void SetOverlay(ArkUINodeHandle node, ArkUI_CharPtr text, const ArkUI_Float32* options, ArkUI_Int32 optionsLength)
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
        overlay.align = Alignment::TOP_LEFT;
        overlay.x = CalcDimension(0);
        overlay.y = CalcDimension(0);
    }
    ViewAbstract::SetOverlay(frameNode, overlay);
}

void ResetOverlay(ArkUINodeHandle node)
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
void SetBorderImage(
    ArkUINodeHandle node, ArkUI_CharPtr src, const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength)
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
    std::vector<BorderImageDirection> directions = { BorderImageDirection::TOP, BorderImageDirection::RIGHT,
        BorderImageDirection::BOTTOM, BorderImageDirection::LEFT };
    SetBorderImageSlice(borderImage, directions, options, optionsLength, loc);  // read 12 double
    SetBorderImageRepeat(borderImage, options, optionsLength, loc);             // read 2 double
    SetBorderImageWidth(borderImage, directions, options, optionsLength, loc);  // read 12 double
    SetBorderImageOutset(borderImage, directions, options, optionsLength, loc); // read 12 double
    SetBorderImageFill(borderImage, options, optionsLength, loc);               // read 2 double
    auto bitsetValue = options[loc].value;
    SetBorderImage(frameNode, borderImage, static_cast<uint8_t>(bitsetValue));
}

void ResetBorderImage(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    uint8_t imageBorderBitsets = 0;
    SetBorderImage(frameNode, borderImage, imageBorderBitsets);
}

void SetBorderImageGradient(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
    const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength)
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

void SetForegroundBlurStyle(ArkUINodeHandle node, ArkUI_Int32 (*intArray)[3], ArkUI_Float32 scale,
    const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Int32 blurStyle = (*intArray)[NUM_0];
    ArkUI_Int32 colorMode = (*intArray)[NUM_1];
    ArkUI_Int32 adaptiveColor = (*intArray)[NUM_2];
    BlurStyleOption fgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            fgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((colorMode < 0) && (adaptiveColor < 0) && (scale < 0) && (blurValuesSize == 0));
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
            fgBlurStyle.scale = std::clamp(scale, 0.0f, 1.0f);
        }
        BlurOption blurOption;
        blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
        fgBlurStyle.blurOption = blurOption;
    }
    ViewAbstract::SetForegroundBlurStyle(frameNode, fgBlurStyle);
}

void ResetForegroundBlurStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption styleOption;
    ViewAbstract::SetForegroundBlurStyle(frameNode, styleOption);
}

ArkUIBlurStyleOptionType GetForegroundBlurStyle(ArkUINodeHandle node)
{
    ArkUIBlurStyleOptionType styleOptionType = { 0, 0, 0, 1.0f, 0, 0 };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, styleOptionType);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, styleOptionType);
    auto blurStyleOption = renderContext->GetFrontBlurStyle();
    if (!blurStyleOption.has_value()) {
        return styleOptionType;
    }
    styleOptionType.blurStyle = static_cast<int32_t>(blurStyleOption->blurStyle);
    styleOptionType.colorMode = static_cast<int32_t>(blurStyleOption->colorMode);
    styleOptionType.adaptiveColor = static_cast<int32_t>(blurStyleOption->adaptiveColor);
    styleOptionType.scale = blurStyleOption->scale;
    styleOptionType.grayScaleStart = blurStyleOption->blurOption.grayscale[NUM_0];
    styleOptionType.grayScaleEnd = blurStyleOption->blurOption.grayscale[NUM_1];
    return styleOptionType;
}

/**
 * @param blurRadius blurRadius value
 * @param stops stop value
 * stops[0], stops[1] : fractionStops pair[0]
 * stops[2], stops[3] : fractionStops pair[1] ...
 * @param stopsLength stops length
 * @param directionValue direction value
 */
void SetLinearGradientBlur(ArkUINodeHandle node, ArkUI_Float32 blurRadius, const ArkUI_Float32* stops,
    ArkUI_Uint32 stopsLength, ArkUI_Int32 directionValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    blurRadius = std::clamp(blurRadius, 0.0f, 60.0f); // 60.0 represents largest blur radius;
    std::vector<std::pair<float, float>> fractionStops;
    if ((stopsLength & 0x1) == 0) {
        float tmpPos = -1.0f;
        for (size_t index = 0; index < stopsLength; index += NUM_2) {
            auto first = stops[index];
            auto second = stops[index + NUM_1];
            std::pair<float, float> fractionStop;
            fractionStop.first = static_cast<float>(std::clamp(first, 0.0f, 1.0f));
            fractionStop.second = static_cast<float>(std::clamp(second, 0.0f, 1.0f));
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

void ResetLinearGradientBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 0.0f));
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    Dimension dimensionRadius(0.0f, DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, GradientDirection::BOTTOM);
    ViewAbstract::SetLinearGradientBlur(frameNode, blurPara);
}

void SetBackgroundBlurStyle(ArkUINodeHandle node, ArkUI_Int32 (*intArray)[5], ArkUI_Float32 scale,
    const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize, ArkUI_Bool isValidColor, ArkUI_Uint32 inactiveColorArg)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Int32 blurStyle = (*intArray)[NUM_0];
    ArkUI_Int32 colorMode = (*intArray)[NUM_1];
    ArkUI_Int32 adaptiveColor = (*intArray)[NUM_2];
    ArkUI_Int32 policy = (*intArray)[NUM_3];
    ArkUI_Int32 blurType = (*intArray)[NUM_4];
    BlurStyleOption bgBlurStyle;
    if (blurStyle >= 0) {
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            bgBlurStyle.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    bool isHasOptions = !((colorMode < 0) && (adaptiveColor < 0) && (scale < 0) && (blurValuesSize == 0));
    if (isHasOptions) {
        if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
            colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
            bgBlurStyle.colorMode = static_cast<ThemeColorMode>(colorMode);
        }
        if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            bgBlurStyle.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
        }
        bgBlurStyle.scale = std::clamp(scale, 0.0f, 1.0f);
        BlurOption blurOption;
        blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
        bgBlurStyle.blurOption = blurOption;
    }
    bgBlurStyle.policy = static_cast<BlurStyleActivePolicy>(policy);
    bgBlurStyle.blurType = static_cast<BlurType>(blurType);
    bgBlurStyle.isValidColor = isValidColor;
    Color inactiveColor(inactiveColorArg);
    bgBlurStyle.inactiveColor = inactiveColor;
    ViewAbstract::SetBackgroundBlurStyle(frameNode, bgBlurStyle);
}

ArkUIBlurStyleOptionType GetBackgroundBlurStyle(ArkUINodeHandle node)
{
    ArkUIBlurStyleOptionType styleOptionType = { 0, 0, 0, 1.0f };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, styleOptionType);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, styleOptionType);
    auto backBlurStyleOption = renderContext->GetBackBlurStyle();
    if (!backBlurStyleOption.has_value()) {
        return styleOptionType;
    }
    styleOptionType.blurStyle = static_cast<int32_t>(backBlurStyleOption->blurStyle);
    styleOptionType.colorMode = static_cast<int32_t>(backBlurStyleOption->colorMode);
    styleOptionType.adaptiveColor = static_cast<int32_t>(backBlurStyleOption->adaptiveColor);
    styleOptionType.scale = backBlurStyleOption->scale;
    auto greyScaleVector = backBlurStyleOption->blurOption.grayscale;
    styleOptionType.grayScaleStart = greyScaleVector.size() > NUM_0 ? greyScaleVector[NUM_0] : 0.0f;
    styleOptionType.grayScaleEnd = greyScaleVector.size() > NUM_1 ? greyScaleVector[NUM_1] : 0.0f;
    return styleOptionType;
}

void ResetBackgroundBlurStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption bgBlurStyle;
    ViewAbstract::SetBackgroundBlurStyle(frameNode, bgBlurStyle);
}

void SetBorderWidth(const ArkUI_Float32* values, ArkUI_Int32 valuesSize, int32_t& offset,
    NG::BorderWidthProperty& borderWidth, ArkUI_Bool isLocalizedBorderWidth, FrameNode* frameNode)
{
    if (isLocalizedBorderWidth) {
        SetOptionalBorder(borderWidth.startDimen, values, valuesSize, offset);
        SetOptionalBorder(borderWidth.endDimen, values, valuesSize, offset);
    } else {
        SetOptionalBorder(borderWidth.leftDimen, values, valuesSize, offset);
        SetOptionalBorder(borderWidth.rightDimen, values, valuesSize, offset);
    }
    SetOptionalBorder(borderWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.bottomDimen, values, valuesSize, offset);
    borderWidth.multiValued = true;
    if (borderWidth.leftDimen.has_value() || borderWidth.rightDimen.has_value() || borderWidth.topDimen.has_value() ||
        borderWidth.bottomDimen.has_value() || borderWidth.startDimen.has_value() || borderWidth.endDimen.has_value()) {
        ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    }
}

void SetBorderBorderRadius(const ArkUI_Float32* values, ArkUI_Int32 valuesSize, int32_t& offset,
    NG::BorderRadiusProperty& borderRadius, ArkUI_Bool isLocalizedBorderRadius, FrameNode* frameNode)
{
    if (isLocalizedBorderRadius) {
        SetOptionalBorder(borderRadius.radiusTopStart, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusTopEnd, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusBottomStart, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusBottomEnd, values, valuesSize, offset);
    } else {
        SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, offset);
        SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, offset);
    }

    borderRadius.multiValued = true;
    if (borderRadius.radiusTopLeft.has_value() || borderRadius.radiusTopRight.has_value() ||
        borderRadius.radiusBottomLeft.has_value() || borderRadius.radiusBottomRight.has_value() ||
        borderRadius.radiusTopStart.has_value() || borderRadius.radiusTopEnd.has_value() ||
        borderRadius.radiusBottomStart.has_value() || borderRadius.radiusBottomEnd.has_value()) {
        ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    }
}

/**
 * @param src source borderWidth and and BorderRadius value
 * @param options option value
 * values[offset + 0], option[offset + 1], option[offset + 2]: borderWidth start/left(hasValue, value, unit)
 * values[offset + 3], option[offset + 4], option[offset + 5]: borderWidth end/right(hasValue, value, unit)
 * values[offset + 6], option[offset + 7], option[offset + 8]: borderWidth top(hasValue, value, unit)
 * values[offset + 9], option[offset + 10], option[offset + 11]: borderWidth bottom(hasValue, value, unit)
 * values[offset + 12], option[offset + 13], option[offset + 14] : BorderRadius TopStart/Left(hasValue, value, unit)
 * values[offset + 15], option[offset + 16], option[offset + 17] : BorderRadius TopEnd/Right(hasValue, value, unit)
 * values[offset + 18], option[offset + 19], option[offset + 20] : BorderRadius BottomStart/Left(hasValue, value, unit)
 * values[offset + 21], option[offset + 22], option[offset + 23] : BorderRadius BottomEnd/Right(hasValue, value, unit)
 * @param optionsLength options valuesSize
 * @param src source color and Style value
 * colorAndStyle[offset + 0], option[offset + 1]: borderColors startColor/leftColor(hasValue, value)
 * colorAndStyle[offset + 2], option[offset + 3]: borderColors endColor/rightColor(hasValue, value)
 * colorAndStyle[offset + 4], option[offset + 5]: borderColors topColor(hasValue, value)
 * colorAndStyle[offset + 6], option[offset + 7]: borderColors bottomColor(hasValue, value)
 * colorAndStyle[offset + 8], option[offset + 9]: borderStyles styleLeft(hasValue, value)
 * colorAndStyle[offset + 10], option[offset + 11]: borderStyles styleRight(hasValue, value)
 * colorAndStyle[offset + 12], option[offset + 12]: borderStyles styleTop(hasValue, value)
 * colorAndStyle[offset + 14], option[offset + 15]: borderStyles styleBottom(hasValue, value)
 * @param optionsLength options colorAndStyleSize
 * @param isLocalizedBorderWidth options isLocalizedBorderWidth
 * @param isLocalizedBorderColor options isLocalizedBorderColor
 * @param isLocalizedBorderRadius options isLocalizedBorderRadius
 */
void SetBorder(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize, const uint32_t* colorAndStyle,
    int32_t colorAndStyleSize, ArkUI_Bool isLocalizedBorderWidth, ArkUI_Bool isLocalizedBorderColor,
    ArkUI_Bool isLocalizedBorderRadius)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_24) || (colorAndStyle == nullptr) || colorAndStyleSize != NUM_16) {
        return;
    }

    int32_t offset = NUM_0;
    NG::BorderWidthProperty borderWidth;
    SetBorderWidth(values, valuesSize, offset, borderWidth, isLocalizedBorderWidth, frameNode);
    NG::BorderRadiusProperty borderRadius;
    SetBorderBorderRadius(values, valuesSize, offset, borderRadius, isLocalizedBorderRadius, frameNode);
    int32_t colorAndStyleOffset = NUM_0;
    NG::BorderColorProperty borderColors;
    if (isLocalizedBorderColor) {
        SetOptionalBorderColor(borderColors.startColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
        SetOptionalBorderColor(borderColors.endColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    } else {
        SetOptionalBorderColor(borderColors.leftColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
        SetOptionalBorderColor(borderColors.rightColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    }
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

void ResetBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension borderWidth;
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    ViewAbstract::SetBorderColor(frameNode, Color::BLACK);
    ViewAbstract::SetBorderRadius(frameNode, borderWidth);
    ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
    ViewAbstract::SetDashGap(frameNode, Dimension(-1));
    ViewAbstract::SetDashWidth(frameNode, Dimension(-1));
}

void SetBackgroundImagePosition(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* types, ArkUI_Bool isAlign, ArkUI_Int32 size)
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

void ResetBackgroundImagePosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImagePosition bgImgPosition;
    SetBgImgPosition(DimensionUnit::PX, DimensionUnit::PX, 0.0, 0.0, bgImgPosition);
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}

void SetResizableFromVec(ImageResizableSlice& resizable, const ArkUIStringAndFloat* options)
{
    std::vector<ResizableOption> directions = { ResizableOption::TOP, ResizableOption::BOTTOM, ResizableOption::LEFT,
        ResizableOption::RIGHT };
    for (unsigned int index = 0; index < NUM_12; index += NUM_3) {
        std::optional<CalcDimension> optDimension;
        SetCalcDimension(optDimension, options, NUM_13, index);
        if (optDimension.has_value()) {
            auto direction = directions[index / NUM_3];
            resizable.SetEdgeSlice(direction, optDimension.value());
        }
    }
}

void SetBackgroundImageResizable(ArkUINodeHandle node, ArkUIStringAndFloat* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageResizableSlice resizable;
    SetResizableFromVec(resizable, options);
    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, resizable);
}

void ResetBackgroundImageResizable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageResizableSlice resizable;
    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, resizable);
}

void SetBackgroundImageSize(ArkUINodeHandle node, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight,
    ArkUI_Int32 typeWidth, ArkUI_Int32 typeHeight)
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

ArkUIImageSizeType GetBackgroundImageSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    ArkUIImageSizeType imageSizeType = { 0, 0, 0, 0 };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, imageSizeType);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, imageSizeType);
    CHECK_NULL_RETURN(renderContext->GetBackground(), imageSizeType);
    auto imageSize = renderContext->GetBackground()->GetBackgroundImageSize();
    double density = unit == static_cast<ArkUI_Int32>(DimensionUnit::PX) ? 1 : PipelineBase::GetCurrentDensity();
    CHECK_NULL_RETURN(imageSize, imageSizeType);
    imageSizeType.xValue = imageSize->GetSizeValueX() / density;
    imageSizeType.yValue = imageSize->GetSizeValueY() / density;
    imageSizeType.xType = static_cast<int32_t>(imageSize->GetSizeTypeX());
    imageSizeType.yType = static_cast<int32_t>(imageSize->GetSizeTypeY());
    return imageSizeType;
}

int32_t GetBackgroundImageSizeWidthStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, 0);
    CHECK_NULL_RETURN(renderContext->GetBackground(), 0);
    auto imageSize = renderContext->GetBackground()->GetBackgroundImageSize();
    CHECK_NULL_RETURN(imageSize, 0);
    return static_cast<int32_t>(imageSize->GetSizeTypeX());
}

void ResetBackgroundImageSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
    bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void SetBackgroundImage(
    ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundle, ArkUI_CharPtr module, ArkUI_Int32 repeatIndex)
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

void SetBackgroundImagePixelMap(ArkUINodeHandle node, void* drawableDescriptor, ArkUI_Int32 repeatIndex)
{
#ifndef ACE_UNITTEST
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<OHOS::Ace::PixelMap> pixelmap = PixelMap::GetFromDrawable(drawableDescriptor);
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { pixelmap });
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    if (repeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && repeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, repeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
#endif
}

void SetBackgroundImagePixelMapByPixelMapPtr(ArkUINodeHandle node, void* pixelMapPtr, ArkUI_Int32 repeatIndex)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PixelMap> pixelmap = PixelMap::CreatePixelMap(pixelMapPtr);
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { pixelmap });
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    if (repeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && repeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, repeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
}

void ResetBackgroundImage(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr;
    std::string bundle;
    std::string module;
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { srcStr, bundle, module });
    ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
}

void SetTranslate(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
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

void ResetTranslate(ArkUINodeHandle node)
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
void SetScale(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength, const ArkUI_Int32* units,
    ArkUI_Int32 unitLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (valLength != NUM_5 && valLength != NUM_2) {
        return;
    }
    auto x = values[NUM_0];
    auto y = values[NUM_1];
    // NOT support Z in source code
    VectorF scale(x, y);
    ViewAbstract::SetScale(frameNode, scale);
    if (valLength != NUM_5) {
        return;
    }
    auto centerX = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    auto centerY = Dimension(values[NUM_4], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    auto centerZ = Dimension(0.0, OHOS::Ace::DimensionUnit::VP);

    DimensionOffset center(centerX, centerY);
    if (!NearZero(centerZ.Value())) {
        center.SetZ(centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

void GetScale(ArkUINodeHandle node, ArkUIScaleType* scaleType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto scale = ViewAbstract::GetScale(frameNode);
    scaleType->xValue = scale.x;
    scaleType->yValue = scale.y;
}

void GetRotate(ArkUINodeHandle node, ArkUIRotateType* rotateType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto rotate = ViewAbstract::GetRotate(frameNode);
    rotateType->xCoordinate = rotate.x;
    rotateType->yCoordinate = rotate.y;
    rotateType->zCoordinate = rotate.z;
    rotateType->angle = rotate.w;
    rotateType->sightDistance = rotate.v;
}

ArkUI_Float32 GetBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_BRIGHTNESS);
    return ViewAbstract::GetBrightness(frameNode).Value();
}

ArkUI_Float32 GetSaturate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_SATURATE);
    return ViewAbstract::GetSaturate(frameNode).Value();
}

void GetBackgroundImagePosition(ArkUINodeHandle node, ArkUIPositionOptions* position, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto imagePosition = ViewAbstract::GetBackgroundImagePosition(frameNode);
    position->x = imagePosition.GetSizeX().GetNativeValue(static_cast<DimensionUnit>(unit));
    position->y = imagePosition.GetSizeY().GetNativeValue(static_cast<DimensionUnit>(unit));
}

/**
 * @param values
 * values[0]: scaleX;values[1]: scaleY;values[2]: scaleZ
 * @param length shadows length
 */
void SetScaleWithoutTransformCenter(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (valLength != NUM_3) {
        return;
    }
    auto x = values[NUM_0];
    auto y = values[NUM_1];
    // NOT support Z in source code
    if (x < 0) {
        x = 1;
    }
    if (y < 0) {
        y = 1;
    }
    VectorF scale(x, y);
    ViewAbstract::SetScale(frameNode, scale);
}

void ResetScale(ArkUINodeHandle node)
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
void SetRotate(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength, const ArkUI_Int32* units,
    ArkUI_Int32 unitLength)
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

/**
 * @param values
 * values[0]: xDirection;values[1]: yDirection;values[2]: zDirection
 * values[3]: angle;values[4]:perspective
 * @param length shadows length
 */
void SetRotateWithoutTransformCenter(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (valLength != NUM_5) {
        return;
    }

    auto xDirection = values[NUM_0];
    auto yDirection = values[NUM_1];
    auto zDirection = values[NUM_2];
    auto angle = values[NUM_3];
    auto perspective = values[NUM_4];
    ViewAbstract::SetRotate(frameNode, NG::Vector5F(xDirection, yDirection, zDirection, angle, perspective));
}

void ResetRotate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct, 0.0f, 0.0f);
    ViewAbstract::SetRotate(
        frameNode, NG::Vector5F(rotate.xDirection, rotate.yDirection, rotate.zDirection, 0.0, rotate.perspective));

    DimensionOffset center(rotate.centerX, rotate.centerY);
    if (!NearZero(rotate.centerZ.Value())) {
        center.SetZ(rotate.centerZ);
    }
    ViewAbstract::SetPivot(frameNode, center);
}

void SetGeometryTransition(ArkUINodeHandle node, ArkUI_CharPtr id, const ArkUIGeometryTransitionOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string idStr(id);
    ViewAbstract::SetGeometryTransition(frameNode, idStr,
        static_cast<bool>(options->follow), static_cast<bool>(options->hierarchyStrategy));
}

ArkUI_CharPtr GetGeometryTransition(ArkUINodeHandle node, ArkUIGeometryTransitionOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    bool followWithoutTransition = false;
    bool doRegisterSharedTransition = true;
    g_strValue = ViewAbstract::GetGeometryTransition(frameNode, &followWithoutTransition, &doRegisterSharedTransition);
    options->follow = followWithoutTransition;
    options->hierarchyStrategy = static_cast<int32_t>(doRegisterSharedTransition);
    return g_strValue.c_str();
}

void ResetGeometryTransition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGeometryTransition(frameNode, "", false, true);
}

void SetOffset(ArkUINodeHandle node, const ArkUI_Float32* number, const ArkUI_Int32* unit)
{
    CHECK_NULL_VOID(number);
    CHECK_NULL_VOID(unit);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xVal(*(number + 0), static_cast<DimensionUnit>(*(unit + 0)));
    Dimension yVal(*(number + 1), static_cast<DimensionUnit>(*(unit + 1)));
    ViewAbstract::SetOffset(frameNode, { xVal, yVal });
}

void SetOffsetEdges(ArkUINodeHandle node, ArkUI_Bool useEdges, const ArkUIStringAndFloat* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (useEdges) {
        OHOS::Ace::EdgesParam edges;
        ParseEdges(edges, options);
        ViewAbstract::SetOffsetEdges(frameNode, edges);
    } else {
        OffsetT<Dimension> offset;
        std::optional<CalcDimension> x;
        std::optional<CalcDimension> y;
        SetCalcDimension(x, options, NUM_7, NUM_0);
        SetCalcDimension(y, options, NUM_7, NUM_3);
        if (x.has_value()) {
            offset.SetX(x.value());
        }
        if (y.has_value()) {
            offset.SetY(y.value());
        }
        ViewAbstract::SetOffset(frameNode, offset);
    }
}

ArkUIOffsetType GetOffset(ArkUINodeHandle node)
{
    ArkUIOffsetType offsetVp = { 0.0f, 0.0f };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, offsetVp);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, offsetVp);
    CHECK_NULL_RETURN(renderContext->GetPositionProperty(), offsetVp);
    if (!renderContext->GetPositionProperty()->HasOffset()) {
        return offsetVp;
    }
    offsetVp.xComponent = renderContext->GetPositionProperty()->GetOffsetValue().GetX().Value();
    offsetVp.yComponent = renderContext->GetPositionProperty()->GetOffsetValue().GetY().Value();
    return offsetVp;
}

void ResetOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xVal(0.0, DimensionUnit::VP);
    Dimension yVal(0.0, DimensionUnit::VP);
    ViewAbstract::SetOffset(frameNode, { xVal, yVal });
}

void SetPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
void SetPixelStretchEffect(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
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

void ResetPixelStretchEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
}

void SetLightUpEffect(ArkUINodeHandle node, ArkUI_Float32 radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    radio = std::clamp(radio, 0.0f, 1.0f);
    ViewAbstract::SetLightUpEffect(frameNode, radio);
}

void ResetLightUpEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightUpEffect(frameNode, 1.0);
}

void SetSphericalEffect(ArkUINodeHandle node, ArkUI_Float64 radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    radio = std::clamp(radio, 0.0, 1.0);
    ViewAbstract::SetSphericalEffect(frameNode, radio);
}

void ResetSphericalEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSphericalEffect(frameNode, 0.0);
}

void SetRenderGroup(ArkUINodeHandle node, ArkUI_Bool isRenderGroup)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderGroup(frameNode, isRenderGroup);
}

void ResetRenderGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderGroup(frameNode, false);
}

void SetRenderFit(ArkUINodeHandle node, ArkUI_Int32 renderFitNumber)
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

void ResetRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderFit(frameNode, RenderFit::TOP_LEFT);
}

ArkUI_Int32 GetRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Int32>(ViewAbstract::GetRenderFit(frameNode));
}

void SetUseEffect(ArkUINodeHandle node, ArkUI_Bool useEffect, ArkUI_Int32 effectType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetUseEffect(frameNode, useEffect, static_cast<EffectType>(effectType));
}

void ResetUseEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetUseEffect(frameNode, false, EffectType::DEFAULT);
}

void SetForegroundColor(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color)
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

void ResetForegroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}

void SetMotionPath(ArkUINodeHandle node, ArkUI_CharPtr path, ArkUI_Float32 from, ArkUI_Float32 to, ArkUI_Bool rotatable)
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

void ResetMotionPath(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::MotionPathOption motionPathOption = MotionPathOption();
    ViewAbstract::SetMotionPath(frameNode, motionPathOption);
}


void SetMotionBlur(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 anchorX, ArkUI_Float32 anchorY)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = radius;
    motionBlurOption.anchor.x = anchorX;
    motionBlurOption.anchor.y = anchorY;
    ViewAbstract::SetMotionBlur(frameNode, motionBlurOption);
}

void ResetMotionBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = 0.0;
    motionBlurOption.anchor.x = 0.0;
    motionBlurOption.anchor.y = 0.0;
    ViewAbstract::SetMotionBlur(frameNode, motionBlurOption);
}

void SetGroupDefaultFocus(ArkUINodeHandle node, ArkUI_Bool groupDefaultFocus)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGroupDefaultFocus(frameNode, groupDefaultFocus);
}

void ResetGroupDefaultFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool groupDefaultFocus = false;
    ViewAbstract::SetGroupDefaultFocus(frameNode, groupDefaultFocus);
}

void SetFocusOnTouch(ArkUINodeHandle node, ArkUI_Bool focusOnTouch)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusOnTouch(frameNode, focusOnTouch);
}

void ResetFocusOnTouch(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool focusOnTouch = false;
    ViewAbstract::SetFocusOnTouch(frameNode, focusOnTouch);
}

ArkUI_Bool GetFocusOnTouch(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetFocusOnTouch(frameNode));
}

void SetFocusable(ArkUINodeHandle node, ArkUI_Bool focusable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == "Custom") {
        ViewAbstract::SetFocusType(frameNode, focusable ? FocusType::SCOPE : FocusType::DISABLE);
    }
    ViewAbstract::SetFocusable(frameNode, focusable);
}

void ResetFocusable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool focusable = false;
    ViewAbstract::SetFocusable(frameNode, focusable);
}

void SetTouchable(ArkUINodeHandle node, ArkUI_Bool touchable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTouchable(frameNode, touchable);
}

void ResetTouchable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool touchable = true;
    ViewAbstract::SetTouchable(frameNode, touchable);
}

void SetDefaultFocus(ArkUINodeHandle node, ArkUI_Bool defaultFocus)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDefaultFocus(frameNode, defaultFocus);
}

void ResetDefaultFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool defaultFocus = false;
    ViewAbstract::SetDefaultFocus(frameNode, defaultFocus);
}

void SetDisplayPriority(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDisplayIndex(frameNode, static_cast<int32_t>(value));
}

void ResetDisplayPriority(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDisplayIndex(frameNode, DEFAULT_DISPLAY_PRIORITY);
}

ArkUI_Int32 GetDisplayPriority(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_DISPLAY_PRIORITY);
    return ViewAbstract::GetDisplayIndex(frameNode);
}

void SetMargin(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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

void ResetMargin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetMargin(frameNode, NG::CalcLength(0.0));
}

void SetMarkAnchor(
    ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue, ArkUI_Int32 yUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension xDimension { xValue, static_cast<DimensionUnit>(xUnit) };
    Dimension yDimension { yValue, static_cast<DimensionUnit>(yUnit) };
    OffsetT<Dimension> value = { xDimension, yDimension };
    ViewAbstract::MarkAnchor(frameNode, value);
}

ArkUIAnchorType GetMarkAnchor(ArkUINodeHandle node)
{
    ArkUIAnchorType anchorType = { 0.0f, 0.0f };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, anchorType);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, anchorType);
    CHECK_NULL_RETURN(renderContext->GetPositionProperty(), anchorType);
    if (!renderContext->GetPositionProperty()->HasAnchor()) {
        return anchorType;
    }
    anchorType.xCoordinate = renderContext->GetPositionProperty()->GetAnchor()->GetX().Value();
    anchorType.yCoordinate = renderContext->GetPositionProperty()->GetAnchor()->GetY().Value();
    return anchorType;
}

void ResetMarkAnchor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::MarkAnchor(frameNode, { Dimension(0.0_vp), Dimension(0.0_vp) });
}

void SetVisibility(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType value_visibleType = static_cast<VisibleType>(value);
    ViewAbstract::SetVisibility(frameNode, value_visibleType);
}

void ResetVisibility(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, DEFAULT_VISIBILITY);
}

void SetAccessibilityText(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityText(frameNode, valueStr);
}

void ResetAccessibilityText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityText(frameNode, "");
}

void SetAllowDrop(ArkUINodeHandle node, ArkUI_CharPtr* allowDropCharArray, ArkUI_Int32 length)
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
    frameNode->SetDisallowDropForcedly(false);
    ViewAbstract::SetAllowDrop(frameNode, allowDropSet);
}

void ResetAllowDrop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::set<std::string> allowDrop;
    frameNode->SetDisallowDropForcedly(false);
    ViewAbstract::SetAllowDrop(frameNode, allowDrop);
}

void SetDisAllowDrop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDisallowDropForcedly(true);
}

void SetAccessibilityLevel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, valueStr);
}

void ResetAccessibilityLevel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, "");
}

void SetDirection(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutDirection(frameNode, static_cast<TextDirection>(direction));
}

void ResetDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutDirection(frameNode, DEFAULT_COMMON_DIRECTION);
}

void SetLayoutWeight(ArkUINodeHandle node, ArkUI_Int32 layoutWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutWeight(frameNode, layoutWeight);
}

void ResetLayoutWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutWeight(frameNode, DEFAULT_COMMON_LAYOUTWEIGHT);
}

ArkUI_Float32 GetLayoutWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ViewAbstract::GetLayoutWeight(frameNode);
}

void SetMinWidth(ArkUINodeHandle node, const struct ArkUISizeType* minWidth)
{
    CHECK_NULL_VOID(minWidth);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength strResult;
    if (minWidth->string != nullptr) {
        strResult = CalcLength(minWidth->string);
        ViewAbstract::SetMinWidth(frameNode, strResult);
    } else {
        CalcDimension result(minWidth->value, static_cast<DimensionUnit>(minWidth->unit));
        ViewAbstract::SetMinWidth(frameNode, CalcLength(result));
    }
}

void ResetMinWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMinSize(frameNode, true);
}

void SetMaxWidth(ArkUINodeHandle node, const struct ArkUISizeType* maxWidth)
{
    CHECK_NULL_VOID(maxWidth);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength strResult;
    if (maxWidth->string != nullptr) {
        strResult = CalcLength(maxWidth->string);
        ViewAbstract::SetMaxWidth(frameNode, strResult);
    } else {
        CalcDimension result(maxWidth->value, static_cast<DimensionUnit>(maxWidth->unit));
        ViewAbstract::SetMaxWidth(frameNode, CalcLength(result));
    }
}

void ResetMaxWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMaxSize(frameNode, true);
}

void SetMinHeight(ArkUINodeHandle node, const struct ArkUISizeType* minHeight)
{
    CHECK_NULL_VOID(minHeight);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength strResult;
    if (minHeight->string != nullptr) {
        strResult = CalcLength(minHeight->string);
        ViewAbstract::SetMinHeight(frameNode, strResult);
    } else {
        CalcDimension result(minHeight->value, static_cast<DimensionUnit>(minHeight->unit));
        ViewAbstract::SetMinHeight(frameNode, CalcLength(result));
    }
}

void ResetMinHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMinSize(frameNode, false);
}

void SetMaxHeight(ArkUINodeHandle node, const struct ArkUISizeType* maxHeight)
{
    CHECK_NULL_VOID(maxHeight);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength strResult;
    if (maxHeight->string != nullptr) {
        strResult = CalcLength(maxHeight->string);
        ViewAbstract::SetMaxHeight(frameNode, strResult);
    } else {
        CalcDimension result(maxHeight->value, static_cast<DimensionUnit>(maxHeight->unit));
        ViewAbstract::SetMaxHeight(frameNode, CalcLength(result));
    }
}

void ResetMaxHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMaxSize(frameNode, false);
}

void SetSize(ArkUINodeHandle node, const ArkUI_Float32* number, const ArkUI_Int32* unit, ArkUI_CharPtr* calc)
{
    CHECK_NULL_VOID(number);
    CHECK_NULL_VOID(unit);
    int widthIndex = 0;
    int heightIndex = 1;
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

void ResetSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetWidth(frameNode, CalcLength(0.0, DimensionUnit::VP));
    ViewAbstract::SetHeight(frameNode, CalcLength(0.0, DimensionUnit::VP));
}

void ClearWidthOrHeight(ArkUINodeHandle node, ArkUI_Bool isWidth)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
}

void SetAlignSelf(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= MAX_ALIGN_VALUE) {
        ViewAbstract::SetAlignSelf(frameNode, static_cast<FlexAlign>(value));
    } else {
        ViewAbstract::SetAlignSelf(frameNode, FlexAlign::AUTO);
    }
}

void ResetAlignSelf(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlignSelf(frameNode, FlexAlign::AUTO);
}

void SetAspectRatio(ArkUINodeHandle node, ArkUI_Float32 value)
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

void ResetAspectRatio(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ViewAbstract::ResetAspectRatio(frameNode);
    } else {
        ViewAbstract::SetAspectRatio(frameNode, static_cast<float>(1.0));
    }
}

void SetFlexGrow(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    double result = value;
    if (result < 0.0) {
        result = 0.0;
    }
    ViewAbstract::SetFlexGrow(frameNode, static_cast<float>(result));
}

void ResetFlexGrow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexGrow(frameNode, static_cast<float>(0.0));
}

void SetFlexShrink(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (value < 0.0) {
        ViewAbstract::ResetFlexShrink(frameNode);
        return;
    }
    ViewAbstract::SetFlexShrink(frameNode, static_cast<float>(value));
}

void ResetFlexShrink(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetFlexShrink(frameNode);
}

void SetGridOffset(ArkUINodeHandle node, ArkUI_Int32 offset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, std::nullopt, offset, GridSizeType::UNDEFINED);
}

void ResetGridOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, std::nullopt, DEFAULT_GRID_OFFSET, GridSizeType::UNDEFINED);
}

void SetGridSpan(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, value, std::nullopt);
}

void ResetGridSpan(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetGrid(frameNode, DEFAULT_GRIDSPAN, std::nullopt);
}

void SetExpandSafeArea(ArkUINodeHandle node, ArkUI_Uint32 safeAreaType, ArkUI_Uint32 safeAreaEdge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_ALL, .edges = NG::SAFE_AREA_EDGE_ALL };
    opts.type = safeAreaType;
    opts.edges = safeAreaEdge;
    ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}

void ResetExpandSafeArea(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts;
    opts.type = DEFAULT_SAFE_AREA_TYPE;
    opts.edges = DEFAULT_SAFE_AREA_EDGE;
    ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}

void SetFlexBasis(ArkUINodeHandle node, const struct ArkUIStringAndFloat* flexBasisValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension result;
    if (flexBasisValue->valueStr != nullptr) {
        result = StringUtils::StringToDimensionWithUnit(std::string(flexBasisValue->valueStr), DimensionUnit::VP);
        // flex basis don't support percent case.
        if (result.Unit() == DimensionUnit::PERCENT) {
            result.SetUnit(DimensionUnit::AUTO);
        }
    } else {
        result = Dimension(flexBasisValue->value, DimensionUnit::VP);
    }
    ViewAbstract::SetFlexBasis(frameNode, result);
}

void ResetFlexBasis(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexBasis(frameNode, DEFAULT_FLEX_BASIS);
}

void SetAlignRules(ArkUINodeHandle node, char** anchors, const ArkUI_Int32* direction, ArkUI_Int32 length)
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
    BiasPair biasPair(DEFAULT_BIAS, DEFAULT_BIAS);
    ViewAbstract::SetBias(frameNode, biasPair);
}

void SetAlignRulesWidthType(ArkUINodeHandle node, const ArkUIAlignRulesType* alignRulesType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(alignRulesType);
    std::map<AlignDirection, AlignRule> rulesMap;
    for (int32_t i = 0; i < alignRulesType->anchorCount && i < NUM_6; i++) {
        std::string anchorId(alignRulesType->anchorIds[i]);
        if (anchorId.empty()) {
            continue;
        }
        AlignRule alignRule;
        alignRule.anchor = anchorId;
        if (i < NUM_3) {
            alignRule.horizontal = static_cast<HorizontalAlign>(alignRulesType->alignTypes[i]);
        } else {
            alignRule.vertical = static_cast<VerticalAlign>(alignRulesType->alignTypes[i]);
        }
        rulesMap[static_cast<AlignDirection>(i)] = alignRule;
    }
    ViewAbstract::SetAlignRules(frameNode, rulesMap);
    BiasPair biasPair(alignRulesType->biasHorizontalValue, alignRulesType->biasVerticalValue);
    ViewAbstract::SetBias(frameNode, biasPair);
}

void ResetAlignRules(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetAlignRules(frameNode);
}

void GetAlignRules(ArkUINodeHandle node, ArkUI_CharPtr* anchors, ArkUI_Int32* direction, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto alignRules = ViewAbstract::GetAlignRules(frameNode);

    ArkUI_Int32 index = 0;
    for (const AlignDirection alignDirection : { AlignDirection::LEFT, AlignDirection::MIDDLE, AlignDirection::RIGHT,
         AlignDirection::TOP, AlignDirection::CENTER, AlignDirection::BOTTOM, AlignDirection::START,
         AlignDirection::END }) {
        if (index >= length) {
            return;
        }
        auto it = alignRules.find(alignDirection);
        if (it != alignRules.end()) {
            anchors[index] = it->second.anchor.c_str();
            switch (alignDirection) {
                case AlignDirection::LEFT:
                case AlignDirection::RIGHT:
                case AlignDirection::CENTER:
                case AlignDirection::START:
                case AlignDirection::END:
                    direction[index] = static_cast<ArkUI_Int32>(it->second.horizontal) - 1;
                    break;
                case AlignDirection::TOP:
                case AlignDirection::MIDDLE:
                case AlignDirection::BOTTOM:
                    direction[index] = static_cast<ArkUI_Int32>(it->second.vertical) - 1;
                    break;
            }
        } else {
            anchors[index] = nullptr;
            direction[index] = -1;
        }
        ++index;
    }
}

void SetAccessibilityDescription(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, valueStr);
}

void ResetAccessibilityDescription(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, "");
}

void SetId(ArkUINodeHandle node, ArkUI_CharPtr id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = id;
    ViewAbstract::SetInspectorId(frameNode, valueStr);
}

void ResetId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string id = "";
    ViewAbstract::SetInspectorId(frameNode, id);
}

void SetKey(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = key;
    ViewAbstract::SetInspectorId(frameNode, valueStr);
}

void ResetKey(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string defaultStr = "";
    ViewAbstract::SetInspectorId(frameNode, defaultStr);
}

void SetRestoreId(ArkUINodeHandle node, uint32_t id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRestoreId(frameNode, id);
}

void ResetRestoreId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRestoreId(frameNode, DEFAULT_ID);
}

void SetTabIndex(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTabIndex(frameNode, index);
}

void ResetTabIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t index = 0;
    ViewAbstract::SetTabIndex(frameNode, index);
}

void SetObscured(ArkUINodeHandle node, const ArkUI_Int32* reason, ArkUI_Int32 length)
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

void ResetObscured(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ObscuredReasons> reasons(0);
    ViewAbstract::SetObscured(frameNode, reasons);
}

void SetResponseRegion(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
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

void ResetResponseRegion(ArkUINodeHandle node)
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

void SetForegroundEffect(ArkUINodeHandle node, ArkUI_Float32 radius)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    radius = std::max(radius, 0.0f);
    ViewAbstract::SetForegroundEffect(frameNode, static_cast<float>(radius));
}

void ResetForegroundEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetForegroundEffect(frameNode, 0.0f);
}

void SetBackgroundEffect(ArkUINodeHandle node, ArkUI_Float32 radiusArg, ArkUI_Float32 saturationArg,
    ArkUI_Float32 brightnessArg, ArkUI_Uint32 colorArg, ArkUI_Int32 adaptiveColorArg, const ArkUI_Float32* blurValues,
    ArkUI_Int32 blurValuesSize, ArkUI_Int32 policy, ArkUI_Int32 blurType, ArkUI_Bool isValidColor,
    ArkUI_Uint32 inactiveColorArg)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        radius = CalcDimension(radiusArg, DimensionUnit::VP);
    } else {
        radius = CalcDimension(radiusArg, DimensionUnit::PX);
    }
    Color color(colorArg);
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);

    EffectOption option;
    option.radius = radius;
    option.saturation = saturationArg;
    option.brightness = brightnessArg;
    option.color = color;
    option.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorArg);
    option.blurOption = blurOption;
    option.blurType = static_cast<BlurType>(blurType);
    option.policy = static_cast<BlurStyleActivePolicy>(policy);
    Color inactiveColor(inactiveColorArg);
    option.inactiveColor = inactiveColor;
    option.isValidColor = isValidColor;
    ViewAbstract::SetBackgroundEffect(frameNode, option);
}

void ResetBackgroundEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    radius.SetValue(0.0f);
    double saturation = 1.0f;
    double brightness = 1.0f;
    Color color = Color::TRANSPARENT;
    color.SetValue(Color::TRANSPARENT.GetValue());
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    BlurOption blurOption;
    EffectOption effectOption = { radius, saturation, brightness, color, adaptiveColor, blurOption };
    ViewAbstract::SetBackgroundEffect(frameNode, effectOption);
}

void SetBackgroundBrightness(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDynamicLightUp(frameNode, rate, lightUpDegree);
}

void ResetBackgroundBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double rate = 0.0;
    double lightUpDegree = 0.0;
    ViewAbstract::SetDynamicLightUp(frameNode, rate, lightUpDegree);
}

void SetBackgroundBrightnessInternal(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree, 
    ArkUI_Float32 cubicCoeff, ArkUI_Float32 quadCoeff, ArkUI_Float32 saturation, 
    const ArkUI_Float32* posRGBValues, ArkUI_Int32 posRGBValuesSize,
    const ArkUI_Float32* negRGBValues, ArkUI_Int32 negRGBValuesSize , ArkUI_Float32 fraction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    std::vector<float> posRGB;
    posRGB.assign(posRGBValues, posRGBValues + posRGBValuesSize);
    std::vector<float> negRGB;
    negRGB.assign(negRGBValues, negRGBValues + negRGBValuesSize);
    BrightnessOption brightnessOption = { rate, lightUpDegree, cubicCoeff, quadCoeff,
        saturation, posRGB, negRGB, fraction };
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBgDynamicBrightness(frameNode, brightnessOption);
}

void ResetBackgroundBrightnessInternal(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    float rate = 1.0f;
    float lightUpDegree = 0.0f;
    float cubicCoeff = 0.0f;
    float quadCoeff = 0.0f;
    float saturation = 1.0f;
    std::vector<float> posRGB(3, 0.0);
    std::vector<float> negRGB(3, 0.0);
    float fraction = 1.0;
    BrightnessOption brightnessOption = { rate, lightUpDegree, cubicCoeff, quadCoeff,
        saturation, posRGB, negRGB, fraction };
    ViewAbstract::SetBgDynamicBrightness(frameNode, brightnessOption);
}
 
void SetForegroundBrightness(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree, 
    ArkUI_Float32 cubicCoeff, ArkUI_Float32 quadCoeff, ArkUI_Float32 saturation, 
    const ArkUI_Float32* posRGBValues, ArkUI_Int32 posRGBValuesSize,
    const ArkUI_Float32* negRGBValues, ArkUI_Int32 negRGBValuesSize, ArkUI_Float32 fraction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    std::vector<float> posRGB;
    posRGB.assign(posRGBValues, posRGBValues + posRGBValuesSize);
    std::vector<float> negRGB;
    negRGB.assign(negRGBValues, negRGBValues + negRGBValuesSize);
    BrightnessOption brightnessOption = { rate, lightUpDegree, cubicCoeff, quadCoeff,
        saturation, posRGB, negRGB, fraction };
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFgDynamicBrightness(frameNode, brightnessOption);
}

void ResetForegroundBrightness(ArkUINodeHandle node)
 {
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    float rate = 1.0f;
    float lightUpDegree = 0.0f;
    float cubicCoeff = 0.0f;
    float quadCoeff = 0.0f;
    float saturation = 1.0f;
    std::vector<float> posRGB(3, 0.0);
    std::vector<float> negRGB(3, 0.0);
    float fraction = 1.0;
    BrightnessOption brightnessOption = { rate, lightUpDegree, cubicCoeff, quadCoeff,
        saturation, posRGB, negRGB, fraction };
    ViewAbstract::SetFgDynamicBrightness(frameNode, brightnessOption);
}

void ParseDragPreviewMode(NG::DragPreviewOption& previewOption, int32_t modeValue, bool& isAuto)
{
    if (modeValue == static_cast<int32_t>(NG::DragPreviewMode::AUTO)) {
        previewOption.ResetDragPreviewMode();
        isAuto = true;
        return;
    } else if (modeValue == static_cast<int32_t>(NG::DragPreviewMode::DISABLE_SCALE)) {
        previewOption.isScaleEnabled = false;
    } else if (modeValue == static_cast<int32_t>(NG::DragPreviewMode::ENABLE_DEFAULT_SHADOW)) {
        previewOption.isDefaultShadowEnabled = true;
    } else if (modeValue == static_cast<int32_t>(NG::DragPreviewMode::ENABLE_DEFAULT_RADIUS)) {
        previewOption.isDefaultRadiusEnabled = true;
    }
    isAuto = false;
}

void SetDragPreviewOptions(ArkUINodeHandle node, ArkUIDragPreViewOptions dragPreviewOptions,
    ArkUIDragInteractionOptions dragInteractionOptions)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DragPreviewOption option;
    bool isAuto = true;
    if (!dragPreviewOptions.isModeArray) {
        ParseDragPreviewMode(option, dragPreviewOptions.mode, isAuto);
    } else {
        for (int32_t i = 0; i < dragPreviewOptions.modeArrayLength; i++) {
            ParseDragPreviewMode(option, dragPreviewOptions.modeArray[i], isAuto);
            if (isAuto) {
                break;
            }
        }
    }

    if (dragPreviewOptions.isBadgeNumber) {
        option.badgeNumber = dragPreviewOptions.badgeNumber;
    } else {
        option.isShowBadge = dragPreviewOptions.isShowBadge;
    }
    option.isNumber = dragPreviewOptions.isBadgeNumber;
    option.isMultiSelectionEnabled = dragInteractionOptions.isMultiSelectionEnabled;
    option.defaultAnimationBeforeLifting = dragInteractionOptions.defaultAnimationBeforeLifting;
    ViewAbstract::SetDragPreviewOptions(frameNode, option);
}

void ResetDragPreviewOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDragPreviewOptions(frameNode,
        { true, false, false, false, false, false, true, { .isShowBadge = true } });
}

void SetMouseResponseRegion(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
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

void ResetMouseResponseRegion(ArkUINodeHandle node)
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

void SetEnabled(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, value);
}

void ResetEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, true);
}

void SetUseShadowBatching(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetUseShadowBatching(frameNode, value);
}

void ResetUseShadowBatching(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetUseShadowBatching(frameNode, false);
}

void SetDraggable(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, value);
}

void ResetDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDraggable(frameNode, false);
}

void SetAccessibilityGroup(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, value);
}

void ResetAccessibilityGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, false);
}

void SetHoverEffect(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::HoverEffectType hoverEffect = OHOS::Ace::HoverEffectType::AUTO;
    hoverEffect = static_cast<OHOS::Ace::HoverEffectType>(hoverEffectValue);
    ViewAbstract::SetHoverEffect(frameNode, hoverEffect);
}

void ResetHoverEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHoverEffect(frameNode, OHOS::Ace::HoverEffectType::AUTO);
}

void SetClickEffect(ArkUINodeHandle node, const int32_t levelValue, ArkUI_Float32 scaleValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::ClickEffectLevel level = OHOS::Ace::ClickEffectLevel::UNDEFINED;
    level = static_cast<OHOS::Ace::ClickEffectLevel>(levelValue);
    ViewAbstract::SetClickEffectLevel(frameNode, level, scaleValue);
}

void ResetClickEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClickEffectLevel(frameNode, OHOS::Ace::ClickEffectLevel::UNDEFINED, 0.9f);
}

void SetKeyBoardShortCut(ArkUINodeHandle node, ArkUI_CharPtr value, const ArkUI_Int32* keysIntArray, ArkUI_Int32 length)
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

void ResetKeyBoardShortCut(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetKeyboardShortcut(frameNode, "", std::vector<OHOS::Ace::ModifierKey>(), nullptr);
}

void SetPointLightPosition(ArkUINodeHandle node, const struct ArkUISizeType* positionX,
    const struct ArkUISizeType* positionY, const struct ArkUISizeType* positionZ)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(positionX);
    CHECK_NULL_VOID(positionY);
    CHECK_NULL_VOID(positionZ);
    CalcDimension lightPositionX(positionX->value, static_cast<DimensionUnit>(positionX->unit));
    CalcDimension lightPositionY(positionY->value, static_cast<DimensionUnit>(positionY->unit));
    CalcDimension lightPositionZ(positionZ->value, static_cast<DimensionUnit>(positionZ->unit));
    ViewAbstract::SetLightPosition(frameNode, lightPositionX, lightPositionY, lightPositionZ);
#endif
}

void ResetPointLightPosition(ArkUINodeHandle node)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension lightPositionX(0.0f, DimensionUnit::VP);
    CalcDimension lightPositionY(0.0f, DimensionUnit::VP);
    CalcDimension lightPositionZ(0.0f, DimensionUnit::VP);
    ViewAbstract::SetLightPosition(frameNode, lightPositionX, lightPositionY, lightPositionZ);
#endif
}

void SetPointLightIntensity(ArkUINodeHandle node, ArkUI_Float32 intensity)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightIntensity(frameNode, static_cast<float>(intensity));
#endif
}

void ResetPointLightIntensity(ArkUINodeHandle node)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightIntensity(frameNode, 0.0f);
#endif
}

void SetPointLightColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color colorValue(color);
    ViewAbstract::SetLightColor(frameNode, colorValue);
#endif
}

void ResetPointLightColor(ArkUINodeHandle node)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightColor(frameNode, Color::WHITE);
#endif
}

void SetPointLightIlluminated(
    ArkUINodeHandle node, ArkUI_Uint32 illuminated, const struct ArkUISizeType* illuminatedBorderWidth)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightIlluminated(frameNode, static_cast<uint32_t>(illuminated));
    Dimension borderWidthValue(illuminatedBorderWidth->value, static_cast<DimensionUnit>(illuminatedBorderWidth->unit));
    ViewAbstract::SetIlluminatedBorderWidth(frameNode, borderWidthValue);
#endif
}

void ResetPointLightIlluminated(ArkUINodeHandle node)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightIlluminated(frameNode, 0);
    Dimension borderWidthValue(0.0f, DimensionUnit::VP);
    ViewAbstract::SetIlluminatedBorderWidth(frameNode, borderWidthValue);
#endif
}

void SetPointLightBloom(ArkUINodeHandle node, ArkUI_Float32 bloom, ArkUI_Float32 bloomRadius, ArkUI_Uint32 bloomColor)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBloom(frameNode, static_cast<float>(bloom));
    Shadow shadow;
    shadow.SetBlurRadius(bloom * static_cast<float>(bloomRadius));
    Color bloomColorValue(bloomColor);
    shadow.SetColor(bloomColorValue);
    ViewAbstract::SetBackShadow(frameNode, shadow);
#endif
}

void ResetPointLightBloom(ArkUINodeHandle node)
{
#ifdef POINT_LIGHT_ENABLE
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBloom(frameNode, 0.0f);
    Shadow shadow;
    shadow.SetBlurRadius(0);
    ViewAbstract::SetBackShadow(frameNode, shadow);
#endif
}

void SetClip(ArkUINodeHandle node, ArkUI_Int32 isClip)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClipEdge(frameNode, static_cast<bool>(isClip));
}

void SetClipShape(
    ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32* attribute, ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (std::strcmp(type, "rect") == 0) {
        auto shape = AceType::MakeRefPtr<ShapeRect>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto radiusWidth = Dimension(attribute[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto radiusHeight = Dimension(attribute[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(unit));
        shape->SetWidth(width);
        shape->SetHeight(height);
        shape->SetRadiusWidth(radiusWidth);
        shape->SetRadiusHeight(radiusHeight);
        if (length > NUM_4) {
            auto topLeftRadius = length > NUM_4
                                     ? Dimension(attribute[NUM_4], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                     : Dimension(0);
            auto bottomLeftRadius = length > NUM_5
                                        ? Dimension(attribute[NUM_5], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                        : Dimension(0);
            auto topRightRadius = length > NUM_6
                                      ? Dimension(attribute[NUM_6], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                      : Dimension(0);
            auto bottomRightRadius = length > NUM_7
                                         ? Dimension(attribute[NUM_7], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                         : Dimension(0);
            shape->SetTopLeftRadius(Radius(topLeftRadius));
            shape->SetBottomLeftRadius(Radius(bottomLeftRadius));
            shape->SetTopRightRadius(Radius(topRightRadius));
            shape->SetBottomRightRadius(Radius(bottomRightRadius));
        }
        ViewAbstract::SetClipShape(frameNode, shape);
    }
    if (std::strcmp(type, "circle") == 0) {
        auto shape = AceType::MakeRefPtr<Circle>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
        shape->SetWidth(width);
        shape->SetHeight(height);
        ViewAbstract::SetClipShape(frameNode, shape);
    }
    if (std::strcmp(type, "ellipse") == 0) {
        auto shape = AceType::MakeRefPtr<Ellipse>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
        shape->SetWidth(width);
        shape->SetHeight(height);
        ViewAbstract::SetClipShape(frameNode, shape);
    }
}

void SetClipPath(ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32 (*attribute)[2], ArkUI_CharPtr commands,
    ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto path = AceType::MakeRefPtr<Path>();
    auto width = Dimension((*attribute)[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
    auto height = Dimension((*attribute)[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
    std::string pathCommands(commands);
    path->SetWidth(width);
    path->SetHeight(height);
    path->SetValue(StringUtils::TrimStr(pathCommands));
    ViewAbstract::SetClipShape(frameNode, path);
}

void ResetClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClipEdge(frameNode, false);
}

void SetAnimationOption(std::shared_ptr<AnimationOption>& option, const ArkUIAnimationOptionType* animationOption)
{
    option->SetDuration(animationOption->duration);
    option->SetCurve(CURVES[std::clamp(animationOption->curve, 0, static_cast<int32_t>(CURVES.size() - 1))]);
    option->SetDelay(animationOption->delay);
    option->SetIteration(animationOption->iteration);
    option->SetAnimationDirection(static_cast<AnimationDirection>(animationOption->playMode));
    option->SetTempo(animationOption->tempo);
}

void SetTransitionCenter(ArkUINodeHandle node, ArkUI_Float32 centerXValue, ArkUI_Int32 centerXUnit,
    ArkUI_Float32 centerYValue, int32_t centerYUnit, ArkUI_Float32 centerZValue, ArkUI_Int32 centerZUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension centerXDimension(centerXValue, static_cast<DimensionUnit>(centerXUnit));
    Dimension centerYDimension(centerYValue, static_cast<DimensionUnit>(centerYUnit));
    Dimension centerZDimension(centerZValue, static_cast<DimensionUnit>(centerZUnit));
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
    }
    oneCenterTransition->SetCenterX(centerXDimension);
    oneCenterTransition->SetCenterY(centerYDimension);
    oneCenterTransition->SetCenterZ(centerZDimension);
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::ROTATE) {
            auto rotateEffect = AceType::DynamicCast<NG::ChainedRotateEffect>(chainEffect);
            NG::RotateOptions rotate(rotateEffect->GetEffect().xDirection, rotateEffect->GetEffect().yDirection,
                rotateEffect->GetEffect().zDirection, rotateEffect->GetEffect().angle,
                oneCenterTransition->GetCenterX(), oneCenterTransition->GetCenterY(), oneCenterTransition->GetCenterZ(),
                rotateEffect->GetEffect().perspective);
            rotateEffect->SetRotateEffect(rotate);
        } else if (chainEffect->GetType() == ChainedTransitionEffectType::SCALE) {
            auto scaleEffect = AceType::DynamicCast<NG::ChainedScaleEffect>(chainEffect);
            NG::ScaleOptions scale(scaleEffect->GetEffect().xScale, scaleEffect->GetEffect().yScale,
                scaleEffect->GetEffect().zScale, oneCenterTransition->GetCenterX(), oneCenterTransition->GetCenterY());
            scaleEffect->SetScaleEffect(scale);
        }
        chainEffect = chainEffect->GetNext();
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    chainEffect = oneCenterTransition->GetTransitionEffect();
    if (chainEffect) {
        ViewAbstract::SetChainedTransition(frameNode, chainEffect);
    }
    DimensionOffset offset(centerXDimension, centerYDimension);
    offset.SetZ(centerZDimension);
    ViewAbstract::SetPivot(frameNode, offset);
}

ArkUITransformCenterType GetTransformCenter(ArkUINodeHandle node)
{
    ArkUITransformCenterType transformCenter = { 0.0f, 0.0f, 0.0f };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, transformCenter);
    CHECK_NULL_RETURN(frameNode->GetGeometryNode(), transformCenter);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, transformCenter);
    auto oneCenterTransform = renderContext->GetOneCenterTransitionOption();
    auto width = frameNode->GetGeometryNode() ? frameNode->GetGeometryNode()->GetFrameSize().Width() : 0.0f;
    auto height = frameNode->GetGeometryNode() ? frameNode->GetGeometryNode()->GetFrameSize().Height() : 0.0f;
    Dimension centerXDimension(HALF, DimensionUnit::PERCENT);
    Dimension centerYDimension(HALF, DimensionUnit::PERCENT);
    Dimension centerZDimension(0, DimensionUnit::VP);
    if (renderContext && oneCenterTransform) {
        centerXDimension.SetValue(oneCenterTransform->GetCenterX().Value());
        centerXDimension.SetUnit(oneCenterTransform->GetCenterX().Unit());
        centerYDimension.SetValue(oneCenterTransform->GetCenterY().Value());
        centerYDimension.SetUnit(oneCenterTransform->GetCenterY().Unit());
        centerZDimension.SetValue(oneCenterTransform->GetCenterZ().Value());
        centerZDimension.SetUnit(oneCenterTransform->GetCenterZ().Unit());
    }
    if (centerXDimension.Unit() == DimensionUnit::PERCENT) {
        Dimension centerXPx(width * centerXDimension.Value(), DimensionUnit::PX);
        centerXDimension.SetValue(centerXPx.ConvertToVp());
        centerXDimension.SetUnit(DimensionUnit::VP);
    }
    if (centerYDimension.Unit() == DimensionUnit::PERCENT) {
        Dimension centerYPx(height * centerYDimension.Value(), DimensionUnit::PX);
        centerYDimension.SetValue(centerYPx.ConvertToVp());
        centerYDimension.SetUnit(DimensionUnit::VP);
    }
    if (centerZDimension.Unit() == DimensionUnit::PERCENT) {
        centerZDimension.SetValue(0.0f);
        centerZDimension.SetUnit(DimensionUnit::VP);
    }
    transformCenter.centerX = centerXDimension.Value();
    transformCenter.centerY = centerYDimension.Value();
    transformCenter.centerZ = centerZDimension.Value();
    return transformCenter;
}

void ResetTransformCenter(RefPtr<OneCenterTransitionOptionType>& oneCenterTransition)
{
    Dimension centerXDimension(HALF, DimensionUnit::PERCENT);
    Dimension centerYDimension(HALF, DimensionUnit::PERCENT);
    Dimension centerZDimension(0, DimensionUnit::VP);
    oneCenterTransition->SetCenterX(centerXDimension);
    oneCenterTransition->SetCenterY(centerYDimension);
    oneCenterTransition->SetCenterZ(centerZDimension);
}

void SetOpacityTransition(ArkUINodeHandle node, ArkUI_Float32 value, const ArkUIAnimationOptionType* animationOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double opacity = value;
    if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
        opacity = 1.0;
    }
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
        ResetTransformCenter(oneCenterTransition);
    }
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedOpacityEffect> opacityEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::OPACITY) {
            opacityEffect = AceType::DynamicCast<NG::ChainedOpacityEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    auto option = std::make_shared<AnimationOption>();
    SetAnimationOption(option, animationOption);
    if (!opacityEffect) {
        opacityEffect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
        opacityEffect->SetAnimationOption(option);
        opacityEffect->SetNext(oneCenterTransition->GetTransitionEffect());
        oneCenterTransition->SetTransitionEffect(opacityEffect);
    } else {
        opacityEffect->SetOpacity(opacity);
        opacityEffect->SetAnimationOption(option);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    ViewAbstract::SetChainedTransition(frameNode, oneCenterTransition->GetTransitionEffect());
}

int32_t findCurveIndex(const RefPtr<Curve> curve)
{
    CHECK_NULL_RETURN(curve, 0);
    auto iterator = std::find(CURVES.begin(), CURVES.end(), curve);
    if (iterator == CURVES.end()) {
        return 0;
    }
    return iterator - CURVES.begin();
}

void ParseAnimationOptionToStruct(
    const std::shared_ptr<AnimationOption> animationOption, ArkUIAnimationOptionType& animationType)
{
    CHECK_NULL_VOID(animationOption);
    animationType.duration = animationOption->GetDuration();
    animationType.curve = findCurveIndex(animationOption->GetCurve());
    animationType.delay = animationOption->GetDelay();
    animationType.iteration = animationOption->GetIteration();
    animationType.playMode = static_cast<int32_t>(animationOption->GetAnimationDirection());
    animationType.tempo = animationOption->GetTempo();
}

ArkUIOpacityTransitionType GetOpacityTransition(ArkUINodeHandle node)
{
    ArkUIAnimationOptionType animationType = { DEFAULT_DURATION, 0, 0, 1, 0, 1.0f };
    ArkUIOpacityTransitionType opacityAnimationStruct = { 1.0f, animationType };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, opacityAnimationStruct);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    CHECK_NULL_RETURN(oneCenterTransition, opacityAnimationStruct);
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedOpacityEffect> opacityEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::OPACITY) {
            opacityEffect = AceType::DynamicCast<NG::ChainedOpacityEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    CHECK_NULL_RETURN(opacityEffect, opacityAnimationStruct);
    opacityAnimationStruct.opacity = opacityEffect->GetEffect();
    ParseAnimationOptionToStruct(opacityEffect->GetAnimationOption(), opacityAnimationStruct.animation);
    return opacityAnimationStruct;
}

void SetRotateTransition(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 length, ArkUI_Float32 perspective,
    ArkUI_Float32 angle, const ArkUIAnimationOptionType* animationOption)
{
    CHECK_NULL_VOID(arrayValue);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length < ARRAY_SIZE) {
        return;
    }
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
        ResetTransformCenter(oneCenterTransition);
    }
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedRotateEffect> rotateEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::ROTATE) {
            rotateEffect = AceType::DynamicCast<NG::ChainedRotateEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    auto option = std::make_shared<AnimationOption>();
    SetAnimationOption(option, animationOption);
    NG::RotateOptions rotate(arrayValue[X_INDEX], arrayValue[Y_INDEX], arrayValue[Z_INDEX], angle,
        oneCenterTransition->GetCenterX(), oneCenterTransition->GetCenterY(), oneCenterTransition->GetCenterZ(),
        perspective);
    if (!rotateEffect) {
        rotateEffect = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
        rotateEffect->SetAnimationOption(option);
        rotateEffect->SetNext(oneCenterTransition->GetTransitionEffect());
        oneCenterTransition->SetTransitionEffect(rotateEffect);
    } else {
        rotateEffect->SetRotateEffect(rotate);
        rotateEffect->SetAnimationOption(option);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    ViewAbstract::SetChainedTransition(frameNode, oneCenterTransition->GetTransitionEffect());
}

ArkUIRotateTransitionType GetRotateTransition(ArkUINodeHandle node)
{
    ArkUIAnimationOptionType animationType = { DEFAULT_DURATION, 0, 0, 1, 0, 1.0f };
    ArkUIRotateTransitionType rotateAnimationStruct = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, animationType };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, rotateAnimationStruct);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    CHECK_NULL_RETURN(oneCenterTransition, rotateAnimationStruct);
    RefPtr<NG::ChainedRotateEffect> rotateEffect;
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::ROTATE) {
            rotateEffect = AceType::DynamicCast<NG::ChainedRotateEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    CHECK_NULL_RETURN(rotateEffect, rotateAnimationStruct);
    auto xRotation = rotateEffect->GetEffect().xDirection;
    auto yRotation = rotateEffect->GetEffect().yDirection;
    auto zRotation = rotateEffect->GetEffect().zDirection;
    auto angle = rotateEffect->GetEffect().angle;
    auto perspective = rotateEffect->GetEffect().perspective;
    rotateAnimationStruct.xRotation = xRotation;
    rotateAnimationStruct.yRotation = yRotation;
    rotateAnimationStruct.zRotation = zRotation;
    rotateAnimationStruct.angle = angle;
    rotateAnimationStruct.perspective = perspective;
    ParseAnimationOptionToStruct(rotateEffect->GetAnimationOption(), rotateAnimationStruct.animation);
    return rotateAnimationStruct;
}

void SetScaleTransition(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 length,
    const ArkUIAnimationOptionType* animationOption)
{
    CHECK_NULL_VOID(arrayValue);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length < ARRAY_SIZE) {
        return;
    }
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
        ResetTransformCenter(oneCenterTransition);
    }
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedScaleEffect> scaleEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::SCALE) {
            scaleEffect = AceType::DynamicCast<NG::ChainedScaleEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    auto option = std::make_shared<AnimationOption>();
    SetAnimationOption(option, animationOption);
    NG::ScaleOptions scale(arrayValue[X_INDEX], arrayValue[Y_INDEX], arrayValue[Z_INDEX],
        oneCenterTransition->GetCenterX(), oneCenterTransition->GetCenterY());
    if (!scaleEffect) {
        scaleEffect = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
        scaleEffect->SetAnimationOption(option);
        scaleEffect->SetNext(oneCenterTransition->GetTransitionEffect());
        oneCenterTransition->SetTransitionEffect(scaleEffect);
    } else {
        scaleEffect->SetScaleEffect(scale);
        scaleEffect->SetAnimationOption(option);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    ViewAbstract::SetChainedTransition(frameNode, oneCenterTransition->GetTransitionEffect());
}

ArkUIScaleTransitionType GetScaleTransition(ArkUINodeHandle node)
{
    ArkUIAnimationOptionType animationType = { DEFAULT_DURATION, 0, 0, 1, 0, 1.0f };
    ArkUIScaleTransitionType scaleAnimationStruct = { 1.0f, 1.0f, 1.0f, animationType };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, scaleAnimationStruct);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    CHECK_NULL_RETURN(oneCenterTransition, scaleAnimationStruct);
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedScaleEffect> scaleEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::SCALE) {
            scaleEffect = AceType::DynamicCast<NG::ChainedScaleEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    CHECK_NULL_RETURN(scaleEffect, scaleAnimationStruct);
    auto xScale = scaleEffect->GetEffect().xScale;
    auto yScale = scaleEffect->GetEffect().yScale;
    auto zScale = scaleEffect->GetEffect().zScale;
    scaleAnimationStruct.xScale = xScale;
    scaleAnimationStruct.yScale = yScale;
    scaleAnimationStruct.zScale = zScale;
    ParseAnimationOptionToStruct(scaleEffect->GetAnimationOption(), scaleAnimationStruct.animation);
    return scaleAnimationStruct;
}

void SetTranslateTransition(ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue,
    ArkUI_Int32 yUnit, ArkUI_Float32 zValue, ArkUI_Int32 zUnit, const ArkUIAnimationOptionType* animationOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
        ResetTransformCenter(oneCenterTransition);
    }
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedTranslateEffect> translateEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::TRANSLATE) {
            translateEffect = AceType::DynamicCast<NG::ChainedTranslateEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }

    auto option = std::make_shared<AnimationOption>();
    SetAnimationOption(option, animationOption);
    Dimension xDimension(xValue, static_cast<DimensionUnit>(xUnit));
    Dimension yDimension(yValue, static_cast<DimensionUnit>(yUnit));
    Dimension zDimension(zValue, static_cast<DimensionUnit>(zUnit));
    NG::TranslateOptions translate(xDimension, yDimension, zDimension);
    if (!translateEffect) {
        translateEffect = AceType::MakeRefPtr<NG::ChainedTranslateEffect>(translate);
        translateEffect->SetAnimationOption(option);
        translateEffect->SetNext(oneCenterTransition->GetTransitionEffect());
        oneCenterTransition->SetTransitionEffect(translateEffect);
    } else {
        translateEffect->SetTranslateEffect(translate);
        translateEffect->SetAnimationOption(option);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    ViewAbstract::SetChainedTransition(frameNode, oneCenterTransition->GetTransitionEffect());
}

ArkUITranslateTransitionType GetTranslateTransition(ArkUINodeHandle node)
{
    ArkUIAnimationOptionType animationType = { DEFAULT_DURATION, 0, 0, 1, 0, 1.0f };
    ArkUITranslateTransitionType translateAnimationStruct = { 0.0f, 0.0f, 0.0f, animationType };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, translateAnimationStruct);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    CHECK_NULL_RETURN(oneCenterTransition, translateAnimationStruct);
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedTranslateEffect> translateEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::TRANSLATE) {
            translateEffect = AceType::DynamicCast<NG::ChainedTranslateEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    CHECK_NULL_RETURN(translateEffect, translateAnimationStruct);
    auto xTransition = translateEffect->GetEffect().x.Value();
    auto yTransition = translateEffect->GetEffect().y.Value();
    auto zTransition = translateEffect->GetEffect().z.Value();
    translateAnimationStruct.xTransition = xTransition;
    translateAnimationStruct.yTransition = yTransition;
    translateAnimationStruct.zTransition = zTransition;
    ParseAnimationOptionToStruct(translateEffect->GetAnimationOption(), translateAnimationStruct.animation);
    return translateAnimationStruct;
}

void SetMoveTransition(ArkUINodeHandle node, ArkUI_Int32 value, const ArkUIAnimationOptionType* animationOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeType = static_cast<TransitionEdge>(value);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    if (!oneCenterTransition) {
        oneCenterTransition = AceType::MakeRefPtr<OneCenterTransitionOptionType>();
        ResetTransformCenter(oneCenterTransition);
    }
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedMoveEffect> moveEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::MOVE) {
            moveEffect = AceType::DynamicCast<NG::ChainedMoveEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    auto option = std::make_shared<AnimationOption>();
    SetAnimationOption(option, animationOption);
    if (!moveEffect) {
        moveEffect = AceType::MakeRefPtr<NG::ChainedMoveEffect>(edgeType);
        moveEffect->SetAnimationOption(option);
        moveEffect->SetNext(oneCenterTransition->GetTransitionEffect());
        oneCenterTransition->SetTransitionEffect(moveEffect);
    } else {
        moveEffect->SetAnimationOption(option);
    }
    ACE_UPDATE_NODE_RENDER_CONTEXT(OneCenterTransitionOption, oneCenterTransition, frameNode);
    ViewAbstract::SetChainedTransition(frameNode, oneCenterTransition->GetTransitionEffect());
}

ArkUIMoveTransitionType GetMoveTransition(ArkUINodeHandle node)
{
    ArkUIAnimationOptionType animationType = { DEFAULT_DURATION, 0, 0, 1, 0, 1.0f };
    ArkUIMoveTransitionType moveAnimationStruct = { 0, animationType };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, moveAnimationStruct);
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition;
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        oneCenterTransition = renderContext->GetOneCenterTransitionOption();
    }
    CHECK_NULL_RETURN(oneCenterTransition, moveAnimationStruct);
    RefPtr<NG::ChainedTransitionEffect> chainEffect = oneCenterTransition->GetTransitionEffect();
    RefPtr<NG::ChainedMoveEffect> moveEffect;
    while (chainEffect) {
        if (chainEffect->GetType() == ChainedTransitionEffectType::MOVE) {
            moveEffect = AceType::DynamicCast<NG::ChainedMoveEffect>(chainEffect);
            break;
        }
        chainEffect = chainEffect->GetNext();
    }
    CHECK_NULL_RETURN(moveEffect, moveAnimationStruct);
    moveAnimationStruct.edgeType = static_cast<ArkUI_Int32>(moveEffect->GetEffect());
    ParseAnimationOptionToStruct(moveEffect->GetAnimationOption(), moveAnimationStruct.animation);
    return moveAnimationStruct;
}

void SetMaskShape(ArkUINodeHandle node, ArkUI_CharPtr type, ArkUI_Uint32 fill, ArkUI_Uint32 stroke,
    ArkUI_Float32 strokeWidth, const ArkUI_Float32* attribute, ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string shapeType(type);
    auto strokeWidth_ = Dimension(strokeWidth, static_cast<OHOS::Ace::DimensionUnit>(unit));
    if (shapeType == "rect") {
        auto shape = AceType::MakeRefPtr<ShapeRect>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto radiusWidth = Dimension(attribute[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(unit));
        auto radiusHeight = Dimension(attribute[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(unit));
        shape->SetWidth(width);
        shape->SetHeight(height);
        shape->SetRadiusWidth(radiusWidth);
        shape->SetRadiusHeight(radiusHeight);
        shape->SetColor(Color(fill));
        shape->SetStrokeColor(stroke);
        shape->SetStrokeWidth(strokeWidth);
        if (length > NUM_4) {
            auto topLeftRadius = length > NUM_4
                                     ? Dimension(attribute[NUM_4], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                     : Dimension(0);
            auto bottomLeftRadius = length > NUM_5
                                        ? Dimension(attribute[NUM_5], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                        : Dimension(0);
            auto topRightRadius = length > NUM_6
                                      ? Dimension(attribute[NUM_6], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                      : Dimension(0);
            auto bottomRightRadius = length > NUM_7
                                         ? Dimension(attribute[NUM_7], static_cast<OHOS::Ace::DimensionUnit>(unit))
                                         : Dimension(0);
            shape->SetTopLeftRadius(Radius(topLeftRadius));
            shape->SetBottomLeftRadius(Radius(bottomLeftRadius));
            shape->SetTopRightRadius(Radius(topRightRadius));
            shape->SetBottomRightRadius(Radius(bottomRightRadius));
        }
        ViewAbstract::SetMask(frameNode, shape);
    } else if (shapeType == "circle") {
        auto shape = AceType::MakeRefPtr<Circle>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(1));
        shape->SetWidth(width);
        shape->SetHeight(height);
        shape->SetColor(Color(fill));
        shape->SetStrokeColor(stroke);
        shape->SetStrokeWidth(strokeWidth);
        ViewAbstract::SetMask(frameNode, shape);
    } else if (shapeType == "ellipse") {
        auto shape = AceType::MakeRefPtr<Ellipse>();
        auto width = Dimension(attribute[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto height = Dimension(attribute[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(1));
        shape->SetWidth(width);
        shape->SetHeight(height);
        shape->SetColor(Color(fill));
        shape->SetStrokeColor(stroke);
        shape->SetStrokeWidth(strokeWidth);
        ViewAbstract::SetMask(frameNode, shape);
    } else {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "type are invalid");
        return;
    }
}

void SetMaskPath(ArkUINodeHandle node, ArkUI_CharPtr type, ArkUI_Uint32 fill, ArkUI_Uint32 stroke,
    ArkUI_Float32 strokeWidth, const ArkUI_Float32 (*attribute)[2], ArkUI_CharPtr commands, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto strokeWidth_ = Dimension(strokeWidth, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CHECK_NULL_VOID(frameNode);
    auto path = AceType::MakeRefPtr<Path>();
    auto width = Dimension((*attribute)[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(unit));
    auto height = Dimension((*attribute)[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(unit));
    std::string pathCommands(commands);
    path->SetWidth(width);
    path->SetHeight(height);
    path->SetValue(StringUtils::TrimStr(pathCommands));
    path->SetColor(Color(fill));
    path->SetStrokeColor(stroke);
    path->SetStrokeWidth(strokeWidth);
    ViewAbstract::SetMask(frameNode, path);
}

void SetProgressMask(ArkUINodeHandle node, const ArkUI_Float32* attribute, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto progressMask = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    int value = attribute[NUM_0];
    int total = attribute[NUM_1];
    progressMask->SetValue(value);
    progressMask->SetMaxValue(total);
    progressMask->SetColor(Color(color));
    ViewAbstract::SetProgressMask(frameNode, progressMask);
}

void ResetMask(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetMask(frameNode, nullptr);
}

void SetOutlineColor(ArkUINodeHandle node, const uint32_t* values, int32_t valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t colorOffset = NUM_0;
    NG::BorderColorProperty borderColors;
    SetOptionalBorderColor(borderColors.topColor, values, valuesSize, colorOffset);
    SetOptionalBorderColor(borderColors.rightColor, values, valuesSize, colorOffset);
    SetOptionalBorderColor(borderColors.bottomColor, values, valuesSize, colorOffset);
    SetOptionalBorderColor(borderColors.leftColor, values, valuesSize, colorOffset);
    borderColors.multiValued = true;
    ViewAbstract::SetOuterBorderColor(frameNode, borderColors);
}

void ResetOutlineColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOuterBorderColor(frameNode, Color::BLACK);
}

void GetOutlineColor(ArkUINodeHandle node, ArkUI_Uint32 (*values)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto colors = ViewAbstract::GetOuterBorderColor(frameNode);
    (*values)[NUM_0] = colors.topColor->GetValue();
    (*values)[NUM_1] = colors.rightColor->GetValue();
    (*values)[NUM_2] = colors.bottomColor->GetValue();
    (*values)[NUM_3] = colors.leftColor->GetValue();
}

void GetSize(ArkUINodeHandle node, ArkUI_Float32 (*values)[2], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    (*values)[NUM_0] = ViewAbstract::GetWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = ViewAbstract::GetHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Bool GetRenderGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetRenderGroup(frameNode));
}

void SetOutlineRadius(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t radiusOffset = NUM_0;

    NG::BorderRadiusProperty borderRadius;
    SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, radiusOffset);
    SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, radiusOffset);
    SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, radiusOffset);
    SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, radiusOffset);
    borderRadius.multiValued = true;
    ViewAbstract::SetOuterBorderRadius(frameNode, borderRadius);
}

void ResetOutlineRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension value;
    ViewAbstract::SetOuterBorderRadius(frameNode, value);
}

void SetOutlineWidth(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t offset = NUM_0;
    NG::BorderWidthProperty borderWidth;

    SetOptionalBorder(borderWidth.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.bottomDimen, values, valuesSize, offset);
    borderWidth.multiValued = true;
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidth);
}

void SetOutlineWidthFloat(ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top,
    ArkUI_Float32 right, ArkUI_Float32 bottom)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = Dimension(left, DimensionUnit::VP);
    borderWidth.topDimen = Dimension(top, DimensionUnit::VP);
    borderWidth.rightDimen = Dimension(right, DimensionUnit::VP);
    borderWidth.bottomDimen = Dimension(bottom, DimensionUnit::VP);
    borderWidth.multiValued = true;
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidth);
}

void GetOutlineWidthFloat(ArkUINodeHandle node, ArkUI_Float32* borderWidthVector, ArkUI_Int32 borderWidthSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (borderWidthSize < OUTLINE_WIDTH_VECTOR_SIZE) {
        return;
    }
    NG::BorderWidthProperty borderWidth = ViewAbstract::GetOuterBorderWidth(frameNode);
    borderWidthVector[OUTLINE_LEFT_WIDTH_INDEX] = borderWidth.leftDimen.has_value() ?
        borderWidth.leftDimen->Value() : 0.0f;
    borderWidthVector[OUTLINE_TOP_WIDTH_INDEX] = borderWidth.topDimen.has_value() ?
        borderWidth.topDimen->Value() : 0.0f;
    borderWidthVector[OUTLINE_RIGHT_WIDTH_INDEX] = borderWidth.rightDimen.has_value() ?
        borderWidth.rightDimen->Value() : 0.0f;
    borderWidthVector[OUTLINE_BOTTOM_WIDTH_INDEX] = borderWidth.bottomDimen.has_value() ?
        borderWidth.bottomDimen->Value() : 0.0f;
}

void ResetOutlineWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension value;
    ViewAbstract::SetOuterBorderWidth(frameNode, value);
}

void SetOutlineStyle(ArkUINodeHandle node, const uint32_t* values, int32_t valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t styleOffset = NUM_0;
    NG::BorderStyleProperty borderStyles;
    SetOptionalBorderStyle(borderStyles.styleLeft, values, valuesSize, styleOffset);
    SetOptionalBorderStyle(borderStyles.styleRight, values, valuesSize, styleOffset);
    SetOptionalBorderStyle(borderStyles.styleTop, values, valuesSize, styleOffset);
    SetOptionalBorderStyle(borderStyles.styleBottom, values, valuesSize, styleOffset);
    borderStyles.multiValued = true;
    ViewAbstract::SetOuterBorderStyle(frameNode, borderStyles);
}

void ResetOutlineStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOuterBorderStyle(frameNode, BorderStyle::SOLID);
}
/**
 * @param src source OutlineWidth and and OutlineRadius value
 * @param options option value
 * values[offset + 0], option[offset + 1], option[offset + 2]: OutlineWidth left(hasValue, value, unit)
 * values[offset + 3], option[offset + 4], option[offset + 5]: OutlineWidth right(hasValue, value, unit)
 * values[offset + 6], option[offset + 7], option[offset + 8]: OutlineWidth top(hasValue, value, unit)
 * values[offset + 9], option[offset + 10], option[offset + 11]: OutlineWidth bottom(hasValue, value, unit)
 * values[offset + 12], option[offset + 13], option[offset + 14] : OutlineRadius TopLeft(hasValue, value, unit)
 * values[offset + 15], option[offset + 16], option[offset + 17] : OutlineRadius TopRight(hasValue, value, unit)
 * values[offset + 18], option[offset + 19], option[offset + 20] : OutlineRadius BottomLeft(hasValue, value, unit)
 * values[offset + 21], option[offset + 22], option[offset + 23] : OutlineRadius BottomRight(hasValue, value, unit)
 * @param optionsLength options valuesSize
 * @param src source color and Style value
 * colorAndStyle[offset + 0], option[offset + 1]: OutlineColors leftColor(hasValue, value)
 * colorAndStyle[offset + 2], option[offset + 3]: OutlineColors rightColor(hasValue, value)
 * colorAndStyle[offset + 4], option[offset + 5]: OutlineColors topColor(hasValue, value)
 * colorAndStyle[offset + 6], option[offset + 7]: OutlineColors bottomColor(hasValue, value)
 * colorAndStyle[offset + 8], option[offset + 9]: OutlineStyles styleLeft(hasValue, value)
 * colorAndStyle[offset + 10], option[offset + 11]: OutlineStyles styleRight(hasValue, value)
 * colorAndStyle[offset + 12], option[offset + 12]: OutlineStyles styleTop(hasValue, value)
 * colorAndStyle[offset + 14], option[offset + 15]: OutlineStyles styleBottom(hasValue, value)
 * @param optionsLength options colorAndStyleSize
 */
void SetOutline(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valuesSize, const uint32_t* colorAndStyle,
    int32_t colorAndStyleSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_24) || (colorAndStyle == nullptr) || colorAndStyleSize != NUM_16) {
        return;
    }

    int32_t offset = NUM_0; // offset for outline width and outline radius
    NG::BorderWidthProperty borderWidth;
    SetOptionalBorder(borderWidth.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.bottomDimen, values, valuesSize, offset);
    borderWidth.multiValued = true;
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidth);

    NG::BorderRadiusProperty borderRadius;
    SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, offset);
    borderRadius.multiValued = true;
    ViewAbstract::SetOuterBorderRadius(frameNode, borderRadius);

    int32_t colorAndStyleOffset = NUM_0; // offset for outline color and outline style
    NG::BorderColorProperty borderColors;
    SetOptionalBorderColor(borderColors.leftColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.rightColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.topColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderColor(borderColors.bottomColor, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    borderColors.multiValued = true;
    ViewAbstract::SetOuterBorderColor(frameNode, borderColors);

    NG::BorderStyleProperty borderStyles;
    SetOptionalBorderStyle(borderStyles.styleLeft, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleRight, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleTop, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    SetOptionalBorderStyle(borderStyles.styleBottom, colorAndStyle, colorAndStyleSize, colorAndStyleOffset);
    borderStyles.multiValued = true;
    ViewAbstract::SetOuterBorderStyle(frameNode, borderStyles);
}

void ResetOutline(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension borderWidth;
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidth);
    ViewAbstract::SetOuterBorderColor(frameNode, Color::BLACK);
    ViewAbstract::SetOuterBorderRadius(frameNode, borderWidth);
    ViewAbstract::SetOuterBorderStyle(frameNode, BorderStyle::SOLID);
}
ArkUI_Bool GetFocusable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetFocusable(frameNode));
}

ArkUI_Bool GetDefaultFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetDefaultFocus(frameNode));
}

ArkUI_Int32 GetResponseRegion(ArkUINodeHandle node, ArkUI_Float32 (*values)[32])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    std::vector<DimensionRect> responseRegions = ViewAbstract::GetResponseRegion(frameNode);
    //set int default
    int index = 0;
    for (auto& element : responseRegions) {
        (*values)[index++] = element.GetOffset().GetX().Value();
        (*values)[index++] = element.GetOffset().GetY().Value();
        (*values)[index++] = element.GetWidth().Value() * PERCENT_100;
        (*values)[index++] = element.GetHeight().Value() * PERCENT_100;
    }
    //values size
    return index;
}

ArkUI_CharPtr GetOverlay(ArkUINodeHandle node, ArkUIOverlayOptions* options, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    NG::OverlayOptions overlayOptions = ViewAbstract::GetOverlay(frameNode);
    options->align = ParseAlignmentToIndex(overlayOptions.align);
    options->x = overlayOptions.x.GetNativeValue(static_cast<DimensionUnit>(unit));
    options->y = overlayOptions.y.GetNativeValue(static_cast<DimensionUnit>(unit));
    options->content = overlayOptions.content.c_str();
    g_strValue = overlayOptions.content;
    return g_strValue.c_str();
}

ArkUI_Bool GetAccessibilityGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(ViewAbstractModelNG::GetAccessibilityGroup(frameNode));
}

ArkUI_CharPtr GetAccessibilityText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ViewAbstractModelNG::GetAccessibilityText(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetAccessibilityDescription(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ViewAbstractModelNG::GetAccessibilityDescription(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetAccessibilityLevel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ViewAbstractModelNG::GetAccessibilityImportance(frameNode);
    return g_strValue.c_str();
}

void SetNeedFocus(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetNeedFocus(frameNode, value);
}

ArkUI_Bool GetNeedFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetNeedFocus(frameNode));
}

void SetBlendMode(ArkUINodeHandle node, int32_t blendMode, ArkUI_Int32 blendApplyTypeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetBlendMode(frameNode, static_cast<OHOS::Ace::BlendMode>(blendMode));
    ViewAbstractModelNG::SetBlendApplyType(frameNode, static_cast<OHOS::Ace::BlendApplyType>(blendApplyTypeValue));
}

void ResetBlendMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetBlendMode(frameNode, OHOS::Ace::BlendMode::NONE);
    ViewAbstractModelNG::SetBlendApplyType(frameNode, OHOS::Ace::BlendApplyType::FAST);
}

void SetMonopolizeEvents(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetMonopolizeEvents(frameNode, value);
}

void ResetMonopolizeEvents(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetMonopolizeEvents(frameNode, false);
}

void SetConstraintSize(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetMinWidth(frameNode, CalcLength(values[NUM_0], static_cast<DimensionUnit>(units[NUM_0])));
    ViewAbstract::SetMaxWidth(frameNode, CalcLength(values[NUM_1], static_cast<DimensionUnit>(units[NUM_1])));
    ViewAbstract::SetMinHeight(frameNode, CalcLength(values[NUM_2], static_cast<DimensionUnit>(units[NUM_2])));
    ViewAbstract::SetMaxHeight(frameNode, CalcLength(values[NUM_3], static_cast<DimensionUnit>(units[NUM_3])));
}

void ResetConstraintSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetMaxSize(frameNode, true);
    ViewAbstract::ResetMinSize(frameNode, true);
    ViewAbstract::ResetMaxSize(frameNode, false);
    ViewAbstract::ResetMinSize(frameNode, false);
}

void BindCustomPopup(FrameNode* frameNode, ArkUIPopupParam* value, UINode* customNode)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    std::function<void(bool)> onStateChangeFunc =
        (value->onStateChange == nullptr) ? std::function<void(bool)>([](bool) -> void {})
        : ([stateChangeCallBack = value->onStateChange, id = value->onStateChangeId](bool input) -> void {
            stateChangeCallBack(id, input);
        });
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };

    popupParam->SetIsShow(value->isShow);
    popupParam->SetUseCustomComponent(value->useCustomComponent);
    popupParam->SetPlacement(static_cast<Placement>(value->placement));
    popupParam->SetMaskColor(Color(value->maskColor));
    popupParam->SetBackgroundColor(Color(value->backgroundColor));
    popupParam->SetEnableArrow(value->enableArrow);
    popupParam->SetHasAction(!value->autoCancel);
    popupParam->SetOnStateChange(onStateChangeCallback);
    if (popupParam->IsShow()) {
        ViewAbstract::BindPopup(popupParam, AceType::Claim(frameNode),
            AceType::Claim(customNode));
    } else {
        ViewAbstract::BindPopup(popupParam, AceType::Claim(frameNode), nullptr);
    }
}

void BindBasePopup(FrameNode* frameNode, ArkUIPopupParam* value)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();

    std::function<void(bool)> onStateChangeFunc =
        (value->onStateChange == nullptr) ? std::function<void(bool)>([](bool) -> void {})
        : ([stateChangeCallBack = value->onStateChange, id = value->onStateChangeId](bool input) -> void {
            stateChangeCallBack(id, input);
        });
    std::function<void()> primaryActionFunc =
        (value->primaryAction == nullptr) ? std::function<void()>([]() -> void {})
        : ([primaryActionCallBack = value->primaryAction, id = value->primaryActionId]() -> void {
            primaryActionCallBack(id);
        });
    std::function<void()> secondaryActionFunc =
        (value->secondaryAction == nullptr) ? std::function<void()>([]() -> void {})
        : ([secondaryActionCallBack = value->secondaryAction, id = value->secondaryActionId]() -> void {
            secondaryActionCallBack(id);
        });
    auto onStateChangeCallback = [onStateChangeFunc](const std::string& param) {
        auto paramData = JsonUtil::ParseJsonString(param);
        onStateChangeFunc(paramData->GetBool("isVisible"));
    };
    popupParam->SetIsShow(value->isShow);
    popupParam->SetMessage(value->message);
    popupParam->SetPlacement(static_cast<Placement>(value->placement));
    popupParam->SetOnStateChange(onStateChangeCallback);
    std::string primaryString = value->primaryString;
    if (!primaryString.empty()) {
        ButtonProperties propertiesPrimary;
        propertiesPrimary.value = primaryString;
        auto touchPrimaryCallback = [primaryActionFunc](TouchEventInfo&) {primaryActionFunc();};
        auto onNewClick = [primaryActionFunc](const GestureEvent& info) {primaryActionFunc();};
        propertiesPrimary.touchFunc = touchPrimaryCallback;
        propertiesPrimary.action = AceType::MakeRefPtr<NG::ClickEvent>(onNewClick);
        propertiesPrimary.showButton = true;
        popupParam->SetPrimaryButtonProperties(propertiesPrimary);
    }

    std::string secondaryString = value->secondaryString;
    if (!secondaryString.empty()) {
        ButtonProperties propertiesSecondary;
        propertiesSecondary.value = secondaryString;
        auto touchSecondaryCallback = [secondaryActionFunc](TouchEventInfo&) {secondaryActionFunc();};
        auto onNewClick = [secondaryActionFunc](const GestureEvent& info) {secondaryActionFunc();};
        propertiesSecondary.touchFunc = touchSecondaryCallback;
        propertiesSecondary.action = AceType::MakeRefPtr<NG::ClickEvent>(onNewClick);
        propertiesSecondary.showButton = true;
        popupParam->SetSecondaryButtonProperties(propertiesSecondary);
    }
    ViewAbstract::BindPopup(popupParam, AceType::Claim(frameNode), nullptr);
}

void SetBindPopup(ArkUINodeHandle node, ArkUIPopupParam* value, ArkUINodeHandle customNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (customNode != nullptr) {
        BindCustomPopup(frameNode, value, reinterpret_cast<UINode*>(customNode));
    } else {
        BindBasePopup(frameNode, value);
    }
}

void ResetBindPopup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(false);
    ViewAbstract::BindPopup(popupParam, AceType::Claim(frameNode), nullptr);
}

ArkUI_Float32 GetOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetOpacity(frameNode);
}

void GetBorderWidth(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = ViewAbstract::GetBorderWidth(frameNode);
    (*values)[NUM_0] = width.topDimen->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = width.rightDimen->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = width.bottomDimen->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = width.leftDimen->GetNativeValue(static_cast<DimensionUnit>(unit));
}

void GetBorderWidthDimension(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 (*units)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto borderWidth = ViewAbstract::GetLayoutBorderWidth(frameNode);
    (*values)[NUM_0] = borderWidth.topDimen->Value();
    (*units)[NUM_0] = static_cast<ArkUI_Int32>(borderWidth.topDimen->Unit());
    (*values)[NUM_1] = borderWidth.rightDimen->Value();
    (*units)[NUM_1] = static_cast<ArkUI_Int32>(borderWidth.rightDimen->Unit());
    (*values)[NUM_2] = borderWidth.bottomDimen->Value();
    (*units)[NUM_2] = static_cast<ArkUI_Int32>(borderWidth.bottomDimen->Unit());
    (*values)[NUM_3] = borderWidth.leftDimen->Value();
    (*units)[NUM_3] = static_cast<ArkUI_Int32>(borderWidth.leftDimen->Unit());
}

void GetBorderRadius(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto radius = ViewAbstract::GetBorderRadius(frameNode);
    (*values)[NUM_0] = radius.radiusTopLeft->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = radius.radiusTopRight->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = radius.radiusBottomLeft->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = radius.radiusBottomRight->GetNativeValue(static_cast<DimensionUnit>(unit));
}

void GetBorderColor(ArkUINodeHandle node, ArkUI_Uint32 (*values)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto colors = ViewAbstract::GetBorderColor(frameNode);
    (*values)[NUM_0] = colors.topColor->GetValue();
    (*values)[NUM_1] = colors.rightColor->GetValue();
    (*values)[NUM_2] = colors.bottomColor->GetValue();
    (*values)[NUM_3] = colors.leftColor->GetValue();
}

void GetBorderStyle(ArkUINodeHandle node, ArkUI_Int32 (*values)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto styles = ViewAbstract::GetBorderStyle(frameNode);
    (*values)[NUM_0] = static_cast<ArkUI_Int32>(styles.styleTop.value());
    (*values)[NUM_1] = static_cast<ArkUI_Int32>(styles.styleRight.value());
    (*values)[NUM_2] = static_cast<ArkUI_Int32>(styles.styleBottom.value());
    (*values)[NUM_3] = static_cast<ArkUI_Int32>(styles.styleLeft.value());
}

ArkUI_Int32 GetZIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetZIndex(frameNode);
}

ArkUI_Int32 GetVisibility(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Int32>(ViewAbstract::GetVisibility(frameNode));
}

ArkUI_Int32 GetClip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Int32>(ViewAbstract::GetClip(frameNode));
}

void GetClipShape(ArkUINodeHandle node, ArkUIClipShapeOptions* options, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto basicShape = ViewAbstract::GetClipShape(frameNode);
    options->width = basicShape->GetWidth().GetNativeValue(static_cast<DimensionUnit>(unit));
    options->height = basicShape->GetHeight().GetNativeValue(static_cast<DimensionUnit>(unit));
    options->type = static_cast<ArkUI_Int32>(basicShape->GetBasicShapeType());
    switch (basicShape->GetBasicShapeType()) {
        case BasicShapeType::PATH: {
            auto path = AceType::DynamicCast<Path>(basicShape);
            options->commands = path->GetValue().c_str();
            break;
        }
        case BasicShapeType::RECT: {
            auto shapeRect = AceType::DynamicCast<ShapeRect>(basicShape);
            //radiusWidth
            options->radiusWidth =
                shapeRect->GetTopLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
            //radiusHeight
            options->radiusHeight =
                shapeRect->GetTopLeftRadius().GetY().GetNativeValue(static_cast<DimensionUnit>(unit));
            //topLeftRadius
            options->topLeftRadius =
                shapeRect->GetTopLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
            //bottomLeftRadius
            options->bottomLeftRadius =
                shapeRect->GetBottomLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
            //topRightRadius
            options->topRightRadius =
                shapeRect->GetTopRightRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
            //bottomRightRadius
            options->bottomRightRadius =
                shapeRect->GetBottomRightRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
            break;
        }
        default:
            break;
    }
}

void GetTransform(ArkUINodeHandle node, ArkUI_Float32 (*values)[16])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto transforms = ViewAbstract::GetTransform(frameNode);
    for (int i = 0; i < NUM_16; i++) {
        (*values)[i] = transforms[i];
    }
}

ArkUI_Int32 GetHitTestBehavior(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ViewAbstract::GetHitTestBehavior(frameNode));
}

void GetPosition(ArkUINodeHandle node, ArkUIPositionOptions* values, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto positions = ViewAbstract::GetPosition(frameNode);
    values->x = positions.GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
    values->y = positions.GetY().GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Int32 GetShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    int style = static_cast<ArkUI_Int32>(ViewAbstract::GetShadow(frameNode)->GetStyle());
    return style;
}

void GetCustomShadow(ArkUINodeHandle node, ArkUICustomShadowOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadow = ViewAbstract::GetShadow(frameNode);
    options->color = shadow->GetColor().GetValue();
    options->shadowType = static_cast<ArkUI_Int32>(shadow->GetShadowType());
    options->colorStrategy = static_cast<ArkUI_Int32>(shadow->GetShadowColorStrategy());
    options->offsetX = shadow->GetOffset().GetX();
    options->offsetY = shadow->GetOffset().GetY();
    options->radius = shadow->GetBlurRadius();
    options->fill = static_cast<ArkUI_Int32>(shadow->GetIsFilled());
}

ArkUI_Int32 GetSweepGradient(ArkUINodeHandle node, ArkUI_Float32 (*values)[6], ArkUI_Uint32 (*colors)[10],
    ArkUI_Float32 (*stops)[10], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto gradient = ViewAbstract::GetSweepGradient(frameNode);
    auto sweepGradient = gradient.GetSweepGradient();

    (*values)[NUM_0] = sweepGradient->centerX->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = sweepGradient->centerY->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = sweepGradient->startAngle->Value();
    (*values)[NUM_3] = sweepGradient->endAngle->Value();
    (*values)[NUM_4] = sweepGradient->rotation->Value();
    (*values)[NUM_5] = gradient.GetRepeat();

    std::vector<GradientColor> gradientColors = gradient.GetColors();
    //0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        (*colors)[index] = gradientColor.GetColor().GetValue();
        (*stops)[index] = gradientColor.GetDimension().Value();
        index++;
    }
    return index;
}

ArkUI_Int32 GetRadialGradient(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Uint32 (*colors)[10],
    ArkUI_Float32 (*stops)[10], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto gradient = ViewAbstract::GetRadialGradient(frameNode);
    auto radialGradient = gradient.GetRadialGradient();

    CHECK_NULL_RETURN(radialGradient, ERROR_INT_CODE);
    (*values)[NUM_0] = radialGradient->radialCenterX->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = radialGradient->radialCenterY->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] =
        gradient.GetRadialGradient()->radialHorizontalSize->GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = gradient.GetRepeat();

    std::vector<GradientColor> gradientColors = gradient.GetColors();
    //0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        (*colors)[index] = gradientColor.GetColor().GetValue();
        (*stops)[index] = gradientColor.GetDimension().Value();
        index++;
    }
    return index;
}

void GetMask(ArkUINodeHandle node, ArkUIMaskOptions* options, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto basicShape = ViewAbstract::GetMask(frameNode);
    if (basicShape == nullptr) {
        auto process = ViewAbstract::GetMaskProgress(frameNode);
        CHECK_NULL_VOID(process);
        options->type = static_cast<ArkUI_Int32>(ArkUI_MaskType::ARKUI_MASK_TYPE_PROGRESS);
        options->value = process->GetValue();
        options->color = process->GetColor().GetValue();
        options->maxValue = process->GetMaxValue();
        return;
    }
    options->type = static_cast<ArkUI_Int32>(basicShape->GetBasicShapeType());
    options->fill = basicShape->GetColor().GetValue();
    options->strokeColor = basicShape->GetStrokeColor();
    options->strokeWidth = basicShape->GetStrokeWidth();
    options->width = basicShape->GetWidth().GetNativeValue(static_cast<DimensionUnit>(unit));
    options->height = basicShape->GetHeight().GetNativeValue(static_cast<DimensionUnit>(unit));
    if (basicShape->GetBasicShapeType() == BasicShapeType::PATH) {
        auto path = AceType::DynamicCast<Path>(basicShape);
        options->commands = path->GetValue().c_str();
    } else if (basicShape->GetBasicShapeType() == BasicShapeType::RECT) {
        auto shapeRect = AceType::DynamicCast<ShapeRect>(basicShape);
        options->radiusWidth =
            shapeRect->GetTopLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
        options->radiusHeight =
            shapeRect->GetTopLeftRadius().GetY().GetNativeValue(static_cast<DimensionUnit>(unit));
        options->topLeftRadius =
            shapeRect->GetTopLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
        options->bottomLeftRadius =
            shapeRect->GetBottomLeftRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
        options->topRightRadius =
            shapeRect->GetTopRightRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
        options->bottomRightRadius =
            shapeRect->GetBottomRightRadius().GetX().GetNativeValue(static_cast<DimensionUnit>(unit));
    }
}

void GetBlendMode(ArkUINodeHandle node, ArkUIBlendModeOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    options->blendMode = static_cast<ArkUI_Int32>(ViewAbstract::GetBlendMode(frameNode));
    options->blendApplyType = static_cast<ArkUI_Int32>(ViewAbstract::GetBlendApplyType(frameNode));
}

ArkUI_Int32 GetDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    int direction = static_cast<ArkUI_Int32>(ViewAbstract::GetDirection(frameNode));
    return direction;
}

ArkUI_Int32 GetAlignSelf(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    int alignSelf = static_cast<ArkUI_Int32>(ViewAbstract::GetAlignSelf(frameNode));
    return alignSelf;
}

ArkUI_Float32 GetFlexGrow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetFlexGrow(frameNode);
}

ArkUI_Float32 GetFlexShrink(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetFlexShrink(frameNode);
}

ArkUI_Float32 GetFlexBasis(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetFlexBasis(frameNode).Value();
}

void GetConstraintSize(ArkUINodeHandle node, ArkUIConstraintSizeOptions* options, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    options->minWidth = ViewAbstract::GetMinWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
    options->maxWidth = ViewAbstract::GetMaxWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
    options->minHeight = ViewAbstract::GetMinHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
    options->maxHeight = ViewAbstract::GetMaxHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetGrayScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetGrayScale(frameNode).Value();
}

ArkUI_Float32 GetInvert(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return std::get<float>(ViewAbstract::GetInvert(frameNode));
}

ArkUI_Float32 GetSepia(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetSepia(frameNode).Value();
}

ArkUI_Float32 GetContrast(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetContrast(frameNode).Value();
}

ArkUI_Uint32 GetForegroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetForegroundColor(frameNode).GetValue();
}

ArkUI_Float32 GetBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetFrontBlur(frameNode).Value();
}

ArkUI_Int32 GetLinearGradient(
    ArkUINodeHandle node, ArkUI_Float32 (*values)[3], ArkUI_Uint32 (*colors)[10], ArkUI_Float32 (*stop)[10])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto gradient = ViewAbstract::GetLinearGradient(frameNode);
    auto angle = gradient.GetLinearGradient()->angle;
    //0 angle
    (*values)[0] = angle.has_value() ? angle.value().Value() : DEFAULT_ANGLE;
    //1 Direction
    (*values)[1] = static_cast<int32_t>(convertToLinearGradientDirection(gradient.GetLinearGradient()));
    //2 Repeat
    (*values)[2] = gradient.GetRepeat();

    std::vector<GradientColor> gradientColors = gradient.GetColors();
    //0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        (*colors)[index] = gradientColor.GetColor().GetValue();
        (*stop)[index] = gradientColor.GetDimension().Value();
        index++;
    }
    return index;
}

ArkUI_Int32 GetAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return ConvertAlignmentToInt(ViewAbstract::GetAlign(frameNode));
}

ArkUI_Float32 GetWidth(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetHeight(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Uint32 GetBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetBackgroundColor(frameNode).GetValue();
}

void GetBackgroundImage(ArkUINodeHandle node, ArkUIBackgroundImage* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    g_strValue = ViewAbstract::GetBackgroundImageSrc(frameNode);
    options->src = g_strValue.c_str();
    options->repeat = static_cast<int>(ViewAbstract::GetBackgroundImageRepeat(frameNode));
}

void GetPadding(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto padding = ViewAbstract::GetPadding(frameNode);
    (*values)[NUM_0] = padding.top->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = padding.right->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = padding.bottom->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = padding.left->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    length = NUM_4;
}

void GetPaddingDimension(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 (*units)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto padding = ViewAbstract::GetPadding(frameNode);
    (*values)[NUM_0] = padding.top->GetDimension().Value();
    (*units)[NUM_0] = static_cast<ArkUI_Int32>(padding.top->GetDimension().Unit());
    (*values)[NUM_1] = padding.right->GetDimension().Value();
    (*units)[NUM_1] = static_cast<ArkUI_Int32>(padding.right->GetDimension().Unit());
    (*values)[NUM_2] = padding.bottom->GetDimension().Value();
    (*units)[NUM_2] = static_cast<ArkUI_Int32>(padding.bottom->GetDimension().Unit());
    (*values)[NUM_3] = padding.left->GetDimension().Value();
    (*units)[NUM_3] = static_cast<ArkUI_Int32>(padding.left->GetDimension().Unit());
}

void GetConfigSize(ArkUINodeHandle node, ArkUI_Float32 (*values)[2], ArkUI_Int32 (*units)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = ViewAbstract::GetConfigSize(frameNode);
    (*values)[NUM_0] = size->Width()->GetDimension().Value();
    (*units)[NUM_0] = static_cast<ArkUI_Int32>(size->Width()->GetDimension().Unit());
    (*values)[NUM_1] = size->Height()->GetDimension().Value();
    (*units)[NUM_1] = static_cast<ArkUI_Int32>(size->Height()->GetDimension().Unit());
}

ArkUI_CharPtr GetKey(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = ViewAbstract::GetKey(frameNode);
    return g_strValue.c_str();
}

int GetEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ViewAbstract::GetEnabled(frameNode));
}

void GetMargin(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto margin = ViewAbstract::GetMargin(frameNode);
    (*values)[NUM_0] = margin.top->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = margin.right->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = margin.bottom->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = margin.left->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    length = NUM_4;
}

void GetMarginDimension(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 (*units)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto margin = ViewAbstract::GetMargin(frameNode);
    (*values)[NUM_0] = margin.top->GetDimension().Value();
    (*units)[NUM_0] = static_cast<ArkUI_Int32>(margin.top->GetDimension().Unit());
    (*values)[NUM_1] = margin.right->GetDimension().Value();
    (*units)[NUM_1] = static_cast<ArkUI_Int32>(margin.right->GetDimension().Unit());
    (*values)[NUM_2] = margin.bottom->GetDimension().Value();
    (*units)[NUM_2] = static_cast<ArkUI_Int32>(margin.bottom->GetDimension().Unit());
    (*values)[NUM_3] = margin.left->GetDimension().Value();
    (*units)[NUM_3] = static_cast<ArkUI_Int32>(margin.left->GetDimension().Unit());
}

void GetTranslate(ArkUINodeHandle node, ArkUI_Float32 (*values)[3], ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto translate = ViewAbstract::GetTranslate(frameNode);
    (*values)[NUM_0] = translate.x.GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = translate.y.GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = translate.z.GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetAspectRatio(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ViewAbstract::GetAspectRatio(frameNode);
}

void SetBackgroundImageSizeWithUnit(
    ArkUINodeHandle node, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    CalcDimension width(valueWidth, static_cast<DimensionUnit>(unit));
    CalcDimension height(valueHeight, static_cast<DimensionUnit>(unit));
    bgImgSize.SetSizeTypeX(OHOS::Ace::BackgroundImageSizeType::LENGTH);
    bgImgSize.SetSizeValueX(width.GetNativeValue(DimensionUnit::PX));
    bgImgSize.SetSizeTypeY(OHOS::Ace::BackgroundImageSizeType::LENGTH);
    bgImgSize.SetSizeValueY(height.GetNativeValue(DimensionUnit::PX));
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void SetChainStyle(ArkUINodeHandle node, ArkUI_Int32 direction, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ChainInfo chainInfo;
    chainInfo.direction = static_cast<LineDirection>(direction);
    chainInfo.style = static_cast<ChainStyle>(style);
    ViewAbstract::SetChainStyle(frameNode, chainInfo);
}

void GetChainStyle(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto chainInfo = ViewAbstract::GetChainStyle(frameNode);
    // 0 index is direction
    if (chainInfo.direction.has_value()) {
        (*values)[0] = static_cast<ArkUI_Int32>(chainInfo.direction.value());
    } else {
        (*values)[0] = -1;
    }
    // 1 index is style
    if (chainInfo.style.has_value()) {
        (*values)[1] = static_cast<ArkUI_Int32>(chainInfo.style.value());
    } else {
        (*values)[1] = -1;
    }
}

void ResetChainStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetChainStyle(frameNode);
}

void SetBias(ArkUINodeHandle node, ArkUI_Float32 horizontal, ArkUI_Float32 vertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BiasPair pair1(horizontal, vertical);
    ViewAbstract::SetBias(frameNode, pair1);
}

void GetBias(ArkUINodeHandle node, ArkUI_Float32* values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto bias = ViewAbstract::GetBias(frameNode);
    //horizontal
    values[0] = bias.first;
    //vertical
    values[1] = bias.second;
}

void ResetBias(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetBias(frameNode);
}
void SetOnVisibleAreaChange(ArkUINodeHandle node, ArkUI_Int64 extraParam, ArkUI_Float32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    std::vector<double> ratioList(values, values + size);
    auto onEvent = [nodeId, extraParam](bool visible, double ratio) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = static_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_VISIBLE_AREA_CHANGE;
        event.componentAsyncEvent.data[0].i32 = visible;
        event.componentAsyncEvent.data[1].f32 = static_cast<ArkUI_Float32>(ratio);
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnVisibleChange(frameNode, onEvent, ratioList);
}

void SetLayoutRect(ArkUINodeHandle node, ArkUI_Int32 (*values)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto rect =
        NG::RectF((*values)[0], (*values)[1], (*values)[2], (*values)[3]); // 2:index of width, 3:index of height
    ViewAbstract::SetLayoutRect(frameNode, rect);
}

void GetLayoutRect(ArkUINodeHandle node, ArkUI_Int32 (*values)[4])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto rect = ViewAbstract::GetLayoutRect(frameNode);
    (*values)[0] = rect.GetX();
    (*values)[1] = rect.GetY();
    (*values)[2] = rect.Width(); // 2:index of width
    (*values)[3] = rect.Height(); // 3:index of height
}

void ResetLayoutRect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    ViewAbstract::ResetLayoutRect(frameNode);
}

void SetSystemBarEffect(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSystemBarEffect(frameNode, enable);
}

ArkUI_Int32 GetAccessibilityID(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    ArkUI_Int32 value = frameNode->GetAccessibilityId();
    return value;
}

void SetAccessibilityState(ArkUINodeHandle node, const ArkUIAccessibilityState& state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (state.isDisabled.isSet) {
        accessibilityProperty->SetUserDisabled(state.isDisabled.value);
    }
    if (state.isSelected.isSet) {
        accessibilityProperty->SetUserSelected(state.isSelected.value);
    }
    if (state.checkedType.isSet) {
        accessibilityProperty->SetUserCheckedType(state.checkedType.value);
    }
}

void GetAccessibilityState(ArkUINodeHandle node, ArkUIAccessibilityState& state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    state.isDisabled.isSet = accessibilityProperty->HasUserDisabled();
    state.isDisabled.value = accessibilityProperty->IsUserDisabled();
    state.isSelected.isSet = accessibilityProperty->HasUserSelected();
    state.isSelected.value = accessibilityProperty->IsUserSelected();
    state.checkedType.isSet = accessibilityProperty->HasUserCheckedType();
    state.checkedType.value = accessibilityProperty->GetUserCheckedType();
}

void ResetAccessibilityState(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (accessibilityProperty->HasUserDisabled()) {
        accessibilityProperty->SetUserDisabled(false);
    }
    if (accessibilityProperty->HasUserSelected()) {
        accessibilityProperty->SetUserSelected(false); 
    }
    if (accessibilityProperty->HasUserCheckedType()) {
        accessibilityProperty->SetUserCheckedType(0);
    }
}

void SetAccessibilityValue(ArkUINodeHandle node, const ArkUIAccessibilityValue& value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (value.min.isSet) {
        accessibilityProperty->SetUserMinValue(value.min.value);
    }
    if (value.max.isSet) {
        accessibilityProperty->SetUserMaxValue(value.max.value);
    }
    if (value.current.isSet) {
        accessibilityProperty->SetUserCurrentValue(value.current.value);
    }
    if (value.rangeMin.isSet) {
        accessibilityProperty->SetUserRangeMinValue(value.rangeMin.value);
    }
    if (value.rangeMax.isSet) {
        accessibilityProperty->SetUserRangeMaxValue(value.rangeMax.value);
    }
    if (value.rangeCurrent.isSet) {
        accessibilityProperty->SetUserRangeCurrentValue(value.rangeCurrent.value);
    }
    if (value.text.isSet) {
        accessibilityProperty->SetUserTextValue(value.text.value);
    }
}

void GetAccessibilityValue(ArkUINodeHandle node, ArkUIAccessibilityValue& value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    value.min.isSet = accessibilityProperty->HasUserMinValue();
    value.min.value = accessibilityProperty->GetUserMinValue();
    value.max.isSet = accessibilityProperty->HasUserMaxValue();
    value.max.value = accessibilityProperty->GetUserMaxValue();
    value.current.isSet = accessibilityProperty->HasUserCurrentValue();
    value.current.value = accessibilityProperty->GetUserCurrentValue();
    value.rangeMin.isSet = accessibilityProperty->HasUserRangeMinValue();
    value.rangeMin.value = accessibilityProperty->GetUserRangeMinValue();
    value.rangeMax.isSet = accessibilityProperty->HasUserRangeMaxValue();
    value.rangeMax.value = accessibilityProperty->GetUserRangeMaxValue();
    value.rangeCurrent.isSet = accessibilityProperty->HasUserRangeCurrentValue();
    value.rangeCurrent.value = accessibilityProperty->GetUserRangeCurrentValue();
    value.text.isSet = accessibilityProperty->HasUserTextValue();
    g_strValue = accessibilityProperty->GetUserTextValue();
    value.text.value = g_strValue.c_str();
}

void ResetAccessibilityValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (accessibilityProperty->HasUserMinValue()) {
        accessibilityProperty->SetUserMinValue(-1);
    }
    if (accessibilityProperty->HasUserMaxValue()) {
        accessibilityProperty->SetUserMaxValue(-1);
    }
    if (accessibilityProperty->HasUserCurrentValue()) {
        accessibilityProperty->SetUserCurrentValue(-1);
    }
    if (accessibilityProperty->HasUserRangeMinValue()) {
        accessibilityProperty->SetUserRangeMinValue(-1);
    }
    if (accessibilityProperty->HasUserRangeMaxValue()) {
        accessibilityProperty->SetUserRangeMaxValue(-1);
    }
    if (accessibilityProperty->HasUserRangeCurrentValue()) {
        accessibilityProperty->SetUserRangeCurrentValue(-1);
    }
    if (accessibilityProperty->HasUserTextValue()) {
        accessibilityProperty->SetUserTextValue("");
    }
}

void SetAccessibilityActions(ArkUINodeHandle node, ArkUI_Uint32 actions)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityActions(actions);
}

void ResetAccessibilityActions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->ResetAccessibilityActions();
}

ArkUI_Uint32 GetAccessibilityActions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    return accessibilityProperty->GetAccessibilityActions();
}

void SetAccessibilityRole(ArkUINodeHandle node, ArkUI_CharPtr role)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityRole(std::string(role));
}

void ResetAccessibilityRole(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->ResetAccessibilityRole();
}

ArkUI_CharPtr GetAccessibilityRole(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    g_strValue = accessibilityProperty->GetAccessibilityRole();
    return g_strValue.c_str();
}

void SetFocusScopeId(ArkUINodeHandle node, ArkUI_CharPtr id, ArkUI_Bool isGroup, ArkUI_Bool arrowKeyStepOut)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string idStr = id;
    ViewAbstract::SetFocusScopeId(frameNode, idStr, isGroup, arrowKeyStepOut);
}

void ResetFocusScopeId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string id = "";
    bool isGroup = false;
    bool arrowKeyStepOut = true;
    ViewAbstract::SetFocusScopeId(frameNode, id, isGroup, arrowKeyStepOut);
}

void SetFocusScopePriority(ArkUINodeHandle node, ArkUI_CharPtr scopeId, ArkUI_Int32 priority)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string scopeIdStr = scopeId;
    ViewAbstract::SetFocusScopePriority(frameNode, scopeIdStr, priority);
}

void ResetFocusScopePriority(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string scopeId = "";
    int32_t priority = 0;
    ViewAbstract::SetFocusScopePriority(frameNode, scopeId, priority);
}

PixelRoundPolicy ConvertCeilPixelRoundPolicy(ArkUI_Int32 index)
{
    PixelRoundPolicy ret = static_cast<PixelRoundPolicy>(0);
    switch (index) {
        case 0:
            ret = PixelRoundPolicy::FORCE_CEIL_START;
            break;
        case 1:
            ret = PixelRoundPolicy::FORCE_CEIL_TOP;
            break;
        case 2: // 2:index of end
            ret = PixelRoundPolicy::FORCE_CEIL_END;
            break;
        case 3: // 3:index of bottom
            ret = PixelRoundPolicy::FORCE_CEIL_BOTTOM;
            break;
        default:
            break;
    }
    return ret;
}

PixelRoundPolicy ConvertFloorPixelRoundPolicy(ArkUI_Int32 index)
{
    PixelRoundPolicy ret = static_cast<PixelRoundPolicy>(0);
    switch (index) {
        case 0:
            ret = PixelRoundPolicy::FORCE_FLOOR_START;
            break;
        case 1:
            ret = PixelRoundPolicy::FORCE_FLOOR_TOP;
            break;
        case 2: // 2:index of end
            ret = PixelRoundPolicy::FORCE_FLOOR_END;
            break;
        case 3: // 3:index of bottom
            ret = PixelRoundPolicy::FORCE_FLOOR_BOTTOM;
            break;
        default:
            break;
    }
    return ret;
}

PixelRoundPolicy ConvertNoPixelRoundPolicy(ArkUI_Int32 index)
{
    switch (index) {
        case 0:
            return PixelRoundPolicy::NO_FORCE_ROUND_START;
        case 1:
            return PixelRoundPolicy::NO_FORCE_ROUND_TOP;
        case 2: // 2:index of end
            return PixelRoundPolicy::NO_FORCE_ROUND_END;
        case 3: // 3:index of bottom
            return PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM;
        default:
            return PixelRoundPolicy::ALL_FORCE_ROUND;
    }
}

uint16_t ConvertPixelRoundPolicy(ArkUI_Int32 value, ArkUI_Int32 index)
{
    auto tmp = static_cast<PixelRoundCalcPolicy>(value);
    PixelRoundPolicy ret = static_cast<PixelRoundPolicy>(0);
    if (tmp == PixelRoundCalcPolicy::FORCE_CEIL) {
        ret = ConvertCeilPixelRoundPolicy(index);
    } else if (tmp == PixelRoundCalcPolicy::FORCE_FLOOR) {
        ret = ConvertFloorPixelRoundPolicy(index);
    } else if (tmp == PixelRoundCalcPolicy::NO_FORCE_ROUND) {
        ret = ConvertNoPixelRoundPolicy(index);
    }
    return static_cast<uint16_t>(ret);
}

void SetPixelRound(ArkUINodeHandle node, const ArkUI_Int32* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    uint16_t value = 0;
    for (ArkUI_Int32 index = 0; index < length; index++) {
        value |= ConvertPixelRoundPolicy(values[index], index);
    }
    ViewAbstract::SetPixelRound(frameNode, value);
}

void ResetPixelRound(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPixelRound(frameNode, static_cast<uint16_t>(PixelRoundCalcPolicy::NO_FORCE_ROUND));
}

RefPtr<NG::ChainedTransitionEffect> ParseTransition(ArkUITransitionEffectOption* option)
{
    CHECK_NULL_RETURN(option, nullptr);
    auto type = static_cast<TransitionEffectType>(option->type);
    RefPtr<NG::ChainedTransitionEffect> transitionEffect;
    switch (type) {
        case TransitionEffectType::TRANSITION_EFFECT_OPACITY: {
            transitionEffect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(option->opacity);
            break;
        }

        case TransitionEffectType::TRANSITION_EFFECT_TRANSLATE: {
            CalcDimension x(option->translate.x, DimensionUnit::VP);
            CalcDimension y(option->translate.y, DimensionUnit::VP);
            CalcDimension z(option->translate.z, DimensionUnit::VP);
            NG::TranslateOptions translate(x, y, z);
            transitionEffect = AceType::MakeRefPtr<NG::ChainedTranslateEffect>(translate);
            break;
        }

        case TransitionEffectType::TRANSITION_EFFECT_SCALE: {
            CalcDimension centerX(option->scale.centerX, DimensionUnit::PERCENT);
            CalcDimension centerY(option->scale.centerY, DimensionUnit::PERCENT);
            NG::ScaleOptions scale(option->scale.x, option->scale.y, option->scale.z, centerX, centerY);
            transitionEffect = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
            break;
        }

        case TransitionEffectType::TRANSITION_EFFECT_ROTATE: {
            CalcDimension centerX(option->rotate.centerX, DimensionUnit::PERCENT);
            CalcDimension centerY(option->rotate.centerY, DimensionUnit::PERCENT);
            CalcDimension centerZ(option->rotate.centerZ, DimensionUnit::PERCENT);
            NG::RotateOptions rotate(option->rotate.x, option->rotate.y, option->rotate.z, option->rotate.angle,
                centerX, centerY, centerZ, option->rotate.perspective);
            transitionEffect = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
            break;
        }

        case TransitionEffectType::TRANSITION_EFFECT_MOVE: {
            transitionEffect =
                AceType::MakeRefPtr<NG::ChainedMoveEffect>(static_cast<NG::TransitionEdge>(option->move));
            break;
        }

        case TransitionEffectType::TRANSITION_EFFECT_ASYMMETRIC: {
            RefPtr<NG::ChainedTransitionEffect> appearEffect;
            RefPtr<NG::ChainedTransitionEffect> disappearEffect;
            if (option->appear) {
                appearEffect = ParseTransition(option->appear);
            }
            if (option->disappear) {
                disappearEffect = ParseTransition(option->disappear);
            }
            transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearEffect, disappearEffect);
            break;
        }
    }

    CHECK_NULL_RETURN(transitionEffect, nullptr);

    if (option->hasAnimation) {
        auto animation = option->animation;
        AnimationOption animationOption;
        animationOption.SetDuration(animation.duration);
        animationOption.SetDelay(animation.delay);
        animationOption.SetIteration(animation.iterations);
        animationOption.SetTempo(animation.tempo);
        animationOption.SetAnimationDirection(DIRECTION_LIST[
            static_cast<ArkUI_Uint32>(animation.playMode) > DIRECTION_LIST.size() ? 0 : animation.playMode]);

        // curve
        if (animation.iCurve) {
            auto curve = reinterpret_cast<Curve*>(animation.iCurve);
            animationOption.SetCurve(AceType::Claim(curve));
        } else {
            if (animation.curve < 0 || static_cast<ArkUI_Uint32>(animation.curve) >= CURVES.size()) {
                animationOption.SetCurve(OHOS::Ace::Curves::EASE_IN_OUT);
            } else {
                animationOption.SetCurve(CURVES[animation.curve]);
            }
        }

        if (animation.expectedFrameRateRange) {
            RefPtr<FrameRateRange> frameRateRange =
                AceType::MakeRefPtr<FrameRateRange>(animation.expectedFrameRateRange->min,
                    animation.expectedFrameRateRange->max, animation.expectedFrameRateRange->expected);
            animationOption.SetFrameRateRange(frameRateRange);
        }
        auto animationOptionResult = std::make_shared<AnimationOption>(animationOption);
        transitionEffect->SetAnimationOption(animationOptionResult);
    }

    if (option->combine) {
        transitionEffect->SetNext(ParseTransition(option->combine));
    }
    return transitionEffect;
}

void SetTransition(ArkUINodeHandle node, ArkUITransitionEffectOption* option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto transitionEffectOption = ParseTransition(option);
    CHECK_NULL_VOID(transitionEffectOption);
    ViewAbstract::SetChainedTransition(frameNode, transitionEffectOption);
}

void SetDragPreview(ArkUINodeHandle node, ArkUIDragPreview dragPreview)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DragDropInfo dragPreviewInfo;
    dragPreviewInfo.inspectorId = dragPreview.inspectorId;
    ViewAbstract::SetDragPreview(frameNode, dragPreviewInfo);
}

void ResetDragPreview(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DragDropInfo dragPreviewInfo;
    ViewAbstract::SetDragPreview(frameNode, dragPreviewInfo);
}

void GetExpandSafeArea(ArkUINodeHandle node, ArkUI_Uint32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    (*values)[NUM_0] = ViewAbstract::GetSafeAreaExpandType(frameNode);
    (*values)[NUM_1] = ViewAbstract::GetSafeAreaExpandEdges(frameNode);
}

void SetBorderDashParams(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_36)) {
        return;
    }
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    int32_t offset = NUM_0;
    NG::BorderWidthProperty borderDashGap;
    SetOptionalBorder(borderDashGap.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashGap.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashGap.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashGap.bottomDimen, values, valuesSize, offset);
    if (isRightToLeft) {
        SetOptionalBorder(borderDashGap.rightDimen, values, valuesSize, offset);
        SetOptionalBorder(borderDashGap.leftDimen, values, valuesSize, offset);
    } else {
        SetOptionalBorder(borderDashGap.leftDimen, values, valuesSize, offset);
        SetOptionalBorder(borderDashGap.rightDimen, values, valuesSize, offset);
    }
    borderDashGap.multiValued = true;
    if (borderDashGap.leftDimen.has_value() || borderDashGap.rightDimen.has_value() ||
        borderDashGap.topDimen.has_value() || borderDashGap.bottomDimen.has_value()) {
        ViewAbstract::SetDashGap(frameNode, borderDashGap);
    } else {
        ViewAbstract::SetDashGap(frameNode, Dimension(DEFAULT_DASH_DIMENSION));
    }

    NG::BorderWidthProperty borderDashWidth;
    SetOptionalBorder(borderDashWidth.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashWidth.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderDashWidth.bottomDimen, values, valuesSize, offset);
    if (isRightToLeft) {
        SetOptionalBorder(borderDashWidth.rightDimen, values, valuesSize, offset);
        SetOptionalBorder(borderDashWidth.leftDimen, values, valuesSize, offset);
    } else {
        SetOptionalBorder(borderDashWidth.leftDimen, values, valuesSize, offset);
        SetOptionalBorder(borderDashWidth.rightDimen, values, valuesSize, offset);
    }
    borderDashWidth.multiValued = true;
    if (borderDashWidth.leftDimen.has_value() || borderDashWidth.rightDimen.has_value() ||
        borderDashWidth.topDimen.has_value() || borderDashWidth.bottomDimen.has_value()) {
        ViewAbstract::SetDashWidth(frameNode, borderDashWidth);
    } else {
        ViewAbstract::SetDashWidth(frameNode, Dimension(DEFAULT_DASH_DIMENSION));
    }
}

ArkUI_Int32 GetNodeUniqueId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    return frameNode->GetId();
}

void SetFocusBoxStyle(ArkUINodeHandle node, ArkUI_Float32 valueMargin, ArkUI_Int32 marginUnit,
    ArkUI_Float32 valueStrokeWidth, ArkUI_Int32 widthUnit, ArkUI_Uint32 valueColor, ArkUI_Uint32 hasValue)
{
    CHECK_NULL_VOID(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto marginUnitEnum = static_cast<OHOS::Ace::DimensionUnit>(marginUnit);
    auto widthUnitEnum = static_cast<OHOS::Ace::DimensionUnit>(widthUnit);
    NG::FocusBoxStyle style;
    if ((hasValue >> 2) & 1) { // 2: margin
        CalcDimension margin = CalcDimension(valueMargin, DimensionUnit::FP);
        if (marginUnitEnum >= OHOS::Ace::DimensionUnit::PX && marginUnitEnum <= OHOS::Ace::DimensionUnit::CALC &&
            marginUnitEnum != OHOS::Ace::DimensionUnit::PERCENT) {
            margin.SetUnit(marginUnitEnum);
        }
        style.margin = margin;
    }
    if ((hasValue >> 1) & 1) { // 1: strokeWidth
        CalcDimension strokeWidth = CalcDimension(valueStrokeWidth, DimensionUnit::FP);
        if (widthUnitEnum >= OHOS::Ace::DimensionUnit::PX && widthUnitEnum <= OHOS::Ace::DimensionUnit::CALC &&
            widthUnitEnum != OHOS::Ace::DimensionUnit::PERCENT) {
            strokeWidth.SetUnit(widthUnitEnum);
        }
        style.strokeWidth = strokeWidth;
    }
    if ((hasValue >> 0) & 1) { // 0: strokeColor
        Color strokeColor(valueColor);
        style.strokeColor = strokeColor;
    }
    ViewAbstract::SetFocusBoxStyle(frameNode, style);
}

void ResetFocusBoxStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::FocusBoxStyle style;
    ViewAbstract::SetFocusBoxStyle(frameNode, style);
}

void SetClickDistance(ArkUINodeHandle node, ArkUI_Float32 valueMargin)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double clickDistance = static_cast<double>(valueMargin);
    ViewAbstract::SetClickDistance(frameNode, clickDistance);
}

void ResetClickDistance(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClickDistance(frameNode, std::numeric_limits<double>::infinity());
}

void SetBlendModeByBlender(ArkUINodeHandle node, ArkUINodeHandle blender, ArkUI_Int32 blendApplyTypeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Rosen::BrightnessBlender* brightnessBlender = reinterpret_cast<OHOS::Rosen::BrightnessBlender*>(blender);
    ViewAbstractModelNG::SetBrightnessBlender(frameNode, brightnessBlender);
    ViewAbstractModelNG::SetBlendApplyType(frameNode, static_cast<OHOS::Ace::BlendApplyType>(blendApplyTypeValue));
}

void SetTabStop(ArkUINodeHandle node, ArkUI_Bool tabstop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTabStop(frameNode, tabstop);
}

void ResetTabStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool tabstop = false;
    ViewAbstract::SetTabStop(frameNode, tabstop);
}

ArkUI_Bool GetTabStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(ViewAbstract::GetTabStop(frameNode));
}

void SetOnClickExt(ArkUINodeHandle node, void (*eventReceiver)(ArkUINodeHandle node, ArkUINodeEvent event))
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto onClick = [node, eventReceiver](GestureEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.componentAsyncEvent.subKind = ON_CLICK;
        auto target = info.GetTarget();
        event.touchEvent.target = { target.id.c_str(), target.type.c_str(),
            { static_cast<ArkUI_Int32>(target.area.GetOffset().GetX().Value()),
                static_cast<ArkUI_Int32>(target.area.GetOffset().GetY().Value()),
                static_cast<ArkUI_Int32>(target.area.GetWidth().Value()),
                static_cast<ArkUI_Int32>(target.area.GetHeight().Value()) },
            { static_cast<ArkUI_Int32>(target.origin.GetX().Value()),
                static_cast<ArkUI_Int32>(target.origin.GetY().Value()) } };
        Offset globalOffset = info.GetGlobalLocation();
        Offset localOffset = info.GetLocalLocation();
        Offset screenOffset = info.GetScreenLocation();
        // x
        event.componentAsyncEvent.data[0].f32 = localOffset.GetX();
        // y
        event.componentAsyncEvent.data[1].f32 = localOffset.GetY();
        // timestamp
        event.componentAsyncEvent.data[2].f32 = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());
        // source
        event.componentAsyncEvent.data[3].i32 = static_cast<int32_t>(info.GetSourceDevice());
        // windowX
        event.componentAsyncEvent.data[4].f32 = globalOffset.GetX();
        // windowY
        event.componentAsyncEvent.data[5].f32 = globalOffset.GetY();
        // displayX
        event.componentAsyncEvent.data[6].f32 = screenOffset.GetX();
        // displayY
        event.componentAsyncEvent.data[7].f32 = screenOffset.GetY();
        eventReceiver(node, event);
    };
    if (uiNode->GetTag() == V2::SPAN_ETS_TAG) {
        SpanModelNG::SetOnClick(uiNode, std::move(onClick));
    } else if (uiNode->GetTag() == V2::TEXT_ETS_TAG) {
        TextModelNG::SetOnClick(reinterpret_cast<FrameNode*>(node), std::move(onClick));
    }  else {
        ViewAbstract::SetOnClick(reinterpret_cast<FrameNode*>(node), std::move(onClick));
    }
}

void SetOnAppearExt(ArkUINodeHandle node, void (*eventReceiver)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onAppear = [node, weak = AceType::WeakClaim(frameNode), eventReceiver]() {
        eventReceiver(node);
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onAppear));
}
} // namespace

namespace NodeModifier {
namespace {
OHOS::Ace::TouchEventInfo globalEventInfo("global");
}

const ArkUICommonModifier* GetCommonModifier()
{
    static const ArkUICommonModifier modifier = { SetBackgroundColor, ResetBackgroundColor, SetWidth, ResetWidth,
        SetHeight, ResetHeight, SetBorderRadius, ResetBorderRadius, SetBorderWidth, ResetBorderWidth, SetTransform,
        ResetTransform, SetBorderColor, ResetBorderColor, SetPosition, ResetPosition, SetPositionEdges,
        ResetPositionEdges, SetBorderStyle, ResetBorderStyle, SetBackShadow, ResetBackShadow, SetHitTestBehavior,
        ResetHitTestBehavior, SetZIndex, ResetZIndex, SetOpacity, ResetOpacity, SetAlign, ResetAlign, SetBackdropBlur,
        ResetBackdropBlur, SetHueRotate, ResetHueRotate, SetInvert, ResetInvert, SetSepia, ResetSepia, SetSaturate,
        ResetSaturate, SetColorBlend, ResetColorBlend, SetGrayscale, ResetGrayscale, SetContrast, ResetContrast,
        SetBrightness, ResetBrightness, SetBlur, ResetBlur, SetLinearGradient, ResetLinearGradient, SetSweepGradient,
        ResetSweepGradient, SetRadialGradient, ResetRadialGradient, SetOverlay, ResetOverlay, SetBorderImage,
        ResetBorderImage, SetBorderImageGradient, SetForegroundBlurStyle, ResetForegroundBlurStyle,
        SetLinearGradientBlur, ResetLinearGradientBlur, SetBackgroundBlurStyle, ResetBackgroundBlurStyle, SetBorder,
        ResetBorder, SetBackgroundImagePosition, ResetBackgroundImagePosition, SetBackgroundImageSize,
        ResetBackgroundImageSize, SetBackgroundImage, ResetBackgroundImage, SetTranslate, ResetTranslate, SetScale,
        SetScaleWithoutTransformCenter, ResetScale, SetRotate, SetRotateWithoutTransformCenter, ResetRotate,
        SetGeometryTransition, ResetGeometryTransition, SetPixelStretchEffect, ResetPixelStretchEffect,
        SetLightUpEffect, ResetLightUpEffect, SetSphericalEffect, ResetSphericalEffect, SetRenderGroup,
        ResetRenderGroup, SetRenderFit, ResetRenderFit, SetUseEffect, ResetUseEffect, SetForegroundColor,
        ResetForegroundColor, SetMotionPath, ResetMotionPath, SetMotionBlur, ResetMotionBlur, SetGroupDefaultFocus,
        ResetGroupDefaultFocus, SetFocusOnTouch, ResetFocusOnTouch, SetFocusable, ResetFocusable, SetTouchable,
        ResetTouchable, SetDefaultFocus, ResetDefaultFocus, SetDisplayPriority, ResetDisplayPriority, SetOffset,
        SetOffsetEdges, ResetOffset, SetPadding, ResetPadding, SetMargin, ResetMargin, SetMarkAnchor, ResetMarkAnchor,
        SetVisibility, ResetVisibility, SetAccessibilityText, ResetAccessibilityText, SetAllowDrop, ResetAllowDrop,
        SetAccessibilityLevel, ResetAccessibilityLevel, SetDirection, ResetDirection, SetLayoutWeight,
        ResetLayoutWeight, SetMinWidth, ResetMinWidth, SetMaxWidth, ResetMaxWidth, SetMinHeight, ResetMinHeight,
        SetMaxHeight, ResetMaxHeight, SetSize, ResetSize, ClearWidthOrHeight, SetAlignSelf, ResetAlignSelf,
        SetAspectRatio, ResetAspectRatio, SetFlexGrow, ResetFlexGrow, SetFlexShrink, ResetFlexShrink, SetGridOffset,
        ResetGridOffset, SetGridSpan, ResetGridSpan, SetExpandSafeArea, ResetExpandSafeArea, SetFlexBasis,
        ResetFlexBasis, SetAlignRules, ResetAlignRules, SetAccessibilityDescription, ResetAccessibilityDescription,
        SetId, ResetId, SetKey, ResetKey, SetRestoreId, ResetRestoreId, SetTabIndex, ResetTabIndex, SetObscured,
        ResetObscured, SetResponseRegion, ResetResponseRegion, SetForegroundEffect, ResetForegroundEffect,
        SetBackgroundEffect, ResetBackgroundEffect, SetBackgroundBrightness, ResetBackgroundBrightness,
        SetBackgroundBrightnessInternal, ResetBackgroundBrightnessInternal, SetForegroundBrightness,
        ResetForegroundBrightness, SetDragPreviewOptions, ResetDragPreviewOptions, SetMouseResponseRegion,
        ResetMouseResponseRegion, SetEnabled, ResetEnabled, SetUseShadowBatching, ResetUseShadowBatching, SetDraggable,
        ResetDraggable, SetAccessibilityGroup, ResetAccessibilityGroup, SetHoverEffect, ResetHoverEffect,
        SetClickEffect, ResetClickEffect, SetKeyBoardShortCut, ResetKeyBoardShortCut, SetPointLightPosition,
        ResetPointLightPosition, SetPointLightIntensity, ResetPointLightIntensity, SetPointLightColor,
        ResetPointLightColor, SetPointLightIlluminated, ResetPointLightIlluminated, SetPointLightBloom,
        ResetPointLightBloom, SetClip, SetClipShape, SetClipPath, ResetClip, SetTransitionCenter, SetOpacityTransition,
        SetRotateTransition, SetScaleTransition, SetTranslateTransition, SetMaskShape, SetMaskPath, SetProgressMask,
        SetBlendMode, ResetBlendMode, SetMonopolizeEvents, ResetMonopolizeEvents, SetConstraintSize,
        ResetConstraintSize, SetOutlineColor, ResetOutlineColor, SetOutlineRadius, ResetOutlineRadius, SetOutlineWidth,
        ResetOutlineWidth, SetOutlineStyle, ResetOutlineStyle, SetOutline, ResetOutline, SetBindPopup, ResetBindPopup,
        GetFocusable, GetDefaultFocus, GetResponseRegion, GetOverlay, GetAccessibilityGroup, GetAccessibilityText,
        GetAccessibilityDescription, GetAccessibilityLevel, SetNeedFocus, GetNeedFocus, GetOpacity, GetBorderWidth,
        GetBorderWidthDimension, GetBorderRadius, GetBorderColor, GetBorderStyle, GetZIndex, GetVisibility, GetClip,
        GetClipShape, GetTransform, GetHitTestBehavior, GetPosition, GetShadow, GetCustomShadow, GetSweepGradient,
        GetRadialGradient, GetMask, GetBlendMode, GetDirection, GetAlignSelf, GetTransformCenter, GetOpacityTransition,
        GetRotateTransition, GetScaleTransition, GetTranslateTransition, GetOffset, GetMarkAnchor, GetAlignRules,
        GetBackgroundBlurStyle, GetBackgroundImageSize, GetBackgroundImageSizeWidthStyle, SetOutlineWidthFloat,
        GetOutlineWidthFloat, GetDisplayPriority, SetAlignRulesWidthType, GetLayoutWeight, GetScale, GetRotate,
        GetBrightness, GetSaturate, GetBackgroundImagePosition, GetFlexGrow, GetFlexShrink, GetFlexBasis,
        GetConstraintSize, GetGrayScale, GetInvert, GetSepia, GetContrast, GetForegroundColor, GetBlur,
        GetLinearGradient, GetAlign, GetWidth, GetHeight, GetBackgroundColor, GetBackgroundImage, GetPadding,
        GetPaddingDimension, GetConfigSize, GetKey, GetEnabled, GetMargin, GetMarginDimension, GetTranslate,
        SetMoveTransition, GetMoveTransition, ResetMask, GetAspectRatio, SetBackgroundImageResizable,
        ResetBackgroundImageResizable, SetBackgroundImageSizeWithUnit, GetRenderFit, GetOutlineColor, GetSize,
        GetRenderGroup, SetOnVisibleAreaChange, GetGeometryTransition, SetChainStyle, GetChainStyle, ResetChainStyle,
        SetBias, GetBias, ResetBias, GetColorBlend, GetForegroundBlurStyle,
        SetBackgroundImagePixelMap, SetBackgroundImagePixelMapByPixelMapPtr,
        SetLayoutRect, GetLayoutRect, ResetLayoutRect, GetFocusOnTouch, SetSystemBarEffect,
        GetAccessibilityID, SetAccessibilityState, GetAccessibilityState, ResetAccessibilityState,
        SetAccessibilityValue, GetAccessibilityValue, ResetAccessibilityValue, SetAccessibilityActions,
        ResetAccessibilityActions, GetAccessibilityActions, SetAccessibilityRole, ResetAccessibilityRole,
        GetAccessibilityRole, SetFocusScopeId, ResetFocusScopeId, SetFocusScopePriority, ResetFocusScopePriority,
        SetPixelRound, ResetPixelRound, SetBorderDashParams, GetExpandSafeArea, SetTransition, SetDragPreview,
        ResetDragPreview, GetNodeUniqueId, SetFocusBoxStyle, ResetFocusBoxStyle, SetClickDistance, ResetClickDistance,
        SetDisAllowDrop, SetBlendModeByBlender, SetTabStop, ResetTabStop, GetTabStop, SetOnClickExt, SetOnAppearExt };

    return &modifier;
}

const CJUICommonModifier* GetCJUICommonModifier()
{
    static const CJUICommonModifier modifier = { SetBackgroundColor, ResetBackgroundColor, SetWidth, ResetWidth,
        SetHeight, ResetHeight, SetBorderRadius, ResetBorderRadius, SetBorderWidth, ResetBorderWidth, SetTransform,
        ResetTransform, SetBorderColor, ResetBorderColor, SetPosition, ResetPosition, SetPositionEdges,
        ResetPositionEdges, SetBorderStyle, ResetBorderStyle, SetBackShadow, ResetBackShadow, SetHitTestBehavior,
        ResetHitTestBehavior, SetZIndex, ResetZIndex, SetOpacity, ResetOpacity, SetAlign, ResetAlign, SetBackdropBlur,
        ResetBackdropBlur, SetHueRotate, ResetHueRotate, SetInvert, ResetInvert, SetSepia, ResetSepia, SetSaturate,
        ResetSaturate, SetColorBlend, ResetColorBlend, SetGrayscale, ResetGrayscale, SetContrast, ResetContrast,
        SetBrightness, ResetBrightness, SetBlur, ResetBlur, SetLinearGradient, ResetLinearGradient, SetSweepGradient,
        ResetSweepGradient, SetRadialGradient, ResetRadialGradient, SetOverlay, ResetOverlay, SetBorderImage,
        ResetBorderImage, SetBorderImageGradient, SetForegroundBlurStyle, ResetForegroundBlurStyle,
        SetLinearGradientBlur, ResetLinearGradientBlur, SetBackgroundBlurStyle, ResetBackgroundBlurStyle, SetBorder,
        ResetBorder, SetBackgroundImagePosition, ResetBackgroundImagePosition, SetBackgroundImageSize,
        ResetBackgroundImageSize, SetBackgroundImage, ResetBackgroundImage, SetTranslate, ResetTranslate, SetScale,
        SetScaleWithoutTransformCenter, ResetScale, SetRotate, SetRotateWithoutTransformCenter, ResetRotate,
        SetGeometryTransition, ResetGeometryTransition, SetPixelStretchEffect, ResetPixelStretchEffect,
        SetLightUpEffect, ResetLightUpEffect, SetSphericalEffect, ResetSphericalEffect, SetRenderGroup,
        ResetRenderGroup, SetRenderFit, ResetRenderFit, SetUseEffect, ResetUseEffect, SetForegroundColor,
        ResetForegroundColor, SetMotionPath, ResetMotionPath, SetMotionBlur, ResetMotionBlur, SetGroupDefaultFocus,
        ResetGroupDefaultFocus, SetFocusOnTouch, ResetFocusOnTouch, SetFocusable, ResetFocusable, SetTouchable,
        ResetTouchable, SetDefaultFocus, ResetDefaultFocus, SetDisplayPriority, ResetDisplayPriority, SetOffset,
        SetOffsetEdges, ResetOffset, SetPadding, ResetPadding, SetMargin, ResetMargin, SetMarkAnchor, ResetMarkAnchor,
        SetVisibility, ResetVisibility, SetAccessibilityText, ResetAccessibilityText, SetAllowDrop, ResetAllowDrop,
        SetAccessibilityLevel, ResetAccessibilityLevel, SetDirection, ResetDirection, SetLayoutWeight,
        ResetLayoutWeight, SetMinWidth, ResetMinWidth, SetMaxWidth, ResetMaxWidth, SetMinHeight, ResetMinHeight,
        SetMaxHeight, ResetMaxHeight, SetSize, ResetSize, ClearWidthOrHeight, SetAlignSelf, ResetAlignSelf,
        SetAspectRatio, ResetAspectRatio, SetFlexGrow, ResetFlexGrow, SetFlexShrink, ResetFlexShrink, SetGridOffset,
        ResetGridOffset, SetGridSpan, ResetGridSpan, SetExpandSafeArea, ResetExpandSafeArea, SetFlexBasis,
        ResetFlexBasis, SetAlignRules, ResetAlignRules, SetAccessibilityDescription, ResetAccessibilityDescription,
        SetId, ResetId, SetKey, ResetKey, SetRestoreId, ResetRestoreId, SetTabIndex, ResetTabIndex, SetObscured,
        ResetObscured, SetResponseRegion, ResetResponseRegion, SetForegroundEffect, ResetForegroundEffect,
        SetBackgroundEffect, ResetBackgroundEffect, SetBackgroundBrightness, ResetBackgroundBrightness,
        SetBackgroundBrightnessInternal, ResetBackgroundBrightnessInternal, SetForegroundBrightness,
        ResetForegroundBrightness, SetDragPreviewOptions, ResetDragPreviewOptions, SetMouseResponseRegion,
        ResetMouseResponseRegion, SetEnabled, ResetEnabled, SetUseShadowBatching, ResetUseShadowBatching, SetDraggable,
        ResetDraggable, SetAccessibilityGroup, ResetAccessibilityGroup, SetHoverEffect, ResetHoverEffect,
        SetClickEffect, ResetClickEffect, SetKeyBoardShortCut, ResetKeyBoardShortCut, SetPointLightPosition,
        ResetPointLightPosition, SetPointLightIntensity, ResetPointLightIntensity, SetPointLightColor,
        ResetPointLightColor, SetPointLightIlluminated, ResetPointLightIlluminated, SetPointLightBloom,
        ResetPointLightBloom, SetClip, SetClipShape, SetClipPath, ResetClip, SetTransitionCenter, SetOpacityTransition,
        SetRotateTransition, SetScaleTransition, SetTranslateTransition, SetMaskShape, SetMaskPath, SetProgressMask,
        SetBlendMode, ResetBlendMode, SetMonopolizeEvents, ResetMonopolizeEvents, SetConstraintSize,
        ResetConstraintSize, SetOutlineColor, ResetOutlineColor, SetOutlineRadius, ResetOutlineRadius, SetOutlineWidth,
        ResetOutlineWidth, SetOutlineStyle, ResetOutlineStyle, SetOutline, ResetOutline, SetBindPopup, ResetBindPopup,
        GetFocusable, GetDefaultFocus, GetResponseRegion, GetOverlay, GetAccessibilityGroup, GetAccessibilityText,
        GetAccessibilityDescription, GetAccessibilityLevel, SetNeedFocus, GetNeedFocus, GetOpacity, GetBorderWidth,
        GetBorderWidthDimension, GetBorderRadius, GetBorderColor, GetBorderStyle, GetZIndex, GetVisibility, GetClip,
        GetClipShape, GetTransform, GetHitTestBehavior, GetPosition, GetShadow, GetCustomShadow, GetSweepGradient,
        GetRadialGradient, GetMask, GetBlendMode, GetDirection, GetAlignSelf, GetTransformCenter, GetOpacityTransition,
        GetRotateTransition, GetScaleTransition, GetTranslateTransition, GetOffset, GetMarkAnchor, GetAlignRules,
        GetBackgroundBlurStyle, GetBackgroundImageSize, GetBackgroundImageSizeWidthStyle, SetOutlineWidthFloat,
        GetOutlineWidthFloat, GetDisplayPriority, SetAlignRulesWidthType, GetLayoutWeight, GetScale, GetRotate,
        GetBrightness, GetSaturate, GetBackgroundImagePosition, GetFlexGrow, GetFlexShrink, GetFlexBasis,
        GetConstraintSize, GetGrayScale, GetInvert, GetSepia, GetContrast, GetForegroundColor, GetBlur,
        GetLinearGradient, GetAlign, GetWidth, GetHeight, GetBackgroundColor, GetBackgroundImage, GetPadding,
        GetPaddingDimension, GetConfigSize, GetKey, GetEnabled, GetMargin, GetMarginDimension, GetTranslate,
        SetMoveTransition, GetMoveTransition, ResetMask, GetAspectRatio, SetBackgroundImageResizable,
        ResetBackgroundImageResizable, SetBackgroundImageSizeWithUnit, GetRenderFit, GetOutlineColor, GetSize,
        GetRenderGroup, SetOnVisibleAreaChange, GetGeometryTransition, SetChainStyle, GetChainStyle, ResetChainStyle,
        SetBias, GetBias, ResetBias, GetColorBlend, GetForegroundBlurStyle,
        SetBackgroundImagePixelMap, SetBackgroundImagePixelMapByPixelMapPtr,
        SetLayoutRect, GetLayoutRect, ResetLayoutRect, GetFocusOnTouch, SetSystemBarEffect,
        GetAccessibilityID, SetAccessibilityState, GetAccessibilityState, ResetAccessibilityState,
        SetAccessibilityValue, GetAccessibilityValue, ResetAccessibilityValue, SetAccessibilityActions,
        ResetAccessibilityActions, GetAccessibilityActions, SetAccessibilityRole, ResetAccessibilityRole,
        GetAccessibilityRole, SetFocusScopeId, ResetFocusScopeId, SetFocusScopePriority, ResetFocusScopePriority,
        SetPixelRound, ResetPixelRound, SetBorderDashParams, GetExpandSafeArea, SetTransition, SetDragPreview,
        ResetDragPreview };

    return &modifier;
}

void SetOnAppear(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onAppear = [node = AceType::WeakClaim(frameNode), nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        event.componentAsyncEvent.subKind = ON_APPEAR;
        PipelineContext::SetCallBackNode(node);
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onAppear));
}

void SetOnDisappear(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDisappear = [node = AceType::WeakClaim(frameNode), nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        event.componentAsyncEvent.subKind = ON_DISAPPEAR;
        PipelineContext::SetCallBackNode(node);
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onDisappear));
}

void SetOnAttach(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onAttach = [node = AceType::WeakClaim(frameNode), nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        event.componentAsyncEvent.subKind = ON_ATTACH;
        PipelineContext::SetCallBackNode(node);
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnAttach(frameNode, std::move(onAttach));
}

void SetOnDetach(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDetach = [node = AceType::WeakClaim(frameNode), nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        event.componentAsyncEvent.subKind = ON_DETACH;
        PipelineContext::SetCallBackNode(node);
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnDetach(frameNode, std::move(onDetach));
}

void SetOnFocus(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_FOCUS;
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}

void SetOnBlur(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_BLUR;
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnBlur(frameNode, std::move(onEvent));
}

void SetOnAreaChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onAreaChanged = [nodeId, node = AceType::WeakClaim(frameNode), extraParam](
                             const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_AREA_CHANGE;
        PipelineContext::SetCallBackNode(node);
        auto oldLocalOffset = oldRect.GetOffset();
        event.componentAsyncEvent.data[0].f32 = PipelineBase::Px2VpWithCurrentDensity(oldRect.Width());
        event.componentAsyncEvent.data[1].f32 = PipelineBase::Px2VpWithCurrentDensity(oldRect.Height());
        event.componentAsyncEvent.data[2].f32 = PipelineBase::Px2VpWithCurrentDensity(oldLocalOffset.GetX());
        event.componentAsyncEvent.data[3].f32 = PipelineBase::Px2VpWithCurrentDensity(oldLocalOffset.GetY());
        event.componentAsyncEvent.data[4].f32 =
            PipelineBase::Px2VpWithCurrentDensity(oldLocalOffset.GetX() + oldOrigin.GetX());
        event.componentAsyncEvent.data[5].f32 =
            PipelineBase::Px2VpWithCurrentDensity(oldLocalOffset.GetY() + oldOrigin.GetY());

        auto localOffset = rect.GetOffset();
        event.componentAsyncEvent.data[6].f32 = PipelineBase::Px2VpWithCurrentDensity(rect.Width());
        event.componentAsyncEvent.data[7].f32 = PipelineBase::Px2VpWithCurrentDensity(rect.Height());
        event.componentAsyncEvent.data[8].f32 = PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX());
        event.componentAsyncEvent.data[9].f32 = PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY());
        event.componentAsyncEvent.data[10].f32 =
            PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX() + origin.GetX());
        event.componentAsyncEvent.data[11].f32 =
            PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY() + origin.GetY());
        SendArkUISyncEvent(&event);
    };
    auto areaChangeCallback = [areaChangeFunc = std::move(onAreaChanged)](const RectF& oldRect,
                                  const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
            Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
            Offset(origin.GetX(), origin.GetY()));
    };
    ViewAbstract::SetOnAreaChanged(frameNode, std::move(areaChangeCallback));
}

void SetOnClick(ArkUINodeHandle node, void* extraParam)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    int32_t nodeId = uiNode->GetId();
    auto onEvent = [nodeId, extraParam](GestureEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        event.componentAsyncEvent.subKind = ON_CLICK;
        auto target = info.GetTarget();
        event.touchEvent.target = { target.id.c_str(), target.type.c_str(),
            { static_cast<ArkUI_Int32>(target.area.GetOffset().GetX().Value()),
                static_cast<ArkUI_Int32>(target.area.GetOffset().GetY().Value()),
                static_cast<ArkUI_Int32>(target.area.GetWidth().Value()),
                static_cast<ArkUI_Int32>(target.area.GetHeight().Value()) },
            { static_cast<ArkUI_Int32>(target.origin.GetX().Value()),
                static_cast<ArkUI_Int32>(target.origin.GetY().Value()) } };
        Offset globalOffset = info.GetGlobalLocation();
        Offset localOffset = info.GetLocalLocation();
        Offset screenOffset = info.GetScreenLocation();
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        //x
        event.componentAsyncEvent.data[0].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()) : localOffset.GetX();
        //y
        event.componentAsyncEvent.data[1].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()) : localOffset.GetY();
        //timestamp
        event.componentAsyncEvent.data[2].f32 = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());
        //source
        event.componentAsyncEvent.data[3].i32 = static_cast<int32_t>(info.GetSourceDevice());
        //windowX
        event.componentAsyncEvent.data[4].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()) : globalOffset.GetX();
        //windowY
        event.componentAsyncEvent.data[5].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()) : globalOffset.GetY();
        //displayX
        event.componentAsyncEvent.data[6].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()) : screenOffset.GetX();
        //displayY
        event.componentAsyncEvent.data[7].f32 =
            usePx ? PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()) : screenOffset.GetY();
        SendArkUISyncEvent(&event);
    };
    if (uiNode->GetTag() == V2::SPAN_ETS_TAG) {
        SpanModelNG::SetOnClick(uiNode, std::move(onEvent));
    } else if (uiNode->GetTag() == V2::TEXT_ETS_TAG) {
        TextModelNG::SetOnClick(reinterpret_cast<FrameNode*>(node), std::move(onEvent));
    }  else {
        ViewAbstract::SetOnClick(reinterpret_cast<FrameNode*>(node), std::move(onEvent));
    }
}

void SetOnKeyEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onKeyEvent = [frameNode, nodeId, extraParam](KeyEventInfo& info) -> bool {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::KEY_INPUT_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.keyEvent.subKind = ArkUIEventSubKind::ON_KEY_EVENT;
        event.keyEvent.type = static_cast<int32_t>(info.GetKeyType());
        event.keyEvent.keyCode = static_cast<int32_t>(info.GetKeyCode());
        event.keyEvent.keyText = info.GetKeyText();
        event.keyEvent.keySource = static_cast<int32_t>(info.GetKeySource());
        event.keyEvent.deviceId = info.GetDeviceId();
        event.keyEvent.unicode = info.GetUnicode();
        event.keyEvent.timestamp = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());

        std::vector<int32_t> pressKeyCodeList;
        auto pressedKeyCodes = info.GetPressedKeyCodes();
        event.keyEvent.keyCodesLength = static_cast<int32_t>(pressedKeyCodes.size());
        for (auto it = pressedKeyCodes.begin(); it != pressedKeyCodes.end(); it++) {
            pressKeyCodeList.push_back(static_cast<int32_t>(*it));
        }
        event.keyEvent.pressedKeyCodes = pressKeyCodeList.data();
        event.keyEvent.intentionCode = static_cast<int32_t>(info.GetKeyIntention());

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info.SetStopPropagation(event.keyEvent.stopPropagation);
        return event.keyEvent.isConsumed;
    };
    ViewAbstract::SetOnKeyEvent(frameNode, onKeyEvent);
}

void SetOnKeyPreIme(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onPreImeEvent = [frameNode, nodeId, extraParam](KeyEventInfo& info) -> bool {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::KEY_INPUT_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.keyEvent.subKind = ON_KEY_PREIME;
        event.keyEvent.type = static_cast<int32_t>(info.GetKeyType());
        event.keyEvent.keyCode = static_cast<int32_t>(info.GetKeyCode());
        event.keyEvent.keyText = info.GetKeyText();
        event.keyEvent.keySource = static_cast<int32_t>(info.GetKeySource());
        event.keyEvent.deviceId = info.GetDeviceId();
        event.keyEvent.unicode = info.GetUnicode();
        event.keyEvent.timestamp = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());

        std::vector<int32_t> pressKeyCodeList;
        auto pressedKeyCodes = info.GetPressedKeyCodes();
        event.keyEvent.keyCodesLength = static_cast<int32_t>(pressedKeyCodes.size());
        for (auto it = pressedKeyCodes.begin(); it != pressedKeyCodes.end(); it++) {
            pressKeyCodeList.push_back(static_cast<int32_t>(*it));
        }
        event.keyEvent.pressedKeyCodes = pressKeyCodeList.data();
        event.keyEvent.intentionCode = static_cast<int32_t>(info.GetKeyIntention());

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info.SetStopPropagation(event.keyEvent.stopPropagation);
        return event.keyEvent.isConsumed;
    };
    NG::ViewAbstractModelNG::SetOnKeyPreIme(frameNode, std::move(onPreImeEvent));
}

void SetOnFocusAxisEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onFocusAxisEvent = [frameNode, nodeId, extraParam](FocusAxisEventInfo& info) {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::FOCUS_AXIS_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.focusAxisEvent.subKind = ArkUIEventSubKind::ON_FOCUS_AXIS;
        event.focusAxisEvent.absXValue = info.GetAbsXValue();
        event.focusAxisEvent.absYValue = info.GetAbsYValue();
        event.focusAxisEvent.absZValue = info.GetAbsZValue();
        event.focusAxisEvent.absRzValue = info.GetAbsRzValue();
        event.focusAxisEvent.absGasValue = info.GetAbsGasValue();
        event.focusAxisEvent.absBrakeValue = info.GetAbsBrakeValue();
        event.focusAxisEvent.absHat0XValue = info.GetAbsHat0XValue();
        event.focusAxisEvent.absHat0YValue = info.GetAbsHat0YValue();
        event.focusAxisEvent.timeStamp = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());
        event.focusAxisEvent.toolType = static_cast<int32_t>(info.GetSourceTool());
        event.focusAxisEvent.sourceType = static_cast<int32_t>(info.GetSourceDevice());
        event.focusAxisEvent.deviceId = info.GetDeviceId();
        std::vector<int32_t> pressKeyCodeList;
        auto pressedKeyCodes = info.GetPressedKeyCodes();
        event.focusAxisEvent.keyCodesLength = pressedKeyCodes.size();
        for (auto it = pressedKeyCodes.begin(); it != pressedKeyCodes.end(); it++) {
            pressKeyCodeList.push_back(static_cast<int32_t>(*it));
        }
        event.focusAxisEvent.pressedKeyCodes = pressKeyCodeList.data();
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info.SetStopPropagation(event.focusAxisEvent.stopPropagation);
    };
    ViewAbstract::SetOnFocusAxisEvent(frameNode, onFocusAxisEvent);
}

void ResetOnKeyEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnKeyEvent(frameNode);
}

void ResetOnKeyPreIme(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstractModelNG::DisableOnKeyPreIme(frameNode);
}

void ResetOnFocusAxisEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstractModelNG::DisableOnFocusAxisEvent(frameNode);
}

void ConvertTouchLocationInfoToPoint(const TouchLocationInfo& locationInfo, ArkUITouchPoint& touchPoint, bool usePx)
{
    const OHOS::Ace::Offset& globalLocation = locationInfo.GetGlobalLocation();
    const OHOS::Ace::Offset& localLocation = locationInfo.GetLocalLocation();
    const OHOS::Ace::Offset& screenLocation = locationInfo.GetScreenLocation();
    touchPoint.id = locationInfo.GetFingerId();
    double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
    touchPoint.nodeX = localLocation.GetX() / density;
    touchPoint.nodeY = localLocation.GetY() / density;
    touchPoint.windowX = globalLocation.GetX() / density;
    touchPoint.windowY = globalLocation.GetY() / density;
    touchPoint.screenX = screenLocation.GetX() / density;
    touchPoint.screenY = screenLocation.GetY() / density;
    touchPoint.pressure = locationInfo.GetForce();
    touchPoint.contactAreaWidth = locationInfo.GetSize();
    touchPoint.contactAreaHeight = locationInfo.GetSize();
    touchPoint.tiltX = locationInfo.GetTiltX().value_or(0.0f);
    touchPoint.tiltY = locationInfo.GetTiltY().value_or(0.0f);
    touchPoint.toolType = static_cast<int32_t>(locationInfo.GetSourceTool());
    touchPoint.pressedTime = locationInfo.GetTimeStamp().time_since_epoch().count();
}

void ConvertTouchPointsToPoints(std::vector<TouchPoint>& touchPointes,
    std::array<ArkUITouchPoint, MAX_POINTS>& points, const TouchLocationInfo& historyLoaction, bool usePx)
{
    if (touchPointes.empty()) {
        return;
    }
    size_t i = 0;
    for (auto& touchPoint : touchPointes) {
        if (i >= MAX_POINTS) {
            break;
        }
        double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
        points[i].id = touchPoint.id;
        points[i].nodeX = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetLocalLocation().GetX() / density;
        points[i].nodeY = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetLocalLocation().GetY() / density;
        points[i].windowX = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetGlobalLocation().GetX() / density;
        points[i].windowY = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetGlobalLocation().GetY() / density;
        points[i].screenX = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetScreenLocation().GetX() / density;
        points[i].screenY = NearEqual(density, 0.0) ? 0.0f :
            historyLoaction.GetScreenLocation().GetY() / density;
        points[i].contactAreaWidth = touchPoint.size;
        points[i].contactAreaHeight = touchPoint.size;
        points[i].pressure = touchPoint.force;
        points[i].tiltX = touchPoint.tiltX.value_or(0.0f);
        points[i].tiltY = touchPoint.tiltY.value_or(0.0f);
        points[i].pressedTime = touchPoint.downTime.time_since_epoch().count();
        points[i].toolType = static_cast<int32_t>(historyLoaction.GetSourceTool());
        i++;
    }
}

void SetOnTouch(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam](TouchEventInfo& eventInfo) {
        globalEventInfo = eventInfo;
        ArkUINodeEvent event;
        event.kind = TOUCH_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.nodeId = nodeId;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        auto target = eventInfo.GetTarget();
        event.touchEvent.target.id = target.id.c_str();
        event.touchEvent.target.type = target.type.c_str();
        event.touchEvent.target.area = {
            static_cast<ArkUI_Int32>(target.area.GetOffset().GetX().Value()),
            static_cast<ArkUI_Int32>(target.area.GetOffset().GetY().Value()),
            static_cast<ArkUI_Int32>(target.area.GetWidth().Value()),
            static_cast<ArkUI_Int32>(target.area.GetHeight().Value())
        };
        event.touchEvent.target.origin = {
            static_cast<ArkUI_Int32>(target.origin.GetX().Value()),
            static_cast<ArkUI_Int32>(target.origin.GetY().Value())
        };
        const std::list<TouchLocationInfo>& changeTouch = eventInfo.GetChangedTouches();
        if (changeTouch.size() > 0) {
            TouchLocationInfo front = changeTouch.front();
            event.touchEvent.action = static_cast<int32_t>(front.GetTouchType());
            ConvertTouchLocationInfoToPoint(front, event.touchEvent.actionTouchPoint, usePx);
        }
        event.touchEvent.timeStamp = eventInfo.GetTimeStamp().time_since_epoch().count();
        event.touchEvent.sourceType = static_cast<int32_t>(eventInfo.GetSourceDevice());
        std::array<ArkUITouchPoint, MAX_POINTS> touchPoints;
        if (!eventInfo.GetTouches().empty()) {
            size_t index = 0;
            for (auto& touchLocationInfo : eventInfo.GetTouches()) {
                if (index >= MAX_POINTS) {
                    break;
                }
                ConvertTouchLocationInfoToPoint(touchLocationInfo, touchPoints[index++], usePx);
            }
            event.touchEvent.touchPointes = &touchPoints[0];
            event.touchEvent.touchPointSize =
                eventInfo.GetTouches().size() < MAX_POINTS ? eventInfo.GetTouches().size() : MAX_POINTS;
        } else {
            event.touchEvent.touchPointes = nullptr;
            event.touchEvent.touchPointSize = 0;
        }
        event.touchEvent.subKind = ON_TOUCH;
        std::array<ArkUIHistoryTouchEvent, MAX_HISTORY_EVENT_COUNT> allHistoryEvents;
        std::array<std::array<ArkUITouchPoint, MAX_POINTS>, MAX_HISTORY_EVENT_COUNT> allHistoryPoints;
        if (!eventInfo.GetHistoryPointerEvent().empty() &&
            eventInfo.GetHistoryPointerEvent().size() == eventInfo.GetHistory().size()) {
            auto historyLoacationIterator = std::begin(eventInfo.GetHistory());
            auto historyMMIPointerEventIterator = std::begin(eventInfo.GetHistoryPointerEvent());
            for (size_t i = 0; i < eventInfo.GetHistory().size() && i < MAX_HISTORY_EVENT_COUNT; i++) {
                if (!(*historyMMIPointerEventIterator)) {
                    historyLoacationIterator++;
                    historyMMIPointerEventIterator++;
                    continue;
                }
                auto tempTouchEvent = NG::ConvertToTouchEvent((*historyMMIPointerEventIterator));
                allHistoryEvents[i].action = static_cast<int32_t>(tempTouchEvent.type);
                allHistoryEvents[i].sourceType = static_cast<int32_t>(tempTouchEvent.sourceType);
                allHistoryEvents[i].timeStamp = tempTouchEvent.time.time_since_epoch().count();
                double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
                allHistoryEvents[i].actionTouchPoint.nodeX =
                    NearEqual(density, 0.0) ? 0.0f : (*historyLoacationIterator).GetLocalLocation().GetX() / density;
                allHistoryEvents[i].actionTouchPoint.nodeY =
                    NearEqual(density, 0.0) ? 0.0f : (*historyLoacationIterator).GetLocalLocation().GetY() / density;
                allHistoryEvents[i].actionTouchPoint.windowX =
                    NearEqual(density, 0.0) ? 0.0f : (*historyLoacationIterator).GetGlobalLocation().GetX() / density;
                allHistoryEvents[i].actionTouchPoint.windowY =
                    NearEqual(density, 0.0) ? 0.0f : (*historyLoacationIterator).GetGlobalLocation().GetY() / density;
                allHistoryEvents[i].actionTouchPoint.screenX = tempTouchEvent.screenX;
                allHistoryEvents[i].actionTouchPoint.screenY = tempTouchEvent.screenY;
                allHistoryEvents[i].actionTouchPoint.pressure = tempTouchEvent.force;
                ConvertTouchPointsToPoints(
                    tempTouchEvent.pointers, allHistoryPoints[i], *historyLoacationIterator, usePx);
                if (tempTouchEvent.pointers.size() > 0) {
                    allHistoryEvents[i].touchPointes = &(allHistoryPoints[i][0]);
                }
                allHistoryEvents[i].touchPointSize =
                    tempTouchEvent.pointers.size() < MAX_POINTS ? tempTouchEvent.pointers.size() : MAX_POINTS;
                historyLoacationIterator++;
                historyMMIPointerEventIterator++;
            }
            event.touchEvent.historyEvents = &allHistoryEvents[0];
            event.touchEvent.historySize = eventInfo.GetHistoryPointerEvent().size() < MAX_HISTORY_EVENT_COUNT
                                               ? eventInfo.GetHistoryPointerEvent().size()
                                               : MAX_HISTORY_EVENT_COUNT;
        } else {
            event.touchEvent.historyEvents = nullptr;
            event.touchEvent.historySize = 0;
        }
        event.touchEvent.stopPropagation = false;
        SendArkUISyncEvent(&event);
        eventInfo.SetStopPropagation(event.touchEvent.stopPropagation);
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}

void SetOnTouchIntercept(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onTouchIntercept = [nodeId, extraParam](TouchEventInfo& eventInfo) -> NG::HitTestMode {
        globalEventInfo = eventInfo;
        ArkUINodeEvent touchEvent;
        touchEvent.kind = TOUCH_EVENT;
        touchEvent.extraParam = reinterpret_cast<intptr_t>(extraParam);
        touchEvent.nodeId = nodeId;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        const std::list<TouchLocationInfo>& changeTouch = eventInfo.GetChangedTouches();
        if (changeTouch.size() > 0) {
            TouchLocationInfo front = changeTouch.front();
            touchEvent.touchEvent.action = static_cast<int32_t>(front.GetTouchType());
            ConvertTouchLocationInfoToPoint(front, touchEvent.touchEvent.actionTouchPoint, usePx);
        }
        touchEvent.touchEvent.timeStamp = eventInfo.GetTimeStamp().time_since_epoch().count();
        touchEvent.touchEvent.sourceType = static_cast<int32_t>(eventInfo.GetSourceDevice());
        std::array<ArkUITouchPoint, MAX_POINTS> touchPoints;
        if (!eventInfo.GetTouches().empty()) {
            size_t index = 0;
            for (auto& touchLocationInfo: eventInfo.GetTouches()) {
                if (index >= MAX_POINTS) {
                    break;
                }
                ConvertTouchLocationInfoToPoint(touchLocationInfo, touchPoints[index++], usePx);
            }
            touchEvent.touchEvent.touchPointes = &touchPoints[0];
            touchEvent.touchEvent.touchPointSize = eventInfo.GetTouches().size() < MAX_POINTS ?
            eventInfo.GetTouches().size() : MAX_POINTS;
        } else {
            touchEvent.touchEvent.touchPointes = nullptr;
            touchEvent.touchEvent.touchPointSize = 0;
        }
        touchEvent.touchEvent.historyEvents = nullptr;
        touchEvent.touchEvent.historySize = 0;
        touchEvent.touchEvent.subKind = ON_TOUCH_INTERCEPT;
        touchEvent.touchEvent.interceptResult = 0;
        SendArkUISyncEvent(&touchEvent);
        return static_cast<NG::HitTestMode>(touchEvent.touchEvent.interceptResult);
    };
    ViewAbstract::SetOnTouchIntercept(frameNode, std::move(onTouchIntercept));
}

void SetOnHover(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam](bool isHover, HoverInfo& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_HOVER;
        event.componentAsyncEvent.data[0].i32 = isHover;
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnHover(frameNode, onEvent);
}

void SetOnMouse(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam](MouseInfo& info) {
        ArkUINodeEvent event;
        event.kind = MOUSE_INPUT_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
        event.mouseEvent.subKind = ON_MOUSE;
        event.mouseEvent.actionTouchPoint.nodeX = info.GetLocalLocation().GetX() / density;
        event.mouseEvent.actionTouchPoint.nodeY = info.GetLocalLocation().GetY() / density;
        event.mouseEvent.button = static_cast<int32_t>(info.GetButton());
        event.mouseEvent.action = static_cast<int32_t>(info.GetAction());
        event.mouseEvent.timeStamp = static_cast<double>(info.GetTimeStamp().time_since_epoch().count());
        event.mouseEvent.actionTouchPoint.windowX = info.GetGlobalLocation().GetX() / density;
        event.mouseEvent.actionTouchPoint.windowY = info.GetGlobalLocation().GetY() / density;
        event.mouseEvent.actionTouchPoint.screenX = info.GetScreenLocation().GetX() / density;
        event.mouseEvent.actionTouchPoint.screenY = info.GetScreenLocation().GetY() / density;
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnMouse(frameNode, onEvent);
}

void SetOnAccessibilityActions(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onEvent = [nodeId, extraParam](uint32_t actionType) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ACCESSIBILITY_ACTIONS;
        event.componentAsyncEvent.data[0].u32 = actionType;
        SendArkUISyncEvent(&event);
    };
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetActions(onEvent);
}

void ResetOnAppear(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnAppear(frameNode);
}

void ResetOnDisappear(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDisappear(frameNode);
}

void ResetOnAttach(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnAttach(frameNode);
}

void ResetOnDetach(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDetach(frameNode);
}

void ResetOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnFocus(frameNode);
}

void ResetOnBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnBlur(frameNode);
}

void ResetOnAreaChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetAreaChanged(frameNode);
}

void ResetOnVisibleAreaChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetVisibleChange(frameNode);
}

void ResetOnClick(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    if (uiNode->GetTag() == V2::SPAN_ETS_TAG) {
        SpanModelNG::ClearOnClick(uiNode);
    } else if (uiNode->GetTag() == V2::TEXT_ETS_TAG) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        TextModelNG::ClearOnClick(frameNode);
    } else {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        ViewAbstract::DisableOnClick(frameNode);
    }
}

void ResetOnTouch(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnTouch(frameNode);
}

void ResetOnTouchIntercept(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOnTouchIntercept(frameNode, nullptr);
}

void ResetOnHover(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnHover(frameNode);
}

void ResetOnMouse(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnMouse(frameNode);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG