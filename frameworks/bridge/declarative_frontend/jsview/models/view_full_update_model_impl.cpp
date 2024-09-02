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

#include "bridge/declarative_frontend/jsview/models/view_full_update_model_impl.h"

namespace OHOS::Ace::Framework {

RefPtr<AceType> ViewFullUpdateModelImpl::CreateNode(NodeInfo&& info)
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID

    std::string key = ViewStackProcessor::GetInstance()->ProcessViewId(info.viewId);
    auto composedComponent = AceType::MakeRefPtr<ComposedComponent>(key, "view");
    auto isStatic = info.isStatic;

    auto elementFunction = [nodeInfo = std::move(info)](const RefPtr<ComposedElement>& element) mutable {
        if (nodeInfo.appearFunc) {
            nodeInfo.appearFunc();
        }

        if (nodeInfo.updateNodeFunc) {
            nodeInfo.updateNodeFunc(element);
        }

        // add render function callback to element. when the element rebuilds due
        // to state update it will call this callback to get the new child component.
        if (element) {
            auto renderFunction = [renderFunc = nodeInfo.renderFunc](
                                      const RefPtr<Component>& component) -> RefPtr<Component> {
                if (!renderFunc) {
                    return nullptr;
                }
                auto node = renderFunc();
                return AceType::DynamicCast<Component>(node);
            };
            element->SetRenderFunction(std::move(renderFunction));
            auto removeFunc = nodeInfo.removeFunc;
            element->SetRemoveFunction(std::move(removeFunc));
            if (nodeInfo.pageTransitionFunc) {
                auto pageTransitionFunction = [transitionFunc = nodeInfo.pageTransitionFunc]() -> RefPtr<Component> {
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

bool ViewFullUpdateModelImpl::MarkNeedUpdate(const WeakPtr<AceType>& node)
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

} // namespace OHOS::Ace::Framework
