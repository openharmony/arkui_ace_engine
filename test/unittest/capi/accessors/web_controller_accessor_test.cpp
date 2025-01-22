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

#include "core/interfaces/native/implementation/web_controller_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components/web/web_property.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockWebController : public WebController {
public:
    MockWebController() = default;
    ~MockWebController() override = default;
    MOCK_METHOD(void, OnInactive, (), (const));
    MOCK_METHOD(void, OnActive, (), (const));
    MOCK_METHOD(void, Zoom, (float), (const));
    MOCK_METHOD(void, ClearHistory, ());
    MOCK_METHOD(void, Refresh, (), (const));
    MOCK_METHOD(void, StopLoading, (), (const));
    MOCK_METHOD(void, RequestFocus, ());
    MOCK_METHOD(bool, AccessBackward, ());
    MOCK_METHOD(bool, AccessForward, ());
    MOCK_METHOD(bool, AccessStep, (int32_t));
    MOCK_METHOD(void, Backward, ());
    MOCK_METHOD(void, Forward, ());
    MOCK_METHOD(void, LoadDataWithBaseUrl,
        (std::string, std::string, std::string, std::string, std::string), (const));
    MOCK_METHOD(void, AddJavascriptInterface, (const std::string&, const std::vector<std::string>&));
    MOCK_METHOD(void, RemoveJavascriptInterface, (std::string, const std::vector<std::string>&));
    MOCK_METHOD(int, GetHitTestResult, ());
};
} // namespace

class WebControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebControllerAccessor,
    &GENERATED_ArkUIAccessors::getWebControllerAccessor, WebControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockWebController_ = new MockWebController();
        mockWebControllerKeeper_ = AceType::Claim(mockWebController_);
        ASSERT_NE(mockWebControllerKeeper_, nullptr);
        auto peerImpl = reinterpret_cast<GeneratedModifier::WebControllerPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockWebControllerKeeper_);
        ASSERT_NE(mockWebController_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockWebControllerKeeper_ = nullptr;
        mockWebController_ = nullptr;
    }

    MockWebController *mockWebController_ = nullptr;
    RefPtr<MockWebController> mockWebControllerKeeper_ = nullptr;
};

/**
 * @tc.name: onInactiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, onInactiveTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onInactive, nullptr);

    EXPECT_CALL(*mockWebController_, OnInactive()).Times(3);
    accessor_->onInactive(peer_);
    accessor_->onInactive(peer_);
    accessor_->onInactive(peer_);
    accessor_->onInactive(nullptr);
}

/**
 * @tc.name: onActiveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, onActiveTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onActive, nullptr);

    EXPECT_CALL(*mockWebController_, OnActive()).Times(3);
    accessor_->onActive(peer_);
    accessor_->onActive(peer_);
    accessor_->onActive(peer_);
    accessor_->onActive(nullptr);
}

/**
 * @tc.name: zoomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, zoomTest, TestSize.Level1)
{
    float factor1 = 5.5;
    float factor2 = -2.5;

    Ark_Number arkFactor1 = Converter::ArkValue<Ark_Number>(factor1);
    Ark_Number arkFactor2 = Converter::ArkValue<Ark_Number>(factor2);

    ASSERT_NE(accessor_->zoom, nullptr);

    EXPECT_CALL(*mockWebController_, Zoom(factor1)).Times(1);
    accessor_->zoom(peer_, &arkFactor1);
    accessor_->zoom(peer_, nullptr);

    EXPECT_CALL(*mockWebController_, Zoom(factor2)).Times(1);
    accessor_->zoom(peer_, &arkFactor2);
    accessor_->zoom(peer_, nullptr);
}

/**
 * @tc.name: clearHistoryTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, clearHistoryTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->clearHistory, nullptr);

    EXPECT_CALL(*mockWebController_, ClearHistory()).Times(3);
    accessor_->clearHistory(peer_);
    accessor_->clearHistory(peer_);
    accessor_->clearHistory(peer_);
    accessor_->clearHistory(nullptr);
}

/**
 * @tc.name: refreshTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, refreshTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->refresh, nullptr);

    EXPECT_CALL(*mockWebController_, Refresh()).Times(3);
    accessor_->refresh(peer_);
    accessor_->refresh(peer_);
    accessor_->refresh(peer_);
    accessor_->refresh(nullptr);
}

/**
 * @tc.name: stopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, stopTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stop, nullptr);

    EXPECT_CALL(*mockWebController_, StopLoading()).Times(3);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
    accessor_->stop(peer_);
    accessor_->stop(nullptr);
}

/**
 * @tc.name: requestFocusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, requestFocusTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->requestFocus, nullptr);

    EXPECT_CALL(*mockWebController_, RequestFocus()).Times(3);
    accessor_->requestFocus(peer_);
    accessor_->requestFocus(peer_);
    accessor_->requestFocus(peer_);
    accessor_->requestFocus(nullptr);
}

/**
 * @tc.name: accessBackwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, accessBackwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->accessBackward, nullptr);

    EXPECT_CALL(*mockWebController_, AccessBackward()).Times(3).WillRepeatedly(Return(true));
    EXPECT_TRUE(accessor_->accessBackward(peer_));
    EXPECT_TRUE(accessor_->accessBackward(peer_));
    EXPECT_TRUE(accessor_->accessBackward(peer_));

    EXPECT_CALL(*mockWebController_, AccessBackward()).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(accessor_->accessBackward(peer_));
    EXPECT_FALSE(accessor_->accessBackward(nullptr));
    EXPECT_FALSE(accessor_->accessBackward(peer_));
}

/**
 * @tc.name: accessForwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, accessForwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->accessForward, nullptr);

    EXPECT_CALL(*mockWebController_, AccessForward()).Times(3).WillRepeatedly(Return(true));
    EXPECT_TRUE(accessor_->accessForward(peer_));
    EXPECT_TRUE(accessor_->accessForward(peer_));
    EXPECT_TRUE(accessor_->accessForward(peer_));

    EXPECT_CALL(*mockWebController_, AccessForward()).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(accessor_->accessForward(peer_));
    EXPECT_FALSE(accessor_->accessForward(nullptr));
    EXPECT_FALSE(accessor_->accessForward(peer_));
}

/**
 * @tc.name: accessStepTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, accessStepTest, TestSize.Level1)
{
    int32_t step1 = 5;
    int32_t step2 = 10;

    Ark_Number arkStep1 = Converter::ArkValue<Ark_Number>(step1);
    Ark_Number arkStep2 = Converter::ArkValue<Ark_Number>(step2);

    ASSERT_NE(accessor_->accessStep, nullptr);

    EXPECT_CALL(*mockWebController_, AccessStep(step1)).Times(3).WillRepeatedly(Return(true));
    EXPECT_TRUE(accessor_->accessStep(peer_, &arkStep1));
    EXPECT_TRUE(accessor_->accessStep(peer_, &arkStep1));
    EXPECT_TRUE(accessor_->accessStep(peer_, &arkStep1));

    EXPECT_CALL(*mockWebController_, AccessStep(step2)).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(accessor_->accessStep(peer_, &arkStep2));
    EXPECT_FALSE(accessor_->accessStep(peer_, nullptr));
    EXPECT_FALSE(accessor_->accessStep(peer_, &arkStep2));
}

/**
 * @tc.name: backwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, backwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->backward, nullptr);

    EXPECT_CALL(*mockWebController_, Backward()).Times(3);
    accessor_->backward(peer_);
    accessor_->backward(peer_);
    accessor_->backward(peer_);
    accessor_->backward(nullptr);
}

/**
 * @tc.name: forwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, forwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->forward, nullptr);

    EXPECT_CALL(*mockWebController_, Forward()).Times(3);
    accessor_->forward(peer_);
    accessor_->forward(peer_);
    accessor_->forward(peer_);
    accessor_->forward(nullptr);
}

/**
 * @tc.name: loadDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, loadDataTest, TestSize.Level1)
{
    std::string baseUrl = "baseUrl";
    std::string data = "data";
    std::string mimeType = "mimeType";
    std::string encoding = "encoding";
    std::string historyUrl = "historyUrl";

    Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType options;
    options.baseUrl = Converter::ArkValue<Opt_String>(baseUrl);
    options.data = Converter::ArkValue<Ark_String>(data);
    options.mimeType = Converter::ArkValue<Ark_String>(mimeType);
    options.encoding = Converter::ArkValue<Ark_String>(encoding);
    options.historyUrl = Converter::ArkValue<Opt_String>(historyUrl);

    ASSERT_NE(accessor_->loadData, nullptr);

    EXPECT_CALL(*mockWebController_, LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl)).Times(1);
    accessor_->loadData(peer_, &options);
    accessor_->loadData(peer_, nullptr);
}

/**
 * @tc.name: DISABLED_loadUrlTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, DISABLED_loadUrlTest, TestSize.Level1)
{
    std::string url = "url";
    std::string headerKey = "headerKey";
    std::string headerValue = "headerValue";
    std::map<std::string, std::string> httpHeaders;
    httpHeaders[headerKey] = headerValue;

    Ark_Literal_Union_String_Resource_url_Array_Header_headers options;
    options.url = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(url);
    Ark_Header header;
    header.headerKey = Converter::ArkValue<Ark_String>(headerKey);
    header.headerValue = Converter::ArkValue<Ark_String>(headerValue);
    std::vector<Ark_Header> vec { header };
    Converter::ArkArrayHolder<Array_Header> vecHolder(vec);
    options.headers = vecHolder.OptValue<Opt_Array_Header>();

    ASSERT_NE(accessor_->loadUrl, nullptr);

    accessor_->loadUrl(peer_, &options);
    accessor_->loadUrl(peer_, nullptr);
}

/**
 * @tc.name: DISABLED_runJavaScriptTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, DISABLED_runJavaScriptTest, TestSize.Level1)
{
    std::string script = "script";

    Ark_Literal_String_script_Callback_String_Void_callback_ options;
    std::function<void(std::string)> callback = nullptr;
    options.script = Converter::ArkValue<Ark_String>(script);
    options.callback_ = Converter::ArkValue<Opt_Callback_String_Void>(Ark_Empty());

    ASSERT_NE(accessor_->runJavaScript, nullptr);

    accessor_->runJavaScript(peer_, &options);
    accessor_->runJavaScript(peer_, nullptr);
}

/**
 * @tc.name: registerJavaScriptProxyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, registerJavaScriptProxyTest, TestSize.Level1)
{
    std::string name = "name";
    std::string methodListItem = "methodListItem";

    Ark_Literal_Object_object__String_name_Array_String_methodList options;
    options.name = Converter::ArkValue<Ark_String>(name);
    std::vector<std::string> vec { methodListItem };
    Converter::ArkArrayHolder<Array_String> vecHolder(vec);
    options.methodList = vecHolder.ArkValue();

    ASSERT_NE(accessor_->registerJavaScriptProxy, nullptr);

    EXPECT_CALL(*mockWebController_, AddJavascriptInterface(name, vec)).Times(1);
    accessor_->registerJavaScriptProxy(peer_, &options);
    accessor_->registerJavaScriptProxy(peer_, nullptr);
}

/**
 * @tc.name: deleteJavaScriptRegisterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, deleteJavaScriptRegisterTest, TestSize.Level1)
{
    std::string name = "name";
    std::vector<std::string> vec {};

    Ark_String arkName = Converter::ArkValue<Ark_String>(name);

    ASSERT_NE(accessor_->deleteJavaScriptRegister, nullptr);

    EXPECT_CALL(*mockWebController_, RemoveJavascriptInterface(name, vec)).Times(1);
    accessor_->deleteJavaScriptRegister(peer_, &arkName);
    accessor_->deleteJavaScriptRegister(peer_, nullptr);
}

/**
 * @tc.name: getHitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebControllerAccessorTest, getHitTest, TestSize.Level1)
{
    int hitTestType = 1;

    ASSERT_NE(accessor_->getHitTest, nullptr);

    EXPECT_CALL(*mockWebController_, GetHitTestResult()).Times(3).WillRepeatedly(Return(hitTestType));
    accessor_->getHitTest(peer_);
    accessor_->getHitTest(peer_);
    accessor_->getHitTest(peer_);
    accessor_->getHitTest(nullptr);
}
} // namespace OHOS::Ace::NG
