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

#include "bridge/declarative_frontend/view_stack_processor.h"

#include <string>

#include "base/log/ace_trace.h"
#include "core/components/button/button_component.h"
#include "core/components/grid_layout/grid_layout_item_component.h"
#include "core/components/image/image_component.h"
#include "core/components/text/text_component.h"
#include "core/components/text_span/text_span_component.h"
#include "core/components/video/video_component_v2.h"
#include "core/components_v2/list/list_item_component.h"
#include "core/pipeline/base/multi_composed_component.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::Framework {
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor);
    }
    return instance.get();
}

RefPtr<ComposedComponent> ViewStackProcessor::GetRootComponent(const std::string& id, const std::string& name)
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("root") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<ComposedComponent>(wrappingComponentsMap["root"]);
    }

    RefPtr<ComposedComponent> rootComponent = AceType::MakeRefPtr<OHOS::Ace::ComposedComponent>(id, name);
    wrappingComponentsMap.emplace("root", rootComponent);
    return rootComponent;
}

RefPtr<CoverageComponent> ViewStackProcessor::GetCoverageComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("coverage") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<CoverageComponent>(wrappingComponentsMap["coverage"]);
    }

    std::list<RefPtr<Component>> children;
    RefPtr<CoverageComponent> coverageComponent = AceType::MakeRefPtr<OHOS::Ace::CoverageComponent>(children);
    wrappingComponentsMap.emplace("coverage", coverageComponent);
    return coverageComponent;
}

RefPtr<PositionedComponent> ViewStackProcessor::GetPositionedComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("position") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<PositionedComponent>(wrappingComponentsMap["position"]);
    }

    RefPtr<PositionedComponent> positionedComponent = AceType::MakeRefPtr<OHOS::Ace::PositionedComponent>();
    wrappingComponentsMap.emplace("position", positionedComponent);
    return positionedComponent;
}

RefPtr<FlexItemComponent> ViewStackProcessor::GetFlexItemComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("flexItem") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<FlexItemComponent>(wrappingComponentsMap["flexItem"]);
    }

    RefPtr<FlexItemComponent> flexItem = AceType::MakeRefPtr<OHOS::Ace::FlexItemComponent>(0.0, 1.0, 0.0);
    wrappingComponentsMap.emplace("flexItem", flexItem);
    return flexItem;
}

RefPtr<BoxComponent> ViewStackProcessor::GetBoxComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("box") != wrappingComponentsMap.end()) {
        auto boxComponent = AceType::DynamicCast<BoxComponent>(wrappingComponentsMap["box"]);
        if (boxComponent) {
            return boxComponent;
        }
    }

    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<OHOS::Ace::BoxComponent>();
    wrappingComponentsMap.emplace("box", boxComponent);
    return boxComponent;
}

RefPtr<Component> ViewStackProcessor::GetMainComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    return wrappingComponentsMap["main"];
}

RefPtr<DisplayComponent> ViewStackProcessor::GetDisplayComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("display") != wrappingComponentsMap.end()) {
        auto displayComponent = AceType::DynamicCast<DisplayComponent>(wrappingComponentsMap["display"]);
        if (displayComponent) {
            return displayComponent;
        }
    }

    RefPtr<DisplayComponent> displayComponent = AceType::MakeRefPtr<OHOS::Ace::DisplayComponent>();
    wrappingComponentsMap.emplace("display", displayComponent);
    return displayComponent;
}

RefPtr<TransformComponent> ViewStackProcessor::GetTransformComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("transform") != wrappingComponentsMap.end()) {
        auto transformComponent = AceType::DynamicCast<TransformComponent>(wrappingComponentsMap["transform"]);
        if (transformComponent) {
            return transformComponent;
        }
    }

    RefPtr<TransformComponent> transformComponent = AceType::MakeRefPtr<OHOS::Ace::TransformComponent>();
    wrappingComponentsMap.emplace("transform", transformComponent);
    return transformComponent;
}

RefPtr<TouchListenerComponent> ViewStackProcessor::GetTouchListenerComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("touch") != wrappingComponentsMap.end()) {
        auto touchListenerComponent = AceType::DynamicCast<TouchListenerComponent>(wrappingComponentsMap["touch"]);
        if (touchListenerComponent) {
            return touchListenerComponent;
        }
    }

    RefPtr<TouchListenerComponent> touchComponent = AceType::MakeRefPtr<OHOS::Ace::TouchListenerComponent>();
    wrappingComponentsMap.emplace("touch", touchComponent);
    return touchComponent;
}

RefPtr<GestureListenerComponent> ViewStackProcessor::GetClickGestureListenerComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("click_guesture") != wrappingComponentsMap.end()) {
        auto gestureListenerComponent =
            AceType::DynamicCast<GestureListenerComponent>(wrappingComponentsMap["click_guesture"]);
        if (gestureListenerComponent) {
            return gestureListenerComponent;
        }
    }

    RefPtr<GestureListenerComponent> clickGuestureComponent =
        AceType::MakeRefPtr<OHOS::Ace::GestureListenerComponent>();
    wrappingComponentsMap.emplace("click_guesture", clickGuestureComponent);
    return clickGuestureComponent;
}

RefPtr<FocusableComponent> ViewStackProcessor::GetFocusableComponent(bool createIfNotExist)
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("focusable") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<FocusableComponent>(wrappingComponentsMap["focusable"]);
    }
    if (createIfNotExist) {
        RefPtr<FocusableComponent> focusableComponent = AceType::MakeRefPtr<OHOS::Ace::FocusableComponent>();
        wrappingComponentsMap.emplace("focusable", focusableComponent);
        return focusableComponent;
    }
    return RefPtr<FocusableComponent>(nullptr);
}

RefPtr<GestureListenerComponent> ViewStackProcessor::GetPanGestureListenerComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("pan_guesture") != wrappingComponentsMap.end()) {
        auto gestureListenerComponent =
            AceType::DynamicCast<GestureListenerComponent>(wrappingComponentsMap["pan_guesture"]);
        if (gestureListenerComponent) {
            return gestureListenerComponent;
        }
    }

    RefPtr<GestureListenerComponent> panGuestureComponent = AceType::MakeRefPtr<OHOS::Ace::GestureListenerComponent>();
    wrappingComponentsMap.emplace("pan_guesture", panGuestureComponent);
    return panGuestureComponent;
}

RefPtr<SharedTransitionComponent> ViewStackProcessor::GetSharedTransitionComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("shared_transition") != wrappingComponentsMap.end()) {
        auto sharedTransitionComponent =
            AceType::DynamicCast<SharedTransitionComponent>(wrappingComponentsMap["shared_transition"]);
        if (sharedTransitionComponent) {
            return sharedTransitionComponent;
        }
    }

    RefPtr<SharedTransitionComponent> sharedTransitionComponent =
        AceType::MakeRefPtr<OHOS::Ace::SharedTransitionComponent>("", "", "");
    wrappingComponentsMap.emplace("shared_transition", sharedTransitionComponent);
    return sharedTransitionComponent;
}

RefPtr<NavigationDeclarationCollector> ViewStackProcessor::GetNavigationDeclarationCollector(bool createIfNotExist)
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("navigation_declaration_collector") != wrappingComponentsMap.end()) {
        return AceType::DynamicCast<NavigationDeclarationCollector>(
            wrappingComponentsMap["navigation_declaration_collector"]);
    }

    if (createIfNotExist) {
        auto navigationDeclarationCollector = AceType::MakeRefPtr<OHOS::Ace::NavigationDeclarationCollector>();
        wrappingComponentsMap.emplace("navigation_declaration_collector", navigationDeclarationCollector);
        return navigationDeclarationCollector;
    }

    return nullptr;
}

RefPtr<GestureComponent> ViewStackProcessor::GetGestureComponent()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("gesture") != wrappingComponentsMap.end()) {
        auto gestureComponent = AceType::DynamicCast<GestureComponent>(wrappingComponentsMap["gesture"]);
        if (gestureComponent) {
            return gestureComponent;
        }
    }

    RefPtr<GestureComponent> gestureComponent = AceType::MakeRefPtr<OHOS::Ace::GestureComponent>();
    wrappingComponentsMap.emplace("gesture", gestureComponent);
    return gestureComponent;
}

RefPtr<PageTransitionComponent> ViewStackProcessor::GetPageTransitionComponent()
{
    if (!pageTransitionComponent_) {
        pageTransitionComponent_ = AceType::MakeRefPtr<PageTransitionComponent>();
    }
    return pageTransitionComponent_;
}

void ViewStackProcessor::ClearPageTransitionComponent()
{
    if (pageTransitionComponent_) {
        pageTransitionComponent_.Reset();
    }
}

void ViewStackProcessor::Push(const RefPtr<Component>& component)
{
    std::unordered_map<std::string, RefPtr<Component>> wrappingComponentsMap;
    if (componentsStack_.size() > 1 && ShouldPopImmediately()) {
        Pop();
    }
    wrappingComponentsMap.emplace("main", component);
    componentsStack_.push(wrappingComponentsMap);

    auto navigationContainer = AceType::DynamicCast<NavigationContainerComponent>(component);
    if (navigationContainer) {
        navigationViewDeclaration_ = navigationContainer->GetDeclaration();
    }
}

bool ViewStackProcessor::ShouldPopImmediately()
{
    auto type = AceType::TypeName(GetMainComponent());
    auto componentGroup = AceType::DynamicCast<ComponentGroup>(GetMainComponent());
    auto multiComposedComponent = AceType::DynamicCast<MultiComposedComponent>(GetMainComponent());
    auto soleChildComponent = AceType::DynamicCast<SoleChildComponent>(GetMainComponent());
    return (strcmp(type, AceType::TypeName<TextSpanComponent>()) == 0 ||
            !(componentGroup || multiComposedComponent || soleChildComponent));
}

void ViewStackProcessor::Pop()
{
    if (componentsStack_.size() == 1) {
        return;
    }
    if (navigationViewDeclaration_) {
        auto navigationDeclarationCollector = GetNavigationDeclarationCollector(false);
        if (navigationDeclarationCollector) {
            navigationDeclarationCollector->CollectTo(navigationViewDeclaration_);
        }
    }

    auto component = WrapComponents();
    SetZIndex(component);
    UpdateTopComponentProps(component);

    componentsStack_.pop();
    auto componentGroup = AceType::DynamicCast<ComponentGroup>(GetMainComponent());
    auto multiComposedComponent = AceType::DynamicCast<MultiComposedComponent>(GetMainComponent());
    if (componentGroup) {
        componentGroup->AppendChild(component);
    } else if (multiComposedComponent) {
        multiComposedComponent->AddChild(component);
    } else {
        auto singleChild = AceType::DynamicCast<SingleChild>(GetMainComponent());
        if (singleChild) {
            singleChild->SetChild(component);
        }
    }
    LOGD("ViewStackProcessor Pop size %{public}zu", componentsStack_.size());
}

void ViewStackProcessor::PopContainer()
{
    auto type = AceType::TypeName(GetMainComponent());
    auto componentGroup = AceType::DynamicCast<ComponentGroup>(GetMainComponent());
    auto multiComposedComponent = AceType::DynamicCast<MultiComposedComponent>(GetMainComponent());
    auto soleChildComponent = AceType::DynamicCast<SoleChildComponent>(GetMainComponent());
    if ((componentGroup && strcmp(type, AceType::TypeName<TextSpanComponent>()) != 0) || multiComposedComponent ||
        soleChildComponent) {
        Pop();
        return;
    }

    while ((!componentGroup && !multiComposedComponent && !soleChildComponent) ||
           strcmp(type, AceType::TypeName<TextSpanComponent>()) == 0) {
        Pop();
        type = AceType::TypeName(GetMainComponent());
        componentGroup = AceType::DynamicCast<ComponentGroup>(GetMainComponent());
        multiComposedComponent = AceType::DynamicCast<MultiComposedComponent>(GetMainComponent());
        soleChildComponent = AceType::DynamicCast<SoleChildComponent>(GetMainComponent());
    }
    Pop();
}

RefPtr<Component> ViewStackProcessor::WrapComponents()
{
    auto& wrappingComponentsMap = componentsStack_.top();
    std::vector<RefPtr<Component>> components;

    auto mainComponent = wrappingComponentsMap["main"];

    bool isVideoType = AceType::InstanceOf<VideoComponentV2>(mainComponent) && saveComponentEvent_;
    std::unordered_map<std::string, RefPtr<Component>> videoMap;

    bool isItemComponent = AceType::InstanceOf<V2::ListItemComponent>(mainComponent);
    isItemComponent |= AceType::InstanceOf<GridLayoutItemComponent>(mainComponent);
    RefPtr<Component> itemChildComponent;

    if (isItemComponent) {
        itemChildComponent = AceType::DynamicCast<SingleChild>(mainComponent)->GetChild();
        components.emplace_back(mainComponent);
    }

    std::string componentNames[] = {
        "flexItem", "display", "transform", "touch", "pan_guesture", "click_guesture",
        "focusable", "box", "shared_transition", "coverage"
    };
    for (auto& name : componentNames) {
        auto iter = wrappingComponentsMap.find(name);
        if (iter != wrappingComponentsMap.end()) {
            iter->second->OnWrap();
            components.emplace_back(iter->second);
            if (isVideoType) {
                videoMap.emplace(std::make_pair(name, iter->second));
            }
        }
    }

    if (wrappingComponentsMap.find("shared_transition") != wrappingComponentsMap.end() &&
        wrappingComponentsMap.find("display") != wrappingComponentsMap.end()) {
        auto sharedTransitionComponent =
            AceType::DynamicCast<SharedTransitionComponent>(wrappingComponentsMap["shared_transition"]);
        auto displayComponent = AceType::DynamicCast<DisplayComponent>(wrappingComponentsMap["display"]);
        if (sharedTransitionComponent && displayComponent) {
            sharedTransitionComponent->SetOpacity(displayComponent->GetOpacity());
        }
    }

    if (isVideoType) {
        saveComponentEvent_(videoMap);
        saveComponentEvent_ = nullptr;
    }

    if (isItemComponent) {
        if (itemChildComponent) {
            components.emplace_back(itemChildComponent);
        }
    } else {
        components.emplace_back(mainComponent);
    }

    // First, composite all components.
    for (int32_t idx = static_cast<int32_t>(components.size()) - 1; idx - 1 >= 0; --idx) {
        auto singleChild = AceType::DynamicCast<SingleChild>(components[idx - 1]);
        if (singleChild) {
            singleChild->SetChild(components[idx]);
            continue;
        }

        auto coverageComponent = AceType::DynamicCast<CoverageComponent>(components[idx - 1]);
        if (coverageComponent) {
            coverageComponent->InsertChild(0, components[idx]);
            coverageComponent->Initialization();
        }
    }

    auto component = components.front();
    auto iter = wrappingComponentsMap.find("box");
    if (iter != wrappingComponentsMap.end()) {
        component->SetTextDirection(iter->second->GetTextDirection());
    }
    return component;
}

void ViewStackProcessor::UpdateTopComponentProps(const RefPtr<Component>& component)
{
    auto& wrappingComponentsMap = componentsStack_.top();
    if (wrappingComponentsMap.find("position") != wrappingComponentsMap.end()) {
        auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
        if (renderComponent) {
            auto positionedComponent = GetPositionedComponent();
            if (positionedComponent->HasPositionStyle()) {
                renderComponent->SetMotionPathOption(positionedComponent->GetMotionPathOption());
                renderComponent->SetHasLeft(positionedComponent->HasLeft());
                renderComponent->SetLeft(positionedComponent->GetLeft());
                renderComponent->SetHasTop(positionedComponent->HasTop());
                renderComponent->SetTop(positionedComponent->GetTop());
                renderComponent->SetHasBottom(positionedComponent->HasBottom());
                renderComponent->SetBottom(positionedComponent->GetBottom());
                renderComponent->SetHasRight(positionedComponent->HasRight());
                renderComponent->SetRight(positionedComponent->GetRight());
                renderComponent->SetPositionType(positionedComponent->GetPositionType());
            }
        }
    }

    if (wrappingComponentsMap.find("root") != wrappingComponentsMap.end()) {
        auto rootComponent = GetRootComponent();
        component->SetDisabledStatus(rootComponent->IsDisabledStatus());
    }
}

RefPtr<Component> ViewStackProcessor::Finish()
{
    if (componentsStack_.empty()) {
        LOGE("ViewStackProcessor Finish failed, input empty render or invalid root component");
        return nullptr;
    }
    auto component = WrapComponents();
    componentsStack_.pop();

    LOGI("ViewStackProcessor Finish size %{public}zu", componentsStack_.size());
    return component;
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

void ViewStackProcessor::SetImplicitAnimationOption(const AnimationOption& option)
{
    implicitAnimationOption_ = option;
}

const AnimationOption& ViewStackProcessor::GetImplicitAnimationOption() const
{
    return implicitAnimationOption_;
}

void ViewStackProcessor::SetZIndex(RefPtr<Component>& component)
{
    int32_t zIndex = 0;
    auto mainComponent = AceType::DynamicCast<RenderComponent>(GetMainComponent());
    if (mainComponent) {
        zIndex = mainComponent->GetZIndex();
    }

    auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
    if (renderComponent) {
        renderComponent->SetZIndex(zIndex);
    }
}

ScopedViewStackProcessor::ScopedViewStackProcessor()
{
    std::swap(instance_, ViewStackProcessor::instance);
}

ScopedViewStackProcessor::~ScopedViewStackProcessor()
{
    std::swap(instance_, ViewStackProcessor::instance);
}

} // namespace OHOS::Ace::Framework
