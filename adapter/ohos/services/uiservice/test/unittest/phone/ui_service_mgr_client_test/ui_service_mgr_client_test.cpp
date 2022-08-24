/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include <memory>

#include "mock_ui_service_mgr_client.h"
#include "ui_service_mgr_proxy.h"
#define private public
#include "mock_ui_mgr_service.h"
#include "mock_ui_service_callback.h"
#include "ui_service_proxy.h"
#include "ui_service_stub.h"

using namespace testing::ext;
using namespace testing;

namespace OHOS {
namespace Ace {
class UIServiceMgrClientTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void UIServiceMgrClientTest::SetUpTestCase(void)
{}
void UIServiceMgrClientTest::TearDownTestCase(void)
{}
void UIServiceMgrClientTest::SetUp()
{}
void UIServiceMgrClientTest::TearDown()
{}

/**
 * @tc.name: UIServiceMgrClient_RegisterCallBack_0100
 * @tc.desc: Verify that the UIServiceMgrClient RegisterCallBack is normal.
 * @tc.type: FUNC
 * @tc.require: issueI5IZU9
 */
HWTEST_F(UIServiceMgrClientTest, UIServiceMgrClient_RegisterCallBack_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_RegisterCallBack_0100 start";

    sptr<MockUIServiceCallBack> callBack(new (std::nothrow) MockUIServiceCallBack());
    sptr<UIServiceProxy> uiServiceProxy(new (std::nothrow) UIServiceProxy(callBack));

    MockUIServiceMgrClient::GetInstance();

    EXPECT_CALL(*((MockUIMgrService *)(UIServiceMgrClient::GetInstance()->remoteObject_).GetRefPtr()),
        RegisterCallBackCall(testing::_, testing::_))
        .Times(1);
    AAFwk::Want want;
    MockUIServiceMgrClient::GetInstance()->RegisterCallBack(want, uiServiceProxy);

    testing::Mock::AllowLeak(UIServiceMgrClient::GetInstance()->remoteObject_);
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_RegisterCallBack_0100 end";
}

/**
 * @tc.name: UIServiceMgrClient_UnregisterCallBack_0100
 * @tc.desc: Verify that the UIServiceMgrClient UnregisterCallBack is normal.
 * @tc.type: FUNC
 * @tc.require: issueI5IZU9
 */
HWTEST_F(UIServiceMgrClientTest, UIServiceMgrClient_UnregisterCallBack_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_UnregisterCallBack_0100 start";
    MockUIServiceMgrClient::GetInstance();
    EXPECT_CALL(*((MockUIMgrService *)(UIServiceMgrClient::GetInstance()->remoteObject_).GetRefPtr()),
        UnregisterCallBackCall(testing::_))
        .Times(1);
    AAFwk::Want want;
    MockUIServiceMgrClient::GetInstance()->UnregisterCallBack(want);

    testing::Mock::AllowLeak(UIServiceMgrClient::GetInstance()->remoteObject_);
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_UnregisterCallBack_0100 end";
}

/**
 * @tc.name: UIServiceMgrClient_Push_0100
 * @tc.desc: Verify that the UIServiceMgrClient Push is normal.
 * @tc.type: FUNC
 * @tc.require: issueI5IZU9
 */
HWTEST_F(UIServiceMgrClientTest, UIServiceMgrClient_Push_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_Push_0100 start";

    MockUIServiceMgrClient::GetInstance()->Connect();

    EXPECT_CALL(*((MockUIMgrService *)(UIServiceMgrClient::GetInstance()->remoteObject_).GetRefPtr()),
        PushCall(testing::_, testing::_, testing::_, testing::_, testing::_))
        .Times(1);

    AAFwk::Want want;
    const std::string name = "name";
    const std::string jsonPath = "jsonPath";
    const std::string data = "data";
    const std::string extraData = "extraData";
    MockUIServiceMgrClient::GetInstance()->Push(want, name, jsonPath, data, extraData);
    testing::Mock::AllowLeak(UIServiceMgrClient::GetInstance()->remoteObject_);
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_Push_0100 end";
}

/**
 * @tc.name: UIServiceMgrClient_Request_0100
 * @tc.desc: Verify that the UIServiceMgrClient Request is normal.
 * @tc.type: FUNC
 * @tc.require: issueI5IZU9
 */
HWTEST_F(UIServiceMgrClientTest, UIServiceMgrClient_Request_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_Request_0100 start";

    MockUIServiceMgrClient::GetInstance()->Connect();

    EXPECT_CALL(*((MockUIMgrService *)(UIServiceMgrClient::GetInstance()->remoteObject_).GetRefPtr()),
        RequestCall(testing::_, testing::_, testing::_))
        .Times(1);

    AAFwk::Want want;
    const std::string name = "name";
    const std::string data = "data";
    MockUIServiceMgrClient::GetInstance()->Request(want, name, data);
    testing::Mock::AllowLeak(UIServiceMgrClient::GetInstance()->remoteObject_);
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_Request_0100 end";
}

/**
 * @tc.name: UIServiceMgrClient_ReturnRequest_0100
 * @tc.desc: Verify that the UIServiceMgrClient ReturnRequest is normal.
 * @tc.type: FUNC
 * @tc.require: issueI5IZU9
 */
HWTEST_F(UIServiceMgrClientTest, UIServiceMgrClient_ReturnRequest_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_ReturnRequest_0100 start";

    MockUIServiceMgrClient::GetInstance()->Connect();

    EXPECT_CALL(*((MockUIMgrService *)(UIServiceMgrClient::GetInstance()->remoteObject_).GetRefPtr()),
        ReturnRequestCall(testing::_, testing::_, testing::_, testing::_))
        .Times(1);

    AAFwk::Want want;
    const std::string source = "source";
    const std::string data = "data";
    const std::string extraData = "extraData";
    MockUIServiceMgrClient::GetInstance()->ReturnRequest(want, source, data, extraData);
    testing::Mock::AllowLeak(UIServiceMgrClient::GetInstance()->remoteObject_);
    GTEST_LOG_(INFO) << "UIServiceMgrClientTest_UIServiceMgrClient_ReturnRequest_0100 end";
}
}  // namespace Ace
}  // namespace OHOS