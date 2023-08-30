/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/for_each_node.h"

namespace OHOS::Ace::NG {
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor);
    }
    return instance.get();
}

ViewStackProcessor::ViewStackProcessor() = default;

std::string ViewStackProcessor::ProcessViewId(const std::string& viewId)
{
    return "";
}

RefPtr<FrameNode> ViewStackProcessor::GetMainFrameNode() const
{
    return AceType::DynamicCast<FrameNode>(GetMainElementNode());
}

RefPtr<UINode> ViewStackProcessor::GetMainElementNode() const
{
    if (elementsStack_.empty()) {
        return nullptr;
    }
    return elementsStack_.top();
}

void ViewStackProcessor::Pop()
{
    if (elementsStack_.empty() || elementsStack_.size() == 1) {
        return;
    }

    auto currentNode = Finish();
    auto parent = GetMainElementNode();
    if (AceType::InstanceOf<GroupNode>(parent)) {
        auto groupNode = AceType::DynamicCast<GroupNode>(parent);
        groupNode->AddChildToGroup(currentNode);
        return;
    }
    currentNode->MountToParent(parent, DEFAULT_NODE_SLOT, AceType::InstanceOf<ForEachNode>(parent));
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    if (currentFrameNode) {
        currentFrameNode->OnMountToParentDone();
    }
    LOGD("ViewStackProcessor Pop size %{public}d", static_cast<int32_t>(elementsStack_.size()));
}

void ViewStackProcessor::PopContainer()
{
    auto top = GetMainElementNode();
    // for container node.
    if (top && !top->IsAtomicNode()) {
        Pop();
        return;
    }

    while (top && (top->IsAtomicNode())) {
        if (elementsStack_.size() == 1) {
            return;
        }
        Pop();
        top = GetMainElementNode();
    }
    Pop();
}

void ViewStackProcessor::Push(const RefPtr<UINode>& element, bool /*isCustomView*/)
{
    elementsStack_.push(element);
}

RefPtr<UINode> ViewStackProcessor::Finish()
{
    auto element = elementsStack_.top();
    elementsStack_.pop();
    return element;
}

bool ViewStackProcessor::IsCurrentVisualStateProcess()
{
    return true;
}

ScopedViewStackProcessor::ScopedViewStackProcessor()
{
    std::swap(instance_, ViewStackProcessor::instance);
}

ScopedViewStackProcessor::~ScopedViewStackProcessor()
{
    std::swap(instance_, ViewStackProcessor::instance);
}
} // namespace OHOS::Ace::NG
