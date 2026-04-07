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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_PARSERS_CONTENT_SWITCH_COMMAND_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_PARSERS_CONTENT_SWITCH_COMMAND_PARSER_H

#include "base/json/json_util.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/base_command_parser.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"

namespace OHOS::Ace::NG {

class PipelineContext;
class BaseExecutor;

class ContentSwitchCommandParser : public BaseCommandParser {
public:
    explicit ContentSwitchCommandParser(WeakPtr<PipelineContext> context);
    ~ContentSwitchCommandParser() override = default;

    std::vector<std::unique_ptr<BaseExecutor>> Parse(const std::unique_ptr<JsonValue>& json) override;

private:
    struct ActionInfo {
        std::string direction;
        int32_t count;
    };

    bool ValidateBasicJson(const std::unique_ptr<JsonValue>& json);
    bool ValidateType(const std::unique_ptr<JsonValue>& json);
    ActionInfo ParseActionInfo(const std::unique_ptr<JsonValue>& actionJson);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_PARSERS_CONTENT_SWITCH_COMMAND_PARSER_H
