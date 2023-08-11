/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/animator/animator_model_ng.h"

namespace OHOS::Ace::Framework {
void AnimatorModelNG::AddEventListener(
    std::function<void()>&& callback, EventOperation operation, const std::string& animatorId)
{
    auto animatorInfo = GetAnimatorInfo(animatorId);
    CHECK_NULL_VOID(animatorInfo);
    auto animator = animatorInfo->GetAnimator();
    CHECK_NULL_VOID(animator);
    switch (operation) {
        case EventOperation::START:
            animator->ClearStartListeners();
            if (callback) {
                animator->AddStartListener(callback);
            }
            break;
        case EventOperation::PAUSE:
            animator->ClearPauseListeners();
            if (callback) {
                animator->AddPauseListener(callback);
            }
            break;
        case EventOperation::REPEAT:
            animator->ClearRepeatListeners();
            if (callback) {
                animator->AddRepeatListener(callback);
            }
            break;
        case EventOperation::CANCEL:
            animator->ClearIdleListeners();
            if (callback) {
                animator->AddIdleListener(callback);
            }
            break;
        case EventOperation::FINISH:
            animator->ClearStopListeners();
            if (callback) {
                animator->AddStopListener(callback);
            }
            break;
        case EventOperation::NONE:
        default:
            break;
    }
}
} // namespace OHOS::Ace::Framework