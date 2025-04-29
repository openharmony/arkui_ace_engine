/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace_kit/include/ui/base/lifecycle_checkable.h"

#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/referenced.h"

namespace OHOS::Ace {

void LifeCycleCheckable::OnDetectedObjDestroyInUse()
{
    if (SystemProperties::DetectObjDestroyInUse()) {
        LOGF_ABORT("this object is still in use by %{public}p@%{public}p, use_count=%{public}d",
            lastStack_ ? *(void**)lastStack_.load() : nullptr, lastStack_.load(), usingCount_.load());
    }
}

void Referenced::OnDetectedClaimDeathObj(bool isNewOrRecycle)
{
    if (SystemProperties::DetectClaimDeathObj()) {
        LOGF_ABORT("invalid claim: refCount=%{public}d, isNewOrRecycle=%{public}d", RefCount(), isNewOrRecycle);
    }
}

} // namespace OHOS::Ace
