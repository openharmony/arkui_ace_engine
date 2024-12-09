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
#include "core/interfaces/native/node/node_slider_modifier.h"

#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components/slider/slider_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
const bool DEFAULT_SHOW_STEPS = false;
const bool DEFAULT_SHOW_TIPS = false;
const std::vector<SliderModel::SliderMode> SLIDER_MODE = { SliderModel::SliderMode::OUTSET,
    SliderModel::SliderMode::INSET, SliderModel::SliderMode::NONE, SliderModel::SliderMode::CAPSULE, };
const std::vector<SliderModel::BlockStyleType> SLIDER_STYLE_TYPE = { SliderModel::BlockStyleType::DEFAULT,
    SliderModel::BlockStyleType::IMAGE, SliderModel::BlockStyleType::SHAPE };
std::map<SliderModel::SliderMode, int> SLIDER_MODE_MAP = {
    { SliderModel::SliderMode::OUTSET, 0 },
    { SliderModel::SliderMode::INSET, 1 },
    { SliderModel::SliderMode::NONE, 2 },
    { SliderModel::SliderMode::CAPSULE, 3 } };
std::map<SliderModel::BlockStyleType, int> SLIDER_STYLE_TYPE_MAP = {
    { SliderModel::BlockStyleType::DEFAULT, 0 },
    { SliderModel::BlockStyleType::IMAGE, 1 },
    { SliderModel::BlockStyleType::SHAPE, 2 } };

std::map<BasicShapeType, int> SHAPE_TYPE_MAP = {
    { BasicShapeType::RECT, 0 },
    { BasicShapeType::CIRCLE, 1 },
    { BasicShapeType::ELLIPSE, 2 },
    { BasicShapeType::PATH, 3 } };

const float DEFAULT_VALUE = 0.0;
const float DEFAULT_MAX_VALUE = 100.0;
const float DEFAULT_MIN_VALUE = 0.0;
const float DEFAULT_STEP_VALUE = 1.0;

const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
namespace SliderModifier {

std::string g_strValue;

void SetShowTips(ArkUINodeHandle node, ArkUI_Bool isShow, const char *value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> content;

    if (value == nullptr) {
        content = std::nullopt;
    } else {
        content = std::string(value);
    }
    SliderModelNG::SetShowTips(frameNode, static_cast<bool>(isShow), content);
}

void ResetShowTips(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> content;
    SliderModelNG::SetShowTips(frameNode, DEFAULT_SHOW_TIPS, content);
}

void SetSliderStepSize(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension size = Dimension(static_cast<double>(value),
    static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetStepSize(frameNode, size);
}

void ResetSliderStepSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SliderTheme>();

    Dimension stepSize = theme->GetMarkerSize();
    SliderModelNG::SetStepSize(frameNode, stepSize);
}

void SetBlockSize(ArkUINodeHandle node, ArkUI_Float32 widthVal,
    int widthUnit, ArkUI_Float32 heightVal, int heightUnit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension blockWidth = Dimension(static_cast<double>(widthVal),
    static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    Dimension blockHeight = Dimension(static_cast<double>(heightVal),
    static_cast<OHOS::Ace::DimensionUnit>(heightUnit));

    if (LessNotEqual(blockWidth.Value(), 0.0)) {
        blockWidth.SetValue(0.0);
    }
    if (LessNotEqual(blockHeight.Value(), 0.0)) {
        blockHeight.SetValue(0.0);
    }
    SliderModelNG::SetBlockSize(frameNode, blockWidth, blockHeight);
}

void ResetBlockSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockSize(frameNode);
}

void SetTrackBorderRadius(ArkUINodeHandle node, float value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetTrackBorderRadius(frameNode, radius);
}

void ResetTrackBorderRadius(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetTrackBorderRadius(frameNode);
}

void SetStepColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStepColor(frameNode, Color(color));
}

void ResetStepColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetStepColor(frameNode);
}

void SetBlockBorderColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockBorderColor(frameNode, Color(color));
}

void ResetBlockBorderColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderColor(frameNode);
}

void SetBlockBorderWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetBlockBorderWidth(frameNode, width);
}

void ResetBlockBorderWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderWidth(frameNode);
}

void SetBlockColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockColor(frameNode, Color(color));
}

void ResetBlockColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockColor(frameNode);
}

void SetTrackBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetTrackBackgroundColor(frameNode, SliderModelNG::CreateSolidGradient(Color(color)), true);
}

void ResetTrackBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);

    SliderModelNG::SetTrackBackgroundColor(
        frameNode, SliderModelNG::CreateSolidGradient(theme->GetTrackBgColor()), true);
}

void SetSelectColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSelectColor(frameNode, Color(color));
}

void ResetSelectColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    SliderModelNG::SetSelectColor(frameNode, theme->GetTrackSelectedColor());
}

void SetShowSteps(ArkUINodeHandle node, int showSteps)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, static_cast<bool>(showSteps));
}

void ResetShowSteps(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, DEFAULT_SHOW_STEPS);
}

void SetThickness(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension thickness =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetThickness(frameNode, thickness);
}

void ResetThickness(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetThickness(frameNode, CalcDimension(0.0));
}

void SetSliderValue(ArkUINodeHandle node, float value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderValue(frameNode, value);
}

void SetMinLabel(ArkUINodeHandle node, float value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinLabel(frameNode, value);
}

void SetMaxLabel(ArkUINodeHandle node, float value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMaxLabel(frameNode, value);
}

void SetDirection(ArkUINodeHandle node, int value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetDirection(frameNode, static_cast<Axis>(value));
}

void SetStep(ArkUINodeHandle node, float value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStep(frameNode, value);
}

void SetReverse(ArkUINodeHandle node, int value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetReverse(frameNode, static_cast<bool>(value));
}

void SetSliderStyle(ArkUINodeHandle node, int value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= static_cast<int32_t>(SLIDER_MODE.size())) {
        return;
    }
    SliderModelNG::SetSliderMode(frameNode, SLIDER_MODE[value]);
}

void ResetSliderValue(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderValue(frameNode, DEFAULT_VALUE);
}

void ResetMinLabel(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinLabel(frameNode, DEFAULT_MIN_VALUE);
}

void ResetMaxLabel(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMaxLabel(frameNode, DEFAULT_MAX_VALUE);
}

void ResetDirection(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}

void ResetStep(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStep(frameNode, DEFAULT_STEP_VALUE);
}

void ResetReverse(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetReverse(frameNode, false);
}

void ResetSliderStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderMode(frameNode, SliderModel::SliderMode::OUTSET);
}

void SetSliderBlockImage(
    ArkUINodeHandle node, const char* src, const char* bundle, const char* module)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr(src);
    std::string bundleStr(bundle);
    std::string moduleStr(module);
    SliderModelNG::SetBlockImage(frameNode, srcStr, bundleStr, moduleStr);
}

void ResetSliderBlockImage(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
}

void SetSliderBlockPath(
    ArkUINodeHandle node, const char* type, const ArkUI_Float32 (*attribute)[2], const char* commands)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto path = AceType::MakeRefPtr<Path>();
    auto width = Dimension((*attribute)[0], static_cast<OHOS::Ace::DimensionUnit>(1));
    auto height = Dimension((*attribute)[1], static_cast<OHOS::Ace::DimensionUnit>(1));
    std::string pathCommands(commands);
    path->SetWidth(width);
    path->SetHeight(height);
    path->SetValue(StringUtils::TrimStr(pathCommands));
    SliderModelNG::SetBlockShape(frameNode, path);
}

void SetSliderBlockShape(ArkUINodeHandle node, const char* type, const ArkUI_Float32* attribute, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (std::strcmp(type, "rect") == 0) {
        auto shape = AceType::MakeRefPtr<ShapeRect>();
        // 0 width 1 height 2 radiusWith 3 radius Height
        auto width = Dimension(attribute[0], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto height = Dimension(attribute[1], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto radiusWidth = Dimension(attribute[2], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto radiusHeight = Dimension(attribute[3], static_cast<OHOS::Ace::DimensionUnit>(1));
        shape->SetWidth(width);
        shape->SetHeight(height);
        shape->SetRadiusWidth(radiusWidth);
        shape->SetRadiusHeight(radiusHeight);
        SliderModelNG::SetBlockShape(frameNode, shape);
    }
    if (std::strcmp(type, "circle") == 0) {
        auto shape = AceType::MakeRefPtr<Circle>();
        // 0 width 1 height
        auto width = Dimension(attribute[0], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto height = Dimension(attribute[1], static_cast<OHOS::Ace::DimensionUnit>(1));
        shape->SetWidth(width);
        shape->SetHeight(height);
        SliderModelNG::SetBlockShape(frameNode, shape);
    }
    if (std::strcmp(type, "ellipse") == 0) {
        auto shape = AceType::MakeRefPtr<Ellipse>();
        // 0 width 1 height
        auto width = Dimension(attribute[0], static_cast<OHOS::Ace::DimensionUnit>(1));
        auto height = Dimension(attribute[1], static_cast<OHOS::Ace::DimensionUnit>(1));
        shape->SetWidth(width);
        shape->SetHeight(height);
        SliderModelNG::SetBlockShape(frameNode, shape);
    }
}

void ResetSliderBlockShape(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
}

void SetSliderBlockType(ArkUINodeHandle node, int value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockType(frameNode, SLIDER_STYLE_TYPE[value]);
}

void ResetSliderBlockType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockType(frameNode);
}

void SetSliderValidSlideRange(ArkUINodeHandle node, float from, float to)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetValidSlideRange(frameNode, from, to);
}

void ResetSliderValidSlideRange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetValidSlideRange(frameNode);
}

void SetSelectedBorderRadius(ArkUINodeHandle node, float value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetSelectedBorderRadius(frameNode, radius);
}

void ResetSelectedBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSelectedBorderRadius(frameNode);
}

void SetInteractionMode(ArkUINodeHandle node, int value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderInteractionMode(frameNode, static_cast<SliderModel::SliderInteraction>(value));
}

void ResetInteractionMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSliderInteractionMode(frameNode);
}

void SetMinResponsiveDistance(ArkUINodeHandle node, float value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinResponsiveDistance(frameNode, value);
}

void ResetMinResponsiveDistance(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetMinResponsiveDistance(frameNode);
}

ArkUI_Uint32 GetBlockColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return SliderModelNG::GetBlockColor(frameNode).GetValue();
}

ArkUI_Uint32 GetTrackBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetTrackBackgroundColor(frameNode);
    return gradient.GetColors().at(0).GetLinearColor().ToColor().GetValue();
}

ArkUI_Uint32 GetSelectColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return SliderModelNG::GetSelectColor(frameNode).GetValue();
}

ArkUI_Bool GetShowSteps(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(SliderModelNG::GetShowSteps(frameNode));
}

ArkUI_Int32 GetBlockType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SLIDER_STYLE_TYPE_MAP[SliderModelNG::GetBlockType(frameNode)];
}

ArkUI_Float32 GetSliderValue(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetSliderValue(frameNode);
}

ArkUI_Float32 GetMinLabel(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetMinLabel(frameNode);
}

ArkUI_Float32 GetMaxLabel(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetMaxLabel(frameNode);
}

ArkUI_Int32 GetDirection(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SliderModelNG::GetDirection(frameNode));
}

ArkUI_Float32 GetStep(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetStep(frameNode);
}

ArkUI_Bool GetReverse(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(SliderModelNG::GetReverse(frameNode));
}

ArkUI_Int32 GetSliderStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SLIDER_MODE_MAP[SliderModelNG::GetSliderMode(frameNode)];
}
ArkUI_CharPtr GetBlockImageValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = SliderModelNG::GetBlockImageValue(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetSliderBlockShape(ArkUINodeHandle node, ArkUI_Float32 (*value)[5])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    RefPtr<BasicShape> basicShape = SliderModelNG::GetBlockShape(frameNode);
    auto shapeType = basicShape->GetBasicShapeType();
    //index 0 shapeType
    (*value)[0] = SHAPE_TYPE_MAP[shapeType];
    //index 1 width
    (*value)[1] = basicShape->GetWidth().Value();
    //index 2 height
    (*value)[2] = basicShape->GetHeight().Value();
    switch (shapeType) {
        case BasicShapeType::PATH: {
            auto path = AceType::DynamicCast<Path>(basicShape);
            g_strValue = path->GetValue();
            return g_strValue.c_str();
        }
        case BasicShapeType::RECT: {
            auto shapeRect = AceType::DynamicCast<ShapeRect>(basicShape);
            //index 3 radius x
            (*value)[3] = shapeRect->GetTopLeftRadius().GetX().Value();
            //index 4 radius y
            (*value)[4] = shapeRect->GetTopLeftRadius().GetY().Value();
            break;
        }
        default:
            break;
    }
    return nullptr;
}

ArkUI_Float32 GetThickness(ArkUINodeHandle node, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetThickness(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUISliderValidSlideRange GetSliderValidSlideRange(ArkUINodeHandle node)
{
    ArkUISliderValidSlideRange errorReturn = {
        std::numeric_limits<float>::quiet_NaN(),
        std::numeric_limits<float>::quiet_NaN()
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, errorReturn);
    auto rangeValue = SliderModelNG::GetValidSlideRange(frameNode).GetRawPtr();
    CHECK_NULL_RETURN(rangeValue && rangeValue->HasValidValues(), errorReturn);
    return { rangeValue->GetFromValue(), rangeValue->GetToValue() };
}
} // namespace SliderModifier

namespace NodeModifier {
const ArkUISliderModifier* GetSliderModifier()
{
    static const ArkUISliderModifier modifier = {
        SliderModifier::SetShowTips,
        SliderModifier::ResetShowTips,
        SliderModifier::SetSliderStepSize,
        SliderModifier::ResetSliderStepSize,
        SliderModifier::SetBlockSize,
        SliderModifier::ResetBlockSize,
        SliderModifier::SetTrackBorderRadius,
        SliderModifier::ResetTrackBorderRadius,
        SliderModifier::SetStepColor,
        SliderModifier::ResetStepColor,
        SliderModifier::SetBlockBorderColor,
        SliderModifier::ResetBlockBorderColor,
        SliderModifier::SetBlockBorderWidth,
        SliderModifier::ResetBlockBorderWidth,
        SliderModifier::SetBlockColor,
        SliderModifier::ResetBlockColor,
        SliderModifier::SetTrackBackgroundColor,
        SliderModifier::ResetTrackBackgroundColor,
        SliderModifier::SetSelectColor,
        SliderModifier::ResetSelectColor,
        SliderModifier::SetShowSteps,
        SliderModifier::ResetShowSteps,
        SliderModifier::SetThickness,
        SliderModifier::ResetThickness,
        SliderModifier::SetSliderValue,
        SliderModifier::SetMinLabel,
        SliderModifier::SetMaxLabel,
        SliderModifier::SetDirection,
        SliderModifier::SetStep,
        SliderModifier::SetReverse,
        SliderModifier::SetSliderStyle,
        SliderModifier::ResetSliderValue,
        SliderModifier::ResetMinLabel,
        SliderModifier::ResetMaxLabel,
        SliderModifier::ResetDirection,
        SliderModifier::ResetStep,
        SliderModifier::ResetReverse,
        SliderModifier::ResetSliderStyle,
        SliderModifier::SetSliderBlockImage,
        SliderModifier::ResetSliderBlockImage,
        SliderModifier::SetSliderBlockPath,
        SliderModifier::SetSliderBlockShape,
        SliderModifier::ResetSliderBlockShape,
        SliderModifier::SetSliderBlockType,
        SliderModifier::ResetSliderBlockType,
        SliderModifier::SetSliderValidSlideRange,
        SliderModifier::ResetSliderValidSlideRange,
        SliderModifier::SetSelectedBorderRadius,
        SliderModifier::ResetSelectedBorderRadius,
        SliderModifier::SetInteractionMode,
        SliderModifier::ResetInteractionMode,
        SliderModifier::SetMinResponsiveDistance,
        SliderModifier::ResetMinResponsiveDistance,
        SliderModifier::GetBlockColor,
        SliderModifier::GetTrackBackgroundColor,
        SliderModifier::GetSelectColor,
        SliderModifier::GetShowSteps,
        SliderModifier::GetBlockType,
        SliderModifier::GetSliderValue,
        SliderModifier::GetMinLabel,
        SliderModifier::GetMaxLabel,
        SliderModifier::GetDirection,
        SliderModifier::GetStep,
        SliderModifier::GetReverse,
        SliderModifier::GetSliderStyle,
        SliderModifier::GetBlockImageValue,
        SliderModifier::GetSliderBlockShape,
        SliderModifier::GetThickness,
        SliderModifier::GetSliderValidSlideRange,
    };

    return &modifier;
}

const CJUISliderModifier* GetCJUISliderModifier()
{
    static const CJUISliderModifier modifier = {
        SliderModifier::SetShowTips,
        SliderModifier::ResetShowTips,
        SliderModifier::SetSliderStepSize,
        SliderModifier::ResetSliderStepSize,
        SliderModifier::SetBlockSize,
        SliderModifier::ResetBlockSize,
        SliderModifier::SetTrackBorderRadius,
        SliderModifier::ResetTrackBorderRadius,
        SliderModifier::SetStepColor,
        SliderModifier::ResetStepColor,
        SliderModifier::SetBlockBorderColor,
        SliderModifier::ResetBlockBorderColor,
        SliderModifier::SetBlockBorderWidth,
        SliderModifier::ResetBlockBorderWidth,
        SliderModifier::SetBlockColor,
        SliderModifier::ResetBlockColor,
        SliderModifier::SetTrackBackgroundColor,
        SliderModifier::ResetTrackBackgroundColor,
        SliderModifier::SetSelectColor,
        SliderModifier::ResetSelectColor,
        SliderModifier::SetShowSteps,
        SliderModifier::ResetShowSteps,
        SliderModifier::SetThickness,
        SliderModifier::ResetThickness,
        SliderModifier::SetSliderValue,
        SliderModifier::SetMinLabel,
        SliderModifier::SetMaxLabel,
        SliderModifier::SetDirection,
        SliderModifier::SetStep,
        SliderModifier::SetReverse,
        SliderModifier::SetSliderStyle,
        SliderModifier::ResetSliderValue,
        SliderModifier::ResetMinLabel,
        SliderModifier::ResetMaxLabel,
        SliderModifier::ResetDirection,
        SliderModifier::ResetStep,
        SliderModifier::ResetReverse,
        SliderModifier::ResetSliderStyle,
        SliderModifier::SetSliderBlockImage,
        SliderModifier::ResetSliderBlockImage,
        SliderModifier::SetSliderBlockPath,
        SliderModifier::SetSliderBlockShape,
        SliderModifier::ResetSliderBlockShape,
        SliderModifier::SetSliderBlockType,
        SliderModifier::ResetSliderBlockType,
        SliderModifier::SetSliderValidSlideRange,
        SliderModifier::ResetSliderValidSlideRange,
        SliderModifier::SetSelectedBorderRadius,
        SliderModifier::ResetSelectedBorderRadius,
        SliderModifier::SetInteractionMode,
        SliderModifier::ResetInteractionMode,
        SliderModifier::SetMinResponsiveDistance,
        SliderModifier::ResetMinResponsiveDistance,
        SliderModifier::GetBlockColor,
        SliderModifier::GetTrackBackgroundColor,
        SliderModifier::GetSelectColor,
        SliderModifier::GetShowSteps,
        SliderModifier::GetBlockType,
        SliderModifier::GetSliderValue,
        SliderModifier::GetMinLabel,
        SliderModifier::GetMaxLabel,
        SliderModifier::GetDirection,
        SliderModifier::GetStep,
        SliderModifier::GetReverse,
        SliderModifier::GetSliderStyle,
        SliderModifier::GetBlockImageValue,
        SliderModifier::GetSliderBlockShape,
        SliderModifier::GetThickness,
        SliderModifier::GetSliderValidSlideRange,
    };

    return &modifier;
}

void SetSliderChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](float value, int32_t mode) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SLIDER_CHANGE;
        event.componentAsyncEvent.data[0].f32 = value;
        event.componentAsyncEvent.data[1].i32 = mode;
        SendArkUISyncEvent(&event);
    };
    SliderModelNG::SetOnChange(frameNode, std::move(onEvent));
}

}
}
