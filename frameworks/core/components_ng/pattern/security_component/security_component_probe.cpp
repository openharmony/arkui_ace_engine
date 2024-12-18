/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/security_component/security_component_probe.h"

#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "core/components_ng/pattern/security_component/security_component_log.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint64_t MAX_CALLBACK_WAITING_TIME = 500; // 500ms
}

void SecurityComponentProbe::InitProbeTask()
{
    if (taskExec_.has_value()) {
        return;
    }
    tmux_.lock();
    if (taskExec_.has_value()) {
        tmux_.unlock();
        return;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    taskExec_ = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    tmux_.unlock();
    return;
}

int32_t SecurityComponentProbe::GetComponentInfo(int32_t nodeId, std::string& compInfoStr)
{
    if (!taskExec_.has_value()) {
        SC_LOG_WARN("callback task do not exist.");
        return -1;
    }
    if (!tmux_.try_lock_for(std::chrono::milliseconds(MAX_CALLBACK_WAITING_TIME))) {
        SC_LOG_WARN("callback task timeout.");
        return -1;
    }
    int taskRes;
    taskExec_.value().PostSyncTask(
        [nodeId, &compInfoStr, &taskRes] {
            auto node = AceType::DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(nodeId));
            if (!node) {
                SC_LOG_WARN("node do not exist.");
                taskRes = -1;
                return;
            }

            if ((node->GetTag() != V2::LOCATION_BUTTON_ETS_TAG) && (node->GetTag() != V2::PASTE_BUTTON_ETS_TAG) &&
                (node->GetTag() != V2::SAVE_BUTTON_ETS_TAG)) {
                SC_LOG_WARN("node is not security component.");
                taskRes = -1;
                return;
            }
            Security::SecurityComponent::SecCompType scType;
            if (!SecurityComponentHandler::InitButtonInfo(compInfoStr, node, scType)) {
                SC_LOG_WARN("node init info failed.");
                taskRes = -1;
                return;
            }
            taskRes = 0;
        },
        "ArkUISecurityComponentInitButtonInfo");
    tmux_.unlock();
    return taskRes;
}
} // namespace OHOS::Ace::NG
