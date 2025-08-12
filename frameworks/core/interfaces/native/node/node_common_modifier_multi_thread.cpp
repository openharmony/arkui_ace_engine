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

#include "core/interfaces/native/node/node_common_modifier_multi_thread.h"
namespace OHOS::Ace::NG {
void SetGeometryTransitionMultiThread(ArkUINodeHandle node, ArkUI_CharPtr id,
    const ArkUIGeometryTransitionOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string idStr(id);

    auto follow = static_cast<bool>(options->follow);
    auto strategy = static_cast<bool>(options->hierarchyStrategy);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), idStr, follow, strategy]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        ViewAbstract::SetGeometryTransition(AceType::RawPtr(node), idStr, follow, strategy);
    });
}

void ResetGeometryTransitionMultiThread(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode)]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        ViewAbstract::SetGeometryTransition(AceType::RawPtr(node), "", false, true);
    });
}
}