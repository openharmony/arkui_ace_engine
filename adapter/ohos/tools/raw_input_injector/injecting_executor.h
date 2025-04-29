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

#ifndef ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTING_EXECUTOR_H
#define ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTING_EXECUTOR_H

#include <string>
#include <vector>

#include "raw_input_command.h"

namespace OHOS {
namespace Ace {

struct InjectingInfo {
    int32_t actionType;
    int32_t finger;
    int32_t x;
    int32_t y;
    int64_t actionTime;
    int32_t sourceType; // not used for now
};

class InjectingExecutor {
public:
    static int32_t GetPointerActionFromCommandType(CommandType type);
    static CommandType GetCommandTypeFromPointerAction(int32_t pointerActionType);
    static std::string GetPointerActionName(int32_t pointerActionType);
    static bool IsEventNeedTriggerImmediatly(int32_t pointerActionType);
    // 1. the activing injecting will be used as the pointer event object;
    // 2. all other injectings will be packed into the activing injecting object;
    // 3. if there is no any activing injecting, the injecting will be given up, and return false as result;
    // 4. if there are more than 1 activing injecting, they will be injected one by one, and all other injecting info
    // will be packed into them seperatly;
    static bool InjectOnePonterEvent(
        std::vector<InjectingInfo>& activingInjecting, std::vector<InjectingInfo>& allOtherInjectings);

private:
    InjectingExecutor() = default;
    ~InjectingExecutor() = default;
};
} // namespace Ace
} // namespace OHOS
#endif // ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTING_EXECUTOR_H
