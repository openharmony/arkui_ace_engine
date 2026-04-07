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

#include "smart_layout_engine_impl.h"

namespace OHOS::Ace::NG {

SmartLayoutNodeImpl::SmartLayoutNodeImpl(std::shared_ptr<SmartLayoutNode> node)
    : node_(std::move(node))
{}

const std::vector<std::shared_ptr<ISmartLayoutNode>>& SmartLayoutNodeImpl::GetChildren() const
{
    const auto& nodes = node_->GetChildren();
    childrenCache_.clear();
    childrenCache_.reserve(nodes.size());
    for (const auto& node : nodes) {
        childrenCache_.push_back(std::make_shared<SmartLayoutNodeImpl>(node));
    }
    return childrenCache_;
}

std::shared_ptr<ISmartLayoutNode> SmartLayoutEngineImpl::CreateRootNode(const std::string& name)
{
    auto node = SmartLayoutNode::CreateRootNode(name);
    if (node == nullptr) {
        return nullptr;
    }
    return std::make_shared<SmartLayoutNodeImpl>(node);
}

} // namespace OHOS::Ace::NG