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
#ifndef MOCK_UI_SA_INTERFACE_H
#define MOCK_UI_SA_INTERFACE_H

#include "iremote_broker.h"

namespace OHOS::Ace {

class MockSaInterface : public IRemoteBroker {
public:
    class MessageCode final {
    public:
        MessageCode() = delete;
        ~MessageCode() = delete;
        static constexpr uint32_t EXECUTE_METHOD = 1;
    };

    static constexpr int32_t SA_ID = 16666;

    MockSaInterface() = default;

    ~MockSaInterface() override = default;

    virtual std::string ExecuteMethod() = 0;

    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.mockSaInterface");
};

} // namespace OHOS::Ace

#endif // MOCK_UI_SA_INTERFACE_H