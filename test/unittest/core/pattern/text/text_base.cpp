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

#include "text_base.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {

void TextBases::onClickFunc(const BaseEventInfo* info) {};

void TextBases::onRemoteMessage() {};

void TextBases::OnDragDropFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};

DragDropBaseInfo TextBases::OnDragStartFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)
{
    DragDropBaseInfo temp;
    return temp;
}

void TextBases::SuppressMockParagraph()
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(0.f));
    std::vector<RectF> rects;
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects)); // 2 means second paras
}

std::pair<RefPtr<FrameNode>, RefPtr<TextPattern>> TextBases::Init()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    pattern->AttachToFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, ROOT_NODE_ID, Referenced::MakeRefPtr<RootPattern>());

    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    pattern->clipboard_ = clipboard;
    return { frameNode, pattern };
}

void TextBases::TestUpdateScenario(const RefPtr<TextPattern>& pattern)
{
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(ADAPT_UPDATE_FONTSIZE_VALUE);
    pattern->BeforeCreateLayoutWrapper();
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
}

void TextBases::ConstructSpanItemList1(std::list<RefPtr<SpanItem>>& spans)
{
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> span3 = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> span4 = AceType::MakeRefPtr<SpanItem>();
    span1->content = MULTIPLE_SPAN1_U16;
    spans.emplace_back(span1);

    span2->content = MULTIPLE_SPAN2_U16;
    span2->textLineStyle->UpdateTextAlign(TextAlign::CENTER);
    span2->textLineStyle->UpdateMaxLines(1);
    spans.emplace_back(span2);

    span3->content = MULTIPLE_SPAN3_U16;
    span3->textLineStyle->UpdateTextAlign(TextAlign::END);
    span3->textLineStyle->UpdateTextIndent(Dimension(20.0f));
    span3->textLineStyle->UpdateWordBreak(WordBreak::BREAK_ALL);
    span3->textLineStyle->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    spans.emplace_back(span3);

    span4->content = MULTIPLE_SPAN4_U16;
    spans.emplace_back(span4);
}

void TextBases::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextBases::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextBases::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
}

void TextBases::TearDown()
{
    MockParagraph::TearDown();
}

RefPtr<SpanNode> TextBases::CreateSpanNodeWithSetDefaultProperty(const std::u16string& content)
{
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
    return AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<ImageSpanNode> TextBases::CreateImageSpanNode(const ImageSpanNodeProperty& property)
{
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageSpanNode->GetLayoutProperty());
    if (property.imageSrc.has_value()) {
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(property.imageSrc.value()));
    }
    if (property.pixelMap.has_value()) {
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(property.pixelMap.value()));
    }
    if (property.imageFit.has_value()) {
        imageLayoutProperty->UpdateImageFit(property.imageFit.value());
    }
    if (property.verticalAlign.has_value()) {
        imageLayoutProperty->UpdateVerticalAlign(property.verticalAlign.value());
    }
    if (property.margin.has_value()) {
        auto geometryNode = imageSpanNode->GetGeometryNode();
        geometryNode->UpdateMargin(property.margin.value());
    }
    return imageSpanNode;
}

RefPtr<FrameNode> TextBases::CreateTextParagraph(const std::u16string& createValue, const TestProperty& testProperty)
{
    TextModelNG textModel;
    textModel.Create(createValue);
    if (testProperty.fontSizeValue.has_value()) {
        textModel.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        textModel.SetTextColor(testProperty.textColorValue.value());
    }
    if (testProperty.italicFontStyleValue.has_value()) {
        textModel.SetItalicFontStyle(testProperty.italicFontStyleValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        textModel.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        textModel.SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.textAlignValue.has_value()) {
        textModel.SetTextAlign(testProperty.textAlignValue.value());
    }
    if (testProperty.textOverflowValue.has_value()) {
        textModel.SetTextOverflow(testProperty.textOverflowValue.value());
    }
    if (testProperty.maxLinesValue.has_value()) {
        textModel.SetMaxLines(testProperty.maxLinesValue.value());
    }
    if (testProperty.lineHeightValue.has_value()) {
        textModel.SetLineHeight(testProperty.lineHeightValue.value());
    }
    if (testProperty.lineSpacingValue.has_value()) {
        textModel.SetLineSpacing(testProperty.lineSpacingValue.value());
    }
    if (testProperty.isOnlyBetweenLines.has_value()) {
        textModel.SetIsOnlyBetweenLines(testProperty.isOnlyBetweenLines.value());
    }
    if (testProperty.textDecorationValue.has_value()) {
        textModel.SetTextDecoration(testProperty.textDecorationValue.value());
    }
    if (testProperty.textDecorationColorValue.has_value()) {
        textModel.SetTextDecorationColor(testProperty.textDecorationColorValue.value());
    }
    if (testProperty.baselineOffsetValue.has_value()) {
        textModel.SetBaselineOffset(testProperty.baselineOffsetValue.value());
    }
    if (testProperty.textCaseValue.has_value()) {
        textModel.SetTextCase(testProperty.textCaseValue.value());
    }
    if (testProperty.adaptMinFontSize.has_value()) {
        textModel.SetAdaptMinFontSize(testProperty.adaptMinFontSize.value());
    }
    if (testProperty.adaptMaxFontSize.has_value()) {
        textModel.SetAdaptMaxFontSize(testProperty.adaptMaxFontSize.value());
    }
    if (testProperty.letterSpacing.has_value()) {
        textModel.SetLetterSpacing(testProperty.letterSpacing.value());
    }
    if (testProperty.textIndent.has_value()) {
        textModel.SetTextIndent(testProperty.textIndent.value());
    }
    if (testProperty.wordBreak.has_value()) {
        textModel.SetWordBreak(testProperty.wordBreak.value());
    }
    if (testProperty.lineBreakStrategy.has_value()) {
        textModel.SetLineBreakStrategy(testProperty.lineBreakStrategy.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

void TextBases::SetContentModifier(TextContentModifier& textContentModifier)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContextRefPtr();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());

    textContentModifier.SetFontWeight(Ace::FontWeight::W200);
    textContentModifier.SetTextColor(TEXT_COLOR_VALUE);
    textContentModifier.SetTextDecorationColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textContentModifier.SetTextShadow({ textShadow });
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE, textStyle);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE, textStyle);
    OffsetF paintOffset;
    textContentModifier.SetPrintOffset(paintOffset);
}

void TextBases::SetPaintMethodModifier(TextPaintMethod& textPaintMethod)
{
    textPaintMethod.textContentModifier_->fontSize_ = ADAPT_FONT_SIZE_VALUE;
    textPaintMethod.textContentModifier_->fontWeight_ = FontWeight::LIGHTER;
    textPaintMethod.textContentModifier_->textColor_ = TEXT_COLOR_VALUE;
    textPaintMethod.textContentModifier_->AddDefaultShadow();
    textPaintMethod.textContentModifier_->textDecorationColorAlpha_ =
        AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0f);
    textPaintMethod.textContentModifier_->textDecoration_ = TextDecoration::NONE;
    textPaintMethod.textContentModifier_->baselineOffset_ = BASELINE_OFFSET_VALUE;
}

void TextBases::UpdateTextLayoutProperty(RefPtr<TextLayoutProperty> textLayoutProperty)
{
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration({TextDecoration::OVERLINE});
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);
    textLayoutProperty->UpdateWordBreak(TEXT_WORD_BREAK);
    textLayoutProperty->UpdateLineBreakStrategy(TEXT_LINE_BREAK_STRATEGY);
}
} // namespace OHOS::Ace::NG