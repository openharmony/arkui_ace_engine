/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"

#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<LayoutAlgorithm> LazyGridLayoutPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo_);
    layoutAlgorithm->SetAxis(axis_);
    return layoutAlgorithm;
}

bool LazyGridLayoutPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<LazyGridLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}

void LazyGridLayoutPattern::PostIdleTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakClaim(this)]
        (int64_t deadline, bool canUseLongPredictTask) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessIdleTask(deadline);
        }
    );
}

void LazyGridLayoutPattern::ProcessIdleTask(int64_t deadline)
{
    if (!layoutInfo_->NeedPredict()) {
        return;
    }
    if (GetSysTimestamp() > deadline) {
        PostIdleTask();
        return;
    }
    ACE_SCOPED_TRACE("LazyGridIdleTask");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(GetHost(), true);
    layoutInfo_->deadline_.reset();
}

void LazyGridLayoutPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedLazyLayout(true);
    auto parent = host->GetParent();
    while (parent) {
        auto frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            parent = parent->GetParent();
            continue;
        }
        if (parent->GetTag() == V2::COMMON_VIEW_ETS_TAG || parent->GetTag() == V2::NODE_CONTAINER_ETS_TAG ||
            parent->GetTag() == "BuilderProxyNode" || parent->GetTag() == V2::FLOW_ITEM_ETS_TAG) {
            frameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }
        return;
    }
}

void LazyGridLayoutPattern::DumpAdvanceInfo()
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo();
}

void LazyGridLayoutPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo(json);
}
} // namespace OHOS::Ace::NG
