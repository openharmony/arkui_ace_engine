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

    int32_t GetTextContentLinesNum() override
    {
        return LINES_NUM;
    }

    Rect GetTextContentRect() override
    {
        return Rect(0, 0, 1, 1);
    }

    NG::OffsetF GetCaretPosition() override
    {
        return NG::OffsetF(1, 1);
    }
};
} // namespace

class TextContentControllerBaseAccessorTest : public AccessorTestBase<GENERATED_ArkUITextContentControllerBaseAccessor,
    &GENERATED_ArkUIAccessors::getTextContentControllerBaseAccessor, TextContentControllerBasePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockTextContentControllerBase_ = new MockTextContentControllerBase();
        mockTextContentControllerBaseKeeper_ = AceType::Claim(mockTextContentControllerBase_);
        ASSERT_NE(mockTextContentControllerBaseKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->handler = mockTextContentControllerBaseKeeper_;
        ASSERT_NE(mockTextContentControllerBase_, nullptr);
    }

    void TearDown() override
    {
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
    auto checkValue = accessor_->getTextContentRect(peer_);
    EXPECT_EQ(checkValue, nullptr); // fix after updating return value
}

} // namespace OHOS::Ace::NG
