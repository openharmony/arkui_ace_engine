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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AUTO_FILL_TRIGGER_STATE_HOLDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AUTO_FILL_TRIGGER_STATE_HOLDER_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
class AutoFillTriggerStateHolder : public virtual AceType {
    DECLARE_ACE_TYPE(AutoFillTriggerStateHolder, AceType);

public:
    AutoFillTriggerStateHolder() = default;
    ~AutoFillTriggerStateHolder() override = default;

    void SetAutoFillPasswordTriggered(bool value)
    {
        autoFillPasswordTriggered_ = value;
    }

    bool IsAutoFillPasswordTriggered() const
    {
        return autoFillPasswordTriggered_;
    }

    void SetAutoFillNewPasswordTriggered(bool value)
    {
        autoFillNewPasswordTriggered_ = value;
    }

    bool IsAutoFillNewPasswordTriggered() const
    {
        return autoFillNewPasswordTriggered_;
    }
private:
    bool autoFillPasswordTriggered_ = false;
    bool autoFillNewPasswordTriggered_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AUTO_FILL_TRIGGER_STATE_HOLDER_H
