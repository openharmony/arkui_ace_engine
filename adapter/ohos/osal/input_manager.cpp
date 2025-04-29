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

#include "base/input_manager/input_manager.h"

#include "input_manager.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {

bool InputManager::GetDeviceIds(std::vector<int32_t>& resDeviceIds)
{
    auto* inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_RETURN(inputManager, false);
    inputManager->GetDeviceIds([&resDeviceIds](std::vector<int32_t>& deviceIds) { resDeviceIds = deviceIds; });
    return true;
}

std::shared_ptr<MMI::PointerEvent> InputManager::CreatePointerEvent(
    const std::shared_ptr<const MMI::PointerEvent>& pointerEvent)
{
    if (!pointerEvent) {
        return nullptr;
    }
    return std::make_shared<MMI::PointerEvent>(*pointerEvent);
}

KeyboardType ConvertKeyboardType(int32_t type)
{
    switch (type) {
        case MMI::KeyboardType::KEYBOARD_TYPE_NONE:
            return KeyboardType::NONE;
        case MMI::KeyboardType::KEYBOARD_TYPE_UNKNOWN:
            return KeyboardType::UNKNOWN;
        case MMI::KeyboardType::KEYBOARD_TYPE_ALPHABETICKEYBOARD:
            return KeyboardType::ALPHABETICKEYBOARD;
        case MMI::KeyboardType::KEYBOARD_TYPE_DIGITALKEYBOARD:
            return KeyboardType::DIGITALKEYBOARD;
        case MMI::KeyboardType::KEYBOARD_TYPE_HANDWRITINGPEN:
            return KeyboardType::HANDWRITINGPEN;
        case MMI::KeyboardType::KEYBOARD_TYPE_REMOTECONTROL:
            return KeyboardType::REMOTECONTROL;
        case MMI::KeyboardType::KEYBOARD_TYPE_MAX:
            return KeyboardType::MAX;
        default:
            return KeyboardType::NONE;
    }
}

KeyboardType InputManager::GetKeyboardType(int32_t deviceId)
{
    auto* inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_RETURN(inputManager, KeyboardType::UNKNOWN);
    int32_t mmiKeyboardType = 0;
    inputManager->GetKeyboardType(
        deviceId, [&mmiKeyboardType](int32_t keyboardType) { mmiKeyboardType = keyboardType; });
    return ConvertKeyboardType(mmiKeyboardType);
}

bool InputManager::GetSystemHotkeys(std::vector<HotKey>& hotkeys)
{
    auto* inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_RETURN(inputManager, false);

    std::vector<std::unique_ptr<OHOS::MMI::KeyOption>> keyOptions;
    int32_t count = 0;
    inputManager->GetAllSystemHotkeys(keyOptions, count);

    if (keyOptions.empty()) {
        return false;
    }
    for (const auto& key : keyOptions) {
        hotkeys.push_back({ key->GetPreKeys(), key->GetFinalKey() });
    }
    return true;
}

bool InputManager::IsKeyboardConnected()
{
    std::vector<int32_t> deviceIds;
    auto resGetIds = GetDeviceIds(deviceIds);
    if (!resGetIds) {
        return false;
    }
    return std::any_of(deviceIds.begin(), deviceIds.end(),
        [](int32_t id) { return GetKeyboardType(id) == KeyboardType::ALPHABETICKEYBOARD; });
}

} // namespace OHOS::Ace
