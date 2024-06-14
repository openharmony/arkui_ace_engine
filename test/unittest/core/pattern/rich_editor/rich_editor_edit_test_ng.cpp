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
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorEditTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorEditTestNg::SetUp()
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

void RichEditorEditTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorEditTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


/**
 * @tc.name: RichEditorInsertValue001
 * @tc.desc: test calc insert value object
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextInsertValueInfo info;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 0);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 1);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
}

/**
 * @tc.name: RichEditorInsertValue002
 * @tc.desc: test insert value last
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it3 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result3 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result3, it3->spanItem_->content);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it4 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result4 = TEST_INSERT_VALUE;
    EXPECT_EQ(result4, it4->spanItem_->content);
    ClearSpan();
    richEditorPattern->InsertValue(" ");
    auto it5 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    EXPECT_TRUE(it5);
}

/**
 * @tc.name: RichEditorInsertValue003
 * @tc.desc: test insert value between text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    AddSpan(INIT_VALUE_2);
    richEditorPattern->caretPosition_ = INIT_VALUE_1.size();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue004
 * @tc.desc: test insert value first
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue005
 * @tc.desc: test insert value if the insert char is line separator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorInsertValue005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result1 = INIT_VALUE_1;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result2 = EXCEPT_VALUE;
    EXPECT_EQ(result2, it2->spanItem_->content);
}

/**
 * @tc.name: CalcInsertValueObj001
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CalcInsertValueObj001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("test1");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    TextInsertValueInfo info;

    it->content = "test";
    it->position = 4;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 2;

    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 0);

    richEditorPattern->moveLength_ = -1;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 2);

    richEditorPattern->moveLength_ = 5;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 2);
}

/**
 * @tc.name: RichEditorDelete001
 * @tc.desc: test delete forward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 0);
}

/**
 * @tc.name: RichEditorDelete002
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(6);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete003
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDelete003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteBackward(1);
    EXPECT_NE(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 0);
    richEditorPattern->textSelector_ = TextSelector(0, 1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    while (!richEditorPattern->spans_.empty()) {
        richEditorPattern->spans_.pop_back();
    }
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDeleteForwardEmoji
 * @tc.desc: test DeleteForward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDeleteForwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorDeleteBackwardEmoji
 * @tc.desc: test DeleteBackward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorDeleteBackwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnCopy001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    AddSpan("test1");
    richEditorPattern->HandleOnCopy();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    richEditorPattern->HandleOnCopy();
    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCopy003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnCopy003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCut002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnCut002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCut003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnCut003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: GetTextSpansInfo
 * @tc.desc: test get paragraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetTextSpansInfo, TestSize.Level1)
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
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options);

    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);

    auto info = richEditorController->GetSpansInfo(0, 6);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto valueString = info.selection_.resultObjects.begin()->valueString;
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;

    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_EQ(textStyle.leadingMarginSize[0], "5.00px");
    EXPECT_EQ(textStyle.leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: GetImageSpansInfo
 * @tc.desc: test image span layoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetImageSpansInfo, TestSize.Level1)
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
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddImageSpan(options);
    auto info = richEditorController->GetSpansInfo(0, 1);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto imageStyleout = info.selection_.resultObjects.begin()->imageStyle;
    EXPECT_EQ(imageStyleout.borderRadius,
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");
    EXPECT_EQ(imageStyleout.margin, "left: [10.00px]right: [10.00px]top: [10.00px]bottom: [10.00px]");
    ClearSpan();
}

/**
 * @tc.name: GetParagraphNodes001
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto nodes = richEditorPattern->GetParagraphNodes(1, 5);
    EXPECT_EQ(nodes.size(), 0);
    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 0);

    // add multiple paragraphs
    AddSpan(INIT_VALUE_1 + "\n"); // length 7
    AddImageSpan();               // length 1
    AddSpan(INIT_VALUE_2 + "\n"); // length 7
    AddSpan(INIT_VALUE_1);        // length 6
    AddSpan(INIT_VALUE_2 + "\n");
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_2 + "\n");
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(richEditorNode_->children_.size(), 8);

    nodes = richEditorPattern->GetParagraphNodes(3, 5);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(0)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 7);

    nodes = richEditorPattern->GetParagraphNodes(10, 15);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(2)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(6, 7);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(0)->GetId());

    // selecting only the placeholder region
    nodes = richEditorPattern->GetParagraphNodes(7, 8);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(1)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(2, 20);
    EXPECT_EQ(nodes.size(), 4);
    EXPECT_EQ(nodes[3]->GetId(), richEditorNode_->GetChildAtIndex(4)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(400, 404);
    EXPECT_EQ(nodes.size(), 0);
}

/**
 * @tc.name: GetParagraphNodes002
 * @tc.desc: test get paragraph nodes with multiple placeholders
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    // add multiple paragraphs
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1

    EXPECT_EQ(richEditorNode_->children_.size(), 3);

    auto nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_TRUE(nodes.empty());

    AddSpan(INIT_VALUE_2);

    // selecting only placeholder, should return span in the same paragraph
    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 1);

    nodes = richEditorPattern->GetParagraphNodes(4, 6);
    EXPECT_EQ(nodes.size(), 1);
}

/**
 * @tc.name: GetParagraphNodes003
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphNodes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    AddSpan("0123");
    AddImageSpan();
    AddSpan("45789\n");
    AddSpan("aaaaaaaaaa");

    EXPECT_EQ(richEditorNode_->children_.size(), 4);

    auto nodes = richEditorPattern->GetParagraphNodes(50, 52);
    EXPECT_EQ(nodes.size(), 0);

    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 2);
}

/**
 * @tc.name: GetParagraphLength001
 * @tc.desc: test get paragraph length
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    // Add multiple paragraphs
    auto host = richEditorPattern->GetHost();
    AddImageSpan(); // length 1
    auto length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 1);
    AddImageSpan();
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 3);
    AddSpan(INIT_VALUE_1 + "\n"); // length 7
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 10);
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 11);
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: test GetLeftTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetLeftTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "e");

    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(2));
    EXPECT_EQ(ret, "e");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "t");

    richEditorPattern->textSelector_.baseOffset = 3;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "e");
}

/**
 * @tc.name: GetLeftTextOfCursor002
 * @tc.desc: test get left text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetLeftTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(3));
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetRightTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "ol");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "es");
}

/**
 * @tc.name: GetRightTextOfCursor002
 * @tc.desc: test get right text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetRightTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(3));
    EXPECT_EQ(ret, "hel");
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: test get text index at cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetTextIndexAtCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 3;
    EXPECT_EQ(richEditorPattern->GetTextIndexAtCursor(), 3);
}

/**
 * @tc.name: GetSelectedSpanText002
 * @tc.desc: test get select span text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetSelectedSpanText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), -1, 1);
    ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), -1, 10);
    ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), 0, 1);
    EXPECT_EQ(ret, "h");
}

/**
 * @tc.name: GetChildByIndex002
 * @tc.desc: test get child by index
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetChildByIndex002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetChildByIndex(-1);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetChildByIndex(0);
    EXPECT_EQ(*(richEditorNode_->GetChildren().begin()), ret);
}

/**
 * @tc.name: GetChildByIndex001
 * @tc.desc: test GetChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetChildByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    AddSpan(INIT_VALUE_1);
    auto ret1 = richEditorPattern->GetChildByIndex(1);
    EXPECT_EQ(ret1, nullptr);
    auto ret2 = richEditorPattern->GetChildByIndex(-1);
    EXPECT_EQ(ret2, nullptr);
    auto ret3 = richEditorPattern->GetChildByIndex(0);
    EXPECT_NE(ret3, nullptr);
}

/**
 * @tc.name: GetSelectedSpanText001
 * @tc.desc: test GetSelectedSpanText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetSelectedSpanText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string ori = "12345";
    std::wstring value = StringUtils::ToWstring(ori);

    std::vector<int> start = { -1, 0, 15 };
    std::vector<int> end = { 10, -3 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto ret = richEditorPattern->GetSelectedSpanText(value, start[i], end[j]);
            EXPECT_EQ(ret, "");
        }
    }

    auto ret = richEditorPattern->GetSelectedSpanText(value, 0, 1);
    EXPECT_EQ(ret, "1");
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->contentMod_ = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, richEditorPattern);
    richEditorPattern->isCustomFont_ = true;
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: GetSpanItemByIndex001
 * @tc.desc: test GetSpanItemByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetSpanItemByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto ret = richEditorPattern->GetSpanItemByIndex(-1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(0);
    EXPECT_EQ(ret, richEditorPattern->spans_.front());
}

/**
 * @tc.name: DeleteValueSetTextSpan
 * @tc.desc: test add delete text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, DeleteValueSetTextSpan, TestSize.Level1)
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
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    auto info = richEditorController->GetSpansInfo(0, 6);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);

    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();
    spanItem->position = 0;
    spanItem->textStyle_ = TextStyle();
    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    richEditorPattern->DeleteValueSetTextSpan(spanItem, 0, 1, spanResult);

    EXPECT_EQ(spanResult.GetTextStyle().textAlign, int(TextAlign::END));
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[0], "5.00px");
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetImageSpan
 * @tc.desc: test delete imagespan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, DeleteValueSetImageSpan, TestSize.Level1)
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
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;

    /**
     * @tc.steps: step3. test delete image span
     */
    richEditorController->AddImageSpan(options);
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    auto spanItem = richEditorPattern->spans_.front();
    richEditorPattern->DeleteValueSetImageSpan(spanItem, spanResult);
    EXPECT_EQ(spanResult.GetMargin(), "left: [10.00px]right: [10.00px]top: [10.00px]bottom: [10.00px]");
    EXPECT_EQ(spanResult.GetBorderRadius(),
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");

    ClearSpan();
}

/**
 * @tc.name: CheckEditorTypeChange001
 * @tc.desc: test CheckEditorTypeChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CheckEditorTypeChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    SelectOverlayInfo selectOverlayInfo;
    int32_t singleLineHeight = 143;
    selectOverlayInfo.singleLineHeight = singleLineHeight;
    CHECK_NULL_VOID(pipeline);
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    pipeline->AddOnAreaChangeNode(host->GetId());

    richEditorPattern->selectOverlayProxy_ =
        pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);

    richEditorPattern->CheckEditorTypeChange();
    EXPECT_EQ(richEditorPattern->GetEditorType(), TextSpanType::NONE);
}

/**
 * @tc.name: InsertValueByPaste001
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, InsertValueByPaste001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. construct spanItem_.
     */
    textPattern->isSpanStringMode_ = true;

    auto pasteStr = richEditorPattern->GetPasteStr();
    richEditorPattern->InsertValueByPaste(pasteStr);

    richEditorPattern->OnAreaChangedInner();
    OffsetF Offset = {1, 2};
    EXPECT_NE(richEditorPattern->GetPaintRectGlobalOffset(), Offset);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetThumbnailCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    gestureHub->InitDragDropEvent();
    gestureHub->SetThumbnailCallback(richEditorPattern->GetThumbnailCallback());
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->DumpInfo();

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);

    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), false);

    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    richEditorPattern->ScrollToSafeArea();
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);

    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = {1, 4};
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    int32_t index = 1;
    richEditorPattern->MouseDoubleClickParagraphEnd(index);
    EXPECT_NE(richEditorPattern->GetParagraphEndPosition(index), index);

    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
        richEditorPattern->selectionMenuOffsetByMouse_.GetX());

    int32_t start = 1;
    int32_t end = 3;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetStart(), start);

    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->HandleSelectOverlayWithOptions(options);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
        richEditorPattern->selectionMenuOffsetByMouse_.GetX());

    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);

    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options);
    EXPECT_NE(richEditorPattern->textSelector_.GetEnd(), end);
}

/**
 * @tc.name: CreateHandles001
 * @tc.desc: test CreateHandles
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, CreateHandles001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    richEditorPattern->CreateHandles();
    auto offsetF = OffsetF(0.0f, 0.0f);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset, offsetF);

    richEditorPattern->ShowHandles(false);
    EXPECT_NE(richEditorPattern->showSelect_, false);

    richEditorPattern->ShowHandles(true);
    EXPECT_EQ(richEditorPattern->showSelect_, true);

    Offset textOffset = {1, 3};
    EXPECT_NE(richEditorPattern->BetweenSelection(textOffset), true);

    richEditorPattern->CloseHandleAndSelect();
    EXPECT_EQ(richEditorPattern->showSelect_, false);
}

/**
 * @tc.name: GetTextBoxes001
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetTextBoxes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 3;

    std::vector<RectF> res;
    auto ret = richEditorPattern->GetTextBoxes();
    EXPECT_EQ(ret, res);


    TextLineMetrics lineMetrics;
    richEditorPattern->GetLineCount();
    EXPECT_EQ(richEditorPattern->GetLineHeight(), 0.0f);
    EXPECT_EQ(richEditorPattern->GetLetterSpacing(), 0.0f);
    auto retLineMetrics = richEditorPattern->GetLineMetrics(-1);
    EXPECT_EQ(retLineMetrics.x, 0);

    auto retLineMetricsS = richEditorPattern->GetLineMetrics(2);
    EXPECT_EQ(retLineMetricsS.x, 0);

    int32_t scroll_from_update = 1;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 1, 100, 160);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update)) << "Reach Top Boundary";

    EXPECT_EQ(richEditorPattern->MoveTextRect(0.0f), 0.0f);

    auto offsetF = OffsetF(0.0f, 0.5f);
    richEditorPattern->MoveCaretToContentRect(offsetF, 8.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->MoveCaretToContentRect(1.0f, 10);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    richEditorPattern->contentChange_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateTextStyle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE);
    textStyle.SetLineHeight(LINE_HEIGHT_VALUE);
    textStyle.SetLetterSpacing(LETTER_SPACING);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLineHeight = LINE_HEIGHT_VALUE;
    updateSpanStyle.updateLetterSpacing = LETTER_SPACING;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;

    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetLetterSpacing(), LETTER_SPACING);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, UpdateTextStyle2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;
    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetTypingStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_VALUE_1);
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
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
 * @tc.name: HasSameTypingStyle001
 * @tc.desc: test HasSameTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HasSameTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    auto ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = std::nullopt;
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, SetTypingStyle2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: MoveCaretToContentRect001
 * @tc.desc: test MoveCaretToContentRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, MoveCaretToContentRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->selectOverlayNode_ = overlayNode;

    richEditorPattern->OnAreaChangedInner();
    OffsetF Offset = { 1, 2 };
    EXPECT_NE(richEditorPattern->GetPaintRectGlobalOffset(), Offset);

    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);

    int32_t scroll_from_update = 1;
    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 5, 100, 160);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scroll_from_update));

    /**
     * @tc.steps: step1. set isShowPlaceholder_
     */
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 120);
    richEditorPattern->contentRect_ = RectF(0, 5, 100, 60);
    auto offsetF = OffsetF(0.0f, 0.5f);
    richEditorPattern->isShowPlaceholder_ = false;
    richEditorPattern->MoveCaretToContentRect(offsetF, 80.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    /**
     * @tc.steps: step2. set MoveCaretToContentRect second parameter
     */
    richEditorPattern->MoveCaretToContentRect(offsetF, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    /**
     * @tc.steps: step3. set MoveCaretToContentRect first parameter
     */
    auto offsetFtemp = OffsetF(0.0f, 10.0f);
    richEditorPattern->MoveCaretToContentRect(offsetFtemp, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);
}

/**
 * @tc.name: InitScrollablePattern001
 * @tc.desc: test InitScrollablePattern
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, InitScrollablePattern001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->SetThemeManager(theme);

    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: GetThumbnailCallback002
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetThumbnailCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    richEditorPattern->InitDragDropEvent();
    EXPECT_EQ(richEditorPattern->dragNode_, nullptr);
}

/**
 * @tc.name: VirtualKeyboardAreaChanged002
 * @tc.desc: test OnVirtualKeyboardAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, VirtualKeyboardAreaChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    richEditorPattern->OnVirtualKeyboardAreaChanged();
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: test GetSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    richEditorPattern->selectedBackgroundColor_.reset();
    auto ret = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_NE(ret.GetValue(), 0);
}

/**
 * @tc.name: HandleOnDragDrop001
 * @tc.desc: test HandleOnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, HandleOnDragDrop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->HandleOnDragDrop(event);
    EXPECT_NE(event->GetData(), nullptr);
}

/**
 * @tc.name: ResetKeyboardIfNeed001
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, ResetKeyboardIfNeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = true;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: GetChangeSpanStyle001
 * @tc.desc: test GetChangeSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, GetChangeSpanStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;

    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);

    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(StringUtils::ToWstring(firstInfo.GetValue()).length());
    firstInfo.SetEraseLength(firstLength);
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    int32_t lastLength = static_cast<int32_t>(StringUtils::ToWstring(lastInfo.GetValue()).length());
    lastInfo.SetEraseLength(lastLength);

    std::optional<TextStyle> spanTextStyle;
    RefPtr<SpanNode> spanNode = OHOS::Ace::NG::SpanNode::CreateSpanNode(1);
    int32_t spanIndex = 0;
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step2. change parameter and call function.
    */
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    lastInfo.SetSpanIndex(richEditorPattern->spans_.size() - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
    /**
     * @tc.steps: step4. change parameter and call function.
    */
    lastInfo.SetEraseLength(lastLength - 1);
    richEditorPattern->GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, spanNode, spanIndex);
    EXPECT_FALSE(spanTextStyle.has_value());
}

/**
 * @tc.name: RichEditorPatternTestUpdatePreviewText003
 * @tc.desc: test UpdatePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorPatternTestUpdatePreviewText003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string previewTextValue;
    PreviewRange previewRange;

    previewRange.start = 0;
    previewRange.end = 0;
    ASSERT_EQ(richEditorPattern->UpdatePreviewText(previewTextValue, previewRange), false);
}

/**
 * @tc.name: RichEditorPatternTestSetPreviewText001
 * @tc.desc: test SetPreviewText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorPatternTestSetPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::string previewTextValue = INIT_VALUE_1;
    PreviewRange previewRange;

    previewRange.start = -1;
    previewRange.end = -1;
    ASSERT_EQ(richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange), 0);

    previewRange.start = 0;
    previewRange.end = -1;
    ASSERT_EQ(richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange), -1);

    previewRange.start = -1;
    previewRange.end = 0;
    ASSERT_EQ(richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange), -1);

    previewRange.start = 0;
    previewRange.end = 0;
    ASSERT_EQ(richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange), 0);
}

/**
 * @tc.name: RichEditorPatternTestGetPreviewTextStyle001
 * @tc.desc: test GetPreviewTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestNg, RichEditorPatternTestGetPreviewTextStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto layoutProperty = host->layoutProperty_;
    host->layoutProperty_ = nullptr;
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);
    host->layoutProperty_ = layoutProperty;

    ASSERT_NE(host->layoutProperty_, nullptr);
    auto property = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(property, nullptr);

    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);

    property->UpdatePreviewTextStyle("normal");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::NORMAL);

    property->UpdatePreviewTextStyle("underline");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);

    property->UpdatePreviewTextStyle("unknown");
    EXPECT_EQ(richEditorPattern->GetPreviewTextStyle(), PreviewTextStyle::UNDERLINE);
}
} // namespace OHOS::Ace::NG