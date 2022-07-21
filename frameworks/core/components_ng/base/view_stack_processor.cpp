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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
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

void ViewStackProcessor::Push(const RefPtr<UINode>& element, bool isCustomView)
{
    if (ShouldPopImmediately()) {
        Pop();
    }
    elementsStack_.push(element);
    if (AceType::InstanceOf<FrameNode>(element)) {
        modifyTaskStack_.push(Referenced::MakeRefPtr<StateModifyTask>());
    }
}

void ViewStackProcessor::PushLayoutTask(Modifier<LayoutProperty>&& task)
{
    if (modifyTaskStack_.empty()) {
        LOGE("the modify task is null");
        return;
    }
    modifyTaskStack_.top()->GetLayoutTask().emplace_back(std::move(task));
}

void ViewStackProcessor::PushRenderTask(Modifier<RenderProperty>&& task)
{
    if (modifyTaskStack_.empty()) {
        LOGE("the modify task is null");
        return;
    }
    modifyTaskStack_.top()->GetRenderTask().emplace_back(std::move(task));
}

void ViewStackProcessor::PushRenderContextTask(Modifier<RenderContext>&& task)
{
    if (modifyTaskStack_.empty()) {
        LOGE("the modify task is null");
        return;
    }
    modifyTaskStack_.top()->GetRenderContextTask().emplace_back(std::move(task));
}

bool ViewStackProcessor::ShouldPopImmediately()
{
    if (elementsStack_.size() <= 1) {
        return false;
    }
    // for custom node and atomic node, just pop top node when next node is coming.
    return GetMainElementNode()->IsAtomicNode();
}

void ViewStackProcessor::Pop()
{
    if (elementsStack_.size() == 1) {
        return;
    }

    auto element = elementsStack_.top();
    elementsStack_.pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    if (!modifyTaskStack_.empty() && frameNode) {
        // TODO: Add Task create on rerender case.
        frameNode->FlushStateModifyTaskOnCreate(*modifyTaskStack_.top());
        modifyTaskStack_.pop();
    }
    element->MountToParent(GetMainElementNode());
    LOGD("ViewStackProcessor Pop size %{public}zu", elementsStack_.size());
}

void ViewStackProcessor::PopContainer()
{
    auto top = GetMainElementNode();
    // for container node.
    if (!top->IsAtomicNode()) {
        Pop();
        return;
    }

    while (top->IsAtomicNode()) {
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
    if (!modifyTaskStack_.empty() && frameNode) {
        // TODO: Add Task create on rerender case.
        frameNode->FlushStateModifyTaskOnCreate(*modifyTaskStack_.top());
        modifyTaskStack_.pop();
    }
    if (!elementsStack_.empty()) {
        LOGE("the elementsStack size is not right");
        do {
            elementsStack_.pop();
        } while (!elementsStack_.empty());
    }
    if (!modifyTaskStack_.empty()) {
        LOGE("the modifyTaskStack_ size is not right");
        do {
            modifyTaskStack_.pop();
        } while (!modifyTaskStack_.empty());
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
