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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_COMMAND_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_COMMAND_PARSER_H

#include <memory>
#include <string>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/base_executor.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class BaseCommandParser {
public:
    explicit BaseCommandParser(WeakPtr<PipelineContext> context) : context_(context) {}
    virtual ~BaseCommandParser() = default;

    virtual std::vector<std::unique_ptr<BaseExecutor>> Parse(const std::unique_ptr<JsonValue>& json) = 0;

    std::string GetLastError() const
    {
        return lastError_;
    }

protected:
    WeakPtr<PipelineContext> context_;
    std::string lastError_;

    void SetLastError(const std::string& error);
    bool ValidateRequiredField(const std::unique_ptr<JsonValue>& json, const std::string& field);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_BASE_COMMAND_PARSER_H
