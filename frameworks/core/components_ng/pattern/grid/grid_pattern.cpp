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

namespace OHOS::Ace::NG {

GridPattern::GridPattern()
{
    layoutController_ = MakeRefPtr<GridLayoutController>();
    layoutController_->SetMarkNeedRenderTask([wp = WeakClaim(this)] {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    });
}

void GridPattern::OnModifyDone()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);

    // update [layoutController_] using newest configuration
    layoutController_->isVertical_ = gridLayoutProperty->IsVertical();
    layoutController_->isConfiguredScrollable_ = gridLayoutProperty->IsConfiguredScrollable();
    std::vector<std::string> cols;
    StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
    std::vector<std::string> rows;
    StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);
    layoutController_->crossCount_ = cols.empty() ? Infinity<uint32_t>() : cols.size();
    layoutController_->mainCount_ = rows.empty() ? Infinity<uint32_t>() : rows.size();
    if (!layoutController_->isVertical_) {
        std::swap(layoutController_->crossCount_, layoutController_->mainCount_);
    }
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
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(layoutController_->GetAxis());
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto gridPattern = weak.Upgrade();
        if (!gridPattern) {
            LOGE("grid pattern upgrade fail when try handle scroll event.");
            return false;
        }
        return gridPattern->HandleScrollEvent(static_cast<float>(offset), source);
    };
    scrollableEvent_->SetScrollPositionCallback(std::move(scrollCallback));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool GridPattern::HandleScrollEvent(float offset, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return layoutController_->UpdateScrollPosition(static_cast<float>(offset), source);
}

} // namespace OHOS::Ace::NG