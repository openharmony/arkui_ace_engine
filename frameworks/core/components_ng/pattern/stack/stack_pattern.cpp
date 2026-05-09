/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/stack/stack_pattern.h"

#include "core/components_ng/event/overflow_scroll_event_hub.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"

namespace OHOS::Ace::NG {
RefPtr<EventHub> StackPattern::CreateEventHub()
{
    return MakeRefPtr<OverflowScrollEventHub>();
}

RefPtr<VerticalOverflowHandler> StackPattern::GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host)
{
    if (!vOverflowHandler_) {
        vOverflowHandler_ = MakeRefPtr<VerticalOverflowHandler>(host);
    }
    return vOverflowHandler_;
}

void StackPattern::PostAsyncLoadTask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    context->AddAsyncLoadTask([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->prevMeasureBreak_) {
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    });
}

bool StackPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto stackLayoutAlgorithm = DynamicCast<StackLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(stackLayoutAlgorithm, false);
    prevMeasureBreak_ = stackLayoutAlgorithm->MeasureInNextFrame();
    if (prevMeasureBreak_) {
        ACE_SCOPED_TRACE("Stack MeasureInNextFrame");
        PostAsyncLoadTask();
    }
    return true;
}

void StackPattern::DumpInfo()
{
    if (vOverflowHandler_) {
        DumpLog::GetInstance().AddDesc(std::string("OverflowInfo: ").append(vOverflowHandler_->ToString().c_str()));
    }
}
} // namespace OHOS::Ace::NG