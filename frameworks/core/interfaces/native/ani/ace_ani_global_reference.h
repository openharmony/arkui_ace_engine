/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ACE_ANI_GLOBAL_REFERENCE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ACE_ANI_GLOBAL_REFERENCE_H

#include "ani.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"

namespace OHOS::Ace::NG {
// class for holding and releasing a global reference of ani.
class AceAniGlobalReference : public AceType {
    DECLARE_ACE_TYPE(AceAniGlobalReference, AceType);

public:
    AceAniGlobalReference(ani_env* env, ani_ref ref) : env_(env), ref_(nullptr)
    {
        if (env_) {
            env_->GlobalReference_Create(ref, &ref_);
        }
    }
    ~AceAniGlobalReference() override
    {
        if (env_ && ref_) {
            env_->GlobalReference_Delete(ref_);
            ref_ = nullptr;
        }
    }
    ani_ref GetValue() const
    {
        return ref_;
    }

private:
    ani_env* env_;
    ani_ref ref_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ACE_ANI_GLOBAL_REFERENCE_H
