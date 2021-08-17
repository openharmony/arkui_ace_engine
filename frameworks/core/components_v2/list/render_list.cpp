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

#include "core/components_v2/list/render_list.h"

#include "base/log/log.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::V2 {
namespace {

constexpr double VIEW_PORT_SCALE = 3.0;

} // namespace

void RenderList::Update(const RefPtr<Component>& component)
{
    component_ = AceType::DynamicCast<ListComponent>(component);
    ACE_DCHECK(component_);

    RemoveAllItems();

    auto axis = component_->GetDirection();
    vertical_ = axis == Axis::VERTICAL;

    // Start index should be updated only for the first time
    if (startIndex_ == INITIAL_CHILD_INDEX) {
        auto initialIndex = component_->GetInitialIndex();
        startIndex_ = initialIndex > 0 ? initialIndex : 0;
    }

    const auto& divider = component_->GetItemDivider();
    spaceWidth_ = std::max(NormalizePercentToPx(component_->GetSpace(), vertical_),
        divider ? NormalizePercentToPx(divider->strokeWidth, vertical_) : 0.0);

    if (scrollable_) {
        scrollable_->SetAxis(axis);
    } else {
        auto callback = [weak = AceType::WeakClaim(this)](double offset, int32_t source) {
            auto renderList = weak.Upgrade();
            return renderList ? renderList->UpdateScrollPosition(offset, source) : false;
        };
        scrollable_ = AceType::MakeRefPtr<Scrollable>(callback, axis);
        scrollable_->Initialize(context_);
    }
    auto controller = component_->GetScrollController();
    if (controller) {
        controller->SetScrollNode(AceType::WeakClaim(this));
    }

    MarkNeedLayout();
}

void RenderList::PerformLayout()
{
    // Check validation of layout size
    const double mainSize = ApplyLayoutParam();
    if (NearZero(mainSize)) {
        LOGW("Cannot layout using invalid view port");
        return;
    }

    const auto innerLayout = MakeInnerLayout();
    double curMainPos = LayoutOrRecycleCurrentItems(innerLayout);

    // Try to request new items at end if needed
    for (size_t newIndex = startIndex_ + items_.size(); curMainPos < endMainPos_; ++newIndex) {
        auto child = RequestAndLayoutNewItem(newIndex, innerLayout);
        if (!child) {
            startIndex_ = std::min(startIndex_, TotalCount());
            break;
        }
        curMainPos += GetMainSize(child->GetLayoutSize()) + spaceWidth_;
    }

    // Check if reach the end of list
    reachEnd_ = LessOrEqual(curMainPos, mainSize);
    if (reachEnd_) {
        // Adjust end of list to match the end of layout
        currentOffset_ += mainSize - curMainPos;
    }

    // Try to request new items at start if needed
    for (; currentOffset_ > startMainPos_ && startIndex_ > 0; --startIndex_) {
        auto child = RequestAndLayoutNewItem(startIndex_ - 1, innerLayout);
        if (!child) {
            break;
        }
        currentOffset_ -= GetMainSize(child->GetLayoutSize()) + spaceWidth_;
    }

    // Check if reach the start of list
    reachStart_ = GreatOrEqual(currentOffset_, 0.0);
    if (reachStart_) {
        // Adjust start of list to match the start of layout
        currentOffset_ = 0.0;
    }

    // Set position for each child
    auto layoutSize = SetItemsPosition(mainSize, innerLayout);

    // Set layout size of list component itself
    SetLayoutSize(GetLayoutParam().Constrain(layoutSize));
}

Size RenderList::SetItemsPosition(double mainSize, const LayoutParam& layoutParam)
{
    double crossSize = fixedCrossSize_ ? GetCrossSize(GetLayoutParam().GetMaxSize()) : 0.0;
    if (items_.empty()) {
        return MakeValue<Size>(fixedMainSize_ ? mainSize : 0.0, crossSize);
    }

    double curMainPos = currentOffset_;
    size_t index = startIndex_;
    size_t newStickyIndex = 0;
    RefPtr<RenderListItem> newStickyItem;
    RefPtr<RenderListItem> nextStickyItem;
    double nextStickyMainAxis = Size::INFINITE_SIZE;
    size_t firstIdx = INITIAL_CHILD_INDEX;
    size_t lastIdx = 0;
    for (const auto& child : items_) {
        child->SetPosition(MakeValue<Offset>(curMainPos, 0.0));
        // Disable sticky mode while expand all items
        if (fixedMainSize_ && child->GetSticky() != StickyMode::NONE) {
            if (LessOrEqual(curMainPos, 0.0)) {
                newStickyItem = child;
                newStickyIndex = index;
            } else if (!nextStickyItem) {
                nextStickyItem = child;
                nextStickyMainAxis = curMainPos;
            }
        }

        const auto& childLayoutSize = child->GetLayoutSize();
        double childMainSize = GetMainSize(childLayoutSize) + spaceWidth_;
        if (LessNotEqual(curMainPos, mainSize) && GreatNotEqual(curMainPos + childMainSize, 0.0)) {
            if (!fixedCrossSize_) {
                crossSize = std::max(crossSize, GetCrossSize(childLayoutSize));
            }
            firstIdx = std::min(firstIdx, index);
            lastIdx = std::max(lastIdx, index);
        }

        curMainPos += childMainSize;
        ++index;
    }
    if (firstIdx != firstDisplayIndex_ || lastIdx != lastDisplayIndex_) {
        firstDisplayIndex_ = firstIdx;
        lastDisplayIndex_ = lastIdx;
        ResumeEventCallback(component_, &ListComponent::GetOnScrollIndex, static_cast<int32_t>(firstDisplayIndex_),
            static_cast<int32_t>(lastDisplayIndex_));
    }

    // Disable sticky mode while expand all items
    if (!fixedMainSize_) {
        return MakeValue<Size>(curMainPos - spaceWidth_, crossSize);
    }

    UpdateStickyListItem(newStickyItem, newStickyIndex, nextStickyItem, layoutParam);
    if (currentStickyItem_) {
        const auto& stickyItemLayoutSize = currentStickyItem_->GetLayoutSize();
        const double mainStickySize = GetMainSize(stickyItemLayoutSize) + spaceWidth_;
        if (nextStickyItem && LessNotEqual(nextStickyMainAxis, mainStickySize)) {
            currentStickyItem_->SetPosition(MakeValue<Offset>(nextStickyMainAxis - mainStickySize, 0.0));
        } else {
            currentStickyItem_->SetPosition(MakeValue<Offset>(0.0, 0.0));
        }

        if (!fixedCrossSize_) {
            crossSize = std::max(crossSize, GetCrossSize(stickyItemLayoutSize));
        }
    }

    return MakeValue<Size>(mainSize, crossSize);
}

void RenderList::UpdateStickyListItem(const RefPtr<RenderListItem>& newStickyItem, size_t newStickyItemIndex,
    const RefPtr<RenderListItem>& nextStickyItem, const LayoutParam& layoutParam)
{
    if (newStickyItem) {
        if (newStickyItem == currentStickyItem_) {
            return;
        }

        if (currentStickyItem_ && currentStickyIndex_ < startIndex_) {
            RecycleListItem(currentStickyIndex_);
            RemoveChild(currentStickyItem_);
        }

        currentStickyItem_ = newStickyItem;
        currentStickyIndex_ = newStickyItemIndex;
        return;
    }

    if (nextStickyItem && nextStickyItem == currentStickyItem_) {
        ApplyPreviousStickyListItem(currentStickyIndex_ - 1, true, layoutParam);
        return;
    }

    if (currentStickyIndex_ == INITIAL_CHILD_INDEX && startIndex_ > 0) {
        ApplyPreviousStickyListItem(startIndex_ - 1, true, layoutParam);
    }
}

LayoutParam RenderList::MakeInnerLayout()
{
    Size maxSize;
    Size minSize;
    if (vertical_) {
        maxSize = Size(GetLayoutParam().GetMaxSize().Width(), Size::INFINITE_SIZE);
        minSize = Size(GetLayoutParam().GetMinSize().Width(), 0.0);
    } else {
        maxSize = Size(Size::INFINITE_SIZE, GetLayoutParam().GetMaxSize().Height());
        minSize = Size(0.0, GetLayoutParam().GetMinSize().Height());
    }
    return LayoutParam(maxSize, minSize);
}

bool RenderList::UpdateScrollPosition(double offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }

    if (NearZero(offset)) {
        return true;
    }

    if (reachStart_ && reachEnd_) {
        return false;
    }

    if (offset > 0.0) {
        if (reachStart_) {
            return false;
        }
        reachEnd_ = false;
    } else {
        if (reachEnd_) {
            return false;
        }
        reachStart_ = false;
    }

    currentOffset_ += offset;
    MarkNeedLayout();
    return true;
}

void RenderList::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible()) {
        return;
    }
    // Disable scroll while expand all items
    if (!fixedMainSize_) {
        return;
    }
    if (!scrollable_ || !scrollable_->Available()) {
        return;
    }

    TouchRestrict newTouchRestrict = touchRestrict;
    if (reachStart_) {
        newTouchRestrict.UpdateForbiddenType(vertical_ ? TouchRestrict::SWIPE_DOWN : TouchRestrict::SWIPE_RIGHT);
    }
    if (reachEnd_) {
        newTouchRestrict.UpdateForbiddenType(vertical_ ? TouchRestrict::SWIPE_UP : TouchRestrict::SWIPE_LEFT);
    }

    scrollable_->SetCoordinateOffset(coordinateOffset);
    scrollable_->SetDragTouchRestrict(newTouchRestrict);
    result.emplace_back(scrollable_);
}

double RenderList::ApplyLayoutParam()
{
    auto maxLayoutSize = GetLayoutParam().GetMaxSize();
    if (!maxLayoutSize.IsValid() || maxLayoutSize.IsEmpty()) {
        return 0.0;
    }

    auto maxMainSize = GetMainSize(maxLayoutSize);

    // Update layout info for list weather layout param is changed
    if (IsLayoutParamChanged()) {
        // Minimum layout param MUST NOT be INFINITE
        ACE_DCHECK(!GetLayoutParam().GetMinSize().IsInfinite());

        if (NearEqual(maxMainSize, Size::INFINITE_SIZE)) {
            // Clear all child items
            RemoveAllItems();
            startIndex_ = 0;
            currentOffset_ = 0.0;

            startMainPos_ = 0.0;
            endMainPos_ = std::numeric_limits<decltype(endMainPos_)>::max();
            fixedMainSize_ = false;
        } else {
            startMainPos_ = -maxMainSize;
            endMainPos_ = startMainPos_ + (maxMainSize * VIEW_PORT_SCALE);
            fixedMainSize_ = true;
        }

        fixedCrossSize_ = !NearEqual(GetCrossSize(maxLayoutSize), Size::INFINITE_SIZE);
        TakeBoundary(fixedMainSize_ && fixedCrossSize_);
    }

    return maxMainSize;
}

double RenderList::LayoutOrRecycleCurrentItems(const LayoutParam& layoutParam)
{
    if (currentStickyItem_) {
        currentStickyItem_->Layout(layoutParam);
    }

    double curMainPos = currentOffset_;
    size_t curIndex = startIndex_;
    for (auto it = items_.begin(); it != items_.end(); ++curIndex) {
        const auto& child = *(it);
        if (LessOrEqual(curMainPos, endMainPos_)) {
            child->Layout(layoutParam);
            double mainSize = GetMainSize(child->GetLayoutSize());
            curMainPos += mainSize + spaceWidth_;
            if (GreatOrEqual(curMainPos, startMainPos_)) {
                ++it;
                continue;
            }
            currentOffset_ = curMainPos;
            startIndex_ = curIndex + 1;
        }

        if (currentStickyItem_ != child) {
            // Recycle list items out of view port
            RecycleListItem(curIndex);
            RemoveChild(child);
        }
        it = items_.erase(it);
    }
    return curMainPos;
}

RefPtr<RenderListItem> RenderList::RequestAndLayoutNewItem(size_t index, const LayoutParam& layoutParam)
{
    RefPtr<RenderListItem> newChild;
    if (index == currentStickyIndex_ && currentStickyItem_) {
        newChild = currentStickyItem_;
    } else {
        newChild = RequestListItem(index);
        if (newChild) {
            AddChild(newChild);
            newChild->Layout(layoutParam);
        }
    }

    if (newChild) {
        if (index < startIndex_) {
            items_.emplace_front(newChild);
        } else {
            items_.emplace_back(newChild);
        }
    }
    return newChild;
}

RefPtr<RenderListItem> RenderList::RequestListItem(size_t index)
{
    auto generator = itemGenerator_.Upgrade();
    auto newItem = generator ? generator->RequestListItem(index) : RefPtr<RenderListItem>();
    if (newItem && component_->GetEditMode()) {
        newItem->SetEditMode(true);
        newItem->SetOnDeleteClick([weak = AceType::WeakClaim(this)](RefPtr<RenderListItem> item) {
            auto spThis = weak.Upgrade();
            if (!spThis) {
                return;
            }
            spThis->OnItemDelete(item);
        });
    }
    return newItem;
}

void RenderList::RecycleListItem(size_t index, bool forceDelete)
{
    auto generator = itemGenerator_.Upgrade();
    if (generator) {
        generator->RecycleListItem(index, forceDelete);
    }
}

size_t RenderList::TotalCount()
{
    auto generator = itemGenerator_.Upgrade();
    return generator ? generator->TotalCount() : 0;
}

size_t RenderList::FindPreviousStickyListItem(size_t index)
{
    auto generator = itemGenerator_.Upgrade();
    return generator ? generator->FindPreviousStickyListItem(index) : ListItemGenerator::INVALID_INDEX;
}

void RenderList::OnItemDelete(const RefPtr<RenderListItem>& item)
{
    ACE_DCHECK(item);

    size_t index = 0;
    auto it = std::find(items_.begin(), items_.end(), item);
    if (it != items_.end()) {
        int32_t offset = std::distance(items_.begin(), it);
        ACE_DCHECK(offset >= 0);
        index = startIndex_ + offset;
    } else {
        ACE_DCHECK(fixedMainSize_);
        ACE_DCHECK(item == currentStickyItem_);
        index = currentStickyIndex_;
    }

    if (!ResumeEventCallback(component_, &ListComponent::GetOnItemDelete, true, static_cast<int32_t>(index))) {
        LOGI("Stop deleting item");
        return;
    }

    if (index == currentStickyIndex_) {
        ApplyPreviousStickyListItem(index - 1);
    }

    RecycleListItem(index, true);
    RemoveChild(item);
    if (it != items_.end()) {
        items_.erase(it);
    }

    if (index < startIndex_) {
        --startIndex_;
    }

    MarkNeedLayout();
}

void RenderList::RemoveAllItems()
{
    items_.clear();
    ClearChildren();
    currentStickyItem_.Reset();
    currentStickyIndex_ = INITIAL_CHILD_INDEX;
}

void RenderList::ApplyPreviousStickyListItem(size_t index, bool needLayout, const LayoutParam& layoutParam)
{
    size_t newIndex = FindPreviousStickyListItem(index);
    if (newIndex == ListItemGenerator::INVALID_INDEX) {
        currentStickyItem_.Reset();
        currentStickyIndex_ = INVALID_CHILD_INDEX;
        return;
    }

    currentStickyIndex_ = newIndex;
    currentStickyItem_ = RequestListItem(currentStickyIndex_);
    if (currentStickyIndex_ < startIndex_) {
        AddChild(currentStickyItem_);
        if (needLayout) {
            currentStickyItem_->Layout(layoutParam);
        }
    }
}

void RenderList::JumpToIndex(int32_t idx, int32_t source)
{
    RemoveAllItems();
    startIndex_ = idx;
    currentOffset_ = 0.0;
    MarkNeedLayout();
}

void RenderList::UpdateTouchRect()
{
    touchRect_.SetSize(GetLayoutSize());
    touchRect_.SetOffset(GetPosition());
    ownTouchRect_ = touchRect_;
}

} // namespace OHOS::Ace::V2
