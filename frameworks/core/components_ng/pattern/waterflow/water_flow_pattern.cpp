/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"

namespace OHOS::Ace::NG {
bool WaterFlowPattern::UpdateCurrentOffset(float delta, int32_t /* source */)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    if (layoutProperty->IsReverse()) {
        delta = -delta;
    }
    if (layoutInfo_.itemStart_ && delta > 0) {
        return false;
    }
    if (layoutInfo_.offsetEnd_ && delta < 0) {
        return false;
    }
    layoutInfo_.prevOffset_ = layoutInfo_.currentOffset_;
    layoutInfo_.currentOffset_ += delta;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
};
bool WaterFlowPattern::IsAtTop() const
{
    return layoutInfo_.itemStart_;
};
bool WaterFlowPattern::IsAtBottom() const
{
    return layoutInfo_.offsetEnd_;
};
void WaterFlowPattern::UpdateScrollBarOffset() {};

RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    return AceType::MakeRefPtr<WaterFlowLayoutAlgorithm>(layoutInfo_);
}

void WaterFlowPattern::OnModifyDone()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // SetAxis for scroll event
    SetAxis(layoutProperty->GetAxis());
    AddScrollEvent();
}

bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto gridLayoutAlgorithm = DynamicCast<WaterFlowLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(gridLayoutAlgorithm, false);
    auto layoutInfo = gridLayoutAlgorithm->GetLayoutInfo();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (layoutInfo.itemStart_ && !layoutInfo_.itemStart_) {
        // onReachStart
        auto onReachStart = eventHub->GetOnReachStart();
        if (onReachStart) {
            onReachStart();
        }
    }
    if (layoutInfo.offsetEnd_ && !layoutInfo_.offsetEnd_) {
        // onReachEnd
        auto onReachEnd = eventHub->GetOnReachEnd();
        if (onReachEnd) {
            onReachEnd();
        }
    }
    layoutInfo_ = std::move(layoutInfo);
    return false;
}

void WaterFlowPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

void WaterFlowPattern::SetPositionController(RefPtr<WaterFlowPositionController> control)
{
    controller_ = control;
    if (control) {
        control->SetScrollPattern(AceType::WeakClaim<WaterFlowPattern>(this));
    }
}

bool WaterFlowPattern::UpdateStartIndex(int32_t index)
{
    layoutInfo_.jumpIndex_ = index + layoutInfo_.footerIndex_ + 1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}
} // namespace OHOS::Ace::NG
