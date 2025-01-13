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

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void ExclusiveRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
    if (activeRecognizer_) {
        activeRecognizer_->AboutToAccept();
    }

    for (const auto& recognizer : recognizers_) {
        if (!recognizer || recognizer == activeRecognizer_) {
            continue;
        }
        if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            group->ForceReject();
            continue;
        }
        if (recognizer->IsBridgeMode()) {
            continue;
        }
        recognizer->OnRejected();
        recognizer->OnRejectBridgeObj();
    }
}

void ExclusiveRecognizer::OnRejected()
{
    if (refereeState_ == RefereeState::SUCCEED) {
        return;
    }
    refereeState_ = RefereeState::FAIL;
    for (const auto& recognizer : recognizers_) {
        if (!recognizer) {
            continue;
        }
        if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            group->ForceReject();
        } else {
            if (recognizer->IsBridgeMode()) {
                continue;
            }
            recognizer->OnRejected();
            recognizer->OnRejectBridgeObj();
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
    if (point.type == TouchType::DOWN || point.type == TouchType::UP) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, exclusive %{public}d type: %{public}d",
            point.touchEventId, point.id, static_cast<int32_t>(point.type));
    }
    switch (point.type) {
        case TouchType::MOVE:
        case TouchType::DOWN: {
            if (activeRecognizer_ && activeRecognizer_->CheckTouchId(point.id)) {
                DispatchEventToActiveRecognizers(point);
            } else {
                DispatchEventToAllRecognizers(point);
            }
            break;
        }
        case TouchType::UP:
        case TouchType::CANCEL: {
            DispatchEventToAllRecognizers(point);
            break;
        }
        default:
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
        case AxisAction::CANCEL:
        case AxisAction::NONE: {
            if (activeRecognizer_) {
                activeRecognizer_->HandleEvent(event);
            } else {
                auto copyRecognizers = recognizers_;
                for (const auto& recognizer : copyRecognizers) {
                    if (recognizer) {
                        recognizer->HandleEvent(event);
                    }
                }
            }
            break;
        }
        default:
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
        return nullptr;
    }
    return *iter;
}

void ExclusiveRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    CHECK_NULL_VOID(recognizer);

    if (IsRefereeFinished()) {
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
            break;
    }
}

void ExclusiveRecognizer::HandleAcceptDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::SUCCEED) {
        return;
    }

    if (recognizer->GetRefereeState() != RefereeState::PENDING && CheckNeedBlocked(recognizer)) {
        recognizer->OnBlocked();
        auto multiFingerRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(recognizer);
        if (multiFingerRecognizer) {
            multiFingerRecognizer->SetTouchPointsForSucceedBlock();
        }
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

void ExclusiveRecognizer::CleanRecognizerState()
{
    for (const auto& child : recognizers_) {
        auto childRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(child);
        if (childRecognizer && childRecognizer->GetTouchPointsSize() <= 1) {
            childRecognizer->CleanRecognizerState();
        }
    }
    if ((refereeState_ == RefereeState::SUCCEED ||
        refereeState_ == RefereeState::FAIL ||
        refereeState_ == RefereeState::DETECTING) &&
        currentFingers_ == 0) {
        refereeState_ = RefereeState::READY;
        disposal_ = GestureDisposal::NONE;
    }
    activeRecognizer_ = nullptr;
}

void ExclusiveRecognizer::ForceCleanRecognizer()
{
    for (const auto& child : recognizers_) {
        if (child) {
            child->ForceCleanRecognizer();
        }
    }
    MultiFingersRecognizer::ForceCleanRecognizer();
    activeRecognizer_ = nullptr;
}

void ExclusiveRecognizer::DispatchEventToActiveRecognizers(const TouchEvent& point)
{
    if (point.type == TouchType::DOWN) {
        auto node = activeRecognizer_->GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE,
            "ExclusiveRecognizer receive down event has activeRecognizer, type: %{public}s, refereeState: "
            "%{public}d, node tag = %{public}s, id = " SEC_PLD(%{public}s) ".",
            AceType::TypeName(activeRecognizer_), activeRecognizer_->GetRefereeState(),
            node ? node->GetTag().c_str() : "null",
            SEC_PARAM(node ? std::to_string(node->GetId()).c_str() : "invalid"));
    }
    auto saveRecognizer = activeRecognizer_;
    activeRecognizer_->SetEventImportGestureGroup(WeakClaim(this));
    activeRecognizer_->HandleEvent(point);
    AddGestureProcedure(point, saveRecognizer);
    int32_t count = 0;
    // if activeRecognizer_ change to another recognizer, call the handleEvent function of the new
    // recognizer.
    while (activeRecognizer_ && saveRecognizer != activeRecognizer_ &&
            activeRecognizer_->CheckTouchId(point.id) &&
            count < static_cast<int32_t>(recognizers_.size()) - 1) {
        saveRecognizer = activeRecognizer_;
        activeRecognizer_->SetEventImportGestureGroup(WeakClaim(this));
        activeRecognizer_->HandleEvent(point);
        AddGestureProcedure(point, saveRecognizer);
        count++;
    }
    // if activeRecognizer_ has changed or be empty, do not dispatch to other recognizers
    if (count > 0) {
        return;
    }
    auto blockRecognizer = UnBlockGesture();
    // ensure do not dispatch same recognizer twice
    if (!blockRecognizer || blockRecognizer == saveRecognizer ||
        !blockRecognizer->CheckTouchId(point.id)) {
        return;
    }
    blockRecognizer->SetEventImportGestureGroup(WeakClaim(this));
    blockRecognizer->HandleEvent(point);
    AddGestureProcedure(point, blockRecognizer);
    return;
}

void ExclusiveRecognizer::DispatchEventToAllRecognizers(const TouchEvent& point)
{
    auto copyRecognizers = recognizers_;
    for (const auto& recognizer : copyRecognizers) {
        if (recognizer && recognizer->CheckTouchId(point.id)) {
            auto saveRecognizer = recognizer;
            recognizer->SetEventImportGestureGroup(WeakClaim(this));
            recognizer->HandleEvent(point);
            AddGestureProcedure(point, saveRecognizer);
        } else if (!recognizer) {
            if (point.type == TouchType::DOWN) {
                TAG_LOGI(AceLogTag::ACE_GESTURE,
                    "ExclusiveRecognizer receive down event has no activeRecognizer recognizer is invalid");
            }
        } else {
            if (point.type == TouchType::DOWN) {
                auto node = recognizer->GetAttachedNode().Upgrade();
                TAG_LOGI(AceLogTag::ACE_GESTURE,
                    "ExclusiveRecognizer receive down event has no activeRecognizer recognizer is not in id: "
                    "%{public}d touchTestResult, node tag = %{public}s",
                    point.id, node ? node->GetTag().c_str() : "null");
            }
        }
    }
}
} // namespace OHOS::Ace::NG
