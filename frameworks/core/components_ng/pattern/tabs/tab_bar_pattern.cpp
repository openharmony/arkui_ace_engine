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

#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void TabBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void TabBarPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    // Init click event.
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            tabBar->HandleClick(info);
        }
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickEvent);

    // Init scrollable.
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    if (axis_ == axis && scrollableEvent_) {
        LOGD("Direction not changed, need't resister scroll event again.");
        return;
    }

    axis_ = axis;
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateCurrentOffset(static_cast<float>(offset));
            }
        }
        return true;
    };

    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    scrollableEvent_->SetScrollPositionCallback(std::move(task));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool TabBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto tabBarLayoutAlgorithm = DynamicCast<TabBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(tabBarLayoutAlgorithm, false);
    tabItemOffsets_ = tabBarLayoutAlgorithm->GetTabItemOffset();
    currentOffset_ = tabBarLayoutAlgorithm->GetCurrentOffset();
    return false;
}

void TabBarPattern::HandleClick(const GestureEvent& info) const
{
    LOGI("Click event x is %{public}lf", info.GetLocalLocation().GetX());
    if (tabItemOffsets_.empty()) {
        LOGW("tabItemOffsets is empty");
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto totalCount = host->TotalChildCount();

    OffsetF currentOffset = (axis == Axis::HORIZONTAL ? OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_));
    auto local = OffsetF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY()) - currentOffset;
    if (axis == Axis::VERTICAL) {
        auto clickRange = std::make_pair(tabItemOffsets_[0].GetY(), tabItemOffsets_[tabItemOffsets_.size() - 1].GetY());
        if (LessNotEqual(local.GetY(), clickRange.first) || GreatNotEqual(local.GetY(), clickRange.second)) {
            LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetY(),
                clickRange.first, clickRange.second);
            return;
        }
    } else {
        auto clickRange = std::make_pair(tabItemOffsets_[0].GetX(), tabItemOffsets_[tabItemOffsets_.size() - 1].GetX());
        if (!isRTL_) {
            if (LessNotEqual(local.GetX(), clickRange.first) || GreatNotEqual(local.GetX(), clickRange.second)) {
                LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetX(),
                    clickRange.first, clickRange.second);
                return;
            }
        } else {
            if (GreatNotEqual(local.GetX(), frameSize.MainSize(axis)) || LessNotEqual(local.GetX(), clickRange.second)) {
                LOGW("clicked (%{public}lf) position out of range [%{public}lf, %{public}lf]", local.GetX(),
                    clickRange.first, clickRange.second);
                return;
            }
        }
    }
    auto pos = std::lower_bound(tabItemOffsets_.begin(), tabItemOffsets_.end(), local,
        [axis, isRTL = isRTL_](const OffsetF& a, const OffsetF& b) {
            return isRTL ? GreatNotEqual(a.GetX(), b.GetX())
                : (axis == Axis::VERTICAL ? LessNotEqual(a.GetY(), b.GetY()) : LessNotEqual(a.GetX(), b.GetX()));
        });

    if (pos == tabItemOffsets_.end()) {
        return;
    }
    auto index = isRTL_ ? std::distance(tabItemOffsets_.begin(), pos)
        : std::distance(tabItemOffsets_.begin(), pos) - 1;
    if (index >= 0 && index < totalCount && swiperController_) {
        swiperController_->SwipeTo(index);
    }
}

void TabBarPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

} // namespace OHOS::Ace::NG
