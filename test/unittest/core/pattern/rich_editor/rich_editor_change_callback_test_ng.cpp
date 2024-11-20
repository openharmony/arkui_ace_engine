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
int32_t testOnSelect = 0;
} // namespace

class RichEditorChangeCallbackTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void ResetContentChangeCallbackState();
    void InitContentChangeCallback(RichEditorModelNG& richEditorModel);
    void InitDeleteCallback(RichEditorModelNG& richEditorModel);
};

void RichEditorChangeCallbackTestNg::SetUp()
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

void RichEditorChangeCallbackTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorChangeCallbackTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


void RichEditorChangeCallbackTestNg::ResetContentChangeCallbackState()
{
    isOnWillChangeCalled = false;
    isOnDidChangeCalled = false;
    onWillChangeValue.reset();
    onDidChangeValue.reset();
}

void RichEditorChangeCallbackTestNg::InitContentChangeCallback(RichEditorModelNG& richEditorModel)
{
    ResetContentChangeCallbackState();
    auto onWillChange = [](const RichEditorChangeValue& changeValue) {
        isOnWillChangeCalled = true;
        onWillChangeValue = changeValue;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    auto onDidChange = [](const RichEditorChangeValue& changeValue) {
        isOnDidChangeCalled = true;
        onDidChangeValue = changeValue;
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));
}

void RichEditorChangeCallbackTestNg::InitDeleteCallback(RichEditorModelNG& richEditorModel)
{
    aboutToDeleteValue = RichEditorDeleteValue();
    auto aboutToDelete = [](const RichEditorDeleteValue& deleteValue) {
        aboutToDeleteValue = deleteValue;
        return true;
    };
    richEditorModel.SetAboutToDelete(std::move(aboutToDelete));
}

/**
 * @tc.name: ChangeTextCallbackTest001
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest001, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return false;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with InsertValue When callback return false
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, false);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest002
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest002, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with AddTextSpan of TextStyle
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    TextStyle style;
    textOptions.offset = 1;
    textOptions.value = INIT_VALUE_2;
    textOptions.style = style;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest003
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest003, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with DeleteSpans
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    replacedCount = 0;
    afterCount = 0;
    RangeOptions delOptions;
    delOptions.start = 0;
    delOptions.end = 2;
    richEditorPattern->DeleteSpans(delOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(replacedCount, 0);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest004
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest004, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with InsertValue
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with multiLine
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->InsertValue("test\nvalue");
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 2);
    EXPECT_EQ(afterCount, 2);
}

/**
 * @tc.name: ChangeTextCallbackTest005
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest005, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with ResetAfterPaste
     * @tc.expected: return value is valid
     */
    richEditorPattern->pasteStr_ = INIT_VALUE_1;
    richEditorPattern->ResetAfterPaste();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest006
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest006, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with HandleOnDragDropTextOperation
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1);
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->caretPosition_ = 4;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->dragRange_.first = 0;
    richEditorPattern->dragRange_.second = 2;
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->HandleOnDragDropTextOperation("he", true);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 1);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest007
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest007, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with HandleOnUndoAction
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1);
    isWillCalled = false;
    isDidCalled = false;
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);

    /**
     * @tc.steps: step3. change text with HandleOnRedoAction
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest008
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest008, TestSize.Level1)
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
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan & DeleteSpans & HandleOnUndoAction
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    RangeOptions delOptions;
    delOptions.start = 0;
    delOptions.end = 2;
    richEditorPattern->DeleteSpans(delOptions);
    richEditorPattern->HandleOnUndoAction();

    /**
     * @tc.steps: step4. change text with HandleOnRedoAction
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(replacedCount, 0);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest009
 * @tc.desc: test for callback onWillchange/onDidChange, add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest009, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(isOnWillChangeCalled, true);
    EXPECT_EQ(isOnDidChangeCalled, true);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 0);
    EXPECT_EQ(onDidRangeAfter.end, 6); // length of INIT_VALUE_1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest010
 * @tc.desc: test for callback onWillchange/onDidChange, add text span then insert value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest010, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // content = hello1
    richEditorPattern->textSelector_.Update(1, 5); // select h[ello]1
    richEditorPattern->InsertValue(INIT_VALUE_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 1);
    EXPECT_EQ(onWillRangeBefore.end, 5);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.value_, "hhello11");
    EXPECT_EQ(spanResult.fontSize_, TEXT_STYLE_1.fontSize_.ConvertToPx());
    EXPECT_EQ(spanResult.offsetInSpan_, 1);
    EXPECT_EQ(spanResult.eraseLength_, 6);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 1);
    EXPECT_EQ(onDidRangeAfter.end, 7); // h[ello]1 -> h[hello1]1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest011
 * @tc.desc: test for callback onWillchange/onDidChange, add multi text span then insert value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest011, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    // content = hello1hello1hello1

    richEditorPattern->textSelector_.Update(1, 17); // select h[ello1hello1hello]1
    richEditorPattern->InsertValue(INIT_VALUE_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 1);
    EXPECT_EQ(onWillRangeBefore.end, 17);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.value_, "hhello1");
    EXPECT_EQ(spanResult.fontSize_, TEXT_STYLE_1.fontSize_.ConvertToPx());
    EXPECT_EQ(spanResult.offsetInSpan_, 1);
    EXPECT_EQ(spanResult.eraseLength_, 6);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 1);
    EXPECT_EQ(onDidRangeAfter.end, 7); // h[ello1hello1hello]1 -> h[hello1]1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest012
 * @tc.desc: test for callback onWillchange/onDidChange, add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest012, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 0);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 1);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedImageSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.offsetInSpan_, 0);
    EXPECT_EQ(spanResult.eraseLength_, 1);
    EXPECT_EQ(spanResult.width_, 200);
    EXPECT_EQ(spanResult.height_, 100);
    EXPECT_EQ(spanResult.verticalAlign_, VerticalAlign::CENTER);
    EXPECT_EQ(spanResult.objectFit_, ImageFit::COVER);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 0);
    EXPECT_EQ(onDidRangeAfter.end, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest013
 * @tc.desc: test for callback onWillchange/onDidChange, add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest013, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 0);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 1);

    auto& spanResult = onWillReplacedSymbolSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.offsetInSpan_, 0);
    EXPECT_EQ(spanResult.eraseLength_, 2);
    EXPECT_EQ(spanResult.spanRangeStart_, 0);
    EXPECT_EQ(spanResult.spanRangeEnd_, 2);
    EXPECT_EQ(spanResult.spanType_, SpanResultType::SYMBOL);
    EXPECT_EQ(spanResult.symbolSpanStyle_, SymbolSpanStyle(TEXT_STYLE_1));

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 0);
    EXPECT_EQ(onDidRangeAfter.end, 2);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest014
 * @tc.desc: test for callback onWillchange/onDidChange, add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest014, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 6);
    EXPECT_EQ(onWillRangeBefore.end, 6);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 0);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 1);

    auto& spanResult = onWillReplacedSymbolSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 1);
    EXPECT_EQ(spanResult.offsetInSpan_, 0);
    EXPECT_EQ(spanResult.eraseLength_, 2);
    EXPECT_EQ(spanResult.spanRangeStart_, 6);
    EXPECT_EQ(spanResult.spanRangeEnd_, 8);
    EXPECT_EQ(spanResult.spanType_, SpanResultType::SYMBOL);
    EXPECT_EQ(spanResult.symbolSpanStyle_, SymbolSpanStyle(TEXT_STYLE_1));

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 6);
    EXPECT_EQ(onDidRangeAfter.end, 8);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest015
 * @tc.desc: test for callback onWillchange/onDidChange, add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest015, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    auto options = SYMBOL_SPAN_OPTIONS_1;
    options.offset = 3;
    richEditorPattern->AddSymbolSpan(options);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 3);
    EXPECT_EQ(onWillRangeBefore.end, 3);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 0);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 1);

    auto& spanResult = onWillReplacedSymbolSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 1);
    EXPECT_EQ(spanResult.offsetInSpan_, 0);
    EXPECT_EQ(spanResult.eraseLength_, 2);
    EXPECT_EQ(spanResult.spanRangeStart_, 3);
    EXPECT_EQ(spanResult.spanRangeEnd_, 5);
    EXPECT_EQ(spanResult.spanType_, SpanResultType::SYMBOL);
    EXPECT_EQ(spanResult.symbolSpanStyle_, SymbolSpanStyle(TEXT_STYLE_1));

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 3);
    EXPECT_EQ(onDidRangeAfter.end, 5);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest016
 * @tc.desc: test for callback onWillchange/onDidChange, delete text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest016, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest017
 * @tc.desc: test for callback onWillchange/onDidChange, delete text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, ChangeTextCallbackTest017, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1

    richEditorPattern->SetCaretPosition(0);
    ASSERT_EQ(richEditorPattern->caretPosition_, 0);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    richEditorPattern->SetCaretPosition(6);
    ASSERT_EQ(richEditorPattern->caretPosition_, 6);
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(onWillRangeBefore.start, 6);
    EXPECT_EQ(onWillRangeBefore.end, 6);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: DeleteCallbackTest001
 * @tc.desc: test for aboutToDelete callback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, DeleteCallbackTest001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitDeleteCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    ASSERT_EQ(richEditorPattern->caretPosition_, 6);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 5);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 1);

    richEditorPattern->DeleteBackward(2);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 3);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 2);

    richEditorPattern->DeleteBackward(3);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 0);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 3);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: DeleteCallbackTest002
 * @tc.desc: test for aboutToDelete callback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, DeleteCallbackTest002, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitDeleteCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 7);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 6);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 1);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    richEditorPattern->UpdateSelector(3, 7);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 3);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 4);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: DeleteCallbackTest003
 * @tc.desc: test for aboutToDelete callback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, DeleteCallbackTest003, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitDeleteCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // add hello1
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 8);

    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 6);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 2);

    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    richEditorPattern->UpdateSelector(3, 7);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 3);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 8);
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(aboutToDeleteValue.GetOffset(), 3);
    EXPECT_EQ(aboutToDeleteValue.GetLength(), 5);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: HandleOnEditChanged001
 * @tc.desc: test Get focus edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleOnEditChanged001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Get the focus to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    richEditorPattern->HandleFocusEvent();
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged002
 * @tc.desc: test Lose focus edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleOnEditChanged002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Lose the focus to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged003
 * @tc.desc: test Long press edit status is keep false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleOnEditChanged003, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorController->IsEditing());

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Long press to trigger the callback function and keep preview state
     */

    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_FALSE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged004
 * @tc.desc: test Click on edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleOnEditChanged004, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Click on to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    richEditorPattern->HandleSingleClickEvent(info);
    richEditorPattern->HandleFocusEvent();
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged005
 * @tc.desc: test mouse release while dragging edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleOnEditChanged005, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. mouse release while dragging to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    MouseInfo info;
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc: test StopEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, StopEditingTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    richEditorPattern->caretTwinkling_ = true;
    richEditorController->StopEditing();

    EXPECT_FALSE(richEditorPattern->caretTwinkling_);

    ClearSpan();
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: test OnSubmitTest
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, OnSubmitTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);

    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](int32_t key, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));

    TextInputAction action2 = TextInputAction::NEW_LINE;
    bool forceCloseKeyboard = false;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 1);

    action2 = TextInputAction::DONE;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 2);
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 3);
    ClearSpan();
}

/**
 * @tc.name: OnScrollCallback
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, OnScrollCallback, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    int32_t SCROLL_FROM_START = 10;
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(0, SCROLL_FROM_START));

    int32_t SCROLL_FROM_UPDATE = 1;
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Reach Top Boundary";

    richEditorPattern->richTextRect_ = RectF(0, -40, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Reach Bottom Boundary";

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Scroll Up 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -10);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -10);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-50, SCROLL_FROM_UPDATE)) << "Scroll Up 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -40);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -40);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Scroll Down 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -30);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -30);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(50, SCROLL_FROM_UPDATE)) << "Scroll Down 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, 0);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), 0);
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, onIMEInputComplete, TestSize.Level1)
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
     * @tc.steps: step2. add text span
     */
    AddSpan(INIT_VALUE_1);
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    auto info = richEditorController->GetSpansInfo(0, 6);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_EQ(textStyle.leadingMarginSize[0], "5.00px");
    EXPECT_EQ(textStyle.leadingMarginSize[1], "10.00px");
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }

    ClearSpan();
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, onIMEInputComplete002, TestSize.Level1)
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
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    /**
     * @tc.steps: step3. add text span
     */
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    EXPECT_EQ(textStyle.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, onIMEInputComplete003, TestSize.Level1)
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
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    /**
     * @tc.steps: step3. add text span
     */
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: RichEditorModel008
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, RichEditorModel008, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: test on handle move done
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->onSelect_ = std::move(func);
    richEditorPattern->OnHandleMoveDone(RectF(0.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(testOnSelect, 1);
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, SetOnSelect, TestSize.Level1)
{
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
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, SetOnSelect2, TestSize.Level1)
{
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
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test Set On Select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, SetOnSelect003, TestSize.Level1)
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
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto spanNode = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test Set On Select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, SetOnSelect004, TestSize.Level1)
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
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto spanNode = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: test on handle move
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, OnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(richEditorPattern->caretPosition_, -1);

    richEditorPattern->caretPosition_ = -1;
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), false);
    EXPECT_EQ(richEditorPattern->caretPosition_, -1);
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: test OnAreaChangedInner
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, OnAreaChangedInner001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->OnAreaChangedInner();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    richEditorPattern->parentGlobalOffset_ = OffsetF(0, 1);

    richEditorPattern->OnAreaChangedInner();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<std::vector<int>> cases = { { 1, 1, 2, 2 }, { 1, 2, 2, 2 }, { 1, 1, 1, 2 }, { 1, 2, 1, 2 } };
    for (uint32_t i = 0; i < cases.size(); ++i) {
        richEditorPattern->HandleSurfaceChanged(cases[i][0], cases[i][1], cases[i][2], cases[i][3]);
        EXPECT_NE(richEditorPattern, nullptr);
    }
}

/**
 * @tc.name: AutoScrollByEdgeDetection001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, AutoScrollByEdgeDetection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "handle reach top edge";
    richEditorPattern->StopAutoScroll();

    auto handleHeight = 20;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1 - handleHeight, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - handleHeight + 1, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "handle reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection002
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, AutoScrollByEdgeDetection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::MOUSE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "mouse reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "mouse reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection003
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, AutoScrollByEdgeDetection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 540);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 500);
    richEditorPattern->frameRect_ = RectF(0, 0, 100, 500);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG };
    Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
    auto dragDistance = AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance - 10), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "drag reach top edge";
    auto speed = richEditorPattern->CalcDragSpeed(dragDistance, 0, dragDistance - 10);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, speed) << "darg speed move up";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->frameRect_.Bottom() - dragDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto pointY = richEditorPattern->frameRect_.Bottom() - dragDistance + 10;
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, pointY), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "drag reach bottom edge";
    speed = richEditorPattern->CalcDragSpeed(
        richEditorPattern->frameRect_.Bottom() - dragDistance, richEditorPattern->frameRect_.Bottom(), pointY);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, -speed) << "darg speed move down";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection004
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, AutoScrollByEdgeDetection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(50, 50);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE, .handleRect = RectF(50, 50, 20, 20) };
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, 50), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "the touch point is the same as the last time";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, edgeDistance - 1);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "content height is too small.";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: CheckScrollable
 * @tc.desc: test CheckScrollable.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeCallbackTestNg, CheckScrollable, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    AddSpan(TEST_INSERT_VALUE);
    richEditorPattern->CheckScrollable();
    EXPECT_TRUE(richEditorPattern->scrollable_);

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 80);
    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    ClearSpan();
}
} // namespace OHOS::Ace::NG