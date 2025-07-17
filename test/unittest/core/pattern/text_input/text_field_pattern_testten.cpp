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
 * @tc.name: CheckTextAlignByDirection001
 * @tc.desc: Test CheckTextAlignByDirection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CheckTextAlignByDirection001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TextAlign textAlign = TextAlign::CENTER;
    TextDirection direction = TextDirection::RTL;
    textFieldPattern->CheckTextAlignByDirection(textAlign, direction);
    EXPECT_NE(textAlign, TextAlign::START);
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
 * @tc.name: OnThemeScopeUpdate002
 * @tc.desc: Test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnThemeScopeUpdate002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->cleanNodeResponseArea_ =
        AceType::MakeRefPtr<CleanNodeResponseArea>(AIWriteAdapter::WeakClaim(AceType::RawPtr(textFieldPattern)));
    int32_t themeScopeId = 1;
    textFieldPattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: TwinklingByFocus001
 * @tc.desc: Test TwinklingByFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, TwinklingByFocus001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    textFieldPattern->TwinklingByFocus();
    EXPECT_EQ(textFieldPattern->cursorVisible_, false);
}

/**
 * @tc.name: PreferredTextHeight001
 * @tc.desc: Test PreferredTextHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, PreferredTextHeight001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    bool isPlaceholder = true;
    bool isAlgorithmMeasure = true;
    textFieldPattern->PreferredTextHeight(isPlaceholder, isAlgorithmMeasure);
    EXPECT_EQ(textFieldPattern->cursorVisible_, false);
}

/**
 * @tc.name: GetLineBeginPosition001
 * @tc.desc: Test GetLineBeginPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, GetLineBeginPosition001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hhh";
    int32_t originCaretPosition = 1;
    bool needToCheckLineChanged = true;
    auto result = textFieldPattern->GetLineBeginPosition(originCaretPosition, needToCheckLineChanged);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CursorMoveToParagraphEnd001
 * @tc.desc: Test CursorMoveToParagraphEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveToParagraphEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 0;
    auto result = textFieldPattern->CursorMoveToParagraphEnd();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveUpOperation001
 * @tc.desc: Test CursorMoveUpOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveUpOperation001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    auto result = textFieldPattern->CursorMoveUpOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveUpOperation002
 * @tc.desc: Test CursorMoveUpOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveUpOperation002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->textRect_ = { 5, 5, 5, 5 };
    auto result = textFieldPattern->CursorMoveUpOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveDownOperation001
 * @tc.desc: Test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveDownOperation001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 3;
    auto result = textFieldPattern->CursorMoveDownOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CursorMoveDownOperation002
 * @tc.desc: Test CursorMoveDownOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CursorMoveDownOperation002, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 5;
    textFieldPattern->textRect_ = { 1, 1, 1, 1 };
    auto result = textFieldPattern->CursorMoveDownOperation();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: HandleParentGlobalOffsetChange001
 * @tc.desc: Test HandleParentGlobalOffsetChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleParentGlobalOffsetChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectOverlay_->isSingleHandle_ = true;
    textFieldPattern->HandleParentGlobalOffsetChange();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: DeleteBackwardWord002
 * @tc.desc: Test DeleteBackwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteBackwardWord002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->DeleteBackwardWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: DeleteForwardWord002
 * @tc.desc: Test DeleteForwardWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteForwardWord002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->DeleteForwardWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLeftWord001
 * @tc.desc: Test HandleSelectionLeftWord
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLeftWord001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->HandleSelectionLeftWord();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineBegin005
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = -1;
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineBegin006
 * @tc.desc: Test HandleSelectionLineBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineBegin006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->selectController_->caretInfo_.index = 3;
    textFieldPattern->HandleSelectionLineBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionParagraghBegin001
 * @tc.desc: Test HandleSelectionParagraghBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionParagraghBegin001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 0;
    textFieldPattern->HandleSelectionParagraghBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionParagraghBegin002
 * @tc.desc: Test HandleSelectionParagraghBegin
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionParagraghBegin002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 5;
    textFieldPattern->contentController_->content_ = u"hhhhh";
    textFieldPattern->HandleSelectionParagraghBegin();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleSelectionLineEnd001
 * @tc.desc: Test HandleSelectionLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleSelectionLineEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->selectController_->caretInfo_.index = 1;
    textFieldPattern->contentController_->content_ = u"hhhhhhh";
    textFieldPattern->HandleSelectionLineEnd();
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: Test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetSelection001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    SelectionOptions options;
    bool isForward = true;
    textFieldPattern->SetSelection(start, end, options, isForward);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: CalcDecoratorHeight001
 * @tc.desc: Test CalcDecoratorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CalcDecoratorHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RefPtr<FrameNode> decoratorNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    textFieldPattern->CalcDecoratorHeight(decoratorNode);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: TextAreaInputRectUpdate001
 * @tc.desc: Test TextAreaInputRectUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, TextAreaInputRectUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto context = frameNode->GetContext();
    ASSERT_NE(context, nullptr);
    textFieldPattern->textFieldTheme_ = context->GetTheme<TextFieldTheme>(frameNode->GetThemeScopeId());
    RectF rect;
    textFieldPattern->contentController_->content_ = u"";
    textFieldPattern->TextAreaInputRectUpdate(rect);
    EXPECT_EQ(textFieldPattern->selectOverlay_, 1);
}

/**
 * @tc.name: ResetObscureTickCountDown001
 * @tc.desc: Test ResetObscureTickCountDown
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ResetObscureTickCountDown001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textObscured_ = true;
    textFieldPattern->ResetObscureTickCountDown();
    EXPECT_EQ(textFieldPattern->obscureTickCountDown_, 0);
}

/**
 * @tc.name: ToTreeJson001
 * @tc.desc: Test ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ToTreeJson001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    InspectorConfig config;
    textFieldPattern->ToTreeJson(json, config);
    EXPECT_EQ(textFieldPattern->obscureTickCountDown_, 0);
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    ASSERT_NE(textFieldPattern->customKeyboard_, nullptr);
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->DumpAdvanceInfo();
    EXPECT_EQ(textFieldPattern->isCustomKeyboardAttached_, false);
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: Test DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DumpAdvanceInfo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->customKeyboardBuilder_ = []() {};
    textFieldPattern->DumpAdvanceInfo();
    EXPECT_EQ(textFieldPattern->isCustomKeyboardAttached_, false);
}

/**
 * @tc.name: CheckAutoSave001
 * @tc.desc: Test CheckAutoSave
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CheckAutoSave001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hh";
    auto result = textFieldPattern->CheckAutoSave();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CheckPasswordAreaState002
 * @tc.desc: Test CheckPasswordAreaState
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, CheckPasswordAreaState002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    textFieldPattern->showPasswordState_ = false;
    textFieldPattern->CheckPasswordAreaState();
    EXPECT_EQ(textFieldPattern->responseArea_, 0);
}

/**
 * @tc.name: UpdateFocusForward001
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdateFocusForward001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto focusHub = textFieldPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    textFieldPattern->focusIndex_ = FocuseIndex::TEXT;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusForward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateFocusForward002
 * @tc.desc: Test UpdateFocusForward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdateFocusForward002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto focusHub = textFieldPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    textFieldPattern->focusIndex_ = FocuseIndex::CANCEL;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusForward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateFocusBackward001
 * @tc.desc: Test UpdateFocusBackward
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, UpdateFocusBackward001, TestSize.Level1)
{
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->focusIndex_ = FocuseIndex::UNIT;
    textFieldPattern->responseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(textFieldPattern);
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    auto result = textFieldPattern->UpdateFocusBackward();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PaintUnitRect001
 * @tc.desc: Test PaintUnitRect
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, PaintUnitRect001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->PaintUnitRect();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnWindowSizeChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t width = 1;
    int32_t height = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::ROTATION;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, true);
    textFieldPattern->OnWindowSizeChanged(width, height, type);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnWindowSizeChanged002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t width = 1;
    int32_t height = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::ROTATION;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->OnWindowSizeChanged(width, height, type);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange001
 * @tc.desc: Test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, TriggerAvoidOnCaretChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RefPtr<SafeAreaManager> safeAreaManager_ = nullptr;
    textFieldPattern->TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange002
 * @tc.desc: Test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, TriggerAvoidOnCaretChange002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: ConvertGlobalToLocalOffset001
 * @tc.desc: Test ConvertGlobalToLocalOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ConvertGlobalToLocalOffset001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset globalOffset;
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->ConvertGlobalToLocalOffset(globalOffset);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: NeedDrawPreviewText001
 * @tc.desc: Test NeedDrawPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, NeedDrawPreviewText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->hasPreviewText_ = false;
    textFieldPattern->selectController_->caretInfo_.index = 1;
    auto result = textFieldPattern->NeedDrawPreviewText();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate002
 * @tc.desc: Test OnTextGestureSelectionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionUpdate002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentScroller_.isScrolling = true;
    textFieldPattern->contentController_->content_ = u"hhh";
    int32_t start = 1;
    int32_t end = 1;
    TouchEventInfo info = TouchEventInfo("info");
    TouchLocationInfo tinfo("test", 0);
    info.touches_.push_back(tinfo);
    textFieldPattern->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd001
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    textFieldPattern->contentRect_.width_ = 1;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd002
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionEnd002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.height_ = 2;
    textFieldPattern->contentRect_.width_ = 1;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd003
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionEnd003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = false;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.width_ = 2;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: OnTextGestureSelectionEnd004
 * @tc.desc: Test OnTextGestureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, OnTextGestureSelectionEnd004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchLocationInfo locationInfo(0);
    textFieldPattern->contentScroller_.isScrolling = true;
    locationInfo.localLocation_.deltaY_ = 1;
    textFieldPattern->contentRect_.width_ = 2;
    textFieldPattern->OnTextGestureSelectionEnd(locationInfo);
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: Test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, IsShowAIWrite001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    ASSERT_NE(textFieldTheme, nullptr);
    textFieldTheme->aiWriteBundleName_ = "hhh";
    textFieldTheme->aiWriteAbilityName_ = "";
    auto result = textFieldPattern->IsShowAIWrite();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleOnAIWrite001
 * @tc.desc: Test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, HandleOnAIWrite001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto aiWriteAdapter = AceType::MakeRefPtr<AIWriteAdapter>();
    textFieldPattern->aiWriteAdapter_ = aiWriteAdapter;
    textFieldPattern->HandleOnAIWrite();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: InsertOrDeleteSpace002
 * @tc.desc: Test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, InsertOrDeleteSpace002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->contentController_->content_ = u"hh";
    int32_t index = 0;
    auto result = textFieldPattern->InsertOrDeleteSpace(index);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DeleteTextRange001
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteTextRange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = 1;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: DeleteTextRange002
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteTextRange002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = -1;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: DeleteTextRange003
 * @tc.desc: Test DeleteTextRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, DeleteTextRange003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    int32_t start = 2;
    int32_t end = 2;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    textFieldPattern->contentController_->content_ = u"h";
    textFieldPattern->DeleteTextRange(start, end, direction);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: GetAcceptedTouchLocationInfo001
 * @tc.desc: Test GetAcceptedTouchLocationInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, GetAcceptedTouchLocationInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    TouchEventInfo info = TouchEventInfo("info");
    info.changedTouches_.clear();
    textFieldPattern->moveCaretState_.isMoveCaret = false;
    textFieldPattern->isSelecting_ = true;
    auto result = textFieldPattern->GetAcceptedTouchLocationInfo(info);
    EXPECT_EQ(result, std::nullopt);
}

/**
 * @tc.name: GetPaddingBottom001
 * @tc.desc: Test GetPaddingBottom
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, GetPaddingBottom001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto result = textFieldPattern->GetPaddingBottom();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ExecuteInputCommand001
 * @tc.desc: Test ExecuteInputCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ExecuteInputCommand001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    InputCommandInfo info;
    info.reason = InputReason::IME;
    textFieldPattern->ExecuteInputCommand(info);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: ExecuteInputCommand002
 * @tc.desc: Test ExecuteInputCommand
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, ExecuteInputCommand002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    InputCommandInfo info;
    info.reason = InputReason::AI_WRITE;
    info.deleteRange.start = 1;
    info.deleteRange.end = 1;
    textFieldPattern->ExecuteInputCommand(info);
    EXPECT_EQ(textFieldPattern->contentController_, 1);
}

/**
 * @tc.name: SetIsEnableSubWindowMenu001
 * @tc.desc: Test SetIsEnableSubWindowMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetIsEnableSubWindowMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    RectF handleRect;
    textFieldPattern->selectOverlay_->OnHandleMove(handleRect, false);
    textFieldPattern->SetIsEnableSubWindowMenu();
    EXPECT_EQ(textFieldPattern->selectOverlay_->isHostNodeEnableSubWindowMenu_, true);
}

/**
 * @tc.name: NotifyKeyboardClosedByUser001
 * @tc.desc: Test NotifyKeyboardClosedByUser
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, NotifyKeyboardClosedByUser001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->NotifyKeyboardClosedByUser();
    EXPECT_EQ(textFieldPattern->isKeyboardClosedByUser_, false);
}

/**
 * @tc.name: NotifyKeyboardClosed001
 * @tc.desc: Test NotifyKeyboardClosed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, NotifyKeyboardClosed001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->customKeyboardBuilder_ = nullptr;
    textFieldPattern->customKeyboard_ = nullptr;
    textFieldPattern->NotifyKeyboardClosed();
    EXPECT_EQ(textFieldPattern->selectController_, 1);
}

/**
 * @tc.name: BetweenSelectedPosition002
 * @tc.desc: Test BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, BetweenSelectedPosition002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    Offset globalOffset = { 1, 1 };
    textFieldPattern->selectController_->firstHandleInfo_.index = 1;
    textFieldPattern->selectController_->secondHandleInfo_.index = 2;
    auto result = textFieldPattern->BetweenSelectedPosition(globalOffset);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SetUnitNode005
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    textFieldPattern->unitNode_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: SetUnitNode006
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ =
        AceType::MakeRefPtr<PasswordResponseArea>(textFieldPattern, textFieldPattern->GetTextObscured());
    ASSERT_NE(textFieldPattern->responseArea_, nullptr);
    textFieldPattern->unitNode_ = nullptr;
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, 1);
}

/**
 * @tc.name: SetUnitNode007
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    textFieldPattern->unitNode_ =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, nullptr);
}

/**
 * @tc.name: SetUnitNode008
 * @tc.desc: Test SetUnitNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, SetUnitNode008, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->responseArea_ = nullptr;
    textFieldPattern->unitNode_ = nullptr;
    RefPtr<NG::UINode> unitNode =
        AceType::DynamicCast<NG::UINode>(AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>()));
    textFieldPattern->SetUnitNode(unitNode);
    EXPECT_EQ(textFieldPattern->responseArea_, nullptr);
}

/**
 * @tc.name: IsStopEditWhenCloseKeyboard001
 * @tc.desc: Test IsStopEditWhenCloseKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestten, IsStopEditWhenCloseKeyboard001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    auto result = textFieldPattern->IsStopEditWhenCloseKeyboard();
    EXPECT_EQ(result, true);
}
} // namespace OHOS::Ace::NG
