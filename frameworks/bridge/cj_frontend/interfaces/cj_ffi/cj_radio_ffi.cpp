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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_radio_ffi.h"

#include "cj_lambda.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

using namespace OHOS::Ace;

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::RadioModelNG* GetRadioModel()
{
    static NG::RadioModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Radio");
        if (module  == nullptr) {
            LOGF("Can't find radio dynamic module");
            abort();
        }
        model = reinterpret_cast<NG::RadioModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkRadioCreate(const char* group, const char* value)
{
    std::optional<int32_t> indicator;
    GetRadioModel()->Create(std::optional<std::string>(value), std::optional<std::string>(group), indicator);
}

void FfiOHOSAceFrameworkRadioWithIndicatorCreate(
    const char* group, const char* value, int32_t indicatorType, void (*indicatorBuilder)())
{
    std::optional<int32_t> indicator(indicatorType);
    GetRadioModel()->Create(std::optional<std::string>(value), std::optional<std::string>(group), indicator);
    GetRadioModel()->SetBuilder(CJLambda::Create(indicatorBuilder));
}

void FfiOHOSAceFrameworkRadioChecked(bool value)
{
    GetRadioModel()->SetChecked(value);
}

void FfiOHOSAceFrameworkRadioSetStyle(
    uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor)
{
    GetRadioModel()->SetCheckedBackgroundColor(Color(checkedBackgroundColor));
    GetRadioModel()->SetUncheckedBorderColor(Color(uncheckedBorderColor));
    GetRadioModel()->SetIndicatorColor(Color(indicatorColor));
}

void FfiOHOSAceFrameworkRadioSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthValue(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightValue(height, static_cast<DimensionUnit>(heightUnit));
    ViewAbstractModel::GetInstance()->SetWidth(widthValue);
    ViewAbstractModel::GetInstance()->SetHeight(heightValue);
}

void FfiOHOSAceFrameworkRadioSetPaddings(CJEdge params)
{
    NG::PaddingPropertyF oldPaddings({ 0.0f, 0.0f, 0.0f, 0.0f });
    NG::PaddingProperty paddings;
    paddings.top = NG::CalcLength(Dimension(params.top, static_cast<DimensionUnit>(params.topUnit)));
    paddings.right = NG::CalcLength(Dimension(params.right, static_cast<DimensionUnit>(params.rightUnit)));
    paddings.bottom = NG::CalcLength(Dimension(params.bottom, static_cast<DimensionUnit>(params.bottomUnit)));
    paddings.left = NG::CalcLength(Dimension(params.left, static_cast<DimensionUnit>(params.leftUnit)));
    GetRadioModel()->SetPadding(oldPaddings, paddings);
}

void FfiOHOSAceFrameworkRadioSetPadding(double padding, uint32_t unit)
{
    Dimension value(padding, static_cast<DimensionUnit>(unit));
    NG::ViewAbstract::SetPadding(NG::CalcLength(value));
}

void FfiOHOSAceFrameworkRadioSetHoverEffect(int32_t value)
{
    GetRadioModel()->SetHoverEffect(static_cast<HoverEffectType>(value));
}

void FfiOHOSAceFrameworkRadioOnChange(void (*callback)(bool isChecked))
{
    GetRadioModel()->SetOnChange(CJLambda::Create(callback));
}

void FfiRadioSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    GetRadioModel()->SetResponseRegion(result);
}

void FfiRadioSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    GetRadioModel()->SetResponseRegion(result);
}
}
