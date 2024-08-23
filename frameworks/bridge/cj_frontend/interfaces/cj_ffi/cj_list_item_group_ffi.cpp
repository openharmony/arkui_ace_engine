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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_list_item_group_ffi.h"

#include "cj_lambda.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkListItemGroupCreate(
    void (*headerBuilder)(), void (*footerBuilder)(), double space, int32_t spaceUnit)
{
    Dimension spaceDime(space, static_cast<DimensionUnit>(spaceUnit));

    V2::ListItemGroupStyle style {};
    ListItemGroupModel::GetInstance()->Create(style);
    ListItemGroupModel::GetInstance()->SetSpace(spaceDime);
    ListItemGroupModel::GetInstance()->SetHeader(CJLambda::Create(headerBuilder));
    ListItemGroupModel::GetInstance()->SetFooter(CJLambda::Create(footerBuilder));
}

void FfiOHOSAceFrameworkListItemGroupSetDivider(DividerParams& params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension startMarginDime(params.startMargin, static_cast<DimensionUnit>(params.startMarginUnit));
    Dimension endMarginDime(params.endMargin, static_cast<DimensionUnit>(params.endMarginUnit));

    V2::ItemDivider divider;
    divider.strokeWidth = widthDime;
    divider.color = Color(params.color);
    divider.startMargin = startMarginDime;
    divider.endMargin = endMarginDime;

    ListItemGroupModel::GetInstance()->SetDivider(divider);
}
}
