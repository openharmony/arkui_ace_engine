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

#include "search_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/search/search_model_static.h"

namespace OHOS::Ace::NG {

void SetSearchIconSymbolModifier(ArkUINodeHandle node,
    std::function<void(OHOS::Ace::WeakPtr<NG::FrameNode>)>& symbolApply)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    SearchModelStatic::SetSearchSymbolIcon(frameNode, symbolApply);
}

const ArkUIAniSearchModifier* GetSearchAniModifier()
{
    static const ArkUIAniSearchModifier impl = {
        .setSearchIconSymbol = OHOS::Ace::NG::SetSearchIconSymbolModifier
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
