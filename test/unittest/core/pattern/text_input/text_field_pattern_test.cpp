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

#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTest : public TextInputBases {
public:
};

/**
 * @tc.name: TextPattern001
 * @tc.desc: Test TextPattern UpdateCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern001, TestSize.Level1)
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
    pattern->UpdateCaretRect(true);
}

/**
 * @tc.name: TextPattern002
 * @tc.desc: Test TextPattern CheckSelectAreaVisible
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern002, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern003, TestSize.Level1)
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
}

/**
 * @tc.name: TextPattern004
 * @tc.desc: Test TextPattern HandleExtendAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern004, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern005, TestSize.Level1)
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
    pattern->isCustomKeyboardAttached_ = true;
    auto func1 = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ;
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
HWTEST_F(TextFieldPatternTest, TextPattern006, TestSize.Level1)
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
    EXPECT_EQ(pattern->CanUndo(), false);
    EXPECT_EQ(pattern->CanRedo(), false);
    pattern->HandleOnUndoAction();
    TextEditingValueNG record {
        .text = pattern->contentController_->GetTextValue(),
        .caretPosition = pattern->selectController_->GetCaretIndex(),
    };
    pattern->operationRecords_.emplace_back(record);
    pattern->HandleOnUndoAction();
    for (int32_t i = 0; i < 30; i++) {
        TextEditingValueNG value;
        value.text = "123";
        pattern->redoOperationRecords_.push_back(value);
    }
    pattern->HandleOnUndoAction();
}

/**
 * @tc.name: TextPattern007
 * @tc.desc: Test TextPattern HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern007, TestSize.Level1)
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
        .text = pattern->contentController_->GetTextValue(),
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
HWTEST_F(TextFieldPatternTest, TextPattern008, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern009, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern010, TestSize.Level1)
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
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = false;
    pattern->InitDragDropCallBack();
}

/**
 * @tc.name: TextPattern011
 * @tc.desc: Test TextPattern InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern011, TestSize.Level1)
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
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = true;
    pattern->InitDragDropCallBack();
}

/**
 * @tc.name: TextPattern012
 * @tc.desc: Test TextPattern HandleDoubleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    CreateTextField();
    GestureEvent info;
    info.deviceType_ = SourceType::MOUSE;
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
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
HWTEST_F(TextFieldPatternTest, TextPattern013, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern014, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern015, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern016, TestSize.Level1)
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
}

/**
 * @tc.name: TextPattern017
 * @tc.desc: Test TextPattern StartTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern017, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern018, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern019, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern020, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern021, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern022, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern023, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern024, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern025, TestSize.Level1)
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
}

/**
 * @tc.name: TextPattern026
 * @tc.desc: Test TextPattern InitEditingValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern026, TestSize.Level1)
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
    pattern->InitEditingValueText("");
}

/**
 * @tc.name: TextPattern027
 * @tc.desc: Test TextPattern InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern027, TestSize.Level1)
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
    pattern->InitValueText("");
    pattern->InitValueText("123");
}

/**
 * @tc.name: TextPattern028
 * @tc.desc: Test TextPattern HandleRightMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern028, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern029, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern030, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern031, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern032, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern033, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern034, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern035, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern036, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("");
    pattern->selectController_->caretInfo_.index = 2;
    pattern->CursorMoveRightWord();
    pattern->contentController_->SetTextValue("123");
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
HWTEST_F(TextFieldPatternTest, TextPattern037, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("123");
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
HWTEST_F(TextFieldPatternTest, TextPattern038, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern039, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern040, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern041, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern042, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern043, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern044, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern045, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern046, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern047, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("");
    pattern->HandleSelectionRight();
}

/**
 * @tc.name: TextPattern048
 * @tc.desc: Test TextPattern HandleSelectionRightWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern048, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("1");
    pattern->HandleSelectionRightWord();
    pattern->selectController_->caretInfo_.index = 4;
    pattern->contentController_->SetTextValue("1");
    pattern->HandleSelectionRightWord();
}

/**
 * @tc.name: TextPattern049
 * @tc.desc: Test TextPattern HandleSelectionLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern049, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("1");
    pattern->HandleSelectionLineEnd();
    pattern->selectController_->caretInfo_.index = 0;
    pattern->contentController_->SetTextValue("1");
    pattern->HandleSelectionLineEnd();
}

/**
 * @tc.name: TextPattern050
 * @tc.desc: Test TextPattern HandleSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern050, TestSize.Level1)
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
    pattern->contentController_->SetTextValue("1");
    pattern->HandleSelectionEnd();
    pattern->selectController_->caretInfo_.index = 4;
    pattern->contentController_->SetTextValue("1");
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionEnd();
}

/**
 * @tc.name: TextPattern050
 * @tc.desc: Test TextPattern SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern051, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern052, TestSize.Level1)
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
HWTEST_F(TextFieldPatternTest, TextPattern053, TestSize.Level1)
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
 * @tc.name: TextPattern054
 * @tc.desc: test testInput text ParseFillContentJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern054, TestSize.Level0)
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

    std::unordered_map<std::string, std::variant<std::string, bool, int32_t>> fillContentMap;
    auto jsonObj = JsonUtil::ParseJsonString("fillContent");
    pattern->ParseFillContentJsonValue(jsonObj, fillContentMap);
    auto jsonObject = JsonUtil::Create(true);
    pattern->ParseFillContentJsonValue(jsonObject, fillContentMap);
    const char* a = "a";
    jsonObject->Put(a, 1);
    pattern->ParseFillContentJsonValue(jsonObject, fillContentMap);
}

/**
 * @tc.name: TextPattern055
 * @tc.desc: test testInput text GetTextPaintOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern055, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern056, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern057, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern058, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern059, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern060, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern061, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern064, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern065, TestSize.Level0)
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
HWTEST_F(TextFieldPatternTest, TextPattern066, TestSize.Level0)
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

/**
 * @tc.name: TextPattern067
 * @tc.desc: test testInput text SetPreviewTextOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern067, TestSize.Level0)
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
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    const PreviewTextInfo info = { "ni", { -1, -1 } };
    pattern->SetPreviewTextOperation(info);
}

/**
 * @tc.name: TextPattern068
 * @tc.desc: test testInput text GetPreviewTextRects
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern068, TestSize.Level0)
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
    pattern->hasPreviewText_ = false;
    pattern->GetPreviewTextRects();
    pattern->hasPreviewText_ = true;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    pattern->GetPreviewTextRects();
}

/**
 * @tc.name: TextPattern069
 * @tc.desc: test testInput text CheckPreviewTextValidate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern069, TestSize.Level0)
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
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    pattern->CheckPreviewTextValidate("", previewRange);
    previewRange.start = -1;
    previewRange.end = 0;
    pattern->CheckPreviewTextValidate("", previewRange);
}

/**
 * @tc.name: TextPattern070
 * @tc.desc: test testInput text ReceivePreviewTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern070, TestSize.Level0)
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
    pattern->ReceivePreviewTextStyle("");
    pattern->ReceivePreviewTextStyle("123");
}

/**
 * @tc.name: TextPattern071
 * @tc.desc: test testInput text OnCaretMoveDone
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern071, TestSize.Level0)
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
    TouchEventInfo Info("");
    pattern->isMoveCaretAnywhere_ = true;
    pattern->OnCaretMoveDone(Info);
    pattern->isMoveCaretAnywhere_ = false;
    pattern->OnCaretMoveDone(Info);
}

/**
 * @tc.name: TextPattern072
 * @tc.desc: test testInput text ProcessOverlayAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern072, TestSize.Level0)
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
    pattern->needToRefreshSelectOverlay_ = true;
    pattern->ProcessOverlayAfterLayout(OffsetF());
    auto func = [] {};
    pattern->processOverlayDelayTask_ = func;
    pattern->ProcessOverlayAfterLayout(OffsetF());
}

/**
 * @tc.name: TextPattern073
 * @tc.desc: test testInput text AdjustTextInReasonableArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern073, TestSize.Level0)
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
    pattern->textRect_.height_ = 0;
    pattern->contentRect_.height_ = 0;
    pattern->textRect_.y_ = 1;
    pattern->contentRect_.y_ = -1;
    pattern->AdjustTextInReasonableArea();
}

/**
 * @tc.name: TextPattern074
 * @tc.desc: test testInput text OnScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern074, TestSize.Level0)
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
    pattern->selectOverlay_->isUsingMouse_ = true;
    pattern->OnScrollEndCallback();
    pattern->selectOverlay_->isUsingMouse_ = false;
    pattern->ProcessOverlay();
    pattern->OnScrollEndCallback();
    pattern->isTextSelectionMenuShow_ = false;
}

/**
 * @tc.name: TextPattern075
 * @tc.desc: test testInput text OnTextAreaScroll
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern075, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnTextAreaScroll(1.0f);
    pattern->textRect_.height_ = 1;
    pattern->contentRect_.height_ = 0;
    pattern->OnTextAreaScroll(1.0f);
    pattern->textRect_.y_ = 1;
    pattern->contentRect_.y_  = 10;
    pattern->OnTextAreaScroll(1.0f);
}

/**
 * @tc.name: TextPattern076
 * @tc.desc: test testInput text OnTextInputScroll
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern076, TestSize.Level0)
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
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    pattern = pattern_;
    pattern->textRect_.width_ = 10;
    pattern->contentRect_.width_ = 0;
    pattern->textRect_.x_ = 10;
    pattern->contentRect_.x_  = 1;
    pattern->OnTextInputScroll(1.0f);
}

/**
 * @tc.name: TextPattern077
 * @tc.desc: test testInput text ConvertTouchOffsetToCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern077, TestSize.Level0)
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
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    Offset offset(1.0, 1.0);
    pattern->ConvertTouchOffsetToCaretPosition(offset);
}

/**
 * @tc.name: TextPattern078
 * @tc.desc: test testInput text HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern078, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
}

/**
 * @tc.name: TextPattern079
 * @tc.desc: test testInput text ProcNormalInlineStateInBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern079, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = textFieldNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    textFieldNode->MarkModifyDone();
    pattern->OnModifyDone();
    pattern->ProcNormalInlineStateInBlurEvent();

    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    textFieldNode->MarkModifyDone();
    pattern->OnModifyDone();
    pattern->isTextInput_ = true;
    pattern->ProcNormalInlineStateInBlurEvent();
}

/**
 * @tc.name: TextPattern080
 * @tc.desc: test testInput text OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern080, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN);
    pattern->needToRequestKeyboardOnFocus_ = false;
    pattern->OnKeyEvent(keyEvent);
    pattern->isFocusedBeforeClick_ = true;
    pattern->OnKeyEvent(keyEvent);
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->OnKeyEvent(keyEvent);
    pattern->GetFocusHub()->currentFocus_ = true;
    pattern->OnKeyEvent(keyEvent);
    pattern->needToRequestKeyboardOnFocus_ = false;
    pattern->needToRequestKeyboardInner_ = true;
    pattern->OnKeyEvent(keyEvent);
}

/**
 * @tc.name: TextPattern081
 * @tc.desc: test testInput text HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern081, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;
    pattern->inlineSelectAllFlag_ = true;
    pattern->HandleOnSelectAll(true, false, false);
    pattern->selectOverlay_->isUsingMouse_ = true;
    pattern->HandleOnSelectAll(false, false, false);
}

/**
 * @tc.name: TextPattern082
 * @tc.desc: test testInput text HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern082, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));

    pattern->isMoveCaretAnywhere_ = true;
    pattern->HandleTouchEvent(touchEventInfo);
    
    pattern->isMoveCaretAnywhere_ = false;
    pattern->ProcessOverlay();
    pattern->moveCaretState_.isTouchCaret = true;
    pattern->selectOverlay_->isUsingMouse_ = true;
    pattern->HandleTouchEvent(touchEventInfo);

    pattern->ProcessOverlay();
    pattern->moveCaretState_.isTouchCaret = false;
    pattern->HandleTouchEvent(touchEventInfo);

    RefPtr<MagnifierController> controller = pattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(OffsetF(0.f, 0.f));
    EXPECT_TRUE(controller->GetShowMagnifier());
    touchLocationInfo.touchType_ = TouchType::CANCEL;
    touchEventInfo.touches_.clear();
    touchEventInfo.changedTouches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(controller->GetShowMagnifier());
}

/**
 * @tc.name: TextPattern083
 * @tc.desc: test testInput text HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern083, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset offset(1.0, 1.0);
    pattern->enableTouchAndHoverEffect_ = false;
    pattern->HandleTouchDown(offset);
    pattern->enableTouchAndHoverEffect_ = true;
    pattern->isMousePressed_ = true;
    pattern->HandleTouchDown(offset);
    pattern->isMousePressed_ = false;
    pattern->moveCaretState_.isTouchCaret = false;
    pattern->HandleTouchDown(offset);
}

/**
 * @tc.name: TextPattern084
 * @tc.desc: test testInput text HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern084, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset offset(1.0, 1.0);
    pattern->magnifierController_->isShowMagnifier_ = true;
    pattern->hasPreviewText_ = true;
    pattern->HandleTouchUp();
    pattern->hasPreviewText_ = false;
    pattern->HandleTouchUp();
}

/**
 * @tc.name: TextPattern085
 * @tc.desc: test testInput text HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern085, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    pattern->moveCaretState_.isTouchCaret = true;
    pattern->hasPreviewText_ = true;
    pattern->HandleTouchMove(touchLocationInfo);
    pattern->hasPreviewText_ = false;
    pattern->HandleTouchMove(touchLocationInfo);
}

/**
 * @tc.name: TextPattern086
 * @tc.desc: test testInput text UpdateCaretByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern086, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    pattern->hasPreviewText_ = true;
    pattern->UpdateCaretByTouchMove(touchLocationInfo);
}

/**
 * @tc.name: TextPattern087
 * @tc.desc: test testInput text ShowSelectAfterDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern087, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->selectOverlay_->isUsingMouse_ = true;
    pattern->ShowSelectAfterDragEvent();
}

/**
 * @tc.name: TextPattern088
 * @tc.desc: test testInput text HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern088, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    GestureEvent info;
    pattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    pattern->HandleClickEvent(info);
}

/**
 * @tc.name: TextPattern089
 * @tc.desc: test testInput text ProcessAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern089, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    bool isPopup1 = true;
    bool isPopup2 = false;
    pattern->ProcessAutoFill(isPopup1, true, true);
    pattern->ProcessAutoFill(isPopup2, false, false);
}

/**
 * @tc.name: TextPattern090
 * @tc.desc: test testInput text ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern090, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    CreateTextField(DEFAULT_TEXT, DEFAULT_PLACE_HOLDER);
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isTransparent_ = true;
    pattern->ScheduleCursorTwinkling();
}

/**
 * @tc.name: TextPattern092
 * @tc.desc: test testInput text ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern092, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tmpHost = pattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto frameId = tmpHost->GetId();
    Offset offset1(1.0, -1.0);
    pattern->frameRect_ = RectF(0, 0, 0, 0);
    pattern->ChangeMouseState(offset1, frameId, true);
    Offset offset2(1.0, -1.0);
    pattern->frameRect_ = RectF(0, 0, 10, 0);
    pattern->ChangeMouseState(offset2, frameId, true);
    Offset offset3(1.0, 1.0);
    pattern->frameRect_ = RectF(0, 0, 10, 0);
    pattern->ChangeMouseState(offset3, frameId, true);
    Offset offset4(1.0, 1.0);
    pattern->frameRect_ = RectF(0, 0, 10, 50);
    pattern->ChangeMouseState(offset4, frameId, true);
}

/**
 * @tc.name: TextPattern093
 * @tc.desc: test testInput text ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern093, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->GetFocusHub()->currentFocus_ = false;
    pattern->TwinklingByFocus();
}

/**
 * @tc.name: TextPattern095
 * @tc.desc: test testInput text GetLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern096, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    Dimension a;
    a.SetValue(1.0);
    ASSERT_NE(pattern->GetLayoutProperty<TextFieldLayoutProperty>(), nullptr);
    auto stylePtr = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    stylePtr->propFontStyle_ = std::make_unique<FontStyle>();
    ASSERT_NE(pattern->GetLayoutProperty<TextFieldLayoutProperty>()->propFontStyle_, nullptr);
    pattern->GetLayoutProperty<TextFieldLayoutProperty>()->propFontStyle_->UpdateFontSize(a);
    Dimension b;
    b.SetValue(2.0);
    auto styleSize = pattern->GetLayoutProperty<TextFieldLayoutProperty>()->GetFontSizeValue(b);
    EXPECT_EQ(1.0, styleSize.Value());
}

/**
 * @tc.name: TextPattern097
 * @tc.desc: test testInput text IsMouseOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern097, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    GestureEvent info;
    Offset localLocation(1, 1);
    info.SetLocalLocation(localLocation);
    bool state = pattern->IsMouseOverScrollBar(&info);
    EXPECT_FALSE(state);
}

/**
 * @tc.name: TextPattern098
 * @tc.desc: test testInput text AllowCopy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern098, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    bool state = pattern->AllowCopy();
    EXPECT_TRUE(state);
}

/**
 * @tc.name: TextPattern099
 * @tc.desc: test testInput text AfterSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern099, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->AfterSelection();
    EXPECT_TRUE(pattern->showSelect_);
}

/**
 * @tc.name: TextPattern100
 * @tc.desc: test testInput text AfterSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern100, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;
    pattern->AfterSelection();
    EXPECT_FALSE(pattern->showSelect_);
}

/**
 * @tc.name: TextPattern101
 * @tc.desc: test testInput text HandleSelectionUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern101, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 0;
    pattern->selectController_->secondHandleInfo_.index = 0;
    pattern->HandleSelectionUp();
    EXPECT_FALSE(pattern->showSelect_);
}

/**
 * @tc.name: TextPattern102
 * @tc.desc: test testInput text HandleSelectionUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern102, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionUp();
    EXPECT_TRUE(pattern->showSelect_);
}

/**
 * @tc.name: TextPattern103
 * @tc.desc: test testInput text HandleSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, TextPattern103, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->firstHandleInfo_.index = 1;
    pattern->selectController_->secondHandleInfo_.index = 2;
    pattern->HandleSelectionEnd();
    EXPECT_TRUE(pattern->showSelect_);
}

/**
 * @tc.name: GetTextOrPlaceHolderFontSize001
 * @tc.desc: test testInput text GetTextOrPlaceHolderFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, GetTextOrPlaceHolderFontSize001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    textFieldLayoutProperty->UpdateFontSize(Dimension(10.0));

    EXPECT_EQ(pattern->GetTextOrPlaceHolderFontSize(), 0.0);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: test testInput text OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, OnDirtyLayoutWrapperSwap001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetAccessibilityPasswordIconAction();
    DirtySwapConfig config;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textFieldNode, AceType::MakeRefPtr<GeometryNode>(), textFieldNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    auto textDragNode0 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextDragPattern>(); });
    ASSERT_NE(textDragNode0, nullptr);
    pattern->dragNode_ = textDragNode0;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    auto textDragNode1 = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textDragNode1, nullptr);
    pattern->dragNode_ = textDragNode1;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->dragStatus_ = DragStatus::DRAGGING;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->needToRefreshSelectOverlay_ = true;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->needToRefreshSelectOverlay_ = true;
    pattern->paragraphWidth_ = 10.0;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->needToRefreshSelectOverlay_ = true;
    pattern->paragraphWidth_ = 10.0;
    pattern->textRect_.SetRect(0, 0, 10, 10);
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    auto oldHostNode = layoutWrapper->hostNode_;
    layoutWrapper->hostNode_ = nullptr;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);
    layoutWrapper->hostNode_ = oldHostNode;

    pattern->needSelectAll_ = true;
    pattern->isLongPress_ = true;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->needSelectAll_ = true;
    pattern->isLongPress_ = false;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);

    pattern->mouseStatus_ = MouseStatus::RELEASED;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), true);
    config.skipMeasure = true;
    layoutWrapper->skipMeasureContent_ = true;
    layoutWrapper->layoutAlgorithm_->skipMeasure_ = true;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);
}

/**
 * @tc.name: OnDirectionConfigurationUpdate001
 * @tc.desc: test testInput text OnDirectionConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, OnDirectionConfigurationUpdate001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = textFieldNode->GetContextRefPtr();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
    ASSERT_NE(context->taskExecutor_, nullptr);

    pattern->isCustomKeyboardAttached_ = true;
    pattern->OnDirectionConfigurationUpdate();

    pattern->selectController_->caretInfo_.rect.SetRect(100, 100, 10, 10);
    pattern->isCustomKeyboardAttached_ = true;
    pattern->OnDirectionConfigurationUpdate();

    context->taskScheduler_->afterLayoutTasks_.clear();
    pattern->isCustomKeyboardAttached_ = false;
    pattern->OnDirectionConfigurationUpdate();
    EXPECT_EQ(context->taskScheduler_->afterLayoutTasks_.empty(), true);
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test testInput text HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, HandleOnCopy001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    pattern->clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    ASSERT_NE(pattern->clipboard_, nullptr);

    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_NE(pattern->contentController_, nullptr);
    pattern->contentController_->content_ = "Test";
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->UpdateHandleIndex(0, 4);

    auto eventHub = textFieldNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    bool calledOnCopy = false;
    eventHub->SetOnCopy([&calledOnCopy](const std::string& value) {
        calledOnCopy = true;
    });

    ASSERT_NE(pattern->selectOverlay_, nullptr);
    pattern->selectOverlay_->SetUsingMouse(true);
    pattern->HandleOnCopy(false);
    pattern->selectOverlay_->SetUsingMouse(false);
    pattern->HandleOnCopy(false);
    EXPECT_EQ(calledOnCopy, true);

    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    calledOnCopy = false;
    pattern->HandleOnCopy(true);
    EXPECT_EQ(calledOnCopy, false);

    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    calledOnCopy = false;
    pattern->HandleOnCopy(true);
    EXPECT_EQ(calledOnCopy, false);
}

/**
 * @tc.name: HandleOnCut001
 * @tc.desc: test testInput text HandleOnCut
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, HandleOnCut001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    auto context = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    pattern->HandleOnCut();
    pattern->UpdateCaretInfoToController(false);
    EXPECT_EQ(pattern->selectController_->GetFirstHandleInfo().index, 0);
    EXPECT_EQ(pattern->selectController_->GetSecondHandleInfo().index, 0);
}

/**
 * @tc.name: FireEventHubOnChange001
 * @tc.desc: test testInput text FireEventHubOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, FireEventHubOnChange001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    pattern->textFieldOverlayModifier_ = AceType::MakeRefPtr<TextFieldOverlayModifier>(pattern, scrollEdgeEffect);
    pattern->textFieldForegroundModifier_ = AceType::MakeRefPtr<TextFieldForegroundModifier>(pattern);
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    std::string text = "Test";
    layoutProperty->UpdateNeedFireOnChange(true);

    pattern->underlineWidth_ = 1.0_px;
    pattern->FireEventHubOnChange(text);
    EXPECT_NE(pattern->underlineWidth_, 2.0_px);

    pattern->underlineWidth_ = 1.0_px;
    layoutProperty->UpdateShowUnderline(true);
    pattern->FireEventHubOnChange(text);
    EXPECT_EQ(pattern->underlineWidth_, 2.0_px);

    pattern->underlineWidth_ = 1.0_px;
    layoutProperty->UpdateShowErrorText(true);
 
    pattern->CalculateBoundsRect();
    pattern->FireEventHubOnChange(text);
    EXPECT_NE(pattern->underlineWidth_, 2.0_px);
}

/**
 * @tc.name: GetAutoFillTriggeredStateByType001
 * @tc.desc: test testInput text GetAutoFillTriggeredStateByType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, GetAutoFillTriggeredStateByType001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto parentFrameNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(parentFrameNode, nullptr);
    textFieldNode->SetParent(parentFrameNode);

    auto autoFillContainerNode = textFieldNode->GetFirstAutoFillContainerNode();
    ASSERT_NE(autoFillContainerNode, nullptr);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    stateHolder->SetAutoFillPasswordTriggered(true);
    stateHolder->SetAutoFillNewPasswordTriggered(true);

    AceAutoFillType autoFillType = AceAutoFillType::ACE_UNSPECIFIED;
    EXPECT_EQ(pattern->GetAutoFillTriggeredStateByType(autoFillType), false);

    autoFillType = AceAutoFillType::ACE_USER_NAME;
    EXPECT_EQ(pattern->GetAutoFillTriggeredStateByType(autoFillType), false);

    autoFillType = AceAutoFillType::ACE_PASSWORD;
    EXPECT_EQ(pattern->GetAutoFillTriggeredStateByType(autoFillType), false);

    autoFillType = AceAutoFillType::ACE_NEW_PASSWORD;
    EXPECT_EQ(pattern->GetAutoFillTriggeredStateByType(autoFillType), false);
}

/**
 * @tc.name: SetAutoFillTriggeredStateByType001
 * @tc.desc: test testInput text SetAutoFillTriggeredStateByType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTest, SetAutoFillTriggeredStateByType001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto parentFrameNode = FrameNode::GetOrCreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()); });
    ASSERT_NE(parentFrameNode, nullptr);
    textFieldNode->SetParent(parentFrameNode);

    auto autoFillContainerNode = textFieldNode->GetFirstAutoFillContainerNode();
    ASSERT_NE(autoFillContainerNode, nullptr);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    ASSERT_NE(stateHolder, nullptr);
    stateHolder->SetAutoFillPasswordTriggered(true);
    stateHolder->SetAutoFillNewPasswordTriggered(true);

    AceAutoFillType autoFillType = AceAutoFillType::ACE_UNSPECIFIED;
    pattern->SetAutoFillTriggeredStateByType(autoFillType);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), true);

    autoFillType = AceAutoFillType::ACE_USER_NAME;
    pattern->SetAutoFillTriggeredStateByType(autoFillType);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), true);

    autoFillType = AceAutoFillType::ACE_PASSWORD;
    pattern->SetAutoFillTriggeredStateByType(autoFillType);
    EXPECT_EQ(stateHolder->IsAutoFillPasswordTriggered(), true);

    autoFillType = AceAutoFillType::ACE_NEW_PASSWORD;
    pattern->SetAutoFillTriggeredStateByType(autoFillType);
    EXPECT_EQ(stateHolder->IsAutoFillNewPasswordTriggered(), true);
}
} // namespace OHOS::Ace::NG
