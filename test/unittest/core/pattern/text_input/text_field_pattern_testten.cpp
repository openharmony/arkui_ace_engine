/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

void TextFieldPatternTestten::SetUp() {}

void TextFieldPatternTestten::TearDown() {}

/**
 * @tc.name: SetCustomKeyboardWithNode001
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->isCustomKeyboardAttached_ = true;
    RefPtr<UINode> keyboardBuilder =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode002
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = false;
    RefPtr<UINode> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode003
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode003, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->isCustomKeyboardAttached_ = false;
    RefPtr<UINode> keyboardBuilder =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode004
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode004, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->isCustomKeyboardAttached_ = true;
    RefPtr<UINode> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode005
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode005, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = true;
    RefPtr<UINode> keyboardBuilder =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode006
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode006, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = true;
    RefPtr<UINode> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode007
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode007, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->isCustomKeyboardAttached_ = false;
    RefPtr<UINode> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboardWithNode008
 * @tc.desc: Test SetCustomKeyboardWithNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboardWithNode008, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = false;
    RefPtr<UINode> keyboardBuilder =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetCustomKeyboardWithNode(keyboardBuilder);
    EXPECT_EQ(textFieldPattern->customKeyboard_, keyboardBuilder);
}

/**
 * @tc.name: SetCustomKeyboard001
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    ASSERT_NE(textFieldPattern->customKeyboardBuilder_, nullptr);
    textFieldPattern->isCustomKeyboardAttached_ = true;
    std::function<void()> keyboardBuilder = []() {};
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_TRUE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard002
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = false;
    std::function<void()> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_FALSE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard003
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard003, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = true;
    std::function<void()> keyboardBuilder = []() {};
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_TRUE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard004
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard004, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->isCustomKeyboardAttached_ = true;
    std::function<void()> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_FALSE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard005
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard005, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->isCustomKeyboardAttached_ = false;
    std::function<void()> keyboardBuilder = []() {};
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_TRUE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard006
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard006, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = true;
    std::function<void()> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_FALSE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard007
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard007, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->isCustomKeyboardAttached_ = false;
    std::function<void()> keyboardBuilder = []() {};
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_TRUE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetCustomKeyboard008
 * @tc.desc: Test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetCustomKeyboard008, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->isCustomKeyboardAttached_ = false;
    std::function<void()> keyboardBuilder = nullptr;
    textFieldPattern->SetCustomKeyboard(std::move(keyboardBuilder));
    EXPECT_FALSE(textFieldPattern->customKeyboardBuilder_);
}

/**
 * @tc.name: SetUnitNode001
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(unitNode, nullptr);
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: SetUnitNode002
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    RefPtr<NG::UINode> unitNode = nullptr;
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 0);
}

/**
 * @tc.name: SetUnitNode003
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode003, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(unitNode, nullptr);
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 0);
}

/**
 * @tc.name: SetUnitNode004
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode004, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    RefPtr<NG::UINode> unitNode = nullptr;
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: Test BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, BetweenSelectedPosition001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    textSelectController->firstHandleInfo_.index = 2;
    textSelectController->secondHandleInfo_.index = 1;
    textSelectController->contentController_->content_ = u"h";
    GestureEvent info;
    auto result = textFieldPattern->BetweenSelectedPosition(info);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: DeleteRange001
 * @tc.desc: Test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteRange001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = 1;
    bool isIME = false;
    textFieldPattern->DeleteRange(start, end, isIME);
    EXPECT_EQ(start, 2);
}

/**
 * @tc.name: DeleteRange002
 * @tc.desc: Test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteRange002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = -1;
    bool isIME = false;
    textFieldPattern->DeleteRange(start, end, isIME);
    EXPECT_EQ(start, 2);
}

/**
 * @tc.name: DeleteRange003
 * @tc.desc: Test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteRange003, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isIME = false;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteRange(start, end, isIME);
    EXPECT_EQ(start, 1);
}

/**
 * @tc.name: InsertOrDeleteSpace001
 * @tc.desc: Test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InsertOrDeleteSpace001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t index = 0;
    textFieldPattern->contentController_ = AceType::MakeRefPtr<ContentController>(textFieldPattern);
    ASSERT_NE(textFieldPattern->contentController_, nullptr);
    textFieldPattern->contentController_->content_ = u"hhh";
    auto result = textFieldPattern->InsertOrDeleteSpace(index);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate001
 * @tc.desc: Test OnTextGestureSelectionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionUpdate001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    TouchEventInfo info = TouchEventInfo("info");
    textFieldPattern->contentScroller_.isScrolling = true;
    textFieldPattern->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_EQ(start, 1);
}

/**
 * @tc.name: CheckPasswordAreaState001
 * @tc.desc: Test CheckPasswordAreaState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CheckPasswordAreaState001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->showPasswordState_ = false;
    textFieldPattern->CheckPasswordAreaState();
    EXPECT_EQ(textFieldPattern->showPasswordState_, false);
}

/**
 * @tc.name: HandleSelectionHome001
 * @tc.desc: Test HandleSelectionHome
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionHome001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 0;
    textFieldPattern->HandleSelectionHome();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: HandleSelectionLineBegin001
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->contentController_->content_ = u"hh";
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: HandleSelectionLineBegin002
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin002, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->contentController_->content_ = u"hhhhhh";
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: HandleSelectionLineBegin003
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin003, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 2;
    textFieldPattern->contentController_->content_ = u"";
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: HandleSelectionLineBegin004
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin004, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 10;
    textFieldPattern->contentController_->content_ = u"hhhh";
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: DeleteForwardWord001
 * @tc.desc: Test DeleteForwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteForwardWord001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->DeleteForwardWord();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: DeleteBackwardWord001
 * @tc.desc: Test DeleteBackwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteBackwardWord001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->DeleteBackwardWord();
    EXPECT_EQ(textSelectController->caretInfo_.index, 0);
}

/**
 * @tc.name: CursorMoveLineEnd001
 * @tc.desc: Test CursorMoveLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveLineEnd001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->contentController_->content_ = u"hh";
    auto result = textFieldPattern->CursorMoveLineEnd();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CursorMoveLineBegin001
 * @tc.desc: Test CursorMoveLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveLineBegin001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->contentController_->content_ = u"hh";
    auto result = textFieldPattern->CursorMoveLineBegin();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: FloatingCaretLand001
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textFieldOverlayModifier_ = nullptr;
    textFieldPattern->floatCaretState_.FloatingCursorVisible = false;
    textFieldPattern->selectController_ = nullptr;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 0);
}

/**
 * @tc.name: FloatingCaretLand002
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textFieldOverlayModifier_ = nullptr;
    textFieldPattern->floatCaretState_.FloatingCursorVisible = true;
    textFieldPattern->selectController_->firstHandleInfo_.index = 1;
    textFieldPattern->selectController_->secondHandleInfo_.index = 1;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 0);
}

/**
 * @tc.name: FloatingCaretLand003
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand003, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    ASSERT_NE(scrollEdgeEffect, nullptr);
    textFieldPattern->textFieldOverlayModifier_ =
        AceType::MakeRefPtr<TextFieldOverlayModifier>(textFieldPattern, scrollEdgeEffect);
    textFieldPattern->floatCaretState_.FloatingCursorVisible = true;
    textFieldPattern->selectController_ = nullptr;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 1);
}

/**
 * @tc.name: FloatingCaretLand004
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand004, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    ASSERT_NE(scrollEdgeEffect, nullptr);
    textFieldPattern->textFieldOverlayModifier_ =
        AceType::MakeRefPtr<TextFieldOverlayModifier>(textFieldPattern, scrollEdgeEffect);
    textFieldPattern->floatCaretState_.FloatingCursorVisible = false;
    textFieldPattern->selectController_->firstHandleInfo_.index = 1;
    textFieldPattern->selectController_->secondHandleInfo_.index = 1;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 1);
}

/**
 * @tc.name: FloatingCaretLand005
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand005, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textFieldOverlayModifier_ = nullptr;
    textFieldPattern->floatCaretState_.FloatingCursorVisible = true;
    textFieldPattern->selectController_ = nullptr;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 0);
}

/**
 * @tc.name: FloatingCaretLand006
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand006, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    ASSERT_NE(scrollEdgeEffect, nullptr);
    textFieldPattern->textFieldOverlayModifier_ = nullptr;
    textFieldPattern->floatCaretState_.FloatingCursorVisible = false;
    textFieldPattern->selectController_->firstHandleInfo_.index = 1;
    textFieldPattern->selectController_->secondHandleInfo_.index = 1;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 0);
}

/**
 * @tc.name: FloatingCaretLand007
 * @tc.desc: Test FloatingCaretLand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FloatingCaretLand007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    ASSERT_NE(scrollEdgeEffect, nullptr);
    textFieldPattern->textFieldOverlayModifier_ =
        AceType::MakeRefPtr<TextFieldOverlayModifier>(textFieldPattern, scrollEdgeEffect);
    textFieldPattern->floatCaretState_.FloatingCursorVisible = false;
    textFieldPattern->selectController_ = nullptr;
    textFieldPattern->FloatingCaretLand();
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 1);
}

/**
 * @tc.name: IsOnCleanNodeByPosition001
 * @tc.desc: Test IsOnCleanNodeByPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, IsOnCleanNodeByPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset localOffset;
    textFieldPattern->cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->cleanNodeResponseArea_, nullptr);
    auto result = textFieldPattern->IsOnCleanNodeByPosition(localOffset);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ScheduleCursorTwinkling001
 * @tc.desc: Test ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ScheduleCursorTwinkling001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->dragRecipientStatus_ = DragStatus::ON_DROP;
    textFieldPattern->ScheduleCursorTwinkling();
    EXPECT_EQ(textFieldPattern->cursorTwinklingTask_, false);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(dirty, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = false;
    dirty->skipMeasureContent_ = true;
    auto result = textFieldPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateSelectionAndHandleVisibility001
 * @tc.desc: Test UpdateSelectionAndHandleVisibility
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdateSelectionAndHandleVisibility001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->releaseInDrop_ = true;
    textFieldPattern->UpdateSelectionAndHandleVisibility();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: SetAccessibilityUnitAction001
 * @tc.desc: Test SetAccessibilityUnitAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetAccessibilityUnitAction001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->unitNode_ = nullptr;
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    textFieldPattern->SetAccessibilityUnitAction();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: HandleSelect001
 * @tc.desc: Test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelect001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->HandleSelect(static_cast<CaretMoveIntent>(12));
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: Test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleOnUndoAction001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TextEditingValueNG t1;
    textFieldPattern->operationRecords_.push_back(t1);
    textFieldPattern->HandleOnUndoAction();
    EXPECT_EQ(textFieldPattern->redoOperationRecords_.empty(), true);
}

/**
 * @tc.name: GetCancelImageText001
 * @tc.desc: Test GetCancelImageText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, GetCancelImageText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->InitTheme();
    auto result = textFieldPattern->GetCancelImageText();
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleTouchEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchEventInfo info = TouchEventInfo("touch");
    auto touchInfo = textFieldPattern->GetAcceptedTouchLocationInfo(info);
    touchInfo->SetTouchType(TouchType::MOVE);
    textFieldPattern->selectOverlay_->isUsingMouse_ = true;
    textFieldPattern->HandleTouchEvent(info);
    EXPECT_EQ(textFieldPattern->moveCaretState_.isTouchCaret, false);
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: Test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleTouchEvent002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchEventInfo info = TouchEventInfo("touch");
    auto touchInfo = textFieldPattern->GetAcceptedTouchLocationInfo(info);
    touchInfo->SetTouchType(TouchType::CANCEL);
    textFieldPattern->magnifierController_->magnifierNodeExist_ = true;
    textFieldPattern->HandleTouchEvent(info);
    EXPECT_NE(textFieldPattern->magnifierController_->magnifierNodeExist_, false);
}

/**
 * @tc.name: HandleTouchDown001
 * @tc.desc: Test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleTouchDown001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset offset;
    textFieldPattern->HandleTouchDown(offset);
    EXPECT_EQ(textFieldPattern->magnifierController_->magnifierNodeExist_, false);
}

/**
 * @tc.name: HandleTouchUp001
 * @tc.desc: Test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleTouchUp001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->magnifierController_ =
        AIWriteAdapter::MakeRefPtr<MagnifierController>(AIWriteAdapter::WeakClaim(AceType::RawPtr(textFieldPattern)));
    textFieldPattern->HandleTouchUp();
    EXPECT_EQ(textFieldPattern->magnifierController_->magnifierNodeExist_, false);
}

/**
 * @tc.name: HandleTouchMove001
 * @tc.desc: Test HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleTouchMove001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo info(100);
    textFieldPattern->moveCaretState_.isMoveCaret = false;
    textFieldPattern->moveCaretState_.isTouchCaret = true;
    textFieldPattern->HandleTouchMove(info);
    EXPECT_NE(textFieldPattern->moveCaretState_.touchFingerId, 0);
}

/**
 * @tc.name: SetMagnifierLocalOffsetToFloatingCaretPos001
 * @tc.desc: Test SetMagnifierLocalOffsetToFloatingCaretPos
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetMagnifierLocalOffsetToFloatingCaretPos001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->floatCaretState_.lastFloatingCursorY = 2.0f;
    textFieldPattern->selectController_->floatingCaretInfo_.rect = { 2, 2, 2, 2 };
    textFieldPattern->SetMagnifierLocalOffsetToFloatingCaretPos();
    EXPECT_NE(textFieldPattern->magnifierController_, nullptr);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: Test HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleClickEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    GestureEvent info;
    textFieldPattern->firstClickAfterLosingFocus_ = false;
    textFieldPattern->hasMousePressed_ = true;
    textFieldPattern->selectController_->floatingCaretInfo_.rect = { 2, 2, 2, 2 };
    textFieldPattern->HandleClickEvent(info);
    EXPECT_NE(textFieldPattern->magnifierController_, nullptr);
}

/**
 * @tc.name: HandleBetweenSelectedPosition001
 * @tc.desc: Test HandleBetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleBetweenSelectedPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    GestureEvent info;
    info.globalLocation_ = { 1, 1 };
    textFieldPattern->selectOverlay_->isUsingMouse_ = false;
    textFieldPattern->selectController_->caretInfo_.index = 3;
    auto result = textFieldPattern->HandleBetweenSelectedPosition(info);
    EXPECT_NE(result, true);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSingleClickEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    GestureEvent info;
    info.globalLocation_ = { 1, 1 };
    bool firstGetFocus = true;
    textFieldPattern->selectOverlay_->isUsingMouse_ = false;
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->HandleSingleClickEvent(info, firstGetFocus);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: ScheduleCursorTwinkling002
 * @tc.desc: Test ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ScheduleCursorTwinkling002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->dragRecipientStatus_ = DragStatus::DRAGGING;
    textFieldPattern->ScheduleCursorTwinkling();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: ScheduleCursorTwinkling003
 * @tc.desc: Test ScheduleCursorTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ScheduleCursorTwinkling003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->dragRecipientStatus_ = DragStatus::ON_DROP;
    textFieldPattern->ScheduleCursorTwinkling();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnModifyDone001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    textFieldPattern->shiftFlag_ = false;
    textFieldPattern->OnModifyDone();
    EXPECT_NE(layoutProperty->GetCopyOptionsValue(CopyOptions::Local), CopyOptions::None);
}

/**
 * @tc.name: FireOnTextChangeEvent001
 * @tc.desc: Test FireOnTextChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FireOnTextChangeEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hh";
    textFieldPattern->hasPreviewText_ = true;
    textFieldPattern->previewTextEnd_ = 5;
    auto result = textFieldPattern->FireOnTextChangeEvent();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleLongPress001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = { 1, 1 };
    textFieldPattern->cancelButtonTouched_ = true;
    textFieldPattern->hasPreviewText_ = false;
    textFieldPattern->HandleLongPress(info);
    EXPECT_EQ(textFieldPattern->moveCaretState_.isTouchCaret, false);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: Test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleLongPress002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    GestureEvent info;
    info.deviceType_ = SourceType::NONE;
    textFieldPattern->hasPreviewText_ = true;
    textFieldPattern->contentController_->content_ = u"";
    textFieldPattern->HandleLongPress(info);
    EXPECT_EQ(textFieldPattern->moveCaretState_.isTouchCaret, false);
}

/**
 * @tc.name: IsAccessibilityClick001
 * @tc.desc: Test IsAccessibilityClick
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, IsAccessibilityClick001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    textFieldPattern->IsAccessibilityClick();
    EXPECT_EQ(accessibilityProperty->isAccessibilityFocused_, false);
}

/**
 * @tc.name: IsOnUnitByPosition001
 * @tc.desc: Test IsOnUnitByPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, IsOnUnitByPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    Offset localOffset;
    auto result = textFieldPattern->IsOnUnitByPosition(localOffset);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: InitEditingValueText001
 * @tc.desc: Test InitEditingValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitEditingValueText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::u16string content = u"asdf";
    textFieldPattern->hasPreviewText_ = true;
    textFieldPattern->contentController_->content_ = u"hh";
    textFieldPattern->InitEditingValueText(content);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: InitValueText001
 * @tc.desc: Test InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitValueText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::u16string content = u"asdf";
    textFieldPattern->hasPreviewText_ = true;
    auto result = textFieldPattern->InitValueText(content);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: InitValueText002
 * @tc.desc: Test InitValueText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitValueText002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::u16string content = u"asdf";
    textFieldPattern->hasPreviewText_ = false;
    textFieldPattern->deleteBackwardOperations_.push(0);
    textFieldPattern->deleteForwardOperations_.push(0);
    InsertCommandInfo info;
    textFieldPattern->insertCommands_.emplace(info);
    auto result = textFieldPattern->InitValueText(content);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: InitMouseEvent001
 * @tc.desc: Test InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->mouseEvent_ = nullptr;
    textFieldPattern->hoverEvent_ = nullptr;
    textFieldPattern->InitMouseEvent();
    EXPECT_EQ(textFieldPattern->hasMousePressed_, false);
}

/**
 * @tc.name: InitMouseEvent002
 * @tc.desc: Test InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitMouseEvent002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto mouseCallback = [](MouseInfo& info) {};
    auto hoverCallback = [](MouseInfo& info) {};
    textFieldPattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(mouseCallback));
    textFieldPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(hoverCallback));
    textFieldPattern->InitMouseEvent();
    EXPECT_EQ(textFieldPattern->hasMousePressed_, false);
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InitPanEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto actionStartTask = [](const GestureEvent& info) {};
    auto actionUpdateTask = [](const GestureEvent& info) {};
    auto actionEndTask = [](const GestureEvent& info) {};
    GestureEventNoParameter actionCancelTask;
    textFieldPattern->boxSelectPanEvent_ = AceType::MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    textFieldPattern->InitPanEvent();
    EXPECT_EQ(textFieldPattern->boxSelectPanEvent_, 1);
}

/**
 * @tc.name: OnHover001
 * @tc.desc: Test OnHover
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnHover001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    bool isHover = true;
    HoverInfo info;
    textFieldPattern->OnHover(isHover, info);
    EXPECT_EQ(textFieldPattern->isOnHover_, false);
}

/**
 * @tc.name: UpdateHoverStyle001
 * @tc.desc: Test UpdateHoverStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdateHoverStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->hoverAndPressBgColorEnabled_ = false;
    bool isHover = true;
    textFieldPattern->UpdateHoverStyle(isHover);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: UpdatePressStyle001
 * @tc.desc: Test UpdatePressStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdatePressStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->hoverAndPressBgColorEnabled_ = false;
    bool isPressed = true;
    textFieldPattern->UpdatePressStyle(isPressed);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: Test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    textFieldPattern->HandleMouseEvent(info);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleRightMouseEvent001
 * @tc.desc: Test HandleRightMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleRightMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    MouseInfo info;
    info.SetAction(OHOS::Ace::MouseAction::PRESS);
    textFieldPattern->HandleRightMouseEvent(info);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleLeftMousePressEvent001
 * @tc.desc: Test HandleLeftMousePressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleLeftMousePressEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    MouseInfo info;
    textFieldPattern->isPressSelectedBox_ = true;
    textFieldPattern->hasPreviewText_ = true;
    textFieldPattern->HandleLeftMousePressEvent(info);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleLeftMouseMoveEvent001
 * @tc.desc: Test HandleLeftMouseMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleLeftMouseMoveEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    MouseInfo info;
    textFieldPattern->leftMouseCanMove_ = true;
    textFieldPattern->blockPress_ = false;
    textFieldPattern->contentController_->content_ = u"";
    textFieldPattern->HandleLeftMouseMoveEvent(info);
    EXPECT_EQ(textFieldPattern->showSelect_, true);
}

/**
 * @tc.name: FreeMouseStyleHoldNode001
 * @tc.desc: Test FreeMouseStyleHoldNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, FreeMouseStyleHoldNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset location = { 0, 0 };
    textFieldPattern->FreeMouseStyleHoldNode(location);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    int32_t themeScopeId = 1;
    textFieldPattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithm = AceType::MakeRefPtr<TextAreaLayoutAlgorithm>();
    dirty->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto paragraph1 = AceType::MakeRefPtr<MockParagraph>();
    layoutAlgorithm->paragraph_ = paragraph1;
    auto textDragNode0 = FrameNode::GetOrCreateFrameNode("DragNode", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextDragPattern>(); });
    ASSERT_NE(dirty, nullptr);
    textFieldPattern->dragNode_ = textDragNode0;
    auto dragPattern = textDragNode0->GetPattern<TextDragPattern>();
    ASSERT_NE(dragPattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    dirty->skipMeasureContent_ = false;
    textFieldPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    auto dragParagraph = dragPattern->GetParagraph().Upgrade();
    ASSERT_NE(dragParagraph, nullptr);
    EXPECT_EQ(paragraph1, dragParagraph);

    auto paintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    auto paragraph2 = AceType::MakeRefPtr<MockParagraph>();
    layoutAlgorithm->paragraph_ = paragraph2;
    dragPattern->CreateNodePaintMethod();
    ASSERT_NE(dragPattern->overlayModifier_, nullptr);
    dragPattern->overlayModifier_->SetAnimateFlag(true);
    textFieldPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    ASSERT_NE(dragPattern->animatingParagraph_, nullptr);
    dragParagraph = dragPattern->GetParagraph().Upgrade();
    EXPECT_EQ(paragraph1, dragParagraph);
}
} // namespace OHOS::Ace::NG
