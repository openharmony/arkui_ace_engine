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
    std::cout << "SetCustomKeyboardWithNode00" << std::endl;
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
    EXPECT_EQ(textFieldPattern->textFieldOverlayModifier_, 1);
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
} // namespace OHOS::Ace::NG
