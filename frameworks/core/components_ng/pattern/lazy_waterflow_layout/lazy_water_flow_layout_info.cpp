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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"

#include <functional>

#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// Pipeline bridge helpers — kept here so model.cpp / pattern.cpp don't need pipeline_context.h.
void AddLazyWaterFlowPredictTask(PipelineContext* context, std::function<void(int64_t, bool)>&& task)
{
    CHECK_NULL_VOID(context);
    context->AddPredictTask(std::move(task));
}

void SetLazyWaterFlowCallbackNode(FrameNode* frameNode)
{
    PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
}

void LazyWaterFlowLayoutInfo::NotifyDataChange(int32_t /* index */, int32_t /* count */)
{
}

bool LazyWaterFlowLayoutInfo::NeedPredict() const
{
    return false;
}

void LazyWaterFlowLayoutInfo::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("itemStartIndex:" + std::to_string(startIndex_));
    DumpLog::GetInstance().AddDesc("itemEndIndex:" + std::to_string(endIndex_));
    DumpLog::GetInstance().AddDesc("itemTotalCount:" + std::to_string(totalItemCount_));
}

void LazyWaterFlowLayoutInfo::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(json);
    json->Put("itemStartIndex", startIndex_);
    json->Put("itemEndIndex", endIndex_);
    json->Put("itemTotalCount", totalItemCount_);
}

} // namespace OHOS::Ace::NG
