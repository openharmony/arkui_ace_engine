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
#include "core/interfaces/native/node/data_panel_modifier.h"

#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_CLOSE_EFFECT = true;
constexpr double DEFAULT_STROKE_WIDTH = 24.0;
constexpr double DEFAULT_RADIUS = 20.0;
constexpr double DEFAULT_OFFSET_X = 5.0;
constexpr double DEFAULT_OFFSET_Y = 5.0;
const std::string DEFAULT_TRACK_BACKGROUND = "#08182431";
}
void SetCloseEffect(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, value);
}

void ResetCloseEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, IS_CLOSE_EFFECT);
}

void SetDataPanelTrackBackgroundColor(ArkUINodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color(value));
}

void SetDataPanelTrackBackgroundColorPtr(ArkUINodeHandle node, uint32_t value, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color(value));

    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        DataPanelModelNG::CreateWithResourceObj(
            frameNode, DataPanelResourceType::TRACK_BACKGROUND_COLOR, colorResObj);
    }
}

void ResetDataPanelTrackBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color::FromString(DEFAULT_TRACK_BACKGROUND));
    DataPanelModelNG::CreateWithResourceObj(frameNode, DataPanelResourceType::TRACK_BACKGROUND_COLOR, nullptr);
}

void SetDataPanelStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void SetDataPanelStrokeWidthPtr(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit, void* strokeWidthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));

    if (SystemProperties::ConfigChangePerform()) {
        auto* strokeWidth = reinterpret_cast<ResourceObject*>(strokeWidthRawPtr);
        auto strokeWidthResObj = AceType::Claim(strokeWidth);
        DataPanelModelNG::CreateWithResourceObj(frameNode, DataPanelResourceType::STROKE_WIDTH, strokeWidthResObj);
    }
}

void ResetDataPanelStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    if (SystemProperties::ConfigChangePerform()) {
        DataPanelModelNG::CreateWithResourceObj(frameNode, DataPanelResourceType::STROKE_WIDTH, nullptr);
    }
}

void ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    RefPtr<DataPanelTheme> theme = themeManager->GetTheme<DataPanelTheme>();
    auto themeColors = theme->GetColorsArray();
    for (const auto& item : themeColors) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        colors.emplace_back(gradient);
    }
}

void SetValueColors(ArkUINodeHandle node, const struct ArkUIGradientType* gradient)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> shadowColors(gradient->length);
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }
        shadowColors.at(i) = tempGradient;
    }
    DataPanelModelNG::SetValueColors(frameNode, shadowColors);
}

void SetValueColorsPtr(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> shadowColors(gradient->length);
    std::vector<RefPtr<ResourceObject>> colorVectorObj;
    if (colorRawPtr) {
        colorVectorObj = *(static_cast<std::vector<RefPtr<ResourceObject>>*>(colorRawPtr));
    }
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }

        if (i < colorVectorObj.size() && colorVectorObj[i] && SystemProperties::ConfigChangePerform()) {
            std::string key = "shadow.color." + std::to_string(i);
            tempGradient.AddResource(
                key, colorVectorObj[i], [i](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
                    Color color;
                    ResourceParseUtils::ParseResColor(resObj, color);
                    gradient.ClearColors();
                    NG::GradientColor startColor;
                    startColor.SetLinearColor(LinearColor(color));
                    startColor.SetDimension(Dimension(0.0));
                    NG::GradientColor endColor;
                    endColor.SetLinearColor(LinearColor(color));
                    endColor.SetDimension(Dimension(1.0));
                    gradient.AddColor(startColor);
                    gradient.AddColor(endColor);
                });
        }
        
        shadowColors.at(i) = tempGradient;
    }
    DataPanelModelNG::SetValueColors(frameNode, shadowColors);
}

void ResetValueColors(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> colors;
    ConvertThemeColor(colors);
    DataPanelModelNG::SetValueColors(frameNode, colors);
}

void SetTrackShadow(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Float32 radius,
    ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::DataPanelShadow shadow;

    std::vector<OHOS::Ace::NG::Gradient> shadowColors(gradient->length);
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }
        shadowColors.at(i) = tempGradient;
    }

    shadow.radius = radius;
    shadow.offsetX = offsetX;
    shadow.offsetY = offsetY;
    shadow.colors = shadowColors;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void FillShadowColorsWithResource(const ArkUIGradientType* gradient,
    const std::vector<RefPtr<ResourceObject>>& colorVectorObj, std::vector<OHOS::Ace::NG::Gradient>& shadowColors)
{
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }
        if (i < colorVectorObj.size() && colorVectorObj[i] && SystemProperties::ConfigChangePerform()) {
            std::string key = "trackShadow.color." + std::to_string(i);
            tempGradient.AddResource(
                key, colorVectorObj[i], [i](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
                    Color color;
                    ResourceParseUtils::ParseResColor(resObj, color);
                    gradient.ClearColors();
                    NG::GradientColor startColor;
                    startColor.SetLinearColor(LinearColor(color));
                    startColor.SetDimension(Dimension(0.0));
                    NG::GradientColor endColor;
                    endColor.SetLinearColor(LinearColor(color));
                    endColor.SetDimension(Dimension(1.0));
                    gradient.AddColor(startColor);
                    gradient.AddColor(endColor);
                });
        }
        shadowColors.at(i) = tempGradient;
    }
}


void AddShadowResource(const struct ArkUIShadowOptionsResource* shadowRes, NG::DataPanelShadow& shadow)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto* radiusObj = reinterpret_cast<ResourceObject*>(shadowRes->radiusRawPtr);
    auto resObjValue = AceType::Claim(radiusObj);
    shadow.AddResource("shadow.radius", resObjValue,
        [](const RefPtr<ResourceObject>& resRadius, NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double radius = theme->GetTrackShadowRadius().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resRadius, radius);
            if (NonPositive(radius)) {
                radius = theme->GetTrackShadowRadius().ConvertToVp();
            }
            shadow.SetRadius(radius);
        });
    if (radiusObj != nullptr) {
        radiusObj->DecRefCount();
    }

    auto* offsetXObj = reinterpret_cast<ResourceObject*>(shadowRes->offsetXRawPtr);
    auto offsetXObjValue = AceType::Claim(offsetXObj);
    shadow.AddResource("shadow.offsetX", offsetXObjValue,
        [](const RefPtr<ResourceObject>& resOffsetX, NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double val = theme->GetTrackShadowOffsetX().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resOffsetX, val);
            if (val < 0.0) {
                val = theme->GetTrackShadowOffsetX().ConvertToVp();
            }
            shadow.SetOffsetX(val);
        });
    if (offsetXObj != nullptr) {
        offsetXObj->DecRefCount();
    }

    auto* offsetYObj = reinterpret_cast<ResourceObject*>(shadowRes->offsetYRawPtr);
    auto offsetYObjValue = AceType::Claim(offsetYObj);
    shadow.AddResource("shadow.offsetY", offsetYObjValue,
        [](const RefPtr<ResourceObject>& resOffsetY, NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double val = theme->GetTrackShadowOffsetY().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resOffsetY, val);
            shadow.SetOffsetY(val);
        });
    if (offsetYObj != nullptr) {
        offsetYObj->DecRefCount();
    }
}

void SetTrackShadowPtr(ArkUINodeHandle node, const struct ArkUIGradientType* gradient,
    const struct ArkUIDatePanelTrackShadow* trackShadow, const struct ArkUIShadowOptionsResource* shadowRes)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DataPanelShadow shadow;

    std::vector<NG::Gradient> shadowColors(gradient->length);
    std::vector<RefPtr<ResourceObject>> colorVectorObj;
    if (trackShadow->colorRawPtr) {
        colorVectorObj = *(static_cast<std::vector<RefPtr<ResourceObject>>*>(trackShadow->colorRawPtr));
    }
    FillShadowColorsWithResource(gradient, colorVectorObj, shadowColors);

    AddShadowResource(shadowRes, shadow);

    shadow.radius = trackShadow->radius;
    shadow.offsetX = trackShadow->offsetX;
    shadow.offsetY = trackShadow->offsetY;
    shadow.colors = shadowColors;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void SetNullTrackShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelShadow shadow;
    shadow.isShadowVisible = false;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void ResetTrackShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelShadow shadow;
    shadow.isShadowVisible = true;
    shadow.radius = DEFAULT_RADIUS;
    shadow.offsetX = DEFAULT_OFFSET_X;
    shadow.offsetY = DEFAULT_OFFSET_Y;
    std::vector<OHOS::Ace::NG::Gradient> colors;
    ConvertThemeColor(colors);
    shadow.colors = colors;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

namespace NodeModifier {
const ArkUIDataPanelModifier* GetDataPanelModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDataPanelModifier modifier = {
        .setCloseEffect = SetCloseEffect,
        .resetCloseEffect = ResetCloseEffect,
        .setDataPanelTrackBackgroundColor = SetDataPanelTrackBackgroundColor,
        .setDataPanelTrackBackgroundColorPtr = SetDataPanelTrackBackgroundColorPtr,
        .resetDataPanelTrackBackgroundColor = ResetDataPanelTrackBackgroundColor,
        .setDataPanelStrokeWidth = SetDataPanelStrokeWidth,
        .setDataPanelStrokeWidthPtr = SetDataPanelStrokeWidthPtr,
        .resetDataPanelStrokeWidth = ResetDataPanelStrokeWidth,
        .setValueColors = SetValueColors,
        .setValueColorsPtr = SetValueColorsPtr,
        .resetValueColors = ResetValueColors,
        .setTrackShadow = SetTrackShadow,
        .setTrackShadowPtr = SetTrackShadowPtr,
        .setNullTrackShadow = SetNullTrackShadow,
        .resetTrackShadow = ResetTrackShadow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIDataPanelModifier* GetCJUIDataPanelModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDataPanelModifier modifier = {
        .setCloseEffect = SetCloseEffect,
        .resetCloseEffect = ResetCloseEffect,
        .setDataPanelTrackBackgroundColor = SetDataPanelTrackBackgroundColor,
        .setDataPanelTrackBackgroundColorPtr = SetDataPanelTrackBackgroundColorPtr,
        .resetDataPanelTrackBackgroundColor = ResetDataPanelTrackBackgroundColor,
        .setDataPanelStrokeWidth = SetDataPanelStrokeWidth,
        .setDataPanelStrokeWidthPtr = SetDataPanelStrokeWidthPtr,
        .resetDataPanelStrokeWidth = ResetDataPanelStrokeWidth,
        .setValueColors = SetValueColors,
        .setValueColorsPtr = SetValueColorsPtr,
        .resetValueColors = ResetValueColors,
        .setTrackShadow = SetTrackShadow,
        .setTrackShadowPtr = SetTrackShadowPtr,
        .setNullTrackShadow = SetNullTrackShadow,
        .resetTrackShadow = ResetTrackShadow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
