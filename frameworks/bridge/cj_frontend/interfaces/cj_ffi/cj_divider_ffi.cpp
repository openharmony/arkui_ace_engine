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
#include "core/components_ng/pattern/divider/divider_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<LineCap> LINECAP = { LineCap::BUTT, LineCap::ROUND, LineCap::SQUARE };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkDividerCreate()
{
    DividerModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkDividerSetVertical(bool isVertical)
{
    DividerModel::GetInstance()->Vertical(isVertical);
}

void FfiOHOSAceFrameworkDividerSetLineCap(int32_t style)
{
    if (!Utils::CheckParamsValid(style, LINECAP.size())) {
        LOGE("invalid value for image repeat");
        return;
    }

    DividerModel::GetInstance()->LineCap(LINECAP[style]);
}

void FfiOHOSAceFrameworkDividerSetStrokeWidth(double width, int32_t unit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(unit));

    DividerModel::GetInstance()->StrokeWidth(widthDime);
}

void FfiOHOSAceFrameworkDividerSetDividerColor(uint32_t color)
{
    DividerModel::GetInstance()->DividerColor(Color(color));
}
}
