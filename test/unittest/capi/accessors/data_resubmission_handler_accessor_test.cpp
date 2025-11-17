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

#include "core/interfaces/native/implementation/data_resubmission_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class DataResubmissionHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUIDataResubmissionHandlerAccessor,
    &GENERATED_ArkUIAccessors::getDataResubmissionHandlerAccessor, DataResubmissionHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockDataResubmitted>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockDataResubmitted> mockHandler_ = nullptr;
};

/**
 * @tc.name: resendTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataResubmissionHandlerAccessorTest, resendTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->cancel, nullptr);

    EXPECT_CALL(*mockHandler_, Resend()).Times(3);
    accessor_->resend(peer_);
    accessor_->resend(peer_);
    accessor_->resend(peer_);
}

/**
 * @tc.name: cancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataResubmissionHandlerAccessorTest, cancelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->cancel, nullptr);

    EXPECT_CALL(*mockHandler_, Cancel()).Times(3);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
    accessor_->cancel(peer_);
}

} // namespace OHOS::Ace::NG