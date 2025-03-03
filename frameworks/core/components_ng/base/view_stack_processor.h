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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/state_style_manager.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/gestures/gesture_processor.h"
#include "core/pipeline/base/render_context.h"

#define ACE_UPDATE_LAYOUT_PROPERTY(target, name, value)                         \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(target, name, value, frameNode);        \
    } while (false)
#define ACE_UPDATE_NODE_LAYOUT_PROPERTY(target, name, value, frameNode)         \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = (frameNode)->GetLayoutPropertyPtr<target>();        \
        if (cast##target) {                                                     \
            cast##target->Update##name(value);                                  \
        }                                                                       \
    } while (false)

#define ACE_GET_NODE_LAYOUT_PROPERTY(target, name, value, frameNode)            \
    do {                                                                        \
        auto cast##target = frameNode->GetLayoutPropertyPtr<target>();          \
        if (cast##target) {                                                     \
            value = cast##target->Get##name##Value();                           \
        }                                                                       \
    } while (false)

#define ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(target, name, value, frameNode, defaultValue)   \
    do {                                                                                                \
        auto cast##target = frameNode->GetLayoutPropertyPtr<target>();                                  \
        if (cast##target) {                                                                             \
            value = cast##target->Get##name##Value(defaultValue);                                       \
        }                                                                                               \
    } while (false)

#define ACE_UPDATE_PAINT_PROPERTY(target, name, value)                          \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_UPDATE_NODE_PAINT_PROPERTY(target, name, value, frameNode);         \
    } while (false)
#define ACE_UPDATE_NODE_PAINT_PROPERTY(target, name, value, frameNode)          \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = (frameNode)->GetPaintPropertyPtr<target>();         \
        if (cast##target) {                                                     \
            cast##target->Update##name(value);                                  \
        }                                                                       \
    } while (false)

#define ACE_GET_NODE_PAINT_PROPERTY(target, name, value, frameNode)             \
    do {                                                                        \
        auto cast##target = frameNode->GetPaintPropertyPtr<target>();           \
        if (cast##target) {                                                     \
            value = cast##target->Get##name##Value();                           \
        }                                                                       \
    } while (false)

#define ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(target, name, value, frameNode, defaultValue) \
    do {                                                                                             \
        auto cast##target = frameNode->GetPaintPropertyPtr<target>();                                \
        if (cast##target) {                                                                          \
            value = cast##target->Get##name##Value(defaultValue);                                    \
        }                                                                                            \
    } while (false)

#define ACE_UPDATE_RENDER_CONTEXT(name, value)                                  \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_UPDATE_NODE_RENDER_CONTEXT(name, value, frameNode);                 \
    } while (false)
#define ACE_UPDATE_NODE_RENDER_CONTEXT(name, value, frameNode)                  \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        const auto& target = (frameNode)->GetRenderContext();                   \
        if (target) {                                                           \
            target->Update##name(value);                                        \
        }                                                                       \
    } while (false)

#define ACE_RESET_LAYOUT_PROPERTY(target, name)                                 \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_RESET_NODE_LAYOUT_PROPERTY(target, name, frameNode);                \
    } while (false)
#define ACE_RESET_NODE_LAYOUT_PROPERTY(target, name, frameNode)                 \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = frameNode->GetLayoutPropertyPtr<target>();          \
        CHECK_NULL_VOID(cast##target);                                          \
        cast##target->Reset##name();                                            \
    } while (false)

#define ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(target, name, changeFlag)                      \
    do {                                                                                   \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();            \
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(target, name, changeFlag, frameNode);     \
    } while (false)
#define ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(target, name, changeFlag, frameNode)      \
    do {                                                                                   \
        CHECK_NULL_VOID(frameNode);                                                        \
        auto cast##target = frameNode->GetLayoutPropertyPtr<target>();                     \
        CHECK_NULL_VOID(cast##target);                                                     \
        if (cast##target->Has##name()) {                                                   \
            cast##target->Reset##name();                                                   \
            cast##target->UpdatePropertyChangeFlag(changeFlag);                            \
        }                                                                                  \
    } while (false)

#define ACE_RESET_PAINT_PROPERTY(target, name)                                  \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_RESET_NODE_PAINT_PROPERTY(target, name, frameNode);                 \
    } while (false)
#define ACE_RESET_NODE_PAINT_PROPERTY(target, name, frameNode)                  \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        auto cast##target = frameNode->GetPaintPropertyPtr<target>();           \
        CHECK_NULL_VOID(cast##target);                                          \
        cast##target->Reset##name();                                            \
    } while (false)

#define ACE_RESET_PAINT_PROPERTY_WITH_FLAG(target, name, changeFlag)                      \
    do {                                                                                  \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();           \
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(target, name, changeFlag, frameNode);     \
    } while (false)
#define ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(target, name, changeFlag, frameNode)      \
    do {                                                                                  \
        CHECK_NULL_VOID(frameNode);                                                       \
        auto cast##target = frameNode->GetPaintPropertyPtr<target>();                     \
        CHECK_NULL_VOID(cast##target);                                                    \
        cast##target->Reset##name();                                                      \
        cast##target->UpdatePropertyChangeFlag(changeFlag);                               \
    } while (false)

#define ACE_RESET_RENDER_CONTEXT(target, name)                                  \
    do {                                                                        \
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode(); \
        ACE_RESET_NODE_RENDER_CONTEXT(target, name, frameNode);                 \
    } while (false)
#define ACE_RESET_NODE_RENDER_CONTEXT(target, name, frameNode)                  \
    do {                                                                        \
        CHECK_NULL_VOID(frameNode);                                             \
        const auto& cast##target = (frameNode)->GetRenderContext();             \
        CHECK_NULL_VOID(cast##target);                                          \
        cast##target->Reset##name();                                            \
    } while (false)

namespace OHOS::Ace::NG {
using PrebuildFunc = std::function<void()>;

enum class PrebuildCompCmdType {
    FRONT = 0,
    BACK,
};

struct PrebuildCompCmd {
    PrebuildCompCmdType commandType;
    const char* commandName = "";
    PrebuildFunc prebuildFunc;

    PrebuildCompCmd(PrebuildCompCmdType commandType) : commandType(commandType) {}
    PrebuildCompCmd(PrebuildCompCmdType commandType, const char* commandName,
        PrebuildFunc& prebuildFunc) : commandType(commandType), commandName(commandName), prebuildFunc(prebuildFunc) {}
};

class ACE_EXPORT ViewStackProcessor final {
public:
    friend class ScopedViewStackProcessor;

    ACE_FORCE_EXPORT static ViewStackProcessor* GetInstance();
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

    template<typename Pattern>
    RefPtr<Pattern> GetMainFrameNodePattern(FrameNode* frameNode) const
    {
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

    RefPtr<InputEventHub> GetMainFrameNodeInputEventHub() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return frameNode->GetOrCreateInputEventHub();
    }

    RefPtr<FocusHub> GetOrCreateMainFrameNodeFocusHub() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return frameNode->GetOrCreateFocusHub();
    }

    RefPtr<FocusHub> GetMainFrameNodeFocusHub() const
    {
        auto frameNode = GetMainFrameNode();
        if (!frameNode) {
            return nullptr;
        }
        return frameNode->GetFocusHub();
    }
    
    ACE_FORCE_EXPORT FrameNode* GetMainFrameNode() const;

   // Get main component include composed component created by js view.
    const RefPtr<UINode>& GetMainElementNode() const;
    void ApplyParentThemeScopeId(const RefPtr<UINode>& element);
    // create wrappingComponentsMap and the component to map and then Push
    // the map to the render component stack.
    ACE_FORCE_EXPORT void Push(const RefPtr<UINode>& element, bool isCustomView = false);

    // Wrap the components map for the stack top and then pop the stack.
    // Add the wrapped component has child of the new stack top's main component.
    void Pop();

    // pop the last container
    ACE_FORCE_EXPORT void PopContainer();

    // End of Render function, create component tree and flush modify task.
    ACE_FORCE_EXPORT RefPtr<UINode> Finish();

    // Set key to be used for next node on the stack
    void PushKey(const std::string& key);

    // Returns a key for the node if it has been pushed to the stack. Default is ""
    std::string GetKey();

    // Takes care of the viewId wrt to foreach
    std::string ProcessViewId(const std::string& viewId);

    // Clear the key pushed to the stack
    void PopKey();

    // Check whether the current node is in the corresponding polymorphic style state.
    // When the polymorphic style is not set on the front end, it returns true regardless of the current node state;
    // When the polymorphic style is set on the front end, true is returned only if the current node state is the same
    // as the polymorphic style.
    bool IsCurrentVisualStateProcess();

    void SetVisualState(VisualState state);

    std::optional<UIState> GetVisualState() const
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

    /**
     * when nesting observeComponentCreation functions, such as in the case of
     * If, and the if branch creates a Text etc that requires an implicit pop
     * this function is needed after executing the inner observeComponentCreation
     * and before read ViewStackProcessor.GetTopMostElementId(); on the outer one
     */
    void ImplicitPopBeforeContinue();

    // End of Rerender function, flush modifier task.
    ACE_FORCE_EXPORT void FlushRerenderTask();

    /**
     * start 'get' access recording
     * account all get access to given node id
     * next node creation will claim the given node id
     * see ClaimNodeId()
     */
    void StartGetAccessRecordingFor(int32_t elmtId)
    {
        accountGetAccessToNodeId_ = elmtId;
        reservedNodeId_ = elmtId;
        if (containerId_ != OHOS::Ace::INSTANCE_ID_UNDEFINED) {
            restoreInstanceId_ = Container::CurrentId();
            ContainerScope::UpdateCurrent(containerId_);
        }
    }

    int32_t ClaimNodeId()
    {
        const auto result = reservedNodeId_;
        reservedNodeId_ = ElementRegister::UndefinedElementId;
        return result;
    }

    void SetRecycleNodeId(int32_t recycleNodeId)
    {
        recycleNodeId_ = recycleNodeId;
    }

    int32_t GetRecycleNodeId()
    {
        const auto result = recycleNodeId_;
        recycleNodeId_ = ElementRegister::UndefinedElementId;
        return result;
    }

    /**
     * get the elmtId to which all get access should be accounted
     * ElementRegister::UndefinedElementId; means no get access recording enabled
     */
    ElementIdType GetNodeIdToAccountFor() const
    {
        return accountGetAccessToNodeId_;
    }
    void SetNodeIdToAccountFor(ElementIdType elmtId)
    {
        accountGetAccessToNodeId_ = elmtId;
    }

    /**
     * inverse of StartGetAccessRecordingFor
     */
    void StopGetAccessRecording()
    {
        if (restoreInstanceId_ != OHOS::Ace::INSTANCE_ID_UNDEFINED) {
            ContainerScope::UpdateCurrent(restoreInstanceId_);
            restoreInstanceId_ = OHOS::Ace::INSTANCE_ID_UNDEFINED;
        }
        accountGetAccessToNodeId_ = ElementRegister::UndefinedElementId;
        reservedNodeId_ = ElementRegister::UndefinedElementId;
    }

    void FlushImplicitAnimation();

    // used for knowing which page node to execute the pageTransitionFunc
    void SetPageNode(const RefPtr<FrameNode>& pageNode)
    {
        currentPage_ = pageNode;
    }

    const RefPtr<FrameNode>& GetPageNode() const
    {
        return currentPage_;
    }

    // Sets the implicit animation option. This is needed for 3D Model View.
    void SetImplicitAnimationOption(const AnimationOption& option);

    // Returns implicit animation option.
    const AnimationOption& GetImplicitAnimationOption() const;

    RefPtr<UINode> GetNewUINode();

    void GetAndPushFrameNode(const std::string& tag, int32_t elmtId)
    {
        auto frameNode = FrameNode::GetFrameNode(tag, elmtId);
        if (!frameNode) {
            return;
        }
        Push(frameNode);
    }

    bool CheckTopNodeFirstBuilding() const
    {
        auto node = GetMainFrameNode();
        CHECK_NULL_RETURN(node, false);
        return node->IsFirstBuilding();
    }

    void SetCustomTitleNode(const RefPtr<UINode>& customTitleNode)
    {
        customTitleNode_ = customTitleNode;
    }

    const RefPtr<UINode> GetCustomTitleNode() const
    {
        return customTitleNode_;
    }

    void SetCustomWindowMaskNode(const RefPtr<UINode>& customWindowMaskNode)
    {
        customWindowMaskNode_ = customWindowMaskNode;
    }

    const RefPtr<UINode> GetCustomWindowMaskNode() const
    {
        return customWindowMaskNode_;
    }

    void SetCustomButtonNode(const RefPtr<UINode>& customButtonNode)
    {
        customButtonNode_ = customButtonNode;
    }

    const RefPtr<UINode> GetCustomButtonNode() const
    {
        return customButtonNode_;
    }

    void SetCustomAppBarNode(const RefPtr<UINode>& customNode)
    {
        customAppBarNode_ = customNode;
    }

    const RefPtr<UINode> GetCustomAppBarNode() const
    {
        return customAppBarNode_;
    }

    void SetIsBuilderNode(bool isBuilderNode)
    {
        isBuilderNode_ = isBuilderNode;
    }

    bool IsBuilderNode() const
    {
        return isBuilderNode_;
    }

    void SetIsExportTexture(bool isExportTexture)
    {
        isExportTexture_ = isExportTexture;
    }

    bool IsExportTexture() const
    {
        return isExportTexture_;
    }

    void SetRebuildContainerId(int32_t containerId)
    {
        containerId_ = containerId;
    }

    bool IsEmpty() const
    {
        return elementsStack_.empty();
    }

    void SetIsPrebuilding(bool isPrebuilding)
    {
        isPrebuilding_ = isPrebuilding;
    }

    bool CheckIsPrebuildTimeout()
    {
        if (!isPrebuildTimeout_) {
            isPrebuildTimeout_ = prebuildDeadline_ > 0 && GetSysTimestamp() > prebuildDeadline_;
        }
        return isPrebuildTimeout_;
    }

    bool IsPrebuilding() const
    {
        return isPrebuilding_;
    }

    std::queue<PrebuildCompCmd>& GetPrebuildComponentCmds()
    {
        return PrebuildCompCmds_;
    }

    void PushPrebuildCompCmd()
    {
        PrebuildCompCmds_.emplace(PrebuildCompCmdType::FRONT);
    }

    void PushPrebuildCompCmd(const char* commandName, PrebuildFunc prebuildFunc)
    {
        PrebuildCompCmds_.emplace(PrebuildCompCmdType::BACK, commandName, prebuildFunc);
    }
private:
    ViewStackProcessor();

    bool ShouldPopImmediately();

    // Singleton instance
    static thread_local std::unique_ptr<ViewStackProcessor> instance;

    // render component stack
    std::stack<RefPtr<UINode>> elementsStack_;

    RefPtr<FrameNode> currentPage_;

    RefPtr<UINode> customTitleNode_;
    RefPtr<UINode> customButtonNode_;
    RefPtr<UINode> customAppBarNode_;
    RefPtr<UINode> customWindowMaskNode_;

    RefPtr<GestureProcessor> gestureStack_;

    std::string viewKey_;
    std::stack<size_t> keyStack_;

    std::stack<int32_t> parentIdStack_;

    std::optional<UIState> visualState_ = std::nullopt;
    bool isBuilderNode_ = false;
    bool isExportTexture_ = false;
    bool isPrebuilding_ = false;
    bool isPrebuildTimeout_ = false;
    int64_t prebuildDeadline_ = 0;
    std::queue<PrebuildCompCmd> PrebuildCompCmds_;
    int32_t containerId_ = OHOS::Ace::INSTANCE_ID_UNDEFINED;
    int32_t restoreInstanceId_ = OHOS::Ace::INSTANCE_ID_UNDEFINED;

    ElementIdType recycleNodeId_ = ElementRegister::UndefinedElementId;
    // elmtId reserved for next component creation
    ElementIdType reservedNodeId_ = ElementRegister::UndefinedElementId;

    // elmtId to account get access to
    ElementIdType accountGetAccessToNodeId_ = ElementRegister::UndefinedElementId;

    AnimationOption implicitAnimationOption_;

    ACE_DISALLOW_COPY_AND_MOVE(ViewStackProcessor);
};

class ACE_FORCE_EXPORT ScopedViewStackProcessor final {
public:
    ScopedViewStackProcessor(int32_t containerId = OHOS::Ace::INSTANCE_ID_UNDEFINED);
    ScopedViewStackProcessor(std::unique_ptr<ViewStackProcessor>& instance,
        int32_t containerId = OHOS::Ace::INSTANCE_ID_UNDEFINED);
    ~ScopedViewStackProcessor();
    void SwapViewStackProcessor(std::unique_ptr<ViewStackProcessor>& instance);

private:
    void Init(int32_t containerId);
    std::unique_ptr<ViewStackProcessor> instance_;

    ACE_DISALLOW_COPY_AND_MOVE(ScopedViewStackProcessor);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H
