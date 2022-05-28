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

#include <memory>
#include <string>

#include "core/components_ng/layout/layout_property.h"

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

RefPtr<ElementNode> ViewStackProcessor::GetMainElementNode() const
{
    if (elementsStack_.empty()) {
        return nullptr;
    }
    const auto& wrappingComponentsMap = elementsStack_.top();
    auto main = wrappingComponentsMap.find("main");
    if (main == wrappingComponentsMap.end()) {
        return nullptr;
    }
    return main->second;
}

void ViewStackProcessor::Push(const RefPtr<ElementNode>& element, bool isCustomView)
{
    if (ShouldPopImmediately()) {
        Pop();
    }
    std::unordered_map<std::string, RefPtr<ElementNode>> wrappingComponentsMap;
    wrappingComponentsMap.emplace("main", element);
    elementsStack_.push(wrappingComponentsMap);
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
    // TODO: add state operation.
    modifyTaskStack_.top()->GetLayoutTask().emplace_back(std::move(task));
}

void ViewStackProcessor::PushRenderTask(Modifier<RenderProperty>&& task)
{
    if (modifyTaskStack_.empty()) {
        LOGE("the modify task is null");
        return;
    }
    // TODO: add state operation.
    modifyTaskStack_.top()->GetRenderTask().emplace_back(std::move(task));
}

void ViewStackProcessor::PushRenderContextTask(Modifier<RenderContext>&& task)
{
    if (modifyTaskStack_.empty()) {
        LOGE("the modify task is null");
        return;
    }
    // TODO: add state operation.
    modifyTaskStack_.top()->GetRenderContext().emplace_back(std::move(task));
}

bool ViewStackProcessor::ShouldPopImmediately()
{
    if (elementsStack_.size() <= 1) {
        return false;
    }
    return GetMainElementNode()->GetType() == ElementNode::ElementType::COMPOSED_ELEMENT;
}

void ViewStackProcessor::Pop()
{
    if (elementsStack_.size() == 1) {
        return;
    }

    auto element = WrapElements();
    elementsStack_.pop();
    element->MountToParent(GetMainElementNode());
    if (!modifyTaskStack_.empty() && AceType::InstanceOf<FrameNode>(element)) {
        auto task = [modify = std::move(modifyTaskStack_.top()),
                        frameNode = AceType::DynamicCast<FrameNode>(element)]() {
            if (frameNode) {
                frameNode->FlushModifyTask(*modify);
            }
        };
        modifyTasks_.emplace_back(std::move(task));
        modifyTaskStack_.pop();
    }
    LOGD("ViewStackProcessor Pop size %{public}zu", elementsStack_.size());
}

void ViewStackProcessor::PopContainer()
{
    auto element = GetMainElementNode();
    if (element->GetType() != ElementNode::ElementType::COMPOSED_ELEMENT) {
        Pop();
        return;
    }

    while (element->GetType() == ElementNode::ElementType::COMPOSED_ELEMENT) {
        Pop();
        element = GetMainElementNode();
    }
    Pop();
}

RefPtr<ElementNode> ViewStackProcessor::WrapElements()
{
    auto& wrappingMap = elementsStack_.top();
    return wrappingMap["main"];
}

std::pair<RefPtr<ElementNode>, std::list<CancelableCallback<void()>>> ViewStackProcessor::Finish()
{
    if (elementsStack_.empty()) {
        LOGE("ViewStackProcessor Finish failed, input empty render or invalid root component");
        return { nullptr, std::list<CancelableCallback<void()>>() };
    }
    auto element = WrapElements();
    elementsStack_.pop();
    if (!modifyTaskStack_.empty() && AceType::InstanceOf<FrameNode>(element)) {
        auto task = [modify = std::move(modifyTaskStack_.top()),
                        frameNode = AceType::DynamicCast<FrameNode>(element)]() {
            if (frameNode) {
                frameNode->FlushModifyTask(*modify);
            }
        };
        modifyTasks_.emplace_back(std::move(task));
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
    return { element, std::move(modifyTasks_) };
}

void ViewStackProcessor::PushKey(const std::string& key)
{
    if (viewKey_.empty()) {
        viewKey_ = key;
        keyStack_.emplace(key.length());
    } else {
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
