
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

#include "core/interfaces/native/node/progress_modifier.h"

#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components/select/select_theme.h"

namespace OHOS::Ace::NG {
constexpr double DEFAULT_PROGRESS_VALUE = 0;
constexpr int32_t MIN_COLOR_STOPS_VALUE_INDEX = 0;
constexpr int32_t MIN_COLOR_STOPS_HAS_DIMENSION_INDEX = 1;
constexpr int32_t MIN_COLOR_STOPS_DIMENSION_INDEX = 2;
constexpr int32_t MIN_COLOR_STOPS_LENGTH = 3;
constexpr double PERCENT_100 = 100;
constexpr int32_t DEFAULT_SCALE_COUNT = 120;
constexpr double DEFAULT_STROKE_WIDTH = 4;
constexpr double DEFAULT_BORDER_WIDTH = 1;
constexpr double DEFAULT_SCALE_WIDTHS = 2;
constexpr double DEFAULT_FONT_SIZE = 12;
const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
constexpr float STROKEWIDTH_DEFAULT_VALUE = 4.0f;

/**
 * @param colors color value
 * colors[0], colors[1], colors[2] : color[0](color, hasDimension, dimension)
 * colors[3], colors[4], colors[5] : color[1](color, hasDimension, dimension)
 * ...
 * @param colorsLength colors length
 */
void SetGradientColors(NG::Gradient& gradient, const ArkUI_Float32* colors, int32_t colorsLength)
{
    if ((colors == nullptr) || (colorsLength % MIN_COLOR_STOPS_LENGTH) != 0) {
        return;
    }
    for (int32_t index = 0; index < colorsLength; index += MIN_COLOR_STOPS_LENGTH) {
        auto colorValue = colors[index + MIN_COLOR_STOPS_VALUE_INDEX];
        auto colorHasDimension = colors[index + MIN_COLOR_STOPS_HAS_DIMENSION_INDEX];
        auto colorDimension = colors[index + MIN_COLOR_STOPS_DIMENSION_INDEX];
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

void SetProgressValue(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetValue(frameNode, value);
}

void ResetProgressValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetValue(frameNode, DEFAULT_PROGRESS_VALUE);
}


void SetProgressTotal(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetTotal(frameNode, value);
}

void SetProgressType(ArkUINodeHandle node, int type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetType(frameNode, static_cast<ProgressType>(type));
}

void ResetProgressType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetType(frameNode, ProgressType::LINEAR);
}

void SetProgressGradientColor(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < length; j++) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }

    ProgressModelNG::SetGradientColor(frameNode, tempGradient);
}

void SetProgressColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::Gradient gradient;
    NG::GradientColor endSideColor;
    NG::GradientColor beginSideColor;
    endSideColor.SetLinearColor(LinearColor(Color(color)));
    endSideColor.SetDimension(Dimension(0.0));
    beginSideColor.SetLinearColor(LinearColor(Color(color)));
    beginSideColor.SetDimension(Dimension(1.0));
    gradient.AddColor(endSideColor);
    gradient.AddColor(beginSideColor);
    ProgressModelNG::SetGradientColor(frameNode, gradient);
    ProgressModelNG::SetColor(frameNode, Color(color));
}

void ResetProgressColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color endColor;
    Color beginColor;
    Color colorVal;
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    if (progresstype == ProgressType::RING) {
        endColor = progressTheme->GetRingProgressEndSideColor();
        beginColor = progressTheme->GetRingProgressBeginSideColor();
    } else if (progresstype == ProgressType::CAPSULE) {
        colorVal = progressTheme->GetCapsuleSelectColor();
    } else {
        colorVal = progressTheme->GetTrackSelectedColor();
    }

    OHOS::Ace::NG::Gradient gradient;
    OHOS::Ace::NG::GradientColor endSideColor;
    OHOS::Ace::NG::GradientColor beginSideColor;
    endSideColor.SetLinearColor(LinearColor(endColor));
    endSideColor.SetDimension(Dimension(0.0f));
    beginSideColor.SetLinearColor(LinearColor(beginColor));
    beginSideColor.SetDimension(Dimension(1.0f));
    gradient.AddColor(endSideColor);
    gradient.AddColor(beginSideColor);
    ProgressModelNG::SetGradientColor(frameNode, gradient);
    ProgressModelNG::SetColor(frameNode, colorVal);
}

void SetLinearStyleOptions(FrameNode* node, ArkUIProgressStyle* value)
{
    if ((value->strokeWidthValue < 0) ||
        (static_cast<DimensionUnit>(value->strokeWidthUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetStrokeWidth(
            node, Dimension(value->strokeWidthValue, static_cast<DimensionUnit>(value->strokeWidthUnit)));
    }
    ProgressModelNG::SetLinearSweepingEffect(node, value->enableScanEffect);
    if ((value->strokeRadiusValue < 0) ||
        (static_cast<DimensionUnit>(value->strokeRadiusUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::ResetStrokeRadius(node);
    } else {
        ProgressModelNG::SetStrokeRadius(
            node, Dimension(value->strokeRadiusValue, static_cast<DimensionUnit>(value->strokeRadiusUnit)));
    }
}

void SetRingStyleOptions(FrameNode* node, ArkUIProgressStyle* value)
{
    if ((value->strokeWidthValue < 0) ||
        (static_cast<DimensionUnit>(value->strokeWidthUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetStrokeWidth(
            node, Dimension(value->strokeWidthValue, static_cast<DimensionUnit>(value->strokeWidthUnit)));
    }
    ProgressModelNG::SetPaintShadow(node, value->shadow);
    ProgressModelNG::SetProgressStatus(node, static_cast<ProgressStatus>(value->status));
    ProgressModelNG::SetRingSweepingEffect(node, value->enableScanEffect);
}

void SetProgressStyleOptions(FrameNode* node, ArkUIProgressStyle* value)
{
    if ((value->strokeWidthValue < 0) ||
        (static_cast<DimensionUnit>(value->strokeWidthUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetStrokeWidth(
            node, Dimension(value->strokeWidthValue, static_cast<DimensionUnit>(value->strokeWidthUnit)));
    }
    ProgressModelNG::SetScaleCount(node, value->scaleCount);
    if ((static_cast<DimensionUnit>(value->scaleWidthUnit) == DimensionUnit::PERCENT) ||
        (value->scaleWidthValue > value->strokeWidthValue)) {
        ProgressModelNG::SetScaleWidth(node, Dimension(DEFAULT_SCALE_WIDTHS, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetScaleWidth(
            node, Dimension(value->scaleWidthValue, static_cast<DimensionUnit>(value->scaleWidthUnit)));
    }
}

void SetCapsuleStyleOptions(FrameNode* node, ArkUIProgressStyle* value)
{
    double fontSizeNumber = value->fontInfo.fontSizeNumber;
    int8_t fontSizeUnit = value->fontInfo.fontSizeUnit;
    uint8_t fontStyle = static_cast<uint8_t>(value->fontInfo.fontStyle);
    uint8_t fontWeight = static_cast<uint8_t>(value->fontInfo.fontWeight);
    const char** fontFamilies = value->fontInfo.fontFamilies;
    uint32_t familyLength = value->fontInfo.familyLength;
    std::vector<std::string> families;
    if (fontFamilies && familyLength > 0) {
        families.resize(familyLength);
        for (uint32_t i = 0; i < familyLength; i++) {
            families.at(i) = std::string(*(fontFamilies + i));
        }
    }
    if ((value->borderWidthValue < 0) ||
        (static_cast<DimensionUnit>(value->borderWidthUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::SetBorderWidth(node, Dimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetBorderWidth(
            node, Dimension(value->borderWidthValue, static_cast<DimensionUnit>(value->borderWidthUnit)));
    }
    if (value->content == nullptr) {
        ProgressModelNG::SetText(node, std::nullopt);
    } else {
        ProgressModelNG::SetText(node, std::string(value->content));
    }
    ProgressModelNG::SetBorderColor(node, Color(value->borderColor));
    ProgressModelNG::SetSweepingEffect(node, value->enableScanEffect);
    ProgressModelNG::SetShowText(node, value->showDefaultPercentage);
    ProgressModelNG::SetFontColor(node, Color(value->fontColor));
    ProgressModelNG::SetFontSize(node, Dimension(fontSizeNumber, static_cast<DimensionUnit>(fontSizeUnit)));
    ProgressModelNG::SetFontWeight(node, static_cast<FontWeight>(fontWeight));
    ProgressModelNG::SetFontFamily(node, families);
    ProgressModelNG::SetItalicFontStyle(node, static_cast<Ace::FontStyle>(fontStyle));
    if (Negative(value->borderRadiusValue) ||
        (static_cast<DimensionUnit>(value->borderRadiusUnit) == DimensionUnit::PERCENT)) {
        ProgressModelNG::ResetBorderRadius(node);
    } else {
        ProgressModelNG::SetBorderRadius(node, Dimension(value->borderRadiusValue,
            static_cast<DimensionUnit>(value->borderRadiusUnit)));
    }
}

void SetProgressStyle(ArkUINodeHandle node, ArkUIProgressStyle* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();

    ProgressModelNG::SetSmoothEffect(frameNode, value->enableSmoothEffect);

    if (progresstype == ProgressType::LINEAR) {
        SetLinearStyleOptions(frameNode, value);
    } else if (progresstype == ProgressType::RING) {
        SetRingStyleOptions(frameNode, value);
    } else if (progresstype == ProgressType::CAPSULE) {
        SetCapsuleStyleOptions(frameNode, value);
    } else {
        SetProgressStyleOptions(frameNode, value);
    }
}

void SetLinearStyleOptions(FrameNode* node)
{
    ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetLinearSweepingEffect(node, false);
    ProgressModelNG::ResetStrokeRadius(node);
}

void SetRingStyleOptions(FrameNode* node)
{
    ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetPaintShadow(node, false);
    ProgressModelNG::SetProgressStatus(node, ProgressStatus::PROGRESSING);
    ProgressModelNG::SetRingSweepingEffect(node, false);
}

void SetProgressStyleOptions(FrameNode* node)
{
    ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetScaleCount(node, DEFAULT_SCALE_COUNT);
    ProgressModelNG::SetScaleWidth(node, Dimension(DEFAULT_SCALE_WIDTHS, DimensionUnit::VP));
}

void SetCapsuleStyleOptions(FrameNode* node)
{
    auto context = node->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    std::optional<std::string> textOpt = std::nullopt;
    ProgressModelNG::SetBorderWidth(node, Dimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetBorderColor(node, Color(0x33006cde));
    ProgressModelNG::SetSweepingEffect(node, false);
    ProgressModelNG::SetShowText(node, false);
    ProgressModelNG::SetText(node, textOpt);
    ProgressModelNG::SetFontColor(node, Color(0xff182431));
    ProgressModelNG::SetFontSize(node, Dimension(DEFAULT_FONT_SIZE, DimensionUnit::FP));
    ProgressModelNG::SetFontWeight(node, textTheme->GetTextStyle().GetFontWeight());
    ProgressModelNG::SetFontFamily(node, textTheme->GetTextStyle().GetFontFamilies());
    ProgressModelNG::SetItalicFontStyle(node, textTheme->GetTextStyle().GetFontStyle());
    ProgressModelNG::ResetBorderRadius(node); // Set default value.
}

void ResetProgressStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();
    ProgressModelNG::SetSmoothEffect(frameNode, true);

    if (progresstype == ProgressType::LINEAR) {
        SetLinearStyleOptions(frameNode);
    } else if (progresstype == ProgressType::RING) {
        SetRingStyleOptions(frameNode);
    } else if (progresstype == ProgressType::CAPSULE) {
        SetCapsuleStyleOptions(frameNode);
    } else {
        SetProgressStyleOptions(frameNode);
    }
}

void SetProgressBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetProgressBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);

    Color backgroundColor;
    if (progresstype == ProgressType::CAPSULE) {
        backgroundColor = theme->GetCapsuleBgColor();
    } else if (progresstype == ProgressType::RING) {
        backgroundColor = theme->GetRingProgressBgColor();
    } else {
        backgroundColor = theme->GetTrackBgColor();
    }

    ProgressModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

ArkUI_Float32 GetProgressValue(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ProgressModelNG::GetValue(frameNode);
}

ArkUI_Float32 GetProgressTotal(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ProgressModelNG::GetTotal(frameNode);
}

ArkUI_Int32 GetProgressType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ProgressModelNG::GetType(frameNode));
}

ArkUI_Uint32 GetProgressColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ProgressModelNG::GetColor(frameNode).GetValue();
}

void GetProgressLinearStyle(ArkUINodeHandle node, ArkUIProgressLinearStyleOption& option)
{
    auto* frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    option.scanEffectEnable = paintProperty->GetEnableLinearScanEffect().value_or(false);
    option.smoothEffectEnable = paintProperty->GetEnableSmoothEffect().value_or(true);
    auto strokeWidth = layoutProperty->GetStrokeWidth().value_or(
        Dimension(STROKEWIDTH_DEFAULT_VALUE, DimensionUnit::VP)).Value();
    option.strokeWidth = strokeWidth;
    auto strokeRadius = paintProperty->GetStrokeRadiusValue(Dimension(strokeWidth / 2.0f, DimensionUnit::VP)).Value();
    strokeRadius = std::min(strokeWidth / 2.0f, strokeRadius);
    option.strokeRadius = strokeRadius;
}

void SetProgressInitialize(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Float32 total, ArkUI_Int32 progressStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::ProgressInitialize(
        frameNode, 0.0, value, 0.0, total, static_cast<NG::ProgressType>(progressStyle));
}

void ResetProgressInitialize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto value = 0;
    auto total = 100;
    ProgressModelNG::ProgressInitialize(
        frameNode, 0.0, value, 0.0, total, ProgressType::LINEAR);
}

namespace NodeModifier {
const ArkUIProgressModifier* GetProgressModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIProgressModifier modifier = {
        .setProgressValue = SetProgressValue,
        .resetProgressValue = ResetProgressValue,
        .setProgressGradientColor = SetProgressGradientColor,
        .setProgressColor = SetProgressColor,
        .resetProgressColor = ResetProgressColor,
        .setProgressStyle = SetProgressStyle,
        .resetProgressStyle = ResetProgressStyle,
        .setProgressBackgroundColor = SetProgressBackgroundColor,
        .resetProgressBackgroundColor = ResetProgressBackgroundColor,
        .setProgressTotal = SetProgressTotal,
        .setProgressType = SetProgressType,
        .resetProgressType = ResetProgressType,
        .getProgressValue = GetProgressValue,
        .getProgressTotal = GetProgressTotal,
        .getProgressType = GetProgressType,
        .getProgressColor = GetProgressColor,
        .setProgressInitialize = SetProgressInitialize,
        .resetProgressInitialize = ResetProgressInitialize,
        .getProgressLinearStyle = GetProgressLinearStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIProgressModifier* GetCJUIProgressModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIProgressModifier modifier = {
        .setProgressValue = SetProgressValue,
        .resetProgressValue = ResetProgressValue,
        .setProgressGradientColor = SetProgressGradientColor,
        .setProgressColor = SetProgressColor,
        .resetProgressColor = ResetProgressColor,
        .setProgressStyle = SetProgressStyle,
        .resetProgressStyle = ResetProgressStyle,
        .setProgressBackgroundColor = SetProgressBackgroundColor,
        .resetProgressBackgroundColor = ResetProgressBackgroundColor,
        .setProgressTotal = SetProgressTotal,
        .setProgressType = SetProgressType,
        .resetProgressType = ResetProgressType,
        .getProgressValue = GetProgressValue,
        .getProgressTotal = GetProgressTotal,
        .getProgressType = GetProgressType,
        .getProgressColor = GetProgressColor,
        .setProgressInitialize = SetProgressInitialize,
        .resetProgressInitialize = ResetProgressInitialize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
