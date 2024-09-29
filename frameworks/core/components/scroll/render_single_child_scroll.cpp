/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/scroll/render_single_child_scroll.h"

#include "core/common/text_field_manager.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t MAX_CHILD_SIZE = 1;

} // namespace

void RenderSingleChildScroll::Update(const RefPtr<Component>& component)
{
    RefPtr<ScrollComponent> scroll = AceType::DynamicCast<ScrollComponent>(component);
    if (!scroll) {
        return;
    }

    rightToLeft_ = scroll->GetTextDirection() == TextDirection::RTL;
    enable_ = scroll->GetEnable();
    onScrollBegin_ = scroll->GetOnScrollBegin();

    auto axis = scroll->GetAxisDirection();
    if (axis_ != axis) {
        axis_ = axis;
        ResetScrollable();
        InitScrollBarProxy();
        initial_ = true;
    }
    padding_ = scroll->GetPadding();
    scrollPage_ = scroll->GetScrollPage();

    positionController_ = scroll->GetScrollPositionController();
    if (positionController_) {
        positionController_->SetScrollNode(AceType::WeakClaim(this));
        positionController_->SetScrollEvent(ScrollEvent::SCROLL_TOP,
            AceAsyncEvent<void(std::shared_ptr<ScrollEventInfo>&)>::Create(scroll->GetOnScrollEdge(), GetContext()));
        positionController_->SetScrollEvent(ScrollEvent::SCROLL_EDGE,
            AceAsyncEvent<void(std::shared_ptr<ScrollEventInfo>&)>::Create(scroll->GetOnScrollEdge(), GetContext()));
        positionController_->SetScrollEvent(ScrollEvent::SCROLL_END,
            AceAsyncEvent<void(std::shared_ptr<ScrollEventInfo>&)>::Create(scroll->GetOnScrollEnd(), GetContext()));
        positionController_->SetScrollEvent(ScrollEvent::SCROLL_POSITION,
            AceAsyncEvent<void(std::shared_ptr<ScrollEventInfo>&)>::Create(scroll->GetOnScroll(), GetContext()));
        positionController_->SetScrollNode(AceType::WeakClaim(this));
    }
    // In dialog, scroll is not takeBoundary, use this flag to determine.
    TakeBoundary(scroll->IsTakeBoundary());

    auto scrollBar = scroll->GetScrollBar();
    InitScrollBar(scrollBar);

    // This should be put after setting positionController_.
    RenderScroll::Update(component);
    UpdateAccessibilityAttr();

    // Update edge effect.
    isEffectSetted_ = scroll->IsEffectSetted();
    auto newEffect = scroll->GetScrollEffect();
    if (scrollEffect_ != newEffect) {
        scrollEffect_ = newEffect;
        if (scrollEffect_) {
            ResetEdgeEffect();
        }
    }
    FindRefreshParent(AceType::WeakClaim(this));
}

LayoutParam RenderSingleChildScroll::MakeInnerLayoutParam() const
{
    LayoutParam layout;
    if (!enable_) {
        layout.SetMaxSize(Size(viewPort_.Width(), viewPort_.Height()));
    } else if (axis_ == Axis::VERTICAL) {
        layout.SetMaxSize(Size(viewPort_.Width(), layout.GetMaxSize().Height()));
    } else {
        layout.SetMaxSize(Size(layout.GetMaxSize().Width(), viewPort_.Height()));
    }
    return layout;
}

bool RenderSingleChildScroll::IsUseOnly()
{
    return true;
}

bool RenderSingleChildScroll::CalculateMainScrollExtent(const Size& itemSize)
{
    bool isScrollable = false;
    if (axis_ == Axis::VERTICAL) {
        mainScrollExtent_ = itemSize.Height() + NormalizeToPx(padding_.Top()) + NormalizeToPx(padding_.Bottom());
        if (mainScrollExtent_ > viewPort_.Height()) {
            isScrollable = true;
        }
    } else {
        mainScrollExtent_ = itemSize.Width() + NormalizeToPx(padding_.Left()) + NormalizeToPx(padding_.Right());
        if (mainScrollExtent_ > viewPort_.Width()) {
            isScrollable = true;
        }
    }

    // If not scrollable, reset scrollable_ to null.
    if (!isScrollable) {
        if (scrollable_) {
            scrollable_->MarkAvailable(false);
            if (scrollable_->Idle() && GetMainOffset(currentOffset_) > 0.0) {
                JumpToPosition(0.0);
            }
        }
    } else {
        if (scrollable_ && scrollable_->Available()) {
            if (scrollable_->Idle() && GetMainOffset(currentOffset_) > mainScrollExtent_ - GetMainSize(viewPort_)) {
                // scroll to bottom
                JumpToPosition(mainScrollExtent_ - GetMainSize(viewPort_));
            }
        } else {
            if (scrollable_) {
                scrollable_->MarkAvailable(true);
            }
        }
    }

    if (scrollBar_) {
        scrollBar_->SetScrollable(isScrollable);
        auto barController = scrollBar_->GetController();
        if (!isScrollable && barController) {
            barController->StopScrollEndAnimator();
        }
    }

    return isScrollable;
}

void RenderSingleChildScroll::MoveChildToViewPort(
    const Size& size, const Offset& childOffset, const Offset& effectOffset)
{
    auto selfOffset = GetGlobalOffset();
    auto viewRect = Rect(selfOffset, viewPort_);
    auto itemActualRect = Rect(childOffset, size);
    // rect is in viewport
    if (itemActualRect.IsWrappedBy(viewRect)) {
        return;
    }
    double childPosition = GetMainOffset(childOffset);
    double viewMin = GetMainOffset(selfOffset);
    double viewMax = GetMainOffset(selfOffset + viewPort_);
    double effectSize = GetMainOffset(effectOffset);
    double childSize = GetMainSize(size);
    double viewPortSize = GetMainSize(viewPort_);

    double moveDelta = 0.0;
    if (viewPortSize <= childSize) {
        return;
    }

    if (childPosition < viewMin) {
        moveDelta = childPosition - viewMin - effectSize;
    } else if (childPosition + childSize > viewMax) {
        moveDelta = childPosition + childSize + effectSize - viewMax;
    }
    JumpToPosition(GetCurrentPosition() + moveDelta);
}

bool RenderSingleChildScroll::IsDeclarativePara()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
}

void RenderSingleChildScroll::PerformLayout()
{
    if (GetChildren().size() != MAX_CHILD_SIZE) {
        LOGE("render Scroll perform layout with %{public}zu children", GetChildren().size());
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }

    viewPort_ = GetLayoutParam().GetMaxSize() > viewPort_ ? viewPort_ : GetLayoutParam().GetMaxSize();

    Size paddingSize = padding_.GetLayoutSizeInPx(context->GetDipScale());
    Offset paddingOffset = padding_.GetOffsetInPx(context->GetDipScale());

    auto child = GetChildren().front();

    LayoutParam layout = MakeInnerLayoutParam();
    child->Layout(layout);

    // Get layout result of child.
    Size itemSize = child->GetLayoutSize();
    // Calculate with padding.
    if (!NearZero(paddingSize.Width()) || !NearZero(paddingSize.Height())) {
        layout.SetFixedSize(itemSize - paddingSize);
        // Layout again with new param.
        child->Layout(layout);
    }
    itemSize = child->GetLayoutSize();
    auto left = child->GetLeft().ConvertToPx();
    auto top = child->GetTop().ConvertToPx();

    if (!IsDeclarativePara()) {
        auto childPosition = child->GetChildren().front();
        if (childPosition) {
            left = childPosition->GetLeft().ConvertToPx();
            top = childPosition->GetTop().ConvertToPx();
        }
    }
    itemSize.SetWidth(itemSize.Width() + left);
    itemSize.SetHeight(itemSize.Height() + top);

    auto currentChildMainSize = GetMainSize(child->GetLayoutSize());
    // Mark need force layout with parent if child size changed in semi and dialog window modal.
    if (!NearEqual(childLastMainSize_, -std::numeric_limits<double>::max()) &&
        !NearEqual(currentChildMainSize, childLastMainSize_) && !context->IsFullScreenModal()) {
        PostForceMakeNeedLayout();
    }
    childLastMainSize_ = currentChildMainSize;

    auto constrainSize = GetLayoutParam().Constrain(itemSize > viewPort_ ? viewPort_ : itemSize);
    if (GetHasWidth()) {
        constrainSize.SetWidth(GetLayoutParam().GetMaxSize().Width());
    }
    if (GetHasHeight()) {
        constrainSize.SetHeight(GetLayoutParam().GetMaxSize().Height());
    }
    SetLayoutSize(constrainSize);

    auto textFieldManager = AceType::DynamicCast<TextFieldManager>(context->GetTextFieldManager());
    if (textFieldManager && moveStatus_.first && axis_ == Axis::VERTICAL) {
        moveDistance_ = textFieldManager->GetClickPosition().GetY() - viewPort_.Height();
        currentOffset_.SetY(moveDistance_);
        moveStatus_.first = false;
    }

    if (textFieldManager && moveStatus_.second && !moveStatus_.first && axis_ == Axis::VERTICAL) {
        currentOffset_.SetY(0 - moveDistance_);
        moveStatus_.second = false;
        moveDistance_ = 0;
    }
    // Get main direction scrollable extent.
    bool isScrollable = CalculateMainScrollExtent(itemSize);
    scrollBarExtent_ = mainScrollExtent_;

    if (initial_ && IsRowReverse()) {
        currentOffset_.SetX(mainScrollExtent_ - viewPort_.Width());
        lastOffset_ = currentOffset_;
        initial_ = false;
    }

    if (isScrollable) {
        ValidateOffset(SCROLL_FROM_NONE);
    } else {
        currentOffset_ = Offset::Zero();
        if (IsRowReverse()) {
            currentOffset_.SetX(mainScrollExtent_ - viewPort_.Width());
            lastOffset_ = currentOffset_;
        }
    }
    auto childOffset = Offset::Zero() - currentOffset_ + paddingOffset;
    auto parentNode = AceType::DynamicCast<RenderBoxBase>(GetParent().Upgrade());
    if (parentNode) {
        auto alignmentPosition =
            Alignment::GetAlignPosition(GetLayoutSize(), child->GetLayoutSize(), parentNode->GetAlign());
        if (GetHasWidth()) {
            childOffset.SetX(childOffset.GetX() + alignmentPosition.GetX());
        }
        if (GetHasHeight()) {
            childOffset.SetY(childOffset.GetY() + alignmentPosition.GetY());
        }
    }
    child->SetPosition(childOffset);

    currentBottomOffset_ = axis_ == Axis::VERTICAL ? currentOffset_ + Offset(0.0, viewPort_.Height())
                                                   : currentOffset_ + Offset(viewPort_.Width(), 0.0);
}

void RenderSingleChildScroll::PostForceMakeNeedLayout()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this)] {
            auto scroll = weak.Upgrade();
            if (!scroll) {
                return;
            }
            scroll->MarkNeedLayout(false, true);
        },
        TaskExecutor::TaskType::UI, "ArkUIScrollForceMakeNeedLayout");
}

void RenderSingleChildScroll::UpdateAccessibilityAttr()
{
    auto refPtr = accessibilityNode_.Upgrade();
    if (!refPtr) {
        LOGW("Get accessibility node failed.");
        return;
    }
    refPtr->SetScrollableState(true);
    refPtr->SetActionScrollForward([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            LOGI("Trigger ScrollForward by Accessibility.");
            scroll->ScrollPage(false, true);
            return true;
        }
        return false;
    });
    refPtr->SetActionScrollBackward([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            LOGI("Trigger ScrollBackward by Accessibility.");
            scroll->ScrollPage(true, true);
            return true;
        }
        return false;
    });
}

void RenderSingleChildScroll::AdjustTouchRestrict(TouchRestrict& touchRestrict)
{
    // If edge effect is setted, do not adjust touch restrict.
    if (isEffectSetted_) {
        return;
    }

    if (currentOffset_.IsZero()) {
        if (axis_ == Axis::VERTICAL) {
            touchRestrict.forbiddenType |= TouchRestrict::SWIPE_DOWN;
        } else {
            touchRestrict.forbiddenType |= TouchRestrict::SWIPE_RIGHT;
        }
    }
}

} // namespace OHOS::Ace
