/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/submit_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class SubmitEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUISubmitEventAccessor,
        &GENERATED_ArkUIAccessors::getSubmitEventAccessor, SubmitEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_unique<TextFieldCommonEvent>();
        peer_->SetEventInfo(eventInfo_.get());
    }

    std::unique_ptr<TextFieldCommonEvent> eventInfo_;
};

/**
 * @tc.name: SetTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SubmitEventAccessorTest, SetTextTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    std::u16string text = info->GetText();
    EXPECT_TRUE(text.empty());
    const std::u16string TEST_VALUE(u"string text");
    Converter::ConvContext ctx;
    Ark_String value = Converter::ArkValue<Ark_String>(TEST_VALUE, &ctx);
    accessor_->setText(peer_, &value);
    text = info->GetText();
    EXPECT_FALSE(text.empty());
    EXPECT_EQ(text, TEST_VALUE);
}

/**
 * @tc.name: GetTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SubmitEventAccessorTest, GetTextTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    const std::u16string TEST_VALUE(u"string text");
    info->SetText(TEST_VALUE);
    auto arkText = accessor_->getText(peer_);
    auto text = Converter::Convert<std::u16string>(arkText);
    EXPECT_FALSE(text.empty());
    EXPECT_EQ(text, TEST_VALUE);
}

/**
 * @tc.name: KeepEditableStateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SubmitEventAccessorTest, KeepEditableStateTest, TestSize.Level1)
{
    auto info = peer_->GetEventInfo();
    ASSERT_NE(info, nullptr);
    auto isKeepEditable = info->IsKeepEditable();
    EXPECT_FALSE(isKeepEditable);
    accessor_->keepEditableState(peer_);
    isKeepEditable = info->IsKeepEditable();
    EXPECT_TRUE(isKeepEditable);
}

} // namespace OHOS::Ace::NG