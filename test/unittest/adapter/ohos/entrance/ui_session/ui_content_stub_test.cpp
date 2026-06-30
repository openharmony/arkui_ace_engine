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

#include "gtest/gtest.h"

#include <atomic>

#define private public
#define protected public

#include "interfaces/inner_api/ui_session/ui_content_stub_impl.h"
#include "interfaces/inner_api/ui_session/ui_content_proxy.h"
#include "interfaces/inner_api/ui_session/ui_report_stub.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "interfaces/inner_api/ui_session/ui_session_request_guard.h"
#include "interfaces/inner_api/ui_session/ui_translate_request_util.h"
#include "test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.h"

#include "accesstoken_kit.h"

#include <functional>
#include <memory>
#include <utility>
#include <vector>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_EMPTY_SCOPE = 0;
constexpr int32_t INVALID_UNKNOWN_SCOPE = 1 << 4;
constexpr int32_t ARKWEB_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKWEB_ONLY);
constexpr int32_t ARKUI_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKUI_ONLY);
constexpr int32_t ARKUI_ARKWEB_SCOPE = static_cast<int32_t>(TranslateContentScope::ARKUI_ARKWEB);
constexpr int32_t RESERVED_XCOMPONENT_SCOPE = static_cast<int32_t>(TranslateContentScope::XCOMPONENT);
constexpr int32_t RESERVED_CANVAS_SCOPE = static_cast<int32_t>(TranslateContentScope::CANVAS_NODE);
constexpr int32_t PAGE_ALL_SCOPE = static_cast<int32_t>(TranslateContentScope::PAGE_ALL);
constexpr char EMPTY_TRANSLATE_REQUEST[] = "";
constexpr char LEGACY_TRANSLATE_EXTRA_DATA[] = "legacy extra data";
constexpr char VALID_NON_OBJECT_TRANSLATE_REQUEST[] = R"([{"scope":3}])";
constexpr char VALID_NO_SCOPE_TRANSLATE_REQUEST[] = R"({"extraData":"test"})";
constexpr char VALID_NULL_SCOPE_TRANSLATE_REQUEST[] = R"({"scope":null})";
constexpr char VALID_TRANSLATE_SCOPE_REQUEST[] = R"({"scope":3})";
constexpr char VALID_TRANSLATE_EXTRA_ONLY_REQUEST[] = R"({"extraData":"test"})";
constexpr char INVALID_ZERO_TRANSLATE_SCOPE_REQUEST[] = R"({"scope":0})";
constexpr char INVALID_NEGATIVE_TRANSLATE_SCOPE_REQUEST[] = R"({"scope":-1})";
constexpr char INVALID_UNKNOWN_TRANSLATE_SCOPE_REQUEST[] = R"({"scope":16})";
constexpr char INVALID_STRING_TRANSLATE_SCOPE_REQUEST[] = R"({"scope":"3"})";
constexpr int32_t TRANSLATE_TITLE_NODE_ID = 6;
constexpr int32_t TRANSLATE_PLACEHOLDER_NODE_ID = 13;
constexpr int32_t TRANSLATE_BUTTON_NODE_ID = 16;
constexpr int64_t TRANSLATE_SNAPSHOT_VERSION = 0;
constexpr int64_t TRANSLATE_FIRST_VERSION = 1;
constexpr int64_t TRANSLATE_SECOND_VERSION = 2;
constexpr int64_t TRANSLATE_THIRD_VERSION = 3;
constexpr int64_t TRANSLATE_LARGE_VERSION = 3000000000;

struct TranslateScopeTestData {
    int32_t scope;
    bool expected;
};

struct TranslateRequestTestData {
    const char* request;
    bool expected;
};

struct TranslateTextDecodeTestData {
    const char* text;
    const char* expected;
};

struct TranslateResultParseTestData {
    const char* result;
    bool expected;
    size_t expectedSize;
};

struct TranslateResultIdentityTestData {
    const char* result;
    std::vector<std::pair<int32_t, int64_t>> expected;
};

void PrepareValidUiSessionParcel(MessageParcel& data)
{
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
}
} // namespace

class UIContentStubTest : public testing::Test {};

/**
 * @tc.name: UIContentStubTest001
 * @tc.desc: Test UI_CONTENT_SERVICE_GET_TREE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UI_CONTENT_SERVICE_GET_TREE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest002
 * @tc.desc: Test UI_CONTENT_CONNECT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UI_CONTENT_CONNECT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest003
 * @tc.desc: Test REGISTER_CLICK_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_CLICK_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest004
 * @tc.desc: Test REGISTER_SEARCH_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_SEARCH_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest005
 * @tc.desc: Test REGISTER_TEXT_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_TEXT_CHANGE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest006
 * @tc.desc: Test REGISTER_ROUTER_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_ROUTER_CHANGE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest007
 * @tc.desc: Test REGISTER_COMPONENT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_COMPONENT_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest008
 * @tc.desc: Test REGISTER_WEB_UNFOCUS_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_WEB_UNFOCUS_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest009
 * @tc.desc: Test REGISTER_SCROLL_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_SCROLL_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest010
 * @tc.desc: Test REGISTER_LIFE_CYCLE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_LIFE_CYCLE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest011
 * @tc.desc: Test REGISTER_SELECT_TEXT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_SELECT_TEXT_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest012
 * @tc.desc: Test SENDCOMMAND_ASYNC_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::SENDCOMMAND_ASYNC_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest013
 * @tc.desc: Test SENDCOMMAND_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::SENDCOMMAND_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest014
 * @tc.desc: Test UNREGISTER_CLICK_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_CLICK_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest015
 * @tc.desc: Test UNREGISTER_SEARCH_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_SEARCH_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest016
 * @tc.desc: Test UNREGISTER_TEXT_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_TEXT_CHANGE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest017
 * @tc.desc: Test UNREGISTER_ROUTER_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_ROUTER_CHANGE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest018
 * @tc.desc: Test UNREGISTER_COMPONENT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_COMPONENT_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest019
 * @tc.desc: Test UNREGISTER_WEB_UNFOCUS_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_WEB_UNFOCUS_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest020
 * @tc.desc: Test UNREGISTER_SCROLL_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_SCROLL_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest021
 * @tc.desc: Test UNREGISTER_LIFE_CYCLE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_LIFE_CYCLE_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest022
 * @tc.desc: Test UNREGISTER_SELECT_TEXT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_SELECT_TEXT_EVENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest023
 * @tc.desc: Test RESET_ALL_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::RESET_ALL_TEXT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest024
 * @tc.desc: Test RESET_TEXT_BY_ID
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::RESET_TEXT_BY_ID, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest025
 * @tc.desc: Test GET_WEB_VIEW_LANGUAGE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_WEB_VIEW_LANGUAGE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest026
 * @tc.desc: Test GET_WEB_TRANSLATE_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_WEB_TRANSLATE_TEXT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest027
 * @tc.desc: Test CONTINUE_GET_WEB_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::CONTINUE_GET_WEB_TEXT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest028
 * @tc.desc: Test SEND_TRANSLATE_RESULT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::SEND_TRANSLATE_RESULT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest029
 * @tc.desc: Test END_WEB_TRANSLATE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::END_WEB_TRANSLATE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest030
 * @tc.desc: Test SEND_TRANSLATE_RESULT_STR
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::SEND_TRANSLATE_RESULT_STR, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest031
 * @tc.desc: Test GET_CURRENT_PAGE_NAME
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_CURRENT_PAGE_NAME, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest032
 * @tc.desc: Test GET_CURRENT_SHOWING_IMAGE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_CURRENT_SHOWING_IMAGE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest033
 * @tc.desc: Test GET_VISIBLE_TREE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_VISIBLE_TREE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest034
 * @tc.desc: Test SEND_COMMAND
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::SEND_COMMAND, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest035
 * @tc.desc: Test EXE_APP_AI_FUNCTION
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::EXE_APP_AI_FUNCTION, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest036
 * @tc.desc: Test GET_SPECIFIED_CONTENT_OFFSETS
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_SPECIFIED_CONTENT_OFFSETS, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest037
 * @tc.desc: Test HIGHLIGHT_SPECIFIED_CONTENT
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::HIGHLIGHT_SPECIFIED_CONTENT, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest038
 * @tc.desc: Test GET_MULTI_IMAGES_BY_ID
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_MULTI_IMAGES_BY_ID, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest039
 * @tc.desc: Test REGISTER_CONTENT_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REGISTER_CONTENT_CHANGE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest040
 * @tc.desc: Test UNREGISTER_CONTENT_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::UNREGISTER_CONTENT_CHANGE, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest041
 * @tc.desc: Test GET_HIT_TEST_NODE_INFO_FOR_TOUCH
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::GET_HIT_TEST_NODE_INFO_FOR_TOUCH, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest042
 * @tc.desc: Test REQUEST_STATE_MGMT_INFO
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat UIContentServiceStubImpl and creat MessageParcel add MessageOption
     * @tc.expected: step1. call UIContentServiceStubImpl OnRemoteRequest return -1 because of AccessToken check failed.
     */
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    MessageParcel data = MessageParcel();
    MessageParcel reply = MessageParcel();
    MessageOption option = MessageOption();

    auto res = ptr->OnRemoteRequest(0, data, reply, option);
    EXPECT_EQ(res, -1);

    /**
     * @tc.steps: step2. simulate AccessToken check success.
     * @tc.expected: step2. call UIContentServiceStubImpl OnRemoteRequest return success.
     */
    Security::AccessToken::AccessTokenKit::mockTokenTypeFlag_ = Security::AccessToken::ATokenTypeEnum::TOKEN_NATIVE;
    data.WriteInterfaceToken(u"ohos.ace.UIContentService");
    res = ptr->OnRemoteRequest(IUiContentService::REQUEST_STATE_MGMT_INFO, data, reply, option);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: UIContentStubTest043
 * @tc.desc: Test translate content scope bitmask validation.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest043, TestSize.Level1)
{
    const TranslateScopeTestData testData[] = {
        { ARKWEB_SCOPE, true },
        { ARKUI_SCOPE, true },
        { ARKUI_ARKWEB_SCOPE, true },
        { RESERVED_XCOMPONENT_SCOPE, true },
        { RESERVED_CANVAS_SCOPE, true },
        { PAGE_ALL_SCOPE, true },
        { INVALID_EMPTY_SCOPE, false },
        { INVALID_UNKNOWN_SCOPE, false },
    };

    for (const auto& item : testData) {
        EXPECT_EQ(PageTranslateRequestUtil::IsTranslateScopeValid(item.scope), item.expected);
    }
}

/**
 * @tc.name: UIContentStubTest044
 * @tc.desc: Test page translate request validation.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest044, TestSize.Level1)
{
    const TranslateRequestTestData testData[] = {
        { EMPTY_TRANSLATE_REQUEST, true },
        { LEGACY_TRANSLATE_EXTRA_DATA, true },
        { VALID_NON_OBJECT_TRANSLATE_REQUEST, true },
        { VALID_NO_SCOPE_TRANSLATE_REQUEST, true },
        { VALID_NULL_SCOPE_TRANSLATE_REQUEST, true },
        { VALID_TRANSLATE_SCOPE_REQUEST, true },
        { VALID_TRANSLATE_EXTRA_ONLY_REQUEST, true },
        { INVALID_ZERO_TRANSLATE_SCOPE_REQUEST, false },
        { INVALID_NEGATIVE_TRANSLATE_SCOPE_REQUEST, false },
        { INVALID_UNKNOWN_TRANSLATE_SCOPE_REQUEST, false },
        { INVALID_STRING_TRANSLATE_SCOPE_REQUEST, false },
    };

    for (const auto& item : testData) {
        EXPECT_EQ(PageTranslateRequestUtil::IsPageTranslateRequestValid(item.request), item.expected);
    }
}

/**
 * @tc.name: UIContentStubTest045
 * @tc.desc: Test page translate result text decodes unicode escape literals only.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest045, TestSize.Level1)
{
    const TranslateTextDecodeTestData testData[] = {
        { u8"详情中文", u8"详情中文" },
        { R"(\u8be6\u60c5\u4e2d\u6587)", u8"详情中文" },
        { R"(prefix-\u8be6\u60c5-suffix)", u8"prefix-详情-suffix" },
        { R"(\ud83d\ude00)", u8"😀" },
        { R"(\u8bg6\x60c5)", R"(\u8bg6\x60c5)" },
        { R"(\ud83d)", R"(\ud83d)" },
        { R"(C:\temp\file)", R"(C:\temp\file)" },
    };

    for (const auto& item : testData) {
        EXPECT_EQ(PageTranslateRequestUtil::DecodeJsonUnicodeEscapes(item.text), item.expected);
    }
}

/**
 * @tc.name: UIContentStubTest046
 * @tc.desc: Test page translate result parser supports single and batch results.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest046, TestSize.Level1)
{
    const TranslateResultParseTestData testData[] = {
        { R"({"nodeId":6,"version":0,"translatedText":"\u6807\u9898"})", true, 1 },
        { R"({"nodeId":7,"version":2,"text":"详情中文"})", true, 1 },
        { R"({"results":[{"nodeId":6,"version":1,"translatedText":"\u6807\u9898"},)"
          R"({"nodeId":13,"version":1,"text":"输入框提示"}]})",
            true, 2 },
        { R"([{"nodeId":6,"version":3,"translatedText":"标题"},{"nodeId":7,"version":3,"text":"详情"}])", true, 2 },
        { R"({"results":[]})", false, 0 },
        { R"({"results":[1,false]})", false, 0 },
        { R"({"version":1,"translatedText":"标题"})", false, 0 },
        { R"({"nodeId":6,"translatedText":"标题"})", false, 0 },
        { R"({"nodeId":6,"version":1,"translatedText":""})", false, 0 },
        { R"("invalid")", false, 0 },
    };

    for (const auto& item : testData) {
        std::vector<PageTranslateRequestUtil::TranslateResult> results;
        EXPECT_EQ(PageTranslateRequestUtil::ParseTranslateResults(item.result, results), item.expected);
        EXPECT_EQ(results.size(), item.expectedSize);
    }

    std::vector<PageTranslateRequestUtil::TranslateResult> results;
    ASSERT_TRUE(PageTranslateRequestUtil::ParseTranslateResults(
        R"({"results":[{"nodeId":6,"version":3000000000,"translatedText":"\u6807\u9898"},)"
        R"({"nodeId":13,"version":2,"text":"输入框提示"}]})",
        results));
    ASSERT_EQ(results.size(), 2U);
    EXPECT_EQ(results[0].nodeId, 6);
    EXPECT_EQ(results[0].version, TRANSLATE_LARGE_VERSION);
    EXPECT_EQ(results[0].translatedText, u8"标题");
    EXPECT_EQ(results[1].nodeId, 13);
    EXPECT_EQ(results[1].version, 2);
    EXPECT_EQ(results[1].translatedText, u8"输入框提示");
}

/**
 * @tc.name: UIContentStubTest047
 * @tc.desc: Test page translate result identity parser supports single, array, and batch results.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest047, TestSize.Level1)
{
    const TranslateResultIdentityTestData testData[] = {
        { R"({"nodeId":6,"version":0,"translatedText":"\u6807\u9898"})",
            { { TRANSLATE_TITLE_NODE_ID, TRANSLATE_SNAPSHOT_VERSION } } },
        { R"({"results":[{"nodeId":6,"version":1,"translatedText":"\u6807\u9898"},)"
          R"({"nodeId":13,"version":2,"text":"输入框提示"},{"nodeId":16,"version":0,"text":"按钮"}]})",
            { { TRANSLATE_TITLE_NODE_ID, TRANSLATE_FIRST_VERSION },
                { TRANSLATE_PLACEHOLDER_NODE_ID, TRANSLATE_SECOND_VERSION },
                { TRANSLATE_BUTTON_NODE_ID, TRANSLATE_SNAPSHOT_VERSION } } },
        { R"([{"nodeId":6,"version":3,"translatedText":"标题"},{"nodeId":13,"version":2,"text":"详情"}])",
            { { TRANSLATE_TITLE_NODE_ID, TRANSLATE_THIRD_VERSION },
                { TRANSLATE_PLACEHOLDER_NODE_ID, TRANSLATE_SECOND_VERSION } } },
        { R"({"nodeId":6,"version":3000000000,"translatedText":"标题"})",
            { { TRANSLATE_TITLE_NODE_ID, TRANSLATE_LARGE_VERSION } } },
        { R"({"results":[{"nodeId":-1,"version":1},{"nodeId":16,"version":0},{"nodeId":)"
          R"(7}]})",
            { { TRANSLATE_BUTTON_NODE_ID, TRANSLATE_SNAPSHOT_VERSION } } },
        { R"({"nodeId":6,"translatedText":"missing version"})", {} },
        { R"({"results":[]})", {} },
        { R"("invalid")", {} },
        { R"(invalid json)", {} },
    };

    for (const auto& item : testData) {
        EXPECT_EQ(PageTranslateRequestUtil::ParseTranslateResultIdentities(item.result), item.expected);
    }
}

/**
 * @tc.name: UIContentStubTest048
 * @tc.desc: Test page translate request transactions are dispatched to UiSessionManager.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest048, TestSize.Level1)
{
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    auto manager = static_cast<OHOS::Ace::MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(manager, nullptr);

    struct RequestTransactionCase {
        uint32_t code;
        int32_t result;
    };
    const RequestTransactionCase testData[] = {
        { IUiContentService::GET_PAGE_TRANSLATE_TEXT, PARAM_INVALID },
        { IUiContentService::START_PAGE_TRANSLATE, LAST_UNFINISH },
    };

    for (const auto& item : testData) {
        Mock::VerifyAndClearExpectations(manager);
        if (item.code == IUiContentService::GET_PAGE_TRANSLATE_TEXT) {
            EXPECT_CALL(*manager, GetPageTranslateText(StrEq("mockString"))).Times(1).WillOnce(Return(item.result));
        } else {
            EXPECT_CALL(*manager, StartPageTranslate(StrEq("mockString"))).Times(1).WillOnce(Return(item.result));
        }
        MessageParcel data;
        MessageParcel reply;
        MessageOption option;
        PrepareValidUiSessionParcel(data);
        data.WriteString(VALID_TRANSLATE_SCOPE_REQUEST);

        EXPECT_EQ(ptr->OnRemoteRequest(item.code, data, reply, option), NO_ERROR);
    }
    Mock::VerifyAndClearExpectations(manager);
}

/**
 * @tc.name: UIContentStubTest049
 * @tc.desc: Test page translate control transactions are dispatched to UiSessionManager.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest049, TestSize.Level1)
{
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    auto manager = static_cast<OHOS::Ace::MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(manager, nullptr);

    struct ControlTransactionCase {
        uint32_t code;
        std::function<void(MessageParcel&)> writePayload;
        std::function<void()> expectCall;
    };
    const std::string translateResult = R"({"nodeId":6,"version":1,"translatedText":"标题"})";
    const ControlTransactionCase testData[] = {
        {
            IUiContentService::END_PAGE_TRANSLATE,
            [](MessageParcel&) {},
            [manager]() { EXPECT_CALL(*manager, EndPageTranslate()).Times(1); },
        },
        {
            IUiContentService::RESET_PAGE_TRANSLATE,
            [](MessageParcel& data) { data.WriteInt32(TRANSLATE_TITLE_NODE_ID); },
            [manager]() { EXPECT_CALL(*manager, ResetPageTranslate(0)).Times(1); },
        },
        {
            IUiContentService::SEND_PAGE_TRANSLATE_RESULT,
            [&translateResult](MessageParcel& data) { data.WriteString(translateResult); },
            [manager]() { EXPECT_CALL(*manager, SendPageTranslateResult(_)).Times(0); },
        },
    };

    for (const auto& item : testData) {
        Mock::VerifyAndClearExpectations(manager);
        item.expectCall();
        MessageParcel data;
        MessageParcel reply;
        MessageOption option;
        PrepareValidUiSessionParcel(data);
        item.writePayload(data);

        EXPECT_EQ(ptr->OnRemoteRequest(item.code, data, reply, option), NO_ERROR);
    }
    Mock::VerifyAndClearExpectations(manager);
}

/**
 * @tc.name: UIContentStubTest050
 * @tc.desc: Test page translate callback rejects repeated single get and releases after result finish.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest050, TestSize.Level1)
{
    sptr<UiReportStub> report = std::make_shared<UiReportStub>();
    int32_t reportCount = 0;
    PageTranslateTextCallback callback = [&reportCount](int32_t, const std::string&, int64_t) {
        ++reportCount;
    };

    EXPECT_TRUE(report->RegisterPageTranslateTextCallback(callback, false));
    EXPECT_FALSE(report->RegisterPageTranslateTextCallback(callback, false));
    report->SendPageText(TRANSLATE_TITLE_NODE_ID, "title", TRANSLATE_FIRST_VERSION);
    EXPECT_EQ(reportCount, 1);
    EXPECT_FALSE(report->RegisterPageTranslateTextCallback(callback, false));
    report->FinishPageTranslateTextRequest();
    EXPECT_TRUE(report->RegisterPageTranslateTextCallback(callback, false));
    report->UnregisterPageTranslateTextCallback();
}

/**
 * @tc.name: UIContentStubTest051
 * @tc.desc: Test continuous page translate callback is released only by unregister.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest051, TestSize.Level1)
{
    sptr<UiReportStub> report = std::make_shared<UiReportStub>();
    PageTranslateTextCallback callback = [](int32_t, const std::string&, int64_t) {};
    int32_t timeoutCount = 0;

    report->pageTranslateTimeoutCallback_ = [&timeoutCount]() {
        ++timeoutCount;
    };
    EXPECT_TRUE(report->RegisterPageTranslateTextCallback(callback, true));
    EXPECT_FALSE(report->pageTranslateTimeoutCallback_);
    report->HandlePageTranslateResultWatchdogTimeout(TRANSLATE_TITLE_NODE_ID, TRANSLATE_FIRST_VERSION);
    EXPECT_EQ(timeoutCount, 0);
    report->FinishPageTranslateTextRequest();
    EXPECT_FALSE(report->RegisterPageTranslateTextCallback(callback, false));
    report->UnregisterPageTranslateTextCallback();
    EXPECT_TRUE(report->RegisterPageTranslateTextCallback(callback, false));
    report->UnregisterPageTranslateTextCallback();
}

/**
 * @tc.name: UIContentStubTest052
 * @tc.desc: Test current ability language transaction uses synchronous manager query.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest052, TestSize.Level1)
{
    sptr<UIContentServiceStubImpl> ptr = std::make_shared<UIContentServiceStubImpl>();
    auto manager = static_cast<OHOS::Ace::MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(manager, nullptr);
    EXPECT_CALL(*manager, GetCurrentAbilityLanguageInfo(_, _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<0>("zh"), SetArgReferee<1>("CN"), Return(NO_ERROR)));
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    PrepareValidUiSessionParcel(data);

    EXPECT_EQ(ptr->OnRemoteRequest(IUiContentService::GET_CURRENT_ABILITY_LANGUAGE_INFO, data, reply, option),
        NO_ERROR);
    Mock::VerifyAndClearExpectations(manager);
}

/**
 * @tc.name: UIContentStubTest053
 * @tc.desc: Test synchronous request guard rejects repeated pending requests.
 * @tc.type: FUNC
 */
HWTEST_F(UIContentStubTest, UIContentStubTest053, TestSize.Level1)
{
    std::atomic_bool pending = false;
    {
        SyncRequestGuard firstGuard(pending);
        EXPECT_TRUE(firstGuard.IsAcquired());
        SyncRequestGuard secondGuard(pending);
        EXPECT_FALSE(secondGuard.IsAcquired());
        EXPECT_TRUE(pending.load());
    }
    EXPECT_FALSE(pending.load());

    SyncRequestGuard guardAfterRelease(pending);
    EXPECT_TRUE(guardAfterRelease.IsAcquired());
}

}
