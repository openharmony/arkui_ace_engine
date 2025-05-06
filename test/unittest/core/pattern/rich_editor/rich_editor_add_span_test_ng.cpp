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
    const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    int32_t testNumber1 = 1;
    int32_t testNumber2 = 2;
} // namespace
const std::string SYMBOL_FONT_FAMILY = "Symbol_Test_CustomSymbol";
class RichEditorAddSpanTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
        const RefPtr<MagnifierController>& controller, const OffsetF& localOffset);
};

void RichEditorAddSpanTestNg::SetUp()
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
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorAddSpanTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorAddSpanTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: AddImageSpan001
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddImageSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    ImageSpanAttribute imageStyle;
    AddSpan("test");
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto index1 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index1, 1);
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 2;
    auto index2 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index2, 2);

    options.offset = std::nullopt;
    auto index3 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index3, 4);

    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index4 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index4, 5);

    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index5 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index5, 6);

    marginProp = { ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC };
    borderRadius = { ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index6 = richEditorPattern->AddImageSpan(options, false, -1);
    EXPECT_EQ(index6, 7);
}

/**
 * @tc.name: AddImageSpan002
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddImageSpan002, TestSize.Level1)
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
    AddSpan("test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());

    /**
     * @tc.steps: step3. test AddImageSpan when isPaste is false
     * @tc.expected: textSelector_ is reset
     */
    ImageSpanAttribute imageStyle;
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto index = richEditorPattern->AddImageSpan(options, false, 0, true);
    EXPECT_EQ(index, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddTextSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetFontFamilies(FONT_FAMILY_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextSpanOptions options;
    options.offset = 1;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index1 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index2, 1);
    options.value = u"hello\n";
    auto index3 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index3, 1);
}

/**
 * @tc.name: AddSymbolSpan001
 * @tc.desc: test add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSymbolSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. test add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    ClearSpan();
}

/**
 * @tc.name: AddSymbolSpan002
 * @tc.desc: test add symbol span for custom symbol
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSymbolSpan002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize custom symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    style.SetSymbolType(SymbolType::CUSTOM);
    std::vector<std::string> fontFamilies;
    fontFamilies.push_back(SYMBOL_FONT_FAMILY);
    style.SetFontFamilies(fontFamilies);

    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. test add custom symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    ClearSpan();
}

/**
 * @tc.name: AddSpans001
 * @tc.desc: test use span & imagespan & symbolspan together
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpans001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddSymbolSpan(options1);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddImageSpan(options3);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddSymbolSpan(options1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 5);

    /**
     * @tc.steps: step4. test get span
     */
    auto info1 = richEditorController->GetSpansInfo(0, 3);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 2);
    auto info2 = richEditorController->GetSpansInfo(8, 9);
    EXPECT_EQ(info2.selection_.resultObjects.size(), 1);

    /**
     * @tc.steps: step5. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(2, 8, textStyle, imageStyle);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.steps: step6. test delete span
     */
    RangeOptions option;
    option.start = 8;
    option.end = 15;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);

    option.start = 0;
    option.end = 2;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);

    ClearSpan();
}

/**
 * @tc.name: AddSpans002
 * @tc.desc: test add many spans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpans002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    for (int i = 0; i < 100; i++) {
        richEditorController->AddSymbolSpan(options1);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddImageSpan(options3);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddSymbolSpan(options1);
    }
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 500);

    ClearSpan();
}

/**
 * @tc.name: AddSpans003
 * @tc.desc: Test the function AddTextSpan.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpans003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    std::string insertValue = "hello";
    RichEditorPattern::OperationRecord record;
    richEditorPattern->InsertValueOperation(StringUtils::Str8ToStr16(insertValue), &record, OperationType::DEFAULT);
    int32_t maxLength = 5;
    richEditorPattern->SetMaxLength(maxLength);
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 5);

    // 0: AddTextSpan
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 5);

    // 1: AddSymbolSpan
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 5);

    // 2: AddPlaceholderSpan
    richEditorPattern->AddPlaceholderSpan(BUILDER_NODE_1, {});
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 5);
}

/**
 * @tc.name: AddSpanByPasteData001
 * @tc.desc: Test add span by pasteData.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpanByPasteData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
    */
    ImageSpanOptions imageOptions;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    imageOptions.imagePixelMap = pixelMap;
    richEditorPattern->AddImageSpan(imageOptions);

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options);

    /**
     * @tc.steps: step2. test AddSpanByPasteData001
     */
    auto spanString = richEditorPattern->ToStyledString(0, 8);
    ASSERT_NE(spanString, nullptr);
    richEditorPattern->spans_.clear();
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
}

/**
 * @tc.name: AddSpansByPaste001
 * @tc.desc: test RichEditorPattern AddSpansByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpansByPaste001, TestSize.Level1)
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
    AddSpan("test");
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 4);
    richEditorPattern->textSelector_.Update(3, 4);
    std::list<RefPtr<NG::SpanItem>> spans;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    spans.push_back(spanItem1);
    richEditorPattern->AddSpansByPaste(spans);
    ASSERT_EQ(richEditorPattern->textSelector_.IsValid(), false);
}

/**
 * @tc.name: AddSpansAndReplacePlaceholder001
 * @tc.desc: test AddSpansAndReplacePlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpansAndReplacePlaceholder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"test![id2]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id3]"] = nullptr;
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id3]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id4]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id4]");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"![id5]");
    richEditorPattern->placeholderSpansMap_[u"![id5]"] = AceType::MakeRefPtr<SpanItem>();
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 1);
    richEditorPattern->ClearOperationRecords();

    spanString = AceType::MakeRefPtr<SpanString>(u"");
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: AddSpanByPasteData002
 * @tc.desc: test AddSpanByPasteData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, AddSpanByPasteData002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);

    richEditorPattern->SetSpanStringMode(true);
    richEditorPattern->AddSpanByPasteData(spanString);
    richEditorPattern->SetSpanStringMode(false);

    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + testNumber1);

    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    spanString->AppendSpanItem(imageSpanItem);
    start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpanByPasteData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + testNumber2);
}

/**
 * @tc.name: ResetSelectionAfterAddSpan001
 * @tc.desc: test ResetSelectionAfterAddSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAddSpanTestNg, ResetSelectionAfterAddSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->ResetSelectionAfterAddSpan(false);
    EXPECT_TRUE(richEditorPattern->caretTwinklingTask_.Cancel());
}
} // namespace OHOS::Ace::NG
