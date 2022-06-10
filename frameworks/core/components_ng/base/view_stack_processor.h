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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "base/memory/referenced.h"
#include "core/components_ng/base/custom_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/modifier/modify_task.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewStackProcessor final {
public:
    friend class ScopedViewStackProcessor;

    static ViewStackProcessor* GetInstance();
    ~ViewStackProcessor() = default;

    template<typename Pattern>
    RefPtr<Pattern> GetMainFrameNodePattern() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return AceType::DynamicCast<Pattern>(frameNode->GetPattern());
    }

    RefPtr<FrameNode> GetMainFrameNode() const;

    // Get main component include composed component created by js view.
    RefPtr<FrameNode> GetMainElementNode() const;

    // create wrappingComponentsMap and the component to map and then Push
    // the map to the render component stack.
    void Push(const RefPtr<FrameNode>& element, bool isCustomView = false);

    // Wrap the components map for the stack top and then pop the stack.
    // Add the wrappedcomponent has child of the new stack top's main component.
    void Pop();

    // pop the last container
    void PopContainer();

    // End of Render function, create component tree and flush modify task.
    RefPtr<FrameNode> Finish();

    void PushLayoutTask(Modifier<LayoutProperty>&& task);

    void PushRenderTask(Modifier<RenderProperty>&& task);

    void PushRenderContextTask(Modifier<RenderContext>&& task);

    // Set key to be used for next custom component on the stack
    void PushKey(const std::string& key);

    // Returns a key for the CustomComponent if it has been pushed to the stack. Default is ""
    std::string GetKey();

    // Takes care of the viewId wrt to foreach
    std::string ProcessViewId(const std::string& viewId);

    // Clear the key pushed to the stack
    void PopKey();

    void SetVisualState(VisualState state)
    {
        visualState_ = state;
    }

    std::optional<VisualState> GetVisualState() const
    {
        return visualState_;
    }

    bool IsVisualStateSet()
    {
        return visualState_.has_value();
    }

    void ClearVisualState()
    {
        visualState_.reset();
    }

    void ClearStack()
    {
        auto emptyStack = std::stack<std::unordered_map<std::string, RefPtr<FrameNode>>>();
        elementsStack_.swap(emptyStack);
    }

private:
    ViewStackProcessor();

    bool ShouldPopImmediately();

    // Go through the wrappingComponentsMap and wrap the components
    // should be done before pushing to the stack.
    RefPtr<FrameNode> WrapElements();

    // Singleton instance
    static thread_local std::unique_ptr<ViewStackProcessor> instance;

    // render component stack
    std::stack<std::unordered_map<std::string, RefPtr<FrameNode>>> elementsStack_;

    // modifier task
    std::stack<RefPtr<StateModifyTask>> modifyTaskStack_;

    std::string viewKey_;
    std::stack<size_t> keyStack_;

    std::stack<int32_t> parentIdStack_;

    std::optional<VisualState> visualState_ = std::nullopt;

    ACE_DISALLOW_COPY_AND_MOVE(ViewStackProcessor);
};

class ScopedViewStackProcessor final {
public:
    ScopedViewStackProcessor();
    ~ScopedViewStackProcessor();

private:
    std::unique_ptr<ViewStackProcessor> instance_;

    ACE_DISALLOW_COPY_AND_MOVE(ScopedViewStackProcessor);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H
