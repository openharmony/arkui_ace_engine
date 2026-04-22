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
#include "core/components_ng/relaxed_interaction/executors/strict_content_switch_executor.h"
#include "core/components_ng/relaxed_interaction/parsers/content_switch_command_parser.h"
#include "core/components_ng/relaxed_interaction/utils/json_utils.h"

namespace OHOS::Ace::NG {

ContentSwitchCommandParser::ContentSwitchCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> ContentSwitchCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    if (!ValidateBasicJson(json) || !ValidateType(json)) {
        return {};
    }

    std::string mode = json->Contains("mode") ? json->GetString("mode") : "target";
    if (mode != "target") {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Parsed mode is not target");
        return {};
    }

    auto actionJson = json->GetValue("action_info");
    if (!actionJson || !actionJson->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid action_info value parsed");
        return {};
    }

    auto [direction, count] = ParseActionInfo(actionJson);
    if (direction.empty()) {
        return {};
    }

    auto coordinates = actionJson->GetValue("coordinates");
    if (!coordinates || !coordinates->IsObject() || !coordinates->Contains("pos")) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid coordinates parsed");
        return {};
    }

    auto pos = coordinates->GetValue("pos");
    if (!pos || !pos->IsObject() || !pos->Contains("x") || !pos->Contains("y")) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid pos or x,y parsed");
        return {};
    }

    auto x = pos->GetValue("x");
    auto y = pos->GetValue("y");
    if (!x || !x->IsNumber() || !y || !y->IsNumber()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid x or y value parsed");
        return {};
    }

    auto point = PointF(static_cast<float>(x->GetDouble()), static_cast<float>(y->GetDouble()));
    auto executor = std::make_unique<StrictContentSwitchExecutor>(context_, mode, direction, count, point);
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    executors.push_back(std::move(executor));
    return executors;
}

bool ContentSwitchCommandParser::ValidateBasicJson(const std::unique_ptr<JsonValue>& json)
{
    if (!json || !json->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Invalid json object");
        return false;
    }

    if (!json->Contains("type") || !json->Contains("action_info")) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid type or action_info parsed");
        return false;
    }

    return true;
}

bool ContentSwitchCommandParser::ValidateType(const std::unique_ptr<JsonValue>& json)
{
    std::string type = json->GetString("type");
    if (type != "content_switch") {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Parsed type is not content_switch");
        return false;
    }

    return true;
}

ContentSwitchCommandParser::ActionInfo ContentSwitchCommandParser::ParseActionInfo(
    const std::unique_ptr<JsonValue>& actionJson)
{
    if (!actionJson->Contains("coordinates")) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "No valid coordinates parsed");
        return {"", 0};
    }

    std::string direction = actionJson->Contains("direction") ?
                            actionJson->GetString("direction") : "forward";
    if (direction != "forward" && direction != "backward") {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Parsed direction is not forward or backward");
        return {"", 0};
    }

    int32_t count = 1;
    if (actionJson->Contains("count")) {
        auto value = actionJson->GetValue("count");
        if (!JsonUtils::IsUint(value)) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "Invalid count type");
            return {"", 0};
        }
        count = value->GetInt();
    }

    return {direction, count};
}
} // namespace OHOS::Ace::NG
