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
#include "core/components/text_field/textfield_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void RichEditorCommonTestNg::AddSpan(const std::string& content)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SpanModelNG spanModelNG;
    spanModelNG.Create(content);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontWeight(FONT_WEIGHT_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    spanModelNG.SetTextShadow(SHADOWS);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    spanNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    richEditorPattern->spans_.emplace_back(spanNode->spanItem_);
    richEditorPattern->childNodes_.push_back(spanNode);
    richEditorPattern->UpdateSpanPosition();
}

void RichEditorCommonTestNg::AddImageSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSourceInfo imageInfo(IMAGE_VALUE, BUNDLE_NAME, MODULE_NAME);
    imageLayoutProperty->UpdateImageSourceInfo(imageInfo);
    imageNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = " ";
    spanItem->placeholderIndex = 0;
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto& span : richEditorPattern->spans_) {
        spanTextLength += StringUtils::ToWstring(span->content).length();
        span->position = spanTextLength;
    }
}

void RichEditorCommonTestNg::AddParagraph(TestParagraphItem testParagraphItem)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testParagraphItem.start, .end = testParagraphItem.end });
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offset, _)).WillRepeatedly(Return(index));
        PositionWithAffinity positionWithAffinity(index, TextAffinity::UPSTREAM);
        EXPECT_CALL(*paragraph, GetGlyphPositionAtCoordinate(offset)).WillRepeatedly(Return(positionWithAffinity));
    }
    for (auto& cursorItem : testParagraphItem.testCursorItems) {
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFUp), Return(true)));
        float cursorHeight = 0.0f;
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, true),
            cursorItem.caretMetricsFDown.offset);
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, false),
            cursorItem.caretMetricsFUp.offset);
    }
    for (auto& paragraphRect : testParagraphItem.testParagraphRects) {
        EXPECT_CALL(*paragraph, GetRectsForRange(paragraphRect.start, paragraphRect.end, _))
            .WillRepeatedly(SetArgReferee<THIRD_PARAM>(paragraphRect.rects));
    }
}

void RichEditorCommonTestNg::ClearParagraph()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.Reset();
}

void RichEditorCommonTestNg::ClearSpan()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->children_.clear();
    richEditorPattern->spans_.clear();
    richEditorPattern->caretPosition_ = 0;
}

void RichEditorCommonTestNg::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
{
    EXPECT_CALL(mockDataDetectorMgr, GetCursorPosition(_, _))
        .WillRepeatedly([](const std::string& text, int8_t offset) -> int8_t {
            if (text.empty()) {
                return DEFAULT_RETURN_VALUE;
            }
            if (text.length() <= WORD_LIMIT_LEN) {
                return WORD_LIMIT_RETURN;
            } else {
                return BEYOND_LIMIT_RETURN;
            }
        });

    EXPECT_CALL(mockDataDetectorMgr, GetWordSelection(_, _))
        .WillRepeatedly([](const std::string& text, int8_t offset) -> std::vector<int8_t> {
            if (text.empty()) {
                return std::vector<int8_t> { -1, -1 };
            }

            if (text.length() <= WORD_LIMIT_LEN) {
                return std::vector<int8_t> { 2, 3 };
            } else {
                return std::vector<int8_t> { 0, 2 };
            }
        });
}

void RichEditorCommonTestNg::RequestFocus()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
}

void RichEditorCommonTestNg::GetFocus(const RefPtr<RichEditorPattern>& pattern)
{
    ASSERT_NE(pattern, nullptr);
    auto focushHub = pattern->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern->HandleFocusEvent();
    FlushLayoutTask(richEditorNode_);
}

void RichEditorCommonTestNg::OnDrawVerify(
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

void RichEditorCommonTestNg::InitMagnifierParams(const SizeF& frameSize)
{
    // set frameSize to RichEditor
    ASSERT_NE(richEditorNode_, nullptr);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(frameSize);

    // set frameSize to RootNode
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto rootUINode = pipeline->GetRootElement();
    ASSERT_NE(rootUINode, nullptr);
    auto rootGeometryNode = rootUINode->GetGeometryNode();
    ASSERT_NE(rootGeometryNode, nullptr);
    rootGeometryNode->SetFrameSize(frameSize);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textfieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textfieldTheme));
}
} // namespace OHOS::Ace::NG