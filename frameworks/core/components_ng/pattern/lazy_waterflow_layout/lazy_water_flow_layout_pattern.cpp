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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"

#include "base/log/log_wrapper.h"
#include "base/utils/time_util.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"

namespace OHOS::Ace::NG {

class PipelineContext;

RefPtr<LayoutAlgorithm> CreateLazyWaterFlowLayoutAlgorithm(const RefPtr<LazyWaterFlowLayoutInfo>& info);
void AddLazyWaterFlowPredictTask(PipelineContext* context, std::function<void(int64_t, bool)>&& task);

LazyWaterFlowLayoutPattern::LazyWaterFlowLayoutPattern()
{
    layoutInfo_ = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
}

RefPtr<LayoutProperty> LazyWaterFlowLayoutPattern::CreateLayoutProperty()
{
    return AceType::MakeRefPtr<LazyWaterFlowLayoutProperty>();
}

RefPtr<LayoutAlgorithm> LazyWaterFlowLayoutPattern::CreateLayoutAlgorithm()
{
    return CreateLazyWaterFlowLayoutAlgorithm(layoutInfo_);
}

FocusPattern LazyWaterFlowLayoutPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm LazyWaterFlowLayoutPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(ScopeFocusDirection::UNIVERSAL, false, true, ScopeType::OTHERS);
}

void LazyWaterFlowLayoutPattern::OnActive()
{
    idleDeadlineMissCount_ = 0;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void LazyWaterFlowLayoutPattern::NotifyDataChange(int32_t index, int32_t count)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->NotifyDataChange(index, count);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

AdjustOffset LazyWaterFlowLayoutPattern::GetAdjustOffset() const
{
    return layoutInfo_ ? layoutInfo_->adjustOffset_ : AdjustOffset();
}

AdjustOffset LazyWaterFlowLayoutPattern::GetAndResetAdjustOffset()
{
    CHECK_NULL_RETURN(layoutInfo_, AdjustOffset());
    auto ret = layoutInfo_->adjustOffset_;
    layoutInfo_->adjustOffset_ = AdjustOffset();
    return ret;
}

bool LazyWaterFlowLayoutPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    CHECK_NULL_RETURN(layoutInfo_, false);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<LazyWaterFlowLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    FireOnVisibleIndexesChange();
    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}

std::pair<int32_t, int32_t> LazyWaterFlowLayoutPattern::GetVisibleIndexesRangeForCallback() const
{
    if (!layoutInfo_) {
        return { -1, -1 };
    }
    if (layoutInfo_->totalItemCount_ <= 0 || layoutInfo_->startIndex_ < 0 || layoutInfo_->endIndex_ < 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->startIndex_ >= layoutInfo_->totalItemCount_ ||
        layoutInfo_->endIndex_ >= layoutInfo_->totalItemCount_) {
        return { -1, -1 };
    }
    return { layoutInfo_->startIndex_, layoutInfo_->endIndex_ };
}

void LazyWaterFlowLayoutPattern::FireOnVisibleIndexesChange()
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    FireOnVisibleIndexesChange(GetVisibleIndexesRangeForCallback());
}

void LazyWaterFlowLayoutPattern::FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range)
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    if (hasVisibleIndexesChangeFired_ && range == lastVisibleIndexesRange_) {
        return;
    }
    onVisibleIndexesChange_(range.first, range.second);
    lastVisibleIndexesRange_ = range;
    hasVisibleIndexesChangeFired_ = true;
}

void LazyWaterFlowLayoutPattern::OnInActive()
{
    if (onVisibleIndexesChange_) {
        FireOnVisibleIndexesChange({ -1, -1 });
    }
    ResetVisibleIndexesChangeState();
}

void LazyWaterFlowLayoutPattern::PostIdleTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    AddLazyWaterFlowPredictTask(context, [weak = WeakClaim(this)](int64_t deadline, bool) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ProcessIdleTask(deadline);
    });
}

void LazyWaterFlowLayoutPattern::ProcessIdleTask(int64_t deadline)
{
    CHECK_NULL_VOID(layoutInfo_);
    if (!layoutInfo_->NeedPredict()) {
        idleDeadlineMissCount_ = 0;
        return;
    }
    // Deadline crossed before we ran. Re-post up to MAX_IDLE_DEADLINE_MISS_COUNT times to absorb frame
    // boundary jitter; drop after that to avoid sustained main-thread contention.
    if (GetSysTimestamp() > deadline) {
        ++idleDeadlineMissCount_;
        if (idleDeadlineMissCount_ <= MAX_IDLE_DEADLINE_MISS_COUNT) {
            PostIdleTask();
        }
        return;
    }
    idleDeadlineMissCount_ = 0;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(host, true);
    layoutInfo_->deadline_.reset();
}

void LazyWaterFlowLayoutPattern::ResetVisibleIndexesChangeState()
{
    hasVisibleIndexesChangeFired_ = false;
    lastVisibleIndexesRange_ = { -2, -2 };
}

void LazyWaterFlowLayoutPattern::OnAttachToMainTree()
{
    LazyLayoutUtils::ValidateLazyLayoutParent(GetHost(), "LazyVWaterFlowLayout");
}

void LazyWaterFlowLayoutPattern::DumpAdvanceInfo()
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo();
}

void LazyWaterFlowLayoutPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo(json);
}

} // namespace OHOS::Ace::NG
