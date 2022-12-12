/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <iostream>
#include <memory>

#include "base/utils/macros.h"

namespace OHOS {
class MockAceContainer {
public:
    MockAceContainer() = default;
    virtual ~MockAceContainer() = default;
};

namespace AbilityRuntime {
class Context {
public:
    Context() = default;
    ~Context() = default;
};
} // namespace AbilityRuntime

namespace Ace::Platform {
class ACE_FORCE_EXPORT AceContainer : public MockAceContainer {
public:
    AceContainer() = default;
    ~AceContainer() = default;
    std::shared_ptr<AbilityRuntime::Context> GetAbilityContextByModule(
        const std::string& bundle, const std::string& module);
};

std::shared_ptr<AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    return nullptr;
}
} // namespace Ace::Platform
} // namespace OHOS