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

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/if_else_node.h"

namespace OHOS::Ace::NG {
namespace {
const RefPtr<UINode> INVALID_NODE = nullptr;
}
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;
thread_local std::unique_ptr<ScopedViewStackProcessor> ViewStackModelNG::scopeStack_ = nullptr;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor);
    }
    return instance.get();
}

ViewStackProcessor::ViewStackProcessor() = default;

FrameNode* ViewStackProcessor::GetMainFrameNode() const
{
    auto uiNode = GetMainElementNode();
    if (!uiNode || !uiNode->IsLayoutSeperately()) {
        return nullptr;
    }
    return static_cast<FrameNode*>(Referenced::RawPtr(uiNode));
}

const RefPtr<UINode>& ViewStackProcessor::GetMainElementNode() const
{
    if (elementsStack_.empty()) {
        return INVALID_NODE;
    }
    return elementsStack_.top();
}

void ViewStackProcessor::ApplyParentThemeScopeId(const RefPtr<UINode>& element)
{
    auto parent = GetMainElementNode();
    int32_t elementThemeScopeId = element->GetThemeScopeId();
    if (parent && elementThemeScopeId == 0) {
        int32_t themeScopeId = parent->GetThemeScopeId();
        if (elementThemeScopeId != themeScopeId) {
            element->SetThemeScopeId(themeScopeId);
        }
    }
}

void ViewStackProcessor::Push(const RefPtr<UINode>& element, bool /*isCustomView*/)
{
    ApplyParentThemeScopeId(element);

    if (ShouldPopImmediately()) {
        Pop();
    }
    element->SetRemoveSilently(false);
    elementsStack_.push(element);
}

#ifdef ACE_STATIC
void ViewStackProcessor::PushPtr(int64_t elementPtr)
{
    if (elementPtr == 0) {
        return;
    }
    Push(UINode::Claim(reinterpret_cast<UINode*>(elementPtr)), true);
}
#endif

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
    if (elementsStack_.empty() || elementsStack_.size() == 1) {
        return;
    }

    auto currentNode = Finish();
    currentNode->SetBuildByJs(true);
    auto parent = GetMainElementNode();
    if (AceType::InstanceOf<GroupNode>(parent)) {
        auto groupNode = AceType::DynamicCast<GroupNode>(parent);
        groupNode->AddChildToGroup(currentNode);
        return;
    }

    currentNode->MountToParent(
        parent, DEFAULT_NODE_SLOT, AceType::InstanceOf<ForEachNode>(parent), AceType::InstanceOf<IfElseNode>(parent));
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
    if (currentFrameNode) {
        currentFrameNode->OnMountToParentDone();
    }
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
        return nullptr;
    }
    auto element = elementsStack_.top();
    elementsStack_.pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    if (frameNode) {
        frameNode->MarkBuildDone();
        frameNode->MarkModifyDone();
        auto renderContext = frameNode->GetRenderContext();
        if (renderContext) {
            renderContext->SetNeedDebugBoundary(true);
        }
    }
    // ForEach Partial Update Path.
    if (AceType::InstanceOf<ForEachNode>(element)) {
        auto forEachNode = AceType::DynamicCast<ForEachNode>(element);
        forEachNode->CompareAndUpdateChildren();
    }
    return element;
}

void ViewStackProcessor::SetVisualState(VisualState state)
{
    switch (state) {
        case VisualState::DISABLED:
            visualState_ = UI_STATE_DISABLED;
            break;
        case VisualState::FOCUSED:
            visualState_ = UI_STATE_FOCUSED;
            break;
        case VisualState::PRESSED:
            visualState_ = UI_STATE_PRESSED;
            break;
        case VisualState::SELECTED:
            visualState_ = UI_STATE_SELECTED;
            break;
        case VisualState::NORMAL:
        default:
            visualState_ = UI_STATE_NORMAL;
    }
    auto eventHub = GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->AddSupportedState(visualState_.value());
}

bool ViewStackProcessor::IsCurrentVisualStateProcess()
{
    if (!visualState_.has_value()) {
        return true;
    }
    auto eventHub = GetMainFrameNodeEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto result = eventHub->IsCurrentStateOn(visualState_.value());
    return result;
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

void ViewStackProcessor::SetImplicitAnimationOption(const AnimationOption& option)
{
    implicitAnimationOption_ = option;
}

const AnimationOption& ViewStackProcessor::GetImplicitAnimationOption() const
{
    return implicitAnimationOption_;
}

RefPtr<UINode> ViewStackProcessor::GetNewUINode()
{
    return Finish();
}

void ScopedViewStackProcessor::Init(int32_t containerId)
{
    std::swap(instance_, ViewStackProcessor::instance);
    ViewStackProcessor::GetInstance()->SetRebuildContainerId(containerId);
}

void ScopedViewStackProcessor::SwapViewStackProcessor(std::unique_ptr<ViewStackProcessor>& instance)
{
    std::swap(instance, ViewStackProcessor::instance);
}

ScopedViewStackProcessor::ScopedViewStackProcessor(int32_t containerId)
{
    Init(containerId);
}

ScopedViewStackProcessor::ScopedViewStackProcessor(std::unique_ptr<ViewStackProcessor>& instance, int32_t containerId)
{
    std::swap(instance_, instance);
    Init(containerId);
}

ScopedViewStackProcessor::~ScopedViewStackProcessor()
{
    ViewStackProcessor::GetInstance()->SetRebuildContainerId(OHOS::Ace::INSTANCE_ID_UNDEFINED);
    std::swap(instance_, ViewStackProcessor::instance);
}
} // namespace OHOS::Ace::NG
