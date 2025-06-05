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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string INIT_STRING_1 = u"初始属性字符串";
const std::u16string INIT_U16STRING_1 = u"初始属性字符串";
const int32_t TEST_MAX_LINE = 10;
const Dimension TEST_BASELINE_OFFSET = Dimension(5, DimensionUnit::PX);
const Dimension TEST_TEXT_INDENT = Dimension(20, DimensionUnit::PX);
const LeadingMarginSize TEST_LEADING_MARGIN_SIZE = { Dimension(5.0), Dimension(10.0) };
const LeadingMargin TEST_LEADING_MARGIN = { .size = TEST_LEADING_MARGIN_SIZE };
const Font TEST_FONT = { FONT_WEIGHT_BOLD, FONT_SIZE_VALUE, ITALIC_FONT_STYLE_VALUE, FONT_FAMILY_VALUE,
    OHOS::Ace::Color::RED, FONT_FAMILY_VALUE};
const SpanParagraphStyle TEST_PARAGRAPH_STYLE = { TextAlign::END, TextVerticalAlign::BASELINE, TEST_MAX_LINE,
    WordBreak::BREAK_ALL, TextOverflow::ELLIPSIS, TEST_LEADING_MARGIN, TEST_TEXT_INDENT};

void ConstructGestureStyle(GestureStyle& gestureInfo)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureInfo.onClick = std::move(tmpClickFunc);

    auto onLongPress = [](const BaseEventInfo* info) {};
    auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
    gestureInfo.onLongPress = std::move(tmpLongPressFunc);
}

void ConstructUserGestureOptions(UserGestureOptions& gestureOption)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureOption.onClick = std::move(tmpClickFunc);

    auto onLongPress = [](const BaseEventInfo* info) {};
    auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
    gestureOption.onLongPress = std::move(tmpLongPressFunc);
}
} // namespace

class RichEditorAccessibilityTestNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    void SetSpanStringMode(bool isSpanStringMode);

    RefPtr<MutableSpanString> CreateTextStyledString(const std::u16string& content);

protected:
    static void MockKeyboardBuilder() {}
    RefPtr<FrameNode> richEditorNode_;
};

void RichEditorAccessibilityTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
}

void RichEditorAccessibilityTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorAccessibilityTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorAccessibilityTestNg::SetSpanStringMode(bool isSpanStringMode)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    if (isSpanStringMode) {
        richEditorPattern->SetSpanStringMode(true);
        richEditorPattern->SetRichEditorStyledStringController(
            AceType::MakeRefPtr<RichEditorStyledStringController>());
        richEditorPattern->GetRichEditorStyledStringController()->SetPattern(WeakPtr(richEditorPattern));
    } else {
        richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
        richEditorPattern->GetRichEditorController()->SetPattern(
            AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    }
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

RefPtr<MutableSpanString> RichEditorAccessibilityTestNg::CreateTextStyledString(const std::u16string& content)
{
    auto styledString = AceType::MakeRefPtr<MutableSpanString>(content);
    auto length = styledString->GetLength();
    styledString->AddSpan(AceType::MakeRefPtr<FontSpan>(TEST_FONT, 0, length));
    std::optional<TextDecorationOptions> options;
    styledString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(std::vector<TextDecoration>({TEXT_DECORATION_VALUE}),
        TEXT_DECORATION_COLOR_VALUE, TextDecorationStyle::WAVY, options, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(TEST_BASELINE_OFFSET, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(LETTER_SPACING, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(SHADOWS, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<ParagraphStyleSpan>(TEST_PARAGRAPH_STYLE, 0, length));
    styledString->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(LINE_HEIGHT_VALUE, 0, length));
    return styledString;
}

/**
 * @tc.name: GetSubComponentInfos000
 * @tc.desc: Test GetSubComponentInfos for addTextSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, GetSubComponentInfos000, TestSize.Level1)
{
    SetSpanStringMode(false);

    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto controller = richEditorPattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set AddTextSpan without onClick
     */
    TextSpanOptions options;
    options.value = INIT_STRING_1;
    controller->AddTextSpan(options);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 0);
}

/**
 * @tc.name: GetSubComponentInfos001
 * @tc.desc: Test GetSubComponentInfos for addTextSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, GetSubComponentInfos001, TestSize.Level1)
{
    SetSpanStringMode(false);

    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto controller = richEditorPattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set AddTextSpan with onClick
     */
    TextSpanOptions options;
    options.value = INIT_STRING_1;
    ConstructUserGestureOptions(options.userGestureOption);
    controller->AddTextSpan(options);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 1);
}

/**
 * @tc.name: GetSubComponentInfos002
 * @tc.desc: Test GetSubComponentInfos for SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, GetSubComponentInfos002, TestSize.Level1)
{
    SetSpanStringMode(true);

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
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

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

    /**
     * @tc.steps: step4. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 0);
}

/**
 * @tc.name: GetSubComponentInfos003
 * @tc.desc: Test GetSubComponentInfos for SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, GetSubComponentInfos003, TestSize.Level1)
{
    SetSpanStringMode(true);

    /**
     * @tc.steps: step1. create styledString with text & onClick
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    auto length = mutableStr->GetLength();
    mutableStr->AddSpan(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, length));

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

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

    /**
     * @tc.steps: step4. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 1);
}

/**
 * @tc.name: ExecSubComponent000
 * @tc.desc: Test ExecSubComponent for addTextSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, ExecSubComponent000, TestSize.Level1)
{
    SetSpanStringMode(false);

    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto controller = richEditorPattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set AddTextSpan with onClick
     */
    TextSpanOptions options;
    options.value = INIT_STRING_1;
    ConstructUserGestureOptions(options.userGestureOption);
    controller->AddTextSpan(options);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 7);

    /**
     * @tc.steps: step3. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);

    EXPECT_EQ(subComponentInfos.size(), 1);

    /**
     * @tc.steps: step4. test pattern ExecSubComponent
     */
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(0), true);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(0), true);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(1), false);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(1), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(-1), false);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(-1), false);
}

/**
 * @tc.name: ExecSubComponent001
 * @tc.desc: Test ExecSubComponent for SetStyledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, ExecSubComponent001, TestSize.Level1)
{
    SetSpanStringMode(true);

    /**
     * @tc.steps: step1. create styledString with text & onClick
     */
    auto mutableStr = CreateTextStyledString(INIT_U16STRING_1);
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    auto length = mutableStr->GetLength();
    mutableStr->AddSpan(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, length));

    /**
     * @tc.steps: step2. get richEditor styledString controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto styledStringController = richEditorPattern->GetRichEditorStyledStringController();
    ASSERT_NE(styledStringController, nullptr);
    auto accessibilityProperty = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

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

    /**
     * @tc.steps: step4. test pattern GetSubComponentInfos
     */
    std::vector<SubComponentInfo> subComponentInfos;
    accessibilityProperty->GetSubComponentInfo(subComponentInfos);
    EXPECT_EQ(subComponentInfos.size(), 1);

    /**
     * @tc.steps: step4. test pattern ExecSubComponent
     */
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(0), true);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(0), true);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(1), false);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(1), false);
    EXPECT_EQ(accessibilityProperty->ActActionExecSubComponent(-1), false);
    EXPECT_EQ(richEditorPattern->ExecSubComponent(-1), false);
}

/**
 * @tc.name: ActActionSetText
 * @tc.desc: Test ActActionSetText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, ActActionSetText, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::ACCESSIBILITY);
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);
    richEditorPattern->SetAccessibilityEditAction();
    auto property = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(property);
    property->ActActionSetText("test123");
    EXPECT_EQ(changeReason, TextChangeReason::ACCESSIBILITY);
}

/**
 * @tc.name: ActActionCut
 * @tc.desc: Test ActActionCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAccessibilityTestNg, ActActionCut, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto eventHub = richEditorPattern->GetOrCreateEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    eventHub->SetOnWillChange(onWillChange);
    richEditorPattern->SetAccessibilityEditAction();
    auto property = richEditorNode_->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(property);

    richEditorPattern->UpdateSelector(0, 1);
    property->ActActionCut();
    EXPECT_EQ(changeReason, TextChangeReason::CUT);
}


} // namespace OHOS::Ace::NG
