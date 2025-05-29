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
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testNumber0 = 0;
int32_t testNumber5 = 5;
const std::string TEST_IMAGE_SOURCE = "src/image.png";
constexpr float DEFAULT_CONTENT_WIDTH = 800.0f;
constexpr float DEFAULT_TEXT_HEIGHT = 50.0f;
} // namespace

class RichEditorOverlayTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    void RequestFocus();
    static void TearDownTestSuite();
};

void RichEditorOverlayTestNg::RequestFocus()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
}

void RichEditorOverlayTestNg::SetUp()
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

void RichEditorOverlayTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorOverlayTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: SelectedBackgroundColorTest001
 * @tc.desc: test set and get selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SelectedBackgroundColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    Color patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_EQ(patternSelectedBackgroundColor, SYSTEM_SELECT_BACKGROUND_COLOR);
    model.SetSelectedBackgroundColor(Color::RED);
    patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    auto selectedBackgroundColorResult = Color::RED.ChangeOpacity(DEFAILT_OPACITY);
    EXPECT_EQ(patternSelectedBackgroundColor, selectedBackgroundColorResult);
}

/**
 * @tc.name: MoveHandle
 * @tc.desc: test whether the handle is moved when scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, MoveHandle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textResponseType_ = TextResponseType::LONG_PRESS;
    richEditorPattern->selectOverlay_->ProcessOverlay({.animation = true});

    richEditorPattern->textSelector_.selectionBaseOffset = OffsetF(20, 20);
    richEditorPattern->textSelector_.firstHandle = RectF(20, 20, 20, 20);
    richEditorPattern->textSelector_.selectionDestinationOffset = OffsetF(60, 40);
    richEditorPattern->textSelector_.secondHandle = RectF(60, 40, 20, 20);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 30);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 30);

    richEditorPattern->OnScrollCallback(5, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 35);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 35);
}

/**
 * @tc.name: SingleHandle001
 * @tc.desc: test show single handle with empty text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;
    /**
     * @tc.steps: step1. first click does not show single handle
     */
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    richEditorPattern->HandleFocusEvent();
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step2. repeat click caret position show single handle
     */
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 50);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. double click or long press show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: SingleHandle002
 * @tc.desc: test show single handle with text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. first click does not show single handle
     */
    richEditorPattern->caretPosition_ = -1;
    GestureEvent info;
    info.localLocation_ = Offset(0, 5);
    richEditorPattern->HandleClickEvent(info);
    richEditorPattern->HandleFocusEvent();
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click caret position show single handle
     */
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step5. double click or long press the end of text show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step6. move single handle
     */
    auto handleOffset = OffsetF(0, 5);
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(handleOffset, false);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: SingleHandle003
 * @tc.desc: test move caret by touch event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, SingleHandle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. request foucus and show caret
     */
    RequestFocus();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->StartTwinkling();
    /**
     * @tc.steps: step3. touch down caret position
     */
    auto touchOffset = Offset(0, 0);
    AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_)
        ->SetCaretOffsetAndHeight(OffsetF(0, 0), 50.0f);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    textOverlayTheme->handleDiameter_ = 14.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = touchOffset;
    touchLocationInfo.SetSourceTool(SourceTool::FINGER);
    richEditorPattern->HandleTouchDown(touchLocationInfo);
    EXPECT_TRUE(richEditorPattern->moveCaretState_.isTouchCaret);
    /**
     * @tc.steps: step4. move caret position by touch move
     */
    touchLocationInfo.localLocation_ = Offset(50, 0);
    richEditorPattern->HandleTouchMove(touchLocationInfo);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
}

/**
 * @tc.name: UpdateSelectionType001
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, UpdateSelectionType001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo selection;

    ResultObject obj1;
    obj1.type = SelectSpanType::TYPESPAN;
    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::TEXT);

    selection.selection_.resultObjects.pop_front();
    ResultObject obj2;
    obj2.type = SelectSpanType::TYPEIMAGE;
    selection.selection_.resultObjects.push_front(obj2);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::IMAGE);

    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: test UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richeditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
	
    /**
     * @tc.steps: step2. add text
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(textOptions);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->SetSelection(0, 2);
	
    /**
     * @tc.steps: step3. create RichEditorPaintMethod
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
	
    /**
     * @tc.steps: step4. test UpdateOverlayModifier
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    const auto& selection = richEditorPattern->GetTextSelector();
    EXPECT_EQ(selection.baseOffset, -1);
    EXPECT_EQ(selection.destinationOffset, -1);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: CalculateSelectedRect001
 * @tc.desc: test CalculateSelectedRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, CalculateSelectedRect001, TestSize.Level1)
{
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> paragraphsRects;
    auto result = RichEditorPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_TRUE(result.empty());

    std::vector<RectF> rects;
    ParagraphStyle paragraphStyle;
    std::pair<std::vector<RectF>, ParagraphStyle> paragraphRects;

    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = RichEditorPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_TRUE(result.empty());

    rects.clear();
    paragraphsRects.clear();
    rects.emplace_back(RectF(0.0f, 0.0f, 0.0f, DEFAULT_TEXT_HEIGHT));
    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = RichEditorPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result.size(), rects.size());

    rects.clear();
    paragraphsRects.clear();
    rects.emplace_back(RectF(0.0f, 0.0f, 0.0f, DEFAULT_TEXT_HEIGHT));
    rects.emplace_back(RectF(0.0f, DEFAULT_TEXT_HEIGHT, 0.0f, DEFAULT_TEXT_HEIGHT));
    rects.emplace_back(RectF(0.0f, DEFAULT_TEXT_HEIGHT + DEFAULT_TEXT_HEIGHT, 0.0f, DEFAULT_TEXT_HEIGHT));
    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = RichEditorPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result.size(), rects.size());
}

/**
 * @tc.name: HandleLevel001
 * @tc.desc: Test RichEditorPattern Handle Level OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, HandleLevel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get rich editor pattern instance, then add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. show overlay
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    richEditorNode_->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_SCROLL);
    richEditorNode_->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(richEditorPattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: HandleLevel002
 * @tc.desc: Test RichEditorPattern Handle Level on FrameNode changed finish.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, HandleLevel002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get rich editor pattern instance, then add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. show overlay
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.steps: step3. mark framnode change finish.
     */
    richEditorNode_->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_END_SCROLL);
    richEditorNode_->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(richEditorPattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: OnCloseOverlay001
 * @tc.desc: test OnCloseOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, OnCloseOverlay001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    RefPtr<OverlayInfo> info = nullptr;
    info = AceType::MakeRefPtr<OverlayInfo>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->OnBackPressed(), false);
    auto offsetF = OffsetF(5.0f, 30.0f);
    RectF rect(testNumber0, testNumber0, testNumber5, testNumber5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, testNumber5);
    richEditorPattern->selectOverlay_->OnCloseOverlay(
        OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_BACK_PRESSED, info);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: Test GetGlyphPositionAtCoordinate.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level1)
{
    auto offset = Offset(50.0, -80.0);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    PositionWithAffinity position = richEditorPattern->paragraphs_.GetGlyphPositionAtCoordinate(offset);
    EXPECT_EQ(position.position_, 0);
}

/**
 * @tc.name: IsSelectLineHeadAndUseLeadingMargin001
 * @tc.desc: Test IsSelectLineHeadAndUseLeadingMargin.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, IsSelectLineHeadAndUseLeadingMargin001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool ret =richEditorPattern->paragraphs_.IsSelectLineHeadAndUseLeadingMargin(0);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RichEditorOverlayTestNg001
 * @tc.desc: Test onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));

    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richEditorOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richEditorOverlayModifier, nullptr);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    richEditorOverlayModifier->previewTextStyle_ = PreviewTextStyle::NORMAL;
    richEditorPattern->contentRect_ = RectF(0, 0, 10.0f, 10.0f);
    richEditorOverlayModifier->showPreviewTextDecoration_ = AceType::MakeRefPtr<PropertyBool>(1);
    richEditorOverlayModifier->caretVisible_ = AceType::MakeRefPtr<PropertyBool>(1);
    richEditorOverlayModifier->caretOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF(50, 30));
    richEditorOverlayModifier->caretWidth_ = AceType::MakeRefPtr<PropertyFloat>(10.0f);
    richEditorOverlayModifier->caretHeight_ = AceType::MakeRefPtr<PropertyFloat>(10.0f);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 10.0, 10.0);
    richEditorOverlayModifier->onDraw(context);
    EXPECT_EQ(richEditorPattern->contentRect_.Height(), 10.0f);

    richEditorPattern->contentRect_ = RectF(0, 0, 10.0f, 50.0f);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 100.0, 10.0);
    richEditorOverlayModifier->onDraw(context);
    richEditorOverlayModifier->contentRect_ = RectF(0, 0, 100.0, 100.0);
    richEditorOverlayModifier->onDraw(context);
    EXPECT_EQ(richEditorPattern->contentRect_.Height(), 50.0f);
}

/**
 * @tc.name: RichEditorOverlayTestNg002
 * @tc.desc: Test UpdateScrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richEditorOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richEditorOverlayModifier, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto  renderContext = RenderContext::Create();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    ASSERT_NE(geometryNode, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    richEditorPattern->InitScrollablePattern();
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));

    auto scrollBar = richEditorPattern->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    scrollBar->isScrollable_ = true;
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));
    scrollBar->positionModeUpdate_ = true;
    richEditorOverlayModifier->UpdateScrollBar(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: RichEditorOverlayTestNg003
 * @tc.desc: test OnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    AddImageSpan();

    richEditorPattern->ShowSelectOverlay(
    richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);

    richEditorPattern->selectOverlay_->hasTransform_ = false;
    richEditorPattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(1.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
}

/**
 * @tc.name: RichEditorOverlayTestNg004
 * @tc.desc: test CheckHandleVisible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(BUILDER_WIDTH, BUILDER_HEIGHT));

    richEditorPattern->selectOverlay_->enableHandleLevel_ = true;
    richEditorPattern->selectOverlay_->SetHandleLevelMode(HandleLevelMode::EMBED);
    auto isShow1 = richEditorPattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow1, true);

    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto isShow2 = richEditorPattern->selectOverlay_->CheckHandleVisible(RectF(0.0f, 0.0f, 10.0f, 10.0f));
    EXPECT_EQ(isShow2, true);
}

/**
 * @tc.name: RichEditorOverlayTestNg005
 * @tc.desc: test UpdateSelectorOnHandleMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(OffsetF(50.0f, 50.0f), false);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: RichEditorOverlayTestNg007
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::DISAPPEAR, OptionMenuType::MOUSE_MENU);
    EXPECT_TRUE(richEditorPattern->GetTextDetectEnable());
    EXPECT_FALSE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: RichEditorOverlayTestNg008
 * @tc.desc: test OnCloseOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg008, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;

    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    auto info = AceType::MakeRefPtr<OverlayInfo>();
    richEditorPattern->selectOverlay_->OnCloseOverlay(
        OptionMenuType::MOUSE_MENU, CloseReason::CLOSE_REASON_BACK_PRESSED, info);
    EXPECT_EQ(richEditorPattern->caretTwinkling_, true);
}

/**
 * @tc.name: RichEditorOverlayTestNg009
 * @tc.desc: test OnHandleLevelModeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg009, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto selectOverlay = richEditorPattern->selectOverlay_;
    ASSERT_NE(selectOverlay, nullptr);
    selectOverlay->handleLevelMode_ = HandleLevelMode::EMBED;
    selectOverlay->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(selectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    selectOverlay->handleLevelMode_ = HandleLevelMode::OVERLAY;
    selectOverlay->OnHandleLevelModeChanged(HandleLevelMode::EMBED);
    EXPECT_EQ(selectOverlay->handleLevelMode_, HandleLevelMode::EMBED);
}

/**
 * @tc.name: RichEditorOverlayTestNg010
 * @tc.desc: test OnAncestorNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorOverlayTestNg, RichEditorOverlayTestNg010, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    FrameNodeChangeInfoFlag flag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    richEditorPattern->selectOverlay_->OnAncestorNodeChanged(flag);
    EXPECT_EQ(richEditorPattern->selectOverlay_->IsAncestorNodeGeometryChange(flag), true);
}
} // namespace OHOS::Ace::NG