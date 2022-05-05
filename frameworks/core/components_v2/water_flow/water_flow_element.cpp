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

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components/proxy/render_item_proxy.h"
#include "core/components_v2/water_flow/render_water_flow.h"
#include "core/components_v2/water_flow/water_flow_component.h"
#include "core/components_v2/water_flow/water_flow_item_component.h"

namespace OHOS::Ace::V2 {
void WaterFlowElement::Update()
{
    RenderElement::Update();
    RefPtr<RenderWaterFlow> render = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (!render) {
        return;
    }
    render->OnDataSourceUpdated(0);
}

RefPtr<RenderNode> WaterFlowElement::CreateRenderNode()
{
    auto render = RenderElement::CreateRenderNode();
    RefPtr<RenderWaterFlow> renderWaterFlow = AceType::DynamicCast<RenderWaterFlow>(render);
    if (renderWaterFlow) {
        renderWaterFlow->SetBuildChildByIndex([weak = WeakClaim(this)](int32_t index) {
            auto element = weak.Upgrade();
            if (!element) {
                return false;
            }
            return element->BuildChildByIndex(index);
        });

        renderWaterFlow->SetDeleteChildByIndex([weak = WeakClaim(this)](int32_t index) {
            auto element = weak.Upgrade();
            if (!element) {
                return;
            }
            element->DeleteChildByIndex(index);
        });

        renderWaterFlow->SetGetChildSpanByIndex(
            [weak = WeakClaim(this)](int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan) {
                auto element = weak.Upgrade();
                if (!element) {
                    return false;
                }
                return element->GetItemSpanByIndex(index, isHorizontal, itemMainSpan, itemCrossSpan);
            });
    }

    return render;
}

void WaterFlowElement::PerformBuild()
{
    auto component = AceType::DynamicCast<V2::WaterFlowComponent>(component_);
    ACE_DCHECK(component); // MUST be WaterFlowComponent
    V2::ElementProxyHost::UpdateChildren(component->GetChildren());
}

bool WaterFlowElement::BuildChildByIndex(int32_t index)
{
    if (index < 0) {
        return false;
    }
    auto element = GetElementByIndex(index);
    if (!element) {
        LOGE("GetElementByIndex failed index=[%d]", index);
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

bool WaterFlowElement::GetItemSpanByIndex(
    int32_t index, bool isHorizontal, int32_t& itemMainSpan, int32_t& itemCrossSpan)
{
    if (index < 0) {
        return false;
    }
    auto component = GetComponentByIndex(index);
    auto flowItem = AceType::DynamicCast<WaterFlowItemComponent>(component);

    if (!flowItem) {
        return false;
    }
    if (isHorizontal) {
        itemMainSpan = flowItem->GetColumnSpan();
        itemCrossSpan = flowItem->GetRowSpan();
    } else {
        itemMainSpan = flowItem->GetRowSpan();
        itemCrossSpan = flowItem->GetColumnSpan();
    }
    return true;
}

void WaterFlowElement::DeleteChildByIndex(int32_t index)
{
    ReleaseElementByIndex(index);
}

bool WaterFlowElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    RefPtr<RenderWaterFlow> waterFlow = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (!waterFlow) {
        LOGE("Render waterFlow is null.");
        return false;
    }
    LOGI("RequestNextFocus vertical:%{public}d reverse:%{public}d.", vertical, reverse);
    bool ret = false;
    while (!ret) {
        int32_t focusIndex = waterFlow->RequestNextFocus(vertical, reverse);
        int32_t size = GetChildrenList().size();
        if (focusIndex < 0 || focusIndex >= size) {
            return false;
        }
        auto iter = GetChildrenList().begin();
        std::advance(iter, focusIndex);
        auto focusNode = *iter;
        if (!focusNode) {
            LOGE("Target focus node is null.");
            return false;
        }
        // If current Node can not obtain focus, move to next.
        ret = focusNode->RequestFocusImmediately();
    }
    return ret;
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
    if (!render) {
        return;
    }
    render->OnDataSourceUpdated(static_cast<int32_t>(startIndex));
    render->SetTotalCount(ElementProxyHost::TotalCount());
}

void WaterFlowElement::OnPostFlush()
{
    ReleaseRedundantComposeIds();
}

size_t WaterFlowElement::GetReloadedCheckNum()
{
    RefPtr<RenderWaterFlow> render = AceType::DynamicCast<RenderWaterFlow>(renderNode_);
    if (render) {
        size_t cachedNum = render->GetCachedSize();
        if (cachedNum > 0) {
            return cachedNum;
        }
    }
    return ElementProxyHost::GetReloadedCheckNum();
}

void WaterFlowElement::Dump()
{
    DumpProxy();
}
} // namespace OHOS::Ace::V2
