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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_ANIMATION_GROUP_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_ANIMATION_GROUP_ADAPTER_H

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/error/error_code.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "ui/animation/animation_constants.h"

namespace OHOS::Rosen {
class RSNode;
} // namespace OHOS::Rosen

namespace OHOS::Ace::NG {

using CreateAnimationFn = std::function<std::shared_ptr<AnimationUtils::InteractiveAnimation>(
    int32_t instanceId, const std::string& key, int64_t generation)>;

struct AnimationGroupEntry {
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation;
    int64_t generation = 0;
};

bool ValidateRSNodeInstance(
    const std::vector<Rosen::RSNode*>& rsNodes, int32_t instanceId);

std::shared_ptr<AnimationUtils::InteractiveAnimation> CreateAndStartGroupAnimation(
    ArkUIAnimationGroupHandle group, const std::vector<Rosen::RSNode*>& childRawRSNodes,
    int32_t instanceId, const std::string& key, int64_t generation);

class AnimationGroupAdapter {
public:
    static AnimationGroupAdapter& GetInstance();

    ArkUI_Int32 AddAnimationGroup(int32_t instanceId, const std::string& key, const CreateAnimationFn& createFn);
    ArkUI_Int32 RemoveAnimationGroup(int32_t instanceId, const std::string& key);
    void RemoveIfMatched(int32_t instanceId, const std::string& key, int64_t generation);

    ArkUI_Int32 PauseAnimationGroup(int32_t instanceId, const std::string& key);
    ArkUI_Int32 ResumeAnimationGroup(int32_t instanceId, const std::string& key);
    ArkUI_Int32 FinishAnimationGroup(int32_t instanceId, const std::string& key,
        InteractiveAnimationFinishPosition position);

    ArkUI_Int32 GetAnimationGroupState(int32_t instanceId, const std::string& key, ArkUI_Int32* state);
    ArkUI_Int32 HasAnimationGroup(int32_t instanceId, const std::string& key, bool* exists);

private:
    AnimationGroupAdapter() = default;
    ~AnimationGroupAdapter() = default;

    std::optional<AnimationGroupEntry> FindEntry(int32_t instanceId, const std::string& key);
    std::optional<AnimationGroupEntry> ExtractAnimation(
        int32_t instanceId, const std::string& key, bool cleanupEmpty);

    std::unordered_map<int32_t, std::unordered_map<std::string,
        AnimationGroupEntry>> animationGroupMap_;
    std::mutex animationGroupMapMutex_;
    static std::atomic<int64_t> generationCounter_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_ANIMATION_ANIMATION_GROUP_ADAPTER_H
