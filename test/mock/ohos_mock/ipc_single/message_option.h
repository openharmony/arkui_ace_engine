/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_MESSAGE_OPTION_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_MESSAGE_OPTION_H

#include <memory>
namespace OHOS {
class MessageOption {
public:
    enum {
        TF_SYNC = 0x00,
        TF_ASYNC = 0x01,
        TF_STATUS_CODE = 0x08,
        TF_ACCEPT_FDS = 0x10,
        TF_WAIT_TIME = 0x8,
        TF_ASYNC_WAKEUP_LATER = 0x100000,
    };
    MessageOption(int flags = TF_SYNC, int waitTime = TF_WAIT_TIME)
        :flags_(static_cast<uint32_t>(flags)), waitTime_(waitTime)
    {
    }

    ~MessageOption() = default;

    void SetFlags(int flags)
    {
        flags_ |= static_cast<uint32_t>(flags);
    }

    int GetFlags() const
    {
        return flags_;
    }

    void SetWaitTime(int waitTime)
    {
        if (waitTime <= 0) {
            waitTime_ = TF_WAIT_TIME;
        } else if (waitTime > MAX_WAIT_TIME) {
            waitTime_ = MAX_WAIT_TIME;
        } else {
            waitTime_ = waitTime;
        }
    }

    int GetWaitTime() const
    {
        return waitTime_;
    }

private:
    static constexpr int MAX_WAIT_TIME = 3000;
    uint32_t flags_;
    int waitTime_;
};
} // namespace OHOS
#endif // OHOS_IPC_MESSAGE_OPTION_H
