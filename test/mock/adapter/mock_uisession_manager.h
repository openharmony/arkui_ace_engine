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

#ifndef TEST_MOCK_ADAPTER_MOCK_UI_SESSION_MANAGER_H
#define TEST_MOCK_ADAPTER_MOCK_UI_SESSION_MANAGER_H

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "gmock/gmock.h"

namespace OHOS::Ace {
class MockUiSessionManager : public UiSessionManager {
public:
    MockUiSessionManager() = default;
    ~MockUiSessionManager() override = default;

    MOCK_METHOD2(OnRouterChange, void(const std::string& path, const std::string& event));
};
}
#endif
