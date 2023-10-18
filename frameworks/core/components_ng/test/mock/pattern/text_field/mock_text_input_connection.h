/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_TEXTINPUTCONNECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_TEXTINPUTCONNECTION_H

#include "core/common/ime/text_input_connection.h"

namespace OHOS::Ace::NG {
class MockTextInputConnection : public TextInputConnection {
    DECLARE_ACE_TYPE(MockTextInputConnection, AceType);
public:
    MockTextInputConnection() : TextInputConnection(nullptr, nullptr) {}

    ~MockTextInputConnection() override = default;

    void Show(bool isFocusViewChanged, int32_t instanceId) override {}

    void SetEditingState(const TextEditingValue& value, int32_t instanceId, bool needFireChangeEvent = true) override {}

    void Close(int32_t instanceId) override {}
};
}
#endif