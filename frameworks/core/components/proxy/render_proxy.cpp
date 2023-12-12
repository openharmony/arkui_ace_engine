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

#include "core/components/proxy/render_proxy.h"

#include "core/components/proxy/proxy_component.h"


namespace OHOS::Ace {

void RenderProxy::Update(const RefPtr<Component>& component)
{
    auto proxy = AceType::DynamicCast<ProxyComponent>(component);
    if (!proxy) {
        return;
    }
    passMinSize_ = proxy->GetPassMinSize();
}

RefPtr<RenderNode> RenderProxy::Create()
{
    return AceType::MakeRefPtr<RenderProxy>();
}

void RenderProxy::PerformLayout()
{
    if (GetLayoutParam().GetMaxSize() < viewPort_) {
        // Use smaller one of parent's viewPort and layoutParam max size.
        viewPort_ = GetLayoutParam().GetMaxSize();
    }
    Size layoutSize;
    const auto& children = GetChildren();
    if (!children.empty()) {
        auto child = children.front();
        auto layoutParamFromParent = GetLayoutParam();
        if (!passMinSize_) {
            // Common view not need to pass min size to child
            layoutParamFromParent.SetMinSize(Size());
        }
        child->Layout(layoutParamFromParent);
        child->SetPosition(Offset::Zero());
        layoutSize = child->GetLayoutSize();
    }
    SetLayoutSize(layoutSize);
}

} // namespace OHOS::Ace