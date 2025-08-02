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

#ifndef ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_H
#define ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_H

#include <map>
#include <string>
#include <vector>

#include "injecting_executor.h"
#include "nocopyable.h"
#include "raw_input_command.h"

namespace OHOS {
namespace Ace {

struct PointerInfo {
    int32_t startDisplayX = 0;
    int32_t startDisplayY = 0;
    int32_t lastDisplayX = 0;
    int32_t lastDisplayY = 0;
    int32_t fingerId = 0;
};

class GlobalPointerStatus {
public:
    GlobalPointerStatus() = default;
    ~GlobalPointerStatus() = default;

    void UpdatePointerStatusByPointerAction(
        int32_t pointerAction, int32_t fingerId, int32_t displayX, int32_t displayY, bool isStartUpdateNeeded = false);

    bool IsAnyPointerExistOnScreen() const
    {
        return pointerStatusList_.size() > 0;
    }

    const std::vector<PointerInfo>& GetPointerStatusList() const
    {
        return pointerStatusList_;
    }

    bool IsPointerExist(int32_t fingerId) const;
    PointerInfo GetLastPointerInfo(int32_t fingerId) const;

private:
    void AddPointerInfo(int32_t id, int32_t x, int32_t y);
    void UpdatePointerInfo(int32_t id, int32_t x, int32_t y, bool isStartUpdateNeeded = false);
    void RemovePointerInfo(int32_t id);

    std::vector<PointerInfo> pointerStatusList_;
};

class RawInputInjector {
public:
    RawInputInjector() = default;
    DISALLOW_COPY_AND_MOVE(RawInputInjector);
    bool ExecuteInject(int32_t argc, char* argv[]);

private:
    void PrintAllCommands(int32_t argc, char* argv[]);
    bool ParseAndPackCommandQueue(int32_t argc, char* argv[]);
    bool ParseAndPackCommandForTouch(int32_t argc, char* argv[]);
    bool ParseFingerId(int32_t argc, char* argv[]);
    bool PackSingleCommandToQueueFromCurrentPos(CommandType type, int32_t argc, char* argv[]);
    bool CheckCommandQueue();
    bool ExecuteQueue();
    bool PrepareAllInjectingActions(std::vector<std::vector<ConsumeActionInfo>>& allActions);
    void DumpAllInjectingActions(const std::vector<std::vector<ConsumeActionInfo>>& allActions);
    void DoInject(const std::vector<std::vector<ConsumeActionInfo>>& allActions);
    void PackInjectActionForOneRound(const std::vector<ConsumeActionInfo>& actionList, int32_t lastActivedFinger,
        int64_t currentTime, std::vector<InjectingInfo>& activedInjectingInfos,
        std::vector<InjectingInfo>& otherInjectingInfos);
    InjectingInfo GetInjectInfoFrom(const ConsumeActionInfo& action, int64_t currentTime) const;
    void UpdateInjectInfoForTouchEvent(const ConsumeActionInfo& action, InjectingInfo& info) const;
    void UpdateInjectInfoForTouchMove(const ConsumeActionInfo& action, InjectingInfo& info) const;
    void UpdateInjectInfoForWaitAction(const ConsumeActionInfo& action, InjectingInfo& info) const;
    void CalculatePosValueBaseOnLastPoint(
        const PointerInfo& lastPoint, const ConsumeActionInfo& action, InjectingInfo& info) const;
    void DumpInjectingInfo(int32_t round, std::vector<InjectingInfo>& activedInjectingInfos,
        std::vector<InjectingInfo>& otherInjectingInfos) const;
    int32_t EstimateActiveFinger(const std::vector<ConsumeActionInfo>& actionList, int32_t lastActivedFinger) const;
    void UpdateGlobalStatus(const std::vector<ConsumeActionInfo>& actionList,
        const std::vector<InjectingInfo>& activedInjectingInfos, const std::vector<InjectingInfo>& otherInjectingInfos);
    bool IsAllConsumed() const;
    int32_t GetOptFromCurrentPosAndMoveOn(int32_t argc, char* argv[]);
    std::string GetParamFromCurrentPosAndMoveOn(int32_t argc, char* argv[]);
    GlobalPointerStatus globalPointerStatus_;
    std::map<int32_t, CommandList> commandMap_;
    int32_t currentParsingFinger_ = 0;
    int32_t currentParsingPos_ = 1;
};
} // namespace Ace
} // namespace OHOS
#endif // ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_H
