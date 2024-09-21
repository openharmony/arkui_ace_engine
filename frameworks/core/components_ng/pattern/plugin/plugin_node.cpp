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

#include "core/components_ng/pattern/plugin/plugin_node.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<PluginNode> PluginNode::GetOrCreatePluginNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto pluginNode = ElementRegister::GetInstance()->GetSpecificItemById<PluginNode>(nodeId);
    if (pluginNode) {
        if (pluginNode->GetTag() == tag) {
            return pluginNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = pluginNode->GetParent();
        if (parent) {
            parent->RemoveChild(pluginNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    pluginNode = AceType::MakeRefPtr<PluginNode>(tag, nodeId, pattern, false);
    pluginNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(pluginNode);
    return pluginNode;
}

} // namespace OHOS::Ace::NG
