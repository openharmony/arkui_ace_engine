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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_GENERATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_GENERATOR_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {

class BaseExecutor;
class BaseCommandParser;
class PipelineContext;

class ExecutorGenerator {
public:
    explicit ExecutorGenerator(WeakPtr<PipelineContext> context);
    ~ExecutorGenerator();

    std::vector<std::unique_ptr<BaseExecutor>> ParseCommand(const std::unique_ptr<JsonValue>& json);

    std::string GetLastError() const
    {
        return lastError_;
    }

private:
    void RegisterDefaultParsers();

    std::vector<std::unique_ptr<BaseExecutor>> ParseFallbackCmd(const std::unique_ptr<JsonValue>& json);

    std::vector<std::unique_ptr<BaseExecutor>> ParseRegularCmd(const std::unique_ptr<JsonValue>& json);

    WeakPtr<PipelineContext> context_;
    std::unordered_map<std::string, std::unique_ptr<BaseCommandParser>> parserRegistry_;
    std::string lastError_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_GENERATOR_H
