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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_gauge_ffi.h"

#include "cj_lambda.h"
#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"

using namespace OHOS::Ace;

namespace {
const std::string INDICATOR_DEFAULT = "default";
const std::string INDICATOR_NULL = "null";
}  // namespace

namespace OHOS::Ace {
ViewAbstractModel* ViewAbstractModel::GetInstance()
{
    static NG::ViewAbstractModelNG instance;
    return &instance;
}

// Should use CJUIModifier API later
NG::GaugeModelNG* GetGaugeModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("gauge");
    if (module == nullptr) {
        LOGF("Can't find gauge dynamic module");
        abort();
    }
    return reinterpret_cast<NG::GaugeModelNG*>(module->GetModel());
}

}

extern "C" {
VectorColorStops FFICJCreateVectorColorStop(int64_t size)
{
    LOGI("Create ColorStop Vector");
    return new std::vector<ColorStop>(size);
}

void FFICJVectorColorStopSetElement(VectorColorStops vec, int64_t index, ColorStop colorStop)
{
    LOGI("ColorStop Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<ColorStop>*>(vec);
    (*actualVec)[index] = colorStop;
    LOGI("ColorStop Vector Set Element Success");
}

void FFICJVectorColorStopDelete(VectorColorStops vec)
{
    auto actualVec = reinterpret_cast<std::vector<ColorStop>*>(vec);
    delete actualVec;
}

VecLinearGradientHandle FFICJCreateVectorGaugeLinearGradient(int64_t size)
{
    LOGI("Create VectorGaugeLinearGradient Vector");
    return new std::vector<VectorColorStops>(size);
}

void FFICJVectorGaugeLinearGradientSetElement(
    VecLinearGradientHandle vec, int64_t index, VectorColorStops vectorColorStops)
{
    LOGI("VectorGaugeLinearGradient Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<VectorColorStops>*>(vec);
    (*actualVec)[index] = vectorColorStops;
    LOGI("VectorGaugeLinearGradient Vector Set Element Success");
}

void FFICJVectorGaugeLinearGradientDelete(VecLinearGradientHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<VectorColorStops>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkGaugeCreate(double gaugeValue, double gaugeMin, double gaugeMax)
{
    if (gaugeMin >= gaugeMax) {
        gaugeMin = NG::DEFAULT_MIN_VALUE;
        gaugeMax = NG::DEFAULT_MAX_VALUE;
    }
    if (gaugeValue < gaugeMin || gaugeValue > gaugeMax) {
        gaugeValue = gaugeMin;
    }
    GetGaugeModel()->Create(gaugeValue, gaugeMin, gaugeMax);
    GetGaugeModel()->SetIsShowLimitValue(true);
}

void FfiOHOSAceFrameworkGaugeSetValue(double value)
{
    GetGaugeModel()->SetValue(value);
}

void FfiOHOSAceFrameworkGaugeSetStartAngle(double startAngle)
{
    GetGaugeModel()->SetStartAngle(startAngle);
}

void FfiOHOSAceFrameworkGaugeSetEndAngle(double endAngle)
{
    GetGaugeModel()->SetEndAngle(endAngle);
}

void SortColorStopOffset(std::vector<NG::ColorStopArray>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}

void FfiOHOSAceFrameworkGaugeSetColors(VectorUInt32Ptr gaugeColors, VectorFloat32Ptr gaugeWeights)
{
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        FfiOHOSAceFrameworkGaugeSetColorsV2(gaugeColors, gaugeWeights);
        return;
    }
    const auto& vecColor = *reinterpret_cast<std::vector<uint32_t>*>(gaugeColors);
    const auto& vecWeight = *reinterpret_cast<std::vector<float>*>(gaugeWeights);
    if (vecColor.size() != vecWeight.size()) {
        LOGE("gauge colors not match weights");
        return;
    }
    std::vector<Color> colors;
    for (size_t i = 0; i < vecColor.size(); ++i) {
        colors.push_back(Color(vecColor[i]));
    }
    GetGaugeModel()->SetColors(colors, vecWeight);
}

void FfiOHOSAceFrameworkGaugeSetColorsV2(VectorUInt32Ptr gaugeColors, VectorFloat32Ptr gaugeWeights)
{
    NG::GaugeType type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    std::vector<NG::ColorStopArray> colors;
    std::vector<float> weights;
    const auto& vecColor = *reinterpret_cast<std::vector<uint32_t>*>(gaugeColors);
    const auto& vecWeight = *reinterpret_cast<std::vector<float>*>(gaugeWeights);
    if (vecColor.size() != vecWeight.size()) {
        LOGE("gauge colors not match weights");
        return;
    }
    if (vecColor.size() <= 0) {
        GetGaugeModel()->ResetGradientColors();
        return;
    }
    if (vecColor.size() > 1) {
        for (size_t i = 0; i < vecColor.size(); ++i) {
            NG::ColorStopArray colorStopArray;
            colorStopArray.emplace_back(std::make_pair(Color(vecColor[i]), Dimension(vecWeight[i], DimensionUnit::VP)));
            colors.emplace_back(colorStopArray);
        }
        GetGaugeModel()->SetGradientColors(colors, weights, type);
        return;
    }
    type = NG::GaugeType::TYPE_CIRCULAR_MONOCHROME;
    NG::ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color(vecColor[0]), Dimension(vecWeight[0], DimensionUnit::VP)));
    colors.emplace_back(colorStopArray);
    GetGaugeModel()->SetGradientColors(colors, weights, type);
}

void FfiOHOSAceFrameworkGaugeResetColors()
{
    GetGaugeModel()->ResetGradientColors();
}

void FfiOHOSAceFrameworkGaugeSetLinearGradientColors(VecLinearGradientHandle linearGradients, VectorUInt32Ptr weight)
{
    NG::GaugeType type = NG::GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    std::vector<NG::ColorStopArray> colors;
    std::vector<float> weights;
    auto vecLinearGradients = *reinterpret_cast<std::vector<VectorColorStops>*>(linearGradients);
    auto vecWeight = *reinterpret_cast<std::vector<float>*>(weight);
    if (vecLinearGradients.size() != vecWeight.size()) {
        LOGE("gauge colors not match weights");
        return;
    }
    if (vecLinearGradients.size() <= 0) {
        GetGaugeModel()->ResetGradientColors();
        return;
    }
    if (vecLinearGradients.size() > 1) {
        for (size_t i = 0; i < vecLinearGradients.size(); i++) {
            if (vecWeight[i] <= 0) {
                continue;
            }
            weights.emplace_back(vecWeight[i]);
            auto vecColorStops = *reinterpret_cast<std::vector<ColorStop>*>(vecLinearGradients[i]);
            if (vecColorStops.size() <= 1) {
                continue;
            }
            NG::ColorStopArray colorStopArray;
            for (size_t j = 0; j < vecColorStops.size(); j++) {
                colorStopArray.emplace_back(std::make_pair(
                    Color(vecColorStops[j].color), Dimension(vecColorStops[j].offset, DimensionUnit::VP)));
            }
            colors.emplace_back(colorStopArray);
        }
        SortColorStopOffset(colors);
        GetGaugeModel()->SetGradientColors(colors, weights, type);
        return;
    }
    type = NG::GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT;
    NG::ColorStopArray colorStopArray;
    auto vecColorStops = *reinterpret_cast<std::vector<ColorStop>*>(vecLinearGradients[0]);
    for (size_t i = 0; i < vecColorStops.size(); i++) {
        colorStopArray.emplace_back(
            std::make_pair(Color(vecColorStops[i].color), Dimension(vecColorStops[i].offset, DimensionUnit::VP)));
    }
    colors.emplace_back(colorStopArray);
    SortColorStopOffset(colors);
    GetGaugeModel()->SetGradientColors(colors, weights, type);
}

void FfiOHOSAceFrameworkGaugeSetShadowOptions(double radius, double offsetX, double offsetY)
{
    NG::GaugeShadowOptions shadowOptions;
    if (radius < 0) {
        radius = NG::DEFAULT_GAUGE_SHADOW_RADIUS;
    }
    if (offsetX < 0) {
        offsetX = NG::DEFAULT_GAUGE_SHADOW_OFFSETX;
    }
    if (offsetY < 0) {
        offsetY = NG::DEFAULT_GAUGE_SHADOW_OFFSETY;
    }
    shadowOptions.radius = radius;
    shadowOptions.offsetX = offsetX;
    shadowOptions.offsetY = offsetY;

    GetGaugeModel()->SetShadowOptions(shadowOptions);
}

void FfiOHOSAceFrameworkGaugeSetStrokeWidth(double strokeWidth, int32_t strokeUnit)
{
    Dimension strokeDimWidth(strokeWidth, static_cast<DimensionUnit>(strokeUnit));
    GetGaugeModel()->SetStrokeWidth(strokeDimWidth);
}

void FfiOHOSAceFrameworkGaugeSetIndicator(const char* icon, double size)
{
    std::string iconPath = icon;
    if (icon == INDICATOR_NULL) {
        GetGaugeModel()->SetIsShowIndicator(false);
        return;
    }
    if (icon == INDICATOR_DEFAULT) {
        GetGaugeModel()->ResetIndicatorIconPath();
    } else {
        std::string bundleName;
        std::string moduleName;
        GetGaugeModel()->SetIndicatorIconPath(iconPath, bundleName, moduleName);
    }

    CalcDimension space;
    if (size < 0) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    } else {
        space = CalcDimension(size, DimensionUnit::VP);
    }
    GetGaugeModel()->SetIndicatorSpace(space);
}

void FfiOHOSAceFrameworkGaugeSetDescription(void (*builder)())
{
    GetGaugeModel()->SetIsShowLimitValue(false);
    GetGaugeModel()->SetIsShowDescription(true);
    // parse builder
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    GetGaugeModel()->SetDescription(customNode);
}

void FfiOHOSAceFrameworkSetPrivacySensitive(bool isprivacySensitiveMode)
{
    ViewAbstractModel::GetInstance()->SetPrivacySensitive(isprivacySensitiveMode);
}
}
