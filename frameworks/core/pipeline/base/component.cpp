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

#include "core/pipeline/base/component.h"

#include "algorithm"
#include "core/common/ace_application_info.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace {
std::atomic<int32_t> Component::key_ = 1;

Component::Component()
{
    SetRetakeId(key_++);
    direction_ = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
}

Component::~Component() = default;

void Component::SetRetakeId(int32_t retakeId)
{
    retakeId_ = retakeId;
}

int32_t Component::GetRetakeId() const
{
    return retakeId_;
}

namespace {
bool IsRenderComponent(const RefPtr<Component>& component)
{
    return AceType::InstanceOf<RenderComponent>(component);
}
} // namespace

void Component::MergeRSNode(const std::vector<RefPtr<Component>>& components, int skip)
{
    if (components.empty()) {
        return;
    }
    // locate first & last RenderComponent
    auto head = std::find_if(components.begin() + skip, components.end(), IsRenderComponent);
    auto tail = std::find_if(components.rbegin(), components.rend() - skip, IsRenderComponent);
    if (head == components.end() || tail == components.rend() - skip) {
        return;
    }
    (*head)->isHeadComponent_ = true;
    (*tail)->isTailComponent_ = true;
}

void Component::MergeRSNode(const RefPtr<Component>& head, const RefPtr<Component>& tail)
{
    if (!head || !tail) {
        return;
    }
    head->isHeadComponent_ = true;
    tail->isTailComponent_ = true;
}

void Component::MergeRSNode(const RefPtr<Component>& standaloneNode)
{
    if (!standaloneNode) {
        return;
    }
    standaloneNode->isHeadComponent_ = true;
    standaloneNode->isTailComponent_ = true;
}

} // namespace OHOS::Ace
