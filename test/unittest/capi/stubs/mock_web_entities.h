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
    MOCK_METHOD(std::vector<std::string>, GetMimeType, ());
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

class MockWebScreenCaptureRequest : public WebScreenCaptureRequest {
public:
    MOCK_METHOD(void, Deny, (), (const));
    MOCK_METHOD(void, SetCaptureMode, (int32_t));
    MOCK_METHOD(std::string, GetOrigin, (), (const));
    MOCK_METHOD(void, SetSourceId, (int32_t));
    MOCK_METHOD(void, Grant, (), (const));
};

class MockWebContextMenuParam : public WebContextMenuParam {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (const));
    MOCK_METHOD(int32_t, GetYCoord, (), (const));
    MOCK_METHOD(std::string, GetLinkUrl, (), (const));
    MOCK_METHOD(std::string, GetUnfilteredLinkUrl, (), (const));
    MOCK_METHOD(std::string, GetSourceUrl, (), (const));
    MOCK_METHOD(bool, HasImageContents, (), (const));
    MOCK_METHOD(bool, IsEditable, (), (const));
    MOCK_METHOD(int, GetEditStateFlags, (), (const));
    MOCK_METHOD(int, GetSourceType, (), (const));
    MOCK_METHOD(int, GetMediaType, (), (const));
    MOCK_METHOD(int, GetInputFieldType, (), (const));
    MOCK_METHOD(std::string, GetSelectionText, (), (const));

    void GetImageRect(int32_t& x, int32_t& y, int32_t& width, int32_t& height) const
    {
        width = mockPreviewWidth;
        height = mockPreviewHeight;
    }

public:
    int32_t mockPreviewWidth = -1;
    int32_t mockPreviewHeight = -1;
};

class MockContextMenuResult : public ContextMenuResult {
public:
    MOCK_METHOD(void, Cancel, (), (const));
    MOCK_METHOD(void, CopyImage, (), (const));
    MOCK_METHOD(void, Copy, (), (const));
    MOCK_METHOD(void, Paste, (), (const));
    MOCK_METHOD(void, Cut, (), (const));
    MOCK_METHOD(void, SelectAll, (), (const));
};

class MockSslErrorResult : public SslErrorResult {
public:
    MOCK_METHOD(void, HandleCancel, (bool));
    MOCK_METHOD(void, HandleConfirm, ());
};

class MockDataResubmitted : public DataResubmitted {
public:
    MOCK_METHOD(void, Resend, ());
    MOCK_METHOD(void, Cancel, ());
};

class MockWebCustomKeyboardHandler : public WebCustomKeyboardHandler {
public:
    MOCK_METHOD(void, InsertText, (const std::string &text));
    MOCK_METHOD(void, DeleteForward, (int32_t));
    MOCK_METHOD(void, DeleteBackward, (int32_t));
    MOCK_METHOD(void, SendFunctionKey, (int32_t));
    MOCK_METHOD(void, Close, ());
};

class MockWebWindowNewHandler : public WebWindowNewHandler {
public:
    MOCK_METHOD(void, SetWebController, (int32_t));
    MOCK_METHOD(bool, IsFrist, (), (const));
    MOCK_METHOD(int32_t, GetId, (), (const));
    MOCK_METHOD(int32_t, GetParentNWebId, (), (const));
};

class MockSslSelectCertResult : public SslSelectCertResult {
public:
    MOCK_METHOD(void, HandleConfirm, (const std::string&, const std::string&));
    MOCK_METHOD(void, HandleCancel, ());
    MOCK_METHOD(void, HandleIgnore, ());
};

} // namespace OHOS::Ace

#endif // CAPI_STUBS_MOCK_WEB_ENTITIES_H