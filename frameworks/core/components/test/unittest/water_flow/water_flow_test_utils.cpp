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

#include "core/components/test/unittest/water_flow/water_flow_test_utils.h"
#include "core/components_v2/water_flow/render_water_flow_item.h"
#include "core/components/box/box_component.h"

namespace OHOS::Ace {
RefPtr<Component> WaterFlowTestUtils::CreateComponent(FlexDirection direction, int32_t cols)
{
    std::list<RefPtr<Component>> children;
    Dimension RowGap = 50.0_px;
    Dimension ColumnsGap = 50.0_px;
    RefPtr<V2::WaterFlowComponent> component = AceType::MakeRefPtr<V2::WaterFlowComponent>(children, cols);
    component->SetRowsGap(RowGap);
    component->SetColumnsGap(ColumnsGap);
    component->SetLayoutDirection(direction);
    return component;
}

RefPtr<Component> WaterFlowTestUtils::CreateComponentItem(const int32_t& itemMainSpan, const int32_t& itemCrossSpan)
{
    RefPtr<BoxComponent> box = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<V2::WaterFlowItemComponent> ComponentItem = AceType::MakeRefPtr<V2::WaterFlowItemComponent>(box);
    auto flowItem = AceType::DynamicCast<V2::WaterFlowItemComponent>(ComponentItem);
    if (flowItem) {
        flowItem->SetRowSpan(itemMainSpan);
        flowItem->SetColumnSpan(itemCrossSpan);
        return flowItem;
    }
    return nullptr;
}

RefPtr<V2::RenderWaterFlowItem> WaterFlowTestUtils::CreateRenderItem(
    int32_t rowSpan, int32_t colSpan, int32_t index, const RefPtr<PipelineContext>& context)
{
    constexpr double DIM_SIZE_VALUE_TEST = 150.0;
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<RenderBox>();
    boxComponent->SetWidth(DIM_SIZE_VALUE_TEST);
    boxComponent->SetHeight(DIM_SIZE_VALUE_TEST);
    renderBox->Update(boxComponent);
    renderBox->Attach(context);
    RefPtr<V2::RenderWaterFlowItem> Renderitem = AceType::MakeRefPtr<V2::RenderWaterFlowItem>();
    if (Renderitem) {
        auto itemComponent = CreateComponentItem(rowSpan, colSpan);
        if (itemComponent) {
            Renderitem->Update(itemComponent);
            Renderitem->SetBoundary();
            Renderitem->SetIndex(index);
            Renderitem->Attach(context);
            Renderitem->SetHidden(false);
            Renderitem->AddChild(renderBox);
            return Renderitem;
        }
    }
    return nullptr;
}

RefPtr<RenderNode> WaterFlowTestUtils::CreateRenderItem(
    double width, double height, int32_t rowspan, int32_t colspan, const RefPtr<PipelineContext>& context)
{
    RefPtr<RenderBox> parent = AceType::MakeRefPtr<RenderBox>();
    RefPtr<V2::RenderWaterFlowItem> child = AceType::MakeRefPtr<V2::RenderWaterFlowItem>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<RenderBox>();
    parent->Attach(context);
    child->Attach(context);
    renderBox->Attach(context);
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    boxComponent->SetWidth(width);
    boxComponent->SetHeight(height);
    renderBox->Update(boxComponent);
    child->SetRowSpan(rowspan);
    child->SetColumnSpan(colspan);
    parent->AddChild(child);
    child->AddChild(renderBox);
    return parent;
}
} // namespace OHOS::Ace
