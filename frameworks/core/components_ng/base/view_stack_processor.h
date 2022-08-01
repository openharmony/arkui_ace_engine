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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/gestures/gesture_processor.h"
#include "core/pipeline/base/render_context.h"

#define ACE_UPDATE_LAYOUT_PROPERTY(target, name, value)                         \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = frameNode->GetLayoutProperty<target>();             \
        if (cast##target) {                                                     \
            cast##target->Update##name(value);                                  \
        }                                                                       \
    } while (false)

#define ACE_UPDATE_PAINT_PROPERTY(target, name, value)                          \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = frameNode->GetPaintProperty<target>();              \
        if (cast##target) {                                                     \
            cast##target->Update##name(value);                                  \
        }                                                                       \
    } while (false)

#define ACE_UPDATE_RENDER_CONTEXT(name, value)                                 \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        CHECK_NULL_VOID(frameNode);                                             \
        auto target = frameNode->GetRenderContext();                            \
        if (target) {                                                           \
            target->Update##name(value);                                        \
        }                                                                       \
    } while (false)

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

    template<typename EventHubType>
    RefPtr<EventHubType> GetMainFrameNodeEventHub() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return frameNode->GetEventHub<EventHubType>();
    }

    RefPtr<GestureEventHub> GetMainFrameNodeGestureEventHub() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return frameNode->GetOrCreateGestureEventHub();
    }

    RefPtr<FrameNode> GetMainFrameNode() const;

    // Get main component include composed component created by js view.
    RefPtr<UINode> GetMainElementNode() const;

    // create wrappingComponentsMap and the component to map and then Push
    // the map to the render component stack.
    void Push(const RefPtr<UINode>& element, bool isCustomView = false);

    // Wrap the components map for the stack top and then pop the stack.
    // Add the wrapped component has child of the new stack top's main component.
    void Pop();

    // pop the last container
    void PopContainer();

    // End of Render function, create component tree and flush modify task.
    RefPtr<UINode> Finish();

    // Set key to be used for next node on the stack
    void PushKey(const std::string& key);

    // Returns a key for the node if it has been pushed to the stack. Default is ""
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
        auto emptyStack = std::stack<RefPtr<UINode>>();
        elementsStack_.swap(emptyStack);
    }

    RefPtr<GestureProcessor> GetOrCreateGestureProcessor()
    {
        if (!gestureStack_) {
            gestureStack_ = AceType::MakeRefPtr<GestureProcessor>();
        }
        return gestureStack_;
    }

    void ResetGestureProcessor()
    {
        return gestureStack_.Reset();
    }

private:
    ViewStackProcessor();

    bool ShouldPopImmediately();

    // Singleton instance
    static thread_local std::unique_ptr<ViewStackProcessor> instance;

    // render component stack
    std::stack<RefPtr<UINode>> elementsStack_;

    RefPtr<GestureProcessor> gestureStack_;

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
