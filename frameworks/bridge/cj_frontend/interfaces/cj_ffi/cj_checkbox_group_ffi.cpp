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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_checkbox_group_ffi.h"


#include "cj_lambda.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
std::function<void(const BaseEventInfo* info)> FormatOnChangeFunction(void (*callback)(FFiCheckboxGroupResult info))
{
    std::function<void(const BaseEventInfo* info)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const BaseEventInfo* info) -> void {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        FFiCheckboxGroupResult ffiInfo {};

        std::vector<std::string> nameList = eventInfo->GetNameList();
        std::vector<const char*> arr;
        auto size = nameList.size();
        arr.resize(size);
        for (size_t i = 0; i < size; ++i) {
            arr[i] = nameList[i].c_str();
        }

        ffiInfo.status = eventInfo->GetStatus();
        ffiInfo.size = static_cast<int64_t>(size);
        ffiInfo.nameBuffer = arr.data();

        ffiOnAction(ffiInfo);
    };
    return result;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkCheckBoxGroupCreate(const char* name)
{
    auto checkboxGroupName = std::optional<std::string>(name);
    CheckBoxGroupModel::GetInstance()->Create(checkboxGroupName);
}

void FfiOHOSAceFrameworkCheckBoxGroupSelectAll(bool value)
{
    CheckBoxGroupModel::GetInstance()->SetSelectAll(value);
}

void FfiOHOSAceFrameworkCheckBoxGroupSetSelectedColor(uint32_t color)
{
    CheckBoxGroupModel::GetInstance()->SetSelectedColor(Color(color));
}

void FfiOHOSAceFrameworkCheckBoxGroupSetWidth(double width, uint32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));

    NG::ViewAbstract::SetWidth(NG::CalcLength(value));
}

void FfiOHOSAceFrameworkCheckBoxGroupSetHeight(double height, uint32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));

    NG::ViewAbstract::SetHeight(NG::CalcLength(value));
}

void FfiOHOSAceFrameworkCheckBoxGroupSetSize(double width, uint32_t widthUnit, double height, uint32_t heightUnit)
{
    FfiOHOSAceFrameworkCheckBoxGroupSetWidth(width, widthUnit);
    FfiOHOSAceFrameworkCheckBoxGroupSetHeight(height, heightUnit);
}

void FfiOHOSAceFrameworkCheckBoxGroupSetPadding(double padding, uint32_t unit)
{
    Dimension value(padding, static_cast<DimensionUnit>(unit));

    NG::ViewAbstract::SetPadding(NG::CalcLength(value));
}

void FfiOHOSAceFrameworkCheckBoxGroupSetPaddings(CJEdge params)
{
    Dimension top(params.top, static_cast<DimensionUnit>(params.topUnit));
    Dimension right(params.right, static_cast<DimensionUnit>(params.rightUnit));
    Dimension bottom(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    Dimension left(params.left, static_cast<DimensionUnit>(params.leftUnit));

    NG::PaddingProperty padding;
    padding.top = NG::CalcLength(top);
    padding.right = NG::CalcLength(right);
    padding.bottom = NG::CalcLength(bottom);
    padding.left = NG::CalcLength(left);

    NG::ViewAbstract::SetPadding(padding);
}

void FfiOHOSAceFrameworkCheckBoxGroupSetOnChange(void (*callback)(FFiCheckboxGroupResult info))
{
    CheckBoxGroupModel::GetInstance()->SetOnChange(FormatOnChangeFunction(callback));
}

void FfiCheckBoxGroupSetResponseRegion(CJResponseRegion value)
{
    std::vector<DimensionRect> result;
    ParseCJResponseRegion(value, result);
    CheckBoxGroupModel::GetInstance()->SetResponseRegion(result);
}

void FfiCheckBoxGroupSetResponseRegionArray(VectorStringPtr vecContent)
{
    std::vector<DimensionRect> result;
    ParseVectorStringPtr(vecContent, result);
    CheckBoxGroupModel::GetInstance()->SetResponseRegion(result);
}
}
