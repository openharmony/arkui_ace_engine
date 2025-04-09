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

#include <gtest/gtest.h>
#include <mutex>
#include <memory>
#include "iservice_registry.h"
#include "iu_i_service_new.h"
#define private public
#define protected public
#include "ui_service_hilog.h"
#include "ui_service_mgr_client_idl.h"
#include "ui_service_new_stub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class MockUIServiceNewStub final : public UIServiceNewStub {
public:
    MockUIServiceNewStub() = default;
    ~MockUIServiceNewStub() = default;

    ErrCode OnPushCallBack(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
        const std::string& data, const std::string& extraData) override
    {
        return NO_ERROR;
    }
    ErrCode OnRequestCallBack(const AAFwk::Want& want, const std::string& name, const std::string& data) override
    {
        return NO_ERROR;
    }
    ErrCode OnReturnRequest(const AAFwk::Want& want, const std::string& source, const std::string& data,
        const std::string& extraData) override
    {
        return NO_ERROR;
    };
};

class UIServiceMgrClientIdlTest : public testing::Test {
protected:
    void SetUp() override
    {
        client_ = Ace::UIServiceMgrClientIdl::GetInstance();
    }

    void TearDown() override {};

    std::shared_ptr<UIServiceMgrClientIdl> client_;
};

/**
 * @tc.name: ConnectSuccess
 * @tc.desc: Test Connect success
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, ConnectSuccess, TestSize.Level1)
{
    // Act
    ErrCode result = client_->Connect();

    // Assert
    EXPECT_EQ(ERR_OK, result);
    EXPECT_NE(nullptr, client_->remoteObject_);
}

/**
 * @tc.name: RegisterCallBackFailure
 * @tc.desc: Test RegisterCallback failure
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, RegisterCallBackFailure, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;
    sptr<IUIServiceNew> uiService;

    // Act
    ErrCode result = client_->RegisterCallBack(want, uiService);

    // Assert ErrCode, uiService is nullptr will fail
    EXPECT_EQ(ERR_INVALID_DATA, result);
}

/**
 * @tc.name: RegisterCallBackSuccess
 * @tc.desc: Test RegisterCallback successfully
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, RegisterCallBackSuccess, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;
    sptr<MockUIServiceNewStub> uiService = new MockUIServiceNewStub();

    // Act
    ErrCode result = client_->RegisterCallBack(want, uiService);

    // Assert
    EXPECT_EQ(ERR_OK, result);
}

/**
 * @tc.name: UnregisterCallBackSuccess
 * @tc.desc: Test UnregisterCallback successfully
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, UnregisterCallBackSuccess, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;

    // Act
    ErrCode result = client_->UnregisterCallBack(want);

    // Assert
    EXPECT_EQ(ERR_OK, result);
}

/**
 * @tc.name: PushSuccess
 * @tc.desc: Test Push successfully
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, PushSuccess, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;
    std::string name = "test";
    std::string jsonPath = "test.json";
    std::string data = "testdata";
    std::string extraData = "extra";

    // Act
    ErrCode result = client_->Push(want, name, jsonPath, data, extraData);

    // Assert
    EXPECT_EQ(ERR_OK, result);
}

/**
 * @tc.name: RequestSuccess
 * @tc.desc: Test Request successfully
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, RequestSuccess, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;
    std::string name = "test";
    std::string data = "testdata";

    // Act
    ErrCode result = client_->Request(want, name, data);

    // Assert
    EXPECT_EQ(ERR_OK, result);
}

/**
 * @tc.name: ReturnRequestSuccess
 * @tc.desc: Test ReturnRequest successfully
 * @tc.type: FUNC
 */
HWTEST_F(UIServiceMgrClientIdlTest, ReturnRequestSuccess, TestSize.Level1)
{
    // Arrange
    AAFwk::Want want;
    std::string name = "test";
    std::string data = "testdata";
    std::string extraData = "extra";

    // Act
    ErrCode result = client_->ReturnRequest(want, name, data, extraData);

    // Assert
    EXPECT_EQ(ERR_OK, result);
}
} // namespace OHOS::Ace
