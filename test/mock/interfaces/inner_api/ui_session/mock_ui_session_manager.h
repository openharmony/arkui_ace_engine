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
    MOCK_METHOD0(GetSelectTextEventRegistered, bool());
    MOCK_METHOD2(ReportContentChangeEvent, void(ChangeType type, const std::string& simpleTree));
    MOCK_METHOD0(GetComponentChangeEventRegistered, bool());
    MOCK_METHOD3(SendPageTextToAI, void(int32_t nodeId, const std::string& text, int64_t version));
    MOCK_METHOD1(GetPageTranslateText, int32_t(const std::string& request));
    MOCK_METHOD1(StartPageTranslate, int32_t(const std::string& request));
    MOCK_METHOD0(EndPageTranslate, void());
    MOCK_METHOD1(ResetPageTranslate, void(int32_t nodeId));
    MOCK_METHOD1(SendPageTranslateResult, void(const std::string& result));
    MOCK_METHOD2(GetCurrentAbilityLanguageInfo, int32_t(std::string&, std::string&));
};
}
#endif
