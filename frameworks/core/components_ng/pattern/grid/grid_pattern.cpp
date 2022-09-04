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

#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

void GridPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void GridPattern::OnModifyDone()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);
    gridLayoutInfo_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    AddScrollEvent();
}

void GridPattern::AddScrollEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(gridLayoutInfo_.axis_);
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto gridPattern = weak.Upgrade();
        if (!gridPattern) {
            LOGE("grid pattern upgrade fail when try handle scroll event.");
            return false;
        }
        return gridPattern->UpdateScrollPosition(static_cast<float>(offset), source);
    };
    scrollableEvent_->SetScrollPositionCallback(std::move(scrollCallback));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool GridPattern::UpdateScrollPosition(float offset, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    if (gridLayoutInfo_.reachEnd_) {
        if (LessOrEqual(offset, 0)) {
            return false;
        }
        gridLayoutInfo_.reachEnd_ = false;
    }
    if (gridLayoutInfo_.reachStart_) {
        if (GreatOrEqual(offset, 0.0)) {
            return false;
        }
        gridLayoutInfo_.reachStart_ = false;
    }
    gridLayoutInfo_.currentOffset_ += offset;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

bool GridPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto gridLayoutAlgorithm = DynamicCast<GridLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(gridLayoutAlgorithm, false);
    gridLayoutInfo_ = gridLayoutAlgorithm->GetGridLayoutInfo();
    return false;
}

} // namespace OHOS::Ace::NG