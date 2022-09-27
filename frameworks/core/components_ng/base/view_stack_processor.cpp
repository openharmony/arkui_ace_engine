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

#include "core/components_ng/base/view_stack_processor.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

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

void ViewStackProcessor::Push(const RefPtr<UINode>& element, bool /*isCustomView*/)
{
    if (ShouldPopImmediately()) {
        Pop();
    }
    elementsStack_.push(element);
}

bool ViewStackProcessor::ShouldPopImmediately()
{
    if (elementsStack_.size() <= 1) {
        return false;
    }
    // for custom node and atomic node, just pop top node when next node is coming.
    return GetMainElementNode()->IsAtomicNode();
}

void ViewStackProcessor::ImplicitPopBeforeContinue()
{
    if ((elementsStack_.size() > 1) && ShouldPopImmediately()) {
        Pop();
        LOGD("Implicit Pop done, top component is %{public}s", GetMainElementNode()->GetTag().c_str());
    } else {
        LOGD("NO Implicit Pop before continue. top component is %{public}s", GetMainElementNode()->GetTag().c_str());
    }
}

void ViewStackProcessor::FlushImplicitAnimation()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->IsOnMainTree()) {
        frameNode->MarkDirtyNode();
    }
}

void ViewStackProcessor::FlushRerenderTask()
{
    auto node = Finish();
    CHECK_NULL_VOID(node);
    node->FlushUpdateAndMarkDirty();
}

void ViewStackProcessor::Pop()
{
    if (elementsStack_.size() == 1) {
        return;
    }

    auto currentNode = Finish();
    auto parent = GetMainElementNode();
    if (AceType::InstanceOf<GroupNode>(parent)) {
        auto groupNode = AceType::DynamicCast<GroupNode>(parent);
        groupNode->AddChildToGroup(currentNode);
        return;
    }
    currentNode->MountToParent(parent);
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

RefPtr<UINode> ViewStackProcessor::Finish()
{
    if (elementsStack_.empty()) {
        LOGE("ViewStackProcessor Finish failed, input empty render or invalid root component");
        return nullptr;
    }
    auto element = elementsStack_.top();
    elementsStack_.pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    if (frameNode) {
        frameNode->MarkModifyDone();
    }
    // ForEach Partial Update Path.
    if (AceType::InstanceOf<ForEachNode>(element)) {
        auto forEachNode = AceType::DynamicCast<ForEachNode>(element);
        forEachNode->CompareAndUpdateChildren();
    }
    return element;
}

void ViewStackProcessor::PushKey(const std::string& key)
{
    if (viewKey_.empty()) {
        // For the root node, the key value is xxx.
        viewKey_ = key;
        keyStack_.emplace(key.length());
    } else {
        // For descendant nodes, the key value is xxx_xxx
        viewKey_.append("_").append(key);
        keyStack_.emplace(key.length() + 1);
    }
}

void ViewStackProcessor::PopKey()
{
    size_t length = keyStack_.top();
    keyStack_.pop();

    if (length > 0) {
        viewKey_.erase(viewKey_.length() - length);
    }
}

std::string ViewStackProcessor::GetKey()
{
    return viewKey_.empty() ? "" : viewKey_;
}

std::string ViewStackProcessor::ProcessViewId(const std::string& viewId)
{
    return viewKey_.empty() ? viewId : viewKey_ + "_" + viewId;
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
