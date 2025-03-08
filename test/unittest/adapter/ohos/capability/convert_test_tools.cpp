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
#include "test/unittest/adapter/ohos/capability/convert_test_tools.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

void HtmlConvertTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void HtmlConvertTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void HtmlConvertTestNg::SetUp() {}

void HtmlConvertTestNg::TearDown() {}

ImageSpanOptions HtmlConvertTestNg::GetImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    // margins len 10.0
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    // paddings len 5.0
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .size = size,
        .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

SpanParagraphStyle HtmlConvertTestNg::GetDefaultParagraphStyle()
{
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    // default max lines 4
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    // defalut textIndent 23
    spanParagraphStyle.textIndent = Dimension(23.0_vp);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    // default width 25.0 height 26.0
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0_vp), Dimension(26.0));
    return spanParagraphStyle;
}

bool HtmlConvertTestNg::IsSpanItemSame(std::list<RefPtr<NG::SpanItem>> src, std::list<RefPtr<NG::SpanItem>> other)
{
    if (src.size() != other.size()) {
        return false;
    }

    while (src.size() != 0) {
        auto it = src.front();
        auto otherIt = other.front();
        if (it->interval.first != otherIt->interval.first || it->interval.second != otherIt->interval.second ||
            it->content != otherIt->content) {
            return false;
        }
        src.pop_front();
        other.pop_front();
    }
    return true;
}

ImageSpanOptions HtmlConvertTestNg::GetImageOption(
    const std::string& src,
    const Dimension& width,
    const Dimension& height,
    ImageFit fit,
    VerticalAlign align,
    const BorderRadiusProperty& borderRadius,
    const MarginProperty& margins,
    const PaddingProperty& paddings
)
{
    ImageSpanSize size { width, height };
    
    BorderRadiusProperty customBorderRadius = borderRadius;
    MarginProperty customMargins = margins;
    PaddingProperty customPaddings = paddings;
    
    ImageSpanAttribute attr {
        .size = size,
        .paddingProp = customPaddings,
        .marginProp = customMargins,
        .borderRadius = customBorderRadius,
        .objectFit = fit,
        .verticalAlign = align
    };

    ImageSpanOptions option {
        .image = src,
        .imageAttribute = attr
    };

    return option;
}
};