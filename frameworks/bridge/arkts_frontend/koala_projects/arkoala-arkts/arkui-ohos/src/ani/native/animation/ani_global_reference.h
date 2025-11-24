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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_GLOBAL_REFERENCE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_GLOBAL_REFERENCE_H

#include <memory>

#include "ani.h"
#include "log/log.h"

namespace OHOS::Ace::Ani {
// class for holding and releasing a global reference of ani.
class AniGlobalReference : public std::enable_shared_from_this<AniGlobalReference> {
public:
    AniGlobalReference(const AniGlobalReference&) = delete;
    AniGlobalReference(AniGlobalReference&&) = delete;
    AniGlobalReference& operator=(const AniGlobalReference&) = delete;
    AniGlobalReference& operator=(AniGlobalReference&&) = delete;
    explicit AniGlobalReference(ani_env* env, ani_ref ref): env_(env)
    {
        if (env_) {
            env_->GlobalReference_Create(ref, &ref_);
        }
    }
    virtual ~AniGlobalReference()
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
    ani_ref ref_ = nullptr;
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_GLOBAL_REFERENCE_H
