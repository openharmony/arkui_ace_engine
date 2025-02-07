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

#include "cj_recycle_ffi.h"

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "frameworks/core/components_ng/pattern/recycle_view/recycle_view_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkRecycleCreate()
{
    if (Container::IsCurrentUseNewPipeline()) {
        RecycleViewModel::GetInstance()->Create();
    }
    return;
}

void FfiOHOSAceFrameworkRecyclePop()
{
    return;
}
}