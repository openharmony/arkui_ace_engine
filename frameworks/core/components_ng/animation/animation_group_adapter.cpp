/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/animation/animation_group_adapter.h"

#include <algorithm>
#include <cinttypes>
#include <cstring>
#include <thread>
#include <vector>

#include "securec.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {

namespace {

class AdapterLockGuard {
public:
    explicit AdapterLockGuard(std::mutex& mtx) : mtx_(mtx), acquired_(false)
    {
        if (!lockHeld_) {
            mtx_.lock();
            lockHeld_ = true;
            acquired_ = true;
        }
    }
    ~AdapterLockGuard()
    {
        if (acquired_) {
            lockHeld_ = false;
            mtx_.unlock();
        }
    }
    explicit operator bool() const { return acquired_; }
private:
    AdapterLockGuard(const AdapterLockGuard&) = delete;
    AdapterLockGuard& operator=(const AdapterLockGuard&) = delete;
    static thread_local bool lockHeld_;
    std::mutex& mtx_;
    bool acquired_;
};

thread_local bool AdapterLockGuard::lockHeld_ = false;

} // namespace

std::atomic<int64_t> AnimationGroupAdapter::generationCounter_ { 0 };

AnimationGroupAdapter& AnimationGroupAdapter::GetInstance()
{
    static AnimationGroupAdapter instance;
    return instance;
}

std::optional<AnimationGroupEntry> AnimationGroupAdapter::FindEntry(
    int32_t instanceId, const std::string& key)
{
    auto it = animationGroupMap_.find(instanceId);
    if (it == animationGroupMap_.end()) {
        return std::nullopt;
    }
    auto keyIt = it->second.find(key);
    if (keyIt == it->second.end()) {
        return std::nullopt;
    }
    return keyIt->second;
}

std::optional<AnimationGroupEntry> AnimationGroupAdapter::ExtractAnimation(
    int32_t instanceId, const std::string& key, bool cleanupEmpty)
{
    auto it = animationGroupMap_.find(instanceId);
    if (it == animationGroupMap_.end()) {
        return std::nullopt;
    }
    auto keyIt = it->second.find(key);
    if (keyIt == it->second.end()) {
        return std::nullopt;
    }
    AnimationGroupEntry entry = std::move(keyIt->second);
    it->second.erase(keyIt);
    if (cleanupEmpty && it->second.empty()) {
        animationGroupMap_.erase(it);
    }
    return entry;
}

ArkUI_Int32 AnimationGroupAdapter::AddAnimationGroup(
    int32_t instanceId, const std::string& key, const CreateAnimationFn& createFn)
{
    CHECK_NULL_RETURN(createFn, ERROR_CODE_PARAM_INVALID);

    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> oldAnim;
    int64_t oldGen = 0;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION, "AddAnimationGroup failed: re-entrant call detected");
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = ExtractAnimation(instanceId, key, false);
        if (entry) {
            oldAnim = std::move(entry->interactiveAnimation);
            oldGen = entry->generation;
        }
    }
    if (oldAnim) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION,
            "AddAnimationGroup: finish old animation, key=%{public}s, gen=%{public}s",
            key.c_str(), std::to_string(oldGen).c_str());
        AnimationUtils::FinishInteractiveAnimation(oldAnim, InteractiveAnimationFinishPosition::TO_START);
    }

    int64_t gen = ++generationCounter_;

    auto interactiveAnimation = createFn(instanceId, key, gen);
    if (!interactiveAnimation) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "AddAnimationGroup failed: createFn returned null, instanceId=%{public}d",
            instanceId);
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> raceAnim;
    int64_t raceGen = 0;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION,
                "AddAnimationGroup commit failed: re-entrant, key=%{public}s, gen=%{public}s",
                key.c_str(), std::to_string(gen).c_str());
            AnimationUtils::FinishInteractiveAnimation(interactiveAnimation,
                InteractiveAnimationFinishPosition::TO_START);
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = ExtractAnimation(instanceId, key, false);
        if (entry) {
            raceAnim = std::move(entry->interactiveAnimation);
            raceGen = entry->generation;
        }
        animationGroupMap_[instanceId][key] =
            AnimationGroupEntry{ std::move(interactiveAnimation), gen };
    }
    if (raceAnim) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION,
            "AddAnimationGroup: finish race animation, key=%{public}s, gen=%{public}s",
            key.c_str(), std::to_string(raceGen).c_str());
        AnimationUtils::FinishInteractiveAnimation(raceAnim, InteractiveAnimationFinishPosition::TO_START);
    }

    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AnimationGroupAdapter::RemoveAnimationGroup(int32_t instanceId, const std::string& key)
{
    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> anim;
    int64_t gen = 0;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION, "RemoveAnimationGroup failed: re-entrant call detected");
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = ExtractAnimation(instanceId, key, true);
        if (!entry) {
            return ERROR_CODE_ANIMATION_GROUP_NOT_FOUND;
        }
        anim = std::move(entry->interactiveAnimation);
        gen = entry->generation;
    }
    if (anim) {
        AnimationUtils::FinishInteractiveAnimation(anim, InteractiveAnimationFinishPosition::TO_START);
    }
    return ERROR_CODE_NO_ERROR;
}

void AnimationGroupAdapter::RemoveIfMatched(
    int32_t instanceId, const std::string& key, int64_t generation)
{
    AdapterLockGuard lock(animationGroupMapMutex_);
    if (!lock) {
        return;
    }
    auto it = animationGroupMap_.find(instanceId);
    if (it == animationGroupMap_.end()) {
        return;
    }
    auto keyIt = it->second.find(key);
    if (keyIt == it->second.end()) {
        return;
    }
    if (keyIt->second.generation != generation) {
        return;
    }
    it->second.erase(keyIt);
    if (it->second.empty()) {
        animationGroupMap_.erase(it);
    }
}

ArkUI_Int32 AnimationGroupAdapter::PauseAnimationGroup(int32_t instanceId, const std::string& key)
{
    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> anim;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION, "PauseAnimationGroup failed: re-entrant call detected");
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = FindEntry(instanceId, key);
        if (!entry) {
            return ERROR_CODE_ANIMATION_GROUP_NOT_FOUND;
        }
        anim = entry->interactiveAnimation;
    }
    if (anim) {
        auto status = AnimationUtils::GetInteractiveAnimationStatus(anim);
        if (status != InteractiveAnimationStatus::RUNNING && status != InteractiveAnimationStatus::ACTIVE) {
            return ERROR_CODE_ANIMATION_GROUP_INVALID_STATE;
        }
        if (status == InteractiveAnimationStatus::ACTIVE) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "PauseAnimationGroup called in ACTIVE state, key=%{public}s", key.c_str());
        }
        AnimationUtils::PauseInteractiveAnimation(anim);
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AnimationGroupAdapter::ResumeAnimationGroup(int32_t instanceId, const std::string& key)
{
    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> anim;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION, "ResumeAnimationGroup failed: re-entrant call detected");
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = FindEntry(instanceId, key);
        if (!entry) {
            return ERROR_CODE_ANIMATION_GROUP_NOT_FOUND;
        }
        anim = entry->interactiveAnimation;
    }
    if (anim) {
        auto status = AnimationUtils::GetInteractiveAnimationStatus(anim);
        if (status != InteractiveAnimationStatus::PAUSED) {
            return ERROR_CODE_ANIMATION_GROUP_INVALID_STATE;
        }
        AnimationUtils::ContinueInteractiveAnimation(anim);
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AnimationGroupAdapter::FinishAnimationGroup(
    int32_t instanceId, const std::string& key, InteractiveAnimationFinishPosition position)
{
    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    std::shared_ptr<AnimationUtils::InteractiveAnimation> anim;
    int64_t gen = 0;
    {
        AdapterLockGuard lock(animationGroupMapMutex_);
        if (!lock) {
            TAG_LOGE(AceLogTag::ACE_ANIMATION, "FinishAnimationGroup failed: re-entrant call detected");
            return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
        }
        auto entry = FindEntry(instanceId, key);
        if (!entry) {
            return ERROR_CODE_ANIMATION_GROUP_NOT_FOUND;
        }
        anim = entry->interactiveAnimation;
        gen = entry->generation;
    }
    if (anim) {
        auto status = AnimationUtils::GetInteractiveAnimationStatus(anim);
        if (status != InteractiveAnimationStatus::RUNNING &&
            status != InteractiveAnimationStatus::ACTIVE &&
            status != InteractiveAnimationStatus::PAUSED) {
            return ERROR_CODE_ANIMATION_GROUP_INVALID_STATE;
        }
        if (status == InteractiveAnimationStatus::ACTIVE) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "FinishAnimationGroup called in ACTIVE state, key=%{public}s",
                key.c_str());
        }
        AnimationUtils::FinishInteractiveAnimation(anim, position);
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AnimationGroupAdapter::GetAnimationGroupState(
    int32_t instanceId, const std::string& key, ArkUI_Int32* state)
{
    CHECK_NULL_RETURN(state, ERROR_CODE_PARAM_INVALID);

    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    AdapterLockGuard lock(animationGroupMapMutex_);
    if (!lock) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "GetAnimationGroupState failed: re-entrant call detected");
        return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
    }
    auto entry = FindEntry(instanceId, key);
    if (!entry) {
        return ERROR_CODE_ANIMATION_GROUP_NOT_FOUND;
    }
    auto status = AnimationUtils::GetInteractiveAnimationStatus(entry->interactiveAnimation);
    switch (status) {
        case InteractiveAnimationStatus::RUNNING:
        case InteractiveAnimationStatus::ACTIVE:
            *state = static_cast<ArkUI_Int32>(AnimationGroupState::RUNNING);
            break;
        case InteractiveAnimationStatus::PAUSED:
            *state = static_cast<ArkUI_Int32>(AnimationGroupState::PAUSED);
            break;
        case InteractiveAnimationStatus::INACTIVE:
            *state = static_cast<ArkUI_Int32>(AnimationGroupState::INACTIVE);
            break;
        default:
            *state = static_cast<ArkUI_Int32>(AnimationGroupState::INACTIVE);
            break;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AnimationGroupAdapter::HasAnimationGroup(
    int32_t instanceId, const std::string& key, bool* exists)
{
    CHECK_NULL_RETURN(exists, ERROR_CODE_PARAM_INVALID);

    if (instanceId < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }

    AdapterLockGuard lock(animationGroupMapMutex_);
    if (!lock) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "HasAnimationGroup failed: re-entrant call detected");
        return ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL;
    }
    *exists = FindEntry(instanceId, key).has_value();
    return ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::NG
