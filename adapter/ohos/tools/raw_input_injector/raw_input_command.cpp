/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "raw_input_command.h"

#include <iostream>

#include "string_ex.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t MIN_DATA_COUNT_FOR_RAW_EVENT = 2;
constexpr int32_t MAX_DATA_COUNT_FOR_RAW_EVENT = 4;
constexpr int32_t RAW_EVENT_X_INDEX = 0;
constexpr int32_t RAW_EVENT_Y_INDEX = 1;
constexpr int32_t RAW_EVENT_DURATION_INDEX = 2;
} // namespace

std::string BaseCommand::GetCommandTypeName(CommandType type)
{
    switch (type) {
        case CommandType::TOUCH_DOWN:
            return "d";
        case CommandType::TOUCH_MOVE:
            return "m";
        case CommandType::TOUCH_UP:
            return "u";
        case CommandType::TOUCH_CANCEL:
            return "c";
        case CommandType::COMMAND_WAIT:
            return "w";
        default:
            return "";
    }
}

std::string BaseCommand::GetReadableCommandTypeName(CommandType type)
{
    switch (type) {
        case CommandType::TOUCH_DOWN:
            return "down";
        case CommandType::TOUCH_MOVE:
            return "move";
        case CommandType::TOUCH_UP:
            return "up";
        case CommandType::TOUCH_CANCEL:
            return "cancel";
        case CommandType::COMMAND_WAIT:
            return "wait";
        default:
            return "";
    }
}

bool BaseCommand::Feed(const std::vector<std::string>& data)
{
    if (data.empty()) {
        return true;
    }
    for (const auto& str : data) {
        int32_t duration;
        if (!StrToInt(str, duration)) {
            return false;
        }
        SetDuration(duration);
        break;
    }

    return true;
}

// -d/m/u/c x y duration finger
bool BaseRawEventCommand::Feed(const std::vector<std::string>& data)
{
    if (data.size() < MIN_DATA_COUNT_FOR_RAW_EVENT || data.size() > MAX_DATA_COUNT_FOR_RAW_EVENT) {
        std::cout << "error data count for -" << GetCommandTypeName(GetCommandType()) << std::endl;
        return false;
    }

    bool durationSet = false;
    int32_t paramInd = 0;
    for (const auto& str : data) {
        int32_t value;
        if (!StrToInt(str, value)) {
            std::cout << "parse error for " << str << std::endl;
            return false;
        }
        switch (paramInd) {
            case RAW_EVENT_X_INDEX:
                SetTargetDisplayX(value);
                break;
            case RAW_EVENT_Y_INDEX:
                SetTargetDisplayY(value);
                break;
            case RAW_EVENT_DURATION_INDEX:
                durationSet = true;
                SetDuration(value);
                break;
            default:
                break;
        }
        paramInd++;
    }

    OnFeeded(durationSet, data);

    return true;
}

std::string BaseRawEventCommand::ToString() const
{
    std::string typeName = GetReadableCommandTypeName(GetCommandType());
    std::string result = "";
    if (GetDuration() != 0) {
        result = typeName + "(" + std::to_string(GetTargetDisplayX()) + ", " + std::to_string(GetTargetDisplayY()) +
                 ")-[" + std::to_string(GetDuration()) + "ms]";
    } else {
        result =
            typeName + "(" + std::to_string(GetTargetDisplayX()) + ", " + std::to_string(GetTargetDisplayY()) + ")";
    }
    return result;
}

std::string WaitCommand::ToString() const
{
    return "wait-[" + std::to_string(GetDuration()) + "]ms";
}

void TouchMoveCommand::OnFeeded(bool durationSet, const std::vector<std::string>& data)
{
    (void)(data); // not used for now
    if (!durationSet) {
        // for touch move, the default duration is 1000
        SetDuration(DEFAULT_MOVE_DURATION);
    }
}

void CommandList::AddCommand(std::shared_ptr<BaseCommand> command)
{
    commands_.push_back(command);
}

void CommandList::Clear()
{
    commands_.clear();
}

const std::vector<std::shared_ptr<BaseCommand>>& CommandList::GetCommands() const
{
    return commands_;
}

std::string CommandList::ToString() const
{
    std::string dumpStr = "";
    for (auto& command : commands_) {
        dumpStr += ("  " + command->ToString());
    }
    return dumpStr;
}

bool BaseCommand::ConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo)
{
    // mark the base time line first if not set before this consuming try
    MarkConsumeBaseTimeLine(currentTime);
    // check if already consumed out
    if (IsConsumedOut()) {
        return false; // running out, can not be consumed any more
    }

    if (currentTime >= (consumeBaseTimeLine_ + duration_)) {
        // give the current command at least one chance to be executed
        isConsumedOut_ = true;
    }

    // call the func implemented by child class
    bool ret = DoConsumeOnce(currentTime, actionInfo);
    // increase consumed count
    MarkConsumedOnce();
    return ret;
}

bool WaitCommand::DoConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo)
{
    actionInfo.type = GetCommandType();
    actionInfo.curve = GetCoordinateCurve();
    actionInfo.finger = GetFingerId();
    actionInfo.targetDisplayX = 0;
    actionInfo.targetDisplayY = 0;
    actionInfo.consumeIndex = GetConsumedCount();
    actionInfo.totalCount = GetTotalCount();
    return true;
}

bool BaseRawEventCommand::DoConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo)
{
    actionInfo.type = GetCommandType();
    actionInfo.curve = GetCoordinateCurve();
    actionInfo.finger = GetFingerId();
    actionInfo.targetDisplayX = GetTargetDisplayX();
    actionInfo.targetDisplayY = GetTargetDisplayY();
    actionInfo.consumeIndex = GetConsumedCount();
    actionInfo.totalCount = GetTotalCount();
    return true;
}

bool CommandList::IsAllConsumed() const
{
    for (const auto& command : commands_) {
        if (!(command->IsConsumedOut())) {
            return false;
        }
    }
    return true;
}

bool CommandList::ConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo)
{
    if (currentConsumingIndex_ >= commands_.size()) {
        return false;
    }

    auto& command = commands_[currentConsumingIndex_];
    command->ConsumeOnce(currentTime, actionInfo);
    if (command->IsConsumedOut()) {
        currentConsumingIndex_++;
    }

    return true;
}

} // namespace Ace
} // namespace OHOS
