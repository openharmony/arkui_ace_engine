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
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void RichEditorCommonTestNg::AddSpan(const std::string& content)
{
    AddSpan(UtfUtils::Str8ToStr16(content));
}

void RichEditorCommonTestNg::AddSpan(const std::u16string& content)
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
    spanItem->content = u" ";
    spanItem->placeholderIndex = 0;
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto& span : richEditorPattern->spans_) {
        spanTextLength += span->content.length();
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
} // namespace OHOS::Ace::NG