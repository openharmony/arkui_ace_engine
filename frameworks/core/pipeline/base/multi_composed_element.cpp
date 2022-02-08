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


#include "frameworks/core/pipeline/base/multi_composed_element.h"

#include "core/pipeline/base/multi_composed_component.h"
#include "frameworks/core/common/frontend.h"
#include "frameworks/core/pipeline/base/render_element.h"

namespace OHOS::Ace {

bool MultiComposedElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    auto multiComposed = AceType::DynamicCast<MultiComposedComponent>(newComponent);
    return multiComposed ? id_ == multiComposed->GetId() : false;
}

void MultiComposedElement::PerformBuild()
{
    auto multiComposed = AceType::DynamicCast<MultiComposedComponent>(component_);
    if (!multiComposed) {
        LOGW("MultiComposedElement: component MUST be instance of MultiComposedComponent");
        return;
    }

    UpdateChildren(multiComposed->GetChildren());
}

void MultiComposedElement::UpdateChildren(const std::list<RefPtr<Component>>& newComponents)
{
    int32_t slot = 0;
    countRenderNode_ = 0;
    if (children_.empty()) {
        for (const auto& component : newComponents) {
            auto newChild = UpdateChildWithSlot(nullptr, component, slot++, countRenderNode_ + GetRenderSlot());
            countRenderNode_ += newChild->CountRenderNode();
        }
        return;
    }

    // For declarative frontend, the component tree is very stable,
    // so size of children MUST be matched between elements and components
    if (children_.size() != newComponents.size() && component_->GetUpdateType() != UpdateType::REBUILD) {
        LOGW("Size of old children and new components are mismatched");
        return;
    }

    auto itChild = children_.begin();
    for (const auto& component : newComponents) {
        auto newChild = UpdateChildWithSlot(*(itChild++), component, slot++, countRenderNode_ + GetRenderSlot());
        countRenderNode_ += newChild->CountRenderNode();
    }
}

} // namespace OHOS::Ace
