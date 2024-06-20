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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_item_ffi.h"

#include "core/components_ng/pattern/grid/grid_item_model.h"

using namespace OHOS::Ace;

extern "C" {
void FfiOHOSAceFrameworkGridItemCreate()
{
    NG::GridItemStyle style {};
    GridItemModel::GetInstance()->Create(style);
}

void FfiOHOSAceFrameworkGridItemSetColumnStart(int32_t columnStart)
{
    GridItemModel::GetInstance()->SetColumnStart(columnStart);
}

void FfiOHOSAceFrameworkGridItemSetColumnEnd(int32_t columnEnd)
{
    GridItemModel::GetInstance()->SetColumnEnd(columnEnd);
}

void FfiOHOSAceFrameworkGridItemSetRowStart(int32_t rowStart)
{
    GridItemModel::GetInstance()->SetRowStart(rowStart);
}

void FfiOHOSAceFrameworkGridItemSetRowEnd(int32_t rowEnd)
{
    GridItemModel::GetInstance()->SetRowEnd(rowEnd);
}

void FfiOHOSAceFrameworkGridItemForceRebuild(bool forceRebuild)
{
    GridItemModel::GetInstance()->SetForceRebuild(forceRebuild);
}
}
