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

void TextSelectControllerTest::SetUp() {}

void TextSelectControllerTest::TearDown() {}

/**
 * @tc.name: FitCaretMetricsToContentRect001
 * @tc.desc: Test FitCaretMetricsToContentRect
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, FitCaretMetricsToContentRect001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->pattern_ = refPattern;
    CaretMetricsF caretMetrics;
    caretMetrics.height = 2.0;
    textSelectController->contentRect_.height_ = 1.0;
    textSelectController->FitCaretMetricsToContentRect(caretMetrics);
    EXPECT_EQ(caretMetrics.height, textSelectController->contentRect_.Height());
}

/**
 * @tc.name: UpdateSelectByOffset001
 * @tc.desc: Test UpdateSelectByOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, UpdateSelectByOffset001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->pattern_ = refPattern;
    auto textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->textRect_ = { 0, 0, 0, 0 };
    Offset localOffset = { 2, 2 };
    textSelectController->UpdateSelectByOffset(localOffset);
    EXPECT_EQ(textSelectController->firstHandleInfo_.index, 0);
}

/**
 * @tc.name: UpdateSelectByOffset002
 * @tc.desc: Test UpdateSelectByOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, UpdateSelectByOffset002, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->pattern_ = refPattern;
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    Offset localOffset = { 2, 2 };
    textSelectController->firstHandleInfo_.index = 2;
    textSelectController->secondHandleInfo_.index = 1;
    textSelectController->contentController_->content_ = u"hhh";
    textSelectController->UpdateSelectByOffset(localOffset);
    EXPECT_EQ(textSelectController->firstHandleInfo_.index, 2);
}

/**
 * @tc.name: MoveCaretAnywhere001
 * @tc.desc: Test MoveCaretAnywhere
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, MoveCaretAnywhere001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    Offset localOffset;
    RectF Offset = { 0, 0, 0, 0 };
    textSelectController->contentController_->content_ = u"hhh";
    textSelectController->CalcCaretOffsetByOffset(localOffset);
    EXPECT_EQ(textSelectController->caretInfo_.rect, Offset);
}

/**
 * @tc.name: FireSelectEvent001
 * @tc.desc: Test FireSelectEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, FireSelectEvent001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    OnAccessibilityCallback onAccessibilityCallback;
    textSelectController->onAccessibilityCallback_ = std::move(onAccessibilityCallback);
    textSelectController->FireSelectEvent();
    EXPECT_EQ(textSelectController->paragraph_, nullptr);
}

/**
 * @tc.name: IsClickAtBoundary001
 * @tc.desc: Test IsClickAtBoundary
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, IsClickAtBoundary001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    textSelectController->pattern_ = refPattern;
    int32_t index = 3;
    Offset touchOffset = { 0, 0 };
    textSelectController->contentController_->content_ = u"hhh";
    auto result = textSelectController->IsClickAtBoundary(index, touchOffset);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IsTouchAtLineEnd001
 * @tc.desc: Test IsTouchAtLineEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, IsTouchAtLineEnd001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);

    textSelectController->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(textSelectController->paragraph_, nullptr);

    Offset localOffset = { 3, 3 };
    textSelectController->contentController_->content_ = u"hhh";
    auto result = textSelectController->IsTouchAtLineEnd(localOffset);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GetTouchLinePos001
 * @tc.desc: Test GetTouchLinePos
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, GetTouchLinePos001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    textSelectController->pattern_ = refPattern;
    textSelectController->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(textSelectController->paragraph_, nullptr);
    Offset localOffset = { 1, 1 };
    textSelectController->contentController_->content_ = u"hhh";
    auto result = textSelectController->GetTouchLinePos(localOffset);
    EXPECT_EQ(result, TouchPosition::LEFT);
}

/**
 * @tc.name: GetTouchLinePos002
 * @tc.desc: Test GetTouchLinePos
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, GetTouchLinePos002, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    textSelectController->pattern_ = refPattern;
    textSelectController->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(textSelectController->paragraph_, nullptr);
    Offset localOffset = { 0, 0 };
    textSelectController->contentController_->content_ = u"";
    auto result = textSelectController->GetTouchLinePos(localOffset);
    EXPECT_EQ(result, TouchPosition::RIGHT);
}

/**
 * @tc.name: UpdateSelectWithBlank001
 * @tc.desc: Test UpdateSelectWithBlank
 * @tc.type: FUNC
 */
HWTEST_F(TextSelectControllerTest, UpdateSelectWithBlank001, TestSize.Level1)
{
    auto refPattern = AceType::MakeRefPtr<TextFieldPattern>();
    ASSERT_NE(refPattern, nullptr);
    WeakPtr<Pattern> pattern = refPattern;
    auto textSelectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    ASSERT_NE(textSelectController, nullptr);
    textSelectController->contentController_ = AceType::MakeRefPtr<ContentController>(textSelectController->pattern_);
    ASSERT_NE(textSelectController->contentController_, nullptr);
    textSelectController->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(textSelectController->paragraph_, nullptr);
    textSelectController->pattern_ = refPattern;
    Offset localOffset = { 2, 2 };
    refPattern->textRect_ = { 1, 1, 1, 1 };
    textSelectController->UpdateSelectWithBlank(localOffset);
    EXPECT_EQ(refPattern->textRect_.width_, 1);
}
} // namespace OHOS::Ace::NG