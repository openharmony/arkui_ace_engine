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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
bool isOnEditChangeCalled = false;

class RichEditorBaseTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    void GetFocus(const RefPtr<RichEditorPattern>& pattern);
    void OnDrawVerify(const SelectSpanType& type, const std::string& text, SymbolSpanOptions options, Offset offset,
        bool selected = false);
};

void RichEditorBaseTestOneNg::GetFocus(const RefPtr<RichEditorPattern>& pattern)
{
    ASSERT_NE(pattern, nullptr);
    auto focushHub = pattern->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern->HandleFocusEvent();
    FlushLayoutTask(richEditorNode_);
}


void RichEditorBaseTestOneNg::OnDrawVerify(
    const SelectSpanType& type, const std::string& text, SymbolSpanOptions options, Offset offset, bool selected)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentRect = richEditorNode_->GetGeometryNode()->GetContentRect();
    richEditorNode_->GetGeometryNode()->SetContentSize({100, 100});
    if (type == SelectSpanType::TYPESPAN) {
        AddSpan(text);
    } else if (type == SelectSpanType::TYPEIMAGE) {
        AddImageSpan();
    } else if (type == SelectSpanType::TYPESYMBOLSPAN) {
        auto richEditorController = richEditorPattern->GetRichEditorController();
        ASSERT_NE(richEditorController, nullptr);
        richEditorController->AddSymbolSpan(options);
    }

    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    GetFocus(richEditorPattern);

    if (!selected) {
        GestureEvent info;
        info.localLocation_ = offset;
        richEditorPattern->HandleClickEvent(info);
    } else {
        richEditorPattern->HandleOnSelectAll();
    }

    /**
     * @tc.steps: step2. Move handle
     */
    auto controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(OffsetF(1.0f, 1.0f));

    /**
     * @tc.steps: step3. Test magnifier open or close
     * @tc.expected: magnifier is open
     */
    auto ret = controller->GetShowMagnifier();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Craete RichEditorOverlayModifier
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richFieldOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step5. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step6. Do onDraw(context)
     */
    richFieldOverlayModifier->onDraw(context);

    /**
     * @tc.steps: step7. When handle move done
     */
    richEditorPattern->selectOverlay_->ProcessOverlay();
    RectF handleRect;
    richEditorPattern->selectOverlay_->OnHandleMoveDone(handleRect, true);

    /**
     * @tc.steps: step8. Test magnifier open or close
     * @tc.expected: magnifier is close
     */
    ret = controller->GetShowMagnifier();
    EXPECT_FALSE(ret);
    richEditorNode_->GetGeometryNode()->SetContentSize(contentRect.GetSize());
}

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
        isOnEditChangeCalled = value;
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
     * @tc.expected: expect isOnEditChangeCalled is true
     */
    eventHub->FireOnEditingChange(true);
    EXPECT_EQ(isOnEditChangeCalled, true);

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
    AddSpan(INIT_U16VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorController->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_U16VALUE_1);
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
    AddSpan(INIT_U16VALUE_1);
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

    AddSpan(INIT_U16VALUE_1);
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

    std::u16string str = u"\n";
    spanItem->content = str;
    spans.emplace_back(spanItem);
    auto layoutAlgorithm = AceType::MakeRefPtr<RichEditorLayoutAlgorithm>(spans, AceType::RawPtr(paragraphManager),
        std::nullopt);
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_NE(*(layoutAlgorithm->allSpans_.begin()), nullptr);
}
} // namespace OHOS::Ace::NG
