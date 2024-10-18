/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_CONFIG_H
#define OHOS_ACE_COMPONENT_TEST_CONFIG_H

#include <functional>
#include <string>
#include <vector>

namespace OHOS::Ace::ComponentTest {

void ParseComponentTestConfig(const std::string JsonText);

class TestConfig {
public:
    std::string GetPage() const;
    std::string GetOut() const;
    bool IsComponentTestEnabled() const;

private:
    friend void ParseComponentTestConfig(const std::string JsonText);
    std::string page_;
    std::string out_;
    bool enableComponentTest_;
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_CONFIG_H
