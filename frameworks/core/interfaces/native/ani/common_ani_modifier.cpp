/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "common_ani_modifier.h"

#include <memory>
#include <vector>

#include "base/log/log.h"
#include "bridge/arkts_frontend/ani_graphics_module.h"
#include "core/common/container_scope.h"
#include "frameworks/bridge/arkts_frontend/ani_context_module.h"

namespace OHOS::Ace::NG {

static thread_local std::vector<int32_t> restoreInstanceIds_;

ani_ref* GetHostContext()
{
#ifndef PREVIEW
    auto contextValue = OHOS::Ace::Framework::AniContextModule::GetAniContext();
    if (contextValue) {
        return contextValue.get();
    }
#endif
    return nullptr;
}

void SyncInstanceId(ArkUI_Int32 instanceId)
{
    restoreInstanceIds_.emplace_back(ContainerScope::CurrentId());
    ContainerScope::UpdateCurrent(instanceId);
}

void RestoreInstanceId()
{
    if (restoreInstanceIds_.empty()) {
        ContainerScope::UpdateCurrent(-1);
        return;
    }
    ContainerScope::UpdateCurrent(restoreInstanceIds_.back());
    restoreInstanceIds_.pop_back();
}

void SetDrawCallback(ani_env* env, ani_long ptr, ani_fn_object fnObj)
{
#ifndef PREVIEW
    Framework::AniGraphicsModule::SetDrawCallback(env, ptr, fnObj);
#endif
}

const ArkUIAniCommonModifier* GetCommonAniModifier()
{
    static const ArkUIAniCommonModifier impl = { .getHostContext = OHOS::Ace::NG::GetHostContext,
        .syncInstanceId = OHOS::Ace::NG::SyncInstanceId,
        .restoreInstanceId = OHOS::Ace::NG::RestoreInstanceId,
        .setDrawCallback = OHOS::Ace::NG::SetDrawCallback };
    return &impl;
}

void SetDrawModifier(ani_env* env, ani_long ptr, ani_object fnObj)
{
#ifndef PREVIEW
    Framework::AniGraphicsModule::SetDrawModifier(env, ptr, fnObj);
#endif
}

void Invalidate(ani_env* env, ani_long ptr)
{
#ifndef PREVIEW
    Framework::AniGraphicsModule::Invalidate(env, ptr);
#endif
}

const ArkUIAniDrawModifier* GetArkUIAniDrawModifier()
{
    static const ArkUIAniDrawModifier impl = {
        .setDrawModifier = OHOS::Ace::NG::SetDrawModifier,
        .invalidate = OHOS::Ace::NG::Invalidate,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
