/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_CONTROLLER_H
#include "base/memory/ace_type.h"
namespace OHOS::Ace::V2 {
enum class PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2,
};
using ErrorImpl = std::function<void(bool)>;
using ResetImpl = std::function<void()>;
using SetChallengeResultImpl = std::function<void(PatternLockChallengeResult)>;

class PatternLockController : public virtual AceType {
    DECLARE_ACE_TYPE(PatternLockController, AceType);

public:
    void Reset()
    {
        if (resetImpl_) {
            resetImpl_();
        }
    }
    void SetResetImpl(const ResetImpl& resetImpl)
    {
        resetImpl_ = resetImpl;
    }
    void SetChallengeResult(PatternLockChallengeResult challengeResult)
    {
        if (setChallengeResultImpl_) {
            setChallengeResultImpl_(challengeResult);
        }
    }
    void SetChallengeResultImpl(const SetChallengeResultImpl& setChallengeResultImpl)
    {
        setChallengeResultImpl_ = setChallengeResultImpl;
    }

private:
    V2::ResetImpl resetImpl_;
    V2::SetChallengeResultImpl setChallengeResultImpl_;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_CONTROLLER_H
