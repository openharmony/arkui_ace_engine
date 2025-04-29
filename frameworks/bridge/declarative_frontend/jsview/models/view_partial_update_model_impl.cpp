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

#include "bridge/declarative_frontend/jsview/models/view_partial_update_model_impl.h"

#include "core/components/grid_layout/grid_layout_item_element.h"
#include "core/components/ifelse/if_else_element.h"
#include "core/components_v2/common/element_proxy.h"

namespace OHOS::Ace::Framework {

RefPtr<AceType> ViewPartialUpdateModelImpl::CreateNode(NodeInfoPU&& info)
{
    ACE_SCOPED_TRACE("JSViewPartialUpdate::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID

    const auto reservedElementId = ViewStackProcessor::GetInstance()->ClaimElementId();
    const std::string key = std::to_string(reservedElementId);
    auto composedComponent = AceType::MakeRefPtr<ComposedComponent>(key, "view");
    composedComponent->SetElementId(reservedElementId);
    auto isStatic = info.isStatic;
    if (info.updateViewIdFunc) {
        info.updateViewIdFunc(key);
    }

    auto renderFunction = [renderFunc = std::move(info.renderFunc), updateFunc = std::move(info.updateFunc)](
                              const RefPtr<Component>& component) -> RefPtr<Component> {
        bool isTimeout = false;
        auto node = renderFunc ? renderFunc(0, isTimeout) : nullptr;
        if (updateFunc) {
            updateFunc();
        }
        return AceType::DynamicCast<Component>(node);
    };

    auto elementFunction = [renderFunction = std::move(renderFunction), nodeInfo = std::move(info)](
                               const RefPtr<ComposedElement>& element) mutable {
        if (nodeInfo.appearFunc) {
            nodeInfo.appearFunc();
        }
        if (nodeInfo.updateNodeFunc) {
            nodeInfo.updateNodeFunc(element);
        }

        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        if (element) {
            element->SetRenderFunction(std::move(renderFunction));
            element->SetRemoveFunction(std::move(nodeInfo.removeFunc));
            if (nodeInfo.pageTransitionFunc) {
                auto pageTransitionFunction = [transitionFunc =
                                                      std::move(nodeInfo.pageTransitionFunc)]() -> RefPtr<Component> {
                    transitionFunc();
                    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
                    ViewStackProcessor::GetInstance()->ClearPageTransitionComponent();
                    return pageTransitionComponent;
                };
                element->SetPageTransitionFunction(std::move(pageTransitionFunction));
            }
        }
    };

    composedComponent->SetElementFunction(std::move(elementFunction));

    if (isStatic) {
        composedComponent->SetStatic();
    }

    return composedComponent;
}

bool ViewPartialUpdateModelImpl::MarkNeedUpdate(const WeakPtr<AceType>& node)
{
    ACE_SCOPED_TRACE("JSView::MarkNeedUpdate");
    auto weakElement = AceType::DynamicCast<ComposedElement>(node);
    if (weakElement.Invalid()) {
        LOGE("Invalid Element weak ref, internal error");
        return false;
    }
    auto element = weakElement.Upgrade();
    if (element) {
        element->MarkDirty();
    }
    return true;
}

void ViewPartialUpdateModelImpl::FlushUpdateTask(const UpdateTask& task)
{
    const int32_t elmtId = std::get<0>(task);
    const RefPtr<Component> outmostWrappingComponent = AceType::DynamicCast<Component>(std::get<1>(task)); // stop at
    const RefPtr<Component> mainComponent = AceType::DynamicCast<Component>(std::get<2>(task));            // has elmtId

    ACE_DCHECK(mainComponent != nullptr);
    ACE_DCHECK(elmtId != ElementRegister::UndefinedElementId);

    RefPtr<Element> element = ElementRegister::GetInstance()->GetElementById(elmtId);
    if (element != nullptr) {
        // special case, because new IfElement will be created
        if (AceType::DynamicCast<IfElseElement>(element) != nullptr) {
            IfElseElement::ComponentToElementLocalizedUpdate(mainComponent, element);
        } else if (AceType::DynamicCast<GridLayoutItemElement>(element) != nullptr) {
            // VSP::Finish returns swapped compared to reg
            AceType::DynamicCast<SoleChildElement>(element)->LocalizedUpdateWithItemComponent(
                mainComponent, outmostWrappingComponent);
        } else {
            element->LocalizedUpdateWithComponent(mainComponent, outmostWrappingComponent);
        }
        return;
    }

    auto elementProxy = ElementRegister::GetInstance()->GetElementProxyById(elmtId);
    if (elementProxy != nullptr) {
        elementProxy->LocalizedUpdate(mainComponent, outmostWrappingComponent);
        return;
    }

    LOGE("No suitable Element/ElementProxy with elmtId %{public}d found to update from %{public}s,"
         " elmtId exists in ElementRegister "
         "'%{public}s'.",
        elmtId, (mainComponent ? AceType::TypeName(mainComponent) : "no Component error"),
        (ElementRegister::GetInstance()->Exists(elmtId) ? "exists" : "missing"));
}

void ViewPartialUpdateModelImpl::FinishUpdate(
    const WeakPtr<AceType>& viewNode, int32_t id, std::function<void(const UpdateTask&)>&& emplaceTaskFunc)
{
    auto componentsPair = ViewStackProcessor::GetInstance()->FinishReturnMain();
    if ((componentsPair.first == nullptr) || (componentsPair.second == nullptr)) {
        LOGE("outmost wrapping component is null");
        return;
    }
    // chk main component componentsPair.second elmtId
    ACE_DCHECK(componentsPair.second->GetElementId() == id);
    // push the result of the update function with elmtId added on the list of pending updates, triple:
    // 0: elmtId
    // 1: outmost wrapping Component (most keep reference until localized updates done to avoid smart pointer auto
    // deletion!) 2: main Component
    if (emplaceTaskFunc) {
        emplaceTaskFunc(std::make_tuple(id, componentsPair.first, componentsPair.second));
    }

    // FlushBuild on UI thread side
    // will call MakeElementUpdatesToCompleteRerender
    auto element = AceType::DynamicCast<ComposedElement>(viewNode.Upgrade());
    if (element) {
        element->MarkDirty();
    } else {
        LOGE("Internal error, element is is null");
    }
}

} // namespace OHOS::Ace::Framework
