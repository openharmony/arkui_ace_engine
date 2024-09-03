/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/transparent_node_detector.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DELAY_TIME = 1000;
} // namespace

TransparentNodeDetector& TransparentNodeDetector::GetInstance()
{
    static TransparentNodeDetector instance;
    return instance;
}


void TransparentNodeDetector::PostCheckNodeTransparentTask(const RefPtr<FrameNode>& node, uint8_t detectCount)
{
    if (detectCount > TransparentNodeDetector::MAX_DETECT_COUNT || detectCount == 0) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    detectCount--;
    auto task = [weakNode = AceType::WeakClaim(AceType::RawPtr(node)), taskDetectCount = detectCount]() {
        auto currentNode = weakNode.Upgrade();
        CHECK_NULL_VOID(currentNode);
        auto host = currentNode->GetHostNode();
        CHECK_NULL_VOID(host);

        if (host->IsContextTransparent()) {
            if (taskDetectCount > 0) {
                LOGW("TransparentNodeDetector try again");
                TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(currentNode, taskDetectCount);
                return;
            }
            LOGW("TransparentNodeDetector transparent node detected");
        }
    };
    executor->PostDelayedTask(std::move(task), TaskExecutor::TaskType::UI, DELAY_TIME,
        "ArkUINodeCheckContextTransparent");
}
} // namespace OHOS::Ace::NG

