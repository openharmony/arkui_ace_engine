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
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace::NG {

class PipelineContext;

RefPtr<LayoutAlgorithm> CreateLazyWaterFlowLayoutAlgorithm(const RefPtr<LazyWaterFlowLayoutInfo>& info,
    const RefPtr<FrameNode>& header, const RefPtr<FrameNode>& footer);
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
    return CreateLazyWaterFlowLayoutAlgorithm(layoutInfo_, GetHeaderNode(), GetFooterNode());
}

StickyStyle LazyWaterFlowLayoutPattern::GetStickyStyle() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, StickyStyle::NONE);
    auto layoutProperty = host->GetLayoutProperty<LazyWaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, StickyStyle::NONE);
    return layoutProperty->GetStickyStyle().value_or(StickyStyle::NONE);
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void LazyWaterFlowLayoutPattern::NotifyDataChange(int32_t index, int32_t count)
{
    CHECK_NULL_VOID(layoutInfo_);
    // Convert host index (which may include a header at slot 0) into item index for layoutInfo_.
    auto itemIndex = index - (header_.Upgrade() ? 1 : 0);
    layoutInfo_->NotifyDataChange(itemIndex, count);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

float LazyWaterFlowLayoutPattern::GetHeaderMainSize() const
{
    return layoutInfo_ ? layoutInfo_->headerMainSize_ : 0.0f;
}

float LazyWaterFlowLayoutPattern::GetFooterMainSize() const
{
    return layoutInfo_ ? layoutInfo_->footerMainSize_ : 0.0f;
}

void LazyWaterFlowLayoutPattern::OnModifyDone()
{
    LazyLayoutPattern::OnModifyDone();
    SyncHeaderFooter();
}

void LazyWaterFlowLayoutPattern::BeforeCreateLayoutWrapper()
{
    SyncHeaderFooter(false);
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
    if (layoutInfo_->totalItemCount_ <= 0 || layoutInfo_->visibleStartIndex_ < 0 ||
        layoutInfo_->visibleEndIndex_ < 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->visibleStartIndex_ >= layoutInfo_->totalItemCount_ ||
        layoutInfo_->visibleEndIndex_ >= layoutInfo_->totalItemCount_) {
        return { -1, -1 };
    }
    return { layoutInfo_->visibleStartIndex_, layoutInfo_->visibleEndIndex_ };
}

void LazyWaterFlowLayoutPattern::FireOnVisibleIndexesChange()
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    FireOnVisibleIndexesChange(GetVisibleIndexesRangeForCallback());
}

void LazyWaterFlowLayoutPattern::FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range)
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    if (range == lastVisibleIndexesRange_) {
        return;
    }
    onVisibleIndexesChange_(range.first, range.second);
    lastVisibleIndexesRange_ = range;
}

void LazyWaterFlowLayoutPattern::OnInActive()
{
    if (onVisibleIndexesChange_) {
        FireOnVisibleIndexesChange({ -1, -1 });
    }
    if (layoutInfo_) {
        layoutInfo_->deadline_.reset();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->IsActive()) {
        layoutInfo_->deadline_.reset();
        return;
    }
    if (!layoutInfo_->NeedPredict()) {
        return;
    }
    // Deadline crossed: re-post unconditionally so predict eventually catches up once main thread frees.
    if (GetSysTimestamp() > deadline) {
        PostIdleTask();
        return;
    }
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(host, true);
    layoutInfo_->deadline_.reset();
}

void LazyWaterFlowLayoutPattern::ResetVisibleIndexesChangeState()
{
    lastVisibleIndexesRange_ = { -2, -2 };
}

void LazyWaterFlowLayoutPattern::AddHeader(const RefPtr<UINode>& header)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!IsValidHeaderFooter(header, true)) {
        return;
    }
    HeaderFooterUtils::ReplaceHeaderFooter(host, header_, header, 0);
    SyncHeaderFooter();
}

void LazyWaterFlowLayoutPattern::AddFooter(const RefPtr<UINode>& footer)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!IsValidHeaderFooter(footer, false)) {
        return;
    }
    // Footer is appended on first mount; SyncHeaderFooter keeps it behind data nodes after LazyForEach updates.
    HeaderFooterUtils::ReplaceHeaderFooter(host, footer_, footer);
    SyncHeaderFooter();
}

bool LazyWaterFlowLayoutPattern::IsValidHeaderFooter(const RefPtr<UINode>& edge, bool isHeader) const
{
    CHECK_NULL_RETURN(edge, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (edge == host) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout rejects itself as header / footer");
        return false;
    }
    auto peerEdge = isHeader ? footer_.Upgrade() : header_.Upgrade();
    if (peerEdge && peerEdge == edge) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout rejects duplicated header/footer edge");
        return false;
    }
    auto currentEdge = isHeader ? header_.Upgrade() : footer_.Upgrade();
    if (currentEdge == edge) {
        return true;
    }
    auto parent = edge->GetParent();
    if (parent && parent != host) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout rejects header / footer with another parent");
        return false;
    }
    if (parent == host && currentEdge != edge) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout rejects existing child as header / footer");
        return false;
    }
    if (!HeaderFooterUtils::GetHeaderFooterFrameNode(edge)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout rejects header / footer without frame content");
        return false;
    }
    return true;
}

void LazyWaterFlowLayoutPattern::RemoveHeader()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    HeaderFooterUtils::RemoveHeaderFooter(host, header_);
}

void LazyWaterFlowLayoutPattern::RemoveFooter()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    HeaderFooterUtils::RemoveHeaderFooter(host, footer_);
}

RefPtr<FrameNode> LazyWaterFlowLayoutPattern::GetHeaderNode() const
{
    return HeaderFooterUtils::GetHeaderFooterFrameNode(header_);
}

RefPtr<FrameNode> LazyWaterFlowLayoutPattern::GetFooterNode() const
{
    return HeaderFooterUtils::GetHeaderFooterFrameNode(footer_);
}

void LazyWaterFlowLayoutPattern::SyncHeaderFooter(bool markDirty)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool needMeasure = false;

    // LazyForEach may append or remove data nodes after header/footer are mounted, so normalize edge positions before
    // every wrapper creation instead of relying only on the first mount order.
    auto header = header_.Upgrade();
    if (header) {
        auto headerIndex = host->GetChildIndex(header);
        if (headerIndex > 0) {
            header->MovePosition(0);
            needMeasure = true;
        }
        HeaderFooterUtils::UpdateEdgeAccessibility(header);
    }

    auto footer = footer_.Upgrade();
    if (footer) {
        auto footerIndex = host->GetChildIndex(footer);
        auto lastIndex = static_cast<int32_t>(host->GetChildren().size()) - 1;
        if (footerIndex >= 0 && footerIndex != lastIndex) {
            footer->MovePosition(lastIndex);
            needMeasure = true;
        }
        HeaderFooterUtils::UpdateEdgeAccessibility(footer);
    }

    if (needMeasure && markDirty) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
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
