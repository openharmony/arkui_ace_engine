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
#include "core/interfaces/native/implementation/text_edit_controller_ex_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
constexpr int32_t OFFSET = 1;

class MockTextEditControllerExPeer : public TextEditControllerExPeer {
public:
    MockTextEditControllerExPeer() = default;
    ~MockTextEditControllerExPeer() override = default;
    MOCK_METHOD(bool, IsEditing, ());
    MOCK_METHOD(int32_t, GetCaretOffset, ());
    MOCK_METHOD(PreviewTextInfo, GetPreviewText, ());
    MOCK_METHOD(void, StopEditing, ());
    MOCK_METHOD(bool, SetCaretOffset, (int32_t));
    // these methods are tested in TextBaseControllerAccessor test
    // just added to avoid abstract class allocation
    MOCK_METHOD(void, CloseSelectionMenu, ());
    MOCK_METHOD(OHOS::Ace::WeakPtr<OHOS::Ace::NG::LayoutInfoInterface>, GetLayoutInfoInterface, ());
    MOCK_METHOD(void, SetSelection, (int32_t selectionStart, int32_t selectionEnd,
        const std::optional<OHOS::Ace::SelectionOptions>& options, bool isForward));
};
} // namespace

class TextEditControllerExAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUITextEditControllerExAccessor,
    &GENERATED_ArkUIAccessors::getTextEditControllerExAccessor, MockTextEditControllerExPeer> {
public:
    void* CreatePeerInstance() override
    {
        return new MockTextEditControllerExPeer();
    }
};

/**
 * @tc.name: IsEditingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextEditControllerExAccessorTest, IsEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEditing, nullptr);
    EXPECT_CALL(*peer_, IsEditing()).Times(1).WillOnce(Return(true));
    auto isEditing = accessor_->isEditing(peer_);
    auto checkValueOpt = Converter::OptConvert<bool>(isEditing);
    ASSERT_TRUE(checkValueOpt.has_value());
    EXPECT_TRUE(*checkValueOpt);
}

/**
 * @tc.name: GetCaretOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextEditControllerExAccessorTest, GetCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);
    EXPECT_CALL(*peer_, GetCaretOffset()).Times(1).WillOnce(Return(OFFSET));
    auto caretOffset = accessor_->getCaretOffset(peer_);
    auto checkValue = Converter::OptConvert<int32_t>(caretOffset);
    EXPECT_EQ(checkValue, OFFSET);
}

/**
 * @tc.name: SetCaretOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextEditControllerExAccessorTest, SetCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setCaretOffset, nullptr);
    auto offset = Converter::ArkValue<Ark_Number>(OFFSET);
    EXPECT_CALL(*peer_, SetCaretOffset(OFFSET)).Times(1).WillOnce(Return(true));
    auto caretOffset = accessor_->setCaretOffset(peer_, &offset);
    auto checkValueOpt = Converter::OptConvert<bool>(caretOffset);
    ASSERT_TRUE(checkValueOpt.has_value());
    EXPECT_TRUE(*checkValueOpt);
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextEditControllerExAccessorTest, StopEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopEditing, nullptr);
    EXPECT_CALL(*peer_, StopEditing()).Times(1);
    accessor_->stopEditing(peer_);
}

/**
 * @tc.name: GetPreviewTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextEditControllerExAccessorTest, GetPreviewTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviewText, nullptr);
    PreviewTextInfo previewText = {.offset = OFFSET, .value = u"info"};
    EXPECT_CALL(*peer_, GetPreviewText()).Times(1).WillOnce(Return(previewText));
    auto checkValue = accessor_->getPreviewText(peer_);
#ifdef WRONG_GEN
    auto checkValueOpt = Converter::GetOpt(previewTextOpt);
    ASSERT_TRUE(checkValueOpt.has_value());
    auto checkValue = checkValueOpt.value();
#endif
    EXPECT_EQ(Converter::Convert<std::string>(checkValue.value), "info");
    EXPECT_EQ(Converter::Convert<int32_t>(checkValue.offset), OFFSET);
}
} // namespace OHOS::Ace::NG
