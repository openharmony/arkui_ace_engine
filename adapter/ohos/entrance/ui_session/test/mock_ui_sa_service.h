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

#ifndef MOCK_UI_SA_SERVICE_H
#define MOCK_UI_SA_SERVICE_H

#include "system_ability.h"

#include "adapter/ohos/entrance/ui_session/test/mock_ui_sa_stub.h"

namespace OHOS::Ace {

class MockSaService final : public SystemAbility, public MockSaStub {
public:
    static MockSaService& GetInstance();

    ~MockSaService() override = default;

    MockSaService(const MockSaService&) = delete;

    MockSaService& operator=(const MockSaService&) = delete;

    MockSaService(MockSaService&&) = delete;

    MockSaService& operator=(MockSaService&&) = delete;

    void OnStart() override;

    void OnStop() override;

    std::string ExecuteMethod() override;

    int32_t Dump(int32_t fd, const std::vector<std::u16string>& args) override;

private:
    DECLEAR_SYSTEM_ABILITY(MockSaService);

    MockSaService();
};

} // namespace OHOS::Ace

#endif // MOCK_UI_SA_SERVICE_H