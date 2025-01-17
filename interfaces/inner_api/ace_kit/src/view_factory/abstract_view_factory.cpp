/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace_kit/include/ui/view_factory/abstract_view_factory.h"

#include "interfaces/inner_api/ace_kit/include/ui/view/frame_node.h"
#include "interfaces/inner_api/ace_kit/src/view/extend_pattern.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

namespace OHOS::Ace::Kit {
RefPtr<FrameNode> AbstractViewFactory::CreateFrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot, bool isLayoutNode)
{
    auto acePattern = AceType::MakeRefPtr<ExtendPattern>(pattern);
    auto aceFrameNode = AceType::MakeRefPtr<NG::FrameNode>(tag, nodeId, acePattern, isRoot, isLayoutNode);

    auto frameNode = AceType::MakeRefPtr<FrameNodeImpl>(aceFrameNode, pattern);
    aceFrameNode->SetKitNode(frameNode);
    frameNode->InitializePatternAndContext();
    pattern->SetHost(frameNode);

    return frameNode;
}
} // namespace OHOS::Ace::Kit
