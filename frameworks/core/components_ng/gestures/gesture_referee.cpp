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
#include "core/components_ng/gestures/gesture_referee.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

void GestureScope::AddMember(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("gesture recognizer is null, AddMember failed.");
        return;
    }

    if (Existed(recognizer)) {
        LOGW("gesture recognizer has already been added.");
        return;
    }

    recognizer->BeginReferee(static_cast<int32_t>(touchId_));
    recognizers_.emplace_back(recognizer);
}

bool GestureScope::Existed(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddGestureRecognizer failed.");
        return false;
    }

    if (recognizers_.empty()) {
        return false;
    }

    auto result = std::find(recognizers_.cbegin(), recognizers_.cend(), recognizer);
    return result != recognizers_.cend();
}

bool GestureScope::CheckNeedBlocked(const RefPtr<GestureRecognizer>& recognizer)
{
    for (const auto& weak : recognizers_) {
        auto member = weak.Upgrade();
        if (member == recognizer) {
            return false;
        }

        if (member && member->GetRefereeState() == RefereeState::PENDING) {
            return true;
        }
    }
    return false;
}

void GestureScope::OnAcceptGesture(const RefPtr<GestureRecognizer>& recognizer)
{
    for (const auto& weak : recognizers_) {
        auto gesture = weak.Upgrade();
        if (gesture == recognizer) {
            continue;
        }
        if (gesture) {
            gesture->OnRejected();
        }
    }
}

RefPtr<GestureRecognizer> GestureScope::UnBlockGesture()
{
    auto iter =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const WeakPtr<GestureRecognizer>& member) {
            auto recognizer = member.Upgrade();
            return recognizer && ((recognizer->GetRefereeState() == RefereeState::PENDING_BLOCKED) ||
                                     (recognizer->GetRefereeState() == RefereeState::SUCCEED_BLOCKED));
        });
    if (iter == recognizers_.end()) {
        LOGD("no blocked gesture in recognizers");
        return nullptr;
    }
    return (*iter).Upgrade();
}

bool GestureScope::IsPending()
{
    auto iter =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const WeakPtr<GestureRecognizer>& member) {
            auto recognizer = member.Upgrade();
            return recognizer && ((recognizer->GetRefereeState() == RefereeState::PENDING));
        });
    return iter != recognizers_.end();
}

void GestureScope::Close()
{
    LOGD("force close gesture scope of id %{public}d", static_cast<int32_t>(touchId_));
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            recognizer->FinishReferee(static_cast<int32_t>(touchId_));
        }
    }
}

void GestureReferee::AddGestureToScope(size_t touchId, const TouchTestResult& result)
{
    RefPtr<GestureScope> scope;
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        LOGI("gesture scope of touch id %{public}d already exists.", static_cast<int32_t>(touchId));
        scope = iter->second;
    } else {
        scope = MakeRefPtr<GestureScope>(touchId);
        gestureScopes_.try_emplace(touchId, scope);
    }
    for (const auto& item : result) {
        if (AceType::InstanceOf<GestureRecognizer>(item)) {
            scope->AddMember(DynamicCast<GestureRecognizer>(item));
        }
    }
}

void GestureReferee::CleanGestureScope(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        const auto& scope = iter->second;
        if (scope->IsPending()) {
            scope->SetDelayClose();
            return;
        }
        scope->Close();
        gestureScopes_.erase(iter);
    }
}

void GestureReferee::Adjudicate(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    CHECK_NULL_VOID(recognizer);

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

void GestureReferee::HandleAcceptDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::SUCCEED) {
        return;
    }

    bool isBlocked = false;
    for (const auto& scope : gestureScopes_) {
        if (scope.second->CheckNeedBlocked(recognizer)) {
            isBlocked = true;
            break;
        }
    }
    if (isBlocked) {
        recognizer->OnBlocked();
        return;
    }
    auto prevState = recognizer->GetRefereeState();
    recognizer->OnAccepted();
    std::list<size_t> delayIds;
    for (const auto& scope : gestureScopes_) {
        scope.second->OnAcceptGesture(recognizer);
    }
    // clean delay task.
    if (prevState == RefereeState::PENDING) {
        auto iter = gestureScopes_.begin();
        while (iter != gestureScopes_.end()) {
            if (iter->second->IsDelayClosed()) {
                iter->second->Close();
                iter = gestureScopes_.erase(iter);
            } else {
                ++iter;
            }
        }
    }
}

void GestureReferee::HandlePendingDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::PENDING) {
        return;
    }

    bool isBlocked = false;
    for (const auto& scope : gestureScopes_) {
        if (scope.second->CheckNeedBlocked(recognizer)) {
            isBlocked = true;
            break;
        }
    }
    if (isBlocked) {
        recognizer->OnBlocked();
        return;
    }
    recognizer->OnPending();
}

void GestureReferee::HandleRejectDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (recognizer->GetRefereeState() == RefereeState::FAIL) {
        return;
    }

    auto prevState = recognizer->GetRefereeState();
    recognizer->OnRejected();
    if (prevState != RefereeState::PENDING) {
        return;
    }
    RefPtr<GestureRecognizer> newBlockRecognizer;
    for (const auto& scope : gestureScopes_) {
        newBlockRecognizer = scope.second->UnBlockGesture();
        if (newBlockRecognizer) {
            break;
        }
    }
    if (newBlockRecognizer) {
        if (newBlockRecognizer->GetRefereeState() == RefereeState::PENDING_BLOCKED) {
            newBlockRecognizer->OnPending();
        } else if (newBlockRecognizer->GetRefereeState() == RefereeState::SUCCEED_BLOCKED) {
            newBlockRecognizer->OnAccepted();
            for (const auto& scope : gestureScopes_) {
                scope.second->OnAcceptGesture(newBlockRecognizer);
            }
        }
    }

    // clean delay task.
    auto iter = gestureScopes_.begin();
    while (iter != gestureScopes_.end()) {
        if (iter->second->IsDelayClosed()) {
            iter->second->Close();
            iter = gestureScopes_.erase(iter);
        } else {
            ++iter;
        }
    }
}

} // namespace OHOS::Ace::NG
