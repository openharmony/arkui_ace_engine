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
#include "core/animation/bilateral_spring_node.h"
#include "core/components/scroll/render_scroll.h"
#include "core/components/scroll/render_single_child_scroll.h"
#include "core/components/scroll/scroll_spring_effect.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::V2 {
namespace {

constexpr double VIEW_PORT_SCALE = 3.0;
constexpr int32_t CHAIN_ANIMATION_NODE_COUNT = 30;
constexpr int32_t DEFAULT_SOURCE = 3;
constexpr int32_t SCROLL_STATE_IDLE = 0;
constexpr int32_t SCROLL_STATE_SCROLL = 1;
constexpr int32_t SCROLL_STATE_FLING = 2;

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

            if (!renderList) {
                return false;
            }

            if (source == SCROLL_FROM_START) {
                renderList->ProcessDragStart(offset);
                return true;
            }

            Offset delta;
            if (renderList->vertical_) {
                delta.SetX(0.0);
                delta.SetY(offset);
            } else {
                delta.SetX(offset);
                delta.SetY(0.0);
            }
            renderList->AdjustOffset(delta, source);
            renderList->processDragUpdate(renderList->GetMainAxis(delta));
            return renderList->UpdateScrollPosition(renderList->GetMainAxis(delta), source);
        };
        scrollable_ = AceType::MakeRefPtr<Scrollable>(callback, axis);
        scrollable_->SetNotifyScrollOverCallBack([weak = AceType::WeakClaim(this)](double velocity) {
            auto list = weak.Upgrade();
            if (!list) {
                return;
            }
            list->ProcessScrollOverCallback(velocity);
        });
        scrollable_->Initialize(context_);
    }
    // now only support spring
    if (component_->GetEdgeEffect() == EdgeEffect::SPRING) {
        if (!scrollEffect_ || scrollEffect_->GetEdgeEffect() != EdgeEffect::SPRING) {
            scrollEffect_ = AceType::MakeRefPtr<ScrollSpringEffect>();
            ResetEdgeEffect();
        }
    } else {
        scrollEffect_ = nullptr;
    }

    auto controller = component_->GetScrollController();
    if (controller) {
        controller->SetScrollNode(AceType::WeakClaim(this));
    }

    // chainAnimation
    if (chainAnimation_ != component_->GetChainAnimation()) {
        chainAnimation_ = component_->GetChainAnimation();
        if (chainAnimation_) {
            InitChainAnimation(CHAIN_ANIMATION_NODE_COUNT);
            overSpringProperty_ = SpringChainProperty::GetDefaultOverSpringProperty();
        } else {
            overSpringProperty_ = nullptr;
            chain_ = nullptr;
            chainAdapter_ = nullptr;
        }
    }

    if (chainAnimation_) {
        // add chain interval length
        spaceWidth_ += NormalizeToPx(chainProperty_.Interval());
    }

    MarkNeedLayout();
}

void RenderList::PerformLayout()
{
    UpdateAccessibilityAttr();
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

    if (selectedItem_ && selectedItemIndex_ < startIndex_) {
        curMainPos += GetMainSize(selectedItem_->GetLayoutSize()) + spaceWidth_;
    }

    curMainPos -= spaceWidth_;

    // Check if reach the end of list
    reachEnd_ = LessOrEqual(curMainPos, mainSize);
    bool noEdgeEffect =
        (scrollable_ && scrollable_->IsAnimationNotRunning()) || !scrollEffect_ || autoScrollingForItemMove_;
    if (noEdgeEffect && reachEnd_) {
        // Adjust end of list to match the end of layout
        currentOffset_ += mainSize - curMainPos;
        curMainPos = mainSize;
    }

    // Try to request new items at start if needed
    for (; currentOffset_ > startMainPos_ && startIndex_ > 0; --startIndex_) {
        auto child = RequestAndLayoutNewItem(startIndex_ - 1, innerLayout);
        if (!child) {
            break;
        }
        if (selectedItemIndex_ == startIndex_) {
            continue;
        }
        currentOffset_ -= GetMainSize(child->GetLayoutSize()) + spaceWidth_;
    }

    // Check if reach the start of list
    reachStart_ = GreatOrEqual(currentOffset_, 0.0);
    if (noEdgeEffect && reachStart_) {
        curMainPos -= currentOffset_;
        currentOffset_ = 0;
    }

    if (!fixedMainSize_) {
        fixedMainSize_ = !(reachStart_ && reachEnd_);
    }
    // Check if disable or enable scrollable
    CalculateMainScrollExtent(curMainPos, mainSize);

    // Set position for each child
    auto layoutSize = SetItemsPosition(mainSize, innerLayout);

    // Set layout size of list component itself
    SetLayoutSize(GetLayoutParam().Constrain(layoutSize));

    // Clear auto scrolling flags
    autoScrollingForItemMove_ = false;
    if (scrollable_ && scrollable_->Idle()) {
        ResumeEventCallback(component_, &ListComponent::GetOnScroll, Dimension(offset_ / dipScale_, DimensionUnit::VP),
            ScrollState(SCROLL_STATE_IDLE));
    }
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
    double selectedItemMainSize = selectedItem_ ? GetMainSize(selectedItem_->GetLayoutSize()) : 0.0;

    for (const auto& child : items_) {
        const auto& childLayoutSize = child->GetLayoutSize();
        double childMainSize = GetMainSize(childLayoutSize);

        if (selectedItem_) {
            double range = std::min(selectedItemMainSize, childMainSize) / 2.0;
            bool beforeSelectedItem = index <= selectedItemIndex_;
            if (beforeSelectedItem && targetIndex_ == index) {
                targetMainAxis_ = curMainPos;
                curMainPos += selectedItemMainSize + spaceWidth_;
            }

            if (movingForward_) {
                double axis = selectedItemMainAxis_;
                if (GreatOrEqual(axis, curMainPos) && LessNotEqual(axis, curMainPos + range)) {
                    targetIndex_ = beforeSelectedItem ? index : index - 1;
                    targetMainAxis_ = curMainPos;
                    curMainPos += selectedItemMainSize + spaceWidth_;
                }
            } else {
                double axis = selectedItemMainAxis_ + selectedItemMainSize;
                double limit = curMainPos + childMainSize;
                if (GreatNotEqual(axis, limit - range) && LessOrEqual(axis, limit)) {
                    targetIndex_ = beforeSelectedItem ? index + 1 : index;
                    targetMainAxis_ = curMainPos;
                    curMainPos -= selectedItemMainSize + spaceWidth_;
                }
            }
        }

        auto offset = MakeValue<Offset>(curMainPos, 0.0);
        if (chainAnimation_) {
            offset += MakeValue<Offset>(-GetChainDelta(index), 0.0);
        }

        child->SetPosition(offset);
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

        childMainSize += spaceWidth_;
        if (LessNotEqual(curMainPos, mainSize) && GreatNotEqual(curMainPos + childMainSize, 0.0)) {
            if (!fixedCrossSize_) {
                crossSize = std::max(crossSize, GetCrossSize(childLayoutSize));
            }
            firstIdx = std::min(firstIdx, index);
            lastIdx = std::max(lastIdx, index);
        }

        if (child != selectedItem_) {
            curMainPos += childMainSize;
        }

        if (selectedItem_ && index > selectedItemIndex_ && targetIndex_ == index) {
            targetMainAxis_ = curMainPos;
            curMainPos += selectedItemMainSize + spaceWidth_;
        }

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
        if (reachStart_ && !scrollEffect_) {
            return false;
        }
        reachEnd_ = false;
    } else {
        if (reachEnd_ && !scrollEffect_) {
            return false;
        }
        reachStart_ = false;
    }

    auto context = context_.Upgrade();
    if (context) {
        dipScale_ = context->GetDipScale();
    }
    offset_ = offset;
    if (source == SCROLL_FROM_UPDATE) {
        ResumeEventCallback(component_, &ListComponent::GetOnScroll, Dimension(offset_ / dipScale_, DimensionUnit::VP),
            ScrollState(SCROLL_STATE_SCROLL));
    } else if (source == SCROLL_FROM_ANIMATION) {
        ResumeEventCallback(component_, &ListComponent::GetOnScroll, Dimension(offset_ / dipScale_, DimensionUnit::VP),
            ScrollState(SCROLL_STATE_FLING));
    }
    currentOffset_ += offset;
    MarkNeedLayout(true);
    return true;
}

void RenderList::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible()) {
        return;
    }

    if (PrepareRawRecognizer()) {
        result.emplace_back(rawRecognizer_);
    }

    // Disable scroll while expand all items
    if (!fixedMainSize_) {
        return;
    }
    if (!scrollable_ || !scrollable_->Available()) {
        return;
    }

    scrollable_->SetCoordinateOffset(coordinateOffset);
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
            fixedMainSizeByLayoutParam_ = false;
        } else {
            startMainPos_ = -maxMainSize;
            endMainPos_ = startMainPos_ + (maxMainSize * VIEW_PORT_SCALE);
            fixedMainSizeByLayoutParam_ = NearEqual(maxMainSize, GetMainSize(GetLayoutParam().GetMinSize()));
        }

        fixedCrossSize_ = !NearEqual(GetCrossSize(maxLayoutSize), Size::INFINITE_SIZE);
        TakeBoundary(fixedMainSizeByLayoutParam_ && fixedCrossSize_);
    }

    fixedMainSize_ = fixedMainSizeByLayoutParam_;
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

        if (currentStickyItem_ != child && selectedItem_ != child) {
            // Recycle list items out of view port
            RecycleListItem(curIndex);
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
    if (!newItem) {
        return newItem;
    }

    if (component_->GetEditMode()) {
        newItem->SetEditMode(true);
        newItem->SetOnDeleteClick([weak = AceType::WeakClaim(this)](RefPtr<RenderListItem> item) {
            auto spThis = weak.Upgrade();
            if (!spThis) {
                return;
            }
            spThis->OnItemDelete(item);
        });

        newItem->SetOnSelect([weak = AceType::WeakClaim(this)](RefPtr<RenderListItem> item) {
            auto spThis = weak.Upgrade();
            if (!spThis) {
                return;
            }
            spThis->OnItemSelect(item);
        });
    }

    if (!newItem->GetVisible()) {
        newItem->SetVisible(true);
    }

    return newItem;
}

void RenderList::RecycleListItem(size_t index)
{
    auto generator = itemGenerator_.Upgrade();
    if (generator) {
        generator->RecycleListItem(index);
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
    size_t index = GetIndexByListItem(item);
    if (!ResumeEventCallback(component_, &ListComponent::GetOnItemDelete, false, static_cast<int32_t>(index))) {
        LOGI("User canceled, stop deleting item");
        return;
    }

    if (index < startIndex_) {
        --startIndex_;
    }
}

void RenderList::OnItemSelect(const RefPtr<RenderListItem>& item)
{
    targetIndex_ = GetIndexByListItem(item);
    selectedItemIndex_ = targetIndex_;
    selectedItem_ = item;
    selectedItemMainAxis_ = GetMainAxis(item->GetPosition());
    LOGI("Select list item %{private}zu to move", selectedItemIndex_);
}

size_t RenderList::GetIndexByListItem(const RefPtr<RenderListItem>& item) const
{
    ACE_DCHECK(item);

    auto it = std::find(items_.begin(), items_.end(), item);
    if (it != items_.end()) {
        int32_t offset = std::distance(items_.begin(), it);
        ACE_DCHECK(offset >= 0);
        return startIndex_ + offset;
    }

    ACE_DCHECK(fixedMainSize_);
    ACE_DCHECK(item == currentStickyItem_);
    return currentStickyIndex_;
}

void RenderList::RemoveAllItems()
{
    items_.clear();
    ClearChildren();
    currentStickyItem_.Reset();
    currentStickyIndex_ = INITIAL_CHILD_INDEX;
    isActionByScroll_ = false;
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
    MarkNeedLayout(true);
}

void RenderList::UpdateTouchRect()
{
    touchRect_.SetSize(GetLayoutSize());
    touchRect_.SetOffset(GetPosition());
    ownTouchRect_ = touchRect_;
}

void RenderList::AdjustOffset(Offset& delta, int32_t source)
{
    // when scrollEffect equal to none, no need to adjust offset
    if (!scrollEffect_) {
        return;
    }

    if (delta.IsZero() || source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
        return;
    }

    double viewPortSize = GetMainSize(GetPaintRect().GetSize());
    double offset = GetMainAxis(delta);
    if (NearZero(viewPortSize) || NearZero(offset)) {
        return;
    }

    double maxScrollExtent = mainScrollExtent_ - viewPortSize;
    double overscrollPastStart = 0.0;
    double overscrollPastEnd = 0.0;
    double overscrollPast = 0.0;
    bool easing = false;

    overscrollPastStart = std::max(GetCurrentPosition(), 0.0);
    overscrollPastEnd = std::max(-GetCurrentPosition() - maxScrollExtent, 0.0);
    // do not adjust offset if direction oppsite from the overScroll direction when out of boundary
    if ((overscrollPastStart > 0.0 && offset < 0.0) || (overscrollPastEnd > 0.0 && offset > 0.0)) {
        return;
    }
    easing = (overscrollPastStart > 0.0 && offset > 0.0) || (overscrollPastEnd > 0.0 && offset < 0.0);

    overscrollPast = std::max(overscrollPastStart, overscrollPastEnd);
    double friction = easing ? RenderScroll::CalculateFriction((overscrollPast - std::abs(offset)) / viewPortSize)
                             : RenderScroll::CalculateFriction(overscrollPast / viewPortSize);
    double direction = offset / std::abs(offset);
    offset = direction * RenderScroll::CalculateOffsetByFriction(overscrollPast, std::abs(offset), friction);
    vertical_ ? delta.SetY(offset) : delta.SetX(offset);
}

double RenderList::GetCurrentPosition() const
{
    return currentOffset_;
}

bool RenderList::IsOutOfBoundary() const
{
    return isOutOfBoundary_;
}

void RenderList::ResetEdgeEffect()
{
    if (!scrollEffect_) {
        LOGE("ResetEdgeEffect failed, scrollEffect_ is nullptr");
        return;
    }

    scrollEffect_->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        if (list) {
            return list->GetCurrentPosition();
        }
        return 0.0;
    });
    scrollEffect_->SetLeadingCallback([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        if (list) {
            return list->GetMainSize(list->GetLayoutSize()) - list->mainScrollExtent_;
        }
        return 0.0;
    });

    scrollEffect_->SetTrailingCallback([weak = AceType::WeakClaim(this)]() { return 0.0; });
    scrollEffect_->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        if (list) {
            return list->GetMainSize(list->GetLayoutSize()) - list->mainScrollExtent_;
        }
        return 0.0;
    });
    scrollEffect_->SetInitTrailingCallback([weak = AceType::WeakClaim(this)]() { return 0.0; });
    scrollEffect_->SetScrollNode(AceType::WeakClaim(this));
    SetEdgeEffectAttribute();
    scrollEffect_->InitialEdgeEffect();
}

void RenderList::SetEdgeEffectAttribute()
{
    if (scrollEffect_ && scrollable_) {
        scrollEffect_->SetScrollable(scrollable_);
        scrollEffect_->RegisterSpringCallback();
        if (scrollEffect_->IsSpringEffect()) {
            scrollable_->SetOutBoundaryCallback([weakScroll = AceType::WeakClaim(this)]() {
                auto scroll = weakScroll.Upgrade();
                if (scroll) {
                    return scroll->IsOutOfBoundary();
                }
                return false;
            });
        }
    }
}

void RenderList::CalculateMainScrollExtent(double curMainPos, double mainSize)
{
    // check current is out of boundary
    isOutOfBoundary_ = LessNotEqual(curMainPos, mainSize) || GreatNotEqual(currentOffset_, 0.0);
    // content length
    mainScrollExtent_ = curMainPos - currentOffset_;
    // disable scroll when content length less than mainSize
    if (scrollable_) {
        scrollable_->MarkAvailable(GreatOrEqual(mainScrollExtent_, mainSize));
    }
    // last item no need add space width
    if (spaceWidth_ > 0.0) {
        mainScrollExtent_ = std::max(0.0, mainScrollExtent_ - spaceWidth_);
    }
}

void RenderList::ProcessDragStart(double startPosition)
{
    auto globalMainOffset = GetMainAxis(GetGlobalOffset());
    auto localOffset = startPosition - globalMainOffset;
    auto index = GetNearChildByPosition(localOffset);
    if (index == INVALID_CHILD_INDEX) {
        LOGE("GetNearChildByPosition failed, localOffset = %lf not in item index [ %zu, %zu )", localOffset,
            startIndex_, startIndex_ + items_.size());
        return;
    }
    dragStartIndexPending_ = index;
}

void RenderList::processDragUpdate(double dragOffset)
{
    if (!chainAnimation_) {
        return;
    }

    if (NearZero(dragOffset)) {
        return;
    }

    currentDelta_ = dragOffset;
    double delta = FlushChainAnimation();
    currentOffset_ += delta;
    if (!NearZero(delta)) {
        LOGE("processDragUpdate delta = %lf currentOffset_ = %lf", delta, currentOffset_);
    }
}

void RenderList::ProcessScrollOverCallback(double velocity)
{
    if (!chainAnimation_) {
        return;
    }

    if (NearZero(velocity)) {
        LOGD("velocity is zero, no need to handle in chain animation.");
        return;
    }

    if (reachStart_) {
        dragStartIndexPending_ = startIndex_;
    } else if (reachEnd_) {
        dragStartIndexPending_ = startIndex_;
        if (!items_.empty()) {
            dragStartIndexPending_ += items_.size() - 1;
        }
    }

    double delta = FlushChainAnimation();
    currentOffset_ += delta;
    if (!NearZero(delta)) {
        LOGE("ProcessScrollOverCallback delta = %lf currentOffset_ = %lf", delta, currentOffset_);
    }
}

void RenderList::InitChainAnimation(int32_t nodeCount)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("Init chain animation failed. context is null");
        return;
    }

    if (chainAdapter_ && chain_) {
        return;
    }
    chainAdapter_ = AceType::MakeRefPtr<BilateralSpringAdapter>();
    chain_ = AceType::MakeRefPtr<SimpleSpringChain>(chainAdapter_);
    const auto& property = GetChainProperty();
    chain_->SetFrameDelta(property.FrameDelay());
    if (property.StiffnessTransfer()) {
        chain_->SetStiffnessTransfer(AceType::MakeRefPtr<ExpParamTransfer>(property.StiffnessCoefficient()));
    } else {
        chain_->SetStiffnessTransfer(AceType::MakeRefPtr<LinearParamTransfer>(property.StiffnessCoefficient()));
    }
    if (property.DampingTransfer()) {
        chain_->SetDampingTransfer(AceType::MakeRefPtr<ExpParamTransfer>(property.DampingCoefficient()));
    } else {
        chain_->SetDampingTransfer(AceType::MakeRefPtr<LinearParamTransfer>(property.DampingCoefficient()));
    }
    chain_->SetControlDamping(property.ControlDamping());
    chain_->SetControlStiffness(property.ControlStiffness());
    chain_->SetDecoration(context->NormalizeToPx(property.Interval()));
    chain_->SetMinDecoration(context->NormalizeToPx(property.MinInterval()));
    chain_->SetMaxDecoration(context->NormalizeToPx(property.MaxInterval()));
    for (int32_t index = 0; index < nodeCount; index++) {
        auto node = AceType::MakeRefPtr<BilateralSpringNode>(GetContext(), index, 0.0);
        WeakPtr<BilateralSpringNode> nodeWeak(node);
        WeakPtr<SimpleSpringAdapter> adapterWeak(chainAdapter_);
        node->AddUpdateListener(
            [weak = AceType::WeakClaim(this), nodeWeak, adapterWeak](double value, double velocity) {
                auto renderList = weak.Upgrade();
                auto node = nodeWeak.Upgrade();
                auto adapter = adapterWeak.Upgrade();
                if (!renderList || !node || !adapter) {
                    return;
                }
                renderList->MarkNeedLayout();
            });
        chainAdapter_->AddNode(node);
    }
    chainAdapter_->NotifyControlIndexChange();
}

double RenderList::GetChainDelta(int32_t index) const
{
    if (!chainAdapter_) {
        return 0.0;
    }
    double value = 0.0;
    RefPtr<BilateralSpringNode> node;
    int32_t controlIndex = dragStartIndex_;
    int32_t baseIndex = controlIndex - chainAdapter_->GetControlIndex();
    auto targetIndex = std::clamp(index - baseIndex, 0, CHAIN_ANIMATION_NODE_COUNT - 1);
    node = AceType::DynamicCast<BilateralSpringNode>(chainAdapter_->GetNode(targetIndex));
    if (node) {
        value = node->GetValue();
    }
    LOGD("ChainDelta. controlIndex: %{public}d, index: %{public}d, value: %{public}.3lf", controlIndex, index, value);
    return value;
}

size_t RenderList::GetNearChildByPosition(double mainOffset) const
{
    size_t index = startIndex_;
    size_t prevIndex = INVALID_CHILD_INDEX;

    for (auto& child : items_) {
        auto childMainOffset = GetMainAxis(child->GetPosition());

        if (childMainOffset > mainOffset) {
            return prevIndex;
        }
        prevIndex = index++;
    }
    return prevIndex;
}

double RenderList::FlushChainAnimation()
{
    if (!chainAnimation_ || !chain_ || !chainAdapter_) {
        return 0.0;
    }
    double deltaDistance = 0.0;
    bool needSetValue = false;
    bool overScroll = scrollable_ && scrollable_->IsSpringMotionRunning();
    if (chainOverScroll_ != overScroll) {
        if (overScroll) {
            const auto& springProperty = GetOverSpringProperty();
            if (springProperty && springProperty->IsValid()) {
                chain_->SetControlStiffness(springProperty->Stiffness());
                chain_->SetControlDamping(springProperty->Damping());
            }
        } else {
            chain_->SetControlStiffness(GetChainProperty().ControlStiffness());
            chain_->SetControlDamping(GetChainProperty().ControlDamping());
        }
        chain_->OnControlNodeChange();
        chainOverScroll_ = overScroll;
    }
    chain_->FlushAnimation();
    if (dragStartIndexPending_ != dragStartIndex_) {
        deltaDistance = chainAdapter_->ResetControl(dragStartIndexPending_ - dragStartIndex_);
        LOGD("Switch chain control node. %{public}zu -> %{public}zu, deltaDistance: %{public}.1f", dragStartIndex_,
            dragStartIndexPending_, deltaDistance);
        dragStartIndex_ = dragStartIndexPending_;
        chainAdapter_->SetDeltaValue(-deltaDistance);
        needSetValue = true;
    }
    if (!NearZero(currentDelta_)) {
        LOGD("Set delta chain value. delta: %{public}.1f", currentDelta_);
        chainAdapter_->SetDeltaValue(currentDelta_);
        currentDelta_ = 0.0;
        needSetValue = true;
    }
    if (needSetValue) {
        chain_->SetValue(0.0);
        LOGD("FlushChainAnimation: %{public}s", chainAdapter_->DumpNodes().c_str());
    }
    return deltaDistance;
}

void RenderList::UpdateAccessibilityAttr()
{
    if (!component_) {
        LOGE("RenderList: component is null.");
        return;
    }

    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        LOGE("RenderList: current accessibilityNode is null.");
        return;
    }

    auto collectionInfo = accessibilityNode->GetCollectionInfo();
    size_t count = TotalCount() > 0 ? TotalCount() : 1;
    if (vertical_) {
        collectionInfo.rows = count;
        collectionInfo.columns = 1;
    } else {
        collectionInfo.rows = 1;
        collectionInfo.columns = count;
    }
    accessibilityNode->SetCollectionInfo(collectionInfo);
    accessibilityNode->SetScrollableState(true);
    accessibilityNode->SetActionScrollForward([weakList = AceType::WeakClaim(this)]() {
        auto list = weakList.Upgrade();
        if (list) {
            LOGI("Trigger ScrollForward by Accessibility.");
            return list->HandleActionScroll(true);
        }
        return false;
    });
    accessibilityNode->SetActionScrollBackward([weakList = AceType::WeakClaim(this)]() {
        auto list = weakList.Upgrade();
        if (list) {
            LOGI("Trigger ScrollBackward by Accessibility.");
            return list->HandleActionScroll(false);
        }
        return false;
    });

    accessibilityNode->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    accessibilityNode->AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
    accessibilityNode->SetActionUpdateIdsImpl([weakList = AceType::WeakClaim(this)]() {
        auto list = weakList.Upgrade();
        if (list) {
            list->UpdateAccessibilityChild();
        }
    });

    scrollFinishEventBack_ = [weakList = AceType::WeakClaim(this)] {
        auto list = weakList.Upgrade();
        if (list) {
            list->ModifyActionScroll();
        }
    };
}

bool RenderList::ActionByScroll(bool forward, ScrollEventBack scrollEventBack)
{
    LOGI("Handle action by Scroll.");
    auto node = GetParent().Upgrade();
    while (node) {
        auto scroll = AceType::DynamicCast<RenderSingleChildScroll>(node);
        if (!scroll) {
            node = node->GetParent().Upgrade();
            continue;
        }

        scroll->ScrollPage(!forward, true, scrollEventBack);
        return true;
    }
    return false;
}

bool RenderList::HandleActionScroll(bool forward)
{
    if (isActionByScroll_) {
        return ActionByScroll(forward, scrollFinishEventBack_);
    }

    if (forward) {
        JumpToIndex(lastDisplayIndex_, DEFAULT_SOURCE);
    } else {
        JumpToIndex(startIndex_, DEFAULT_SOURCE);
    }
    if (scrollFinishEventBack_) {
        scrollFinishEventBack_();
    }
    return true;
}

void RenderList::ModifyActionScroll()
{
    hasActionScroll_ = true;
}

void RenderList::OnPaintFinish()
{
    if (!hasActionScroll_) {
        return;
    }

    hasActionScroll_ = false;
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("RenderList: context is null.");
        return;
    }

    AccessibilityEvent scrollEvent;
    scrollEvent.nodeId = GetAccessibilityNodeId();
    scrollEvent.eventType = "scrollend";
    context->SendEventToAccessibility(scrollEvent);
}

void RenderList::UpdateAccessibilityChild()
{
    auto parentAccessibilityNode = GetAccessibilityNode().Upgrade();
    if (!parentAccessibilityNode) {
        LOGE("RenderList: current accessibilityNode is null.");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("RenderList: context is null.");
        return;
    }

    std::list<RefPtr<AccessibilityNode>> children;
    parentAccessibilityNode->ResetChildList(children);

    for (size_t index = (firstDisplayIndex_ - startIndex_); index <= (lastDisplayIndex_ - startIndex_); ++index) {
        auto iter = items_.begin();
        std::advance(iter, index);
        if (iter == items_.end()) {
            continue;
        }

        auto childAccessibilityNode = (*iter)->GetAccessibilityNode().Upgrade();
        if (!childAccessibilityNode) {
            continue;
        }

        Rect viewRect = context->GetStageRect();
        if (childAccessibilityNode->GetLeft() > viewRect.Right() ||
            childAccessibilityNode->GetTop() > viewRect.Bottom()) {
            isActionByScroll_ = true;
            break;
        }

        if (childAccessibilityNode->GetLeft() + childAccessibilityNode->GetWidth() < viewRect.Left() ||
            childAccessibilityNode->GetTop() + childAccessibilityNode->GetHeight() < viewRect.Top()) {
            continue;
        }

        auto oldParent = childAccessibilityNode->GetParentNode();
        if (oldParent) {
            oldParent->RemoveNode(childAccessibilityNode);
        }

        childAccessibilityNode->SetParentNode(parentAccessibilityNode);
        childAccessibilityNode->Mount(-1);
    }
}

bool RenderList::PrepareRawRecognizer()
{
    if (rawRecognizer_) {
        return true;
    }

    rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    auto weak = AceType::WeakClaim(this);
    rawRecognizer_->SetOnTouchDown([weak](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            return;
        }
        auto spThis = weak.Upgrade();
        if (spThis) {
            spThis->lastPos_ = spThis->GetMainAxis(info.GetTouches().front().GetLocalLocation());
        }
    });
    rawRecognizer_->SetOnTouchMove([weak](const TouchEventInfo& info) {
        if (info.GetTouches().empty()) {
            return;
        }

        auto spThis = weak.Upgrade();
        if (!spThis || !spThis->selectedItem_) {
            return;
        }
        double currentPos = spThis->GetMainAxis(info.GetTouches().front().GetLocalLocation());
        spThis->OnSelectedItemMove(currentPos);
    });
    rawRecognizer_->SetOnTouchUp([weak](const TouchEventInfo& info) {
        auto spThis = weak.Upgrade();
        if (spThis) {
            spThis->OnSelectedItemStopMoving(false);
        }
    });
    rawRecognizer_->SetOnTouchCancel([weak](const TouchEventInfo& info) {
        auto spThis = weak.Upgrade();
        if (spThis) {
            spThis->OnSelectedItemStopMoving(true);
        }
    });

    return true;
}

void RenderList::OnSelectedItemMove(double position)
{
    double deltaPos = position - lastPos_;

    movingForward_ = LessOrEqual(deltaPos, 0.0);
    selectedItemMainAxis_ += deltaPos;
    deltaPos = -deltaPos;
    if (LessOrEqual(selectedItemMainAxis_, 0.0)) {
        selectedItemMainAxis_ = 0.0;
    } else {
        double maxMainSize = GetMainSize(GetLayoutSize());
        double mainSize = GetMainSize(selectedItem_->GetLayoutSize());
        if (GreatOrEqual(selectedItemMainAxis_ + mainSize, maxMainSize)) {
            selectedItemMainAxis_ = maxMainSize - mainSize;
        } else {
            deltaPos = 0.0;
            lastPos_ = position;
        }
    }

    if (!NearZero(deltaPos)) {
        currentOffset_ += deltaPos;
        autoScrollingForItemMove_ = true;
    }

    MarkNeedLayout();
}

void RenderList::OnSelectedItemStopMoving(bool canceled)
{
    if (!canceled && targetIndex_ != selectedItemIndex_) {
        auto from = static_cast<int32_t>(selectedItemIndex_);
        auto to = static_cast<int32_t>(targetIndex_);
        LOGI("Moving item from %{private}d to %{private}d", from, to);
        if (!ResumeEventCallback(component_, &ListComponent::GetOnItemMove, false, from, to)) {
            LOGI("User canceled, stop moving item");
        }
    }

    if (selectedItemIndex_ < startIndex_ || selectedItemIndex_ >= startIndex_ + items_.size()) {
        RecycleListItem(selectedItemIndex_);
    }

    targetIndex_ = INITIAL_CHILD_INDEX;
    selectedItemIndex_ = INITIAL_CHILD_INDEX;
    selectedItem_ = nullptr;
    MarkNeedLayout();
}

} // namespace OHOS::Ace::V2
