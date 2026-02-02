/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/pattern/slider/bridge/slider_model_impl.h"
#include "core/components_ng/pattern/slider/slider_custom_content_options.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::SliderModelImpl* GetSliderModelImpl()
{
    static Framework::SliderModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
const bool DEFAULT_SHOW_STEPS = false;
const bool DEFAULT_SHOW_TIPS = false;
const std::vector<SliderModel::SliderMode> SLIDER_MODE = {
    SliderModel::SliderMode::OUTSET,
    SliderModel::SliderMode::INSET,
    SliderModel::SliderMode::NONE,
    SliderModel::SliderMode::CAPSULE,
};
const std::vector<SliderModel::BlockStyleType> SLIDER_STYLE_TYPE = { SliderModel::BlockStyleType::DEFAULT,
    SliderModel::BlockStyleType::IMAGE, SliderModel::BlockStyleType::SHAPE };
std::map<SliderModel::SliderMode, int> SLIDER_MODE_MAP = { { SliderModel::SliderMode::OUTSET, 0 },
    { SliderModel::SliderMode::INSET, 1 }, { SliderModel::SliderMode::NONE, 2 },
    { SliderModel::SliderMode::CAPSULE, 3 } };
std::map<SliderModel::BlockStyleType, int> SLIDER_STYLE_TYPE_MAP = { { SliderModel::BlockStyleType::DEFAULT, 0 },
    { SliderModel::BlockStyleType::IMAGE, 1 }, { SliderModel::BlockStyleType::SHAPE, 2 } };

std::map<BasicShapeType, int> SHAPE_TYPE_MAP = { { BasicShapeType::RECT, 0 }, { BasicShapeType::CIRCLE, 1 },
    { BasicShapeType::ELLIPSE, 2 }, { BasicShapeType::PATH, 3 } };

const float DEFAULT_VALUE = 0.0;
const float DEFAULT_MAX_VALUE = 100.0;
const float DEFAULT_MIN_VALUE = 0.0;
const float DEFAULT_STEP_VALUE = 1.0;

const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
const int32_t LINEAR_GRADIENT_LIMIT_TO_SLIDER = 10;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

namespace SliderModifier {

thread_local std::string g_strValue;

void SetShowTips(ArkUINodeHandle node, ArkUI_Bool isShow, const char* value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> content;
    if (value == nullptr) {
        content = std::nullopt;
    } else {
        content = std::string(value);
    }
    SliderModelNG::SetShowTips(frameNode, static_cast<bool>(isShow), content);
}

void SetShowTipsPtr(ArkUINodeHandle node, ArkUI_Bool isShow, const char* value, void* strRawPtr)
{
    SetShowTips(node, isShow, value);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        if (strRawPtr) {
            auto* str = reinterpret_cast<ResourceObject*>(strRawPtr);
            auto strResObj = AceType::Claim(str);
            SliderModelNG::CreateWithStringResourceObj(frameNode, strResObj, static_cast<bool>(isShow));
        } else {
            SliderModelNG::CreateWithStringResourceObj(frameNode, nullptr, static_cast<bool>(isShow));
        }
    }
}

void ResetShowTips(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> content;
    SliderModelNG::SetShowTips(frameNode, DEFAULT_SHOW_TIPS, content);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithStringResourceObj(frameNode, nullptr, false);
    }
}

void SetSliderStepSize(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension size = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetStepSize(frameNode, size);
}

void ResetSliderStepSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);

    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SliderTheme>();

    Dimension stepSize = theme->GetMarkerSize();
    SliderModelNG::SetStepSize(frameNode, stepSize);
}

void SetBlockSize(ArkUINodeHandle node, ArkUI_Float32 widthVal, int widthUnit, ArkUI_Float32 heightVal, int heightUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension blockWidth = Dimension(static_cast<double>(widthVal), static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    Dimension blockHeight =
        Dimension(static_cast<double>(heightVal), static_cast<OHOS::Ace::DimensionUnit>(heightUnit));

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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockSize(frameNode);
}

void SetTrackBorderRadius(ArkUINodeHandle node, float value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetTrackBorderRadius(frameNode, radius);
}

void ResetTrackBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetTrackBorderRadius(frameNode);
}

void SetStepColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStepColor(frameNode, Color(color));
}

void SetStepColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    SetStepColor(node, color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        if (colorRawPtr) {
            auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
            auto colorResObj = AceType::Claim(color);
            SliderModelNG::CreateWithColorResourceObj(frameNode, colorResObj, SliderColorType::STEP_COLOR);
        } else {
            SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::STEP_COLOR);
        }
    }
}

void ResetStepColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetStepColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::STEP_COLOR);
    }
}

void SetBlockBorderColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockBorderColor(frameNode, Color(color));
}

void SetBlockBorderColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    SetBlockBorderColor(node, color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        if (colorRawPtr) {
            auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
            auto colorResObj = AceType::Claim(color);
            SliderModelNG::CreateWithColorResourceObj(frameNode, colorResObj, SliderColorType::BLOCK_BORDER_COLOR);
        } else {
            SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::BLOCK_BORDER_COLOR);
        }
    }
}

void ResetBlockBorderColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::BLOCK_BORDER_COLOR);
    }
}

void SetBlockBorderWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetBlockBorderWidth(frameNode, width);
}

void ResetBlockBorderWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderWidth(frameNode);
}

void SetBlockColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockColor(frameNode, Color(color));
}

void SetBlockColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        SliderModelNG::CreateWithColorResourceObj(frameNode, resObj, SliderColorType::BLOCK_COLOR);
    }
    SetBlockColor(node, result.GetValue());
}

void SetLinearBlockColor(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(gradient);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < colorLength; ++j) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }
    SliderModelNG::SetLinearGradientBlockColor(frameNode, tempGradient);
}

void ResetBlockColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::BLOCK_COLOR);
    }
}

void SetTrackBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetTrackBackgroundColor(frameNode, SliderModelNG::CreateSolidGradient(Color(color)), true);
}

void SetTrackBackgroundColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        SliderModelNG::CreateWithColorResourceObj(frameNode, resObj, SliderColorType::TRACK_COLOR);
    }
    SetTrackBackgroundColor(node, result.GetValue());
}

void SetLinearTrackBackgroundColor(
    ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < colorLength; ++j) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }

    SliderModelNG::SetTrackBackgroundColor(frameNode, tempGradient, false);
}

void ResetTrackBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetTrackColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::TRACK_COLOR);
    }
}

void SetSelectColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSelectColor(frameNode, SliderModelNG::CreateSolidGradient(Color(color)), true);
}

void SetSelectColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        SliderModelNG::CreateWithColorResourceObj(frameNode, resObj, SliderColorType::SELECT_COLOR);
    }
    SetSelectColor(node, result.GetValue());
}

void SetLinearSelectColor(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::Gradient tempGradient;
    for (int32_t j = 0; j < colorLength; ++j) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(Color(gradient->color[j])));
        gradientColor.SetDimension(
            Dimension(gradient->offset[j].number, static_cast<DimensionUnit>(gradient->offset[j].unit)));
        tempGradient.AddColor(gradientColor);
    }

    SliderModelNG::SetSelectColor(frameNode, tempGradient, false);
}

void ResetSelectColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSelectColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        SliderModelNG::CreateWithColorResourceObj(frameNode, nullptr, SliderColorType::SELECT_COLOR);
    }
}

void SetShowSteps(ArkUINodeHandle node, int showSteps)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, static_cast<bool>(showSteps));
}

void SetShowStepsWithOptions(
    ArkUINodeHandle node, int showSteps, ArkUISliderShowStepOptions* options, ArkUI_Int32 length)
{
    std::unordered_map<uint32_t, std::string> optionMaps;
    std::optional<std::unordered_map<uint32_t, std::string>> showStepOptions = std::nullopt;
    while (options && (length > 0)) {
        optionMaps[options->step] = std::string(options->text);
        ++options;
        --length;
    }
    if (optionMaps.size() > 0) {
        showStepOptions = optionMaps;
    }
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, static_cast<bool>(showSteps), showStepOptions);
}

void ResetShowSteps(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, DEFAULT_SHOW_STEPS);
}

void SetThickness(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension thickness = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetThickness(frameNode, thickness);
}

void ResetThickness(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetThickness(frameNode, CalcDimension(0.0));
}

void SetSliderValue(ArkUINodeHandle node, float value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderValue(frameNode, value);
}

void SetMinLabel(ArkUINodeHandle node, float value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinLabel(frameNode, value);
}

void SetMaxLabel(ArkUINodeHandle node, float value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMaxLabel(frameNode, value);
}

void SetDirection(ArkUINodeHandle node, int value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetDirection(frameNode, static_cast<Axis>(value));
}

void SetStep(ArkUINodeHandle node, float value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStep(frameNode, value);
}

void SetReverse(ArkUINodeHandle node, int value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetReverse(frameNode, static_cast<bool>(value));
}

void SetSliderStyle(ArkUINodeHandle node, int value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (value < 0 || value >= static_cast<int32_t>(SLIDER_MODE.size())) {
        return;
    }
    SliderModelNG::SetSliderMode(frameNode, SLIDER_MODE[value]);
}

void ResetSliderValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderValue(frameNode, DEFAULT_VALUE);
}

void ResetMinLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinLabel(frameNode, DEFAULT_MIN_VALUE);
}

void ResetMaxLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMaxLabel(frameNode, DEFAULT_MAX_VALUE);
}

void ResetDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}

void ResetStep(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStep(frameNode, DEFAULT_STEP_VALUE);
}

void ResetReverse(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetReverse(frameNode, false);
}

void ResetSliderStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderMode(frameNode, SliderModel::SliderMode::OUTSET);
}

void SetSliderBlockImage(ArkUINodeHandle node, const char* src, const char* bundle, const char* module)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr(src);
    std::string bundleStr(bundle);
    std::string moduleStr(module);
    SliderModelNG::SetBlockImage(frameNode, srcStr, bundleStr, moduleStr);
}

void ResetSliderBlockImage(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
}

void SetSliderBlockPath(
    ArkUINodeHandle node, const char* type, const ArkUI_Float32 (*attribute)[2], const char* commands)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
}

void SetSliderBlockType(ArkUINodeHandle node, int value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (value < 0 || value >= static_cast<int32_t>(SLIDER_STYLE_TYPE.size())) {
        return;
    }
    SliderModelNG::SetBlockType(frameNode, SLIDER_STYLE_TYPE[value]);
}

void ResetSliderBlockType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockType(frameNode);
}

void SetSliderValidSlideRange(ArkUINodeHandle node, float from, float to)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetValidSlideRange(frameNode, from, to);
}

void ResetSliderValidSlideRange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetValidSlideRange(frameNode);
}

void SetSelectedBorderRadius(ArkUINodeHandle node, float value, int unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    SliderModelNG::SetSelectedBorderRadius(frameNode, radius);
}

void ResetSelectedBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSelectedBorderRadius(frameNode);
}

void SetInteractionMode(ArkUINodeHandle node, int value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSliderInteractionMode(frameNode, static_cast<SliderModel::SliderInteraction>(value));
}

void ResetInteractionMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSliderInteractionMode(frameNode);
}

void SetMinResponsiveDistance(ArkUINodeHandle node, float value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetMinResponsiveDistance(frameNode, value);
}

void ResetMinResponsiveDistance(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetMinResponsiveDistance(frameNode);
}

void SetPrefix(ArkUINodeHandle node, ArkUINodeHandle prefix, ArkUISliderCustomContentOptions* options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* prefixNode = reinterpret_cast<FrameNode*>(prefix);
    CHECK_NULL_VOID(prefixNode);
    CHECK_NULL_VOID(options);
    SliderPrefixOptions prefixOptions;
    prefixOptions.accessibilityText = options->accessibilityText ? options->accessibilityText : "";
    prefixOptions.accessibilityDescription = options->accessibilityDescription ? options->accessibilityDescription : "";
    prefixOptions.accessibilityLevel = options->accessibilityLevel ? options->accessibilityLevel : "";
    prefixOptions.accessibilityGroup = options->accessibilityGroup;
    SliderModelNG::SetPrefix(frameNode, AceType::Claim<UINode>(prefixNode), prefixOptions);
}

void ResetPrefix(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetPrefix(frameNode);
}

void SetSuffix(ArkUINodeHandle node, ArkUINodeHandle suffix, ArkUISliderCustomContentOptions* options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* suffixNode = reinterpret_cast<FrameNode*>(suffix);
    CHECK_NULL_VOID(suffixNode);
    CHECK_NULL_VOID(options);
    SliderSuffixOptions suffixOptions;
    suffixOptions.accessibilityText = options->accessibilityText ? options->accessibilityText : "";
    suffixOptions.accessibilityDescription = options->accessibilityDescription ? options->accessibilityDescription : "";
    suffixOptions.accessibilityLevel = options->accessibilityLevel ? options->accessibilityLevel : "";
    suffixOptions.accessibilityGroup = options->accessibilityGroup;
    SliderModelNG::SetSuffix(frameNode, AceType::Claim<UINode>(suffixNode), suffixOptions);
}

void ResetSuffix(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSuffix(frameNode);
}

void SetDigitalCrownSensitivity(ArkUINodeHandle node, ArkUI_Int32 value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetDigitalCrownSensitivity(frameNode, value);
#endif
}

void ResetDigitalCrownSensitivity(ArkUINodeHandle node)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetDigitalCrownSensitivity(frameNode);
#endif
}

void SetOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(float, int32_t)>*>(callback);
        SliderModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        SliderModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetOnChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetOnChange(frameNode, nullptr);
}

ArkUI_Uint32 GetBlockColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return SliderModelNG::GetBlockColor(frameNode).GetValue();
}

ArkUI_Uint32 GetTrackBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetTrackBackgroundColor(frameNode);
    return gradient.GetColors().at(0).GetLinearColor().ToColor().GetValue();
}

ArkUI_Uint32 GetSelectColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetSelectColor(frameNode);
    return gradient.GetColors().at(0).GetLinearColor().ToColor().GetValue();
}

ArkUI_Int32 GetLinearBlockColor(ArkUINodeHandle node, ArkUI_Uint32 (*colors)[LINEAR_GRADIENT_LIMIT_TO_SLIDER],
    ArkUI_Float32 (*stop)[LINEAR_GRADIENT_LIMIT_TO_SLIDER])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetLinearGradientBlockColor(frameNode);
    std::vector<OHOS::Ace::NG::GradientColor> gradientColors = gradient.GetColors();
    // 0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        if (index >= LINEAR_GRADIENT_LIMIT_TO_SLIDER) {
            break;
        }
        (*colors)[index] = gradientColor.GetLinearColor().GetValue();
        (*stop)[index] = gradientColor.GetDimension().Value();
        ++index;
    }
    return index;
}

ArkUI_Int32 GetLinearSelectColor(ArkUINodeHandle node, ArkUI_Uint32 (*colors)[LINEAR_GRADIENT_LIMIT_TO_SLIDER],
    ArkUI_Float32 (*stop)[LINEAR_GRADIENT_LIMIT_TO_SLIDER])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetSelectColor(frameNode);
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    // 0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        if (index >= LINEAR_GRADIENT_LIMIT_TO_SLIDER) {
            break;
        }
        (*colors)[index] = gradientColor.GetLinearColor().GetValue();
        (*stop)[index] = gradientColor.GetDimension().Value();
        ++index;
    }
    return index;
}

ArkUI_Int32 GetLinearTrackBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 (*colors)[LINEAR_GRADIENT_LIMIT_TO_SLIDER],
    ArkUI_Float32 (*stop)[LINEAR_GRADIENT_LIMIT_TO_SLIDER])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    NG::Gradient gradient = SliderModelNG::GetTrackBackgroundColor(frameNode);
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    // 0 start index
    int index = 0;
    for (auto& gradientColor : gradientColors) {
        if (index >= LINEAR_GRADIENT_LIMIT_TO_SLIDER) {
            break;
        }
        (*colors)[index] = gradientColor.GetLinearColor().GetValue();
        (*stop)[index] = gradientColor.GetDimension().Value();
        ++index;
    }
    return index;
}

ArkUI_Bool GetShowSteps(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(SliderModelNG::GetShowSteps(frameNode));
}

ArkUI_Int32 GetBlockType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SLIDER_STYLE_TYPE_MAP[SliderModelNG::GetBlockType(frameNode)];
}

ArkUI_Float32 GetSliderValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetSliderValue(frameNode);
}

ArkUI_Float32 GetMinLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetMinLabel(frameNode);
}

ArkUI_Float32 GetMaxLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetMaxLabel(frameNode);
}

ArkUI_Int32 GetDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SliderModelNG::GetDirection(frameNode));
}

ArkUI_Float32 GetStep(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetStep(frameNode);
}

ArkUI_Bool GetReverse(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(SliderModelNG::GetReverse(frameNode));
}

ArkUI_Int32 GetSliderStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SLIDER_MODE_MAP[SliderModelNG::GetSliderMode(frameNode)];
}
ArkUI_CharPtr GetBlockImageValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = SliderModelNG::GetBlockImageValue(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetSliderBlockShape(ArkUINodeHandle node, ArkUI_Float32 (*value)[5])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    RefPtr<BasicShape> basicShape = SliderModelNG::GetBlockShape(frameNode);
    auto shapeType = basicShape->GetBasicShapeType();
    // index 0 shapeType
    (*value)[0] = SHAPE_TYPE_MAP[shapeType];
    // index 1 width
    (*value)[1] = basicShape->GetWidth().Value();
    // index 2 height
    (*value)[2] = basicShape->GetHeight().Value();
    switch (shapeType) {
        case BasicShapeType::PATH: {
            auto path = AceType::DynamicCast<Path>(basicShape);
            g_strValue = path->GetValue();
            return g_strValue.c_str();
        }
        case BasicShapeType::RECT: {
            auto shapeRect = AceType::DynamicCast<ShapeRect>(basicShape);
            // index 3 radius x
            (*value)[3] = shapeRect->GetTopLeftRadius().GetX().Value();
            // index 4 radius y
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return SliderModelNG::GetThickness(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUISliderValidSlideRange GetSliderValidSlideRange(ArkUINodeHandle node)
{
    ArkUISliderValidSlideRange errorReturn = { std::numeric_limits<float>::quiet_NaN(),
        std::numeric_limits<float>::quiet_NaN() };
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, errorReturn);
    auto rangeValue = SliderModelNG::GetValidSlideRange(frameNode);
    CHECK_NULL_RETURN(rangeValue && rangeValue->HasValidValues(), errorReturn);
    return { rangeValue->GetFromValue(), rangeValue->GetToValue() };
}

ArkUI_Bool GetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, true);
    return SliderModelNG::GetEnableHapticFeedback(frameNode);
}

void SetEnableHapticFeedback(ArkUINodeHandle node, int enableHapticFeedback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetEnableHapticFeedback(frameNode, enableHapticFeedback);
}

void ResetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetEnableHapticFeedback(frameNode, true);
}
} // namespace SliderModifier

void CreateSlider(ArkUI_Float32 value, ArkUI_Float32 step, ArkUI_Float32 min, ArkUI_Float32 max)
{
    static SliderModelNG model;
    model.Create(value, step, min, max);
}

ArkUINodeHandle CreateSliderFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = SliderModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SliderPaintPropertyUpdateValue(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateValue(static_cast<float>(value));
}

void SetOnChangeEvent(void* callback)
{
    if (callback) {
        auto changeEvent = reinterpret_cast<std::function<void(float)>*>(callback);
        FrameNode* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        SliderModelNG::SetOnChangeEvent(frameNode, std::move(*changeEvent));
    }
}

void SetOnSliderChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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

#ifndef CROSS_PLATFORM
void SetShowTipsImpl(ArkUINodeHandle node, ArkUI_Bool isShow, const char* value)
{
    std::optional<std::string> content;
    if (value == nullptr) {
        content = std::nullopt;
    }
    GetSliderModelImpl()->SetShowTips(static_cast<bool>(isShow), content);
}

void SetShowTipsPtrImpl(ArkUINodeHandle node, ArkUI_Bool isShow, const char* value, void* strRawPtr)
{
    std::optional<std::string> content;
    if (value == nullptr) {
        content = std::nullopt;
    }
    GetSliderModelImpl()->SetShowTips(static_cast<bool>(isShow), content);
}

void SetSliderStepSizeImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    Dimension stepSize = Dimension(value, static_cast<DimensionUnit>(unit));
    GetSliderModelImpl()->SetStepSize(stepSize);
}

void ResetSliderStepSizeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetStepSize();
}

void SetBlockSizeImpl(
    ArkUINodeHandle node, ArkUI_Float32 widthVal, int widthUnit, ArkUI_Float32 heightVal, int heightUnit)
{
    GetSliderModelImpl()->SetBlockSize(Dimension(widthVal, static_cast<DimensionUnit>(widthUnit)),
        Dimension(heightVal, static_cast<DimensionUnit>(heightUnit)));
}

void ResetBlockSizeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockSize();
}

void SetTrackBorderRadiusImpl(ArkUINodeHandle node, float value, int unit)
{
    GetSliderModelImpl()->SetTrackBorderRadius(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetTrackBorderRadiusImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetTrackBorderRadius();
}

void SetStepColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSliderModelImpl()->SetStepColor(Color(color));
}

void SetStepColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr) {}

void ResetStepColorImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetStepColor();
}

void SetBlockBorderColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSliderModelImpl()->SetBlockBorderColor(Color(color));
}

void SetBlockBorderColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
}

void ResetBlockBorderColorImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockBorderColor();
}

void SetBlockBorderWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetSliderModelImpl()->SetBlockBorderWidth(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetBlockBorderWidthImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockBorderWidth();
}

void SetBlockColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSliderModelImpl()->SetBlockColor(Color(color));
}

void SetBlockColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetSliderModelImpl()->SetBlockColor(Color(color));
}

void SetLinearBlockColorImpl(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength) {}

void ResetBlockColorImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockColor();
}

void SetTrackBackgroundColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSliderModelImpl()->SetTrackBackgroundColor(Color(color));
}

void SetTrackBackgroundColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetSliderModelImpl()->SetTrackBackgroundColor(Color(color));
}

void SetLinearTrackBackgroundColorImpl(
    ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength)
{}

void ResetTrackBackgroundColorImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetTrackColor();
}

void SetSelectColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetSliderModelImpl()->SetSelectColor(Color(color));
}

void SetSelectColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetSliderModelImpl()->SetSelectColor(Color(color));
}

void SetLinearSelectColorImpl(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 colorLength)
{}

void ResetSelectColorImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetSelectColor();
}

void SetShowStepsImpl(ArkUINodeHandle node, int showSteps)
{
    GetSliderModelImpl()->SetShowSteps(showSteps);
}

void SetShowStepsWithOptionsImpl(
    ArkUINodeHandle node, int showSteps, ArkUISliderShowStepOptions* options, ArkUI_Int32 length)
{}

void SetThicknessImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    GetSliderModelImpl()->SetThickness(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void SetMinLabelImpl(ArkUINodeHandle node, float value)
{
    GetSliderModelImpl()->SetMinLabel(value);
}

void SetMaxLabelImpl(ArkUINodeHandle node, float value)
{
    GetSliderModelImpl()->SetMaxLabel(value);
}

void SetDirectionImpl(ArkUINodeHandle node, int value)
{
    GetSliderModelImpl()->SetDirection(static_cast<Axis>(value));
}

void SetReverseImpl(ArkUINodeHandle node, int value)
{
    GetSliderModelImpl()->SetReverse(value);
}

void SetSliderStyleImpl(ArkUINodeHandle node, int value)
{
    GetSliderModelImpl()->SetSliderMode(static_cast<SliderModel::SliderMode>(value));
}

void SetSliderBlockImageImpl(ArkUINodeHandle node, const char* src, const char* bundle, const char* module)
{
    GetSliderModelImpl()->SetBlockImage(src, bundle, module);
}

void ResetSliderBlockImageImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockImage();
}

void SetSliderBlockShapeImpl(ArkUINodeHandle node, const char* type, const ArkUI_Float32* attribute, int length) {}

void ResetSliderBlockShapeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockShape();
}

void SetSliderBlockTypeImpl(ArkUINodeHandle node, int value)
{
    GetSliderModelImpl()->SetBlockType(static_cast<SliderModel::BlockStyleType>(value));
}

void ResetSliderBlockTypeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetBlockType();
}

void ResetSliderValidSlideRangeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetValidSlideRange();
}

void SetSelectedBorderRadiusImpl(ArkUINodeHandle node, float value, int unit)
{
    GetSliderModelImpl()->SetSelectedBorderRadius(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetSelectedBorderRadiusImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetSelectedBorderRadius();
}

void ResetInteractionModeImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetSliderInteractionMode();
}

void ResetMinResponsiveDistanceImpl(ArkUINodeHandle node)
{
    GetSliderModelImpl()->ResetMinResponsiveDistance();
}

void SetPrefixImpl(ArkUINodeHandle node, ArkUINodeHandle prefix, ArkUISliderCustomContentOptions* options)
{
    auto prefixNode = AceType::Claim(reinterpret_cast<NG::UINode*>(prefix));
    CHECK_NULL_VOID(prefixNode);
    CHECK_NULL_VOID(options);
    SliderPrefixOptions prefixOptions;
    prefixOptions.accessibilityText = options->accessibilityText ? options->accessibilityText : "";
    prefixOptions.accessibilityDescription = options->accessibilityDescription ? options->accessibilityDescription : "";
    prefixOptions.accessibilityLevel = options->accessibilityLevel ? options->accessibilityLevel : "";
    prefixOptions.accessibilityGroup = options->accessibilityGroup;
    GetSliderModelImpl()->SetPrefix(prefixNode, prefixOptions);
}

void SetSuffixImpl(ArkUINodeHandle node, ArkUINodeHandle suffix, ArkUISliderCustomContentOptions* options)
{
    auto suffixNode = AceType::Claim(reinterpret_cast<NG::UINode*>(suffix));
    CHECK_NULL_VOID(suffixNode);
    CHECK_NULL_VOID(options);
    SliderSuffixOptions suffixOptions;
    suffixOptions.accessibilityText = options->accessibilityText ? options->accessibilityText : "";
    suffixOptions.accessibilityDescription = options->accessibilityDescription ? options->accessibilityDescription : "";
    suffixOptions.accessibilityLevel = options->accessibilityLevel ? options->accessibilityLevel : "";
    suffixOptions.accessibilityGroup = options->accessibilityGroup;
    GetSliderModelImpl()->SetSuffix(suffixNode, suffixOptions);
}

void SetDigitalCrownSensitivityImpl(ArkUINodeHandle node, ArkUI_Int32 value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    GetSliderModelImpl()->SetDigitalCrownSensitivity(value);
#endif
}

void ResetDigitalCrownSensitivityImpl(ArkUINodeHandle node)
{
#ifdef SUPPORT_DIGITAL_CROWN
    GetSliderModelImpl()->ResetDigitalCrownSensitivity();
#endif
}

void SetOnChangeImpl(ArkUINodeHandle node, void* callback) {}

void SetEnableHapticFeedbackImpl(ArkUINodeHandle node, int enableHapticFeedback)
{
    GetSliderModelImpl()->SetEnableHapticFeedback(enableHapticFeedback);
}

void CreateSliderImpl(ArkUI_Float32 value, ArkUI_Float32 step, ArkUI_Float32 min, ArkUI_Float32 max)
{
    if (value < min) {
        value = min;
    }

    if (value > max) {
        value = max;
    }
    GetSliderModelImpl()->Create(value, step, min, max);
}
#endif

const ArkUISliderModifier* GetSliderDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUISliderModifier modifier = {
            .setShowTips = SetShowTipsImpl,
            .resetShowTips = nullptr,
            .setSliderStepSize = SetSliderStepSizeImpl,
            .resetSliderStepSize = ResetSliderStepSizeImpl,
            .setBlockSize = SetBlockSizeImpl,
            .resetBlockSize = ResetBlockSizeImpl,
            .setTrackBorderRadius = SetTrackBorderRadiusImpl,
            .resetTrackBorderRadius = ResetTrackBorderRadiusImpl,
            .setStepColor = SetStepColorImpl,
            .resetStepColor = ResetStepColorImpl,
            .setBlockBorderColor = SetBlockBorderColorImpl,
            .resetBlockBorderColor = ResetBlockBorderColorImpl,
            .setBlockBorderWidth = SetBlockBorderWidthImpl,
            .resetBlockBorderWidth = ResetBlockBorderWidthImpl,
            .setBlockColor = SetBlockColorImpl,
            .resetBlockColor = ResetBlockColorImpl,
            .setTrackBackgroundColor = SetTrackBackgroundColorImpl,
            .resetTrackBackgroundColor = ResetTrackBackgroundColorImpl,
            .setSelectColor = SetSelectColorImpl,
            .resetSelectColor = ResetSelectColorImpl,
            .setShowSteps = SetShowStepsImpl,
            .resetShowSteps = nullptr,
            .setThickness = SetThicknessImpl,
            .resetThickness = nullptr,
            .setSliderValue = nullptr,
            .setMinLabel = SetMinLabelImpl,
            .setMaxLabel = SetMaxLabelImpl,
            .setDirection = SetDirectionImpl,
            .setStep = nullptr,
            .setReverse = SetReverseImpl,
            .setSliderStyle = SetSliderStyleImpl,
            .resetSliderValue = nullptr,
            .resetMinLabel = nullptr,
            .resetMaxLabel = nullptr,
            .resetDirection = nullptr,
            .resetStep = nullptr,
            .resetReverse = nullptr,
            .resetSliderStyle = nullptr,
            .setSliderBlockImage = SetSliderBlockImageImpl,
            .resetSliderBlockImage = ResetSliderBlockImageImpl,
            .setSliderBlockPath = nullptr,
            .setSliderBlockShape = SetSliderBlockShapeImpl,
            .resetSliderBlockShape = ResetSliderBlockShapeImpl,
            .setSliderBlockType = SetSliderBlockTypeImpl,
            .resetSliderBlockType = ResetSliderBlockTypeImpl,
            .setSliderValidSlideRange = nullptr,
            .resetSliderValidSlideRange = ResetSliderValidSlideRangeImpl,
            .setSelectedBorderRadius = SetSelectedBorderRadiusImpl,
            .resetSelectedBorderRadius = ResetSelectedBorderRadiusImpl,
            .setInteractionMode = nullptr,
            .resetInteractionMode = ResetInteractionModeImpl,
            .setMinResponsiveDistance = nullptr,
            .resetMinResponsiveDistance = ResetMinResponsiveDistanceImpl,
            .setOnChange = SetOnChangeImpl,
            .resetOnChange = nullptr,
            .setLinearTrackBackgroundColor = SetLinearTrackBackgroundColorImpl,
            .setLinearSelectColor = SetLinearSelectColorImpl,
            .getBlockColor = nullptr,
            .getTrackBackgroundColor = nullptr,
            .getSelectColor = nullptr,
            .getShowSteps = nullptr,
            .getBlockType = nullptr,
            .getSliderValue = nullptr,
            .getMinLabel = nullptr,
            .getMaxLabel = nullptr,
            .getDirection = nullptr,
            .getStep = nullptr,
            .getReverse = nullptr,
            .getSliderStyle = nullptr,
            .getBlockImageValue = nullptr,
            .getSliderBlockShape = nullptr,
            .getThickness = nullptr,
            .getSliderValidSlideRange = nullptr,
            .getEnableHapticFeedback = nullptr,
            .setEnableHapticFeedback = SetEnableHapticFeedbackImpl,
            .resetEnableHapticFeedback = nullptr,
            .setPrefix = SetPrefixImpl,
            .resetPrefix = nullptr,
            .setSuffix = SetSuffixImpl,
            .resetSuffix = nullptr,
            .setDigitalCrownSensitivity = nullptr,
            .resetDigitalCrownSensitivity = ResetDigitalCrownSensitivityImpl,
            .setShowStepsWithOptions = SetShowStepsWithOptionsImpl,
            .setShowTipsPtr = SetShowTipsPtrImpl,
            .setStepColorPtr = SetStepColorPtrImpl,
            .setBlockBorderColorPtr = SetBlockBorderColorPtrImpl,
            .setBlockColorPtr = SetBlockColorPtrImpl,
            .setTrackBackgroundColorPtr = SetTrackBackgroundColorPtrImpl,
            .setSelectColorPtr = SetSelectColorPtrImpl,
            .setLinearBlockColor = SetLinearBlockColorImpl,
            .resetLinearTrackBackgroundColor = ResetTrackBackgroundColorImpl,
            .resetLinearSelectColor = ResetSelectColorImpl,
            .resetLinearBlockColor = ResetBlockColorImpl,
            .getLinearTrackBackgroundColor = nullptr,
            .getLinearSelectColor = nullptr,
            .getLinearBlockColor = nullptr,
            .createSlider = CreateSliderImpl,
            .createSliderFrameNode = nullptr,
            .setOnChangeEvent = nullptr,
            .setOnSliderChange = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISliderModifier modifier = {
        .setShowTips = SliderModifier::SetShowTips,
        .resetShowTips = SliderModifier::ResetShowTips,
        .setSliderStepSize = SliderModifier::SetSliderStepSize,
        .resetSliderStepSize = SliderModifier::ResetSliderStepSize,
        .setBlockSize = SliderModifier::SetBlockSize,
        .resetBlockSize = SliderModifier::ResetBlockSize,
        .setTrackBorderRadius = SliderModifier::SetTrackBorderRadius,
        .resetTrackBorderRadius = SliderModifier::ResetTrackBorderRadius,
        .setStepColor = SliderModifier::SetStepColor,
        .resetStepColor = SliderModifier::ResetStepColor,
        .setBlockBorderColor = SliderModifier::SetBlockBorderColor,
        .resetBlockBorderColor = SliderModifier::ResetBlockBorderColor,
        .setBlockBorderWidth = SliderModifier::SetBlockBorderWidth,
        .resetBlockBorderWidth = SliderModifier::ResetBlockBorderWidth,
        .setBlockColor = SliderModifier::SetBlockColor,
        .resetBlockColor = SliderModifier::ResetBlockColor,
        .setTrackBackgroundColor = SliderModifier::SetTrackBackgroundColor,
        .resetTrackBackgroundColor = SliderModifier::ResetTrackBackgroundColor,
        .setSelectColor = SliderModifier::SetSelectColor,
        .resetSelectColor = SliderModifier::ResetSelectColor,
        .setShowSteps = SliderModifier::SetShowSteps,
        .resetShowSteps = SliderModifier::ResetShowSteps,
        .setThickness = SliderModifier::SetThickness,
        .resetThickness = SliderModifier::ResetThickness,
        .setSliderValue = SliderModifier::SetSliderValue,
        .setMinLabel = SliderModifier::SetMinLabel,
        .setMaxLabel = SliderModifier::SetMaxLabel,
        .setDirection = SliderModifier::SetDirection,
        .setStep = SliderModifier::SetStep,
        .setReverse = SliderModifier::SetReverse,
        .setSliderStyle = SliderModifier::SetSliderStyle,
        .resetSliderValue = SliderModifier::ResetSliderValue,
        .resetMinLabel = SliderModifier::ResetMinLabel,
        .resetMaxLabel = SliderModifier::ResetMaxLabel,
        .resetDirection = SliderModifier::ResetDirection,
        .resetStep = SliderModifier::ResetStep,
        .resetReverse = SliderModifier::ResetReverse,
        .resetSliderStyle = SliderModifier::ResetSliderStyle,
        .setSliderBlockImage = SliderModifier::SetSliderBlockImage,
        .resetSliderBlockImage = SliderModifier::ResetSliderBlockImage,
        .setSliderBlockPath = SliderModifier::SetSliderBlockPath,
        .setSliderBlockShape = SliderModifier::SetSliderBlockShape,
        .resetSliderBlockShape = SliderModifier::ResetSliderBlockShape,
        .setSliderBlockType = SliderModifier::SetSliderBlockType,
        .resetSliderBlockType = SliderModifier::ResetSliderBlockType,
        .setSliderValidSlideRange = SliderModifier::SetSliderValidSlideRange,
        .resetSliderValidSlideRange = SliderModifier::ResetSliderValidSlideRange,
        .setSelectedBorderRadius = SliderModifier::SetSelectedBorderRadius,
        .resetSelectedBorderRadius = SliderModifier::ResetSelectedBorderRadius,
        .setInteractionMode = SliderModifier::SetInteractionMode,
        .resetInteractionMode = SliderModifier::ResetInteractionMode,
        .setMinResponsiveDistance = SliderModifier::SetMinResponsiveDistance,
        .resetMinResponsiveDistance = SliderModifier::ResetMinResponsiveDistance,
        .setOnChange = SliderModifier::SetOnChange,
        .resetOnChange = SliderModifier::ResetOnChange,
        .setLinearTrackBackgroundColor = SliderModifier::SetLinearTrackBackgroundColor,
        .setLinearSelectColor = SliderModifier::SetLinearSelectColor,
        .getBlockColor = SliderModifier::GetBlockColor,
        .getTrackBackgroundColor = SliderModifier::GetTrackBackgroundColor,
        .getSelectColor = SliderModifier::GetSelectColor,
        .getShowSteps = SliderModifier::GetShowSteps,
        .getBlockType = SliderModifier::GetBlockType,
        .getSliderValue = SliderModifier::GetSliderValue,
        .getMinLabel = SliderModifier::GetMinLabel,
        .getMaxLabel = SliderModifier::GetMaxLabel,
        .getDirection = SliderModifier::GetDirection,
        .getStep = SliderModifier::GetStep,
        .getReverse = SliderModifier::GetReverse,
        .getSliderStyle = SliderModifier::GetSliderStyle,
        .getBlockImageValue = SliderModifier::GetBlockImageValue,
        .getSliderBlockShape = SliderModifier::GetSliderBlockShape,
        .getThickness = SliderModifier::GetThickness,
        .getSliderValidSlideRange = SliderModifier::GetSliderValidSlideRange,
        .getEnableHapticFeedback = SliderModifier::GetEnableHapticFeedback,
        .setEnableHapticFeedback = SliderModifier::SetEnableHapticFeedback,
        .resetEnableHapticFeedback = SliderModifier::ResetEnableHapticFeedback,
        .setPrefix = SliderModifier::SetPrefix,
        .resetPrefix = SliderModifier::ResetPrefix,
        .setSuffix = SliderModifier::SetSuffix,
        .resetSuffix = SliderModifier::ResetSuffix,
        .setDigitalCrownSensitivity = SliderModifier::SetDigitalCrownSensitivity,
        .resetDigitalCrownSensitivity = SliderModifier::ResetDigitalCrownSensitivity,
        .setShowStepsWithOptions = SliderModifier::SetShowStepsWithOptions,
        .setShowTipsPtr = SliderModifier::SetShowTipsPtr,
        .setStepColorPtr = SliderModifier::SetStepColorPtr,
        .setBlockBorderColorPtr = SliderModifier::SetBlockBorderColorPtr,
        .setBlockColorPtr = SliderModifier::SetBlockColorPtr,
        .setTrackBackgroundColorPtr = SliderModifier::SetTrackBackgroundColorPtr,
        .setSelectColorPtr = SliderModifier::SetSelectColorPtr,
        .setLinearBlockColor = SliderModifier::SetLinearBlockColor,
        .resetLinearTrackBackgroundColor = SliderModifier::ResetTrackBackgroundColor,
        .resetLinearSelectColor = SliderModifier::ResetSelectColor,
        .resetLinearBlockColor = SliderModifier::ResetBlockColor,
        .getLinearTrackBackgroundColor = SliderModifier::GetLinearTrackBackgroundColor,
        .getLinearSelectColor = SliderModifier::GetLinearSelectColor,
        .getLinearBlockColor = SliderModifier::GetLinearBlockColor,
        .createSlider = CreateSlider,
        .createSliderFrameNode = CreateSliderFrameNode,
        .setOnChangeEvent = SetOnChangeEvent,
        .setOnSliderChange = SetOnSliderChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUISliderModifier* GetCJUISliderModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISliderModifier modifier = {
        .setShowTips = SliderModifier::SetShowTips,
        .resetShowTips = SliderModifier::ResetShowTips,
        .setSliderStepSize = SliderModifier::SetSliderStepSize,
        .resetSliderStepSize = SliderModifier::ResetSliderStepSize,
        .setBlockSize = SliderModifier::SetBlockSize,
        .resetBlockSize = SliderModifier::ResetBlockSize,
        .setTrackBorderRadius = SliderModifier::SetTrackBorderRadius,
        .resetTrackBorderRadius = SliderModifier::ResetTrackBorderRadius,
        .setStepColor = SliderModifier::SetStepColor,
        .resetStepColor = SliderModifier::ResetStepColor,
        .setBlockBorderColor = SliderModifier::SetBlockBorderColor,
        .resetBlockBorderColor = SliderModifier::ResetBlockBorderColor,
        .setBlockBorderWidth = SliderModifier::SetBlockBorderWidth,
        .resetBlockBorderWidth = SliderModifier::ResetBlockBorderWidth,
        .setBlockColor = SliderModifier::SetBlockColor,
        .resetBlockColor = SliderModifier::ResetBlockColor,
        .setTrackBackgroundColor = SliderModifier::SetTrackBackgroundColor,
        .resetTrackBackgroundColor = SliderModifier::ResetTrackBackgroundColor,
        .setSelectColor = SliderModifier::SetSelectColor,
        .resetSelectColor = SliderModifier::ResetSelectColor,
        .setShowSteps = SliderModifier::SetShowSteps,
        .resetShowSteps = SliderModifier::ResetShowSteps,
        .setThickness = SliderModifier::SetThickness,
        .resetThickness = SliderModifier::ResetThickness,
        .setSliderValue = SliderModifier::SetSliderValue,
        .setMinLabel = SliderModifier::SetMinLabel,
        .setMaxLabel = SliderModifier::SetMaxLabel,
        .setDirection = SliderModifier::SetDirection,
        .setStep = SliderModifier::SetStep,
        .setReverse = SliderModifier::SetReverse,
        .setSliderStyle = SliderModifier::SetSliderStyle,
        .resetSliderValue = SliderModifier::ResetSliderValue,
        .resetMinLabel = SliderModifier::ResetMinLabel,
        .resetMaxLabel = SliderModifier::ResetMaxLabel,
        .resetDirection = SliderModifier::ResetDirection,
        .resetStep = SliderModifier::ResetStep,
        .resetReverse = SliderModifier::ResetReverse,
        .resetSliderStyle = SliderModifier::ResetSliderStyle,
        .setSliderBlockImage = SliderModifier::SetSliderBlockImage,
        .resetSliderBlockImage = SliderModifier::ResetSliderBlockImage,
        .setSliderBlockPath = SliderModifier::SetSliderBlockPath,
        .setSliderBlockShape = SliderModifier::SetSliderBlockShape,
        .resetSliderBlockShape = SliderModifier::ResetSliderBlockShape,
        .setSliderBlockType = SliderModifier::SetSliderBlockType,
        .resetSliderBlockType = SliderModifier::ResetSliderBlockType,
        .setSliderValidSlideRange = SliderModifier::SetSliderValidSlideRange,
        .resetSliderValidSlideRange = SliderModifier::ResetSliderValidSlideRange,
        .setSelectedBorderRadius = SliderModifier::SetSelectedBorderRadius,
        .resetSelectedBorderRadius = SliderModifier::ResetSelectedBorderRadius,
        .setInteractionMode = SliderModifier::SetInteractionMode,
        .resetInteractionMode = SliderModifier::ResetInteractionMode,
        .setMinResponsiveDistance = SliderModifier::SetMinResponsiveDistance,
        .resetMinResponsiveDistance = SliderModifier::ResetMinResponsiveDistance,
        .getBlockColor = SliderModifier::GetBlockColor,
        .getTrackBackgroundColor = SliderModifier::GetTrackBackgroundColor,
        .getSelectColor = SliderModifier::GetSelectColor,
        .getShowSteps = SliderModifier::GetShowSteps,
        .getBlockType = SliderModifier::GetBlockType,
        .getSliderValue = SliderModifier::GetSliderValue,
        .getMinLabel = SliderModifier::GetMinLabel,
        .getMaxLabel = SliderModifier::GetMaxLabel,
        .getDirection = SliderModifier::GetDirection,
        .getStep = SliderModifier::GetStep,
        .getReverse = SliderModifier::GetReverse,
        .getSliderStyle = SliderModifier::GetSliderStyle,
        .getBlockImageValue = SliderModifier::GetBlockImageValue,
        .getSliderBlockShape = SliderModifier::GetSliderBlockShape,
        .getThickness = SliderModifier::GetThickness,
        .getSliderValidSlideRange = SliderModifier::GetSliderValidSlideRange,
        .getEnableHapticFeedback = SliderModifier::GetEnableHapticFeedback,
        .setEnableHapticFeedback = SliderModifier::SetEnableHapticFeedback,
        .resetEnableHapticFeedback = SliderModifier::ResetEnableHapticFeedback,
        .setPrefix = SliderModifier::SetPrefix,
        .resetPrefix = SliderModifier::ResetPrefix,
        .setSuffix = SliderModifier::SetSuffix,
        .resetSuffix = SliderModifier::ResetSuffix,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace OHOS::Ace::NG