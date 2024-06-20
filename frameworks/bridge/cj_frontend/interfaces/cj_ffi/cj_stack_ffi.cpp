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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_stack_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::array<Alignment, 9> ALIGNMENT_ARR {Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };
const std::vector<StackFit> STACK_FITS = {
    StackFit::KEEP,
    StackFit::STRETCH,
    StackFit::INHERIT,
    StackFit::FIRST_CHILD
};
const std::vector<Overflow> OVERFLOWS = {
    Overflow::CLIP,
    Overflow::OBSERVABLE,
    Overflow::SCROLL,
    Overflow::FORCE_CLIP
};
} // namespace

extern "C" {
void FfiOHOSAceFrameworkStackCreate(int32_t value)
{
    if (!Utils::CheckParamsValid(value, ALIGNMENT_ARR.size())) {
        LOGE("invalid value for overflow");
        return;
    }
    StackModel::GetInstance()->Create(ALIGNMENT_ARR[value]);
}

void FfiOHOSAceFrameworkStackSetOverflow(int32_t value)
{
    if (!Utils::CheckParamsValid(value, OVERFLOWS.size())) {
        LOGE("invalid value for overflow");
        return;
    }
    StackModel::GetInstance()->SetOverflow(OVERFLOWS[value]);
}

void FfiOHOSAceFrameworkStackSetStackFit(int32_t value)
{
    if (!Utils::CheckParamsValid(value, STACK_FITS.size())) {
        LOGE("invalid value for stack fit");
        return;
    }
    StackModel::GetInstance()->SetStackFit(STACK_FITS[value]);
}

void FfiOHOSAceFrameworkStackSetAlignment(int32_t value)
{
    if (!Utils::CheckParamsValid(value, ALIGNMENT_ARR.size())) {
        LOGE("invalid value for stack fit");
        return;
    }
    StackModel::GetInstance()->SetAlignment(ALIGNMENT_ARR[value]);
}

void FfiOHOSAceFrameworkStackSetWidth(double value, int32_t unit)
{
    Dimension width(value, static_cast<DimensionUnit>(unit));

    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
    StackModel::GetInstance()->SetHasHeight();
}

void FfiOHOSAceFrameworkStackSetHeight(double value, int32_t unit)
{
    Dimension height(value, static_cast<DimensionUnit>(unit));

    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
    StackModel::GetInstance()->SetHasHeight();
}

void FfiOHOSAceFrameworkStackSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));

    if (LessNotEqual(widthDime.Value(), 0.0)) {
        widthDime.SetValue(0.0);
    }
    if (LessNotEqual(heightDime.Value(), 0.0)) {
        heightDime.SetValue(0.0);
    }
    NG::ViewAbstract::SetWidth(NG::CalcLength(widthDime));
    NG::ViewAbstract::SetHeight(NG::CalcLength(heightDime));
    StackModel::GetInstance()->SetHasHeight();
    StackModel::GetInstance()->SetHasHeight();
}
}
