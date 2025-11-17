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

#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class JsResultAccessorTest : public AccessorTestBase<GENERATED_ArkUIJsResultAccessor,
    &GENERATED_ArkUIAccessors::getJsResultAccessor, JsResultPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockResult_ = Referenced::MakeRefPtr<MockResult>();
        ASSERT_NE(mockResult_, nullptr);
        peer_->result = mockResult_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockResult_ = nullptr;
    }

    RefPtr<MockResult> mockResult_ = nullptr;
};

/**
 * @tc.name: handlePromptConfirmTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(JsResultAccessorTest, handlePromptConfirmTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->handlePromptConfirm, nullptr);

    std::string message = "message";

    Ark_String arkMessage = Converter::ArkValue<Ark_String>(message);

    EXPECT_CALL(*mockResult_, Confirm(message)).Times(1);
    accessor_->handlePromptConfirm(peer_, &arkMessage);
}

/**
 * @tc.name: handleConfirmTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(JsResultAccessorTest, handleConfirmTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->handleConfirm, nullptr);

    EXPECT_CALL(*mockResult_, Confirm()).Times(3);
    accessor_->handleConfirm(peer_);
    accessor_->handleConfirm(peer_);
    accessor_->handleConfirm(peer_);
}

/**
 * @tc.name: handleCancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(JsResultAccessorTest, handleCancelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->handleConfirm, nullptr);

    EXPECT_CALL(*mockResult_, Cancel()).Times(3);
    accessor_->handleCancel(peer_);
    accessor_->handleCancel(peer_);
    accessor_->handleCancel(peer_);
}

} // namespace OHOS::Ace::NG
