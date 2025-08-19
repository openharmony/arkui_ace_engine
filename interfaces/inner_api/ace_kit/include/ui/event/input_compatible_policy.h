/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_EVENT_INPUT_COMPATIBLE_POLICY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_EVENT_INPUT_COMPATIBLE_POLICY_H
#include <memory>
#include <string>
#include <unordered_map>

#include "ui/base/ace_type.h"
#include "ui/base/macros.h"

namespace OHOS::Ace::Kit {
enum class InputCompatibleSource : int8_t {
    LEFT_PRESS,
    SCROLL_AXIS_EVENT,
};

class ACE_EXPORT InputCompatiblePolicy : public AceType {
public:
    static InputCompatiblePolicy* GetInputCompatiblePolicyInstance();
    virtual bool IsInputCompatibleConvertingNeeded(InputCompatibleSource source) = 0;
    virtual ~InputCompatiblePolicy() {}
};
} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_EVENT_INPUT_COMPATIBLE_POLICY_H