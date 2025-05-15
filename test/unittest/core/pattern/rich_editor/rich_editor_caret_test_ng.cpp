/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


#include <memory>

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorCaretTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorCaretTestNg::SetUp()
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

void RichEditorCaretTestNg::TearDown()
{
    richEditorNode_.Reset();
    MockParagraph::TearDown();
}

void RichEditorCaretTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetCaretColor001
 * @tc.desc: test GetCaretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, GetCaretColor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->caretColor_.reset();
    auto ret = richEditorPattern->GetCaretColor();
    EXPECT_NE(ret.GetValue(), 0);
}

/**
 * @tc.name: MoveCaretToContentRect001
 * @tc.desc: test MoveCaretToContentRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, MoveCaretToContentRect001, TestSize.Level1)
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

    int32_t scrollFromUpdate = 1;
    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 5, 100, 160);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, scrollFromUpdate));

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
 * @tc.name: CaretColorTest001
 * @tc.desc: test set and get caretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, CaretColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    Color patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, SYSTEM_CARET_COLOR);
    model.SetCaretColor(Color::BLUE);
    patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, Color::BLUE);
}

/**
 * @tc.name: SetCaretPosition001
 * @tc.desc: test SetCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, SetCaretPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"SetCaretPosition");
    richEditorPattern->caretChangeListener_ = [](int32_t x) {};
    EXPECT_TRUE(richEditorPattern->SetCaretPosition(2, false));
}

/**
 * @tc.name: RepeatClickCaret001
 * @tc.desc: test RepeatClickCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, RepeatClickCaret001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretTwinkling_ = true;
    Offset offset = Offset(50.0, 50.0);
    RectF lastCaretRect;
    EXPECT_FALSE(richEditorPattern->RepeatClickCaret(offset, lastCaretRect));
}

/**
 * @tc.name: GetCaretMetrics001
 * @tc.desc: test GetCaretMetrics
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, GetCaretMetrics001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    CaretMetricsF caretCaretMetric;
    caretCaretMetric.height = 10.0f;
    richEditorPattern->GetCaretMetrics(caretCaretMetric);
    EXPECT_EQ(caretCaretMetric.height, 0.0f);
}

/**
 * @tc.name: CalcCaretMetricsByPosition001
 * @tc.desc: Test the paragraph manager function.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, CalcCaretMetricsByPosition001, TestSize.Level1)
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

/**
 * @tc.name: GetCaretOffsetInfoByPosition001
 * @tc.desc: test GetCaretOffsetInfoByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, GetCaretOffsetInfoByPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo result = richEditorPattern->GetCaretOffsetInfoByPosition(1);
    EXPECT_EQ(result.caretOffsetUp.GetX(), 0);
    EXPECT_EQ(result.caretOffsetUp.GetY(), 0);
}

/**
 * @tc.name: CalculateEmptyValueCaretRect001
 * @tc.desc: test RichEditorPattern CalculateEmptyValueCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, CalculateEmptyValueCaretRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    TestParagraphItem testParagraphItem = {
        .start = 0, .end = 6, .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } }
    };
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 6 });
    CaretMetricsF metricsDown;
    CaretMetricsF metricsUp;
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        metricsDown.offset.SetX(offset.GetX());
        metricsDown.offset.SetY(offset.GetY());
        metricsUp.offset.SetX(offset.GetX());
        metricsUp.offset.SetY(offset.GetY());
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
        EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
        EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsUp), Return(true)));
    }

    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    auto layoutProperty = richEditorPattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    richEditorPattern->presetParagraph_ = paragraph;
    richEditorPattern->CalculateEmptyValueCaretRect();
    richEditorPattern->typingTextStyle_ = style;
    richEditorPattern->PreferredParagraph();
    EXPECT_NE(richEditorPattern->presetParagraph_, nullptr);
}

/**
 * @tc.name: CalculateEmptyValueCaretRect002
 * @tc.desc: test CalculateEmptyValueCaretRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, CalculateEmptyValueCaretRect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto layoutProperty = richEditorPattern->GetLayoutProperty<TextLayoutProperty>();

    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty->UpdateTextAlign(TextAlign::LEFT);
    richEditorPattern->CalculateEmptyValueCaretRect();

    layoutProperty->UpdateLayoutDirection(TextDirection::INHERIT);
    layoutProperty->UpdateTextAlign(TextAlign::CENTER);
    richEditorPattern->CalculateEmptyValueCaretRect();

    layoutProperty->UpdateLayoutDirection(TextDirection::INHERIT);
    layoutProperty->UpdateTextAlign(TextAlign::LEFT);
    richEditorPattern->CalculateEmptyValueCaretRect();

    EXPECT_EQ(richEditorPattern->presetParagraph_, false);
}

/**
 * @tc.name: SetCaretOffset001
 * @tc.desc: test SetCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, SetCaretOffset001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = u"abc";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;

    bool res = richEditorPattern->SetCaretOffset(0);
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: SetCaretOffset002
 * @tc.desc: test SetCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, SetCaretOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. add span
     */
    AddSpan(u"test");
    EXPECT_FALSE(richEditorPattern->caretVisible_);

    /**
     * @tc.step: step3. Request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.steps: step4. call the callback function
     */
    richEditorPattern->SetCaretOffset(2);
    EXPECT_TRUE(richEditorPattern->caretTwinkling_);
    EXPECT_TRUE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: MoveCaretAndStartFocus001
 * @tc.desc: test MoveCaretAndStartFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, MoveCaretAndStartFocus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    Offset textOffset;
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->MoveCaretAndStartFocus(textOffset);
    EXPECT_TRUE(focusHub->RequestFocusImmediately());
}

/**
 * @tc.name: IsCaretInContentArea001
 * @tc.desc: test IsCaretInContentArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, IsCaretInContentArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    auto ret = richEditorPattern->IsCaretInContentArea();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: FloatingCaretTest001
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, FloatingCaretTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(options);

    CaretMetricsF caretMetricsBegin = { OffsetF(20.0f, 0), 50.0f };
    CaretMetricsF caretMetricsEnd = { OffsetF(100.0f, 0), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 7,
        .testCursorItems = { { 0, caretMetricsBegin, caretMetricsBegin}, {6, caretMetricsEnd, caretMetricsEnd} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::DOWNSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(0.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(0.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(20.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(20.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);

    richEditorPattern->caretPosition_ = 6;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
}

/**
 * @tc.name: FloatingCaretTest002
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, FloatingCaretTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorPattern->AddTextSpan(options);

    CaretMetricsF caretMetricsLineEndUp = { OffsetF(100.0f, 0), 50.0f };
    CaretMetricsF caretMetricsLineEndDown = { OffsetF(0, 50.0f), 50.0f };
    CaretMetricsF caretMetricsInLine = { OffsetF(50.0f, 0), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 38,
        .testCursorItems = { { 5, caretMetricsInLine, caretMetricsInLine},
        { 10, caretMetricsLineEndDown, caretMetricsLineEndUp} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(50.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(50.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(70.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(70.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);

    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(100.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_FALSE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.touchMoveOffset.has_value());
    EXPECT_EQ(richEditorPattern->floatingCaretState_.touchMoveOffset.value(), Offset(120.0, 0));
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isFloatingCaretVisible);
    EXPECT_TRUE(richEditorPattern->floatingCaretState_.isOriginCaretVisible);
}

/**
 * @tc.name: FloatingCaretTest003
 * @tc.desc: test FloatingCaret
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, FloatingCaretTest003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    ASSERT_NE(richEditorOverlay, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);

    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorPattern->AddTextSpan(options);
    CaretMetricsF caretMetricsLineEndUp = { OffsetF(100.0f, 0), 50.0f };
    CaretMetricsF caretMetricsLineEndDown = { OffsetF(0, 50.0f), 50.0f };
    TestParagraphItem paragraphItem = { .start = 0, .end = 38,
        .testCursorItems = { { 10, caretMetricsLineEndDown, caretMetricsLineEndUp} } };
    AddParagraph(paragraphItem);
    richEditorPattern->richTextRect_.SetSize({ 200.f, 200.f });
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };

    richEditorPattern->caretPosition_ = 10;
    richEditorPattern->floatingCaretState_.Reset();
    richEditorPattern->caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    richEditorPattern->SetCaretTouchMoveOffset(Offset(100.0, 0));
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(richEditorOverlay->floatingCaretOffset_->Get(), OffsetF(100.0f, 0));
    EXPECT_TRUE(richEditorOverlay->floatingCaretVisible_->Get());
    EXPECT_FALSE(richEditorOverlay->originCaretVisible_->Get());
    richEditorPattern->SetCaretTouchMoveOffset(Offset(120.0, 0));
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(richEditorOverlay->floatingCaretOffset_->Get(), OffsetF(120.0f, 0));
    EXPECT_TRUE(richEditorOverlay->floatingCaretVisible_->Get());
    EXPECT_TRUE(richEditorOverlay->originCaretVisible_->Get());
}

/**
 * @tc.name: ScheduleCaretTwinkling001
 * @tc.desc: test ScheduleCaretTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, ScheduleCaretTwinkling001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    richEditorPattern->ScheduleCaretTwinkling();
    EXPECT_NE(context->GetCurrentContext(), nullptr);
}

/**
 * @tc.name: ScheduleCaretTwinkling002
 * @tc.desc: test ScheduleCaretTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, ScheduleCaretTwinkling002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = nullptr;
    richEditorPattern->ScheduleCaretTwinkling();
    EXPECT_EQ(context->GetTaskExecutor(), nullptr);
}

/**
 * @tc.name: GetCaretRect001
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, GetCaretRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    EXPECT_EQ(richEditorOverlay->GetCaretOffset(), OffsetF(80.0f, 100.0f));
    EXPECT_EQ(richEditorOverlay->GetCaretHeight(), 60.0f);
    EXPECT_EQ(caretRect.GetOffset(), richEditorOverlay->GetCaretOffset());
    EXPECT_EQ(caretRect.Height(), richEditorOverlay->GetCaretHeight());
}

/**
 * @tc.name: GetCaretRect002
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, GetCaretRect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    manager->SetClickPosition({ caretRect.GetOffset().GetX(), caretRect.GetOffset().GetY() });
    manager->SetHeight(caretRect.Height());
    manager->ScrollTextFieldToSafeArea();
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetX(), 0.0f), true);
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetY(), 0.0f), true);

    EXPECT_EQ(GreatNotEqual(manager->GetHeight(), 0.0f), true);
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);
}

/**
 * @tc.name: MoveCaretAfterTextChange001
 * @tc.desc: test move caret after text change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, MoveCaretAfterTextChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->moveDirection_ = MoveDirection::BACKWARD;
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 4);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection::FORWARD;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection(-1);
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
}

/**
 * @tc.name: SetCaretWidth001
 * @tc.desc: test SetCaretWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, SetCaretWidth001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretWidth(-1);
    EXPECT_NE(richEditorOverlay->caretWidth_, -1);
    float tagertCaretWidth = static_cast<float>(Dimension(2.0f, DimensionUnit::VP).ConvertToPx());
    EXPECT_EQ(tagertCaretWidth, richEditorPattern->GetCaretWidth());
}

/**
 * @tc.name: OnCaretTwinkling001
 * @tc.desc: test on caret twinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCaretTestNg, OnCaretTwinkling001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->OnCaretTwinkling();
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

}