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

#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/common/clipboard/mock_clip_board.h"

namespace OHOS::Ace::NG {
namespace {
class TextMockClipboardImpl : public MockClipboardImpl {
public:
    explicit TextMockClipboardImpl(const RefPtr<TaskExecutor>& taskExecutor) : MockClipboardImpl(taskExecutor) {}
    ~TextMockClipboardImpl() = default;

    MOCK_METHOD2(AddTextRecord, void(const RefPtr<PasteDataMix>& pasteData, const std::string& selectedStr));
    MOCK_METHOD2(AddSpanStringRecord, void(const RefPtr<PasteDataMix>& pasteData, std::vector<uint8_t>& data));
    MOCK_METHOD2(AddMultiTypeRecord,
        void(const RefPtr<PasteDataMix>& pasteData, const RefPtr<MultiTypeRecordMix>& multiTypeRecord));
    MOCK_METHOD2(SetData, void(const RefPtr<PasteDataMix>& pasteData, CopyOptions copyOption));
};
} // namespace

class TextTestSevenNg : public TextBases {
public:
};

/**
 * @tc.name: CopyTextWithSpanString001
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto mockClipboardImpl = AceType::MakeRefPtr<TextMockClipboardImpl>(pipeline->GetTaskExecutor());
    EXPECT_CALL(*mockClipboardImpl, SetData(_, _)).Times(1);
    EXPECT_CALL(*mockClipboardImpl, AddTextRecord(_, _)).Times(1);
    EXPECT_CALL(*mockClipboardImpl, AddSpanStringRecord(_, _)).Times(1);
    pattern->clipboard_ = mockClipboardImpl;

    pattern->textSelector_.Update(0, 6);
    std::list<RefPtr<NG::SpanItem>> selectSpanItems;
    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->interval = { 0, 7 };
    span0->content = u"012345";
    selectSpanItems.emplace_back(span0);
    selectSpanItems.emplace_back(span0);
    pattern->spans_ = selectSpanItems;
    auto textLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    frameNode->layoutProperty_ = textLayoutProperty;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->isSpanStringMode_ = true;
    pattern->AllocStyledString();
    pattern->HandleOnCopy();
}

/**
 * @tc.name: CopyTextWithSpanString002
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString002, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto mockClipboardImpl = AceType::MakeRefPtr<TextMockClipboardImpl>(pipeline->GetTaskExecutor());
    EXPECT_CALL(*mockClipboardImpl, AddMultiTypeRecord(_, _)).Times(1);
    EXPECT_CALL(*mockClipboardImpl, SetData(_, _)).Times(1);
    pattern->clipboard_ = mockClipboardImpl;

    pattern->textSelector_.Update(0, 6);
    std::list<RefPtr<NG::SpanItem>> selectSpanItems;
    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->interval = { 0, 7 };
    span0->content = u"0123456789";
    span0->position = 7;
    span0->placeholderIndex = -1;
    selectSpanItems.emplace_back(span0);
    pattern->spans_ = selectSpanItems;
    auto textLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    frameNode->layoutProperty_ = textLayoutProperty;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->isSpanStringMode_ = false;
    pattern->AllocStyledString();
    pattern->HandleOnCopy();
}

/**
 * @tc.name: CopyTextWithSpanString003
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto mockClipboardImpl = AceType::MakeRefPtr<TextMockClipboardImpl>(pipeline->GetTaskExecutor());
    EXPECT_CALL(*mockClipboardImpl, AddMultiTypeRecord(_, _)).Times(1);
    EXPECT_CALL(*mockClipboardImpl, SetData(_, _)).Times(1);
    pattern->clipboard_ = mockClipboardImpl;

    pattern->textSelector_.Update(0, 6);
    pattern->textForDisplay_ = u"123456789";
    auto textLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    frameNode->layoutProperty_ = textLayoutProperty;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->isSpanStringMode_ = false;
    pattern->AllocStyledString();
    pattern->HandleOnCopy();
}

/**
 * @tc.name: CopyTextWithSpanString004
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString004, TestSize.Level1)
{
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"123456789");
    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->content = u"123456789";
    std::list<RefPtr<NG::SpanItem>> spansEn;
    spansEn.emplace_back(span0);
    spanStr->spans_ = spansEn;
    std::vector<uint8_t> buff;
    spanStr->EncodeTlv(buff);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();

    EXPECT_EQ(spanStr->GetString(), spanStringDe->GetString());
    EXPECT_EQ(spanStr->spans_.size(), spanStringDe->spans_.size());
}

/**
 * @tc.name: CopyTextWithSpanString005
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString005, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto textLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    std::vector<Shadow> shadow;
    std::vector<std::string> fontFamily = { "FontFamily" };
    FONT_FEATURES_LIST fontFeature;
    textLayoutProperty->UpdateFontSize(Dimension(1));
    textLayoutProperty->UpdateTextColor(Color::RED);
    textLayoutProperty->UpdateTextShadow(shadow);
    textLayoutProperty->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    textLayoutProperty->UpdateFontWeight(FontWeight::W400);
    textLayoutProperty->UpdateFontFamily(fontFamily);
    textLayoutProperty->UpdateFontFeature(fontFeature);
    textLayoutProperty->UpdateTextDecoration(TextDecoration::UNDERLINE);
    textLayoutProperty->UpdateTextDecorationColor(Color::RED);
    textLayoutProperty->UpdateTextDecorationStyle(TextDecorationStyle::DOTTED);
    textLayoutProperty->UpdateTextCase(TextCase::LOWERCASE);
    textLayoutProperty->UpdateAdaptMinFontSize(Dimension(2));
    textLayoutProperty->UpdateAdaptMaxFontSize(Dimension(3));
    textLayoutProperty->UpdateLetterSpacing(Dimension(4));
    textLayoutProperty->UpdateLineHeight(Dimension(5));
    textLayoutProperty->UpdateLineSpacing(Dimension(6));
    textLayoutProperty->UpdateTextBaseline(TextBaseline::BOTTOM);
    textLayoutProperty->UpdateBaselineOffset(Dimension(7));
    textLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateMaxLines(9);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    textLayoutProperty->UpdateTextIndent(Dimension(10));
    textLayoutProperty->UpdateWordBreak(WordBreak::BREAK_ALL);
    textLayoutProperty->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    textLayoutProperty->UpdateEllipsisMode(EllipsisMode::MIDDLE);
    frameNode->layoutProperty_ = textLayoutProperty;
    std::vector<uint8_t> buff;
    pattern->EncodeTlvNoChild("123456789", buff);
    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), "123456789");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
    auto it = spansDe.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "123456789");
    EXPECT_EQ((*it)->interval.first, 0);
    EXPECT_EQ((*it)->interval.second, 9);
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(1));
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value(), shadow);
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), FontWeight::W400);
    EXPECT_EQ((*it)->fontStyle->GetFontFamily().value(), fontFamily);
    EXPECT_EQ((*it)->fontStyle->GetFontFeature().value(), fontFeature);
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::UNDERLINE);
    EXPECT_EQ((*it)->fontStyle->GetTextDecorationColor().value(), Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetTextDecorationStyle().value(), TextDecorationStyle::DOTTED);
    EXPECT_EQ((*it)->fontStyle->GetTextCase().value(), TextCase::LOWERCASE);
    EXPECT_EQ((*it)->fontStyle->GetAdaptMinFontSize().value(), Dimension(2));
    EXPECT_EQ((*it)->fontStyle->GetAdaptMaxFontSize().value(), Dimension(3));
    EXPECT_EQ((*it)->fontStyle->GetLetterSpacing().value(), Dimension(4));
    EXPECT_EQ((*it)->textLineStyle->GetLineHeight().value(), Dimension(5));
    EXPECT_EQ((*it)->textLineStyle->GetLineSpacing().value(), Dimension(6));
    EXPECT_EQ((*it)->textLineStyle->GetTextBaseline().value(), TextBaseline::BOTTOM);
    // text's baselineOffset attribute is not span's baselineOffset attribute
    EXPECT_FALSE((*it)->textLineStyle->HasBaselineOffset());
    EXPECT_EQ((*it)->textLineStyle->GetTextOverflow().value(), TextOverflow::CLIP);
    EXPECT_EQ((*it)->textLineStyle->GetTextAlign().value(), TextAlign::CENTER);
    EXPECT_EQ((*it)->textLineStyle->GetMaxLines().value(), 9);
    EXPECT_EQ((*it)->textLineStyle->GetHeightAdaptivePolicy().value(), TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ((*it)->textLineStyle->GetTextIndent().value(), Dimension(10));
    EXPECT_EQ((*it)->textLineStyle->GetWordBreak().value(), WordBreak::BREAK_ALL);
    EXPECT_EQ((*it)->textLineStyle->GetLineBreakStrategy().value(), LineBreakStrategy::GREEDY);
    EXPECT_EQ((*it)->textLineStyle->GetEllipsisMode().value(), EllipsisMode::MIDDLE);
}

/**
 * @tc.name: CopyTextWithSpanString006
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString006, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();

    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->content = u"123456789";
    span0->position = 9;
    span0->length = 9;
    std::list<RefPtr<NG::SpanItem>> spansEn;
    spansEn.emplace_back(span0);
    pattern->spans_ = spansEn;
    std::vector<uint8_t> buff;
    pattern->textSelector_.Update(0, 9);
    pattern->EncodeTlvSpanItems("123456789", buff);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), "123456789");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
}

/**
 * @tc.name: CopyTextWithSpanString007
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString007, TestSize.Level1)
{
    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->content = u"123456789";
    span0->interval.first = 0;
    span0->interval.second = 9;
    std::vector<Shadow> shadow;
    std::vector<std::string> fontFamily = { "FontFamily" };
    FONT_FEATURES_LIST fontFeature;
    span0->fontStyle->UpdateFontSize(Dimension(1));
    span0->fontStyle->UpdateTextColor(Color::RED);
    span0->fontStyle->UpdateTextShadow(shadow);
    span0->fontStyle->UpdateItalicFontStyle(Ace::FontStyle::NORMAL);
    span0->fontStyle->UpdateFontWeight(FontWeight::W400);
    span0->fontStyle->UpdateFontFamily(fontFamily);
    span0->fontStyle->UpdateFontFeature(fontFeature);
    span0->fontStyle->UpdateTextDecoration(TextDecoration::UNDERLINE);
    span0->fontStyle->UpdateTextDecorationColor(Color::RED);
    span0->fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::DOTTED);
    span0->fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    span0->fontStyle->UpdateAdaptMinFontSize(Dimension(2));
    span0->fontStyle->UpdateAdaptMaxFontSize(Dimension(3));
    span0->fontStyle->UpdateLetterSpacing(Dimension(4));
    span0->textLineStyle->UpdateLineHeight(Dimension(5));
    span0->textLineStyle->UpdateLineSpacing(Dimension(6));
    span0->textLineStyle->UpdateTextBaseline(TextBaseline::BOTTOM);
    span0->textLineStyle->UpdateBaselineOffset(Dimension(7));
    span0->textLineStyle->UpdateTextOverflow(TextOverflow::CLIP);
    span0->textLineStyle->UpdateTextAlign(TextAlign::CENTER);
    span0->textLineStyle->UpdateMaxLines(9);
    span0->textLineStyle->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    span0->textLineStyle->UpdateTextIndent(Dimension(10));
    span0->textLineStyle->UpdateWordBreak(WordBreak::BREAK_ALL);
    span0->textLineStyle->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    span0->textLineStyle->UpdateEllipsisMode(EllipsisMode::MIDDLE);
    auto span1 = span0->GetSameStyleSpanItem(true);
    span1->content = u"123456789";
    span1->interval.first = 0;
    span1->interval.second = 9;

    std::vector<uint8_t> buff;
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteInt32(buff, 1);
    TLVUtil::WriteInt32(buff, static_cast<int32_t>(NG::SpanItemType::NORMAL));
    span1->EncodeTlv(buff);
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(buff, "123456789");
    TLVUtil::WriteUint8(buff, TLV_END);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), "123456789");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
    auto it = spansDe.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), "123456789");
    EXPECT_EQ((*it)->interval.first, 0);
    EXPECT_EQ((*it)->interval.second, 9);
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(1));
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value(), shadow);
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), FontWeight::W400);
    EXPECT_EQ((*it)->fontStyle->GetFontFamily().value(), fontFamily);
    EXPECT_EQ((*it)->fontStyle->GetFontFeature().value(), fontFeature);
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::UNDERLINE);
    EXPECT_EQ((*it)->fontStyle->GetTextDecorationColor().value(), Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetTextDecorationStyle().value(), TextDecorationStyle::DOTTED);
    EXPECT_EQ((*it)->fontStyle->GetTextCase().value(), TextCase::LOWERCASE);
    EXPECT_EQ((*it)->fontStyle->GetAdaptMinFontSize().value(), Dimension(2));
    EXPECT_EQ((*it)->fontStyle->GetAdaptMaxFontSize().value(), Dimension(3));
    EXPECT_EQ((*it)->fontStyle->GetLetterSpacing().value(), Dimension(4));
    EXPECT_EQ((*it)->textLineStyle->GetLineHeight().value(), Dimension(5));
    EXPECT_EQ((*it)->textLineStyle->GetLineSpacing().value(), Dimension(6));
    EXPECT_EQ((*it)->textLineStyle->GetTextBaseline().value(), TextBaseline::BOTTOM);
    EXPECT_EQ((*it)->textLineStyle->GetBaselineOffset().value(), Dimension(7));
    EXPECT_EQ((*it)->textLineStyle->GetTextOverflow().value(), TextOverflow::CLIP);
    EXPECT_EQ((*it)->textLineStyle->GetTextAlign().value(), TextAlign::CENTER);
    EXPECT_EQ((*it)->textLineStyle->GetMaxLines().value(), 9);
    EXPECT_EQ((*it)->textLineStyle->GetHeightAdaptivePolicy().value(), TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ((*it)->textLineStyle->GetTextIndent().value(), Dimension(10));
    EXPECT_EQ((*it)->textLineStyle->GetWordBreak().value(), WordBreak::BREAK_ALL);
    EXPECT_EQ((*it)->textLineStyle->GetLineBreakStrategy().value(), LineBreakStrategy::GREEDY);
    EXPECT_EQ((*it)->textLineStyle->GetEllipsisMode().value(), EllipsisMode::MIDDLE);
}

/**
 * @tc.name: CopyTextWithSpanString008
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString008, TestSize.Level1)
{
    auto span0 = AceType::MakeRefPtr<ImageSpanItem>();
    span0->content = u" ";
    span0->interval.first = 0;
    span0->interval.second = 1;
    ImageSpanOptions options;
    options.offset = 1;
    options.image = "iamge";
    options.bundleName = "bundleName";
    options.moduleName = "moduleName";
    span0->options = options;

    auto span1 = span0->GetSameStyleSpanItem(true);
    span1->content = u" ";
    span1->interval.first = 0;
    span1->interval.second = 1;

    std::vector<uint8_t> buff;
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteInt32(buff, 1);
    TLVUtil::WriteInt32(buff, static_cast<int32_t>(NG::SpanItemType::IMAGE));
    span1->EncodeTlv(buff);
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(buff, " ");
    TLVUtil::WriteUint8(buff, TLV_END);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), " ");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
    auto it = spansDe.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), " ");
    if ((*it)->spanItemType == SpanItemType::IMAGE) {
        auto spanDe = AceType::DynamicCast<ImageSpanItem>(*it);
        EXPECT_EQ(spanDe->options.image, "iamge");
        EXPECT_EQ(spanDe->options.bundleName, "bundleName");
        EXPECT_EQ(spanDe->options.moduleName, "moduleName");
    }
}

/**
 * @tc.name: CopyTextWithSpanString009
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString009, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<FrameNode> frameNode =
        ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    stack->Push(frameNode);

    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.src_ = "iamge";
    imageSourceInfo.bundleName_ = "bundleName";
    imageSourceInfo.moduleName_ = "moduleName";
    imageSourceInfo.pixmap_ = AceType::MakeRefPtr<MockPixelMap>();
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    MarginProperty marginProperty;
    imageLayoutProperty->UpdateMargin(marginProperty);
    MarginProperty paddingProperty;
    imageLayoutProperty->UpdatePadding(paddingProperty);
    imageLayoutProperty->UpdateVerticalAlign(VerticalAlign::BOTTOM);
    imageLayoutProperty->UpdateImageFit(ImageFit::BOTTOM);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1), CalcLength(2)));
    frameNode->layoutProperty_ = imageLayoutProperty;
    auto renderContext = frameNode->GetRenderContext();
    BorderRadiusProperty borderRadius;
    renderContext->UpdateBorderRadius(borderRadius);
    frameNode->renderContext_ = renderContext;

    auto span0 = AceType::MakeRefPtr<ImageSpanItem>();
    span0->content = u" ";
    span0->interval.first = 0;
    span0->interval.second = 1;
    span0->imageNodeId = 1;
    auto span1 = span0->GetSameStyleSpanItem(true);
    span1->content = u" ";
    span1->interval.first = 0;
    span1->interval.second = 1;

    std::vector<uint8_t> buff;
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteInt32(buff, 1);
    TLVUtil::WriteInt32(buff, static_cast<int32_t>(NG::SpanItemType::IMAGE));
    span1->EncodeTlv(buff);
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(buff, " ");
    TLVUtil::WriteUint8(buff, TLV_END);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), " ");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
    auto it = spansDe.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), " ");
    if ((*it)->spanItemType == SpanItemType::IMAGE) {
        auto spanDe = AceType::DynamicCast<ImageSpanItem>(*it);
        EXPECT_EQ(spanDe->options.image, "iamge");
        EXPECT_EQ(spanDe->options.bundleName, "bundleName");
        EXPECT_EQ(spanDe->options.moduleName, "moduleName");
    }
}

/**
 * @tc.name: CopyTextWithSpanString010
 * @tc.desc: test sr CopyTextWithSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, CopyTextWithSpanString010, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<FrameNode> frameNode =
        ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    stack->Push(frameNode);

    auto imageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    auto span0 = AceType::MakeRefPtr<ImageSpanItem>();
    span0->content = u" ";
    span0->interval.first = 0;
    span0->interval.second = 1;
    span0->imageNodeId = 1;
    auto span1 = span0->GetSameStyleSpanItem(true);
    span1->content = u" ";
    span1->interval.first = 0;
    span1->interval.second = 1;

    std::vector<uint8_t> buff;
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteInt32(buff, 1);
    TLVUtil::WriteInt32(buff, static_cast<int32_t>(span1->spanItemType));
    span1->EncodeTlv(buff);
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    TLVUtil::WriteUint8(buff, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(buff, " ");
    TLVUtil::WriteUint8(buff, TLV_END);

    auto spanStringDe = SpanString::DecodeTlv(buff);
    std::list<RefPtr<NG::SpanItem>> spansDe = spanStringDe->GetSpanItems();
    EXPECT_EQ(spanStringDe->GetString(), " ");
    EXPECT_EQ(spanStringDe->spans_.size(), 1);
    auto it = spansDe.begin();
    EXPECT_EQ(StringUtils::Str16ToStr8((*it)->content), " ");
    if ((*it)->spanItemType == SpanItemType::NORMAL) {
        auto spanDe = AceType::DynamicCast<SpanItem>(*it);
        EXPECT_EQ(spanDe->interval.first, 0);
        EXPECT_EQ(spanDe->interval.second, 1);
        EXPECT_EQ(StringUtils::Str16ToStr8(spanDe->content), " ");
    }
}


/**
 * @tc.name: InheritParentTextStyle001
 * @tc.desc: test InheritParentTextStyle of multiple paragraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, InheritParentTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct a minimal version 10.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE)); // 12 means min platformVersion.
    TextStyle textStyleBase;
    textStyleBase.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    auto multipleAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    multipleAlgorithm->textStyle_ = textStyleBase;

    /**
     * @tc.steps: step2. Construct MultipleParagraphLayoutAlgorithm and test inheritTextStyle_.
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    multipleAlgorithm->InheritParentTextStyle(textStyle);
    EXPECT_EQ(multipleAlgorithm->inheritTextStyle_.GetFontSize(), ADAPT_FONT_SIZE_VALUE);

    /**
     * @tc.steps: step3. Construct a minimal version 16 and test inheritTextStyle_.
     */
    int originApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN)); // 16 means min platformVersion.

    textStyle.SetFontSize(FONT_SIZE_VALUE);
    multipleAlgorithm->InheritParentTextStyle(textStyle);
    MockContainer::Current()->SetApiTargetVersion(originApiVersion);
    EXPECT_EQ(multipleAlgorithm->inheritTextStyle_.GetFontSize(), FONT_SIZE_VALUE);
}

/**
 * @tc.name: SpanBuildParagraph001
 * @tc.desc: test InheritParentTextStyle of multiple paragraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSevenNg, SpanBuildParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct textLayoutAlgorithm with span.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE)); // 12 means min platformVersion.
    std::list<RefPtr<NG::SpanItem>> selectSpanItems;
    auto span0 = AceType::MakeRefPtr<SpanItem>();
    span0->interval = { 0, 7 };
    span0->content = u"012345";
    selectSpanItems.emplace_back(span0);
    selectSpanItems.emplace_back(span0);
    auto pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager_, nullptr);
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>(selectSpanItems, pManager_, true);
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetHeight(RK356_HEIGHT);
    contentConstraint.maxSize.SetWidth(RK356_WIDTH);

    /**
     * @tc.steps: step2. test span MAX_LINES_FIRST.
     */
    TextStyle textStyle;
    textStyle.SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textStyle.SetFontSize(FONT_SIZE_VALUE);

    textLayoutAlgorithm->BuildParagraph(
        textStyle, textLayoutProperty, contentConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);

    int originApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN)); // 16 means min platformVersion.

    textLayoutAlgorithm->BuildParagraph(
        textStyle, textLayoutProperty, contentConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    MockContainer::Current()->SetApiTargetVersion(originApiVersion);
    EXPECT_EQ(textStyle.GetFontSize(), ADAPT_MAX_FONT_SIZE_VALUE);
}
} // namespace OHOS::Ace::NG