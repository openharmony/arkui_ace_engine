/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_VIEW_STACK_PROCESSOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_VIEW_STACK_PROCESSOR_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "core/accessibility/accessibility_node.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/pipeline/base/component.h"
#include "frameworks/core/components/box/box_component.h"
#include "frameworks/core/components/checkable/radio_group_component.h"
#include "frameworks/core/components/coverage/coverage_component.h"
#include "frameworks/core/components/display/display_component.h"
#include "frameworks/core/components/flex/flex_item_component.h"
#include "frameworks/core/components/focusable/focusable_component.h"
#include "frameworks/core/components/gesture_listener/gesture_component.h"
#include "frameworks/core/components/gesture_listener/gesture_listener_component.h"
#include "frameworks/core/components/menu/menu_component.h"
#include "frameworks/core/components/mouse_listener/mouse_listener_component.h"
#include "frameworks/core/components/navigation_bar/navigation_container_component.h"
#include "frameworks/core/components/page_transition/page_transition_component.h"
#include "frameworks/core/components/scroll/scroll_component.h"
#include "frameworks/core/components/stepper/stepper_item_component.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/core/components/popup/popup_component_v2.h"
#endif
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/positioned/positioned_component.h"
#include "frameworks/core/components/shared_transition/shared_transition_component.h"
#include "frameworks/core/components/touch_listener/touch_listener_component.h"
#include "frameworks/core/components/transform/transform_component.h"
#include "frameworks/core/components_v2/inspector/inspector_composed_component.h"

namespace OHOS::Ace::Framework {
    using JsPageRadioGroups = std::unordered_map<std::string, RadioGroupComponent<std::string>>;
    using JsPageCheckboxGroups = std::unordered_map<std::string, RefPtr<CheckboxComponent>>;

class ViewStackProcessor final {
public:
    using SaveComponentEvent = std::function<void(std::unordered_map<std::string, RefPtr<Component>>)>;
    friend class ScopedViewStackProcessor;

    ACE_FORCE_EXPORT static ViewStackProcessor* GetInstance();
    ~ViewStackProcessor() = default;
    // possible wrapping components
    RefPtr<FlexItemComponent> GetFlexItemComponent();
    RefPtr<StepperItemComponent> GetStepperItemComponent();
    RefPtr<DisplayComponent> GetStepperDisplayComponent();
    RefPtr<ScrollComponent> GetStepperScrollComponent();
    RefPtr<BoxComponent> GetBoxComponent();
    RefPtr<Component> GetMainComponent() const;
    RefPtr<DisplayComponent> GetDisplayComponent();
    bool HasDisplayComponent() const;
    RefPtr<TransformComponent> GetTransformComponent();
    RefPtr<TouchListenerComponent> GetTouchListenerComponent();
    bool HasTouchListenerComponent() const;
    RefPtr<MouseListenerComponent> GetMouseListenerComponent();
    RefPtr<GestureListenerComponent> GetClickGestureListenerComponent();
    bool HasClickGestureListenerComponent() const;
    RefPtr<GestureListenerComponent> GetPanGestureListenerComponent();
    RefPtr<FocusableComponent> GetFocusableComponent(bool createIfNotExist = true);
    RefPtr<SharedTransitionComponent> GetSharedTransitionComponent();
    RefPtr<GestureComponent> GetGestureComponent();
    RefPtr<PositionedComponent> GetPositionedComponent();
    RefPtr<ComposedComponent> GetRootComponent(const std::string& id = "", const std::string& name = "");
    RefPtr<PageTransitionComponent> GetPageTransitionComponent();
    RefPtr<CoverageComponent> GetCoverageComponent();
    void ClearPageTransitionComponent();
    RefPtr<MenuComponent> GetMenuComponent(bool createNewComponent = true);
#ifndef WEARABLE_PRODUCT
    RefPtr<PopupComponentV2> GetPopupComponent(bool createNewComponent = true);
#endif

    // create wrappingComponentsMap and the component to map and then Push
    // the map to the stack.
    // use flag: isCustomView to avoid creating redundant Components.
    void Push(const RefPtr<Component>& component, bool isCustomView = false);

    // special versions of Push and Pop for JSGrid
    // maintains a stack of GridLayoutComponent
    // to be accessed when creating JSGridItems
    void PushGrid(const RefPtr<GridLayoutComponent>& gridComponent)
    {
        gridStack_.push(gridComponent);
        Push(gridComponent);
    }

    void PopGrid()
    {
        if (!gridStack_.empty()) {
            gridStack_.pop();
        }
        Pop();
    }

    RefPtr<GridLayoutComponent> GetTopGrid() const
    {
        if (gridStack_.empty()) {
            return nullptr;
        }
        return gridStack_.top();
    }

    // Push special tabs component for tabs, tabContent.
    void PushTabs(const RefPtr<Component>& component)
    {
        tabsStack_.push(component);
    }

    void PopTabs()
    {
        tabsStack_.pop();
    }

    RefPtr<Component> GetTopTabs() const
    {
        if (tabsStack_.empty()) {
            return nullptr;
        }
        return tabsStack_.top();
    }

    // Wrap the components map for the stack top and then pop the stack.
    // Add the wrappedcomponent has child of the new stack top's main component.
    void Pop();

    // pop the last container
    void PopContainer();

    // End of Render function, create component tree.
    RefPtr<Component> Finish()
    {
        return FinishReturnMain().first;
    }

    // return mainComponent ... outmostWrappingComponent
    // local Component to Element updates will be performed on these any any Component in-between
    // returns the same cComponent twice if no wrapping Components.
    std::pair<RefPtr<Component>, RefPtr<Component>> FinishReturnMain();

    int32_t Size() const
    {
        return static_cast<int32_t>(componentsStack_.size());
    }

    // Set key to be used for next custom component on the stack
    void PushKey(const std::string& key);

    // Returns a key for the CustomComponent if it has been pushed to the stack. Default is ""
    std::string GetKey();

    // Takes care of the viewId wrt to foreach
    std::string ProcessViewId(const std::string& viewId);

    // Clear the key pushed to the stack
    void PopKey();

    // Sets the implicit animation option. All the views use the same option.
    void SetImplicitAnimationOption(const AnimationOption& option);

    // Returns implicit animation option.
    const AnimationOption& GetImplicitAnimationOption() const;

    void SetZIndex(RefPtr<Component>& component);
    bool ShouldPopImmediately();

    void SetIsPercentSize(RefPtr<Component>& component);
    std::shared_ptr<JsPageRadioGroups> GetRadioGroupComponent();
    std::shared_ptr<JsPageCheckboxGroups> GetCheckboxGroupComponent();

    RefPtr<Component> GetNewComponent();
    RefPtr<V2::InspectorComposedComponent> GetInspectorComposedComponent() const;

    void SetVisualState(VisualState state)
    {
        visualState_ = state;
    }

    VisualState GetVisualState()
    {
        return visualState_;
    }

    bool IsVisualStateSet()
    {
        return visualState_ != VisualState::NOTSET;
    }

    void ClearVisualState()
    {
        visualState_ = VisualState::NOTSET;
    }

    void ClearStack()
    {
        auto emptyStack = std::stack<std::unordered_map<std::string, RefPtr<Component>>>();
        componentsStack_.swap(emptyStack);
    }

    /**
     * start 'get' access recording
     * account all get access to given elmtId
     * next component creation will claim the given elmtId
     * see ClaimElementId()
     */
    void StartGetAccessRecordingFor(int32_t elmtId)
    {
        accountGetAccessToElmtId_ = elmtId;
        reservedElementId_ = elmtId;
    }

    /**
     * Use reserved elementId for given component
     * sets the reserved lemntId to none
     */
    void ClaimElementId(const RefPtr<Component>& component);

    int32_t ClaimElementId()
    {
        ACE_DCHECK(
            (reservedElementId_ != ElementRegister::UndefinedElementId) && "No reserved elmtId, internal error!");
        const auto result = reservedElementId_;
        reservedElementId_ = ElementRegister::UndefinedElementId;
        return result;
    }

    /**
     * get the elmtId to which all get access should be accounted
     * ElementRegister::UndefinedElementId; means no get access recording enabled
     */
    ElementIdType GetElmtIdToAccountFor()
    {
        return accountGetAccessToElmtId_;
    }
    void SetElmtIdToAccountFor(ElementIdType elmtId)
    {
        accountGetAccessToElmtId_ = elmtId;
    }

    /**
     * inverse of StartGetAccessRecordingFor
     */
    void StopGetAccessRecording()
    {
        accountGetAccessToElmtId_ = ElementRegister::UndefinedElementId;
        // normally already set like this, but just in case
        reservedElementId_ = ElementRegister::UndefinedElementId;
    }
    RefPtr<ComposedComponent> CreateInspectorWrapper(const std::string& inspectorTag);

    void GetAndPushFrameNode(const std::string& tag, int32_t elmtId)
    {
        LOGW("NON NG ViewStackProcessor GetAndPushFrameNode()");
        // FrameNode is not available in NON-NG pipeline.
    }

private:
    ViewStackProcessor();

#ifdef ACE_DEBUG
    // Dump view stack comtent
    void DumpStack();
#endif

    // Go through the wrappingComponentsMap and wrap the components
    // should be done before pushing to the stack.
    // returns pair(outmost wrapping Component, main Component)
    std::pair<RefPtr<Component>, RefPtr<Component>> WrapComponents();

    // Update position and enabled status
    void UpdateTopComponentProps(const RefPtr<Component>& component);

    void CreateInspectorComposedComponent(const std::string& inspectorTag);
    void CreateScoringComponent(const std::string& tag);
    RefPtr<Component> GetScoringComponent() const;

    // Singleton instance
    static thread_local std::unique_ptr<ViewStackProcessor> instance;

    // stack
    std::stack<std::unordered_map<std::string, RefPtr<Component>>> componentsStack_;
    std::shared_ptr<JsPageRadioGroups> radioGroups_;
    std::shared_ptr<JsPageCheckboxGroups> checkboxGroups_;
    // stack for tabs component.
    std::stack<RefPtr<Component>> tabsStack_;

    // stack for Grid component.
    std::stack<RefPtr<GridLayoutComponent>> gridStack_;

    RefPtr<PageTransitionComponent> pageTransitionComponent_;

    std::string viewKey_;
    std::stack<size_t> keyStack_;

    RefPtr<AccessibilityManager> accessibilityManager_;
    std::stack<int32_t> parentIdStack_;

    AnimationOption implicitAnimationOption_;
    VisualState visualState_ = VisualState::NOTSET;

    bool isScoringEnable_ = false;

    // elmtId reserved for next component creation
    ElementIdType reservedElementId_ = ElementRegister::UndefinedElementId;

    // elmtId to accouunt get access to
    ElementIdType accountGetAccessToElmtId_ = ElementRegister::UndefinedElementId;

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

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_VIEW_STACK_PROCESSOR_H
