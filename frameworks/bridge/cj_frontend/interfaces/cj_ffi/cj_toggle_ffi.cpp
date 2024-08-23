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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_toggle_ffi.h"

#include "cj_lambda.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<ToggleType> TOGGOLE_TYPES = { ToggleType::CHECKBOX, ToggleType::SWITCH, ToggleType::BUTTON };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkToggleCreate(int type, bool isOn)
{
    if (!Utils::CheckParamsValid(type, TOGGOLE_TYPES.size())) {
        LOGE("invalid value for toggle type");
        return;
    }
    ToggleModel::GetInstance()->Create(NG::ToggleType(type), isOn);
}

void FfiOHOSAceFrameworkToggleWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetWidth(value);
}

void FfiOHOSAceFrameworkToggleHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetHeight(value);
}

void FfiOHOSAceFrameworkToggleSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));
    ViewAbstractModel::GetInstance()->SetWidth(widthDime);
    ViewAbstractModel::GetInstance()->SetHeight(heightDime);
}

void FfiOHOSAceFrameworkTogglePadding(double left, int32_t leftUnit, double top, int32_t topUnit, double right,
    int32_t rightUnit, double bottom, int32_t bottomUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetPaddings(CJEdge{
        .top = top,
        .topUnit = topUnit,
        .right = right,
        .rightUnit = rightUnit,
        .bottom = bottom,
        .bottomUnit = bottomUnit,
        .left = left,
        .leftUnit = leftUnit
    });
}

void FfiOHOSAceFrameworkToggleSelectedColor(uint32_t color)
{
    ToggleModel::GetInstance()->SetSelectedColor(Color(color));
}

void FfiOHOSAceFrameworkToggleSwitchPointColor(uint32_t color)
{
    ToggleModel::GetInstance()->SetSwitchPointColor(Color(color));
}

void FfiOHOSAceFrameworkToggleOnChange(void (*callback)(bool isOn))
{
    auto lambda = CJLambda::Create(callback);
    auto onChange = [lambda](bool isOn) {
        lambda(isOn);
    };
    ToggleModel::GetInstance()->OnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkTogglePop()
{
    ToggleModel::GetInstance()->Pop();
}

void FfiToggleSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    ToggleModel::GetInstance()->SetResponseRegion(result);
}

void FfiToggleSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    ToggleModel::GetInstance()->SetResponseRegion(result);
}
}
