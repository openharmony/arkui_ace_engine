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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_divider_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
NG::DividerModelNG* GetDividerModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Divider");
    CHECK_NULL_RETURN(module, nullptr);
    return static_cast<NG::DividerModelNG*>(module->GetModel());
}
} // namespace OHOS::Ace
namespace {
const std::vector<LineCap> LINECAP = { LineCap::BUTT, LineCap::ROUND, LineCap::SQUARE };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkDividerCreate()
{
    GetDividerModel()->Create();
}

void FfiOHOSAceFrameworkDividerSetVertical(bool isVertical)
{
    GetDividerModel()->Vertical(isVertical);
}

void FfiOHOSAceFrameworkDividerSetLineCap(int32_t style)
{
    if (!Utils::CheckParamsValid(style, LINECAP.size())) {
        LOGE("invalid value for image repeat");
        return;
    }

    GetDividerModel()->LineCap(LINECAP[style]);
}

void FfiOHOSAceFrameworkDividerSetStrokeWidth(double width, int32_t unit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(unit));
    GetDividerModel()->StrokeWidth(widthDime);
}

void FfiOHOSAceFrameworkDividerSetDividerColor(uint32_t color)
{
    GetDividerModel()->DividerColor(Color(color));
}
}
