
/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
ProgressModel* GetProgressModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("progress");
    static ProgressModel* instance = loader ? reinterpret_cast<ProgressModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr double DEFAULT_PROGRESS_VALUE = 0;
constexpr double DEFAULT_PROGRESS_TOTAL = 100;
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
constexpr ArkUI_Uint32 MAX_FONT_FAMILY_LENGTH = Infinity<ArkUI_Uint32>();

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetValue(frameNode, value);
}

void ResetProgressValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetValue(frameNode, DEFAULT_PROGRESS_VALUE);
    ProgressModelNG::SetTotal(frameNode, DEFAULT_PROGRESS_TOTAL);
}

void SetProgressTotal(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetTotal(frameNode, value);
}

void SetProgressType(ArkUINodeHandle node, int type)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetType(frameNode, static_cast<ProgressType>(type));
}

void ResetProgressType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetType(frameNode, ProgressType::LINEAR);
}

void SetProgressGradientColorInternal(
    ArkUINodeHandle node, const struct ArkUIGradientType* gradient, int32_t length, ArkUI_Bool isNeedSetResObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(gradient);
    CHECK_NULL_VOID(gradient->color);
    CHECK_NULL_VOID(gradient->offset);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < length; j++) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }

    if (isNeedSetResObj) {
        ProgressModelNG::SetGradientColorResObj(frameNode, tempGradient);
    }
    ProgressModelNG::SetGradientColor(frameNode, tempGradient);
}

void SetProgressGradientColor(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, int32_t length)
{
    SetProgressGradientColorInternal(node, gradient, length, false);
}

void SetProgressGradientColorWithResourceObj(ArkUINodeHandle node, void* gradientRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* gradient = reinterpret_cast<OHOS::Ace::NG::Gradient*>(gradientRawPtr);
    CHECK_NULL_VOID(gradient);
    auto tempGradient = *gradient;
    ProgressModelNG::SetGradientColorResObj(frameNode, tempGradient);
    ProgressModelNG::SetGradientColor(frameNode, tempGradient);
    ProgressModelNG::SetGradientColorByUser(frameNode, true);
}

void SetProgressColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = GetFrameNode(node);
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

void CreateWithResourceObjIfNeeded(FrameNode* node, JsProgressResourceType type, void* rawPtr, bool needDecRef = true)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (rawPtr) {
        auto* obj = reinterpret_cast<ResourceObject*>(rawPtr);
        if (obj != nullptr) {
            auto resObj = AceType::Claim(obj);
            if (resObj) {
                ProgressModelNG::CreateWithResourceObj(node, type, resObj);
            }
            if (needDecRef) {
                obj->DecRefCount();
            }
        }
    } else {
        ProgressModelNG::CreateWithResourceObj(node, type, nullptr);
    }
}

void SetProgressColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto *frameNode = GetFrameNode(node);
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
    Color colorValue = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, colorValue, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            auto* resourceObj = static_cast<ResourceObject*>(colorRawPtr);
            resObj = AceType::Claim(resourceObj);
        }
        if (resObj) {
            ProgressModelNG::CreateWithResourceObj(frameNode, JsProgressResourceType::COLOR, resObj);
        }
    }
    ProgressModelNG::SetColor(frameNode, colorValue);
    ProgressModelNG::SetGradientColorByUser(frameNode, true);
}

void SetProgressColorJS(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetColor(frameNode, Color(color));
}

void ResetProgressColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color endColor;
    Color beginColor;
    Color colorVal;
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();
    auto progressTheme = frameNode->GetTheme<ProgressTheme>(true);
    CHECK_NULL_VOID(progressTheme);
    if (progresstype == ProgressType::RING) {
        endColor = progressTheme->GetRingProgressEndSideColor();
        beginColor = progressTheme->GetRingProgressBeginSideColor();
    } else if (progresstype == ProgressType::CAPSULE) {
        colorVal = progressTheme->GetCapsuleSelectColor();
        endColor = colorVal;
        beginColor = colorVal;
    } else if (progresstype == ProgressType::LINEAR) {
        colorVal = progressTheme->GetTrackSelectedColor();
        endColor = colorVal;
        beginColor = colorVal;
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
    ProgressModelNG::CreateWithResourceObj(frameNode, JsProgressResourceType::COLOR, nullptr);
    ProgressModelNG::SetUserInitiatedColor(frameNode, false);
    ProgressModelNG::SetGradientColorByUser(frameNode, false);
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
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::LSStrokeWidth, value->styleResource.strokeWidthRawPtr);
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
    CreateWithResourceObjIfNeeded(
        node, JsProgressResourceType::RingStrokeWidth, value->styleResource.strokeWidthRawPtr);
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
        CreateWithResourceObjIfNeeded(
            node, JsProgressResourceType::PSStrokeWidth, value->styleResource.strokeWidthRawPtr);
    }
    ProgressModelNG::SetScaleCount(node, value->scaleCount);
    if ((static_cast<DimensionUnit>(value->scaleWidthUnit) == DimensionUnit::PERCENT) ||
        (value->scaleWidthValue > value->strokeWidthValue)) {
        ProgressModelNG::SetScaleWidth(node, Dimension(DEFAULT_SCALE_WIDTHS, DimensionUnit::VP));
    } else {
        ProgressModelNG::SetScaleWidth(
            node, Dimension(value->scaleWidthValue, static_cast<DimensionUnit>(value->scaleWidthUnit)));
        CreateWithResourceObjIfNeeded(
            node, JsProgressResourceType::PSScaleWidth, value->styleResource.scaleWidthRawPtr);
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
    if (fontFamilies && familyLength > 0 && familyLength <= MAX_FONT_FAMILY_LENGTH) {
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
    auto styleRes = value->styleResource;
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::CapsuleBorderWidth, styleRes.borderWidthRawPtr);
    ProgressModelNG::SetBorderColor(node, Color(value->borderColor));
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::CapsuleBorderColor, styleRes.borderColorRawPtr);
    ProgressModelNG::SetSweepingEffect(node, value->enableScanEffect);
    ProgressModelNG::SetShowText(node, value->showDefaultPercentage);
    if (value->content == nullptr) {
        ProgressModelNG::SetText(node, std::nullopt);
    } else {
        ProgressModelNG::SetText(node, std::string(value->content));
    }
    ProgressModelNG::SetCapsuleStyle(node, true);
    ProgressModelNG::SetCapsuleStyleFontColor(node, value->fontColorSetByUser);
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::Text, styleRes.contentRawPtr, false);
    ProgressModelNG::SetFontColor(node, Color(value->fontColor));
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::FontColor, styleRes.fontColorRawPtr);
    ProgressModelNG::SetFontSize(node, Dimension(fontSizeNumber, static_cast<DimensionUnit>(fontSizeUnit)));
    CreateWithResourceObjIfNeeded(node, JsProgressResourceType::FontSize, styleRes.fontResource.fontSizeRawPtr);
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
    auto* frameNode = GetFrameNode(node);
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
    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::LSStrokeWidth, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::LSSweepingEffect, nullptr);
    }
}

void SetRingStyleOptions(FrameNode* node)
{
    ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetPaintShadow(node, false);
    ProgressModelNG::SetProgressStatus(node, ProgressStatus::PROGRESSING);
    ProgressModelNG::SetRingSweepingEffect(node, false);
    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::RingStrokeWidth, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::RingShadow, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::RingStatus, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::RingSweepingEffect, nullptr);
    }
}

void SetProgressStyleOptions(FrameNode* node)
{
    ProgressModelNG::SetStrokeWidth(node, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetScaleCount(node, DEFAULT_SCALE_COUNT);
    ProgressModelNG::SetScaleWidth(node, Dimension(DEFAULT_SCALE_WIDTHS, DimensionUnit::VP));
    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::PSStrokeWidth, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::PSScaleWidth, nullptr);
    }
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
    auto progressTheme = node->GetTheme<ProgressTheme>(true);
    CHECK_NULL_VOID(progressTheme);
    std::optional<std::string> textOpt = std::nullopt;
    ProgressModelNG::SetCapsuleStyle(node, false);
    ProgressModelNG::SetCapsuleStyleFontColor(node, false);
    ProgressModelNG::SetBorderWidth(node, Dimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP));
    ProgressModelNG::SetBorderColor(node, progressTheme->GetBorderColor());
    ProgressModelNG::SetSweepingEffect(node, false);
    ProgressModelNG::SetShowText(node, false);
    ProgressModelNG::SetText(node, textOpt);
    ProgressModelNG::SetFontColor(node, Color(0xff182431));
    ProgressModelNG::SetFontSize(node, Dimension(DEFAULT_FONT_SIZE, DimensionUnit::FP));
    ProgressModelNG::SetFontWeight(node, textTheme->GetTextStyle().GetFontWeight());
    ProgressModelNG::SetFontFamily(node, textTheme->GetTextStyle().GetFontFamilies());
    ProgressModelNG::SetItalicFontStyle(node, textTheme->GetTextStyle().GetFontStyle());
    ProgressModelNG::ResetBorderRadius(node); // Set default value.
    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::CapsuleBorderWidth, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::CapsuleBorderColor, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::Text, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::FontColor, nullptr);
        CreateWithResourceObjIfNeeded(node, JsProgressResourceType::FontSize, nullptr);
    }
}

void ResetProgressStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
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
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetBackgroundColor(frameNode, Color(color));
}

void SetProgressBackgroundColorWithColorSpace(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }

    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(frameNode, JsProgressResourceType::BackgroundColor, colorRawPtr, false);
    }

    ProgressModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

void ResetProgressBackgroundColorWithColorSpace(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::ResetBackgroundColor(frameNode);
    ProgressModelNG::CreateWithResourceObj(frameNode, JsProgressResourceType::BackgroundColor, nullptr);
}

void ResetProgressBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progresstype = progressLayoutProperty->GetType();
    auto theme = frameNode->GetTheme<ProgressTheme>(true);
    CHECK_NULL_VOID(theme);

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX) &&
        progresstype != ProgressType::CAPSULE && SystemProperties::ConfigChangePerform()) {
        ProgressModelNG::ResetBackgroundColor(frameNode);
        ProgressModelNG::CreateWithResourceObj(frameNode, JsProgressResourceType::BackgroundColor, nullptr);
        return;
    }

    Color backgroundColor;
    if (progresstype == ProgressType::CAPSULE) {
        backgroundColor = theme->GetCapsuleBgColor();
    } else if (progresstype == ProgressType::RING) {
        backgroundColor = theme->GetRingProgressBgColor();
    } else {
        backgroundColor = theme->GetTrackBgColor();
    }

    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        ProgressModelNG::CreateWithResourceObj(frameNode, JsProgressResourceType::BackgroundColor, resObj);
    }

    ProgressModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

ArkUI_Float32 GetProgressValue(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ProgressModelNG::GetValue(frameNode);
}

ArkUI_Float32 GetProgressTotal(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ProgressModelNG::GetTotal(frameNode);
}

ArkUI_Int32 GetProgressType(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ProgressModelNG::GetType(frameNode));
}

ArkUI_Uint32 GetProgressColor(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ProgressModelNG::GetColor(frameNode).GetValue();
}

void GetProgressLinearStyle(ArkUINodeHandle node, ArkUIProgressLinearStyleOption& option)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::ProgressInitialize(
        frameNode, 0.0, value, 0.0, total, static_cast<NG::ProgressType>(progressStyle));
}

void ResetProgressInitialize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto value = 0;
    auto total = 100;
    ProgressModelNG::ProgressInitialize(
        frameNode, 0.0, value, 0.0, total, ProgressType::LINEAR);
}

void SetBorderColorSetByUser(ArkUINodeHandle node, bool isSetByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetBorderColorSetByUser(frameNode, isSetByUser);
}

void SetGradientColorByUser(ArkUINodeHandle node, bool isSetByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetGradientColorByUser(frameNode, isSetByUser);
}

void SetCapsuleStyleSetByUser(ArkUINodeHandle node, bool isSetByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ProgressModelNG::SetCapsuleStyleSetByUser(frameNode, isSetByUser);
}

ArkUINodeHandle CreateProgressFrameNode(ArkUI_Uint32 nodeId, ArkUI_Float32 value, ArkUI_Float32 max, ArkUI_Int32 type)
{
    auto frameNode = ProgressModelNG::CreateFrameNode(nodeId, value, max, static_cast<ProgressType>(type));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void CreateModel(
    ArkUI_Float32 min, ArkUI_Float32 value, ArkUI_Float32 cachedValue, ArkUI_Float32 max, ArkUI_Int32 type)
{
    ProgressModelNG::CreateProgressModelNG(min, value, cachedValue, max, static_cast<NG::ProgressType>(type));
}

void CreateWithResourceObj(ArkUINodeHandle node, ArkUI_Int32 jsType, void* resObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    ProgressModelNG::CreateWithResourceObj(
        frameNode, static_cast<JsProgressResourceType>(jsType), AceType::Claim(resourceObj));
}

void SetProgressValueImpl(ArkUINodeHandle node, ArkUI_Float32 value)
{
    GetProgressModelImpl()->SetValue(value);
}

void ResetProgressValueImpl(ArkUINodeHandle node)
{
    GetProgressModelImpl()->SetValue(DEFAULT_PROGRESS_VALUE);
}

void SetProgressGradientColorImplInternal(
    ArkUINodeHandle node, const struct ArkUIGradientType* gradient, int32_t length, ArkUI_Bool isNeedSetResObj)
{
    CHECK_NULL_VOID(gradient);
    CHECK_NULL_VOID(gradient->color);
    CHECK_NULL_VOID(gradient->offset);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < length; ++j) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }

    auto* progressModel = GetProgressModelImpl();
    CHECK_NULL_VOID(progressModel);
    if (isNeedSetResObj) {
        progressModel->SetGradientColorResObj(tempGradient);
    }
    progressModel->SetGradientColor(tempGradient);
}

void SetProgressGradientColorImpl(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, int32_t length)
{
    SetProgressGradientColorImplInternal(node, gradient, length, false);
}

void SetProgressGradientColorWithResourceObjImpl(ArkUINodeHandle node, void* gradientRawPtr)
{
    auto* gradient = reinterpret_cast<OHOS::Ace::NG::Gradient*>(gradientRawPtr);
    CHECK_NULL_VOID(gradient);
    auto* progressModel = GetProgressModelImpl();
    CHECK_NULL_VOID(progressModel);
    progressModel->SetGradientColorResObj(*gradient);
    progressModel->SetGradientColor(*gradient);
    progressModel->SetGradientColorByUser(true);
}

void SetProgressColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetProgressModelImpl()->SetColor(Color(color));
}

void ResetProgressColorImpl(ArkUINodeHandle node)
{
    GetProgressModelImpl()->ResetColor();
}

void setProgressStyleImpl(ArkUINodeHandle node, ArkUIProgressStyle* value)
{
    GetProgressModelImpl()->SetStrokeWidth(
        Dimension(value->strokeWidthValue, static_cast<DimensionUnit>(value->strokeWidthUnit)));
    GetProgressModelImpl()->SetScaleCount(value->scaleCount);
    GetProgressModelImpl()->SetScaleWidth(
        Dimension(value->scaleWidthValue, static_cast<DimensionUnit>(value->scaleWidthUnit)));
    GetProgressModelImpl()->SetBorderColor(Color(value->borderColor));
    GetProgressModelImpl()->SetBorderWidth(
        Dimension(value->borderWidthValue, static_cast<DimensionUnit>(value->borderWidthUnit)));
    GetProgressModelImpl()->SetFontSize(
        Dimension(value->fontInfo.fontSizeNumber, static_cast<DimensionUnit>(value->fontInfo.fontSizeUnit)));
    GetProgressModelImpl()->SetFontColor(Color(value->fontColor));
    GetProgressModelImpl()->SetText(
        value->content ? std::optional<std::string>(std::string(value->content)) : std::nullopt);
    GetProgressModelImpl()->SetItalicFontStyle(static_cast<FontStyle>(value->fontInfo.fontStyle));
    GetProgressModelImpl()->SetFontWeight(static_cast<FontWeight>(value->fontInfo.fontWeight));
    std::vector<std::string> fontFamilies;
    const char** familyNames = value->fontInfo.fontFamilies;
    uint32_t familyLength = value->fontInfo.familyLength;
    if (familyNames && familyLength > 0 && familyLength <= MAX_FONT_FAMILY_LENGTH) {
        fontFamilies.reserve(familyLength);
        for (uint32_t i = 0; i < familyLength; ++i) {
            fontFamilies.emplace_back(*(familyNames + i));
        }
    }
    GetProgressModelImpl()->SetFontFamily(fontFamilies);
    GetProgressModelImpl()->SetSweepingEffect(value->enableScanEffect);
    GetProgressModelImpl()->SetPaintShadow(value->shadow);
    GetProgressModelImpl()->SetProgressStatus(static_cast<ProgressStatus>(value->status));
    GetProgressModelImpl()->SetShowText(value->showDefaultPercentage);
    GetProgressModelImpl()->SetRingSweepingEffect(value->enableScanEffect);
    GetProgressModelImpl()->SetLinearSweepingEffect(value->enableScanEffect);
    GetProgressModelImpl()->SetSmoothEffect(value->enableSmoothEffect);
    GetProgressModelImpl()->SetCapsuleStyleFontColor(value->fontColor);
}

void SetProgressBackgroundColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetProgressModelImpl()->SetBackgroundColor(Color(color));
}

void SetGradientColorByUserImpl(ArkUINodeHandle node, bool isSetByUser)
{
    GetProgressModelImpl()->SetGradientColorByUser(isSetByUser);
}

void SetBorderColorSetByUserImpl(ArkUINodeHandle node, bool isSetByUser)
{
    GetProgressModelImpl()->SetBorderColorSetByUser(isSetByUser);
}

void SetCapsuleStyleSetByUserImpl(ArkUINodeHandle node, bool isSetByUser)
{
    (void)node;
    (void)isSetByUser;
}

void resetProgressBackgroundColorImpl(ArkUINodeHandle node)
{
    GetProgressModelImpl()->ResetBackgroundColor();
}

void CreateWithResourceObjImpl(ArkUINodeHandle node, ArkUI_Int32 jsType, void* resObj)
{
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    GetProgressModelImpl()->CreateWithResourceObj(
        static_cast<JsProgressResourceType>(jsType), AceType::Claim(resourceObj));
}

void SetBackgroundColorForHDR(
    ArkUINodeHandle node, ArkUI_Int32 colorSpace, const ArkUI_Float32* hdrValues, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(hdrValues);
    Color backgroundColor = Color::FromFloat(hdrValues[0], hdrValues[1], hdrValues[2], hdrValues[3], hdrValues[4]);
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else if (ColorSpace::BT2020 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::BT2020);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }

    if (SystemProperties::ConfigChangePerform()) {
        CreateWithResourceObjIfNeeded(frameNode, JsProgressResourceType::BackgroundColor, colorRawPtr, false);
    }

    ProgressModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

namespace NodeModifier {
const ArkUIProgressModifier* GetProgressModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
        #ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIProgressModifier modifier = {
            .setProgressValue = SetProgressValueImpl,
            .resetProgressValue = ResetProgressValueImpl,
            .setProgressGradientColor = SetProgressGradientColorImpl,
            .setProgressColor = SetProgressColorImpl,
            .setProgressColorPtr = nullptr,
            .resetProgressColor = ResetProgressColorImpl,
            .setProgressStyle = setProgressStyleImpl,
            .resetProgressStyle = nullptr,
            .setProgressBackgroundColor = SetProgressBackgroundColorImpl,
            .setProgressBackgroundColorWithColorSpace = nullptr,
            .setBackgroundColorForHDR = nullptr,
            .resetProgressBackgroundColor = resetProgressBackgroundColorImpl,
            .setProgressTotal = nullptr,
            .setProgressType = nullptr,
            .resetProgressType = nullptr,
            .getProgressValue = nullptr,
            .getProgressTotal = nullptr,
            .getProgressType = nullptr,
            .getProgressColor = nullptr,
            .setProgressInitialize = nullptr,
            .resetProgressInitialize = nullptr,
            .getProgressLinearStyle = nullptr,
            .setBorderColorSetByUser = SetBorderColorSetByUserImpl,
            .setGradientColorByUser = SetGradientColorByUserImpl,
            .setCapsuleStyleSetByUser = SetCapsuleStyleSetByUserImpl,
            .setProgressColorJS = SetProgressColorImpl,
            .setProgressGradientColorWithResourceObj = SetProgressGradientColorWithResourceObjImpl,
            .createProgressFrameNode = CreateProgressFrameNode,
            .createModel = CreateModel,
            .createWithResourceObj = CreateWithResourceObjImpl,
            .resetProgressBackgroundColorWithColorSpace = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    } else {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIProgressModifier modifier = {
            .setProgressValue = SetProgressValue,
            .resetProgressValue = ResetProgressValue,
            .setProgressGradientColor = SetProgressGradientColor,
            .setProgressColor = SetProgressColor,
            .setProgressColorPtr = SetProgressColorPtr,
            .resetProgressColor = ResetProgressColor,
            .setProgressStyle = SetProgressStyle,
            .resetProgressStyle = ResetProgressStyle,
            .setProgressBackgroundColor = SetProgressBackgroundColor,
            .setProgressBackgroundColorWithColorSpace = SetProgressBackgroundColorWithColorSpace,
            .setBackgroundColorForHDR  = SetBackgroundColorForHDR,
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
            .setBorderColorSetByUser = SetBorderColorSetByUser,
            .setGradientColorByUser = SetGradientColorByUser,
            .setCapsuleStyleSetByUser = SetCapsuleStyleSetByUser,
            .setProgressColorJS = SetProgressColorJS,
            .setProgressGradientColorWithResourceObj = SetProgressGradientColorWithResourceObj,
            .createProgressFrameNode = CreateProgressFrameNode,
            .createModel = CreateModel,
            .createWithResourceObj = CreateWithResourceObj,
            .resetProgressBackgroundColorWithColorSpace = ResetProgressBackgroundColorWithColorSpace,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
}

const CJUIProgressModifier* GetCJUIProgressModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIProgressModifier modifier = {
        .setProgressValue = SetProgressValue,
        .resetProgressValue = ResetProgressValue,
        .setProgressGradientColor = SetProgressGradientColor,
        .setProgressColor = SetProgressColor,
        .setProgressColorPtr = SetProgressColorPtr,
        .resetProgressColor = ResetProgressColor,
        .setProgressStyle = SetProgressStyle,
        .resetProgressStyle = ResetProgressStyle,
        .setProgressBackgroundColor = SetProgressBackgroundColor,
        .setProgressBackgroundColorWithColorSpace = SetProgressBackgroundColorWithColorSpace,
        .setBackgroundColorForHDR  = SetBackgroundColorForHDR,
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
        .resetProgressBackgroundColorWithColorSpace = ResetProgressBackgroundColorWithColorSpace,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
