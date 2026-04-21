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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_UTILS_WORKFLOW_DUMPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_UTILS_WORKFLOW_DUMPER_H

#include <deque>
#include <string>

namespace OHOS::Ace::NG {

class WorkflowDumper {
    static const int32_t LIMIT = 50;

public:
    WorkflowDumper(const WorkflowDumper&) = delete;
    WorkflowDumper& operator=(const WorkflowDumper&) = delete;

    static WorkflowDumper& GetInstance();

    void AddLog(const std::string& log);
    std::string Dump() const;

private:
    WorkflowDumper() = default;
    std::deque<std::string> logs_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_UTILS_WORKFLOW_DUMPER_H