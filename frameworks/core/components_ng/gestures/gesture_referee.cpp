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

#include "core/common/ace_application_info.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {

void GestureScope::AddMember(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);

    if (Existed(recognizer)) {
        return;
    }

    recognizers_.emplace_back(recognizer);
}

bool GestureScope::Existed(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_RETURN(recognizer, false);

    if (recognizers_.empty()) {
        return false;
    }

    auto result = std::find(recognizers_.cbegin(), recognizers_.cend(), recognizer);
    return result != recognizers_.cend();
}

bool GestureScope::CheckNeedBlocked(const RefPtr<NGGestureRecognizer>& recognizer)
{
    for (const auto& weak : recognizers_) {
        auto member = weak.Upgrade();
        if (!member || member->GetRefereeState() != RefereeState::PENDING) {
            continue;
        }
        if (member == recognizer) {
            return false;
        }
        RefPtr<NGGestureRecognizer> group = member->GetGestureGroup().Upgrade();
        while (group) {
            if (group == recognizer) {
                return false;
            }
            group = group->GetGestureGroup().Upgrade();
        }
        return true;
    }
    return false;
}

void GestureScope::OnAcceptGesture(const RefPtr<NGGestureRecognizer>& recognizer)
{
    hasGestureAccepted_ = true;
    for (const auto& weak : recognizers_) {
        auto gesture = weak.Upgrade();
        if (gesture == recognizer) {
            continue;
        }
        if (!gesture || gesture->IsBridgeMode()) {
            continue;
        }
        gesture->OnRejected();
        gesture->OnRejectBridgeObj();
    }
    if (queryStateFunc_) {
        queryStateFunc_(touchId_);
    }
}

RefPtr<NGGestureRecognizer> GestureScope::UnBlockGesture()
{
    auto iter =
        std::find_if(std::begin(recognizers_), std::end(recognizers_), [](const WeakPtr<NGGestureRecognizer>& member) {
            auto recognizer = member.Upgrade();
            return recognizer && ((recognizer->GetRefereeState() == RefereeState::PENDING_BLOCKED) ||
                                     (recognizer->GetRefereeState() == RefereeState::SUCCEED_BLOCKED));
        });
    if (iter == recognizers_.end()) {
        return nullptr;
    }
    return (*iter).Upgrade();
}

bool GestureScope::IsPending(size_t touchId)
{
    auto iter = std::find_if(
        std::begin(recognizers_), std::end(recognizers_), [touchId](const WeakPtr<NGGestureRecognizer>& member) {
            auto recognizer = member.Upgrade();
            RefereeState state = RefereeState::READY;
            if (recognizer) {
                state = recognizer->GetRefereeState();
                if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
                    auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
                    state = group->CheckStates(touchId);
                }
            }
            return recognizer && ((state == RefereeState::PENDING));
        });
    return iter != recognizers_.end();
}

bool DectectAllDone(const RefPtr<NGGestureRecognizer> recognizer)
{
    RefereeState state = recognizer->GetRefereeState();
    if (!AceType::InstanceOf<RecognizerGroup>(recognizer)) {
        if (state != RefereeState::SUCCEED && state != RefereeState::SUCCEED_BLOCKED &&
            state != RefereeState::FAIL && state != RefereeState::READY &&
            state != RefereeState::DETECTING) {
            return false;
        }
    } else {
        auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
        for (const auto& item : group->GetGroupRecognizer()) {
            bool ret = DectectAllDone(item);
            if (!ret) {
                return false;
            }
        }
    }
    return true;
}

bool GestureScope::QueryAllDone(size_t touchId)
{
    bool ret = true;
    for (auto item : recognizers_) {
        auto recognizer = item.Upgrade();
        if (!recognizer) {
            continue;
        }
        ret = DectectAllDone(recognizer);
        if (ret == false) {
            break;
        }
    }
    return ret;
}

void GestureScope::Close(bool isBlocked)
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            auto weakGroup = recognizer->GetGestureGroup();
            auto group = weakGroup.Upgrade();
            while (group) {
                recognizer = group;
                weakGroup = group->GetGestureGroup();
                group = weakGroup.Upgrade();
            }
            recognizer->FinishReferee(static_cast<int32_t>(touchId_), isBlocked);
        }
    }
}

static bool CheckRecognizer(const RefPtr<NGGestureRecognizer>& recognizer)
{
    if (!recognizer) {
        return false;
    }
    auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
    if (!group) {
        return recognizer->GetRefereeState() == RefereeState::PENDING;
    }
    auto children = group->GetGroupRecognizer();
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
        if (CheckRecognizer(*iter)) {
            return true;
        }
    }
    return group->CheckGroupState();
}

bool GestureScope::CheckRecognizerState()
{
    for (auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (CheckRecognizer(recognizer)) {
            return true;
        }
    }
    return false;
}

bool GestureScope::IsReady()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer && !recognizer->IsReady()) {
            return false;
        }
    }
    return true;
}

bool GestureScope::HasFailRecognizer()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer && recognizer->GetRefereeState() == RefereeState::FAIL) {
            return true;
        }
    }
    return false;
}

bool GestureScope::IsAnySucceedRecognizerExist()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer && (recognizer->GetRefereeState() == RefereeState::SUCCEED ||
                              recognizer->GetRefereeState() == RefereeState::SUCCEED_BLOCKED)) {
            return true;
        }
    }
    return false;
}

void GestureScope::ForceCleanGestureScope()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            recognizer->ForceCleanRecognizer();
        }
    }
    recognizers_.clear();
}

void GestureScope::ForceCleanGestureScopeState()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            recognizer->ForceCleanRecognizer();
        }
    }
}

void GestureScope::CleanGestureScopeState()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        auto multiFingerRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(recognizer);
        if (multiFingerRecognizer && multiFingerRecognizer->CheckTouchId(touchId_) &&
            multiFingerRecognizer->GetTouchPointsSize() == 1) {
            multiFingerRecognizer->CleanRecognizerState();
        }
    }
}

void GestureScope::CleanGestureScopeStateVoluntarily()
{
    for (const auto& weak : recognizers_) {
        auto recognizer = weak.Upgrade();
        if (recognizer) {
            recognizer->CleanRecognizerStateVoluntarily();
        }
    }
}

void GestureReferee::AddGestureToScope(size_t touchId, const TouchTestResult& result)
{
    RefPtr<GestureScope> scope;
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        scope = iter->second;
    } else {
        scope = MakeRefPtr<GestureScope>(touchId);
        gestureScopes_.try_emplace(touchId, scope);
    }
    for (const auto& item : result) {
        if (AceType::InstanceOf<NGGestureRecognizer>(item)) {
            scope->AddMember(DynamicCast<NGGestureRecognizer>(item));
            scope->SetQueryStateFunc(queryStateFunc_);
        }
    }
}

void GestureReferee::CleanGestureScope(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        const auto& scope = iter->second;
        if (scope->IsPending(touchId)) {
            scope->SetDelayClose();
            return;
        }
        scope->Close();
        gestureScopes_.erase(iter);
    }
}

void GestureReferee::CleanGestureStateVoluntarily(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        const auto& scope = iter->second;
        CHECK_NULL_VOID(scope);
        scope->CleanGestureScopeStateVoluntarily();
    }
}

bool GestureReferee::QueryAllDone(size_t touchId)
{
    bool ret = true;
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        const auto& scope = iter->second;
        ret = scope->QueryAllDone(touchId);
    }
    return ret;
}

bool GestureReferee::QueryAllDone()
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); ++iter) {
        if (!iter->second->QueryAllDone(iter->first)) {
            return false;
        }
    }
    return true;
}

bool GestureReferee::CheckEventTypeChange(SourceType type, bool isAxis) const
{
    if (!isAxis && lastIsAxis_) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_SIXTEEN)) {
            return (type == SourceType::TOUCH || type == SourceType::MOUSE);
        } else {
            return (type == SourceType::TOUCH);
        }
    }
    return false;
}

bool GestureReferee::CheckSourceTypeChange(SourceType type, bool isAxis_)
{
    bool ret = false;
    if (type != lastSourceType_) {
        ret = true;
        lastSourceType_ = type;
    }
    if (isAxis_ != lastIsAxis_) {
        ret = true;
        lastIsAxis_ = isAxis_;
    }
    return ret;
}

void GestureReferee::CleanAll(bool isBlocked)
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); iter++) {
        iter->second->Close(isBlocked);
    }
    gestureScopes_.clear();
}

void GestureReferee::CleanRedundanceScope()
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); iter++) {
        if (iter->second->CheckRecognizerState()) {
            continue;
        }
        iter->second->Close();
    }
}

bool GestureReferee::IsReady()
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); iter++) {
        if (!iter->second->IsReady()) {
            return false;
        }
    }
    return true;
}

bool GestureReferee::HasFailRecognizer(int32_t touchId)
{
    const auto& iter = gestureScopes_.find(touchId);
    if (iter == gestureScopes_.end()) {
        return false;
    }

    const auto& scope = iter->second;
    CHECK_NULL_RETURN(scope, false);

    return scope->HasFailRecognizer();
}

bool GestureReferee::IsAnySucceedRecognizerExist(int32_t touchId)
{
    const auto& iter = gestureScopes_.find(touchId);
    if (iter == gestureScopes_.end()) {
        return false;
    }

    const auto& scope = iter->second;
    CHECK_NULL_RETURN(scope, false);

    return scope->IsAnySucceedRecognizerExist();
}

void GestureReferee::ForceCleanGestureReferee()
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); iter++) {
        iter->second->ForceCleanGestureScope();
    }
    gestureScopes_.clear();
}

void GestureReferee::ForceCleanGestureRefereeState()
{
    for (auto iter = gestureScopes_.begin(); iter != gestureScopes_.end(); iter++) {
        iter->second->ForceCleanGestureScopeState();
    }
}

void GestureReferee::CleanGestureRefereeState(int32_t touchId)
{
    const auto& iter = gestureScopes_.find(touchId);
    if (iter == gestureScopes_.end()) {
        return;
    }

    const auto& scope = iter->second;
    CHECK_NULL_VOID(scope);

    scope->CleanGestureScopeState();
}

void GestureReferee::Adjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
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
            break;
    }
}

void GestureReferee::HandleAcceptDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
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
    recognizer->AboutToAccept();
    for (const auto& scope : gestureScopes_) {
        scope.second->OnAcceptGesture(recognizer);
    }
}

void GestureReferee::HandlePendingDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
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

void GestureReferee::HandleRejectDisposal(const RefPtr<NGGestureRecognizer>& recognizer)
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
    RefPtr<NGGestureRecognizer> newBlockRecognizer;
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
            newBlockRecognizer->AboutToAccept();
            for (const auto& scope : gestureScopes_) {
                scope.second->OnAcceptGesture(newBlockRecognizer);
            }
        }
    }
}

bool GestureReferee::HasGestureAccepted(size_t touchId) const
{
    const auto& iter = gestureScopes_.find(touchId);
    if (iter == gestureScopes_.end()) {
        return false;
    }

    const auto& scope = iter->second;
    CHECK_NULL_RETURN(scope, false);
    return scope->HasGestureAccepted();
}

} // namespace OHOS::Ace::NG
