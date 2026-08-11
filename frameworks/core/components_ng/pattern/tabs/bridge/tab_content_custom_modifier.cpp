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

#include "core/components_ng/pattern/tabs/bridge/tab_content_custom_modifier.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_model_static.h"

namespace OHOS::Ace::NG {
namespace {
ArkUINodeHandle CreateTabContentFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TabContentModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetTabContentShallowBuilder(ArkUINodeHandle node, void* shallowBuilder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* builder = reinterpret_cast<ShallowBuilder*>(shallowBuilder);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(builder);
    TabContentModelStatic::SetShallowBuilder(frameNode, AceType::Claim(builder));
}
} // namespace

namespace NodeModifier {
const ArkUITabContentCustomModifier* GetTabContentCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabContentCustomModifier modifier = {
        .createFrameNode = CreateTabContentFrameNode,
        .setShallowBuilder = SetTabContentShallowBuilder,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
