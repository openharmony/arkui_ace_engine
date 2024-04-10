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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_XCOLLIEINTERFACE_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_XCOLLIEINTERFACE_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
class XcollieInterface : public AceType {
    DECLARE_ACE_TYPE(XcollieInterface, AceType);
public:
    static XcollieInterface& GetInstance();
    virtual int32_t SetTimerCount(const std::string& name, uint32_t timeLimit, int32_t countLimit)
    {
        return -1;
    }
    virtual void TriggerTimerCount(const std::string& name, bool bTrigger, const std::string& message) {};
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_XCOLLIEINTERFACE_H
