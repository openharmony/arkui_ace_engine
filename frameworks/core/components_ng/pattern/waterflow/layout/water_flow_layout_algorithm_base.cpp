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
std::list<int32_t> WaterFlowLayoutBase::LayoutCachedItem(
    LayoutWrapper* layoutWrapper, const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t cacheCount)
{
    std::list<int32_t> predictBuildList;
    auto currIndex = info->NodeIdx(info->endIndex_ + 1);
    auto totalCount = layoutWrapper->GetTotalChildCount();
    for (int32_t i = 0; i < cacheCount && currIndex + i < totalCount; ++i) {
        int32_t index = currIndex + i;
        auto wrapper = layoutWrapper->GetChildByIndex(index, true);
        if (!wrapper) {
            predictBuildList.emplace_back(index);
            continue;
        }
        wrapper->SetActive(false);
    }

    currIndex = info->NodeIdx(info->FirstIdx() - 1);
    for (int32_t i = 0; i < cacheCount && currIndex - i >= info->NodeIdx(0); ++i) {
        int32_t index = currIndex - i;
        auto wrapper = layoutWrapper->GetChildByIndex(index, true);
        if (!wrapper) {
            predictBuildList.emplace_back(index);
            continue;
        }
        wrapper->SetActive(false);
    }
    return predictBuildList;
}

void WaterFlowLayoutBase::PreBuildItems(LayoutWrapper* layoutWrapper, const RefPtr<WaterFlowLayoutInfoBase>& info,
    const LayoutConstraintF& constraint, int32_t cachedCount)
{
    if (cachedCount > 0) {
        auto items = LayoutCachedItem(layoutWrapper, info, cachedCount);
        if (!items.empty()) {
            PostIdleTask(layoutWrapper->GetHostNode(), { items, constraint });
        } else {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(host);
            auto pattern = host->GetPattern<WaterFlowPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPredictLayoutParam(std::nullopt);
        }
    }
}

bool WaterFlowLayoutBase::PredictBuildItem(RefPtr<LayoutWrapper> wrapper, const LayoutConstraintF& constraint)
{
    CHECK_NULL_RETURN(wrapper, false);
    wrapper->SetActive(false);

    auto frameNode = wrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(constraint);
    FrameNode::ProcessOffscreenNode(frameNode);
    return true;
}

void WaterFlowLayoutBase::PostIdleTask(RefPtr<FrameNode> frameNode, const PredictLayoutParam& param)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetPredictLayoutParam()) {
        pattern->SetPredictLayoutParam(param);
        return;
    }
    pattern->SetPredictLayoutParam(param);
    auto* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = WeakClaim(RawPtr(frameNode))](int64_t deadline, bool canUseLongPredictTask) {
        ACE_SCOPED_TRACE("WaterFlow predict");
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<WaterFlowPattern>();
        CHECK_NULL_VOID(pattern);
        if (!pattern->GetPredictLayoutParam().has_value()) {
            return;
        }
        bool needMarkDirty = false;
        auto param = pattern->GetPredictLayoutParam().value();
        for (auto it = param.items.begin(); it != param.items.end();) {
            if (GetSysTimestamp() > deadline) {
                break;
            }
            auto wrapper = frameNode->GetOrCreateChildByIndex(*it, false, true);
            if (wrapper && wrapper->GetHostNode() && !wrapper->GetHostNode()->RenderCustomChild(deadline)) {
                break;
            }
            needMarkDirty = PredictBuildItem(wrapper, param.layoutConstraint) || needMarkDirty;
            param.items.erase(it++);
        }
        if (needMarkDirty) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
        pattern->SetPredictLayoutParam(std::nullopt);
        if (!param.items.empty()) {
            WaterFlowLayoutBase::PostIdleTask(frameNode, param);
            pattern->SetPredictLayoutParam(param);
        }
    });
}

int32_t WaterFlowLayoutBase::GetUpdateIdx(LayoutWrapper* host, int32_t footerIdx)
{
    int32_t updateIdx = host->GetHostNode()->GetChildrenUpdated();
    if (updateIdx > 0 && footerIdx == 0) {
        --updateIdx;
    }
    return updateIdx;
}
} // namespace OHOS::Ace::NG
