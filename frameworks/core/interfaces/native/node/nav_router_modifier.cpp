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
#include "core/interfaces/native/node/nav_router_modifier.h"

#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"

namespace OHOS::Ace::NG {
void SetNavRouteMode(ArkUINodeHandle node, int32_t mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavRouterModelNG::SetNavRouteMode(frameNode, mode);
}

void ResetNavRouteMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavRouterModelNG::SetNavRouteMode(frameNode, 0);
}

namespace NodeModifier {
const ArkUINavRouterModifier* GetNavRouterModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINavRouterModifier modifier = {
        .setNavRouteMode = SetNavRouteMode,
        .resetNavRouteMode = ResetNavRouteMode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUINavRouterModifier* GetCJUINavRouterModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINavRouterModifier modifier = {
        .setNavRouteMode = SetNavRouteMode,
        .resetNavRouteMode = ResetNavRouteMode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
}
