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
#include "core/interfaces/native/implementation/text_content_controller_base_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
constexpr int32_t LINES_NUM = 1;
class MockTextContentControllerBase : public TextFieldControllerBase {
public:
    MockTextContentControllerBase() = default;
    ~MockTextContentControllerBase() override = default;
    MOCK_METHOD(int32_t, GetTextContentLinesNum, (), (override));
    MOCK_METHOD(Rect, GetTextContentRect, (), (override));
    MOCK_METHOD(NG::OffsetF, GetCaretPosition, (), (override));
};
} // namespace

class TextContentControllerBaseAccessorTest :
    public AccessorTestBase<GENERATED_ArkUITextContentControllerBaseAccessor,
    &GENERATED_ArkUIAccessors::getTextContentControllerBaseAccessor, TextContentControllerBasePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextContentControllerBase_ = new MockTextContentControllerBase();
        mockTextContentControllerBaseKeeper_ = AceType::Claim(mockTextContentControllerBase_);
        ASSERT_NE(mockTextContentControllerBaseKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->controller_ = mockTextContentControllerBaseKeeper_;
        ASSERT_NE(mockTextContentControllerBase_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockTextContentControllerBaseKeeper_ = nullptr;
        mockTextContentControllerBase_ = nullptr;
    }

    MockTextContentControllerBase *mockTextContentControllerBase_ = nullptr;
    RefPtr<MockTextContentControllerBase> mockTextContentControllerBaseKeeper_ = nullptr;
};

/**
 * @tc.name: GetTextContentLinesNumTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextContentControllerBaseAccessorTest, GetTextContentLinesNumTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTextContentLineCount, nullptr);
    EXPECT_CALL(*mockTextContentControllerBase_, GetTextContentLinesNum()).Times(1).WillOnce(Return(LINES_NUM));
    auto checkValue = accessor_->getTextContentLineCount(peer_);
    EXPECT_EQ(checkValue, LINES_NUM);
}

/**
 * @tc.name: GetCaretOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextContentControllerBaseAccessorTest, DISABLED_GetCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);
    EXPECT_CALL(*mockTextContentControllerBase_, GetCaretPosition()).Times(1).WillOnce(Return(NG::OffsetF(1, 1)));
    auto checkValue = accessor_->getCaretOffset(peer_);
    EXPECT_EQ(checkValue, nullptr); // fix after updating return value
}

/**
 * @tc.name: GetTextContentRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextContentControllerBaseAccessorTest, DISABLED_GetTextContentRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getTextContentRect, nullptr);
    EXPECT_CALL(*mockTextContentControllerBase_, GetTextContentRect()).Times(1).WillOnce(Return(Rect(0, 0, 1, 1)));
    auto checkValue = accessor_->getTextContentRect(peer_);
    EXPECT_EQ(checkValue, nullptr); // fix after updating return value
}
} // namespace OHOS::Ace::NG
