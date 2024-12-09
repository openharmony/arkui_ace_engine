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
#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXT_DRAG_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXT_DRAG_TEST_NG_H

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"

#include "test/mock/core/render/mock_paragraph.h"

namespace OHOS::Ace::NG {
struct TextProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyleValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Ace::TextAlign> textAlignValue = std::nullopt;
    std::optional<Ace::TextOverflow> textOverflowValue = std::nullopt;
    std::optional<uint32_t> maxLinesValue = std::nullopt;
    std::optional<Dimension> lineHeightValue = std::nullopt;
    std::optional<Ace::TextDecoration> textDecorationValue = std::nullopt;
    std::optional<Color> textDecorationColorValue = std::nullopt;
    std::optional<Dimension> baselineOffsetValue = std::nullopt;
    std::optional<Ace::TextCase> textCaseValue = std::nullopt;
    std::optional<Dimension> adaptMinFontSize = std::nullopt;
    std::optional<Dimension> adaptMaxFontSize = std::nullopt;
    std::optional<Dimension> letterSpacing = std::nullopt;
    std::optional<Dimension> textIndent = std::nullopt;
    std::optional<Ace::WordBreak> wordBreak = std::nullopt;
    std::optional<std::pair<uint32_t, uint32_t>> textSelectionValue = std::nullopt;
};

struct MockParagraphExpectCallParas {
    std::optional<float> heightValue = std::nullopt;
    std::optional<float> longestLineValue = std::nullopt;
    std::optional<float> maxWidthValue = std::nullopt;
    std::optional<size_t> lineCountValue = std::nullopt;
    std::optional<float> textWidthValue = std::nullopt;
};

class TextDragTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTextWithDragNode(const std::u16string& textContent, const TextProperty& textProperty);
    void SetTextProperty(TextModelNG& model, const TextProperty& textProperty);
    void GetInstance();
    void SetMockParagraphExpectCallParas(MockParagraphExpectCallParas params);
    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPattern> pattern_;
    RefPtr<MockParagraph> paragraph_;
    RefPtr<FrameNode> dragNode_;
    RefPtr<TextDragPattern> dragPattern_;
    RefPtr<RenderContext> dragContext_;
};
} // namespace OHOS::Ace::NG
#endif
