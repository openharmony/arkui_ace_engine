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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool LazyColumnLayoutPattern::IsAtomicNode() const
{
    return false;
}

RefPtr<LayoutProperty> LazyColumnLayoutPattern::CreateLayoutProperty()
{
    return MakeRefPtr<LazyColumnLayoutProperty>();
}

RefPtr<LayoutAlgorithm> LazyColumnLayoutPattern::CreateLayoutAlgorithm()
{
    auto algorithm = MakeRefPtr<LazyColumnLayoutAlgorithm>(layoutInfo_);
    algorithm->SetHeader(GetHeaderNode());
    algorithm->SetFooter(GetFooterNode());
    return algorithm;
}

StickyStyle LazyColumnLayoutPattern::GetStickyStyle() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, StickyStyle::NONE);
    auto layoutProperty = host->GetLayoutProperty<LazyColumnLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, StickyStyle::NONE);
    return layoutProperty->GetStickyStyle().value_or(StickyStyle::NONE);
}

FocusPattern LazyColumnLayoutPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm LazyColumnLayoutPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(ScopeFocusDirection::UNIVERSAL, false, true, ScopeType::OTHERS);
}

float LazyColumnLayoutPattern::GetHeaderMainSize() const
{
    return layoutInfo_ ? layoutInfo_->headerMainSize_ : 0.0f;
}

float LazyColumnLayoutPattern::GetFooterMainSize() const
{
    return layoutInfo_ ? layoutInfo_->footerMainSize_ : 0.0f;
}

void LazyColumnLayoutPattern::OnModifyDone()
{
    LazyLayoutPattern::OnModifyDone();
    SyncHeaderFooter();
}

void LazyColumnLayoutPattern::BeforeCreateLayoutWrapper()
{
    SyncHeaderFooter(false);
}

AdjustOffset LazyColumnLayoutPattern::GetAdjustOffset() const
{
    return layoutInfo_->adjustOffset_;
}

AdjustOffset LazyColumnLayoutPattern::GetAndResetAdjustOffset()
{
    AdjustOffset ret = layoutInfo_->adjustOffset_;
    layoutInfo_->adjustOffset_ = AdjustOffset();
    return ret;
}

void LazyColumnLayoutPattern::SetOnVisibleIndexesChange(std::function<void(int32_t, int32_t)>&& onVisibleIndexesChange)
{
    onVisibleIndexesChange_ = std::move(onVisibleIndexesChange);
}

bool LazyColumnLayoutPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<LazyColumnLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();
    FireOnVisibleIndexesChange();
    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}

std::pair<int32_t, int32_t> LazyColumnLayoutPattern::GetVisibleIndexesRangeForCallback() const
{
    if (!layoutInfo_) {
        return { -1, -1 };
    }
    auto totalItemCount = layoutInfo_->totalItemCount_;
    if (totalItemCount <= 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->visibleStartIndex_ < 0 || layoutInfo_->visibleEndIndex_ < 0) {
        return { -1, -1 };
    }
    if (layoutInfo_->visibleStartIndex_ >= totalItemCount || layoutInfo_->visibleEndIndex_ >= totalItemCount) {
        return { -1, -1 };
    }
    return { layoutInfo_->visibleStartIndex_, layoutInfo_->visibleEndIndex_ };
}

void LazyColumnLayoutPattern::FireOnVisibleIndexesChange()
{
    CHECK_NULL_VOID(onVisibleIndexesChange_);
    auto currentRange = GetVisibleIndexesRangeForCallback();
    if (hasVisibleIndexesFired_ && currentRange == lastVisibleIndexesRange_) {
        return;
    }
    onVisibleIndexesChange_(currentRange.first, currentRange.second);
    lastVisibleIndexesRange_ = currentRange;
    hasVisibleIndexesFired_ = true;
}

void LazyColumnLayoutPattern::PostIdleTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask(
        [weak = WeakClaim(this)](int64_t deadline, bool canUseLongPredictTask) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessIdleTask(deadline);
        });
}

void LazyColumnLayoutPattern::ProcessIdleTask(int64_t deadline)
{
    if (!layoutInfo_->NeedPredict()) {
        return;
    }
    if (GetSysTimestamp() > deadline) {
        PostIdleTask();
        return;
    }
    ACE_SCOPED_TRACE("LazyColumnIdleTask");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    layoutInfo_->deadline_ = deadline;
    FrameNode::ProcessOffscreenNode(GetHost(), true);
}

void LazyColumnLayoutPattern::AddHeader(const RefPtr<UINode>& header)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!IsValidHeaderFooter(header, true)) {
        return;
    }
    HeaderFooterUtils::ReplaceHeaderFooter(host, header_, header, 0);
    SyncHeaderFooter();
}

void LazyColumnLayoutPattern::AddFooter(const RefPtr<UINode>& footer)
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

bool LazyColumnLayoutPattern::IsValidHeaderFooter(const RefPtr<UINode>& edge, bool isHeader) const
{
    CHECK_NULL_RETURN(edge, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (edge == host) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects itself as header / footer");
        return false;
    }
    auto peerEdge = isHeader ? footer_.Upgrade() : header_.Upgrade();
    if (peerEdge && peerEdge == edge) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects duplicated header/footer edge");
        return false;
    }
    auto currentEdge = isHeader ? header_.Upgrade() : footer_.Upgrade();
    if (currentEdge == edge) {
        return true;
    }
    auto parent = edge->GetParent();
    if (parent && parent != host) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects header / footer with another parent");
        return false;
    }
    if (parent == host && currentEdge != edge) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects existing child as header / footer");
        return false;
    }
    if (!HeaderFooterUtils::GetHeaderFooterFrameNode(edge)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout rejects header / footer without frame content");
        return false;
    }
    return true;
}

void LazyColumnLayoutPattern::RemoveHeader()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    HeaderFooterUtils::RemoveHeaderFooter(host, header_);
}

void LazyColumnLayoutPattern::RemoveFooter()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    HeaderFooterUtils::RemoveHeaderFooter(host, footer_);
}

RefPtr<FrameNode> LazyColumnLayoutPattern::GetHeaderNode() const
{
    return HeaderFooterUtils::GetHeaderFooterFrameNode(header_);
}

RefPtr<FrameNode> LazyColumnLayoutPattern::GetFooterNode() const
{
    return HeaderFooterUtils::GetHeaderFooterFrameNode(footer_);
}

void LazyColumnLayoutPattern::SyncHeaderFooter(bool markDirty)
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

void LazyColumnLayoutPattern::OnAttachToMainTree()
{
    LazyLayoutUtils::ValidateLazyLayoutParent(GetHost(), "LazyColumnLayout");
}

void LazyColumnLayoutPattern::DumpAdvanceInfo()
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo();
}

void LazyColumnLayoutPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo(json);
}
} // namespace OHOS::Ace::NG
