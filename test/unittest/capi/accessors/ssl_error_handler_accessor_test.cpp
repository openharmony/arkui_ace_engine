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

#include "core/interfaces/native/implementation/ssl_error_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class SslErrorHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUISslErrorHandlerAccessor,
    &GENERATED_ArkUIAccessors::getSslErrorHandlerAccessor, SslErrorHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockSslErrorResult>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockSslErrorResult> mockHandler_ = nullptr;
};

/**
 * @tc.name: handleCancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SslErrorHandlerAccessorTest, handleCancelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->handleCancel, nullptr);

    EXPECT_CALL(*mockHandler_, HandleCancel()).Times(3);
    accessor_->handleCancel(peer_);
    accessor_->handleCancel(peer_);
    accessor_->handleCancel(peer_);
}

/**
 * @tc.name: handleConfirmTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SslErrorHandlerAccessorTest, handleConfirmTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->handleConfirm, nullptr);

    EXPECT_CALL(*mockHandler_, HandleConfirm()).Times(3);
    accessor_->handleConfirm(peer_);
    accessor_->handleConfirm(peer_);
    accessor_->handleConfirm(peer_);
}

} // namespace OHOS::Ace::NG