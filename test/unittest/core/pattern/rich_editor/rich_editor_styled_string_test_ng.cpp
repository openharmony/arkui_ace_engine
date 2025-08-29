/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorStyledStringTestNg : public RichEditorStyledStringCommonTestNg {};

/**
 * @tc.name: RichEditorModel001
 * @tc.desc: Test events not supported in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, RichEditorModel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create richEditorModel in styledString mode
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.isStyledStringMode_ = true;
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. init events not supported in styledString mode
     */
    auto onSelectFunc = [](const BaseEventInfo* info) {};
    richEditorModel.SetOnSelect(std::move(onSelectFunc));
    auto aboutToIMEInputFunc = [](const RichEditorInsertValue&) { return true; };
    richEditorModel.SetAboutToIMEInput(std::move(aboutToIMEInputFunc));
    auto iMEInputCompleteFunc = [](const RichEditorAbstractSpanResult&) {};
    richEditorModel.SetOnIMEInputComplete(std::move(iMEInputCompleteFunc));
    auto aboutToDeleteFunc = [](const RichEditorDeleteValue&) { return true; };
    richEditorModel.SetAboutToDelete(std::move(aboutToDeleteFunc));
    auto deleteCompleteFunc = []() {};
    richEditorModel.SetOnDeleteComplete(std::move(deleteCompleteFunc));
    auto onWillChange = [](const RichEditorChangeValue& beforeResult) { return false; };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    auto onDidChange = [](const RichEditorChangeValue& afterResult) {};
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step3. verify whether the event settings have failed
     */
    EXPECT_FALSE(eventHub->onSelect_);
    EXPECT_FALSE(eventHub->aboutToIMEInput_);
    EXPECT_FALSE(eventHub->onIMEInputComplete_);
    EXPECT_FALSE(eventHub->aboutToDelete_);
    EXPECT_FALSE(eventHub->onDeleteComplete_);
    EXPECT_FALSE(eventHub->onWillChange_);
    EXPECT_FALSE(eventHub->onDidChange_);
}

/**
 * @tc.name: StyledStringController001
 * @tc.desc: Test SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);

    /**
     * @tc.steps: step3. set styledString
     */
    styledStringController->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);
    EXPECT_EQ(richEditorPattern->dataDetectorAdapter_->textForAI_, INIT_STRING_1);
    auto spanItem = richEditorPattern->spans_.front();
    auto& fontStyle = spanItem->fontStyle;
    ASSERT_NE(fontStyle, nullptr);
    EXPECT_EQ(fontStyle->GetFontWeight(), FONT_WEIGHT_BOLD);
    EXPECT_EQ(fontStyle->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(fontStyle->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(fontStyle->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(fontStyle->GetTextColor(), OHOS::Ace::Color::RED);
    EXPECT_EQ(fontStyle->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(fontStyle->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(fontStyle->GetTextDecorationStyle(), TextDecorationStyle::WAVY);
    EXPECT_EQ(fontStyle->GetLetterSpacing(), LETTER_SPACING);
    EXPECT_EQ(fontStyle->GetTextShadow(), SHADOWS);

    auto& textLineStyle = spanItem->textLineStyle;
    EXPECT_EQ(textLineStyle->GetBaselineOffset(), TEST_BASELINE_OFFSET);
    EXPECT_EQ(textLineStyle->GetTextAlign(), TextAlign::END);
    EXPECT_EQ(textLineStyle->GetMaxLines(), TEST_MAX_LINE);
    EXPECT_EQ(textLineStyle->GetTextOverflow(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(textLineStyle->GetLeadingMargin(), TEST_LEADING_MARGIN);
    EXPECT_EQ(textLineStyle->GetWordBreak(), WordBreak::BREAK_ALL);
    EXPECT_EQ(textLineStyle->GetTextIndent(), TEST_TEXT_INDENT);
    EXPECT_EQ(textLineStyle->GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(textLineStyle->GetParagraphSpacing(), std::nullopt);
}

/**
 * @tc.name: StyledStringController002
 * @tc.desc: Test SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with image
     */
    auto mutableStr = CreateImageStyledString();

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step3. set styledString
     */
    styledStringController->SetStyledString(mutableStr);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 1);
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(richEditorPattern->spans_.front());
    ASSERT_NE(imageSpanItem, nullptr);
    auto imageSpanoptions = imageSpanItem->options;
    auto imageAttr = imageSpanoptions.imageAttribute.value();
    EXPECT_EQ(imageAttr.size->GetSize(), TEST_IMAGE_SIZE.GetSize());
    EXPECT_EQ(imageAttr.verticalAlign.value(), VerticalAlign::BOTTOM);
    EXPECT_EQ(imageAttr.objectFit.value(), ImageFit::COVER);
    auto& padding = imageAttr.paddingProp.value();
    PaddingProperty paddings;
    paddings.SetEdges(TEST_PADDING_CALC);
    EXPECT_EQ(padding.ToString(), paddings.ToString());
    auto& margin = imageAttr.marginProp.value();
    MarginProperty margins;
    margins.SetEdges(TEST_MARGIN_CALC);
    EXPECT_EQ(margin.ToString(), margins.ToString());
    EXPECT_EQ(imageAttr.borderRadius.value(), TEST_BORDER_RADIUS);
}

/**
 * @tc.name: StyledStringController003
 * @tc.desc: Test SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan
     */
    auto mutableStr = CreateCustomSpanStyledString();

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);

    /**
     * @tc.steps: step3. set styledString
     */
    styledStringController->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 1);
    auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(richEditorPattern->spans_.front());
    EXPECT_NE(customSpanItem, nullptr);
}

/**
 * @tc.name: StyledStringController004
 * @tc.desc: Test SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step3. set styledString
     */
    styledStringController->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 9);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 1);
    auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(richEditorPattern->spans_.front());
    EXPECT_NE(customSpanItem, nullptr);
}

/**
 * @tc.name: StyledStringController005
 * @tc.desc: Test GetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. get styledString
     */
    auto styledString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    ASSERT_NE(styledString, nullptr);
    EXPECT_EQ(styledString->GetString(), richEditorPattern->styledString_->GetString());
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->InsertValue(INIT_STRING_2);
    styledString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    ASSERT_NE(styledString, nullptr);
    EXPECT_EQ(styledString->GetString(), richEditorPattern->styledString_->GetString());
    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->DeleteBackward(1);
    styledString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    ASSERT_NE(styledString, nullptr);
    EXPECT_EQ(styledString->GetString(), richEditorPattern->styledString_->GetString());
    richEditorPattern->caretPosition_ = 3;
    richEditorPattern->DeleteBackward(1);
    styledString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    ASSERT_NE(styledString, nullptr);
    EXPECT_EQ(styledString->GetString(), richEditorPattern->styledString_->GetString());
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteBackward(1);
    styledString = AceType::DynamicCast<MutableSpanString>(styledStringController->GetStyledString());
    ASSERT_NE(styledString, nullptr);
    EXPECT_EQ(styledString->GetString(), richEditorPattern->styledString_->GetString());
}

/**
 * @tc.name: StyledStringController006
 * @tc.desc: Test OnWillChange.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. SetOnWillChange
     */
    auto onWillChange = [](const StyledStringChangeValue& changeValue) {
        onStyledStringWillChangeValue = changeValue;
        return true;
    };
    styledStringController->SetOnWillChange(onWillChange);

    /**
     * @tc.steps: step3. addition、deletion and substitution in styledString
     */
    std::u16string replacementString;
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().start, 5);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().end, 5);
    replacementString =
        AceType::DynamicCast<MutableSpanString>(onStyledStringWillChangeValue.GetReplacementString())->GetU16string();
    EXPECT_EQ(replacementString, INIT_STRING_3);

    richEditorPattern->caretPosition_ = 13;
    richEditorPattern->DeleteBackward(6);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().start, 7);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().end, 13);
    replacementString =
        AceType::DynamicCast<MutableSpanString>(onStyledStringWillChangeValue.GetReplacementString())->GetU16string();
    EXPECT_TRUE(replacementString.empty());

    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().start, 3);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().end, 4);
    replacementString =
        AceType::DynamicCast<MutableSpanString>(onStyledStringWillChangeValue.GetReplacementString())->GetU16string();
    EXPECT_EQ(replacementString, INIT_STRING_3);

    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().start, 0);
    EXPECT_EQ(onStyledStringWillChangeValue.GetRangeBefore().end, 0);
}

/**
 * @tc.name: StyledStringController007
 * @tc.desc: Test OnDidChange.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. SetOnDidChange
     */
    auto onDidChange = [](const StyledStringChangeValue& changeValue) {
        onStyledStringDidChangeValue = changeValue;
    };
    styledStringController->SetOnDidChange(onDidChange);

    /**
     * @tc.steps: step3. addition、deletion and substitution in styledString
     */
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().start, 5);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().end, 5);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().start, 5);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().end, 11);

    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->ResetSelection();
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().start, 4);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().end, 5);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().start, 4);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().end, 4);

    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().start, 3);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeBefore().end, 4);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().start, 3);
    EXPECT_EQ(onStyledStringDidChangeValue.GetRangeAfter().end, 9);
}

/**
 * @tc.name: StyledStringController008
 * @tc.desc: Test SetTypingStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. set typingStyle
     */
    SetTypingStyle();

    /**
     * @tc.steps: step4. insert value
     */
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(INIT_STRING_3);
    auto spanItem = richEditorPattern->spans_.front();
    auto& fontStyle = spanItem->fontStyle;
    ASSERT_NE(fontStyle, nullptr);
    EXPECT_EQ(fontStyle->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(fontStyle->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(fontStyle->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(fontStyle->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(fontStyle->GetTextDecorationFirst(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(fontStyle->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(fontStyle->GetLetterSpacing(), LETTER_SPACING);
    EXPECT_EQ(fontStyle->GetTextShadow(), SHADOWS);
}

/**
 * @tc.name: StyledStringController009
 * @tc.desc: Test SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);

    /**
     * @tc.steps: step3. SetOnWillChange
     */
    auto onWillChange = [styledStringController, mutableStr](const StyledStringChangeValue& changeValue) {
        onStyledStringWillChangeValue = changeValue;
        styledStringController->SetStyledString(mutableStr);
        return false;
    };
    styledStringController->SetOnWillChange(onWillChange);

    /**
     * @tc.steps: step4. enable preview text
     */
    richEditorPattern->previewTextRecord_.previewContent = u"test";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 4;

    /**
     * @tc.steps: step3. insert value
     */
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(INIT_STRING_2);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);
}

/**
 * @tc.name: StyledStringController010
 * @tc.desc: Test textVerticalAlign.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringController010, TestSize.Level1)
{
    /*
     *@tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);
    /**
     *@tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);
    EXPECT_EQ(richEditorPattern->dataDetectorAdapter_->textForAI_, INIT_STRING_1);
    auto spanItem = richEditorPattern->spans_.front();
    auto& textLineStyle = spanItem->textLineStyle;
    EXPECT_NE(textLineStyle->GetTextVerticalAlign(), std::nullopt);
}

/**
 * @tc.name: StyledStringInsertValue001
 * @tc.desc: Test insert value in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringInsertValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. insert value
     */
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 15);

    richEditorPattern->caretPosition_ = 15;
    richEditorPattern->InsertValue(INIT_STRING_2);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 27);

    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->InsertValue(INIT_STRING_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 34);
}

/**
 * @tc.name: StyledStringInsertValue002
 * @tc.desc: Test insert value in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringInsertValue002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. insert value
     */
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->InsertValue(INIT_STRING_3);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 13);

    richEditorPattern->textSelector_.Update(2, 4);
    richEditorPattern->InsertValue(INIT_STRING_2);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 23);

    richEditorPattern->textSelector_.Update(13, 14);
    richEditorPattern->InsertValue(INIT_STRING_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 29);
}

/**
 * @tc.name: CustomSpan001
 * @tc.desc: Test caret and handles with customSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CustomSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    mutableStr->AppendSpanString(mutableTextStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. add paragraph
     */
    CaretMetricsF caretMetricsLeft = { OffsetF(0, 0), 50.0f };
    CaretMetricsF caretMetricsRight = { OffsetF(100.f, 0), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 8,
        .testCursorItems = { { 0, caretMetricsLeft, caretMetricsLeft}, {1, caretMetricsRight, caretMetricsRight} } };
    AddParagraph(paragraphItem);
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    richEditorNode_->Measure(layoutConstraintF);
    richEditorNode_->Layout();

    /**
     * @tc.steps: step4. calculate caret and handles with customSpan
     */
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    auto [caretOffset, caretHeight] = richEditorPattern->CalculateCaretOffsetAndHeight();
    EXPECT_EQ(caretOffset, OffsetF(100.f, 0));
    EXPECT_EQ(caretHeight, 50.0f);
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), 50.f };
    auto firstHandleOffset = OffsetF(0 - handlePaintSize.Width() / 2.0f, 0);
    auto secondHandleOffset = OffsetF(100.f - handlePaintSize.Width() / 2.0f, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle, RectF(firstHandleOffset, handlePaintSize));
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle, RectF(secondHandleOffset, handlePaintSize));
}

/**
 * @tc.name: FromStyledStrign001
 * @tc.desc: Test FromStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, FromStyledString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller and set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    styledStringController->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. FromStyledString
     */
    auto info = richEditorPattern->FromStyledString(mutableStr);
    EXPECT_EQ(info.selection_.resultObjects.size(), mutableStr->GetSpanItems().size());
}

/**
 * @tc.name: CopySpanStyle001
 * @tc.desc: test CopySpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CopySpanStyle001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> source = AceType::MakeRefPtr<SpanItem>();
    source->textLineStyle->UpdateTextAlign(TextAlign::CENTER);
    source->textLineStyle->UpdateMaxLines(1);
    layoutAlgorithm->CopySpanStyle(source, AceType::MakeRefPtr<SpanItem>());
    EXPECT_TRUE(source->textLineStyle->HasTextAlign());
}

/**
 * @tc.name: CopySpanStyle002
 * @tc.desc: test CopySpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CopySpanStyle002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SpanItem> source = AceType::MakeRefPtr<SpanItem>();
    layoutAlgorithm->CopySpanStyle(source, AceType::MakeRefPtr<SpanItem>());
    EXPECT_FALSE(source->textLineStyle->HasTextAlign());
}

/**
 * @tc.name: CopySpanStyle003
 * @tc.desc: test CopySpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CopySpanStyle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto source = AceType::MakeRefPtr<SpanItem>();
    auto target = AceType::MakeRefPtr<SpanItem>();

    LeadingMargin leadingMargin;
    source->textLineStyle->UpdateLeadingMargin(leadingMargin);
    source->fontStyle->UpdateFontSize(FONT_SIZE_VALUE);
    source->textLineStyle->UpdateLineHeight(LINE_HEIGHT_VALUE);

    layoutAlgorithm->CopySpanStyle(source, target);
    EXPECT_EQ(target->fontStyle->GetFontSize(), FONT_SIZE_VALUE);
}

/**
 * @tc.name: CopySpanStyle004
 * @tc.desc: test CopySpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CopySpanStyle004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto source = AceType::MakeRefPtr<SpanItem>();
    auto target = AceType::MakeRefPtr<SpanItem>();

    LeadingMargin leadingMargin;
    source->textLineStyle->UpdateLeadingMargin(leadingMargin);
    source->fontStyle->UpdateFontSize(FONT_SIZE_VALUE);
    source->textLineStyle->UpdateLineHeight(LINE_HEIGHT_VALUE);

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    style.SetFontSize(FONT_SIZE_VALUE);

    layoutAlgorithm->CopySpanStyle(source, target);
    EXPECT_EQ(target->fontStyle->GetFontSize(), FONT_SIZE_VALUE);
}

/**
 * @tc.name: GetSelection001
 * @tc.desc: test GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, GetSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with text
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);

    /**
     * @tc.steps: step2. get richEditor styledString controller , set styledString and GetSelection
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    auto testRangeInfo = styledStringController->GetSelection();
    ASSERT_EQ(testRangeInfo.start_, 0);
}

/**
 * @tc.name: InsertValueInStyledString001
 * @tc.desc: test RichEditorPattern InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, InsertValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);

    UpdateSpanStyle updateSpanStyle;

    std::u16string content = u"TEST123";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(content);

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString(u"abc");

    richEditorPattern->typingStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->InsertValueInStyledString(u"abc");

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    richEditorPattern->InsertValueInStyledString(u"abc");

    richEditorPattern->typingStyle_ = updateSpanStyle;
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->InsertValueInStyledString(u"abc");

    ASSERT_EQ(richEditorPattern->typingTextStyle_.has_value(), true);
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test RichEditorPattern DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, DeleteValueInStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    richEditorPattern->caretVisible_ = false;
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, true);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->DeleteValueInStyledString(0, 10, true);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, false);
    richEditorPattern->previewLongPress_ = false;
    richEditorPattern->DeleteValueInStyledString(0, 10, false);
    ASSERT_EQ(!richEditorPattern->BeforeStyledStringChange(0, 10, u""), false);
}

/**
 * @tc.name: InsertStyledStringByPaste001
 * @tc.desc: test RichEditorPattern InsertStyledStringByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, InsertStyledStringByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern and controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. add span and select text
     */
    richEditorPattern->InsertValue(u"test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    std::u16string data = u"abc";
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(data);
    richEditorPattern->InsertStyledStringByPaste(spanString);

    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: UpdateSpanStyle001
 * @tc.desc: test UpdateSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, UpdateSpanStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorController->updateSpanStyle_.useThemeFontColor = false;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"UpdateSpanStyle");
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_FALSE(richEditorPattern->updateSpanStyle_.useThemeFontColor);
}

/**
 * @tc.name: FromStyledString002
 * @tc.desc: test FromStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, FromStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    Selection selection;
    RefPtr<SpanString> spanString;

    selection = richEditorPattern->FromStyledString(spanString).GetSelection();
    EXPECT_EQ(selection.selection[0], 0);
    EXPECT_EQ(selection.selection[1], 0);

    spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    selection = richEditorPattern->FromStyledString(spanString).GetSelection();
    EXPECT_EQ(selection.selection[0], 0);
    EXPECT_EQ(selection.selection[1], INIT_VALUE_1.size());

    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    spanString->AppendSpanItem(imageSpanItem);
    selection = richEditorPattern->FromStyledString(spanString).GetSelection();
    EXPECT_EQ(selection.selection[0], 0);
    EXPECT_EQ(selection.selection[1], 0);
}

/**
 * @tc.name: FromStyledString003
 * @tc.desc: test FromStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, FromStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    Selection selection;
    RefPtr<SpanString> spanString;
    spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    spanString->spans_.front() = nullptr;
    spanString->spans_.emplace_back();

    selection = richEditorPattern->FromStyledString(spanString).GetSelection();
    EXPECT_EQ(selection.selection[0], 0);
    EXPECT_EQ(selection.selection[1], 0);
}

/**
 * @tc.name: ToStyledString001
 * @tc.desc: Test spans to styledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ToStyledString001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(options);

    /**
     * @tc.steps: step2. test ToStyledString
     */
    auto spanString = richEditorPattern->ToStyledString(0, 8);
    ASSERT_NE(spanString, nullptr);
    EXPECT_EQ(spanString->GetSpanItems().size(), 2);
}

/**
 * @tc.name: ToStyledString002
 * @tc.desc: test ToStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ToStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    int32_t start = 3;
    int32_t end = -2;
    AddSpan("test");
    RefPtr<SpanString> res = richEditorPattern->ToStyledString(start, end);
    ASSERT_NE(res, nullptr);
}

/**
 * @tc.name: ToStyledString003
 * @tc.desc: Test spans to styledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ToStyledString003, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_4;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_5;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_6;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_7;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_8;
    richEditorController->AddTextSpan(options);

    /**
     * @tc.steps: step2. test ToStyledString after add spans
     */
    auto spanString = richEditorPattern->ToStyledString(3, 4);
    ASSERT_NE(spanString, nullptr);
    EXPECT_EQ(spanString->GetSpanItems().size(), 1);
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    options.value = INIT_VALUE_4;
    richEditorController->AddTextSpan(options);
    auto spanString2 = richEditorPattern->ToStyledString(3, 4);
    ASSERT_NE(spanString2, nullptr);
    EXPECT_EQ(spanString2->GetSpanItems().size(), 1);
}

/**
 * @tc.name: CreateStyledStringByTextStyle
 * @tc.desc: test CreateStyledStringByTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CreateStyledStringByTextStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step3. add text
     */
    AddSpan(INIT_VALUE_1);
    EXPECT_EQ(richEditorNode_->children_.size(), 1);

    /**
     * @tc.steps: step4. initalize style
     */
    TextStyle textStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;

    /**
     * @tc.steps: step5. test CreateStyledStringByTextStyle
     */
    auto& styledString = richEditorPattern->styledString_;
    richEditorPattern->styleManager_->CreateStyledStringByTypingStyle(INIT_VALUE_2, styledString, 0, 0);
    auto spanItem = richEditorPattern->spans_.back();
    auto& fontStyle = spanItem->fontStyle;
    ASSERT_NE(fontStyle, nullptr);
    EXPECT_EQ(fontStyle->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(fontStyle->GetTextColor(), TEXT_COLOR_VALUE);
}

/**
 * @tc.name: CreateStyledStringByTextStyle002
 * @tc.desc: test CreateStyledStringByTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CreateStyledStringByTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step3. add two text span
     */
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_3);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    EXPECT_EQ(contentNode->children_.size(), 2);

    /**
     * @tc.steps: step4. initalize style
     */
    TextStyle textStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);

    /**
     * @tc.steps: step5. test CreateStyledStringByTextStyle
     */
    auto& styledString = richEditorPattern->styledString_;
    richEditorPattern->styleManager_->CreateStyledStringByTypingStyle(INIT_VALUE_2, styledString, 0, 0);
    auto spanItemFirst = richEditorPattern->spans_.front();
    auto& fontStyleFirst = spanItemFirst->fontStyle;
    ASSERT_NE(fontStyleFirst, nullptr);
    EXPECT_EQ(fontStyleFirst->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(fontStyleFirst->GetFontFamily()->size(), 1);
    EXPECT_EQ(fontStyleFirst->GetTextColor(), TEXT_COLOR_VALUE);
    auto spanItemSecond = richEditorPattern->spans_.back();
    auto& fontStyleSecond = spanItemSecond->fontStyle;
    ASSERT_NE(fontStyleSecond, nullptr);
    EXPECT_EQ(fontStyleSecond->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(fontStyleSecond->GetFontFamily()->size(), 1);
    EXPECT_EQ(fontStyleSecond->GetTextColor(), TEXT_COLOR_VALUE);
}

/**
 * @tc.name: StyledStringDeleteBackward001
 * @tc.desc: Test delete backward in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringDeleteBackward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. delete backward
     */
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 8);

    richEditorPattern->caretPosition_ = 3;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
}

/**
 * @tc.name: StyledStringDeleteBackward002
 * @tc.desc: Test delete backward in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringDeleteBackward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. delete backward
     */
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    richEditorPattern->textSelector_.Update(2, 5);
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);

    richEditorPattern->textSelector_.Update(1, 3);
    richEditorPattern->caretPosition_ = 3;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 2);
}

/**
 * @tc.name: StyledStringDeleteForward001
 * @tc.desc: Test delete forward in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringDeleteForward001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. delete forward
     */
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 8);

    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 6);
}

/**
 * @tc.name: StyledStringDeleteForward002
 * @tc.desc: Test delete backward in styledString mode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringDeleteForward002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with customSpan、image and text
     */
    auto mutableStr = CreateCustomSpanStyledString();
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    mutableStr->AppendSpanString(mutableTextStr);
    mutableStr->InsertSpanString(3, mutableImageStr);

    /**
     * @tc.steps: step2. set styledString
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetStyledString(mutableStr);

    /**
     * @tc.steps: step3. delete forward
     */
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    richEditorPattern->textSelector_.Update(2, 5);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);

    richEditorPattern->textSelector_.Update(1, 3);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 2);
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test DeleteValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, DeleteValueInStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    richEditorPattern->previewLongPress_ = true;
    auto focusHub = richEditorPattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    richEditorPattern->DeleteValueInStyledString(0, 10, true, false);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: DeleteTextDecorationType
 * @tc.desc: Test deleteDecorationType of DecorationSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, DeleteTextDecorationType, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize a spanString and AddSpan
     * @tc.expected: The SpanString and style should be successfully created and applied
     */
    std::string buffer;
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({ TextDecoration::UNDERLINE, TextDecoration::OVERLINE }), Color::RED,
        TextDecorationStyle::WAVY, 1.0f, std::optional<TextDecorationOptions>(), 0, 1);
    decorationSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    buffer.clear();
    buffer = decorationSpan->ToString();
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.find("DecorationSpan"), 0);

    /**
     * @tc.steps2:remove overline to decorationSpan
     * @tc.expected: The decorationSpan types removed Overline ,size equal 1
     */
    decorationSpan->RemoveTextDecorationType(TextDecoration::OVERLINE);
    EXPECT_EQ(decorationSpan->GetTextDecorationTypes().size(), 1);

    /**
     * @tc.steps3:remove none to decorationSpan
     * @tc.expected: The decorationSpan types can remove None, size equal 1
     */
    decorationSpan->RemoveTextDecorationType(TextDecoration::NONE);
    EXPECT_EQ(decorationSpan->GetTextDecorationTypes().size(), 1);
}

/**
 * @tc.name: InsertValueInStyledString002
 * @tc.desc: test InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, InsertValueInStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->InsertValueInStyledString(PREVIEW_TEXT_VALUE1);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: InsertValueInStyledString003
 * @tc.desc: test RichEditorPattern InsertValueInStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, InsertValueInStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto host = richEditorPattern->GetHost();
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    richEditorPattern->FireOnSelectionChange(-1, 0);
    richEditorPattern->FireOnSelectionChange(0, -1);
    richEditorPattern->FireOnSelectionChange(-1, -1);
    ASSERT_EQ(richEditorPattern->HasFocus(), true);
}

/**
 * @tc.name: CreatePasteCallback001
 * @tc.desc: test CreatePasteCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, CreatePasteCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    /**
     * @tc.steps: step1. CreatePasteCallback
     */
    auto pasteCallback = richEditorPattern->CreatePasteCallback();
    /**
     * @tc.steps: step2. value from clipBoard
     */
    auto mutableTextStr = CreateTextStyledString(INIT_U16STRING_1);
    auto mutableImageStr = CreateImageStyledString();
    std::vector<uint8_t> data1;
    std::vector<uint8_t> data2;
    mutableTextStr->EncodeTlv(data1);
    mutableImageStr->EncodeTlv(data2);
    std::vector<std::vector<uint8_t>> arrs = { std::move(data1), std::move(data2) };
    string text = UtfUtils::Str16ToStr8(INIT_U16STRING_1);
    bool isMulitiTypeRecord = true;
    /**
     * @tc.steps: step3. test spanStringMode
     */
    richEditorPattern->spans_.clear();
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    pasteCallback(arrs, text, isMulitiTypeRecord);
    EXPECT_EQ(2, richEditorPattern->spans_.size());
}

/**
 * @tc.name: ProcessStyledString001
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ProcessStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    ASSERT_EQ(richEditorPattern->spans_.empty(), true);
}

/**
 * @tc.name: ProcessStyledString002
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ProcessStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->textForDisplay_ = INIT_VALUE_1;
    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, ProcessStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);

    richEditorPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    richEditorPattern->ProcessStyledString();

    EXPECT_FALSE(richEditorPattern->spans_.empty());
}

/**
 * @tc.name: ProcessStyledString003
 * @tc.desc: test ProcessStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringTestNg, StyledStringCreateTest, TestSize.Level1)
{
    RefPtr<RichEditorPattern> pattern;
    bool isStyledStringMode;

    isStyledStringMode = false;
    pattern = AceType::MakeRefPtr<RichEditorPattern>(isStyledStringMode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isSpanStringMode_, false);
    EXPECT_EQ(pattern->styledString_, nullptr);

    isStyledStringMode = true;
    pattern = AceType::MakeRefPtr<RichEditorPattern>(isStyledStringMode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->isSpanStringMode_, true);
    EXPECT_NE(pattern->styledString_, nullptr);
}

} // namespace OHOS::Ace::NG
