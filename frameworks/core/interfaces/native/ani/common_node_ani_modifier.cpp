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

#include "common_node_ani_modifier.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"

namespace OHOS::Ace::NG {

ani_long Construct(ani_int id, ani_int flags)
{
    auto frameNode = CommonViewModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, 0);
    frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    frameNode->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(frameNode));
}

void SetCommonOptions(ani_long node)
{
}

const ArkUIAniCommonNodeAniModifier* GetCommonNodeAniModifier()
{
    static const ArkUIAniCommonNodeAniModifier impl = {
        .construct = OHOS::Ace::NG::Construct,
        .setCommonOptions = OHOS::Ace::NG::SetCommonOptions,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG