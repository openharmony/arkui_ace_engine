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
#include "core/components_ng/pattern/slider/slider_model.h"

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
    SliderModel::SliderMode::INSET };

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
    SliderModel::GetInstance()->SetTrackBackgroundColor(Color(color));
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
}
