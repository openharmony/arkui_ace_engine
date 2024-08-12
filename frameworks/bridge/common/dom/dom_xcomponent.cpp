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

#include "frameworks/bridge/common/dom/dom_xcomponent.h"

namespace OHOS::Ace::Framework {
DOMXComponent::DOMXComponent(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    xComponentChild_ = AceType::MakeRefPtr<XComponentComponent>(nodeName);
    xComponentChild_->SetNodeId(nodeId);
}

void DOMXComponent::PrepareSpecializedComponent()
{
    auto xcomponentDeclaration = AceType::DynamicCast<XComponentDeclaration>(declaration_);
    if (!xcomponentDeclaration) {
        return;
    }

    auto& commonAttr = declaration_->MaybeResetAttribute<CommonAttribute>(AttributeTag::COMMON_ATTR);
    if (commonAttr.IsValid()) {
        xcomponentDeclaration->SetXComponentId(commonAttr.id);
    }

    xComponentChild_->SetDeclaration(xcomponentDeclaration);
}

std::string DOMXComponent::GetSurfaceId() const
{
    if (!xComponentChild_) {
        return 0;
    }
    const auto& controller = xComponentChild_->GetXComponentController();
    if (!controller) {
        return 0;
    }
    auto surfaceId = controller->GetSurfaceId();
    return surfaceId;
}

void DOMXComponent::SetSurfaceSize(uint32_t surfaceWidth, uint32_t surfaceHeight) const
{
    if (!xComponentChild_) {
        return;
    }
    const auto& controller = xComponentChild_->GetXComponentController();
    if (!controller) {
        return;
    }
    controller->ConfigSurface(surfaceWidth, surfaceHeight);
}
} // namespace OHOS::Ace::Framework
