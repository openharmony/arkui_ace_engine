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

#include "core/components_ng/relaxed_interaction/parsers/scroll_command_parser.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_simulating_executor.h"

#include <memory>
#include <vector>
#include <string>

#include "base/geometry/ng/point_t.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/display_info.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"

namespace OHOS::Ace::NG {

ScrollCommandParser::ScrollCommandParser(WeakPtr<PipelineContext> context) : BaseCommandParser(context) {}

std::vector<std::unique_ptr<BaseExecutor>> ScrollCommandParser::Parse(const std::unique_ptr<JsonValue>& json)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;
    if (!json || !json->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid json object");
        return executors;
    }
    Command cmd = {};
    if (!ParseCmd(json.get(), cmd)) {
        return executors;
    }
    return CreateExecutor(cmd);
}

bool ScrollCommandParser::ParseMode(const JsonValue* cmdJson, ExecuteMode& mode)
{
    if (!cmdJson->Contains("mode")) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "No mode. default value is auto");
        mode = ExecuteMode::AUTO;
        return true;
    }
    if (cmdJson->Contains("mode") && !cmdJson->GetValue("mode")->IsString()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid mode, value is not string.");
        return false;
    }
    std::string modeStr = cmdJson->GetString("mode");
    if (modeStr == "simulating") {
        mode = ExecuteMode::SIMULATING;
    } else if (modeStr == "target") {
        mode = ExecuteMode::TARGET;
    } else if (modeStr == "auto") {
        mode = ExecuteMode::AUTO;
    } else {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid mode, must be one of: auto, simulating, target");
        return false;
    }

    return true;
}

bool ScrollCommandParser::ParseDirection(const JsonValue* actionInfoJson, RelaxedScrollDirection& direction)
{
    // default direction
    if (!actionInfoJson || !actionInfoJson->Contains("direction")) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid direction, default direction is forward.");
        direction = RelaxedScrollDirection::FORWARD;
        return true;
    }
    if (actionInfoJson->Contains("direction") && !actionInfoJson->GetValue("direction")->IsString()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid direction, direction value type is not string.");
        return false;
    }
    std::string dirStr = actionInfoJson->GetValue("direction")->GetString();
    if (dirStr == "forward") {
        direction = RelaxedScrollDirection::FORWARD;
    } else if (dirStr == "backward") {
        direction = RelaxedScrollDirection::BACKWARD;
    } else if (dirStr == "left") {
        direction = RelaxedScrollDirection::LEFT;
    } else if (dirStr == "right") {
        direction = RelaxedScrollDirection::RIGHT;
    } else if (dirStr == "down") {
        direction = RelaxedScrollDirection::DOWN;
    } else if (dirStr == "up") {
        direction = RelaxedScrollDirection::UP;
    } else {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Invalid direction value: %s", dirStr.c_str());
        return false;
    }

    return true;
}

bool ScrollCommandParser::ParseCoordinates(const JsonValue* cmdJson, Command& cmd)
{
    auto coordinatesJson = cmdJson->GetValue("coordinates");
    if (!coordinatesJson || !coordinatesJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing or invalid coordinates object");
        return false;
    }

    if (!coordinatesJson->Contains("x1") || !coordinatesJson->Contains("y1")) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing required coordinates x1 or y1");
        return false;
    }
    if (!coordinatesJson->GetValue("x1")->IsNumber() || !coordinatesJson->GetValue("y1")->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "coordinates x1 or y1 is not number.");
        return false;
    }
    cmd.actionInfo.coordinates = { 0.0f, 0.0f, 0.0f, 0.0f };
    cmd.actionInfo.coordinates.x1 = coordinatesJson->GetDouble("x1");
    cmd.actionInfo.coordinates.y1 = coordinatesJson->GetDouble("y1");
    if (coordinatesJson->Contains("x2") && coordinatesJson->Contains("y2") &&
        coordinatesJson->GetValue("x2")->IsNumber() && coordinatesJson->GetValue("y2")->IsNumber()) {
        cmd.actionInfo.coordinates.x2 = coordinatesJson->GetDouble("x2");
        cmd.actionInfo.coordinates.y2 = coordinatesJson->GetDouble("y2");
        cmd.isY2Set = true;
    } else {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Coordinates x2 or y2 is invalid.");
    }

    return true;
}

bool ScrollCommandParser::ParseCmd(const JsonValue* cmdJson, Command& cmd)
{
    auto actionInfoJson = cmdJson->GetValue("action_info");
    if (!actionInfoJson || !actionInfoJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Missing or invalid action_info object");
        return false;
    }
    ExecuteMode mode = ExecuteMode::AUTO;
    if (!ParseMode(cmdJson, mode)) {
        return false;
    }
    cmd.mode = mode;
    // default direstion
    RelaxedScrollDirection direction = RelaxedScrollDirection::FORWARD;
    if (!ParseDirection(actionInfoJson.get(), direction)) {
        return false;
    }
    cmd.actionInfo.direction = direction;
    // distance
    if (!actionInfoJson->Contains("distance")) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "No distance. default 1/3 screen height");
        cmd.actionInfo.distance = GetDefaultScrollDistance();
    } else {
        if (!actionInfoJson->GetValue("distance")->IsNumber()) {
            TAG_LOGE(AceLogTag::ACE_UIEVENT, "distance is not number.");
            return false;
        }
        double distanceVal = actionInfoJson->GetValue("distance")->GetDouble();
        if (distanceVal < 0) {
            TAG_LOGE(AceLogTag::ACE_UIEVENT, "distance is negative.");
            return false;
        }
        cmd.actionInfo.distance = static_cast<float>(distanceVal);
    }

    if (!ParseCoordinates(actionInfoJson.get(), cmd)) {
        return false;
    }

    return true;
}

float ScrollCommandParser::GetDefaultScrollDistance()
{
    auto container = Container::CurrentSafely();
    if (container && container->GetDisplayInfo()) {
        // window height
        float windowHeight = container->GetDisplayInfo()->GetHeight();
        // 1/3 screen height (default scroll distance)
        return windowHeight / 3.0f;
    }

    // physical device height
    float deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    return deviceHeight / 3.0f;
}

std::vector<std::unique_ptr<BaseExecutor>> ScrollCommandParser::CreateExecutor(const Command& cmd)
{
    std::vector<std::unique_ptr<BaseExecutor>> executors;

    if (cmd.mode == ExecuteMode::SIMULATING) {
        executors.emplace_back(std::make_unique<ScrollSimulatingExecutor>(context_, cmd));
    } else if (cmd.mode == ExecuteMode::AUTO) {
        executors.emplace_back(std::make_unique<ScrollTouchExecutor>(context_, cmd));
        executors.emplace_back(std::make_unique<ScrollSimulatingExecutor>(context_, cmd));
    } else {
        executors.emplace_back(std::make_unique<ScrollTouchExecutor>(context_, cmd));
    }

    return executors;
}

} // namespace OHOS::Ace::NG
