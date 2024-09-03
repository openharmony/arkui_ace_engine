/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/bar_item_node.h"

#include "core/components_ng/pattern/navigation/bar_item_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<BarItemNode> BarItemNode::GetOrCreateBarItemNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return AceType::DynamicCast<BarItemNode>(frameNode);
    }
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(tag, nodeId, MakeRefPtr<BarItemPattern>());
    barItemNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(barItemNode);
    return barItemNode;
}

} // namespace OHOS::Ace::NG