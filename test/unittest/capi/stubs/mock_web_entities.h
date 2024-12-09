/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_WEB_ENTITIES_H
#define CAPI_STUBS_MOCK_WEB_ENTITIES_H

#include "gmock/gmock.h"

#include "core/components/web/web_event.h"

namespace OHOS::Ace {

class MockWebGeolocation : public WebGeolocation {
public:
    MOCK_METHOD(void, Invoke, (const std::string&, const bool&, const bool&));
};

class MockResult : public Result {
public:
    MOCK_METHOD(void, Confirm, (const std::string&));
    MOCK_METHOD(void, Confirm, ());
    MOCK_METHOD(void, Cancel, ());
};

} // namespace OHOS::Ace

#endif // CAPI_STUBS_MOCK_WEB_ENTITIES_H