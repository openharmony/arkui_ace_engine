/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "gtest/gtest.h"

#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string TEXT_CONTENT = "text";
constexpr int32_t TEXT_ERROR = -1;
constexpr int32_t TEXT_SIZE = 10;
} // namespace
class TextAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitTextTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPattern> textPattern_;
    RefPtr<TextAccessibilityProperty> textAccessibilityProperty_;
};
void TextAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitTextTestNg());
}

void TextAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    textPattern_ = nullptr;
    textAccessibilityProperty_ = nullptr;
}

bool TextAccessibilityPropertyTestNg::InitTextTestNg()
{
    TextModelNG textModel;
    textModel.Create(TEXT_CONTENT);

    frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    CHECK_NULL_RETURN(frameNode_, false);

    textPattern_ = frameNode_->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern_, false);

    textAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextAccessibilityProperty>();
    CHECK_NULL_RETURN(textAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: TextAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextAccessibilityPropertyTestNg, TextAccessibilityPropertyGetText001, TestSize.Level1)
{
    EXPECT_EQ(textAccessibilityProperty_->GetText(), EMPTY_TEXT);

    textPattern_->textForDisplay_ = TEXT_CONTENT;
    EXPECT_EQ(textAccessibilityProperty_->GetText(), TEXT_CONTENT);
}

/**
 * @tc.name: TextAccessibilityPropertyIsSelected001
 * @tc.desc: Test IsSelected of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextAccessibilityPropertyTestNg, TextAccessibilityPropertyIsSelected001, TestSize.Level1)
{
    EXPECT_FALSE(textAccessibilityProperty_->IsSelected());

    textPattern_->textSelector_.Update(0, TEXT_SIZE);
    EXPECT_TRUE(textAccessibilityProperty_->IsSelected());
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionStart001
 * @tc.desc: Test GetTextSelectionStart of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextAccessibilityPropertyTestNg, TextAccessibilityPropertyGetTextSelectionStart001, TestSize.Level1)
{
    EXPECT_EQ(textAccessibilityProperty_->GetTextSelectionStart(), TEXT_ERROR);

    textPattern_->textSelector_.Update(0, TEXT_SIZE);
    EXPECT_EQ(textAccessibilityProperty_->GetTextSelectionStart(), 0);
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionEnd001
 * @tc.desc: Test GetTextSelectionEnd of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextAccessibilityPropertyTestNg, TextAccessibilityPropertyGetTextSelectionEnd001, TestSize.Level1)
{
    EXPECT_EQ(textAccessibilityProperty_->GetTextSelectionEnd(), TEXT_ERROR);

    textPattern_->textSelector_.Update(0, TEXT_SIZE);
    EXPECT_EQ(textAccessibilityProperty_->GetTextSelectionEnd(), TEXT_SIZE);
}

/**
 * @tc.name: TextAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextAccessibilityPropertyTestNg, TextAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    auto gestureEventHub = frameNode_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->longPressEventActuator_ =
        AceType::MakeRefPtr<LongPressEventActuator>(WeakPtr<GestureEventHub>(gestureEventHub));
    gestureEventHub->CheckClickActuator();

    auto focusHub = frameNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = true;
    focusHub->focusable_ = true;
    focusHub->focusType_ = FocusType::NODE;

    auto textLayoutProperty = frameNode_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);

    textAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = textAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_FOCUS);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLICK);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_LONG_CLICK);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_COPY);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SET_SELECTION);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_NEXT_AT_MOVEMENT_GRANULARITY);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}
} // namespace OHOS::Ace::NG
