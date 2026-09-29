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

namespace OHOS::Ace::NG {
#ifndef ENABLE_ROSEN_BACKEND

bool ValidateRSNodeInstance(
    const std::vector<Rosen::RSNode*>& rsNodes, int32_t instanceId)
{
    return true;
}

std::shared_ptr<AnimationUtils::InteractiveAnimation> CreateAndStartGroupAnimation(
    ArkUIAnimationGroupHandle group, const std::vector<Rosen::RSNode*>& childRawRSNodes,
    int32_t instanceId, const std::string& key, int64_t generation)
{
    return nullptr;
}

#endif
} // namespace OHOS::Ace::NG
