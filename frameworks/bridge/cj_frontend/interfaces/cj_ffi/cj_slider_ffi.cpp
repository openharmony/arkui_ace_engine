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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_slider_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL };
/*
 * SliderMode is defined in core/component.
 * SliderModel::SliderMode is defined in core/component_ng.
 * The two enum have the same content, but are defined in different namespaces.
 */
const std::vector<SliderModel::SliderMode> SLIDER_MODES_NG = { SliderModel::SliderMode::OUTSET,
    SliderModel::SliderMode::INSET, SliderModel::SliderMode::NONE };

} // namespace

extern "C" {
void FfiOHOSAceFrameworkSliderCreate(CJSliderCreate value)
{
    if (!Utils::CheckParamsValid(value.style, SLIDER_MODES_NG.size())) {
        LOGE("invalid value for slider style");
        return;
    }
    if (!Utils::CheckParamsValid(value.direction, AXIS.size())) {
        LOGE("invalid value for slider direction");
        return;
    }

    SliderModel::GetInstance()->Create(value.value, value.step, value.min, value.max);
    SliderModel::GetInstance()->SetSliderMode(SLIDER_MODES_NG[value.style]);
    SliderModel::GetInstance()->SetDirection(AXIS[value.direction]);
    SliderModel::GetInstance()->SetReverse(value.reverse);
}

void FfiOHOSAceFrameworkSliderBlockColor(uint32_t color)
{
    SliderModel::GetInstance()->SetBlockColor(Color(color));
}

void FfiOHOSAceFrameworkSliderTrackColor(uint32_t color)
{
    NG::Gradient gradient;
    NG::GradientColor gradientColorBegin;
    gradientColorBegin.SetLinearColor(LinearColor(Color(color)));
    gradientColorBegin.SetDimension(Dimension(0.0f));
    gradient.AddColor(gradientColorBegin);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(Color(color)));
    gradientColorEnd.SetDimension(Dimension(1.0f));
    gradient.AddColor(gradientColorEnd);
    SliderModel::GetInstance()->SetTrackBackgroundColor(gradient, true);
}

void FfiOHOSAceFrameworkSliderSelectedColor(uint32_t color)
{
    SliderModel::GetInstance()->SetSelectColor(Color(color));
}

void FfiOHOSAceFrameworkSliderShowSteps(bool isShow)
{
    SliderModel::GetInstance()->SetShowSteps(isShow);
}

void FfiOHOSAceFrameworkSliderShowTips(bool isShow)
{
    std::optional<std::string> none;
    SliderModel::GetInstance()->SetShowTips(isShow, none);
}

void FfiOHOSAceFrameworkSliderShowTipsNew(bool isShow, const char* content, bool contentExist)
{
    std::optional<std::string> value;
    if (contentExist) {
        value = std::string(content);
    } else {
        value = std::nullopt;
    }
    SliderModel::GetInstance()->SetShowTips(isShow, value);
}

void FfiOHOSAceFrameworkSliderTrackThickness(double value, int32_t unit)
{
    Dimension width(value, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value, 0.0)) {
        return;
    }
    SliderModel::GetInstance()->SetThickness(width);
}

void FfiOHOSAceFrameworkSliderMaxLabel(double value)
{
    SliderModel::GetInstance()->SetMaxLabel(value);
}

void FfiOHOSAceFrameworkSliderMinLabel(double value)
{
    SliderModel::GetInstance()->SetMinLabel(value);
}

void FfiOHOSAceFrameworkSliderOnChange(void (*callback)(double value, int32_t mode))
{
    SliderModel::GetInstance()->SetOnChange(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkSliderBlockBorderColor(uint32_t color)
{
    SliderModel::GetInstance()->SetBlockBorderColor(Color(color));
}

void FfiOHOSAceFrameworkSliderBlockBorderWidth(double value, int32_t unit)
{
    Dimension blockBorderWidth(value, static_cast<DimensionUnit>(unit));
    SliderModel::GetInstance()->SetBlockBorderWidth(blockBorderWidth);
}

void FfiOHOSAceFrameworkSliderBlockSize(double widthVal, int32_t widthUnit, double heightVal, int32_t heightUnit)
{
    Dimension width(widthVal, static_cast<DimensionUnit>(widthUnit));
    Dimension height(heightVal, static_cast<DimensionUnit>(heightUnit));
    SliderModel::GetInstance()->SetBlockSize(width, height);
}

void FfiOHOSAceFrameworkSliderMinResponsiveDistance(float value)
{
    SliderModel::GetInstance()->SetMinResponsiveDistance(value);
}

void FfiOHOSAceFrameworkSliderSelectedBorderRadius(double value, int32_t unit)
{
    Dimension selectedBorderRadius(value, static_cast<DimensionUnit>(unit));
    SliderModel::GetInstance()->SetSelectedBorderRadius(selectedBorderRadius);
}

void FfiOHOSAceFrameworkSliderInteractionMode(int32_t value)
{
    SliderModel::GetInstance()->SetSliderInteractionMode(static_cast<SliderModel::SliderInteraction>(value));
}

void FfiOHOSAceFrameworkSliderSlideRange(float from, float to, bool fromExist, bool toExist)
{
    if (!fromExist && !toExist) {
        SliderModel::GetInstance()->ResetValidSlideRange();
        return;
    }
    float fromValue = fromExist ? from : std::numeric_limits<float>::infinity();
    float toValue = toExist ? to : std::numeric_limits<float>::infinity();
    SliderModel::GetInstance()->SetValidSlideRange(fromValue, toValue);
}

void FfiOHOSAceFrameworkSliderStepColor(uint32_t color)
{
    SliderModel::GetInstance()->SetStepColor(Color(color));
}

void FfiOHOSAceFrameworkSliderStepSize(double value, int32_t unit)
{
    double stepSizeValue = value < 0 ? 4 : value;
    Dimension stepSize(stepSizeValue, static_cast<DimensionUnit>(unit));
    SliderModel::GetInstance()->SetStepSize(stepSize);
}

void FfiOHOSAceFrameworkSliderTrackBorderRadius(double value, int32_t unit)
{
    Dimension trackBorderRadius(value, static_cast<DimensionUnit>(unit));
    SliderModel::GetInstance()->SetTrackBorderRadius(trackBorderRadius);
}

void FfiOHOSAceFrameworkSliderContentModifier() {}

void FfiOHOSAceFrameworkSliderBlockStyle(int32_t type, const char* image, int64_t shapeId)
{
    auto blockType = static_cast<SliderModel::BlockStyleType>(type);
    if (blockType == SliderModel::BlockStyleType::IMAGE) {
        std::string src(image);
        std::string bundleName;
        std::string moduleName;
        SliderModel::GetInstance()->SetBlockImage(src, bundleName, moduleName);
    } else if (blockType == SliderModel::BlockStyleType::SHAPE) {
        auto context = OHOS::FFI::FFIData::GetData<NativeShapeAbstract>(shapeId);
        if (context != nullptr) {
            SliderModel::GetInstance()->SetBlockShape(context->GetBasicShape());
        } else {
            LOGI("set BlockShape error, Cannot get NativeShape by id: %{public}" PRId64, shapeId);
        }
    }
    SliderModel::GetInstance()->SetBlockType(blockType);
}
}
