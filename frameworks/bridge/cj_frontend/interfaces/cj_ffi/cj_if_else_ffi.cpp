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
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_if_else_ffi.h"


#include "core/common/container.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkIfElseCreate()
{
    IfElseModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkIfElsePop()
{
    IfElseModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameworkIfElseSetBranchId(int32_t value)
{
    std::list<int32_t> removes;
    IfElseModel::GetInstance()->SetBranchId(value, removes);
}

int32_t FfiOHOSAceFrameworkIfElseGetBranchId()
{
    return IfElseModel::GetInstance()->GetBranchId();
}
}
