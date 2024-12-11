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

class MockWebFileSelectorParam : public WebFileSelectorParam {
public:
    MOCK_METHOD(std::string, GetTitle, ());
    MOCK_METHOD(int, GetMode, ());
    MOCK_METHOD(std::vector<std::string>, GetAcceptType, ());
    MOCK_METHOD(std::string, GetDefaultFileName, ());
    MOCK_METHOD(bool, IsCapture, ());
};

class MockFileSelectorResult : public FileSelectorResult {
public:
    MOCK_METHOD(void, HandleFileList, (std::vector<std::string>&));
};

class MockFullScreenExitHandler : public FullScreenExitHandler {
public:
    MOCK_METHOD(void, ExitFullScreen, ());
};

class MockAuthResult : public AuthResult {
public:
    MOCK_METHOD(bool, Confirm, (std::string&, std::string&));
    MOCK_METHOD(bool, IsHttpAuthInfoSaved, ());
    MOCK_METHOD(void, Cancel, ());
};

class MockWebPermissionRequest : public WebPermissionRequest {
public:
    MOCK_METHOD(void, Deny, (), (const));
    MOCK_METHOD(std::string, GetOrigin, (), (const));
    MOCK_METHOD(std::vector<std::string>, GetResources, (), (const));
    MOCK_METHOD(void, Grant, (std::vector<std::string>&), (const));
};

} // namespace OHOS::Ace

#endif // CAPI_STUBS_MOCK_WEB_ENTITIES_H