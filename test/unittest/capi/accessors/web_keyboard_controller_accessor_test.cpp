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

#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "test/unittest/capi/stubs/mock_web_entities.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class WebKeyboardControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIWebKeyboardControllerAccessor,
    &GENERATED_ArkUIAccessors::getWebKeyboardControllerAccessor, WebKeyboardControllerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockHandler_ = Referenced::MakeRefPtr<MockWebCustomKeyboardHandler>();
        ASSERT_NE(mockHandler_, nullptr);
        peer_->handler = mockHandler_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockHandler_ = nullptr;
    }

    RefPtr<MockWebCustomKeyboardHandler> mockHandler_ = nullptr;
};

/**
 * @tc.name: insertTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebKeyboardControllerAccessorTest, insertTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->insertText, nullptr);

    std::string text = "text";

    Ark_String arkText = Converter::ArkValue<Ark_String>(text);

    EXPECT_CALL(*mockHandler_, InsertText(text)).Times(1);
    accessor_->insertText(peer_, &arkText);
}

/**
 * @tc.name: deleteForwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebKeyboardControllerAccessorTest, deleteForwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->deleteForward, nullptr);

    int32_t length = 5;
    int32_t invalid1 = -1;
    int32_t invalid2 = 0;

    Ark_Int32 arkLength= Converter::ArkValue<Ark_Int32>(length);
    Ark_Int32 arkInvalid1= Converter::ArkValue<Ark_Int32>(invalid1);
    Ark_Int32 arkInvalid2= Converter::ArkValue<Ark_Int32>(invalid2);

    EXPECT_CALL(*mockHandler_, DeleteForward(length)).Times(1);
    accessor_->deleteForward(peer_, &arkInvalid1);
    accessor_->deleteForward(peer_, &arkLength);
    accessor_->deleteForward(peer_, &arkInvalid2);
}

/**
 * @tc.name: deleteBackwardTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebKeyboardControllerAccessorTest, deleteBackwardTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->deleteBackward, nullptr);

    int32_t length = 5;
    int32_t invalid1 = -1;
    int32_t invalid2 = 0;

    Ark_Int32 arkLength= Converter::ArkValue<Ark_Int32>(length);
    Ark_Int32 arkInvalid1= Converter::ArkValue<Ark_Int32>(invalid1);
    Ark_Int32 arkInvalid2= Converter::ArkValue<Ark_Int32>(invalid2);

    EXPECT_CALL(*mockHandler_, DeleteBackward(length)).Times(1);
    accessor_->deleteBackward(peer_, &arkInvalid1);
    accessor_->deleteBackward(peer_, &arkLength);
    accessor_->deleteBackward(peer_, &arkInvalid2);
}

/**
 * @tc.name: sendFunctionKeyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebKeyboardControllerAccessorTest, sendFunctionKeyTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->sendFunctionKey, nullptr);

    int32_t key = 5;

    Ark_Int32 arkKey= Converter::ArkValue<Ark_Int32>(key);

    EXPECT_CALL(*mockHandler_, SendFunctionKey(key)).Times(1);
    accessor_->sendFunctionKey(peer_, &arkKey);
}

/**
 * @tc.name: closeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WebKeyboardControllerAccessorTest, closeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->close, nullptr);

    EXPECT_CALL(*mockHandler_, Close()).Times(3);
    accessor_->close(peer_);
    accessor_->close(peer_);
    accessor_->close(peer_);
}

} // namespace OHOS::Ace::NG
