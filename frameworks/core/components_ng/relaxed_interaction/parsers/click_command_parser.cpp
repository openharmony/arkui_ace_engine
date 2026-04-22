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

#include "core/components_ng/relaxed_interaction/parsers/click_command_parser.h"

#include <string>
#include <vector>

#include "base/geometry/ng/point_t.h"
#include "base/log/log.h"
#include "core/components_ng/relaxed_interaction/executors/strict_click_executor.h"
#include "core/components_ng/relaxed_interaction/executors/simulate_touch_executor.h"

namespace OHOS::Ace::NG {

ClickCommandParser::ClickCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> ClickCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;

    if (!json || !json->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid json object");
        return executors;
    }

    ExecuteMode mode = ExecuteMode::AUTO;
    if (!ParseMode(json.get(), mode)) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid mode, must be one of: auto, simulating, target");
        return executors;
    }

    PointF coordinates(0.0f, 0.0f);

    // action_info.coordinates is required for all modes
    if (!ParseCoordinates(json.get(), coordinates)) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Failed to parse required action_info.coordinates");
        return executors;
    }

    TAG_LOGD(AceLogTag::ACE_UIEVENT, "Parsed click command: mode=%{public}d", mode);

    return CreateExecutor(mode, coordinates);
}

bool ClickCommandParser::ParseMode(const JsonValue* cmdJson, ExecuteMode& mode)
{
    if (!cmdJson->Contains("mode")) {
        mode = ExecuteMode::AUTO;
        return true;
    }

    std::string modeStr = cmdJson->GetString("mode");
    if (modeStr == "simulating") {
        mode = ExecuteMode::SIMULATING;
        return true;
    } else if (modeStr == "target") {
        mode = ExecuteMode::TARGET;
        return true;
    } else if (modeStr == "auto") {
        mode = ExecuteMode::AUTO;
        return true;
    }

    return false;
}

bool ClickCommandParser::ParseCoordinates(const JsonValue* cmdJson, PointF& coordinates)
{
    auto actionInfoJson = cmdJson->GetValue("action_info");
    if (!actionInfoJson || !actionInfoJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing or invalid action_info object");
        return false;
    }

    auto coordinatesJson = actionInfoJson->GetValue("coordinates");
    if (!coordinatesJson || !coordinatesJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing or invalid coordinates object");
        return false;
    }

    auto x1Value = coordinatesJson->GetValue("x1");
    auto y1Value = coordinatesJson->GetValue("y1");
    if (!x1Value || !y1Value) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing required coordinates x1 or y1");
        return false;
    }

    if (!x1Value->IsNumber() || !y1Value->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Coordinates x1 or y1 is not a valid number");
        return false;
    }

    float x1 = x1Value->GetDouble();
    float y1 = y1Value->GetDouble();
    coordinates = PointF(x1, y1);
    return true;
}

std::vector<std::unique_ptr<BaseExecutor>> ClickCommandParser::CreateExecutor(
    ExecuteMode mode, const PointF& coordinates)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;

    if (mode == ExecuteMode::SIMULATING) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Creating SimulateTouchExecutor for simulating mode");
        executors.emplace_back(std::make_unique<SimulateTouchExecutor>(context_, coordinates));
    } else if (mode == ExecuteMode::AUTO) {
        // For auto mode, create both StrictClickExecutor and SimulateTouchExecutor
        // StrictClickExecutor goes first, SimulateTouchExecutor as fallback
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Creating StrictClickExecutor and SimulateTouchExecutor for auto mode");
        executors.emplace_back(std::make_unique<StrictClickExecutor>(context_, coordinates));
        executors.emplace_back(std::make_unique<SimulateTouchExecutor>(context_, coordinates));
    } else if (mode == ExecuteMode::TARGET) {
        // For target mode, only create StrictClickExecutor
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Creating StrictClickExecutor for target mode");
        executors.emplace_back(std::make_unique<StrictClickExecutor>(context_, coordinates));
    }

    return executors;
}

} // namespace OHOS::Ace::NG