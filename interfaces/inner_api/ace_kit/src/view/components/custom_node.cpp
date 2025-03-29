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

#include "ui/view/components/custom_node.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"

#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_model_ng.h"

namespace OHOS::Ace::Kit {

CustomNode::CustomNode(const RefPtr<FrameNode> aceNode)
{
    node_ = aceNode;
}

CustomNode::~CustomNode() = default;

RefPtr<CustomNode> CustomNode::Create(const std::string& tag)
{
    auto aceNode = NG::CustomNodeExtModelNG::CreateFrameNode(tag);
    return Referenced::MakeRefPtr<CustomNode>(AceType::MakeRefPtr<FrameNodeImpl>(aceNode));
}

RefPtr<CustomNode> CustomNode::GetOrCreateFrameNode(const std::string& tag)
{
    auto aceNode = NG::CustomNodeExtModelNG::GetOrCreateFrameNode(tag);
    return Referenced::MakeRefPtr<CustomNode>(AceType::MakeRefPtr<FrameNodeImpl>(aceNode));
}

} // namespace OHOS::Ace::Kit
