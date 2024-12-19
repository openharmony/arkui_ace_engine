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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class HttpAuthHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUIHttpAuthHandlerAccessor,
    &GENERATED_ArkUIAccessors::getHttpAuthHandlerAccessor, HttpAuthHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockAuthResult>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockAuthResult> mockHandler_ = nullptr;
};

/**
 * @tc.name: isHttpAuthInfoSavedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HttpAuthHandlerAccessorTest, isHttpAuthInfoSavedTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isHttpAuthInfoSaved, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    EXPECT_CALL(*mockHandler_, IsHttpAuthInfoSaved()).Times(1).WillOnce(Return(true));
    EXPECT_EQ(arkTrue, accessor_->isHttpAuthInfoSaved(peer_));

    EXPECT_CALL(*mockHandler_, IsHttpAuthInfoSaved()).Times(1).WillOnce(Return(false));
    EXPECT_EQ(arkFalse, accessor_->isHttpAuthInfoSaved(peer_));
}

/**
 * @tc.name: confirmTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HttpAuthHandlerAccessorTest, confirmTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->confirm, nullptr);

    Ark_Boolean arkTrue = Converter::ArkValue<Ark_Boolean>(true);
    Ark_Boolean arkFalse = Converter::ArkValue<Ark_Boolean>(false);

    std::string userName1 = "userName1";
    std::string pwd1 = "pwd1";

    Ark_String arkUserName1 = Converter::ArkValue<Ark_String>(userName1);
    Ark_String arkPwd1 = Converter::ArkValue<Ark_String>(pwd1);

    EXPECT_CALL(*mockHandler_, Confirm(userName1, pwd1)).Times(1).WillOnce(Return(true));
    EXPECT_EQ(arkTrue, accessor_->confirm(peer_, &arkUserName1, &arkPwd1));

    std::string userName2 = "userName2";
    std::string pwd2 = "pwd2";

    Ark_String arkUserName2 = Converter::ArkValue<Ark_String>(userName2);
    Ark_String arkPwd2 = Converter::ArkValue<Ark_String>(pwd2);

    EXPECT_CALL(*mockHandler_, Confirm(userName2, pwd2)).Times(1).WillOnce(Return(false));
    EXPECT_EQ(arkFalse, accessor_->confirm(peer_, &arkUserName2, &arkPwd2));
}

/**
 * @tc.name: cancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HttpAuthHandlerAccessorTest, cancelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->cancel, nullptr);

    EXPECT_CALL(*mockHandler_, Cancel()).Times(3);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
}

} // namespace OHOS::Ace::NG
