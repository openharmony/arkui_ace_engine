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

#include <memory>
#include <vector>

#include "base/log/log_wrapper.h"
#include "core/components_ng/relaxed_interaction/executors/fallback_executor.h"
#include "core/components_ng/relaxed_interaction/parsers/fallback_command_parser.h"
#include "core/components_ng/relaxed_interaction/utils/json_utils.h"

namespace OHOS::Ace::NG {

FallbackCommandParser::FallbackCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> FallbackCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    if (!json || !json->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Invalid fallback_cmd object");
        return executors;
    }

    if (!json->Contains("identity") || !json->Contains("body")) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid identity or body parsed");
        return executors;
    }

    auto body = json->GetValue("body");
    if (!body || !body->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid body value parsed");
        return executors;
    }

    auto identity = json->GetValue("identity");
    if (!identity) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid identity value parsed");
        return executors;
    }

    if (identity->IsString()) {
        executors.emplace_back(std::make_unique<FallbackExecutor>(context_, identity->GetString(), body->ToString()));
    } else if (JsonUtils::IsUint(identity)) {
        executors.emplace_back(std::make_unique<FallbackExecutor>(context_, identity->GetInt(), body->ToString()));
    } else {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Identity is not string or integer");
    }

    return executors;
}

} // namespace OHOS::Ace::NG
