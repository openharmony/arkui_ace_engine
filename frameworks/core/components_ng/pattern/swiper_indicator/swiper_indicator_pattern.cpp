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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SwiperIndicatorPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void SwiperIndicatorPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    auto requestCallBack = [weak = WeakClaim(this), host, swiperPattern](const BaseEventInfo* /*info*/) {
        auto pattern = weak.Upgrade();
        auto paintMethod = pattern->GetPaintMethod();
        CHECK_NULL_VOID(paintMethod);
        paintMethod->SetCurrentIndex(swiperPattern->GetCurrentIndex());
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    swiperEventHub->SetIndicatorOnChange(requestCallBack);
}

void SwiperIndicatorPattern::SetIndicatorSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperGeometryNode = swiperNode->GetGeometryNode();
    CHECK_NULL_VOID(swiperGeometryNode);
    auto frameSize = swiperGeometryNode->GetFrameSize();
    float width = frameSize.Width();
    float height = frameSize.Height();

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    itemCount_ = swiperPattern->TotalCount();
    SetItemCount(itemCount_);
    axis_ = swiperPattern->GetDirection();
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    if (swiperLayoutProperty->GetShowIndicator().has_value()) {
        showIndicator_ = swiperLayoutProperty->GetShowIndicator().value_or(true);
    }

    auto indicatorNode = DynamicCast<FrameNode>(host);
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorGeometryNode = indicatorNode->GetGeometryNode();
    CHECK_NULL_VOID(indicatorGeometryNode);
    auto indicatorFrameSize = indicatorGeometryNode->GetFrameSize();
    auto indicatorWidth = indicatorFrameSize.Width();
    auto indicatorHeight = indicatorFrameSize.Height();
    if (indicatorHeight > height) {
        indicatorHeight = height;
    }
    if (indicatorWidth > width) {
        indicatorWidth = width;
    }

    indicatorGeometryNode->SetFrameSize(SizeF { indicatorWidth, indicatorHeight });
}

bool SwiperIndicatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    SetIndicatorSize();
    return true;
}

} // namespace OHOS::Ace::NG
