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

#include "core/components_ng/relaxed_interaction/parsers/backpress_command_parser.h"

#include <memory>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/executors/backpress_executor.h"

namespace OHOS::Ace::NG {

BackpressCommandParser::BackpressCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> BackpressCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    (void)json;
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.emplace_back(std::make_unique<BackpressExecutor>(context_));
    return executors;
}

} // namespace OHOS::Ace::NG
