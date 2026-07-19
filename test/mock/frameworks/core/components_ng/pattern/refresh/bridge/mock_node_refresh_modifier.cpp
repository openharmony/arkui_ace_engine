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

#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"


namespace OHOS::Ace::NG {
namespace {
ArkUINodeHandle CreateRefreshFrameNodeMock(ArkUI_Uint32 nodeId)
{
    auto frameNode = RefreshModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void InitCoordinationEventMock(
    ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    auto* coordinationEvent =
        reinterpret_cast<RefPtr<ScrollableCoordinationEvent>*>(callback);
    CHECK_NULL_VOID(coordinationEvent);
    pattern->InitCoordinationEvent(*coordinationEvent);
}
} // namespace

namespace NodeModifier {
const ArkUIRefreshModifier* GetRefreshModifier()
{
    static const ArkUIRefreshModifier modifier = {
        .createRefreshFrameNode = CreateRefreshFrameNodeMock,
        .initCoordinationEvent = InitCoordinationEventMock,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
