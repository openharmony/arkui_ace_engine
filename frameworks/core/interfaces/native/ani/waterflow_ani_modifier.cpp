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
#include "waterflow_ani_modifier.h"

#include <memory>
#include <vector>

#include "frameworks/bridge/arkts_frontend/ani_water_flow_module.h"
#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void SetWaterFlowOptions(ani_env* env, ani_long ptr, ani_object fnObj)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);
    Framework::AniWaterFlowModule::SetWaterFlowSection(env, ptr, fnObj);
}

const ArkUIAniWaterFlowModifier* GetArkUIAniWaterFlowModifier()
{
    static const ArkUIAniWaterFlowModifier impl = {
        .setWaterFlowOptions = OHOS::Ace::NG::SetWaterFlowOptions,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
