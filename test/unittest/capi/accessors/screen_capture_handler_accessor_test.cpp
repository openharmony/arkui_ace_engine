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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ScreenCaptureHandlerAccessorTest : public AccessorTestBase<GENERATED_ArkUIScreenCaptureHandlerAccessor,
    &GENERATED_ArkUIAccessors::getScreenCaptureHandlerAccessor, ScreenCaptureHandlerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockWebScreenCaptureRequest>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockWebScreenCaptureRequest> mockHandler_ = nullptr;
};

/**
 * @tc.name: getOriginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScreenCaptureHandlerAccessorTest, getOriginTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOrigin, nullptr);

    std::string value = "value";

    EXPECT_CALL(*mockHandler_, GetOrigin()).Times(1).WillOnce(Return(value));
    EXPECT_EQ(Converter::Convert<std::string>(accessor_->getOrigin(peer_)), value);
}

/**
 * @tc.name: grantTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScreenCaptureHandlerAccessorTest, grantTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->grant, nullptr);

    Ark_ScreenCaptureConfig config;
    config.captureMode = ARK_WEB_CAPTURE_MODE_HOME_SCREEN;

    EXPECT_CALL(*mockHandler_, Grant()).Times(2);
    accessor_->grant(peer_, &config);
    accessor_->grant(peer_, nullptr);
    accessor_->grant(peer_, &config);
}

/**
 * @tc.name: denyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScreenCaptureHandlerAccessorTest, denyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->deny, nullptr);

    EXPECT_CALL(*mockHandler_, Deny()).Times(3);
    accessor_->deny(peer_);
    accessor_->deny(peer_);
    accessor_->deny(peer_);
}

} // namespace OHOS::Ace::NG
