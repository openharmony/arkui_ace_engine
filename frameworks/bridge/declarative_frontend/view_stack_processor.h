/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/animation_option.h"
#include "core/pipeline/base/component.h"
#include "frameworks/core/components/box/box_component.h"
#include "frameworks/core/components/coverage/coverage_component.h"
#include "frameworks/core/components/display/display_component.h"
#include "frameworks/core/components/flex/flex_item_component.h"
#include "frameworks/core/components/focusable/focusable_component.h"
#include "frameworks/core/components/gesture_listener/gesture_component.h"
#include "frameworks/core/components/gesture_listener/gesture_listener_component.h"
#include "frameworks/core/components/mouse_listener/mouse_listener_component.h"
#include "frameworks/core/components/navigation_bar/navigation_container_component.h"
#include "frameworks/core/components/page_transition/page_transition_component.h"
#ifndef WEARABLE_PRODUCT
#include "frameworks/core/components/popup/popup_component_v2.h"
#endif
#include "frameworks/core/components/positioned/positioned_component.h"
#include "frameworks/core/components/shared_transition/shared_transition_component.h"
#include "frameworks/core/components/touch_listener/touch_listener_component.h"
#include "frameworks/core/components/transform/transform_component.h"
#include "frameworks/core/components_v2/inspector/inspector_composed_component.h"

namespace OHOS::Ace::Framework {
class ViewStackProcessor final {
public:
    using SaveComponentEvent = std::function<void(std::unordered_map<std::string, RefPtr<Component>>)>;
    friend class ScopedViewStackProcessor;

    static ViewStackProcessor* GetInstance();
    ~ViewStackProcessor() = default;
    // possible wrapping components
    static std::string GenerateId();
    RefPtr<FlexItemComponent> GetFlexItemComponent();
    RefPtr<BoxComponent> GetBoxComponent();
    RefPtr<Component> GetMainComponent();
    RefPtr<DisplayComponent> GetDisplayComponent();
    bool HasDisplayComponent() const;
    RefPtr<TransformComponent> GetTransformComponent();
    RefPtr<TouchListenerComponent> GetTouchListenerComponent();
    RefPtr<MouseListenerComponent> GetMouseListenerComponent();
    RefPtr<GestureListenerComponent> GetClickGestureListenerComponent();
    RefPtr<GestureListenerComponent> GetPanGestureListenerComponent();
    RefPtr<FocusableComponent> GetFocusableComponent(bool createIfNotExist = true);
    RefPtr<SharedTransitionComponent> GetSharedTransitionComponent();
    RefPtr<NavigationDeclarationCollector> GetNavigationDeclarationCollector(bool createIfNotExist = true);
    RefPtr<GestureComponent> GetGestureComponent();
    RefPtr<PositionedComponent> GetPositionedComponent();
    RefPtr<ComposedComponent> GetRootComponent(const std::string& id = "", const std::string& name = "");
    RefPtr<PageTransitionComponent> GetPageTransitionComponent();
    RefPtr<CoverageComponent> GetCoverageComponent();
    void ClearPageTransitionComponent();
    void CreateAccessibilityNode(const RefPtr<Component>& component);
#ifndef WEARABLE_PRODUCT
    RefPtr<PopupComponentV2> GetPopupComponent(bool createNewComponent = true);
#endif

    // create wrappingComponentsMap and the component to map and then Push
    // the map to the stack.
    // use flag: isCustomView to avoid creating redundant Components.
    void Push(const RefPtr<Component>& component, bool isCustomView = false);

    // Wrap the components map for the stack top and then pop the stack.
    // Add the wrappedcomponent has child of the new stack top's main component.
    void Pop();

    // pop the last container
    void PopContainer();

    // End of Render function, create component tree.
    RefPtr<Component> Finish();

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

    void SetIsPercentSize(RefPtr<Component>& component);

private:
    ViewStackProcessor() = default;

    bool ShouldPopImmediately();

#ifdef ACE_DEBUG
    // Dump view stack comtent
    void DumpStack();
#endif

    // Go through the wrappingComponentsMap and wrap the components
    // should be done before pushing to the stack.
    RefPtr<Component> WrapComponents();

    // Update position and enabled status
    void UpdateTopComponentProps(const RefPtr<Component>& component);

    RefPtr<ComposedComponent> GetInspectorComposedComponent(RefPtr<Component> mainComponent);

    // Singleton instance
    static thread_local std::unique_ptr<ViewStackProcessor> instance;

    // stack
    std::stack<std::unordered_map<std::string, RefPtr<Component>>> componentsStack_;

    // navigation declaration of NavigatonView
    RefPtr<NavigationDeclaration> navigationViewDeclaration_;

    RefPtr<PageTransitionComponent> pageTransitionComponent_;

    std::string viewKey_;
    std::stack<size_t> keyStack_;

    RefPtr<AccessibilityManager> accessibilityManager_;
    std::stack<int32_t> parentIdStack_;

    AnimationOption implicitAnimationOption_;

    static thread_local int32_t composedElementId_;

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
