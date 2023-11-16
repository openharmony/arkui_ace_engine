/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_nav_router_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
void SetNavRouteMode(NodeHandle node, int32_t mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavRouterModelNG::SetNavRouteMode(frameNode, mode);
}

void ResetNavRouteMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavRouterModelNG::SetNavRouteMode(frameNode, 0);
}

ArkUINavRouterModifierAPI GetNavRouterModifier()
{
    static const ArkUINavRouterModifierAPI modifier = {SetNavRouteMode, ResetNavRouteMode};

    return modifier;
}
}