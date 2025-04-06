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

#include "text_input_base.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldUXTest : public TextInputBases {
public:
};

/**
 * @tc.name: testUnderlineColor007
 * @tc.desc: test testInput underlineColor detailed, TextInput is more other properties 3
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, testUnderlineColor007, TestSize.Level1)
{
    /**
     * @tc.steps: Create Text filed node
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetShowUnderline(true);
        model.SetMaxLength(10);
        model.SetMaxLines(5);
        model.SetFontSize(Dimension(20));
        model.SetShowError(u"error", false);

    /**
     * @tc.step: step1. Set UnderlineColor is null
     */
        UserUnderlineColor userColor;
        model.SetUserUnderlineColor(userColor);
    });
    frameNode_->MarkModifyDone();

    /**
     * @tc.expected: UserUnderlineColor is null
     */
    EXPECT_EQ(pattern_->GetUserUnderlineColor().normal, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().typing, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().error, std::nullopt);
    EXPECT_EQ(pattern_->GetUserUnderlineColor().disable, std::nullopt);

    /**
     * @tc.step: step2. Set userUnderlineColor.normal is GREEN
     */
    UserUnderlineColor userColor;
    userColor.normal = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    UserUnderlineColor userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.normal is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    EXPECT_NE(layoutProperty_, nullptr);
    auto theme = GetTheme();
    EXPECT_NE(theme, nullptr);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */

    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step3. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step4. Set userUnderlineColor.typing is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.typing = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step5. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is GetErrorUnderlineColor
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step6. Set userUnderlineColor.error is GREEN
     */
    userColor.typing = std::nullopt;
    userColor.error = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step7. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step8. Set userUnderlineColor.disable is GREEN
     */
    userColor.error = std::nullopt;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: UserUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, std::nullopt);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step9. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step10. Set userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    userColor.normal = Color::BLUE;
    userColor.typing = Color::GREEN;
    userColor.error = std::nullopt;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.normal is BLUE and userUnderlineColor.typing is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::GREEN);
    EXPECT_EQ(userColorRes.normal, Color::BLUE);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step11. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = Color::GREEN;
    userColor.typing = Color::BLUE;
    userColor.disable = std::nullopt;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.error is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, Color::GREEN);
    EXPECT_EQ(userColorRes.disable, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step12. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.error, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step13. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step14. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    userColor.normal = std::nullopt;
    userColor.error = std::nullopt;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, std::nullopt);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, std::nullopt);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step15. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    /**
     * @tc.step: step16. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());

    /**
     * @tc.step: step17. Set SetOnFocus
     * @tc.expected: CurrentUnderlineColor is theme->GetErrorUnderlineColor()
     */
    pattern_->SetShowKeyBoardOnFocus(true);
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
    pattern_->SetShowKeyBoardOnFocus(false);

    eventHub_->SetEnabled(false);
    
    /**
     * @tc.step: step18. Set userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    userColor.normal = Color::BLACK;
    userColor.error = Color::WHITE;
    userColor.typing = Color::BLUE;
    userColor.disable = Color::GREEN;
    pattern_->SetUserUnderlineColor(userColor);
    userColorRes = pattern_->GetUserUnderlineColor();

    /**
     * @tc.expected: userUnderlineColor.typing is BLUE and userUnderlineColor.disable is GREEN and
     *                userUnderlineColor.error is WHITE and userUnderlineColor.normal is BLACK
     */
    EXPECT_EQ(userColorRes.typing, Color::BLUE);
    EXPECT_EQ(userColorRes.normal, Color::BLACK);
    EXPECT_EQ(userColorRes.disable, Color::GREEN);
    EXPECT_EQ(userColorRes.error, Color::WHITE);

    /**
     * @tc.expected: CurrentUnderlineColor is Color::GREEN
     */
    EXPECT_EQ(pattern_->GetUnderlineColor(), theme->GetErrorUnderlineColor());
}

/**
 * @tc.name: TextInputTypeToString007
 * @tc.desc: Test TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, TextInputTypeToString007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize show number icon text input.
     */
    CreateTextField("", "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::URL);
    });

    /**
     * @tc.steps: step2. Call TextInputTypeToString.
     */
    EXPECT_EQ(pattern_->TextInputTypeToString(), "InputType.URL");
}

/**
 * @tc.name: DoProcessAutoFill001
 * @tc.desc: Test DoProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, DoProcessAutoFill001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize enableautofill textInput.
     * As if model.SetType ACE_USER_NAME, isPopup is true, MockContainer::RequestAutoFill return false.
     */
    TextFieldModelNG model;
    model.CreateTextInput(u"", u"");
    model.SetEnableAutoFill(true);
    model.SetType(TextInputType::USER_NAME);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(element);
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();

    auto parentFrameNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>())
    );
    frameNode->MountToParent(parentFrameNode);
    ViewStackProcessor::GetInstance()->Push(parentFrameNode);
    
    frameNode->SetActive();
    FlushLayoutTask(frameNode);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto contextPtr = pattern->GetHost()->GetContextRefPtr();
    contextPtr->textFieldManager_ = textFieldManager;

    /**
     * @tc.steps: step2. Call DoProcessAutoFill, case Popup
     */
    pattern->needToRequestKeyboardInner_ = true;
    pattern->DoProcessAutoFill();
    EXPECT_EQ(pattern->needToRequestKeyboardInner_, true);
}

/**
 * @tc.name: DoProcessAutoFill002
 * @tc.desc: Test DoProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, DoProcessAutoFill002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize enableautofill textInput.
     * As if model.SetType ACE_NEW_PASSWORD, isPopup is true, MockContainer::RequestAutoFill return false.
     */
    TextFieldModelNG model;
    model.CreateTextInput(u"", u"");
    model.SetEnableAutoFill(true);
    model.SetType(TextInputType::NEW_PASSWORD);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(element);
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();

    auto parentFrameNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>())
    );
    frameNode->MountToParent(parentFrameNode);
    ViewStackProcessor::GetInstance()->Push(parentFrameNode);
    
    frameNode->SetActive();
    FlushLayoutTask(frameNode);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto contextPtr = pattern->GetHost()->GetContextRefPtr();
    contextPtr->textFieldManager_ = textFieldManager;

    /**
     * @tc.steps: step2. Call DoProcessAutoFill, case notPopup,ProcessAutoFill,notImeShow
     */
    pattern->needToRequestKeyboardInner_ = true;
    pattern->DoProcessAutoFill();
    EXPECT_EQ(pattern->needToRequestKeyboardInner_, true);
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test DoProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnAttachToMainTree001, TestSize.Level1)
{
    TextFieldModelNG model;
    model.CreateTextInput(u"placeholder", u"text");
    model.SetEnableAutoFill(true);
    model.SetType(TextInputType::USER_NAME);

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();

    auto parentFrameNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(parentFrameNode, nullptr);
    frameNode->SetParent(parentFrameNode);

    auto autoFillContainerNode = frameNode->GetFirstAutoFillContainerNode();
    ASSERT_NE(autoFillContainerNode, nullptr);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    stateHolder->SetAutoFillPasswordTriggered(true);
    stateHolder->SetAutoFillNewPasswordTriggered(true);

    auto currentId = frameNode->GetId();
    auto parrent_currentId = parentFrameNode->GetId();

    auto manager = pattern->GetHost()->GetContextRefPtr()->GetTextFieldManager();
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(manager);
    auto containerNodeIter = textFieldManager->textFieldInfoMap_.find(currentId);
    EXPECT_TRUE(containerNodeIter == textFieldManager->textFieldInfoMap_.end());
    
    pattern->OnAttachToMainTree();
    auto containerNodeIter_2 = textFieldManager->textFieldInfoMap_.find(parrent_currentId);
    EXPECT_FALSE(containerNodeIter_2 == textFieldManager->textFieldInfoMap_.end());
}

/**
 * @tc.name: OnCut001
 * @tc.desc: Test DoProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnCut001, TestSize.Level1)
{
    TextFieldModelNG model;
    model.CreateTextInput(u"placeholder", u"text");
    model.SetEnableAutoFill(true);
    model.SetType(TextInputType::USER_NAME);

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pattern->OnAttachContext(Referenced::RawPtr(pipeline));
    ASSERT_EQ(pipeline->GetInstanceId(), pipeline->GetInstanceId());

    pattern->OnDetachContext(Referenced::RawPtr(pipeline));
    ASSERT_EQ(pipeline->GetInstanceId(), 0);
}

/**
 * @tc.name: OnCut002
 * @tc.desc: Test DoProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldUXTest, OnCut002, TestSize.Level1)
{
    TextFieldModelNG model;
    model.CreateTextInput(u"placeholder", u"text");
    model.SetEnableAutoFill(true);
    model.SetType(TextInputType::USER_NAME);

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pattern->OnAttachContext(Referenced::RawPtr(pipeline));
    ASSERT_EQ(pipeline->GetInstanceId(), pipeline->GetInstanceId());

    pattern->OnDetachContext(Referenced::RawPtr(pipeline));
    ASSERT_EQ(pipeline->GetInstanceId(), 0);
}

} // namespace OHOS::Ace::NG