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

#include "bridge/cj_frontend/interfaces/cj_ffi/concurrency/cj_concurrency_ffi.h"

#include "cj_lambda.h"
#include "frameworks/core/common/container.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkPostTaskToMainThread(void(*callback)())
{
    auto currentObj = Container::CurrentSafely();
    if (!currentObj) {
        LOGE("Can not found valid container");
        return;
    }
    auto executor = currentObj->GetTaskExecutor();
    if (!executor) {
        LOGE("can not get executor.");
        return;
    }
    executor->PostTask(
        [task = CJLambda::Create(callback), instanceId = currentObj->GetInstanceId()] {
            ContainerScope scope(instanceId);
            task();
        },
        TaskExecutor::TaskType::UI, "CJSPAWNMAIN");
}

bool FfiOHOSAceFrameworkHasContainer()
{
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGI("Can not get Current Container");
        return false;
    } else {
        return true;
    }
}
}
