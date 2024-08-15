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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_column_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/flex/flex_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FlexAlign> FLEX_ALIGNS = {
    FlexAlign::AUTO,
    FlexAlign::FLEX_START,
    FlexAlign::CENTER,
    FlexAlign::FLEX_END,
    FlexAlign::SPACE_BETWEEN,
    FlexAlign::SPACE_AROUND,
    FlexAlign::SPACE_EVENLY
};
} // namespace

extern "C" {
void FfiOHOSAceFrameworkColumnCreate()
{
    ColumnModel::GetInstance()->CreateWithWrap();
}

void FfiOHOSAceFrameworkColumnCreateWithSpace(double space, int32_t unit)
{
    Dimension value(space, static_cast<DimensionUnit>(unit));
    ColumnModel::GetInstance()->Create(value, nullptr, "");
}

void FfiOHOSAceFrameworkColumnSetAlignItems(int32_t alignItems)
{
    if (!Utils::CheckParamsValid(alignItems, FLEX_ALIGNS.size())) {
        LOGE("invalid value for align item");
        return;
    }
    ColumnModel::GetInstance()->SetAlignItems(FLEX_ALIGNS[alignItems]);
}

void FfiOHOSAceFrameworkColumnSetJustifyContent(int32_t justifyContent)
{
    if (!Utils::CheckParamsValid(justifyContent, FLEX_ALIGNS.size())) {
        LOGE("invalid value for justifyContent");
        return;
    }
    ColumnModel::GetInstance()->SetJustifyContent(FLEX_ALIGNS[justifyContent]);
}

void FfiOHOSAceFrameworkColumnSetHeight(double height, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetHeight(height, unit);
    FlexModel::GetInstance()->SetHasHeight();
}

void FfiOHOSAceFrameworkColumnSetWidth(double width, int32_t unit)
{
    FfiOHOSAceFrameworkViewAbstractSetWidth(width, unit);
    FlexModel::GetInstance()->SetHasWidth();
}
}
