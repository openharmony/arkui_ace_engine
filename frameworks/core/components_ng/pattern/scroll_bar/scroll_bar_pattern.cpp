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

#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {

void ScrollBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->GetRenderContext()->SetClipToFrame(true);
}

void ScrollBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ScrollBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (axis_ == axis && scrollableEvent_) {
        LOGD("Direction not changed, need't resister scroll event again.");
        return;
    }

    axis_ = axis;
    displayMode_ = layoutProperty->GetDisplayMode().value_or(DisplayMode::AUTO);
    // scrollPosition callback
    auto offsetTask = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                return pattern->UpdateCurrentOffset(offset, source);
            }
            return false;
        }
        return true;
    };

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    scrollableEvent_->SetScrollPositionCallback(std::move(offsetTask));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool ScrollBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ScrollBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
    return false;
}

bool ScrollBarPattern::IsAtTop() const
{
    return LessOrEqual(currentOffset_, 0.0);
}

bool ScrollBarPattern::IsAtBottom() const
{
    return GreatOrEqual(currentOffset_, scrollableDistance_);
}

void ScrollBarPattern::ValidateOffset(int32_t source)
{
    if (scrollableDistance_ <= 0.0f) {
        return;
    }
    currentOffset_ = std::clamp(currentOffset_, 0.0f, scrollableDistance_);
}

bool ScrollBarPattern::UpdateCurrentOffset(float delta, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (NearZero(delta) || axis_ == Axis::NONE) {
        return false;
    }
    if ((IsAtBottom() && delta > 0.0f) || (IsAtTop() && delta < 0.0f)) {
        return false;
    }

    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    ValidateOffset(source);
    if (scrollBarProxy_ && lastOffset_ != currentOffset_) {
        scrollBarProxy_->NotifyScrollableNode(-delta, AceType::WeakClaim(this));
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    return true;
}

} // namespace OHOS::Ace::NG
