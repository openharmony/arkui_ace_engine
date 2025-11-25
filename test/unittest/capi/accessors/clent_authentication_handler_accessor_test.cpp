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

#include "core/interfaces/native/implementation/client_authentication_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ClientAuthenticationHandlerAccessorTest : public AccessorTestBase<
    GENERATED_ArkUIClientAuthenticationHandlerAccessor,
    &GENERATED_ArkUIAccessors::getClientAuthenticationHandlerAccessor,
    ClientAuthenticationHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockSslSelectCertResult>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockSslSelectCertResult> mockHandler_ = nullptr;
};

/**
 * @tc.name: confirm0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClientAuthenticationHandlerAccessorTest, confirm0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->confirm0, nullptr);

    std::string priKeyFile = "priKeyFile";
    std::string certChainFile = "certChainFile";

    Ark_String arkPriKeyFile = Converter::ArkValue<Ark_String>(priKeyFile);
    Ark_String arkCertChainFile = Converter::ArkValue<Ark_String>(certChainFile);

    EXPECT_CALL(*mockHandler_, HandleConfirm(priKeyFile, certChainFile)).Times(1);
    accessor_->confirm0(peer_, &arkPriKeyFile, &arkCertChainFile);
}

/**
 * @tc.name: confirm1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClientAuthenticationHandlerAccessorTest, confirm1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->confirm1, nullptr);

    std::string priKeyFile = "authUri";
    std::string certChainFile;

    Ark_String authUri = Converter::ArkValue<Ark_String>(priKeyFile);

    EXPECT_CALL(*mockHandler_, HandleConfirm(priKeyFile, certChainFile)).Times(1);
    accessor_->confirm1(peer_, &authUri);
}

/**
 * @tc.name: cancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClientAuthenticationHandlerAccessorTest, cancelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->cancel, nullptr);

    EXPECT_CALL(*mockHandler_, HandleCancel()).Times(3);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
}

/**
 * @tc.name: ignoreTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ClientAuthenticationHandlerAccessorTest, ignoreTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->ignore, nullptr);

    EXPECT_CALL(*mockHandler_, HandleIgnore()).Times(3);
    accessor_->ignore(peer_);
    accessor_->ignore(peer_);
    accessor_->ignore(peer_);
}

} // namespace OHOS::Ace::NG