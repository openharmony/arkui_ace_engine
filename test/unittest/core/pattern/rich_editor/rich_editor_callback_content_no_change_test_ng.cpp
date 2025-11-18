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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnSelect = 1;
bool g_isOnWillChangeCalled = false;
bool g_isOnDidChangeCalled = false;
RichEditorChangeValue onWillChangeValue;
RichEditorChangeValue onDidChangeValue;
RichEditorDeleteValue aboutToDeleteValue;
} // namespace

class RichEditorCallbackContentNoChangeTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void ResetContentChangeCallbackState();
    void InitContentChangeCallback(RichEditorModelNG& richEditorModel);
    void InitDeleteCallback(RichEditorModelNG& richEditorModel);
};

void RichEditorCallbackContentNoChangeTestNg::SetUp()
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

void RichEditorCallbackContentNoChangeTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorCallbackContentNoChangeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}


void RichEditorCallbackContentNoChangeTestNg::ResetContentChangeCallbackState()
{
    g_isOnWillChangeCalled = false;
    g_isOnDidChangeCalled = false;
    onWillChangeValue.reset();
    onDidChangeValue.reset();
}

void RichEditorCallbackContentNoChangeTestNg::InitContentChangeCallback(RichEditorModelNG& richEditorModel)
{
    ResetContentChangeCallbackState();
    auto onWillChange = [](const RichEditorChangeValue& changeValue) {
        g_isOnWillChangeCalled = true;
        onWillChangeValue = changeValue;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    auto onDidChange = [](const RichEditorChangeValue& changeValue) {
        g_isOnDidChangeCalled = true;
        onDidChangeValue = changeValue;
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));
}

void RichEditorCallbackContentNoChangeTestNg::InitDeleteCallback(RichEditorModelNG& richEditorModel)
{
    aboutToDeleteValue = RichEditorDeleteValue();
    auto aboutToDelete = [](const RichEditorDeleteValue& deleteValue) {
        aboutToDeleteValue = deleteValue;
        return true;
    };
    richEditorModel.SetAboutToDelete(std::move(aboutToDelete));
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, SetOnSelect, TestSize.Level0)
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
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, SetOnSelect2, TestSize.Level0)
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
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, SetOnSelect003, TestSize.Level0)
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
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
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
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, SetOnSelect004, TestSize.Level0)
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
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto spanNode = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
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
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, OnHandleMove001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), false);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: test OnAreaChangedInner
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, OnAreaChangedInner001, TestSize.Level0)
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
    EXPECT_NE(richEditorPattern->parentGlobalOffset_, OffsetF(0, 1));
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, HandleSurfaceChanged001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<std::vector<int>> cases = { { 1, 1, 2, 2 }, { 1, 2, 2, 2 }, { 1, 1, 1, 2 }, { 1, 2, 1, 2 } };
    for (uint32_t i = 0; i < cases.size(); ++i) {
        richEditorPattern->HandleSurfaceChanged(
            cases[i][0], cases[i][1], cases[i][2], cases[i][3], WindowSizeChangeReason::DRAG);
        EXPECT_NE(richEditorPattern, nullptr);
    }
}

/**
 * @tc.name: IsStopBackPress001
 * @tc.desc: test IsStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, IsStopBackPress001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isStopBackPress_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    auto result = richEditorPattern->OnBackPressed();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnBackPressed001
 * @tc.desc: test OnBackPressed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCallbackContentNoChangeTestNg, OnBackPressed001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);

    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);

    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    auto func = []() {};
    richEditorPattern->SetCustomKeyboard(func);
    richEditorPattern->RequestCustomKeyboard();
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);

    richEditorPattern->imeShown_ = true;
    EXPECT_EQ(richEditorPattern->OnBackPressed(), true);
}

} // namespace OHOS::Ace::NG