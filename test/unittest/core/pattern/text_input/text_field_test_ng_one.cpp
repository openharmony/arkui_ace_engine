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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldTestNGOne : public TextInputBases {
public:
};

/**
 * @tc.name: TextPattern001
 * @tc.desc: Test TextPattern UpdateCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern UpdateCaretRect
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UpdateCaretRect(true);
}

/**
 * @tc.name: TextPattern002
 * @tc.desc: Test TextPattern CheckSelectAreaVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CheckSelectAreaVisible();
}

/**
 * @tc.name: TextPattern003
 * @tc.desc: Test TextPattern OnIsFocusActiveUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: TextPattern004
 * @tc.desc: Test TextPattern HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleExtendAction(ACTION_AUTOFILL);
}

/**
 * @tc.name: TextPattern005
 * @tc.desc: Test TextPattern HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isCustomKeyboardAttached_ = true;
    auto func1 = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto func2 = [] {};
    pattern->customKeyboard_ = AceType::Claim<UINode>(func1);
    pattern->customKeyboardBuilder_ = func2;
    pattern->HandleBlurEvent();
}

/**
 * @tc.name: TextPattern006
 * @tc.desc: Test TextPattern HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    textFieldNode->SetParent(frameNode_);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->CanUndo(), false);
    EXPECT_EQ(pattern->CanRedo(), false);
    pattern->HandleOnUndoAction();
    TextEditingValueNG record {
        .text = pattern->contentController_->GetTextUtf16Value(),
        .caretPosition = pattern->selectController_->GetCaretIndex(),
    };
    pattern->operationRecords_.emplace_back(record);
    pattern->HandleOnUndoAction();
    for (int32_t i = 0; i < 30; i++) {
        TextEditingValueNG value;
        value.text = u"123";
        pattern->redoOperationRecords_.push_back(value);
    }
    pattern->HandleOnUndoAction();
}

/**
 * @tc.name: TextPattern007
 * @tc.desc: Test TextPattern HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleOnRedoAction();
    TextEditingValueNG record {
        .text = pattern->contentController_->GetTextUtf16Value(),
        .caretPosition = pattern->selectController_->GetCaretIndex(),
    };
    pattern->operationRecords_.emplace_back(record);
    auto textEditingValue = pattern->operationRecords_.back();
    pattern->redoOperationRecords_.push_back(textEditingValue);
    pattern->HandleOnRedoAction();
}

/**
 * @tc.name: TextPattern008
 * @tc.desc: Test TextPattern CheckAutoFillType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CheckAutoFillType(AceAutoFillType::ACE_UNSPECIFIED, true);
}

/**
 * @tc.name: TextPattern009
 * @tc.desc: Test TextPattern InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragStatus_ = DragStatus::ON_DROP;
    pattern->InitDragDropCallBack();
}

/**
 * @tc.name: TextPattern010
 * @tc.desc: Test TextPattern InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    textFieldNode->SetParent(frameNode_);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = false;
    pattern->InitDragDropCallBack();
}

/**
 * @tc.name: TextPattern011
 * @tc.desc: Test TextPattern InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    textFieldNode->SetParent(frameNode_);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = true;
    pattern->InitDragDropCallBack();
}

/**
 * @tc.name: TextPattern012
 * @tc.desc: Test TextPattern HandleDoubleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    info.deviceType_ = SourceType::MOUSE;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->HandleDoubleClickEvent(info);
    pattern->showSelect_ = false;
    pattern->hasPreviewText_ = false;
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleDoubleClickEvent(info);
    info.deviceType_ = SourceType::NONE;
    pattern->HandleDoubleClickEvent(info);
}

/**
 * @tc.name: TextPattern013
 * @tc.desc: Test TextPattern GetAutoFillTriggeredStateByType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_USER_NAME);
    pattern->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_NEW_PASSWORD);
    pattern->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_PASSWORD);
    pattern->GetAutoFillTriggeredStateByType(AceAutoFillType::ACE_FULL_STREET_ADDRESS);
}

/**
 * @tc.name: TextPattern014
 * @tc.desc: Test TextPattern SetAutoFillTriggeredStateByType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_USER_NAME);
    pattern->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_PASSWORD);
    pattern->SetAutoFillTriggeredStateByType(AceAutoFillType::ACE_NEW_PASSWORD);
}

/**
 * @tc.name: TextPattern015
 * @tc.desc: Test TextPattern HandleTripleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->HandleTripleClickEvent(info);
    pattern->hasPreviewText_ = false;
    pattern->showSelect_ = false;
    info.deviceType_ = SourceType::MOUSE;
    pattern->HandleTripleClickEvent(info);
}

/**
 * @tc.name: TextPattern016
 * @tc.desc: Test TextPattern HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->mouseStatus_ = MouseStatus::MOVE;
    pattern->HandleSingleClickEvent(info);

    layoutProperty_->UpdateMaxLines(100000);
    pattern->contentRect_ = RectF(0.0f, 0.0f, 150.0f, 200.0f);
    pattern->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    auto caretOffset = pattern->GetCaretClickLocalOffset(Offset(20.0f, 120.0f));
    EXPECT_EQ(caretOffset.GetX(), 150.0f);
    EXPECT_EQ(caretOffset.GetY(), 75.0f);
    pattern->textRect_ = RectF(0.0f, 0.0f, 100.0f, 400.0f);
    caretOffset = pattern->GetCaretClickLocalOffset(Offset(20.0f, 250.0f));
    EXPECT_EQ(caretOffset.GetX(), 150.0f);
    EXPECT_EQ(caretOffset.GetY(), 175.0f);
}

/**
 * @tc.name: TextPattern017
 * @tc.desc: Test TextPattern StartTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isTransparent_ = true;
    pattern->StartTwinkling();
}

/**
 * @tc.name: TextPattern018
 * @tc.desc: Test TextPattern FilterInitializeText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    textFieldNode->SetParent(frameNode_);
    ASSERT_NE(textFieldNode, nullptr);

    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->deleteBackwardOperations_.emplace(10);
    pattern->FilterInitializeText();
}

/**
 * @tc.name: TextPattern019
 * @tc.desc: Test TextPattern HandleRightMouseReleaseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    MouseInfo info1;
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    pattern1->hasPreviewText_ = true;
    pattern1->HandleRightMouseReleaseEvent(info1);

    MouseInfo info2;
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->hasPreviewText_ = false;
    pattern2->HandleRightMouseReleaseEvent(info2);

    MouseInfo info3;
    auto textFieldNode3 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern3 = textFieldNode3->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern3, nullptr);
    pattern3->hasPreviewText_ = false;
    pattern3->GetFocusHub()->currentFocus_ = true;
    pattern3->HandleRightMouseReleaseEvent(info3);
}

/**
 * @tc.name: TextPattern020
 * @tc.desc: Test TextPattern HandleLeftMouseMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    MouseInfo info1;
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    pattern1->leftMouseCanMove_ = true;
    pattern1->blockPress_ = true;
    pattern1->HandleLeftMouseMoveEvent(info1);

    MouseInfo info2;
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->leftMouseCanMove_ = true;
    pattern2->blockPress_ = false;
    pattern2->HandleLeftMouseMoveEvent(info2);

    MouseInfo info3;
    auto textFieldNode3 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern3 = textFieldNode3->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern3, nullptr);
    pattern3->leftMouseCanMove_ = true;
    pattern3->blockPress_ = false;
    pattern3->GetFocusHub()->currentFocus_ = true;
    pattern3->HandleLeftMouseMoveEvent(info3);

    MouseInfo info4;
    auto textFieldNode4 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern4 = textFieldNode4->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern4, nullptr);
    pattern4->leftMouseCanMove_ = true;
    pattern4->blockPress_ = false;
    pattern4->GetFocusHub()->currentFocus_ = false;
    pattern4->HandleLeftMouseMoveEvent(info4);
}

/**
 * @tc.name: TextPattern021
 * @tc.desc: Test TextPattern HandleLeftMouseReleaseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    MouseInfo info1;
    auto textFieldNode1 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern1 = textFieldNode1->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern1, nullptr);
    pattern1->blockPress_ = true;
    pattern1->mouseStatus_ = MouseStatus::PRESSED;
    pattern1->HandleLeftMouseReleaseEvent(info1);

    MouseInfo info2;
    auto textFieldNode2 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    RefPtr<TextFieldPattern> pattern2 = textFieldNode2->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->blockPress_ = true;
    pattern2->mouseStatus_ = MouseStatus::NONE;
    pattern2->HandleLeftMouseReleaseEvent(info2);
}

/**
 * @tc.name: TextPattern022
 * @tc.desc: Test TextPattern RequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showKeyBoardOnFocus_ = true;
    pattern->RequestKeyboard(false, true, true);
    pattern->showKeyBoardOnFocus_ = false;
    auto func1 = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern->customKeyboard_ = AceType::Claim<UINode>(func1);
    pattern->RequestKeyboard(false, true, true);
}

/**
 * @tc.name: TextPattern023
 * @tc.desc: Test TextPattern CloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto func1 = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ;
    auto func2 = [] {};
    pattern->customKeyboard_ = AceType::Claim<UINode>(func1);
    pattern->customKeyboardBuilder_ = func2;
    pattern->showKeyBoardOnFocus_ = true;
    pattern->CloseKeyboard(true, false);
    pattern->isCustomKeyboardAttached_ = true;
    pattern->CloseKeyboard(true, false);
}

/**
 * @tc.name: TextPattern024
 * @tc.desc: Test TextPattern AutoFillValueChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFillRequestFinish_ = true;
    pattern->AutoFillValueChanged();
}

/**
 * @tc.name: TextPattern025
 * @tc.desc: Test TextPattern HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    pattern->HandleLongPress(info);
    pattern->GetFocusHub()->focusType_ = FocusType::NODE;
    pattern->hasPreviewText_ = true;
    pattern->HandleLongPress(info);

    info.SetSourceDevice(SourceType::TOUCH);
    info.SetLocalLocation(Offset(10, 10));
    pattern->hasPreviewText_ = false;
    std::list<FingerInfo> fingerList;
    fingerList.push_back({ .fingerId_ = 0 });
    info.SetFingerList(fingerList);
    pattern->HandleLongPress(info);

    TouchEventInfo touchInfo("test");
    TouchLocationInfo moveLocationInfo(0);
    moveLocationInfo.SetLocalLocation(Offset(30, 30));
    moveLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfo.AddChangedTouchLocationInfo(std::move(moveLocationInfo));

    TouchLocationInfo moveLocationInfo0(0);
    moveLocationInfo0.SetLocalLocation(Offset(30, 30));
    moveLocationInfo0.SetTouchType(TouchType::MOVE);
    touchInfo.AddTouchLocationInfo(std::move(moveLocationInfo0));
    pattern->contentController_->SetTextValue(u"Hello");
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_TRUE(pattern->GetMagnifierController()->magnifierNodeExist_);

    pattern->GetMagnifierController()->RemoveMagnifierFrameNode();
    EXPECT_FALSE(pattern->GetMagnifierController()->magnifierNodeExist_);
}

/**
 * @tc.name: TextPattern026
 * @tc.desc: Test TextPattern InitEditingValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->deleteBackwardOperations_.emplace(10);
    pattern->InitEditingValueText(u"");
}

/**
 * @tc.name: TextPattern027
 * @tc.desc: Test TextPattern InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->deleteBackwardOperations_.emplace(10);
    pattern->InitValueText(u"");
    pattern->InitValueText(u"123");
}

/**
 * @tc.name: TextPattern028
 * @tc.desc: Test TextPattern HandleRightMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::RELEASE);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->HandleRightMouseEvent(info);
}

/**
 * @tc.name: TextPattern029
 * @tc.desc: Test TextPattern HandleRightMousePressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::RELEASE);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    pattern->hasPreviewText_ = true;
    pattern->HandleRightMousePressEvent(info);
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleRightMousePressEvent(info);
}

/**
 * @tc.name: TextPattern030
 * @tc.desc: Test TextPattern GetWordLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetWordLength(10, 10);
}

/**
 * @tc.name: TextPattern031
 * @tc.desc: Test TextPattern GetLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetLineEndPosition(10, true);
}

/**
 * @tc.name: TextPattern032
 * @tc.desc: Test TextPattern GetLineBeginPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetLineBeginPosition(10, true);
}

/**
 * @tc.name: TextPattern033
 * @tc.desc: Test TextPattern CursorMoveLeftOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->CursorMoveLeftOperation();
}

/**
 * @tc.name: TextPattern034
 * @tc.desc: Test TextPattern CursorMoveLeftWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = -1;
    pattern->CursorMoveLeftWord();
}

/**
 * @tc.name: TextPattern035
 * @tc.desc: Test TextPattern CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->CursorMoveRightOperation();
}

/**
 * @tc.name: TextPattern036
 * @tc.desc: Test TextPattern CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->contentController_->SetTextValue(u"");
    pattern->selectController_->caretInfo_.index = 2;
    pattern->CursorMoveRightWord();
    pattern->contentController_->SetTextValue(u"123");
    pattern->selectController_->caretInfo_.index = 0;
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 3;
    pattern->CursorMoveRightWord();
}

/**
 * @tc.name: TextPattern037
 * @tc.desc: Test TextPattern CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->contentController_->SetTextValue(u"123");
    pattern->selectController_->caretInfo_.index = 0;
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 3;
    pattern->CursorMoveLineEnd();
}

/**
 * @tc.name: TextPattern038
 * @tc.desc: Test TextPattern HandleCounterBorder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->showCountBorderStyle_ = true;
    pattern->HandleCounterBorder();
}

/**
 * @tc.name: TextPattern039
 * @tc.desc: Test TextPattern PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->PerformAction(TextInputAction::NEW_LINE, false);
    pattern->focusIndex_ = FocuseIndex::UNIT;
    pattern->PerformAction(TextInputAction::NEW_LINE, false);
    pattern->textInputBlurOnSubmit_ = false;
    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->PerformAction(TextInputAction::DONE, false);
}

/**
 * @tc.name: TextPattern040
 * @tc.desc: Test TextPattern OnHandleAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->parentGlobalOffset_ = pattern->GetPaintRectGlobalOffset();
    pattern->OnHandleAreaChanged();
    pattern->parentGlobalOffset_ = OffsetF(1.0f, 1.0f);
    pattern->OnHandleAreaChanged();
}

/**
 * @tc.name: TextPattern041
 * @tc.desc: Test TextPattern OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->OnVisibleChange(false);
}

/**
 * @tc.name: TextPattern042
 * @tc.desc: Test TextPattern OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->DeleteBackwardOperation(1);
    pattern->DeleteForwardOperation(1);
}

/**
 * @tc.name: TextPattern043
 * @tc.desc: Test TextPattern HandleSelectionLeft
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 0;
    pattern->HandleSelectionLeft();
}

/**
 * @tc.name: TextPattern044
 * @tc.desc: Test TextPattern HandleSelectionLeftWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 0;
    pattern->HandleSelectionLeftWord();
    pattern->selectController_->caretInfo_.index = -1;
    pattern->HandleSelectionLeftWord();
    pattern->selectController_->caretInfo_.index = 1;
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionLeftWord();
}

/**
 * @tc.name: TextPattern045
 * @tc.desc: Test TextPattern HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 0;
    pattern->HandleSelectionLineBegin();
    pattern->selectController_->caretInfo_.index = 1;
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionLineBegin();
}

/**
 * @tc.name: TextPattern046
 * @tc.desc: Test TextPattern HandleSelectionHome
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 0;
    pattern->HandleSelectionHome();
    pattern->selectController_->caretInfo_.index = 1;
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionHome();
}

/**
 * @tc.name: TextPattern047
 * @tc.desc: Test TextPattern HandleSelectionRight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 1;
    pattern->contentController_->SetTextValue(u"");
    pattern->HandleSelectionRight();
}

/**
 * @tc.name: TextPattern048
 * @tc.desc: Test TextPattern HandleSelectionRightWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 1;
    pattern->contentController_->SetTextValue(u"1");
    pattern->HandleSelectionRightWord();
    pattern->selectController_->caretInfo_.index = 4;
    pattern->contentController_->SetTextValue(u"1");
    pattern->HandleSelectionRightWord();
}

/**
 * @tc.name: TextPattern049
 * @tc.desc: Test TextPattern HandleSelectionLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 1;
    pattern->contentController_->SetTextValue(u"1");
    pattern->HandleSelectionLineEnd();
    pattern->selectController_->caretInfo_.index = 0;
    pattern->contentController_->SetTextValue(u"1");
    pattern->HandleSelectionLineEnd();
}

/**
 * @tc.name: TextPattern050
 * @tc.desc: Test TextPattern HandleSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->caretInfo_.index = 1;
    pattern->contentController_->SetTextValue(u"1");
    pattern->HandleSelectionEnd();
    pattern->selectController_->caretInfo_.index = 4;
    pattern->contentController_->SetTextValue(u"1");
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionEnd();
}

/**
 * @tc.name: TextPattern050
 * @tc.desc: Test TextPattern SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->magnifierController_->isShowMagnifier_ = true;
    pattern->SetCaretPosition(0);
}

/**
 * @tc.name: TextPattern052
 * @tc.desc: Test TextPattern SetSelectionFlag
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->hasPreviewText_ = true;
    pattern->SetSelectionFlag(1, 10, std::nullopt, true);
}

/**
 * @tc.name: TextPattern053
 * @tc.desc: Test TextPattern OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnScrollCallback(1.0f, SCROLL_FROM_START);
}

/**
 * @tc.name: TextPattern055
 * @tc.desc: test testInput text GetTextPaintOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern055, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->GetTextPaintOffset();
}

/**
 * @tc.name: TextPattern056
 * @tc.desc: test testInput text CreateHandles
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern056, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->CreateHandles();
    pattern->dragStatus_ = DragStatus::NONE;
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->CreateHandles();
    pattern->dragStatus_ = DragStatus::NONE;
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->selectOverlay_->lastSourceType_ = SourceType::TOUCH;
    pattern->CreateHandles();
}

/**
 * @tc.name: TextPattern057
 * @tc.desc: test testInput text ProcessResponseArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern057, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<TextInputResponseArea> responseArea = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern);
    pattern->cleanNodeResponseArea_ = AceType::DynamicCast<CleanNodeResponseArea>(responseArea);
    pattern->ProcessResponseArea();
}

/**
 * @tc.name: TextPattern058
 * @tc.desc: test testInput text UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern058, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->UpdateFocusForward();
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->UpdateFocusForward();
}

/**
 * @tc.name: TextPattern059
 * @tc.desc: test testInput text UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern059, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->UpdateFocusBackward();
}

/**
 * @tc.name: TextPattern060
 * @tc.desc: test testInput text HandleSpaceEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern060, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->focusIndex_ = FocuseIndex::TEXT;
    pattern->HandleSpaceEvent();
}

/**
 * @tc.name: TextPattern061
 * @tc.desc: test testInput text GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern061, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    RoundRect paintRect;
    pattern->focusIndex_ = FocuseIndex::CANCEL;
    pattern->GetInnerFocusPaintRect(paintRect);
}

/**
 * @tc.name: TextPattern064
 * @tc.desc: test testInput text GetAvoidSoftKeyboardOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern064, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetAvoidSoftKeyboardOffset();
}

/**
 * @tc.name: TextPattern065
 * @tc.desc: test testInput text ConvertGlobalToLocalOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern065, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    GestureEvent info;
    pattern->selectOverlay_->hasTransform_ = false;
    pattern->ConvertGlobalToLocalOffset(info.GetGlobalLocation());
}

/**
 * @tc.name: TextPattern066
 * @tc.desc: test testInput text FinishTextPreviewOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNGOne, TextPattern066, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField();
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->hasPreviewText_ = true;
    pattern->FinishTextPreviewOperation();
    pattern->hasPreviewText_ = false;
    pattern->FinishTextPreviewOperation();
}
} // namespace OHOS::Ace::NG
