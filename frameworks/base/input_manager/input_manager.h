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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_INPUT_MANAGER_INPUT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_INPUT_MANAGER_INPUT_MANAGER_H

#include <set>
#include <vector>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {

using HotKey = std::tuple<std::set<int32_t>, int32_t>;

enum class KeyboardType : int32_t {
    NONE,
    UNKNOWN,
    ALPHABETICKEYBOARD,
    DIGITALKEYBOARD,
    HANDWRITINGPEN,
    REMOTECONTROL,
    MAX,
};

class ACE_EXPORT InputManager : public AceType {
    DECLARE_ACE_TYPE(InputManager, AceType)

public:
    static bool GetDeviceIds(std::vector<int32_t>& resDeviceIds);

    static KeyboardType GetKeyboardType(int32_t deviceId);

    static bool IsKeyboardConnected();

    static bool GetSystemHotkeys(std::vector<HotKey>& hotkeys);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_INPUT_MANAGER_INPUT_MANAGER_H