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

#include "core/components/tab_bar/render_tab_content.h"

#include "core/animation/curve_animation.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr double FRIC_RATIO = 0.5; // default ratio
constexpr double MIN_SCROLL_OFFSET = 0.20;

} // namespace

RenderTabContent::RenderTabContent() : RenderNode(true) {}

void RenderTabContent::Update(const RefPtr<Component>& component)
{
    const RefPtr<TabContentComponent> tabContent = AceType::DynamicCast<TabContentComponent>(component);
    if (!tabContent || !tabContent->GetController()) {
        LOGW("tabContent is null");
        return;
    }
    auto tabController = tabContent->GetController();
    int32_t count = tabContent->GetChildren().size();
    int32_t tabIndex = tabController->GetIndex();
    if (count != contentCount_ && tabIndex >= count) {
        tabController->ValidateIndex(count - 1);
        tabIndex = tabController->GetIndex();
        currentIndex_ = tabIndex;
    }
    contentCount_ = count;
    if (scrollable_ != tabContent->IsScrollable()) {
        if (animator_ && animator_->IsRunning()) {
            animator_->Finish();
        }
        scrollable_ = tabContent->IsScrollable();
    }
    scrollDuration_ = tabContent->GetScrollDuration();
    isVertical_ = tabContent->IsVertical();
    SetTextDirection(tabContent->GetTextDirection());
    if (!isInitialized_) {
        currentIndex_ = tabIndex;
        isInitialized_ = true;
    }
    changeEvent_ = AceAsyncEvent<void(const std::string&)>::Create(tabContent->GetChangeEventId(), context_);
    domChangeEvent_ = AceAsyncEvent<void(uint32_t)>::Create(tabContent->GetDomChangeEventId(), context_);

    MarkNeedLayout();
    Initialize(GetContext());
}

void RenderTabContent::Initialize(const WeakPtr<PipelineContext>& context)
{
    animator_ = AceType::MakeRefPtr<Animator>(context);

    // if the tab is vertical, use VerticalDragRecognizer
    if (isVertical_) {
        dragDetector_ = AceType::MakeRefPtr<VerticalDragRecognizer>();
    } else {
        dragDetector_ = AceType::MakeRefPtr<HorizontalDragRecognizer>();
    }

    // if scrollable is true, initialize the dragDetector
    if (scrollable_) {
        dragDetector_->SetOnDragStart([weakContent = AceType::WeakClaim(this)](const DragStartInfo& info) {
            auto tabContent = weakContent.Upgrade();
            if (tabContent) {
                tabContent->HandleDragStart();
            }
        });
        dragDetector_->SetOnDragUpdate([weakContent = AceType::WeakClaim(this)](const DragUpdateInfo& info) {
            auto tabContent = weakContent.Upgrade();
            if (tabContent) {
                tabContent->HandleDragUpdate(info.GetMainDelta());
            }
        });
        dragDetector_->SetOnDragEnd([weakContent = AceType::WeakClaim(this)](const DragEndInfo& info) {
            auto tabContent = weakContent.Upgrade();
            if (tabContent) {
                tabContent->HandleDragEnd();
            }
        });
    } else {
        dragDetector_->SetOnDragStart([](const DragStartInfo& info) {});
        dragDetector_->SetOnDragUpdate([](const DragUpdateInfo& info) {});
        dragDetector_->SetOnDragEnd([](const DragEndInfo& info) {});
    }
}

void RenderTabContent::FireContentChangeEvent() const
{
    if (changeEvent_) {
        LOGI("FireChangeEvent, index = %{public}d.", currentIndex_);
        std::string param =
            std::string(R"("change",{"index":)").append(std::to_string(currentIndex_).append("},null"));
        changeEvent_(param);
    }
}

void RenderTabContent::FireDomChangeEvent(int32_t index) const
{
    LOGI("FireDomChangeEvent, index is %{public}d", index);
    if (domChangeEvent_) {
        domChangeEvent_(index);
    }
}

void RenderTabContent::HandleDragStart()
{
    LOGD("HandleDragStart");
    if (isInAnimation_) {
        return;
    }
    isDragging_ = true;
}

void RenderTabContent::HandleDragUpdate(double offset)
{
    if (isInAnimation_) {
        return;
    }
    UpdateScrollPosition(offset);
}

void RenderTabContent::HandleDragEnd()
{
    LOGD("HandleDragEnd");
    if (isInAnimation_) {
        return;
    }
    isDragging_ = false;
    if (NearZero(scrollOffset_)) {
        LOGI("ScrollOffset near equals 0.");
        return;
    }
    int32_t newIndex = IsRightToLeft() ? (scrollOffset_ < 0.0 ? GetPrevIndex() : GetNextIndex())
                                       : (scrollOffset_ > 0.0 ? GetPrevIndex() : GetNextIndex());
    ScrollContents(newIndex, false);
}

void RenderTabContent::ChangeScroll(int32_t index)
{
    LOGI("Change scroll index is %{public}d", index);
    ScrollContents(index, true);
}

void RenderTabContent::ScrollContents(int32_t newIndex, bool isLinkBar)
{
    LOGD("ScrollContents from %{public}d to %{public}d", currentIndex_, newIndex);
    if (!animator_->IsStopped()) {
        LOGD("Animationis not stopped, clear stop listener.");
        // clear stop listener and stop
        if (isInAnimation_) {
            LOGD("In animation,controller end");
            animator_->Finish();
        } else {
            LOGD("Not in animation,controller stop");
            animator_->Stop();
        }
    }
    animator_->ClearStopListeners();
    animator_->ClearStartListeners();

    if (isAnimationAdded_) {
        animator_->RemoveInterpolator(translate_);
        isAnimationAdded_ = false;
    }

    bool needChange = false;
    int32_t index = currentIndex_;
    double start = scrollOffset_;
    double end = 0.0;
    if (newIndex >= 0 && newIndex < contentCount_) {
        end = currentIndex_ > newIndex ? nextOffset_ : prevOffset_;

        // Adjust offset more than MIN_SCROLL_OFFSET at least
        double minOffset = 0.0;
        if (isVertical_) {
            minOffset = MIN_SCROLL_OFFSET * contentHeight_;
        } else {
            minOffset = MIN_SCROLL_OFFSET * contentWidth_;
        }
        if (!NearZero(scrollOffset_) && std::abs(scrollOffset_) < minOffset) {
            LOGI("ScrollOffset less than min scroll offset.");
            end = 0.0;
        }
    }

    if (!NearZero(end) || NearZero(scrollOffset_)) {
        needChange = true;
    }
    LOGD("Translate animation, start=%{public}lf, end=%{public}lf", start, end);
    translate_ = AceType::MakeRefPtr<CurveAnimation<double>>(start, end, Curves::FRICTION);
    auto weak = AceType::WeakClaim(this);
    translate_->AddListener(Animation<double>::ValueCallback([weak, index, newIndex, needChange](double value) {
        auto tabContent = weak.Upgrade();
        if (tabContent) {
            tabContent->UpdateChildPosition(value, index, newIndex, needChange);
        }
    }));

    animator_->AddStopListener([weak, newIndex, needChange]() {
        auto tabContent = weak.Upgrade();
        if (tabContent) {
            tabContent->HandleStopListener(newIndex, needChange);
        }
    });
    animator_->AddStartListener([weak, newIndex, needChange, isLinkBar]() {
        auto tabContent = weak.Upgrade();
        if (tabContent) {
            tabContent->HandleStartListener(newIndex, needChange, isLinkBar);
        }
    });
    animator_->SetDuration(scrollDuration_);
    animator_->AddInterpolator(translate_);
    animator_->Play();
    MarkNeedRender();
}

void RenderTabContent::HandleStartListener(int32_t newIndex, bool needChange, bool isLinkBar)
{
    isInAnimation_ = true;
    isAnimationAdded_ = true;
    if (newIndex >= 0 && newIndex < contentCount_ && needChange) {
        currentIndex_ = newIndex;
        if (callback_) {
            callback_(newIndex);
        }
        if (!isLinkBar) {
            FireDomChangeEvent(newIndex);
        }

        // Set the new index node not hidden
        const auto& newItem = contentMap_[newIndex];
        if (!newItem) {
            LOGE("no content at index %{public}d", newIndex);
            return;
        }
        newItem->SetHidden(false);
    }
}

void RenderTabContent::HandleStopListener(int32_t newIndex, bool needChange)
{
    LOGI("HandleStopListener start, newIndex is %{public}d,needChange is %{public}d", newIndex, needChange);
    // callback used to notify the change of index
    if (newIndex >= 0 && newIndex < contentCount_ && needChange) {
        FireContentChangeEvent();
        SetHiddenChild();
    }
    if (isInAnimation_) {
        isInAnimation_ = false;
        scrollOffset_ = 0.0;
    }
}

void RenderTabContent::SetHiddenChild()
{
    for (const auto& item : contentMap_) {
        const auto& childItem = item.second;
        if (!childItem) {
            continue;
        }
        int32_t index = item.first;
        childItem->SetHidden(index != currentIndex_);
    }
}

void RenderTabContent::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (dragDetector_) {
        dragDetector_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDetector_);
    }
}

double RenderTabContent::GetOffset(double delta)
{
    if (isVertical_) {
        if (!NearZero(contentHeight_)) {
            double friction = GetFriction(std::abs(scrollOffset_) / contentHeight_);
            return friction * delta;
        }
    } else {
        if (!NearZero(contentWidth_)) {
            double friction = GetFriction(std::abs(scrollOffset_) / contentWidth_);
            return friction * delta;
        }
    }
    return delta;
}

double RenderTabContent::GetFriction(double percentage)
{
    return FRIC_RATIO * std::pow(1.0 - percentage, SQUARE);
}

void RenderTabContent::UpdateScrollPosition(double dragDelta)
{
    double newDragOffset = scrollOffset_ + dragDelta;
    int32_t newIndex = IsRightToLeft() ? (newDragOffset < 0.0 ? GetPrevIndex() : GetNextIndex())
                                       : (newDragOffset > 0.0 ? GetPrevIndex() : GetNextIndex());

    if ((currentIndex_ == 0 && newIndex == -1) || (currentIndex_ == (contentCount_ - 1) && newIndex == contentCount_)) {
        scrollOffset_ += GetOffset(dragDelta);
    } else {
        scrollOffset_ = newDragOffset;
    }
    if (contentMap_.find(newIndex) == contentMap_.end() && newIndex >= 0 && newIndex < contentCount_) {
        if (requireCallback_) {
            requireCallback_(newIndex);
        }
        return;
    }
    UpdateChildPosition(scrollOffset_, currentIndex_, newIndex, true);
}

void RenderTabContent::UpdateDragPosition(int32_t index)
{
    UpdateChildPosition(scrollOffset_, currentIndex_, index, true);
}

void RenderTabContent::UpdateChildPosition(double offset, int32_t currentIndex, int32_t newIndex, bool needChange)
{
    scrollOffset_ = offset;
    LOGD("UpdateChildPosition start offset = %{public}lf, from = %{public}d, to = %{public}d", offset, currentIndex,
        newIndex);
    if (currentIndex < 0 || currentIndex >= contentCount_) {
        LOGE("currentIndex out of range, currentIndex is %{public}d", currentIndex);
        return;
    }
    const auto& fromItem = contentMap_[currentIndex];
    if (!fromItem) {
        LOGE("no content at index %{public}d", currentIndex);
        return;
    }
    fromItem->SetPosition(GetMainAxisOffset(offset));
    fromItem->MarkNeedRender();

    // at the first one item or the last one item, no more switching
    if (newIndex < 0 || newIndex >= contentCount_) {
        return;
    }

    // scroll between left and right
    const auto& toItem = contentMap_[newIndex];
    if (!toItem) {
        LOGE("no content at index %{public}d", newIndex);
        return;
    }
    toItem->SetHidden(false);
    auto toItemPosValue = offset + (newIndex < currentIndex ? prevOffset_ : nextOffset_);
    Offset toItemPos = GetMainAxisOffset(toItemPosValue);
    toItem->SetPosition(toItemPos);
    toItem->MarkNeedRender();
    LOGD("update position from(%{public}lf in %{public}u) to(%{public}lf in %{public}u)", offset, currentIndex,
        toItemPosValue, newIndex);
}

inline int32_t RenderTabContent::GetPrevIndex() const
{
    return currentIndex_ - 1;
}

inline int32_t RenderTabContent::GetNextIndex() const
{
    return currentIndex_ + 1;
}

void RenderTabContent::PerformLayout()
{
    const std::list<RefPtr<RenderNode>>& children = GetChildren();
    if (!children.empty()) {
        LayoutParam innerLayout = GetLayoutParam();
        Size maxSize = GetLayoutParam().GetMaxSize();
        for (const auto& item : contentMap_) {
            const auto& childItem = item.second;
            if (childItem) {
                childItem->Layout(innerLayout);
            }
        }
        SetLayoutSize(maxSize);
        contentWidth_ = GetLayoutSize().Width();
        contentHeight_ = GetLayoutSize().Height();
        if (isVertical_) {
            prevOffset_ = -contentHeight_;
            nextOffset_ = contentHeight_;
        } else {
            prevOffset_ = IsRightToLeft() ? contentWidth_ : -contentWidth_;
            nextOffset_ = IsRightToLeft() ? -contentWidth_ : contentWidth_;
        }
        Offset prevPosition = GetMainAxisOffset(prevOffset_);
        Offset nextPosition = GetMainAxisOffset(nextOffset_);

        for (const auto& item : contentMap_) {
            const auto& childItem = item.second;
            if (!childItem) {
                LOGW("The childItem is null");
                continue;
            }
            int32_t index = item.first;
            // make sure the new requested tab start with right position, when in animation
            if ((!isDragging_ && !isInAnimation_) || (index == requestedIndex_)) {
                if (index < currentIndex_) {
                    childItem->SetPosition(prevPosition);
                    childItem->SetHidden(true);
                } else if (index == currentIndex_) {
                    childItem->SetPosition(Offset::Zero());
                    childItem->SetHidden(false);
                } else {
                    childItem->SetPosition(nextPosition);
                    childItem->SetHidden(true);
                }
            }
        }
        requestedIndex_ = -1;
    }
}

void RenderTabContent::UpdateTouchRect()
{
    SetTouchRect(GetPaintRect());
}

} // namespace OHOS::Ace
