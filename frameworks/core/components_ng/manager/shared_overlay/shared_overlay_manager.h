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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_OVERLAY_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/animation/animator.h"
#include "core/components_ng/manager/shared_overlay/shared_transition_effect.h"

namespace OHOS::Ace::NG {
class FrameNode;

// SharedOverlayManager is for root render node to perform shared transition.
class ACE_EXPORT SharedOverlayManager : public AceType {
    DECLARE_ACE_TYPE(SharedOverlayManager, AceType);

public:
    explicit SharedOverlayManager(const RefPtr<FrameNode>& sharedManager) : sharedManager_(sharedManager) {};
    ~SharedOverlayManager() override = default;

    void StartSharedTransition(const RefPtr<FrameNode>& pageSrc, const RefPtr<FrameNode>& pageDest);
    void StopSharedTransition();
    bool OnBackPressed();

private:
    void PrepareSharedTransition(const RefPtr<FrameNode>& pageSrc, const RefPtr<FrameNode>& pageDest);
    void ClearAllEffects();
    void CheckAndPrepareTransition(std::list<RefPtr<SharedTransitionEffect>>& effects,
        std::list<RefPtr<SharedTransitionEffect>>& effectiveEffects);
    bool PrepareEachTransition(const RefPtr<SharedTransitionEffect>& effect);
    bool CheckIn(const RefPtr<SharedTransitionEffect>& effect);
    bool AboardShuttle(const RefPtr<SharedTransitionEffect>& effect);
    void GetOffShuttle(const RefPtr<SharedTransitionEffect>& effect);
    void PassengerAboard(const RefPtr<SharedTransitionEffect>& effect, const RefPtr<FrameNode>& passenger);

    RefPtr<FrameNode> sharedManager_;
    OffsetF pageOffset_;
    std::list<RefPtr<SharedTransitionEffect>> effects_;

    ACE_DISALLOW_COPY_AND_MOVE(SharedOverlayManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_OVERLAY_MANAGER_H
