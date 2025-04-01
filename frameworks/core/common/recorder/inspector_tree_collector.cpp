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
#include "core/common/recorder/inspector_tree_collector.h"

#include <memory>
#include <string>

namespace OHOS::Ace::Recorder {
InspectorTreeCollector::InspectorTreeCollector(OnInspectorTreeResult&& callback, bool isBackground)
    : onResultFunc_(std::move(callback)), isBackground_(isBackground)
{
    root_ = JsonUtil::Create(true);
}

void InspectorTreeCollector::IncreaseTaskNum()
{
    if (isBackground_) {
        std::unique_lock<std::mutex> lock(mutex_);
        UpdateTaskNum(1);
    } else {
        UpdateTaskNum(1);
    }
}

void InspectorTreeCollector::DecreaseTaskNum()
{
    if (isBackground_) {
        std::unique_lock<std::mutex> lock(mutex_);
        UpdateTaskNum(-1);
    } else {
        UpdateTaskNum(-1);
    }
}

void InspectorTreeCollector::UpdateTaskNum(int32_t num)
{
    taskNum_ += num;
    if (taskNum_ == 0) {
        if (!root_) {
            return;
        }
        if (!onResultFunc_) {
            root_ = JsonUtil::Create(true);
            return;
        }
        onResultFunc_(std::make_shared<std::string>(root_->ToString()));
        root_ = JsonUtil::Create(true);
        if (taskExecutor_ && isBackground_) {
            taskExecutor_->PostTask(
                [collector = shared_from_this()]() {
                    collector->cacheNodes_.clear();
                },
                TaskExecutor::TaskType::UI, "InspectorTreeCollector");
        }
    }
}

void InspectorTreeCollector::CreateJson()
{
    root_ = JsonUtil::Create(true);
}

std::unique_ptr<JsonValue>& InspectorTreeCollector::GetJson()
{
    return root_;
}

void InspectorTreeCollector::RetainNode(const RefPtr<NG::UINode>& node)
{
    cacheNodes_.emplace_back(node);
}

void InspectorTreeCollector::SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor)
{
    taskExecutor_ = taskExecutor;
}
} // namespace OHOS::Ace::Recorder
