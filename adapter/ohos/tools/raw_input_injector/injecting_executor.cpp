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

#include "injecting_executor.h"

#include <thread>

#include "input_manager.h"

namespace OHOS {
namespace Ace {

int32_t InjectingExecutor::GetPointerActionFromCommandType(CommandType type)
{
    switch (type) {
        case CommandType::TOUCH_DOWN:
            return MMI::PointerEvent::POINTER_ACTION_DOWN;
        case CommandType::TOUCH_MOVE:
            return MMI::PointerEvent::POINTER_ACTION_MOVE;
        case CommandType::TOUCH_UP:
            return MMI::PointerEvent::POINTER_ACTION_UP;
        case CommandType::TOUCH_CANCEL:
            return MMI::PointerEvent::POINTER_ACTION_CANCEL;
        default:
            return MMI::PointerEvent::POINTER_ACTION_MOVE;
    }
}

CommandType InjectingExecutor::GetCommandTypeFromPointerAction(int32_t pointerActionType)
{
    switch (pointerActionType) {
        case MMI::PointerEvent::POINTER_ACTION_DOWN:
            return CommandType::TOUCH_DOWN;
        case MMI::PointerEvent::POINTER_ACTION_MOVE:
            return CommandType::TOUCH_MOVE;
        case MMI::PointerEvent::POINTER_ACTION_UP:
            return CommandType::TOUCH_UP;
        case MMI::PointerEvent::POINTER_ACTION_CANCEL:
            return CommandType::TOUCH_CANCEL;
        default:
            return CommandType::UNKNOWN;
    }

    return CommandType::UNKNOWN;
}

std::string InjectingExecutor::GetPointerActionName(int32_t pointerActionType)
{
    switch (pointerActionType) {
        case MMI::PointerEvent::POINTER_ACTION_DOWN:
            return "down";
        case MMI::PointerEvent::POINTER_ACTION_MOVE:
            return "move";
        case MMI::PointerEvent::POINTER_ACTION_UP:
            return "up";
        case MMI::PointerEvent::POINTER_ACTION_CANCEL:
            return "cancel";
        default:
            return "unkown";
    }

    return "unkown";
}

bool InjectingExecutor::IsEventNeedTriggerImmediatly(int32_t pointerActionType)
{
    if (pointerActionType == MMI::PointerEvent::POINTER_ACTION_DOWN ||
        pointerActionType == MMI::PointerEvent::POINTER_ACTION_UP ||
        pointerActionType == MMI::PointerEvent::POINTER_ACTION_CANCEL) {
        return true;
    }
    return false;
}

bool InjectingExecutor::InjectOnePonterEvent(
    std::vector<InjectingInfo>& activingInjecting, std::vector<InjectingInfo>& allOtherInjectings)
{
    // must have one activing action at least
    if (activingInjecting.empty()) {
        return false;
    }

    bool ret = false;
    for (auto& activingPointer : activingInjecting) {
        if (ret) {
            // give a little break 1ms between two actions
            std::cout << "give a little break between two continus injecting" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        // 1. prepare the pointer event
        auto pointerEvent = MMI::PointerEvent::Create();
        if (!pointerEvent) {
            continue;
        }
        pointerEvent->SetSourceType(MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
        pointerEvent->SetPointerAction(activingPointer.actionType);
        pointerEvent->SetPointerId(activingPointer.finger);
        // 2. add the activing pointer self as the first item
        MMI::PointerEvent::PointerItem activingItem;
        activingItem.SetDisplayX(activingPointer.x);
        activingItem.SetDisplayY(activingPointer.y);
        activingItem.SetPointerId(activingPointer.finger);
        activingItem.SetPressed(true);
        activingItem.SetOriginPointerId(activingPointer.finger);
        pointerEvent->AddPointerItem(activingItem);
        pointerEvent->SetActionTime(activingPointer.actionTime);
        pointerEvent->SetSensorInputTime(activingPointer.actionTime - 2000);
        // 3. pack all other pointers into items
        for (auto& otherPointer : allOtherInjectings) {
            MMI::PointerEvent::PointerItem item;
            item.SetDisplayX(otherPointer.x);
            item.SetDisplayY(otherPointer.y);
            item.SetPointerId(otherPointer.finger);
            item.SetPressed(true);
            item.SetOriginPointerId(otherPointer.finger);
            pointerEvent->AddPointerItem(item);
        }
        // 4. inject
        MMI::InputManager::GetInstance()->SimulateInputEvent(pointerEvent);
        ret = true;
    }
    return ret;
}

} // namespace Ace
} // namespace OHOS
