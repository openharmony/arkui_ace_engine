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

#include "bridge/declarative_frontend/jsview/models/grid_item_model_impl.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/grid_layout/grid_layout_item_component.h"

namespace OHOS::Ace::Framework {

void GridItemModelImpl::Create(NG::GridItemStyle gridItemStyle)
{
    auto itemComponent = AceType::MakeRefPtr<GridLayoutItemComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(itemComponent);
    ViewStackProcessor::GetInstance()->Push(itemComponent);
}

void GridItemModelImpl::Create(
    std::function<void(int32_t)>&& deepRenderFunc, bool isLazy, NG::GridItemStyle gridItemStyle)
{
    auto itemComponent = AceType::MakeRefPtr<GridLayoutItemComponent>();
    DeepRenderFunc gridItemDeepRenderFunc = [func = std::move(deepRenderFunc),
                                                id = itemComponent->GetElementId()]() -> RefPtr<Component> {
        CHECK_NULL_RETURN(func, nullptr);
        func(id);
        return ViewStackProcessor::GetInstance()->Finish();
    };
    ViewStackProcessor::GetInstance()->ClaimElementId(itemComponent);
    ViewStackProcessor::GetInstance()->Push(itemComponent);
    itemComponent->SetDeepRenderFunc(gridItemDeepRenderFunc);
    itemComponent->SetIsLazyCreating(isLazy);
}

void GridItemModelImpl::SetRowStart(int32_t value)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetRowIndex(std::max(value, 0));
}

void GridItemModelImpl::SetRowEnd(int32_t value)
{
    // row end must be set after start. loader needs to make the method in order.
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetRowSpan(std::max(value, 0) - gridItem->GetRowIndex() + 1);
}

void GridItemModelImpl::SetColumnStart(int32_t value)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetColumnIndex(std::max(value, 0));
}

void GridItemModelImpl::SetColumnEnd(int32_t value)
{
    // column end must be set after start. loader needs to make the method in order.
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetColumnSpan(std::max(value, 0) - gridItem->GetColumnIndex() + 1);
}

void GridItemModelImpl::SetForceRebuild(bool value)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetForceRebuild(value);
}

void GridItemModelImpl::SetSelectable(bool value)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetSelectable(value);
}

void GridItemModelImpl::SetOnSelect(std::function<void(bool)>&& onSelect)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(gridItem);
    gridItem->SetOnSelectId(onSelect);
}

} // namespace OHOS::Ace::Framework
