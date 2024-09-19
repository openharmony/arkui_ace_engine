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

#include "core/components_v2/water_flow/water_flow_element.h"

#include "core/components_v2/water_flow/render_water_flow.h"
#include "core/components_v2/water_flow/water_flow_item_component.h"

namespace OHOS::Ace::V2 {
void WaterFlowElement::Update()
{
    RenderElement::Update();
    RefPtr<RenderWaterFlow> render = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (!render) {
        return;
    }
}

RefPtr<RenderNode> WaterFlowElement::CreateRenderNode()
{
    auto render = RenderElement::CreateRenderNode();
    RefPtr<RenderWaterFlow> renderWaterFlow = AceType::DynamicCast<RenderWaterFlow>(render);
    if (renderWaterFlow) {
        renderWaterFlow->SetBuildChildByIndex([weak = WeakClaim(this)](size_t index) {
            auto element = weak.Upgrade();
            if (!element) {
                return false;
            }
            return element->BuildChildByIndex(index);
        });

        renderWaterFlow->SetDeleteChildByIndex([weak = WeakClaim(this)](size_t index) {
            auto element = weak.Upgrade();
            if (!element) {
                return;
            }
            element->DeleteChildByIndex(index);
        });

        renderWaterFlow->SetGetTotalCount([weak = WeakClaim(this)]() {
            auto element = weak.Upgrade();
            if (!element) {
                return static_cast<size_t>(0);
            }
            return element->TotalCount();
        });
        renderWaterFlow->RegisterItemGenerator(AceType::WeakClaim(static_cast<WaterFlowItemGenerator*>(this)));
    }
    return render;
}

void WaterFlowElement::PerformBuild()
{
    auto component = AceType::DynamicCast<V2::WaterFlowComponent>(component_);
    ACE_DCHECK(component); // MUST be WaterFlowComponent
    V2::ElementProxyHost::UpdateChildren(component->GetChildren());
    footerElement_ = UpdateChild(footerElement_, component->GetFooterComponent());
}

RefPtr<RenderNode> WaterFlowElement::RequestWaterFlowFooter()
{
    return footerElement_ ? AceType::DynamicCast<RenderNode>(footerElement_->GetRenderNode()) : nullptr;
}

bool WaterFlowElement::BuildChildByIndex(size_t index)
{
    if (index < 0) {
        return false;
    }
    auto element = GetElementByIndex(index);
    if (!element) {
        LOGE("GetElementByIndex failed index=[%{public}zu]", index);
        return false;
    }
    auto renderNode = element->GetRenderNode();
    if (!renderNode) {
        LOGE("GetRenderNode failed");
        return false;
    }
    RefPtr<RenderWaterFlow> waterFlow = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (!waterFlow) {
        return false;
    }
    waterFlow->AddChildByIndex(index, renderNode);
    return true;
}

void WaterFlowElement::DeleteChildByIndex(size_t index)
{
    ReleaseElementByIndex(index);
}

void WaterFlowElement::ApplyRenderChild(const RefPtr<RenderElement>& renderChild)
{
    if (!renderChild) {
        LOGE("Element child is null");
        return;
    }

    if (!renderNode_) {
        LOGE("RenderElement don't have a render node");
        return;
    }
    renderNode_->AddChild(renderChild->GetRenderNode());
}

RefPtr<Element> WaterFlowElement::OnUpdateElement(const RefPtr<Element>& element, const RefPtr<Component>& component)
{
    return UpdateChild(element, component);
}

RefPtr<Component> WaterFlowElement::OnMakeEmptyComponent()
{
    return AceType::MakeRefPtr<WaterFlowItemComponent>();
}

void WaterFlowElement::OnDataSourceUpdated(size_t startIndex)
{
    auto context = context_.Upgrade();
    if (context) {
        context->AddPostFlushListener(AceType::Claim(this));
    }

    RefPtr<RenderWaterFlow> render = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (render) {
        render->OnDataSourceUpdated(startIndex);
        render->SetTotalCount(ElementProxyHost::TotalCount());
    }
    ElementProxyHost::OnDataSourceUpdated(startIndex);
}

size_t WaterFlowElement::TotalCount()
{
    return ElementProxyHost::TotalCount();
}

void WaterFlowElement::OnPostFlush()
{
    ReleaseRedundantComposeIds();
}

void WaterFlowElement::Dump()
{
    DumpProxy();
}
} // namespace OHOS::Ace::V2
