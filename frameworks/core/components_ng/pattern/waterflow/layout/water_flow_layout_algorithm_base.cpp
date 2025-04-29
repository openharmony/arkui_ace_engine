/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"

#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
void WaterFlowLayoutBase::PreloadItems(
    LayoutWrapper* host, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cacheCount)
{
    if (cacheCount <= 0) {
        return;
    }
    auto frameNode = host->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    const bool taskRegistered = !pattern->PreloadListEmpty();
    pattern->SetPreloadList(GeneratePreloadList(info, host, cacheCount, false));
    if (pattern->PreloadListEmpty()) {
        return;
    }

    pattern->SetCacheLayoutAlgo(Claim(this));
    if (taskRegistered) {
        return;
    }
    PostIdleTask(frameNode);
}

void WaterFlowLayoutBase::SyncPreloadItems(
    LayoutWrapper* host, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cacheCount)
{
    auto list = GeneratePreloadList(info, host, cacheCount, true);
    if (list.empty()) {
        return;
    }

    StartCacheLayout();
    for (auto&& item : list) {
        SyncPreloadItem(host, item);
    }
    EndCacheLayout();
}

std::list<int32_t> WaterFlowLayoutBase::GeneratePreloadList(
    const RefPtr<WaterFlowLayoutInfoBase>& info, LayoutWrapper* host, int32_t cacheCount, bool force)
{
    std::list<int32_t> preloadList;
    if (info->startIndex_ > info->endIndex_) {
        return preloadList;
    }
    const int32_t endBound = std::min(info->ItemCnt(info->GetChildrenCount()) - 1, info->endIndex_ + cacheCount);
    for (int32_t i = info->endIndex_ + 1; i <= endBound; ++i) {
        if (force || !host->GetChildByIndex(info->NodeIdx(i), true)) {
            preloadList.emplace_back(i);
        }
    }

    const int32_t startBound = std::max(0, info->startIndex_ - cacheCount);
    for (int32_t i = info->startIndex_ - 1; i >= startBound; --i) {
        if (force || !host->GetChildByIndex(info->NodeIdx(i), true)) {
            preloadList.emplace_back(i);
        }
    }
    return preloadList;
}

void WaterFlowLayoutBase::PostIdleTask(const RefPtr<FrameNode>& frameNode)
{
    auto* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakPtr(frameNode)](int64_t deadline, bool canUseLongPredictTask) {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<WaterFlowPattern>();
        CHECK_NULL_VOID(pattern);

        auto&& algo = pattern->GetCacheLayoutAlgo();
        CHECK_NULL_VOID(algo);
        algo->StartCacheLayout();

        ScopedLayout scope(host->GetContext());
        bool needMarkDirty = false;
        auto items = pattern->MovePreloadList();
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (GetSysTimestamp() > deadline) {
                pattern->SetPreloadList(std::list<int32_t>(it, items.end()));
                PostIdleTask(host);
                break;
            }
            ACE_SCOPED_TRACE("Preload FlowItem %d", *it);
            needMarkDirty |= algo->PreloadItem(RawPtr(host), *it, deadline);
        }
        if (needMarkDirty) {
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
        algo->EndCacheLayout();
    });
}

int32_t WaterFlowLayoutBase::GetUpdateIdx(LayoutWrapper* host, int32_t footerIdx)
{
    int32_t updateIdx = host->GetHostNode()->GetChildrenUpdated();
    if (updateIdx >= 0 && footerIdx == 0) {
        --updateIdx;
    }
    return updateIdx;
}

void WaterFlowLayoutBase::UpdateOverlay(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetFadingEdge().value_or(false)) {
        return;
    }
    auto overlayNode = frameNode->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto overlayGeometryNode = overlayNode->GetGeometryNode();
    CHECK_NULL_VOID(overlayGeometryNode);
    overlayGeometryNode->SetFrameSize(geometryNode->GetFrameSize());
}

void WaterFlowLayoutBase::GetExpandArea(
    const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const RefPtr<WaterFlowLayoutInfoBase>& info)
{
    auto&& safeAreaOpts = layoutProperty->GetSafeAreaExpandOpts();
    expandSafeArea_ = safeAreaOpts && safeAreaOpts->Expansive();
    info->expandHeight_ = ScrollableUtils::CheckHeightExpansion(layoutProperty, layoutProperty->GetAxis());
}
} // namespace OHOS::Ace::NG
