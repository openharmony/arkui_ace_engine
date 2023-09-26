/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"

#include <vector>

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {

void ExclusiveRecognizer::OnAccepted()
{
    LOGD("the exclusive gesture recognizer has been accepted, active recognizer: %{public}s",
        AceType::TypeName(activeRecognizer_));
    refereeState_ = RefereeState::SUCCEED;
    if (activeRecognizer_) {
        activeRecognizer_->OnAccepted();
    } else {
        LOGW("the active recognizer is null");
    }

    for (const auto& recognizer : recognizers_) {
        if (recognizer && (recognizer != activeRecognizer_)) {
            LOGD("the sub gesture %{public}s is rejected because %{public}s is accepted", AceType::TypeName(recognizer),
                AceType::TypeName(activeRecognizer_));
            if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
                auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
                group->ForceReject();
            } else {
                recognizer->OnRejected();
            }
        }
    }
}

void ExclusiveRecognizer::OnRejected()
{
    refereeState_ = RefereeState::FAIL;
    for (const auto& recognizer : recognizers_) {
        if (!recognizer) {
            continue;
        }
        if (recognizer->GetRefereeState() == RefereeState::FAIL) {
            LOGE("the %{public}s gesture recognizer already failed", AceType::TypeName(recognizer));
        }
        if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            group->ForceReject();
        } else {
            recognizer->OnRejected();
        }
    }
}

void ExclusiveRecognizer::OnPending()
{
    refereeState_ = RefereeState::PENDING;
    if (activeRecognizer_) {
        activeRecognizer_->OnPending();
    }
}

void ExclusiveRecognizer::OnBlocked()
{
    if (disposal_ == GestureDisposal::ACCEPT) {
        refereeState_ = RefereeState::SUCCEED_BLOCKED;
        if (activeRecognizer_) {
            activeRecognizer_->OnBlocked();
        }
        return;
    }
    if (disposal_ == GestureDisposal::PENDING) {
        refereeState_ = RefereeState::PENDING_BLOCKED;
        if (activeRecognizer_) {
            activeRecognizer_->OnBlocked();
        }
    }
}

bool ExclusiveRecognizer::HandleEvent(const TouchEvent& point)
{
    switch (point.type) {
        case TouchType::MOVE:
        case TouchType::DOWN:
        case TouchType::UP:
        case TouchType::CANCEL: {
            if (activeRecognizer_ && activeRecognizer_->CheckTouchId(point.id)) {
                activeRecognizer_->HandleEvent(point);
            } else {
                for (const auto& recognizer : recognizers_) {
                    if (recognizer && recognizer->CheckTouchId(point.id)) {
                        recognizer->HandleEvent(point);
                    }
                }
            }
            break;
        }
        default:
            LOGW("exclusive recognizer received unknown touch type");
            break;
    }

    return true;
}

bool ExclusiveRecognizer::HandleEvent(const AxisEvent& event)
{
    switch (event.action) {
        case AxisAction::BEGIN:
        case AxisAction::UPDATE:
        case AxisAction::END:
        case AxisAction::NONE: {
            if (activeRecognizer_) {
                activeRecognizer_->HandleEvent(event);
            } else {
                for (const auto& recognizer : recognizers_) {
                    if (recognizer) {
                        recognizer->HandleEvent(event);
                    }
                }
            }
            break;
        }
        default:
            LOGW("exclusive recognizer received unknown touch type");
            break;
    }

    return true;
}

bool ExclusiveRecognizer::CheckNeedBlocked(const RefPtr<NGGestureRecognizer>& recognizer)
{
    for (const auto& child : recognizers_) {
        if (child == recognizer) {
            return false;
        }

        if (child && child->GetRefereeState() == RefereeState::PENDING) {
            return true;
        }
    }
    return false;
}

RefPtr<NGGestureRecognizer> ExclusiveRecognizer::UnBlockGesture()
{
    auto iter =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const RefPtr<NGGestureRecognizer>& member) {
            return member && ((member->GetRefereeState() == RefereeState::PENDING_BLOCKED) ||
                                 (member->GetRefereeState() == RefereeState::SUCCEED_BLOCKED));
        });
    if (iter == recognizers_.end()) {
        LOGD("no blocked gesture in recognizers");
        return nullptr;
    }
    return *iter;
}

void ExclusiveRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    CHECK_NULL_VOID(recognizer);

    if (IsRefereeFinished()) {
        LOGW("the exclusiveRecognizer has already finished referee");
        recognizer->OnRejected();
        return;
    }

    switch (disposal) {
        case GestureDisposal::ACCEPT:
            HandleAcceptDisposal(recognizer);
            break;
        case GestureDisposal::PENDING:
            HandlePendingDisposal(recognizer);
            break;
        case GestureDisposal::REJECT:
            HandleRejectDisposal(recognizer);
            break;
        default:
            LOGW("handle known gesture disposal %{public}d", disposal);
            break;
    }
}

void ExclusiveRecognizer::HandleAcceptDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::SUCCEED) {
        return;
    }

    if (CheckNeedBlocked(recognizer)) {
        LOGD("%{public}s recognizer has to be blocked", AceType::TypeName(recognizer));
        recognizer->OnBlocked();
        return;
    }
    activeRecognizer_ = recognizer;
    GroupAdjudicate(Claim(this), GestureDisposal::ACCEPT);
}

void ExclusiveRecognizer::HandlePendingDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::PENDING) {
        return;
    }

    if (CheckNeedBlocked(recognizer)) {
        recognizer->OnBlocked();
        return;
    }
    activeRecognizer_ = recognizer;
    GroupAdjudicate(Claim(this), GestureDisposal::PENDING);
}

void ExclusiveRecognizer::HandleRejectDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::FAIL) {
        return;
    }

    auto prevState = recognizer->GetRefereeState();
    recognizer->OnRejected();
    if ((prevState == RefereeState::PENDING) && (refereeState_ == RefereeState::PENDING)) {
        auto newBlockRecognizer = UnBlockGesture();
        if (!newBlockRecognizer) {
            // ask parent or global referee to unlock pending.
            GroupAdjudicate(Claim(this), GestureDisposal::REJECT);
            return;
        }
        activeRecognizer_ = newBlockRecognizer;
        if (newBlockRecognizer->GetRefereeState() == RefereeState::PENDING_BLOCKED) {
            // current exclusive recognizer is pending, no need to ask referee again.
            newBlockRecognizer->OnPending();
            return;
        }
        if (newBlockRecognizer->GetRefereeState() == RefereeState::SUCCEED_BLOCKED) {
            // ask parent or global referee to unlock pending.
            GroupAdjudicate(Claim(this), GestureDisposal::ACCEPT);
        }
    } else {
        if (CheckAllFailed()) {
            GroupAdjudicate(Claim(this), GestureDisposal::REJECT);
        }
    }
}

void ExclusiveRecognizer::OnResetStatus()
{
    RecognizerGroup::OnResetStatus();
    activeRecognizer_ = nullptr;
}

bool ExclusiveRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    auto curr = AceType::DynamicCast<ExclusiveRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (recognizers_.size() != curr->recognizers_.size() || curr->priorityMask_ != priorityMask_) {
        ResetStatus();
        return false;
    }

    auto currIter = curr->recognizers_.begin();

    for (auto iter = recognizers_.begin(); iter != recognizers_.end(); iter++, currIter++) {
        auto child = *iter;
        auto newChild = *currIter;
        if (!child || !child->ReconcileFrom(newChild)) {
            ResetStatus();
            return false;
        }
    }

    return true;
}

} // namespace OHOS::Ace::NG
