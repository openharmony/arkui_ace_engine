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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

LazyGridLayoutPattern::~LazyGridLayoutPattern() = default;

RefPtr<LayoutProperty> LazyGridLayoutPattern::CreateLayoutProperty()
{
    return MakeRefPtr<LazyGridLayoutProperty>();
}

AdjustOffset LazyGridLayoutPattern::GetAdjustOffset() const
{
    CHECK_NULL_RETURN(layoutInfo_, AdjustOffset());
    return layoutInfo_->adjustOffset_;
}

AdjustOffset LazyGridLayoutPattern::GetAndResetAdjustOffset()
{
    CHECK_NULL_RETURN(layoutInfo_, AdjustOffset());
    AdjustOffset ret = layoutInfo_->adjustOffset_;
    layoutInfo_->adjustOffset_ = AdjustOffset();
    return ret;
}

RefPtr<LayoutAlgorithm> LazyGridLayoutPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo_);
    layoutAlgorithm->SetAxis(axis_);
    // DynamicLayout support: set flag if DynamicLayout
    // Alignment is now obtained from common properties (PositionProperty), no need to pass separately
    if (isDynamicLayout_) {
        layoutAlgorithm->SetDynamicLayout(true);
    }
    return layoutAlgorithm;
}

FocusPattern LazyGridLayoutPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm LazyGridLayoutPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(ScopeFocusDirection::UNIVERSAL, false, true,
        ScopeType::OTHERS);
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
    FireOnVisibleIndexesChange();
    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}

std::pair<int32_t, int32_t> LazyGridLayoutPattern::GetVisibleIndexesRangeForCallback() const
{
    if (!layoutInfo_) {
        return { -1, -1 };
    }
    auto totalItemCount = layoutInfo_->totalItemCount_;
    if (totalItemCount <= 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->startIndex_ < 0 || layoutInfo_->endIndex_ < 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->startIndex_ >= totalItemCount || layoutInfo_->endIndex_ >= totalItemCount) {
        return { -1, -1 };
    }
    return { layoutInfo_->startIndex_, layoutInfo_->endIndex_ };
}

void LazyGridLayoutPattern::FireOnVisibleIndexesChange()
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    auto currentRange = GetVisibleIndexesRangeForCallback();
    FireOnVisibleIndexesChange(currentRange);
}

void LazyGridLayoutPattern::FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range)
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    auto currentRange = range;
    if (hasVisibleIndexesChangeFired_ && currentRange == lastVisibleIndexesRange_) {
        return;
    }
    onVisibleIndexesChange_(currentRange.first, currentRange.second);
    lastVisibleIndexesRange_ = currentRange;
    hasVisibleIndexesChangeFired_ = true;
}

void LazyGridLayoutPattern::OnInActive()
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    FireOnVisibleIndexesChange({ -1, -1 });
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

bool LazyGridLayoutPattern::IsDynamicLayout() const
{
    return isDynamicLayout_;
}

void LazyGridLayoutPattern::OnAttachToMainTree()
{
    if (isDynamicLayout_) {
        return;
    }
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
        if (LazyLayoutUtils::IsAllowedIntermediateNode(parent)) {
            frameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }
        if (parent->GetTag() == V2::WATERFLOW_ETS_TAG || LazyLayoutUtils::IsVerticalScrollableParent(parent)) {
            return;
        }
        LOGF_ABORT("LazyGridLayout cannot be used under the %{public}s", parent->GetTag().c_str());
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
