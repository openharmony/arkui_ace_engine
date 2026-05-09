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

#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"
#include "frameworks/base/utils/time_util.h"
#include <sstream>

namespace OHOS::Ace::NG {

WorkflowDumper& WorkflowDumper::GetInstance()
{
    static WorkflowDumper instance;
    return instance;
}

void WorkflowDumper::AddLog(const std::string& log)
{
    if (logs_.size() >= LIMIT) {
        logs_.pop_front();
    }

    int64_t createTime_ = GetCurrentTimestamp();
    logs_.push_back(ConvertTimestampToStr(createTime_) + " " + log);
}

std::string WorkflowDumper::Dump() const
{
    std::ostringstream buffer;
    buffer << "\n";
    for (const auto& log : logs_) {
        buffer << log << "\n";
    }

    return buffer.str();
}

} // namespace OHOS::Ace::NG