/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_layout_algorithm.h"

#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::OnReset() {}

void TextLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper) {}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    return SizeF(1.0f, 1.0f);
}

bool TextLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper)
{
    return true;
}

bool TextLayoutAlgorithm::CreateParagraphAndLayout(const TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    return true;
}

bool TextLayoutAlgorithm::AdaptMinTextSize(TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline, LayoutWrapper* layoutWrapper)
{
    return true;
}

bool TextLayoutAlgorithm::DidExceedMaxLines(const SizeF& maxSize)
{
    return true;
}

TextDirection TextLayoutAlgorithm::GetTextDirection(const std::string& content)
{
    return TextDirection::LTR;
}

float TextLayoutAlgorithm::GetTextWidth() const
{
    return 0.0f;
}

const RefPtr<Paragraph>& TextLayoutAlgorithm::GetParagraph()
{
    return paragraph_;
}

float TextLayoutAlgorithm::GetBaselineOffset() const
{
    return baselineOffset_;
}

SizeF TextLayoutAlgorithm::GetMaxMeasureSize(const LayoutConstraintF& contentConstraint) const
{
    return SizeF(1.0f, 1.0f);
}

std::list<RefPtr<SpanItem>>&& TextLayoutAlgorithm::GetSpanItemChildren()
{
    return std::move(spanItemChildren_);
}

std::optional<TextStyle> TextLayoutAlgorithm::GetTextStyle() const
{
    return std::optional<TextStyle>(TextStyle());
}

size_t TextLayoutAlgorithm::GetLineCount() const
{
    return size_t();
}

void TextLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper) {}

void TextLayoutAlgorithm::GetPlaceholderRects(std::vector<RectF>& rects) {}

ParagraphStyle TextLayoutAlgorithm::GetParagraphStyle(const TextStyle& textStyle, const std::string& content) const
{
    return {};
}

void TextLayoutAlgorithm::ApplyIndent(const TextStyle& textStyle, double width) {}
} // namespace OHOS::Ace::NG
