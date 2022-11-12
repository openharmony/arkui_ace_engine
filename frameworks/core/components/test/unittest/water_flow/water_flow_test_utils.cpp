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

#include "core/components/box/box_component.h"
#include "core/components/box/render_box.h"
#include "core/components/test/unittest/water_flow/water_flow_test_utils.h"

namespace OHOS::Ace {
Dimension WaterFlowTestUtils::rowGap = 100.0_px;
Dimension WaterFlowTestUtils::columnsGap = 100.0_px;
RefPtr<Component>  WaterFlowTestUtils::CreateComponent(std::string columnsArgs,
    std::string rowsArgs, FlexDirection direction)
{
    std::list<RefPtr<Component>> children;
    RefPtr<V2::WaterFlowComponent> component = AceType::MakeRefPtr<V2::WaterFlowComponent>(children);
    if (component) {
        component->SetRowsGap(rowGap);
        component->SetColumnsGap(columnsGap);
        component->SetLayoutDirection(direction);
        component->SetColumnsArgs(columnsArgs);
        component->SetRowsArgs(rowsArgs);
    }
    return component;
}

RefPtr<V2::RenderWaterFlowItem> WaterFlowTestUtils::CreateRenderItem(const RefPtr<PipelineContext>& context)
{
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<RenderBox>();
    boxComponent->SetWidth(ITEM_WIDTH);
    boxComponent->SetHeight(ITEM_HEIGHT);
    renderBox->Update(boxComponent);
    renderBox->Attach(context);
    RefPtr<V2::RenderWaterFlowItem> renderWaterflowItem = AceType::MakeRefPtr<V2::RenderWaterFlowItem>();
    if (renderWaterflowItem) {
        renderWaterflowItem->Attach(context);
        renderWaterflowItem->AddChild(renderBox);
    }
    return renderWaterflowItem;
}
} // namespace OHOS::Ace
