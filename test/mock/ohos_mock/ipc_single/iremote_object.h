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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H

#include "refbase.h"
#include <string>

namespace OHOS {
class IRemoteObject {
public:
    explicit IRemoteObject(const std::u16string& descriptor = std::u16string()) {}
    virtual ~IRemoteObject() = default;

    class DeathRecipient {
    public:
       /**
        * @brief Methods that enumerate death notifications.
        * @since 9
        */
        enum {
            ADD_DEATH_RECIPIENT,
            REMOVE_DEATH_RECIPIENT,
            NOTICE_DEATH_RECIPIENT,
            TEST_SERVICE_DEATH_RECIPIENT,
            TEST_DEVICE_DEATH_RECIPIENT,
        };
        DeathRecipient() = default;
        virtual ~DeathRecipient() = default;

        /**
         * @brief Called to perform subsequent operations when a death notification of the remote object is received.
         * @param object Indicates the IRemoteObject pointer object.
         * @return void
         * @since 9
         */
        virtual void OnRemoteDied(const wptr<IRemoteObject> &object) = 0;
    };
};
}

#endif //FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_TEST_MOCK_MOCK_IREMOTE_OBJECT_H
