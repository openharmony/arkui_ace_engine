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

#include "raw_input_injector.h"

#include <iostream>
#include <thread>

#include "string_ex.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t SLEEPTIME = 20;
constexpr int32_t OPT_CHARACTER_COUNT = 2;
} // namespace

void RawInputInjector::PrintAllCommands(int32_t argc, char* argv[])
{
    if (!InjectorUtils::IsDebugOn()) {
        return;
    }
    std::cout << "all args: " << std::endl;
    for (int32_t i = 0; i < argc; i++) {
        std::cout << " - args[" << i << "]: " << argv[i] << std::endl;
    }
}

bool RawInputInjector::ExecuteInject(int32_t argc, char* argv[])
{
    if (!ParseAndPackCommandQueue(argc, argv)) {
        std::cout << "parse commands failed" << std::endl;
        return false;
    }

    // alway return true if the parse successfully
    bool ret = true;
    if (!CheckCommandQueue()) {
        std::cout << "the commands queue can not be handled" << std::endl;
        return ret;
    }

    if (!ExecuteQueue()) {
        std::cout << "execute commands failed" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEPTIME));
    return ret;
}

int32_t RawInputInjector::GetOptFromCurrentPosAndMoveOn(int32_t argc, char* argv[])
{
    int32_t opt = -1;
    if (currentParsingPos_ >= argc) {
        return opt;
    }

    if (argv[currentParsingPos_] == nullptr || strlen(argv[currentParsingPos_]) != OPT_CHARACTER_COUNT ||
        argv[currentParsingPos_][0] != '-') {
        return opt;
    }

    opt = argv[currentParsingPos_][1];
    currentParsingPos_++;
    return opt;
}

std::string RawInputInjector::GetParamFromCurrentPosAndMoveOn(int32_t argc, char* argv[])
{
    if (currentParsingPos_ >= argc) {
        return "";
    }

    if (argv[currentParsingPos_] == nullptr || strlen(argv[currentParsingPos_]) == 0 ||
        argv[currentParsingPos_][0] == '-') {
        return "";
    }

    std::string ret(argv[currentParsingPos_]);
    currentParsingPos_++;
    return ret;
}

bool RawInputInjector::ParseAndPackCommandQueue(int32_t argc, char* argv[])
{
    PrintAllCommands(argc, argv);
    int32_t opt = 0;
    // check the first opt, it must be -R
    opt = GetOptFromCurrentPosAndMoveOn(argc, argv);
    if (opt != 'R') {
        // quit
        return false;
    }
    opt = GetOptFromCurrentPosAndMoveOn(argc, argv);
    if (opt == 'D') {
        InjectorUtils::SetDebugEnabled(true);
        // move to next
        opt = GetOptFromCurrentPosAndMoveOn(argc, argv);
    }
    switch (opt) {
        case 'T':
            ParseAndPackCommandForTouch(argc, argv);
            break;
        default:
            break;
    }

    return true;
}

// rawinput -R -T -f 0 -w 333 -d 601 602 -w 603 -m 610 1120 1000 -w 5000 -u 610 1120 -f 1 -d 501 502 -w 503 -m 510 1520
// 5000 -w 5000 -u 510 1525
bool RawInputInjector::ParseAndPackCommandForTouch(int32_t argc, char* argv[])
{
    int32_t opt = 0;
    bool packRet = true;
    // do not use the getopt for the next parsing as it will reorder the args, which will affect the parsing
    while ((opt = GetOptFromCurrentPosAndMoveOn(argc, argv)) != -1) {
        switch (opt) {
            case 'f':
                packRet = ParseFingerId(argc, argv);
                break;
            case 'd':
                packRet = PackSingleCommandToQueueFromCurrentPos(CommandType::TOUCH_DOWN, argc, argv);
                break;
            case 'm':
                packRet = PackSingleCommandToQueueFromCurrentPos(CommandType::TOUCH_MOVE, argc, argv);
                break;
            case 'u':
                packRet = PackSingleCommandToQueueFromCurrentPos(CommandType::TOUCH_UP, argc, argv);
                break;
            case 'c':
                packRet = PackSingleCommandToQueueFromCurrentPos(CommandType::TOUCH_CANCEL, argc, argv);
                break;
            case 'w':
                packRet = PackSingleCommandToQueueFromCurrentPos(CommandType::COMMAND_WAIT, argc, argv);
                break;
            default:
                std::cout << "unsupprted opt: -" << static_cast<char>(opt) << std::endl;
                return false;
        }
        if (!packRet) {
            std::cout << "pack single command failed for -" << opt << std::endl;
            return false;
        }
    }
    return true;
}

bool RawInputInjector::ParseFingerId(int32_t argc, char* argv[])
{
    if (currentParsingPos_ >= argc) {
        return false;
    }

    std::string fingerValue = GetParamFromCurrentPosAndMoveOn(argc, argv);
    int32_t fingerID = 0;
    if (!StrToInt(fingerValue, fingerID)) {
        return false;
    }
    const auto& existFinger = commandMap_.find(fingerID);
    if (existFinger != commandMap_.end()) {
        return false;
    }

    CommandList commandList;
    commandList.SetPointerID(fingerID);
    commandMap_[fingerID] = std::move(commandList);
    // mark the current handling finger
    currentParsingFinger_ = fingerID;
    return true;
}

bool RawInputInjector::PackSingleCommandToQueueFromCurrentPos(CommandType type, int32_t argc, char* argv[])
{
    if (currentParsingPos_ >= argc) {
        return false;
    }

    std::shared_ptr<BaseCommand> command = nullptr;
    switch (type) {
        case CommandType::TOUCH_DOWN:
            command = std::make_shared<TouchDownCommand>();
            break;
        case CommandType::TOUCH_MOVE:
            command = std::make_shared<TouchMoveCommand>();
            break;
        case CommandType::TOUCH_UP:
            command = std::make_shared<TouchUpCommand>();
            break;
        case CommandType::TOUCH_CANCEL:
            command = std::make_shared<TouchCancelCommand>();
            break;
        case CommandType::COMMAND_WAIT:
            command = std::make_shared<WaitCommand>();
            break;
        default:
            return false;
    }

    command->SetCommandType(type);
    command->SetFingerId(currentParsingFinger_);

    std::vector<std::string> data;
    std::string parameter;
    while ((parameter = GetParamFromCurrentPosAndMoveOn(argc, argv)) != "") {
        data.push_back(parameter);
    }

    if (!command->Feed(data)) {
        return false;
    }
    commandMap_[currentParsingFinger_].AddCommand(command);
    return true;
}

bool RawInputInjector::CheckCommandQueue()
{
    if (commandMap_.empty()) {
        return false;
    }

    for (auto iter = commandMap_.begin(); iter != commandMap_.end(); ++iter) {
        std::string dumpStr = "finger " + std::to_string(iter->first) + ":";
        dumpStr += iter->second.ToString();
        std::cout << dumpStr << std::endl;
    }

    return true;
}

bool RawInputInjector::ExecuteQueue()
{
    // 先按照7ms步进间隔扫描整个队列，生成所有的待注入的事件action信息
    std::vector<std::vector<ConsumeActionInfo>> actionList;
    if (!PrepareAllInjectingActions(actionList)) {
        return false;
    }

    // dump all injecting actions
    DumpAllInjectingActions(actionList);

    // 遍历生成的事件序列，按照间隔依次执行注入
    DoInject(actionList);

    std::cout << "injecting done" << std::endl;
    return true;
}

bool RawInputInjector::PrepareAllInjectingActions(std::vector<std::vector<ConsumeActionInfo>>& allActions)
{
    int64_t currentTime = 0;
    while (!IsAllConsumed()) {
        std::vector<ConsumeActionInfo> actionList;
        for (auto iter = commandMap_.begin(); iter != commandMap_.end(); ++iter) {
            ConsumeActionInfo action;
            if (iter->second.ConsumeOnce(currentTime, action)) {
                actionList.push_back(action);
            }
        }
        currentTime += BaseCommand::EVENT_INJECTING_INTERVAL;
        allActions.push_back(std::move(actionList));
    }

    return true;
}

void RawInputInjector::DumpAllInjectingActions(const std::vector<std::vector<ConsumeActionInfo>>& allActions)
{
    if (!InjectorUtils::IsDebugOn()) {
        return;
    }

    if (allActions.empty()) {
        return;
    }

    int32_t round = 0;
    for (auto& actionList : allActions) {
        std::string str = "round " + std::to_string(round) + ": ";
        for (auto& action : actionList) {
            str += ("finger " + std::to_string(action.finger) + " " +
                    BaseCommand::GetReadableCommandTypeName(action.type) + ", ");
        }
        std::cout << str << std::endl;
        round++;
    }
}

void RawInputInjector::DoInject(const std::vector<std::vector<ConsumeActionInfo>>& allActions)
{
    if (allActions.empty()) {
        return;
    }

    int64_t startTime = InjectorUtils::GetSysClockTime(); // todo: do we need to backforward some ms for robustness
    int32_t intervalTimeMs = BaseCommand::EVENT_INJECTING_INTERVAL;
    int64_t currentTime = startTime;
    int32_t lastActivedFinger = 0;
    int32_t round = 0;

    for (auto& actionList : allActions) {
        std::vector<InjectingInfo> activedInjectingInfos;
        std::vector<InjectingInfo> allOtherInjectingInfos;
        PackInjectActionForOneRound(
            actionList, lastActivedFinger, currentTime, activedInjectingInfos, allOtherInjectingInfos);

        // do the injecting
        DumpInjectingInfo(round, activedInjectingInfos, allOtherInjectingInfos);

        // update last activing finger for next round suggesting
        if (!activedInjectingInfos.empty()) {
            lastActivedFinger = activedInjectingInfos[0].finger;
        }

        InjectingExecutor::InjectOnePonterEvent(activedInjectingInfos, allOtherInjectingInfos);

        // sleep 7ms
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalTimeMs));

        // update current global status
        UpdateGlobalStatus(actionList, activedInjectingInfos, allOtherInjectingInfos);
        currentTime += intervalTimeMs;
        round++;
    }
}

void RawInputInjector::UpdateGlobalStatus(const std::vector<ConsumeActionInfo>& actionList,
    const std::vector<InjectingInfo>& activedInjectingInfos, const std::vector<InjectingInfo>& otherInjectingInfos)
{
    std::vector<InjectingInfo> allEvents;
    allEvents.insert(allEvents.end(), activedInjectingInfos.begin(), activedInjectingInfos.end());
    allEvents.insert(allEvents.end(), otherInjectingInfos.begin(), otherInjectingInfos.end());

    if (allEvents.empty()) {
        return;
    }

    for (auto& info : allEvents) {
        bool isStartUpdateNeeded = false;
        for (auto& action : actionList) {
            if (action.finger == info.finger) {
                isStartUpdateNeeded = (action.consumeIndex == action.totalCount);
                break;
            }
        }
        globalPointerStatus_.UpdatePointerStatusByPointerAction(
            info.actionType, info.finger, info.x, info.y, isStartUpdateNeeded);
    }
}

void RawInputInjector::DumpInjectingInfo(int32_t round, std::vector<InjectingInfo>& activedInjectingInfos,
    std::vector<InjectingInfo>& otherInjectingInfos) const
{
    if (!InjectorUtils::IsDebugOn()) {
        return;
    }

    auto dumpInfoToString = [](const InjectingInfo& info, std::string& targetStr) {
        targetStr += "[";
        targetStr += "finger " + std::to_string(info.finger) + " ";
        targetStr += InjectingExecutor::GetPointerActionName(info.actionType) + " ";
        targetStr += "(x: " + std::to_string(info.x) + ", y: " + std::to_string(info.y) + ")";
        targetStr += "] ";
    };
    std::string str = "round " + std::to_string(round) + ": ";
    if (!activedInjectingInfos.empty()) {
        str += "|-ACTIVE(" + std::to_string(activedInjectingInfos.size()) + "): ";
        for (auto& info : activedInjectingInfos) {
            dumpInfoToString(info, str);
        }
    }

    if (!otherInjectingInfos.empty()) {
        str += "|-OTHER(" + std::to_string(otherInjectingInfos.size()) + "): ";
        for (auto& info : otherInjectingInfos) {
            dumpInfoToString(info, str);
        }
    }

    std::cout << str << std::endl;
}

void RawInputInjector::UpdateInjectInfoForTouchEvent(const ConsumeActionInfo& action, InjectingInfo& info) const
{
    info.actionType = InjectingExecutor::GetPointerActionFromCommandType(action.type);
    // for the immediate event, us target x/y directly
    if (InjectingExecutor::IsEventNeedTriggerImmediatly(info.actionType)) {
        info.x = action.targetDisplayX;
        info.y = action.targetDisplayY;
        return;
    }

    // for touch move event, calculate the next pos
    if (action.type == CommandType::TOUCH_MOVE) {
        UpdateInjectInfoForTouchMove(action, info);
        return;
    }

    // error
    std::cout << "fatal error, no handling" << std::endl;
}

void RawInputInjector::UpdateInjectInfoForTouchMove(const ConsumeActionInfo& action, InjectingInfo& info) const
{
    if (action.type != CommandType::TOUCH_MOVE) {
        std::cout << "fatal error, not touch move" << std::endl;
        return;
    }

    // step 1: try to get the last point info which is already by simulated into system,
    // if not exsit, use the target position directly
    if (!globalPointerStatus_.IsPointerExist(action.finger)) {
        info.x = action.targetDisplayX;
        info.y = action.targetDisplayY;
        return;
    }

    // step 2: get last point from globalPointerStatus_
    PointerInfo lastPointerInfo = globalPointerStatus_.GetLastPointerInfo(action.finger);
    // step 3: caluculate next point base on the last point
    CalculatePosValueBaseOnLastPoint(lastPointerInfo, action, info);
}

void RawInputInjector::CalculatePosValueBaseOnLastPoint(
    const PointerInfo& lastPoint, const ConsumeActionInfo& action, InjectingInfo& info) const
{
    Point startPoint = { lastPoint.startDisplayX, lastPoint.startDisplayY };
    Point targetPoint = { action.targetDisplayX, action.targetDisplayY };
    std::vector<Point> controlPoints; // will support control points in the future
    // prepare control points
    controlPoints.push_back(startPoint);
    // will support extra middle point in the future
    controlPoints.push_back(targetPoint);
    Point nextPoint = InjectorUtils::CalculateNextPosValueWithBezier(
        controlPoints, action.consumeIndex, action.totalCount, action.curve);
    info.x = static_cast<int32_t>(nextPoint.x);
    info.y = static_cast<int32_t>(nextPoint.y);
}

void RawInputInjector::UpdateInjectInfoForWaitAction(const ConsumeActionInfo& action, InjectingInfo& info) const
{
    // for wait action, always use the move action
    info.actionType = InjectingExecutor::GetPointerActionFromCommandType(CommandType::TOUCH_MOVE);
    if (!globalPointerStatus_.IsPointerExist(action.finger)) {
        info.x = action.targetDisplayX;
        info.y = action.targetDisplayY;
        return;
    }

    PointerInfo lastPointerInfo = globalPointerStatus_.GetLastPointerInfo(action.finger);
    info.x = lastPointerInfo.lastDisplayX;
    info.y = lastPointerInfo.lastDisplayY;
    return;
}

InjectingInfo RawInputInjector::GetInjectInfoFrom(const ConsumeActionInfo& action, int64_t currentTime) const
{
    InjectingInfo info;
    info.finger = action.finger;
    info.actionTime = currentTime;

    if (action.type == CommandType::COMMAND_WAIT) {
        UpdateInjectInfoForWaitAction(action, info);
        return info;
    }

    UpdateInjectInfoForTouchEvent(action, info);
    return info;
}

void RawInputInjector::PackInjectActionForOneRound(const std::vector<ConsumeActionInfo>& actionList,
    int32_t lastActivedFinger, int64_t currentTime, std::vector<InjectingInfo>& activedInjectingInfos,
    std::vector<InjectingInfo>& otherInjectingInfos)
{
    if (actionList.empty()) {
        return;
    }

    int32_t estimatedFinger = EstimateActiveFinger(actionList, lastActivedFinger);
    if (estimatedFinger < 0) {
        return;
    }

    bool immediateEventExist = false;
    for (auto& action : actionList) {
        InjectingInfo info = GetInjectInfoFrom(action, currentTime);
        if (InjectingExecutor::IsEventNeedTriggerImmediatly(info.actionType)) {
            immediateEventExist = true;
            activedInjectingInfos.push_back(info);
            continue; // next
        }
        // if there is no any event such as down/up/cancel exist, let move as activing event
        if (info.finger == estimatedFinger && !immediateEventExist) {
            activedInjectingInfos.push_back(info);
        } else {
            otherInjectingInfos.push_back(info);
        }
    }
}

int32_t RawInputInjector::EstimateActiveFinger(
    const std::vector<ConsumeActionInfo>& actionList, int32_t lastActivedFinger) const
{
    if (actionList.empty()) {
        return -1;
    }
    int32_t estimatedFinger = -1;
    for (auto& action : actionList) {
        // give other finger chance
        if (action.finger != lastActivedFinger) {
            estimatedFinger = action.finger;
            break;
        }
    }
    // if no last actived finger found, use the first directly
    if (estimatedFinger == -1) {
        estimatedFinger = actionList[0].finger;
    }
    return estimatedFinger;
}

bool RawInputInjector::IsAllConsumed() const
{
    if (commandMap_.empty()) {
        return true;
    }

    for (auto iter = commandMap_.begin(); iter != commandMap_.end(); ++iter) {
        if (!(iter->second.IsAllConsumed())) {
            return false;
        }
    }

    return true;
}

void GlobalPointerStatus::UpdatePointerStatusByPointerAction(
    int32_t pointerAction, int32_t fingerId, int32_t displayX, int32_t displayY, bool isStartUpdateNeeded)
{
    CommandType commandType = InjectingExecutor::GetCommandTypeFromPointerAction(pointerAction);
    switch (commandType) {
        case CommandType::TOUCH_DOWN:
            AddPointerInfo(fingerId, displayX, displayY);
            return;
        case CommandType::TOUCH_MOVE:
            UpdatePointerInfo(fingerId, displayX, displayY, isStartUpdateNeeded);
            return;
        case CommandType::TOUCH_UP:
        case CommandType::TOUCH_CANCEL:
            RemovePointerInfo(fingerId);
            return;
        default:
            return;
    }
}

void GlobalPointerStatus::AddPointerInfo(int32_t id, int32_t x, int32_t y)
{
    PointerInfo pointerStatus;
    pointerStatus.fingerId = id;
    pointerStatus.startDisplayX = x;
    pointerStatus.startDisplayY = y;
    pointerStatus.lastDisplayX = x;
    pointerStatus.lastDisplayY = y;
    pointerStatusList_.push_back(pointerStatus);
}

void GlobalPointerStatus::UpdatePointerInfo(int32_t id, int32_t x, int32_t y, bool isStartUpdateNeeded)
{
    for (auto& pointerStatus : pointerStatusList_) {
        if (pointerStatus.fingerId == id) {
            pointerStatus.lastDisplayX = x;
            pointerStatus.lastDisplayY = y;
            if (isStartUpdateNeeded) {
                pointerStatus.startDisplayX = x;
                pointerStatus.startDisplayY = y;
            }
            return;
        }
    }
}

void GlobalPointerStatus::RemovePointerInfo(int32_t id)
{
    auto iter = pointerStatusList_.begin();
    while (iter != pointerStatusList_.end()) {
        auto pointerStatus = *iter;
        if (pointerStatus.fingerId == id) {
            pointerStatusList_.erase(iter);
            break;
        }
        ++iter;
    }
}

bool GlobalPointerStatus::IsPointerExist(int32_t fingerId) const
{
    for (auto& pointerStatus : pointerStatusList_) {
        if (pointerStatus.fingerId == fingerId) {
            return true;
        }
    }
    return false;
}

PointerInfo GlobalPointerStatus::GetLastPointerInfo(int32_t fingerId) const
{
    for (auto& pointerStatus : pointerStatusList_) {
        if (pointerStatus.fingerId == fingerId) {
            return pointerStatus;
        }
    }

    return PointerInfo();
}

} // namespace Ace
} // namespace OHOS
