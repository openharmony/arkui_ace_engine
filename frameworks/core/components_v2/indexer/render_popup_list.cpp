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

#include "core/components_v2/indexer/render_popup_list.h"

#include "base/log/log.h"
#include "core/animation/bilateral_spring_node.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/scroll/render_scroll.h"
#include "core/components/scroll/render_single_child_scroll.h"
#include "core/components/scroll/scroll_spring_effect.h"
#include "core/components_v2/indexer/popup_list_component.h"
#include "core/components_v2/indexer/popup_list_item_component.h"

namespace OHOS::Ace::V2 {
RefPtr<RenderNode> RenderPopupList::Create()
{
    return AceType::MakeRefPtr<RenderPopupList>();
}

void RenderPopupList::Update(const RefPtr<Component>& component)
{
    component_ = AceType::DynamicCast<PopupListComponent>(component);
    ACE_DCHECK(component_);

    auto axis = component_->GetDirection();
    vertical_ = axis == Axis::VERTICAL;

    popupSelectedEventFun_ = AceAsyncEvent<void(const std::shared_ptr<IndexerEventInfo>&)>::
        Create(component_->GetPopupSelectedEvent(), context_);

    MarkNeedLayout();
}

void RenderPopupList::PerformLayout()
{
    // set the position of children
    LayoutParam childrenLayout;
    childrenLayout.SetMinSize(Size(0.0, 0.0));
    Offset position;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    for (const auto& item : GetChildren()) {
        if (!AceType::InstanceOf<RenderPopupListItem>(item)) {
            continue;
        }
        position.SetX(0.0);
        position.SetY(y);
        item->Layout(childrenLayout);
        item->SetPosition(position);

        width = item->GetLayoutSize().Width();
        height += item->GetLayoutSize().Height();
        y += item->GetLayoutSize().Height();
    }

    // Set layout size of list component itself
    Size layoutSizeAfterConstrain = GetLayoutParam().Constrain(Size(width, height));
    SetLayoutSize(layoutSizeAfterConstrain);
}

bool RenderPopupList::TouchTest(const Point& globalPoint, const Point& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (GetDisableTouchEvent() || disabled_) {
        return false;
    }

    // calculate touch point in which item.
    CalTouchPoint(globalPoint, popupSelected_);

    // call js function
    OnPopupSelected(popupSelected_);

    return true;
}

void RenderPopupList::OnRequestPopupDataSelected(std::vector<std::string>& data)
{
    if (!GetChildren().empty()) {
        ClearChildren();
    }
    listItem_.clear();

    for (size_t index = 0; index < data.size() && index < MAX_POPUP_DATA_COUNT; index++) {
        RefPtr<PopupListItemComponent> itemComponent = AceType::MakeRefPtr<PopupListItemComponent>(data[index]);
        auto renderItem = AceType::DynamicCast<RenderPopupListItem>(RenderPopupListItem::Create());
        AddChild(renderItem);
        renderItem->Attach(GetContext());
        renderItem->Update(itemComponent);
        listItem_.push_back(renderItem);
    }
}

void RenderPopupList::CalTouchPoint(const Point& globalPoint, int32_t& selected)
{
    selected = INVALID_POPUP_SELECTED;
    std::list<RefPtr<RenderPopupListItem>>::iterator iter;
    int32_t index = 0;
    for (iter = listItem_.begin(); iter != listItem_.end(); iter++) {
        auto renderItem = *iter;
        std::unique_ptr<Rect> rect = std::make_unique<Rect>(renderItem->GetGlobalOffset(),
                                                            renderItem->GetPaintRect().GetSize());
        if (rect->IsInRegion(globalPoint)) {
            selected = index;
            renderItem->UpdateBoxSelected();
        } else {
            renderItem->UpdateBoxNormal();
        }
        index++;
    }
}

void RenderPopupList::OnPopupSelected(int32_t selected) const
{
    if (popupSelectedEventFun_) {
        auto event = std::make_shared<IndexerEventInfo>(selected);
        if (event) {
            popupSelectedEventFun_(event);
        }
    }
}
} // namespace OHOS::Ace::V2
