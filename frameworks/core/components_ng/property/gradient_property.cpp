/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace::NG {

void Gradient::AddColor(const GradientColor& color)
{
    colors_.push_back(color);
}

void Gradient::ClearColors()
{
    colors_.clear();
}

static void GetColorsAndRepeating(std::unique_ptr<JsonValue>& resultJson, const Gradient& gradient)
{
    auto jsonColorArray = JsonUtil::CreateArray(true);
    auto colors = gradient.GetColors();
    for (size_t i = 0; i < colors.size(); ++i) {
        auto temp = JsonUtil::CreateArray(true);
        auto value = std::to_string(colors[i].GetDimension().Value() / 100.0);
        auto color = colors[i].GetColor().ColorToString();
        temp->Put("0", color.c_str());
        temp->Put("1", value.c_str());
        auto index = std::to_string(i);
        jsonColorArray->Put(index.c_str(), temp);
    }
    resultJson->Put("colors", jsonColorArray);
    resultJson->Put("repeating", gradient.GetRepeat() ? "true" : "false");
}

std::unique_ptr<JsonValue> Gradient::LinearGradientToJson() const
{
    auto resultJson = JsonUtil::Create(true);
    if (GradientType::LINEAR != GetType()) {
        return resultJson;
    }
    CHECK_NULL_RETURN(linearGradient_, resultJson);
    if (linearGradient_->angle.has_value()) {
        resultJson->Put("angle", linearGradient_->angle->ToString().c_str());
    }

    auto linearX = linearGradient_->linearX;
    auto linearY = linearGradient_->linearY;
    if (linearX == GradientDirection::LEFT) {
        if (linearY == GradientDirection::TOP) {
            resultJson->Put("direction", "GradientDirection.LeftTop");
        } else if (linearY == GradientDirection::BOTTOM) {
            resultJson->Put("direction", "GradientDirection.LeftBottom");
        } else {
            resultJson->Put("direction", "GradientDirection.Left");
        }
    } else if (linearX == GradientDirection::RIGHT) {
        if (linearY == GradientDirection::TOP) {
            resultJson->Put("direction", "GradientDirection.RightTop");
        } else if (linearY == GradientDirection::BOTTOM) {
            resultJson->Put("direction", "GradientDirection.RightBottom");
        } else {
            resultJson->Put("direction", "GradientDirection.Right");
        }
    } else {
        if (linearY == GradientDirection::TOP) {
            resultJson->Put("direction", "GradientDirection.Top");
        } else if (linearY == GradientDirection::BOTTOM) {
            resultJson->Put("direction", "GradientDirection.Bottom");
        } else {
            resultJson->Put("direction", "GradientDirection.None");
        }
    }
    GetColorsAndRepeating(resultJson, *this);
    return resultJson;
}

std::unique_ptr<JsonValue> Gradient::SweepGradientToJson() const
{
    auto resultJson = JsonUtil::Create(true);

    if (GradientType::SWEEP != GetType()) {
        return resultJson;
    }
    CHECK_NULL_RETURN(sweepGradient_, resultJson);
    auto radialCenterX = sweepGradient_->centerX;
    auto radialCenterY = sweepGradient_->centerY;
    if (radialCenterX && radialCenterY) {
        auto jsPoint = JsonUtil::CreateArray(true);
        jsPoint->Put("0", radialCenterX->ToString().c_str());
        jsPoint->Put("1", radialCenterY->ToString().c_str());
        resultJson->Put("center", jsPoint);
    }

    auto startAngle = sweepGradient_->startAngle;
    auto endAngle = sweepGradient_->endAngle;
    if (startAngle) {
        resultJson->Put("start", startAngle->ToString().c_str());
    }
    if (endAngle) {
        resultJson->Put("end", endAngle->ToString().c_str());
    }

    GetColorsAndRepeating(resultJson, *this);

    return resultJson;
}

std::unique_ptr<JsonValue> Gradient::RadialGradientToJson() const
{
    auto resultJson = JsonUtil::Create(true);
    if (GradientType::RADIAL != GetType()) {
        return resultJson;
    }
    CHECK_NULL_RETURN(radialGradient_, resultJson);

    auto radialCenterX = radialGradient_->radialCenterX;
    auto radialCenterY = radialGradient_->radialCenterY;
    if (radialCenterX && radialCenterY) {
        auto jsPoint = JsonUtil::CreateArray(true);
        jsPoint->Put("0", radialCenterX->ToString().c_str());
        jsPoint->Put("1", radialCenterY->ToString().c_str());
        resultJson->Put("center", jsPoint);
    }

    auto radius = radialGradient_->radialVerticalSize;
    if (radius) {
        resultJson->Put("radius", radius->ToString().c_str());
    }

    GetColorsAndRepeating(resultJson, *this);

    return resultJson;
}

} // namespace OHOS::Ace::NG