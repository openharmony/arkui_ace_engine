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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorBaseTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorBaseTestOneNg::SetUp()
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

void RichEditorBaseTestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorBaseTestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorController015
 * @tc.desc: test use span & imagespan & symbolspan together
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorController015, TestSize.Level1)
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
 * @tc.name: RichEditorController016
 * @tc.desc: test add many spans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorController016, TestSize.Level1)
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
 * @tc.name: SetEnterKeyType
 * @tc.desc: test SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, SetEnterKeyType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetEnterKeyType(TextInputAction::NEW_LINE);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    richEditorModel.SetEnterKeyType(TextInputAction::UNSPECIFIED);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    ClearSpan();
}

/**
 * @tc.name: SupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, SupportAvoidanceTest, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto supportAvoidance = true;
    richEditorPattern->SetCustomKeyboardOption(supportAvoidance);
    auto support = richEditorPattern->keyboardAvoidance_;
    overlayManager->SetCustomKeyboardOption(support);
    EXPECT_TRUE(richEditorPattern->keyboardAvoidance_);
    supportAvoidance = false;
    richEditorPattern->SetCustomKeyboardOption(supportAvoidance);
    overlayManager->SetCustomKeyboardOption(support);
    EXPECT_FALSE(richEditorPattern->keyboardAvoidance_);
}

/**
 * @tc.name: IsSelectAreaVisible001
 * @tc.desc: test selectArea inVisible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, IsSelectAreaVisible001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsSelectAreaVisible002
 * @tc.desc: test selectArea Visible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, IsSelectAreaVisible002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify the onDraw Magnifier.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, onDraw001, TestSize.Level1)
{
    Offset localOffset(0, 0);
    SymbolSpanOptions symbolSpanOptions;
    symbolSpanOptions.symbolId = SYMBOL_ID;

    //Verify the selected single line text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify the selected multi line text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_3, symbolSpanOptions, localOffset, true);

    //Verify the selected image magnifying glass
    OnDrawVerify(SelectSpanType::TYPEIMAGE, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify the selected symbol magnifying glass
    OnDrawVerify(SelectSpanType::TYPESYMBOLSPAN, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify insertion status with a regular text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_1, symbolSpanOptions, localOffset);

    //Verify the insertion status of the image magnifying glass
    OnDrawVerify(SelectSpanType::TYPEIMAGE, INIT_VALUE_1, symbolSpanOptions, localOffset);

    //Verify the insertion state symbol magnifying glass
    OnDrawVerify(SelectSpanType::TYPESYMBOLSPAN, INIT_VALUE_1, symbolSpanOptions, localOffset);
}

/**
 * @tc.name: RichEditorController017
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorController017, TestSize.Level1)
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
     * @tc.steps: step2. test add span
     */
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 3);

    /**
     * @tc.steps: step3. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    TextStyle textStyle2;
    textStyle2.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;

    /**
     * @tc.cases: case. call UpdateSpanStyle(), cover branch end < 0
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, -1, textStyle, imageStyle);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch end > length
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE_2
     */
    richEditorController->UpdateSpanStyle(0, 20, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE, cover branch start > end
     * @tc.expected: expect GetFontSize() is equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(10, 0, textStyle, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start == end
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(0, 0, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);

    /**
     * @tc.cases: case. call UpdateSpanStyle(), update FontSize to FONT_SIZE_VALUE_2, cover branch start > length
     * @tc.expected: expect GetFontSize() is still equal to FONT_SIZE_VALUE
     */
    richEditorController->UpdateSpanStyle(20, 30, textStyle2, imageStyle);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    ClearSpan();
}

/**
 * @tc.name: RichEditorEventHub001
 * @tc.desc: test get insert
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorEventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set insert value
     */
    RichEditorInsertValue insertValueInfo;
    insertValueInfo.SetInsertOffset(1);
    insertValueInfo.SetInsertValue(INIT_VALUE_1);
    /**
     * @tc.steps: step2. get insert value
     */
    EXPECT_EQ(insertValueInfo.GetInsertOffset(), 1);
    EXPECT_EQ(insertValueInfo.GetInsertValue(), INIT_VALUE_1);
}

/**
 * @tc.name: RichEditorEventHub002
 * @tc.desc: test span result
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorEventHub002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set span result
     */
    RichEditorAbstractSpanResult result;
    FONT_FEATURES_LIST fontFeature;
    RefPtr<ResourceObject> valueResource;
    SymbolSpanStyle symbolSpanStyle;

    result.SetSpanRangeEnd(1);
    result.SetFontFeature(fontFeature);
    result.SetLineHeight(20.0);
    result.SetLetterspacing(20.0);
    result.SetValueResource(valueResource);
    result.SetValueString(INIT_VALUE_1);
    result.SetSymbolSpanStyle(symbolSpanStyle);
    result.SetTextDecoration(TextDecoration::UNDERLINE);
    result.SetColor("");

    /**
     * @tc.steps: step2. get span result
     */
    EXPECT_EQ(result.GetSpanRangeEnd(), 1);
    EXPECT_EQ(result.GetFontFeatures(), fontFeature);
    EXPECT_EQ(result.GetLineHeight(), 20.0);
    EXPECT_EQ(result.GetLetterspacing(), 20.0);
    EXPECT_EQ(result.GetFontColor(), "");
    EXPECT_EQ(result.GetFontSize(), 0);
    EXPECT_EQ(result.GetValueResource(), valueResource);
    EXPECT_EQ(result.GetValueString(), INIT_VALUE_1);
    EXPECT_EQ(result.GetSymbolSpanStyle().lineHeight, 0.0);
    EXPECT_EQ(result.GetFontWeight(), 0);
    EXPECT_EQ(result.GetFontFamily(), "");
    EXPECT_EQ(result.GetTextDecoration(), TextDecoration::UNDERLINE);
    EXPECT_EQ(result.GetColor(), "");
}

/**
 * @tc.name: RichEditorEventHub003
 * @tc.desc: test edit change event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorEventHub003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set OnEditingChange func
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](bool value) {
        g_isOnEditChangeCalled = value;
    };
    richEditorModel.SetOnEditingChange(std::move(func));

    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. fire OnEditingChange func
     * @tc.expected: expect g_isOnEditChangeCalled is true
     */
    eventHub->FireOnEditingChange(true);
    EXPECT_EQ(g_isOnEditChangeCalled, true);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorEventHub004
 * @tc.desc: test GetDragExtraParams
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorEventHub004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch !extraInfo.empty()
     * @tc.expected: expect return jsonStr is {"extraInfo":"info"}
     */
    auto jsonStr = eventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch type == DragEventType::DROP
     * @tc.expected: expect return jsonStr is {"extraInfo":"info"}
     */
    jsonStr = eventHub->GetDragExtraParams("info", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{\"extraInfo\":\"info\"}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch timestamp_ != 0
     * @tc.expected: expect return jsonStr is {}
     */
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    eventHub->timestamp_ = timestamp;
    jsonStr = eventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{}");

    /**
     * @tc.cases: case. call GetDragExtraParams(), cover branch pattern->GetTimestamp() == timestamp_
     * @tc.expected: expect return jsonStr is {"isInComponent":true}
     */
    richEditorPattern->timestamp_ = timestamp;
    jsonStr = eventHub->GetDragExtraParams("", Point(0, 250.f), DragEventType::DROP);
    EXPECT_EQ(jsonStr, "{\"isInComponent\":true}");
    EXPECT_EQ(eventHub->timestamp_, 0);
}

/**
 * @tc.name: RichEditorEventHub005
 * @tc.desc: test fire event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorEventHub005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init eventHub
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. fire event when there is null func
     */
    RichEditorChangeValue value;
    StyledStringChangeValue info;
    TextCommonEvent event;
    eventHub->FireOnDidChange(value);
    eventHub->FireOnCut(event);
    eventHub->FireOnCopy(event);
    EXPECT_TRUE(eventHub->FireOnWillChange(value));
    EXPECT_TRUE(eventHub->FireOnStyledStringWillChange(info));

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ParagraphManager001
 * @tc.desc: Test the paragraph manager GetHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial height
     */
    auto height = richEditorPattern->paragraphs_.GetHeight();
    EXPECT_EQ(height, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get height
     */
    height = richEditorPattern->paragraphs_.GetHeight();
    EXPECT_EQ(height, 0.0f);
}

/**
 * @tc.name: ParagraphManager002
 * @tc.desc: Test the paragraph manager GetMaxIntrinsicWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max intrinsic width
     */
    double maxIntrinsicWidth = richEditorPattern->paragraphs_.GetMaxIntrinsicWidth();
    EXPECT_EQ(maxIntrinsicWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get maxIntrinsicWidth
     */
    maxIntrinsicWidth = richEditorPattern->paragraphs_.GetMaxIntrinsicWidth();
    EXPECT_EQ(maxIntrinsicWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager003
 * @tc.desc: Test the paragraph manager DidExceedMaxLines function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial exceed max lines
     */
    bool didExceedMaxLines = richEditorPattern->paragraphs_.DidExceedMaxLines();
    EXPECT_EQ(didExceedMaxLines, false);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test didExceedMaxLines
     */
    didExceedMaxLines = richEditorPattern->paragraphs_.DidExceedMaxLines();
    EXPECT_EQ(didExceedMaxLines, false);
}

/**
 * @tc.name: ParagraphManager004
 * @tc.desc: Test the paragraph manager GetLongestLine function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max intrinsic width
     */
    double longestLine = richEditorPattern->paragraphs_.GetLongestLine();
    EXPECT_EQ(longestLine, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get longest line
     */
    longestLine = richEditorPattern->paragraphs_.GetLongestLine();
    EXPECT_EQ(longestLine, 0.0f);
}

/**
 * @tc.name: ParagraphManager005
 * @tc.desc: Test the paragraph manager GetMaxWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max width
     */
    double maxWidth = richEditorPattern->paragraphs_.GetMaxWidth();
    EXPECT_EQ(maxWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get max width
     */
    maxWidth = richEditorPattern->paragraphs_.GetMaxWidth();
    EXPECT_EQ(maxWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager006
 * @tc.desc: Test the paragraph manager GetTextWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial max width
     */
    double maxTextWidth = richEditorPattern->paragraphs_.GetTextWidth();
    EXPECT_EQ(maxTextWidth, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get text width
     */
    maxTextWidth = richEditorPattern->paragraphs_.GetTextWidth();
    EXPECT_EQ(maxTextWidth, 0.0f);
}

/**
 * @tc.name: ParagraphManager007
 * @tc.desc: Test the paragraph manager GetTextWidthIncludeIndent function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial text width include indent
     */
    double textWidthIncludeIndent = richEditorPattern->paragraphs_.GetTextWidthIncludeIndent();
    EXPECT_EQ(textWidthIncludeIndent, 0.0f);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get text width include indent
     */
    textWidthIncludeIndent = richEditorPattern->paragraphs_.GetTextWidthIncludeIndent();
    EXPECT_EQ(textWidthIncludeIndent, 0.0f);
}

/**
 * @tc.name: ParagraphManager008
 * @tc.desc: Test the paragraph manager GetLineCount function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    /**
     * @tc.steps: step1. test to obtain initial line count
     */
    size_t dineCount = richEditorPattern->paragraphs_.GetLineCount();
    EXPECT_EQ(dineCount, 0);

    /**
     * @tc.steps: step2. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step3. test get line count
     */
    dineCount = richEditorPattern->paragraphs_.GetLineCount();
    EXPECT_EQ(dineCount, 0);
}

/**
 * @tc.name: ParagraphManager009
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager009, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get index
     */
    auto textRect = richEditorPattern->GetTextRect();
    textRect.SetTop(textRect.GetY() - 0.0f);
    textRect.SetHeight(textRect.Height() - 0.0f);
    Offset offset = Offset(textRect.GetX(), textRect.GetY());
    bool clamp = false;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(offset, clamp);
    EXPECT_EQ(paragraphsIndex, 0);

    /**
     * @tc.steps: step3. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetGlyphIndexByCoordinate(offset, clamp);
    EXPECT_EQ(glyphIndex, 0);

    /**
     * @tc.steps: step4. test get word boundary
     */
    int32_t offset1 = 0;
    int32_t start = 0;
    int32_t end = 0;
    bool wordBoundary = richEditorPattern->paragraphs_.GetWordBoundary(offset1, start, end);
    EXPECT_EQ(wordBoundary, false);

    /**
     * @tc.steps: step5. test calc caret metrics
     */
    int32_t extent = 0;
    CaretMetricsF caretCaretMetric;
    TextAffinity textAffinity = TextAffinity::DOWNSTREAM;
    bool caretMetrics = richEditorPattern->paragraphs_.CalcCaretMetricsByPosition(extent, caretCaretMetric,
        textAffinity);
    EXPECT_EQ(caretMetrics, false);
}

/**
 * @tc.name: ParagraphManager010
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager010, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get line metrics
     */
    RectF rect = { 0.0, 0.0, 100.0, 100.0 };
    int32_t paragraphIndex = 0;
    LineMetrics lineMetrics = richEditorPattern->paragraphs_.GetLineMetricsByRectF(rect, paragraphIndex);
    EXPECT_EQ(lineMetrics.ascender, 0.0f);

    /**
     * @tc.steps: step3. test editable status
     */
    auto accessibilityProperty = richEditorPattern->CreateAccessibilityProperty();
    bool isEditable = accessibilityProperty->IsEditable();
    EXPECT_EQ(isEditable, true);
}

/**
 * @tc.name: ParagraphManager011
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ParagraphManager011, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    bool clamp = true;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(-1.0, -1.0), clamp);
    EXPECT_EQ(paragraphsIndex, 0);

    PositionWithAffinity finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(-1.0, -1.0));
    EXPECT_EQ(finalResult.position_, 0);
}

/**
 * @tc.name: Controller001
 * @tc.desc: Test the controller function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, Controller001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorController->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_VALUE_1);
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle2.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle2.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: Controller002
 * @tc.desc: Test the controller function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, Controller002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    richEditorController->SetSelection(1, 3);
    auto info1 = richEditorController->GetSpansInfo(1, 2);
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : info1.selection_.resultObjects.front().textStyle.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
    richEditorController->CloseSelectionMenu();
}

/**
 * @tc.name: ToStyledString001
 * @tc.desc: Test spans to styledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, ToStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
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
 * @tc.name: AddSpanByPasteData001
 * @tc.desc: Test add span by pasteData.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, AddSpanByPasteData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. init spans
     */
    AddImageSpan();
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
 * @tc.name: RichEditorLayoutAlgorithm001
 * @tc.desc: test MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorLayoutAlgorithm001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    parentLayoutConstraint.selfIdealSize.SetHeight(std::nullopt);
    parentLayoutConstraint.selfIdealSize.SetWidth(1.0f);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);

    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    layoutAlgorithm->paragraphManager_ = paragraphManager;

    AddSpan(INIT_VALUE_1);
    layoutAlgorithm->spans_.emplace_back(richEditorPattern->spans_);
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));

    layoutAlgorithm->spans_.clear();
    auto size1 = layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(size1.value().Width(), 1.0f);

    richEditorPattern->presetParagraph_ = paragraph;
    auto size2 = layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(size2.value().Width(), 1.0f);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm002
 * @tc.desc: test GetParagraphStyleSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorLayoutAlgorithm002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    std::list<RefPtr<SpanItem>> spanGroup;
    spanGroup.clear();
    spanGroup.emplace_back(AceType::MakeRefPtr<PlaceholderSpanItem>());
    auto span = layoutAlgorithm->GetParagraphStyleSpanItem(spanGroup);
    EXPECT_EQ(*spanGroup.begin(), span);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm003
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorLayoutAlgorithm003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(10.0f, 1000.0f);
    layoutConstraint.minSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 720.0f);
}

/**
 * @tc.name: RichEditorLayoutAlgorithm004
 * @tc.desc: test RichEditorLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, RichEditorLayoutAlgorithm004, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    auto placeholderSpanItem = AceType::MakeRefPtr<PlaceholderSpanItem>();
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::string str = "\n";
    spanItem->content = str;
    spans.emplace_back(spanItem);
    auto layoutAlgorithm = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(spans, AceType::RawPtr(paragraphManager),
        std::nullopt);
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_NE(*(layoutAlgorithm->allSpans_.begin()), nullptr);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin001
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, IsSelectLineHeadAndUseLeadingMargin001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(paragraphItem.start);
    EXPECT_EQ(bRet, false);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin002
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, IsSelectLineHeadAndUseLeadingMargin002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    testStyle.leadingMargin = LeadingMargin();
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    int start = richEditorPattern->paragraphs_.paragraphs_.begin()->start;
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(start);
    EXPECT_EQ(bRet, true);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin003
 * @tc.desc: Test the paragraph manager IsSelectLineHeadAndUseLeadingMargin function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, IsSelectLineHeadAndUseLeadingMargin003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step1. add paragraph and Mock func.
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ParagraphStyle testStyle = {};
    testStyle.leadingMargin = LeadingMargin();
    EXPECT_CALL(*paragraph, GetParagraphStyle())
        .WillRepeatedly(ReturnRef(testStyle));
    /**
     * @tc.steps: step2. test IsSelectLineHeadAndUseLeadingMargin fun
    */
    bool bRet = richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(paragraphRect.end);
    EXPECT_EQ(bRet, true);
}

/**
 * @tc.name: GetIndex001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetGetIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    PositionWithAffinity positionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));

    bool clamp = true;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, -10.0), clamp);
    EXPECT_EQ(paragraphsIndex, 0);
    paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 0.0), clamp);
    EXPECT_EQ(paragraphsIndex, 6);
    clamp = false;
    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 600.0, 600.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 900.0), clamp);
    EXPECT_EQ(paragraphsIndex, 13);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
    PositionWithAffinity positionWithAffinity(2, TextAffinity::UPSTREAM);
    EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    bool clamp = false;
    int32_t paragraphsIndex = richEditorPattern->paragraphs_.GetIndex(Offset(100.0, 0.0), clamp);
    EXPECT_EQ(paragraphsIndex, 6);

    PositionWithAffinity finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, 0.0));
    EXPECT_EQ(finalResult.position_, 2);
    finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, -10.0));
    EXPECT_EQ(finalResult.position_, 0);
    finalResult = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(Offset(0.0, 900.0));
    EXPECT_EQ(finalResult.position_, 2);
}

/**
 * @tc.name: GetLineMetrics001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetLineMetrics001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    TextLineMetrics textLineMetrics;
    textLineMetrics.lineNumber = 0;
    EXPECT_CALL(*paragraph, GetLineMetrics(_)).WillRepeatedly(Return(textLineMetrics));

    TextLineMetrics finalResult = richEditorPattern->paragraphs_.GetLineMetrics(0);
    EXPECT_EQ(finalResult.lineNumber, 0);

    finalResult = richEditorPattern->paragraphs_.GetLineMetrics(2);
    EXPECT_EQ(finalResult.lineNumber, 0);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 600.0, 600.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);
    finalResult = richEditorPattern->paragraphs_.GetLineMetrics(1);
    EXPECT_EQ(finalResult.lineNumber, 1);
}

/**
 * @tc.name: GetGlyphIndexByCoordinate001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetGlyphIndexByCoordinate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));
    /**
     * @tc.steps: step2. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetGlyphIndexByCoordinate(Offset(0.0, 1000.00), true);
    EXPECT_EQ(glyphIndex, 6);
}

/**
 * @tc.name: GetWordBoundary001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetWordBoundary001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    /**
     * @tc.steps: step2. test get glyph index
     */
    int32_t glyphIndex = richEditorPattern->paragraphs_.GetWordBoundary(1000, paragraphItem.start, paragraphItem.end);
    EXPECT_EQ(glyphIndex, 0);
}

/**
 * @tc.name: GetLineMetricsByRectF001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, GetLineMetricsByRectF001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItemSec);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(800.0f));

    /**
     * @tc.steps: step2. test get glyph index
     */
    LineMetrics testMetrics = richEditorPattern->paragraphs_.GetLineMetricsByRectF(RectF(0.0, 100.0, 200.0, 300.0), 1);
    EXPECT_EQ(testMetrics.y, 800);
}

/**
 * @tc.name: CalcCaretMetricsByPosition001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseTestOneNg, CalcCaretMetricsByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    TestParagraphRect paragraphRectSec = { .start = 7, .end = 12, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemSec = { .start = 7, .end = 12, .testParagraphRects = { paragraphRectSec } };
    AddParagraph(paragraphItemSec);

    TestParagraphRect paragraphRectThr = { .start = 13, .end = 20, .rects = { { 200.0, 200.0, 400.0, 400.0 } } };
    TestParagraphItem paragraphItemThr = { .start = 13, .end = 20, .testParagraphRects = { paragraphRectThr } };
    AddParagraph(paragraphItemThr);
    /**
     * @tc.steps: step5. test calc caret metrics
     */
    int32_t extent = 0;
    CaretMetricsF caretCaretMetric;
    TextAffinity textAffinity = TextAffinity::DOWNSTREAM;
    bool caretMetrics = richEditorPattern->paragraphs_.CalcCaretMetricsByPosition(extent, caretCaretMetric,
        textAffinity);
    EXPECT_EQ(caretMetrics, false);
}
} // namespace OHOS::Ace::NG
