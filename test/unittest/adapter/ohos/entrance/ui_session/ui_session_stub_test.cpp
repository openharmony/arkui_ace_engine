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
}
