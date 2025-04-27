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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_INSPRCTOR_TREE_COLLECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_INSPRCTOR_TREE_COLLECTOR_H

#include <list>

#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/ui_node.h"
#include "interfaces/inner_api/ace/ui_event_observer.h"

namespace OHOS::Ace::Recorder {
class InspectorTreeCollector final : public std::enable_shared_from_this<InspectorTreeCollector> {
public:
    InspectorTreeCollector(OnInspectorTreeResult&& callback, bool isBackground);
    ~InspectorTreeCollector() = default;
    void IncreaseTaskNum();
    void DecreaseTaskNum();
    void CreateJson();
    std::unique_ptr<JsonValue>& GetJson();
    void RetainNode(const RefPtr<NG::UINode>& node);
    void SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor);

private:
    void UpdateTaskNum(int32_t num);

    std::unique_ptr<JsonValue> root_;
    int32_t taskNum_ = 0;
    OnInspectorTreeResult onResultFunc_;
    bool isBackground_;
    std::mutex mutex_;

    RefPtr<TaskExecutor> taskExecutor_;
    std::list<RefPtr<NG::UINode>> cacheNodes_;
};
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_INSPRCTOR_TREE_COLLECTOR_H
