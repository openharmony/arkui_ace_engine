/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_COMMAND_H
#define ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_COMMAND_H

#include <string>
#include <vector>

#include "injector_utils.h"

namespace OHOS {
namespace Ace {
// command types
enum class CommandType : size_t { TOUCH_DOWN = 0, TOUCH_UP, TOUCH_MOVE, TOUCH_CANCEL, COMMAND_WAIT, UNKNOWN };

struct ConsumeActionInfo {
    CommandType type = CommandType::UNKNOWN;
    CoordinateCurve curve = CoordinateCurve::EASE_IN_OUT;
    int32_t finger = 0;
    int32_t targetDisplayX = 0;
    int32_t targetDisplayY = 0;
    int32_t consumeIndex = 0;
    int32_t totalCount = 1;
};

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual bool Feed(const std::vector<std::string>& data);
    virtual std::string ToString() const = 0;
    bool ConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo);
    // implemented by child for raw event injecting
    virtual bool DoConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo) = 0;

    static std::string GetCommandTypeName(CommandType type);
    static std::string GetReadableCommandTypeName(CommandType type);

    bool IsConsumedOut() const
    {
        return isConsumedOut_;
    }

    void SetDuration(int32_t duration)
    {
        duration_ = duration;
        auto total = (duration / eventInjectingInterval_);
        totalCount_ = (duration % eventInjectingInterval_ != 0) ? (total + 1) : total;
    }

    int32_t GetDuration() const
    {
        return duration_;
    }

    void SetCommandType(CommandType type)
    {
        commandType_ = type;
    }

    CommandType GetCommandType() const
    {
        return commandType_;
    }

    void SetFingerId(int32_t finger)
    {
        fingerId_ = finger;
    }

    int32_t GetFingerId() const
    {
        return fingerId_;
    }

    int32_t GetConsumedCount() const
    {
        return consumedCount_;
    }

    int32_t GetTotalCount() const
    {
        return totalCount_;
    }

    void SetCoordinateCurve(CoordinateCurve curve)
    {
        coordinateCurve_ = curve;
    }

    CoordinateCurve GetCoordinateCurve() const
    {
        return coordinateCurve_;
    }

    void MarkConsumedOnce()
    {
        consumedCount_++;
    }

    // inject event every 5ms, not use 7ms as we need consider the IPC consumed time
    static const int32_t EVENT_INJECTING_INTERVAL = 5; // inject event every 5 ms

private:
    void MarkConsumeBaseTimeLine(int64_t currentTime)
    {
        if (consumeBaseTimeLine_ < 0) {
            consumeBaseTimeLine_ = currentTime;
        }
    }

    int32_t eventInjectingInterval_ = EVENT_INJECTING_INTERVAL;
    int32_t fingerId_ = 0;
    int32_t duration_ = 0;             // the total time for this command can be executed
    int64_t consumeBaseTimeLine_ = -1; // the base time line for consume this command
    bool isConsumedOut_ = false;
    int32_t consumedCount_ = 0;
    int32_t totalCount_ = 1;
    CoordinateCurve coordinateCurve_ = CoordinateCurve::EASE_IN_OUT;
    CommandType commandType_ = CommandType::UNKNOWN;
};

class WaitCommand : public BaseCommand {
public:
    WaitCommand() = default;
    ~WaitCommand() override = default;
    bool DoConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo) override;
    std::string ToString() const override;
};

class BaseRawEventCommand : public BaseCommand {
public:
    BaseRawEventCommand() = default;
    ~BaseRawEventCommand() override = default;
    bool Feed(const std::vector<std::string>& data) override;
    virtual void OnFeeded(bool durationSet, const std::vector<std::string>& data) {}
    bool DoConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo) override;
    std::string ToString() const override;

    void SetTargetDisplayX(int32_t x)
    {
        targetDisplayX_ = x;
    }

    int32_t GetTargetDisplayX() const
    {
        return targetDisplayX_;
    }

    void SetTargetDisplayY(int32_t y)
    {
        targetDisplayY_ = y;
    }

    int32_t GetTargetDisplayY() const
    {
        return targetDisplayY_;
    }

private:
    int32_t targetDisplayX_ = 0;
    int32_t targetDisplayY_ = 0;
};

class TouchDownCommand : public BaseRawEventCommand {
public:
    TouchDownCommand() = default;
    ~TouchDownCommand() override = default;
};

class TouchUpCommand : public BaseRawEventCommand {
public:
    TouchUpCommand() = default;
    ~TouchUpCommand() override = default;
};

class TouchMoveCommand : public BaseRawEventCommand {
public:
    TouchMoveCommand() = default;
    ~TouchMoveCommand() override = default;
    void OnFeeded(bool durationSet, const std::vector<std::string>& data) override;
    static const int32_t DEFAULT_MOVE_DURATION = 1000;
};

class TouchCancelCommand : public BaseRawEventCommand {
public:
    TouchCancelCommand() = default;
    ~TouchCancelCommand() override = default;
};

class CommandList final {
public:
    CommandList() = default;
    ~CommandList() = default;

    std::string ToString() const;
    void AddCommand(std::shared_ptr<BaseCommand> command);
    void Clear();
    const std::vector<std::shared_ptr<BaseCommand>>& GetCommands() const;
    bool ConsumeOnce(int64_t currentTime, ConsumeActionInfo& actionInfo);

    void SetPointerID(int32_t pointerID)
    {
        pointerID_ = pointerID;
    }

    int32_t GetPointerID() const
    {
        return pointerID_;
    }

    bool IsAllConsumed() const;

private:
    std::vector<std::shared_ptr<BaseCommand>> commands_;
    int32_t pointerID_ = 0;
    size_t currentConsumingIndex_ = 0;
};

} // namespace Ace
} // namespace OHOS
#endif // ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_COMMAND_H
