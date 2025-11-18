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

#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "text_base.h"

#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"

namespace OHOS::Ace::NG {

namespace {
const std::string SYMBOL_FONT_FAMILY = "Symbol_Test_CustomSymbol";
} // namespace

class TextTestFiveNg : public TextBases {
public:
};

/**
 * @tc.name: CalcHandleLevelMode001
 * @tc.desc: test base_text_select_overlay.cpp CalcHandleLevelMode function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CalcHandleLevelMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    ASSERT_NE(frameNode->GetGeometryNode(), nullptr);

    frameNode->GetGeometryNode()->SetFrameSize(SizeF(10, 10));
    textSelectOverlay->isChangeToOverlayModeAtEdge_ = false;

    RectF firstRect(3, 3, 5, 5);
    RectF secondRect(4, 4, 6, 6);

    textSelectOverlay->CalcHandleLevelMode(firstRect, secondRect);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::EMBED);

    firstRect.SetRect(3, 3, 5, 5);
    secondRect.SetRect(11, 11, 15, 15);

    textSelectOverlay->CalcHandleLevelMode(firstRect, secondRect);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: OnAncestorNodeChanged001
 * @tc.desc: test base_text_select_overlay.cpp OnAncestorNodeChanged function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, OnAncestorNodeChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    FrameNodeChangeInfoFlag frameNodeChangeInfoFlag = 0;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_START_SCROLL;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_START_ANIMATION;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);
    auto viewPort = textSelectOverlay->GetAncestorNodeViewPort();
    ASSERT_TRUE(viewPort.has_value());
    EXPECT_EQ(viewPort.value(), RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: OnHandleMarkInfoChange001
 * @tc.desc: test base_text_select_overlay.cpp OnHandleMarkInfoChange function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, OnHandleMarkInfoChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    textSelectOverlay->OnBind(manager);

    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    SelectOverlayDirtyFlag flag = DIRTY_HANDLE_COLOR_FLAG;
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->handlerColor, std::nullopt);

    flag = DIRTY_FIRST_HANDLE;
    shareOverlayInfo->menuInfo.showTranslate = false;
    textSelectOverlay->SetMenuTranslateIsSupport(false);
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showTranslate, false);

    flag = DIRTY_SECOND_HANDLE;
    shareOverlayInfo->menuInfo.showTranslate = true;
    textSelectOverlay->SetMenuTranslateIsSupport(true);
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showTranslate, false);

    flag = DIRTY_FIRST_HANDLE;
    shareOverlayInfo->menuInfo.showSearch = false;
    textSelectOverlay->SetIsSupportMenuSearch(false);
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showSearch, false);

    shareOverlayInfo->menuInfo.showShare = false;
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showShare, false);

    flag = DIRTY_SECOND_HANDLE;
    shareOverlayInfo->menuInfo.showSearch = true;
    textSelectOverlay->SetIsSupportMenuSearch(true);
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showSearch, false);

    shareOverlayInfo->menuInfo.showShare = true;
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->menuInfo.showShare, false);
}

/**
 * @tc.name: IsNeedMenuTranslate001
 * @tc.desc: test base_text_select_overlay.cpp IsNeedMenuTranslate function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsNeedMenuTranslate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    EXPECT_EQ(textSelectOverlay->IsNeedMenuTranslate(), false);
}

/**
 * @tc.name: HandleOnTranslate001
 * @tc.desc: test base_text_select_overlay.cpp HandleOnTranslate function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HandleOnTranslate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    textSelectOverlay->HandleOnTranslate();
    EXPECT_EQ(pattern->GetTextSelector().GetTextStart(), -1);
    EXPECT_EQ(pattern->GetTextSelector().GetTextEnd(), -1);
}

/**
 * @tc.name: IsNeedMenuSearch001
 * @tc.desc: test base_text_select_overlay.cpp IsNeedMenuSearch function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsNeedMenuSearch001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    EXPECT_EQ(textSelectOverlay->IsNeedMenuSearch(), false);
}

/**
 * @tc.name: HandleOnSearch001
 * @tc.desc: test base_text_select_overlay.cpp HandleOnSearch function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HandleOnSearch001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    textSelectOverlay->HandleOnSearch();
    EXPECT_EQ(pattern->GetTextSelector().GetTextStart(), -1);
    EXPECT_EQ(pattern->GetTextSelector().GetTextEnd(), -1);
}

/**
 * @tc.name: IsNeedMenuShare001
 * @tc.desc: test base_text_select_overlay.cpp IsNeedMenuShare function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsNeedMenuShare001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    EXPECT_EQ(textSelectOverlay->IsNeedMenuShare(), false);
}

/**
 * @tc.name: IsNeedMenuShare002
 * @tc.desc: test base_text_select_overlay.cpp IsNeedMenuShare function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsNeedMenuShare002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    pattern->textForDisplay_ = TEXT_U16CONTENT;

    EXPECT_EQ(textSelectOverlay->IsNeedMenuShare(), false);
}

/**
 * @tc.name: HandleOnShare001
 * @tc.desc: test base_text_select_overlay.cpp HandleOnShare function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HandleOnShare001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    textSelectOverlay->HandleOnShare();
    EXPECT_EQ(pattern->GetTextSelector().GetTextStart(), -1);
    EXPECT_EQ(pattern->GetTextSelector().GetTextEnd(), -1);
}

/**
 * @tc.name: GetSpanParagraphStyle001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp GetSpanParagraphStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpanParagraphStyle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    ParagraphStyle pStyle;

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->textLineStyle->UpdateMaxLines(1024);
    spanItem->textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);
    spanItem->textLineStyle->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    spanItem->textLineStyle->UpdateLeadingMargin(LeadingMargin());
    ParagraphUtil::GetSpanParagraphStyle(nullptr, spanItem, pStyle);
    EXPECT_EQ(pStyle.maxLines, 1024);
    EXPECT_EQ(pStyle.ellipsisMode, EllipsisMode::HEAD);
    EXPECT_EQ(pStyle.lineBreakStrategy, LineBreakStrategy::GREEDY);
}

/**
 * @tc.name: FontRegisterCallback001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp FontRegisterCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, FontRegisterCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    TextStyle textStyle;
    std::vector<std::string> fontFamilies;

    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    textStyle.SetFontFamilies(fontFamilies);

    textLayoutAlgorithm->FontRegisterCallback(frameNode, textStyle);
    EXPECT_EQ(pattern->GetIsCustomFont(), false);

    pipeline->SetIsFormRender(true);
    textLayoutAlgorithm->FontRegisterCallback(frameNode, textStyle);
    EXPECT_EQ(pattern->GetIsCustomFont(), false);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateTextColorIfForeground001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateTextColorIfForeground function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateTextColorIfForeground001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    TextStyle textStyle;

    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    textLayoutAlgorithm->UpdateTextColorIfForeground(frameNode, textStyle, Color::BLACK);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);

    textStyle.SetTextColor(Color::BLACK);
    renderContext->UpdateForegroundColor(Color::BLACK);

    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetTextColorValue(Color::RED), Color::BLACK);
}

/**
 * @tc.name: UpdateParagraphBySpan001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateParagraphBySpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraphBySpan001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto spanNode = AceType::MakeRefPtr<ImageSpanNode>("Test1", 1, pattern);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    textLayoutAlgorithm->spans_.emplace_back(spanItem);

    ParagraphStyle paraStyle;
    TextStyle textStyle;

    paraStyle.maxLines = 1024;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    textLayoutAlgorithm->spanStringHasMaxLines_ = true;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    textLayoutAlgorithm->spanStringHasMaxLines_ = false;
    textLayoutAlgorithm->isSpanStringMode_ = true;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    textLayoutAlgorithm->paragraphManager_->AddParagraph(
        { .paragraph = paragraph, .start = 0, .end = 2 });
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    std::list<RefPtr<SpanItem>> group;
    spanNode = AceType::MakeRefPtr<ImageSpanNode>("Test2", 2, pattern);
    ASSERT_NE(spanNode, nullptr);
    spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    group.emplace_back(spanItem);
    auto spanNode1 = AceType::MakeRefPtr<PlaceholderSpanNode>("Test", 3, pattern);
    ASSERT_NE(spanNode1, nullptr);
    auto spanItem1 = spanNode1->GetSpanItem();
    ASSERT_NE(spanItem1, nullptr);
    group.emplace_back(spanItem1);
    textLayoutAlgorithm->spans_.emplace_back(group);
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);
}

/**
 * @tc.name: UpdateParagraphByCustomSpan001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateParagraphByCustomSpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraphByCustomSpan001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    auto oldTheme = pipeline->themeManager_;
    pipeline->themeManager_ = theme;

    auto customSpanItem = AceType::MakeRefPtr<CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t spanTextLength;
    CustomSpanPlaceholderInfo customSpanPlaceholder;

    textLayoutAlgorithm->UpdateParagraphByCustomSpan(
        customSpanItem, paragraph, spanTextLength, customSpanPlaceholder);
    EXPECT_EQ(customSpanPlaceholder.onDraw, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateFontSize(Dimension(10.0));
    customSpanItem->onMeasure = [](CustomSpanMeasureInfo info)->CustomSpanMetrics {
        return CustomSpanMetrics();
    };
    customSpanItem->onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {
    };

    textLayoutAlgorithm->UpdateParagraphByCustomSpan(
        customSpanItem, paragraph, spanTextLength, customSpanPlaceholder);
    EXPECT_NE(customSpanPlaceholder.onDraw, nullptr);

    pipeline->themeManager_ = oldTheme;
}

/**
 * @tc.name: UpdateParagraph001
 * @tc.desc: test span_node.cpp UpdateParagraph function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraph001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    ASSERT_NE(fontManager, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = fontManager;

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    spanItem->UpdateParagraph(frameNode, paragraph, true);

    pattern->textDetectEnable_ = true;
    pattern->copyOption_ = CopyOptions::InApp;
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(spanItem->UpdateParagraph(frameNode, paragraph, true), -1);

    spanItem->aiSpanMap.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(spanItem->UpdateParagraph(frameNode, paragraph, true), -1);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateSymbolSpanParagraph001
 * @tc.desc: test span_node.cpp UpdateSymbolSpanParagraph function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanParagraph001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount](){ callPushStyleCount++; });

    EXPECT_EQ(callPushStyleCount, 0);

    spanItem->fontStyle->UpdateFontSize(Dimension(0));
    spanItem->UpdateSymbolSpanParagraph(nullptr, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 1);

    std::unique_ptr<FontStyle> oldFontStyle = std::move(spanItem->fontStyle);
    std::unique_ptr<TextLineStyle> oldTextLineStyle = std::move(spanItem->textLineStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    spanItem->textLineStyle = std::move(oldTextLineStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    spanItem->fontStyle = std::move(oldFontStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 3);
}

/**
 * @tc.name: UpdateSymbolSpanParagraph002
 * @tc.desc: test span_node.cpp UpdateSymbolSpanParagraph function for customSymbol
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanParagraph002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount](){ callPushStyleCount++; });

    EXPECT_EQ(callPushStyleCount, 0);

    spanItem->fontStyle->UpdateFontSize(Dimension(1));
    spanItem->fontStyle->UpdateSymbolType(SymbolType::SYSTEM);
    spanItem->UpdateSymbolSpanParagraph(nullptr, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 1);

    spanItem->fontStyle->UpdateSymbolType(SymbolType::CUSTOM);
    spanItem->UpdateSymbolSpanParagraph(nullptr, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 1);

    std::vector<std::string> fontFamilies;
    fontFamilies.push_back(SYMBOL_FONT_FAMILY);
    spanItem->fontStyle->UpdateFontFamily(fontFamilies);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 2);
}

/**
 * @tc.name: UpdateSymbolSpanParagraph003
 * @tc.desc: test span_node.cpp UpdateSymbolSpanParagraph function for customSymbol
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanParagraph003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem->unicode = 100;
    spanItem->UpdateSymbolSpanParagraph(nullptr, TextStyle(), paragraph);
    ASSERT_NE(spanItem->textStyle_, std::nullopt);
    EXPECT_EQ(spanItem->nodeId_, spanItem->textStyle_->GetSymbolUid());
    EXPECT_TRUE(spanItem->textStyle_->isSymbolGlyph_);
}

/**
 * @tc.name: UpdateSymbolSpanColor001
 * @tc.desc: test span_node.cpp UpdateSymbolSpanColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    TextStyle symbolSpanStyle;

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextColor(Color::BLACK);

    spanItem->SetIsParentText(true);
    symbolSpanStyle.propRenderColors_.clear();
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);

    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);

    spanItem->SetIsParentText(false);
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);
}

/**
 * @tc.name: FontRegisterCallback002
 * @tc.desc: test span_node.cpp FontRegisterCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, FontRegisterCallback002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    TextStyle textStyle;
    std::vector<std::string> fontFamilies;

    spanItem->FontRegisterCallback(frameNode, textStyle);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    textStyle.SetFontFamilies(fontFamilies);

    spanItem->FontRegisterCallback(frameNode, textStyle);
    EXPECT_EQ(pattern->GetIsCustomFont(), false);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateTextStyle001
 * @tc.desc: test span_node.cpp UpdateTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode and paragraph.
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetTextDetectEnable(true);
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->position = StringUtils::ToWstring(CREATE_VALUE).length();
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    /**
     * @tc.steps: step2. call StartDrag
     * @tc.expected: IsDragging() return ture
     */
    spanNode->spanItem_->StartDrag(1, 2);
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    /**
     * @tc.steps: step3. call UpdateTextStyle
     * @tc.expected: cover branch content is empty.
     */
    std::u16string spanContent;
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step4. call UpdateTextStyle
     * @tc.expected: cover branch selStart > 0, selEnd < contentLength.
     */
    spanContent = CREATE_VALUE_W;
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step5. call UpdateTextStyle
     * @tc.expected: cover branch selStart < 0, selEnd < 0.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, -1, -1);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step6. call UpdateTextStyle
     * @tc.expected: cover branch selStart > contentLength, selEnd > contentLength.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 20, 20);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    MockParagraph::TearDown();
}

/**
 * @tc.name: UpdateTextStyle002
 * @tc.desc: test span_node.cpp UpdateTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode and paragraph.
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetTextDetectEnable(true);
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->position = StringUtils::ToWstring(CREATE_VALUE).length();
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    /**
     * @tc.steps: step2. call UpdateTextStyle
     * @tc.expected: update text style for three parts.
     */
    std::u16string spanContent = u"0123456789";
    spanNode->spanItem_->selectedStart = 3;
    spanNode->spanItem_->selectedEnd = 6;
    std::u16string part1 = u"012";
    std::u16string part2 = u"345";
    std::u16string part3 = u"6789";
    EXPECT_CALL(*paragraph, AddText(part1)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part2)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part3)).Times(1);
    EXPECT_CALL(*paragraph, PushStyle).Times(3);
    EXPECT_CALL(*paragraph, PopStyle).Times(3);
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 3, 6);
    /**
     * @tc.steps: step3. call UpdateTextStyle
     * @tc.expected: update text style when selStart equals 0.
     */
    spanNode->spanItem_->selectedStart = 0;
    spanNode->spanItem_->selectedEnd = 6;
    part1 = u"012345";
    part2 = u"6789";
    EXPECT_CALL(*paragraph, AddText(part1)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part2)).Times(1);
    EXPECT_CALL(*paragraph, PushStyle).Times(2);
    EXPECT_CALL(*paragraph, PopStyle).Times(2);
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 0, 6);
    /**
     * @tc.steps: step4. call UpdateTextStyle
     * @tc.expected: update text style when selEnd reaches before the end of string.
     */
    spanNode->spanItem_->selectedStart = 3;
    spanNode->spanItem_->selectedEnd = 9;
    part1 = u"012";
    part2 = u"345678";
    part3 = u"9";
    EXPECT_CALL(*paragraph, AddText(part1)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part2)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part3)).Times(1);
    EXPECT_CALL(*paragraph, PushStyle).Times(3);
    EXPECT_CALL(*paragraph, PopStyle).Times(3);
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 3, 9);
    /**
     * @tc.steps: step5. call UpdateTextStyle
     * @tc.expected: update text style when selEnd reaches end of string.
     */
    spanNode->spanItem_->selectedStart = 3;
    spanNode->spanItem_->selectedEnd = 10;
    part2 = u"012";
    part3 = u"3456789";
    EXPECT_CALL(*paragraph, AddText(part2)).Times(1);
    EXPECT_CALL(*paragraph, AddText(part3)).Times(1);
    EXPECT_CALL(*paragraph, PushStyle).Times(2);
    EXPECT_CALL(*paragraph, PopStyle).Times(2);
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 3, 10);
    /**
     * @tc.steps: step6. call UpdateTextStyle
     * @tc.expected: update text style when selStart and selEnd is invalid.
     */
    EXPECT_CALL(*paragraph, AddText).Times(1);
    EXPECT_CALL(*paragraph, PushStyle).Times(2);
    EXPECT_CALL(*paragraph, PopStyle).Times(2);
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, -1, -1);
}

/**
 * @tc.name: EncodeTlv002
 * @tc.desc: test span_node.cpp EncodeTlv function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, EncodeTlv002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<uint8_t> buff;
    int32_t cursor = 1;

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), false);

    cursor = 0;
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), false);

    cursor = 0;
    buff.clear();

    spanItem->fontStyle->UpdateFontSize(Dimension(10.0, DimensionUnit::PX));
    spanItem->fontStyle->UpdateTextColor(Color::WHITE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    spanItem->fontStyle->UpdateTextShadow({ textShadow });
    spanItem->fontStyle->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    spanItem->fontStyle->UpdateSuperscript(SuperscriptStyle::SUBSCRIPT);
    spanItem->fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    spanItem->fontStyle->UpdateFontFamily(fontFamilies);
    spanItem->fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    spanItem->fontStyle->UpdateTextDecoration({TextDecoration::OVERLINE});
    spanItem->fontStyle->UpdateTextDecorationColor(Color::WHITE);
    spanItem->fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    spanItem->fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    spanItem->fontStyle->UpdateAdaptMinFontSize(12.0_fp);
    spanItem->fontStyle->UpdateAdaptMaxFontSize(10.0_fp);
    spanItem->fontStyle->UpdateLetterSpacing(Dimension(10.0, DimensionUnit::PX));
    spanItem->backgroundStyle = TextBackgroundStyle();

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), true);
}

/**
 * @tc.name: EncodeTlv003
 * @tc.desc: test span_node.cpp EncodeTlv function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, EncodeTlv003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<uint8_t> buff;
    int32_t cursor = 0;

    spanItem->textLineStyle->UpdateLineHeight(Dimension(10.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateLineSpacing(Dimension(1.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateTextBaseline(TextBaseline::MIDDLE);
    spanItem->textLineStyle->UpdateBaselineOffset(Dimension(20.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateTextOverflow(TextOverflow::DEFAULT);
    spanItem->textLineStyle->UpdateTextAlign(TextAlign::LEFT);
    spanItem->textLineStyle->UpdateMaxLength(1024);
    spanItem->textLineStyle->UpdateMaxLines(1024);
    spanItem->textLineStyle->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    spanItem->textLineStyle->UpdateTextIndent(Dimension(40, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateLeadingMargin(LeadingMargin());
    spanItem->textLineStyle->UpdateWordBreak(WordBreak::NORMAL);
    spanItem->textLineStyle->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    spanItem->textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);

    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::BLACK;
    textBackgroundStyle.backgroundRadius = NG::BorderRadiusProperty();
    spanItem->backgroundStyle = textBackgroundStyle;

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->textLineStyle->HasLineHeight(), true);
}

/**
 * @tc.name: SymbolColorToString001
 * @tc.desc: test span_node.cpp SymbolColorToString function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, SymbolColorToString001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<Color> colorList;
    colorList.emplace_back(Color::WHITE);
    colorList.emplace_back(Color::BLACK);
    spanItem->fontStyle->UpdateSymbolColorList(colorList);

    EXPECT_EQ(spanItem->SymbolColorToString(), "[#FFFFFFFF,#FF000000,]");
}

/**
 * @tc.name: GetSpanResultObject001
 * @tc.desc: test span_node.cpp GetSpanResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpanResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode.
     */
    RefPtr<ImageSpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->interval = {0, 10};
    auto obj = spanItem->GetSpanResultObject(1, 10);
    EXPECT_FALSE(obj.isInit);
    obj = spanItem->GetSpanResultObject(0, 9);
    EXPECT_FALSE(obj.isInit);
    /**
     * @tc.steps: step2. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image don't have value.
     */
    std::optional<std::string> image;
    std::optional<RefPtr<PixelMap>> pixelMap;
    ImageSpanOptions options1 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options1);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    /**
     * @tc.steps: step3. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image have value.
     */
    image = std::make_optional("app.media.icon");
    pixelMap = PixelMap::CreatePixelMap(nullptr);
    ImageSpanOptions options2 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options2);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    EXPECT_EQ(StringUtils::Str16ToStr8(obj.valueString), image);
    EXPECT_EQ(obj.valuePixelMap, pixelMap.value());
}

/**
 * @tc.name: GetFontInJson001
 * @tc.desc: test text_pattern.cpp GetFontInJson function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetFontInJson001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    textPattern->textStyle_ = TextStyle();

    EXPECT_GT(textPattern->GetFontInJson().size(), 0);

    textPattern->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));

    EXPECT_GT(textPattern->GetFontInJson().size(), 0);
}

/**
 * @tc.name: InitClickEvent001
 * @tc.desc: test text_pattern.cpp InitClickEvent function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, InitClickEvent001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    eventHub->AttachHost(textFrameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    textPattern->InitClickEvent(gestureEventHub);

    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    event.action = KeyAction::DOWN;

    EXPECT_EQ(gestureEventHub->KeyBoardShortCutClick(event, textFrameNode), true);

    auto sysJudgeFunc = gestureEventHub->clickEventActuator_->GetSysJudgeFunc();
    ASSERT_NE(sysJudgeFunc.has_value(), false);

    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    ASSERT_NE(gestureInfo, nullptr);
    auto info = std::make_shared<BaseGestureEvent>();
    ASSERT_NE(info, nullptr);

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::CONTINUE);

    std::list<FingerInfo> fingerList;
    fingerList.emplace_back(FingerInfo());
    info->SetFingerList(fingerList);

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::REJECT);

    textPattern->textDetectEnable_ = true;
    textPattern->copyOption_ = CopyOptions::InApp;
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: SetOnClickMenu001
 * @tc.desc: test text_pattern.cpp SetOnClickMenu function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, SetOnClickMenu001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    bool calledCalculateHandleFunc = false;
    bool calledShowSelectOverlayFunc = false;

    AISpan aiSpan;
    CalculateHandleFunc calculateHandleFunc = [&calledCalculateHandleFunc]() {
        calledCalculateHandleFunc = true;
    };
    ShowSelectOverlayFunc showSelectOverlayFunc = [&calledShowSelectOverlayFunc](const RectF&, const RectF&) {
        calledShowSelectOverlayFunc = true;
    };

    textPattern->SetOnClickMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);

    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    auto func = textPattern->dataDetectorAdapter_->onClickMenu_;
    ASSERT_NE(func, nullptr);

    func("复制");
    EXPECT_EQ(calledCalculateHandleFunc, false);
    EXPECT_EQ(calledShowSelectOverlayFunc, false);

    textPattern->copyOption_ = CopyOptions::InApp;
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);

    func("");
    func("复制");
    func("选择文本");

    calledCalculateHandleFunc = false;
    calledShowSelectOverlayFunc = false;

    textPattern->SetOnClickMenu(aiSpan, nullptr, showSelectOverlayFunc);
    func = textPattern->dataDetectorAdapter_->onClickMenu_;
    ASSERT_NE(func, nullptr);

    func("选择文本");
    EXPECT_EQ(calledCalculateHandleFunc, false);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: test text_pattern.cpp ToJsonValue function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, ToJsonValue001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    InspectorFilter filter;

    auto firstJson = JsonUtil::Create(true);
    ASSERT_NE(firstJson, nullptr);
    textPattern->textStyle_ = TextStyle();

    textPattern->ToJsonValue(firstJson, filter);
    EXPECT_NE(firstJson->ToString(), "{}");

    auto secondJson = JsonUtil::Create(true);
    ASSERT_NE(secondJson, nullptr);
    textPattern->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));

    textPattern->ToJsonValue(secondJson, filter);
    EXPECT_NE(secondJson->ToString(), "{}");

    filter.AddFilterAttr("id");

    auto thirdJson = JsonUtil::Create(true);
    ASSERT_NE(thirdJson, nullptr);

    textPattern->ToJsonValue(thirdJson, filter);
    EXPECT_EQ(thirdJson->ToString(), "{}");
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test text_pattern.cpp GetThumbnailCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetThumbnailCallback001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_EQ(textPattern->dragNode_, nullptr);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    textFrameNode->draggable_ = true;
    textFrameNode->GetEventHub<EventHub>()->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(0, 3);
    textPattern->textForDisplay_ = TEXT_U16CONTENT;

    func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);

    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(childFrameNode, nullptr);
    auto childPattern = childFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(childPattern, nullptr);
    textPattern->childNodes_.emplace_back(childFrameNode);

    func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    auto children = textPattern->GetChildNodes();
    EXPECT_EQ(children.size(), 1);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);
}

/**
 * @tc.name: UpdateRectForSymbolShadow001
 * @tc.desc: test text_pattern.cpp UpdateRectForSymbolShadow function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateRectForSymbolShadow001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    TextModelNG text;
    text.Create(u"text");
    text.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    Shadow textShadow;
    text.SetTextShadow({ textShadow });
    RectF rectsForPlaceholders(0, 0, 10, 10);
    textPattern->UpdateRectForSymbolShadow(rectsForPlaceholders, 1, 1, 1.0);
    EXPECT_EQ(textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(*textLayoutProperty->GetTextShadowValue({ textShadow }).begin(), textShadow);
}

/**
 * @tc.name: UpdateRectForSymbolShadow002
 * @tc.desc: test text_pattern.cpp UpdateRectForSymbolShadow function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateRectForSymbolShadow002, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    TextModelNG text;
    text.Create(u"text");
    text.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    Shadow textShadow;
    text.SetTextShadow({ textShadow });
    RectF rectsForPlaceholders(0, 0, 10, 10);
    textPattern->UpdateRectForSymbolShadow(rectsForPlaceholders, -1, -1, 1.0);
    EXPECT_EQ(textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(*textLayoutProperty->GetTextShadowValue({ textShadow }).begin(), textShadow);
}

/**
 * @tc.name: UpdateContainerChildren001
 * @tc.desc: test text_pattern.cpp UpdateContainerChildren function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateContainerChildren001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto parentNode = AceType::MakeRefPtr<ContainerSpanNode>(1);
    ASSERT_NE(parentNode, nullptr);

    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    frameNode->AddChild(textframeNode);
    textframeNode->SetParent(frameNode);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageSpanNode, nullptr);
    frameNode->AddChild(imageSpanNode);
    imageSpanNode->SetParent(frameNode);
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    frameNode->AddChild(spanNode);
    spanNode->SetParent(frameNode);

    auto imageLayoutProperty = imageSpanNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    pattern->UpdateContainerChildren(parentNode, textframeNode);
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    pattern->UpdateContainerChildren(parentNode, spanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), false);

    spanNode->SetHasTextBackgroundStyle(true);
    pattern->UpdateContainerChildren(parentNode, spanNode);

    imageLayoutProperty->UpdateHasPlaceHolderStyle(true);
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), false);
    imageLayoutProperty->UpdateHasPlaceHolderStyle(false);

    parentNode->SetTextBackgroundStyle(TextBackgroundStyle());
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), true);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test text_pattern.cpp HandleSurfaceChanged function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HandleSurfaceChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->selectOverlay_->OnBind(manager);
    SelectOverlayInfo info;
    manager->CreateSelectOverlay(info);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateMaxLines(0);

    pattern->HandleSurfaceChanged(100, 100, 100, 100, WindowSizeChangeReason::DRAG);
    pattern->HandleSurfaceChanged(100, 100, 10, 100, WindowSizeChangeReason::DRAG);
    pattern->HandleSurfaceChanged(100, 100, 100, 10, WindowSizeChangeReason::DRAG);
    pattern->HandleSurfaceChanged(100, 100, 10, 10, WindowSizeChangeReason::DRAG);

    manager->shareOverlayInfo_->menuInfo.menuType = OptionMenuType::MOUSE_MENU;

    pattern->HandleSurfaceChanged(100, 100, 10, 10, WindowSizeChangeReason::DRAG);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
}

/**
 * @tc.name: MountImageNode001
 * @tc.desc: test text_pattern.cpp MountImageNode function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, MountImageNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);

    imageSpanItem->options.imageAttribute = ImageSpanAttribute();

    pattern->MountImageNode(imageSpanItem);

    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageSpanItem->nodeId_, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), false);

    imageSpanItem->options.imageAttribute->size = ImageSpanSize();
    imageSpanItem->options.imageAttribute->verticalAlign = VerticalAlign();
    imageSpanItem->options.imageAttribute->objectFit = ImageFit();
    imageSpanItem->options.imageAttribute->marginProp = OHOS::Ace::NG::MarginProperty();
    imageSpanItem->options.imageAttribute->borderRadius = OHOS::Ace::NG::BorderRadiusProperty();
    imageSpanItem->options.imageAttribute->paddingProp = OHOS::Ace::NG::PaddingProperty();

    pattern->MountImageNode(imageSpanItem);

    imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageSpanItem->nodeId_, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), true);
}

/**
 * @tc.name: PaintImage001
 * @tc.desc: test text_content_modifier.cpp PaintImage function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, PaintImage001, TestSize.Level1)
{
    auto oldVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);

    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) { callOnDrawCount++; }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);

    bool calledDrawRect = false;
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        auto imagePattern = imageNode->GetPattern<ImagePattern>();
        auto mockCanvasImage = AceType::MakeRefPtr<NG::MockCanvasImage>();
        EXPECT_CALL(
            *mockCanvasImage, DrawRect(_, _, _)).WillRepeatedly([&calledDrawRect]() { calledDrawRect = true; });
        imagePattern->altImage_ = mockCanvasImage;
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        if (i > 0) {
            imageNodeLocalList.emplace_back(imageNode);
        }
    }
    textContentModifier->SetImageSpanNodeList(imageNodeList);

    RSCanvas canvas;

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    std::vector<int32_t> placeholderIndex = { 0 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    calledDrawRect = false;
    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, true);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(oldVersion);
}

/**
 * @tc.name: PaintImage002
 * @tc.desc: test text_content_modifier.cpp PaintImage function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, PaintImage002, TestSize.Level1)
{
    auto oldVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);

    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) { callOnDrawCount++; }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);

    bool calledDrawRect = false;
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        auto imagePattern = imageNode->GetPattern<ImagePattern>();
        auto mockCanvasImage = AceType::MakeRefPtr<NG::MockCanvasImage>();
        EXPECT_CALL(
            *mockCanvasImage, DrawRect(_, _, _)).WillRepeatedly([&calledDrawRect]() { calledDrawRect = true; });
        imagePattern->altImage_ = mockCanvasImage;
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        if (i > 0) {
            imageNodeLocalList.emplace_back(imageNode);
        }
    }
    textContentModifier->SetImageSpanNodeList(imageNodeList);

    std::vector<int32_t> placeholderIndex = { -1 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    RSCanvas canvas;

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    placeholderIndex[0] = 1;
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(oldVersion);
}
} // namespace OHOS::Ace::NG
