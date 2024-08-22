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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_data_panel_ffi.h"


#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components/chart/chart_component.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
    const std::vector<ChartType> DataPanel_TYPE = { ChartType::LINE, ChartType::RAINBOW};
    constexpr unsigned int MAX_VALUES_LENGTH = 9;
    constexpr double DEFAULT_STROKE_WIDTH = 24.0;
}

extern "C" {
VectorNativeLinearGradientHandle FFICJCreateVectorNativeLinearGradient(int64_t size)
{
    LOGI("Create NativeLinearGradient Vector");
    return new std::vector<NativeLinearGradient>(size);
}

void FFICJVectorNativeLinearGradientSetElement(
    VectorNativeLinearGradientHandle vec, int64_t index, NativeLinearGradient linearGradient)
{
    LOGI("NativeLinearGradient Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeLinearGradient>*>(vec);
    (*actualVec)[index] = linearGradient;
    LOGI("NativeLinearGradient Vector Set Element Success");
}

void FFICJVectorNativeLinearGradientDelete(VectorNativeLinearGradientHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeLinearGradient>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkDataPanelCreate(VectorDoubleHandle values, double max, int32_t panelType)
{
    if (!Utils::CheckParamsValid(panelType, DataPanel_TYPE.size())) {
        LOGE("invalid value for data_panel type");
        return;
    }
    std::vector<double>* pValues = (std::vector<double>*)values;
    std::vector<double> dateValues;
    unsigned int length = pValues->size() > MAX_VALUES_LENGTH ? MAX_VALUES_LENGTH : pValues->size();
    double dataSum = 0.0;
    double maxValue = max;
    for (unsigned int i = 0; i < length; ++i) {
        auto value = pValues->at(i);
        if (value <= 0.0) {
            value = 0.0;
        }
        dataSum += value;
        if ((dataSum >= maxValue) && maxValue > 0) {
            value = maxValue - (dataSum - value);
            if (value <= 0.0) {
                break;
            }
        }
        dateValues.push_back(value);
    }
    if (maxValue <= 0.0) {
        maxValue = dataSum;
    }

    DataPanelModel::GetInstance()->Create(dateValues, maxValue, panelType);
}

void FfiOHOSAceFrameworkDataPanelSetCloseEffect(bool isCloseEffect)
{
    DataPanelModel::GetInstance()->SetEffect(isCloseEffect);
}

void FfiOHOSAceFrameworkDataPanelSetValueColors(VectorStringPtr vecContent)
{
    auto nativeLinearGradientVec = *reinterpret_cast<std::vector<NativeLinearGradient>*>(vecContent);

    std::vector<OHOS::Ace::NG::Gradient> valueColors;

    for (size_t i = 0; i < nativeLinearGradientVec.size(); i++) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;

        gradientColorStart.SetLinearColor(LinearColor(nativeLinearGradientVec[i].firstColor));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;

        gradientColorEnd.SetLinearColor(LinearColor(nativeLinearGradientVec[i].secondColor));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        valueColors.emplace_back(gradient);
    }

    DataPanelModel::GetInstance()->SetValueColors(valueColors);
}

void FfiOHOSAceFrameworkDataPanelSetTrackBackgroundColor(uint32_t color)
{
    DataPanelModel::GetInstance()->SetTrackBackground(Color(color));
}

void FfiOHOSAceFrameworkDataPanelSetStrokeWidth(double strokeWidth, int32_t widthUnit)
{
    if (strokeWidth < 0.0) {
        strokeWidth = DEFAULT_STROKE_WIDTH;
    }
    Dimension dimStrokeWidth(strokeWidth, static_cast<DimensionUnit>(widthUnit));
    DataPanelModel::GetInstance()->SetStrokeWidth(dimStrokeWidth);
}

void FfiOHOSAceFrameworkDataPanelSetTrackShadow(NativeDataPanelShadow nativeDataPanelShadow)
{
    auto nativeLinearGradientVec = *reinterpret_cast<std::vector<NativeLinearGradient>*>(nativeDataPanelShadow.colors);

    std::vector<OHOS::Ace::NG::Gradient> valueColors;
    for (size_t i = 0; i < nativeLinearGradientVec.size(); i++) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;

        gradientColorStart.SetLinearColor(LinearColor(nativeLinearGradientVec[i].firstColor));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;

        gradientColorEnd.SetLinearColor(LinearColor(nativeLinearGradientVec[i].secondColor));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        valueColors.emplace_back(gradient);
    }
    OHOS::Ace::NG::DataPanelShadow shadow;
    shadow.radius = nativeDataPanelShadow.radius;
    shadow.offsetX = nativeDataPanelShadow.offsetX;
    shadow.offsetY = nativeDataPanelShadow.offsetY;
    shadow.colors = valueColors;
    DataPanelModel::GetInstance()->SetShadowOption(shadow);
}
}
