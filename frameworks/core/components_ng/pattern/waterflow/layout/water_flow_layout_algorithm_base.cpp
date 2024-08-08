/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
    const bool taskRegistered = pattern->HasPreloadList();
    pattern->SetPreloadList(GeneratePreloadList(info, host, cacheCount));
    pattern->SetCacheLayoutAlgo(Claim(this));
    if (taskRegistered) {
        return;
    }
    PostIdleTask(frameNode);
}

std::list<int32_t> WaterFlowLayoutBase::GeneratePreloadList(
    const RefPtr<WaterFlowLayoutInfoBase>& info, LayoutWrapper* host, int32_t cacheCount)
{
    std::list<int32_t> preloadList;
    auto currIndex = info->NodeIdx(info->endIndex_ + 1);
    auto totalCount = host->GetTotalChildCount();
    for (int32_t i = 0; i < cacheCount && currIndex + i < totalCount; ++i) {
        int32_t index = currIndex + i;
        if (!host->GetChildByIndex(index, true)) {
            preloadList.emplace_back(index);
        }
    }

    currIndex = info->NodeIdx(info->FirstIdx() - 1);
    for (int32_t i = 0; i < cacheCount && currIndex - i >= info->NodeIdx(0); ++i) {
        int32_t index = currIndex - i;
        if (!host->GetChildByIndex(index, true)) {
            preloadList.emplace_back(index);
        }
    }
    return preloadList;
}

void WaterFlowLayoutBase::PostIdleTask(const RefPtr<FrameNode>& frameNode)
{
    auto* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakPtr(frameNode)](int64_t deadline, bool canUseLongPredictTask) {
        ACE_SCOPED_TRACE("WaterFlow predict");
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern<WaterFlowPattern>();
        CHECK_NULL_VOID(pattern);

        auto&& algo = pattern->GetCacheLayoutAlgo();
        CHECK_NULL_VOID(algo);
        algo->StartCacheLayout();

        const auto& items = pattern->MovePreloadList();
        bool needMarkDirty = false;
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (GetSysTimestamp() > deadline) {
                pattern->SetPreloadList(std::list<int32_t>(it, items.end()));
                algo->PostIdleTask(host);
                return;
            }
            needMarkDirty |= algo->AppendCacheItem(RawPtr(host), *it);
        }
        if (needMarkDirty) {
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
        algo->EndCacheLayout();
    });
}
} // namespace OHOS::Ace::NG
