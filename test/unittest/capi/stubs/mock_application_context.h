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
#ifndef CAPI_STUBS_MOCK_APPLICATION_CONTEXT_H
#define CAPI_STUBS_MOCK_APPLICATION_CONTEXT_H

#include <memory>
#include <string>

namespace OHOS {
namespace AbilityRuntime {

class ApplicationContext {
public:
    static std::shared_ptr<ApplicationContext> GetApplicationContext()
    {
        static std::shared_ptr<ApplicationContext> applicationContext;
        if (!applicationContext) {
            applicationContext = std::make_shared<ApplicationContext>();
        }
        return applicationContext;
    }
    std::string GetBundleCodeDir()
    {
        return "/test/";
    }
};
} // namespace AbilityRuntime
} // namespace OHOS

#endif