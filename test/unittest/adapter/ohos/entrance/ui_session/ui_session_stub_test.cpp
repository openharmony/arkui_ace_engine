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

#define private public
#define protected public

#include "interfaces/inner_api/ui_session/ui_content_stub_impl.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "accesstoken_kit.h"

#include <memory>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class UISessionStubTest : public testing::Test {};

/**
 * @tc.name: UISessionStubTest001
 * @tc.desc: Test UI_CONTENT_SERVICE_GET_TREE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest001, TestSize.Level1)
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
 * @tc.name: UISessionStubTest002
 * @tc.desc: Test UI_CONTENT_CONNECT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest002, TestSize.Level1)
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
 * @tc.name: UISessionStubTest003
 * @tc.desc: Test REGISTER_CLICK_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest003, TestSize.Level1)
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
 * @tc.name: UISessionStubTest004
 * @tc.desc: Test REGISTER_SEARCH_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest004, TestSize.Level1)
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
 * @tc.name: UISessionStubTest005
 * @tc.desc: Test REGISTER_TEXT_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest005, TestSize.Level1)
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
 * @tc.name: UISessionStubTest006
 * @tc.desc: Test REGISTER_ROUTER_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest006, TestSize.Level1)
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
 * @tc.name: UISessionStubTest007
 * @tc.desc: Test REGISTER_COMPONENT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest007, TestSize.Level1)
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
 * @tc.name: UISessionStubTest008
 * @tc.desc: Test REGISTER_WEB_UNFOCUS_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest008, TestSize.Level1)
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
 * @tc.name: UISessionStubTest009
 * @tc.desc: Test REGISTER_SCROLL_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest009, TestSize.Level1)
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
 * @tc.name: UISessionStubTest010
 * @tc.desc: Test REGISTER_LIFE_CYCLE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest010, TestSize.Level1)
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
 * @tc.name: UISessionStubTest011
 * @tc.desc: Test REGISTER_SELECT_TEXT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest011, TestSize.Level1)
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
 * @tc.name: UISessionStubTest012
 * @tc.desc: Test SENDCOMMAND_ASYNC_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest012, TestSize.Level1)
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
 * @tc.name: UISessionStubTest013
 * @tc.desc: Test SENDCOMMAND_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest013, TestSize.Level1)
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
 * @tc.name: UISessionStubTest014
 * @tc.desc: Test UNREGISTER_CLICK_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest014, TestSize.Level1)
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
 * @tc.name: UISessionStubTest015
 * @tc.desc: Test UNREGISTER_SEARCH_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest015, TestSize.Level1)
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
 * @tc.name: UISessionStubTest016
 * @tc.desc: Test UNREGISTER_TEXT_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest016, TestSize.Level1)
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
 * @tc.name: UISessionStubTest017
 * @tc.desc: Test UNREGISTER_ROUTER_CHANGE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest017, TestSize.Level1)
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
 * @tc.name: UISessionStubTest018
 * @tc.desc: Test UNREGISTER_COMPONENT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest018, TestSize.Level1)
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
 * @tc.name: UISessionStubTest019
 * @tc.desc: Test UNREGISTER_WEB_UNFOCUS_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest019, TestSize.Level1)
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
 * @tc.name: UISessionStubTest020
 * @tc.desc: Test UNREGISTER_SCROLL_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest020, TestSize.Level1)
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
 * @tc.name: UISessionStubTest021
 * @tc.desc: Test UNREGISTER_LIFE_CYCLE_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest021, TestSize.Level1)
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
 * @tc.name: UISessionStubTest022
 * @tc.desc: Test UNREGISTER_SELECT_TEXT_EVENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest022, TestSize.Level1)
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
 * @tc.name: UISessionStubTest023
 * @tc.desc: Test RESET_ALL_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest023, TestSize.Level1)
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
 * @tc.name: UISessionStubTest024
 * @tc.desc: Test RESET_TEXT_BY_ID
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest024, TestSize.Level1)
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
 * @tc.name: UISessionStubTest025
 * @tc.desc: Test GET_WEB_VIEW_LANGUAGE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest025, TestSize.Level1)
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
 * @tc.name: UISessionStubTest026
 * @tc.desc: Test GET_WEB_TRANSLATE_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest026, TestSize.Level1)
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
 * @tc.name: UISessionStubTest027
 * @tc.desc: Test CONTINUE_GET_WEB_TEXT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest027, TestSize.Level1)
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
 * @tc.name: UISessionStubTest028
 * @tc.desc: Test SEND_TRANSLATE_RESULT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest028, TestSize.Level1)
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
 * @tc.name: UISessionStubTest029
 * @tc.desc: Test END_WEB_TRANSLATE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest029, TestSize.Level1)
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
 * @tc.name: UISessionStubTest030
 * @tc.desc: Test SEND_TRANSLATE_RESULT_STR
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest030, TestSize.Level1)
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
 * @tc.name: UISessionStubTest031
 * @tc.desc: Test GET_CURRENT_PAGE_NAME
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest031, TestSize.Level1)
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
 * @tc.name: UISessionStubTest032
 * @tc.desc: Test GET_CURRENT_SHOWING_IMAGE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest032, TestSize.Level1)
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
 * @tc.name: UISessionStubTest033
 * @tc.desc: Test GET_VISIBLE_TREE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest033, TestSize.Level1)
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
 * @tc.name: UISessionStubTest034
 * @tc.desc: Test SEND_COMMAND
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest034, TestSize.Level1)
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
 * @tc.name: UISessionStubTest035
 * @tc.desc: Test EXE_APP_AI_FUNCTION
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest035, TestSize.Level1)
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
 * @tc.name: UISessionStubTest036
 * @tc.desc: Test GET_SPECIFIED_CONTENT_OFFSETS
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest036, TestSize.Level1)
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
 * @tc.name: UISessionStubTest037
 * @tc.desc: Test HIGHLIGHT_SPECIFIED_CONTENT
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest037, TestSize.Level1)
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
 * @tc.name: UISessionStubTest038
 * @tc.desc: Test GET_MULTI_IMAGES_BY_ID
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest038, TestSize.Level1)
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
 * @tc.name: UISessionStubTest039
 * @tc.desc: Test REGISTER_CONTENT_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest039, TestSize.Level1)
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
 * @tc.name: UISessionStubTest040
 * @tc.desc: Test UNREGISTER_CONTENT_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest040, TestSize.Level1)
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
 * @tc.name: UISessionStubTest041
 * @tc.desc: Test GET_HIT_TEST_NODE_INFO_FOR_TOUCH
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest041, TestSize.Level1)
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
 * @tc.name: UISessionStubTest042
 * @tc.desc: Test REQUEST_STATE_MGMT_INFO
 * @tc.type: FUNC
 */
HWTEST_F(UISessionStubTest, UISessionStubTest042, TestSize.Level1)
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
}
