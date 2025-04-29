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

#include "bridge/declarative_frontend/jsview/models/grid_model_impl.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

void GridModelImpl::Create(
    const RefPtr<ScrollControllerBase>& positionController, const RefPtr<ScrollProxy>& scrollProxy)
{
    auto controller = AceType::DynamicCast<V2::GridPositionController>(positionController);
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::GridLayoutComponent> gridComponent = AceType::MakeRefPtr<GridLayoutComponent>(componentChildren);
    ViewStackProcessor::GetInstance()->ClaimElementId(gridComponent);
    gridComponent->SetDeclarative();
    gridComponent->SetNeedShrink(true);
    if (controller) {
        gridComponent->SetController(controller);
    }
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(scrollProxy);
    if (scrollBarProxy) {
        gridComponent->SetScrollBarProxy(scrollBarProxy);
    }

    if (Container::IsCurrentUsePartialUpdate()) {
        ViewStackProcessor::GetInstance()->PushGrid(gridComponent);
    } else {
        ViewStackProcessor::GetInstance()->Push(gridComponent);
    }
}

void GridModelImpl::Pop()
{
    ViewStackProcessor::GetInstance()->PopGrid();
}

void GridModelImpl::SetColumnsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetColumnsArgs(value);
}

void GridModelImpl::SetRowsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetRowsArgs(value);
}

void GridModelImpl::SetColumnsGap(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetColumnGap(value);
}

void GridModelImpl::SetRowsGap(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetRowGap(value);
}

void GridModelImpl::SetGridHeight(const Dimension& value)
{
    ViewAbstractModel::GetInstance()->SetHeight(value);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid && value.IsValid()) {
        grid->SetNeedShrink(false);
    }
}

void GridModelImpl::SetScrollBarMode(DisplayMode value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetScrollBar(value);
}

void GridModelImpl::SetScrollBarColor(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetScrollBarColor(value);
}

void GridModelImpl::SetScrollBarWidth(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetScrollBarWidth(value);
}

void GridModelImpl::SetCachedCount(int32_t value, bool show)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetCachedCount(value);
}

void GridModelImpl::SetIsRTL(TextDirection direction)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    bool isRtl;
    switch (direction) {
        case TextDirection::RTL:
            isRtl = true;
            break;
        case TextDirection::LTR:
            isRtl = false;
            break;
        default:
            isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    }
    grid->SetRightToLeft(isRtl);
}

void GridModelImpl::SetLayoutDirection(FlexDirection value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetDirection(value);
}

void GridModelImpl::SetMaxCount(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetMaxCount(value);
}

void GridModelImpl::SetMinCount(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetMinCount(value);
}

void GridModelImpl::SetCellLength(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetCellLength(value);
}

void GridModelImpl::SetEditable(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetEditMode(value);
}

void GridModelImpl::SetMultiSelectable(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetMultiSelectable(value);
}

void GridModelImpl::SetSupportAnimation(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetSupportAnimation(value);
}

void GridModelImpl::SetSupportDragAnimation(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetDragAnimation(value);
}

void GridModelImpl::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    CHECK_NULL_VOID(grid);
    grid->SetEdgeEffect(edgeEffect);
}

void GridModelImpl::SetOnScrollToIndex(std::function<void(const BaseEventInfo*)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    grid->SetScrolledEvent(EventMarker(std::move(value)));
}

void GridModelImpl::SetOnScrollBarUpdate(
    std::function<std::pair<std::optional<float>, std::optional<float>>(int32_t, Dimension)>&& value)
{}

void GridModelImpl::SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    auto onDragStart = [func = std::move(value)](const ItemDragInfo& dragInfo, int32_t index) -> RefPtr<Component> {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            func(dragInfo, index);
        }
        return ViewStackProcessor::GetInstance()->Finish();
    };
    grid->SetOnGridDragStartId(onDragStart);
}

void GridModelImpl::SetOnItemDragEnter(std::function<void(const ItemDragInfo&)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    grid->SetOnGridDragEnterId(value);
}

void GridModelImpl::SetOnItemDragMove(std::function<void(const ItemDragInfo&, int32_t, int32_t)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    grid->SetOnGridDragMoveId(value);
}

void GridModelImpl::SetOnItemDragLeave(std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    grid->SetOnGridDragLeaveId(value);
}

void GridModelImpl::SetOnItemDrop(std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>&& value)
{
    auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(grid);
    grid->SetOnGridDropId(value);
}

RefPtr<ScrollControllerBase> GridModelImpl::CreatePositionController()
{
    return AceType::MakeRefPtr<V2::GridPositionController>();
}

RefPtr<ScrollProxy> GridModelImpl::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<ScrollBarProxy>();
}

} // namespace OHOS::Ace::Framework
